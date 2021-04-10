// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/hash/jenkins_hash.h"

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

TEST(Hash, Jenkins_Rev_Mix32) {
  uint32_t i1 = 3805486511ul;
  uint32_t i1_res = 381808021ul;
  EXPECT_EQ(i1_res, jenkins_rev_mix32(i1));
  EXPECT_EQ(i1, jenkins_rev_unmix32(i1_res));

  uint32_t i2 = 2309737967ul;
  uint32_t i2_res = 1834777923ul;
  EXPECT_EQ(i2_res, jenkins_rev_mix32(i2));
  EXPECT_EQ(i2, jenkins_rev_unmix32(i2_res));
}

namespace {
void checkJenkins(uint32_t r) {
  uint32_t result = jenkins_rev_mix32(r);
  EXPECT_EQ(r, jenkins_rev_unmix32(result));
}
} // namespace

TEST(Hash, Jenkins_Rev_Unmix32) {
  // We'll try (1 << i), (1 << i) + 1, (1 << i) - 1
  for (int i = 1; i < 32; i++) {
    checkJenkins((1U << i) - 1);
    checkJenkins(1U << i);
    checkJenkins((1U << i) + 1);
  }
}

} // namespace hash
} // namespace basic

