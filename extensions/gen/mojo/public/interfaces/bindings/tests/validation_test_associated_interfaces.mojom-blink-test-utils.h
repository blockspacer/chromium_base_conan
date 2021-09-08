// mojo/public/interfaces/bindings/tests/validation_test_associated_interfaces.mojom-blink-test-utils.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_VALIDATION_TEST_ASSOCIATED_INTERFACES_MOJOM_BLINK_TEST_UTILS_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_VALIDATION_TEST_ASSOCIATED_INTERFACES_MOJOM_BLINK_TEST_UTILS_H_

#include "mojo/public/interfaces/bindings/tests/validation_test_associated_interfaces.mojom-blink.h"


namespace mojo {
namespace test {
namespace blink {


class  InterfaceXInterceptorForTesting : public InterfaceX {
  virtual InterfaceX* GetForwardingInterface() = 0;
};
class  InterfaceXAsyncWaiter {
 public:
  explicit InterfaceXAsyncWaiter(InterfaceX* proxy);
  ~InterfaceXAsyncWaiter();

 private:
  InterfaceX* const proxy_;

  DISALLOW_COPY_AND_ASSIGN(InterfaceXAsyncWaiter);
};


class  AssociatedConformanceTestInterfaceInterceptorForTesting : public AssociatedConformanceTestInterface {
  virtual AssociatedConformanceTestInterface* GetForwardingInterface() = 0;
  void Method0(::mojo::PendingAssociatedRemote<InterfaceX> param0) override;
  void Method1(::mojo::PendingAssociatedReceiver<InterfaceX> param0) override;
  void Method2(::mojo::PendingAssociatedRemote<InterfaceX> param0) override;
  void Method3(WTF::Vector<::mojo::PendingAssociatedRemote<InterfaceX>> param0) override;
};
class  AssociatedConformanceTestInterfaceAsyncWaiter {
 public:
  explicit AssociatedConformanceTestInterfaceAsyncWaiter(AssociatedConformanceTestInterface* proxy);
  ~AssociatedConformanceTestInterfaceAsyncWaiter();

 private:
  AssociatedConformanceTestInterface* const proxy_;

  DISALLOW_COPY_AND_ASSIGN(AssociatedConformanceTestInterfaceAsyncWaiter);
};




}  // namespace blink
}  // namespace test
}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_VALIDATION_TEST_ASSOCIATED_INTERFACES_MOJOM_BLINK_TEST_UTILS_H_