// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_NUMERICS_CLAMPED_MATH_H_
#define BASE_NUMERICS_CLAMPED_MATH_H_

#include <stddef.h>

#include <limits>
#include <type_traits>

#include "base/numerics/clamped_math_impl.h"

// default tag for strong type
#define STRONG_CLAMPED_INT_TAG_NAME UniqueClampedIntTypeTag

// format tag name (concats strings)
#define STRONG_CLAMPED_INT_TAG_CUSTOM_2(using_name, suffix) \
  using_name ## _ ## suffix

// STRONG_CLAMPED_INT_TAG_CUSTOM(MyType, UniqueTypeTag) expands to `MyType_UniqueTypeTag`
#define STRONG_CLAMPED_INT_TAG_CUSTOM(using_name, suffix) \
  STRONG_CLAMPED_INT_TAG_CUSTOM_2(using_name,suffix)

/// \note Each `StrongAlias` must have UNIQUE tag.
/// We assume that provided `using_name` globally unique
/// (even between shared libs!)
// STRONG_CLAMPED_INT_TAG(MyType) expands to `MyType_UniqueTypeTag`
#define STRONG_CLAMPED_INT_TAG(using_name) \
  STRONG_CLAMPED_INT_TAG_CUSTOM(using_name,STRONG_CLAMPED_INT_TAG_NAME)

#define DECLARE_STRONG_CLAMPED_TYPE_WITH_TAG(TAG, NAME, TYPE) \
  using NAME = base::internal::StrongClampedNumeric<TAG, TYPE>;

// USAGE
//
// namespace base {
// namespace internal {
// DECLARE_STRONG_CLAMPED_TYPE(Petabytes, int);
// } // namespace base
// } // namespace internal
// using Petabytes = ::base::internal::Petabytes;
//
// // Or with custom type:
// template<typename T>
// using PetabytesTyped = base::StrongClampedNumeric<class STRONG_CLAMPED_INT_TAG(Petabytes), T>;
// Petabytes t1(std::numeric_limits<int>::max());
// t1++;
// // t1 == std::numeric_limits<int>::max()
// DLOG(INFO) << t1;
#define DECLARE_STRONG_CLAMPED_TYPE(NAME, TYPE) \
  DECLARE_STRONG_CLAMPED_TYPE_WITH_TAG(class STRONG_CLAMPED_INT_TAG(NAME), NAME, TYPE)

#define STRONGLY_TYPED_CLAMPED_INT(NAME) \
  DECLARE_STRONG_CLAMPED_TYPE(NAME, int)

// USAGE: CLAMPED_UNARY_OPERATOR(ClampedAddOp, +=)
#define CLAMPED_UNARY_OPERATOR(OP_NAME, OP2)                 \
  template <typename R>                                  \
  constexpr auto& operator OP2 (                         \
      const R rhs) {                                     \
    return MathOp<OP_NAME>(rhs);                         \
  }

#define CLAMPED_BINARY_OPERATOR(OP_NAME, OP2) \
  template <typename TagT, typename ClampedT, typename R \
        , typename std::enable_if< \
                !std::is_same<R, base::internal::StrongClampedNumeric<TagT, ClampedT> >::value \
                && internal::IsClampedOp<base::internal::StrongClampedNumeric<TagT, ClampedT>, R>::value \
          >::type* = nullptr \
  > \
  constexpr \
  StrongClampedNumeric<TagT, typename base::internal::MathWrapper<OP_NAME, typename UnderlyingType<ClampedT>::type, typename UnderlyingType<R>::type >::type> \
  operator OP2 ( \
    const R other \
    , const base::internal::StrongClampedNumeric<TagT, ClampedT> ClampedVal) \
  { \
    return decltype(ClampedVal OP2 other)::template MathOp<TagT, OP_NAME>(ClampedVal, other); \
  } \
  template <typename TagT, typename ClampedT, typename R \
        , typename std::enable_if< \
                !std::is_same<R, base::internal::StrongClampedNumeric<TagT, ClampedT> >::value \
                && internal::IsClampedOp<base::internal::StrongClampedNumeric<TagT, ClampedT>, R>::value \
          >::type* = nullptr \
  > \
  constexpr \
  StrongClampedNumeric<TagT, typename base::internal::MathWrapper<OP_NAME, typename UnderlyingType<ClampedT>::type, typename UnderlyingType<R>::type >::type> \
  operator OP2 ( \
    const base::internal::StrongClampedNumeric<TagT, ClampedT> ClampedVal \
    , const R other) \
  { \
    return decltype(ClampedVal OP2 other)::template MathOp<TagT, OP_NAME>(ClampedVal, other); \
  } \
  template <typename TagT, typename ClampedT, typename RTagT, typename RClampedT \
  > \
  constexpr \
  StrongClampedNumeric<TagT, typename base::internal::MathWrapper<OP_NAME, typename UnderlyingType<ClampedT>::type, typename UnderlyingType<RClampedT>::type >::type> \
  operator OP2 ( \
    const base::internal::StrongClampedNumeric<TagT, ClampedT> ClampedVal \
    , const base::internal::StrongClampedNumeric<RTagT, RClampedT> other) \
  { \
    static_assert(std::is_same<TagT, RTagT>::value, \
                  "Unable to select underlying tag."); \
    return decltype(ClampedVal OP2 other)::template MathOp<TagT, OP_NAME>(ClampedVal, other); \
  }

namespace base {
namespace internal {

template <typename Tag, typename T>
class StrongClampedNumeric {
  static_assert(std::is_arithmetic<T>::value,
                "StrongClampedNumeric<T>: T must be a numeric type.");

 public:
  using type = T;

  using tag = Tag;

  constexpr StrongClampedNumeric() : value_(0) {}

  // Copy constructor.
  template <typename Src>
  constexpr StrongClampedNumeric(const StrongClampedNumeric<Tag, Src>& rhs)
      : value_(saturated_cast<T>(rhs.value_)) {}

  template <typename StrongTag, typename Src>
  friend class StrongClampedNumeric;

  // This is not an explicit constructor because we implicitly upgrade regular
  // numerics to ClampedNumerics to make them easier to use.
  template <typename Src>
  constexpr StrongClampedNumeric(Src value)  // NOLINT(runtime/explicit)
      : value_(saturated_cast<T>(value)) {
    static_assert(std::is_arithmetic<Src>::value, "Argument must be numeric.");
  }

  // This is not an explicit constructor because we want a seamless conversion
  // from StrictNumeric types.
  template <typename Src>
  constexpr StrongClampedNumeric(
      StrictNumeric<Src> value)  // NOLINT(runtime/explicit)
      : value_(saturated_cast<T>(static_cast<Src>(value))) {}

  // Returns a StrongClampedNumeric of the specified type, cast from the current
  // StrongClampedNumeric, and saturated to the destination type.
  template <typename Dst>
  constexpr StrongClampedNumeric<Tag, typename UnderlyingType<Dst>::type> Cast() const {
    return *this;
  }

  CLAMPED_UNARY_OPERATOR(ClampedAddOp, +=)
  CLAMPED_UNARY_OPERATOR(ClampedSubOp, -=)
  CLAMPED_UNARY_OPERATOR(ClampedMulOp, *=)
  CLAMPED_UNARY_OPERATOR(ClampedDivOp, /=)
  CLAMPED_UNARY_OPERATOR(ClampedModOp, %=)
  CLAMPED_UNARY_OPERATOR(ClampedLshOp, <<=)
  CLAMPED_UNARY_OPERATOR(ClampedRshOp, >>=)
  CLAMPED_UNARY_OPERATOR(ClampedAndOp, &=)
  CLAMPED_UNARY_OPERATOR(ClampedOrOp , |=)
  CLAMPED_UNARY_OPERATOR(ClampedXorOp, ^=)

  constexpr StrongClampedNumeric operator-() const {
    // The negation of two's complement int min is int min, so that's the
    // only overflow case where we will saturate.
    return StrongClampedNumeric<Tag, T>(SaturatedNegWrapper(value_));
  }

  constexpr StrongClampedNumeric operator~() const {
    return StrongClampedNumeric<Tag, decltype(InvertWrapper(T()))>(InvertWrapper(value_));
  }

  constexpr StrongClampedNumeric Abs() const {
    // The negation of two's complement int min is int min, so that's the
    // only overflow case where we will saturate.
    return StrongClampedNumeric<Tag, T>(SaturatedAbsWrapper(value_));
  }

  template <typename U>
  constexpr StrongClampedNumeric<Tag, typename MathWrapper<ClampedMaxOp, T, U>::type> Max(
      const U rhs) const {
    using result_type = typename MathWrapper<ClampedMaxOp, T, U>::type;
    return StrongClampedNumeric<Tag, result_type>(
        ClampedMaxOp<T, U>::Do(value_, Wrapper<U>::value(rhs)));
  }

  template <typename U>
  constexpr StrongClampedNumeric<Tag, typename MathWrapper<ClampedMinOp, T, U>::type> Min(
      const U rhs) const {
    using result_type = typename MathWrapper<ClampedMinOp, T, U>::type;
    return StrongClampedNumeric<Tag, result_type>(
        ClampedMinOp<T, U>::Do(value_, Wrapper<U>::value(rhs)));
  }

  // This function is available only for integral types. It returns an unsigned
  // integer of the same width as the source type, containing the absolute value
  // of the source, and properly handling signed min.
  constexpr StrongClampedNumeric<Tag, typename UnsignedOrFloatForSize<T>::type>
  UnsignedAbs() const {
    return StrongClampedNumeric<Tag, typename UnsignedOrFloatForSize<T>::type>(
        SafeUnsignedAbs(value_));
  }

  constexpr StrongClampedNumeric& operator++() {
    *this += 1;
    return *this;
  }

  constexpr StrongClampedNumeric operator++(int) {
    StrongClampedNumeric value = *this;
    *this += 1;
    return value;
  }

  constexpr StrongClampedNumeric& operator--() {
    *this -= 1;
    return *this;
  }

  constexpr StrongClampedNumeric operator--(int) {
    StrongClampedNumeric value = *this;
    *this -= 1;
    return value;
  }

  // These perform the actual math operations on the StrongClampedNumeric.
  // Binary arithmetic operations.
  template <typename MathTag,
            template <typename, typename, typename> class M,
            typename L,
            typename R>
  static constexpr StrongClampedNumeric MathOp(const L lhs, const R rhs) {
    using Math = typename MathWrapper<M, L, R>::math;
    return StrongClampedNumeric<MathTag, T>(
        Math::template Do<T>(Wrapper<L>::value(lhs), Wrapper<R>::value(rhs)));
  }

  // Assignment arithmetic operations.
  template <template <typename, typename, typename> class M, typename R>
  constexpr StrongClampedNumeric& MathOp(const R rhs) {
    using Math = typename MathWrapper<M, T, R>::math;
    *this =
        StrongClampedNumeric<Tag, T>(Math::template Do<T>(value_, Wrapper<R>::value(rhs)));
    return *this;
  }

  template <typename Dst>
  constexpr operator Dst() const {
    return saturated_cast<typename ArithmeticOrUnderlyingEnum<Dst>::type>(
        value_);
  }

  // This method extracts the raw integer value without saturating it to the
  // destination type as the conversion operator does. This is useful when
  // e.g. assigning to an auto type or passing as a deduced template parameter.
  constexpr T RawValue() const { return value_; }

 private:
  T value_;

  // These wrappers allow us to handle state the same way for both
  // StrongClampedNumeric and POD arithmetic types.
  template <typename Src>
  struct Wrapper {
    static constexpr Src value(Src value) {
      return static_cast<typename UnderlyingType<Src>::type>(value);
    }
  };
};

template <typename T>
struct HasTag {
private:
  template <typename T1>
  static typename T1::tag test(int);
  template <typename>
  static void test(...);
public:
  enum { value = !std::is_void<decltype(test<T>(0))>::value };
};

static_assert(std::is_same<StrongCheckedNumeric<class TmpTag, int>::tag, class TmpTag>::value,
              "Unable to find tag.");

static_assert(HasTag< StrongCheckedNumeric<class TmpTag, int> >::value,
              "Unable to find tag.");

static_assert(!HasTag< int >::value,
              "int must not have tag.");

// Convience wrapper to return a new StrongClampedNumeric from the provided arithmetic
// or StrongClampedNumericType.
template <typename Tag, typename T>
constexpr StrongClampedNumeric<Tag, typename UnderlyingType<T>::type> MakeClampedNumInternal(
    const T value) {
  return value;
}

// used to print type names in static_assert
template<typename ... typeclass>
struct clamped_underlying_false : std::false_type {};

// SelectTag<int, int> -> error
// SelectTag<StrongCheckedNumeric<Tag, T>, int> -> Tag
// SelectTag<int, StrongCheckedNumeric<Tag, T>> -> Tag
// SelectTag<StrongCheckedNumeric<Tag, T1>, StrongCheckedNumeric<Tag, T2>> -> Tag
// SelectTag<StrongCheckedNumeric<TagOne, T1>, StrongCheckedNumeric<TagTwo, T2>> -> error
template <typename L, typename R
          , bool LHasTag = HasTag<L>::value
          , bool RHasTag = HasTag<R>::value
         >
struct SelectClampedTag;

template <typename L, typename R>
struct SelectClampedTag<L, R, false, false>
{
  static_assert(clamped_underlying_false<L, R>::value,
                "Unable to find underlying tag.");
};

template <typename L, typename R>
struct SelectClampedTag<L, R, true, true>
{
  static_assert(std::is_same<typename L::tag, typename R::tag>::value,
                "Unable to select underlying tag.");
  static_assert(UnderlyingType<L>::is_clamped,
                "Unable to find underlying tag.");
  using type = typename L::tag;
};

template <typename L, typename R>
struct SelectClampedTag<L, R, false, true>
{
  static_assert(UnderlyingType<R>::is_clamped,
                "Unable to find underlying tag.");
  using type = typename R::tag;
};

template <typename L, typename R>
struct SelectClampedTag<L, R, true, false>
{
  static_assert(UnderlyingType<L>::is_clamped,
                "Unable to find underlying tag.");
  using type = typename L::tag;
};

// Overload the ostream output operator to make logging work nicely.
template <typename Tag, typename T>
std::ostream& operator<<(std::ostream& os, const StrongClampedNumeric<Tag, T>& value) {
  os << static_cast<T>(value);
  return os;
}

// These implement the variadic wrapper for the math operations.
template <typename Tag,
          template <typename, typename, typename> class M,
          typename L,
          typename R>
constexpr StrongClampedNumeric<Tag, typename MathWrapper<M, L, R>::type> ClampMathOp(
    const L lhs,
    const R rhs) {
  using Math = typename MathWrapper<M, L, R>::math;
  return StrongClampedNumeric<Tag, typename Math::result_type>::template MathOp<Tag, M>(lhs,
                                                                        rhs);
}

// General purpose wrapper template for arithmetic operations.
template <typename Tag,
          template <typename, typename, typename> class M,
          typename L,
          typename R,
          typename... Args>
constexpr StrongClampedNumeric<Tag, typename ResultType<M, L, R, Args...>::type>
ClampMathOp(const L lhs, const R rhs, const Args... args) {
  return ClampMathOp<Tag, M>(ClampMathOp<Tag, M>(lhs, rhs), args...);
}

class ClampedNumericTag{};

BASE_STRONG_COMPARISON_OPERATORS(Strong, Clamped, IsLess, <)
BASE_STRONG_COMPARISON_OPERATORS(Strong, Clamped, IsLessOrEqual, <=)
BASE_STRONG_COMPARISON_OPERATORS(Strong, Clamped, IsGreater, >)
BASE_STRONG_COMPARISON_OPERATORS(Strong, Clamped, IsGreaterOrEqual, >=)
BASE_STRONG_COMPARISON_OPERATORS(Strong, Clamped, IsEqual, ==)
BASE_STRONG_COMPARISON_OPERATORS(Strong, Clamped, IsNotEqual, !=)

CLAMPED_BINARY_OPERATOR(ClampedAddOp, + )
CLAMPED_BINARY_OPERATOR(ClampedSubOp, - )
CLAMPED_BINARY_OPERATOR(ClampedMulOp, * )
CLAMPED_BINARY_OPERATOR(ClampedDivOp, / )
CLAMPED_BINARY_OPERATOR(ClampedModOp, % )
CLAMPED_BINARY_OPERATOR(ClampedLshOp, <<)
CLAMPED_BINARY_OPERATOR(ClampedRshOp, >>)
CLAMPED_BINARY_OPERATOR(ClampedAndOp, & )
CLAMPED_BINARY_OPERATOR(ClampedOrOp , | )
CLAMPED_BINARY_OPERATOR(ClampedXorOp, ^ )

BASE_ARITHMETIC_VARIADIC(Strong, Clamped, Clamp, Add, ClampedAddOp)
BASE_ARITHMETIC_VARIADIC(Strong, Clamped, Clamp, Sub, ClampedSubOp)
BASE_ARITHMETIC_VARIADIC(Strong, Clamped, Clamp, Mul, ClampedMulOp)
BASE_ARITHMETIC_VARIADIC(Strong, Clamped, Clamp, Div, ClampedDivOp)
BASE_ARITHMETIC_VARIADIC(Strong, Clamped, Clamp, Mod, ClampedModOp)
BASE_ARITHMETIC_VARIADIC(Strong, Clamped, Clamp, Lsh, ClampedLshOp)
BASE_ARITHMETIC_VARIADIC(Strong, Clamped, Clamp, Rsh, ClampedRshOp)
BASE_ARITHMETIC_VARIADIC(Strong, Clamped, Clamp, And, ClampedAndOp)
BASE_ARITHMETIC_VARIADIC(Strong, Clamped, Clamp, Or,  ClampedOrOp)
BASE_ARITHMETIC_VARIADIC(Strong, Clamped, Clamp, Xor, ClampedXorOp)
BASE_ARITHMETIC_VARIADIC(Strong, Clamped, Clamp, Max, ClampedMaxOp)
BASE_ARITHMETIC_VARIADIC(Strong, Clamped, Clamp, Min, ClampedMinOp)

DECLARE_STRONG_CLAMPED_TYPE_WITH_TAG(internal::ClampedNumericTag, ClampedNumericInt, int)

// `ClampAdd`, `ClampSub`, etc. will default to `ClampedNumericTag`
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::ClampedNumericTag, Strong, Clamped, Clamp, Add, ClampedAddOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::ClampedNumericTag, Strong, Clamped, Clamp, Sub, ClampedSubOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::ClampedNumericTag, Strong, Clamped, Clamp, Mul, ClampedMulOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::ClampedNumericTag, Strong, Clamped, Clamp, Div, ClampedDivOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::ClampedNumericTag, Strong, Clamped, Clamp, Mod, ClampedModOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::ClampedNumericTag, Strong, Clamped, Clamp, Lsh, ClampedLshOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::ClampedNumericTag, Strong, Clamped, Clamp, Rsh, ClampedRshOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::ClampedNumericTag, Strong, Clamped, Clamp, And, ClampedAndOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::ClampedNumericTag, Strong, Clamped, Clamp, Or,  ClampedOrOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::ClampedNumericTag, Strong, Clamped, Clamp, Xor, ClampedXorOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::ClampedNumericTag, Strong, Clamped, Clamp, Max, ClampedMaxOp)
BASE_STRONG_ARITHMETIC_VARIADIC(base::internal::ClampedNumericTag, Strong, Clamped, Clamp, Min, ClampedMinOp)

}  // namespace internal

using internal::StrongClampedNumeric;

template <typename T>
using ClampedNumeric = internal::StrongClampedNumeric<internal::ClampedNumericTag, T>;

using ClampedNumericInt = internal::ClampedNumericInt;

template <typename T>
constexpr auto MakeClampedNum(
    const T value) {
  return internal::MakeClampedNumInternal<internal::ClampedNumericTag, T>(value);
}

using internal::ClampMax;
using internal::ClampMin;
using internal::ClampAdd;
using internal::ClampSub;
using internal::ClampMul;
using internal::ClampDiv;
using internal::ClampMod;
using internal::ClampLsh;
using internal::ClampRsh;
using internal::ClampAnd;
using internal::ClampOr;
using internal::ClampXor;

}  // namespace base

#endif  // BASE_NUMERICS_CLAMPED_MATH_H_
