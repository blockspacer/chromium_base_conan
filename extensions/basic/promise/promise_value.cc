// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/promise/promise_value.h" // IWYU pragma: associated
#include "basic/promise/abstract_promise.h"

namespace base {
namespace internal {

// static
void PromiseValueInternal::NopMove(PromiseValueInternal* src,
                                   PromiseValueInternal* dest) {}

// static
void PromiseValueInternal::NopDelete(PromiseValueInternal* src) {}

constexpr PromiseValueInternal::TypeOps PromiseValueInternal::null_type_;

}  // namespace internal
}  // namespace base
