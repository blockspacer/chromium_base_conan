#include "basic/strings/substitute.h" // IWYU pragma: associated

#include "base/logging.h"
#include "base/macros.h"
#include "base/strings/utf_string_conversions.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_util.h"
#include "base/strings/stringprintf.h"
#include "basic/rvalue_cast.h"
#include "base/location.h"

#include <vector>
#include <iterator>

using namespace base;

namespace {

template <typename T> struct ForwardIterable;

template <typename T> struct ForwardIterable<T&&>
{
  ForwardIterable(T&& t) : t(t) {}
  auto begin() && { return std::make_move_iterator(std::begin(t)); }
  auto end() && { return std::make_move_iterator(std::end(t)); }

  T& t;
};

template <typename T> struct ForwardIterable<T&>
{
  ForwardIterable(T& t) : t(t) {}
  auto begin() { return std::begin(t); }
  auto end() { return std::end(t); }
  auto begin() const { return std::begin(t); }
  auto end() const { return std::end(t); }

  T& t;
};

template <typename T>
ForwardIterable<T&&> makeForwardIterable(T&& t)
{
  return {std::forward<T>(t)};
}

} // namespace

namespace basic {

using internal::SubstituteArg;

SubstituteArg::SubstituteArg(const char* value)
  : text_(value ? value : "NULL") {}

SubstituteArg::SubstituteArg(const std::string& value)
  : text_(value) {}

SubstituteArg::SubstituteArg(std::string&& value)
  : text_(RVALUE_CAST(value)) {}

SubstituteArg::SubstituteArg(const base::string16& value)
  : text_(base::UTF16ToASCII(value)) {}

SubstituteArg::SubstituteArg(const StringPiece& value)
  : text_(value.data()) {}

SubstituteArg::SubstituteArg(const StringPiece16& value)
  : text_(base::UTF16ToASCII(value.data())) {}

SubstituteArg::SubstituteArg(const Location& value)
  : text_(value.ToString()) {}

SubstituteArg::SubstituteArg(char value)
  : text_(std::string(1, value)) {}

SubstituteArg::SubstituteArg(int value)
  : text_(NumberToString(value)) {}

SubstituteArg::SubstituteArg(unsigned int value)
  : text_(NumberToString(value)) {}

SubstituteArg::SubstituteArg(long value)
  : text_(NumberToString(value)) {}

SubstituteArg::SubstituteArg(unsigned long value)
  : text_(NumberToString(value)) {}

SubstituteArg::SubstituteArg(long long value)
  : text_(NumberToString(value)) {}

SubstituteArg::SubstituteArg(unsigned long long value)
  : text_(NumberToString(value)) {}

SubstituteArg::SubstituteArg(double value)
  : text_(NumberToString(value)) {}

SubstituteArg::SubstituteArg(const void* bytes, size_t size)
  : text_(bytes ? HexEncode(bytes, size) : "NULL") {}

SubstituteArg::SubstituteArg(const void* bytes)
  : text_(bytes ?
            static_cast<std::ostringstream&&>(
              std::ostringstream() << bytes
            ).str()
          : "NULL") {}

SubstituteArg::SubstituteArg(bool value)
  : text_(value ? "true" : "false") {}

using internal::SubstituteArg16;

SubstituteArg16::SubstituteArg16(const char* value)
  : text_(base::ASCIIToUTF16(value ? value : "NULL")) {}

SubstituteArg16::SubstituteArg16(const std::string& value)
  : text_(base::ASCIIToUTF16(value)) {}

SubstituteArg16::SubstituteArg16(const base::string16& value)
  : text_(value) {}

SubstituteArg16::SubstituteArg16(base::string16&& value)
  : text_(RVALUE_CAST(value)) {}

SubstituteArg16::SubstituteArg16(const StringPiece& value)
  : text_(base::ASCIIToUTF16(value.data())) {}

SubstituteArg16::SubstituteArg16(const StringPiece16& value)
  : text_(value.data()) {}

SubstituteArg16::SubstituteArg16(const Location& value)
  : text_(base::ASCIIToUTF16(value.ToString())) {}

SubstituteArg16::SubstituteArg16(char value)
  : text_(base::ASCIIToUTF16(std::string(1, value))) {}

SubstituteArg16::SubstituteArg16(int value)
  : text_(base::ASCIIToUTF16(NumberToString(value))) {}

SubstituteArg16::SubstituteArg16(unsigned int value)
  : text_(base::ASCIIToUTF16(NumberToString(value))) {}

SubstituteArg16::SubstituteArg16(long value)
  : text_(base::ASCIIToUTF16(NumberToString(value))) {}

SubstituteArg16::SubstituteArg16(unsigned long value)
  : text_(base::ASCIIToUTF16(NumberToString(value))) {}

SubstituteArg16::SubstituteArg16(long long value)
  : text_(base::ASCIIToUTF16(NumberToString(value))) {}

SubstituteArg16::SubstituteArg16(unsigned long long value)
  : text_(base::ASCIIToUTF16(NumberToString(value))) {}

SubstituteArg16::SubstituteArg16(double value)
  : text_(base::ASCIIToUTF16(NumberToString(value))) {}

SubstituteArg16::SubstituteArg16(const void* bytes, size_t size)
  : text_(bytes ? base::ASCIIToUTF16(HexEncode(bytes, size)) : base::ASCIIToUTF16("NULL")) {}

SubstituteArg16::SubstituteArg16(const void* bytes)
  : text_(bytes ? base::ASCIIToUTF16(
                    static_cast<std::ostringstream&&>(
                      std::ostringstream() << bytes
                    ).str())
                : base::ASCIIToUTF16("NULL")) {}

SubstituteArg16::SubstituteArg16(bool value)
  : text_(base::ASCIIToUTF16(value ? "true" : "false")) {}

#define EMPLACE_RVALUE_TO(vec_name, arg_name) \
  if(arg_name != base::nullopt)  \
  { \
    vec_name.emplace_back( \
      RVALUE_CAST( \
        RVALUE_CAST(arg_name.value()) \
          .value()) \
    ); \
  }

template<class FormatStringType, class OutStringType, class ArgType>
void SubstituteAndAppendInternal(
  OutStringType* output,
  const FormatStringType& format,
  base::Optional<ArgType>&& arg0,
  base::Optional<ArgType>&& arg1,
  base::Optional<ArgType>&& arg2,
  base::Optional<ArgType>&& arg3,
  base::Optional<ArgType>&& arg4,
  base::Optional<ArgType>&& arg5,
  base::Optional<ArgType>&& arg6,
  base::Optional<ArgType>&& arg7,
  base::Optional<ArgType>&& arg8,
  base::Optional<ArgType>&& arg9)
{
  std::vector<OutStringType> subst;

  EMPLACE_RVALUE_TO(subst, arg0);
  EMPLACE_RVALUE_TO(subst, arg1);
  EMPLACE_RVALUE_TO(subst, arg2);
  EMPLACE_RVALUE_TO(subst, arg3);
  EMPLACE_RVALUE_TO(subst, arg4);
  EMPLACE_RVALUE_TO(subst, arg5);
  EMPLACE_RVALUE_TO(subst, arg6);
  EMPLACE_RVALUE_TO(subst, arg7);
  EMPLACE_RVALUE_TO(subst, arg8);
  EMPLACE_RVALUE_TO(subst, arg9);

  *output +=
    ReplaceStringPlaceholders(
      format,
      subst,
      nullptr);
}

void SubstituteAndAppend(
  base::string16* output,
  const string16& format,
  internal::OptArg16&& arg0,
  internal::OptArg16&& arg1,
  internal::OptArg16&& arg2,
  internal::OptArg16&& arg3,
  internal::OptArg16&& arg4,
  internal::OptArg16&& arg5,
  internal::OptArg16&& arg6,
  internal::OptArg16&& arg7,
  internal::OptArg16&& arg8,
  internal::OptArg16&& arg9)
{
  SubstituteAndAppendInternal(output, format,
                              RVALUE_CAST(arg0),
                              RVALUE_CAST(arg1),
                              RVALUE_CAST(arg2),
                              RVALUE_CAST(arg3),
                              RVALUE_CAST(arg4),
                              RVALUE_CAST(arg5),
                              RVALUE_CAST(arg6),
                              RVALUE_CAST(arg7),
                              RVALUE_CAST(arg8),
                              RVALUE_CAST(arg9));
}

base::string16 Substitute(
  const string16& format,
  internal::OptArg16&& arg0,
  internal::OptArg16&& arg1,
  internal::OptArg16&& arg2,
  internal::OptArg16&& arg3,
  internal::OptArg16&& arg4,
  internal::OptArg16&& arg5,
  internal::OptArg16&& arg6,
  internal::OptArg16&& arg7,
  internal::OptArg16&& arg8,
  internal::OptArg16&& arg9)
{
  base::string16 result;
  SubstituteAndAppend(&result, format,
                      RVALUE_CAST(arg0),
                      RVALUE_CAST(arg1),
                      RVALUE_CAST(arg2),
                      RVALUE_CAST(arg3),
                      RVALUE_CAST(arg4),
                      RVALUE_CAST(arg5),
                      RVALUE_CAST(arg6),
                      RVALUE_CAST(arg7),
                      RVALUE_CAST(arg8),
                      RVALUE_CAST(arg9));
  return result;
}

void SubstituteAndAppend(
  std::string* output,
  StringPiece format,
  internal::OptArg&& arg0,
  internal::OptArg&& arg1,
  internal::OptArg&& arg2,
  internal::OptArg&& arg3,
  internal::OptArg&& arg4,
  internal::OptArg&& arg5,
  internal::OptArg&& arg6,
  internal::OptArg&& arg7,
  internal::OptArg&& arg8,
  internal::OptArg&& arg9)
{
  return SubstituteAndAppendInternal(output,
                    format,
                    RVALUE_CAST(arg0),
                    RVALUE_CAST(arg1),
                    RVALUE_CAST(arg2),
                    RVALUE_CAST(arg3),
                    RVALUE_CAST(arg4),
                    RVALUE_CAST(arg5),
                    RVALUE_CAST(arg6),
                    RVALUE_CAST(arg7),
                    RVALUE_CAST(arg8),
                    RVALUE_CAST(arg9));
}

std::string Substitute(
  StringPiece format,
  internal::OptArg&& arg0,
  internal::OptArg&& arg1,
  internal::OptArg&& arg2,
  internal::OptArg&& arg3,
  internal::OptArg&& arg4,
  internal::OptArg&& arg5,
  internal::OptArg&& arg6,
  internal::OptArg&& arg7,
  internal::OptArg&& arg8,
  internal::OptArg&& arg9)
{
  std::string result;
  SubstituteAndAppend(&result, format,
                      RVALUE_CAST(arg0),
                      RVALUE_CAST(arg1),
                      RVALUE_CAST(arg2),
                      RVALUE_CAST(arg3),
                      RVALUE_CAST(arg4),
                      RVALUE_CAST(arg5),
                      RVALUE_CAST(arg6),
                      RVALUE_CAST(arg7),
                      RVALUE_CAST(arg8),
                      RVALUE_CAST(arg9));
  return result;
}

}  // namespace base

