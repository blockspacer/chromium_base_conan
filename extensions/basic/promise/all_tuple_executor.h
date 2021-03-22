// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <tuple>

#include "basic/promise/abstract_promise.h"
#include "basic/promise/helpers.h"

namespace base {
namespace internal {

// For Promises::All(Promise<Ts>... promises)
template <typename ResolveTuple, typename RejectType>
class AllTuplePromiseExecutor {
 public:
  using RejectT = Rejected<RejectType>;

  bool IsCancelled() const { return false; }

  static constexpr PromiseExecutor::PrerequisitePolicy kPrerequisitePolicy =
      PromiseExecutor::PrerequisitePolicy::kAll;

  void Execute(AbstractPromise* promise) {
    // All is rejected if any prerequisites are rejected.
    AbstractPromise* first_settled = promise->GetFirstSettledPrerequisite();
    if (first_settled && first_settled->IsRejected()) {
      AllPromiseRejectHelper<RejectT>::Reject(promise, first_settled);
      return;
    }

    const std::vector<DependentList::Node>* prerequisite_list =
        promise->prerequisite_list();
    DCHECK(prerequisite_list);
    TupleConstructor<ResolveTuple>::ConstructResolvedTuple(prerequisite_list, promise);
  }

#if DCHECK_IS_ON()
  PromiseExecutor::ArgumentPassingType ResolveArgumentPassingType() const {
    return UseMoveSemantics<ResolveTuple>::argument_passing_type;
  }

  PromiseExecutor::ArgumentPassingType RejectArgumentPassingType() const {
    return UseMoveSemantics<RejectType>::argument_passing_type;
  }

  bool CanResolve() const { return TupleCanResolveHelper<ResolveTuple>::value; }

  bool CanReject() const { return !std::is_same<RejectType, NoReject>::value; }
#endif
};

}  // namespace internal
}  // namespace base
