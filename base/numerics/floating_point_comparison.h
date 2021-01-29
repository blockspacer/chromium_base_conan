#pragma once

#include <cmath>
#include <limits>

// Comparing floating point numbers for depends on the context.
// Since even changing the order of operations can produce different results,
// it is important to know how "equal" you want the numbers to be.
//
// Comparing floating point numbers by Bruce Dawson
// is a good place to start when looking at floating point comparison.
// https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition

// I found that the Google C++ Testing Framework contains a nice
// cross-platform template-based implementation of AlmostEqual2sComplement
// which works on both doubles and floats.
// See:
// cygnus-software.com/papers/comparingfloats/comparingfloats.htm
// googletest/blob/master/googletest/include/gtest/internal/gtest-internal.h#L232
// googletest/blob/master/googletest/include/gtest/internal/gtest-port.h#L2452

// macro to test if numbers are equal within a small error margin
//
// USAGE
//
// bool res1 = NEAR_EQUAL_BY_EPSILON(1.1, 1.1, std::numeric_limits<double>::epsilon());
// bool res2 = NEAR_EQUAL_BY_EPSILON(1.1f, 1.1f, std::numeric_limits<float>::epsilon());
//
#define NEAR_EQUAL_BY_EPSILON(lhs, rhs, epsilon) \
  std::fabs((lhs) - (rhs)) < (epsilon)

namespace base {

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

} // namespace base
