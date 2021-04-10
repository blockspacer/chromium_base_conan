#pragma once

#include <base/macros.h>
#include <base/template_util.h>
#include <base/numerics/safe_conversions.h>
#include <base/numerics/checked_math.h>
#include <base/numerics/clamped_math.h>

#include <basic/rvalue_cast.h>
#include <basic/macros.h>

#include <ostream>
#include <utility>
#include <functional>
#include <string>
#include <type_traits>

// default tag for strong type
#define STRONG_INT_TAG_NAME UniqueIntTypeTag

// format tag name (concats strings)
#define STRONG_INT_TAG_CUSTOM_2(using_name, suffix) \
  using_name ## _ ## suffix

// STRONG_INT_TAG_CUSTOM(MyType, UniqueTypeTag) expands to `MyType_UniqueTypeTag`
#define STRONG_INT_TAG_CUSTOM(using_name, suffix) \
  STRONG_INT_TAG_CUSTOM_2(using_name,suffix)

/// \note Each `StrongAlias` must have UNIQUE tag.
/// We assume that provided `using_name` globally unique
/// (even between shared libs!)
// STRONG_INT_TAG(MyType) expands to `MyType_UniqueTypeTag`
#define STRONG_INT_TAG(using_name) \
  STRONG_INT_TAG_CUSTOM(using_name,STRONG_INT_TAG_NAME)

#define DEFINE_STRONGLY_TYPED_INT(NAME, TYPE) \
  using NAME = basic::StrongInt<class STRONG_INT_TAG(NAME), TYPE>

#define STRONGLY_TYPED_INT(NAME) \
  DEFINE_STRONGLY_TYPED_INT(NAME, int)

namespace basic {

/// \note If you want checked or clamped integer, than see:
/// * <base/numerics/checked_math.h>
/// * <base/numerics/clamped_math.h>
///
// Type-safe integer with `strict_cast` compile-time-checks
//
// StrongInt objects are type-safe integer values
// that cannot be implicitly casted to untyped integers,
// integers or different StrongInt types while still
// provides all relevant logical and comparison operators.
//
// StrongInt template parameter is a tag type
// that is going to be used to distinguish integers
// of different types.
//
// EXAMPLE
//
// #include <basic/strong_types/strong_int.h>
//
// STRONGLY_TYPED_INT(foo);
//
// DEFINE_STRONGLY_TYPED_INT(bar, size_t);
//
template<
  typename Tag
  // primitive integral type as defined by std::is_integral
  , typename NativeType
>
class StrongInt
{
  static_assert(
    std::is_integral<NativeType>::value
    , "Invalid integer type for StrongInt");

public:
  using type = NativeType;

  static const StrongInt kZero;

  static const StrongInt kOne;

  /// Constructs a StrongInt object.
  constexpr StrongInt() NO_EXCEPTION
    : value_()
  {}

  template<
    typename IntegralType
    , typename = typename std::enable_if<std::is_integral<IntegralType>::value>
  >
  constexpr explicit StrongInt(IntegralType v) NO_EXCEPTION
    : value_(base::strict_cast<NativeType>(v))
  {}

  template <typename ValType>
  ValType unsafe_cast() const
  {
    return static_cast<ValType>(value_);
  }

  template <typename ValType>
  ValType checked_cast() const
  {
    return ::base::checked_cast<ValType>(value_);
  }

  template <typename ValType>
  ValType strict_cast() const
  {
    return ::base::strict_cast<ValType>(value_);
  }

  template <typename ValType>
  ValType saturated_cast() const
  {
    return ::base::saturated_cast<ValType>(value_);
  }

  NativeType Max() const
  {
    return std::numeric_limits<NativeType>::max();
  }

  NativeType Min() const
  {
    return std::numeric_limits<NativeType>::min();
  }

  /// Casts a StrongInt object to an untyped \c int.
  constexpr explicit operator int() const NO_EXCEPTION
  {
    return value_;
  }

  /// Casts a StrongInt object to an untyped \c bool.
  constexpr explicit operator bool() const NO_EXCEPTION
  {
    return static_cast<bool>(value_);
  }

  int get() const NO_EXCEPTION
  {
    return value_;
  }

  constexpr int& value() & { return value_; }
  constexpr const int& value() const& { return value_; }
  constexpr int&& value() && { return RVALUE_CAST(value_); }
  constexpr const int&& value() const&& { return COPY_OR_MOVE(value_); }

  // Shortcut for `.value`
  //
  // BEFORE
  // DCHECK(obj.value().empty());
  //
  // AFTER
  // DCHECK((*obj).empty());
  constexpr const int& operator*() const
  {
    return value_;
  }

  constexpr int& operator*()
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
  constexpr const int* operator->() const
  {
    return &value_;
  }

  constexpr int* operator->()
  {
    return &value_;
  }

  /// Logical OR.
  friend StrongInt operator||(
    StrongInt x, StrongInt y) NO_EXCEPTION
  {
    return StrongInt(x.value_ || y.value_);
  }

  /// Logical AND.
  friend StrongInt operator&&(
    StrongInt x, StrongInt y) NO_EXCEPTION
  {
    return StrongInt(x.value_ && y.value_);
  }

  /// Logical NOT.
  friend StrongInt operator!(
    StrongInt x) NO_EXCEPTION
  {
    return StrongInt(!x.value_);
  }

  const StrongInt operator+() const {
    return StrongInt(value_);
  }

  const StrongInt operator-() const {
    return StrongInt(-value_);
  }

  const StrongInt operator~() const {
    return StrongInt(NativeType(~value_));
  }

  /// Equal-to operator.
  friend int operator==(
    StrongInt x, StrongInt y) NO_EXCEPTION
  {
    return x.value_ == y.value_;
  }

#if __cplusplus <= 201703L
  /// Not-equal-to operator.
  friend int operator!=(
    StrongInt x, StrongInt y) NO_EXCEPTION
  {
    return x.value_ != y.value_;
  }
#endif

  /// Equal-to operator.
  friend bool operator==(
    int x, const StrongInt& y) NO_EXCEPTION
  {
    return x == y.value_;
  }

#if __cplusplus <= 201703L
  /// Not-equal-to operator.
  friend bool operator!=(
    int x, const StrongInt& y) NO_EXCEPTION
  {
    return x != y.value_;
  }
#endif

  // Increment and decrement operators.
  StrongInt& operator++() {  // ++x
    ++value_;
    return *this;
  }
  const StrongInt operator++(int) {  // x++
    StrongInt temp(*this);
    ++value_;
    return temp;
  }
  StrongInt& operator--() {  // --x
    --value_;
    return *this;
  }
  const StrongInt operator--(int) {  // x--
    StrongInt temp(*this);
    --value_;
    return temp;
  }

  // Action-Assignment operators.
  StrongInt& operator+=(StrongInt arg) {
    value_ += arg.value();
    return *this;
  }
  StrongInt& operator-=(StrongInt arg) {
    value_ -= arg.value();
    return *this;
  }
  template<typename ArgType>
  StrongInt& operator*=(ArgType arg) {
    static_assert(
      std::is_integral<ArgType>::value
      , "Invalid integer type for StrongInt::operator*=");
    value_ *= ::base::strict_cast<NativeType>(arg);
    return *this;
  }
  template<typename ArgType>
  StrongInt& operator/=(ArgType arg) {
    static_assert(
      std::is_integral<ArgType>::value
      , "Invalid integer type for StrongInt::operator*=");
    value_ /= ::base::strict_cast<NativeType>(arg);
    return *this;
  }
  template<typename ArgType>
  StrongInt& operator%=(ArgType arg) {
    static_assert(
      std::is_integral<ArgType>::value
      , "Invalid integer type for StrongInt::operator*=");
    value_ %= ::base::strict_cast<NativeType>(arg);
    return *this;
  }
  StrongInt& operator<<=(int64_t arg) {
    value_ <<= arg;
    return *this;
  }
  StrongInt& operator>>=(int64_t arg) {
    value_ >>= arg;
    return *this;
  }
  StrongInt& operator&=(StrongInt arg) {
    value_ &= arg.value();
    return *this;
  }
  StrongInt& operator|=(StrongInt arg) {
    value_ |= arg.value();
    return *this;
  }
  StrongInt& operator^=(StrongInt arg) {
    value_ ^= arg.value();
    return *this;
  }

  const std::string ToString() const NO_EXCEPTION
  {
    return std::to_string(value_);
  }

  /// Prints StrongInt value to an output stream.
  friend std::ostream& operator<<(
    std::ostream& os, StrongInt v)
  {
    return os << (v.ToString());
  }

  // Hasher to use in std::unordered_map, std::unordered_set, etc.
  //
  // USAGE
  //
  // using FooAlias = StrongInt<class FooTag, size_t>;
  // std::unordered_map<FooAlias, std::string, typename FooAlias::Hasher> map;
  //
  struct Hasher
  {
    using argument_type = StrongInt;
    using result_type = std::size_t;
    result_type operator()(const argument_type& id) const
    {
      return std::hash<int>()(id.get());
    }
  };

private:
  int value_;
};

template<typename Tag, typename NativeType>
const StrongInt<Tag, NativeType>
  StrongInt<Tag, NativeType>::kZero { 0 };

template<typename Tag, typename NativeType>
const StrongInt<Tag, NativeType>
  StrongInt<Tag, NativeType>::kOne { 1 };

// Define operators that take two StrongInt arguments. These operators are
// defined in terms of their op-equal member function cousins.
#define STRONG_INT_VS_STRONG_INT_BINARY_OP(op)                                 \
  template<typename TagType, typename ValueType>       \
  inline StrongInt<TagType, ValueType>                          \
  operator op(StrongInt<TagType, ValueType> lhs,                \
              StrongInt<TagType, ValueType> rhs) {              \
    lhs op ## = rhs;                                                           \
    return lhs;                                                                \
  }
STRONG_INT_VS_STRONG_INT_BINARY_OP(+);
STRONG_INT_VS_STRONG_INT_BINARY_OP(-);
STRONG_INT_VS_STRONG_INT_BINARY_OP(&);
STRONG_INT_VS_STRONG_INT_BINARY_OP(|);
STRONG_INT_VS_STRONG_INT_BINARY_OP(^);
#undef STRONG_INT_VS_STRONG_INT_BINARY_OP

// Define operators that take one StrongInt and one native integer argument.
// These operators are defined in terms of their op-equal member function
// cousins, mostly.
#define STRONG_INT_VS_NUMERIC_BINARY_OP(op)                                    \
  template<typename TagType, typename ValueType,       \
           typename NumType>                                                   \
  inline StrongInt<TagType, ValueType>                          \
  operator op(StrongInt<TagType, ValueType> lhs, NumType rhs) { \
    lhs op ## = rhs;                                                           \
    return lhs;                                                                \
  }

STRONG_INT_VS_NUMERIC_BINARY_OP(*);
STRONG_INT_VS_NUMERIC_BINARY_OP(/);
STRONG_INT_VS_NUMERIC_BINARY_OP(%);
STRONG_INT_VS_NUMERIC_BINARY_OP(<<);
STRONG_INT_VS_NUMERIC_BINARY_OP(>>);
#undef STRONG_INT_VS_NUMERIC_BINARY_OP

// This is used for commutative operators between one StrongInt and one native
// integer argument.  That is a long way of saying "multiplication".
#define NUMERIC_VS_STRONG_INT_BINARY_OP(op)                                    \
  template<typename TagType, typename ValueType,       \
           typename NumType>                                                   \
  inline StrongInt<TagType, ValueType>                          \
  operator op(NumType lhs, StrongInt<TagType, ValueType> rhs) { \
    rhs op ## = lhs;                                                           \
    return rhs;                                                                \
  }

NUMERIC_VS_STRONG_INT_BINARY_OP(*);
NUMERIC_VS_STRONG_INT_BINARY_OP(/);
NUMERIC_VS_STRONG_INT_BINARY_OP(%);
NUMERIC_VS_STRONG_INT_BINARY_OP(<<);
NUMERIC_VS_STRONG_INT_BINARY_OP(>>);
#undef NUMERIC_VS_STRONG_INT_BINARY_OP

// Define comparison operators.  We allow all comparison operators.
#define STRONG_INT_COMPARISON_OP(op)                                           \
  template<typename TagType, typename ValueType>       \
  inline bool operator op(StrongInt<TagType, ValueType> lhs,    \
                          StrongInt<TagType, ValueType> rhs) {  \
    return lhs.value() op rhs.value();                                         \
  }
STRONG_INT_COMPARISON_OP(==);
STRONG_INT_COMPARISON_OP(!=);
STRONG_INT_COMPARISON_OP(<);
STRONG_INT_COMPARISON_OP(<=);
STRONG_INT_COMPARISON_OP(>);
STRONG_INT_COMPARISON_OP(>=);
#undef STRONG_INT_COMPARISON_OP

}  // namespace basic

namespace std {

// Allow StrongInt to be used as a key to hashable containers.
template<typename Tag, typename NativeType>
struct hash<basic::StrongInt<Tag, NativeType> >
{
  size_t operator()(
      const basic::StrongInt<Tag, NativeType> &idx) const
  {
    return hash<NativeType>()(idx.value());
  }
};

}  // namespace std
