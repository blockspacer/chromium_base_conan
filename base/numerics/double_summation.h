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

#pragma once

#include <cmath>
#include <tuple>
#include <utility>

#include "base/logging.h"

// Many scientific applications require accuracy greater than
// that provided by �double precision�.
// See 2Sum and Fast2Sum formulas for implementation details.
// 2Sum computes the floating-point sum and the floating-point error.
// See:
// * Handbook of Floating-Point Arithmetic
// * Techniques for Floating-Point Arithmetic
//   https://indico.cern.ch/event/313684/contributions/1687773/attachments/600513/826490/FPArith-Part2.pdf
// * Workshop on Numerical Computing Floating-Point Arithmetic
//   https://indico.cern.ch/event/166141/sessions/125684/attachments/201414/282782/Arnold-FPWorkshop-Print.pdf
// * D.E. Knuth. "The Art of Computer Programming: Seminumerical Algorithms". Volume 2. 1981
//
namespace base {

using DoubleDouble = std::pair<double, double>;

/**
 * Assuming |b| <= |a|, returns exact unevaluated sum of a and b,
 * where the first member is the
 * double nearest the sum (ties to even) and the second member is the remainder.
 *
 * T. J. Dekker. A floating-point technique for extending the available precision.
 * Numerische Mathematik, 18(3):224–242, 1971.
 */
inline DoubleDouble computeFast2Sum(double a, double b, bool auto_swap = false) {
  if(auto_swap && std::fabs(b) > std::fabs(a)) {
    double tmp = a;
    b = a;
    a = tmp;
  } else {
    DCHECK_LE(b, a);
  }
  double s = a + b;
  double z = s - a;
  double t = b - z;
  return {s, t};
}

/**
 * TwoSum is usually faster on modern processors than Fast2Sum.
 * returns exact unevaluated sum of a and b,
 * where the first member is the double nearest the
 * sum (ties to even) and the second member is the remainder.
 *
 * O. Møller. Quasi double-precision in floating-point addition. BIT, 5:37–50, 1965.
 * D. Knuth. The Art of Computer Programming, vol 2. Addison-Wesley, Reading, MA, 3rd ed, 1998.
 */
inline DoubleDouble compute2Sum(double a, double b) {
  double s = a + b;
  double aPrime = s - b;
  double bPrime = s - aPrime;
  double deltaA = a - aPrime;
  double deltaB = b - bPrime;
  double t = deltaA + deltaB;
  return {s, t};
}

/**
 * Compensated Summation Based on FastTwoSum and TwoSum techniques
 * Knowledge of the exact rounding error in a
 * floating-point addition is used to correct the summation
 *
 * Class to accurately sum series of numbers using a 2Sum and Fast2Sum formulas to maintain an
 * unevaluated sum of two numbers: a rounded-to-nearest _sum and an _addend.
 * See Sylvie Boldo, Stef Graillat, Jean-Michel Muller. On the robustness of the 2Sum and Fast2Sum
 * algorithms. 2016. https://hal-ens-lyon.archives-ouvertes.fr/ensl-01310023
 */
class DoubleDoubleSummation {
public:
  /**
   * Adds x to the sum, keeping track of a compensation amount to be subtracted later.
   */
  void addDouble(double x) {
    // Keep a simple sum to use in case of NaN
    _special += x;
    // Compensated add: _addend tinier than _sum
    std::tie(x, _addend) = computeFast2Sum(x, _addend);
    // Compensated add: x maybe larger than _sum
    std::tie(_sum, x) = compute2Sum(_sum, x);
    // Store away lowest part of sum
    _addend += x;
  }

  /**
   * Adds x to internal sum. Extra precision guarantees that sum is exact, unless intermediate
   * sums exceed a magnitude of 2**106.
   */
  void addLong(long long x);

  /**
   * Adds x to internal sum. Adds as double as that is more efficient.
   */
  void addInt(int x) {
    addDouble(x);
  }

  /**
   * Returns the double nearest to the accumulated sum.
   */
  double getDouble() const {
    return std::isnan(_sum) ? _special : _sum;
  }

  /**
   * Return a pair of double representing the sum, with first being the nearest double and second
   * the amount to add for full precision.
   */
  DoubleDouble getDoubleDouble() const {
    return std::isnan(_sum) ? DoubleDouble{_special, 0.0} : DoubleDouble{_sum, _addend};
  }

  /**
   * Returns whether the sum is in range of the 64-bit signed integer long long type.
   */
  bool fitsLong() const;

  /**
   * Returns whether the accumulated sum has a fractional part.
   */
  bool isInteger() const {
    return std::trunc(_sum) == _sum && std::trunc(_addend) == _addend;
  }

  /**
   * Returns result of sum rounded to nearest integer, rounding half-way cases away from zero.
   */
  long long getLong() const;

private:
  double _sum = 0.0;
  double _addend = 0.0;

  // Simple sum to be returned if _sum is NaN.
  // This addresses infinities turning into NaNs when
  // using compensated addition.
  double _special = 0.0;
};

}  // namespace base
