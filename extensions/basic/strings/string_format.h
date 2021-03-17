#pragma once

#include <fmt/args.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/locale.h>

#include <base/strings/utf_string_conversions.h>
#include <base/strings/string_util.h>

#include <string_view>

namespace basic {

/*
 * Format string with the help of {fmt} library (http://fmtlib.net)
 *
 * Thread-safe.
 *
 * \param pattern - Format string pattern
 * \param args - Format arguments
 * \return Formatted string
*/
template <typename... Args>
std::string fmt(base::StringPiece pattern, Args&&... args)
{
  return fmt::format(std::string_view{pattern.data(), pattern.size()}, std::forward<Args>(args)...);
}

/*
 * Format wide string with the help of {fmt} library (http://fmtlib.net)
 *
 * Thread-safe.
 *
 * \param pattern - Format wide string pattern
 * \param args - Format arguments
 * \return Formatted wide string
*/
template <typename... Args>
std::u16string fmt(base::StringPiece16 pattern, Args&&... args) {
  return fmt::format(std::u16string_view{pattern.data(), pattern.size()}, std::forward<Args>(args)...);
}

/*
 * Format wide string with the help of {fmt} library (http://fmtlib.net)
 *
 * Thread-safe.
 *
 * \param pattern - Format wide string pattern
 * \param args - Format arguments
 * \return Formatted wide string
*/
template <typename... Args>
std::wstring fmt(base::WStringPiece pattern, Args&&... args)
{
  return fmt::format(std::wstring_view{pattern.data(), pattern.size()}, std::forward<Args>(args)...);
}

} // namespace basic
