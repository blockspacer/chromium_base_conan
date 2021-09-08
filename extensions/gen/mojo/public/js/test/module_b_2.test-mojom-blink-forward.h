// mojo/public/js/test/module_b_2.test-mojom-blink-forward.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_BLINK_FORWARD_H_
#define MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_BLINK_FORWARD_H_



#include "mojo/public/cpp/bindings/struct_forward.h"

#include "mojo/public/cpp/bindings/deprecated_interface_types_forward.h"


#include "mojo/public/interfaces/bindings/native_struct.mojom-forward.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace module_b {
class TestInterfaceInterfaceBase;
}  // namespace module_b


namespace module_b {
namespace blink {
// Aliases for definition in the parent namespace.
using TestInterfaceInterfaceBase = TestInterfaceInterfaceBase;
class TestStructB2;
using TestStructB2Ptr = mojo::StructPtr<TestStructB2>;

class TestInterface;

// @generated_from: module_b.TestInterface
using TestInterfacePtr = mojo::InterfacePtr<TestInterface>;
using TestInterfacePtrInfo = mojo::InterfacePtrInfo<TestInterface>;

// @generated_from: module_b.TestInterface
using TestInterfaceRequest = mojo::InterfaceRequest<TestInterface>;
using TestInterfaceAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<TestInterface>;

// @generated_from: module_b.TestInterface
using TestInterfaceAssociatedRequest =
    mojo::AssociatedInterfaceRequest<TestInterface>;




}  // namespace blink
}  // namespace module_b

#endif  // MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_BLINK_FORWARD_H_