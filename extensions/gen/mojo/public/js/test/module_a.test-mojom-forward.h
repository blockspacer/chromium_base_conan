// mojo/public/js/test/module_a.test-mojom-forward.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_JS_TEST_MODULE_A_TEST_MOJOM_FORWARD_H_
#define MOJO_PUBLIC_JS_TEST_MODULE_A_TEST_MOJOM_FORWARD_H_

#include <stdint.h>

#include "mojo/public/cpp/bindings/struct_forward.h"

#include "mojo/public/cpp/bindings/deprecated_interface_types_forward.h"


#include "mojo/public/interfaces/bindings/native_struct.mojom-forward.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif




namespace module_a {
class TestStructA1DataView;

class TestStructA2DataView;


enum class ModuleEnum : int32_t;

enum class TestStructA2_NestedEnum : int32_t;

enum class ParentInterface_NestedEnum : int32_t;
class TestStructA1;
using TestStructA1Ptr = mojo::InlinedStructPtr<TestStructA1>;

class TestStructA2;
using TestStructA2Ptr = mojo::StructPtr<TestStructA2>;

class ParentInterface;

// @generated_from: module_a.ParentInterface
using ParentInterfacePtr = mojo::InterfacePtr<ParentInterface>;
using ParentInterfacePtrInfo = mojo::InterfacePtrInfo<ParentInterface>;

// @generated_from: module_a.ParentInterface
using ParentInterfaceRequest = mojo::InterfaceRequest<ParentInterface>;
using ParentInterfaceAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<ParentInterface>;

// @generated_from: module_a.ParentInterface
using ParentInterfaceAssociatedRequest =
    mojo::AssociatedInterfaceRequest<ParentInterface>;




}  // namespace module_a

#endif  // MOJO_PUBLIC_JS_TEST_MODULE_A_TEST_MOJOM_FORWARD_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTE3MSwgImJlZ2luIjogMTE1MywgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9hLlBhcmVudEludGVyZmFjZSJ9fSwgeyJl
bmQiOiAxMzk4LCAiYmVnaW4iOiAxMzgzLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVz
IiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1
bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJz
aWduYXR1cmUiOiAibW9kdWxlX2EuUGFyZW50SW50ZXJmYWNlIn19XSwgInR5cGUiOiAia3l0aGUw
In0=
*/