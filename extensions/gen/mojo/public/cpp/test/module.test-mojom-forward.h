// mojo/public/cpp/test/module.test-mojom-forward.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_TEST_MODULE_TEST_MOJOM_FORWARD_H_
#define MOJO_PUBLIC_CPP_TEST_MODULE_TEST_MOJOM_FORWARD_H_

#include <stdint.h>

#include "mojo/public/cpp/bindings/struct_forward.h"

#include "mojo/public/cpp/bindings/deprecated_interface_types_forward.h"


#include "mojo/public/interfaces/bindings/native_struct.mojom-forward.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif




namespace test_module {
class StructDataView;

class UnionDataView;

enum class GlobalEnum : int32_t;

enum class Struct_StructEnum : int32_t;

enum class Interface_InterfaceEnum : int32_t;

// @generated_from: test_module.GlobalConst
extern const char GlobalConst[];
class Struct;
using StructPtr = mojo::InlinedStructPtr<Struct>;

class Union;

typedef mojo::InlinedStructPtr<Union> UnionPtr;

class Interface;

// @generated_from: test_module.Interface
using InterfacePtr = mojo::InterfacePtr<Interface>;
using InterfacePtrInfo = mojo::InterfacePtrInfo<Interface>;

// @generated_from: test_module.Interface
using InterfaceRequest = mojo::InterfaceRequest<Interface>;
using InterfaceAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<Interface>;

// @generated_from: test_module.Interface
using InterfaceAssociatedRequest =
    mojo::AssociatedInterfaceRequest<Interface>;




}  // namespace test_module

#endif  // MOJO_PUBLIC_CPP_TEST_MODULE_TEST_MOJOM_FORWARD_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogOTcwLCAiYmVnaW4iOiA5NTksICJlZGdlIjogIiUva3l0aGUvZWRn
ZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVz
IjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjog
Im1vam9tIiwgInNpZ25hdHVyZSI6ICJ0ZXN0X21vZHVsZS5HbG9iYWxDb25zdCJ9fSwgeyJlbmQi
OiAxMTgwLCAiYmVnaW4iOiAxMTY4LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwg
InR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5n
b29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWdu
YXR1cmUiOiAidGVzdF9tb2R1bGUuSW50ZXJmYWNlIn19LCB7ImVuZCI6IDEzNzQsICJiZWdpbiI6
IDEzNjUsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3Jf
ZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20v
Y2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJ0ZXN0X21v
ZHVsZS5JbnRlcmZhY2UifX1dLCAidHlwZSI6ICJreXRoZTAifQ==
*/