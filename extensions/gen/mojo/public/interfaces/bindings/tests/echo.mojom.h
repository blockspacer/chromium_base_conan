// mojo/public/interfaces/bindings/tests/echo.mojom.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_ECHO_MOJOM_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_ECHO_MOJOM_H_

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
#include "mojo/public/interfaces/bindings/tests/echo.mojom-shared.h"
#include "mojo/public/interfaces/bindings/tests/echo.mojom-forward.h"
#include "mojo/public/interfaces/bindings/tests/echo_import/echo_import.mojom.h"
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


namespace test {
namespace echo {
namespace mojom {

class EchoProxy;

template <typename ImplRefTraits>
class EchoStub;

class EchoRequestValidator;
class EchoResponseValidator;


// @generated_from: test.echo.mojom.Echo
class  Echo
    : public EchoInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = EchoInterfaceBase;
  using Proxy_ = EchoProxy;

  template <typename ImplRefTraits>
  using Stub_ = EchoStub<ImplRefTraits>;

  using RequestValidator_ = EchoRequestValidator;
  using ResponseValidator_ = EchoResponseValidator;
  enum MethodMinVersions : uint32_t {
    kEchoPointMinVersion = 0,
  };
  virtual ~Echo() {}


  using EchoPointCallback = base::OnceCallback<void(::test::echo_import::mojom::PointPtr)>;
  
// @generated_from: test.echo.mojom.Echo.EchoPoint
  virtual void EchoPoint(::test::echo_import::mojom::PointPtr point, EchoPointCallback callback) = 0;
};



// @generated_from: test.echo.mojom.Echo
class  EchoProxy
    : public Echo {
 public:
  using InterfaceType = Echo;

  explicit EchoProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: test.echo.mojom.Echo.EchoPoint
  void EchoPoint(::test::echo_import::mojom::PointPtr point, EchoPointCallback callback) final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};
class  EchoStubDispatch {
 public:
  static bool Accept(Echo* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      Echo* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<Echo>>
class EchoStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  EchoStub() {}
  ~EchoStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return EchoStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return EchoStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  EchoRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  EchoResponseValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};





}  // namespace mojom
}  // namespace echo
}  // namespace test

namespace mojo {

}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_ECHO_MOJOM_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTkwMywgImJlZ2luIjogMTg5OSwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogInRlc3QuZWNoby5tb2pvbS5FY2hvIn19LCB7ImVuZCI6
IDI2MzMsICJiZWdpbiI6IDI2MjQsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAi
dHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdv
b2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25h
dHVyZSI6ICJ0ZXN0LmVjaG8ubW9qb20uRWNoby5FY2hvUG9pbnQifX0sIHsiZW5kIjogMjk3Mywg
ImJlZ2luIjogMjk2NCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjog
ImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291
cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjog
InRlc3QuZWNoby5tb2pvbS5FY2hvLkVjaG9Qb2ludCJ9fV0sICJ0eXBlIjogImt5dGhlMCJ9
*/