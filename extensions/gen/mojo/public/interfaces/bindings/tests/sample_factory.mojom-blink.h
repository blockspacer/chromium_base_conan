// mojo/public/interfaces/bindings/tests/sample_factory.mojom-blink.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_FACTORY_MOJOM_BLINK_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_FACTORY_MOJOM_BLINK_H_

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
#include "mojo/public/interfaces/bindings/tests/sample_factory.mojom-shared.h"
#include "mojo/public/interfaces/bindings/tests/sample_factory.mojom-blink-forward.h"
#include "mojo/public/interfaces/bindings/tests/sample_import.mojom-blink.h"

#include "mojo/public/cpp/bindings/lib/wtf_clone_equals_util.h"
#include "mojo/public/cpp/bindings/lib/wtf_hash_util.h"
#include "third_party/blink/renderer/platform/wtf/hash_functions.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

#include "mojo/public/cpp/bindings/associated_interface_ptr_info.h"
#include "mojo/public/cpp/bindings/associated_interface_request.h"
#include "mojo/public/cpp/bindings/interface_ptr.h"
#include "mojo/public/cpp/bindings/interface_request.h"
#include "mojo/public/cpp/bindings/lib/control_message_handler.h"
#include "mojo/public/cpp/bindings/raw_ptr_impl_ref_traits.h"



#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace sample {
namespace blink {

class NamedObjectProxy;

template <typename ImplRefTraits>
class NamedObjectStub;

class NamedObjectRequestValidator;
class NamedObjectResponseValidator;


// @generated_from: sample.NamedObject
class  NamedObject
    : public NamedObjectInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = NamedObjectInterfaceBase;
  using Proxy_ = NamedObjectProxy;

  template <typename ImplRefTraits>
  using Stub_ = NamedObjectStub<ImplRefTraits>;

  using RequestValidator_ = NamedObjectRequestValidator;
  using ResponseValidator_ = NamedObjectResponseValidator;
  enum MethodMinVersions : uint32_t {
    kSetNameMinVersion = 0,
    kGetNameMinVersion = 0,
  };
  virtual ~NamedObject() {}

  
// @generated_from: sample.NamedObject.SetName
  virtual void SetName(const WTF::String& name) = 0;


  using GetNameCallback = base::OnceCallback<void(const WTF::String&)>;
  
// @generated_from: sample.NamedObject.GetName
  virtual void GetName(GetNameCallback callback) = 0;
};

class FactoryProxy;

template <typename ImplRefTraits>
class FactoryStub;

class FactoryRequestValidator;
class FactoryResponseValidator;


// @generated_from: sample.Factory
class  Factory
    : public FactoryInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = FactoryInterfaceBase;
  using Proxy_ = FactoryProxy;

  template <typename ImplRefTraits>
  using Stub_ = FactoryStub<ImplRefTraits>;

  using RequestValidator_ = FactoryRequestValidator;
  using ResponseValidator_ = FactoryResponseValidator;
  enum MethodMinVersions : uint32_t {
    kDoStuffMinVersion = 0,
    kDoStuff2MinVersion = 0,
    kCreateNamedObjectMinVersion = 0,
    kRequestImportedInterfaceMinVersion = 0,
    kTakeImportedInterfaceMinVersion = 0,
  };
  virtual ~Factory() {}


  using DoStuffCallback = base::OnceCallback<void(ResponsePtr, const WTF::String&)>;
  
// @generated_from: sample.Factory.DoStuff
  virtual void DoStuff(RequestPtr request, ::mojo::ScopedMessagePipeHandle pipe, DoStuffCallback callback) = 0;


  using DoStuff2Callback = base::OnceCallback<void(const WTF::String&)>;
  
// @generated_from: sample.Factory.DoStuff2
  virtual void DoStuff2(::mojo::ScopedDataPipeConsumerHandle pipe, DoStuff2Callback callback) = 0;

  
// @generated_from: sample.Factory.CreateNamedObject
  virtual void CreateNamedObject(::mojo::PendingReceiver<NamedObject> obj) = 0;


  using RequestImportedInterfaceCallback = base::OnceCallback<void(::mojo::PendingReceiver<::imported::blink::ImportedInterface>)>;
  
// @generated_from: sample.Factory.RequestImportedInterface
  virtual void RequestImportedInterface(::mojo::PendingReceiver<::imported::blink::ImportedInterface> obj, RequestImportedInterfaceCallback callback) = 0;


  using TakeImportedInterfaceCallback = base::OnceCallback<void(::mojo::PendingRemote<::imported::blink::ImportedInterface>)>;
  
// @generated_from: sample.Factory.TakeImportedInterface
  virtual void TakeImportedInterface(::mojo::PendingRemote<::imported::blink::ImportedInterface> obj, TakeImportedInterfaceCallback callback) = 0;
};



// @generated_from: sample.NamedObject
class  NamedObjectProxy
    : public NamedObject {
 public:
  using InterfaceType = NamedObject;

  explicit NamedObjectProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: sample.NamedObject.SetName
  void SetName(const WTF::String& name) final;
  
// @generated_from: sample.NamedObject.GetName
  void GetName(GetNameCallback callback) final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};



// @generated_from: sample.Factory
class  FactoryProxy
    : public Factory {
 public:
  using InterfaceType = Factory;

  explicit FactoryProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: sample.Factory.DoStuff
  void DoStuff(RequestPtr request, ::mojo::ScopedMessagePipeHandle pipe, DoStuffCallback callback) final;
  
// @generated_from: sample.Factory.DoStuff2
  void DoStuff2(::mojo::ScopedDataPipeConsumerHandle pipe, DoStuff2Callback callback) final;
  
// @generated_from: sample.Factory.CreateNamedObject
  void CreateNamedObject(::mojo::PendingReceiver<NamedObject> obj) final;
  
// @generated_from: sample.Factory.RequestImportedInterface
  void RequestImportedInterface(::mojo::PendingReceiver<::imported::blink::ImportedInterface> obj, RequestImportedInterfaceCallback callback) final;
  
// @generated_from: sample.Factory.TakeImportedInterface
  void TakeImportedInterface(::mojo::PendingRemote<::imported::blink::ImportedInterface> obj, TakeImportedInterfaceCallback callback) final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};
class  NamedObjectStubDispatch {
 public:
  static bool Accept(NamedObject* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      NamedObject* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<NamedObject>>
class NamedObjectStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  NamedObjectStub() {}
  ~NamedObjectStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return NamedObjectStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return NamedObjectStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  FactoryStubDispatch {
 public:
  static bool Accept(Factory* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      Factory* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<Factory>>
class FactoryStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  FactoryStub() {}
  ~FactoryStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return FactoryStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return FactoryStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  NamedObjectRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  FactoryRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  NamedObjectResponseValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  FactoryResponseValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};









// @generated_from: sample.Request
class  Request {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<Request, T>::value>;
  using DataView = RequestDataView;
  using Data_ = internal::Request_Data;

  template <typename... Args>
  static RequestPtr New(Args&&... args) {
    return RequestPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static RequestPtr From(const U& u) {
    return mojo::TypeConverter<RequestPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, Request>::Convert(*this);
  }


  Request();

  Request(
      int32_t x,
      ::mojo::ScopedMessagePipeHandle pipe,
      base::Optional<WTF::Vector<::mojo::ScopedMessagePipeHandle>> more_pipes,
      ::mojo::PendingRemote<::imported::blink::ImportedInterface> obj);

  ~Request();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = RequestPtr>
  RequestPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, Request::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, Request::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        Request::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::Request_UnserializedMessageContext<
            UserType, Request::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<Request::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
                          UserType* output) {
    return Request::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::Request_UnserializedMessageContext<
            UserType, Request::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<Request::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: sample.Request.x
  int32_t x;
  
// @generated_from: sample.Request.pipe
  ::mojo::ScopedMessagePipeHandle pipe;
  
// @generated_from: sample.Request.more_pipes
  base::Optional<WTF::Vector<::mojo::ScopedMessagePipeHandle>> more_pipes;
  
// @generated_from: sample.Request.obj
  ::mojo::PendingRemote<::imported::blink::ImportedInterface> obj;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
  DISALLOW_COPY_AND_ASSIGN(Request);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, Request::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, Request::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, Request::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, Request::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}





// @generated_from: sample.Response
class  Response {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<Response, T>::value>;
  using DataView = ResponseDataView;
  using Data_ = internal::Response_Data;

  template <typename... Args>
  static ResponsePtr New(Args&&... args) {
    return ResponsePtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static ResponsePtr From(const U& u) {
    return mojo::TypeConverter<ResponsePtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, Response>::Convert(*this);
  }


  Response();

  Response(
      int32_t x,
      ::mojo::ScopedMessagePipeHandle pipe);

  ~Response();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = ResponsePtr>
  ResponsePtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, Response::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, Response::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        Response::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::Response_UnserializedMessageContext<
            UserType, Response::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<Response::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
                          UserType* output) {
    return Response::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::Response_UnserializedMessageContext<
            UserType, Response::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<Response::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: sample.Response.x
  int32_t x;
  
// @generated_from: sample.Response.pipe
  ::mojo::ScopedMessagePipeHandle pipe;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
  DISALLOW_COPY_AND_ASSIGN(Response);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, Response::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, Response::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, Response::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, Response::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}

template <typename StructPtrType>
RequestPtr Request::Clone() const {
  return New(
      mojo::Clone(x),
      mojo::Clone(pipe),
      mojo::Clone(more_pipes),
      mojo::Clone(obj)
  );
}

template <typename T, Request::EnableIfSame<T>*>
bool Request::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->x, other_struct.x))
    return false;
  if (!mojo::Equals(this->pipe, other_struct.pipe))
    return false;
  if (!mojo::Equals(this->more_pipes, other_struct.more_pipes))
    return false;
  if (!mojo::Equals(this->obj, other_struct.obj))
    return false;
  return true;
}

template <typename T, Request::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.x < rhs.x)
    return true;
  if (rhs.x < lhs.x)
    return false;
  if (lhs.pipe < rhs.pipe)
    return true;
  if (rhs.pipe < lhs.pipe)
    return false;
  if (lhs.more_pipes < rhs.more_pipes)
    return true;
  if (rhs.more_pipes < lhs.more_pipes)
    return false;
  if (lhs.obj < rhs.obj)
    return true;
  if (rhs.obj < lhs.obj)
    return false;
  return false;
}
template <typename StructPtrType>
ResponsePtr Response::Clone() const {
  return New(
      mojo::Clone(x),
      mojo::Clone(pipe)
  );
}

template <typename T, Response::EnableIfSame<T>*>
bool Response::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->x, other_struct.x))
    return false;
  if (!mojo::Equals(this->pipe, other_struct.pipe))
    return false;
  return true;
}

template <typename T, Response::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.x < rhs.x)
    return true;
  if (rhs.x < lhs.x)
    return false;
  if (lhs.pipe < rhs.pipe)
    return true;
  if (rhs.pipe < lhs.pipe)
    return false;
  return false;
}


}  // namespace blink
}  // namespace sample

namespace mojo {


template <>
struct  StructTraits<::sample::blink::Request::DataView,
                                         ::sample::blink::RequestPtr> {
  static bool IsNull(const ::sample::blink::RequestPtr& input) { return !input; }
  static void SetToNull(::sample::blink::RequestPtr* output) { output->reset(); }

  static decltype(::sample::blink::Request::x) x(
      const ::sample::blink::RequestPtr& input) {
    return input->x;
  }

  static  decltype(::sample::blink::Request::pipe)& pipe(
       ::sample::blink::RequestPtr& input) {
    return input->pipe;
  }

  static  decltype(::sample::blink::Request::more_pipes)& more_pipes(
       ::sample::blink::RequestPtr& input) {
    return input->more_pipes;
  }

  static  decltype(::sample::blink::Request::obj)& obj(
       ::sample::blink::RequestPtr& input) {
    return input->obj;
  }

  static bool Read(::sample::blink::Request::DataView input, ::sample::blink::RequestPtr* output);
};


template <>
struct  StructTraits<::sample::blink::Response::DataView,
                                         ::sample::blink::ResponsePtr> {
  static bool IsNull(const ::sample::blink::ResponsePtr& input) { return !input; }
  static void SetToNull(::sample::blink::ResponsePtr* output) { output->reset(); }

  static decltype(::sample::blink::Response::x) x(
      const ::sample::blink::ResponsePtr& input) {
    return input->x;
  }

  static  decltype(::sample::blink::Response::pipe)& pipe(
       ::sample::blink::ResponsePtr& input) {
    return input->pipe;
  }

  static bool Read(::sample::blink::Response::DataView input, ::sample::blink::ResponsePtr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_FACTORY_MOJOM_BLINK_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMjIxMywgImJlZ2luIjogMjIwMiwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogInNhbXBsZS5OYW1lZE9iamVjdCJ9fSwgeyJlbmQiOiAy
OTE5LCAiYmVnaW4iOiAyOTEyLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5
cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29n
bGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1
cmUiOiAic2FtcGxlLk5hbWVkT2JqZWN0LlNldE5hbWUifX0sIHsiZW5kIjogMzA5NiwgImJlZ2lu
IjogMzA4OSwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hv
cl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNv
bS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogInNhbXBs
ZS5OYW1lZE9iamVjdC5HZXROYW1lIn19LCB7ImVuZCI6IDMzMjEsICJiZWdpbiI6IDMzMTQsICJl
ZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIs
ICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0v
c3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJzYW1wbGUuRmFjdG9yeSJ9
fSwgeyJlbmQiOiA0MjA3LCAiYmVnaW4iOiA0MjAwLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2Vu
ZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJj
aHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pv
bSIsICJzaWduYXR1cmUiOiAic2FtcGxlLkZhY3RvcnkuRG9TdHVmZiJ9fSwgeyJlbmQiOiA0NDQy
LCAiYmVnaW4iOiA0NDM0LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUi
OiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVz
b3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUi
OiAic2FtcGxlLkZhY3RvcnkuRG9TdHVmZjIifX0sIHsiZW5kIjogNDYwNywgImJlZ2luIjogNDU5
MCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZp
bmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJv
bWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogInNhbXBsZS5GYWN0
b3J5LkNyZWF0ZU5hbWVkT2JqZWN0In19LCB7ImVuZCI6IDQ4OTEsICJiZWdpbiI6IDQ4NjcsICJl
ZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIs
ICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0v
c3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJzYW1wbGUuRmFjdG9yeS5S
ZXF1ZXN0SW1wb3J0ZWRJbnRlcmZhY2UifX0sIHsiZW5kIjogNTIzMiwgImJlZ2luIjogNTIxMSwg
ImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVz
IiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1
bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogInNhbXBsZS5GYWN0b3J5
LlRha2VJbXBvcnRlZEludGVyZmFjZSJ9fSwgeyJlbmQiOiA1NjI1LCAiYmVnaW4iOiA1NjE4LCAi
ZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMi
LCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVt
L3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAic2FtcGxlLk5hbWVkT2Jq
ZWN0LlNldE5hbWUifX0sIHsiZW5kIjogNTcyMiwgImJlZ2luIjogNTcxNSwgImVkZ2UiOiAiJS9r
eXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjog
eyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFu
Z3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogInNhbXBsZS5OYW1lZE9iamVjdC5HZXROYW1l
In19LCB7ImVuZCI6IDYwNzQsICJiZWdpbiI6IDYwNjcsICJlZGdlIjogIiUva3l0aGUvZWRnZS9n
ZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjog
ImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1v
am9tIiwgInNpZ25hdHVyZSI6ICJzYW1wbGUuRmFjdG9yeS5Eb1N0dWZmIn19LCB7ImVuZCI6IDYy
MjgsICJiZWdpbiI6IDYyMjAsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlw
ZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2ds
ZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVy
ZSI6ICJzYW1wbGUuRmFjdG9yeS5Eb1N0dWZmMiJ9fSwgeyJlbmQiOiA2Mzg2LCAiYmVnaW4iOiA2
MzY5LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2Rl
ZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2No
cm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAic2FtcGxlLkZh
Y3RvcnkuQ3JlYXRlTmFtZWRPYmplY3QifX0sIHsiZW5kIjogNjUzMCwgImJlZ2luIjogNjUwNiwg
ImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVz
IiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1
bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogInNhbXBsZS5GYWN0b3J5
LlJlcXVlc3RJbXBvcnRlZEludGVyZmFjZSJ9fSwgeyJlbmQiOiA2NzM2LCAiYmVnaW4iOiA2NzE1
LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmlu
ZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9t
aXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAic2FtcGxlLkZhY3Rv
cnkuVGFrZUltcG9ydGVkSW50ZXJmYWNlIn19LCB7ImVuZCI6IDk5NjAsICJiZWdpbiI6IDk5NTMs
ICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5l
cyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21p
dW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJzYW1wbGUuUmVxdWVz
dCJ9fSwgeyJlbmQiOiAxMzQwMCwgImJlZ2luIjogMTMzOTksICJlZGdlIjogIiUva3l0aGUvZWRn
ZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVz
IjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjog
Im1vam9tIiwgInNpZ25hdHVyZSI6ICJzYW1wbGUuUmVxdWVzdC54In19LCB7ImVuZCI6IDEzNDgz
LCAiYmVnaW4iOiAxMzQ3OSwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBl
IjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xl
c291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJl
IjogInNhbXBsZS5SZXF1ZXN0LnBpcGUifX0sIHsiZW5kIjogMTM2MDcsICJiZWdpbiI6IDEzNTk3
LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmlu
ZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9t
aXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAic2FtcGxlLlJlcXVl
c3QubW9yZV9waXBlcyJ9fSwgeyJlbmQiOiAxMzcxNiwgImJlZ2luIjogMTM3MTMsICJlZGdlIjog
IiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFt
ZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwg
Imxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJzYW1wbGUuUmVxdWVzdC5vYmoifX0s
IHsiZW5kIjogMTQ3NTAsICJiZWdpbiI6IDE0NzQyLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2Vu
ZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJj
aHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pv
bSIsICJzaWduYXR1cmUiOiAic2FtcGxlLlJlc3BvbnNlIn19LCB7ImVuZCI6IDE4MDY0LCAiYmVn
aW4iOiAxODA2MywgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFu
Y2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNl
LmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogInNh
bXBsZS5SZXNwb25zZS54In19LCB7ImVuZCI6IDE4MTQ4LCAiYmVnaW4iOiAxODE0NCwgImVkZ2Ui
OiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZu
YW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMi
LCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogInNhbXBsZS5SZXNwb25zZS5waXBl
In19XSwgInR5cGUiOiAia3l0aGUwIn0=
*/