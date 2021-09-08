// mojo/public/interfaces/bindings/tests/test_unions.mojom-forward.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_UNIONS_MOJOM_FORWARD_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_UNIONS_MOJOM_FORWARD_H_

#include <stdint.h>

#include "mojo/public/cpp/bindings/struct_forward.h"

#include "mojo/public/cpp/bindings/deprecated_interface_types_forward.h"


#include "mojo/public/interfaces/bindings/native_struct.mojom-forward.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif




namespace mojo {
namespace test {
class WrapperStructDataView;

class DummyStructDataView;

class SmallStructDataView;

class SmallStructNonNullableUnionDataView;

class SmallObjStructDataView;

class TryNonNullStructDataView;

class ImportedUnionStructDataView;

class PodUnionDataView;
class ObjectUnionDataView;
class HandleUnionDataView;
class OldUnionDataView;
class NewUnionDataView;
class ImportedUnionUnionDataView;
class UnionWithStringForFirstFieldDataView;

enum class AnEnum : int32_t;

enum class AnExtensibleEnum : int32_t;
class WrapperStruct;
using WrapperStructPtr = mojo::StructPtr<WrapperStruct>;

class DummyStruct;
using DummyStructPtr = mojo::InlinedStructPtr<DummyStruct>;

class SmallStruct;
using SmallStructPtr = mojo::StructPtr<SmallStruct>;

class SmallStructNonNullableUnion;
using SmallStructNonNullableUnionPtr = mojo::StructPtr<SmallStructNonNullableUnion>;

class SmallObjStruct;
using SmallObjStructPtr = mojo::StructPtr<SmallObjStruct>;

class TryNonNullStruct;
using TryNonNullStructPtr = mojo::StructPtr<TryNonNullStruct>;

class ImportedUnionStruct;
using ImportedUnionStructPtr = mojo::StructPtr<ImportedUnionStruct>;

class PodUnion;

typedef mojo::InlinedStructPtr<PodUnion> PodUnionPtr;

class ObjectUnion;

typedef mojo::StructPtr<ObjectUnion> ObjectUnionPtr;

class HandleUnion;

typedef mojo::StructPtr<HandleUnion> HandleUnionPtr;

class OldUnion;

typedef mojo::InlinedStructPtr<OldUnion> OldUnionPtr;

class NewUnion;

typedef mojo::InlinedStructPtr<NewUnion> NewUnionPtr;

class ImportedUnionUnion;

typedef mojo::StructPtr<ImportedUnionUnion> ImportedUnionUnionPtr;

class UnionWithStringForFirstField;

typedef mojo::StructPtr<UnionWithStringForFirstField> UnionWithStringForFirstFieldPtr;

class SmallCache;

// @generated_from: mojo.test.SmallCache
using SmallCachePtr = mojo::InterfacePtr<SmallCache>;
using SmallCachePtrInfo = mojo::InterfacePtrInfo<SmallCache>;

// @generated_from: mojo.test.SmallCache
using SmallCacheRequest = mojo::InterfaceRequest<SmallCache>;
using SmallCacheAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<SmallCache>;

// @generated_from: mojo.test.SmallCache
using SmallCacheAssociatedRequest =
    mojo::AssociatedInterfaceRequest<SmallCache>;

class UnionInterface;

// @generated_from: mojo.test.UnionInterface
using UnionInterfacePtr = mojo::InterfacePtr<UnionInterface>;
using UnionInterfacePtrInfo = mojo::InterfacePtrInfo<UnionInterface>;

// @generated_from: mojo.test.UnionInterface
using UnionInterfaceRequest = mojo::InterfaceRequest<UnionInterface>;
using UnionInterfaceAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<UnionInterface>;

// @generated_from: mojo.test.UnionInterface
using UnionInterfaceAssociatedRequest =
    mojo::AssociatedInterfaceRequest<UnionInterface>;




}  // namespace test
}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_UNIONS_MOJOM_FORWARD_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMjU3OCwgImJlZ2luIjogMjU2NSwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5TbWFsbENhY2hlIn19LCB7ImVuZCI6
IDI3NzYsICJiZWdpbiI6IDI3NjYsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAi
dHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdv
b2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25h
dHVyZSI6ICJtb2pvLnRlc3QuU21hbGxDYWNoZSJ9fSwgeyJlbmQiOiAzMDg1LCAiYmVnaW4iOiAz
MDY4LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2Rl
ZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2No
cm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0
LlVuaW9uSW50ZXJmYWNlIn19LCB7ImVuZCI6IDMzMDcsICJiZWdpbiI6IDMyOTMsICJlZGdlIjog
IiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFt
ZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwg
Imxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuVW5pb25JbnRlcmZh
Y2UifX1dLCAidHlwZSI6ICJreXRoZTAifQ==
*/