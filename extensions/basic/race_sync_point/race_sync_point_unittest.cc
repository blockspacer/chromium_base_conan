// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
// The following only applies to changes made to this file as part of YugaByte development.
//
// Portions Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//

#include "basic/race_sync_point/race_sync_point.h"
#include "basic/promise/post_task_executor.h"
#include "basic/promise/do_nothing_promise.h"
#include "basic/promise/abstract_promise.h"
#include "basic/promise/helpers.h"
#include "basic/rvalue_cast.h"

#include "base/test/gtest_util.h"
#include "base/test/test_mock_time_task_runner.h"
#include "base/test/task_environment.h"
#include "base/bind.h"
#include "base/run_loop.h"
#include "base/threading/thread.h"
#include "base/task_runner.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace basic {

#ifndef NDEBUG
static void RunThread(bool *var) {
  *var = true;
  TEST_SYNC_POINT("first");
}
#endif

class RaceSyncPointTest : public testing::Test {
 public:
  base::test::TaskEnvironment task_environment;
};

TEST_F(RaceSyncPointTest, Hierarchy) {
#ifndef NDEBUG
  {
    std::vector<RaceSyncPoint::SyncDependency> dependencies;
    dependencies.push_back(RaceSyncPoint::SyncDependency(
      SyncPredecessor{"first"}, SyncSuccessor{"second"}));
    // does nothing
    dependencies.push_back(RaceSyncPoint::SyncDependency(
      SyncPredecessor{"first"}, SyncSuccessor{"second"}));
    EXPECT_OK(RaceSyncPoint::GetInstance()->ClearAndLoadDependencies(dependencies));
  }

  {
    std::vector<RaceSyncPoint::SyncDependency> dependencies;
    dependencies.push_back(RaceSyncPoint::SyncDependency(
      SyncPredecessor{"first"}, SyncSuccessor{"second"}));
    dependencies.push_back(RaceSyncPoint::SyncDependency(
      SyncPredecessor{"second"}, SyncSuccessor{"third"}));
    dependencies.push_back(RaceSyncPoint::SyncDependency(
      SyncPredecessor{"third"}, SyncSuccessor{"first"}));
    EXPECT_NOT_OK(RaceSyncPoint::GetInstance()->ClearAndLoadDependencies(dependencies));
  }
#else
  LOG(INFO) << "Test skipped in release mode.";
#endif // NDEBUG
}

TEST_F(RaceSyncPointTest, TestRaceSyncPoint) {
#ifndef NDEBUG
  // Set up a sync point "second" that depends on "first".
  std::vector<RaceSyncPoint::SyncDependency> dependencies;
  dependencies.push_back(RaceSyncPoint::SyncDependency(
    SyncPredecessor{"first"}, SyncSuccessor{"second"}));
  EXPECT_OK(RaceSyncPoint::GetInstance()->ClearAndLoadDependencies(dependencies));
  RaceSyncPoint::GetInstance()->EnableProcessing();

  base::RunLoop run_loop;

  // Kick off a thread that'll process "first", but not before
  // setting 'var' to true, which unblocks the main thread.
  ::base::Thread thread("Test thread");
  ASSERT_TRUE(thread.Start());
  // Without this call this test is racy.
  EXPECT_TRUE(thread.WaitUntilThreadStarted());
  bool var = false;

  thread.task_runner()->PostTaskAndReply(
    FROM_HERE
    , ::base::BindOnce(&RunThread, base::Unretained(&var))
    , run_loop.QuitClosure()
  );

  // Blocked on RunThread to process "first".
  TEST_SYNC_POINT("second");
  // "first" must be processed before "second", so `var` must be `true`
  ASSERT_TRUE(var);

  run_loop.Run();

  thread.Stop();

  RaceSyncPoint::GetInstance()->ClearTrace();
  RaceSyncPoint::GetInstance()->DisableProcessing();

#else
  LOG(INFO) << "Test skipped in release mode.";
#endif // NDEBUG
}

} // namespace basic
