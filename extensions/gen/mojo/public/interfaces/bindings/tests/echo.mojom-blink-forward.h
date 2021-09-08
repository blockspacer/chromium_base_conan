// mojo/public/interfaces/bindings/tests/echo.mojom-blink-forward.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_ECHO_MOJOM_BLINK_FORWARD_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_ECHO_MOJOM_BLINK_FORWARD_H_





#include "mojo/public/cpp/bindings/deprecated_interface_types_forward.h"



#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace test {
namespace echo {
namespace mojom {
class EchoInterfaceBase;
}  // namespace test
}  // namespace echo
}  // namespace mojom


namespace test {
namespace echo {
namespace mojom {
namespace blink {
// Aliases for definition in the parent namespace.
using EchoInterfaceBase = EchoInterfaceBase;
class Echo;

// @generated_from: test.echo.mojom.Echo
using EchoPtr = mojo::InterfacePtr<Echo>;
using EchoPtrInfo = mojo::InterfacePtrInfo<Echo>;

// @generated_from: test.echo.mojom.Echo
using EchoRequest = mojo::InterfaceRequest<Echo>;
using EchoAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<Echo>;

// @generated_from: test.echo.mojom.Echo
using EchoAssociatedRequest =
    mojo::AssociatedInterfaceRequest<Echo>;




}  // namespace blink
}  // namespace mojom
}  // namespace echo
}  // namespace test

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_ECHO_MOJOM_BLINK_FORWARD_H_