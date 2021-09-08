// mojo/public/cpp/bindings/tests/idle_tracking_unittest.test-mojom-shared.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/public/cpp/bindings/tests/idle_tracking_unittest.test-mojom-shared.h"

#include <utility>

#include "base/stl_util.h"  // for base::size()
#include "base/strings/stringprintf.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/lib/validation_util.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/cpp/bindings/tests/idle_tracking_unittest.test-mojom-params-data.h"
namespace mojo {
namespace test {
namespace idle_tracking_unittest {
namespace mojom {

namespace internal {


// static
bool TestService_Ping_Params_Data::Validate(
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
  const TestService_Ping_Params_Data* object = static_cast<const TestService_Ping_Params_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  return true;
}

TestService_Ping_Params_Data::TestService_Ping_Params_Data()
    : header_({sizeof(*this), 0}) {}


// static
bool TestService_PingPong_Params_Data::Validate(
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
  const TestService_PingPong_Params_Data* object = static_cast<const TestService_PingPong_Params_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  return true;
}

TestService_PingPong_Params_Data::TestService_PingPong_Params_Data()
    : header_({sizeof(*this), 0}) {}


// static
bool TestService_PingPong_ResponseParams_Data::Validate(
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
  const TestService_PingPong_ResponseParams_Data* object = static_cast<const TestService_PingPong_ResponseParams_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  return true;
}

TestService_PingPong_ResponseParams_Data::TestService_PingPong_ResponseParams_Data()
    : header_({sizeof(*this), 0}) {}


// static
bool TestService_BindKeepAlive_Params_Data::Validate(
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
  const TestService_BindKeepAlive_Params_Data* object = static_cast<const TestService_BindKeepAlive_Params_Data*>(data);
  ALLOW_UNUSED_LOCAL(object);

  if (!mojo::internal::ValidateHandleOrInterfaceNonNullable(
          object->receiver, 1, validation_context)) {
    return false;
  }
  if (!mojo::internal::ValidateHandleOrInterface(object->receiver,
                                                 validation_context)) {
    return false;
  }

  return true;
}

TestService_BindKeepAlive_Params_Data::TestService_BindKeepAlive_Params_Data()
    : header_({sizeof(*this), 0}) {}

}  // namespace internal
}  // namespace mojom
}  // namespace idle_tracking_unittest
}  // namespace test
}  // namespace mojo
