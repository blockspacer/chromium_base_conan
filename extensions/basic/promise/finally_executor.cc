// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/promise/finally_executor.h" // IWYU pragma: associated

#include "basic/rvalue_cast.h"

namespace base {
namespace internal {

FinallyExecutorCommon::FinallyExecutorCommon(
    internal::CallbackBase&& callback) noexcept
    : callback_(RVALUE_CAST(callback)) {}

FinallyExecutorCommon::~FinallyExecutorCommon() = default;

bool FinallyExecutorCommon::IsCancelled() const {
  return callback_.IsCancelled();
}

}  // namespace internal
}  // namespace base
