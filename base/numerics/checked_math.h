// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_NUMERICS_CHECKED_MATH_H_
#define BASE_NUMERICS_CHECKED_MATH_H_

#include <stddef.h>

#include <limits>
#include <type_traits>

#include "base/numerics/checked_math_impl.h"

// default tag for strong type
#define STRONG_CHECKED_INT_TAG_NAME UniqueCheckedIntTypeTag

// format tag name (concats strings)
#define STRONG_CHECKED_INT_TAG_CUSTOM_2(using_name, suffix) \
  using_name ## _ ## suffix

// STRONG_CHECKED_INT_TAG_CUSTOM(MyType, UniqueTypeTag) expands to `MyType_UniqueTypeTag`
#define STRONG_CHECKED_INT_TAG_CUSTOM(using_name, suffix) \
  STRONG_CHECKED_INT_TAG_CUSTOM_2(using_name,suffix)

/// \note Each `StrongAlias` must have UNIQUE tag.
/// We assume that provided `using_name` globally unique
/// (even between shared libs!)
// STRONG_CHECKED_INT_TAG(MyType) expands to `MyType_UniqueTypeTag`
#define STRONG_CHECKED_INT_TAG(using_name) \
  STRONG_CHECKED_INT_TAG_CUSTOM(using_name,STRONG_CHECKED_INT_TAG_NAME)

#define DECLARE_STRONG_CHECKED_TYPE_WITH_TAG(TAG, NAME, TYPE) \
  using NAME = base::internal::StrongCheckedNumeric<TAG, TYPE>;

// USAGE
// namespace base {
// namespace internal {
// DECLARE_STRONG_CHECKED_TYPE(Gigabytes, int);
// } // namespace base
// } // namespace internal
// using Gigabytes = ::base::internal::Gigabytes;
// // Or with custom type:
// template<typename T>
// using GigabytesTyped = base::StrongCheckedNumeric<class STRONG_CHECKED_INT_TAG(Gigabytes), T>;
// Gigabytes t1(std::numeric_limits<int>::max());
// t1++; // will CRASH
// DLOG(INFO) << t1.ValueOrDie();
// CHECK(t1.ValueOrDie() == std::numeric_limits<int>::max());
#define DECLARE_STRONG_CHECKED_TYPE(NAME, TYPE) \
  DECLARE_STRONG_CHECKED_TYPE_WITH_TAG(class STRONG_CHECKED_INT_TAG(NAME), NAME, TYPE)

#define STRONGLY_TYPED_CHECKED_INT(NAME) \
  DECLARE_STRONG_CHECKED_TYPE(NAME, int)

// USAGE: CHECKED_UNARY_OPERATOR(CheckedAddOp, +=)
#define CHECKED_UNARY_OPERATOR(OP_NAME, OP2)                 \
  template <typename R>                                  \
  constexpr auto& operator OP2 (                         \
      const R rhs) {                                     \
    return MathOp<OP_NAME>(rhs);                         \
  }

#define CHECKED_BINARY_OPERATOR(OP_NAME, OP2) \
  template <typename TagT, typename CheckedT, typename R \
        , typename std::enable_if< \
                !std::is_same<R, base::internal::StrongCheckedNumeric<TagT, CheckedT> >::value \
                && internal::IsCheckedOp<base::internal::StrongCheckedNumeric<TagT, CheckedT>, R>::value \
          >::type* = nullptr \
  > \
  constexpr \
  StrongCheckedNumeric<TagT, typename base::internal::MathWrapper<OP_NAME, typename UnderlyingType<CheckedT>::type, typename UnderlyingType<R>::type >::type> \
  operator OP2 ( \
    const R other \
    , const base::internal::StrongCheckedNumeric<TagT, CheckedT> CheckedVal) \
  { \
    return decltype(CheckedVal OP2 other)::template MathOp<TagT, OP_NAME>(CheckedVal, other); \
  } \
  template <typename TagT, typename CheckedT, typename R \
        , typename std::enable_if< \
                !std::is_same<R, base::internal::StrongCheckedNumeric<TagT, CheckedT> >::value \
                && internal::IsCheckedOp<base::internal::StrongCheckedNumeric<TagT, CheckedT>, R>::value \
          >::type* = nullptr \
  > \
  constexpr \
  StrongCheckedNumeric<TagT, typename base::internal::MathWrapper<OP_NAME, typename UnderlyingType<CheckedT>::type, typename UnderlyingType<R>::type >::type> \
  operator OP2 ( \
    const base::internal::StrongCheckedNumeric<TagT, CheckedT> CheckedVal \
    , const R other) \
  { \
    return decltype(CheckedVal OP2 other)::template MathOp<TagT, OP_NAME>(CheckedVal, other); \
  } \
  template <typename TagT, typename CheckedT, typename RTagT, typename RCheckedT \
  > \
  constexpr \
  StrongCheckedNumeric<TagT, typename base::internal::MathWrapper<OP_NAME, typename UnderlyingType<CheckedT>::type, typename UnderlyingType<RCheckedT>::type >::type> \
  operator OP2 ( \
    const base::internal::StrongCheckedNumeric<TagT, CheckedT> CheckedVal \
    , const base::internal::StrongCheckedNumeric<RTagT, RCheckedT> other) \
  { \
    static_assert(std::is_same<TagT, RTagT>::value, \
                  "Unable to select underlying tag."); \
    return decltype(CheckedVal OP2 other)::template MathOp<TagT, OP_NAME>(CheckedVal, other); \
  }

namespace base {
namespace internal {

template <typename Tag, typename T>
class StrongCheckedNumeric {
  static_assert(std::is_arithmetic<T>::value,
                "StrongCheckedNumeric<T>: T must be a numeric type.");

 public:
  using type = T;

  using tag = Tag;

  constexpr StrongCheckedNumeric() = default;

  // Copy constructor.
  template <typename Src>
  constexpr StrongCheckedNumeric(const StrongCheckedNumeric<Tag, Src>& rhs)
      : state_(rhs.state_.value(), rhs.IsValid()) {}

  template <typename StrongTag, typename Src>
  friend class StrongCheckedNumeric;

  // This is not an explicit constructor because we implicitly upgrade regular
  // numerics to StrongCheckedNumeric to make them easier to use.
  template <typename Src>
  constexpr StrongCheckedNumeric(Src value)  // NOLINT(runtime/explicit)
      : state_(value) {
    static_assert(std::is_arithmetic<Src>::value, "Argument must be numeric.");
  }

  // This is not an explicit constructor because we want a seamless conversion
  // from StrictNumeric types.
  template <typename Src>
  constexpr StrongCheckedNumeric(
      StrictNumeric<Src> value)  // NOLINT(runtime/explicit)
      : state_(static_cast<Src>(value)) {}

  // IsValid() - The public API to test if a StrongCheckedNumeric is currently valid.
  // A range checked destination type can be supplied using the Dst template
  // parameter.
  template <typename Dst = T>
  constexpr bool IsValid() const {
    return state_.is_valid() &&
           IsValueInRangeForNumericType<Dst>(state_.value());
  }

  // AssignIfValid(Dst) - Assigns the underlying value if it is currently valid
  // and is within the range supported by the destination type. Returns true if
  // successful and false otherwise.
  template <typename Dst>
#if defined(__clang__) || defined(__GNUC__)
  __attribute__((warn_unused_result))
#elif defined(_MSC_VER)
  _Check_return_
#endif
  constexpr bool
  AssignIfValid(Dst* result) const {
    return BASE_NUMERICS_LIKELY(IsValid<Dst>())
               ? ((*result = static_cast<Dst>(state_.value())), true)
               : false;
  }

  // ValueOrDie() - The primary accessor for the underlying value. If the
  // current state is not valid it will CHECK and crash.
  // A range checked destination type can be supplied using the Dst template
  // parameter, which will trigger a CHECK if the value is not in bounds for
  // the destination.
  // The CHECK behavior can be overridden by supplying a handler as a
  // template parameter, for test code, etc. However, the handler cannot access
  // the underlying value, and it is not available through other means.
  template <typename Dst = T, class CheckHandler = CheckOnFailure>
  constexpr StrictNumeric<Dst> ValueOrDie() const {
    return BASE_NUMERICS_LIKELY(IsValid<Dst>())
               ? static_cast<Dst>(state_.value())
               : CheckHandler::template HandleFailure<Dst>();
  }

  // ValueOrDefault(T default_value) - A convenience method that returns the
  // current value if the state is valid, and the supplied default_value for
  // any other state.
  // A range checked destination type can be supplied using the Dst template
  // parameter. WARNING: This function may fail to compile or CHECK at runtime
  // if the supplied default_value is not within range of the destination type.
  template <typename Dst = T, typename Src>
  constexpr StrictNumeric<Dst> ValueOrDefault(const Src default_value) const {
    return BASE_NUMERICS_LIKELY(IsValid<Dst>())
               ? static_cast<Dst>(state_.value())
               : checked_cast<Dst>(default_value);
  }

  // Returns a checked numeric of the specified type, cast from the current
  // StrongCheckedNumeric. If the current state is invalid or the destination cannot
  // represent the result then the returned StrongCheckedNumeric will be invalid.
  template <typename Dst>
  constexpr StrongCheckedNumeric<Tag, typename UnderlyingType<Dst>::type> Cast() const {
    return *this;
  }

  // This friend method is available solely for providing more detailed logging
  // in the the tests. Do not implement it in production code, because the
  // underlying values may change at any time.
  template <typename U>
  friend U GetNumericValueForTest(const StrongCheckedNumeric<Tag, U>& src);

  // Prototypes for the supported arithmetic operator overloads.
  CHECKED_UNARY_OPERATOR(CheckedAddOp, +=)
  CHECKED_UNARY_OPERATOR(CheckedSubOp, -=)
  CHECKED_UNARY_OPERATOR(CheckedMulOp, *=)
  CHECKED_UNARY_OPERATOR(CheckedDivOp, /=)
  CHECKED_UNARY_OPERATOR(CheckedModOp, %=)
  CHECKED_UNARY_OPERATOR(CheckedLshOp, <<=)
  CHECKED_UNARY_OPERATOR(CheckedRshOp, >>=)
  CHECKED_UNARY_OPERATOR(CheckedAndOp, &=)
  CHECKED_UNARY_OPERATOR(CheckedOrOp , |=)
  CHECKED_UNARY_OPERATOR(CheckedXorOp, ^=)

  constexpr StrongCheckedNumeric operator-() const {
    // The negation of two's complement int min is int min, so we simply
    // check for that in the constexpr case.
    // We use an optimized code path for a known run-time variable.
    return MustTreatAsConstexpr(state_.value()) || !std::is_signed<T>::value ||
                   std::is_floating_point<T>::value
               ? StrongCheckedNumeric<Tag, T>(
                     NegateWrapper(state_.value()),
                     IsValid() && (!std::is_signed<T>::value ||
                                   std::is_floating_point<T>::value ||
                                   NegateWrapper(state_.value()) !=
                                       std::numeric_limits<T>::lowest()))
               : FastRuntimeNegate();
  }

  constexpr StrongCheckedNumeric operator~() const {
    return StrongCheckedNumeric<Tag, decltype(InvertWrapper(T()))>(
        InvertWrapper(state_.value()), IsValid());
  }

  constexpr StrongCheckedNumeric Abs() const {
    return !IsValueNegative(state_.value()) ? *this : -*this;
  }

  template <typename U>
  constexpr StrongCheckedNumeric<Tag, typename MathWrapper<CheckedMaxOp, T, U>::type> Max(
      const U rhs) const {
    using R = typename UnderlyingType<U>::type;
    using result_type = typename MathWrapper<CheckedMaxOp, T, U>::type;
    // TODO(jschuh): This can be converted to the MathOp version and remain
    // constexpr once we have C++14 support.
    return StrongCheckedNumeric<Tag, result_type>(
        static_cast<result_type>(
            IsGreater<T, R>::Test(state_.value(), Wrapper<U>::value(rhs))
                ? state_.value()
                : Wrapper<U>::value(rhs)),
        state_.is_valid() && Wrapper<U>::is_valid(rhs));
  }

  template <typename U>
  constexpr StrongCheckedNumeric<Tag, typename MathWrapper<CheckedMinOp, T, U>::type> Min(
      const U rhs) const {
    using R = typename UnderlyingType<U>::type;
    using result_type = typename MathWrapper<CheckedMinOp, T, U>::type;
    // TODO(jschuh): This can be converted to the MathOp version and remain
    // constexpr once we have C++14 support.
    return StrongCheckedNumeric<Tag, result_type>(
        static_cast<result_type>(
            IsLess<T, R>::Test(state_.value(), Wrapper<U>::value(rhs))
                ? state_.value()
                : Wrapper<U>::value(rhs)),
        state_.is_valid() && Wrapper<U>::is_valid(rhs));
  }

  // This function is available only for integral types. It returns an unsigned
  // integer of the same width as the source type, containing the absolute value
  // of the source, and properly handling signed min.
  constexpr StrongCheckedNumeric<Tag, typename UnsignedOrFloatForSize<T>::type>
  UnsignedAbs() const {
    return StrongCheckedNumeric<Tag, typename UnsignedOrFloatForSize<T>::type>(
        SafeUnsignedAbs(state_.value()), state_.is_valid());
  }

  constexpr StrongCheckedNumeric& operator++() {
    *this += 1;
    return *this;
  }

  constexpr StrongCheckedNumeric operator++(int) {
    StrongCheckedNumeric value = *this;
    *this += 1;
    return value;
  }

  constexpr StrongCheckedNumeric& operator--() {
    *this -= 1;
    return *this;
  }

  constexpr StrongCheckedNumeric operator--(int) {
    StrongCheckedNumeric value = *this;
    *this -= 1;
    return value;
  }

  // These perform the actual math operations on the StrongCheckedNumerics.
  // Binary arithmetic operations.
  template <typename MathTag,
            template <typename, typename, typename> class M,
            typename L,
            typename R>
  static constexpr StrongCheckedNumeric MathOp(const L lhs, const R rhs) {
    using Math = typename MathWrapper<M, L, R>::math;
    T result = 0;
    bool is_valid =
        Wrapper<L>::is_valid(lhs) && Wrapper<R>::is_valid(rhs) &&
        Math::Do(Wrapper<L>::value(lhs), Wrapper<R>::value(rhs), &result);
    return StrongCheckedNumeric<MathTag, T>(result, is_valid);
  }

  // Assignment arithmetic operations.
  template <template <typename, typename, typename> class M, typename R>
  constexpr StrongCheckedNumeric& MathOp(const R rhs) {
    using Math = typename MathWrapper<M, T, R>::math;
    T result = 0;  // Using T as the destination saves a range check.
    bool is_valid = state_.is_valid() && Wrapper<R>::is_valid(rhs) &&
                    Math::Do(state_.value(), Wrapper<R>::value(rhs), &result);
    *this = StrongCheckedNumeric<Tag, T>(result, is_valid);
    return *this;
  }

 private:
  CheckedNumericState<T> state_;

  StrongCheckedNumeric FastRuntimeNegate() const {
    T result;
    bool success = CheckedSubOp<T, T>::Do(T(0), state_.value(), &result);
    return StrongCheckedNumeric<Tag, T>(result, IsValid() && success);
  }

  template <typename Src>
  constexpr StrongCheckedNumeric(Src value, bool is_valid)
      : state_(value, is_valid) {}

  // These wrappers allow us to handle state the same way for both
  // StrongCheckedNumeric and POD arithmetic types.
  template <typename Src>
  struct Wrapper {
    static constexpr bool is_valid(Src) { return true; }
    static constexpr Src value(Src value) { return value; }
  };

  template <typename Src>
  struct Wrapper<StrongCheckedNumeric<Tag, Src>> {
    static constexpr bool is_valid(const StrongCheckedNumeric<Tag, Src> v) {
      return v.IsValid();
    }
    static constexpr Src value(const StrongCheckedNumeric<Tag, Src> v) {
      return v.state_.value();
    }
  };

  template <typename Src>
  struct Wrapper<StrictNumeric<Src>> {
    static constexpr bool is_valid(const StrictNumeric<Src>) { return true; }
    static constexpr Src value(const StrictNumeric<Src> v) {
      return static_cast<Src>(v);
    }
  };
};

// Convenience functions to avoid the ugly template disambiguator syntax.
template <typename Tag, typename Dst, typename Src>
constexpr bool IsValidForTypeInternal(const StrongCheckedNumeric<Tag, Src> value) {
  return value.template IsValid<Dst>();
}

template <typename Tag, typename Dst, typename Src>
constexpr StrictNumeric<Dst> ValueOrDieForTypeInternal(
    const StrongCheckedNumeric<Tag, Src> value) {
  return value.template ValueOrDie<Dst>();
}

template <typename Tag, typename Dst, typename Src, typename Default>
constexpr StrictNumeric<Dst> ValueOrDefaultForTypeInternal(
    const StrongCheckedNumeric<Tag, Src> value,
    const Default default_value) {
  return value.template ValueOrDefault<Dst>(default_value);
}

// Convience wrapper to return a new CheckedNumeric from the provided arithmetic
// or CheckedNumericType.
template <typename Tag, typename T>
constexpr StrongCheckedNumeric<Tag, typename UnderlyingType<T>::type> MakeCheckedNumInternal(
    const T value) {
  return value;
}

// These implement the variadic wrapper for the math operations.
template <typename Tag,
          template <typename, typename, typename> class M,
          typename L,
          typename R>
constexpr StrongCheckedNumeric<Tag, typename MathWrapper<M, L, R>::type> CheckMathOp(
    const L lhs,
    const R rhs) {
  using Math = typename MathWrapper<M, L, R>::math;
  return StrongCheckedNumeric<Tag, typename Math::result_type>::template MathOp<Tag, M>(lhs,
                                                                        rhs);
}

// General purpose wrapper template for arithmetic operations.
template <typename Tag,
          template <typename, typename, typename> class M,
          typename L,
          typename R,
          typename... Args>
constexpr StrongCheckedNumeric<Tag, typename ResultType<M, L, R, Args...>::type>
CheckMathOp(const L lhs, const R rhs, const Args... args) {
  return CheckMathOp<Tag, M>(CheckMathOp<Tag, M>(lhs, rhs), args...);
}

/// \note Call `ValueOrDie` manually instead.
/// Overload the ostream output operator to make logging work nicely.
/// template <typename Tag, typename T>
/// std::ostream& operator<<(std::ostream& os, const StrongCheckedNumeric<Tag, T>& value) {
///   os << static_cast<T>(value.ValueOrDie());
///   return os;
/// }

class CheckedNumericTag{};

/// \note Call `ValueOrDie` manually instead.
/// BASE_STRONG_COMPARISON_OPERATORS(Strong, Checked, IsLess, <)
/// BASE_STRONG_COMPARISON_OPERATORS(Strong, Checked, IsLessOrEqual, <=)
/// BASE_STRONG_COMPARISON_OPERATORS(Strong, Checked, IsGreater, >)
/// BASE_STRONG_COMPARISON_OPERATORS(Strong, Checked, IsGreaterOrEqual, >=)
/// BASE_STRONG_COMPARISON_OPERATORS(Strong, Checked, IsEqual, ==)
/// BASE_STRONG_COMPARISON_OPERATORS(Strong, Checked, IsNotEqual, !=)

BASE_ARITHMETIC_VARIADIC(Strong, Checked, Check, Add, CheckedAddOp)
BASE_ARITHMETIC_VARIADIC(Strong, Checked, Check, Sub, CheckedSubOp)
BASE_ARITHMETIC_VARIADIC(Strong, Checked, Check, Mul, CheckedMulOp)
BASE_ARITHMETIC_VARIADIC(Strong, Checked, Check, Div, CheckedDivOp)
BASE_ARITHMETIC_VARIADIC(Strong, Checked, Check, Mod, CheckedModOp)
BASE_ARITHMETIC_VARIADIC(Strong, Checked, Check, Lsh, CheckedLshOp)
BASE_ARITHMETIC_VARIADIC(Strong, Checked, Check, Rsh, CheckedRshOp)
BASE_ARITHMETIC_VARIADIC(Strong, Checked, Check, And, CheckedAndOp)
BASE_ARITHMETIC_VARIADIC(Strong, Checked, Check, Or , CheckedOrOp)
BASE_ARITHMETIC_VARIADIC(Strong, Checked, Check, Xor, CheckedXorOp)
BASE_ARITHMETIC_VARIADIC(Strong, Checked, Check, Max, CheckedMaxOp)
BASE_ARITHMETIC_VARIADIC(Strong, Checked, Check, Min, CheckedMinOp)

CHECKED_BINARY_OPERATOR(CheckedAddOp, + )
CHECKED_BINARY_OPERATOR(CheckedSubOp, - )
CHECKED_BINARY_OPERATOR(CheckedMulOp, * )
CHECKED_BINARY_OPERATOR(CheckedDivOp, / )
CHECKED_BINARY_OPERATOR(CheckedModOp, % )
CHECKED_BINARY_OPERATOR(CheckedLshOp, <<)
CHECKED_BINARY_OPERATOR(CheckedRshOp, >>)
CHECKED_BINARY_OPERATOR(CheckedAndOp, & )
CHECKED_BINARY_OPERATOR(CheckedOrOp , | )
CHECKED_BINARY_OPERATOR(CheckedXorOp, ^ )

// `CheckAdd`, `CheckSub`, etc. will default to `CheckedNumericTag`
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::CheckedNumericTag, Strong, Checked, Check, Add, CheckedAddOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::CheckedNumericTag, Strong, Checked, Check, Sub, CheckedSubOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::CheckedNumericTag, Strong, Checked, Check, Mul, CheckedMulOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::CheckedNumericTag, Strong, Checked, Check, Div, CheckedDivOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::CheckedNumericTag, Strong, Checked, Check, Mod, CheckedModOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::CheckedNumericTag, Strong, Checked, Check, Lsh, CheckedLshOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::CheckedNumericTag, Strong, Checked, Check, Rsh, CheckedRshOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::CheckedNumericTag, Strong, Checked, Check, And, CheckedAndOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::CheckedNumericTag, Strong, Checked, Check, Or , CheckedOrOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::CheckedNumericTag, Strong, Checked, Check, Xor, CheckedXorOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::CheckedNumericTag, Strong, Checked, Check, Max, CheckedMaxOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::CheckedNumericTag, Strong, Checked, Check, Min, CheckedMinOp)

DECLARE_STRONG_CHECKED_TYPE_WITH_TAG(internal::CheckedNumericTag, CheckedNumericInt, int)

// These are some extra StrictNumeric operators to support simple pointer
// arithmetic with our result types. Since wrapping on a pointer is always
// bad, we trigger the CHECK condition here.
template <typename L, typename R>
L* operator+(L* lhs, const StrictNumeric<R> rhs) {
  uintptr_t result = CheckAdd(reinterpret_cast<uintptr_t>(lhs),
                              CheckMul(sizeof(L), static_cast<R>(rhs)))
                         .template ValueOrDie<uintptr_t>();
  return reinterpret_cast<L*>(result);
}

template <typename L, typename R>
L* operator-(L* lhs, const StrictNumeric<R> rhs) {
  uintptr_t result = CheckSub(reinterpret_cast<uintptr_t>(lhs),
                              CheckMul(sizeof(L), static_cast<R>(rhs)))
                         .template ValueOrDie<uintptr_t>();
  return reinterpret_cast<L*>(result);
}

}  // namespace internal

using internal::StrongCheckedNumeric;

template <typename T>
using CheckedNumeric = internal::StrongCheckedNumeric<internal::CheckedNumericTag, T>;

using CheckedNumericInt = internal::CheckedNumericInt;

template <typename Dst, typename Src>
constexpr bool IsValidForType(const StrongCheckedNumeric<internal::CheckedNumericTag, Src> value) {
  return internal::IsValidForTypeInternal<internal::CheckedNumericTag, Dst, Src>(value);
}

template <typename Dst, typename Src>
constexpr auto ValueOrDieForType(
    const StrongCheckedNumeric<internal::CheckedNumericTag, Src> value) {
  return internal::ValueOrDieForTypeInternal<internal::CheckedNumericTag, Dst, Src>(value);
}

template <typename Dst, typename Src, typename Default>
constexpr auto ValueOrDefaultForType(
    const internal::StrongCheckedNumeric<internal::CheckedNumericTag, Src> value,
    const Default default_value) {
  return internal::ValueOrDefaultForTypeInternal<internal::CheckedNumericTag, Dst, Src>(value, default_value);
}

// Convience wrapper to return a new CheckedNumeric from the provided arithmetic
// or CheckedNumericType.
template <typename T>
constexpr auto MakeCheckedNum(
    const T value) {
  return internal::MakeCheckedNumInternal<internal::CheckedNumericTag, T>(value);
}

using internal::CheckMax;
using internal::CheckMin;
using internal::CheckAdd;
using internal::CheckSub;
using internal::CheckMul;
using internal::CheckDiv;
using internal::CheckMod;
using internal::CheckLsh;
using internal::CheckRsh;
using internal::CheckAnd;
using internal::CheckOr;
using internal::CheckXor;

}  // namespace base

#endif  // BASE_NUMERICS_CHECKED_MATH_H_
