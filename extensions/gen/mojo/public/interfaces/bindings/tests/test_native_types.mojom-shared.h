// mojo/public/interfaces/bindings/tests/test_native_types.mojom-shared.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_NATIVE_TYPES_MOJOM_SHARED_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_NATIVE_TYPES_MOJOM_SHARED_H_

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
#include "mojo/public/interfaces/bindings/tests/test_native_types.mojom-shared-internal.h"
#include "mojo/public/interfaces/bindings/tests/rect.mojom-shared.h"
#include "mojo/public/cpp/bindings/lib/interface_serialization.h"


#include "mojo/public/cpp/bindings/native_enum.h"
#include "mojo/public/cpp/bindings/lib/native_struct_serialization.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo {
namespace test {
using PickledStructDataView = mojo::native::NativeStructDataView;

class PickleContainerDataView;

using TestNativeStructMojomDataView = mojo::native::NativeStructDataView;

using TestNativeStructWithAttachmentsMojomDataView = mojo::native::NativeStructDataView;



}  // namespace test
}  // namespace mojo

namespace mojo {
namespace internal {

template <>
struct MojomTypeTraits<::mojo::test::PickleContainerDataView> {
  using Data = ::mojo::test::internal::PickleContainer_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

}  // namespace internal
}  // namespace mojo


namespace mojo {
namespace test {
using PickledEnum = mojo::NativeEnum;
// Interface base classes. They are used for type safety check.
class PicklePasserInterfaceBase {};

using PicklePasserPtrDataView =
    mojo::InterfacePtrDataView<PicklePasserInterfaceBase>;
using PicklePasserRequestDataView =
    mojo::InterfaceRequestDataView<PicklePasserInterfaceBase>;
using PicklePasserAssociatedPtrInfoDataView =
    mojo::AssociatedInterfacePtrInfoDataView<PicklePasserInterfaceBase>;
using PicklePasserAssociatedRequestDataView =
    mojo::AssociatedInterfaceRequestDataView<PicklePasserInterfaceBase>;
class RectServiceInterfaceBase {};

using RectServicePtrDataView =
    mojo::InterfacePtrDataView<RectServiceInterfaceBase>;
using RectServiceRequestDataView =
    mojo::InterfaceRequestDataView<RectServiceInterfaceBase>;
using RectServiceAssociatedPtrInfoDataView =
    mojo::AssociatedInterfacePtrInfoDataView<RectServiceInterfaceBase>;
using RectServiceAssociatedRequestDataView =
    mojo::AssociatedInterfaceRequestDataView<RectServiceInterfaceBase>;
class NativeTypeTesterInterfaceBase {};

using NativeTypeTesterPtrDataView =
    mojo::InterfacePtrDataView<NativeTypeTesterInterfaceBase>;
using NativeTypeTesterRequestDataView =
    mojo::InterfaceRequestDataView<NativeTypeTesterInterfaceBase>;
using NativeTypeTesterAssociatedPtrInfoDataView =
    mojo::AssociatedInterfacePtrInfoDataView<NativeTypeTesterInterfaceBase>;
using NativeTypeTesterAssociatedRequestDataView =
    mojo::AssociatedInterfaceRequestDataView<NativeTypeTesterInterfaceBase>;


class PickleContainerDataView {
 public:
  PickleContainerDataView() {}

  PickleContainerDataView(
      internal::PickleContainer_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetFStructDataView(
      PickledStructDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadFStruct(UserType* output) {
    
    auto* pointer = data_->f_struct.Get();
    return mojo::internal::Deserialize<::mojo::test::PickledStructDataView>(
        pointer, output, message_);
  }
  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadFEnum(UserType* output) const {
    auto data_value = data_->f_enum;
    return mojo::internal::Deserialize<::mojo::test::PickledEnum>(
        data_value, output);
  }
  PickledEnum f_enum() const {
    return ::mojo::internal::ToKnownEnumValueHelper(
          static_cast<::mojo::test::PickledEnum>(data_->f_enum));
  }
 private:
  internal::PickleContainer_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



}  // namespace test
}  // namespace mojo

namespace std {

}  // namespace std

namespace mojo {


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo::test::PickleContainerDataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::mojo::test::PickleContainerDataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::mojo::test::internal::PickleContainer_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    decltype(Traits::f_struct(input)) in_f_struct = Traits::f_struct(input);
    mojo::internal::MessageFragment<
        typename decltype(fragment->f_struct)::BaseType> f_struct_fragment(
            fragment.message());
    mojo::internal::Serialize<::mojo::test::PickledStructDataView>(
        in_f_struct, f_struct_fragment);
    fragment->f_struct.Set(
        f_struct_fragment.is_null() ? nullptr : f_struct_fragment.data());
    MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
        fragment->f_struct.is_null(),
        mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
        "null f_struct in PickleContainer struct");
    mojo::internal::Serialize<::mojo::test::PickledEnum>(
        Traits::f_enum(input), &fragment->f_enum);
  }

  static bool Deserialize(::mojo::test::internal::PickleContainer_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::mojo::test::PickleContainerDataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal

}  // namespace mojo


namespace mojo {
namespace test {

inline void PickleContainerDataView::GetFStructDataView(
    PickledStructDataView* output) {
  auto pointer = data_->f_struct.Get();
  *output = PickledStructDataView(pointer, message_);
}



}  // namespace test
}  // namespace mojo

// Declare TraceFormatTraits for enums, which should be defined in ::perfetto
// namespace.

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_NATIVE_TYPES_MOJOM_SHARED_H_

/* Metadata comment
eyJtZXRhIjogW10sICJ0eXBlIjogImt5dGhlMCJ9
*/