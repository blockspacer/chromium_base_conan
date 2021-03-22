// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/containers/prioritized_repeating_task_list.h"

#include <ctype.h>

#include <memory>
#include <string>
#include <cstddef>

#include "base/logging.h"
#include "base/compiler_specific.h"
#include "base/bind.h"
#include "base/stl_util.h"
#include "base/callback.h"
#include "base/run_loop.h"

#include "base/test/task_environment.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace basic {

namespace {

enum TestRequestPriority {
  THROTTLED = 0,  // Used to signal that resources
                  // should be reserved for following
                  // requests (i.e. that higher priority
                  // following requests are expected).
  MINIMUM_PRIORITY = THROTTLED,
  IDLE = 1,  // Default "as resources available" level.
  LOWEST = 2,
  DEFAULT_PRIORITY = LOWEST,
  LOW = 3,
  MEDIUM = 4,
  HIGHEST = 5,
  LARGE = 6,
  MAXIMUM_PRIORITY = LARGE,
};

enum TestRequestPrioritySize {
  NUM_PRIORITIES = MAXIMUM_PRIORITY + 1,
};

class PrioritizedRepeatingTaskListTest : public testing::Test {
 public:
  typedef PrioritizedRepeatingTaskList::Priority Priority;

  void PushTaskName(const std::string& task_name) {
    base::AutoLock auto_lock(task_names_lock_);
    task_names_.push_back(task_name);
  }

 protected:
  void Prepare() {
    task_list_ = std::make_unique<PrioritizedRepeatingTaskList>(NUM_PRIORITIES);
  }

  std::unique_ptr<PrioritizedRepeatingTaskList> task_list_;
  std::vector<std::string> task_names_;
  base::Lock task_names_lock_;
  base::test::TaskEnvironment task_environment;
};

TEST_F(PrioritizedRepeatingTaskListTest, RepeatingClosure) {
  Prepare();

  PrioritizedRepeatingTaskList::Handle Task5;
  PrioritizedRepeatingTaskList::Handle Task3;
  PrioritizedRepeatingTaskList::Handle Task6;
  PrioritizedRepeatingTaskList::Handle Task1;

  auto resetTasks = [&](bool eraseAll = false) {
    if(!Task5.is_null()) Task5.Reset();
    Task5 =
      task_list_->Add(
        base::BindRepeating(
          &PrioritizedRepeatingTaskListTest::PushTaskName
          , base::Unretained(this)
          , "Task5")
        , 5);

    if(!Task3.is_null()) Task3.Reset();
    Task3 =
      task_list_->Add(
        base::BindRepeating(
          &PrioritizedRepeatingTaskListTest::PushTaskName
          , base::Unretained(this)
          , "Task3")
        , 3);

    if(!Task6.is_null()) Task6.Reset();
    Task6 =
      task_list_->Add(
        base::BindRepeating(
          &PrioritizedRepeatingTaskListTest::PushTaskName
          , base::Unretained(this)
          , "Task6")
        , 6);

    if(!Task1.is_null()) Task1.Reset();
    Task1 =
      task_list_->Add(
        base::BindRepeating(
          &PrioritizedRepeatingTaskListTest::PushTaskName
          , base::Unretained(this)
          , "Task1")
        , 1);
  };

  resetTasks();
  task_list_->RunAll();
  EXPECT_EQ((std::vector<std::string>{"Task6", "Task5", "Task3", "Task1"}), task_names_);
  task_names_.clear();
  task_list_->RunAll();
  EXPECT_EQ((std::vector<std::string>{"Task6", "Task5", "Task3", "Task1"}), task_names_);
  task_names_.clear();
  task_list_->RunAndRemoveAll();
  EXPECT_EQ((std::vector<std::string>{"Task6", "Task5", "Task3", "Task1"}), task_names_);
  task_names_.clear();
  EXPECT_EQ(0u, task_list_->size());
  task_list_->RunAll(); // does nothing
  task_list_->RunAndRemoveAll(); // does nothing
  EXPECT_EQ(0u, task_list_->size());

  resetTasks();
  task_list_->Cancel(Task5);
  task_list_->RunAll();
  EXPECT_EQ((std::vector<std::string>{"Task6", "Task3", "Task1"}), task_names_);
  task_names_.clear();
  task_list_->Cancel(Task1);
  task_list_->RunAll();
  EXPECT_EQ((std::vector<std::string>{"Task6", "Task3"}), task_names_);
  task_names_.clear();
  task_list_->Cancel(Task6);
  task_list_->RunAndRemoveAll();
  EXPECT_EQ((std::vector<std::string>{"Task3",}), task_names_);
  task_names_.clear();
  EXPECT_EQ(0u, task_list_->size());
}

}  // namespace

}  // namespace basic
