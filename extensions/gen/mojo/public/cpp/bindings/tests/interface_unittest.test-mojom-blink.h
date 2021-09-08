// mojo/public/cpp/bindings/tests/interface_unittest.test-mojom-blink.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_TESTS_INTERFACE_UNITTEST_TEST_MOJOM_BLINK_H_
#define MOJO_PUBLIC_CPP_BINDINGS_TESTS_INTERFACE_UNITTEST_TEST_MOJOM_BLINK_H_

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
#include "mojo/public/cpp/bindings/tests/interface_unittest.test-mojom-shared.h"
#include "mojo/public/cpp/bindings/tests/interface_unittest.test-mojom-blink-forward.h"

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


#include "base/token.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo {
namespace test {
namespace interface_unittest {
namespace mojom {
namespace blink {

class VeryCoolInterfaceProxy;

template <typename ImplRefTraits>
class VeryCoolInterfaceStub;

class VeryCoolInterfaceRequestValidator;


// @generated_from: mojo.test.interface_unittest.mojom.VeryCoolInterface
class  VeryCoolInterface
    : public VeryCoolInterfaceInterfaceBase {
 public:
  static const char Name_[];
  static constexpr base::Token Uuid_{ 5900358954060302158ULL,
                                      10444222698245138944ULL };
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = VeryCoolInterfaceInterfaceBase;
  using Proxy_ = VeryCoolInterfaceProxy;

  template <typename ImplRefTraits>
  using Stub_ = VeryCoolInterfaceStub<ImplRefTraits>;

  using RequestValidator_ = VeryCoolInterfaceRequestValidator;
  using ResponseValidator_ = mojo::PassThroughFilter;
  enum MethodMinVersions : uint32_t {
    kDoesNotMatterMinVersion = 0,
  };
  virtual ~VeryCoolInterface() {}

  
// @generated_from: mojo.test.interface_unittest.mojom.VeryCoolInterface.DoesNotMatter
  virtual void DoesNotMatter() = 0;
};



// @generated_from: mojo.test.interface_unittest.mojom.VeryCoolInterface
class  VeryCoolInterfaceProxy
    : public VeryCoolInterface {
 public:
  using InterfaceType = VeryCoolInterface;

  explicit VeryCoolInterfaceProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: mojo.test.interface_unittest.mojom.VeryCoolInterface.DoesNotMatter
  void DoesNotMatter() final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};
class  VeryCoolInterfaceStubDispatch {
 public:
  static bool Accept(VeryCoolInterface* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      VeryCoolInterface* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<VeryCoolInterface>>
class VeryCoolInterfaceStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  VeryCoolInterfaceStub() {}
  ~VeryCoolInterfaceStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return VeryCoolInterfaceStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return VeryCoolInterfaceStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  VeryCoolInterfaceRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};





}  // namespace blink
}  // namespace mojom
}  // namespace interface_unittest
}  // namespace test
}  // namespace mojo

namespace mojo {

}  // namespace mojo

#endif  // MOJO_PUBLIC_CPP_BINDINGS_TESTS_INTERFACE_UNITTEST_TEST_MOJOM_BLINK_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMjI1NiwgImJlZ2luIjogMjIzOSwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5pbnRlcmZhY2VfdW5pdHRlc3QubW9q
b20uVmVyeUNvb2xJbnRlcmZhY2UifX0sIHsiZW5kIjogMzE0NCwgImJlZ2luIjogMzEzMSwgImVk
Z2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwg
InZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9z
cmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5pbnRlcmZh
Y2VfdW5pdHRlc3QubW9qb20uVmVyeUNvb2xJbnRlcmZhY2UuRG9lc05vdE1hdHRlciJ9fSwgeyJl
bmQiOiAzNTM4LCAiYmVnaW4iOiAzNTI1LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVz
IiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1
bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJz
aWduYXR1cmUiOiAibW9qby50ZXN0LmludGVyZmFjZV91bml0dGVzdC5tb2pvbS5WZXJ5Q29vbElu
dGVyZmFjZS5Eb2VzTm90TWF0dGVyIn19XSwgInR5cGUiOiAia3l0aGUwIn0=
*/