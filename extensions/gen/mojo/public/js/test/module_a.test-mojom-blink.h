// mojo/public/js/test/module_a.test-mojom-blink.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_JS_TEST_MODULE_A_TEST_MOJOM_BLINK_H_
#define MOJO_PUBLIC_JS_TEST_MODULE_A_TEST_MOJOM_BLINK_H_

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
#include "mojo/public/js/test/module_a.test-mojom-blink-forward.h"

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


namespace WTF {
struct module_a_internal_ModuleEnum_DataHashFn {
  static unsigned GetHash(const ::module_a::ModuleEnum& value) {
    using utype = std::underlying_type<::module_a::ModuleEnum>::type;
    return DefaultHash<utype>::Hash().GetHash(static_cast<utype>(value));
  }
  static bool Equal(const ::module_a::ModuleEnum& left, const ::module_a::ModuleEnum& right) {
    return left == right;
  }
  static const bool safe_to_compare_to_empty_or_deleted = true;
};

template <>
struct HashTraits<::module_a::ModuleEnum>
    : public GenericHashTraits<::module_a::ModuleEnum> {
  static_assert(true,
                "-1000000 is a reserved enum value");
  static_assert(true,
                "-1000001 is a reserved enum value");
  static const bool hasIsEmptyValueFunction = true;
  static bool IsEmptyValue(const ::module_a::ModuleEnum& value) {
    return value == static_cast<::module_a::ModuleEnum>(-1000000);
  }
  static void ConstructDeletedValue(::module_a::ModuleEnum& slot, bool) {
    slot = static_cast<::module_a::ModuleEnum>(-1000001);
  }
  static bool IsDeletedValue(const ::module_a::ModuleEnum& value) {
    return value == static_cast<::module_a::ModuleEnum>(-1000001);
  }
};
}  // namespace WTF


namespace WTF {
struct module_a_internal_TestStructA2_NestedEnum_DataHashFn {
  static unsigned GetHash(const ::module_a::TestStructA2_NestedEnum& value) {
    using utype = std::underlying_type<::module_a::TestStructA2_NestedEnum>::type;
    return DefaultHash<utype>::Hash().GetHash(static_cast<utype>(value));
  }
  static bool Equal(const ::module_a::TestStructA2_NestedEnum& left, const ::module_a::TestStructA2_NestedEnum& right) {
    return left == right;
  }
  static const bool safe_to_compare_to_empty_or_deleted = true;
};

template <>
struct HashTraits<::module_a::TestStructA2_NestedEnum>
    : public GenericHashTraits<::module_a::TestStructA2_NestedEnum> {
  static_assert(true,
                "-1000000 is a reserved enum value");
  static_assert(true,
                "-1000001 is a reserved enum value");
  static const bool hasIsEmptyValueFunction = true;
  static bool IsEmptyValue(const ::module_a::TestStructA2_NestedEnum& value) {
    return value == static_cast<::module_a::TestStructA2_NestedEnum>(-1000000);
  }
  static void ConstructDeletedValue(::module_a::TestStructA2_NestedEnum& slot, bool) {
    slot = static_cast<::module_a::TestStructA2_NestedEnum>(-1000001);
  }
  static bool IsDeletedValue(const ::module_a::TestStructA2_NestedEnum& value) {
    return value == static_cast<::module_a::TestStructA2_NestedEnum>(-1000001);
  }
};
}  // namespace WTF


namespace WTF {
struct module_a_internal_ParentInterface_NestedEnum_DataHashFn {
  static unsigned GetHash(const ::module_a::ParentInterface_NestedEnum& value) {
    using utype = std::underlying_type<::module_a::ParentInterface_NestedEnum>::type;
    return DefaultHash<utype>::Hash().GetHash(static_cast<utype>(value));
  }
  static bool Equal(const ::module_a::ParentInterface_NestedEnum& left, const ::module_a::ParentInterface_NestedEnum& right) {
    return left == right;
  }
  static const bool safe_to_compare_to_empty_or_deleted = true;
};

template <>
struct HashTraits<::module_a::ParentInterface_NestedEnum>
    : public GenericHashTraits<::module_a::ParentInterface_NestedEnum> {
  static_assert(true,
                "-1000000 is a reserved enum value");
  static_assert(true,
                "-1000001 is a reserved enum value");
  static const bool hasIsEmptyValueFunction = true;
  static bool IsEmptyValue(const ::module_a::ParentInterface_NestedEnum& value) {
    return value == static_cast<::module_a::ParentInterface_NestedEnum>(-1000000);
  }
  static void ConstructDeletedValue(::module_a::ParentInterface_NestedEnum& slot, bool) {
    slot = static_cast<::module_a::ParentInterface_NestedEnum>(-1000001);
  }
  static bool IsDeletedValue(const ::module_a::ParentInterface_NestedEnum& value) {
    return value == static_cast<::module_a::ParentInterface_NestedEnum>(-1000001);
  }
};
}  // namespace WTF


namespace module_a {
namespace blink {

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
      const WTF::String& q,
      const WTF::String& r,
      const WTF::String& s);

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
  static WTF::Vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        TestStructA1::DataView, WTF::Vector<uint8_t>>(input);
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
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
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
  WTF::String q;
  
// @generated_from: module_a.TestStructA1.r
  WTF::String r;
  
// @generated_from: module_a.TestStructA1.s
  WTF::String s;

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
  static WTF::Vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        TestStructA2::DataView, WTF::Vector<uint8_t>>(input);
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
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
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


}  // namespace blink
}  // namespace module_a

namespace mojo {


template <>
struct  StructTraits<::module_a::blink::TestStructA1::DataView,
                                         ::module_a::blink::TestStructA1Ptr> {
  static bool IsNull(const ::module_a::blink::TestStructA1Ptr& input) { return !input; }
  static void SetToNull(::module_a::blink::TestStructA1Ptr* output) { output->reset(); }

  static const decltype(::module_a::blink::TestStructA1::q)& q(
      const ::module_a::blink::TestStructA1Ptr& input) {
    return input->q;
  }

  static const decltype(::module_a::blink::TestStructA1::r)& r(
      const ::module_a::blink::TestStructA1Ptr& input) {
    return input->r;
  }

  static const decltype(::module_a::blink::TestStructA1::s)& s(
      const ::module_a::blink::TestStructA1Ptr& input) {
    return input->s;
  }

  static bool Read(::module_a::blink::TestStructA1::DataView input, ::module_a::blink::TestStructA1Ptr* output);
};


template <>
struct  StructTraits<::module_a::blink::TestStructA2::DataView,
                                         ::module_a::blink::TestStructA2Ptr> {
  static bool IsNull(const ::module_a::blink::TestStructA2Ptr& input) { return !input; }
  static void SetToNull(::module_a::blink::TestStructA2Ptr* output) { output->reset(); }

  static const decltype(::module_a::blink::TestStructA2::ax)& ax(
      const ::module_a::blink::TestStructA2Ptr& input) {
    return input->ax;
  }

  static const decltype(::module_a::blink::TestStructA2::ay)& ay(
      const ::module_a::blink::TestStructA2Ptr& input) {
    return input->ay;
  }

  static decltype(::module_a::blink::TestStructA2::enumField) enumField(
      const ::module_a::blink::TestStructA2Ptr& input) {
    return input->enumField;
  }

  static bool Read(::module_a::blink::TestStructA2::DataView input, ::module_a::blink::TestStructA2Ptr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_JS_TEST_MODULE_A_TEST_MOJOM_BLINK_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogNjA3NSwgImJlZ2luIjogNjA2MCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9hLlBhcmVudEludGVyZmFjZSJ9fSwgeyJl
bmQiOiA2NzQ3LCAiYmVnaW4iOiA2NzM3LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVz
IiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1
bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJz
aWduYXR1cmUiOiAibW9kdWxlX2EuUGFyZW50SW50ZXJmYWNlLk5lc3RlZEVudW0ifX0sIHsiZW5k
IjogNjg5NSwgImJlZ2luIjogNjg4NSwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIs
ICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0u
Z29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2ln
bmF0dXJlIjogIm1vZHVsZV9hLlBhcmVudEludGVyZmFjZS5Tb21lTWV0aG9kIn19LCB7ImVuZCI6
IDcyNTIsICJiZWdpbiI6IDcyNDIsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAi
dHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdv
b2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25h
dHVyZSI6ICJtb2R1bGVfYS5QYXJlbnRJbnRlcmZhY2UuU29tZU1ldGhvZCJ9fSwgeyJlbmQiOiA4
ODUyLCAiYmVnaW4iOiA4ODQwLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5
cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29n
bGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1
cmUiOiAibW9kdWxlX2EuVGVzdFN0cnVjdEExIn19LCB7ImVuZCI6IDEyNTIzLCAiYmVnaW4iOiAx
MjUyMiwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9k
ZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9j
aHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9h
LlRlc3RTdHJ1Y3RBMS5xIn19LCB7ImVuZCI6IDEyNTg3LCAiYmVnaW4iOiAxMjU4NiwgImVkZ2Ui
OiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZu
YW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMi
LCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9hLlRlc3RTdHJ1Y3RB
MS5yIn19LCB7ImVuZCI6IDEyNjUxLCAiYmVnaW4iOiAxMjY1MCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9hLlRlc3RTdHJ1Y3RBMS5zIn19LCB7ImVu
ZCI6IDEzNjgyLCAiYmVnaW4iOiAxMzY3MCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRl
cyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21p
dW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAi
c2lnbmF0dXJlIjogIm1vZHVsZV9hLlRlc3RTdHJ1Y3RBMiJ9fSwgeyJlbmQiOiAxMzk1NCwgImJl
Z2luIjogMTM5NDQsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJh
bmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJj
ZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJt
b2R1bGVfYS5UZXN0U3RydWN0QTIuTmVzdGVkRW51bSJ9fSwgeyJlbmQiOiAxNzQ2OCwgImJlZ2lu
IjogMTc0NjYsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNo
b3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5j
b20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2R1
bGVfYS5UZXN0U3RydWN0QTIuYXgifX0sIHsiZW5kIjogMTc1MzgsICJiZWdpbiI6IDE3NTM2LCAi
ZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMi
LCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVt
L3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9kdWxlX2EuVGVzdFN0
cnVjdEEyLmF5In19LCB7ImVuZCI6IDE3NjMxLCAiYmVnaW4iOiAxNzYyMiwgImVkZ2UiOiAiJS9r
eXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjog
eyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFu
Z3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vZHVsZV9hLlRlc3RTdHJ1Y3RBMi5lbnVt
RmllbGQifX1dLCAidHlwZSI6ICJreXRoZTAifQ==
*/