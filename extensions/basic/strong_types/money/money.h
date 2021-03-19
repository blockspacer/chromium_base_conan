#pragma once

#include <string>
#include <cstdint>

#include <base/macros.h>

#include <basic/rvalue_cast.h>
#include <basic/macros.h>

namespace basic {

// Represents an amount of money with its currency type.
//
// EXAMPLE
//
// {currency_code = "USD", units = 0, nanos = 750,000,000} is $0.75
// {currency_code = "USD", units = -2, nanos = -750,000,000} is $-2.75
//
// MOTIVATION
//
// `Money` does not use floating point numbers, do not use floats for currency!
// The float and double types are particularly ill-suited
// for monetary calculations because it is impossible to represent 0.1
// (or any other negative power of ten) as a float or double exactly.
//
// TIPS AND TRICKS
//
// Some suggestions to avoid floats for currency include:
//
// 1. Generally when dealing with money, use specialized data stores.
//    MySQL for example has the DECIMAL field type.
// 2. When serializing currency values, in for example JSON,
//    pass them around as a string, not a number.
// So instead of $5.00, you would simply multiply by 100
// (or other multiplier) and use 500, which fits in an integer.
//
// See:
// * evertpot.com/currencies-floats/
// * randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
//
class Money
{
 public:
  using CurrencyCodeType = std::string;
  using UnitsType = int64_t;
  using NanosType = int32_t;

  // The 3-letter currency code defined in ISO 4217.
  MUST_USE_RETURN_VALUE
  const std::string& currency_code() const NO_EXCEPTION
  {
    return currency_code_;
  }

  MUST_USE_RETURN_VALUE
  int64_t units() const NO_EXCEPTION
  {
    return units_;
  }

  MUST_USE_RETURN_VALUE
  int32_t nanos() const NO_EXCEPTION
  {
    return nanos_;
  }

  void clear_currency_code() NO_EXCEPTION
  {
    currency_code_ = "";
  }

  void clear_units() NO_EXCEPTION
  {
    units_ = 0;
  }

  void clear_nanos() NO_EXCEPTION
  {
    nanos_ = 0;
  }

  // The 3-letter currency code defined in ISO 4217.
  void set_currency_code(std::string&& in_currency_code) NO_EXCEPTION
  {
    currency_code_ = RVALUE_CAST(in_currency_code);
  }

  // The 3-letter currency code defined in ISO 4217.
  void set_currency_code(const std::string& in_currency_code) NO_EXCEPTION
  {
    currency_code_ = in_currency_code;
  }

  void set_units(uint64_t in_units) NO_EXCEPTION
  {
    units_ = in_units;
  }

  void set_nanos(int32_t in_nanos) NO_EXCEPTION
  {
    nanos_ = in_nanos;
  }

private:
  // The three-letter currency code defined in ISO 4217.
  CurrencyCodeType currency_code_ = "USD";

  // The whole units of the amount.
  // For example if `currencyCode` is `"USD"`, then 1 unit is one US dollar.
  UnitsType units_ = 0;

  // Number of nano (10^-9) units of the amount.
  // The nanos must be between -999,999,999 and +999,999,999 inclusive.
  // If `units` is positive, `nanos` must be positive or zero.
  // If `units` is zero, `nanos` can be positive, zero, or negative.
  // If `units` is negative, `nanos` must be negative or zero.
  // For example $-1.75 is represented as `units`=-1 and `nanos`=-750,000,000.
  NanosType nanos_ = 0;
};

} // namespace basic
