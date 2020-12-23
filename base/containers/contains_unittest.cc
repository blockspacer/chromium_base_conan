// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "tests_common.hpp"

#include "base/containers/contains.h"

#include <set>
#include <string>

#include "base/containers/flat_set.h"
#include "base/functional/identity.h"
#include "base/strings/string_piece.h"
#include "base/strings/string_util.h"

namespace base {

TEST(ContainsTest, GenericContains) {
  constexpr char allowed_chars[] = {'a', 'b', 'c', 'd'};

  static_assert(Contains(allowed_chars, 'a'), "");
  static_assert(!Contains(allowed_chars, 'z'), "");
  static_assert(!Contains(allowed_chars, 0), "");

  constexpr char allowed_chars_including_nul[] = "abcd";
  static_assert(Contains(allowed_chars_including_nul, 0), "");
}

// ASCII-specific tolower.  The standard library's tolower is locale sensitive,
// so we don't want to use it here.
template <typename CharT,
          typename = std::enable_if_t<std::is_integral<CharT>::value>>
CharT lowerASCII(CharT c) {
  return (c >= 'A' && c <= 'Z') ? (c + ('a' - 'A')) : c;
}

TEST(ContainsTest, GenericContainsWithProjection) {
  const char allowed_chars[] = {'A', 'B', 'C', 'D'};

  EXPECT_TRUE(Contains(allowed_chars, 'a', &lowerASCII<char>));
  EXPECT_FALSE(Contains(allowed_chars, 'z', &lowerASCII<char>));
  EXPECT_FALSE(Contains(allowed_chars, 0, &lowerASCII<char>));
}

TEST(ContainsTest, GenericSetContainsWithProjection) {
  constexpr StringPiece kFoo = "foo";
  std::set<std::string> set = {"foo", "bar", "baz"};

  // Opt into a linear search by explicitly providing a projection:
  EXPECT_TRUE(Contains(set, kFoo, identity{}));
}

TEST(ContainsTest, ContainsWithFindAndNpos) {
  std::string str = "abcd";

  EXPECT_TRUE(Contains(str, 'a'));
  EXPECT_FALSE(Contains(str, 'z'));
  EXPECT_FALSE(Contains(str, 0));
}

TEST(ContainsTest, ContainsWithFindAndEnd) {
  std::set<int> set = {1, 2, 3, 4};

  EXPECT_TRUE(Contains(set, 1));
  EXPECT_FALSE(Contains(set, 5));
  EXPECT_FALSE(Contains(set, 0));
}

TEST(ContainsTest, ContainsWithContains) {
  flat_set<int> set = {1, 2, 3, 4};

  EXPECT_TRUE(Contains(set, 1));
  EXPECT_FALSE(Contains(set, 5));
  EXPECT_FALSE(Contains(set, 0));
}

}  // namespace base
