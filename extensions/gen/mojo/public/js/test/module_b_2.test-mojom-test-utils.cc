// mojo/public/js/test/module_b_2.test-mojom-test-utils.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif


#include "mojo/public/js/test/module_b_2.test-mojom-test-utils.h"

#include <utility>

#include "base/bind.h"
#include "base/run_loop.h"
#include "mojo/public/js/test/module_a.test-mojom.h"
#include "mojo/public/js/test/module_b_1.test-mojom.h"


#ifndef MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_JUMBO_H_
#define MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_JUMBO_H_
#endif


namespace module_b {


void TestInterfaceInterceptorForTesting::PassA1(::module_a::TestStructA1Ptr a1) {
  GetForwardingInterface()->PassA1(std::move(a1));
}
void TestInterfaceInterceptorForTesting::PassB1(::module_b::TestStructB1Ptr b1) {
  GetForwardingInterface()->PassB1(std::move(b1));
}
void TestInterfaceInterceptorForTesting::PassB2(TestStructB2Ptr b2) {
  GetForwardingInterface()->PassB2(std::move(b2));
}
TestInterfaceAsyncWaiter::TestInterfaceAsyncWaiter(
    TestInterface* proxy) : proxy_(proxy) {}

TestInterfaceAsyncWaiter::~TestInterfaceAsyncWaiter() = default;






}  // namespace module_b

#if defined(__clang__)
#pragma clang diagnostic pop
#endif