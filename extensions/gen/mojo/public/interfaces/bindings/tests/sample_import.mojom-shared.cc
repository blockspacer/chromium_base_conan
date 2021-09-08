// mojo/public/interfaces/bindings/tests/sample_import.mojom-shared.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/public/interfaces/bindings/tests/sample_import.mojom-shared.h"

#include <utility>

#include "base/stl_util.h"  // for base::size()
#include "base/strings/stringprintf.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/lib/validation_util.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/interfaces/bindings/tests/sample_import.mojom-params-data.h"
namespace imported {

std::string ShapeToString(Shape value) {
  switch(value) {
    case Shape::RECTANGLE:
      return "RECTANGLE";
    case Shape::CIRCLE:
      return "CIRCLE";
    case Shape::TRIANGLE:
      return "{TRIANGLE, LAST}";
    default:
      return base::StringPrintf("Unknown Shape value: %i", static_cast<int32_t>(value));
  }
}

std::ostream& operator<<(std::ostream& os, Shape value) {
  return os << ShapeToString(value);
}

std::string AnotherShapeToString(AnotherShape value) {
  switch(value) {
    case AnotherShape::RECTANGLE:
      return "RECTANGLE";
    case AnotherShape::CIRCLE:
      return "CIRCLE";
    case AnotherShape::TRIANGLE:
      return "TRIANGLE";
    default:
      return base::StringPrintf("Unknown AnotherShape value: %i", static_cast<int32_t>(value));
  }
}

std::ostream& operator<<(std::ostream& os, AnotherShape value) {
  return os << AnotherShapeToString(value);
}

std::string YetAnotherShapeToString(YetAnotherShape value) {
  switch(value) {
    case YetAnotherShape::RECTANGLE:
      return "RECTANGLE";
    case YetAnotherShape::CIRCLE:
      return "CIRCLE";
    case YetAnotherShape::TRIANGLE:
      return "TRIANGLE";
    default:
      return base::StringPrintf("Unknown YetAnotherShape value: %i", static_cast<int32_t>(value));
  }
}

std::ostream& operator<<(std::ostream& os, YetAnotherShape value) {
  return os << YetAnotherShapeToString(value);
}

namespace internal {
// static
bool PointOrShape_Data::Validate(
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

  const PointOrShape_Data* object = static_cast<const PointOrShape_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  if (inlined && object->is_null())
    return true;

  switch (object->tag) {

    case PointOrShape_Tag::POINT: {

      if (!mojo::internal::ValidatePointerNonNullable(
              object->data.f_point, 1, validation_context)) {
        return false;
      }
      if (!mojo::internal::ValidateStruct(object->data.f_point, validation_context))
        return false;
      return true;
    }
    case PointOrShape_Tag::SHAPE: {


      if (!::imported::internal::Shape_Data
            ::Validate(object->data.f_shape, validation_context))
        return false;
      return true;
    }
    default: {
      ReportValidationError(
          validation_context,
          mojo::internal::VALIDATION_ERROR_UNKNOWN_UNION_TAG,
          "unknown tag in PointOrShape");
      return false;
    }
  }
}


// static
bool Point_Data::Validate(
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
  const Point_Data* object = static_cast<const Point_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  return true;
}

Point_Data::Point_Data()
    : header_({sizeof(*this), 0}) {}


// static
bool ImportedInterface_DoSomething_Params_Data::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  if (!data)
    return true;
  if (!ValidateUnversionedStructHeaderAndSizeAndClaimMemory(
          data, 8, validation_context)) {
    return false;
  }

  // NOTE: The memory backing |object| may be smaller than |sizeof(*object)| if
  // the message comes from an older version.
  const ImportedInterface_DoSomething_Params_Data* object = static_cast<const ImportedInterface_DoSomething_Params_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  return true;
}

ImportedInterface_DoSomething_Params_Data::ImportedInterface_DoSomething_Params_Data()
    : header_({sizeof(*this), 0}) {}

}  // namespace internal
}  // namespace imported

namespace perfetto {

// static
void TraceFormatTraits<::imported::Shape>::WriteIntoTracedValue(
   perfetto::TracedValue context, ::imported::Shape value) {
  return std::move(context).WriteString(::imported::ShapeToString(value));
}

} // namespace perfetto

namespace perfetto {

// static
void TraceFormatTraits<::imported::AnotherShape>::WriteIntoTracedValue(
   perfetto::TracedValue context, ::imported::AnotherShape value) {
  return std::move(context).WriteString(::imported::AnotherShapeToString(value));
}

} // namespace perfetto

namespace perfetto {

// static
void TraceFormatTraits<::imported::YetAnotherShape>::WriteIntoTracedValue(
   perfetto::TracedValue context, ::imported::YetAnotherShape value) {
  return std::move(context).WriteString(::imported::YetAnotherShapeToString(value));
}

} // namespace perfetto
