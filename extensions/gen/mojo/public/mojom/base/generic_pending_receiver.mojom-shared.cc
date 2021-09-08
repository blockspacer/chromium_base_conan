// mojo/public/mojom/base/generic_pending_receiver.mojom-shared.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/public/mojom/base/generic_pending_receiver.mojom-shared.h"

#include <utility>

#include "base/stl_util.h"  // for base::size()
#include "base/strings/stringprintf.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/lib/validation_util.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/mojom/base/generic_pending_receiver.mojom-params-data.h"
namespace mojo_base {
namespace mojom {

namespace internal {


// static
bool GenericPendingReceiver_Data::Validate(
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
  const GenericPendingReceiver_Data* object = static_cast<const GenericPendingReceiver_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  if (!mojo::internal::ValidatePointerNonNullable(
          object->interface_name, 1, validation_context)) {
    return false;
  }
  const mojo::internal::ContainerValidateParams interface_name_validate_params(
      0, false, nullptr);
  if (!mojo::internal::ValidateContainer(object->interface_name, validation_context,
                                         &interface_name_validate_params)) {
    return false;
  }

  if (!mojo::internal::ValidateHandleOrInterfaceNonNullable(
          object->receiving_pipe, 2, validation_context)) {
    return false;
  }
  if (!mojo::internal::ValidateHandleOrInterface(object->receiving_pipe,
                                                 validation_context)) {
    return false;
  }

  return true;
}

GenericPendingReceiver_Data::GenericPendingReceiver_Data()
    : header_({sizeof(*this), 0}) {}

}  // namespace internal
}  // namespace mojom
}  // namespace mojo_base