// mojo/public/interfaces/bindings/tests/validation_test_associated_interfaces.mojom.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "mojo/public/interfaces/bindings/tests/validation_test_associated_interfaces.mojom.h"

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

#include "mojo/public/interfaces/bindings/tests/validation_test_associated_interfaces.mojom-params-data.h"
#include "mojo/public/interfaces/bindings/tests/validation_test_associated_interfaces.mojom-shared-message-ids.h"

#include "mojo/public/interfaces/bindings/tests/validation_test_associated_interfaces.mojom-import-headers.h"


#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_VALIDATION_TEST_ASSOCIATED_INTERFACES_MOJOM_JUMBO_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_VALIDATION_TEST_ASSOCIATED_INTERFACES_MOJOM_JUMBO_H_
#endif
namespace mojo {
namespace test {
const char InterfaceX::Name_[] = "mojo.test.InterfaceX";

InterfaceXProxy::InterfaceXProxy(mojo::MessageReceiverWithResponder* receiver)
    : receiver_(receiver) {
}

// static
bool InterfaceXStubDispatch::Accept(
    InterfaceX* impl,
    mojo::Message* message) {
  return false;
}

// static
bool InterfaceXStubDispatch::AcceptWithResponder(
    InterfaceX* impl,
    mojo::Message* message,
    std::unique_ptr<mojo::MessageReceiverWithStatus> responder) {
  return false;
}



bool InterfaceXRequestValidator::Accept(mojo::Message* message) {
  const char* name = ::mojo::test::InterfaceX::Name_;
  return mojo::internal::ValidateRequestGeneric(message, name, {});
}

const char AssociatedConformanceTestInterface::Name_[] = "mojo.test.AssociatedConformanceTestInterface";

AssociatedConformanceTestInterfaceProxy::AssociatedConformanceTestInterfaceProxy(mojo::MessageReceiverWithResponder* receiver)
    : receiver_(receiver) {
}

void AssociatedConformanceTestInterfaceProxy::Method0(
    ::mojo::PendingAssociatedRemote<InterfaceX> in_param0) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT1(
    "mojom", "mojo::test::AssociatedConformanceTestInterface::Method0", "input_parameters",
    [&](perfetto::TracedValue context){
      auto dict = std::move(context).WriteDictionary();
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("param0"), in_param0, 
                        "<value of type ::mojo::PendingAssociatedRemote<InterfaceX>>");
   });
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  
  const uint32_t kFlags =
      ((kExpectsResponse) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((kIsSync) ? mojo::Message::kFlagIsSync : 0);
  
  mojo::Message message(
      internal::kAssociatedConformanceTestInterface_Method0_Name, kFlags, 0, 0, nullptr);
  mojo::internal::MessageFragment<
      ::mojo::test::internal::AssociatedConformanceTestInterface_Method0_Params_Data> params(
          message);
  params.Allocate();
  mojo::internal::Serialize<::mojo::test::InterfaceXAssociatedPtrInfoDataView>(
      in_param0, &params->param0, &params.message());
  MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
      !mojo::internal::IsHandleOrInterfaceValid(params->param0),
      mojo::internal::VALIDATION_ERROR_UNEXPECTED_INVALID_INTERFACE_ID,
      "invalid param0 in AssociatedConformanceTestInterface.Method0 request");

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(AssociatedConformanceTestInterface::Name_);
  message.set_method_name("Method0");
#endif
  // This return value may be ignored as false implies the Connector has
  // encountered an error, which will be visible through other means.
  ignore_result(receiver_->Accept(&message));
}

void AssociatedConformanceTestInterfaceProxy::Method1(
    ::mojo::PendingAssociatedReceiver<InterfaceX> in_param0) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT1(
    "mojom", "mojo::test::AssociatedConformanceTestInterface::Method1", "input_parameters",
    [&](perfetto::TracedValue context){
      auto dict = std::move(context).WriteDictionary();
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("param0"), in_param0, 
                        "<value of type ::mojo::PendingAssociatedReceiver<InterfaceX>>");
   });
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  
  const uint32_t kFlags =
      ((kExpectsResponse) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((kIsSync) ? mojo::Message::kFlagIsSync : 0);
  
  mojo::Message message(
      internal::kAssociatedConformanceTestInterface_Method1_Name, kFlags, 0, 0, nullptr);
  mojo::internal::MessageFragment<
      ::mojo::test::internal::AssociatedConformanceTestInterface_Method1_Params_Data> params(
          message);
  params.Allocate();
  mojo::internal::Serialize<::mojo::test::InterfaceXAssociatedRequestDataView>(
      in_param0, &params->param0, &params.message());
  MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
      !mojo::internal::IsHandleOrInterfaceValid(params->param0),
      mojo::internal::VALIDATION_ERROR_UNEXPECTED_INVALID_INTERFACE_ID,
      "invalid param0 in AssociatedConformanceTestInterface.Method1 request");

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(AssociatedConformanceTestInterface::Name_);
  message.set_method_name("Method1");
#endif
  // This return value may be ignored as false implies the Connector has
  // encountered an error, which will be visible through other means.
  ignore_result(receiver_->Accept(&message));
}

void AssociatedConformanceTestInterfaceProxy::Method2(
    ::mojo::PendingAssociatedRemote<InterfaceX> in_param0) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT1(
    "mojom", "mojo::test::AssociatedConformanceTestInterface::Method2", "input_parameters",
    [&](perfetto::TracedValue context){
      auto dict = std::move(context).WriteDictionary();
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("param0"), in_param0, 
                        "<value of type ::mojo::PendingAssociatedRemote<InterfaceX>>");
   });
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  
  const uint32_t kFlags =
      ((kExpectsResponse) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((kIsSync) ? mojo::Message::kFlagIsSync : 0);
  
  mojo::Message message(
      internal::kAssociatedConformanceTestInterface_Method2_Name, kFlags, 0, 0, nullptr);
  mojo::internal::MessageFragment<
      ::mojo::test::internal::AssociatedConformanceTestInterface_Method2_Params_Data> params(
          message);
  params.Allocate();
  mojo::internal::Serialize<::mojo::test::InterfaceXAssociatedPtrInfoDataView>(
      in_param0, &params->param0, &params.message());

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(AssociatedConformanceTestInterface::Name_);
  message.set_method_name("Method2");
#endif
  // This return value may be ignored as false implies the Connector has
  // encountered an error, which will be visible through other means.
  ignore_result(receiver_->Accept(&message));
}

void AssociatedConformanceTestInterfaceProxy::Method3(
    std::vector<::mojo::PendingAssociatedRemote<InterfaceX>> in_param0) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT1(
    "mojom", "mojo::test::AssociatedConformanceTestInterface::Method3", "input_parameters",
    [&](perfetto::TracedValue context){
      auto dict = std::move(context).WriteDictionary();
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("param0"), in_param0, 
                        "<value of type std::vector<::mojo::PendingAssociatedRemote<InterfaceX>>>");
   });
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  
  const uint32_t kFlags =
      ((kExpectsResponse) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((kIsSync) ? mojo::Message::kFlagIsSync : 0);
  
  mojo::Message message(
      internal::kAssociatedConformanceTestInterface_Method3_Name, kFlags, 0, 0, nullptr);
  mojo::internal::MessageFragment<
      ::mojo::test::internal::AssociatedConformanceTestInterface_Method3_Params_Data> params(
          message);
  params.Allocate();
  mojo::internal::MessageFragment<
      typename decltype(params->param0)::BaseType>
      param0_fragment(params.message());
  const mojo::internal::ContainerValidateParams param0_validate_params(
      0, false, nullptr);
  mojo::internal::Serialize<mojo::ArrayDataView<::mojo::test::InterfaceXAssociatedPtrInfoDataView>>(
      in_param0, param0_fragment, &param0_validate_params);
  params->param0.Set(
      param0_fragment.is_null() ? nullptr : param0_fragment.data());
  MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
      params->param0.is_null(),
      mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
      "null param0 in AssociatedConformanceTestInterface.Method3 request");

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(AssociatedConformanceTestInterface::Name_);
  message.set_method_name("Method3");
#endif
  // This return value may be ignored as false implies the Connector has
  // encountered an error, which will be visible through other means.
  ignore_result(receiver_->Accept(&message));
}

// static
bool AssociatedConformanceTestInterfaceStubDispatch::Accept(
    AssociatedConformanceTestInterface* impl,
    mojo::Message* message) {
  switch (message->header()->name) {
    case internal::kAssociatedConformanceTestInterface_Method0_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)mojo::test::AssociatedConformanceTestInterface::Method0",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)mojo::test::AssociatedConformanceTestInterface::Method0");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);

      DCHECK(message->is_serialized());
      internal::AssociatedConformanceTestInterface_Method0_Params_Data* params =
          reinterpret_cast<internal::AssociatedConformanceTestInterface_Method0_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      ::mojo::PendingAssociatedRemote<InterfaceX> p_param0{};
      AssociatedConformanceTestInterface_Method0_ParamsDataView input_data_view(params, message);
      
      if (success) {
        p_param0 =
            input_data_view.TakeParam0<decltype(p_param0)>();
      }
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            AssociatedConformanceTestInterface::Name_, 0, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->Method0(
std::move(p_param0));
      return true;
    }
    case internal::kAssociatedConformanceTestInterface_Method1_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)mojo::test::AssociatedConformanceTestInterface::Method1",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)mojo::test::AssociatedConformanceTestInterface::Method1");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);

      DCHECK(message->is_serialized());
      internal::AssociatedConformanceTestInterface_Method1_Params_Data* params =
          reinterpret_cast<internal::AssociatedConformanceTestInterface_Method1_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      ::mojo::PendingAssociatedReceiver<InterfaceX> p_param0{};
      AssociatedConformanceTestInterface_Method1_ParamsDataView input_data_view(params, message);
      
      if (success) {
        p_param0 =
            input_data_view.TakeParam0<decltype(p_param0)>();
      }
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            AssociatedConformanceTestInterface::Name_, 1, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->Method1(
std::move(p_param0));
      return true;
    }
    case internal::kAssociatedConformanceTestInterface_Method2_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)mojo::test::AssociatedConformanceTestInterface::Method2",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)mojo::test::AssociatedConformanceTestInterface::Method2");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);

      DCHECK(message->is_serialized());
      internal::AssociatedConformanceTestInterface_Method2_Params_Data* params =
          reinterpret_cast<internal::AssociatedConformanceTestInterface_Method2_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      ::mojo::PendingAssociatedRemote<InterfaceX> p_param0{};
      AssociatedConformanceTestInterface_Method2_ParamsDataView input_data_view(params, message);
      
      if (success) {
        p_param0 =
            input_data_view.TakeParam0<decltype(p_param0)>();
      }
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            AssociatedConformanceTestInterface::Name_, 2, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->Method2(
std::move(p_param0));
      return true;
    }
    case internal::kAssociatedConformanceTestInterface_Method3_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)mojo::test::AssociatedConformanceTestInterface::Method3",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)mojo::test::AssociatedConformanceTestInterface::Method3");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);

      DCHECK(message->is_serialized());
      internal::AssociatedConformanceTestInterface_Method3_Params_Data* params =
          reinterpret_cast<internal::AssociatedConformanceTestInterface_Method3_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      std::vector<::mojo::PendingAssociatedRemote<InterfaceX>> p_param0{};
      AssociatedConformanceTestInterface_Method3_ParamsDataView input_data_view(params, message);
      
      if (success && !input_data_view.ReadParam0(&p_param0))
        success = false;
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            AssociatedConformanceTestInterface::Name_, 3, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->Method3(
std::move(p_param0));
      return true;
    }
  }
  return false;
}

// static
bool AssociatedConformanceTestInterfaceStubDispatch::AcceptWithResponder(
    AssociatedConformanceTestInterface* impl,
    mojo::Message* message,
    std::unique_ptr<mojo::MessageReceiverWithStatus> responder) {
  const bool message_is_sync = message->has_flag(mojo::Message::kFlagIsSync);
  const uint64_t request_id = message->request_id();
  ALLOW_UNUSED_LOCAL(message_is_sync);
  ALLOW_UNUSED_LOCAL(request_id);
  switch (message->header()->name) {
    case internal::kAssociatedConformanceTestInterface_Method0_Name: {
      break;
    }
    case internal::kAssociatedConformanceTestInterface_Method1_Name: {
      break;
    }
    case internal::kAssociatedConformanceTestInterface_Method2_Name: {
      break;
    }
    case internal::kAssociatedConformanceTestInterface_Method3_Name: {
      break;
    }
  }
  return false;
}


static const mojo::internal::GenericValidationInfo kAssociatedConformanceTestInterfaceValidationInfo[] = {
    {&internal::AssociatedConformanceTestInterface_Method0_Params_Data::Validate,
     nullptr /* no response */},
    {&internal::AssociatedConformanceTestInterface_Method1_Params_Data::Validate,
     nullptr /* no response */},
    {&internal::AssociatedConformanceTestInterface_Method2_Params_Data::Validate,
     nullptr /* no response */},
    {&internal::AssociatedConformanceTestInterface_Method3_Params_Data::Validate,
     nullptr /* no response */},
};

bool AssociatedConformanceTestInterfaceRequestValidator::Accept(mojo::Message* message) {
  const char* name = ::mojo::test::AssociatedConformanceTestInterface::Name_;
  return mojo::internal::ValidateRequestGenericPacked(message, name, kAssociatedConformanceTestInterfaceValidationInfo);
}

}  // namespace test
}  // namespace mojo

namespace mojo {

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif