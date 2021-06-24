// Copyright 2015 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <basic/message_loop/message_loop_utils.h>

#include <base/callback.h>
#include <base/time/time.h>
#include <base/run_loop.h>
#include "base/test/gtest_util.h"
#include "base/test/bind.h"
#include "base/test/test_mock_time_task_runner.h"
#include "base/test/task_environment.h"
#include "base/location.h"
#include "base/bind.h"
#include "base/threading/thread.h"
#include "base/task_runner.h"
#include "base/strings/string_util.h"
#include "base/test/scoped_environment_variable_override.h"
#include "base/environment.h"
#include "base/threading/thread.h"
#include "base/sequenced_task_runner.h"

#include "testing/gtest/include/gtest/gtest.h"

using namespace base;

namespace basic {
namespace {

class MessageLoopUtilsTest : public ::testing::Test {
 protected:
#if SIGNLE_THREAD_ENV_MESSAGE_LOOP_UTILS_TEST
  test::SingleThreadTaskEnvironment task_environment_;
  SequencedTaskRunner& task_runner_ =
    *(SequencedTaskRunnerHandle::Get());
#else
  base::test::TaskEnvironment task_environment_;
  base::SingleThreadTaskRunner& task_runner_ =
    *(task_environment_.GetMainThreadTaskRunner());
#endif
};

static void LoopCounterTask(int* counter) {
  ++(*counter);
}

TEST_F(MessageLoopUtilsTest, RunLoopRunUntilIterations) {
  int counter = 0;
  task_runner_.PostTask(
      FROM_HERE, BindOnce(&LoopCounterTask,
                          Unretained(&counter)));

  task_runner_.PostTask(
      FROM_HERE, BindOnce(&LoopCounterTask,
                          Unretained(&counter)));

  task_runner_.PostTask(
      FROM_HERE, BindOnce(&LoopCounterTask,
                          Unretained(&counter)));

  task_runner_.PostDelayedTask(
      FROM_HERE, MakeExpectedNotRunClosure(FROM_HERE), TimeDelta::FromMinutes(1));

  int runs = RunLoopRunUntilIterations(2,
    base::BindRepeating(
      [](){
        return false; // stop loop
      }
    ));
  EXPECT_EQ(2, runs);

  EXPECT_EQ(3, counter);
}

TEST_F(MessageLoopUtilsTest, RunLoopRunMinIterations) {
  int counter = 0;
  task_runner_.PostTask(
      FROM_HERE, BindOnce(&LoopCounterTask,
                          Unretained(&counter)));

  task_runner_.PostTask(
      FROM_HERE, BindOnce(&LoopCounterTask,
                          Unretained(&counter)));

  task_runner_.PostTask(
      FROM_HERE, BindOnce(&LoopCounterTask,
                          Unretained(&counter)));

  task_runner_.PostDelayedTask(
      FROM_HERE, MakeExpectedNotRunClosure(FROM_HERE), TimeDelta::FromMinutes(1));

  int runs = RunLoopRunUntilIterations(2,
    base::BindRepeating(
      [](){
        return true; // stop loop
      }
    ));
  EXPECT_EQ(0, runs);

  EXPECT_EQ(0, counter);
}

TEST_F(MessageLoopUtilsTest, RunLoopRunUntilMax) {
  task_runner_.PostDelayedTask(
      FROM_HERE, MakeExpectedNotRunClosure(FROM_HERE), TimeDelta::FromMinutes(1));

  base::Time start = base::Time::Now();

  static const uint64_t kTimeMax = 10;

  RunLoopRunUntil(TimeDelta::FromMilliseconds(kTimeMax),
    base::BindRepeating(
      [](){
        return false; // stop loop
      }
    ));

  base::Time end = base::Time::Now();

  EXPECT_GE(base::TimeDelta(end - start).InMilliseconds(), kTimeMax);
  EXPECT_LE(base::TimeDelta(end - start).InMilliseconds(), kTimeMax * 2);
}

TEST_F(MessageLoopUtilsTest, RunLoopRunUntilMin) {
  task_runner_.PostDelayedTask(
      FROM_HERE, MakeExpectedNotRunClosure(FROM_HERE), TimeDelta::FromMinutes(1));

  base::Time start = base::Time::Now();

  static const uint64_t kTimeMax = 10;

  RunLoopRunUntil(TimeDelta::FromMilliseconds(kTimeMax),
    base::BindRepeating(
      [](){
        return true; // stop loop
      }
    ));

  base::Time end = base::Time::Now();

  EXPECT_LT(base::TimeDelta(end - start).InMilliseconds(), kTimeMax);
}

} // namespace
} // namespace basic
