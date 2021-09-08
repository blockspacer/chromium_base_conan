// mojo/public/cpp/test/module.test-mojom-shared.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_TEST_MODULE_TEST_MOJOM_SHARED_H_
#define MOJO_PUBLIC_CPP_TEST_MODULE_TEST_MOJOM_SHARED_H_

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
#include "mojo/public/cpp/test/module.test-mojom-shared-internal.h"
#include "mojo/public/cpp/bindings/lib/interface_serialization.h"



#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace test_module {
class StructDataView;

class UnionDataView;


}  // namespace test_module

namespace mojo {
namespace internal {

template <>
struct MojomTypeTraits<::test_module::StructDataView> {
  using Data = ::test_module::internal::Struct_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

template <>
struct MojomTypeTraits<::test_module::UnionDataView> {
  using Data = ::test_module::internal::Union_Data;
  using DataAsArrayElement = Data;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kUnion;
};

}  // namespace internal
}  // namespace mojo


namespace test_module {


// @generated_from: test_module.GlobalEnum
enum class GlobalEnum : int32_t {
  
// @generated_from: test_module.GlobalEnum.FIRST
  FIRST = 0,
  
// @generated_from: test_module.GlobalEnum.SECOND
  SECOND = 2,
  kMinValue = 0,
  kMaxValue = 2,
};

 std::ostream& operator<<(std::ostream& os, GlobalEnum value);
inline bool IsKnownEnumValue(GlobalEnum value) {
  return internal::GlobalEnum_Data::IsKnownValue(
      static_cast<int32_t>(value));
}


// @generated_from: test_module.Struct.StructEnum
enum class Struct_StructEnum : int32_t {
  
// @generated_from: test_module.Struct.StructEnum.SECOND
  SECOND = 0,
  
// @generated_from: test_module.Struct.StructEnum.THIRD
  THIRD = 1,
  
// @generated_from: test_module.Struct.StructEnum.FOURTH
  FOURTH = 4,
  kMinValue = 0,
  kMaxValue = 4,
};

 std::ostream& operator<<(std::ostream& os, Struct_StructEnum value);
inline bool IsKnownEnumValue(Struct_StructEnum value) {
  return internal::Struct_StructEnum_Data::IsKnownValue(
      static_cast<int32_t>(value));
}


// @generated_from: test_module.Interface.InterfaceEnum
enum class Interface_InterfaceEnum : int32_t {
  
// @generated_from: test_module.Interface.InterfaceEnum.FIFTH
  FIFTH = 0,
  
// @generated_from: test_module.Interface.InterfaceEnum.SIXTH
  SIXTH = 6,
  kMinValue = 0,
  kMaxValue = 6,
};

 std::ostream& operator<<(std::ostream& os, Interface_InterfaceEnum value);
inline bool IsKnownEnumValue(Interface_InterfaceEnum value) {
  return internal::Interface_InterfaceEnum_Data::IsKnownValue(
      static_cast<int32_t>(value));
}
// Interface base classes. They are used for type safety check.
class InterfaceInterfaceBase {};

using InterfacePtrDataView =
    mojo::InterfacePtrDataView<InterfaceInterfaceBase>;
using InterfaceRequestDataView =
    mojo::InterfaceRequestDataView<InterfaceInterfaceBase>;
using InterfaceAssociatedPtrInfoDataView =
    mojo::AssociatedInterfacePtrInfoDataView<InterfaceInterfaceBase>;
using InterfaceAssociatedRequestDataView =
    mojo::AssociatedInterfaceRequestDataView<InterfaceInterfaceBase>;


class StructDataView {
 public:
  StructDataView() {}

  StructDataView(
      internal::Struct_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  bool c() const {
    return data_->c;
  }
 private:
  internal::Struct_Data* data_ = nullptr;
};



class UnionDataView {
 public:
  using Tag = internal::Union_Data::Union_Tag;

  UnionDataView() {}

  UnionDataView(
      internal::Union_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const {
    // For inlined unions, |data_| is always non-null. In that case we need to
    // check |data_->is_null()|.
    return !data_ || data_->is_null();
  }

  Tag tag() const { return data_->tag; }
  bool is_a() const { return data_->tag == Tag::A; }
  bool a() const {
    DCHECK(is_a());
    return data_->data.f_a;
  }
  bool is_b() const { return data_->tag == Tag::B; }
  int64_t b() const {
    DCHECK(is_b());
    return data_->data.f_b;
  }

 private:
  internal::Union_Data* data_ = nullptr;
};



}  // namespace test_module

namespace std {

template <>
struct hash<::test_module::GlobalEnum>
    : public mojo::internal::EnumHashImpl<::test_module::GlobalEnum> {};

template <>
struct hash<::test_module::Struct_StructEnum>
    : public mojo::internal::EnumHashImpl<::test_module::Struct_StructEnum> {};

template <>
struct hash<::test_module::Interface_InterfaceEnum>
    : public mojo::internal::EnumHashImpl<::test_module::Interface_InterfaceEnum> {};

}  // namespace std

namespace mojo {


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::test_module::GlobalEnum, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = EnumTraits<::test_module::GlobalEnum, UserType>;

  static void Serialize(UserType input, int32_t* output) {
    *output = static_cast<int32_t>(Traits::ToMojom(input));
  }

  static bool Deserialize(int32_t input, UserType* output) {
    return Traits::FromMojom(::mojo::internal::ToKnownEnumValueHelper(
        static_cast<::test_module::GlobalEnum>(input)), output);
  }
};

}  // namespace internal


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::test_module::Struct_StructEnum, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = EnumTraits<::test_module::Struct_StructEnum, UserType>;

  static void Serialize(UserType input, int32_t* output) {
    *output = static_cast<int32_t>(Traits::ToMojom(input));
  }

  static bool Deserialize(int32_t input, UserType* output) {
    return Traits::FromMojom(::mojo::internal::ToKnownEnumValueHelper(
        static_cast<::test_module::Struct_StructEnum>(input)), output);
  }
};

}  // namespace internal


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::test_module::Interface_InterfaceEnum, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = EnumTraits<::test_module::Interface_InterfaceEnum, UserType>;

  static void Serialize(UserType input, int32_t* output) {
    *output = static_cast<int32_t>(Traits::ToMojom(input));
  }

  static bool Deserialize(int32_t input, UserType* output) {
    return Traits::FromMojom(::mojo::internal::ToKnownEnumValueHelper(
        static_cast<::test_module::Interface_InterfaceEnum>(input)), output);
  }
};

}  // namespace internal


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::test_module::StructDataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::test_module::StructDataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::test_module::internal::Struct_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
    fragment->c = Traits::c(input);
  }

  static bool Deserialize(::test_module::internal::Struct_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::test_module::StructDataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::test_module::UnionDataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = UnionTraits<::test_module::UnionDataView, UserType>;

  static void Serialize(MaybeConstUserType& input,
                        MessageFragment<::test_module::internal::Union_Data>& fragment,
                        bool inlined) {
    if (CallIsNullIfExists<Traits>(input)) {
       if (inlined)
        fragment->set_null();
      return;
    }

    if (!inlined)
      fragment.Allocate();

    // TODO(azani): Handle unknown and objects.
    // Set the not-null flag.
    fragment->size = kUnionDataSize;
    fragment->tag = Traits::GetTag(input);
    switch (fragment->tag) {
      case ::test_module::UnionDataView::Tag::A: {
        decltype(Traits::a(input))
            in_a = Traits::a(input);
        fragment->data.f_a = in_a;
        break;
      }
      case ::test_module::UnionDataView::Tag::B: {
        decltype(Traits::b(input))
            in_b = Traits::b(input);
        fragment->data.f_b = in_b;
        break;
      }
    }
  }

  static bool Deserialize(::test_module::internal::Union_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input || input->is_null())
      return CallSetToNullIfExists<Traits>(output);

    ::test_module::UnionDataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal

}  // namespace mojo


namespace test_module {





}  // namespace test_module

// Declare TraceFormatTraits for enums, which should be defined in ::perfetto
// namespace.

namespace perfetto {

template <>
struct  TraceFormatTraits<::test_module::GlobalEnum> {
 static void WriteIntoTracedValue(perfetto::TracedValue context, ::test_module::GlobalEnum value);
};

} // namespace perfetto

namespace perfetto {

template <>
struct  TraceFormatTraits<::test_module::Struct_StructEnum> {
 static void WriteIntoTracedValue(perfetto::TracedValue context, ::test_module::Struct_StructEnum value);
};

} // namespace perfetto

namespace perfetto {

template <>
struct  TraceFormatTraits<::test_module::Interface_InterfaceEnum> {
 static void WriteIntoTracedValue(perfetto::TracedValue context, ::test_module::Interface_InterfaceEnum value);
};

} // namespace perfetto

#endif  // MOJO_PUBLIC_CPP_TEST_MODULE_TEST_MOJOM_SHARED_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMjAxMiwgImJlZ2luIjogMjAwMiwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogInRlc3RfbW9kdWxlLkdsb2JhbEVudW0ifX0sIHsiZW5k
IjogMjA4NCwgImJlZ2luIjogMjA3OSwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIs
ICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0u
Z29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2ln
bmF0dXJlIjogInRlc3RfbW9kdWxlLkdsb2JhbEVudW0uRklSU1QifX0sIHsiZW5kIjogMjE1MSwg
ImJlZ2luIjogMjE0NSwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjog
ImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291
cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjog
InRlc3RfbW9kdWxlLkdsb2JhbEVudW0uU0VDT05EIn19LCB7ImVuZCI6IDI0NzUsICJiZWdpbiI6
IDI0NTgsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3Jf
ZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20v
Y2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJ0ZXN0X21v
ZHVsZS5TdHJ1Y3QuU3RydWN0RW51bSJ9fSwgeyJlbmQiOiAyNTU2LCAiYmVnaW4iOiAyNTUwLCAi
ZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMi
LCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVt
L3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAidGVzdF9tb2R1bGUuU3Ry
dWN0LlN0cnVjdEVudW0uU0VDT05EIn19LCB7ImVuZCI6IDI2MjgsICJiZWdpbiI6IDI2MjMsICJl
ZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIs
ICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0v
c3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJ0ZXN0X21vZHVsZS5TdHJ1
Y3QuU3RydWN0RW51bS5USElSRCJ9fSwgeyJlbmQiOiAyNzAyLCAiYmVnaW4iOiAyNjk2LCAiZWRn
ZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAi
dm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3Ny
YyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAidGVzdF9tb2R1bGUuU3RydWN0
LlN0cnVjdEVudW0uRk9VUlRIIn19LCB7ImVuZCI6IDMwNTksICJiZWdpbiI6IDMwMzYsICJlZGdl
IjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2
bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3Jj
IiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJ0ZXN0X21vZHVsZS5JbnRlcmZh
Y2UuSW50ZXJmYWNlRW51bSJ9fSwgeyJlbmQiOiAzMTQ0LCAiYmVnaW4iOiAzMTM5LCAiZWRnZSI6
ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5h
bWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIs
ICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAidGVzdF9tb2R1bGUuSW50ZXJmYWNl
LkludGVyZmFjZUVudW0uRklGVEgifX0sIHsiZW5kIjogMzIyMiwgImJlZ2luIjogMzIxNywgImVk
Z2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwg
InZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9z
cmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogInRlc3RfbW9kdWxlLkludGVy
ZmFjZS5JbnRlcmZhY2VFbnVtLlNJWFRIIn19XSwgInR5cGUiOiAia3l0aGUwIn0=
*/