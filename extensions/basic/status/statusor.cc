// Copyright 2018 Google LLC
// Copyright 2018-present Open Networking Foundation
// SPDX-License-Identifier: Apache-2.0


#include "basic/status/statusor.h" // IWYU pragma: associated

#include "basic/status/posix_error_space.h"

#include <errno.h>
#include <algorithm>

#include <base/logging.h>

namespace basic {
namespace internal {

::basic::Status StatusOrHelper::HandleInvalidStatusCtorArg() {
  const char* kMessage =
      "OK Status is not a valid constructor argument to StatusOr<T>";
  LOG(DFATAL) << kMessage;
  // In optimized builds, we will fall back on an EINVAL status.
  // TODO(unknown): Change this to ::basic::error::INVALID_ARGUMENT.
  return ::basic::PosixErrorToStatus(FROM_HERE, EINVAL, kMessage);
}

::basic::Status StatusOrHelper::HandleNullObjectCtorArg() {
  const char* kMessage =
      "NULL is not a valid constructor argument to StatusOr<T*>";
  LOG(DFATAL) << kMessage;
  // In optimized builds, we will fall back on an EINVAL status.
  // TODO(unknown): Change this to ::basic::error::INVALID_ARGUMENT.
  return ::basic::PosixErrorToStatus(FROM_HERE, EINVAL, kMessage);
}

void StatusOrHelper::Crash(const ::basic::Status& status) {
  LOG(FATAL) << "Attempting to fetch value instead of handling error "
             << status;
}

}  // namespace internal
}  // namespace basic
