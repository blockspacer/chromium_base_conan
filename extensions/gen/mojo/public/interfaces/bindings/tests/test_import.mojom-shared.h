// mojo/public/interfaces/bindings/tests/test_import.mojom-shared.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_IMPORT_MOJOM_SHARED_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_IMPORT_MOJOM_SHARED_H_

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
#include "mojo/public/interfaces/bindings/tests/test_import.mojom-shared-internal.h"
#include "mojo/public/interfaces/bindings/tests/test_export.mojom-shared.h"




#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo {
namespace test {
namespace test_import {
class ImportingStructDataView;



}  // namespace test_import
}  // namespace test
}  // namespace mojo

namespace mojo {
namespace internal {

template <>
struct MojomTypeTraits<::mojo::test::test_import::ImportingStructDataView> {
  using Data = ::mojo::test::test_import::internal::ImportingStruct_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

}  // namespace internal
}  // namespace mojo


namespace mojo {
namespace test {
namespace test_import {


class ImportingStructDataView {
 public:
  ImportingStructDataView() {}

  ImportingStructDataView(
      internal::ImportingStruct_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetStringsDataView(
      ::mojo::test::test_export::StringPairDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadStrings(UserType* output) {
    
    auto* pointer = data_->strings.Get();
    return mojo::internal::Deserialize<::mojo::test::test_export::StringPairDataView>(
        pointer, output, message_);
  }
 private:
  internal::ImportingStruct_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



}  // namespace test_import
}  // namespace test
}  // namespace mojo

namespace std {

}  // namespace std

namespace mojo {


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo::test::test_import::ImportingStructDataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::mojo::test::test_import::ImportingStructDataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::mojo::test::test_import::internal::ImportingStruct_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    decltype(Traits::strings(input)) in_strings = Traits::strings(input);
    mojo::internal::MessageFragment<
        typename decltype(fragment->strings)::BaseType> strings_fragment(
            fragment.message());
    mojo::internal::Serialize<::mojo::test::test_export::StringPairDataView>(
        in_strings, strings_fragment);
    fragment->strings.Set(
        strings_fragment.is_null() ? nullptr : strings_fragment.data());
    MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
        fragment->strings.is_null(),
        mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
        "null strings in ImportingStruct struct");
  }

  static bool Deserialize(::mojo::test::test_import::internal::ImportingStruct_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::mojo::test::test_import::ImportingStructDataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal

}  // namespace mojo


namespace mojo {
namespace test {
namespace test_import {

inline void ImportingStructDataView::GetStringsDataView(
    ::mojo::test::test_export::StringPairDataView* output) {
  auto pointer = data_->strings.Get();
  *output = ::mojo::test::test_export::StringPairDataView(pointer, message_);
}



}  // namespace test_import
}  // namespace test
}  // namespace mojo

// Declare TraceFormatTraits for enums, which should be defined in ::perfetto
// namespace.

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_IMPORT_MOJOM_SHARED_H_

/* Metadata comment
eyJtZXRhIjogW10sICJ0eXBlIjogImt5dGhlMCJ9
*/