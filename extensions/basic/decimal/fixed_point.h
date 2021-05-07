/*
 * Copyright (c) 2020, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basic,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <limits>
#include <type_traits>

#include <base/check.h>
#include <base/logging.h>
#include <base/notreached.h>
#include <base/macros.h>
#include <base/compiler_specific.h>

namespace basic {

// This is a wrapper struct that enforces "strong typing"
// at the construction site of the type. No implicit
// conversions will be allowed and you will need to use the
// name of the type alias (i.e. scale_type{0})
template <typename T>
struct strong_typedef {
  T _t;
  explicit constexpr strong_typedef(T t) : _t(t) {}
  operator T() const { return _t; }
};
/** \endcond */

using scale_type = strong_typedef<int32_t>;

/**
 * @brief Scoped enumerator to use when constructing `FixedPointNumber`
 *
 * Examples:
 * ```cpp
 * using decimal32 = FixedPointNumber<int32_t, Radix::BASE_10>;
 * using binary64  = FixedPointNumber<int64_t, Radix::BASE_2>;
 * ```
 */
enum class Radix : int32_t { BASE_2 = 2, BASE_10 = 10 };

template <typename T>
constexpr inline auto is_supported_representation_type()
{
  return std::is_same<T, int32_t>::value || std::is_same<T, int64_t>::value;
}

template <typename T>
constexpr inline auto is_supported_construction_value_type()
{
  return std::is_integral<T>::value || std::is_floating_point<T>::value;
}

// Helper functions for `FixedPointNumber` type
namespace detail {
/**
 * @brief A function for integer exponentiation by squaring
 *
 * https://simple.wikipedia.org/wiki/Exponentiation_by_squaring <br>
 * Note: this is the iterative equivalent of the recursive definition (faster) <br>
 * Quick-bench: http://quick-bench.com/Wg7o7HYQC9FW5M0CO0wQAjSwP_Y <br>
 * `exponent` comes from `using scale_type = strong_typedef<int32_t>` <br>
 *
 * @tparam Rep Representation type for return type
 * @tparam Base The base to be exponentiated
 * @param exponent The exponent to be used for exponentiation
 * @return Result of `Base` to the power of `exponent` of type `Rep`
 */
template <typename Rep,
          Radix Base,
          typename T,
          typename std::enable_if_t<(std::is_same<int32_t, T>::value &&
                                           is_supported_representation_type<Rep>())>* = nullptr>
Rep ipow(T exponent)
{
  CHECK(exponent >= 0)
    << "integer exponentiation with negative exponent is not possible.";
  if (exponent == 0) return static_cast<Rep>(1);
  auto extra  = static_cast<Rep>(1);
  auto square = static_cast<Rep>(Base);
  while (exponent > 1) {
    if (exponent & 1 /* odd */) {
      extra *= square;
      exponent -= 1;
    }
    exponent /= 2;
    square *= square;
  }
  return square * extra;
}

/** @brief Helper function to negate strongly typed scale_type
 *
 * @param scale The scale to be negated
 * @return The negated scale
 */
inline auto negate(scale_type const& scale) { return scale_type{-scale}; }

/** @brief Function that performs a `right shift` scale "times" on the `val`
 *
 * Note: perform this operation when constructing with positive scale
 *
 * @tparam Rep Representation type needed for integer exponentiation
 * @tparam Rad The radix which will act as the base in the exponentiation
 * @tparam T Type for value `val` being shifted and the return type
 * @param val The value being shifted
 * @param scale The amount to shift the value by
 * @return Shifted value of type T
 */
template <typename Rep, Radix Rad, typename T>
constexpr T right_shift(T const& val, scale_type const& scale)
{
  return val / ipow<Rep, Rad>(scale._t);
}

/** @brief Function that performs a `left shift` scale "times" on the `val`
 *
 * Note: perform this operation when constructing with negative scale
 *
 * @tparam Rep Representation type needed for integer exponentiation
 * @tparam Rad The radix which will act as the base in the exponentiation
 * @tparam T Type for value `val` being shifted and the return type
 * @param val The value being shifted
 * @param scale The amount to shift the value by
 * @return Shifted value of type T
 */
template <typename Rep, Radix Rad, typename T>
constexpr T left_shift(T const& val, scale_type const& scale)
{
  return val * ipow<Rep, Rad>(-scale._t);
}

/** @brief Function that performs a `right` or `left shift`
 * scale "times" on the `val`
 *
 * Note: Function will call the correct right or left shift based
 * on the sign of `val`
 *
 * @tparam Rep Representation type needed for integer exponentiation
 * @tparam Rad The radix which will act as the base in the exponentiation
 * @tparam T Type for value `val` being shifted and the return type
 * @param val The value being shifted
 * @param scale The amount to shift the value by
 * @return Shifted value of type T
 */
template <typename Rep, Radix Rad, typename T>
constexpr T shift(T const& val, scale_type const& scale)
{
  if (scale == 0)
    return val;
  else if (scale > 0)
    return right_shift<Rep, Rad>(val, scale);
  else
    return left_shift<Rep, Rad>(val, scale);
}

}  // namespace detail

/**
 * @addtogroup FixedPointNumber_classes
 * @{
 * @file
 * @brief Class definition for fixed point data type
 */

/**
 * @brief Helper struct for constructing `FixedPointNumber` when value is already shifted
 *
 * Example:
 * ```cpp
 * using decimal32 = FixedPointNumber<int32_t, Radix::BASE_10>;
 * auto n = decimal32{scaled_integer{1001, 3}}; // n = 1.001
 * ```
 *
 * @tparam Rep The representation type (either `int32_t` or `int64_t`)
 */
template <typename Rep,
          typename std::enable_if_t<is_supported_representation_type<Rep>()>* = nullptr>
struct scaled_integer {
  Rep value;
  scale_type scale;
  explicit scaled_integer(Rep v, scale_type s) : value(v), scale(s) {}
};

/**
 * @brief A type for representing a number with a fixed amount of precision
 *
 * Currently, only binary and decimal `FixedPointNumber` numbers are supported.
 * Binary operations can only be performed with other `FixedPointNumber` numbers
 *
 * @tparam Rep The representation type (either `int32_t` or `int64_t`)
 * @tparam Rad The radix/base (either `Radix::BASE_2` or `Radix::BASE_10`)
 */
template <typename Rep, Radix Rad>
class FixedPointNumber {
  // _value of `decimal32(12.43)` is 12
  Rep _value;
  scale_type _scale;

 public:
  using rep = Rep;

  /**
   * @brief Constructor that will perform shifting to store value appropriately
   *
   * @tparam T The type that you are constructing from (integral or floating)
   * @param value The value that will be constructed from
   * @param scale The exponent that is applied to Rad to perform shifting
   */
  template <typename T,
            typename std::enable_if_t<is_supported_construction_value_type<T>() &&
                                            is_supported_representation_type<Rep>()>* = nullptr>
  explicit FixedPointNumber(T const& value, scale_type const& scale)
    : _value{static_cast<Rep>(detail::shift<Rep, Rad>(value, scale))}, _scale{scale}
  {
    //DCHECK_LE(_scale, 0);
  }

  /**
   * @brief Constructor that will not perform shifting (assumes value already
   * shifted)
   *
   * @param s scaled_integer that contains scale and already shifted value
   */
  explicit FixedPointNumber(scaled_integer<Rep> s) : _value{s.value}, _scale{s.scale} {}

  /**
   * @brief "Scale-less" constructor that constructs `FixedPointNumber` number with a specified
   * value and scale of zero
   */
  template <typename T,
            typename std::enable_if_t<is_supported_construction_value_type<T>()>* = nullptr>
  FixedPointNumber(T const& value)
    : _value{static_cast<Rep>(value)}, _scale{scale_type{0}}
  {
    //DCHECK_LE(_scale, 0);
  }

  /**
   * @brief Default constructor that constructs `FixedPointNumber` number with a
   * value and scale of zero
   */
  FixedPointNumber() : _value{0}, _scale{scale_type{0}} {
    //DCHECK_LE(_scale, 0);
  }

  /**
   * @brief Explicit conversion operator
   *
   * @tparam U The type that is being explicitly converted to (integral or floating)
   * @return The `FixedPointNumber` number in base 10 (aka human readable format)
   */
  template <typename U,
            typename std::enable_if_t<is_supported_construction_value_type<U>()>* = nullptr>
  explicit constexpr operator U() const
  {
    return detail::shift<Rep, Rad>(static_cast<U>(_value), detail::negate(_scale));
  }

  operator scaled_integer<Rep>() const
  {
    return scaled_integer<Rep>{_value, _scale};
  }

  /**
   * @brief Method that returns the underlying value of the `FixedPointNumber` number
   *
   * @return The underlying value of the `FixedPointNumber` number
   *
   * @example _value of `decimal32(12.43)` is 12
   */
  rep value() const { return _value; }

  /**
   * @brief Method that returns the scale of the `FixedPointNumber` number
   *
   * @return The scale of the `FixedPointNumber` number
   */
  scale_type scale() const { return _scale; }

  /**
   * @brief Explicit conversion operator to `bool`
   *
   * @return The `FixedPointNumber` value as a boolean (zero is `false`, nonzero is `true`)
   */
  explicit constexpr operator bool() const
  {
    return static_cast<bool>(_value);
  }

  /**
   * @brief operator +=
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return The sum
   */
  template <typename Rep1, Radix Rad1>
  FixedPointNumber<Rep1, Rad1>& operator+=(FixedPointNumber<Rep1, Rad1> const& rhs)
  {
    *this = *this + rhs;
    return *this;
  }

  /**
   * @brief operator *=
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return The product
   */
  template <typename Rep1, Radix Rad1>
  FixedPointNumber<Rep1, Rad1>& operator*=(FixedPointNumber<Rep1, Rad1> const& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  /**
   * @brief operator -=
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return The difference
   */
  template <typename Rep1, Radix Rad1>
  FixedPointNumber<Rep1, Rad1>& operator-=(FixedPointNumber<Rep1, Rad1> const& rhs)
  {
    *this = *this - rhs;
    return *this;
  }

  /**
   * @brief operator /=
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return The quotient
   */
  template <typename Rep1, Radix Rad1>
  FixedPointNumber<Rep1, Rad1>& operator/=(FixedPointNumber<Rep1, Rad1> const& rhs)
  {
    *this = *this / rhs;
    return *this;
  }

  /**
   * @brief operator ++ (post-increment)
   *
   * @return The incremented result
   */
  FixedPointNumber<Rep, Rad>& operator++()
  {
    *this = *this + FixedPointNumber<Rep, Rad>{1, scale_type{_scale}};
    return *this;
  }

  /**
   * @brief operator + (for adding two `FixedPointNumber` numbers)
   *
   * If `_scale`s are equal, `_value`s are added <br>
   * If `_scale`s are not equal, number with smaller `_scale` is shifted to the
   * greater `_scale`, and then `_value`s are added
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return The resulting `FixedPointNumber` sum
   */
  template <typename Rep1, Radix Rad1>
  friend FixedPointNumber<Rep1, Rad1> operator+(
    FixedPointNumber<Rep1, Rad1> const& lhs, FixedPointNumber<Rep1, Rad1> const& rhs);

  /**
   * @brief operator - (for subtracting two `FixedPointNumber` numbers)
   *
   * If `_scale`s are equal, `_value`s are subtracted <br>
   * If `_scale`s are not equal, number with smaller `_scale` is shifted to the
   * greater `_scale`, and then `_value`s are subtracted
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return The resulting `FixedPointNumber` difference
   */
  template <typename Rep1, Radix Rad1>
  friend FixedPointNumber<Rep1, Rad1> operator-(
    FixedPointNumber<Rep1, Rad1> const& lhs, FixedPointNumber<Rep1, Rad1> const& rhs);

  /**
   * @brief operator * (for multiplying two `FixedPointNumber` numbers)
   *
   * `_scale`s are added and `_value`s are multiplied
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return The resulting `FixedPointNumber` product
   */
  template <typename Rep1, Radix Rad1>
  friend FixedPointNumber<Rep1, Rad1> operator*(
    FixedPointNumber<Rep1, Rad1> const& lhs, FixedPointNumber<Rep1, Rad1> const& rhs);

  /**
   * @brief operator / (for dividing two `FixedPointNumber` numbers)
   *
   * `_scale`s are subtracted and `_value`s are divided
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return The resulting `FixedPointNumber` quotient
   */
  template <typename Rep1, Radix Rad1>
  friend FixedPointNumber<Rep1, Rad1> operator/(
    FixedPointNumber<Rep1, Rad1> const& lhs, FixedPointNumber<Rep1, Rad1> const& rhs);

  /**
   * @brief operator == (for comparing two `FixedPointNumber` numbers)
   *
   * If `_scale`s are equal, `_value`s are compared <br>
   * If `_scale`s are not equal, number with smaller `_scale` is shifted to the
   * greater `_scale`, and then `_value`s are compared
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return true if `lhs` and `rhs` are equal, false if not
   */
  template <typename Rep1, Radix Rad1>
  friend bool operator==(FixedPointNumber<Rep1, Rad1> const& lhs,
                                                   FixedPointNumber<Rep1, Rad1> const& rhs);

  /**
   * @brief operator != (for comparing two `FixedPointNumber` numbers)
   *
   * If `_scale`s are equal, `_value`s are compared <br>
   * If `_scale`s are not equal, number with smaller `_scale` is shifted to the
   * greater `_scale`, and then `_value`s are compared
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return true if `lhs` and `rhs` are not equal, false if not
   */
#if __cplusplus <= 201703L
  template <typename Rep1, Radix Rad1>
  friend bool operator!=(FixedPointNumber<Rep1, Rad1> const& lhs,
                                                   FixedPointNumber<Rep1, Rad1> const& rhs);
#endif

  /**
   * @brief operator <= (for comparing two `FixedPointNumber` numbers)
   *
   * If `_scale`s are equal, `_value`s are compared <br>
   * If `_scale`s are not equal, number with smaller `_scale` is shifted to the
   * greater `_scale`, and then `_value`s are compared
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return true if `lhs` less than or equal to `rhs`, false if not
   */
  template <typename Rep1, Radix Rad1>
  friend bool operator<=(FixedPointNumber<Rep1, Rad1> const& lhs,
                                                   FixedPointNumber<Rep1, Rad1> const& rhs);

  /**
   * @brief operator >= (for comparing two `FixedPointNumber` numbers)
   *
   * If `_scale`s are equal, `_value`s are compared <br>
   * If `_scale`s are not equal, number with smaller `_scale` is shifted to the
   * greater `_scale`, and then `_value`s are compared
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return true if `lhs` greater than or equal to `rhs`, false if not
   */
  template <typename Rep1, Radix Rad1>
  friend bool operator>=(FixedPointNumber<Rep1, Rad1> const& lhs,
                                                   FixedPointNumber<Rep1, Rad1> const& rhs);

  /**
   * @brief operator < (for comparing two `FixedPointNumber` numbers)
   *
   * If `_scale`s are equal, `_value`s are compared <br>
   * If `_scale`s are not equal, number with smaller `_scale` is shifted to the
   * greater `_scale`, and then `_value`s are compared
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return true if `lhs` less than `rhs`, false if not
   */
  template <typename Rep1, Radix Rad1>
  friend bool operator<(FixedPointNumber<Rep1, Rad1> const& lhs,
                                                  FixedPointNumber<Rep1, Rad1> const& rhs);

  /**
   * @brief operator > (for comparing two `FixedPointNumber` numbers)
   *
   * If `_scale`s are equal, `_value`s are compared <br>
   * If `_scale`s are not equal, number with smaller `_scale` is shifted to the
   * greater `_scale`, and then `_value`s are compared
   *
   * @tparam Rep1 Representation type of number being added to `this`
   * @tparam Rad1 Radix (base) type of number being added to `this`
   * @return true if `lhs` greater than `rhs`, false if not
   */
  template <typename Rep1, Radix Rad1>
  friend bool operator>(FixedPointNumber<Rep1, Rad1> const& lhs,
                                                  FixedPointNumber<Rep1, Rad1> const& rhs);

  /**
   * @brief Method for creating a `FixedPointNumber` number with a new `scale`
   *
   * The `FixedPointNumber` number returned will have the same value, underlying representation and
   * radix as `this`, the only thing changed is the scale
   *
   * @param scale The `scale` of the returned `FixedPointNumber` number
   * @return `FixedPointNumber` number with a new `scale`
   */
  FixedPointNumber<Rep, Rad> rescaled(scale_type scale) const
  {
    if (scale == _scale) return *this;
    Rep const value = detail::shift<Rep, Rad>(_value, scale_type{scale - _scale});
    return FixedPointNumber<Rep, Rad>{scaled_integer<Rep>{value, scale}};
  }

  /**
   * @brief Returns a string representation of the FixedPointNumber value.
   */
  explicit operator std::string() const
  {
    if (_scale < 0) {
      int const n = std::pow(10, -_scale);
      int const f = _value % n;
      auto const num_zeros =
        std::max(0, (-_scale - static_cast<int32_t>(std::to_string(f).size())));
      auto const zeros = std::string(num_zeros, '0');
      return std::to_string(_value / n) + std::string(".") + zeros +
             std::to_string(std::abs(_value) % n);
    } else {
      auto const zeros = std::string(_scale, '0');
      return std::to_string(_value) + zeros;
    }
  }
};  // namespace numeric

/** @brief Function that converts Rep to `std::string`
 *
 * @tparam Rep Representation type
 * @return String-ified Rep
 */
template <typename Rep>
std::string print_rep()
{
  if (std::is_same<Rep, int32_t>::value)
    return "int32_t";
  else if (std::is_same<Rep, int64_t>::value)
    return "int64_t";
  else
    return "unknown type";
}

/** @brief Function for identifying integer overflow when adding
 *
 * @tparam Rep Type of integer to check for overflow on
 * @tparam T Types of lhs and rhs (ensures they are the same type)
 * @param lhs Left hand side of addition
 * @param rhs Right hand side of addition
 * @return true if addition causes overflow, false otherwise
 */
template <typename Rep, typename T>
bool addition_overflow(T lhs, T rhs)
{
  return rhs > 0 ? lhs > std::numeric_limits<Rep>::max() - rhs
                 : lhs < std::numeric_limits<Rep>::min() - rhs;
}

/** @brief Function for identifying integer overflow when subtracting
 *
 * @tparam Rep Type of integer to check for overflow on
 * @tparam T Types of lhs and rhs (ensures they are the same type)
 * @param lhs Left hand side of subtraction
 * @param rhs Right hand side of subtraction
 * @return true if subtraction causes overflow, false otherwise
 */
template <typename Rep, typename T>
auto subtraction_overflow(T lhs, T rhs)
{
  return rhs > 0 ? lhs < std::numeric_limits<Rep>::min() + rhs
                 : lhs > std::numeric_limits<Rep>::max() + rhs;
}

/** @brief Function for identifying integer overflow when dividing
 *
 * @tparam Rep Type of integer to check for overflow on
 * @tparam T Types of lhs and rhs (ensures they are the same type)
 * @param lhs Left hand side of division
 * @param rhs Right hand side of division
 * @return true if division causes overflow, false otherwise
 */
template <typename Rep, typename T>
auto division_overflow(T lhs, T rhs)
{
  return lhs == std::numeric_limits<Rep>::min() && rhs == -1;
}

/** @brief Function for identifying integer overflow when multiplying
 *
 * @tparam Rep Type of integer to check for overflow on
 * @tparam T Types of lhs and rhs (ensures they are the same type)
 * @param lhs Left hand side of multiplication
 * @param rhs Right hand side of multiplication
 * @return true if multiplication causes overflow, false otherwise
 */
template <typename Rep, typename T>
auto multiplication_overflow(T lhs, T rhs)
{
  auto const min = std::numeric_limits<Rep>::min();
  auto const max = std::numeric_limits<Rep>::max();
  if (rhs > 0)
    return lhs > max / rhs || lhs < min / rhs;
  else if (rhs < -1)
    return lhs > min / rhs || lhs < max / rhs;
  else
    return rhs == -1 && lhs == min;
}

// PLUS Operation
template <typename Rep1, Radix Rad1>
FixedPointNumber<Rep1, Rad1> operator+(FixedPointNumber<Rep1, Rad1> const& lhs,
                                                            FixedPointNumber<Rep1, Rad1> const& rhs)
{
  auto const scale = std::min(lhs._scale, rhs._scale);
  auto const sum   = lhs.rescaled(scale)._value + rhs.rescaled(scale)._value;

  DCHECK(!addition_overflow<Rep1>(lhs.rescaled(scale)._value, rhs.rescaled(scale)._value))
    << "FixedPointNumber overflow of underlying representation type "
    << print_rep<Rep1>();

  return FixedPointNumber<Rep1, Rad1>{scaled_integer<Rep1>{sum, scale}};
}

// MINUS Operation
template <typename Rep1, Radix Rad1>
FixedPointNumber<Rep1, Rad1> operator-(FixedPointNumber<Rep1, Rad1> const& lhs,
                                                            FixedPointNumber<Rep1, Rad1> const& rhs)
{
  auto const scale = std::min(lhs._scale, rhs._scale);
  auto const diff  = lhs.rescaled(scale)._value - rhs.rescaled(scale)._value;

  DCHECK(!subtraction_overflow<Rep1>(lhs.rescaled(scale)._value, rhs.rescaled(scale)._value))
    << "FixedPointNumber overflow of underlying representation type "
    << print_rep<Rep1>();

  return FixedPointNumber<Rep1, Rad1>{scaled_integer<Rep1>{diff, scale}};
}

// MULTIPLIES Operation
template <typename Rep1, Radix Rad1>
FixedPointNumber<Rep1, Rad1> operator*(FixedPointNumber<Rep1, Rad1> const& lhs,
                                                            FixedPointNumber<Rep1, Rad1> const& rhs)
{
  DCHECK(!multiplication_overflow<Rep1>(lhs._value, rhs._value))
    << "FixedPointNumber overflow of underlying representation type "
    << print_rep<Rep1>();

  scale_type const scale{lhs._scale + rhs._scale};
  auto const mul = (lhs._value * rhs._value);

  //scale_type const scale_after = std::min(lhs._scale, rhs._scale);
  return FixedPointNumber<Rep1, Rad1>{
    scaled_integer<Rep1>(mul, scale)};//.rescaled(scale_after);
}

// DIVISION Operation
template <typename Rep1, Radix Rad1>
FixedPointNumber<Rep1, Rad1> operator/(FixedPointNumber<Rep1, Rad1> const& lhs,
                                                            FixedPointNumber<Rep1, Rad1> const& rhs)
{
  /// \todo does not work as expected
  /// Make code as in https://stackoverflow.com/a/79942
  NOTIMPLEMENTED();

  DCHECK(!division_overflow<Rep1>(lhs._value, rhs._value))
    << "FixedPointNumber overflow of underlying representation type "
    << print_rep<Rep1>();

  FixedPointNumber<Rep1, Rad1> lhs_scaled{
    lhs//.rescaled(scale_type{std::min(lhs._scale, rhs._scale)})
  };
  FixedPointNumber<Rep1, Rad1> rhs_scaled{
    rhs//.rescaled(scale_type{std::min(lhs._scale, rhs._scale)})
  };
  return FixedPointNumber<Rep1, Rad1>{
    scaled_integer<Rep1>(lhs_scaled._value / rhs_scaled._value
    , scale_type{lhs_scaled._scale - rhs_scaled._scale}
  )}
    /*.rescaled(scale_type{lhs._scale - rhs._scale})*/;
}

// EQUALITY COMPARISON Operation
template <typename Rep1, Radix Rad1>
bool operator==(FixedPointNumber<Rep1, Rad1> const& lhs,
                                          FixedPointNumber<Rep1, Rad1> const& rhs)
{
  auto const scale = std::min(lhs._scale, rhs._scale);
  return lhs.rescaled(scale)._value == rhs.rescaled(scale)._value;
}

#if __cplusplus <= 201703L
// EQUALITY NOT COMPARISON Operation
template <typename Rep1, Radix Rad1>
bool operator!=(FixedPointNumber<Rep1, Rad1> const& lhs,
                                          FixedPointNumber<Rep1, Rad1> const& rhs)
{
  auto const scale = std::min(lhs._scale, rhs._scale);
  return lhs.rescaled(scale)._value != rhs.rescaled(scale)._value;
}
#endif

// LESS THAN OR EQUAL TO Operation
template <typename Rep1, Radix Rad1>
bool operator<=(FixedPointNumber<Rep1, Rad1> const& lhs,
                                          FixedPointNumber<Rep1, Rad1> const& rhs)
{
  auto const scale = std::min(lhs._scale, rhs._scale);
  return lhs.rescaled(scale)._value <= rhs.rescaled(scale)._value;
}

// GREATER THAN OR EQUAL TO Operation
template <typename Rep1, Radix Rad1>
bool operator>=(FixedPointNumber<Rep1, Rad1> const& lhs,
                                          FixedPointNumber<Rep1, Rad1> const& rhs)
{
  auto const scale = std::min(lhs._scale, rhs._scale);
  return lhs.rescaled(scale)._value >= rhs.rescaled(scale)._value;
}

// LESS THAN Operation
template <typename Rep1, Radix Rad1>
bool operator<(FixedPointNumber<Rep1, Rad1> const& lhs,
                                         FixedPointNumber<Rep1, Rad1> const& rhs)
{
  auto const scale = std::min(lhs._scale, rhs._scale);
  return lhs.rescaled(scale)._value < rhs.rescaled(scale)._value;
}

// GREATER THAN Operation
template <typename Rep1, Radix Rad1>
bool operator>(FixedPointNumber<Rep1, Rad1> const& lhs,
                                         FixedPointNumber<Rep1, Rad1> const& rhs)
{
  auto const scale = std::min(lhs._scale, rhs._scale);
  return lhs.rescaled(scale)._value > rhs.rescaled(scale)._value;
}

template<typename T>
using BigFloat = FixedPointNumber<T, Radix::BASE_2>;

template<typename T>
using BigDecimal = FixedPointNumber<T, Radix::BASE_10>;

using decimal32 = BigDecimal<int32_t>;
using decimal64 = BigDecimal<int64_t>;

/// \todo
//using Decimal128 = Decimal<Int128>;
//using Decimal256 = Decimal<Int256>;

/**
 * @brief Indicates whether the type `T` is a fixed-point type.
 *
 * @tparam T  The type to verify
 * @return true `T` is a fixed-point type
 * @return false  `T` is not a fixed-point type
 */
template <typename T>
constexpr inline bool is_fixed_point()
{
  return std::is_same<decimal32, T>::value || std::is_same<decimal64, T>::value;
}

struct is_fixed_point_impl {
  template <typename T>
  bool operator()()
  {
    return is_fixed_point<T>();
  }
};

/**
 * @brief Indicates whether `type` is a fixed point `data_type`.
 *
 * @param type The `data_type` to verify
 * @return true `type` is a fixed point type
 * @return false `type` is not a fixed point type
 */
template <typename T>
constexpr inline bool is_fixed_point(T type)
{
  return is_fixed_point_impl{}.template operator()<T>();
}

/**
 * @brief Indicates whether the type `T` is a numeric type.
 *
 * @tparam T  The type to verify
 * @return true `T` is numeric
 * @return false  `T` is not numeric
 */
template <typename T>
constexpr inline bool is_numeric()
{
  return std::is_integral<T>::value or std::is_floating_point<T>::value;
}

struct is_numeric_impl {
  template <typename T>
  bool operator()()
  {
    return is_numeric<T>();
  }
};
/**
 * @brief Indicates whether `type` is a numeric `data_type`.
 *
 * "Numeric" types are fundamental integral/floating point types such as `INT*`
 * or `FLOAT*`. Types that wrap a numeric type are not considered numeric, e.g.,
 *`TIMESTAMP`.
 *
 * @param type The `data_type` to verify
 * @return true `type` is numeric
 * @return false `type` is not numeric
 */
template <typename T>
constexpr inline bool is_numeric(T type)
{
  return is_numeric_impl{}.template operator()<T>();
}

/**
 * @brief "Returns" the corresponding type that is stored on the device when using `cudf::column`
 *
 * For `decimal32`, the storage type is an `int32_t`.
 * For `decimal64`, the storage type is an `int64_t`.
 *
 * Use this "type function" with the `using` type alias:
 * @code
 * using Type = storage_type_t<Element>;
 * @endcode
 *
 * @tparam T The literal type that is stored on the host
 */
// clang-format off
template <typename T>
using storage_type_t =
  std::conditional_t<
    std::is_same<decimal32, T>::value, int32_t,
    std::conditional_t<
      std::is_same<decimal64, T>::value, int64_t,
      T
    >
  >;
// clang-format on

// USAGE
//
// fixed_point_unary_cast<SourceT, TargetT>{scale}.operator()(element)
//
template <typename _SourceT, typename _TargetT>
struct fixed_point_unary_cast {
  scale_type scale;
  using FixedPointT = std::conditional_t<is_fixed_point<_SourceT>(), _SourceT, _TargetT>;
  using DeviceT     = storage_type_t<FixedPointT>;

  // from fixed_point to numeric
  template <typename SourceT                                          = _SourceT,
            typename TargetT                                          = _TargetT,
            typename std::enable_if_t<(is_fixed_point<_SourceT>() &&
                                       is_numeric<TargetT>())>* = nullptr>
  TargetT operator()(DeviceT const element)
  {
    auto const fp = SourceT{scaled_integer<DeviceT>{element, scale}};
    return static_cast<TargetT>(fp);
  }

  // from numeric to fixed_point
  template <typename SourceT                                              = _SourceT,
            typename TargetT                                              = _TargetT,
            typename std::enable_if_t<(is_numeric<_SourceT>() &&
                                       is_fixed_point<TargetT>())>* = nullptr>
  DeviceT operator()(SourceT const element)
  {
    return TargetT{element, scale}.value();
  }
};

/*
 * Ceiling is calculated using integer division. When we divide by `n`, we get the integer part of
 * the `fixed_point` number. For a negative number, this is all that is needed since the ceiling
 * operation is defined as the least integer greater than the value. For a positive number, we may
 * need to round up if the `fixed_point` number has a fractional part. This is handled by comparing
 * the truncated value to the original value and if they are not equal, the result needs to be
 * incremented by `n`.
 */
template <typename T>
struct fixed_point_ceil {
  T n;  // 10^-scale (value required to determine integer part of fixed_point number)
  T operator()(T data)
  {
    T const a = (data / n) * n;                  // result of integer division
    return a + (data > 0 && a != data ? n : 0);  // add 1 if positive and not round number
  }
};

template <typename T, typename Rep, Radix Rad>
storage_type_t<T> ceil(const FixedPointNumber<Rep, Rad>& input) {
  using Type = storage_type_t<T>;
  Type const n  = std::pow(10, -input.scale());
  fixed_point_ceil<Type> t{n};
  Type result = t.operator()(static_cast<Type>(input));
  return result;
}

/*
 * Floor is calculated using integer division. When we divide by `n`, we get the integer part of
 * the `fixed_point` number. For a positive number, this is all that is needed since the floor
 * operation is defined as the greatest integer less than the value. For a negative number, we may
 * need to round down if the `fixed_point` number has a fractional part. This is handled by
 * comparing the truncated value to the original value and if they are not equal, the result needs
 * to be decremented by `n`.
 */
template <typename T>
struct fixed_point_floor {
  T n;  // 10^-scale (value required to determine integer part of fixed_point number)
  T operator()(T data)
  {
    T const a = (data / n) * n;                  // result of integer division
    return a - (data < 0 && a != data ? n : 0);  // subtract 1 if negative and not round number
  }
};

template <typename T, typename Rep, Radix Rad>
storage_type_t<T> floor(const FixedPointNumber<Rep, Rad>& input) {
  using Type = storage_type_t<T>;
  Type const n  = std::pow(10, -input.scale());
  fixed_point_floor<Type> t{n};
  Type result = t.operator()(static_cast<Type>(input));
  return result;
}

template <typename T>
struct fixed_point_abs {
  T n;
  T operator()(T data) { return std::abs(data); }
};

template <typename T, typename Rep, Radix Rad>
storage_type_t<T> abs(const FixedPointNumber<Rep, Rad>& input) {
  using Type = storage_type_t<T>;
  Type const n  = std::pow(10, -input.scale());
  fixed_point_abs<Type> t{n};
  Type result = t.operator()(static_cast<Type>(input));
  return result;
}

} // namespace basic
