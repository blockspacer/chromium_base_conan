// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/ranges/pipelined.h"

#include "testing/gtest/include/gtest/gtest.h"

#include <cstdio>
#include <cmath>

namespace {

int square(const int i) { return i * i; }
int add(const int x, const int y) { return x + y; }
int get_value() { return 1; }

// Simulates the proposed "operator |>"
int after()
{
  return get_value()
    | basic::pipelined(add, 5)
    | basic::pipelined(square)
    | basic::pipelined(add, 6);
}

} // namespace

namespace basic {

TEST(PipelinedTest, Pipelined)
{
  EXPECT_EQ(42, after());

  EXPECT_EQ(1, (-1 | basic::pipelined(square)));

  int i = -1;
  EXPECT_EQ(4, (--i | basic::pipelined(square)));
}

}  // namespace basic
