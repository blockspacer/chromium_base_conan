// mojo/public/interfaces/bindings/tests/regression_tests.mojom-forward.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_REGRESSION_TESTS_MOJOM_FORWARD_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_REGRESSION_TESTS_MOJOM_FORWARD_H_

#include <stdint.h>

#include "mojo/public/cpp/bindings/struct_forward.h"

#include "mojo/public/cpp/bindings/deprecated_interface_types_forward.h"


#include "mojo/public/interfaces/bindings/native_struct.mojom-forward.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif




namespace regression_tests {
class EdgeDataView;

class VertexDataView;

class EmptyStructDataView;

class ADataView;

class BDataView;

class HandlesNameCollisionStructDataView;

class HandlesHandleNameCollisionStructDataView;

class HandlesUnionNameCollisionStructDataView;

class HandlesNameCollisionUnionDataView;

enum class EnumWithReference : int32_t;

enum class EnumWithLowercase : int32_t;

enum class EnumWithNumbers : int32_t;

enum class EnumWithK : int32_t;
class Edge;
using EdgePtr = mojo::StructPtr<Edge>;

class Vertex;
using VertexPtr = mojo::StructPtr<Vertex>;

class EmptyStruct;
using EmptyStructPtr = mojo::InlinedStructPtr<EmptyStruct>;

class A;
using APtr = mojo::StructPtr<A>;

class B;
using BPtr = mojo::StructPtr<B>;

class HandlesNameCollisionStruct;
using HandlesNameCollisionStructPtr = mojo::StructPtr<HandlesNameCollisionStruct>;

class HandlesHandleNameCollisionStruct;
using HandlesHandleNameCollisionStructPtr = mojo::StructPtr<HandlesHandleNameCollisionStruct>;

class HandlesUnionNameCollisionStruct;
using HandlesUnionNameCollisionStructPtr = mojo::StructPtr<HandlesUnionNameCollisionStruct>;

class HandlesNameCollisionUnion;

typedef mojo::InlinedStructPtr<HandlesNameCollisionUnion> HandlesNameCollisionUnionPtr;

class CheckMethodWithEmptyResponse;

// @generated_from: regression_tests.CheckMethodWithEmptyResponse
using CheckMethodWithEmptyResponsePtr = mojo::InterfacePtr<CheckMethodWithEmptyResponse>;
using CheckMethodWithEmptyResponsePtrInfo = mojo::InterfacePtrInfo<CheckMethodWithEmptyResponse>;

// @generated_from: regression_tests.CheckMethodWithEmptyResponse
using CheckMethodWithEmptyResponseRequest = mojo::InterfaceRequest<CheckMethodWithEmptyResponse>;
using CheckMethodWithEmptyResponseAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<CheckMethodWithEmptyResponse>;

// @generated_from: regression_tests.CheckMethodWithEmptyResponse
using CheckMethodWithEmptyResponseAssociatedRequest =
    mojo::AssociatedInterfaceRequest<CheckMethodWithEmptyResponse>;

class CheckNameCollision;

// @generated_from: regression_tests.CheckNameCollision
using CheckNameCollisionPtr = mojo::InterfacePtr<CheckNameCollision>;
using CheckNameCollisionPtrInfo = mojo::InterfacePtrInfo<CheckNameCollision>;

// @generated_from: regression_tests.CheckNameCollision
using CheckNameCollisionRequest = mojo::InterfaceRequest<CheckNameCollision>;
using CheckNameCollisionAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<CheckNameCollision>;

// @generated_from: regression_tests.CheckNameCollision
using CheckNameCollisionAssociatedRequest =
    mojo::AssociatedInterfaceRequest<CheckNameCollision>;

class HandlesNameCollisionInterface;

// @generated_from: regression_tests.HandlesNameCollisionInterface
using HandlesNameCollisionInterfacePtr = mojo::InterfacePtr<HandlesNameCollisionInterface>;
using HandlesNameCollisionInterfacePtrInfo = mojo::InterfacePtrInfo<HandlesNameCollisionInterface>;

// @generated_from: regression_tests.HandlesNameCollisionInterface
using HandlesNameCollisionInterfaceRequest = mojo::InterfaceRequest<HandlesNameCollisionInterface>;
using HandlesNameCollisionInterfaceAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<HandlesNameCollisionInterface>;

// @generated_from: regression_tests.HandlesNameCollisionInterface
using HandlesNameCollisionInterfaceAssociatedRequest =
    mojo::AssociatedInterfaceRequest<HandlesNameCollisionInterface>;




}  // namespace regression_tests

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_REGRESSION_TESTS_MOJOM_FORWARD_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMjE3MCwgImJlZ2luIjogMjEzOSwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogInJlZ3Jlc3Npb25fdGVzdHMuQ2hlY2tNZXRob2RXaXRo
RW1wdHlSZXNwb25zZSJ9fSwgeyJlbmQiOiAyNDgzLCAiYmVnaW4iOiAyNDU1LCAiZWRnZSI6ICIl
L2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUi
OiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJs
YW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAicmVncmVzc2lvbl90ZXN0cy5DaGVja01l
dGhvZFdpdGhFbXB0eVJlc3BvbnNlIn19LCB7ImVuZCI6IDI5MDgsICJiZWdpbiI6IDI4ODcsICJl
ZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIs
ICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0v
c3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJyZWdyZXNzaW9uX3Rlc3Rz
LkNoZWNrTmFtZUNvbGxpc2lvbiJ9fSwgeyJlbmQiOiAzMTYxLCAiYmVnaW4iOiAzMTQzLCAiZWRn
ZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAi
dm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3Ny
YyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAicmVncmVzc2lvbl90ZXN0cy5D
aGVja05hbWVDb2xsaXNpb24ifX0sIHsiZW5kIjogMzU2OSwgImJlZ2luIjogMzUzNywgImVkZ2Ui
OiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZu
YW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMi
LCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogInJlZ3Jlc3Npb25fdGVzdHMuSGFu
ZGxlc05hbWVDb2xsaXNpb25JbnRlcmZhY2UifX0sIHsiZW5kIjogMzg4OCwgImJlZ2luIjogMzg1
OSwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZp
bmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJv
bWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogInJlZ3Jlc3Npb25f
dGVzdHMuSGFuZGxlc05hbWVDb2xsaXNpb25JbnRlcmZhY2UifX1dLCAidHlwZSI6ICJreXRoZTAi
fQ==
*/