// mojo/public/cpp/bindings/tests/interface_unittest.test-mojom-blink-test-utils.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_TESTS_INTERFACE_UNITTEST_TEST_MOJOM_BLINK_TEST_UTILS_H_
#define MOJO_PUBLIC_CPP_BINDINGS_TESTS_INTERFACE_UNITTEST_TEST_MOJOM_BLINK_TEST_UTILS_H_

#include "mojo/public/cpp/bindings/tests/interface_unittest.test-mojom-blink.h"


namespace mojo {
namespace test {
namespace interface_unittest {
namespace mojom {
namespace blink {


class  VeryCoolInterfaceInterceptorForTesting : public VeryCoolInterface {
  virtual VeryCoolInterface* GetForwardingInterface() = 0;
  void DoesNotMatter() override;
};
class  VeryCoolInterfaceAsyncWaiter {
 public:
  explicit VeryCoolInterfaceAsyncWaiter(VeryCoolInterface* proxy);
  ~VeryCoolInterfaceAsyncWaiter();

 private:
  VeryCoolInterface* const proxy_;

  DISALLOW_COPY_AND_ASSIGN(VeryCoolInterfaceAsyncWaiter);
};




}  // namespace blink
}  // namespace mojom
}  // namespace interface_unittest
}  // namespace test
}  // namespace mojo

#endif  // MOJO_PUBLIC_CPP_BINDINGS_TESTS_INTERFACE_UNITTEST_TEST_MOJOM_BLINK_TEST_UTILS_H_