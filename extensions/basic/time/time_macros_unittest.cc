// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/time/time_macros.h"

#include "base/memory/ptr_util.h"
#include "base/timer/mock_timer.h"
#include "base/test/task_environment.h"
#include "base/rand_util.h"
#include "base/i18n/time_formatting.h"
#include "base/strings/utf_string_conversions.h"
#include "base/threading/platform_thread.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace basic {

class TimeMacrosTest : public testing::Test {
 public:
  void SetUp() override {
    time_now_ = base::Time::Now();
  }

  void IncrementCounterEveryN(int* counter) {
    INTERNAL_DO_EVERY_N_US(time_step_.InMicroseconds(), microsecondSinceUnixEpoch()) {
      ++(*counter);
    }
  }

 protected:
  uint64_t microsecondSinceUnixEpoch()
  {
    return (time_now_ - base::Time::UnixEpoch()).InMicroseconds();
  }

 protected:
  base::Time time_now_;

  base::TimeDelta time_step_ = base::TimeDelta::FromMicroseconds(100);

  base::test::TaskEnvironment task_environment;
};

TEST_F(TimeMacrosTest, Basic) {
  int counter = 0;

  IncrementCounterEveryN(&counter);
  EXPECT_EQ(counter, 1);
  IncrementCounterEveryN(&counter);
  EXPECT_EQ(counter, 1);

  time_now_ += time_step_;

  IncrementCounterEveryN(&counter);
  EXPECT_EQ(counter, 2);
  IncrementCounterEveryN(&counter);
  EXPECT_EQ(counter, 2);
}

}  // namespace basic
