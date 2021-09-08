// mojo/public/cpp/bindings/tests/flush_async_unittest.test-mojom-blink-forward.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_TESTS_FLUSH_ASYNC_UNITTEST_TEST_MOJOM_BLINK_FORWARD_H_
#define MOJO_PUBLIC_CPP_BINDINGS_TESTS_FLUSH_ASYNC_UNITTEST_TEST_MOJOM_BLINK_FORWARD_H_





#include "mojo/public/cpp/bindings/deprecated_interface_types_forward.h"



#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo {
namespace test {
namespace flush_async_unittest {
namespace mojom {
class WriterInterfaceBase;
class KeyValueStoreClientInterfaceBase;
class KeyValueStoreInterfaceBase;
class PingerInterfaceBase;
}  // namespace mojo
}  // namespace test
}  // namespace flush_async_unittest
}  // namespace mojom


namespace mojo {
namespace test {
namespace flush_async_unittest {
namespace mojom {
namespace blink {
// Aliases for definition in the parent namespace.
using WriterInterfaceBase = WriterInterfaceBase;
using KeyValueStoreClientInterfaceBase = KeyValueStoreClientInterfaceBase;
using KeyValueStoreInterfaceBase = KeyValueStoreInterfaceBase;
using PingerInterfaceBase = PingerInterfaceBase;
class Writer;

// @generated_from: mojo.test.flush_async_unittest.mojom.Writer
using WriterPtr = mojo::InterfacePtr<Writer>;
using WriterPtrInfo = mojo::InterfacePtrInfo<Writer>;

// @generated_from: mojo.test.flush_async_unittest.mojom.Writer
using WriterRequest = mojo::InterfaceRequest<Writer>;
using WriterAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<Writer>;

// @generated_from: mojo.test.flush_async_unittest.mojom.Writer
using WriterAssociatedRequest =
    mojo::AssociatedInterfaceRequest<Writer>;

class KeyValueStoreClient;

// @generated_from: mojo.test.flush_async_unittest.mojom.KeyValueStoreClient
using KeyValueStoreClientPtr = mojo::InterfacePtr<KeyValueStoreClient>;
using KeyValueStoreClientPtrInfo = mojo::InterfacePtrInfo<KeyValueStoreClient>;

// @generated_from: mojo.test.flush_async_unittest.mojom.KeyValueStoreClient
using KeyValueStoreClientRequest = mojo::InterfaceRequest<KeyValueStoreClient>;
using KeyValueStoreClientAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<KeyValueStoreClient>;

// @generated_from: mojo.test.flush_async_unittest.mojom.KeyValueStoreClient
using KeyValueStoreClientAssociatedRequest =
    mojo::AssociatedInterfaceRequest<KeyValueStoreClient>;

class KeyValueStore;

// @generated_from: mojo.test.flush_async_unittest.mojom.KeyValueStore
using KeyValueStorePtr = mojo::InterfacePtr<KeyValueStore>;
using KeyValueStorePtrInfo = mojo::InterfacePtrInfo<KeyValueStore>;

// @generated_from: mojo.test.flush_async_unittest.mojom.KeyValueStore
using KeyValueStoreRequest = mojo::InterfaceRequest<KeyValueStore>;
using KeyValueStoreAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<KeyValueStore>;

// @generated_from: mojo.test.flush_async_unittest.mojom.KeyValueStore
using KeyValueStoreAssociatedRequest =
    mojo::AssociatedInterfaceRequest<KeyValueStore>;

class Pinger;

// @generated_from: mojo.test.flush_async_unittest.mojom.Pinger
using PingerPtr = mojo::InterfacePtr<Pinger>;
using PingerPtrInfo = mojo::InterfacePtrInfo<Pinger>;

// @generated_from: mojo.test.flush_async_unittest.mojom.Pinger
using PingerRequest = mojo::InterfaceRequest<Pinger>;
using PingerAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<Pinger>;

// @generated_from: mojo.test.flush_async_unittest.mojom.Pinger
using PingerAssociatedRequest =
    mojo::AssociatedInterfaceRequest<Pinger>;




}  // namespace blink
}  // namespace mojom
}  // namespace flush_async_unittest
}  // namespace test
}  // namespace mojo

#endif  // MOJO_PUBLIC_CPP_BINDINGS_TESTS_FLUSH_ASYNC_UNITTEST_TEST_MOJOM_BLINK_FORWARD_H_