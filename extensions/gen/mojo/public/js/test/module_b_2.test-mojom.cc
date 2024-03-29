// mojo/public/js/test/module_b_2.test-mojom.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "mojo/public/js/test/module_b_2.test-mojom.h"

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

#include "mojo/public/js/test/module_b_2.test-mojom-params-data.h"
#include "mojo/public/js/test/module_b_2.test-mojom-shared-message-ids.h"

#include "mojo/public/js/test/module_b_2.test-mojom-import-headers.h"


#ifndef MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_JUMBO_H_
#define MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_JUMBO_H_
#endif
namespace module_b {
TestStructB2::TestStructB2()
    : a1(),
      a2(),
      b2() {}

TestStructB2::TestStructB2(
    ::module_a::TestStructA1Ptr a1_in,
    ::module_a::TestStructA2Ptr a2_in,
    TestStructB2Ptr b2_in)
    : a1(std::move(a1_in)),
      a2(std::move(a2_in)),
      b2(std::move(b2_in)) {}

TestStructB2::~TestStructB2() = default;
size_t TestStructB2::Hash(size_t seed) const {
  seed = mojo::internal::Hash(seed, this->a1);
  seed = mojo::internal::Hash(seed, this->a2);
  seed = mojo::internal::Hash(seed, this->b2);
  return seed;
}

void TestStructB2::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "a1"), this->a1,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type ::module_a::TestStructA1Ptr>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "a2"), this->a2,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type ::module_a::TestStructA2Ptr>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "b2"), this->b2,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type TestStructB2Ptr>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool TestStructB2::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
const char TestInterface::Name_[] = "module_b.TestInterface";

TestInterfaceProxy::TestInterfaceProxy(mojo::MessageReceiverWithResponder* receiver)
    : receiver_(receiver) {
}

void TestInterfaceProxy::PassA1(
    ::module_a::TestStructA1Ptr in_a1) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT1(
    "mojom", "module_b::TestInterface::PassA1", "input_parameters",
    [&](perfetto::TracedValue context){
      auto dict = std::move(context).WriteDictionary();
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("a1"), in_a1, 
                        "<value of type ::module_a::TestStructA1Ptr>");
   });
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  
  const uint32_t kFlags =
      ((kExpectsResponse) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((kIsSync) ? mojo::Message::kFlagIsSync : 0);
  
  mojo::Message message(
      internal::kTestInterface_PassA1_Name, kFlags, 0, 0, nullptr);
  mojo::internal::MessageFragment<
      ::module_b::internal::TestInterface_PassA1_Params_Data> params(
          message);
  params.Allocate();
  mojo::internal::MessageFragment<
      typename decltype(params->a1)::BaseType> a1_fragment(
          params.message());
  mojo::internal::Serialize<::module_a::TestStructA1DataView>(
      in_a1, a1_fragment);
  params->a1.Set(
      a1_fragment.is_null() ? nullptr : a1_fragment.data());
  MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
      params->a1.is_null(),
      mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
      "null a1 in TestInterface.PassA1 request");

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(TestInterface::Name_);
  message.set_method_name("PassA1");
#endif
  // This return value may be ignored as false implies the Connector has
  // encountered an error, which will be visible through other means.
  ignore_result(receiver_->Accept(&message));
}

void TestInterfaceProxy::PassB1(
    ::module_b::TestStructB1Ptr in_b1) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT1(
    "mojom", "module_b::TestInterface::PassB1", "input_parameters",
    [&](perfetto::TracedValue context){
      auto dict = std::move(context).WriteDictionary();
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("b1"), in_b1, 
                        "<value of type ::module_b::TestStructB1Ptr>");
   });
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  
  const uint32_t kFlags =
      ((kExpectsResponse) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((kIsSync) ? mojo::Message::kFlagIsSync : 0);
  
  mojo::Message message(
      internal::kTestInterface_PassB1_Name, kFlags, 0, 0, nullptr);
  mojo::internal::MessageFragment<
      ::module_b::internal::TestInterface_PassB1_Params_Data> params(
          message);
  params.Allocate();
  mojo::internal::MessageFragment<
      typename decltype(params->b1)::BaseType> b1_fragment(
          params.message());
  mojo::internal::Serialize<::module_b::TestStructB1DataView>(
      in_b1, b1_fragment);
  params->b1.Set(
      b1_fragment.is_null() ? nullptr : b1_fragment.data());
  MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
      params->b1.is_null(),
      mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
      "null b1 in TestInterface.PassB1 request");

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(TestInterface::Name_);
  message.set_method_name("PassB1");
#endif
  // This return value may be ignored as false implies the Connector has
  // encountered an error, which will be visible through other means.
  ignore_result(receiver_->Accept(&message));
}

void TestInterfaceProxy::PassB2(
    TestStructB2Ptr in_b2) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT1(
    "mojom", "module_b::TestInterface::PassB2", "input_parameters",
    [&](perfetto::TracedValue context){
      auto dict = std::move(context).WriteDictionary();
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("b2"), in_b2, 
                        "<value of type TestStructB2Ptr>");
   });
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  
  const uint32_t kFlags =
      ((kExpectsResponse) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((kIsSync) ? mojo::Message::kFlagIsSync : 0);
  
  mojo::Message message(
      internal::kTestInterface_PassB2_Name, kFlags, 0, 0, nullptr);
  mojo::internal::MessageFragment<
      ::module_b::internal::TestInterface_PassB2_Params_Data> params(
          message);
  params.Allocate();
  mojo::internal::MessageFragment<
      typename decltype(params->b2)::BaseType> b2_fragment(
          params.message());
  mojo::internal::Serialize<::module_b::TestStructB2DataView>(
      in_b2, b2_fragment);
  params->b2.Set(
      b2_fragment.is_null() ? nullptr : b2_fragment.data());
  MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
      params->b2.is_null(),
      mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
      "null b2 in TestInterface.PassB2 request");

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(TestInterface::Name_);
  message.set_method_name("PassB2");
#endif
  // This return value may be ignored as false implies the Connector has
  // encountered an error, which will be visible through other means.
  ignore_result(receiver_->Accept(&message));
}

// static
bool TestInterfaceStubDispatch::Accept(
    TestInterface* impl,
    mojo::Message* message) {
  switch (message->header()->name) {
    case internal::kTestInterface_PassA1_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)module_b::TestInterface::PassA1",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)module_b::TestInterface::PassA1");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);

      DCHECK(message->is_serialized());
      internal::TestInterface_PassA1_Params_Data* params =
          reinterpret_cast<internal::TestInterface_PassA1_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      ::module_a::TestStructA1Ptr p_a1{};
      TestInterface_PassA1_ParamsDataView input_data_view(params, message);
      
      if (success && !input_data_view.ReadA1(&p_a1))
        success = false;
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            TestInterface::Name_, 0, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->PassA1(
std::move(p_a1));
      return true;
    }
    case internal::kTestInterface_PassB1_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)module_b::TestInterface::PassB1",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)module_b::TestInterface::PassB1");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);

      DCHECK(message->is_serialized());
      internal::TestInterface_PassB1_Params_Data* params =
          reinterpret_cast<internal::TestInterface_PassB1_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      ::module_b::TestStructB1Ptr p_b1{};
      TestInterface_PassB1_ParamsDataView input_data_view(params, message);
      
      if (success && !input_data_view.ReadB1(&p_b1))
        success = false;
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            TestInterface::Name_, 1, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->PassB1(
std::move(p_b1));
      return true;
    }
    case internal::kTestInterface_PassB2_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)module_b::TestInterface::PassB2",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)module_b::TestInterface::PassB2");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);

      DCHECK(message->is_serialized());
      internal::TestInterface_PassB2_Params_Data* params =
          reinterpret_cast<internal::TestInterface_PassB2_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      TestStructB2Ptr p_b2{};
      TestInterface_PassB2_ParamsDataView input_data_view(params, message);
      
      if (success && !input_data_view.ReadB2(&p_b2))
        success = false;
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            TestInterface::Name_, 2, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->PassB2(
std::move(p_b2));
      return true;
    }
  }
  return false;
}

// static
bool TestInterfaceStubDispatch::AcceptWithResponder(
    TestInterface* impl,
    mojo::Message* message,
    std::unique_ptr<mojo::MessageReceiverWithStatus> responder) {
  const bool message_is_sync = message->has_flag(mojo::Message::kFlagIsSync);
  const uint64_t request_id = message->request_id();
  ALLOW_UNUSED_LOCAL(message_is_sync);
  ALLOW_UNUSED_LOCAL(request_id);
  switch (message->header()->name) {
    case internal::kTestInterface_PassA1_Name: {
      break;
    }
    case internal::kTestInterface_PassB1_Name: {
      break;
    }
    case internal::kTestInterface_PassB2_Name: {
      break;
    }
  }
  return false;
}


static const std::pair<uint32_t, mojo::internal::GenericValidationInfo> kTestInterfaceValidationInfo[] = {
    {internal::kTestInterface_PassA1_Name,
     {&internal::TestInterface_PassA1_Params_Data::Validate,
      nullptr /* no response */}},
    {internal::kTestInterface_PassB1_Name,
     {&internal::TestInterface_PassB1_Params_Data::Validate,
      nullptr /* no response */}},
    {internal::kTestInterface_PassB2_Name,
     {&internal::TestInterface_PassB2_Params_Data::Validate,
      nullptr /* no response */}},
};

bool TestInterfaceRequestValidator::Accept(mojo::Message* message) {
  const char* name = ::module_b::TestInterface::Name_;
  return mojo::internal::ValidateRequestGeneric(message, name, kTestInterfaceValidationInfo);
}

}  // namespace module_b

namespace mojo {


// static
bool StructTraits<::module_b::TestStructB2::DataView, ::module_b::TestStructB2Ptr>::Read(
    ::module_b::TestStructB2::DataView input,
    ::module_b::TestStructB2Ptr* output) {
  bool success = true;
  ::module_b::TestStructB2Ptr result(::module_b::TestStructB2::New());
  
      if (success && !input.ReadA1(&result->a1))
        success = false;
      if (success && !input.ReadA2(&result->a2))
        success = false;
      if (success && !input.ReadB2(&result->b2))
        success = false;
  *output = std::move(result);
  return success;
}

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif