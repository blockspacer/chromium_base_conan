// mojo/public/interfaces/bindings/tests/test_data_view.mojom-shared.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/public/interfaces/bindings/tests/test_data_view.mojom-shared.h"

#include <utility>

#include "base/stl_util.h"  // for base::size()
#include "base/strings/stringprintf.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/lib/validation_util.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/interfaces/bindings/tests/test_data_view.mojom-params-data.h"
namespace mojo {
namespace test {
namespace data_view {

std::string TestEnumToString(TestEnum value) {
  switch(value) {
    case TestEnum::VALUE_0:
      return "VALUE_0";
    case TestEnum::VALUE_1:
      return "VALUE_1";
    default:
      return base::StringPrintf("Unknown TestEnum value: %i", static_cast<int32_t>(value));
  }
}

std::ostream& operator<<(std::ostream& os, TestEnum value) {
  return os << TestEnumToString(value);
}

namespace internal {
// static
bool TestUnion_Data::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context,
    bool inlined) {
  if (!data) {
    DCHECK(!inlined);
    return true;
  }

  // If it is inlined, the alignment is already enforced by its enclosing
  // object. We don't have to validate that.
  DCHECK(!inlined || mojo::internal::IsAligned(data));

  if (!inlined &&
      !mojo::internal::ValidateNonInlinedUnionHeaderAndClaimMemory(
          data, validation_context)) {
    return false;
  }

  const TestUnion_Data* object = static_cast<const TestUnion_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  if (inlined && object->is_null())
    return true;

  switch (object->tag) {

    case TestUnion_Tag::F_BOOL: {

      return true;
    }
    case TestUnion_Tag::F_INT32: {

      return true;
    }
    default: {
      ReportValidationError(
          validation_context,
          mojo::internal::VALIDATION_ERROR_UNKNOWN_UNION_TAG,
          "unknown tag in TestUnion");
      return false;
    }
  }
}


// static
bool NestedStruct_Data::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  if (!data)
    return true;
  if (!ValidateUnversionedStructHeaderAndSizeAndClaimMemory(
          data, 16, validation_context)) {
    return false;
  }

  // NOTE: The memory backing |object| may be smaller than |sizeof(*object)| if
  // the message comes from an older version.
  const NestedStruct_Data* object = static_cast<const NestedStruct_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  return true;
}

NestedStruct_Data::NestedStruct_Data()
    : header_({sizeof(*this), 0}) {}


// static
bool TestStruct_Data::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  if (!data)
    return true;
  if (!ValidateUnversionedStructHeaderAndSizeAndClaimMemory(
          data, 96, validation_context)) {
    return false;
  }

  // NOTE: The memory backing |object| may be smaller than |sizeof(*object)| if
  // the message comes from an older version.
  const TestStruct_Data* object = static_cast<const TestStruct_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  if (!mojo::internal::ValidatePointerNonNullable(
          object->f_string, 1, validation_context)) {
    return false;
  }
  const mojo::internal::ContainerValidateParams f_string_validate_params(
      0, false, nullptr);
  if (!mojo::internal::ValidateContainer(object->f_string, validation_context,
                                         &f_string_validate_params)) {
    return false;
  }

  if (!mojo::internal::ValidateStruct(object->f_struct, validation_context))
    return false;

  if (!mojo::internal::ValidateStruct(object->f_native_struct, validation_context))
    return false;

  if (!mojo::internal::ValidatePointerNonNullable(
          object->f_bool_array, 4, validation_context)) {
    return false;
  }
  const mojo::internal::ContainerValidateParams f_bool_array_validate_params(
      0, false, nullptr);
  if (!mojo::internal::ValidateContainer(object->f_bool_array, validation_context,
                                         &f_bool_array_validate_params)) {
    return false;
  }

  if (!mojo::internal::ValidatePointerNonNullable(
          object->f_int32_array, 5, validation_context)) {
    return false;
  }
  const mojo::internal::ContainerValidateParams f_int32_array_validate_params(
      0, false, nullptr);
  if (!mojo::internal::ValidateContainer(object->f_int32_array, validation_context,
                                         &f_int32_array_validate_params)) {
    return false;
  }

  if (!mojo::internal::ValidatePointerNonNullable(
          object->f_enum_array, 6, validation_context)) {
    return false;
  }
  const mojo::internal::ContainerValidateParams f_enum_array_validate_params(
      0, ::mojo::test::data_view::internal::TestEnum_Data::Validate);
  if (!mojo::internal::ValidateContainer(object->f_enum_array, validation_context,
                                         &f_enum_array_validate_params)) {
    return false;
  }

  if (!mojo::internal::ValidatePointerNonNullable(
          object->f_interface_array, 7, validation_context)) {
    return false;
  }
  const mojo::internal::ContainerValidateParams f_interface_array_validate_params(
      0, false, nullptr);
  if (!mojo::internal::ValidateContainer(object->f_interface_array, validation_context,
                                         &f_interface_array_validate_params)) {
    return false;
  }

  if (!mojo::internal::ValidatePointerNonNullable(
          object->f_nested_array, 8, validation_context)) {
    return false;
  }
  const mojo::internal::ContainerValidateParams f_nested_array_validate_params(
      0, false, new mojo::internal::ContainerValidateParams(0, false, nullptr));
  if (!mojo::internal::ValidateContainer(object->f_nested_array, validation_context,
                                         &f_nested_array_validate_params)) {
    return false;
  }

  if (!mojo::internal::ValidatePointerNonNullable(
          object->f_struct_array, 9, validation_context)) {
    return false;
  }
  const mojo::internal::ContainerValidateParams f_struct_array_validate_params(
      0, false, nullptr);
  if (!mojo::internal::ValidateContainer(object->f_struct_array, validation_context,
                                         &f_struct_array_validate_params)) {
    return false;
  }

  if (!mojo::internal::ValidatePointerNonNullable(
          object->f_union_array, 10, validation_context)) {
    return false;
  }
  const mojo::internal::ContainerValidateParams f_union_array_validate_params(
      0, false, nullptr);
  if (!mojo::internal::ValidateContainer(object->f_union_array, validation_context,
                                         &f_union_array_validate_params)) {
    return false;
  }

  if (!mojo::internal::ValidatePointerNonNullable(
          object->f_map, 11, validation_context)) {
    return false;
  }
  const mojo::internal::ContainerValidateParams f_map_validate_params(
      new mojo::internal::ContainerValidateParams(0, false, new mojo::internal::ContainerValidateParams(0, false, nullptr)), new mojo::internal::ContainerValidateParams(0, false, nullptr));
  if (!mojo::internal::ValidateContainer(object->f_map, validation_context,
                                         &f_map_validate_params)) {
    return false;
  }

  return true;
}

TestStruct_Data::TestStruct_Data()
    : header_({sizeof(*this), 0}) {}


// static
bool TestInterface_Echo_Params_Data::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  if (!data)
    return true;
  if (!ValidateUnversionedStructHeaderAndSizeAndClaimMemory(
          data, 16, validation_context)) {
    return false;
  }

  // NOTE: The memory backing |object| may be smaller than |sizeof(*object)| if
  // the message comes from an older version.
  const TestInterface_Echo_Params_Data* object = static_cast<const TestInterface_Echo_Params_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  return true;
}

TestInterface_Echo_Params_Data::TestInterface_Echo_Params_Data()
    : header_({sizeof(*this), 0}) {}


// static
bool TestInterface_Echo_ResponseParams_Data::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  if (!data)
    return true;
  if (!ValidateUnversionedStructHeaderAndSizeAndClaimMemory(
          data, 16, validation_context)) {
    return false;
  }

  // NOTE: The memory backing |object| may be smaller than |sizeof(*object)| if
  // the message comes from an older version.
  const TestInterface_Echo_ResponseParams_Data* object = static_cast<const TestInterface_Echo_ResponseParams_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  return true;
}

TestInterface_Echo_ResponseParams_Data::TestInterface_Echo_ResponseParams_Data()
    : header_({sizeof(*this), 0}) {}

}  // namespace internal
}  // namespace data_view
}  // namespace test
}  // namespace mojo

namespace perfetto {

// static
void TraceFormatTraits<::mojo::test::data_view::TestEnum>::WriteIntoTracedValue(
   perfetto::TracedValue context, ::mojo::test::data_view::TestEnum value) {
  return std::move(context).WriteString(::mojo::test::data_view::TestEnumToString(value));
}

} // namespace perfetto
