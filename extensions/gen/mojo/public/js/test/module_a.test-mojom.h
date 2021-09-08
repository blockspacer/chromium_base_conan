// mojo/public/js/test/module_a.test-mojom.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_JS_TEST_MODULE_A_TEST_MOJOM_H_
#define MOJO_PUBLIC_JS_TEST_MODULE_A_TEST_MOJOM_H_

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
#include "mojo/public/js/test/module_a.test-mojom-shared.h"
#include "mojo/public/js/test/module_a.test-mojom-forward.h"
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


namespace module_a {

class ParentInterfaceProxy;

template <typename ImplRefTraits>
class ParentInterfaceStub;

class ParentInterfaceRequestValidator;


// @generated_from: module_a.ParentInterface
class  ParentInterface
    : public ParentInterfaceInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = false;

  using Base_ = ParentInterfaceInterfaceBase;
  using Proxy_ = ParentInterfaceProxy;

  template <typename ImplRefTraits>
  using Stub_ = ParentInterfaceStub<ImplRefTraits>;

  using RequestValidator_ = ParentInterfaceRequestValidator;
  using ResponseValidator_ = mojo::PassThroughFilter;
  enum MethodMinVersions : uint32_t {
    kSomeMethodMinVersion = 0,
  };
  
// @generated_from: module_a.ParentInterface.NestedEnum
  using NestedEnum = ParentInterface_NestedEnum;
  virtual ~ParentInterface() {}

  
// @generated_from: module_a.ParentInterface.SomeMethod
  virtual void SomeMethod(ParentInterface::NestedEnum value) = 0;
};



// @generated_from: module_a.ParentInterface
class  ParentInterfaceProxy
    : public ParentInterface {
 public:
  using InterfaceType = ParentInterface;

  explicit ParentInterfaceProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: module_a.ParentInterface.SomeMethod
  void SomeMethod(ParentInterface::NestedEnum value) final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};
class  ParentInterfaceStubDispatch {
 public:
  static bool Accept(ParentInterface* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      ParentInterface* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<ParentInterface>>
class ParentInterfaceStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  ParentInterfaceStub() {}
  ~ParentInterfaceStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return ParentInterfaceStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return ParentInterfaceStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  ParentInterfaceRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};





// @generated_from: module_a.TestStructA1
class  TestStructA1 {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<TestStructA1, T>::value>;
  using DataView = TestStructA1DataView;
  using Data_ = internal::TestStructA1_Data;

  template <typename... Args>
  static TestStructA1Ptr New(Args&&... args) {
    return TestStructA1Ptr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static TestStructA1Ptr From(const U& u) {
    return mojo::TypeConverter<TestStructA1Ptr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, TestStructA1>::Convert(*this);
  }


  TestStructA1();

  TestStructA1(
      const std::string& q,
      const std::string& r,
      const std::string& s);

  ~TestStructA1();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = TestStructA1Ptr>
  TestStructA1Ptr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, TestStructA1::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, TestStructA1::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  size_t Hash(size_t seed) const;
  template <typename UserType>
  static std::vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        TestStructA1::DataView, std::vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        TestStructA1::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::TestStructA1_UnserializedMessageContext<
            UserType, TestStructA1::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<TestStructA1::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const std::vector<uint8_t>& input,
                          UserType* output) {
    return TestStructA1::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::TestStructA1_UnserializedMessageContext<
            UserType, TestStructA1::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<TestStructA1::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: module_a.TestStructA1.q
  std::string q;
  
// @generated_from: module_a.TestStructA1.r
  std::string r;
  
// @generated_from: module_a.TestStructA1.s
  std::string s;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, TestStructA1::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, TestStructA1::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, TestStructA1::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, TestStructA1::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}









// @generated_from: module_a.TestStructA2
class  TestStructA2 {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<TestStructA2, T>::value>;
  using DataView = TestStructA2DataView;
  using Data_ = internal::TestStructA2_Data;
// @generated_from: module_a.TestStructA2.NestedEnum
  using NestedEnum = TestStructA2_NestedEnum;

  template <typename... Args>
  static TestStructA2Ptr New(Args&&... args) {
    return TestStructA2Ptr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static TestStructA2Ptr From(const U& u) {
    return mojo::TypeConverter<TestStructA2Ptr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, TestStructA2>::Convert(*this);
  }


  TestStructA2();

  TestStructA2(
      TestStructA1Ptr ax,
      TestStructA1Ptr ay,
      TestStructA2::NestedEnum enumField);

  ~TestStructA2();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = TestStructA2Ptr>
  TestStructA2Ptr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, TestStructA2::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, TestStructA2::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  size_t Hash(size_t seed) const;
  template <typename UserType>
  static std::vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        TestStructA2::DataView, std::vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        TestStructA2::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::TestStructA2_UnserializedMessageContext<
            UserType, TestStructA2::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<TestStructA2::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const std::vector<uint8_t>& input,
                          UserType* output) {
    return TestStructA2::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::TestStructA2_UnserializedMessageContext<
            UserType, TestStructA2::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<TestStructA2::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: module_a.TestStructA2.ax
  TestStructA1Ptr ax;
  
// @generated_from: module_a.TestStructA2.ay
  TestStructA1Ptr ay;
  
// @generated_from: module_a.TestStructA2.enumField
  TestStructA2::NestedEnum enumField;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
  DISALLOW_COPY_AND_ASSIGN(TestStructA2);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, TestStructA2::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, TestStructA2::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, TestStructA2::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, TestStructA2::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}

template <typename StructPtrType>
TestStructA1Ptr TestStructA1::Clone() const {
  return New(
      mojo::Clone(q),
      mojo::Clone(r),
      mojo::Clone(s)
  );
}

template <typename T, TestStructA1::EnableIfSame<T>*>
bool TestStructA1::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->q, other_struct.q))
    return false;
  if (!mojo::Equals(this->r, other_struct.r))
    return false;
  if (!mojo::Equals(this->s, other_struct.s))
    return false;
  return true;
}

template <typename T, TestStructA1::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.q < rhs.q)
    return true;
  if (rhs.q < lhs.q)
    return false;
  if (lhs.r < rhs.r)
    return true;
  if (rhs.r < lhs.r)
    return false;
  if (lhs.s < rhs.s)
    return true;
  if (rhs.s < lhs.s)
    return false;
  return false;
}
template <typename StructPtrType>
TestStructA2Ptr TestStructA2::Clone() const {
  return New(
      mojo::Clone(ax),
      mojo::Clone(ay),
      mojo::Clone(enumField)
  );
}

template <typename T, TestStructA2::EnableIfSame<T>*>
bool TestStructA2::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->ax, other_struct.ax))
    return false;
  if (!mojo::Equals(this->ay, other_struct.ay))
    return false;
  if (!mojo::Equals(this->enumField, other_struct.enumField))
    return false;
  return true;
}

template <typename T, TestStructA2::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.ax < rhs.ax)
    return true;
  if (rhs.ax < lhs.ax)
    return false;
  if (lhs.ay < rhs.ay)
    return true;
  if (rhs.ay < lhs.ay)
    return false;
  if (lhs.enumField < rhs.enumField)
    return true;
  if (rhs.enumField < lhs.enumField)
    return false;
  return false;
}


}  // namespace module_a

namespace mojo {


template <>
struct  StructTraits<::module_a::TestStructA1::DataView,
                                         ::module_a::TestStructA1Ptr> {
  static bool IsNull(const ::module_a::TestStructA1Ptr& input) { return !input; }
  static void SetToNull(::module_a::TestStructA1Ptr* output) { output->reset(); }

  static const decltype(::module_a::TestStructA1::q)& q(
      const ::module_a::TestStructA1Ptr& input) {
    return input->q;
  }

  static const decltype(::module_a::TestStructA1::r)& r(
      const ::module_a::TestStructA1Ptr& input) {
    return input->r;
  }

  static const decltype(::module_a::TestStructA1::s)& s(
      const ::module_a::TestStructA1Ptr& input) {
    return input->s;
  }

  static bool Read(::module_a::TestStructA1::DataView input, ::module_a::TestStructA1Ptr* output);
};


template <>
struct  StructTraits<::module_a::TestStructA2::DataView,
                                         ::module_a::TestStructA2Ptr> {
  static bool IsNull(const ::module_a::TestStructA2Ptr& input) { return !input; }
  static void SetToNull(::module_a::TestStructA2Ptr* output) { output->reset(); }

  static const decltype(::module_a::TestStructA2::ax)& ax(
      const ::module_a::TestStructA2Ptr& input) {
    return input->ax;
  }

  static const decltype(::module_a::TestStructA2::ay)& ay(
      const ::module_a::TestStructA2Ptr& input) {
    return input->ay;
  }

  static decltype(::module_a::TestStructA2::enumField) enumField(
      const ::module_a::TestStructA2Ptr& input) {
    return input->enumField;
  }

  static bool Read(::module_a::TestStructA2::DataView input, ::module_a::TestStructA2Ptr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_JS_TEST_MODULE_A_TEST_MOJOM_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTc2NSwgImJlZ2luIjogMTc1MCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9hLlBhcmVudEludGVyZmFjZSJ9fSwgeyJl
bmQiOiAyNDM3LCAiYmVnaW4iOiAyNDI3LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVz
IiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1
bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJz
aWduYXR1cmUiOiAibW9kdWxlX2EuUGFyZW50SW50ZXJmYWNlLk5lc3RlZEVudW0ifX0sIHsiZW5k
IjogMjU4NSwgImJlZ2luIjogMjU3NSwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIs
ICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0u
Z29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2ln
bmF0dXJlIjogIm1vZHVsZV9hLlBhcmVudEludGVyZmFjZS5Tb21lTWV0aG9kIn19LCB7ImVuZCI6
IDI5NDIsICJiZWdpbiI6IDI5MzIsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAi
dHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdv
b2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25h
dHVyZSI6ICJtb2R1bGVfYS5QYXJlbnRJbnRlcmZhY2UuU29tZU1ldGhvZCJ9fSwgeyJlbmQiOiA0
NTQyLCAiYmVnaW4iOiA0NTMwLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5
cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29n
bGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1
cmUiOiAibW9kdWxlX2EuVGVzdFN0cnVjdEExIn19LCB7ImVuZCI6IDgyMTMsICJiZWdpbiI6IDgy
MTIsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVm
aW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hy
b21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2R1bGVfYS5U
ZXN0U3RydWN0QTEucSJ9fSwgeyJlbmQiOiA4Mjc3LCAiYmVnaW4iOiA4Mjc2LCAiZWRnZSI6ICIl
L2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUi
OiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJs
YW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9kdWxlX2EuVGVzdFN0cnVjdEExLnIi
fX0sIHsiZW5kIjogODM0MSwgImJlZ2luIjogODM0MCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dl
bmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAi
Y2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9q
b20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9hLlRlc3RTdHJ1Y3RBMS5zIn19LCB7ImVuZCI6IDkz
NzIsICJiZWdpbiI6IDkzNjAsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlw
ZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2ds
ZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVy
ZSI6ICJtb2R1bGVfYS5UZXN0U3RydWN0QTIifX0sIHsiZW5kIjogOTY0NCwgImJlZ2luIjogOTYz
NCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZp
bmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJv
bWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9hLlRl
c3RTdHJ1Y3RBMi5OZXN0ZWRFbnVtIn19LCB7ImVuZCI6IDEzMTU4LCAiYmVnaW4iOiAxMzE1Niwg
ImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVz
IiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1
bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9hLlRlc3RT
dHJ1Y3RBMi5heCJ9fSwgeyJlbmQiOiAxMzIyOCwgImJlZ2luIjogMTMyMjYsICJlZGdlIjogIiUv
a3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6
IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxh
bmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2R1bGVfYS5UZXN0U3RydWN0QTIuYXki
fX0sIHsiZW5kIjogMTMzMjEsICJiZWdpbiI6IDEzMzEyLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2Uv
Z2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6
ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJt
b2pvbSIsICJzaWduYXR1cmUiOiAibW9kdWxlX2EuVGVzdFN0cnVjdEEyLmVudW1GaWVsZCJ9fV0s
ICJ0eXBlIjogImt5dGhlMCJ9
*/