// mojo/public/js/test/module_b_2.test-mojom-blink-test-utils.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_BLINK_TEST_UTILS_H_
#define MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_BLINK_TEST_UTILS_H_

#include "mojo/public/js/test/module_b_2.test-mojom-blink.h"


namespace module_b {
namespace blink {


class  TestInterfaceInterceptorForTesting : public TestInterface {
  virtual TestInterface* GetForwardingInterface() = 0;
  void PassA1(::module_a::blink::TestStructA1Ptr a1) override;
  void PassB1(::module_b::blink::TestStructB1Ptr b1) override;
  void PassB2(TestStructB2Ptr b2) override;
};
class  TestInterfaceAsyncWaiter {
 public:
  explicit TestInterfaceAsyncWaiter(TestInterface* proxy);
  ~TestInterfaceAsyncWaiter();

 private:
  TestInterface* const proxy_;

  DISALLOW_COPY_AND_ASSIGN(TestInterfaceAsyncWaiter);
};




}  // namespace blink
}  // namespace module_b

#endif  // MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_BLINK_TEST_UTILS_H_