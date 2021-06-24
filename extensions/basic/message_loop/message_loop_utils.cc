// Copyright 2015 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <basic/message_loop/message_loop_utils.h>

#include "base/cancelable_callback.h"
#include "base/threading/thread_task_runner_handle.h"
#include "base/bind.h"
#include "base/callback_helpers.h"
#include "base/location.h"

#include "base/test/scoped_run_loop_timeout.h"

using namespace base;

namespace basic {

void RunLoopRunUntil(base::TimeDelta timeout,
                     base::RepeatingCallback<bool()> terminate) {
  bool timeout_called = false;

  CancelableOnceClosure cancelable_timeout;

  cancelable_timeout.Reset(BindOnce([](bool* timeout_called) {
    *timeout_called = true;
  }, &timeout_called));

  ThreadTaskRunnerHandle::Get()->PostDelayedTask(
    FROM_HERE, cancelable_timeout.callback(), timeout);

  while (!timeout_called
         && (terminate.is_null() || !terminate.Run()))
  {
    base::RunLoop(base::RunLoop::Type::kNestableTasksAllowed).RunUntilIdle();
  }

  if (!timeout_called) {
    cancelable_timeout.Cancel();
  }
}

int RunLoopRunUntilIterations(int iterations,
                              base::RepeatingCallback<bool()> terminate) {
  int result;
  for (result = 0; result < iterations
                   && (terminate.is_null() || !terminate.Run()); result++)
  {
    base::RunLoop(base::RunLoop::Type::kNestableTasksAllowed).RunUntilIdle();
  }
  return result;
}

} // namespace basic
