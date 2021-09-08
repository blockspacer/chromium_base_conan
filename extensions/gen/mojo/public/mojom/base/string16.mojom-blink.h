// mojo/public/mojom/base/string16.mojom-blink.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_MOJOM_BASE_STRING16_MOJOM_BLINK_H_
#define MOJO_PUBLIC_MOJOM_BASE_STRING16_MOJOM_BLINK_H_

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
#include "mojo/public/mojom/base/string16.mojom-shared.h"
#include "mojo/public/mojom/base/string16.mojom-blink-forward.h"
#include "mojo/public/mojom/base/big_buffer.mojom-blink.h"

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


#include "third_party/blink/renderer/platform/mojo/string16_mojom_traits.h"
#include "base/component_export.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo_base {
namespace mojom {
namespace blink {









// @generated_from: mojo_base.mojom.String16
class COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) String16 {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<String16, T>::value>;
  using DataView = String16DataView;
  using Data_ = internal::String16_Data;

  template <typename... Args>
  static String16Ptr New(Args&&... args) {
    return String16Ptr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static String16Ptr From(const U& u) {
    return mojo::TypeConverter<String16Ptr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, String16>::Convert(*this);
  }


  String16();

  explicit String16(
      WTF::Vector<uint16_t> data);

  ~String16();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = String16Ptr>
  String16Ptr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, String16::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, String16::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  template <typename UserType>
  static WTF::Vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        String16::DataView, WTF::Vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        String16::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::String16_UnserializedMessageContext<
            UserType, String16::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<String16::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
                          UserType* output) {
    return String16::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::String16_UnserializedMessageContext<
            UserType, String16::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<String16::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo_base.mojom.String16.data
  WTF::Vector<uint16_t> data;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, String16::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, String16::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, String16::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, String16::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}





// @generated_from: mojo_base.mojom.BigString16
class COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) BigString16 {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<BigString16, T>::value>;
  using DataView = BigString16DataView;
  using Data_ = internal::BigString16_Data;

  template <typename... Args>
  static BigString16Ptr New(Args&&... args) {
    return BigString16Ptr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static BigString16Ptr From(const U& u) {
    return mojo::TypeConverter<BigString16Ptr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, BigString16>::Convert(*this);
  }


  BigString16();

  explicit BigString16(
      ::mojo_base::BigBuffer data);

  ~BigString16();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = BigString16Ptr>
  BigString16Ptr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, BigString16::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, BigString16::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        BigString16::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::BigString16_UnserializedMessageContext<
            UserType, BigString16::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<BigString16::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
                          UserType* output) {
    return BigString16::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::BigString16_UnserializedMessageContext<
            UserType, BigString16::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<BigString16::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo_base.mojom.BigString16.data
  ::mojo_base::BigBuffer data;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
  DISALLOW_COPY_AND_ASSIGN(BigString16);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, BigString16::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, BigString16::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, BigString16::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, BigString16::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}

template <typename StructPtrType>
String16Ptr String16::Clone() const {
  return New(
      mojo::Clone(data)
  );
}

template <typename T, String16::EnableIfSame<T>*>
bool String16::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->data, other_struct.data))
    return false;
  return true;
}

template <typename T, String16::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.data < rhs.data)
    return true;
  if (rhs.data < lhs.data)
    return false;
  return false;
}
template <typename StructPtrType>
BigString16Ptr BigString16::Clone() const {
  return New(
      mojo::Clone(data)
  );
}

template <typename T, BigString16::EnableIfSame<T>*>
bool BigString16::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->data, other_struct.data))
    return false;
  return true;
}

template <typename T, BigString16::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.data < rhs.data)
    return true;
  if (rhs.data < lhs.data)
    return false;
  return false;
}


}  // namespace blink
}  // namespace mojom
}  // namespace mojo_base

namespace mojo {


template <>
struct COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) StructTraits<::mojo_base::mojom::blink::String16::DataView,
                                         ::mojo_base::mojom::blink::String16Ptr> {
  static bool IsNull(const ::mojo_base::mojom::blink::String16Ptr& input) { return !input; }
  static void SetToNull(::mojo_base::mojom::blink::String16Ptr* output) { output->reset(); }

  static const decltype(::mojo_base::mojom::blink::String16::data)& data(
      const ::mojo_base::mojom::blink::String16Ptr& input) {
    return input->data;
  }

  static bool Read(::mojo_base::mojom::blink::String16::DataView input, ::mojo_base::mojom::blink::String16Ptr* output);
};


template <>
struct COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) StructTraits<::mojo_base::mojom::blink::BigString16::DataView,
                                         ::mojo_base::mojom::blink::BigString16Ptr> {
  static bool IsNull(const ::mojo_base::mojom::blink::BigString16Ptr& input) { return !input; }
  static void SetToNull(::mojo_base::mojom::blink::BigString16Ptr* output) { output->reset(); }

  static  decltype(::mojo_base::mojom::blink::BigString16::data)& data(
       ::mojo_base::mojom::blink::BigString16Ptr& input) {
    return input->data;
  }

  static bool Read(::mojo_base::mojom::blink::BigString16::DataView input, ::mojo_base::mojom::blink::BigString16Ptr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_MOJOM_BASE_STRING16_MOJOM_BLINK_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMjExNiwgImJlZ2luIjogMjEwOCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam9fYmFzZS5tb2pvbS5TdHJpbmcxNiJ9fSwgeyJl
bmQiOiA1NjM1LCAiYmVnaW4iOiA1NjMxLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVz
IiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1
bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJz
aWduYXR1cmUiOiAibW9qb19iYXNlLm1vam9tLlN0cmluZzE2LmRhdGEifX0sIHsiZW5kIjogNjY5
MCwgImJlZ2luIjogNjY3OSwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBl
IjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xl
c291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJl
IjogIm1vam9fYmFzZS5tb2pvbS5CaWdTdHJpbmcxNiJ9fSwgeyJlbmQiOiAxMDA4OSwgImJlZ2lu
IjogMTAwODUsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNo
b3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5j
b20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pv
X2Jhc2UubW9qb20uQmlnU3RyaW5nMTYuZGF0YSJ9fV0sICJ0eXBlIjogImt5dGhlMCJ9
*/