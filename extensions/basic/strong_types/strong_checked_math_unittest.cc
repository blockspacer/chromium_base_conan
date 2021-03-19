#include "basic/strong_types/strong_checked_math.h"

#include "base/logging.h"

#include <cstddef>
#include <cstdint>

#include "testing/gtest/include/gtest/gtest.h"

using namespace base;
using namespace base::internal;


namespace basic {

STRONG_CHECKED_NUMERIC(Gigabytes, int);

template<typename T>
using GigabytesTyped = basic::StrongCheckedNumeric<class STRONG_CHECKED_NUMERIC_TAG(Gigabytes), T>;

} // namespace basic

namespace base {
namespace internal {

template <typename U>
U GetNumericValueForTest(const CheckedNumeric<U>& src) {
  return src.state_.value();
}

template <typename U>
U GetNumericValueForTest(const U& src) {
  return src;
}

} // namespace base
} // namespace internal

namespace basic {

// Logs the ValueOrDie() failure instead of crashing.
struct LogOnFailure {
  template <typename T>
  static T HandleFailure() {
    LOG(WARNING) << "ValueOrDie() failed unexpectedly.";
    return T();
  }
};

template <typename T>
constexpr T GetValue(const T& src) {
  return src;
}

template <typename T, typename U>
constexpr T GetValueAsDest(const U& src) {
  return static_cast<T>(src);
}

template <typename T>
constexpr T GetValue(const GigabytesTyped<T>& src) {
  return src.template ValueOrDie<T, LogOnFailure>();
}

template <typename T, typename U>
constexpr T GetValueAsDest(const GigabytesTyped<U>& src) {
  return src.template ValueOrDie<T, LogOnFailure>();
}

// We have to handle promotions, so infer the underlying type below from actual.
#define TEST_STRONG_EXPECTED_VALUE(expected, actual)                               \
  EXPECT_EQ(GetValue(expected), GetValueAsDest<decltype(expected)>(actual)) \
      << "Result test: Value " << GetNumericValueForTest(actual);

TEST(StrongCheckedNumericTest, Simple) {
  Gigabytes valA(1);
  valA += 1;
  TEST_STRONG_EXPECTED_VALUE(2, valA);

  Gigabytes valB = 1 + Gigabytes(1);
  TEST_STRONG_EXPECTED_VALUE(2, valB);

  Gigabytes valC = valA + valB;
  TEST_STRONG_EXPECTED_VALUE(4, valC);
}

}  // namespace basic
