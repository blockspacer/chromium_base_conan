// mojo/public/interfaces/bindings/tests/test_constants.mojom-blink-forward.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_CONSTANTS_MOJOM_BLINK_FORWARD_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_CONSTANTS_MOJOM_BLINK_FORWARD_H_



#include "mojo/public/cpp/bindings/struct_forward.h"

#include "mojo/public/cpp/bindings/deprecated_interface_types_forward.h"


#include "mojo/public/interfaces/bindings/native_struct.mojom-forward.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo {
namespace test {
class InterfaceWithConstantsInterfaceBase;
}  // namespace mojo
}  // namespace test


namespace mojo {
namespace test {
namespace blink {
// Aliases for definition in the parent namespace.
using InterfaceWithConstantsInterfaceBase = InterfaceWithConstantsInterfaceBase;

// @generated_from: mojo.test.kBoolValue
constexpr bool kBoolValue = true;

// @generated_from: mojo.test.kInt8Value
constexpr int8_t kInt8Value = -2;

// @generated_from: mojo.test.kUint8Value
constexpr uint8_t kUint8Value = 128U;

// @generated_from: mojo.test.kInt16Value
constexpr int16_t kInt16Value = -233;

// @generated_from: mojo.test.kUint16Value
constexpr uint16_t kUint16Value = 44204U;

// @generated_from: mojo.test.kInt32Value
constexpr int32_t kInt32Value = -44204;

// @generated_from: mojo.test.kUint32Value
constexpr uint32_t kUint32Value = 4294967295U;

// @generated_from: mojo.test.kInt64Value
constexpr int64_t kInt64Value = -9223372036854775807;

// @generated_from: mojo.test.kUint64Value
constexpr uint64_t kUint64Value = 9999999999999999999ULL;

// @generated_from: mojo.test.kDoubleValue
constexpr double kDoubleValue = 3.14159;

// @generated_from: mojo.test.kDoubleInfinity
constexpr double kDoubleInfinity = std::numeric_limits<double>::infinity();

// @generated_from: mojo.test.kDoubleNegativeInfinity
constexpr double kDoubleNegativeInfinity = -std::numeric_limits<double>::infinity();

// @generated_from: mojo.test.kDoubleNaN
constexpr double kDoubleNaN = std::numeric_limits<double>::quiet_NaN();

// @generated_from: mojo.test.kFloatValue
constexpr float kFloatValue = 2.71828f;

// @generated_from: mojo.test.kFloatInfinity
constexpr float kFloatInfinity = std::numeric_limits<float>::infinity();

// @generated_from: mojo.test.kFloatNegativeInfinity
constexpr float kFloatNegativeInfinity = -std::numeric_limits<float>::infinity();

// @generated_from: mojo.test.kFloatNaN
constexpr float kFloatNaN = std::numeric_limits<float>::quiet_NaN();

// @generated_from: mojo.test.kStringValue
extern const char kStringValue[];
class StructWithConstants;
using StructWithConstantsPtr = mojo::InlinedStructPtr<StructWithConstants>;

class InterfaceWithConstants;

// @generated_from: mojo.test.InterfaceWithConstants
using InterfaceWithConstantsPtr = mojo::InterfacePtr<InterfaceWithConstants>;
using InterfaceWithConstantsPtrInfo = mojo::InterfacePtrInfo<InterfaceWithConstants>;

// @generated_from: mojo.test.InterfaceWithConstants
using InterfaceWithConstantsRequest = mojo::InterfaceRequest<InterfaceWithConstants>;
using InterfaceWithConstantsAssociatedPtrInfo =
    mojo::AssociatedInterfacePtrInfo<InterfaceWithConstants>;

// @generated_from: mojo.test.InterfaceWithConstants
using InterfaceWithConstantsAssociatedRequest =
    mojo::AssociatedInterfaceRequest<InterfaceWithConstants>;




}  // namespace blink
}  // namespace test
}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_CONSTANTS_MOJOM_BLINK_FORWARD_H_