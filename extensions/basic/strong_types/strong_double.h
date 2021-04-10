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
#define STRONG_DOUBLE_TAG_NAME UniqueDoubleTypeTag

// format tag name (concats strings)
#define STRONG_DOUBLE_TAG_CUSTOM_2(using_name, suffix) \
  using_name ## _ ## suffix

// STRONG_DOUBLE_TAG_CUSTOM(MyType, UniqueTypeTag) expands to `MyType_UniqueTypeTag`
#define STRONG_DOUBLE_TAG_CUSTOM(using_name, suffix) \
  STRONG_DOUBLE_TAG_CUSTOM_2(using_name,suffix)

/// \note Each `StrongAlias` must have UNIQUE tag.
/// We assume that provided `using_name` globally unique
/// (even between shared libs!)
// STRONG_DOUBLE_TAG(MyType) expands to `MyType_UniqueTypeTag`
#define STRONG_DOUBLE_TAG(using_name) \
  STRONG_DOUBLE_TAG_CUSTOM(using_name,STRONG_DOUBLE_TAG_NAME)

#define DEFINE_STRONGLY_TYPED_DOUBLE(NAME, TYPE) \
  using NAME = basic::StrongDouble<class STRONG_DOUBLE_TAG(NAME), TYPE>

#define STRONGLY_TYPED_DOUBLE(NAME) \
  DEFINE_STRONGLY_TYPED_DOUBLE(NAME, double)

namespace basic {

// Type-safe double with `strict_cast` compile-time-checks
//
// StrongDouble objects are type-safe double values
// that cannot be implicitly casted to untyped doubles,
// doubles or different StrongDouble types while still
// provides all relevant logical and comparison operators.
//
// StrongDouble template parameter is a tag type
// that is going to be used to distinguish doubles
// of different types.
//
// EXAMPLE
//
// #include <basic/strong_types/strong_double.h>
//
// STRONGLY_TYPED_DOUBLE(foo);
//
// DEFINE_STRONGLY_TYPED_DOUBLE(bar, double);
//
template<
  typename Tag
  // primitive double type as defined by std::is_floating_point
  , typename NativeType
>
class StrongDouble
{
  static_assert(
    std::is_floating_point<NativeType>::value
    , "Invalid not-floating-point type for StrongDouble");

public:
  using type = NativeType;

  static const StrongDouble kZero;

  static const StrongDouble kOne;

  /// Constructs a StrongDouble object.
  constexpr StrongDouble() NO_EXCEPTION
    : value_()
  {}

  template<
    typename IntegralType
    , typename = typename std::enable_if<std::is_floating_point<IntegralType>::value>
  >
  constexpr explicit StrongDouble(IntegralType v) NO_EXCEPTION
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

  /// Casts a StrongDouble object to an untyped \c double.
  constexpr explicit operator double() const NO_EXCEPTION
  {
    return value_;
  }

  /// Casts a StrongDouble object to an untyped \c bool.
  constexpr explicit operator bool() const NO_EXCEPTION
  {
    return static_cast<bool>(value_);
  }

  double get() const NO_EXCEPTION
  {
    return value_;
  }

  constexpr double& value() & { return value_; }
  constexpr const double& value() const& { return value_; }
  constexpr double&& value() && { return RVALUE_CAST(value_); }
  constexpr const double&& value() const&& { return COPY_OR_MOVE(value_); }

  // Shortcut for `.value`
  //
  // BEFORE
  // DCHECK(obj.value().empty());
  //
  // AFTER
  // DCHECK((*obj).empty());
  constexpr const double& operator*() const
  {
    return value_;
  }

  constexpr double& operator*()
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
  constexpr const double* operator->() const
  {
    return &value_;
  }

  constexpr double* operator->()
  {
    return &value_;
  }

  /// Logical OR.
  friend StrongDouble operator||(
    StrongDouble x, StrongDouble y) NO_EXCEPTION
  {
    return StrongDouble(x.value_ || y.value_);
  }

  /// Logical AND.
  friend StrongDouble operator&&(
    StrongDouble x, StrongDouble y) NO_EXCEPTION
  {
    return StrongDouble(x.value_ && y.value_);
  }

  /// Logical NOT.
  friend StrongDouble operator!(
    StrongDouble x) NO_EXCEPTION
  {
    return StrongDouble(!x.value_);
  }

  const StrongDouble operator+() const {
    return StrongDouble(value_);
  }

  const StrongDouble operator-() const {
    return StrongDouble(-value_);
  }

  /// Equal-to operator.
  friend int operator==(
    StrongDouble x, StrongDouble y) NO_EXCEPTION
  {
    return x.value_ == y.value_;
  }

#if __cplusplus <= 201703L
  /// Not-equal-to operator.
  friend int operator!=(
    StrongDouble x, StrongDouble y) NO_EXCEPTION
  {
    return x.value_ != y.value_;
  }
#endif

  /// Equal-to operator.
  friend bool operator==(
    double x, const StrongDouble& y) NO_EXCEPTION
  {
    return x == y.value_;
  }

#if __cplusplus <= 201703L
  /// Not-equal-to operator.
  friend bool operator!=(
    double x, const StrongDouble& y) NO_EXCEPTION
  {
    return x != y.value_;
  }
#endif

  // Increment and decrement operators.
  StrongDouble& operator++() {  // ++x
    ++value_;
    return *this;
  }
  const StrongDouble operator++(int) {  // x++
    StrongDouble temp(*this);
    ++value_;
    return temp;
  }
  StrongDouble& operator--() {  // --x
    --value_;
    return *this;
  }
  const StrongDouble operator--(int) {  // x--
    StrongDouble temp(*this);
    --value_;
    return temp;
  }

  // Action-Assignment operators.
  StrongDouble& operator+=(StrongDouble arg) {
    value_ += arg.value();
    return *this;
  }
  StrongDouble& operator-=(StrongDouble arg) {
    value_ -= arg.value();
    return *this;
  }
  template<typename ArgType>
  StrongDouble& operator*=(ArgType arg) {
    static_assert(
      std::is_floating_point<ArgType>::value
      , "Invalid not-floating-point type for StrongDouble::operator*=");
    value_ *= ::base::strict_cast<NativeType>(arg);
    return *this;
  }
  template<typename ArgType>
  StrongDouble& operator/=(ArgType arg) {
    static_assert(
      std::is_floating_point<ArgType>::value
      , "Invalid not-floating-point type for StrongDouble::operator*=");
    value_ /= ::base::strict_cast<NativeType>(arg);
    return *this;
  }
  template<typename ArgType>
  StrongDouble& operator%=(ArgType arg) {
    static_assert(
      std::is_floating_point<ArgType>::value
      , "Invalid not-floating-point type for StrongDouble::operator*=");
    value_ %= ::base::strict_cast<NativeType>(arg);
    return *this;
  }
  StrongDouble& operator&=(StrongDouble arg) {
    value_ &= arg.value();
    return *this;
  }
  StrongDouble& operator|=(StrongDouble arg) {
    value_ |= arg.value();
    return *this;
  }
  StrongDouble& operator^=(StrongDouble arg) {
    value_ ^= arg.value();
    return *this;
  }

  const std::string ToString() const NO_EXCEPTION
  {
    return std::to_string(value_);
  }

  /// Prints StrongDouble value to an output stream.
  friend std::ostream& operator<<(
    std::ostream& os, StrongDouble v)
  {
    return os << (v.ToString());
  }

  // Hasher to use in std::unordered_map, std::unordered_set, etc.
  //
  // USAGE
  //
  // using FooAlias = StrongDouble<class FooTag, size_t>;
  // std::unordered_map<FooAlias, std::string, typename FooAlias::Hasher> map;
  //
  struct Hasher
  {
    using argument_type = StrongDouble;
    using result_type = std::size_t;
    result_type operator()(const argument_type& id) const
    {
      return std::hash<double>()(id.get());
    }
  };

private:
  double value_;
};

template<typename Tag, typename NativeType>
const StrongDouble<Tag, NativeType>
  StrongDouble<Tag, NativeType>::kZero { 0 };

template<typename Tag, typename NativeType>
const StrongDouble<Tag, NativeType>
  StrongDouble<Tag, NativeType>::kOne { 1 };

// Define operators that take two StrongDouble arguments. These operators are
// defined in terms of their op-equal member function cousins.
#define STRONG_DOUBLE_VS_STRONG_DOUBLE_BINARY_OP(op)                                 \
  template<typename TagType, typename ValueType>       \
  inline StrongDouble<TagType, ValueType>                          \
  operator op(StrongDouble<TagType, ValueType> lhs,                \
              StrongDouble<TagType, ValueType> rhs) {              \
    lhs op ## = rhs;                                                           \
    return lhs;                                                                \
  }
STRONG_DOUBLE_VS_STRONG_DOUBLE_BINARY_OP(+);
STRONG_DOUBLE_VS_STRONG_DOUBLE_BINARY_OP(-);
STRONG_DOUBLE_VS_STRONG_DOUBLE_BINARY_OP(&);
STRONG_DOUBLE_VS_STRONG_DOUBLE_BINARY_OP(|);
STRONG_DOUBLE_VS_STRONG_DOUBLE_BINARY_OP(^);
#undef STRONG_DOUBLE_VS_STRONG_DOUBLE_BINARY_OP

// Define operators that take one StrongDouble and one native double argument.
// These operators are defined in terms of their op-equal member function
// cousins, mostly.
#define STRONG_DOUBLE_VS_NUMERIC_BINARY_OP(op)                                    \
  template<typename TagType, typename ValueType,       \
           typename NumType>                                                   \
  inline StrongDouble<TagType, ValueType>                          \
  operator op(StrongDouble<TagType, ValueType> lhs, NumType rhs) { \
    lhs op ## = rhs;                                                           \
    return lhs;                                                                \
  }

STRONG_DOUBLE_VS_NUMERIC_BINARY_OP(*);
STRONG_DOUBLE_VS_NUMERIC_BINARY_OP(/);
STRONG_DOUBLE_VS_NUMERIC_BINARY_OP(%);
STRONG_DOUBLE_VS_NUMERIC_BINARY_OP(<<);
STRONG_DOUBLE_VS_NUMERIC_BINARY_OP(>>);
#undef STRONG_DOUBLE_VS_NUMERIC_BINARY_OP

// This is used for commutative operators between one StrongDouble and one native
// double argument.  That is a long way of saying "multiplication".
#define NUMERIC_VS_STRONG_DOUBLE_BINARY_OP(op)                                    \
  template<typename TagType, typename ValueType,       \
           typename NumType>                                                   \
  inline StrongDouble<TagType, ValueType>                          \
  operator op(NumType lhs, StrongDouble<TagType, ValueType> rhs) { \
    rhs op ## = lhs;                                                           \
    return rhs;                                                                \
  }

NUMERIC_VS_STRONG_DOUBLE_BINARY_OP(*);
NUMERIC_VS_STRONG_DOUBLE_BINARY_OP(/);
NUMERIC_VS_STRONG_DOUBLE_BINARY_OP(%);
NUMERIC_VS_STRONG_DOUBLE_BINARY_OP(<<);
NUMERIC_VS_STRONG_DOUBLE_BINARY_OP(>>);
#undef NUMERIC_VS_STRONG_DOUBLE_BINARY_OP

// Define comparison operators.  We allow all comparison operators.
#define STRONG_DOUBLE_COMPARISON_OP(op)                                           \
  template<typename TagType, typename ValueType>       \
  inline bool operator op(StrongDouble<TagType, ValueType> lhs,    \
                          StrongDouble<TagType, ValueType> rhs) {  \
    return lhs.value() op rhs.value();                                         \
  }
STRONG_DOUBLE_COMPARISON_OP(==);
STRONG_DOUBLE_COMPARISON_OP(!=);
STRONG_DOUBLE_COMPARISON_OP(<);
STRONG_DOUBLE_COMPARISON_OP(<=);
STRONG_DOUBLE_COMPARISON_OP(>);
STRONG_DOUBLE_COMPARISON_OP(>=);
#undef STRONG_DOUBLE_COMPARISON_OP

}  // namespace basic

namespace std {

// Allow StrongDouble to be used as a key to hashable containers.
template<typename Tag, typename NativeType>
struct hash<basic::StrongDouble<Tag, NativeType> >
{
  size_t operator()(
      const basic::StrongDouble<Tag, NativeType> &idx) const
  {
    return hash<NativeType>()(idx.value());
  }
};

}  // namespace std
