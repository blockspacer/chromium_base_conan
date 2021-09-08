// mojo/public/mojom/base/unguessable_token.mojom-shared.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/public/mojom/base/unguessable_token.mojom-shared.h"

#include <utility>

#include "base/stl_util.h"  // for base::size()
#include "base/strings/stringprintf.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/lib/validation_util.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/mojom/base/unguessable_token.mojom-params-data.h"
namespace mojo_base {
namespace mojom {

namespace internal {


// static
bool UnguessableToken_Data::Validate(
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
  const UnguessableToken_Data* object = static_cast<const UnguessableToken_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  return true;
}

UnguessableToken_Data::UnguessableToken_Data()
    : header_({sizeof(*this), 0}) {}

}  // namespace internal
}  // namespace mojom
}  // namespace mojo_base