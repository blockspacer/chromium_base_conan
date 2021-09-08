// mojo/public/mojom/base/binder.mojom-blink-test-utils.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_MOJOM_BASE_BINDER_MOJOM_BLINK_TEST_UTILS_H_
#define MOJO_PUBLIC_MOJOM_BASE_BINDER_MOJOM_BLINK_TEST_UTILS_H_

#include "mojo/public/mojom/base/binder.mojom-blink.h"
#include "base/component_export.h"


namespace mojo_base {
namespace mojom {
namespace blink {


class COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) BinderInterceptorForTesting : public Binder {
  virtual Binder* GetForwardingInterface() = 0;
  void Bind(::mojo::GenericPendingReceiver receiver) override;
};
class COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) BinderAsyncWaiter {
 public:
  explicit BinderAsyncWaiter(Binder* proxy);
  ~BinderAsyncWaiter();

 private:
  Binder* const proxy_;

  DISALLOW_COPY_AND_ASSIGN(BinderAsyncWaiter);
};




}  // namespace blink
}  // namespace mojom
}  // namespace mojo_base

#endif  // MOJO_PUBLIC_MOJOM_BASE_BINDER_MOJOM_BLINK_TEST_UTILS_H_