#pragma once

#include <base/logging.h>
#include <base/macros.h>
#include <base/callback.h>
#include <base/sequence_checker.h>
#include <base/memory/ref_counted.h>

#include <basic/status/status_macros.h>
#include <basic/rvalue_cast.h>

#include <string>

// MOTIVATION
//
// Assumed to be used with large, long-lived set of functionality
// that may be enabled or disabled at runtime that can depend
// on other long-lived functionality (for example: plugins,
// hierarchy of ECS systems, global static components, etc.).
// Use to enable or disable functionality based on dependency order
// (plugin initialization or termination may depend on other plugins).
//
// We use `scoped_refptr` because same dependencies may be shared between
// different sets of long-lived functionality.
//
// PERFORMANCE
//
// Large, long-lived set of functionality is not expected to be created often,
// so we assume that modification of dependencies is not performance-critical.
//
namespace basic {

namespace dependency_error_space {

// The custom error space.
enum ErrorCode {
  // These are reserved errors.
  ERR_SUCCESS = 0,  // Success (default value). Same as OK.
  ERR_CANCELLED = 1,
  ERR_UNKNOWN = 2,
  ERR_PERMISSION_DENIED = 7,
  ERR_FAILED_PRECONDITION = 9,
  ERR_ABORTED = 10,
  ERR_OUT_OF_RANGE = 11,
  ERR_UNIMPLEMENTED = 12,
  ERR_INTERNAL = 13,
  ERR_DATA_LOSS = 15,
  ERR_UNAUTHENTICATED = 16,

  // The following errors start from 500,
  // to make sure they are not conflicting with the
  // canonical errors. DO NOT USE ANY VALUE BELOW 500 FOR THE ERRORS BEYOND
  // THIS LINE.
  ERR_CIRCULAR_DEPENDENCY = 500,
  ERR_DEPENDENCY_NOT_FOUND = 501,            // Entry (e.g. flow) not found.
};

// returns the singleton instance to be used through out the code.
const ::basic::ErrorSpace* ErrorSpace();

}  // namespace dependency_error_space

// Allow using status_macros. For example:
// RETURN_ERROR(ERR_UNKNOWN) << "test";
namespace status_macros {

template <>
class ErrorCodeOptions<dependency_error_space::ErrorCode>
    : public BaseErrorCodeOptions {
 public:
  const ::basic::ErrorSpace* GetErrorSpace() {
    return dependency_error_space::ErrorSpace();
  }
};

}  // namespace status_macros

}  // namespace basic
