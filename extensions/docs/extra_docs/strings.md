## About

Some usage examples.

See for details:

* https://www.chromium.org/developers/chromium-string-usage

## FAQ

* How to print pointers?

```cpp
#include <base/format_macros.h>

std::string GetDumpNameForDB(const leveldb::DB* db) {
  return base::StringPrintf("leveldatabase/db_0x%" PRIXPTR,
                            reinterpret_cast<uintptr_t>(db));
}
```

* How to use UTF strings?

Don't use std::wstring.

Use base::string16 or base::FilePath instead. (Windows-specific code interfacing with system APIs using wstring and wchar_t can still use string16 and char16; it is safe to assume that these are equivalent to the "wide" types.)

See `base/strings/utf_string_conversions.h`

* How to pass strings similar to `std::string_view`?

`StringPiece` makes it easy and efficient to write functions that take both C++ and C style strings.

Usually you want to use `base::StringPiece` as parameter and return `std::string`:

```cpp
std::string JoinPrefs(base::StringPiece parent, base::StringPiece child) {
  return base::JoinString({parent, child}, ".");
}

std::string GetNativeLibraryName(StringPiece name) {
  DCHECK(IsStringASCII(name));
  return "lib" + name.as_string() + ".so";
}
```

But it may be fine to return `base::StringPiece` (take care of object lifetime!) in internal API (note anonymous namespace below):

```cpp
namespace {
base::StringPiece GetModule(const base::StringPiece& file) {
  base::StringPiece module(file);
  base::StringPiece::size_type last_slash_pos =
      module.find_last_of("\\/");
  if (last_slash_pos != base::StringPiece::npos)
    module.remove_prefix(last_slash_pos + 1);
  base::StringPiece::size_type extension_start = module.rfind('.');
  module = module.substr(0, extension_start);
  static const char kInlSuffix[] = "-inl";
  static const int kInlSuffixLen = base::size(kInlSuffix) - 1;
  if (module.ends_with(kInlSuffix))
    module.remove_suffix(kInlSuffixLen);
  return module;
}
} // namespace
```

See for details https://abseil.io/tips/1

* String-number conversions

```cpp
#include <base/strings/string_number_conversions.h>

std::string string_value = base::NumberToString(value);

base::string16 string16_value = base::NumberToString16(out_int);

base::string16 utf16_input = base::UTF8ToUTF16(string_value);
int64_t output64 = 0;
base::StringToInt64(utf16_input, &output64)

const char input[] = "6";
std::string input_string(input, base::size(input));
int output;
base::StringToInt(input_string, &output)
```

* Pattern matching

```cpp
#include <base/strings/pattern.h>

base::MatchPattern("www.google.com", "*.com")
```

* Concatenation on a sequence of strings

Use `base::StrCat` if you don't need a separator. Use `base::JoinString` if you need a separator.


```cpp
// StrCat is a function to perform concatenation on a sequence of strings.
// It is preferrable to a sequence of "a + b + c" because it is both faster and
// generates less code.

base::StrCat({"1", "22", "333", "4444", "55555"})

base::StrCat({base::ASCIIToUTF16("arg1"), base::ASCIIToUTF16("arg2"), base::ASCIIToUTF16("arg3")})
```

```cpp
// Appends a sequence of strings to a destination. Prefer:
//   StrAppend(&foo, ...);
// over:
//   foo += StrCat(...);
// because it avoids a temporary string allocation and copy.

std::string result = "foo";
base::StrAppend(&result, {"1", "22", "333"});


string16 result = base::ASCIIToUTF16("foo");
base::StrAppend(&result, {string16("333")});
```

See `base/strings/strcat.h`


* String split

See `base/strings/string_split.h`

* How to support plural forms (i18n)?

See `base/i18n/message_formatter_unittest.cc`

```cpp
#include <base/i18n/rtl.h>
#include <base/i18n/icu_util.h>
#include <base/i18n/message_formatter.h>
#include <base/strings/string_piece.h>
#include <base/strings/string_util.h>
#include <base/strings/utf_string_conversions.h>

#include <third_party/icu/source/common/unicode/unistr.h>
#include <third_party/icu/source/i18n/unicode/datefmt.h>
#include <third_party/icu/source/i18n/unicode/msgfmt.h>
#include <third_party/icu/source/common/unicode/uloc.h>

#if UCONFIG_NO_FORMATTING
#error "UCONFIG_NO_FORMATTING"
#endif // UCONFIG_NO_FORMATTING

TEST(MessageFormatterTest, PluralNumberedArgs) {
  const base::string16 pattern = base::ASCIIToUTF16(
      "{1, plural, "
      "=1 {The cert for {0} expired yesterday.}"
      "=7 {The cert for {0} expired a week ago.}"
      "other {The cert for {0} expired # days ago.}}");
  std::string result
    = base::UTF16ToASCII(
        base::i18n::MessageFormatter::FormatWithNumberedArgs(
      pattern, "example.com", 1));
  EXPECT_EQ("The cert for example.com expired yesterday.", result);
  result = base::UTF16ToASCII(
    base::i18n::MessageFormatter::FormatWithNumberedArgs(
      pattern, "example.com", 7));
  EXPECT_EQ("The cert for example.com expired a week ago.", result);
  result = base::UTF16ToASCII(
    base::i18n::MessageFormatter::FormatWithNumberedArgs(
      pattern, "example.com", 15));
  EXPECT_EQ("The cert for example.com expired 15 days ago.", result);
}
```

## Examples

```cpp
base::string16 template_icu_escaped;
base::ReplaceChars(template_icu, base::ASCIIToUTF16("$"),
                   base::ASCIIToUTF16("$$"), &template_icu_escaped);

base::string16 template_dollars =
    base::i18n::MessageFormatter::FormatWithNumberedArgs(
        template_icu_escaped, "$1", "$2", "$3", "$4", "$5", "$6", "$7");

// Replace "$1", "$2", ... with the display text of each parameter.
*out_message = base::ReplaceStringPlaceholders(template_dollars,
                                               display_texts, out_offsets);
```
