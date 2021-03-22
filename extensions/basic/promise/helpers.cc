// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/promise/helpers.h" // IWYU pragma: associated
#include "basic/promise/no_op_promise_executor.h"

#include "base/threading/sequenced_task_runner_handle.h"
#include "basic/rvalue_cast.h"
#include "base/callback_helpers.h"

namespace base {
namespace internal {

DoNothing ToCallbackBase(DoNothing task) {
  return task;
}

PassedPromise ConstructAbstractPromiseWithSinglePrerequisite(
    const scoped_refptr<TaskRunner>& task_runner,
    const Location& from_here,
    AbstractPromise* prerequisite,
    internal::PromiseExecutor::Data&& executor_data) noexcept {
  // Note |prerequisite| can legitimately be null when posting a promise chain
  // during shutdown.
  if (!prerequisite) {
    // Ensure the destructor for |executor_data| runs.
    PromiseExecutor dummy_executor(RVALUE_CAST(executor_data));
    return PassedPromise();
  }

  return PassedPromise(AbstractPromise::Create(
      task_runner, from_here,
      std::make_unique<AbstractPromise::AdjacencyList>(prerequisite),
      RejectPolicy::kMustCatchRejection,
      internal::DependentList::ConstructUnresolved(),
      RVALUE_CAST(executor_data)));
}

PassedPromise ConstructHereAbstractPromiseWithSinglePrerequisite(
    const Location& from_here,
    AbstractPromise* prerequisite,
    internal::PromiseExecutor::Data&& executor_data) noexcept {
  return ConstructAbstractPromiseWithSinglePrerequisite(
      SequencedTaskRunnerHandle::Get(), from_here, prerequisite,
      RVALUE_CAST(executor_data));
}

PassedPromise ConstructManualPromiseResolverPromise(const Location& from_here,
                                                    RejectPolicy reject_policy,
                                                    bool can_resolve,
                                                    bool can_reject) {
  return PassedPromise(AbstractPromise::CreateNoPrerequisitePromise(
      from_here, reject_policy, internal::DependentList::ConstructUnresolved(),
      internal::PromiseExecutor::Data(
          in_place_type_t<internal::NoOpPromiseExecutor>(), can_resolve,
          can_reject)));
}

}  // namespace internal
}  // namespace base
