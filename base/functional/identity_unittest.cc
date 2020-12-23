// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "tests_common.hpp"

#include "base/functional/identity.h"

#include <vector>

namespace base {

TEST(FunctionalTest, Identity) {
  static constexpr identity id;

  std::vector<int> v;
  EXPECT_EQ(&v, &id(v));

  constexpr int arr = {0};
  static_assert(arr == id(arr), "");
}

}  // namespace base
