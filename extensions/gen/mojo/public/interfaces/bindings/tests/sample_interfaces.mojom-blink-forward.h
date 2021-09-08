// mojo/public/interfaces/bindings/tests/sample_interfaces.mojom-blink-forward.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_INTERFACES_MOJOM_BLINK_FORWARD_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_INTERFACES_MOJOM_BLINK_FORWARD_H_

#include <stdint.h>



#include "mojo/public/cpp/bindings/deprecated_interface_types_forward.h"



#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace sample {

enum class Enum : int32_t;
class PingTestInterfaceBase;
class ProviderInterfaceBase;
class IntegerAccessorInterfaceBase;
class InterfaceFactoryInterfaceBase;
}  // namespace sample


namespace sample {
namespace blink {
// Aliases for definition in the parent namespace.
using Enum = Enum;
using PingTestInterfaceBase = PingTestInterfaceBase;
using ProviderInterfaceBase = ProviderInterfaceBase;
using IntegerAccessorInterfaceBase = IntegerAccessorInterfaceBase;
using InterfaceFactoryInterfaceBase = InterfaceFactoryInterfaceBase;

// @generated_from: sample.kLong
constexpr uint64_t kLong = 4405ULL;
class PingTest;

// @generated_from: sample.PingTest
using PingTestPtr = mojo::InterfacePtr<PingTest>;
using PingTestPtrInfo = mojo::InterfacePtrInfo<PingTest>;

// @generated_from: sample.PingTest
using PingTestRequest = mojo::InterfaceRequest<PingTest>;
using PingTestAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<PingTest>;

// @generated_from: sample.PingTest
using PingTestAssociatedRequest =
    mojo::AssociatedInterfaceRequest<PingTest>;

class Provider;

// @generated_from: sample.Provider
using ProviderPtr = mojo::InterfacePtr<Provider>;
using ProviderPtrInfo = mojo::InterfacePtrInfo<Provider>;

// @generated_from: sample.Provider
using ProviderRequest = mojo::InterfaceRequest<Provider>;
using ProviderAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<Provider>;

// @generated_from: sample.Provider
using ProviderAssociatedRequest =
    mojo::AssociatedInterfaceRequest<Provider>;

class IntegerAccessor;

// @generated_from: sample.IntegerAccessor
using IntegerAccessorPtr = mojo::InterfacePtr<IntegerAccessor>;
using IntegerAccessorPtrInfo = mojo::InterfacePtrInfo<IntegerAccessor>;

// @generated_from: sample.IntegerAccessor
using IntegerAccessorRequest = mojo::InterfaceRequest<IntegerAccessor>;
using IntegerAccessorAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<IntegerAccessor>;

// @generated_from: sample.IntegerAccessor
using IntegerAccessorAssociatedRequest =
    mojo::AssociatedInterfaceRequest<IntegerAccessor>;

class InterfaceFactory;

// @generated_from: sample.InterfaceFactory
using InterfaceFactoryPtr = mojo::InterfacePtr<InterfaceFactory>;
using InterfaceFactoryPtrInfo = mojo::InterfacePtrInfo<InterfaceFactory>;

// @generated_from: sample.InterfaceFactory
using InterfaceFactoryRequest = mojo::InterfaceRequest<InterfaceFactory>;
using InterfaceFactoryAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<InterfaceFactory>;

// @generated_from: sample.InterfaceFactory
using InterfaceFactoryAssociatedRequest =
    mojo::AssociatedInterfaceRequest<InterfaceFactory>;




}  // namespace blink
}  // namespace sample

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_INTERFACES_MOJOM_BLINK_FORWARD_H_