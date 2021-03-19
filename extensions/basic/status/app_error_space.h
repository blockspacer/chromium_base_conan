#pragma once

#include <basic/status/status_macros.h>

//
// USAGE
//
// #include <basic/status/app_error_space.h>
// static ::basic::StatusOr<std::string> or_testErr()
// {
//   using namespace ::app_error_space;
//
//   ::basic::StatusOr<std::string> status =
//     MAKE_ERROR(ERR_PERMISSION_DENIED)
//       << "testCustomErr";
//
//   return status;
// }
//
// {
//   ::basic::StatusOr<std::string> or_testErr1 = or_testErr();
//   DVLOG(99) << " or_testErr1 " << or_testErr1;
// }
//
namespace app_error_space {

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
  ERR_TABLE_FULL = 500,                 // Table (e.g. flow table) full.
  ERR_TABLE_EMPTY = 501,                // Table (e.g. flow table) empty.
  ERR_HARDWARE_ERROR = 502,             // Generic hardware error.
  ERR_INVALID_PARAM = 503,              // Invalid param.
  ERR_ENTRY_NOT_FOUND = 504,            // Entry (e.g. flow) not found.
  ERR_ENTRY_EXISTS = 505,               // Entry (e.g. flow) already exists.
  ERR_OPER_NOT_SUPPORTED = 506,         // Unsupported operation.
  ERR_OPER_DISABLED = 507,              // Disabled operation.
  ERR_OPER_TIMEOUT = 508,               // Operation timeout.
  ERR_OPER_STILL_RUNNING = 509,         // Operation still running (chip busy).
  ERR_REBOOT_REQUIRED = 510,            // Operation cannot be done w/o reboot.
  ERR_FEATURE_UNAVAILABLE = 511,        // Feature not available.
  ERR_NOT_INITIALIZED = 512,            // Desired module is not initialized.
  ERR_NO_RESOURCE = 513,                // No resource available (e.g. OOM).
  ERR_FILE_NOT_FOUND = 514,             // The file is not found.
  ERR_AT_LEAST_ONE_OPER_FAILED = 515,   // At least one failed (from many).
  ERR_INVALID_INFO = 516,            // Invalid P4Info pushed.
  ERR_NO_OP = 517                       // No operation performed.
};

// returns the singleton instance to be used through out the code.
const ::basic::ErrorSpace* ErrorSpace();

}  // namespace app_error_space

// Allow using status_macros. For example:
// RETURN_ERROR(ERR_UNKNOWN) << "test";
namespace basic {
namespace status_macros {

template <>
class ErrorCodeOptions<::app_error_space::ErrorCode>
    : public BaseErrorCodeOptions {
 public:
  const ::basic::ErrorSpace* GetErrorSpace() {
    return ::app_error_space::ErrorSpace();
  }
};

}  // namespace status_macros
}  // namespace basic
