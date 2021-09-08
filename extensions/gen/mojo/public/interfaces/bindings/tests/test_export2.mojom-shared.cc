// mojo/public/interfaces/bindings/tests/test_export2.mojom-shared.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/public/interfaces/bindings/tests/test_export2.mojom-shared.h"

#include <utility>

#include "base/stl_util.h"  // for base::size()
#include "base/strings/stringprintf.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/lib/validation_util.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/interfaces/bindings/tests/test_export2.mojom-params-data.h"
namespace mojo {
namespace test {
namespace test_export2 {

namespace internal {


// static
bool StringPair_Data::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  if (!data)
    return true;
  if (!ValidateUnversionedStructHeaderAndSizeAndClaimMemory(
          data, 24, validation_context)) {
    return false;
  }

  // NOTE: The memory backing |object| may be smaller than |sizeof(*object)| if
  // the message comes from an older version.
  const StringPair_Data* object = static_cast<const StringPair_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  if (!mojo::internal::ValidatePointerNonNullable(
          object->s1, 1, validation_context)) {
    return false;
  }
  const mojo::internal::ContainerValidateParams s1_validate_params(
      0, false, nullptr);
  if (!mojo::internal::ValidateContainer(object->s1, validation_context,
                                         &s1_validate_params)) {
    return false;
  }

  if (!mojo::internal::ValidatePointerNonNullable(
          object->s2, 2, validation_context)) {
    return false;
  }
  const mojo::internal::ContainerValidateParams s2_validate_params(
      0, false, nullptr);
  if (!mojo::internal::ValidateContainer(object->s2, validation_context,
                                         &s2_validate_params)) {
    return false;
  }

  return true;
}

StringPair_Data::StringPair_Data()
    : header_({sizeof(*this), 0}) {}

}  // namespace internal
}  // namespace test_export2
}  // namespace test
}  // namespace mojo