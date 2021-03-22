// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <stddef.h>

#include <vector>

#include "base/logging.h"
#include "base/callback.h"
#include "base/bind.h"
#include "base/optional.h"
#include "basic/containers/prioritized_list.h"

namespace basic {

// A priority-based list of repeating callbacks.
// Processing order is by priority
// (task with highest priority runs first i.e. from +inf to 0) and then FIFO.
// Owns copies of added |RepeatingClosure|-s.
//
// This class is NOT thread-safe which is enforced by the underlying
// non-thread-safe PrioritizedList.
//
/// \note See instead `PrioritizedOnceTaskHeap`
/// if you search for priority-based queue of not-periodic once callbacks.
//
class PrioritizedRepeatingTaskList {
 public:
  using RepeatingTask = base::RepeatingClosure;
  using Priority = PrioritizedList<RepeatingTask>::Priority;

  // A handle to the enqueued `RepeatingTask`.
  // The handle becomes invalid when the `RepeatingTask` is
  // canceled, updated, or started.
  typedef PrioritizedList<RepeatingTask>::Pointer Handle;

  explicit PrioritizedRepeatingTaskList(const Priority num_priorities);

  PrioritizedRepeatingTaskList(const PrioritizedRepeatingTaskList&) = delete;
  PrioritizedRepeatingTaskList& operator=(const PrioritizedRepeatingTaskList&) = delete;
  ~PrioritizedRepeatingTaskList();

  size_t size() const { return queue_.size(); }
  size_t num_priorities() const { return queue_.num_priorities(); }

  // Adds |task| with |priority| to the |queue_|.
  // Returns handle to the task.
  Handle Add(RepeatingTask task, Priority priority);

  // Just like Add, except that it adds task at the font of queue of tasks with
  // priorities of |priority|.
  Handle AddAtHead(RepeatingTask task, Priority priority);

  // Removes the task with |handle| from the queue. Invalidates |handle|.
  // Note: a Handle is valid if the task is in the queue.
  void Cancel(const Handle& handle);

  // Cancels and returns the oldest-lowest-priority task invalidating any
  // handles to it. Returns NULL if the queue is empty.
  base::Optional<RepeatingTask> EvictOldestLowest();

  // Moves the queued task with |handle| to the end of all values with priority
  // |priority| and returns the updated handle.
  // Invalidates |handle|. No-op if priority did not change.
  Handle ChangePriority(const Handle& handle, Priority priority);

  // Calls `MaybeRunNext(true)` in loop.
  void RunAndRemoveAll();

  // Calls `MaybeRunNext(false)` in loop.
  void RunAll();

 private:
  // Attempts to run the task with |handle|.
  // Returns true if successful. If so  the |handle| becomes invalid.
  bool MaybeRun(const Handle& handle);

  // Attempts to run the next highest priority task in the queue. Returns
  // true if successful, and all handles to that task become invalid.
  bool MaybeRunNext();

  // Queue for tasks that need to wait for a spare slot.
  PrioritizedList<RepeatingTask> queue_;
};

}  // namespace basic
