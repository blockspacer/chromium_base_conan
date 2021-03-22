// Copyright 2014-2015 Project Vogue. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string>

#include "basic/disjoint_sets/disjoint_sets.h"
#include "basic/status/status_macros.h"
#include "basic/promise/post_promise.h"
#include "basic/rvalue_cast.h"
#include "basic/promise/abstract_promise.h"
#include "basic/promise/helpers.h"

#include "base/test/gtest_util.h"
#include "base/test/test_mock_time_task_runner.h"
#include "base/test/task_environment.h"
#include "base/bind.h"
#include "base/run_loop.h"
#include "base/threading/thread.h"
#include "base/task_runner.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace basic {
namespace {

class DisjointSetsTest : public testing::Test {
 public:
  void SetUp() override {
    DCHECK(!disjoint_sets_);
    disjoint_sets_ = std::make_unique<DisjointSets<size_t>>();
  }

  void TearDown() override {
    disjoint_sets_.reset();
  }

 protected:
  base::test::TaskEnvironment task_environment;
  std::unique_ptr<DisjointSets<size_t>> disjoint_sets_;
};

TEST_F(DisjointSetsTest, Simple) {
  disjoint_sets_->AddToSet(0);
  disjoint_sets_->AddToSet(1);
  disjoint_sets_->AddToSet(2);
  disjoint_sets_->AddToSet(3);
  disjoint_sets_->AddToSet(4);
  disjoint_sets_->AddToSet(5);
  disjoint_sets_->AddToSet(6);
  disjoint_sets_->AddToSet(7);
  disjoint_sets_->AddToSet(8);

  EXPECT_FALSE(disjoint_sets_->IsInSameSet(0, 1));
  EXPECT_FALSE(disjoint_sets_->IsInSameSet(5, 6));

  // Before UnionMerge's: {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}
  disjoint_sets_->UnionMerge(1, 2);
  disjoint_sets_->UnionMerge(1, 5);
  disjoint_sets_->UnionMerge(6, 8);
  disjoint_sets_->UnionMerge(5, 6);
  disjoint_sets_->UnionMerge(4, 3);

  // After UnionMerge's: {1, 2, 5, 6, 8}, {3, 4}, {7}
  EXPECT_TRUE(disjoint_sets_->IsInSameSet(1, 2));
  EXPECT_TRUE(disjoint_sets_->IsInSameSet(2, 1));
  EXPECT_TRUE(disjoint_sets_->IsInSameSet(1, 5));
  EXPECT_TRUE(disjoint_sets_->IsInSameSet(5, 6));
  EXPECT_TRUE(disjoint_sets_->IsInSameSet(1, 6));
  EXPECT_TRUE(disjoint_sets_->IsInSameSet(6, 1));
  EXPECT_TRUE(disjoint_sets_->IsInSameSet(1, 8));
  EXPECT_TRUE(disjoint_sets_->IsInSameSet(8, 1));

  EXPECT_TRUE(disjoint_sets_->IsInSameSet(3, 4));
  EXPECT_TRUE(disjoint_sets_->IsInSameSet(4, 3));

  EXPECT_TRUE(disjoint_sets_->IsInSameSet(7, 7));

  EXPECT_FALSE(disjoint_sets_->IsInSameSet(1, 7));
  EXPECT_FALSE(disjoint_sets_->IsInSameSet(7, 1));

  EXPECT_FALSE(disjoint_sets_->IsInSameSet(1, 4));
  EXPECT_FALSE(disjoint_sets_->IsInSameSet(4, 1));

  EXPECT_FALSE(disjoint_sets_->IsInSameSet(3, 7));
  EXPECT_FALSE(disjoint_sets_->IsInSameSet(7, 3));

  auto const disjoint_sets_tmp = std::move(disjoint_sets_);
  EXPECT_TRUE(disjoint_sets_tmp->IsInSameSet(8, 1));
}

}  // namespace
}  // namespace basic
