#pragma once

#include <basic/macros.h>

#include <base/macros.h>
#include <base/template_util.h>
#include <base/numerics/checked_math.h>

#include <basic/rvalue_cast.h>
#include <basic/macros.h>

#include <ostream>
#include <utility>
#include <functional>

// default tag for strong type
#define STRONG_CHECKED_NUMERIC_TAG_NAME UniqueCheckedNumericTypeTag

// format tag name (concats strings)
#define STRONG_CHECKED_NUMERIC_TAG_CUSTOM_2(using_name, suffix) \
  using_name ## _ ## suffix

// STRONG_CHECKED_NUMERIC_TAG_CUSTOM(MyType, UniqueTypeTag) expands to `MyType_UniqueTypeTag`
#define STRONG_CHECKED_NUMERIC_TAG_CUSTOM(using_name, suffix) \
  STRONG_CHECKED_NUMERIC_TAG_CUSTOM_2(using_name,suffix)

/// \note Each `StrongAlias` must have UNIQUE tag.
/// We assume that provided `using_name` globally unique
/// (even between shared libs!)
// STRONG_CHECKED_NUMERIC_TAG(MyType) expands to `MyType_UniqueTypeTag`
#define STRONG_CHECKED_NUMERIC_TAG(using_name) \
  STRONG_CHECKED_NUMERIC_TAG_CUSTOM(using_name,STRONG_CHECKED_NUMERIC_TAG_NAME)

#define STRONG_CHECKED_NUMERIC(NAME, TYPE) \
  using NAME = basic::StrongCheckedNumeric<class STRONG_CHECKED_NUMERIC_TAG(NAME), TYPE>

// lhs - StrongCheckedNumeric
// rhs - StrongCheckedNumeric
#define STRONG_CHECKED_MAPTH_OP_0(CMP_OP) \
  template < \
    typename L \
    , typename std::enable_if< \
        std::is_same<L, basic::StrongCheckedNumeric<Tag, T> >::value \
      >::type* = nullptr \
  > \
  constexpr auto operator CMP_OP( \
    const L rhs) \
  { \
    return basic::StrongCheckedNumeric<Tag, T>(get() CMP_OP rhs.get()); \
  }

// lhs - StrongCheckedNumeric
// rhs - anything, but not StrongCheckedNumeric
#define STRONG_CHECKED_MAPTH_OP_1(CMP_OP) \
  template < \
    typename L \
    , typename std::enable_if< \
        !std::is_same<L, basic::StrongCheckedNumeric<Tag, T> >::value \
      >::type* = nullptr \
  > \
  constexpr auto operator CMP_OP( \
    const L rhs) \
  { \
    return basic::StrongCheckedNumeric<Tag, T>(get() CMP_OP rhs); \
  }

namespace basic {

// Type-safe base::CheckedNumeric
//
// StrongCheckedNumeric objects are type-safe
// and cannot be implicitly casted to untyped objects,
// or different StrongCheckedNumeric types while still
// provides all relevant operators.
//
// StrongCheckedNumeric template parameter is a tag type
// that is going to be used to distinguish objects
// of different types.
//
// EXAMPLE
//
// #include <basic/strong_types/strong_checked_numeric.h>
//
// STRONG_CHECKED_NUMERIC(fooObj, int);
//
// STRONG_CHECKED_NUMERIC(barObj, int64_t);
//
template<
  typename Tag
  , typename T
>
class StrongCheckedNumeric
{
public:
  static_assert(std::is_arithmetic<T>::value,
                "CheckedNumeric<Type>: T must be a numeric type.");

public:
  template <typename Src>
  friend class base::CheckedNumeric;

  using type = T;

  explicit operator base::CheckedNumeric<T>() const NO_EXCEPTION
  {
    return value_;
  }

  const base::CheckedNumeric<T>& get() const NO_EXCEPTION
  {
    return value_;
  }

  constexpr base::CheckedNumeric<T>& value() & { return value_; }
  constexpr const base::CheckedNumeric<T>& value() const& { return value_; }
  constexpr base::CheckedNumeric<T>&& value() && { return RVALUE_CAST(value_); }
  constexpr const base::CheckedNumeric<T>&& value() const&& { return COPY_OR_MOVE(value_); }

  template <typename Src>
  constexpr StrongCheckedNumeric(const StrongCheckedNumeric<Tag, Src>& rhs)
      : value_(rhs) {}

  template <typename Src>
  constexpr StrongCheckedNumeric(
      StrongCheckedNumeric<Tag, Src> value)  // NOLINT(runtime/explicit)
      : value_(value) {}

  template <typename Src>
  constexpr StrongCheckedNumeric(const base::CheckedNumeric<Src>& rhs)
      : value_(rhs) {}

  template <typename Src>
  constexpr StrongCheckedNumeric(Src value)  // NOLINT(runtime/explicit)
      : value_(value) {
    static_assert(std::is_arithmetic<Src>::value, "Argument must be numeric.");
  }

  template <typename Src>
  constexpr StrongCheckedNumeric(
      base::StrictNumeric<Src> value)  // NOLINT(runtime/explicit)
      : value_(value) {}

  template <typename Dst = T>
  constexpr bool IsValid() const {
    return value_.template IsValid<Dst>();
  }

  template <typename Dst>
  constexpr bool
  AssignIfValid(Dst* result) const {
    return value_.template AssignIfValid<Dst>(result);
  }

  template <typename Dst = T, class CheckHandler = base::internal::CheckOnFailure>
  constexpr auto ValueOrDie() const {
    return value_.template ValueOrDie<Dst, CheckHandler>();
  }

  template <typename Dst = T, typename Src>
  constexpr auto ValueOrDefault(const Src default_value) const {
    return value_.template ValueOrDie<Dst, Src>(default_value);
  }

  template <typename Dst>
  constexpr auto Cast() const {
    return value_.template Cast<Dst>();
  }

  friend T GetNumericValueForTest(const StrongCheckedNumeric<Tag, T>& src) {
    return src.get().state_.value();
  }

  STRONG_CHECKED_MAPTH_OP_0(+)
  STRONG_CHECKED_MAPTH_OP_0(-)
  STRONG_CHECKED_MAPTH_OP_0(&);
  STRONG_CHECKED_MAPTH_OP_0(|);
  STRONG_CHECKED_MAPTH_OP_0(^);
  STRONG_CHECKED_MAPTH_OP_0(*);
  STRONG_CHECKED_MAPTH_OP_0(/);
  STRONG_CHECKED_MAPTH_OP_0(%);
  STRONG_CHECKED_MAPTH_OP_0(<<);
  STRONG_CHECKED_MAPTH_OP_0(>>);

  STRONG_CHECKED_MAPTH_OP_1(+)
  STRONG_CHECKED_MAPTH_OP_1(-)
  STRONG_CHECKED_MAPTH_OP_1(&);
  STRONG_CHECKED_MAPTH_OP_1(|);
  STRONG_CHECKED_MAPTH_OP_1(^);
  STRONG_CHECKED_MAPTH_OP_1(*);
  STRONG_CHECKED_MAPTH_OP_1(/);
  STRONG_CHECKED_MAPTH_OP_1(%);
  STRONG_CHECKED_MAPTH_OP_1(<<);
  STRONG_CHECKED_MAPTH_OP_1(>>);

  template <typename Src>
  constexpr auto& operator+=(const Src rhs) {
    return value_.operator+=(rhs);
  }
  template <typename Src>
  constexpr auto& operator-=(const Src rhs) {
    return value_.operator-=(rhs);
  }
  template <typename Src>
  constexpr auto& operator*=(const Src rhs) {
    return value_.operator*=(rhs);
  }
  template <typename Src>
  constexpr auto& operator/=(const Src rhs) {
    return value_.operator/=(rhs);
  }
  template <typename Src>
  constexpr auto& operator%=(const Src rhs) {
    return value_.operator%=(rhs);
  }
  template <typename Src>
  constexpr auto& operator<<=(const Src rhs) {
    return value_.operator<<=(rhs);
  }
  template <typename Src>
  constexpr auto& operator>>=(const Src rhs) {
    return value_.operator>>=(rhs);
  }
  template <typename Src>
  constexpr auto& operator&=(const Src rhs) {
    return value_.operator&=(rhs);
  }
  template <typename Src>
  constexpr auto& operator|=(const Src rhs) {
    return value_.operator|=(rhs);
  }
  template <typename Src>
  constexpr auto& operator^=(const Src rhs) {
    return value_.operator^=(rhs);
  }

  constexpr auto operator-() const {
    return value_.operator-();
  }

  constexpr auto operator~() const {
    return value_.operator~();
  }

  constexpr auto Abs() const {
    return value_.Abs();
  }

  template <typename U>
  constexpr auto Max(const U rhs) const {
    return value_.Max(rhs);
  }

  template <typename U>
  constexpr auto Min(const U rhs) const {
    return value_.Min(rhs);
  }

  // This function is available only for integral types. It returns an unsigned
  // integer of the same width as the source type, containing the absolute value
  // of the source, and properly handling signed min.
  constexpr auto
  UnsignedAbs() const {
    return value_.UnsignedAbs();
  }

  constexpr auto& operator++() {
    return value_.operator++();
  }

  constexpr auto operator++(int) {
    return value_.operator++(1);
  }

  constexpr auto& operator--() {
    return value_.operator--();
  }

  constexpr auto operator--(int) {
    return value_.operator--(1);
  }

  template <template <typename, typename, typename> class M,
            typename L,
            typename R>
  constexpr auto MathOp(const L lhs, const R rhs) {
    return value_.template MathOp<M, L, R>(lhs, rhs);
  }

  template <template <typename, typename, typename> class M, typename R>
  constexpr auto& MathOp(const R rhs) {
    return value_.template MathOp<M, R>(rhs);
  }

  // Shortcut for `.value`
  //
  // BEFORE
  // DCHECK(obj.value().empty());
  //
  // AFTER
  // DCHECK((*obj).empty());
  constexpr const auto& operator*() const
  {
    return value_;
  }

  constexpr auto& operator*()
  {
    return value_;
  }

  // Shortcut for `.value`
  //
  // BEFORE
  // DCHECK(obj.value().empty());
  //
  // AFTER
  // DCHECK(obj->empty());
  constexpr const auto* operator->() const
  {
    return &value_;
  }

  constexpr auto* operator->()
  {
    return &value_;
  }

  friend bool operator==(
    const StrongCheckedNumeric& x, const StrongCheckedNumeric& y) NO_EXCEPTION
  {
    return x.value_ == y.value_;
  }

#if __cplusplus <= 201703L
  friend bool operator!=(
    const StrongCheckedNumeric& x, const StrongCheckedNumeric& y) NO_EXCEPTION
  {
    return x.value_ != y.value_;
  }
#endif

  template <
    typename Src
    , typename std::enable_if<
            !std::is_same<Src, StrongCheckedNumeric >::value
      >::type* = nullptr
  >
  constexpr auto& operator==(const Src rhs) {
    return value_.operator==(rhs);
  }

  /// Prints StrongCheckedNumeric value to an output stream.
  friend std::ostream& operator<<(
    std::ostream& os, const StrongCheckedNumeric& v)
  {
    return os << v.value_;
  }

private:
  base::CheckedNumeric<T> value_;
};

// lhs - anything, but not StrongCheckedNumeric
// rhs - StrongCheckedNumeric
#define STRONG_CHECKED_MAPTH_OP_2(CMP_OP) \
  template < \
    typename L \
    , typename T \
    , typename Tag \
    , typename std::enable_if< \
        !std::is_same<L, basic::StrongCheckedNumeric<Tag, T> >::value \
      >::type* = nullptr \
  > \
  constexpr auto operator CMP_OP ( \
    const L lhs, const basic::StrongCheckedNumeric<Tag, T> rhs)  \
  { \
    return basic::StrongCheckedNumeric<Tag, T>(rhs.get() CMP_OP lhs); \
  }

STRONG_CHECKED_MAPTH_OP_2(+)
STRONG_CHECKED_MAPTH_OP_2(-)

/*
// Define operators that take two basic::StrongCheckedNumeric arguments. These operators are
// defined in terms of their op-equal member function cousins.
#define STRONG_INT_VS_STRONG_INT_BINARY_OP(op)                                 \
  template< \
    typename TagType, typename ValueType \
    , typename std::enable_if< \
        std::is_same<L, basic::StrongCheckedNumeric<Tag, T> >::value \
      >::type* = nullptr \
  >       \
  inline basic::StrongCheckedNumeric<TagType, ValueType>                          \
  operator op(basic::StrongCheckedNumeric<TagType, ValueType> lhs,                \
              basic::StrongCheckedNumeric<TagType, ValueType> rhs) {              \
    lhs op ## = rhs;                                                           \
    return lhs;                                                                \
  }
STRONG_INT_VS_STRONG_INT_BINARY_OP(+);
STRONG_INT_VS_STRONG_INT_BINARY_OP(-);
STRONG_INT_VS_STRONG_INT_BINARY_OP(&);
STRONG_INT_VS_STRONG_INT_BINARY_OP(|);
STRONG_INT_VS_STRONG_INT_BINARY_OP(^);
#undef STRONG_INT_VS_STRONG_INT_BINARY_OP

// Define operators that take one basic::StrongCheckedNumeric and one native integer argument.
// These operators are defined in terms of their op-equal member function
// cousins, mostly.
#define STRONG_INT_VS_NUMERIC_BINARY_OP(op)                                    \
  template<typename TagType, typename ValueType,       \
           typename NumType>                                                   \
  inline basic::StrongCheckedNumeric<TagType, ValueType>                          \
  operator op(basic::StrongCheckedNumeric<TagType, ValueType> lhs, NumType rhs) { \
    lhs op ## = rhs;                                                           \
    return lhs;                                                                \
  }
// This is used for commutative operators between one basic::StrongCheckedNumeric and one native
// integer argument.  That is a long way of saying "multiplication".
#define NUMERIC_VS_STRONG_INT_BINARY_OP(op)                                    \
  template<typename TagType, typename ValueType,       \
           typename NumType>                                                   \
  inline basic::StrongCheckedNumeric<TagType, ValueType>                          \
  operator op(NumType lhs, basic::StrongCheckedNumeric<TagType, ValueType> rhs) { \
    rhs op ## = lhs;                                                           \
    return rhs;                                                                \
  }
STRONG_INT_VS_NUMERIC_BINARY_OP(*);
NUMERIC_VS_STRONG_INT_BINARY_OP(*);
STRONG_INT_VS_NUMERIC_BINARY_OP(/);
STRONG_INT_VS_NUMERIC_BINARY_OP(%);
STRONG_INT_VS_NUMERIC_BINARY_OP(<<);
STRONG_INT_VS_NUMERIC_BINARY_OP(>>);
#undef STRONG_INT_VS_NUMERIC_BINARY_OP
#undef NUMERIC_VS_STRONG_INT_BINARY_OP

// Define comparison operators.  We allow all comparison operators.
#define STRONG_INT_COMPARISON_OP(op)                                           \
  template<typename TagType, typename ValueType>       \
  inline bool operator op(basic::StrongCheckedNumeric<TagType, ValueType> lhs,    \
                          basic::StrongCheckedNumeric<TagType, ValueType> rhs) {  \
    return lhs.value() op rhs.value();                                         \
  }
STRONG_INT_COMPARISON_OP(==);
STRONG_INT_COMPARISON_OP(!=);
STRONG_INT_COMPARISON_OP(<);
STRONG_INT_COMPARISON_OP(<=);
STRONG_INT_COMPARISON_OP(>);
STRONG_INT_COMPARISON_OP(>=);
#undef STRONG_INT_COMPARISON_OP*/

}  // namespace basic
