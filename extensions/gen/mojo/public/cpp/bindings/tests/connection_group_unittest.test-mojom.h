// mojo/public/cpp/bindings/tests/connection_group_unittest.test-mojom.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_TESTS_CONNECTION_GROUP_UNITTEST_TEST_MOJOM_H_
#define MOJO_PUBLIC_CPP_BINDINGS_TESTS_CONNECTION_GROUP_UNITTEST_TEST_MOJOM_H_

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
#include "mojo/public/cpp/bindings/tests/connection_group_unittest.test-mojom-shared.h"
#include "mojo/public/cpp/bindings/tests/connection_group_unittest.test-mojom-forward.h"
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


namespace mojo {
namespace test {
namespace connection_group_unittest {
namespace mojom {

class TestInterfaceProxy;

template <typename ImplRefTraits>
class TestInterfaceStub;

class TestInterfaceRequestValidator;


// @generated_from: mojo.test.connection_group_unittest.mojom.TestInterface
class  TestInterface
    : public TestInterfaceInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = TestInterfaceInterfaceBase;
  using Proxy_ = TestInterfaceProxy;

  template <typename ImplRefTraits>
  using Stub_ = TestInterfaceStub<ImplRefTraits>;

  using RequestValidator_ = TestInterfaceRequestValidator;
  using ResponseValidator_ = mojo::PassThroughFilter;
  enum MethodMinVersions : uint32_t {
    kBindReceiverMinVersion = 0,
  };
  virtual ~TestInterface() {}

  
// @generated_from: mojo.test.connection_group_unittest.mojom.TestInterface.BindReceiver
  virtual void BindReceiver(::mojo::PendingReceiver<TestInterface> receiver) = 0;
};



// @generated_from: mojo.test.connection_group_unittest.mojom.TestInterface
class  TestInterfaceProxy
    : public TestInterface {
 public:
  using InterfaceType = TestInterface;

  explicit TestInterfaceProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: mojo.test.connection_group_unittest.mojom.TestInterface.BindReceiver
  void BindReceiver(::mojo::PendingReceiver<TestInterface> receiver) final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};
class  TestInterfaceStubDispatch {
 public:
  static bool Accept(TestInterface* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      TestInterface* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<TestInterface>>
class TestInterfaceStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  TestInterfaceStub() {}
  ~TestInterfaceStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return TestInterfaceStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return TestInterfaceStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  TestInterfaceRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};





}  // namespace mojom
}  // namespace connection_group_unittest
}  // namespace test
}  // namespace mojo

namespace mojo {

}  // namespace mojo

#endif  // MOJO_PUBLIC_CPP_BINDINGS_TESTS_CONNECTION_GROUP_UNITTEST_TEST_MOJOM_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTk5NywgImJlZ2luIjogMTk4NCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5jb25uZWN0aW9uX2dyb3VwX3VuaXR0
ZXN0Lm1vam9tLlRlc3RJbnRlcmZhY2UifX0sIHsiZW5kIjogMjczNCwgImJlZ2luIjogMjcyMiwg
ImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVz
IiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1
bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5jb25u
ZWN0aW9uX2dyb3VwX3VuaXR0ZXN0Lm1vam9tLlRlc3RJbnRlcmZhY2UuQmluZFJlY2VpdmVyIn19
LCB7ImVuZCI6IDMxNjMsICJiZWdpbiI6IDMxNTEsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5l
cmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNo
cm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9t
IiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuY29ubmVjdGlvbl9ncm91cF91bml0dGVzdC5tb2pv
bS5UZXN0SW50ZXJmYWNlLkJpbmRSZWNlaXZlciJ9fV0sICJ0eXBlIjogImt5dGhlMCJ9
*/