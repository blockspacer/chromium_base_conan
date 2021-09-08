// mojo/public/interfaces/bindings/tests/test_constants.mojom-blink.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "mojo/public/interfaces/bindings/tests/test_constants.mojom-blink.h"

#include <math.h>
#include <stdint.h>
#include <utility>

#include "base/hash/md5_constexpr.h"
#include "base/run_loop.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/common/task_annotator.h"
#include "base/trace_event/trace_event.h"
#include "mojo/public/cpp/bindings/lib/generated_code_util.h"
#include "mojo/public/cpp/bindings/lib/message_internal.h"
#include "mojo/public/cpp/bindings/lib/serialization_util.h"
#include "mojo/public/cpp/bindings/lib/unserialized_message_context.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/mojo_buildflags.h"
#include "mojo/public/interfaces/bindings/interface_control_messages.mojom.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/interfaces/bindings/tests/test_constants.mojom-params-data.h"
#include "mojo/public/interfaces/bindings/tests/test_constants.mojom-shared-message-ids.h"

#include "mojo/public/interfaces/bindings/tests/test_constants.mojom-blink-import-headers.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"


#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_CONSTANTS_MOJOM_BLINK_JUMBO_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_CONSTANTS_MOJOM_BLINK_JUMBO_H_
#endif
namespace mojo {
namespace test {
namespace blink {
const char kStringValue[] = "test string contents";
constexpr int8_t StructWithConstants::kInt8Value;
constexpr float StructWithConstants::kFloatValue;
const char StructWithConstants::kStringValue[] = "struct test string contents";
StructWithConstants::StructWithConstants() {}

StructWithConstants::~StructWithConstants() = default;
size_t StructWithConstants::Hash(size_t seed) const {
  return seed;
}

void StructWithConstants::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
}

bool StructWithConstants::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
const char InterfaceWithConstants::Name_[] = "mojo.test.InterfaceWithConstants";
constexpr uint32_t InterfaceWithConstants::kUint32Value;
constexpr double InterfaceWithConstants::kDoubleValue;
const char InterfaceWithConstants::kStringValue[] = "interface test string contents";

InterfaceWithConstantsProxy::InterfaceWithConstantsProxy(mojo::MessageReceiverWithResponder* receiver)
    : receiver_(receiver) {
}

// static
bool InterfaceWithConstantsStubDispatch::Accept(
    InterfaceWithConstants* impl,
    mojo::Message* message) {
  return false;
}

// static
bool InterfaceWithConstantsStubDispatch::AcceptWithResponder(
    InterfaceWithConstants* impl,
    mojo::Message* message,
    std::unique_ptr<mojo::MessageReceiverWithStatus> responder) {
  return false;
}



bool InterfaceWithConstantsRequestValidator::Accept(mojo::Message* message) {
  const char* name = ::mojo::test::blink::InterfaceWithConstants::Name_;
  return mojo::internal::ValidateRequestGeneric(message, name, {});
}

}  // namespace blink
}  // namespace test
}  // namespace mojo

namespace mojo {


// static
bool StructTraits<::mojo::test::blink::StructWithConstants::DataView, ::mojo::test::blink::StructWithConstantsPtr>::Read(
    ::mojo::test::blink::StructWithConstants::DataView input,
    ::mojo::test::blink::StructWithConstantsPtr* output) {
  bool success = true;
  ::mojo::test::blink::StructWithConstantsPtr result(::mojo::test::blink::StructWithConstants::New());
  
  *output = std::move(result);
  return success;
}

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif