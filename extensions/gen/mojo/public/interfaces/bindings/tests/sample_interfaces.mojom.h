// mojo/public/interfaces/bindings/tests/sample_interfaces.mojom.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_INTERFACES_MOJOM_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_INTERFACES_MOJOM_H_

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
#include "mojo/public/interfaces/bindings/tests/sample_interfaces.mojom-shared.h"
#include "mojo/public/interfaces/bindings/tests/sample_interfaces.mojom-forward.h"
#include "mojo/public/mojom/base/generic_pending_receiver.mojom.h"
#include <string>
#include <vector>

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

class PingTestProxy;

template <typename ImplRefTraits>
class PingTestStub;

class PingTestRequestValidator;
class PingTestResponseValidator;


// @generated_from: sample.PingTest
class  PingTest
    : public PingTestInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = PingTestInterfaceBase;
  using Proxy_ = PingTestProxy;

  template <typename ImplRefTraits>
  using Stub_ = PingTestStub<ImplRefTraits>;

  using RequestValidator_ = PingTestRequestValidator;
  using ResponseValidator_ = PingTestResponseValidator;
  enum MethodMinVersions : uint32_t {
    kPingMinVersion = 0,
  };
  virtual ~PingTest() {}


  using PingCallback = base::OnceCallback<void()>;
  
// @generated_from: sample.PingTest.Ping
  virtual void Ping(PingCallback callback) = 0;
};

class ProviderProxy;

template <typename ImplRefTraits>
class ProviderStub;

class ProviderRequestValidator;
class ProviderResponseValidator;


// @generated_from: sample.Provider
class  Provider
    : public ProviderInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = ProviderInterfaceBase;
  using Proxy_ = ProviderProxy;

  template <typename ImplRefTraits>
  using Stub_ = ProviderStub<ImplRefTraits>;

  using RequestValidator_ = ProviderRequestValidator;
  using ResponseValidator_ = ProviderResponseValidator;
  enum MethodMinVersions : uint32_t {
    kEchoStringMinVersion = 0,
    kEchoStringsMinVersion = 0,
    kEchoMessagePipeHandleMinVersion = 0,
    kEchoEnumMinVersion = 0,
    kEchoIntMinVersion = 0,
  };
  virtual ~Provider() {}


  using EchoStringCallback = base::OnceCallback<void(const std::string&)>;
  
// @generated_from: sample.Provider.EchoString
  virtual void EchoString(const std::string& a, EchoStringCallback callback) = 0;


  using EchoStringsCallback = base::OnceCallback<void(const std::string&, const std::string&)>;
  
// @generated_from: sample.Provider.EchoStrings
  virtual void EchoStrings(const std::string& a, const std::string& b, EchoStringsCallback callback) = 0;


  using EchoMessagePipeHandleCallback = base::OnceCallback<void(::mojo::ScopedMessagePipeHandle)>;
  
// @generated_from: sample.Provider.EchoMessagePipeHandle
  virtual void EchoMessagePipeHandle(::mojo::ScopedMessagePipeHandle a, EchoMessagePipeHandleCallback callback) = 0;


  using EchoEnumCallback = base::OnceCallback<void(Enum)>;
  
// @generated_from: sample.Provider.EchoEnum
  virtual void EchoEnum(Enum a, EchoEnumCallback callback) = 0;


  using EchoIntCallback = base::OnceCallback<void(int32_t)>;
  
// @generated_from: sample.Provider.EchoInt
  virtual void EchoInt(int32_t a, EchoIntCallback callback) = 0;
};

class IntegerAccessorProxy;

template <typename ImplRefTraits>
class IntegerAccessorStub;

class IntegerAccessorRequestValidator;
class IntegerAccessorResponseValidator;


// @generated_from: sample.IntegerAccessor
class  IntegerAccessor
    : public IntegerAccessorInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 3;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = IntegerAccessorInterfaceBase;
  using Proxy_ = IntegerAccessorProxy;

  template <typename ImplRefTraits>
  using Stub_ = IntegerAccessorStub<ImplRefTraits>;

  using RequestValidator_ = IntegerAccessorRequestValidator;
  using ResponseValidator_ = IntegerAccessorResponseValidator;
  enum MethodMinVersions : uint32_t {
    kGetIntegerMinVersion = 0,
    kSetIntegerMinVersion = 1,
  };
  virtual ~IntegerAccessor() {}


  using GetIntegerCallback = base::OnceCallback<void(int64_t, Enum)>;
  
// @generated_from: sample.IntegerAccessor.GetInteger
  virtual void GetInteger(GetIntegerCallback callback) = 0;

  
// @generated_from: sample.IntegerAccessor.SetInteger
  virtual void SetInteger(int64_t data, Enum type) = 0;
};

class InterfaceFactoryProxy;

template <typename ImplRefTraits>
class InterfaceFactoryStub;

class InterfaceFactoryRequestValidator;


// @generated_from: sample.InterfaceFactory
class  InterfaceFactory
    : public InterfaceFactoryInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = InterfaceFactoryInterfaceBase;
  using Proxy_ = InterfaceFactoryProxy;

  template <typename ImplRefTraits>
  using Stub_ = InterfaceFactoryStub<ImplRefTraits>;

  using RequestValidator_ = InterfaceFactoryRequestValidator;
  using ResponseValidator_ = mojo::PassThroughFilter;
  enum MethodMinVersions : uint32_t {
    kBindInterfaceMinVersion = 0,
  };
  virtual ~InterfaceFactory() {}

  
// @generated_from: sample.InterfaceFactory.BindInterface
  virtual void BindInterface(::mojo::GenericPendingReceiver receiver) = 0;
};



// @generated_from: sample.PingTest
class  PingTestProxy
    : public PingTest {
 public:
  using InterfaceType = PingTest;

  explicit PingTestProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: sample.PingTest.Ping
  void Ping(PingCallback callback) final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};



// @generated_from: sample.Provider
class  ProviderProxy
    : public Provider {
 public:
  using InterfaceType = Provider;

  explicit ProviderProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: sample.Provider.EchoString
  void EchoString(const std::string& a, EchoStringCallback callback) final;
  
// @generated_from: sample.Provider.EchoStrings
  void EchoStrings(const std::string& a, const std::string& b, EchoStringsCallback callback) final;
  
// @generated_from: sample.Provider.EchoMessagePipeHandle
  void EchoMessagePipeHandle(::mojo::ScopedMessagePipeHandle a, EchoMessagePipeHandleCallback callback) final;
  
// @generated_from: sample.Provider.EchoEnum
  void EchoEnum(Enum a, EchoEnumCallback callback) final;
  
// @generated_from: sample.Provider.EchoInt
  void EchoInt(int32_t a, EchoIntCallback callback) final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};



// @generated_from: sample.IntegerAccessor
class  IntegerAccessorProxy
    : public IntegerAccessor {
 public:
  using InterfaceType = IntegerAccessor;

  explicit IntegerAccessorProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: sample.IntegerAccessor.GetInteger
  void GetInteger(GetIntegerCallback callback) final;
  
// @generated_from: sample.IntegerAccessor.SetInteger
  void SetInteger(int64_t data, Enum type) final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};



// @generated_from: sample.InterfaceFactory
class  InterfaceFactoryProxy
    : public InterfaceFactory {
 public:
  using InterfaceType = InterfaceFactory;

  explicit InterfaceFactoryProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: sample.InterfaceFactory.BindInterface
  void BindInterface(::mojo::GenericPendingReceiver receiver) final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};
class  PingTestStubDispatch {
 public:
  static bool Accept(PingTest* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      PingTest* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<PingTest>>
class PingTestStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  PingTestStub() {}
  ~PingTestStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return PingTestStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return PingTestStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  ProviderStubDispatch {
 public:
  static bool Accept(Provider* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      Provider* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<Provider>>
class ProviderStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  ProviderStub() {}
  ~ProviderStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return ProviderStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return ProviderStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  IntegerAccessorStubDispatch {
 public:
  static bool Accept(IntegerAccessor* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      IntegerAccessor* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<IntegerAccessor>>
class IntegerAccessorStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  IntegerAccessorStub() {}
  ~IntegerAccessorStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return IntegerAccessorStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return IntegerAccessorStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  InterfaceFactoryStubDispatch {
 public:
  static bool Accept(InterfaceFactory* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      InterfaceFactory* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<InterfaceFactory>>
class InterfaceFactoryStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  InterfaceFactoryStub() {}
  ~InterfaceFactoryStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return InterfaceFactoryStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return InterfaceFactoryStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  PingTestRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  ProviderRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  IntegerAccessorRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  InterfaceFactoryRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  PingTestResponseValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  ProviderResponseValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  IntegerAccessorResponseValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};





}  // namespace sample

namespace mojo {

}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_INTERFACES_MOJOM_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTkzNiwgImJlZ2luIjogMTkyOCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogInNhbXBsZS5QaW5nVGVzdCJ9fSwgeyJlbmQiOiAyNjMz
LCAiYmVnaW4iOiAyNjI5LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUi
OiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVz
b3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUi
OiAic2FtcGxlLlBpbmdUZXN0LlBpbmcifX0sIHsiZW5kIjogMjg2MSwgImJlZ2luIjogMjg1Mywg
ImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVz
IiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1
bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogInNhbXBsZS5Qcm92aWRl
ciJ9fSwgeyJlbmQiOiAzNzMxLCAiYmVnaW4iOiAzNzIxLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2Uv
Z2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6
ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJt
b2pvbSIsICJzaWduYXR1cmUiOiAic2FtcGxlLlByb3ZpZGVyLkVjaG9TdHJpbmcifX0sIHsiZW5k
IjogMzk2MywgImJlZ2luIjogMzk1MiwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIs
ICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0u
Z29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2ln
bmF0dXJlIjogInNhbXBsZS5Qcm92aWRlci5FY2hvU3RyaW5ncyJ9fSwgeyJlbmQiOiA0MjQxLCAi
YmVnaW4iOiA0MjIwLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAi
YW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3Vy
Y2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAi
c2FtcGxlLlByb3ZpZGVyLkVjaG9NZXNzYWdlUGlwZUhhbmRsZSJ9fSwgeyJlbmQiOiA0NDU0LCAi
YmVnaW4iOiA0NDQ2LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAi
YW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3Vy
Y2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAi
c2FtcGxlLlByb3ZpZGVyLkVjaG9FbnVtIn19LCB7ImVuZCI6IDQ2MjcsICJiZWdpbiI6IDQ2MjAs
ICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5l
cyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21p
dW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJzYW1wbGUuUHJvdmlk
ZXIuRWNob0ludCJ9fSwgeyJlbmQiOiA0OTExLCAiYmVnaW4iOiA0ODk2LCAiZWRnZSI6ICIlL2t5
dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7
ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5n
dWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAic2FtcGxlLkludGVnZXJBY2Nlc3NvciJ9fSwg
eyJlbmQiOiA1NzMyLCAiYmVnaW4iOiA1NzIyLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJh
dGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJv
bWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIs
ICJzaWduYXR1cmUiOiAic2FtcGxlLkludGVnZXJBY2Nlc3Nvci5HZXRJbnRlZ2VyIn19LCB7ImVu
ZCI6IDU4NTAsICJiZWdpbiI6IDU4NDAsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMi
LCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVt
Lmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNp
Z25hdHVyZSI6ICJzYW1wbGUuSW50ZWdlckFjY2Vzc29yLlNldEludGVnZXIifX0sIHsiZW5kIjog
NjA4NywgImJlZ2luIjogNjA3MSwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0
eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29v
Z2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0
dXJlIjogInNhbXBsZS5JbnRlcmZhY2VGYWN0b3J5In19LCB7ImVuZCI6IDY4MTMsICJiZWdpbiI6
IDY4MDAsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3Jf
ZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20v
Y2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJzYW1wbGUu
SW50ZXJmYWNlRmFjdG9yeS5CaW5kSW50ZXJmYWNlIn19LCB7ImVuZCI6IDcxMTgsICJiZWdpbiI6
IDcxMTQsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3Jf
ZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20v
Y2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJzYW1wbGUu
UGluZ1Rlc3QuUGluZyJ9fSwgeyJlbmQiOiA3NDc5LCAiYmVnaW4iOiA3NDY5LCAiZWRnZSI6ICIl
L2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUi
OiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJs
YW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAic2FtcGxlLlByb3ZpZGVyLkVjaG9TdHJp
bmcifX0sIHsiZW5kIjogNzYwNywgImJlZ2luIjogNzU5NiwgImVkZ2UiOiAiJS9reXRoZS9lZGdl
L2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMi
OiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAi
bW9qb20iLCAic2lnbmF0dXJlIjogInNhbXBsZS5Qcm92aWRlci5FY2hvU3RyaW5ncyJ9fSwgeyJl
bmQiOiA3Nzc4LCAiYmVnaW4iOiA3NzU3LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVz
IiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1
bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJz
aWduYXR1cmUiOiAic2FtcGxlLlByb3ZpZGVyLkVjaG9NZXNzYWdlUGlwZUhhbmRsZSJ9fSwgeyJl
bmQiOiA3OTI0LCAiYmVnaW4iOiA3OTE2LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVz
IiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1
bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJz
aWduYXR1cmUiOiAic2FtcGxlLlByb3ZpZGVyLkVjaG9FbnVtIn19LCB7ImVuZCI6IDgwMjgsICJi
ZWdpbiI6IDgwMjEsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJh
bmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJj
ZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJz
YW1wbGUuUHJvdmlkZXIuRWNob0ludCJ9fSwgeyJlbmQiOiA4NDQ1LCAiYmVnaW4iOiA4NDM1LCAi
ZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMi
LCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVt
L3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAic2FtcGxlLkludGVnZXJB
Y2Nlc3Nvci5HZXRJbnRlZ2VyIn19LCB7ImVuZCI6IDg1NTYsICJiZWdpbiI6IDg1NDYsICJlZGdl
IjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2
bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3Jj
IiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJzYW1wbGUuSW50ZWdlckFjY2Vz
c29yLlNldEludGVnZXIifX0sIHsiZW5kIjogODk3MywgImJlZ2luIjogODk2MCwgImVkZ2UiOiAi
JS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1l
IjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAi
bGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogInNhbXBsZS5JbnRlcmZhY2VGYWN0b3J5
LkJpbmRJbnRlcmZhY2UifX1dLCAidHlwZSI6ICJreXRoZTAifQ==
*/