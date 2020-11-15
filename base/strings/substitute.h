#pragma once

#include "base/macros.h"
#include "base/base_export.h"
#include "base/optional.h"
#include "base/strings/string16.h"
#include "base/strings/string_piece.h"
#include "build/build_config.h"

#include <string>
#include <variant>

namespace base {

/// \note Argument format starts from $1
/// i.e. $0 is invalid.
//
// base::Substitute()
// base::SubstituteAndAppend()
//   Kind of like StringPrintf, but different.
//
//   Differences from StringPrintf:
//   * The format string does not identify the types of arguments.
//     Instead, the magic of C++ deals with this for us.  See below
//     for a list of accepted types.
//   * Substitutions in the format string are identified by a '$'
//     followed by a digit.  So, you can use arguments out-of-order and
//     use the same argument multiple times.
//   * '$$' in the format string means output a literal '$' character.
//   * It is faster than StringPrintf.
//     TODO: measure performance
//
//   SubstituteAndAppend() is like Substitute() but appends the result to
//   *output.  Example:
//
//     std::string str;
//     base::SubstituteAndAppend(&str,
//                                  "My name is $1 $2 and I am $3 years old.",
//                                  first_name, last_name, age);
//
// USAGE
//
//  #include <base/strings/substitute.h>
//  #include <base/strings/utf_string_conversions.h>
//
//  {
//    std::string first_name = "Alex";
//    base::string16 last_name = base::ASCIIToUTF16("Gordon");
//    int age = 25;
//    double delay = 1.3;
//    LOG(INFO) << base::Substitute(
//                   "My name is $1 $2 and I am $3 years old after $4."
//                   , first_name
//                   , last_name
//                   , age
//                   , delay);
//  }
//
//  {
//    std::string first_name = "Alex";
//    base::string16 last_name = base::ASCIIToUTF16("Gordon");
//    int age = 25;
//    double delay = 1.3;
//    LOG(INFO) << base::Substitute(
//                   base::ASCIIToUTF16("My name is $1 $2 and I am $3 years old after $4.")
//                   , first_name
//                   , last_name
//                   , age
//                   , delay);
//  }
//
namespace internal {

class SubstituteArg {
 public:
  SubstituteArg(SubstituteArg&& other)
    : text_(std::move(other.text_)) {}

  // Overload `const char*` because compiler casts it to bool.
  SubstituteArg(const char* value);

  // Overload `const string&` to avoid a temporary object.
  SubstituteArg(const std::string& value);

  SubstituteArg(std::string&& value);

  // Overload `const base::string16&` to avoid a temporary object.
  SubstituteArg(const base::string16& value);

  SubstituteArg(const StringPiece& value);

  SubstituteArg(const StringPiece16& value);

  SubstituteArg(int value);

  SubstituteArg(unsigned int value);

  SubstituteArg(long value);

  SubstituteArg(unsigned long value);

  SubstituteArg(long long value);

  SubstituteArg(unsigned long long value);

  SubstituteArg(double value);

  // Printed as "0x<lower case hex string>"
  SubstituteArg(const void* bytes, size_t size);

  // Printed as "true" or "false".
  SubstituteArg(bool value);

  constexpr std::string& str() & { return text_; }
  constexpr const std::string& str() const& { return text_; }
  constexpr std::string&& value() && { return std::move(text_); }
  constexpr const std::string&& value() const&& { return std::move(text_); }

 private:
  inline SubstituteArg() : text_() {}

  std::string text_;

  DISALLOW_COPY_AND_ASSIGN(SubstituteArg);
};

class SubstituteArg16 {
 public:
  SubstituteArg16(SubstituteArg16&& other)
    : text_(std::move(other.text_)) {}

  // Overload `const char*` because compiler casts it to bool.
  SubstituteArg16(const char* value);

  // Overload `const string&` to avoid a temporary object.
  SubstituteArg16(const std::string& value);

  // Overload `const base::string16&` to avoid a temporary object.
  SubstituteArg16(const base::string16& value);

  SubstituteArg16(base::string16&& value);

  SubstituteArg16(const StringPiece& value);

  SubstituteArg16(const StringPiece16& value);

  SubstituteArg16(int value);

  SubstituteArg16(unsigned int value);

  SubstituteArg16(long value);

  SubstituteArg16(unsigned long value);

  SubstituteArg16(long long value);

  SubstituteArg16(unsigned long long value);

  SubstituteArg16(double value);

  // Printed as "0x<lower case hex string>"
  SubstituteArg16(const void* bytes, size_t size);

  // Printed as "true" or "false".
  SubstituteArg16(bool value);

  constexpr base::string16& str() & { return text_; }
  constexpr const base::string16& str() const& { return text_; }
  constexpr base::string16&& value() && { return std::move(text_); }
  constexpr const base::string16&& value() const&& { return std::move(text_); }

 private:
  inline SubstituteArg16() : text_() {}

  base::string16 text_;

  DISALLOW_COPY_AND_ASSIGN(SubstituteArg16);
};

using OptArg = base::Optional<internal::SubstituteArg>;

using OptArg16 = base::Optional<internal::SubstituteArg16>;

}  // namespace internal

void SubstituteAndAppend(
  base::string16* output, const string16& format,
  internal::OptArg16&& arg0 = base::nullopt,
  internal::OptArg16&& arg1 = base::nullopt,
  internal::OptArg16&& arg2 = base::nullopt,
  internal::OptArg16&& arg3 = base::nullopt,
  internal::OptArg16&& arg4 = base::nullopt,
  internal::OptArg16&& arg5 = base::nullopt,
  internal::OptArg16&& arg6 = base::nullopt,
  internal::OptArg16&& arg7 = base::nullopt,
  internal::OptArg16&& arg8 = base::nullopt,
  internal::OptArg16&& arg9 = base::nullopt);

base::string16 Substitute(
  const string16& format,
  internal::OptArg16&& arg0 = base::nullopt,
  internal::OptArg16&& arg1 = base::nullopt,
  internal::OptArg16&& arg2 = base::nullopt,
  internal::OptArg16&& arg3 = base::nullopt,
  internal::OptArg16&& arg4 = base::nullopt,
  internal::OptArg16&& arg5 = base::nullopt,
  internal::OptArg16&& arg6 = base::nullopt,
  internal::OptArg16&& arg7 = base::nullopt,
  internal::OptArg16&& arg8 = base::nullopt,
  internal::OptArg16&& arg9 = base::nullopt);

void SubstituteAndAppend(
  std::string* output, StringPiece format,
  internal::OptArg&& arg0 = base::nullopt,
  internal::OptArg&& arg1 = base::nullopt,
  internal::OptArg&& arg2 = base::nullopt,
  internal::OptArg&& arg3 = base::nullopt,
  internal::OptArg&& arg4 = base::nullopt,
  internal::OptArg&& arg5 = base::nullopt,
  internal::OptArg&& arg6 = base::nullopt,
  internal::OptArg&& arg7 = base::nullopt,
  internal::OptArg&& arg8 = base::nullopt,
  internal::OptArg&& arg9 = base::nullopt);

std::string Substitute(
  StringPiece format,
  internal::OptArg&& arg0 = base::nullopt,
  internal::OptArg&& arg1 = base::nullopt,
  internal::OptArg&& arg2 = base::nullopt,
  internal::OptArg&& arg3 = base::nullopt,
  internal::OptArg&& arg4 = base::nullopt,
  internal::OptArg&& arg5 = base::nullopt,
  internal::OptArg&& arg6 = base::nullopt,
  internal::OptArg&& arg7 = base::nullopt,
  internal::OptArg&& arg8 = base::nullopt,
  internal::OptArg&& arg9 = base::nullopt);

} // namespace base

