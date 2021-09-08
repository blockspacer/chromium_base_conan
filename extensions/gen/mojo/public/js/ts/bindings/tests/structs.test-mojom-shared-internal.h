// mojo/public/js/ts/bindings/tests/structs.test-mojom-shared-internal.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_JS_TS_BINDINGS_TESTS_STRUCTS_TEST_MOJOM_SHARED_INTERNAL_H_
#define MOJO_PUBLIC_JS_TS_BINDINGS_TESTS_STRUCTS_TEST_MOJOM_SHARED_INTERNAL_H_

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
namespace tstest {
namespace internal {
class EmptyStruct_Data;
class StructMemberStruct_Data;
class IntStruct_Data;
class BoolStruct_Data;
class NoDefaultValuesStruct_Data;

#pragma pack(push, 1)
class  EmptyStruct_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<EmptyStruct_Data>;

  EmptyStruct_Data();
  ~EmptyStruct_Data() = delete;
};
static_assert(sizeof(EmptyStruct_Data) == 8,
              "Bad sizeof(EmptyStruct_Data)");
// Used by EmptyStruct::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct EmptyStruct_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  EmptyStruct_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~EmptyStruct_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<EmptyStruct_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    EmptyStruct_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  StructMemberStruct_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<internal::EmptyStruct_Data> empty_struct;

 private:
  friend class mojo::internal::MessageFragment<StructMemberStruct_Data>;

  StructMemberStruct_Data();
  ~StructMemberStruct_Data() = delete;
};
static_assert(sizeof(StructMemberStruct_Data) == 16,
              "Bad sizeof(StructMemberStruct_Data)");
// Used by StructMemberStruct::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct StructMemberStruct_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  StructMemberStruct_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~StructMemberStruct_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<StructMemberStruct_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    StructMemberStruct_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  IntStruct_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int8_t value;
  uint8_t padfinal_[7];

 private:
  friend class mojo::internal::MessageFragment<IntStruct_Data>;

  IntStruct_Data();
  ~IntStruct_Data() = delete;
};
static_assert(sizeof(IntStruct_Data) == 16,
              "Bad sizeof(IntStruct_Data)");
// Used by IntStruct::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct IntStruct_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  IntStruct_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~IntStruct_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<IntStruct_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    IntStruct_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  BoolStruct_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  uint8_t value : 1;
  uint8_t padfinal_[7];

 private:
  friend class mojo::internal::MessageFragment<BoolStruct_Data>;

  BoolStruct_Data();
  ~BoolStruct_Data() = delete;
};
static_assert(sizeof(BoolStruct_Data) == 16,
              "Bad sizeof(BoolStruct_Data)");
// Used by BoolStruct::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct BoolStruct_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  BoolStruct_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~BoolStruct_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<BoolStruct_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    BoolStruct_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};
class  NoDefaultValuesStruct_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  uint8_t bool_value : 1;
  int8_t int8_value;
  uint8_t uint8_value;
  uint8_t pad2_[1];
  int16_t int16_value;
  uint16_t uint16_value;
  int32_t int32_value;
  uint32_t uint32_value;
  int64_t int64_value;
  uint64_t uint64_value;
  float float_value;
  uint8_t pad9_[4];
  double double_value;
  mojo::internal::Pointer<mojo::internal::String_Data> string_value;

 private:
  friend class mojo::internal::MessageFragment<NoDefaultValuesStruct_Data>;

  NoDefaultValuesStruct_Data();
  ~NoDefaultValuesStruct_Data() = delete;
};
static_assert(sizeof(NoDefaultValuesStruct_Data) == 64,
              "Bad sizeof(NoDefaultValuesStruct_Data)");
// Used by NoDefaultValuesStruct::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct NoDefaultValuesStruct_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  NoDefaultValuesStruct_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~NoDefaultValuesStruct_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<NoDefaultValuesStruct_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    NoDefaultValuesStruct_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};

#pragma pack(pop)

}  // namespace internal
}  // namespace tstest
}  // namespace mojo

#endif  // MOJO_PUBLIC_JS_TS_BINDINGS_TESTS_STRUCTS_TEST_MOJOM_SHARED_INTERNAL_H_

/* Metadata comment
eyJtZXRhIjogW10sICJ0eXBlIjogImt5dGhlMCJ9
*/