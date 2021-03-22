//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.
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
#include "basic/dependency_hierarchy/dependency_hierarchy.h"
#include "basic/status/app_error_space.h"
#include "basic/stl_util.h"
#include "basic/logging.h"

#include "base/rand_util.h"
#include "base/logging.h"
#include "base/macros.h"
#include "base/location.h"
#include "base/stl_util.h"

#ifndef NDEBUG

namespace basic {

namespace {

basic::Status checkCyclesInHierarchy(
  const std::vector<RaceSyncPoint::SyncDependency>& dependencies)
{
  using namespace app_error_space;

  std::map<
    // stores both `SyncSuccessor`-s and `SyncPredecessor`-s
    // converted to `std::string`
    std::string
    , scoped_refptr<Dependency>
  > dependencyHierarchy;

  for (const auto& dependency : dependencies) {
    scoped_refptr<Dependency> successorContents
      = basic::LookupOrInsert(&dependencyHierarchy
        , dependency.successor.ToString()
        , ::base::MakeRefCounted<Dependency>());
    DCHECK_VALID_PTR(successorContents.get());

    scoped_refptr<Dependency> predecessorContents
      = basic::LookupOrInsert(&dependencyHierarchy
        , dependency.predecessor.ToString()
        , ::base::MakeRefCounted<Dependency>());
    DCHECK_VALID_PTR(predecessorContents.get());

    RETURN_WITH_MESSAGE_IF_NOT_OK(
      successorContents->addDependency(predecessorContents))
      << "(Sync Point) Wrong Hierarchy";
  }

  RETURN_OK();
}

} // namespace

RaceSyncPoint::SyncDependency::SyncDependency(
  SyncPredecessor predecessor, SyncSuccessor successor)
  : predecessor(std::move(predecessor)), successor(std::move(successor)) {}

RaceSyncPoint::RaceSyncPoint()
  : enabled_(false) {
}

#if TODO
int basic_kill_odds = 0;

std::vector<std::string> basic_kill_prefix_blacklist;

void TestKillRandom(std::string kill_point, int odds,
                    const std::string& srcfile, int srcline) {
  for (auto& p : basic_kill_prefix_blacklist) {
    if (kill_point.substr(0, p.length()) == p) {
      return;
    }
  }

  assert(odds > 0);
  if (odds % 7 == 0) {
    // class Random uses multiplier 16807, which is 7^5. If odds are
    // multiplier of 7, there might be limited values generated.
    odds++;
  }
  /// \todo refactor & test
  bool crash = base::RandInt(0, odds) == odds;
  if (crash) {
    LOG_CALL(LOG(FATAL)) << srcfile << srcline;
  }
}
#endif // TODO

RaceSyncPoint* RaceSyncPoint::GetInstance() {
  static RaceSyncPoint sync_point;
  return &sync_point;
}

basic::Status RaceSyncPoint::ClearAndLoadDependencies(
  const std::vector<SyncDependency>& dependencies)
{
  std::unique_lock<std::mutex> lock(mutex_);
  successors_.clear();
  predecessors_.clear();
  cleared_points_.clear();

  RETURN_IF_NOT_OK(checkCyclesInHierarchy(dependencies));

  for (const auto& dependency : dependencies) {
    successors_[dependency.predecessor].push_back(dependency.successor);
    predecessors_[dependency.successor].push_back(dependency.predecessor);
  }
  cv_.notify_all();

  RETURN_OK();
}

bool RaceSyncPoint::PredecessorsAllCleared(const SyncSuccessor& point) {
  for (const auto& pred : predecessors_[point]) {
    if (cleared_points_.count(pred.ToString()) == 0) {
      return false;
    }
  }
  return true;
}

#if TODO
void RaceSyncPoint::SetCallBack(const SyncSuccessor point,
                            std::function<void(void*)> callback) {
  std::unique_lock<std::mutex> lock(mutex_);
  callbacks_[point] = callback;
}

void RaceSyncPoint::ClearAllCallBacks() {
  std::unique_lock<std::mutex> lock(mutex_);
  while (num_callbacks_running_ > 0) {
    cv_.wait(lock);
  }
  callbacks_.clear();
}
#endif // TODO

void RaceSyncPoint::EnableProcessing() {
  std::unique_lock<std::mutex> lock(mutex_);
  enabled_ = true;
}

void RaceSyncPoint::DisableProcessing() {
  std::unique_lock<std::mutex> lock(mutex_);
  enabled_ = false;
}

void RaceSyncPoint::ClearTrace() {
  std::unique_lock<std::mutex> lock(mutex_);
  cleared_points_.clear();
}

void RaceSyncPoint::Process(const SyncSuccessor& point, void* cb_arg) {
  std::unique_lock<std::mutex> lock(mutex_);

  if (!enabled_) return;

#if TODO
  auto callback_pair = callbacks_.find(point);
  if (callback_pair != callbacks_.end()) {
    num_callbacks_running_++;
    lock.unlock();
    callback_pair->second(cb_arg);
    lock.lock();
    num_callbacks_running_--;
    cv_.notify_all();
  }
#endif // TODO

  while (!PredecessorsAllCleared(point)) {
    cv_.wait(lock);
  }

  cleared_points_.insert(point.ToString());
  cv_.notify_all();
}

}  // namespace basic
#endif  // NDEBUG
