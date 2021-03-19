// Copyright 2018 Google LLC
// Copyright 2018-present Open Networking Foundation
// SPDX-License-Identifier: Apache-2.0


// This package defines the POSIX error space (think 'errno'
// values). Given a (stable) errno value, this class can be used to
// translate that value to a string description by calling the
// 'String' method below.
//
//  e.g.: cout << PosixErrorSpace()->String(ENOSYS);
//
// As a convenience, this package provides a static ToStatus routine
// which returns a Status object referring to this error space
// with the given code and message.
//
//  e.g.: return PosixErrorToStatus(ENOSYS, "Not Implemented");
//
// Calls to PosixErrorToStatus where 'code' is zero will be short
// circuited by the implementation of Status to be equivalent to
// Status::OK, ignoring this error space and the provided message.
//


#pragma once

#include "basic/status/status.h"

#include <string>

namespace basic {

const ErrorSpace* PosixErrorSpace();

inline Status PosixErrorToStatus(const base::Location& location, int code, const std::string& message) {
  return Status(location, PosixErrorSpace(), code, message);
}

}  // namespace basic
