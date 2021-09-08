// mojo/public/cpp/bindings/tests/connection_group_unittest.test-mojom-blink.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "mojo/public/cpp/bindings/tests/connection_group_unittest.test-mojom-blink.h"

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

#include "mojo/public/cpp/bindings/tests/connection_group_unittest.test-mojom-params-data.h"
#include "mojo/public/cpp/bindings/tests/connection_group_unittest.test-mojom-shared-message-ids.h"

#include "mojo/public/cpp/bindings/tests/connection_group_unittest.test-mojom-blink-import-headers.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"


#ifndef MOJO_PUBLIC_CPP_BINDINGS_TESTS_CONNECTION_GROUP_UNITTEST_TEST_MOJOM_BLINK_JUMBO_H_
#define MOJO_PUBLIC_CPP_BINDINGS_TESTS_CONNECTION_GROUP_UNITTEST_TEST_MOJOM_BLINK_JUMBO_H_
#endif
namespace mojo {
namespace test {
namespace connection_group_unittest {
namespace mojom {
namespace blink {
const char TestInterface::Name_[] = "mojo.test.connection_group_unittest.mojom.TestInterface";

TestInterfaceProxy::TestInterfaceProxy(mojo::MessageReceiverWithResponder* receiver)
    : receiver_(receiver) {
}
class TestInterfaceProxy_BindReceiver_Message
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  explicit TestInterfaceProxy_BindReceiver_Message(
      uint32_t message_flags
      , ::mojo::PendingReceiver<TestInterface> param_receiver
  )
      : mojo::internal::UnserializedMessageContext(
          &kMessageTag,
          internal::kTestInterface_BindReceiver_Name,
          message_flags)
      , param_receiver_(std::move(param_receiver)){}
  ~TestInterfaceProxy_BindReceiver_Message() override = default;

  static mojo::Message Build(
      bool serialize,
      bool expects_response,
      bool is_sync,
      ::mojo::PendingReceiver<TestInterface> param_receiver) {

    
  const uint32_t kFlags =
      ((expects_response) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((is_sync) ? mojo::Message::kFlagIsSync : 0);

    if (!serialize) {
      return mojo::Message(std::make_unique<TestInterfaceProxy_BindReceiver_Message>(
          kFlags
          , std::move(param_receiver)
          ),
          MOJO_CREATE_MESSAGE_FLAG_NONE);
    }

    DCHECK(serialize);
    
  mojo::Message message(
      internal::kTestInterface_BindReceiver_Name, kFlags, 0, 0, nullptr);
  mojo::internal::MessageFragment<
      ::mojo::test::connection_group_unittest::mojom::internal::TestInterface_BindReceiver_Params_Data> params(
          message);
  params.Allocate();
  mojo::internal::Serialize<mojo::InterfaceRequestDataView<::mojo::test::connection_group_unittest::mojom::TestInterfaceInterfaceBase>>(
      param_receiver, &params->receiver, &params.message());
  MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
      !mojo::internal::IsHandleOrInterfaceValid(params->receiver),
      mojo::internal::VALIDATION_ERROR_UNEXPECTED_INVALID_HANDLE,
      "invalid receiver in TestInterface.BindReceiver request");
    return message;
  }


  void Dispatch(
      mojo::Message* message,
      TestInterface* impl) {
    if (message->receiver_connection_group()) {
      param_receiver_.set_connection_group(
          *message->receiver_connection_group());
    }

    impl->BindReceiver(
        std::move(param_receiver_));
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<
        ::mojo::test::connection_group_unittest::mojom::internal::TestInterface_BindReceiver_Params_Data> params(
            message);
    params.Allocate();
  mojo::internal::Serialize<mojo::InterfaceRequestDataView<::mojo::test::connection_group_unittest::mojom::TestInterfaceInterfaceBase>>(
      param_receiver_, &params->receiver, &params.message());
  MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
      !mojo::internal::IsHandleOrInterfaceValid(params->receiver),
      mojo::internal::VALIDATION_ERROR_UNEXPECTED_INVALID_HANDLE,
      "invalid receiver in TestInterface.BindReceiver request");
  }
  ::mojo::PendingReceiver<TestInterface> param_receiver_;

  DISALLOW_COPY_AND_ASSIGN(TestInterfaceProxy_BindReceiver_Message);
};

const mojo::internal::UnserializedMessageContext::Tag
TestInterfaceProxy_BindReceiver_Message::kMessageTag = {};

void TestInterfaceProxy::BindReceiver(
    ::mojo::PendingReceiver<TestInterface> in_receiver) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT1(
    "mojom", "mojo::test::connection_group_unittest::mojom::TestInterface::BindReceiver", "input_parameters",
    [&](perfetto::TracedValue context){
      auto dict = std::move(context).WriteDictionary();
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("receiver"), in_receiver, 
                        "<value of type ::mojo::PendingReceiver<TestInterface>>");
   });
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  const bool kSerialize = receiver_->PrefersSerializedMessages();
  auto message = TestInterfaceProxy_BindReceiver_Message::Build(
      kSerialize, kExpectsResponse, kIsSync, std::move(in_receiver));

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(TestInterface::Name_);
  message.set_method_name("BindReceiver");
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
    case internal::kTestInterface_BindReceiver_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)mojo::test::connection_group_unittest::mojom::TestInterface::BindReceiver",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)mojo::test::connection_group_unittest::mojom::TestInterface::BindReceiver");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);
      if (!message->is_serialized()) {
        auto context = message->TakeUnserializedContext<
            TestInterfaceProxy_BindReceiver_Message>();
        if (!context) {
          // The Message was not of the expected type. It may be a valid message
          // which was serialized using a different variant of these bindings.
          // Force serialization before dispatch in this case.
          message->SerializeIfNecessary();
        } else {
          context->Dispatch(message, impl);
          return true;
        }
      }

      DCHECK(message->is_serialized());
      internal::TestInterface_BindReceiver_Params_Data* params =
          reinterpret_cast<internal::TestInterface_BindReceiver_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      ::mojo::PendingReceiver<TestInterface> p_receiver{};
      TestInterface_BindReceiver_ParamsDataView input_data_view(params, message);
      
      if (success) {
        p_receiver =
            input_data_view.TakeReceiver<decltype(p_receiver)>();
      }
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            TestInterface::Name_, 0, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->BindReceiver(
std::move(p_receiver));
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
    case internal::kTestInterface_BindReceiver_Name: {
      break;
    }
  }
  return false;
}


static const std::pair<uint32_t, mojo::internal::GenericValidationInfo> kTestInterfaceValidationInfo[] = {
    {internal::kTestInterface_BindReceiver_Name,
     {&internal::TestInterface_BindReceiver_Params_Data::Validate,
      nullptr /* no response */}},
};

bool TestInterfaceRequestValidator::Accept(mojo::Message* message) {
  const char* name = ::mojo::test::connection_group_unittest::mojom::blink::TestInterface::Name_;
  return mojo::internal::ValidateRequestGeneric(message, name, kTestInterfaceValidationInfo);
}

}  // namespace blink
}  // namespace mojom
}  // namespace connection_group_unittest
}  // namespace test
}  // namespace mojo

namespace mojo {

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif