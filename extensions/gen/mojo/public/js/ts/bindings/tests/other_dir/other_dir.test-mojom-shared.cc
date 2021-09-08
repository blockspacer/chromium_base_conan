// mojo/public/js/ts/bindings/tests/other_dir/other_dir.test-mojom-shared.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/public/js/ts/bindings/tests/other_dir/other_dir.test-mojom-shared.h"

#include <utility>

#include "base/stl_util.h"  // for base::size()
#include "base/strings/stringprintf.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/lib/validation_util.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/js/ts/bindings/tests/other_dir/other_dir.test-mojom-params-data.h"
namespace mojo {
namespace tstest {
namespace exported {

namespace internal {


// static
bool ExportedStructOtherDir_Data::Validate(
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
  const ExportedStructOtherDir_Data* object = static_cast<const ExportedStructOtherDir_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  return true;
}

ExportedStructOtherDir_Data::ExportedStructOtherDir_Data()
    : header_({sizeof(*this), 0}) {}

}  // namespace internal
}  // namespace exported
}  // namespace tstest
}  // namespace mojo