// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/output_parameter.h"

#include <stddef.h>

#include <algorithm>
#include <utility>
#include <iostream>
#include <sstream>
#include <string>

#include "base/format_macros.h"
#include "base/memory/read_only_shared_memory_region.h"
#include "base/metrics/field_trial.h"
#include "base/metrics/persistent_memory_allocator.h"
#include "base/stl_util.h"
#include "base/strings/string_piece.h"
#include "base/strings/string_util.h"
#include "base/strings/stringprintf.h"
#include GTEST_HEADER_INCLUDE

namespace base {

namespace {

// task: read strings from stream until EOF
// concatenate all strings
// return whether any strings read

// using a reference as output parameter - BAD:
// * not obvious from the caller that the string will be modified  (in the general case)
// * requires default constructor
// * implicit precondition that the output is empty
bool read_str_naive(std::istream& in, std::string& out)
{
  for (std::string tmp; in >> tmp;)
    out += tmp;
  return !out.empty();
}

// does not have these problems
bool read_str_better(std::istream& in, base::output_parameter<std::string> out)
{
  std::string result; // no way to access the string directly
  // so need to create new one

  for (std::string tmp; in >> tmp;)
      result += tmp;

  // granted, that's verbose
  auto empty = result.empty();    // we need to query here, because after move it might be empty
  out        = std::move(result); // set output parameter
  return !empty;

  // so use this one:
  // assignment op returns the value that was assigned
  return (out = std::move(result)).empty();
}

}  // namespace

TEST(OutputParameterTest, Simple) {
  {
    std::istringstream in("hello world");
    std::string        str;
    bool               res = read_str_naive(in, str);
    EXPECT_TRUE(res);
    EXPECT_EQ(str, "helloworld");
  }

  {
    std::istringstream in("hello world");
    std::string        str;
    // use base::out() to create an output_parameter easily
    bool res = read_str_better(in, base::out(str));
    EXPECT_TRUE(res);
    EXPECT_EQ(str, "helloworld");
  }

  // what if std::string had no default constructor?
  {
    // use this one:
    // base::deferred_construction<T> - create an object without initializing it yet
    base::deferred_construction<std::string> str;
    // str is not initialized yet,
    // so it does not require a constructor
    // once you give it a value, it will never be empty again

    std::istringstream in("hello world");
    bool               res = read_str_better(in, base::out(str));
    // if the function assigned a value to the output parameter,
    // it will call the constructor and directly initializes it with the correct value
    EXPECT_TRUE(res);
    EXPECT_TRUE(str.has_value());
    EXPECT_EQ(str.value(), "helloworld");
  }
}

}  // namespace base
