// mojo/public/interfaces/bindings/tests/struct_with_traits.mojom-shared-internal.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_STRUCT_WITH_TRAITS_MOJOM_SHARED_INTERNAL_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_STRUCT_WITH_TRAITS_MOJOM_SHARED_INTERNAL_H_

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
namespace internal {
class NestedStructWithTraits_Data;
class StructWithTraits_Data;
class StructWithUnreachableTraits_Data;
class StructWithTraitsContainer_Data;
class TrivialStructWithTraits_Data;
class MoveOnlyStructWithTraits_Data;
class MoveOnlyStructWithTraitsContainer_Data;
class StructWithTraitsForUniquePtr_Data;
class EnumWithTraitsContainer_Data;
class StructForceSerialize_Data;
class StructNestedForceSerialize_Data;
class UnionWithTraits_Data;

struct EnumWithTraits_Data {
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


class  UnionWithTraits_Data {
 public:
  // Used to identify Mojom Union Data Classes.
  typedef void MojomUnionDataType;

  UnionWithTraits_Data() {}
  // Do nothing in the destructor since it won't be called when it is a
  // non-inlined union.
  ~UnionWithTraits_Data() {}

  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context,
                       bool inlined);

  bool is_null() const { return size == 0; }

  void set_null() {
    size = 0U;
    tag = static_cast<UnionWithTraits_Tag>(0);
    data.unknown = 0U;
  }

  // TODO(crbug.com/1148486): SHOUTY_CASE values are being deprecated per C++ code style
  // guidelines (https://google.github.io/styleguide/cppguide.html#Enumerator_Names),
  // please use kCamelCase values instead.  Cleanup NULL_VALUE, BOOL_VALUE, INT_VALUE, etc.
  // generation once codebase is transitioned to kNullValue, kBoolValue, kIntValue, etc.
  enum class UnionWithTraits_Tag : uint32_t {

    
// @generated_from: mojo.test.UnionWithTraits.f_int32
    F_INT32,
    
// @generated_from: mojo.test.UnionWithTraits.f_int32
    kFInt32 = F_INT32,
    
// @generated_from: mojo.test.UnionWithTraits.f_struct
    F_STRUCT,
    
// @generated_from: mojo.test.UnionWithTraits.f_struct
    kFStruct = F_STRUCT,
  };

  // A note on layout:
  // "Each non-static data member is allocated as if it were the sole member of
  // a struct." - Section 9.5.2 ISO/IEC 14882:2011 (The C++ Spec)
  union MOJO_ALIGNAS(8) Union_ {
    Union_() : unknown(0) {}
    int32_t f_f_int32;
    mojo::internal::Pointer<internal::NestedStructWithTraits_Data> f_f_struct;
    uint64_t unknown;
  };

  uint32_t size;
  UnionWithTraits_Tag tag;
  Union_ data;
};
static_assert(sizeof(UnionWithTraits_Data) == mojo::internal::kUnionDataSize,
              "Bad sizeof(UnionWithTraits_Data)");
class  NestedStructWithTraits_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t value;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<NestedStructWithTraits_Data>;

  NestedStructWithTraits_Data();
  ~NestedStructWithTraits_Data() = delete;
};
static_assert(sizeof(NestedStructWithTraits_Data) == 16,
              "Bad sizeof(NestedStructWithTraits_Data)");
// Used by NestedStructWithTraits::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct NestedStructWithTraits_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  NestedStructWithTraits_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~NestedStructWithTraits_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<NestedStructWithTraits_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    NestedStructWithTraits_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  StructWithTraits_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t f_enum;
  uint8_t f_bool : 1;
  uint8_t pad1_[3];
  uint32_t f_uint32;
  uint8_t pad2_[4];
  uint64_t f_uint64;
  mojo::internal::Pointer<mojo::internal::String_Data> f_string;
  mojo::internal::Pointer<mojo::internal::String_Data> f_string2;
  mojo::internal::Pointer<mojo::internal::Array_Data<mojo::internal::Pointer<mojo::internal::String_Data>>> f_string_array;
  mojo::internal::Pointer<mojo::internal::Array_Data<mojo::internal::Pointer<mojo::internal::String_Data>>> f_string_set;
  mojo::internal::Pointer<internal::NestedStructWithTraits_Data> f_struct;
  mojo::internal::Pointer<mojo::internal::Array_Data<mojo::internal::Pointer<internal::NestedStructWithTraits_Data>>> f_struct_array;
  mojo::internal::Pointer<mojo::internal::Map_Data<mojo::internal::Pointer<mojo::internal::String_Data>, mojo::internal::Pointer<internal::NestedStructWithTraits_Data>>> f_struct_map;

 private:
  friend class mojo::internal::MessageFragment<StructWithTraits_Data>;

  StructWithTraits_Data();
  ~StructWithTraits_Data() = delete;
};
static_assert(sizeof(StructWithTraits_Data) == 88,
              "Bad sizeof(StructWithTraits_Data)");
// Used by StructWithTraits::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct StructWithTraits_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  StructWithTraits_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~StructWithTraits_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<StructWithTraits_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    StructWithTraits_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  StructWithUnreachableTraits_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  uint8_t ignore_me : 1;
  uint8_t padfinal_[7];

 private:
  friend class mojo::internal::MessageFragment<StructWithUnreachableTraits_Data>;

  StructWithUnreachableTraits_Data();
  ~StructWithUnreachableTraits_Data() = delete;
};
static_assert(sizeof(StructWithUnreachableTraits_Data) == 16,
              "Bad sizeof(StructWithUnreachableTraits_Data)");
// Used by StructWithUnreachableTraits::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct StructWithUnreachableTraits_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  StructWithUnreachableTraits_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~StructWithUnreachableTraits_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<StructWithUnreachableTraits_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    StructWithUnreachableTraits_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  StructWithTraitsContainer_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<internal::StructWithTraits_Data> f_struct;

 private:
  friend class mojo::internal::MessageFragment<StructWithTraitsContainer_Data>;

  StructWithTraitsContainer_Data();
  ~StructWithTraitsContainer_Data() = delete;
};
static_assert(sizeof(StructWithTraitsContainer_Data) == 16,
              "Bad sizeof(StructWithTraitsContainer_Data)");
// Used by StructWithTraitsContainer::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct StructWithTraitsContainer_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  StructWithTraitsContainer_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~StructWithTraitsContainer_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<StructWithTraitsContainer_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    StructWithTraitsContainer_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  TrivialStructWithTraits_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t value;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<TrivialStructWithTraits_Data>;

  TrivialStructWithTraits_Data();
  ~TrivialStructWithTraits_Data() = delete;
};
static_assert(sizeof(TrivialStructWithTraits_Data) == 16,
              "Bad sizeof(TrivialStructWithTraits_Data)");
// Used by TrivialStructWithTraits::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct TrivialStructWithTraits_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  TrivialStructWithTraits_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~TrivialStructWithTraits_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<TrivialStructWithTraits_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    TrivialStructWithTraits_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  MoveOnlyStructWithTraits_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Handle_Data f_handle;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<MoveOnlyStructWithTraits_Data>;

  MoveOnlyStructWithTraits_Data();
  ~MoveOnlyStructWithTraits_Data() = delete;
};
static_assert(sizeof(MoveOnlyStructWithTraits_Data) == 16,
              "Bad sizeof(MoveOnlyStructWithTraits_Data)");
// Used by MoveOnlyStructWithTraits::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct MoveOnlyStructWithTraits_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  MoveOnlyStructWithTraits_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~MoveOnlyStructWithTraits_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<MoveOnlyStructWithTraits_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    MoveOnlyStructWithTraits_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  MoveOnlyStructWithTraitsContainer_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<internal::MoveOnlyStructWithTraits_Data> f_struct;

 private:
  friend class mojo::internal::MessageFragment<MoveOnlyStructWithTraitsContainer_Data>;

  MoveOnlyStructWithTraitsContainer_Data();
  ~MoveOnlyStructWithTraitsContainer_Data() = delete;
};
static_assert(sizeof(MoveOnlyStructWithTraitsContainer_Data) == 16,
              "Bad sizeof(MoveOnlyStructWithTraitsContainer_Data)");
// Used by MoveOnlyStructWithTraitsContainer::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct MoveOnlyStructWithTraitsContainer_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  MoveOnlyStructWithTraitsContainer_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~MoveOnlyStructWithTraitsContainer_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<MoveOnlyStructWithTraitsContainer_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    MoveOnlyStructWithTraitsContainer_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  StructWithTraitsForUniquePtr_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t f_int32;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<StructWithTraitsForUniquePtr_Data>;

  StructWithTraitsForUniquePtr_Data();
  ~StructWithTraitsForUniquePtr_Data() = delete;
};
static_assert(sizeof(StructWithTraitsForUniquePtr_Data) == 16,
              "Bad sizeof(StructWithTraitsForUniquePtr_Data)");
// Used by StructWithTraitsForUniquePtr::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct StructWithTraitsForUniquePtr_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  StructWithTraitsForUniquePtr_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~StructWithTraitsForUniquePtr_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<StructWithTraitsForUniquePtr_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    StructWithTraitsForUniquePtr_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  EnumWithTraitsContainer_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t f_field;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<EnumWithTraitsContainer_Data>;

  EnumWithTraitsContainer_Data();
  ~EnumWithTraitsContainer_Data() = delete;
};
static_assert(sizeof(EnumWithTraitsContainer_Data) == 16,
              "Bad sizeof(EnumWithTraitsContainer_Data)");
// Used by EnumWithTraitsContainer::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct EnumWithTraitsContainer_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  EnumWithTraitsContainer_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~EnumWithTraitsContainer_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<EnumWithTraitsContainer_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    EnumWithTraitsContainer_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  StructForceSerialize_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t value;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<StructForceSerialize_Data>;

  StructForceSerialize_Data();
  ~StructForceSerialize_Data() = delete;
};
static_assert(sizeof(StructForceSerialize_Data) == 16,
              "Bad sizeof(StructForceSerialize_Data)");
// Used by StructForceSerialize::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct StructForceSerialize_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  StructForceSerialize_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~StructForceSerialize_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<StructForceSerialize_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    StructForceSerialize_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  StructNestedForceSerialize_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<internal::StructForceSerialize_Data> force;

 private:
  friend class mojo::internal::MessageFragment<StructNestedForceSerialize_Data>;

  StructNestedForceSerialize_Data();
  ~StructNestedForceSerialize_Data() = delete;
};
static_assert(sizeof(StructNestedForceSerialize_Data) == 16,
              "Bad sizeof(StructNestedForceSerialize_Data)");
// Used by StructNestedForceSerialize::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct StructNestedForceSerialize_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  StructNestedForceSerialize_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~StructNestedForceSerialize_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<StructNestedForceSerialize_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    StructNestedForceSerialize_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};

#pragma pack(pop)

}  // namespace internal
}  // namespace test
}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_STRUCT_WITH_TRAITS_MOJOM_SHARED_INTERNAL_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMzE1NiwgImJlZ2luIjogMzE0OSwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5VbmlvbldpdGhUcmFpdHMuZl9pbnQz
MiJ9fSwgeyJlbmQiOiAzMjM4LCAiYmVnaW4iOiAzMjMxLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2Uv
Z2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6
ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJt
b2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0LlVuaW9uV2l0aFRyYWl0cy5mX2ludDMyIn19
LCB7ImVuZCI6IDMzMTIsICJiZWdpbiI6IDMzMDQsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5l
cmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNo
cm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9t
IiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuVW5pb25XaXRoVHJhaXRzLmZfc3RydWN0In19LCB7
ImVuZCI6IDMzOTcsICJiZWdpbiI6IDMzODksICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0
ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9t
aXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwg
InNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuVW5pb25XaXRoVHJhaXRzLmZfc3RydWN0In19XSwgInR5
cGUiOiAia3l0aGUwIn0=
*/