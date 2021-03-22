// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/containers/prioritized_repeating_task_list.h" // IWYU pragma: associated

#include "base/logging.h"

namespace basic {

PrioritizedRepeatingTaskList::PrioritizedRepeatingTaskList(const Priority num_priorities)
    : queue_(num_priorities)
{}

PrioritizedRepeatingTaskList::~PrioritizedRepeatingTaskList() = default;

PrioritizedRepeatingTaskList::Handle PrioritizedRepeatingTaskList::Add(
    RepeatingTask task, Priority priority) {
  DCHECK(task);
  DCHECK_LT(priority, num_priorities());
  return queue_.Insert(task, priority);
}

PrioritizedRepeatingTaskList::Handle PrioritizedRepeatingTaskList::AddAtHead(
    RepeatingTask task, Priority priority) {
  DCHECK(task);
  DCHECK_LT(priority, num_priorities());
  return queue_.InsertAtFront(task, priority);
}

void PrioritizedRepeatingTaskList::Cancel(const Handle& handle) {
  queue_.Erase(handle);
}

base::Optional<PrioritizedRepeatingTaskList::RepeatingTask>
  PrioritizedRepeatingTaskList::EvictOldestLowest()
{
  Handle handle = queue_.FirstMin();
  if (handle.is_null())
    return base::nullopt;
  RepeatingTask task = handle.value();
  Cancel(handle);
  return task;
}

PrioritizedRepeatingTaskList::Handle PrioritizedRepeatingTaskList::ChangePriority(
    const Handle& handle, Priority priority) {
  DCHECK(!handle.is_null());
  DCHECK_LT(priority, num_priorities());

  if (handle.priority() == priority)
    return handle;

  RepeatingTask task = handle.value();
  queue_.Erase(handle);
  return queue_.Insert(task, priority);
}

bool PrioritizedRepeatingTaskList::MaybeRun(const Handle& handle)
{
  RepeatingTask task = handle.value();
  DCHECK(task);
  if (!task) {
    return false;
  }
  task.Run();
  queue_.Erase(handle);
  return true;
}

bool PrioritizedRepeatingTaskList::MaybeRunNext() {
  Handle handle = queue_.FirstMax();
  if (handle.is_null()) {
    DCHECK_EQ(0u, queue_.size());
    return false;
  }
  return MaybeRun(handle);
}

void PrioritizedRepeatingTaskList::RunAndRemoveAll() {
  // Start pending tasks
  while (true) {
    if (!MaybeRunNext())
      break;
  }
}

void PrioritizedRepeatingTaskList::RunAll() {
  // Start pending tasks
  const size_t cached_size = queue_.size();
  Handle current = queue_.FirstMax();
  for (size_t i = 0; i < cached_size; ++i) {
    DCHECK(!current.is_null());
    Handle next = queue_.GetNextTowardsLastMin(current);
    current.value().Run();
    current = next;
  }
}

}  // namespace basic
