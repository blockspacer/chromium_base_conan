// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#pragma once

#include <cmath>
#include <limits>
#include <cstdint>
#include <type_traits>

#include "base/numerics/double_summation.h"

/// \note In short: On Intel CPU's use `base::almostEqual(1.1, 1.1);`
/// instead of (1.1 == 1.1).
//
// Comparing floating point numbers depends on the context.
// Since even changing the order of operations can produce different results,
// it is important to know how "equal" you want the numbers to be.
//
// Comparing floating point numbers by Bruce Dawson
// is a good place to start when looking at floating point comparison.
// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition
//
// Tolerance is simply a way of stating how much precision you need, or conversely,
// how much error you are willing to accept in your project.
// Tolerances come in two varieties: absolute and relative.
//
// Absolute tolerances are not good if your data has a very large range.
// An absolute tolerance is a fixed number that is used to make direct comparisons.
// Absolute tolerance dictates the greatest permissible distance
// apart that two objects or elements can be and still considered close enough
// i.e. absolute(a-b)
//
// Relative tolerances are good at handling large ranges but poor
// if you have very small values that should be considered as zero.
// Relative tolerance uses the percentage difference between A and B
// i.e. abs(X - Y) / min(abs(X), abs(Y))
//
namespace base {

// macro to test if numbers are equal within a small error margin
//
// USAGE
//
// bool res1 = NEAR_EQUAL_BY_EPSILON(1.1, 1.1, std::numeric_limits<double>::epsilon());
// bool res2 = NEAR_EQUAL_BY_EPSILON(1.1f, 1.1f, std::numeric_limits<float>::epsilon());
//
#define NEAR_EQUAL_BY_EPSILON(lhs, rhs, epsilon) \
  std::fabs((lhs) - (rhs)) < (epsilon)

template<typename T>
bool WithinEpsilon(T a, T b) {
  return NEAR_EQUAL_BY_EPSILON(a, b, std::numeric_limits<T>::epsilon());
}

inline bool ApproximatelyEqualByEpsilon(float a, float b, float test_epsilon) {
  float abs_a = std::fabs(a);
  float abs_b = std::fabs(b);
  float abs_err = std::fabs(a - b);
  if (a == b)
    return true;

  if (a == 0 || b == 0 || abs_err < std::numeric_limits<float>::min())
    return abs_err < (test_epsilon * std::numeric_limits<float>::min());

  return ((abs_err / (abs_a + abs_b)) < test_epsilon);
}

// from The art of computer programming by Knuth
inline bool approximatelyEqual(float a, float b, float epsilon)
{
  return std::fabs(a - b)
    <= ( (std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

// from The art of computer programming by Knuth
inline bool essentiallyEqual(float a, float b, float epsilon)
{
  return std::fabs(a - b)
    <= ( (std::fabs(a) > std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

// from The art of computer programming by Knuth
inline bool definitelyGreaterThan(float a, float b, float epsilon)
{
  return (a - b)
    > ( (std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

// from The art of computer programming by Knuth
inline bool definitelyLessThan(float a, float b, float epsilon)
{
  return (b - a)
    > ( (std::fabs(a) < std::fabs(b) ? std::fabs(b) : std::fabs(a)) * epsilon);
}

// I found that the Google C++ Testing Framework contains a nice
// cross-platform template-based implementation of AlmostEqual2sComplement
// which works on both doubles and floats.
// See:
// cygnus-software.com/papers/comparingfloats/comparingfloats.htm
// googletest/blob/master/googletest/include/gtest/internal/gtest-internal.h#L232
// googletest/blob/master/googletest/include/gtest/internal/gtest-port.h#L2452
//
namespace internal {

/**
 * This class represents an single-precision IEEE floating-point number.
 *
 * The purpose of this class is to do more sophisticated number comparison.
 * Due to round-off error, etc, it's very unlikely that two floating-points will
 * be equal exactly. Hence a naive comparison by the == operation often doesn't
 * work.
 */
class FloatBits {
  typedef uint32_t BitType;

public:
  static const int MAX_ULP = 4;
  static const BitType SIGN_MASK     = 0x80000000UL; // 0 bit.
  static const BitType EXPONENT_MASK = 0x7F800000UL; // 1 ~ 8 bits.
  static const BitType MANTISSA_MASK = 0x007FFFFFUL; // 9 ~ 31 bits.

  explicit FloatBits(float num) {
    u_.value = num;
  }

  /**
   * @return the sign bit of this number.
   */
  BitType sign_bit() const { return SIGN_MASK & u_.bits; }

  /**
   * @return the exponent bits of this number.
   */
  BitType exponent_bits() const { return EXPONENT_MASK & u_.bits; }

  /**
   * @return the mantissa bits of this number (9 ~ 31 bits).
   */
  BitType mantissa_bits() const { return MANTISSA_MASK & u_.bits; }

  /**
   * @return true iff this is NAN (not a number).
   */
  bool is_nan() const {
    return exponent_bits() == EXPONENT_MASK && mantissa_bits() != 0;
  }

  /**
   * Return true iff this number is at most MAX_ULP ULP's away from rhs.
   *
   * In particular, this function:
   *   - returns false if either number is (or both are) NAN.
   *   - treats really large numbers as almost equal to infinity.
   *   - thinks +0.0 and -0.0 are 0 DLP's apart.
   */
  bool operator == (const FloatBits& rhs) const {
    // The IEEE standard says that any comparison operation involving
    // a NAN must return false.
    if (is_nan() || rhs.is_nan()) return false;

    return ULPDistance(u_.bits, rhs.u_.bits) <= MAX_ULP;
  }

private:
  /**
   * Convert an integer from the sign-and-magnitude representation to the
   * biased representation.
   */
  static BitType SignAndMagnitudeToBiased(BitType sam) {
    if (SIGN_MASK & sam) {
      // sam represents a negative number.
      return ~sam + 1;
    } else {
      // sam represents a positive number.
      return SIGN_MASK | sam;
    }
  }

  /**
   * Given two numbers in the sign-and-magnitude representation, return the
   * distance of ULP between them as an unsigned number.
   */
  static BitType ULPDistance(BitType sam1, BitType sam2) {
    BitType biased1 = SignAndMagnitudeToBiased(sam1);
    BitType biased2 = SignAndMagnitudeToBiased(sam2);
    return (biased1 >= biased2) ? (biased1 - biased2) : (biased2 - biased1);
  }

  // The data type used to store the actual floating-point number.
  union FloatUnion {
    float value;   // The raw floating-point number.
    BitType bits;  // The bits that represent the number.
  };

  FloatUnion u_;
};

/**
 * This class represents an double-precision IEEE floating-point number.
 *
 * The purpose of this class is to do more sophisticated number comparison.
 * Due to round-off error, etc, it's very unlikely that two floating-points will
 * be equal exactly. Hence a naive comparison by the == operation often doesn't
 * work.
 */
class DoubleBits {
  typedef uint64_t BitType;

public:
  // The maximum error of a single floating-point operation is 0.5
  // units in the last place.  On Intel CPU's, all floating-point
  // calculations are done with 80-bit precision, while double has 64
  // bits.  Therefore, 4 should be enough for ordinary use.
  static const int MAX_ULP = 4;

  static const BitType SIGN_MASK     = 0x8000000000000000ULL; // 0 bit.
  static const BitType EXPONENT_MASK = 0x7FF0000000000000ULL; // 1 ~ 11 bits.
  static const BitType MANTISSA_MASK = 0x000FFFFFFFFFFFFFULL; // 12 ~ 63 bits.

  explicit DoubleBits(double num) {
    u_.value = num;
  }

  /**
   * @return the sign bit of this number.
   */
  BitType sign_bit() const { return SIGN_MASK & u_.bits; }

  /**
   * @return the exponent bits of this number.
   */
  BitType exponent_bits() const { return EXPONENT_MASK & u_.bits; }

  /**
   * @return the mantissa bits of this number (9 ~ 31 bits).
   */
  BitType mantissa_bits() const { return MANTISSA_MASK & u_.bits; }

  /**
   * @return true iff this is NAN (not a number).
   */
  bool is_nan() const {
    return exponent_bits() == EXPONENT_MASK && mantissa_bits() != 0;
  }

  /**
   * Return true iff this number is at most MAX_ULP ULP's away from rhs.
   *
   * In particular, this function:
   *   - returns false if either number is (or both are) NAN.
   *   - treats really large numbers as almost equal to infinity.
   *   - thinks +0.0 and -0.0 are 0 DLP's apart.
   */
  bool operator == (const DoubleBits& rhs) const {
    // The IEEE standard says that any comparison operation involving
    // a NAN must return false.
    if (is_nan() || rhs.is_nan()) return false;

    return ULPDistance(u_.bits, rhs.u_.bits) <= MAX_ULP;
  }

private:
  /**
   * Convert an integer from the sign-and-magnitude representation to the
   * biased representation.
   */
  static BitType SignAndMagnitudeToBiased(BitType sam) {
    if (SIGN_MASK & sam) {
      // sam represents a negative number.
      return ~sam + 1;
    } else {
      // sam represents a positive number.
      return SIGN_MASK | sam;
    }
  }

  /**
   * Given two numbers in the sign-and-magnitude representation, return the
   * distance of ULP between them as an unsigned number.
   */
  static BitType ULPDistance(BitType sam1, BitType sam2) {
    BitType biased1 = SignAndMagnitudeToBiased(sam1);
    BitType biased2 = SignAndMagnitudeToBiased(sam2);
    return (biased1 >= biased2) ? (biased1 - biased2) : (biased2 - biased1);
  }

  // The data type used to store the actual floating-point number.
  union DoubleUnion {
    double value;  // The raw floating-point number.
    BitType bits;  // The bits that represent the number.
  };

  DoubleUnion u_;
};

} // namespace internal

/**
 * Return true iff 'lhs' is at most 4 away from 'rhs'.
 *
 * In particular, this function:
 *   - returns false if either number is (or both are) NAN;
 *   - treats really large numbers as almost equal to infinity;
 *   - thinks +0.0 and -0.0 are 0 DLP's apart.
 */
inline bool almostEqual(float lhs, float rhs) {
  return internal::FloatBits(lhs) == internal::FloatBits(rhs);
}

/**
 * Similar to the previous one.
 */
inline bool almostEqual(double lhs, double rhs) {
  return internal::DoubleBits(lhs) == internal::DoubleBits(rhs);
}

/// \note uses Fast2Sum algorithm
//
// Return true if and only if the distance from l0 to r0 equals the distance
// from l1 to r1, with real-number mathematics regardless of floating-point
// errors.
//
inline bool DistancesAreEqualByFast2Sum(
  double l0, double r0, double l1, double r1)
{
  //  Find the exact difference of r0 and l0.
  DoubleDouble d0 = computeFast2Sum(r0, -l0, true);

  //  Find the exact difference of r1 and l1.
  DoubleDouble d1 = computeFast2Sum(r1, -l1, true);

  //  Return true if and only if the two differences are equal.
  return d0.first == d1.first && d0.second == d1.second;
}

} // namespace base
