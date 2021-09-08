// mojo/public/interfaces/bindings/tests/scoping.mojom-blink-forward.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SCOPING_MOJOM_BLINK_FORWARD_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SCOPING_MOJOM_BLINK_FORWARD_H_





#include "mojo/public/cpp/bindings/deprecated_interface_types_forward.h"



#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo {
namespace test {
class AInterfaceBase;
class BInterfaceBase;
class CInterfaceBase;
}  // namespace mojo
}  // namespace test


namespace mojo {
namespace test {
namespace blink {
// Aliases for definition in the parent namespace.
using AInterfaceBase = AInterfaceBase;
using BInterfaceBase = BInterfaceBase;
using CInterfaceBase = CInterfaceBase;
class A;

// @generated_from: mojo.test.A
using APtr = mojo::InterfacePtr<A>;
using APtrInfo = mojo::InterfacePtrInfo<A>;

// @generated_from: mojo.test.A
using ARequest = mojo::InterfaceRequest<A>;
using AAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<A>;

// @generated_from: mojo.test.A
using AAssociatedRequest =
    mojo::AssociatedInterfaceRequest<A>;

class B;

// @generated_from: mojo.test.B
using BPtr = mojo::InterfacePtr<B>;
using BPtrInfo = mojo::InterfacePtrInfo<B>;

// @generated_from: mojo.test.B
using BRequest = mojo::InterfaceRequest<B>;
using BAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<B>;

// @generated_from: mojo.test.B
using BAssociatedRequest =
    mojo::AssociatedInterfaceRequest<B>;

class C;

// @generated_from: mojo.test.C
using CPtr = mojo::InterfacePtr<C>;
using CPtrInfo = mojo::InterfacePtrInfo<C>;

// @generated_from: mojo.test.C
using CRequest = mojo::InterfaceRequest<C>;
using CAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<C>;

// @generated_from: mojo.test.C
using CAssociatedRequest =
    mojo::AssociatedInterfaceRequest<C>;




}  // namespace blink
}  // namespace test
}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SCOPING_MOJOM_BLINK_FORWARD_H_