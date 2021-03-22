#include "basic/dependency_hierarchy/dependency_error_space.h" // IWYU pragma: associated

#include <base/logging.h>

#include <algorithm>

namespace basic {

namespace dependency_error_space {

namespace error {

static const char kErrorSpaceName[] = "dependency_error_space::ErrorSpace";

static const char kErrorUnknownStr[] = "UNKNOWN";

::std::string ErrorCode_Name(const ErrorCode code)
{
  switch (code) {
    case ERR_SUCCESS:
      return "ERR_SUCCESS";
    case ERR_CANCELLED:
      return "ERR_CANCELLED";
    case ERR_UNKNOWN:
      return "ERR_UNKNOWN";
    case ERR_PERMISSION_DENIED:
      return "ERR_PERMISSION_DENIED";
    case ERR_FAILED_PRECONDITION:
      return "ERR_FAILED_PRECONDITION";
    case ERR_ABORTED:
      return "ERR_ABORTED";
    case ERR_OUT_OF_RANGE:
      return "ERR_OUT_OF_RANGE";
    case ERR_UNIMPLEMENTED:
      return "ERR_UNIMPLEMENTED";
    case ERR_INTERNAL:
      return "ERR_INTERNAL";
    case ERR_DATA_LOSS:
      return "ERR_DATA_LOSS";
    case ERR_UNAUTHENTICATED:
      return "ERR_UNAUTHENTICATED";
    case ERR_CIRCULAR_DEPENDENCY:
      return "ERR_CIRCULAR_DEPENDENCY";
    case ERR_DEPENDENCY_NOT_FOUND:
      return "ERR_DEPENDENCY_NOT_FOUND";
  }

  // No default clause, clang will abort if a code is missing from
  // above switch.
  return kErrorUnknownStr;
}

::basic::error::Code ErrorCode_Canonical(const ErrorCode code)
{
  switch (code) {
    case ERR_SUCCESS:
      return ::basic::error::OK;
    case ERR_CANCELLED:
      return ::basic::error::CANCELLED;
    case ERR_UNKNOWN:
      return ::basic::error::UNKNOWN;
    case ERR_PERMISSION_DENIED:
      return ::basic::error::PERMISSION_DENIED;
    case ERR_ABORTED:
      return ::basic::error::ABORTED;
    case ERR_DATA_LOSS:
      return ::basic::error::DATA_LOSS;
    case ERR_INTERNAL:
      return ::basic::error::INTERNAL;
    case ERR_DEPENDENCY_NOT_FOUND:
      return ::basic::error::NOT_FOUND;
    case ERR_UNIMPLEMENTED:
      return ::basic::error::UNIMPLEMENTED;
    case ERR_FAILED_PRECONDITION:
      return ::basic::error::FAILED_PRECONDITION;
    case ERR_OUT_OF_RANGE:
    case ERR_CIRCULAR_DEPENDENCY:
      return ::basic::error::OUT_OF_RANGE;
    default:
      return ::basic::error::UNKNOWN;  // Default error.
  }
}

bool ErrorCode_IsValid(const ErrorCode code)
{
  return ErrorCode_Name(code) != kErrorUnknownStr;
}

class ErrorSpace : public ::basic::ErrorSpace {
 public:
  ErrorSpace() : ::basic::ErrorSpace(kErrorSpaceName) {}
  ~ErrorSpace() override {}

  ::std::string String(int code) const final {
    if (!ErrorCode_IsValid(static_cast<ErrorCode>(code))) {
      code = ERR_UNKNOWN;
    }
    return ErrorCode_Name(static_cast<ErrorCode>(code));
  }

  // map custom error code to canonical error code
  ::basic::error::Code CanonicalCode(const ::basic::Status& status) const final {
    return ErrorCode_Canonical(static_cast<ErrorCode>(status.error_code()));
  }

  // ErrorSpace is neither copyable nor movable.
  ErrorSpace(const ErrorSpace&) = delete;
  ErrorSpace& operator=(const ErrorSpace&) = delete;
};

}  // namespace error

// Singleton ErrorSpace.
const ::basic::ErrorSpace* ErrorSpace() {
  static const ::basic::ErrorSpace* space = new error::ErrorSpace();
  return space;
}

// Force registering of the errorspace at run-time.
static const ::basic::ErrorSpace* dummy __attribute__((unused)) =
    dependency_error_space::ErrorSpace();

}  // namespace dependency_error_space

}  // namespace basic
