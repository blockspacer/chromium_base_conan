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

#include "basic/numerics/double_summation.h"

#include <cmath>

using namespace base;

namespace basic {

// Even if the conditions are not satisfied, 2Sum and Fast2Sum often provide
// reasonable approximations to the error,  which enables algorithms
// for compensated summation, dot-product, etc.,
// to have low error even if the inputs are not sorted
// or the rounding mode is unusual.
#define ENABLE_FAST2SUM_CHECK 0

#if ENABLE_FAST2SUM_CHECK
#define DCHECK_FAST2SUM(x) DCHECK(x)
#define DCHECK_LE_FAST2SUM(x, y) DCHECK_LE(x, y)
#else
#define DCHECK_FAST2SUM(x) EAT_CHECK_STREAM_PARAMS(!(x))
#define DCHECK_LE_FAST2SUM(x, y) EAT_CHECK_STREAM_PARAMS(!(x <= y))
#endif

DoubleDouble computeFast2Sum(double a, double b, bool auto_swap) {
  if(auto_swap && std::fabs(b) > std::fabs(a)) {
    double tmp = a;
    b = a;
    a = tmp;
  }

#if ENABLE_FAST2SUM_CHECK
  if (std::isfinite(a) && std::isfinite(b)) {
    DCHECK_LE_FAST2SUM(std::fabs(b), std::fabs(a));
  } else {
    DCHECK_FAST2SUM(false)
      << "numbers not finite"
      << " a = "
      << a
      << " b = "
      << b;
  }
#endif // ENABLE_FAST2SUM_CHECK

  double s = a + b;

  // a+b must result in a normal floating point number with no overflow
  DCHECK_FAST2SUM(std::isfinite(s));

  double z = s - a;
  double t = b - z;
  return {s, t};
}

DoubleDouble compute2Sum(double a, double b) {
  double s = a + b;
  double aPrime = s - b;
  double bPrime = s - aPrime;
  double deltaA = a - aPrime;
  double deltaB = b - bPrime;
  double t = deltaA + deltaB;
  return {s, t};
}

void DoubleDoubleSummation::addLong(long long x) {
  // Split 64-bit integers into two doubles, so the sum remains exact.
  int64_t high = x / (1ll << 32) * (1ll << 32);
  int64_t low = x - high;
  DCHECK(high + low == x && 1.0 * high == high && 1.0 * low == low);
  addDouble(low);
  addDouble(high);
}

/**
 * Returns whether the sum is in range of the 64-bit signed integer long long type.
 */
bool DoubleDoubleSummation::fitsLong() const {
  using limits = std::numeric_limits<long long>;
  // Fast path: if the rounded _sum is strictly between the minimum and maximum long long value,
  // it must be valid. This is the common case. Note that this is correct for NaNs/infinities.
  if (_sum > limits::min() && _sum < limits::max())
    return true;

  // Now check the cases where the _sum equals one of the boundaries, and check the compensation
  // amount to determine to what integer the value would round.

  // If _sum is equal to limits::max() + 1, _addend must cause us to round down to a lower integer
  // and thus be strictly less than -0.5. limits.max() rounds up to limits.max() + 1, as double
  // precision does not have enough precision.
  if (_sum == limits::max())
    return _addend < -0.5;

  // If _sum is equal to limits::min(), _addend must not cause us to round down and thus be
  // greater than or equal to -0.5.
  if (_sum == limits::min())
    return _addend >= -0.5;

  // The sum is out of range, an infinity or a NaN.
  return false;
}

/**
 * Returns result of sum rounded to nearest integer, rounding half-way cases away from zero.
 */
long long DoubleDoubleSummation::getLong() const {
  DCHECK(fitsLong()) << "sum out of range of a 64-bit signed integer";
  if (_sum == std::numeric_limits<long long>::max()) {
    // Can't directly convert, because _sum would overflow a signed 64-bit number.
    DCHECK(_addend < -0.5 && -_sum == std::numeric_limits<long long>::min());
    return llround(_addend) - std::numeric_limits<long long>::min();
  }
  long long sum = llround(_sum);
  sum += llround((_sum - sum) + _addend);
  return sum;
}

}  // namespace basic
