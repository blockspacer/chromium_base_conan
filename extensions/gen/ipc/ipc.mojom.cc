// ipc/ipc.mojom.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "ipc/ipc.mojom.h"

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

#include "ipc/ipc.mojom-params-data.h"
#include "ipc/ipc.mojom-shared-message-ids.h"

#include "ipc/ipc.mojom-import-headers.h"


#ifndef IPC_IPC_MOJOM_JUMBO_H_
#define IPC_IPC_MOJOM_JUMBO_H_
#endif
namespace IPC {
namespace mojom {
Message::Message()
    : bytes(),
      handles() {}

Message::Message(
    std::vector<uint8_t> bytes_in,
    base::Optional<std::vector<::mojo::native::SerializedHandlePtr>> handles_in)
    : bytes(std::move(bytes_in)),
      handles(std::move(handles_in)) {}

Message::~Message() = default;

void Message::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "bytes"), this->bytes,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type const std::vector<uint8_t>&>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "handles"), this->handles,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type base::Optional<std::vector<::mojo::native::SerializedHandlePtr>>>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool Message::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
const char GenericInterface::Name_[] = "IPC.mojom.GenericInterface";

GenericInterfaceProxy::GenericInterfaceProxy(mojo::MessageReceiverWithResponder* receiver)
    : receiver_(receiver) {
}

// static
bool GenericInterfaceStubDispatch::Accept(
    GenericInterface* impl,
    mojo::Message* message) {
  return false;
}

// static
bool GenericInterfaceStubDispatch::AcceptWithResponder(
    GenericInterface* impl,
    mojo::Message* message,
    std::unique_ptr<mojo::MessageReceiverWithStatus> responder) {
  return false;
}



bool GenericInterfaceRequestValidator::Accept(mojo::Message* message) {
  const char* name = ::IPC::mojom::GenericInterface::Name_;
  return mojo::internal::ValidateRequestGeneric(message, name, {});
}

const char Channel::Name_[] = "IPC.mojom.Channel";

ChannelProxy::ChannelProxy(mojo::MessageReceiverWithResponder* receiver)
    : receiver_(receiver) {
}

void ChannelProxy::SetPeerPid(
    int32_t in_pid) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT1(
    "mojom", "IPC::mojom::Channel::SetPeerPid", "input_parameters",
    [&](perfetto::TracedValue context){
      auto dict = std::move(context).WriteDictionary();
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("pid"), in_pid, 
                        "<value of type int32_t>");
   });
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  
  const uint32_t kFlags =
      ((kExpectsResponse) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((kIsSync) ? mojo::Message::kFlagIsSync : 0);
  
  mojo::Message message(
      internal::kChannel_SetPeerPid_Name, kFlags, 0, 0, nullptr);
  mojo::internal::MessageFragment<
      ::IPC::mojom::internal::Channel_SetPeerPid_Params_Data> params(
          message);
  params.Allocate();
  params->pid = in_pid;

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(Channel::Name_);
  message.set_method_name("SetPeerPid");
#endif
  // This return value may be ignored as false implies the Connector has
  // encountered an error, which will be visible through other means.
  ignore_result(receiver_->Accept(&message));
}

void ChannelProxy::Receive(
    ::IPC::MessageView in_message) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT1(
    "mojom", "IPC::mojom::Channel::Receive", "input_parameters",
    [&](perfetto::TracedValue context){
      auto dict = std::move(context).WriteDictionary();
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("message"), in_message, 
                        "<value of type ::IPC::MessageView>");
   });
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  
  const uint32_t kFlags =
      ((kExpectsResponse) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((kIsSync) ? mojo::Message::kFlagIsSync : 0);
  
  mojo::Message message(
      internal::kChannel_Receive_Name, kFlags, 0, 0,
      MOJO_CREATE_MESSAGE_FLAG_UNLIMITED_SIZE, nullptr);
  mojo::internal::MessageFragment<
      ::IPC::mojom::internal::Channel_Receive_Params_Data> params(
          message);
  params.Allocate();
  mojo::internal::MessageFragment<
      typename decltype(params->message)::BaseType> message_fragment(
          params.message());
  mojo::internal::Serialize<::IPC::mojom::MessageDataView>(
      in_message, message_fragment);
  params->message.Set(
      message_fragment.is_null() ? nullptr : message_fragment.data());
  MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
      params->message.is_null(),
      mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
      "null message in Channel.Receive request");

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(Channel::Name_);
  message.set_method_name("Receive");
#endif
  // This return value may be ignored as false implies the Connector has
  // encountered an error, which will be visible through other means.
  ignore_result(receiver_->Accept(&message));
}

void ChannelProxy::GetAssociatedInterface(
    const std::string& in_name, ::mojo::PendingAssociatedReceiver<GenericInterface> in_receiver) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT1(
    "mojom", "IPC::mojom::Channel::GetAssociatedInterface", "input_parameters",
    [&](perfetto::TracedValue context){
      auto dict = std::move(context).WriteDictionary();
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("name"), in_name, 
                        "<value of type const std::string&>");
      perfetto::WriteIntoTracedValueWithFallback(
           dict.AddItem("receiver"), in_receiver, 
                        "<value of type ::mojo::PendingAssociatedReceiver<GenericInterface>>");
   });
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  
  const uint32_t kFlags =
      ((kExpectsResponse) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((kIsSync) ? mojo::Message::kFlagIsSync : 0);
  
  mojo::Message message(
      internal::kChannel_GetAssociatedInterface_Name, kFlags, 0, 0, nullptr);
  mojo::internal::MessageFragment<
      ::IPC::mojom::internal::Channel_GetAssociatedInterface_Params_Data> params(
          message);
  params.Allocate();
  mojo::internal::MessageFragment<
      typename decltype(params->name)::BaseType> name_fragment(
          params.message());
  mojo::internal::Serialize<mojo::StringDataView>(
      in_name, name_fragment);
  params->name.Set(
      name_fragment.is_null() ? nullptr : name_fragment.data());
  MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
      params->name.is_null(),
      mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
      "null name in Channel.GetAssociatedInterface request");
  mojo::internal::Serialize<::IPC::mojom::GenericInterfaceAssociatedRequestDataView>(
      in_receiver, &params->receiver, &params.message());
  MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
      !mojo::internal::IsHandleOrInterfaceValid(params->receiver),
      mojo::internal::VALIDATION_ERROR_UNEXPECTED_INVALID_INTERFACE_ID,
      "invalid receiver in Channel.GetAssociatedInterface request");

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(Channel::Name_);
  message.set_method_name("GetAssociatedInterface");
#endif
  // This return value may be ignored as false implies the Connector has
  // encountered an error, which will be visible through other means.
  ignore_result(receiver_->Accept(&message));
}

// static
bool ChannelStubDispatch::Accept(
    Channel* impl,
    mojo::Message* message) {
  switch (message->header()->name) {
    case internal::kChannel_SetPeerPid_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)IPC::mojom::Channel::SetPeerPid",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)IPC::mojom::Channel::SetPeerPid");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);

      DCHECK(message->is_serialized());
      internal::Channel_SetPeerPid_Params_Data* params =
          reinterpret_cast<internal::Channel_SetPeerPid_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      int32_t p_pid{};
      Channel_SetPeerPid_ParamsDataView input_data_view(params, message);
      
      if (success)
        p_pid = input_data_view.pid();
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            Channel::Name_, 0, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->SetPeerPid(
std::move(p_pid));
      return true;
    }
    case internal::kChannel_Receive_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)IPC::mojom::Channel::Receive",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)IPC::mojom::Channel::Receive");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);

      DCHECK(message->is_serialized());
      internal::Channel_Receive_Params_Data* params =
          reinterpret_cast<internal::Channel_Receive_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      ::IPC::MessageView p_message{};
      Channel_Receive_ParamsDataView input_data_view(params, message);
      
      if (success && !input_data_view.ReadMessage(&p_message))
        success = false;
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            Channel::Name_, 1, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->Receive(
std::move(p_message));
      return true;
    }
    case internal::kChannel_GetAssociatedInterface_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)IPC::mojom::Channel::GetAssociatedInterface",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)IPC::mojom::Channel::GetAssociatedInterface");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);

      DCHECK(message->is_serialized());
      internal::Channel_GetAssociatedInterface_Params_Data* params =
          reinterpret_cast<internal::Channel_GetAssociatedInterface_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      std::string p_name{};
      ::mojo::PendingAssociatedReceiver<GenericInterface> p_receiver{};
      Channel_GetAssociatedInterface_ParamsDataView input_data_view(params, message);
      
      if (success && !input_data_view.ReadName(&p_name))
        success = false;
      if (success) {
        p_receiver =
            input_data_view.TakeReceiver<decltype(p_receiver)>();
      }
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            Channel::Name_, 2, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->GetAssociatedInterface(
std::move(p_name), 
std::move(p_receiver));
      return true;
    }
  }
  return false;
}

// static
bool ChannelStubDispatch::AcceptWithResponder(
    Channel* impl,
    mojo::Message* message,
    std::unique_ptr<mojo::MessageReceiverWithStatus> responder) {
  const bool message_is_sync = message->has_flag(mojo::Message::kFlagIsSync);
  const uint64_t request_id = message->request_id();
  ALLOW_UNUSED_LOCAL(message_is_sync);
  ALLOW_UNUSED_LOCAL(request_id);
  switch (message->header()->name) {
    case internal::kChannel_SetPeerPid_Name: {
      break;
    }
    case internal::kChannel_Receive_Name: {
      break;
    }
    case internal::kChannel_GetAssociatedInterface_Name: {
      break;
    }
  }
  return false;
}


static const std::pair<uint32_t, mojo::internal::GenericValidationInfo> kChannelValidationInfo[] = {
    {internal::kChannel_SetPeerPid_Name,
     {&internal::Channel_SetPeerPid_Params_Data::Validate,
      nullptr /* no response */}},
    {internal::kChannel_Receive_Name,
     {&internal::Channel_Receive_Params_Data::Validate,
      nullptr /* no response */}},
    {internal::kChannel_GetAssociatedInterface_Name,
     {&internal::Channel_GetAssociatedInterface_Params_Data::Validate,
      nullptr /* no response */}},
};

bool ChannelRequestValidator::Accept(mojo::Message* message) {
  const char* name = ::IPC::mojom::Channel::Name_;
  return mojo::internal::ValidateRequestGeneric(message, name, kChannelValidationInfo);
}

const char ChannelBootstrap::Name_[] = "IPC.mojom.ChannelBootstrap";

ChannelBootstrapProxy::ChannelBootstrapProxy(mojo::MessageReceiverWithResponder* receiver)
    : receiver_(receiver) {
}

// static
bool ChannelBootstrapStubDispatch::Accept(
    ChannelBootstrap* impl,
    mojo::Message* message) {
  return false;
}

// static
bool ChannelBootstrapStubDispatch::AcceptWithResponder(
    ChannelBootstrap* impl,
    mojo::Message* message,
    std::unique_ptr<mojo::MessageReceiverWithStatus> responder) {
  return false;
}



bool ChannelBootstrapRequestValidator::Accept(mojo::Message* message) {
  const char* name = ::IPC::mojom::ChannelBootstrap::Name_;
  return mojo::internal::ValidateRequestGeneric(message, name, {});
}

}  // namespace mojom
}  // namespace IPC

namespace mojo {


// static
bool StructTraits<::IPC::mojom::Message::DataView, ::IPC::mojom::MessagePtr>::Read(
    ::IPC::mojom::Message::DataView input,
    ::IPC::mojom::MessagePtr* output) {
  bool success = true;
  ::IPC::mojom::MessagePtr result(::IPC::mojom::Message::New());
  
      if (success && !input.ReadBytes(&result->bytes))
        success = false;
      if (success && !input.ReadHandles(&result->handles))
        success = false;
  *output = std::move(result);
  return success;
}

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif