// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/containers/prioritized_job_dispatcher.h" // IWYU pragma: associated

#include "base/logging.h"

namespace basic {

PrioritizedJobDispatcher::Limits::Limits(Priority num_priorities,
                                      size_t total_jobs)
    : total_jobs(total_jobs), reserved_slots(num_priorities) {}

PrioritizedJobDispatcher::Limits::Limits(const Limits& other) = default;

PrioritizedJobDispatcher::Limits::~Limits() = default;

PrioritizedJobDispatcher::PrioritizedJobDispatcher(const Limits& limits)
    : queue_(limits.reserved_slots.size()),
      max_running_jobs_(limits.reserved_slots.size()) {
  SetLimits(limits);
}

PrioritizedJobDispatcher::~PrioritizedJobDispatcher() = default;

PrioritizedJobDispatcher::Handle PrioritizedJobDispatcher::Add(
    Job* job, Priority priority) {
  DCHECK(job);
  DCHECK_LT(priority, num_priorities());
  if (num_running_jobs_ < max_running_jobs_[priority]) {
    ++num_running_jobs_;
    job->Start();
    return Handle();
  }
  return queue_.Insert(job, priority);
}

PrioritizedJobDispatcher::Handle PrioritizedJobDispatcher::AddAtHead(
    Job* job, Priority priority) {
  DCHECK(job);
  DCHECK_LT(priority, num_priorities());
  if (num_running_jobs_ < max_running_jobs_[priority]) {
    ++num_running_jobs_;
    job->Start();
    return Handle();
  }
  return queue_.InsertAtFront(job, priority);
}

void PrioritizedJobDispatcher::Cancel(const Handle& handle) {
  queue_.Erase(handle);
}

PrioritizedJobDispatcher::Job* PrioritizedJobDispatcher::EvictOldestLowest() {
  Handle handle = queue_.FirstMin();
  if (handle.is_null())
    return nullptr;
  Job* job = handle.value();
  Cancel(handle);
  return job;
}

PrioritizedJobDispatcher::Handle PrioritizedJobDispatcher::ChangePriority(
    const Handle& handle, Priority priority) {
  DCHECK(!handle.is_null());
  DCHECK_LT(priority, num_priorities());
  DCHECK_GE(num_running_jobs_, max_running_jobs_[handle.priority()]) <<
      "Job should not be in queue when limits permit it to start.";

  if (handle.priority() == priority)
    return handle;

  if (MaybeDispatchJob(handle, priority))
    return Handle();
  Job* job = handle.value();
  queue_.Erase(handle);
  return queue_.Insert(job, priority);
}

void PrioritizedJobDispatcher::OnJobFinished() {
  DCHECK_GT(num_running_jobs_, 0u);
  --num_running_jobs_;
  MaybeDispatchNextJob();
}

PrioritizedJobDispatcher::Limits PrioritizedJobDispatcher::GetLimits() const {
  size_t num_priorities = max_running_jobs_.size();
  Limits limits(num_priorities, max_running_jobs_.back());

  // Calculate the number of jobs reserved for each priority and higher.  Leave
  // the number of jobs reserved for the lowest priority or higher as 0.
  for (size_t i = 1; i < num_priorities; ++i) {
    limits.reserved_slots[i] = max_running_jobs_[i] - max_running_jobs_[i - 1];
  }

  return limits;
}

void PrioritizedJobDispatcher::SetLimits(const Limits& limits) {
  DCHECK_EQ(queue_.num_priorities(), limits.reserved_slots.size());
  size_t total = 0;
  for (size_t i = 0; i < limits.reserved_slots.size(); ++i) {
    total += limits.reserved_slots[i];
    max_running_jobs_[i] = total;
  }
  // Unreserved slots are available for all priorities.
  DCHECK_LE(total, limits.total_jobs) << "sum(reserved_slots) <= total_jobs";
  size_t spare = limits.total_jobs - total;
  for (size_t i = limits.reserved_slots.size(); i > 0; --i) {
    max_running_jobs_[i - 1] += spare;
  }

  // Start pending jobs, if limits permit.
  while (true) {
    if (!MaybeDispatchNextJob())
      break;
  }
}

void PrioritizedJobDispatcher::SetLimitsToZero() {
  SetLimits(Limits(queue_.num_priorities(), 0));
}

bool PrioritizedJobDispatcher::MaybeDispatchJob(const Handle& handle,
                                             Priority job_priority) {
  DCHECK_LT(job_priority, num_priorities());
  if (num_running_jobs_ >= max_running_jobs_[job_priority])
    return false;
  Job* job = handle.value();
  queue_.Erase(handle);
  ++num_running_jobs_;
  job->Start();
  return true;
}

bool PrioritizedJobDispatcher::MaybeDispatchNextJob() {
  Handle handle = queue_.FirstMax();
  if (handle.is_null()) {
    DCHECK_EQ(0u, queue_.size());
    return false;
  }
  return MaybeDispatchJob(handle, handle.priority());
}

}  // namespace basic