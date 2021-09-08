// mojo/public/cpp/test/module.test-mojom-blink-test-utils.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif


#include "mojo/public/cpp/test/module.test-mojom-blink-test-utils.h"

#include <utility>

#include "base/bind.h"
#include "base/run_loop.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"


#ifndef MOJO_PUBLIC_CPP_TEST_MODULE_TEST_MOJOM_BLINK_JUMBO_H_
#define MOJO_PUBLIC_CPP_TEST_MODULE_TEST_MOJOM_BLINK_JUMBO_H_
#endif


namespace test_module {
namespace blink {


void InterfaceInterceptorForTesting::DoSomething() {
  GetForwardingInterface()->DoSomething();
}
void InterfaceInterceptorForTesting::DoSomethingElse(StructPtr s, DoSomethingElseCallback callback) {
  GetForwardingInterface()->DoSomethingElse(std::move(s), std::move(callback));
}
InterfaceAsyncWaiter::InterfaceAsyncWaiter(
    Interface* proxy) : proxy_(proxy) {}

InterfaceAsyncWaiter::~InterfaceAsyncWaiter() = default;

void InterfaceAsyncWaiter::DoSomethingElse(
    StructPtr s, GlobalEnum* out_e) {
  base::RunLoop loop;
  proxy_->DoSomethingElse(std::move(s),
      base::BindOnce(
          [](base::RunLoop* loop,
             GlobalEnum* out_e
,
             GlobalEnum e) {*out_e = std::move(e);
            loop->Quit();
          },
          &loop,
          out_e));
  loop.Run();
}





}  // namespace blink
}  // namespace test_module

#if defined(__clang__)
#pragma clang diagnostic pop
#endif