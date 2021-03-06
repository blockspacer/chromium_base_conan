// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/containers/any_internal.h"

using namespace base;

namespace basic {
namespace internal {

AnyInternal::~AnyInternal() {
  reset();
}

void AnyInternal::reset() noexcept {
  if (!has_value())
    return;

  type_ops_->delete_fn_ptr(this);
  type_ops_ = nullptr;
}

}  // namespace internal
}  // namespace basic
