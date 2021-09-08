// mojo/public/mojom/base/token.mojom.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_MOJOM_BASE_TOKEN_MOJOM_H_
#define MOJO_PUBLIC_MOJOM_BASE_TOKEN_MOJOM_H_

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
#include "mojo/public/mojom/base/token.mojom-shared.h"
#include "mojo/public/mojom/base/token.mojom-forward.h"
#include <string>
#include <vector>




#include "mojo/public/cpp/base/token_mojom_traits.h"
#include "base/component_export.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo_base {
namespace mojom {





// @generated_from: mojo_base.mojom.Token
class COMPONENT_EXPORT(MOJO_BASE_MOJOM) Token {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<Token, T>::value>;
  using DataView = TokenDataView;
  using Data_ = internal::Token_Data;

  template <typename... Args>
  static TokenPtr New(Args&&... args) {
    return TokenPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static TokenPtr From(const U& u) {
    return mojo::TypeConverter<TokenPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, Token>::Convert(*this);
  }


  Token();

  Token(
      uint64_t high,
      uint64_t low);

  ~Token();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = TokenPtr>
  TokenPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, Token::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, Token::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  template <typename UserType>
  static std::vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        Token::DataView, std::vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        Token::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::Token_UnserializedMessageContext<
            UserType, Token::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<Token::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const std::vector<uint8_t>& input,
                          UserType* output) {
    return Token::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::Token_UnserializedMessageContext<
            UserType, Token::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<Token::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo_base.mojom.Token.high
  uint64_t high;
  
// @generated_from: mojo_base.mojom.Token.low
  uint64_t low;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, Token::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, Token::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, Token::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, Token::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}




template <typename StructPtrType>
TokenPtr Token::Clone() const {
  return New(
      mojo::Clone(high),
      mojo::Clone(low)
  );
}

template <typename T, Token::EnableIfSame<T>*>
bool Token::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->high, other_struct.high))
    return false;
  if (!mojo::Equals(this->low, other_struct.low))
    return false;
  return true;
}

template <typename T, Token::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.high < rhs.high)
    return true;
  if (rhs.high < lhs.high)
    return false;
  if (lhs.low < rhs.low)
    return true;
  if (rhs.low < lhs.low)
    return false;
  return false;
}


}  // namespace mojom
}  // namespace mojo_base

namespace mojo {


template <>
struct COMPONENT_EXPORT(MOJO_BASE_MOJOM) StructTraits<::mojo_base::mojom::Token::DataView,
                                         ::mojo_base::mojom::TokenPtr> {
  static bool IsNull(const ::mojo_base::mojom::TokenPtr& input) { return !input; }
  static void SetToNull(::mojo_base::mojom::TokenPtr* output) { output->reset(); }

  static decltype(::mojo_base::mojom::Token::high) high(
      const ::mojo_base::mojom::TokenPtr& input) {
    return input->high;
  }

  static decltype(::mojo_base::mojom::Token::low) low(
      const ::mojo_base::mojom::TokenPtr& input) {
    return input->low;
  }

  static bool Read(::mojo_base::mojom::Token::DataView input, ::mojo_base::mojom::TokenPtr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_MOJOM_BASE_TOKEN_MOJOM_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTM2OSwgImJlZ2luIjogMTM2NCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam9fYmFzZS5tb2pvbS5Ub2tlbiJ9fSwgeyJlbmQi
OiA0Nzk4LCAiYmVnaW4iOiA0Nzk0LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwg
InR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5n
b29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWdu
YXR1cmUiOiAibW9qb19iYXNlLm1vam9tLlRva2VuLmhpZ2gifX0sIHsiZW5kIjogNDg2MywgImJl
Z2luIjogNDg2MCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFu
Y2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNl
LmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1v
am9fYmFzZS5tb2pvbS5Ub2tlbi5sb3cifX1dLCAidHlwZSI6ICJreXRoZTAifQ==
*/