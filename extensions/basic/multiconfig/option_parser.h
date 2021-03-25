#pragma once

#include "basic/status/status_macros.h"
#include "basic/concept/dependent_false.h"

#include <base/logging.h>
#include <base/base_export.h>
#include <base/macros.h>
#include <basic/rvalue_cast.h>

#include <string>

// Parses `std::string` and returns parsing error or desired type.
//
// USAGE
//
// CONSUME_OR_RETURN(int value, parseOptionAs<int>("1234"));
//
namespace basic {

template<typename Type>
basic::StatusOr<Type> parseOptionAs(
  const std::string& str) NO_EXCEPTION
{
  static_assert(dependent_false<Type>::value
    , "parser does not support provided type of option.");
}

template<>
basic::StatusOr<std::string> parseOptionAs<std::string>(
  const std::string& str) NO_EXCEPTION;

/// \note Strings "TrUe", "True", "true" and "1" will result in `true` value.
template<>
basic::StatusOr<bool> parseOptionAs<bool>(
  const std::string& str) NO_EXCEPTION;

template<>
basic::StatusOr<int64_t> parseOptionAs<int64_t>(
  const std::string& str) NO_EXCEPTION;

template<>
basic::StatusOr<int32_t> parseOptionAs<int32_t>(
  const std::string& str) NO_EXCEPTION;

template<>
basic::StatusOr<uint32_t> parseOptionAs<uint32_t>(
  const std::string& str) NO_EXCEPTION;

template<>
basic::StatusOr<uint64_t> parseOptionAs<uint64_t>(
  const std::string& str) NO_EXCEPTION;

template<>
basic::StatusOr<double> parseOptionAs<double>(
  const std::string& str) NO_EXCEPTION;

template<>
basic::StatusOr<float> parseOptionAs<float>(
  const std::string& str) NO_EXCEPTION;

} // namespace basic
