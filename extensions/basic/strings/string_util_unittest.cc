// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/strings/string_util.h"

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
#include "base/strings/string_util.h"

#include "testing/gtest/include/gtest/gtest.h"

using namespace base;

namespace basic {

TEST(StringUtil, EscapeAtEnd) {
  std::string stripped = StripAnsiEscapeCodes("foo\33");
  EXPECT_EQ("foo", stripped);

  stripped = StripAnsiEscapeCodes("foo\33[");
  EXPECT_EQ("foo", stripped);
}

TEST(StringUtil, StripColors) {
  // An actual clang warning.
  std::string input = "\33[1maffixmgr.cxx:286:15: \33[0m\33[0;1;35mwarning: "
                 "\33[0m\33[1musing the result... [-Wparentheses]\33[0m";
  std::string stripped = StripAnsiEscapeCodes(input);
  EXPECT_EQ("affixmgr.cxx:286:15: warning: using the result... [-Wparentheses]",
            stripped);
}

TEST(StringUtil, IsNullTerminatedStd) {
  std::string input = "SOME_STR";
  ASSERT_FALSE(isNullTerminated(input));
  input.push_back('\0');
  ASSERT_TRUE(isNullTerminated(input));
}

TEST(StringUtil, IsNullTerminatedStrStd) {
  std::string input = "SOME_STR";
  ASSERT_FALSE(IsNullTerminatedStr(input.size(), input.c_str()));
  input.push_back('\0');
  ASSERT_TRUE(IsNullTerminatedStr(input.size(), input.c_str()));
}

TEST(StringUtil, IsNullTerminated) {
  ASSERT_TRUE(IsNullTerminated("SOME_STR"));
}

}  // namespace basic
