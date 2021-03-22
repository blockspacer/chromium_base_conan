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
#pragma once

#include "basic/strong_types/strong_string.h"
#include "basic/status/status_macros.h"

#include <assert.h>

#include <condition_variable>
#include <mutex>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <functional>

#if TODO

#ifdef NDEBUG
// empty in release build
#define TEST_KILL_RANDOM(kill_point, basic_kill_odds)
#else

namespace basic {

// This is only set for testing only.
// If non-zero, kill at various points in source code with probability 1/this
extern int basic_kill_odds;

// If kill point has a prefix on this list, will skip killing.
extern std::vector<std::string> basic_kill_prefix_blacklist;

// Kill the process with probablity 1/odds for testing.
extern void TestKillRandom(std::string kill_point, int odds,
                           const std::string& srcfile, int srcline);

// To avoid crashing always at some frequently executed codepaths (during
// kill random test), use this factor to reduce odds
#define REDUCE_ODDS 2
#define REDUCE_ODDS2 4

#define TEST_KILL_RANDOM(kill_point, basic_kill_odds)                  \
  {                                                                      \
    if (basic_kill_odds > 0) {                                         \
      TestKillRandom(kill_point, basic_kill_odds, __FILE__, __LINE__); \
    }                                                                    \
  }

}  // namespace basic
#endif

#endif // TODO

#ifdef NDEBUG
#define TEST_SYNC_POINT(x)
#define TEST_SYNC_POINT_CALLBACK(x, y)
#else

namespace basic {

// Predecessor (Dependency) must finish before Successor
STRONGLY_TYPED_STRING(SyncPredecessor);
STRONGLY_TYPED_STRING(SyncSuccessor);

// This class provides facility to reproduce race conditions deterministically
// in unit tests.
// Developer could specify sync points in the codebase via TEST_SYNC_POINT.
// Each sync point represents a position in the execution stream of a thread.
// In the unit test, 'Happens After' relationship among sync points could be
// setup via RaceSyncPoint::ClearAndLoadDependencies, to reproduce a desired interleave of
// threads execution.
// Refer to (DBTest,TransactionLogIteratorRace), for an example use case.
class RaceSyncPoint {
 public:
  static RaceSyncPoint* GetInstance();

  struct SyncDependency {
    // successor depends on predecessor
    SyncDependency(SyncPredecessor predecessor, SyncSuccessor successor);

    // Predecessor must finish before Successor
    SyncPredecessor predecessor;

    SyncSuccessor successor;
  };

  /// \note also clears `successors_`, `predecessors_` and `cleared_points_`
  //
  // call once at the beginning of a test to setup the dependency between
  // sync points
  //
  basic::Status ClearAndLoadDependencies(
    const std::vector<SyncDependency>& dependencies);

#if TODO
  // Set up a call back function in sync point.
  void SetCallBack(const SyncSuccessor point,
                   std::function<void(void*)> callback);
  // Clear all call back functions.
  void ClearAllCallBacks();
#endif // TODO

  // enable sync point processing (disabled on startup)
  void EnableProcessing();

  // disable sync point processing
  void DisableProcessing();

  // remove the execution trace of all sync points
  // calls `cleared_points_.clear()`
  void ClearTrace();

  // triggered by TEST_SYNC_POINT, blocking execution until all predecessors
  // are executed.
  // And/or call registered callback functionn, with argument `cb_arg`
  void Process(const SyncSuccessor& point, void* cb_arg = nullptr);

  /// \TODO: it might be useful to provide a function that blocks until all
  /// sync points are cleared.

 private:
  RaceSyncPoint();

  bool PredecessorsAllCleared(const SyncSuccessor& point);

  // successor/predecessor map loaded from ClearAndLoadDependencies
  std::unordered_map<SyncPredecessor, std::vector<SyncSuccessor>> successors_;
  std::unordered_map<SyncSuccessor, std::vector<SyncPredecessor>> predecessors_;
#if TODO
  std::unordered_map<SyncPredecessor, std::function<void(void*)> > callbacks_;
#endif // TODO

  std::mutex mutex_;
  std::condition_variable cv_;
  // sync points that have been passed through
  // stores both `SyncSuccessor`-s and `SyncPredecessor`-s
  // converted to `std::string`
  std::unordered_set<std::string> cleared_points_;
  bool enabled_ = false;
#if TODO
  int num_callbacks_running_ = 0;
#endif // TODO
};

}  // namespace basic

// Use TEST_SYNC_POINT to specify sync points inside code base.
// Sync points can have happens-after depedency on other sync points,
// configured at runtime via RaceSyncPoint::ClearAndLoadDependencies. This could be
// utilized to re-produce race conditions between threads.
// TEST_SYNC_POINT is no op in release build.
//
// USAGE
//
// // Set up a sync point "second" that depends on "first".
// vector<RaceSyncPoint::SyncDependency> dependencies;
// dependencies.push_back(RaceSyncPoint::SyncDependency("first", "second"));
// DCHECK_OK(RaceSyncPoint::GetInstance()->ClearAndLoadDependencies(dependencies));
// RaceSyncPoint::GetInstance()->EnableProcessing();
//
// // blocking execution until all predecessors are executed.
// // i.e. blocked to process "first".
// TEST_SYNC_POINT("second");
//
// RaceSyncPoint::GetInstance()->ClearTrace();
// RaceSyncPoint::GetInstance()->DisableProcessing();
//
#define TEST_SYNC_POINT(x) basic::RaceSyncPoint::GetInstance()->Process(SyncSuccessor{x})
#define TEST_SYNC_POINT_CALLBACK(x, y) \
  basic::RaceSyncPoint::GetInstance()->Process(SyncSuccessor{x}, (void*)y)
#endif  // NDEBUG
