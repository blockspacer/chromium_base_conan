// mojo/public/interfaces/bindings/tests/test_associated_interfaces.mojom-blink-forward.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_ASSOCIATED_INTERFACES_MOJOM_BLINK_FORWARD_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_ASSOCIATED_INTERFACES_MOJOM_BLINK_FORWARD_H_



#include "mojo/public/cpp/bindings/struct_forward.h"

#include "mojo/public/cpp/bindings/deprecated_interface_types_forward.h"


#include "mojo/public/interfaces/bindings/native_struct.mojom-forward.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo {
namespace test {
class FooInterfaceInterfaceBase;
class InterfacePassesAssociatedInterfaceBase;
class IntegerSenderInterfaceBase;
class StringSenderInterfaceBase;
class IntegerSenderConnectionInterfaceBase;
class IntegerSenderConnectionAtBothEndsInterfaceBase;
class SenderConnectionInterfaceBase;
class AssociatedPingProviderInterfaceBase;
class AssociatedPingProviderProviderInterfaceBase;
}  // namespace mojo
}  // namespace test


namespace mojo {
namespace test {
namespace blink {
// Aliases for definition in the parent namespace.
using FooInterfaceInterfaceBase = FooInterfaceInterfaceBase;
using InterfacePassesAssociatedInterfaceBase = InterfacePassesAssociatedInterfaceBase;
using IntegerSenderInterfaceBase = IntegerSenderInterfaceBase;
using StringSenderInterfaceBase = StringSenderInterfaceBase;
using IntegerSenderConnectionInterfaceBase = IntegerSenderConnectionInterfaceBase;
using IntegerSenderConnectionAtBothEndsInterfaceBase = IntegerSenderConnectionAtBothEndsInterfaceBase;
using SenderConnectionInterfaceBase = SenderConnectionInterfaceBase;
using AssociatedPingProviderInterfaceBase = AssociatedPingProviderInterfaceBase;
using AssociatedPingProviderProviderInterfaceBase = AssociatedPingProviderProviderInterfaceBase;
class StructContainsAssociated;
using StructContainsAssociatedPtr = mojo::StructPtr<StructContainsAssociated>;

class UnionContainsAssociated;

typedef mojo::StructPtr<UnionContainsAssociated> UnionContainsAssociatedPtr;

class FooInterface;

// @generated_from: mojo.test.FooInterface
using FooInterfacePtr = mojo::InterfacePtr<FooInterface>;
using FooInterfacePtrInfo = mojo::InterfacePtrInfo<FooInterface>;

// @generated_from: mojo.test.FooInterface
using FooInterfaceRequest = mojo::InterfaceRequest<FooInterface>;
using FooInterfaceAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<FooInterface>;

// @generated_from: mojo.test.FooInterface
using FooInterfaceAssociatedRequest =
    mojo::AssociatedInterfaceRequest<FooInterface>;

class InterfacePassesAssociated;

// @generated_from: mojo.test.InterfacePassesAssociated
using InterfacePassesAssociatedPtr = mojo::InterfacePtr<InterfacePassesAssociated>;
using InterfacePassesAssociatedPtrInfo = mojo::InterfacePtrInfo<InterfacePassesAssociated>;

// @generated_from: mojo.test.InterfacePassesAssociated
using InterfacePassesAssociatedRequest = mojo::InterfaceRequest<InterfacePassesAssociated>;
using InterfacePassesAssociatedAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<InterfacePassesAssociated>;

// @generated_from: mojo.test.InterfacePassesAssociated
using InterfacePassesAssociatedAssociatedRequest =
    mojo::AssociatedInterfaceRequest<InterfacePassesAssociated>;

class IntegerSender;

// @generated_from: mojo.test.IntegerSender
using IntegerSenderPtr = mojo::InterfacePtr<IntegerSender>;
using IntegerSenderPtrInfo = mojo::InterfacePtrInfo<IntegerSender>;

// @generated_from: mojo.test.IntegerSender
using IntegerSenderRequest = mojo::InterfaceRequest<IntegerSender>;
using IntegerSenderAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<IntegerSender>;

// @generated_from: mojo.test.IntegerSender
using IntegerSenderAssociatedRequest =
    mojo::AssociatedInterfaceRequest<IntegerSender>;

class StringSender;

// @generated_from: mojo.test.StringSender
using StringSenderPtr = mojo::InterfacePtr<StringSender>;
using StringSenderPtrInfo = mojo::InterfacePtrInfo<StringSender>;

// @generated_from: mojo.test.StringSender
using StringSenderRequest = mojo::InterfaceRequest<StringSender>;
using StringSenderAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<StringSender>;

// @generated_from: mojo.test.StringSender
using StringSenderAssociatedRequest =
    mojo::AssociatedInterfaceRequest<StringSender>;

class IntegerSenderConnection;

// @generated_from: mojo.test.IntegerSenderConnection
using IntegerSenderConnectionPtr = mojo::InterfacePtr<IntegerSenderConnection>;
using IntegerSenderConnectionPtrInfo = mojo::InterfacePtrInfo<IntegerSenderConnection>;

// @generated_from: mojo.test.IntegerSenderConnection
using IntegerSenderConnectionRequest = mojo::InterfaceRequest<IntegerSenderConnection>;
using IntegerSenderConnectionAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<IntegerSenderConnection>;

// @generated_from: mojo.test.IntegerSenderConnection
using IntegerSenderConnectionAssociatedRequest =
    mojo::AssociatedInterfaceRequest<IntegerSenderConnection>;

class IntegerSenderConnectionAtBothEnds;

// @generated_from: mojo.test.IntegerSenderConnectionAtBothEnds
using IntegerSenderConnectionAtBothEndsPtr = mojo::InterfacePtr<IntegerSenderConnectionAtBothEnds>;
using IntegerSenderConnectionAtBothEndsPtrInfo = mojo::InterfacePtrInfo<IntegerSenderConnectionAtBothEnds>;

// @generated_from: mojo.test.IntegerSenderConnectionAtBothEnds
using IntegerSenderConnectionAtBothEndsRequest = mojo::InterfaceRequest<IntegerSenderConnectionAtBothEnds>;
using IntegerSenderConnectionAtBothEndsAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<IntegerSenderConnectionAtBothEnds>;

// @generated_from: mojo.test.IntegerSenderConnectionAtBothEnds
using IntegerSenderConnectionAtBothEndsAssociatedRequest =
    mojo::AssociatedInterfaceRequest<IntegerSenderConnectionAtBothEnds>;

class SenderConnection;

// @generated_from: mojo.test.SenderConnection
using SenderConnectionPtr = mojo::InterfacePtr<SenderConnection>;
using SenderConnectionPtrInfo = mojo::InterfacePtrInfo<SenderConnection>;

// @generated_from: mojo.test.SenderConnection
using SenderConnectionRequest = mojo::InterfaceRequest<SenderConnection>;
using SenderConnectionAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<SenderConnection>;

// @generated_from: mojo.test.SenderConnection
using SenderConnectionAssociatedRequest =
    mojo::AssociatedInterfaceRequest<SenderConnection>;

class AssociatedPingProvider;

// @generated_from: mojo.test.AssociatedPingProvider
using AssociatedPingProviderPtr = mojo::InterfacePtr<AssociatedPingProvider>;
using AssociatedPingProviderPtrInfo = mojo::InterfacePtrInfo<AssociatedPingProvider>;

// @generated_from: mojo.test.AssociatedPingProvider
using AssociatedPingProviderRequest = mojo::InterfaceRequest<AssociatedPingProvider>;
using AssociatedPingProviderAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<AssociatedPingProvider>;

// @generated_from: mojo.test.AssociatedPingProvider
using AssociatedPingProviderAssociatedRequest =
    mojo::AssociatedInterfaceRequest<AssociatedPingProvider>;

class AssociatedPingProviderProvider;

// @generated_from: mojo.test.AssociatedPingProviderProvider
using AssociatedPingProviderProviderPtr = mojo::InterfacePtr<AssociatedPingProviderProvider>;
using AssociatedPingProviderProviderPtrInfo = mojo::InterfacePtrInfo<AssociatedPingProviderProvider>;

// @generated_from: mojo.test.AssociatedPingProviderProvider
using AssociatedPingProviderProviderRequest = mojo::InterfaceRequest<AssociatedPingProviderProvider>;
using AssociatedPingProviderProviderAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<AssociatedPingProviderProvider>;

// @generated_from: mojo.test.AssociatedPingProviderProvider
using AssociatedPingProviderProviderAssociatedRequest =
    mojo::AssociatedInterfaceRequest<AssociatedPingProviderProvider>;




}  // namespace blink
}  // namespace test
}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_ASSOCIATED_INTERFACES_MOJOM_BLINK_FORWARD_H_