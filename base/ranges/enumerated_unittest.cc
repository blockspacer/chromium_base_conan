// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "tests_common.hpp"

#include "base/ranges/enumerated.h"

namespace base {

TEST(EnumeratedTest, Enumerated)
{
  const std::vector<std::string> strings
  {
    "Hello", "World", "Yeah",
    "Things", "Strings", "Vector"
  };
  size_t idx = 0;
  for (const auto [index, str] : base::ranges::enumerated(strings))
  {
    std::cout << "index: " << index
        << " string: " << str << '\n';
    EXPECT_EQ(idx, index);
    EXPECT_EQ(strings[idx], str);
    idx++;
  }
}

}  // namespace base
