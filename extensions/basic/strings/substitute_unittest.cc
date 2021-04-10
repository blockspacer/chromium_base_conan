// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/strings/substitute.h"

#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <cmath>
#include <limits>

#include "base/bit_cast.h"
#include "base/format_macros.h"
#include "base/stl_util.h"
#include "base/strings/stringprintf.h"
#include "base/strings/utf_string_conversions.h"
#include "base/strings/strcat.h"
#include "base/strings/abseil_string_conversions.h"
#include "base/test/gtest_util.h"

#include "absl/strings/str_cat.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "testing/gmock/include/gmock/gmock.h"

using namespace base;

namespace basic {

#define EXPECT_MATCH_IGNORE_CASE(find_this, in_this, ex_start, ex_len)         \
  {                                                                            \
    size_t index = 0;                                                          \
    size_t length = 0;                                                         \
    EXPECT_TRUE(StringSearchIgnoringCaseAndAccents(find_this, in_this, &index, \
                                                   &length));                  \
    EXPECT_EQ(ex_start, index);                                                \
    EXPECT_EQ(ex_len, length);                                                 \
    index = 0;                                                                 \
    length = 0;                                                                \
    EXPECT_TRUE(                                                               \
        StringSearch(find_this, in_this, &index, &length, false, true));       \
    EXPECT_EQ(ex_start, index);                                                \
    EXPECT_EQ(ex_len, length);                                                 \
  }

TEST(SubstituteTest, Substitute) {
  // Basic.
  EXPECT_EQ("Hello, world!", basic::Substitute("$1, $2!", "Hello", "world"));

  // Non-char* types.
  /// \note float may expand i.e. "123 0.2 0.10000000149011612 foo true false x"

  std::string pattern = R"raw(123 0.2 0.1.* foo true false x)raw";
  EXPECT_THAT(basic::Substitute("$1 $2 $3 $4 $5 $6 $7", 123, 0.2, 0.1f,
                               std::string("foo"), true, false, 'x')
              , testing::MatchesRegex(pattern));

  // All int types.
  EXPECT_EQ(
      "-32767 65535 "
      "-1234567890 3234567890 "
      "-1234567890 3234567890 "
      "-1234567890123456789 9234567890123456789",
      basic::Substitute(
          "$1 $2 $3 $4 $5 $6 $7 $8",
          static_cast<short>(-32767),          // NOLINT(runtime/int)
          static_cast<unsigned short>(65535),  // NOLINT(runtime/int)
          -1234567890, 3234567890U, -1234567890L, 3234567890UL,
          -int64_t{1234567890123456789}, uint64_t{9234567890123456789u}));

  // Pointer.
  const int* int_p = reinterpret_cast<const int*>(0x12345);
  std::string str = basic::Substitute("$1", int_p);

  // Volatile Pointer.
  // Like C++ streamed I/O, such pointers implicitly become bool
  volatile int vol = 237;
  volatile int *volatile volptr = &vol;
  str = basic::Substitute("$1", volptr);
  EXPECT_EQ("true", str);

  // null is special. StrCat prints 0x0. Substitute prints NULL.
  const uint64_t* null_p = nullptr;
  str = basic::Substitute("$1", null_p);
  EXPECT_EQ("NULL", str);

  // char* is also special.
  const char* char_p = "print me";
  str = basic::Substitute("$1", char_p);
  EXPECT_EQ("print me", str);

  char char_buf[16];
  strncpy(char_buf, "print me too", sizeof(char_buf));
  str = basic::Substitute("$1", char_buf);
  EXPECT_EQ("print me too", str);

  // null char* is "doubly" special. Represented as the empty string.
  char_p = nullptr;
  str = basic::Substitute("$1", char_p);
  EXPECT_EQ("NULL", str);

  // Out-of-order.
  EXPECT_EQ("b, a, c, b", basic::Substitute("$2, $1, $3, $2", "a", "b", "c"));

  // Literal $
  EXPECT_EQ("$", basic::Substitute("$$"));

  EXPECT_EQ("$2", basic::Substitute("$$2"));

  // Test all overloads.
  EXPECT_EQ("a", basic::Substitute("$1", "a"));
  EXPECT_EQ("a b", basic::Substitute("$1 $2", "a", "b"));
  EXPECT_EQ("a b c", basic::Substitute("$1 $2 $3", "a", "b", "c"));
  EXPECT_EQ("a b c d", basic::Substitute("$1 $2 $3 $4", "a", "b", "c", "d"));
  EXPECT_EQ("a b c d e",
            basic::Substitute("$1 $2 $3 $4 $5", "a", "b", "c", "d", "e"));
  EXPECT_EQ("a b c d e f", basic::Substitute("$1 $2 $3 $4 $5 $6", "a", "b", "c",
                                            "d", "e", "f"));
  EXPECT_EQ("a b c d e f g", basic::Substitute("$1 $2 $3 $4 $5 $6 $7", "a", "b",
                                              "c", "d", "e", "f", "g"));
  EXPECT_EQ("a b c d e f g h",
            basic::Substitute("$1 $2 $3 $4 $5 $6 $7 $8", "a", "b", "c", "d", "e",
                             "f", "g", "h"));
  EXPECT_EQ("a b c d e f g h i",
            basic::Substitute("$1 $2 $3 $4 $5 $6 $7 $8 $9", "a", "b", "c", "d",
                             "e", "f", "g", "h", "i"));

  const char* null_cstring = nullptr;
  EXPECT_EQ("Text: 'NULL'", basic::Substitute("Text: '$1'", null_cstring));
}

TEST(SubstituteTest, SubstituteAndAppend) {
  std::string str = "Hello";
  basic::SubstituteAndAppend(&str, ", $1!", "world");
  EXPECT_EQ("Hello, world!", str);

  // Test all overloads.
  str.clear();
  basic::SubstituteAndAppend(&str, "$1", "a");
  EXPECT_EQ("a", str);
  str.clear();
  basic::SubstituteAndAppend(&str, "$1 $2", "a", "b");
  EXPECT_EQ("a b", str);
  str.clear();
  basic::SubstituteAndAppend(&str, "$1 $2 $3", "a", "b", "c");
  EXPECT_EQ("a b c", str);
  str.clear();
  basic::SubstituteAndAppend(&str, "$1 $2 $3 $4", "a", "b", "c", "d");
  EXPECT_EQ("a b c d", str);
  str.clear();
  basic::SubstituteAndAppend(&str, "$1 $2 $3 $4 $5", "a", "b", "c", "d", "e");
  EXPECT_EQ("a b c d e", str);
  str.clear();
  basic::SubstituteAndAppend(&str, "$1 $2 $3 $4 $5 $6", "a", "b", "c", "d", "e",
                            "f");
  EXPECT_EQ("a b c d e f", str);
  str.clear();
  basic::SubstituteAndAppend(&str, "$1 $2 $3 $4 $5 $6 $7", "a", "b", "c", "d",
                            "e", "f", "g");
  EXPECT_EQ("a b c d e f g", str);
  str.clear();
  basic::SubstituteAndAppend(&str, "$1 $2 $3 $4 $5 $6 $7 $8", "a", "b", "c", "d",
                            "e", "f", "g", "h");
  EXPECT_EQ("a b c d e f g h", str);
  str.clear();
  basic::SubstituteAndAppend(&str, "$1 $2 $3 $4 $5 $6 $7 $8 $9", "a", "b", "c",
                            "d", "e", "f", "g", "h", "i");
  EXPECT_EQ("a b c d e f g h i", str);
  str.clear();
}

TEST(SubstituteTest, VectorBoolRef) {
  std::vector<bool> v = {true, false};
  const auto& cv = v;
  std::set<std::string> strings1{"1 0 true false", "1 0 1 0"};
  std::string str1 = basic::Substitute("$1 $2 $3 $4", v[0], v[1], cv[0], cv[1]);
  EXPECT_THAT(strings1, ::testing::Contains(testing::Eq(str1)));

  std::string str2 = "Logic be like: ";
  std::set<std::string> strings2{"Logic be like: 1 0 true false", "Logic be like: 1 0 1 0"};
  basic::SubstituteAndAppend(&str2, "$1 $2 $3 $4", v[0], v[1], cv[0], cv[1]);
  EXPECT_THAT(strings2, ::testing::Contains(testing::Eq(str2)));
}

#ifdef GTEST_HAS_DEATH_TEST

TEST(SubstituteDeathTest, SubstituteDeath) {
  {
    std::string str;
    EXPECT_DCHECK_DEATH(
      basic::SubstituteAndAppend(&str, "$1 $2 $3 $4 $5 $6 $7 $8 $9 $10", "a", "b",
                                "c", "d", "e", "f", "g", "h", "i", "j"));
  }
#if TODO
  EXPECT_DCHECK_DEATH(
      static_cast<void>(basic::Substitute(base::StringPiece("-$3"), "a", "b")),
      "Invalid basic::Substitute\\(\\) format string: asked for \"\\$3\", "
      "but only 2 args were given.");

  EXPECT_DCHECK_DEATH(
      static_cast<void>(basic::Substitute(base::StringPiece("-$z-"))),
      "Invalid basic::Substitute\\(\\) format string: \"-\\$z-\"");

  EXPECT_DCHECK_DEATH(
      static_cast<void>(basic::Substitute(StringViewsToStringPieces(std::vector<absl::string_view>{absl::string_view("-$")})[0])),
      "Invalid basic::Substitute\\(\\) format string: \"-\\$\"");

  str.clear();
  basic::SubstituteAndAppend(&str, "$1 $2 $3 $4 $5 $6 $7 $8 $9 $10", "a", "b",
                            "c", "d", "e", "f", "g", "h", "i", "j");
  EXPECT_EQ("a b c d e f g h i j", str);

  EXPECT_EQ("a b c d e f g h i j",
            basic::Substitute("$1 $2 $3 $4 $5 $6 $7 $8 $9 $10", "a", "b", "c",
                             "d", "e", "f", "g", "h", "i", "j"));
  EXPECT_EQ("a b c d e f g h i j b0",
            basic::Substitute("$1 $2 $3 $4 $5 $6 $7 $8 $9 $10 $11", "a", "b", "c",
                             "d", "e", "f", "g", "h", "i", "j"));
#endif
}

#endif  // GTEST_HAS_DEATH_TEST

}  // namespace base
