// mojo/public/mojom/base/read_only_buffer.mojom-shared.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_MOJOM_BASE_READ_ONLY_BUFFER_MOJOM_SHARED_H_
#define MOJO_PUBLIC_MOJOM_BASE_READ_ONLY_BUFFER_MOJOM_SHARED_H_

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
#include "mojo/public/mojom/base/read_only_buffer.mojom-shared-internal.h"



#include "base/component_export.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo_base {
namespace mojom {
class ReadOnlyBufferDataView;



}  // namespace mojom
}  // namespace mojo_base

namespace mojo {
namespace internal {

template <>
struct MojomTypeTraits<::mojo_base::mojom::ReadOnlyBufferDataView> {
  using Data = ::mojo_base::mojom::internal::ReadOnlyBuffer_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

}  // namespace internal
}  // namespace mojo


namespace mojo_base {
namespace mojom {


class ReadOnlyBufferDataView {
 public:
  ReadOnlyBufferDataView() {}

  ReadOnlyBufferDataView(
      internal::ReadOnlyBuffer_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetBufferDataView(
      mojo::ArrayDataView<uint8_t>* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadBuffer(UserType* output) {
    
    auto* pointer = data_->buffer.Get();
    return mojo::internal::Deserialize<mojo::ArrayDataView<uint8_t>>(
        pointer, output, message_);
  }
 private:
  internal::ReadOnlyBuffer_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



}  // namespace mojom
}  // namespace mojo_base

namespace std {

}  // namespace std

namespace mojo {


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo_base::mojom::ReadOnlyBufferDataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::mojo_base::mojom::ReadOnlyBufferDataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::mojo_base::mojom::internal::ReadOnlyBuffer_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    decltype(Traits::buffer(input)) in_buffer = Traits::buffer(input);
    mojo::internal::MessageFragment<
        typename decltype(fragment->buffer)::BaseType>
        buffer_fragment(fragment.message());
    const mojo::internal::ContainerValidateParams buffer_validate_params(
        0, false, nullptr);
    mojo::internal::Serialize<mojo::ArrayDataView<uint8_t>>(
        in_buffer, buffer_fragment, &buffer_validate_params);
    fragment->buffer.Set(
        buffer_fragment.is_null() ? nullptr : buffer_fragment.data());
    MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
        fragment->buffer.is_null(),
        mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
        "null buffer in ReadOnlyBuffer struct");
  }

  static bool Deserialize(::mojo_base::mojom::internal::ReadOnlyBuffer_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::mojo_base::mojom::ReadOnlyBufferDataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal

}  // namespace mojo


namespace mojo_base {
namespace mojom {

inline void ReadOnlyBufferDataView::GetBufferDataView(
    mojo::ArrayDataView<uint8_t>* output) {
  auto pointer = data_->buffer.Get();
  *output = mojo::ArrayDataView<uint8_t>(pointer, message_);
}



}  // namespace mojom
}  // namespace mojo_base

// Declare TraceFormatTraits for enums, which should be defined in ::perfetto
// namespace.

#endif  // MOJO_PUBLIC_MOJOM_BASE_READ_ONLY_BUFFER_MOJOM_SHARED_H_

/* Metadata comment
eyJtZXRhIjogW10sICJ0eXBlIjogImt5dGhlMCJ9
*/