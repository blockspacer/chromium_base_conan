// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/hash/twang_hash.h"

#include "base/stl_util.h"
#include "base/strings/string_piece.h"
#include "base/containers/span.h"

#include <string>
#include <vector>
#include <algorithm>

#include "testing/gtest/include/gtest/gtest.h"

using namespace base;

namespace basic {
namespace hash {

TEST(TwangMix64Test, TWang_mix64) {
  uint64_t i1 = 0x78a87873e2d31dafULL;
  uint64_t i1_res = 3389151152926383528ULL;
  EXPECT_EQ(i1_res, twang_mix64(i1));
  EXPECT_EQ(i1, twang_unmix64(i1_res));

  uint64_t i2 = 0x0123456789abcdefULL;
  uint64_t i2_res = 3061460455458984563ull;
  EXPECT_EQ(i2_res, twang_mix64(i2));
  EXPECT_EQ(i2, twang_unmix64(i2_res));
}

namespace {
void checkTWang(uint64_t r) {
  uint64_t result = twang_mix64(r);
  EXPECT_EQ(r, twang_unmix64(result));
}
} // namespace

TEST(TwangMix64Test, TWang_Unmix64) {
  // We'll try (1 << i), (1 << i) + 1, (1 << i) - 1
  for (int i = 1; i < 64; i++) {
    checkTWang((uint64_t(1) << i) - 1);
    checkTWang(uint64_t(1) << i);
    checkTWang((uint64_t(1) << i) + 1);
  }
}

TEST(TwangMix64Test, TWang_32From64) {
  uint64_t i1 = 0x78a87873e2d31dafULL;
  uint32_t i1_res = 1525586863ul;
  EXPECT_EQ(twang_32from64(i1), i1_res);

  uint64_t i2 = 0x0123456789abcdefULL;
  uint32_t i2_res = 2918899159ul;
  EXPECT_EQ(twang_32from64(i2), i2_res);
}

} // namespace hash
} // namespace basic

