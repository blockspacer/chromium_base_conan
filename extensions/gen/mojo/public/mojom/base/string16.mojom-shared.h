// mojo/public/mojom/base/string16.mojom-shared.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_MOJOM_BASE_STRING16_MOJOM_SHARED_H_
#define MOJO_PUBLIC_MOJOM_BASE_STRING16_MOJOM_SHARED_H_

#include <stdint.h>

#include <functional>
#include <ostream>
#include <type_traits>
#include <utility>

#include "base/compiler_specific.h"
#include "base/containers/flat_map.h"
#include "mojo/public/cpp/bindings/array_data_view.h"
#include "mojo/public/cpp/bindings/enum_traits.h"
#include "mojo/public/cpp/bindings/interface_data_view.h"
#include "mojo/public/cpp/bindings/lib/bindings_internal.h"
#include "mojo/public/cpp/bindings/lib/serialization.h"
#include "mojo/public/cpp/bindings/map_data_view.h"
#include "mojo/public/cpp/bindings/string_data_view.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value_forward.h"
#include "mojo/public/mojom/base/string16.mojom-shared-internal.h"
#include "mojo/public/mojom/base/big_buffer.mojom-shared.h"
#include "mojo/public/cpp/bindings/lib/interface_serialization.h"


#include "base/component_export.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo_base {
namespace mojom {
class String16DataView;

class BigString16DataView;



}  // namespace mojom
}  // namespace mojo_base

namespace mojo {
namespace internal {

template <>
struct MojomTypeTraits<::mojo_base::mojom::String16DataView> {
  using Data = ::mojo_base::mojom::internal::String16_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

template <>
struct MojomTypeTraits<::mojo_base::mojom::BigString16DataView> {
  using Data = ::mojo_base::mojom::internal::BigString16_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

}  // namespace internal
}  // namespace mojo


namespace mojo_base {
namespace mojom {


class String16DataView {
 public:
  String16DataView() {}

  String16DataView(
      internal::String16_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetDataDataView(
      mojo::ArrayDataView<uint16_t>* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadData(UserType* output) {
    
    auto* pointer = data_->data.Get();
    return mojo::internal::Deserialize<mojo::ArrayDataView<uint16_t>>(
        pointer, output, message_);
  }
 private:
  internal::String16_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class BigString16DataView {
 public:
  BigString16DataView() {}

  BigString16DataView(
      internal::BigString16_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetDataDataView(
      ::mojo_base::mojom::BigBufferDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadData(UserType* output) {
    
    auto* pointer = !data_->data.is_null() ? &data_->data : nullptr;
    return mojo::internal::Deserialize<::mojo_base::mojom::BigBufferDataView>(
        pointer, output, message_);
  }
 private:
  internal::BigString16_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



}  // namespace mojom
}  // namespace mojo_base

namespace std {

}  // namespace std

namespace mojo {


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo_base::mojom::String16DataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::mojo_base::mojom::String16DataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::mojo_base::mojom::internal::String16_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    decltype(Traits::data(input)) in_data = Traits::data(input);
    mojo::internal::MessageFragment<
        typename decltype(fragment->data)::BaseType>
        data_fragment(fragment.message());
    const mojo::internal::ContainerValidateParams data_validate_params(
        0, false, nullptr);
    mojo::internal::Serialize<mojo::ArrayDataView<uint16_t>>(
        in_data, data_fragment, &data_validate_params);
    fragment->data.Set(
        data_fragment.is_null() ? nullptr : data_fragment.data());
    MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
        fragment->data.is_null(),
        mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
        "null data in String16 struct");
  }

  static bool Deserialize(::mojo_base::mojom::internal::String16_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::mojo_base::mojom::String16DataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo_base::mojom::BigString16DataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::mojo_base::mojom::BigString16DataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::mojo_base::mojom::internal::BigString16_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    decltype(Traits::data(input)) in_data = Traits::data(input);
    mojo::internal::MessageFragment<decltype(fragment->data)>
        data_fragment(fragment.message());
    data_fragment.Claim(&fragment->data);
    mojo::internal::Serialize<::mojo_base::mojom::BigBufferDataView>(
        in_data, data_fragment, true);
    MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
        fragment->data.is_null(),
        mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
        "null data in BigString16 struct");
  }

  static bool Deserialize(::mojo_base::mojom::internal::BigString16_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::mojo_base::mojom::BigString16DataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal

}  // namespace mojo


namespace mojo_base {
namespace mojom {

inline void String16DataView::GetDataDataView(
    mojo::ArrayDataView<uint16_t>* output) {
  auto pointer = data_->data.Get();
  *output = mojo::ArrayDataView<uint16_t>(pointer, message_);
}


inline void BigString16DataView::GetDataDataView(
    ::mojo_base::mojom::BigBufferDataView* output) {
  auto pointer = &data_->data;
  *output = ::mojo_base::mojom::BigBufferDataView(pointer, message_);
}



}  // namespace mojom
}  // namespace mojo_base

// Declare TraceFormatTraits for enums, which should be defined in ::perfetto
// namespace.

#endif  // MOJO_PUBLIC_MOJOM_BASE_STRING16_MOJOM_SHARED_H_

/* Metadata comment
eyJtZXRhIjogW10sICJ0eXBlIjogImt5dGhlMCJ9
*/