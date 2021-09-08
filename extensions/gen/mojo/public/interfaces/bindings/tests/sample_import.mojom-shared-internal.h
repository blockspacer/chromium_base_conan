// mojo/public/interfaces/bindings/tests/sample_import.mojom-shared-internal.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_IMPORT_MOJOM_SHARED_INTERNAL_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_IMPORT_MOJOM_SHARED_INTERNAL_H_

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
namespace imported {
namespace internal {
class Point_Data;
class PointOrShape_Data;

struct Shape_Data {
 public:
  static bool constexpr kIsExtensible = false;

  static bool IsKnownValue(int32_t value) {
    switch (value) {
      case 1:
      case 2:
      case 3:
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

struct AnotherShape_Data {
 public:
  static bool constexpr kIsExtensible = false;

  static bool IsKnownValue(int32_t value) {
    switch (value) {
      case 10:
      case 11:
      case 12:
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

struct YetAnotherShape_Data {
 public:
  static bool constexpr kIsExtensible = false;

  static bool IsKnownValue(int32_t value) {
    switch (value) {
      case 20:
      case 21:
      case 22:
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


class  PointOrShape_Data {
 public:
  // Used to identify Mojom Union Data Classes.
  typedef void MojomUnionDataType;

  PointOrShape_Data() {}
  // Do nothing in the destructor since it won't be called when it is a
  // non-inlined union.
  ~PointOrShape_Data() {}

  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context,
                       bool inlined);

  bool is_null() const { return size == 0; }

  void set_null() {
    size = 0U;
    tag = static_cast<PointOrShape_Tag>(0);
    data.unknown = 0U;
  }

  // TODO(crbug.com/1148486): SHOUTY_CASE values are being deprecated per C++ code style
  // guidelines (https://google.github.io/styleguide/cppguide.html#Enumerator_Names),
  // please use kCamelCase values instead.  Cleanup NULL_VALUE, BOOL_VALUE, INT_VALUE, etc.
  // generation once codebase is transitioned to kNullValue, kBoolValue, kIntValue, etc.
  enum class PointOrShape_Tag : uint32_t {

    
// @generated_from: imported.PointOrShape.point
    POINT,
    
// @generated_from: imported.PointOrShape.point
    kPoint = POINT,
    
// @generated_from: imported.PointOrShape.shape
    SHAPE,
    
// @generated_from: imported.PointOrShape.shape
    kShape = SHAPE,
  };

  // A note on layout:
  // "Each non-static data member is allocated as if it were the sole member of
  // a struct." - Section 9.5.2 ISO/IEC 14882:2011 (The C++ Spec)
  union MOJO_ALIGNAS(8) Union_ {
    Union_() : unknown(0) {}
    mojo::internal::Pointer<internal::Point_Data> f_point;
    int32_t f_shape;
    uint64_t unknown;
  };

  uint32_t size;
  PointOrShape_Tag tag;
  Union_ data;
};
static_assert(sizeof(PointOrShape_Data) == mojo::internal::kUnionDataSize,
              "Bad sizeof(PointOrShape_Data)");
class  Point_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t x;
  int32_t y;

 private:
  friend class mojo::internal::MessageFragment<Point_Data>;

  Point_Data();
  ~Point_Data() = delete;
};
static_assert(sizeof(Point_Data) == 16,
              "Bad sizeof(Point_Data)");
// Used by Point::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct Point_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  Point_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~Point_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<Point_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    Point_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};

#pragma pack(pop)

}  // namespace internal
}  // namespace imported

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_IMPORT_MOJOM_SHARED_INTERNAL_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMzg3OCwgImJlZ2luIjogMzg3MywgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogImltcG9ydGVkLlBvaW50T3JTaGFwZS5wb2ludCJ9fSwg
eyJlbmQiOiAzOTUxLCAiYmVnaW4iOiAzOTQ2LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJh
dGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJv
bWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIs
ICJzaWduYXR1cmUiOiAiaW1wb3J0ZWQuUG9pbnRPclNoYXBlLnBvaW50In19LCB7ImVuZCI6IDQw
MTUsICJiZWdpbiI6IDQwMTAsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlw
ZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2ds
ZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVy
ZSI6ICJpbXBvcnRlZC5Qb2ludE9yU2hhcGUuc2hhcGUifX0sIHsiZW5kIjogNDA4OCwgImJlZ2lu
IjogNDA4MywgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hv
cl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNv
bS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogImltcG9y
dGVkLlBvaW50T3JTaGFwZS5zaGFwZSJ9fV0sICJ0eXBlIjogImt5dGhlMCJ9
*/