// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/hash/city_hash.h"
#include "base/stl_util.h"
#include "base/strings/string_piece.h"
#include "base/containers/span.h"

#include <string>
#include <vector>
#include <algorithm>

#include GTEST_HEADER_INCLUDE

namespace base {

TEST(CityHashTest, String) {
  constexpr struct {
    uint64_t output;
    uint64_t output_with_seed;
    StringPiece input;
  } kTestCases[] = {
      {11160318154034397263ull, 14404538258149959151ull, ""},
      {12631666426400459317ull, 12757304017804637665ull, "0123456789"},
      {12386028635079221413ull, 4144044770257928618ull, "hello world"},
  };
  for (const auto& test_case : kTestCases) {
    SCOPED_TRACE(test_case.input);
    auto bytes = as_bytes(make_span(test_case.input));
    EXPECT_EQ(test_case.output, CityHash64(bytes));
  }
  for (const auto& test_case : kTestCases) {
    SCOPED_TRACE(test_case.input);
    auto bytes = as_bytes(make_span(test_case.input));
    const uint64_t seed = 112358;
    EXPECT_EQ(test_case.output_with_seed, CityHash64WithSeed(bytes, seed));
  }
}

}  // namespace base
