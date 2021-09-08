// mojo/public/tools/fuzzers/fuzz.mojom-blink-forward.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_TOOLS_FUZZERS_FUZZ_MOJOM_BLINK_FORWARD_H_
#define MOJO_PUBLIC_TOOLS_FUZZERS_FUZZ_MOJOM_BLINK_FORWARD_H_

#include <stdint.h>

#include "mojo/public/cpp/bindings/struct_forward.h"

#include "mojo/public/cpp/bindings/deprecated_interface_types_forward.h"


#include "mojo/public/interfaces/bindings/native_struct.mojom-forward.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace fuzz {
namespace mojom {

enum class FuzzEnum : int32_t;
class FuzzDummyInterfaceInterfaceBase;
class FuzzInterfaceInterfaceBase;
}  // namespace fuzz
}  // namespace mojom


namespace fuzz {
namespace mojom {
namespace blink {
// Aliases for definition in the parent namespace.
using FuzzEnum = FuzzEnum;
using FuzzDummyInterfaceInterfaceBase = FuzzDummyInterfaceInterfaceBase;
using FuzzInterfaceInterfaceBase = FuzzInterfaceInterfaceBase;
class FuzzDummyStruct;
using FuzzDummyStructPtr = mojo::InlinedStructPtr<FuzzDummyStruct>;

class FuzzStruct;
using FuzzStructPtr = mojo::StructPtr<FuzzStruct>;

class FuzzUnion;

typedef mojo::StructPtr<FuzzUnion> FuzzUnionPtr;

class FuzzDummyInterface;

// @generated_from: fuzz.mojom.FuzzDummyInterface
using FuzzDummyInterfacePtr = mojo::InterfacePtr<FuzzDummyInterface>;
using FuzzDummyInterfacePtrInfo = mojo::InterfacePtrInfo<FuzzDummyInterface>;

// @generated_from: fuzz.mojom.FuzzDummyInterface
using FuzzDummyInterfaceRequest = mojo::InterfaceRequest<FuzzDummyInterface>;
using FuzzDummyInterfaceAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<FuzzDummyInterface>;

// @generated_from: fuzz.mojom.FuzzDummyInterface
using FuzzDummyInterfaceAssociatedRequest =
    mojo::AssociatedInterfaceRequest<FuzzDummyInterface>;

class FuzzInterface;

// @generated_from: fuzz.mojom.FuzzInterface
using FuzzInterfacePtr = mojo::InterfacePtr<FuzzInterface>;
using FuzzInterfacePtrInfo = mojo::InterfacePtrInfo<FuzzInterface>;

// @generated_from: fuzz.mojom.FuzzInterface
using FuzzInterfaceRequest = mojo::InterfaceRequest<FuzzInterface>;
using FuzzInterfaceAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<FuzzInterface>;

// @generated_from: fuzz.mojom.FuzzInterface
using FuzzInterfaceAssociatedRequest =
    mojo::AssociatedInterfaceRequest<FuzzInterface>;




}  // namespace blink
}  // namespace mojom
}  // namespace fuzz

#endif  // MOJO_PUBLIC_TOOLS_FUZZERS_FUZZ_MOJOM_BLINK_FORWARD_H_