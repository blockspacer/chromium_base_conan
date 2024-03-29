// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/core/weak_handle.h" // IWYU pragma: associated

#include <sstream>

#include "base/callback.h"
#include "base/threading/sequenced_task_runner_handle.h"

namespace basic {

namespace internal {

WeakHandleCoreBase::WeakHandleCoreBase()
    : owner_loop_task_runner_(base::SequencedTaskRunnerHandle::Get()) {}

bool WeakHandleCoreBase::IsOnOwnerThread() const {
  return owner_loop_task_runner_->RunsTasksInCurrentSequence();
}

WeakHandleCoreBase::~WeakHandleCoreBase() {}

void WeakHandleCoreBase::PostToOwnerThread(const base::Location& from_here,
                                           const base::Closure& fn) const {
  if (!owner_loop_task_runner_->PostTask(from_here, fn)) {
    DVLOG(1) << "Could not post task from " << from_here.ToString();
  }
}

}  // namespace internal

}  // namespace basic
