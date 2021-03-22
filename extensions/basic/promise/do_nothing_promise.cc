// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/promise/do_nothing_promise.h" // IWYU pragma: associated

namespace base {

DoNothingPromiseBuilder::operator WrappedPromise() const {
  return WrappedPromise(internal::NoOpPromiseExecutor::Create(
      from_here, can_resolve, can_reject, reject_policy));
}

DoNothingPromiseBuilder::operator scoped_refptr<internal::AbstractPromise>()
    const {
  return WrappedPromise(internal::NoOpPromiseExecutor::Create(
                            from_here, can_resolve, can_reject, reject_policy))
      .TakeForTesting();
}

}  // namespace base
