// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "tests_common.hpp"

#include "base/ranges/pipelined.h"

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
    | base::pipelined(add, 5)
    | base::pipelined(square)
    | base::pipelined(add, 6);
}

} // namespace

namespace base {

TEST(PipelinedTest, Pipelined)
{
  EXPECT_EQ(42, after());

  EXPECT_EQ(1, (-1 | base::pipelined(square)));

  int i = -1;
  EXPECT_EQ(4, (--i | base::pipelined(square)));
}

}  // namespace base
