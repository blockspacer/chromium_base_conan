// mojo/public/js/test/module_b_2.test-mojom.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_H_
#define MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_H_

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
#include "mojo/public/js/test/module_b_2.test-mojom-shared.h"
#include "mojo/public/js/test/module_b_2.test-mojom-forward.h"
#include "mojo/public/js/test/module_a.test-mojom.h"
#include "mojo/public/js/test/module_b_1.test-mojom.h"
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


namespace module_b {

class TestInterfaceProxy;

template <typename ImplRefTraits>
class TestInterfaceStub;

class TestInterfaceRequestValidator;


// @generated_from: module_b.TestInterface
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
    kPassA1MinVersion = 0,
    kPassB1MinVersion = 0,
    kPassB2MinVersion = 0,
  };
  virtual ~TestInterface() {}

  
// @generated_from: module_b.TestInterface.PassA1
  virtual void PassA1(::module_a::TestStructA1Ptr a1) = 0;

  
// @generated_from: module_b.TestInterface.PassB1
  virtual void PassB1(::module_b::TestStructB1Ptr b1) = 0;

  
// @generated_from: module_b.TestInterface.PassB2
  virtual void PassB2(TestStructB2Ptr b2) = 0;
};



// @generated_from: module_b.TestInterface
class  TestInterfaceProxy
    : public TestInterface {
 public:
  using InterfaceType = TestInterface;

  explicit TestInterfaceProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: module_b.TestInterface.PassA1
  void PassA1(::module_a::TestStructA1Ptr a1) final;
  
// @generated_from: module_b.TestInterface.PassB1
  void PassB1(::module_b::TestStructB1Ptr b1) final;
  
// @generated_from: module_b.TestInterface.PassB2
  void PassB2(TestStructB2Ptr b2) final;

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








// @generated_from: module_b.TestStructB2
class  TestStructB2 {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<TestStructB2, T>::value>;
  using DataView = TestStructB2DataView;
  using Data_ = internal::TestStructB2_Data;

  template <typename... Args>
  static TestStructB2Ptr New(Args&&... args) {
    return TestStructB2Ptr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static TestStructB2Ptr From(const U& u) {
    return mojo::TypeConverter<TestStructB2Ptr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, TestStructB2>::Convert(*this);
  }


  TestStructB2();

  TestStructB2(
      ::module_a::TestStructA1Ptr a1,
      ::module_a::TestStructA2Ptr a2,
      TestStructB2Ptr b2);

  ~TestStructB2();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = TestStructB2Ptr>
  TestStructB2Ptr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, TestStructB2::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, TestStructB2::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  size_t Hash(size_t seed) const;
  template <typename UserType>
  static std::vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        TestStructB2::DataView, std::vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        TestStructB2::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::TestStructB2_UnserializedMessageContext<
            UserType, TestStructB2::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<TestStructB2::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const std::vector<uint8_t>& input,
                          UserType* output) {
    return TestStructB2::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::TestStructB2_UnserializedMessageContext<
            UserType, TestStructB2::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<TestStructB2::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: module_b.TestStructB2.a1
  ::module_a::TestStructA1Ptr a1;
  
// @generated_from: module_b.TestStructB2.a2
  ::module_a::TestStructA2Ptr a2;
  
// @generated_from: module_b.TestStructB2.b2
  TestStructB2Ptr b2;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
  DISALLOW_COPY_AND_ASSIGN(TestStructB2);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, TestStructB2::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, TestStructB2::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, TestStructB2::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, TestStructB2::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}

template <typename StructPtrType>
TestStructB2Ptr TestStructB2::Clone() const {
  return New(
      mojo::Clone(a1),
      mojo::Clone(a2),
      mojo::Clone(b2)
  );
}

template <typename T, TestStructB2::EnableIfSame<T>*>
bool TestStructB2::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->a1, other_struct.a1))
    return false;
  if (!mojo::Equals(this->a2, other_struct.a2))
    return false;
  if (!mojo::Equals(this->b2, other_struct.b2))
    return false;
  return true;
}

template <typename T, TestStructB2::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.a1 < rhs.a1)
    return true;
  if (rhs.a1 < lhs.a1)
    return false;
  if (lhs.a2 < rhs.a2)
    return true;
  if (rhs.a2 < lhs.a2)
    return false;
  if (lhs.b2 < rhs.b2)
    return true;
  if (rhs.b2 < lhs.b2)
    return false;
  return false;
}


}  // namespace module_b

namespace mojo {


template <>
struct  StructTraits<::module_b::TestStructB2::DataView,
                                         ::module_b::TestStructB2Ptr> {
  static bool IsNull(const ::module_b::TestStructB2Ptr& input) { return !input; }
  static void SetToNull(::module_b::TestStructB2Ptr* output) { output->reset(); }

  static const decltype(::module_b::TestStructB2::a1)& a1(
      const ::module_b::TestStructB2Ptr& input) {
    return input->a1;
  }

  static const decltype(::module_b::TestStructB2::a2)& a2(
      const ::module_b::TestStructB2Ptr& input) {
    return input->a2;
  }

  static const decltype(::module_b::TestStructB2::b2)& b2(
      const ::module_b::TestStructB2Ptr& input) {
    return input->b2;
  }

  static bool Read(::module_b::TestStructB2::DataView input, ::module_b::TestStructB2Ptr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_JS_TEST_MODULE_B_2_TEST_MOJOM_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTg3MywgImJlZ2luIjogMTg2MCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9iLlRlc3RJbnRlcmZhY2UifX0sIHsiZW5k
IjogMjYxMywgImJlZ2luIjogMjYwNywgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIs
ICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0u
Z29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2ln
bmF0dXJlIjogIm1vZHVsZV9iLlRlc3RJbnRlcmZhY2UuUGFzc0ExIn19LCB7ImVuZCI6IDI3MjYs
ICJiZWdpbiI6IDI3MjAsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6
ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNv
dXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6
ICJtb2R1bGVfYi5UZXN0SW50ZXJmYWNlLlBhc3NCMSJ9fSwgeyJlbmQiOiAyODM5LCAiYmVnaW4i
OiAyODMzLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9y
X2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29t
L2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9kdWxl
X2IuVGVzdEludGVyZmFjZS5QYXNzQjIifX0sIHsiZW5kIjogMzE2MSwgImJlZ2luIjogMzE1NSwg
ImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVz
IiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1
bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9iLlRlc3RJ
bnRlcmZhY2UuUGFzc0ExIn19LCB7ImVuZCI6IDMyNjcsICJiZWdpbiI6IDMyNjEsICJlZGdlIjog
IiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFt
ZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwg
Imxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2R1bGVfYi5UZXN0SW50ZXJmYWNl
LlBhc3NCMSJ9fSwgeyJlbmQiOiAzMzczLCAiYmVnaW4iOiAzMzY3LCAiZWRnZSI6ICIlL2t5dGhl
L2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNv
cnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFn
ZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9kdWxlX2IuVGVzdEludGVyZmFjZS5QYXNzQjIi
fX0sIHsiZW5kIjogNDk0MSwgImJlZ2luIjogNDkyOSwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dl
bmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAi
Y2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9q
b20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9iLlRlc3RTdHJ1Y3RCMiJ9fSwgeyJlbmQiOiA4NjQ4
LCAiYmVnaW4iOiA4NjQ2LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUi
OiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVz
b3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUi
OiAibW9kdWxlX2IuVGVzdFN0cnVjdEIyLmExIn19LCB7ImVuZCI6IDg3MzAsICJiZWdpbiI6IDg3
MjgsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVm
aW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hy
b21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2R1bGVfYi5U
ZXN0U3RydWN0QjIuYTIifX0sIHsiZW5kIjogODgwMCwgImJlZ2luIjogODc5OCwgImVkZ2UiOiAi
JS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1l
IjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAi
bGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9iLlRlc3RTdHJ1Y3RCMi5i
MiJ9fV0sICJ0eXBlIjogImt5dGhlMCJ9
*/