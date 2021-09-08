// mojo/public/interfaces/bindings/tests/serialization_test_structs.mojom-shared.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SERIALIZATION_TEST_STRUCTS_MOJOM_SHARED_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SERIALIZATION_TEST_STRUCTS_MOJOM_SHARED_H_

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
#include "mojo/public/interfaces/bindings/tests/serialization_test_structs.mojom-shared-internal.h"
#include "mojo/public/cpp/bindings/lib/interface_serialization.h"



#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo {
namespace test {
class Struct1DataView;

class Struct2DataView;

class Struct3DataView;

class Struct4DataView;

class Struct5DataView;

class Struct6DataView;

class StructOfNullablesDataView;



}  // namespace test
}  // namespace mojo

namespace mojo {
namespace internal {

template <>
struct MojomTypeTraits<::mojo::test::Struct1DataView> {
  using Data = ::mojo::test::internal::Struct1_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

template <>
struct MojomTypeTraits<::mojo::test::Struct2DataView> {
  using Data = ::mojo::test::internal::Struct2_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

template <>
struct MojomTypeTraits<::mojo::test::Struct3DataView> {
  using Data = ::mojo::test::internal::Struct3_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

template <>
struct MojomTypeTraits<::mojo::test::Struct4DataView> {
  using Data = ::mojo::test::internal::Struct4_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

template <>
struct MojomTypeTraits<::mojo::test::Struct5DataView> {
  using Data = ::mojo::test::internal::Struct5_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

template <>
struct MojomTypeTraits<::mojo::test::Struct6DataView> {
  using Data = ::mojo::test::internal::Struct6_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

template <>
struct MojomTypeTraits<::mojo::test::StructOfNullablesDataView> {
  using Data = ::mojo::test::internal::StructOfNullables_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

}  // namespace internal
}  // namespace mojo


namespace mojo {
namespace test {


class Struct1DataView {
 public:
  Struct1DataView() {}

  Struct1DataView(
      internal::Struct1_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  uint8_t i() const {
    return data_->i;
  }
 private:
  internal::Struct1_Data* data_ = nullptr;
};



class Struct2DataView {
 public:
  Struct2DataView() {}

  Struct2DataView(
      internal::Struct2_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  mojo::ScopedHandle TakeHdl() {
    mojo::ScopedHandle result;
    bool ret =
        mojo::internal::Deserialize<mojo::ScopedHandle>(
            &data_->hdl, &result, message_);
    DCHECK(ret);
    return result;
  }
 private:
  internal::Struct2_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class Struct3DataView {
 public:
  Struct3DataView() {}

  Struct3DataView(
      internal::Struct3_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetStruct1DataView(
      Struct1DataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadStruct1(UserType* output) {
    
    auto* pointer = data_->struct_1.Get();
    return mojo::internal::Deserialize<::mojo::test::Struct1DataView>(
        pointer, output, message_);
  }
 private:
  internal::Struct3_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class Struct4DataView {
 public:
  Struct4DataView() {}

  Struct4DataView(
      internal::Struct4_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetDataDataView(
      mojo::ArrayDataView<Struct1DataView>* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadData(UserType* output) {
    
    auto* pointer = data_->data.Get();
    return mojo::internal::Deserialize<mojo::ArrayDataView<::mojo::test::Struct1DataView>>(
        pointer, output, message_);
  }
 private:
  internal::Struct4_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class Struct5DataView {
 public:
  Struct5DataView() {}

  Struct5DataView(
      internal::Struct5_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetPairDataView(
      mojo::ArrayDataView<Struct1DataView>* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadPair(UserType* output) {
    
    auto* pointer = data_->pair.Get();
    return mojo::internal::Deserialize<mojo::ArrayDataView<::mojo::test::Struct1DataView>>(
        pointer, output, message_);
  }
 private:
  internal::Struct5_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class Struct6DataView {
 public:
  Struct6DataView() {}

  Struct6DataView(
      internal::Struct6_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetStrDataView(
      mojo::StringDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadStr(UserType* output) {
    
    auto* pointer = data_->str.Get();
    return mojo::internal::Deserialize<mojo::StringDataView>(
        pointer, output, message_);
  }
 private:
  internal::Struct6_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class StructOfNullablesDataView {
 public:
  StructOfNullablesDataView() {}

  StructOfNullablesDataView(
      internal::StructOfNullables_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  mojo::ScopedHandle TakeHdl() {
    mojo::ScopedHandle result;
    bool ret =
        mojo::internal::Deserialize<mojo::ScopedHandle>(
            &data_->hdl, &result, message_);
    DCHECK(ret);
    return result;
  }
  inline void GetStruct1DataView(
      Struct1DataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadStruct1(UserType* output) {
    
static_assert(
    mojo::internal::IsValidUserTypeForOptionalValue<
        ::mojo::test::Struct1DataView, UserType>(),
    "Attempting to read the optional `struct_1` field into a type which "
    "cannot represent a null value. Either wrap the destination object "
    "with base::Optional, ensure that any corresponding "
    "{Struct/Union/Array/String}Traits define the necessary IsNull and "
    "SetToNull methods, or use `MaybeReadStruct1` instead "
    "of `ReadStruct1 if you're fine with null values being "
    "silently ignored in this case.");
    auto* pointer = data_->struct_1.Get();
    return mojo::internal::Deserialize<::mojo::test::Struct1DataView>(
        pointer, output, message_);
  }
  inline void GetStrDataView(
      mojo::StringDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadStr(UserType* output) {
    
static_assert(
    mojo::internal::IsValidUserTypeForOptionalValue<
        mojo::StringDataView, UserType>(),
    "Attempting to read the optional `str` field into a type which "
    "cannot represent a null value. Either wrap the destination object "
    "with base::Optional, ensure that any corresponding "
    "{Struct/Union/Array/String}Traits define the necessary IsNull and "
    "SetToNull methods, or use `MaybeReadStr` instead "
    "of `ReadStr if you're fine with null values being "
    "silently ignored in this case.");
    auto* pointer = data_->str.Get();
    return mojo::internal::Deserialize<mojo::StringDataView>(
        pointer, output, message_);
  }
 private:
  internal::StructOfNullables_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



}  // namespace test
}  // namespace mojo

namespace std {

}  // namespace std

namespace mojo {


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo::test::Struct1DataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::mojo::test::Struct1DataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::mojo::test::internal::Struct1_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    fragment->i = Traits::i(input);
  }

  static bool Deserialize(::mojo::test::internal::Struct1_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::mojo::test::Struct1DataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo::test::Struct2DataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::mojo::test::Struct2DataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::mojo::test::internal::Struct2_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    decltype(Traits::hdl(input)) in_hdl = Traits::hdl(input);
    mojo::internal::Serialize<mojo::ScopedHandle>(
        in_hdl, &fragment->hdl, &fragment.message());
    MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
        !mojo::internal::IsHandleOrInterfaceValid(fragment->hdl),
        mojo::internal::VALIDATION_ERROR_UNEXPECTED_INVALID_HANDLE,
        "invalid hdl in Struct2 struct");
  }

  static bool Deserialize(::mojo::test::internal::Struct2_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::mojo::test::Struct2DataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo::test::Struct3DataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::mojo::test::Struct3DataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::mojo::test::internal::Struct3_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    decltype(Traits::struct_1(input)) in_struct_1 = Traits::struct_1(input);
    mojo::internal::MessageFragment<
        typename decltype(fragment->struct_1)::BaseType> struct_1_fragment(
            fragment.message());
    mojo::internal::Serialize<::mojo::test::Struct1DataView>(
        in_struct_1, struct_1_fragment);
    fragment->struct_1.Set(
        struct_1_fragment.is_null() ? nullptr : struct_1_fragment.data());
    MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
        fragment->struct_1.is_null(),
        mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
        "null struct_1 in Struct3 struct");
  }

  static bool Deserialize(::mojo::test::internal::Struct3_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::mojo::test::Struct3DataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo::test::Struct4DataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::mojo::test::Struct4DataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::mojo::test::internal::Struct4_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    decltype(Traits::data(input)) in_data = Traits::data(input);
    mojo::internal::MessageFragment<
        typename decltype(fragment->data)::BaseType>
        data_fragment(fragment.message());
    const mojo::internal::ContainerValidateParams data_validate_params(
        0, false, nullptr);
    mojo::internal::Serialize<mojo::ArrayDataView<::mojo::test::Struct1DataView>>(
        in_data, data_fragment, &data_validate_params);
    fragment->data.Set(
        data_fragment.is_null() ? nullptr : data_fragment.data());
    MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
        fragment->data.is_null(),
        mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
        "null data in Struct4 struct");
  }

  static bool Deserialize(::mojo::test::internal::Struct4_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::mojo::test::Struct4DataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo::test::Struct5DataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::mojo::test::Struct5DataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::mojo::test::internal::Struct5_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    decltype(Traits::pair(input)) in_pair = Traits::pair(input);
    mojo::internal::MessageFragment<
        typename decltype(fragment->pair)::BaseType>
        pair_fragment(fragment.message());
    const mojo::internal::ContainerValidateParams pair_validate_params(
        2, false, nullptr);
    mojo::internal::Serialize<mojo::ArrayDataView<::mojo::test::Struct1DataView>>(
        in_pair, pair_fragment, &pair_validate_params);
    fragment->pair.Set(
        pair_fragment.is_null() ? nullptr : pair_fragment.data());
    MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
        fragment->pair.is_null(),
        mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
        "null pair in Struct5 struct");
  }

  static bool Deserialize(::mojo::test::internal::Struct5_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::mojo::test::Struct5DataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo::test::Struct6DataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::mojo::test::Struct6DataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::mojo::test::internal::Struct6_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    decltype(Traits::str(input)) in_str = Traits::str(input);
    mojo::internal::MessageFragment<
        typename decltype(fragment->str)::BaseType> str_fragment(
            fragment.message());
    mojo::internal::Serialize<mojo::StringDataView>(
        in_str, str_fragment);
    fragment->str.Set(
        str_fragment.is_null() ? nullptr : str_fragment.data());
    MOJO_INTERNAL_DLOG_SERIALIZATION_WARNING(
        fragment->str.is_null(),
        mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
        "null str in Struct6 struct");
  }

  static bool Deserialize(::mojo::test::internal::Struct6_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::mojo::test::Struct6DataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo::test::StructOfNullablesDataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::mojo::test::StructOfNullablesDataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::mojo::test::internal::StructOfNullables_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    decltype(Traits::hdl(input)) in_hdl = Traits::hdl(input);
    mojo::internal::Serialize<mojo::ScopedHandle>(
        in_hdl, &fragment->hdl, &fragment.message());
    decltype(Traits::struct_1(input)) in_struct_1 = Traits::struct_1(input);
    mojo::internal::MessageFragment<
        typename decltype(fragment->struct_1)::BaseType> struct_1_fragment(
            fragment.message());
    mojo::internal::Serialize<::mojo::test::Struct1DataView>(
        in_struct_1, struct_1_fragment);
    fragment->struct_1.Set(
        struct_1_fragment.is_null() ? nullptr : struct_1_fragment.data());
    decltype(Traits::str(input)) in_str = Traits::str(input);
    mojo::internal::MessageFragment<
        typename decltype(fragment->str)::BaseType> str_fragment(
            fragment.message());
    mojo::internal::Serialize<mojo::StringDataView>(
        in_str, str_fragment);
    fragment->str.Set(
        str_fragment.is_null() ? nullptr : str_fragment.data());
  }

  static bool Deserialize(::mojo::test::internal::StructOfNullables_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::mojo::test::StructOfNullablesDataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal

}  // namespace mojo


namespace mojo {
namespace test {





inline void Struct3DataView::GetStruct1DataView(
    Struct1DataView* output) {
  auto pointer = data_->struct_1.Get();
  *output = Struct1DataView(pointer, message_);
}


inline void Struct4DataView::GetDataDataView(
    mojo::ArrayDataView<Struct1DataView>* output) {
  auto pointer = data_->data.Get();
  *output = mojo::ArrayDataView<Struct1DataView>(pointer, message_);
}


inline void Struct5DataView::GetPairDataView(
    mojo::ArrayDataView<Struct1DataView>* output) {
  auto pointer = data_->pair.Get();
  *output = mojo::ArrayDataView<Struct1DataView>(pointer, message_);
}


inline void Struct6DataView::GetStrDataView(
    mojo::StringDataView* output) {
  auto pointer = data_->str.Get();
  *output = mojo::StringDataView(pointer, message_);
}


inline void StructOfNullablesDataView::GetStruct1DataView(
    Struct1DataView* output) {
  auto pointer = data_->struct_1.Get();
  *output = Struct1DataView(pointer, message_);
}
inline void StructOfNullablesDataView::GetStrDataView(
    mojo::StringDataView* output) {
  auto pointer = data_->str.Get();
  *output = mojo::StringDataView(pointer, message_);
}



}  // namespace test
}  // namespace mojo

// Declare TraceFormatTraits for enums, which should be defined in ::perfetto
// namespace.

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SERIALIZATION_TEST_STRUCTS_MOJOM_SHARED_H_

/* Metadata comment
eyJtZXRhIjogW10sICJ0eXBlIjogImt5dGhlMCJ9
*/