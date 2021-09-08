// ipc/ipc.mojom.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPC_IPC_MOJOM_H_
#define IPC_IPC_MOJOM_H_

#include <stdint.h>

#include <limits>
#include <type_traits>
#include <utility>

#include "base/callback.h"
#include "base/macros.h"
#include "base/optional.h"

#include "mojo/public/cpp/bindings/clone_traits.h"
#include "mojo/public/cpp/bindings/equals_traits.h"
#include "mojo/public/cpp/bindings/lib/serialization.h"
#include "mojo/public/cpp/bindings/struct_ptr.h"
#include "mojo/public/cpp/bindings/struct_traits.h"
#include "mojo/public/cpp/bindings/union_traits.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value_forward.h"
#include "ipc/ipc.mojom-shared.h"
#include "ipc/ipc.mojom-forward.h"
#include "mojo/public/interfaces/bindings/native_struct.mojom.h"
#include <string>
#include <vector>

#include "mojo/public/cpp/bindings/associated_interface_ptr_info.h"
#include "mojo/public/cpp/bindings/associated_interface_request.h"
#include "mojo/public/cpp/bindings/interface_ptr.h"
#include "mojo/public/cpp/bindings/interface_request.h"
#include "mojo/public/cpp/bindings/lib/control_message_handler.h"
#include "mojo/public/cpp/bindings/raw_ptr_impl_ref_traits.h"


#include "ipc/message_mojom_traits.h"
#include "base/component_export.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace IPC {
namespace mojom {

class GenericInterfaceProxy;

template <typename ImplRefTraits>
class GenericInterfaceStub;

class GenericInterfaceRequestValidator;


// @generated_from: IPC.mojom.GenericInterface
class COMPONENT_EXPORT(IPC_MOJOM) GenericInterface
    : public GenericInterfaceInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = GenericInterfaceInterfaceBase;
  using Proxy_ = GenericInterfaceProxy;

  template <typename ImplRefTraits>
  using Stub_ = GenericInterfaceStub<ImplRefTraits>;

  using RequestValidator_ = GenericInterfaceRequestValidator;
  using ResponseValidator_ = mojo::PassThroughFilter;
  enum MethodMinVersions : uint32_t {
  };
  virtual ~GenericInterface() {}
};

class ChannelProxy;

template <typename ImplRefTraits>
class ChannelStub;

class ChannelRequestValidator;


// @generated_from: IPC.mojom.Channel
class COMPONENT_EXPORT(IPC_MOJOM) Channel
    : public ChannelInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = true;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = ChannelInterfaceBase;
  using Proxy_ = ChannelProxy;

  template <typename ImplRefTraits>
  using Stub_ = ChannelStub<ImplRefTraits>;

  using RequestValidator_ = ChannelRequestValidator;
  using ResponseValidator_ = mojo::PassThroughFilter;
  enum MethodMinVersions : uint32_t {
    kSetPeerPidMinVersion = 0,
    kReceiveMinVersion = 0,
    kGetAssociatedInterfaceMinVersion = 0,
  };
  virtual ~Channel() {}

  
// @generated_from: IPC.mojom.Channel.SetPeerPid
  virtual void SetPeerPid(int32_t pid) = 0;

  
// @generated_from: IPC.mojom.Channel.Receive
  virtual void Receive(::IPC::MessageView message) = 0;

  
// @generated_from: IPC.mojom.Channel.GetAssociatedInterface
  virtual void GetAssociatedInterface(const std::string& name, ::mojo::PendingAssociatedReceiver<GenericInterface> receiver) = 0;
};

class ChannelBootstrapProxy;

template <typename ImplRefTraits>
class ChannelBootstrapStub;

class ChannelBootstrapRequestValidator;


// @generated_from: IPC.mojom.ChannelBootstrap
class COMPONENT_EXPORT(IPC_MOJOM) ChannelBootstrap
    : public ChannelBootstrapInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = ChannelBootstrapInterfaceBase;
  using Proxy_ = ChannelBootstrapProxy;

  template <typename ImplRefTraits>
  using Stub_ = ChannelBootstrapStub<ImplRefTraits>;

  using RequestValidator_ = ChannelBootstrapRequestValidator;
  using ResponseValidator_ = mojo::PassThroughFilter;
  enum MethodMinVersions : uint32_t {
  };
  virtual ~ChannelBootstrap() {}
};



// @generated_from: IPC.mojom.GenericInterface
class COMPONENT_EXPORT(IPC_MOJOM) GenericInterfaceProxy
    : public GenericInterface {
 public:
  using InterfaceType = GenericInterface;

  explicit GenericInterfaceProxy(mojo::MessageReceiverWithResponder* receiver);

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};



// @generated_from: IPC.mojom.Channel
class COMPONENT_EXPORT(IPC_MOJOM) ChannelProxy
    : public Channel {
 public:
  using InterfaceType = Channel;

  explicit ChannelProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: IPC.mojom.Channel.SetPeerPid
  void SetPeerPid(int32_t pid) final;
  
// @generated_from: IPC.mojom.Channel.Receive
  void Receive(::IPC::MessageView message) final;
  
// @generated_from: IPC.mojom.Channel.GetAssociatedInterface
  void GetAssociatedInterface(const std::string& name, ::mojo::PendingAssociatedReceiver<GenericInterface> receiver) final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};



// @generated_from: IPC.mojom.ChannelBootstrap
class COMPONENT_EXPORT(IPC_MOJOM) ChannelBootstrapProxy
    : public ChannelBootstrap {
 public:
  using InterfaceType = ChannelBootstrap;

  explicit ChannelBootstrapProxy(mojo::MessageReceiverWithResponder* receiver);

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};
class COMPONENT_EXPORT(IPC_MOJOM) GenericInterfaceStubDispatch {
 public:
  static bool Accept(GenericInterface* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      GenericInterface* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<GenericInterface>>
class GenericInterfaceStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  GenericInterfaceStub() {}
  ~GenericInterfaceStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return GenericInterfaceStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return GenericInterfaceStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class COMPONENT_EXPORT(IPC_MOJOM) ChannelStubDispatch {
 public:
  static bool Accept(Channel* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      Channel* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<Channel>>
class ChannelStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  ChannelStub() {}
  ~ChannelStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return ChannelStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return ChannelStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class COMPONENT_EXPORT(IPC_MOJOM) ChannelBootstrapStubDispatch {
 public:
  static bool Accept(ChannelBootstrap* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      ChannelBootstrap* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<ChannelBootstrap>>
class ChannelBootstrapStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  ChannelBootstrapStub() {}
  ~ChannelBootstrapStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return ChannelBootstrapStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return ChannelBootstrapStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class COMPONENT_EXPORT(IPC_MOJOM) GenericInterfaceRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class COMPONENT_EXPORT(IPC_MOJOM) ChannelRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class COMPONENT_EXPORT(IPC_MOJOM) ChannelBootstrapRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};








// @generated_from: IPC.mojom.Message
class COMPONENT_EXPORT(IPC_MOJOM) Message {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<Message, T>::value>;
  using DataView = MessageDataView;
  using Data_ = internal::Message_Data;

  template <typename... Args>
  static MessagePtr New(Args&&... args) {
    return MessagePtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static MessagePtr From(const U& u) {
    return mojo::TypeConverter<MessagePtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, Message>::Convert(*this);
  }


  Message();

  Message(
      std::vector<uint8_t> bytes,
      base::Optional<std::vector<::mojo::native::SerializedHandlePtr>> handles);

  ~Message();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = MessagePtr>
  MessagePtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, Message::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, Message::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        Message::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::Message_UnserializedMessageContext<
            UserType, Message::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<Message::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const std::vector<uint8_t>& input,
                          UserType* output) {
    return Message::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::Message_UnserializedMessageContext<
            UserType, Message::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<Message::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: IPC.mojom.Message.bytes
  std::vector<uint8_t> bytes;
  
// @generated_from: IPC.mojom.Message.handles
  base::Optional<std::vector<::mojo::native::SerializedHandlePtr>> handles;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
  DISALLOW_COPY_AND_ASSIGN(Message);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, Message::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, Message::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, Message::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, Message::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}

template <typename StructPtrType>
MessagePtr Message::Clone() const {
  return New(
      mojo::Clone(bytes),
      mojo::Clone(handles)
  );
}

template <typename T, Message::EnableIfSame<T>*>
bool Message::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->bytes, other_struct.bytes))
    return false;
  if (!mojo::Equals(this->handles, other_struct.handles))
    return false;
  return true;
}

template <typename T, Message::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.bytes < rhs.bytes)
    return true;
  if (rhs.bytes < lhs.bytes)
    return false;
  if (lhs.handles < rhs.handles)
    return true;
  if (rhs.handles < lhs.handles)
    return false;
  return false;
}


}  // namespace mojom
}  // namespace IPC

namespace mojo {


template <>
struct COMPONENT_EXPORT(IPC_MOJOM) StructTraits<::IPC::mojom::Message::DataView,
                                         ::IPC::mojom::MessagePtr> {
  static bool IsNull(const ::IPC::mojom::MessagePtr& input) { return !input; }
  static void SetToNull(::IPC::mojom::MessagePtr* output) { output->reset(); }

  static const decltype(::IPC::mojom::Message::bytes)& bytes(
      const ::IPC::mojom::MessagePtr& input) {
    return input->bytes;
  }

  static  decltype(::IPC::mojom::Message::handles)& handles(
       ::IPC::mojom::MessagePtr& input) {
    return input->handles;
  }

  static bool Read(::IPC::mojom::Message::DataView input, ::IPC::mojom::MessagePtr* output);
};

}  // namespace mojo

#endif  // IPC_IPC_MOJOM_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTgxOSwgImJlZ2luIjogMTgwMywgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIklQQy5tb2pvbS5HZW5lcmljSW50ZXJmYWNlIn19LCB7
ImVuZCI6IDI2MTIsICJiZWdpbiI6IDI2MDUsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0
ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9t
aXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwg
InNpZ25hdHVyZSI6ICJJUEMubW9qb20uQ2hhbm5lbCJ9fSwgeyJlbmQiOiAzMzM5LCAiYmVnaW4i
OiAzMzI5LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9y
X2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29t
L2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAiSVBDLm1v
am9tLkNoYW5uZWwuU2V0UGVlclBpZCJ9fSwgeyJlbmQiOiAzNDMwLCAiYmVnaW4iOiAzNDIzLCAi
ZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMi
LCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVt
L3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAiSVBDLm1vam9tLkNoYW5u
ZWwuUmVjZWl2ZSJ9fSwgeyJlbmQiOiAzNTY2LCAiYmVnaW4iOiAzNTQ0LCAiZWRnZSI6ICIlL2t5
dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7
ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5n
dWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAiSVBDLm1vam9tLkNoYW5uZWwuR2V0QXNzb2Np
YXRlZEludGVyZmFjZSJ9fSwgeyJlbmQiOiAzODk1LCAiYmVnaW4iOiAzODc5LCAiZWRnZSI6ICIl
L2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUi
OiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJs
YW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAiSVBDLm1vam9tLkNoYW5uZWxCb290c3Ry
YXAifX0sIHsiZW5kIjogNTEyNywgImJlZ2luIjogNTExNywgImVkZ2UiOiAiJS9reXRoZS9lZGdl
L2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMi
OiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAi
bW9qb20iLCAic2lnbmF0dXJlIjogIklQQy5tb2pvbS5DaGFubmVsLlNldFBlZXJQaWQifX0sIHsi
ZW5kIjogNTIxMSwgImJlZ2luIjogNTIwNCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRl
cyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21p
dW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAi
c2lnbmF0dXJlIjogIklQQy5tb2pvbS5DaGFubmVsLlJlY2VpdmUifX0sIHsiZW5kIjogNTM0MCwg
ImJlZ2luIjogNTMxOCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjog
ImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291
cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjog
IklQQy5tb2pvbS5DaGFubmVsLkdldEFzc29jaWF0ZWRJbnRlcmZhY2UifX0sIHsiZW5kIjogMTAz
MDQsICJiZWdpbiI6IDEwMjk3LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5
cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29n
bGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1
cmUiOiAiSVBDLm1vam9tLk1lc3NhZ2UifX0sIHsiZW5kIjogMTM2NzEsICJiZWdpbiI6IDEzNjY2
LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmlu
ZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9t
aXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAiSVBDLm1vam9tLk1l
c3NhZ2UuYnl0ZXMifX0sIHsiZW5kIjogMTM3OTYsICJiZWdpbiI6IDEzNzg5LCAiZWRnZSI6ICIl
L2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUi
OiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJs
YW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAiSVBDLm1vam9tLk1lc3NhZ2UuaGFuZGxl
cyJ9fV0sICJ0eXBlIjogImt5dGhlMCJ9
*/