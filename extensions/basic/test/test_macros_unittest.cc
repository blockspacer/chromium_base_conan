// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/test/test_macros.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "testing/gmock/include/gmock/gmock.h"

#include <algorithm>
#include <limits>
#include <vector>

#include "basic/rvalue_cast.h"
#include "base/location.h"
#include "base/rand_util.h"
#include "base/run_loop.h"
#include "base/sequenced_task_runner.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_util.h"
#include "base/synchronization/lock.h"
#include "base/synchronization/waitable_event.h"
#include "base/task/post_task.h"
#include "base/threading/thread_restrictions.h"
#include "base/test/task_environment.h"

using namespace base;

namespace basic {

class TestMacrosTest : public testing::Test {
 protected:
  base::test::TaskEnvironment task_environment;
};

TEST_F(TestMacrosTest, ExpectElementsEq) {
  std::vector<int> vecA{1,2,3};
  EXPECT_ELEMENTS_EQ(vecA, 1, 2, 3);
}

TEST_F(TestMacrosTest, StrContains) {
  ASSERT_STR_CONTAINS("abcd", "bc");
  ASSERT_STR_NOT_CONTAINS("agfm", "bc");
}

}  // namespace basic
