// mojo/public/interfaces/bindings/tests/deserializer.test-mojom.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_DESERIALIZER_TEST_MOJOM_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_DESERIALIZER_TEST_MOJOM_H_

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
#include "mojo/public/interfaces/bindings/tests/deserializer.test-mojom-shared.h"
#include "mojo/public/interfaces/bindings/tests/deserializer.test-mojom-forward.h"
#include <string>
#include <vector>





#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace deserializer {





// @generated_from: deserializer.TestStruct
class  TestStruct {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<TestStruct, T>::value>;
  using DataView = TestStructDataView;
  using Data_ = internal::TestStruct_Data;

  template <typename... Args>
  static TestStructPtr New(Args&&... args) {
    return TestStructPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static TestStructPtr From(const U& u) {
    return mojo::TypeConverter<TestStructPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, TestStruct>::Convert(*this);
  }


  TestStruct();

  TestStruct(
      int32_t v1,
      int32_t v2,
      int64_t v3);

  ~TestStruct();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = TestStructPtr>
  TestStructPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, TestStruct::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, TestStruct::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  size_t Hash(size_t seed) const;
  template <typename UserType>
  static std::vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        TestStruct::DataView, std::vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        TestStruct::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::TestStruct_UnserializedMessageContext<
            UserType, TestStruct::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<TestStruct::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const std::vector<uint8_t>& input,
                          UserType* output) {
    return TestStruct::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::TestStruct_UnserializedMessageContext<
            UserType, TestStruct::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<TestStruct::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: deserializer.TestStruct.v1
  int32_t v1;
  
// @generated_from: deserializer.TestStruct.v2
  int32_t v2;
  
// @generated_from: deserializer.TestStruct.v3
  int64_t v3;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, TestStruct::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, TestStruct::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, TestStruct::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, TestStruct::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}




template <typename StructPtrType>
TestStructPtr TestStruct::Clone() const {
  return New(
      mojo::Clone(v1),
      mojo::Clone(v2),
      mojo::Clone(v3)
  );
}

template <typename T, TestStruct::EnableIfSame<T>*>
bool TestStruct::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->v1, other_struct.v1))
    return false;
  if (!mojo::Equals(this->v2, other_struct.v2))
    return false;
  if (!mojo::Equals(this->v3, other_struct.v3))
    return false;
  return true;
}

template <typename T, TestStruct::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.v1 < rhs.v1)
    return true;
  if (rhs.v1 < lhs.v1)
    return false;
  if (lhs.v2 < rhs.v2)
    return true;
  if (rhs.v2 < lhs.v2)
    return false;
  if (lhs.v3 < rhs.v3)
    return true;
  if (rhs.v3 < lhs.v3)
    return false;
  return false;
}


}  // namespace deserializer

namespace mojo {


template <>
struct  StructTraits<::deserializer::TestStruct::DataView,
                                         ::deserializer::TestStructPtr> {
  static bool IsNull(const ::deserializer::TestStructPtr& input) { return !input; }
  static void SetToNull(::deserializer::TestStructPtr* output) { output->reset(); }

  static decltype(::deserializer::TestStruct::v1) v1(
      const ::deserializer::TestStructPtr& input) {
    return input->v1;
  }

  static decltype(::deserializer::TestStruct::v2) v2(
      const ::deserializer::TestStructPtr& input) {
    return input->v2;
  }

  static decltype(::deserializer::TestStruct::v3) v3(
      const ::deserializer::TestStructPtr& input) {
    return input->v3;
  }

  static bool Read(::deserializer::TestStruct::DataView input, ::deserializer::TestStructPtr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_DESERIALIZER_TEST_MOJOM_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTM3NSwgImJlZ2luIjogMTM2NSwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogImRlc2VyaWFsaXplci5UZXN0U3RydWN0In19LCB7ImVu
ZCI6IDQ5NjgsICJiZWdpbiI6IDQ5NjYsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMi
LCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVt
Lmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNp
Z25hdHVyZSI6ICJkZXNlcmlhbGl6ZXIuVGVzdFN0cnVjdC52MSJ9fSwgeyJlbmQiOiA1MDMyLCAi
YmVnaW4iOiA1MDMwLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAi
YW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3Vy
Y2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAi
ZGVzZXJpYWxpemVyLlRlc3RTdHJ1Y3QudjIifX0sIHsiZW5kIjogNTA5NiwgImJlZ2luIjogNTA5
NCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZp
bmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJv
bWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogImRlc2VyaWFsaXpl
ci5UZXN0U3RydWN0LnYzIn19XSwgInR5cGUiOiAia3l0aGUwIn0=
*/