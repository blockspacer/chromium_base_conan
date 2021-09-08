// mojo/public/js/test/module_a.test-mojom-blink.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "mojo/public/js/test/module_a.test-mojom-blink.h"

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

#include "mojo/public/js/test/module_a.test-mojom-params-data.h"
#include "mojo/public/js/test/module_a.test-mojom-shared-message-ids.h"

#include "mojo/public/js/test/module_a.test-mojom-blink-import-headers.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"


#ifndef MOJO_PUBLIC_JS_TEST_MODULE_A_TEST_MOJOM_BLINK_JUMBO_H_
#define MOJO_PUBLIC_JS_TEST_MODULE_A_TEST_MOJOM_BLINK_JUMBO_H_
#endif
namespace module_a {
namespace blink {
TestStructA1::TestStructA1()
    : q(),
      r(),
      s() {}

TestStructA1::TestStructA1(
    const WTF::String& q_in,
    const WTF::String& r_in,
    const WTF::String& s_in)
    : q(std::move(q_in)),
      r(std::move(r_in)),
      s(std::move(s_in)) {}

TestStructA1::~TestStructA1() = default;
size_t TestStructA1::Hash(size_t seed) const {
  seed = mojo::internal::WTFHash(seed, this->q);
  seed = mojo::internal::WTFHash(seed, this->r);
  seed = mojo::internal::WTFHash(seed, this->s);
  return seed;
}

void TestStructA1::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "q"), this->q,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type const WTF::String&>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "r"), this->r,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type const WTF::String&>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "s"), this->s,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type const WTF::String&>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool TestStructA1::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
TestStructA2::TestStructA2()
    : ax(),
      ay(),
      enumField() {}

TestStructA2::TestStructA2(
    TestStructA1Ptr ax_in,
    TestStructA1Ptr ay_in,
    TestStructA2::NestedEnum enumField_in)
    : ax(std::move(ax_in)),
      ay(std::move(ay_in)),
      enumField(std::move(enumField_in)) {}

TestStructA2::~TestStructA2() = default;
size_t TestStructA2::Hash(size_t seed) const {
  seed = mojo::internal::WTFHash(seed, this->ax);
  seed = mojo::internal::WTFHash(seed, this->ay);
  seed = mojo::internal::WTFHash(seed, this->enumField);
  return seed;
}

void TestStructA2::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "ax"), this->ax,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type TestStructA1Ptr>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "ay"), this->ay,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type TestStructA1Ptr>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "enumField"), this->enumField,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type TestStructA2::NestedEnum>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool TestStructA2::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
const char ParentInterface::Name_[] = "module_a.ParentInterface";

ParentInterfaceProxy::ParentInterfaceProxy(mojo::MessageReceiverWithResponder* receiver)
    : receiver_(receiver) {
}

void ParentInterfaceProxy::SomeMethod(
    ParentInterface::NestedEnum in_value) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT1(
    "mojom", "module_a::ParentInterface::SomeMethod", "input_parameters",
    [&](perfetto::TracedValue context){
      auto dict = std::move(context).WriteDictionary();
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("value"), in_value, 
                        "<value of type ParentInterface::NestedEnum>");
   });
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  
  const uint32_t kFlags =
      ((kExpectsResponse) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((kIsSync) ? mojo::Message::kFlagIsSync : 0);
  
  mojo::Message message(
      internal::kParentInterface_SomeMethod_Name, kFlags, 0, 0, nullptr);
  mojo::internal::MessageFragment<
      ::module_a::internal::ParentInterface_SomeMethod_Params_Data> params(
          message);
  params.Allocate();
  mojo::internal::Serialize<::module_a::ParentInterface_NestedEnum>(
      in_value, &params->value);

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(ParentInterface::Name_);
  message.set_method_name("SomeMethod");
#endif
  // This return value may be ignored as false implies the Connector has
  // encountered an error, which will be visible through other means.
  ignore_result(receiver_->Accept(&message));
}

// static
bool ParentInterfaceStubDispatch::Accept(
    ParentInterface* impl,
    mojo::Message* message) {
  switch (message->header()->name) {
    case internal::kParentInterface_SomeMethod_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)module_a::ParentInterface::SomeMethod",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)module_a::ParentInterface::SomeMethod");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);

      DCHECK(message->is_serialized());
      internal::ParentInterface_SomeMethod_Params_Data* params =
          reinterpret_cast<internal::ParentInterface_SomeMethod_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      ParentInterface::NestedEnum p_value{};
      ParentInterface_SomeMethod_ParamsDataView input_data_view(params, message);
      
      if (success && !input_data_view.ReadValue(&p_value))
        success = false;
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            ParentInterface::Name_, 0, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->SomeMethod(
std::move(p_value));
      return true;
    }
  }
  return false;
}

// static
bool ParentInterfaceStubDispatch::AcceptWithResponder(
    ParentInterface* impl,
    mojo::Message* message,
    std::unique_ptr<mojo::MessageReceiverWithStatus> responder) {
  const bool message_is_sync = message->has_flag(mojo::Message::kFlagIsSync);
  const uint64_t request_id = message->request_id();
  ALLOW_UNUSED_LOCAL(message_is_sync);
  ALLOW_UNUSED_LOCAL(request_id);
  switch (message->header()->name) {
    case internal::kParentInterface_SomeMethod_Name: {
      break;
    }
  }
  return false;
}


static const std::pair<uint32_t, mojo::internal::GenericValidationInfo> kParentInterfaceValidationInfo[] = {
    {internal::kParentInterface_SomeMethod_Name,
     {&internal::ParentInterface_SomeMethod_Params_Data::Validate,
      nullptr /* no response */}},
};

bool ParentInterfaceRequestValidator::Accept(mojo::Message* message) {
  const char* name = ::module_a::blink::ParentInterface::Name_;
  return mojo::internal::ValidateRequestGeneric(message, name, kParentInterfaceValidationInfo);
}

}  // namespace blink
}  // namespace module_a

namespace mojo {


// static
bool StructTraits<::module_a::blink::TestStructA1::DataView, ::module_a::blink::TestStructA1Ptr>::Read(
    ::module_a::blink::TestStructA1::DataView input,
    ::module_a::blink::TestStructA1Ptr* output) {
  bool success = true;
  ::module_a::blink::TestStructA1Ptr result(::module_a::blink::TestStructA1::New());
  
      if (success && !input.ReadQ(&result->q))
        success = false;
      if (success && !input.ReadR(&result->r))
        success = false;
      if (success && !input.ReadS(&result->s))
        success = false;
  *output = std::move(result);
  return success;
}


// static
bool StructTraits<::module_a::blink::TestStructA2::DataView, ::module_a::blink::TestStructA2Ptr>::Read(
    ::module_a::blink::TestStructA2::DataView input,
    ::module_a::blink::TestStructA2Ptr* output) {
  bool success = true;
  ::module_a::blink::TestStructA2Ptr result(::module_a::blink::TestStructA2::New());
  
      if (success && !input.ReadAx(&result->ax))
        success = false;
      if (success && !input.ReadAy(&result->ay))
        success = false;
      if (success && !input.ReadEnumField(&result->enumField))
        success = false;
  *output = std::move(result);
  return success;
}

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif