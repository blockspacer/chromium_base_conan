// mojo/public/js/ts/bindings/tests/export3.test-mojom-shared-internal.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_JS_TS_BINDINGS_TESTS_EXPORT3_TEST_MOJOM_SHARED_INTERNAL_H_
#define MOJO_PUBLIC_JS_TS_BINDINGS_TESTS_EXPORT3_TEST_MOJOM_SHARED_INTERNAL_H_

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
namespace exported {
namespace internal {
class ExportedStructThree_Data;

#pragma pack(push, 1)
class  ExportedStructThree_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  uint8_t value : 1;
  uint8_t padfinal_[7];

 private:
  friend class mojo::internal::MessageFragment<ExportedStructThree_Data>;

  ExportedStructThree_Data();
  ~ExportedStructThree_Data() = delete;
};
static_assert(sizeof(ExportedStructThree_Data) == 16,
              "Bad sizeof(ExportedStructThree_Data)");
// Used by ExportedStructThree::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct ExportedStructThree_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  ExportedStructThree_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~ExportedStructThree_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<ExportedStructThree_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    ExportedStructThree_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};

#pragma pack(pop)

}  // namespace internal
}  // namespace exported
}  // namespace tstest
}  // namespace mojo

#endif  // MOJO_PUBLIC_JS_TS_BINDINGS_TESTS_EXPORT3_TEST_MOJOM_SHARED_INTERNAL_H_

/* Metadata comment
eyJtZXRhIjogW10sICJ0eXBlIjogImt5dGhlMCJ9
*/