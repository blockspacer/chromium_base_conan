// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/hash/xxhash.h"

#include "base/stl_util.h"
#include "base/strings/string_piece.h"
#include "base/containers/span.h"

#include <string>
#include <vector>
#include <algorithm>

#include GTEST_HEADER_INCLUDE

namespace base {

static size_t GetHash(const base::span<const uint8_t>& slice) {
  static const unsigned int hash_seed = 0;
  void* xxh = XXH32_init(hash_seed);
  XXH32_update(xxh, slice.data(), static_cast<uint32_t>(slice.size()));
  return XXH32_digest(xxh);
}

static size_t GetHashWithSeed(const base::span<const uint8_t>& slice) {
  static const unsigned int hash_seed = 112358;
  void* xxh = XXH32_init(hash_seed);
  XXH32_update(xxh, slice.data(), static_cast<uint32_t>(slice.size()));
  return XXH32_digest(xxh);
}

TEST(XXHashTest, All) {
  constexpr struct {
    uint64_t output;
    uint64_t output_with_seed;
    StringPiece input;
  } kTestCases[] = {
      {46947589ull, 4136753956ull, ""},
      {2500631562ull, 4273423082ull, "0123456789"},
      {3468387874ull, 4212333116ull, "hello world"},
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

} // namespace base

