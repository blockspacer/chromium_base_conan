// mojo/public/interfaces/bindings/tests/test_data_view.mojom-shared-internal.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_DATA_VIEW_MOJOM_SHARED_INTERNAL_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_DATA_VIEW_MOJOM_SHARED_INTERNAL_H_

#include "mojo/public/cpp/bindings/lib/array_internal.h"
#include "mojo/public/cpp/bindings/lib/bindings_internal.h"
#include "mojo/public/cpp/bindings/lib/map_data_internal.h"
#include "mojo/public/cpp/bindings/lib/buffer.h"
#include "mojo/public/cpp/bindings/lib/native_enum_data.h"
#include "mojo/public/interfaces/bindings/native_struct.mojom-shared-internal.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif

namespace mojo {
namespace internal {
class ValidationContext;
}
}
namespace mojo {
namespace test {
namespace data_view {
namespace internal {
class NestedStruct_Data;
using TestNativeStruct_Data = mojo::native::internal::NativeStruct_Data;
class TestStruct_Data;
class TestUnion_Data;

struct TestEnum_Data {
 public:
  static bool constexpr kIsExtensible = false;

  static bool IsKnownValue(int32_t value) {
    switch (value) {
      case 0:
      case 1:
        return true;
    }
    return false;
  }

  static bool Validate(int32_t value,
                       mojo::internal::ValidationContext* validation_context) {
    if (kIsExtensible || IsKnownValue(value))
      return true;

    ReportValidationError(validation_context,
                          mojo::internal::VALIDATION_ERROR_UNKNOWN_ENUM_VALUE);
    return false;
  }
};

#pragma pack(push, 1)


class  TestUnion_Data {
 public:
  // Used to identify Mojom Union Data Classes.
  typedef void MojomUnionDataType;

  TestUnion_Data() {}
  // Do nothing in the destructor since it won't be called when it is a
  // non-inlined union.
  ~TestUnion_Data() {}

  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context,
                       bool inlined);

  bool is_null() const { return size == 0; }

  void set_null() {
    size = 0U;
    tag = static_cast<TestUnion_Tag>(0);
    data.unknown = 0U;
  }

  // TODO(crbug.com/1148486): SHOUTY_CASE values are being deprecated per C++ code style
  // guidelines (https://google.github.io/styleguide/cppguide.html#Enumerator_Names),
  // please use kCamelCase values instead.  Cleanup NULL_VALUE, BOOL_VALUE, INT_VALUE, etc.
  // generation once codebase is transitioned to kNullValue, kBoolValue, kIntValue, etc.
  enum class TestUnion_Tag : uint32_t {

    
// @generated_from: mojo.test.data_view.TestUnion.f_bool
    F_BOOL,
    
// @generated_from: mojo.test.data_view.TestUnion.f_bool
    kFBool = F_BOOL,
    
// @generated_from: mojo.test.data_view.TestUnion.f_int32
    F_INT32,
    
// @generated_from: mojo.test.data_view.TestUnion.f_int32
    kFInt32 = F_INT32,
  };

  // A note on layout:
  // "Each non-static data member is allocated as if it were the sole member of
  // a struct." - Section 9.5.2 ISO/IEC 14882:2011 (The C++ Spec)
  union MOJO_ALIGNAS(8) Union_ {
    Union_() : unknown(0) {}
    uint8_t f_f_bool : 1;
    int32_t f_f_int32;
    uint64_t unknown;
  };

  uint32_t size;
  TestUnion_Tag tag;
  Union_ data;
};
static_assert(sizeof(TestUnion_Data) == mojo::internal::kUnionDataSize,
              "Bad sizeof(TestUnion_Data)");
class  NestedStruct_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t f_int32;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<NestedStruct_Data>;

  NestedStruct_Data();
  ~NestedStruct_Data() = delete;
};
static_assert(sizeof(NestedStruct_Data) == 16,
              "Bad sizeof(NestedStruct_Data)");
// Used by NestedStruct::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct NestedStruct_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  NestedStruct_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~NestedStruct_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<NestedStruct_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    NestedStruct_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  TestStruct_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<mojo::internal::String_Data> f_string;
  mojo::internal::Pointer<internal::NestedStruct_Data> f_struct;
  mojo::internal::Pointer<internal::TestNativeStruct_Data> f_native_struct;
  mojo::internal::Pointer<mojo::internal::Array_Data<bool>> f_bool_array;
  mojo::internal::Pointer<mojo::internal::Array_Data<int32_t>> f_int32_array;
  mojo::internal::Pointer<mojo::internal::Array_Data<int32_t>> f_enum_array;
  mojo::internal::Pointer<mojo::internal::Array_Data<mojo::internal::Interface_Data>> f_interface_array;
  mojo::internal::Pointer<mojo::internal::Array_Data<mojo::internal::Pointer<mojo::internal::Array_Data<int32_t>>>> f_nested_array;
  mojo::internal::Pointer<mojo::internal::Array_Data<mojo::internal::Pointer<internal::NestedStruct_Data>>> f_struct_array;
  mojo::internal::Pointer<mojo::internal::Array_Data<internal::TestUnion_Data>> f_union_array;
  mojo::internal::Pointer<mojo::internal::Map_Data<mojo::internal::Pointer<mojo::internal::String_Data>, int32_t>> f_map;

 private:
  friend class mojo::internal::MessageFragment<TestStruct_Data>;

  TestStruct_Data();
  ~TestStruct_Data() = delete;
};
static_assert(sizeof(TestStruct_Data) == 96,
              "Bad sizeof(TestStruct_Data)");
// Used by TestStruct::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct TestStruct_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  TestStruct_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~TestStruct_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<TestStruct_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    TestStruct_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};

#pragma pack(pop)

}  // namespace internal
}  // namespace data_view
}  // namespace test
}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_DATA_VIEW_MOJOM_SHARED_INTERNAL_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMjgzNywgImJlZ2luIjogMjgzMSwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5kYXRhX3ZpZXcuVGVzdFVuaW9uLmZf
Ym9vbCJ9fSwgeyJlbmQiOiAyOTIwLCAiYmVnaW4iOiAyOTE0LCAiZWRnZSI6ICIlL2t5dGhlL2Vk
Z2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1
cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6
ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0LmRhdGFfdmlldy5UZXN0VW5pb24uZl9i
b29sIn19LCB7ImVuZCI6IDI5OTYsICJiZWdpbiI6IDI5ODksICJlZGdlIjogIiUva3l0aGUvZWRn
ZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVz
IjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjog
Im1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuZGF0YV92aWV3LlRlc3RVbmlvbi5mX2lu
dDMyIn19LCB7ImVuZCI6IDMwODIsICJiZWdpbiI6IDMwNzUsICJlZGdlIjogIiUva3l0aGUvZWRn
ZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVz
IjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjog
Im1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuZGF0YV92aWV3LlRlc3RVbmlvbi5mX2lu
dDMyIn19XSwgInR5cGUiOiAia3l0aGUwIn0=
*/