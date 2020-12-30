/**
 *    Copyright (C) 2018-present MongoDB, Inc.
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the Server Side Public License, version 1,
 *    as published by MongoDB, Inc.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    Server Side Public License for more details.
 *
 *    You should have received a copy of the Server Side Public License
 *    along with this program. If not, see
 *    <http://www.mongodb.com/licensing/server-side-public-license>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the Server Side Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#include <cmath>
#include <limits>
#include <vector>

#include "base/numerics/double_summation.h"
#include "base/callback.h"
#include "base/test/bind_test_util.h"
#include "base/threading/simple_thread.h"
#include GTEST_HEADER_INCLUDE

namespace base {

namespace {
using limits = std::numeric_limits<long long>;
std::vector<long long> longValues = {limits::min(),
                                     limits::min() + 1,
                                     limits::min() / 2,
                                     -(1LL << 53),
                                     -(1LL << 52),
                                     -(1LL << 32),
                                     -0x100,
                                     -0xff,
                                     -0xaa,
                                     -0x55,
                                     -1,
                                     0,
                                     1,
                                     2,
                                     0x55,
                                     0x80,
                                     0xaa,
                                     0x100,
                                     512,
                                     1024,
                                     2048,
                                     1LL << 31,
                                     1LL << 32,
                                     1LL << 52,
                                     1LL << 53,
                                     limits::max() / 2,

#pragma warning(push)
// C4308: negative integral constant converted to unsigned type
#pragma warning(disable : 4308)
                                     static_cast<long long>(1ULL << 63) -
                                         (1ULL << (63 - 53 - 1)),  // Halfway between two doubles
#pragma warning(pop)
                                     limits::max() - 1,
                                     limits::max()};

std::vector<double> doubleValues = {
    1.4831356930199802e-05, -3.121724665346865,     3041897608700.073,       1001318343149.7166,
    -1714.6229586696593,    1731390114894580.8,     6.256645803154374e-08,   -107144114533844.25,
    -0.08839485091750919,   -265119153.02185738,    -0.02450615965231944,    0.0002684331017079073,
    32079040427.68358,      -0.04733295911845742,   0.061381859083076085,    -25329.59126796951,
    -0.0009567520620034965, -1553879364344.9932,    -2.1101077525869814e-08, -298421079729.5547,
    0.03182394834273594,    22.201944843278916,     -33.35667991109125,      11496013.960449915,
    -40652595.33210472,     3.8496066090328163,     2.5074042398147304e-08,  -0.02208724071782122,
    -134211.37290639878,    0.17640433666616578,    4.463787499171126,       9.959669945399718,
    129265976.35224283,     1.5865526187526546e-07, -4746011.710555799,      -712048598925.0789,
    582214206210.4034,      0.025236204812875362,   530078170.91147506,      -14.865307666195053,
    1.6727994895185032e-05, -113386276.03121366,    -6.135827207137054,      10644945799901.145,
    -100848907797.1582,     2.2404406961625282e-08, 1.315662618424494e-09,   -0.832190208349044,
    -9.779323414999364,     -546522170658.2997};

const double doubleValuesSum = 1636336982012512.5;  // simple summation will yield wrong result

std::vector<double> specialValues = {-std::numeric_limits<double>::infinity(),
                                     std::numeric_limits<double>::infinity(),
                                     std::numeric_limits<double>::quiet_NaN()};

}  // namespace

TEST(Summation, AddLongs) {
  int iter = 0;
  for (auto x : longValues) {
    for (auto y : longValues) {
      for (auto z : longValues) {
        iter++;
        DoubleDoubleSummation sum;

        // This checks for correct results mod 2**64, which helps with checking correctness
        // around the 2**53 transition between both doubles of the DoubleDouble result in
        // int64 additions, as well off-by-one errors.
        uint64_t checkUint64 =
            static_cast<uint64_t>(x) + static_cast<uint64_t>(y) + static_cast<uint64_t>(z);

        sum.addLong(x);
        sum.addLong(y);
        sum.addLong(z);
        EXPECT_TRUE(sum.isInteger());

        if (!sum.fitsLong()) {
            EXPECT_TRUE(std::abs(sum.getDouble()) >= limits::max());
            // Reduce sum to fit in a 64-bit integer.
            while (!sum.fitsLong()) {
                sum.addDouble(sum.getDouble() < 0 ? std::ldexp(1, 64) : -std::ldexp(1, 64));
            }
        }
        EXPECT_EQ(static_cast<uint64_t>(sum.getLong()), checkUint64);
      }
    }
  }
}

TEST(Summation, AddSpecial) {
  for (auto x : specialValues) {
    DoubleDoubleSummation sum;

    // Check that a special number will result in that special number.
    sum.addLong(-42);
    sum.addLong(100);
    sum.addDouble(x);
    EXPECT_TRUE(!sum.fitsLong());
    EXPECT_TRUE(!sum.isInteger());
    if (std::isnan(x)) {
      EXPECT_TRUE(std::isnan(sum.getDouble()));
    } else {
      EXPECT_EQ(sum.getDouble(), x);
    }

    // Check that adding more numbers doesn't reset the special value.
    sum.addDouble(-1E22);
    sum.addLong(limits::min());
    EXPECT_TRUE(!sum.fitsLong());
    if (std::isnan(x)) {
      EXPECT_TRUE(std::isnan(sum.getDouble()));
    } else {
      EXPECT_EQ(sum.getDouble(), x);
    }
  }
}

TEST(Summation, AddInvalid) {
  DoubleDoubleSummation sum;
  sum.addDouble(std::numeric_limits<double>::infinity());
  sum.addDouble(-std::numeric_limits<double>::infinity());

  EXPECT_TRUE(std::isnan(sum.getDouble()));
  EXPECT_TRUE(!sum.fitsLong());
  EXPECT_TRUE(!sum.isInteger());
}

TEST(Summation, LongOverflow) {
  DoubleDoubleSummation positive;

  // Overflow should result in number no longer fitting in a long.
  positive.addLong(limits::max());
  positive.addLong(limits::max());
  EXPECT_TRUE(!positive.fitsLong());

  // However, actual stored overflow should not overflow or lose precision.
  positive.addLong(-limits::max());
  EXPECT_EQ(positive.getLong(), limits::max());

  DoubleDoubleSummation negative;

  // Similarly for negative numbers.
  negative.addLong(limits::min());
  negative.addLong(-1);
  EXPECT_TRUE(!negative.fitsLong());
  negative.addDouble(-1.0 * limits::min());
  EXPECT_EQ(negative.getLong(), -1);
}


TEST(Summation, AddDoubles) {
  DoubleDoubleSummation sum;
  double straightSum = 0.0;

  for (auto x : doubleValues) {
    sum.addDouble(x);
    straightSum += x;
  }
  EXPECT_EQ(sum.getDouble(), doubleValuesSum);
  EXPECT_TRUE(straightSum != sum.getDouble());
}

}  // namespace base
