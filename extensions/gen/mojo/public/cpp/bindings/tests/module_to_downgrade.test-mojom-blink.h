// mojo/public/cpp/bindings/tests/module_to_downgrade.test-mojom-blink.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_TESTS_MODULE_TO_DOWNGRADE_TEST_MOJOM_BLINK_H_
#define MOJO_PUBLIC_CPP_BINDINGS_TESTS_MODULE_TO_DOWNGRADE_TEST_MOJOM_BLINK_H_

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
#include "mojo/public/cpp/bindings/tests/module_to_downgrade.test-mojom-shared.h"
#include "mojo/public/cpp/bindings/tests/module_to_downgrade.test-mojom-blink-forward.h"

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


namespace mojo {
namespace test {
namespace mojom_types_downgrader_unittest {
namespace mojom {
namespace blink {

class FooProxy;

template <typename ImplRefTraits>
class FooStub;

class FooRequestValidator;


// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.Foo
class  Foo
    : public FooInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = FooInterfaceBase;
  using Proxy_ = FooProxy;

  template <typename ImplRefTraits>
  using Stub_ = FooStub<ImplRefTraits>;

  using RequestValidator_ = FooRequestValidator;
  using ResponseValidator_ = mojo::PassThroughFilter;
  enum MethodMinVersions : uint32_t {
    kDummyMethodMinVersion = 0,
  };
  virtual ~Foo() {}

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.Foo.DummyMethod
  virtual void DummyMethod() = 0;
};

class DowngradedTestInterfaceProxy;

template <typename ImplRefTraits>
class DowngradedTestInterfaceStub;

class DowngradedTestInterfaceRequestValidator;
class DowngradedTestInterfaceResponseValidator;


// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface
class  DowngradedTestInterface
    : public DowngradedTestInterfaceInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = true;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = DowngradedTestInterfaceInterfaceBase;
  using Proxy_ = DowngradedTestInterfaceProxy;

  template <typename ImplRefTraits>
  using Stub_ = DowngradedTestInterfaceStub<ImplRefTraits>;

  using RequestValidator_ = DowngradedTestInterfaceRequestValidator;
  using ResponseValidator_ = DowngradedTestInterfaceResponseValidator;
  enum MethodMinVersions : uint32_t {
    kInterfaceRequestMinVersion = 0,
    kInterfacePtrMinVersion = 0,
    kAssociatedInterfacePtrInfoMinVersion = 0,
    kAssociatedInterfaceRequestMinVersion = 0,
    kPendingReceiverMinVersion = 0,
    kPendingRemoteMinVersion = 0,
    kPendingAssociatedReceiverMinVersion = 0,
    kPendingAssociatedRemoteMinVersion = 0,
    kMultipleParams2MinVersion = 0,
    kMultipleParams3MinVersion = 0,
    kMultipleParams4MinVersion = 0,
    kMethodWithResponseCallbackOneLineMinVersion = 0,
    kMethodWithResponseCallbackTwoLinesMinVersion = 0,
    kOddSpacesMinVersion = 0,
    kOddSpacesAndLineBreakMinVersion = 0,
  };
  virtual ~DowngradedTestInterface() {}

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.InterfaceRequest
  virtual void InterfaceRequest(FooRequest request) = 0;

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.InterfacePtr
  virtual void InterfacePtr(FooPtr ptr) = 0;

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.AssociatedInterfacePtrInfo
  virtual void AssociatedInterfacePtrInfo(FooAssociatedPtrInfo associated_ptr_info) = 0;

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.AssociatedInterfaceRequest
  virtual void AssociatedInterfaceRequest(FooAssociatedRequest associated_request) = 0;

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.PendingReceiver
  virtual void PendingReceiver(FooRequest receiver) = 0;

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.PendingRemote
  virtual void PendingRemote(FooPtr remote) = 0;

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.PendingAssociatedReceiver
  virtual void PendingAssociatedReceiver(FooAssociatedRequest associated_remote) = 0;

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.PendingAssociatedRemote
  virtual void PendingAssociatedRemote(FooAssociatedPtrInfo associated_receiver) = 0;

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.MultipleParams2
  virtual void MultipleParams2(FooPtr remote, FooRequest receiver) = 0;

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.MultipleParams3
  virtual void MultipleParams3(FooPtr remote, FooRequest receiver, FooAssociatedPtrInfo associated_remote) = 0;

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.MultipleParams4
  virtual void MultipleParams4(FooPtr remote, FooRequest receiver, FooAssociatedPtrInfo associated_remote, FooAssociatedRequest associated_receiver) = 0;


  using MethodWithResponseCallbackOneLineCallback = base::OnceCallback<void()>;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.MethodWithResponseCallbackOneLine
  virtual void MethodWithResponseCallbackOneLine(FooPtr data, MethodWithResponseCallbackOneLineCallback callback) = 0;


  using MethodWithResponseCallbackTwoLinesCallback = base::OnceCallback<void(FooRequest)>;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.MethodWithResponseCallbackTwoLines
  virtual void MethodWithResponseCallbackTwoLines(FooPtr data, MethodWithResponseCallbackTwoLinesCallback callback) = 0;

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.OddSpaces
  virtual void OddSpaces(FooPtr remote, FooRequest receiver) = 0;

  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.OddSpacesAndLineBreak
  virtual void OddSpacesAndLineBreak(FooPtr remote, FooRequest receiver) = 0;
};



// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.Foo
class  FooProxy
    : public Foo {
 public:
  using InterfaceType = Foo;

  explicit FooProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.Foo.DummyMethod
  void DummyMethod() final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};



// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface
class  DowngradedTestInterfaceProxy
    : public DowngradedTestInterface {
 public:
  using InterfaceType = DowngradedTestInterface;

  explicit DowngradedTestInterfaceProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.InterfaceRequest
  void InterfaceRequest(FooRequest request) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.InterfacePtr
  void InterfacePtr(FooPtr ptr) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.AssociatedInterfacePtrInfo
  void AssociatedInterfacePtrInfo(FooAssociatedPtrInfo associated_ptr_info) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.AssociatedInterfaceRequest
  void AssociatedInterfaceRequest(FooAssociatedRequest associated_request) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.PendingReceiver
  void PendingReceiver(FooRequest receiver) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.PendingRemote
  void PendingRemote(FooPtr remote) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.PendingAssociatedReceiver
  void PendingAssociatedReceiver(FooAssociatedRequest associated_remote) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.PendingAssociatedRemote
  void PendingAssociatedRemote(FooAssociatedPtrInfo associated_receiver) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.MultipleParams2
  void MultipleParams2(FooPtr remote, FooRequest receiver) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.MultipleParams3
  void MultipleParams3(FooPtr remote, FooRequest receiver, FooAssociatedPtrInfo associated_remote) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.MultipleParams4
  void MultipleParams4(FooPtr remote, FooRequest receiver, FooAssociatedPtrInfo associated_remote, FooAssociatedRequest associated_receiver) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.MethodWithResponseCallbackOneLine
  void MethodWithResponseCallbackOneLine(FooPtr data, MethodWithResponseCallbackOneLineCallback callback) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.MethodWithResponseCallbackTwoLines
  void MethodWithResponseCallbackTwoLines(FooPtr data, MethodWithResponseCallbackTwoLinesCallback callback) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.OddSpaces
  void OddSpaces(FooPtr remote, FooRequest receiver) final;
  
// @generated_from: mojo.test.mojom_types_downgrader_unittest.mojom.DowngradedTestInterface.OddSpacesAndLineBreak
  void OddSpacesAndLineBreak(FooPtr remote, FooRequest receiver) final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};
class  FooStubDispatch {
 public:
  static bool Accept(Foo* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      Foo* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<Foo>>
class FooStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  FooStub() {}
  ~FooStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return FooStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return FooStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  DowngradedTestInterfaceStubDispatch {
 public:
  static bool Accept(DowngradedTestInterface* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      DowngradedTestInterface* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<DowngradedTestInterface>>
class DowngradedTestInterfaceStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  DowngradedTestInterfaceStub() {}
  ~DowngradedTestInterfaceStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return DowngradedTestInterfaceStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return DowngradedTestInterfaceStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  FooRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  DowngradedTestInterfaceRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  DowngradedTestInterfaceResponseValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};





}  // namespace blink
}  // namespace mojom
}  // namespace mojom_types_downgrader_unittest
}  // namespace test
}  // namespace mojo

namespace mojo {

}  // namespace mojo

#endif  // MOJO_PUBLIC_CPP_BINDINGS_TESTS_MODULE_TO_DOWNGRADE_TEST_MOJOM_BLINK_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMjE5MywgImJlZ2luIjogMjE5MCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5tb2pvbV90eXBlc19kb3duZ3JhZGVy
X3VuaXR0ZXN0Lm1vam9tLkZvbyJ9fSwgeyJlbmQiOiAyODYzLCAiYmVnaW4iOiAyODUyLCAiZWRn
ZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAi
dm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3Ny
YyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5
cGVzX2Rvd25ncmFkZXJfdW5pdHRlc3QubW9qb20uRm9vLkR1bW15TWV0aG9kIn19LCB7ImVuZCI6
IDMyMDEsICJiZWdpbiI6IDMxNzgsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAi
dHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdv
b2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25h
dHVyZSI6ICJtb2pvLnRlc3QubW9qb21fdHlwZXNfZG93bmdyYWRlcl91bml0dGVzdC5tb2pvbS5E
b3duZ3JhZGVkVGVzdEludGVyZmFjZSJ9fSwgeyJlbmQiOiA0NjE4LCAiYmVnaW4iOiA0NjAyLCAi
ZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMi
LCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVt
L3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9t
X3R5cGVzX2Rvd25ncmFkZXJfdW5pdHRlc3QubW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2Uu
SW50ZXJmYWNlUmVxdWVzdCJ9fSwgeyJlbmQiOiA0NzgwLCAiYmVnaW4iOiA0NzY4LCAiZWRnZSI6
ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5h
bWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIs
ICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVz
X2Rvd25ncmFkZXJfdW5pdHRlc3QubW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuSW50ZXJm
YWNlUHRyIn19LCB7ImVuZCI6IDQ5NjIsICJiZWdpbiI6IDQ5MzYsICJlZGdlIjogIiUva3l0aGUv
ZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29y
cHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdl
IjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QubW9qb21fdHlwZXNfZG93bmdyYWRl
cl91bml0dGVzdC5tb2pvbS5Eb3duZ3JhZGVkVGVzdEludGVyZmFjZS5Bc3NvY2lhdGVkSW50ZXJm
YWNlUHRySW5mbyJ9fSwgeyJlbmQiOiA1MTc0LCAiYmVnaW4iOiA1MTQ4LCAiZWRnZSI6ICIlL2t5
dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7
ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5n
dWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25n
cmFkZXJfdW5pdHRlc3QubW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuQXNzb2NpYXRlZElu
dGVyZmFjZVJlcXVlc3QifX0sIHsiZW5kIjogNTM2MywgImJlZ2luIjogNTM0OCwgImVkZ2UiOiAi
JS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1l
IjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAi
bGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5tb2pvbV90eXBlc19k
b3duZ3JhZGVyX3VuaXR0ZXN0Lm1vam9tLkRvd25ncmFkZWRUZXN0SW50ZXJmYWNlLlBlbmRpbmdS
ZWNlaXZlciJ9fSwgeyJlbmQiOiA1NTI4LCAiYmVnaW4iOiA1NTE1LCAiZWRnZSI6ICIlL2t5dGhl
L2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNv
cnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFn
ZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25ncmFk
ZXJfdW5pdHRlc3QubW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuUGVuZGluZ1JlbW90ZSJ9
fSwgeyJlbmQiOiA1NzExLCAiYmVnaW4iOiA1Njg2LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2Vu
ZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJj
aHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pv
bSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25ncmFkZXJfdW5pdHRl
c3QubW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuUGVuZGluZ0Fzc29jaWF0ZWRSZWNlaXZl
ciJ9fSwgeyJlbmQiOiA1OTE1LCAiYmVnaW4iOiA1ODkyLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2Uv
Z2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6
ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJt
b2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25ncmFkZXJfdW5p
dHRlc3QubW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuUGVuZGluZ0Fzc29jaWF0ZWRSZW1v
dGUifX0sIHsiZW5kIjogNjEwNSwgImJlZ2luIjogNjA5MCwgImVkZ2UiOiAiJS9reXRoZS9lZGdl
L2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMi
OiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAi
bW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5tb2pvbV90eXBlc19kb3duZ3JhZGVyX3Vu
aXR0ZXN0Lm1vam9tLkRvd25ncmFkZWRUZXN0SW50ZXJmYWNlLk11bHRpcGxlUGFyYW1zMiJ9fSwg
eyJlbmQiOiA2Mjg5LCAiYmVnaW4iOiA2Mjc0LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJh
dGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJv
bWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIs
ICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25ncmFkZXJfdW5pdHRlc3Qu
bW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuTXVsdGlwbGVQYXJhbXMzIn19LCB7ImVuZCI6
IDY1MTMsICJiZWdpbiI6IDY0OTgsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAi
dHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdv
b2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25h
dHVyZSI6ICJtb2pvLnRlc3QubW9qb21fdHlwZXNfZG93bmdyYWRlcl91bml0dGVzdC5tb2pvbS5E
b3duZ3JhZGVkVGVzdEludGVyZmFjZS5NdWx0aXBsZVBhcmFtczQifX0sIHsiZW5kIjogNjg5Niwg
ImJlZ2luIjogNjg2MywgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjog
ImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291
cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjog
Im1vam8udGVzdC5tb2pvbV90eXBlc19kb3duZ3JhZGVyX3VuaXR0ZXN0Lm1vam9tLkRvd25ncmFk
ZWRUZXN0SW50ZXJmYWNlLk1ldGhvZFdpdGhSZXNwb25zZUNhbGxiYWNrT25lTGluZSJ9fSwgeyJl
bmQiOiA3MjM5LCAiYmVnaW4iOiA3MjA1LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVz
IiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1
bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJz
aWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25ncmFkZXJfdW5pdHRlc3QubW9q
b20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuTWV0aG9kV2l0aFJlc3BvbnNlQ2FsbGJhY2tUd29M
aW5lcyJ9fSwgeyJlbmQiOiA3NDQxLCAiYmVnaW4iOiA3NDMyLCAiZWRnZSI6ICIlL2t5dGhlL2Vk
Z2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1
cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6
ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25ncmFkZXJf
dW5pdHRlc3QubW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuT2RkU3BhY2VzIn19LCB7ImVu
ZCI6IDc2MzcsICJiZWdpbiI6IDc2MTYsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMi
LCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVt
Lmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNp
Z25hdHVyZSI6ICJtb2pvLnRlc3QubW9qb21fdHlwZXNfZG93bmdyYWRlcl91bml0dGVzdC5tb2pv
bS5Eb3duZ3JhZGVkVGVzdEludGVyZmFjZS5PZGRTcGFjZXNBbmRMaW5lQnJlYWsifX0sIHsiZW5k
IjogODAwMywgImJlZ2luIjogNzk5MiwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIs
ICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0u
Z29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2ln
bmF0dXJlIjogIm1vam8udGVzdC5tb2pvbV90eXBlc19kb3duZ3JhZGVyX3VuaXR0ZXN0Lm1vam9t
LkZvby5EdW1teU1ldGhvZCJ9fSwgeyJlbmQiOiA4NTI3LCAiYmVnaW4iOiA4NTExLCAiZWRnZSI6
ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5h
bWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIs
ICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVz
X2Rvd25ncmFkZXJfdW5pdHRlc3QubW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuSW50ZXJm
YWNlUmVxdWVzdCJ9fSwgeyJlbmQiOiA4NjgyLCAiYmVnaW4iOiA4NjcwLCAiZWRnZSI6ICIlL2t5
dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7
ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5n
dWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25n
cmFkZXJfdW5pdHRlc3QubW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuSW50ZXJmYWNlUHRy
In19LCB7ImVuZCI6IDg4NTcsICJiZWdpbiI6IDg4MzEsICJlZGdlIjogIiUva3l0aGUvZWRnZS9n
ZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjog
ImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1v
am9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QubW9qb21fdHlwZXNfZG93bmdyYWRlcl91bml0
dGVzdC5tb2pvbS5Eb3duZ3JhZGVkVGVzdEludGVyZmFjZS5Bc3NvY2lhdGVkSW50ZXJmYWNlUHRy
SW5mbyJ9fSwgeyJlbmQiOiA5MDYyLCAiYmVnaW4iOiA5MDM2LCAiZWRnZSI6ICIlL2t5dGhlL2Vk
Z2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1
cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6
ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25ncmFkZXJf
dW5pdHRlc3QubW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuQXNzb2NpYXRlZEludGVyZmFj
ZVJlcXVlc3QifX0sIHsiZW5kIjogOTI0NCwgImJlZ2luIjogOTIyOSwgImVkZ2UiOiAiJS9reXRo
ZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJj
b3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3Vh
Z2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5tb2pvbV90eXBlc19kb3duZ3Jh
ZGVyX3VuaXR0ZXN0Lm1vam9tLkRvd25ncmFkZWRUZXN0SW50ZXJmYWNlLlBlbmRpbmdSZWNlaXZl
ciJ9fSwgeyJlbmQiOiA5NDAyLCAiYmVnaW4iOiA5Mzg5LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2Uv
Z2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6
ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJt
b2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25ncmFkZXJfdW5p
dHRlc3QubW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuUGVuZGluZ1JlbW90ZSJ9fSwgeyJl
bmQiOiA5NTc4LCAiYmVnaW4iOiA5NTUzLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVz
IiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1
bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJz
aWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25ncmFkZXJfdW5pdHRlc3QubW9q
b20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuUGVuZGluZ0Fzc29jaWF0ZWRSZWNlaXZlciJ9fSwg
eyJlbmQiOiA5Nzc1LCAiYmVnaW4iOiA5NzUyLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJh
dGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJv
bWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIs
ICJzaWduYXR1cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25ncmFkZXJfdW5pdHRlc3Qu
bW9qb20uRG93bmdyYWRlZFRlc3RJbnRlcmZhY2UuUGVuZGluZ0Fzc29jaWF0ZWRSZW1vdGUifX0s
IHsiZW5kIjogOTk1OCwgImJlZ2luIjogOTk0MywgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVy
YXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hy
b21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20i
LCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5tb2pvbV90eXBlc19kb3duZ3JhZGVyX3VuaXR0ZXN0
Lm1vam9tLkRvd25ncmFkZWRUZXN0SW50ZXJmYWNlLk11bHRpcGxlUGFyYW1zMiJ9fSwgeyJlbmQi
OiAxMDEzNSwgImJlZ2luIjogMTAxMjAsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMi
LCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVt
Lmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNp
Z25hdHVyZSI6ICJtb2pvLnRlc3QubW9qb21fdHlwZXNfZG93bmdyYWRlcl91bml0dGVzdC5tb2pv
bS5Eb3duZ3JhZGVkVGVzdEludGVyZmFjZS5NdWx0aXBsZVBhcmFtczMifX0sIHsiZW5kIjogMTAz
NTIsICJiZWdpbiI6IDEwMzM3LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5
cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29n
bGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1
cmUiOiAibW9qby50ZXN0Lm1vam9tX3R5cGVzX2Rvd25ncmFkZXJfdW5pdHRlc3QubW9qb20uRG93
bmdyYWRlZFRlc3RJbnRlcmZhY2UuTXVsdGlwbGVQYXJhbXM0In19LCB7ImVuZCI6IDEwNjQ3LCAi
YmVnaW4iOiAxMDYxNCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjog
ImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291
cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjog
Im1vam8udGVzdC5tb2pvbV90eXBlc19kb3duZ3JhZGVyX3VuaXR0ZXN0Lm1vam9tLkRvd25ncmFk
ZWRUZXN0SW50ZXJmYWNlLk1ldGhvZFdpdGhSZXNwb25zZUNhbGxiYWNrT25lTGluZSJ9fSwgeyJl
bmQiOiAxMDg5MSwgImJlZ2luIjogMTA4NTcsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0
ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9t
aXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwg
InNpZ25hdHVyZSI6ICJtb2pvLnRlc3QubW9qb21fdHlwZXNfZG93bmdyYWRlcl91bml0dGVzdC5t
b2pvbS5Eb3duZ3JhZGVkVGVzdEludGVyZmFjZS5NZXRob2RXaXRoUmVzcG9uc2VDYWxsYmFja1R3
b0xpbmVzIn19LCB7ImVuZCI6IDExMDg2LCAiYmVnaW4iOiAxMTA3NywgImVkZ2UiOiAiJS9reXRo
ZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJj
b3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3Vh
Z2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5tb2pvbV90eXBlc19kb3duZ3Jh
ZGVyX3VuaXR0ZXN0Lm1vam9tLkRvd25ncmFkZWRUZXN0SW50ZXJmYWNlLk9kZFNwYWNlcyJ9fSwg
eyJlbmQiOiAxMTI3NSwgImJlZ2luIjogMTEyNTQsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5l
cmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNo
cm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9t
IiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QubW9qb21fdHlwZXNfZG93bmdyYWRlcl91bml0dGVz
dC5tb2pvbS5Eb3duZ3JhZGVkVGVzdEludGVyZmFjZS5PZGRTcGFjZXNBbmRMaW5lQnJlYWsifX1d
LCAidHlwZSI6ICJreXRoZTAifQ==
*/