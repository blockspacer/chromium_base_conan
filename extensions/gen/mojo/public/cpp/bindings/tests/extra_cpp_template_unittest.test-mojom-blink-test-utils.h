// mojo/public/cpp/bindings/tests/extra_cpp_template_unittest.test-mojom-blink-test-utils.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_TESTS_EXTRA_CPP_TEMPLATE_UNITTEST_TEST_MOJOM_BLINK_TEST_UTILS_H_
#define MOJO_PUBLIC_CPP_BINDINGS_TESTS_EXTRA_CPP_TEMPLATE_UNITTEST_TEST_MOJOM_BLINK_TEST_UTILS_H_

#include "mojo/public/cpp/bindings/tests/extra_cpp_template_unittest.test-mojom-blink.h"


namespace mojo {
namespace test {
namespace extra_cpp_template_unittest {
namespace mojom {
namespace blink {


class  ExtraCppInterfaceInterceptorForTesting : public ExtraCppInterface {
  virtual ExtraCppInterface* GetForwardingInterface() = 0;
};
class  ExtraCppInterfaceAsyncWaiter {
 public:
  explicit ExtraCppInterfaceAsyncWaiter(ExtraCppInterface* proxy);
  ~ExtraCppInterfaceAsyncWaiter();

 private:
  ExtraCppInterface* const proxy_;

  DISALLOW_COPY_AND_ASSIGN(ExtraCppInterfaceAsyncWaiter);
};




}  // namespace blink
}  // namespace mojom
}  // namespace extra_cpp_template_unittest
}  // namespace test
}  // namespace mojo

#endif  // MOJO_PUBLIC_CPP_BINDINGS_TESTS_EXTRA_CPP_TEMPLATE_UNITTEST_TEST_MOJOM_BLINK_TEST_UTILS_H_