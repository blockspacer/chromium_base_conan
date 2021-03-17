// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/hash/murmurhash.h"

#include "base/stl_util.h"
#include "base/strings/string_piece.h"
#include "base/containers/span.h"

#include <string>
#include <vector>
#include <algorithm>

#include "testing/gtest/include/gtest/gtest.h"

using namespace base;

namespace basic {

static size_t GetHash(const base::span<const uint8_t>& slice) {
  static const unsigned int hash_seed = 0;
  static basic::murmur_hash hash;
  auto result = hash(slice);
  uint64_t result2 = basic::MurmurHash2_64(slice.data(), static_cast<int>(slice.size()), hash_seed);
  EXPECT_EQ(result, result2);
  return result;
}

static size_t GetHashWithSeed(const base::span<const uint8_t>& slice) {
  static const unsigned int hash_seed = 112358;
  auto result = basic::MurmurHash(slice.data(), static_cast<int>(slice.size()), hash_seed);
  uint64_t result2 = basic::MurmurHash2_64(slice.data(), static_cast<int>(slice.size()), hash_seed);
  EXPECT_EQ(result, result2);
  return result;
}

TEST(MurmurhashTest, All) {
  constexpr struct {
    uint64_t output;
    uint64_t output_with_seed;
    StringPiece input;
  } kTestCases[] = {
      {0ull, 3361001977063183511ull, ""},
      {12115936543014688869ull, 5901146008870064726ull, "0123456789"},
      {15256545620076441550ull, 15739062127867740014ull, "hello world"},
  };
  for (const auto& test_case : kTestCases) {
    SCOPED_TRACE(test_case.input);
    auto bytes = as_bytes(make_span(test_case.input));
    EXPECT_EQ(test_case.output, GetHash(bytes));
  }
  for (const auto& test_case : kTestCases) {
    SCOPED_TRACE(test_case.input);
    auto bytes = as_bytes(make_span(test_case.input));
    EXPECT_EQ(test_case.output_with_seed, GetHashWithSeed(bytes));
  }
}

} // namespace basic

