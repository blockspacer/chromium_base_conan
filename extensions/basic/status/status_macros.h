// Copyright 2018 Google LLC
// Copyright 2018-present Open Networking Foundation
// SPDX-License-Identifier: Apache-2.0


// This library contains helper macros and methods to make returning errors
// and propagating statuses easier.
//
// We use ::basic::Status for error codes.  Methods that return status should
// have signatures like
//   ::basic::Status Method(arg, ...);
// or
//   ::basic::StatusOr<ValueType> Method(arg, ...);
//
// Inside the method, to return errors, use the macros
//   RETURN_ERROR() << "Message with ::basic::error::UNKNOWN code";
//   RETURN_ERROR(code_enum)
//       << "Message with an error code, in that error_code's ErrorSpace "
//       << "(See ErrorCodeOptions below)";
//   RETURN_ERROR(error_space, code_int)
//       << "Message with integer error code in specified ErrorSpace "
//       << "(Not recommended - use previous form with an enum code instead)";
//
// When calling another method, use this to propagate status easily.
//   RETURN_IF_NOT_OK(method(args));
//
// Use this to also append to the end of the error message when propagating
// an error:
//   RETURN_WITH_MESSAGE_IF_NOT_OK(method(args)) << " for method with " << args;
//
// Use this to propagate the status to a Stubby1 or Stubby2 RPC easily. This
// assumes an AutoClosureRunner has been set up on the RPC's associated
// closure, or it gets run some other way to signal the RPC's termination.
//   RETURN_RPC_IF_NOT_OK(rpc, method(args));
//
// Use this to propagate the status to a ::basic::Task* instance
// calling task->Return() with the status.
//   RETURN_TASK_IF_NOT_OK(task, method(args));
//
// For StatusOr results, you can extract the value or return on error.
//   CONSUME_OR_RETURN(ValueType value, MaybeGetValue(arg));
// Or:
//   ValueType value;
//   CONSUME_OR_RETURN(value, MaybeGetValue(arg));
//
// WARNING: CONSUME_OR_RETURN expands into multiple statements; it cannot be used
//  in a single statement (e.g. as the body of an if statement without {})!
//
// This can optionally be used to return ::basic::Status::OK.
//   RETURN_OK();
//
// To construct an error without immediately returning it, use MAKE_ERROR,
// which supports the same argument types as RETURN_ERROR.
//   ::basic::Status status = MAKE_ERROR(...) << "Message";
//
// To add additional text onto an existing error, use
//   ::basic::Status new_status = APPEND_ERROR(status) << ", additional details";
//
// These macros can also be assigned to a ::basic::StatusOr variable:
//   ::basic::StatusOr<T> status_or = MAKE_ERROR(...) << "Message";
//
// They can also be used to return from a function that returns
// ::basic::StatusOr:
//   ::basic::StatusOr<T> MyFunction() {
//     RETURN_ERROR(...) << "Message";
//   }
//
//
// Error codes:
//
// Using error codes is optional.  ::basic::error::UNKNOWN will be used if no
// code is provided.
//
// By default, these macros work with canonical ::basic::error::Code codes,
// using the canonical ErrorSpace. These macros will also work with
// project-specific ErrorSpaces and error code enums if a specialization
// of ErrorCodeOptions is defined.
//
//
// Logging:
//
// RETURN_ERROR and MAKE_ERROR log the error to LOG(ERROR) by default.
//
// Logging can be turned on or off for a specific error by using
//   RETURN_ERROR().with_logging() << "Message logged to LOG(ERROR)";
//   RETURN_ERROR().without_logging() << "Message not logged";
//   RETURN_ERROR().set_logging(false) << "Message not logged";
//   RETURN_ERROR().severity(INFO) << "Message logged to LOG(INFO)";
//
// If logging is enabled, this will make an error also log a stack trace.
//   RETURN_ERROR().with_log_stack_trace() << "Message";
//
// Logging can also be controlled within a scope using
// ScopedErrorLogSuppression.
//
//
// Assertion handling:
//
// When you would use a CHECK, CHECK_EQ, etc, you can instead use RET_CHECK
// to return a ::basic::Status if the condition is not met:
//   RET_CHECK(ptr != null);
//   RET_CHECK_GT(value, 0) << "Optional additional message";
//   RET_CHECK_FAIL() << "Always fail, like a LOG(FATAL)";
//
// These are a better replacement for CHECK because they don't crash, and for
// DCHECK and LOG(DFATAL) because they don't ignore errors in opt builds.
//
// The RET_CHECK* macros can only be used in functions that return
// ::basic::Status.
//
// The returned error will have the ::basic::error::INTERNAL error code and the
// message will include the file and line number.  The current stack trace
// will also be logged.

#pragma once

#include "basic/status/status.h"
#include "basic/status/statusor.h"

#include <memory>
#include <ostream>
#include <sstream> // IWYU pragma: keep
#include <string>
#include <vector>

#include <base/logging.h>
#include <base/macros.h>
#include <basic/rvalue_cast.h>
#include <base/location.h>
#include <base/compiler_specific.h>
#include <base/callback_forward.h>

namespace basic {

namespace status_macros {

using logging::LogSeverity;

bool IsMacroErrorLoggedByDefault();

/// \note logs even if `IsMacroErrorLoggedByDefault` disabled.
/// Use for important errors that must always be logged.
//
// USAGE
//
// ERR_IF_NOT_OK(statusor.status());
//
// // passes extra args to status_macros::LogError
// ERR_IF_NOT_OK(statusor.status(), ERROR, /*should_log_stack_trace*/ true);
//
#define ERR_IF_NOT_OK(expr, ...) \
  do {                                                                         \
    /* Using _status below to avoid capture problems if expr is "status". */   \
    const ::basic::Status _status = (expr);                                    \
    if (UNLIKELY(!_status.ok())) {                                             \
      ::basic::status_macros::LogError(_status, FROM_HERE, ##__VA_ARGS__);  \
    }                                                                          \
  } while (0)

// Emit a warning if 'to_call' returns a bad status.
#define WARN_IF_NOT_OK(to_call, warning_prefix) do { \
    ::basic::Status _s = (to_call); \
    if (UNLIKELY(!_s.ok())) { \
      LOG(WARNING) << (warning_prefix) << ": " << _s;  \
    } \
  } while (0);

void LogError(const ::basic::Status& status
  , const ::base::Location location
  , LogSeverity log_severity = ::logging::LOG_ERROR
  , bool should_log_stack_trace = true);

// Base class for options attached to a project-specific error code enum.
// Projects that use non-canonical error codes should specialize the
// ErrorCodeOptions template below with a subclass of this class, overriding
// GetErrorSpace, and optionally other methods.
class BaseErrorCodeOptions {
 public:
  // Return the ErrorSpace to use for this error code enum.
  // Not implemented in base class - must be overridden.
  const ::basic::ErrorSpace* GetErrorSpace();

  // Returns true if errors with this code should be logged upon creation, by
  // default.  (Default can be overridden with modifiers on MakeErrorStream.)
  // Can be overridden to customize default logging per error code.
  bool IsLoggedByDefault(int code) { return IsMacroErrorLoggedByDefault(); }
};

// Template that should be specialized for any project-specific error code enum.
template <typename ERROR_CODE_ENUM_TYPE>
class ErrorCodeOptions;

// Specialization for the canonical error codes and canonical ErrorSpace.
template <>
class ErrorCodeOptions< ::basic::error::Code> : public BaseErrorCodeOptions {
 public:
  const ::basic::ErrorSpace* GetErrorSpace() {
    return ::basic::Status::canonical_space();
  }
};

// Stream object used to collect error messages in MAKE_ERROR macros or
// append error messages with APPEND_ERROR.
// It accepts any arguments with operator<< to build an error string, and
// then has an implicit cast operator to ::basic::Status, which converts the
// logged string to a Status object and returns it, after logging the error.
// At least one call to operator<< is required; a compile time error will be
// generated if none are given. Errors will only be logged by default for
// certain status codes, as defined in IsLoggedByDefault. This class will
// give DFATAL errors if you don't retrieve a ::basic::Status exactly once before
// destruction.
//
class MakeErrorStream {
 public:
  // Make an error with ::basic::error::UNKNOWN.
  MakeErrorStream(const base::Location& location)
      : impl_(new Impl(location,
                       ::basic::Status::canonical_space(),
                       ::basic::error::UNKNOWN, this)) {}

  // Make an error with the given error code and error_space.
  MakeErrorStream(const ::base::Location& location,
                  const ::basic::ErrorSpace* error_space, int code)
      : impl_(new Impl(location, error_space, code, this)) {}

  // Make an error that appends additional messages onto a copy of status.
  MakeErrorStream(::basic::Status status, const ::base::Location& location)
      : impl_(new Impl(status, location, this)) {}

  // Make an error with the given code, inferring its ErrorSpace from
  // code's type using the specialized ErrorCodeOptions.
  template <typename ERROR_CODE_TYPE>
  MakeErrorStream(const ::base::Location& location, ERROR_CODE_TYPE code)
    : impl_(new Impl(
          location,
          ErrorCodeOptions<ERROR_CODE_TYPE>().GetErrorSpace(),
          code, this,
          ErrorCodeOptions<ERROR_CODE_TYPE>().IsLoggedByDefault(code))) {}

  // Implicit cast operators to ::basic::Status and ::basic::StatusOr.
  // Exactly one of these must be called exactly once before destruction.
  operator ::basic::Status () const NO_EXCEPTION {
    return GetStatus();
  }
  template <typename T>
  operator ::basic::StatusOr<T> () const NO_EXCEPTION {
    return GetStatus();
  }

  template <typename T>
  MakeErrorStream& operator<<(const T& value) & {
    CheckNotDone();
    impl_->stream_ << value;
    return *this;
  }

  template <typename T>
  MakeErrorStream&& operator<<(const T& value) && {
    CheckNotDone();
    impl_->stream_ << value;
    // moving this is ok here because method is ref-qualified with &&
    return RVALUE_CAST(*this);
  }

  // Disable sending this message to LOG(ERROR), even if this code is usually
  // logged. Some error codes are logged by default, and others are not.
  // Usage:
  //   RETURN_ERROR().without_logging() << "Message";
  MakeErrorStream& without_logging() {
    impl_->should_log_ = false;
    return *this;
  }

  // Send this message to LOG(ERROR), even if this code is not usually logged.
  // Usage:
  //   RETURN_ERROR().with_logging() << "Message";
  MakeErrorStream& with_logging() {
    impl_->should_log_ = true;
    return *this;
  }

  MakeErrorStream& with_debug_logging() {
#if DCHECK_IS_ON()
    impl_->should_log_ = true;
#else
    impl_->should_log_ = false;
#endif // DCHECK_IS_ON
    return *this;
  }

  // `with_dvlog(99)` resuts in `DVLOG(99)`
  // Usage:
  //   RETURN_ERROR().with_dvlog(99) << "Message";
  MakeErrorStream& with_dvlog(LogSeverity log_severity) {
    /// \note positive log severity will become log verbosity that < 0
    DCHECK_GT(log_severity, 0);
    return with_debug_logging().severity(-log_severity);
  }

  // `with_vlog(99)` resuts in `VLOG(99)`
  // Usage:
  //   RETURN_ERROR().with_vlog(99) << "Message";
  MakeErrorStream& with_vlog(LogSeverity log_severity) {
    /// \note positive log severity will become log verbosity that < 0
    DCHECK_GT(log_severity, 0);
    return with_logging().severity(-log_severity);
  }

  // Determine whether to log this message based on the value of <should_log>.
  MakeErrorStream& set_logging(bool should_log) {
    impl_->should_log_ = should_log;
    return *this;
  }

  // Log the status at this LogSeverity: INFO, WARNING, or ERROR.
  // Setting severity to NUM_SEVERITIES will disable logging.]
  //
  /// \note pass `-9` to set VLOG(9)
  //
  // USAGE
  //
  // RETURN_ERROR().with_logging().severity(logging::LOG_WARNING) << "...";
  //
  MakeErrorStream& severity(LogSeverity log_severity) {
    impl_->log_severity_ = log_severity;
    return *this;
  }

  // When this message is logged (see with_logging()), include the stack trace.
  MakeErrorStream& with_log_stack_trace() {
    impl_->should_log_stack_trace_ = true;
    return *this;
  }

  // When this message is logged, omit the stack trace, even if
  // with_log_stack_trace() was previously called.
  MakeErrorStream& without_log_stack_trace() {
    impl_->should_log_stack_trace_ = false;
    return *this;
  }

  // Adds RET_CHECK failure text to error message.
  MakeErrorStream& add_ret_check_failure(const char* condition) {
    return *this << "RET_CHECK failure (" << impl_->location_.ToString()
                 << ") " << condition << " ";
  }

  // Adds RET_CHECK_FAIL text to error message.
  MakeErrorStream& add_ret_check_fail_failure() {
    return *this << "RET_CHECK_FAIL failure (" << impl_->location_.ToString() << ") ";
  }

  // MakeErrorStream is neither copyable nor movable.
  MakeErrorStream(const MakeErrorStream&) = delete;
  MakeErrorStream& operator=(const MakeErrorStream&) = delete;

  MakeErrorStream(MakeErrorStream&& other)
    : impl_{RVALUE_CAST(other.impl_)}
  {}

  MakeErrorStream& operator=(MakeErrorStream&& other)
  {
    impl_ = RVALUE_CAST(other.impl_);
    return *this;
  }

 private:
  class Impl {
   public:
    Impl(const ::base::Location& location,
         const ::basic::ErrorSpace* error_space, int  code,
         MakeErrorStream* error_stream,
         bool is_logged_by_default = IsMacroErrorLoggedByDefault());
    Impl(const ::basic::Status& status, const ::base::Location& location,
         MakeErrorStream* error_stream);

    ~Impl();

    // This must be called exactly once before destruction.
    ::basic::Status GetStatus();

    void CheckNotDone() const;

    // Impl is neither copyable nor movable.
    Impl(const Impl&) = delete;
    Impl& operator=(const Impl&) = delete;

   private:
    const ::base::Location location_;
    const ::basic::ErrorSpace* error_space_;
    int code_;

    std::string prior_message_;
    bool is_done_;  // true after Status object has been returned
    std::ostringstream stream_;
    bool should_log_;
    LogSeverity log_severity_;
    bool should_log_stack_trace_;

    friend class MakeErrorStream;
  };

  void CheckNotDone() const;

  // Returns the status.
  ::basic::Status GetStatus() const { return impl_->GetStatus(); }

  // Store the actual data on the heap to reduce stack frame sizes.
  std::unique_ptr<Impl> impl_;
};

// Make an error ::basic::Status, building message with LOG-style shift
// operators.  The error also gets sent to LOG(ERROR).
//
// Takes an optional error code parameter. Uses ::basic::error::UNKNOWN by
// default.  Returns a ::basic::Status object that must be returned or stored.
//
// Examples:
//   RETURN_ERROR() << "Message";
//   RETURN_ERROR(INTERNAL_ERROR) << "Message";
//   ::basic::Status status = MAKE_ERROR() << "Message";
#define MAKE_ERROR(...) \
  ::basic::status_macros::MakeErrorStream(FROM_HERE, ##__VA_ARGS__)

// accepts custom |base::Location| i.e. |from_here|
#define MAKE_ERROR_HERE(from_here, ...) \
  ::basic::status_macros::MakeErrorStream(from_here, ##__VA_ARGS__)

/// \note APPEND_ERROR requires !status.ok()
//
// Return a new error based on an existing error,
// with an additional string appended.
// Otherwise behaves like MAKE_ERROR,
// including logging the error by default.
// Requires !status.ok().
// Example:
//   status = APPEND_ERROR(status) << ", more details";
//   return APPEND_ERROR(status) << ", more details";
#define APPEND_ERROR(status) \
  ::basic::status_macros::MakeErrorStream((status), FROM_HERE)

#define RETURN_APPEND_ERROR(status) \
  DCHECK(!status.ok()) << "APPEND_ERROR requires !status.ok()." << status; \
  return APPEND_ERROR(status)

/// \note By default uses `::basic::error::UNKNOWN`.
/// You can change error code like so: `RETURN_ERROR(INVALID_ARGUMENT)`
//
// Shorthand to make an error (with MAKE_ERROR) and return it.
//   if (error) {
//     RETURN_ERROR() << "Message";
//   }
//
#define RETURN_ERROR return MAKE_ERROR

// Return success.
#define RETURN_OK() \
  return ::basic::OkStatus()

/// \note condition must return boolean result (do not pass status here).
//
// Logs condition if check failed.
// Supports `IsMacroErrorLoggedByDefault` feature.
//
// BEFORE
//
// if(!dependency) {
//   RETURN_ERROR(INVALID_ARGUMENT)
//     << "Condition: !dependency failed"
//     << "null can not be dependency";
// }
//
// if(!found == storage_.end()) {
//   RETURN_ERROR(ERR_DEPENDENCY_NOT_FOUND).without_logging()
//     << "Condition: !found == storage_.end() failed"
//     << "Can not remove dependency that was not added before";
// }
//
// AFTER
//
// RETURN_ERROR_IF(!dependency, INVALID_ARGUMENT)
//   << "null can not be dependency";
//
// RETURN_ERROR_IF(found == storage_.end(), ERR_DEPENDENCY_NOT_FOUND).without_logging()
//   << "Can not remove dependency that was not added before";
//
#define RETURN_ERROR_IF(cond, ...)                                             \
  if (UNLIKELY(!(cond))) {                                                       \
  } else /* NOLINT */                                                          \
    return ([&]() -> ::basic::status_macros::MakeErrorStream {                 \
      if (UNLIKELY(::basic::status_macros::IsMacroErrorLoggedByDefault())) {   \
        LOG(ERROR) << "Condition: " << #cond << " failed";                     \
      }                                                                        \
      ::basic::status_macros::MakeErrorStream stream =                         \
        MAKE_ERROR(__VA_ARGS__) << "'" << #cond << "' is false. ";             \
      return RVALUE_CAST(stream); \
    })()

// A simple class to explicitly cast the return value of an ::basic::Status
// to bool.
class BooleanStatus {
 public:
  BooleanStatus(::basic::Status status) : status_(status) {}  // NOLINT
  // Implicitly cast to bool.
  operator bool() const { return status_.ok(); }
  inline ::basic::Status status() const { return status_; }
 private:
  ::basic::Status status_;
};

inline const std::string FixMessage(const std::string& msg) {
  std::string str = msg;
  std::size_t found = str.find_last_not_of(" \t\f\v\n\r");
  if (found != std::string::npos) {
    str.erase(found + 1);
    if (str.back() != '.' && str.back() != '!' && str.back() != '?' &&
        str.back() != ';' && str.back() != ':' && str.back() != ',') {
      str += ". ";
    } else {
      str += " ";
    }
  } else {
    str.clear();
  }

  return str;
}

// USAGE
//
// RETURN_OTHER_STATUS_IF_NOT_OK(status, ERR_INTERNAL)
//   << "Message1"
//   /// \note added message from other status
//   << STATUS_MESSAGE(status);
//
#define STATUS_MESSAGE(x)                                      \
  ::basic::status_macros::FixMessage(x.error_message())

// A macro for simplifying creation of a new error or appending new info to an
// error based on the return value of a function that returns ::basic::Status.
#define APPEND_STATUS_IF_NOT_OK(out, expr)                                      \
  if (const ::basic::status_macros::BooleanStatus __ret = (expr)) {             \
  } else /* NOLINT */                                                          \
    out = APPEND_ERROR(!out.ok() ? out : __ret.status().StripMessage())        \
              .without_logging()                                               \
          << (out.error_message().empty() || out.error_message().back() == ' ' \
                  ? ""                                                         \
                  : " ")                                                       \
          << STATUS_MESSAGE(__ret.status())

#define RETURN_WITH_APPEND_IF_NOT_OK(expr, ...)                                 \
  return APPEND_STATUS_IF_NOT_OK(expr, ##__VA_ARGS__)

// Wraps a ::basic::Status so it can be assigned and used in an if-statement.
// Implicitly converts from status and to bool.
namespace internal {
class UtilStatusConvertibleToBool {
 public:
  // Implicity conversion from a status to wrap.
  // Need implicit conversion to allow in if-statement.
  // NOLINTNEXTLINE(runtime/explicit)
  UtilStatusConvertibleToBool(::basic::Status status) : status_(status) {}
  // Implicity cast to bool. True on ok() and false on error.
  operator bool() const { return LIKELY(status_.ok()); }
  // Returns the wrapped status.
  ::basic::Status status() const { return status_; }

 private:
  ::basic::Status status_;
};
}  // namespace internal

/// \note does not perform extra logging
/// even with `IsMacroErrorLoggedByDefault` enabled bacause status is OK
#define RETURN_IF_OK(expr)                                                   \
  do {                                                                       \
    /* Using _status below to avoid capture problems if expr is "status". */ \
    const ::basic::Status _status = (expr);                                  \
    if (LIKELY(_status.ok())) {                                              \
      return _status;                                                        \
    }                                                                        \
  } while (0)

#define SILENT_RETURN_IF_NOT_OK(expr)                                                \
  do {                                                                       \
    /* Using _status below to avoid capture problems if expr is "status". */ \
    const ::basic::Status _status = (expr);                                   \
    if (UNLIKELY(!_status.ok())) {                                 \
      return _status;                                                        \
    }                                                                        \
  } while (0)

/// \note performs extra logging using `LOG(ERROR)`
/// only if `IsMacroErrorLoggedByDefault` enabled
//
// Run a command that returns a ::basic::Status.  If the called code returns an
// error status, return that status up out of this method too.
//
// Example:
//   RETURN_IF_NOT_OK(DoThings(4));
#define RETURN_IF_NOT_OK(expr)                                                \
  do {                                                                       \
    /* Using _status below to avoid capture problems if expr is "status". */ \
    const ::basic::Status _status = (expr);                                   \
    if (UNLIKELY(!_status.ok())) {                                 \
      if (UNLIKELY(::basic::status_macros::IsMacroErrorLoggedByDefault()))   \
        LOG(ERROR) << "Return Error: " << #expr << " failed with " << _status; \
      return _status;                                                        \
    }                                                                        \
  } while (0)

/// \note performs extra logging using `LOG(ERROR)`
/// only if `IsMacroErrorLoggedByDefault` enabled
//
// This is like RETURN_IF_NOT_OK, but instead of propagating the existing error
// Status, it constructs a new Status and can append additional messages.
//
// This has slightly worse performance that RETURN_IF_NOT_OK in both OK and ERROR
// case. (see status_macros_benchmark.cc for details)
//
// Example:
//   RETURN_WITH_MESSAGE_IF_NOT_OK(DoThings(4)) << "Things went wrong for " << 4;
//
// Args:
//   expr: Command to run that returns a ::basic::Status.
#define RETURN_WITH_MESSAGE_IF_NOT_OK(expr, ...)                                      \
  /* Using _status below to avoid capture problems if expr is "status". */     \
  /* We also need the error to be in the else clause, to avoid a dangling  */  \
  /* else in the client code. (see test for example). */                       \
  if (const ::basic::status_macros::internal::UtilStatusConvertibleToBool      \
          _status = (expr); _status) {                                         \
  } else                                                                       \
    return                                                                     \
      ([&]() -> ::basic::status_macros::MakeErrorStream {                    \
        if (UNLIKELY(::basic::status_macros::IsMacroErrorLoggedByDefault())) { \
          LOG(ERROR) << "Return error: " << #expr << " failed with "           \
                        << _status.status();                                   \
        }                                                                      \
        return ::basic::status_macros::MakeErrorStream(_status.status(),       \
                                                      FROM_HERE,               \
                                                      ##__VA_ARGS__);          \
      })().without_logging()

/// \note returns completely new status, not affected by passed status
//
#define RETURN_OTHER_STATUS_IF_NOT_OK(expr, ...)                                      \
  /* Using _status below to avoid capture problems if expr is "status". */     \
  /* We also need the error to be in the else clause, to avoid a dangling  */  \
  /* else in the client code. (see test for example). */                       \
  if (const ::basic::status_macros::internal::UtilStatusConvertibleToBool      \
          _status = (expr); _status) {                                         \
  } else                                                                       \
    return                                                                     \
      ([&]() -> ::basic::status_macros::MakeErrorStream {                      \
        if (UNLIKELY(::basic::status_macros::IsMacroErrorLoggedByDefault())) { \
          LOG(ERROR) << "Return error: " << #expr << " failed with "           \
                        << _status.status();                                   \
        }                                                                      \
        return ::basic::status_macros::MakeErrorStream(FROM_HERE,               \
                                                      ##__VA_ARGS__);          \
      })().without_logging()

#define SILENT_RETURN_IF_ERROR_CODE_EQUALS(expr, expect_code)                  \
  do {                                                                       \
    /* Using _status below to avoid capture problems if expr is "status". */ \
    const ::basic::Status _status = (expr);                                  \
    if (UNLIKELY(!_status.ok() && expect_code == _status.error_code())) {    \
      return _status;                                                        \
    }                                                                        \
  } while (0)

/// \note performs extra logging using `LOG(ERROR)`
/// only if `IsMacroErrorLoggedByDefault` enabled
//
// Run a command that returns a ::basic::Status.  If the called code returns an
// error status, return that status up out of this method too.
//
// Example:
//   auto res = DoThings(4);
//   RETURN_IF_ERROR_CODE_EQUALS(res, ERR_CIRCULAR_DEPENDENCY)
//     << "Things went wrong";
//   RETURN_IF_ERROR_CODE_EQUALS(res, ERR_INVALID_ARGUMENT)
//     << "Things went wrong";
#define RETURN_IF_ERROR_CODE_EQUALS(expr, expect_code)                         \
  /* Using _status below to avoid capture problems if expr is "status". */     \
  if (const ::basic::status_macros::internal::UtilStatusConvertibleToBool      \
          _status = (expr); _status) {                                         \
  } else if(expect_code == _status.status().error_code())                      \
    return                                                                     \
      ([&]() -> ::basic::status_macros::MakeErrorStream {                      \
        if (UNLIKELY(::basic::status_macros::IsMacroErrorLoggedByDefault())) { \
          LOG(ERROR) << "Return error: " << #expr << " failed with "           \
                        << _status.status();                                   \
        }                                                                      \
        return ::basic::status_macros::MakeErrorStream(_status.status(),       \
                                                      FROM_HERE);              \
      })().without_logging()

// Internal helper for concatenating macro values.
#define STATUS_MACROS_CONCAT_NAME_INNER(x, y) x##y
#define STATUS_MACROS_CONCAT_NAME(x, y) STATUS_MACROS_CONCAT_NAME_INNER(x, y)

/// \note performs extra logging using `LOG(ERROR)`
/// only if `IsMacroErrorLoggedByDefault` enabled
//
// USAGE
//
//  CONSUME_OR_RETURN_WITH_MESSAGE(cached_dictionary_
//    , parseJSONData(json_data), std::string{"failed_to_parse_JSON_string"});
//
#define CONSUME_OR_RETURN_WITH_MESSAGE(lhs, rexpr, ...) \
  CONSUME_OR_RETURN_WITH_MESSAGE_IMPL( \
      STATUS_MACROS_CONCAT_NAME(_status_or_value, __COUNTER__), lhs, rexpr, ##__VA_ARGS__)

#define CONSUME_OR_RETURN_WITH_MESSAGE_IMPL(statusor, lhs, rexpr, ...)    \
  auto statusor = (rexpr);                                                \
  RETURN_WITH_MESSAGE_IF_NOT_OK(statusor.status())                        \
    << "Failed check: " << #rexpr << " " << __VA_ARGS__;                  \
  lhs = std::move(statusor.ConsumeValueOrDie())                           \

/// \note performs extra logging using `LOG(ERROR)`
/// only if `IsMacroErrorLoggedByDefault` enabled
//
// Executes an expression that returns a ::basic::StatusOr, extracting its value
// into the variable defined by lhs (or returning on error).
//
// Think that `CONSUME_OR_RETURN(int value, statusor)` is same as:
// int value;
// if(statusor) {
//   value = statusor.ConsumeValueOrDie();
// } else {
//   return statusor.status();
// } /* It is safe now to use `int value`... */
//
// Example: Declaring and initializing a new value
//   CONSUME_OR_RETURN(const ValueType& value, MaybeGetValue(arg));
//
// Example: Assigning to an existing value
//   ValueType value;
//   CONSUME_OR_RETURN(value, MaybeGetValue(arg));
//
// Example: Assigning std::unique_ptr<T>
//   CONSUME_OR_RETURN(std::unique_ptr<T> ptr, MaybeGetPtr(arg));
//
// The value assignment example would expand into:
//   StatusOr<ValueType> status_or_value = MaybeGetValue(arg);
//   if (!status_or_value.ok()) return status_or_value.status();
//   value = status_or_value.ConsumeValueOrDie();
//
// WARNING: CONSUME_OR_RETURN expands into multiple statements; it cannot be used
//  in a single statement (e.g. as the body of an if statement without {})!
#define CONSUME_OR_RETURN(lhs, rexpr) \
  CONSUME_OR_RETURN_WITH_MESSAGE_IMPL( \
      STATUS_MACROS_CONCAT_NAME(_status_or_value, __COUNTER__), lhs, rexpr, std::string{""})

/// \note performs extra logging using `LOG(ERROR)`
/// only if `IsMacroErrorLoggedByDefault` enabled
//
// Similar to `CONSUME_OR_RETURN_IMPL`, but
// calls `ValueOrDie` instead of `ConsumeValueOrDie`
//
// USAGE
//
//  COPY_OR_RETURN_WITH_MESSAGE(cached_dictionary_
//    , parseJSONData(json_data), std::string{"failed_to_parse_JSON_string"});
//
#define COPY_OR_RETURN_WITH_MESSAGE_IMPL(statusor, lhs, rexpr, ...)       \
  auto statusor = (rexpr);                                                \
  RETURN_WITH_MESSAGE_IF_NOT_OK(statusor.status())                        \
    << "Failed check: " << #rexpr << " " << __VA_ARGS__;                  \
  lhs = statusor.ValueOrDie()                                             \

#define COPY_OR_RETURN_WITH_MESSAGE(lhs, rexpr, ...) \
  COPY_OR_RETURN_WITH_MESSAGE_IMPL( \
      STATUS_MACROS_CONCAT_NAME(_status_or_value, __COUNTER__), lhs, rexpr, ##__VA_ARGS__)

// Similar to `CONSUME_OR_RETURN`, but
// calls `ValueOrDie` instead of `ConsumeValueOrDie`
#define COPY_OR_RETURN(lhs, rexpr) \
  COPY_OR_RETURN_WITH_MESSAGE( \
      STATUS_MACROS_CONCAT_NAME(_status_or_value, __COUNTER__), lhs, rexpr, std::string{""})

// If condition is false, this macro returns, from the current function, a
// ::basic::Status with the ::basic::error::INTERNAL code.
// For example:
//   RET_CHECK(condition) << message;
// is equivalent to:
//   if(!condition) {
//     RETURN_ERROR() << message;
//   }
// Note that the RET_CHECK macro includes some more information in the error
// and logs a stack trace.
//
// Intended to be used as a replacement for CHECK where crashes are
// unacceptable. The containing function must return a ::basic::Status.
#define RET_CHECK(condition)                                             \
  while (UNLIKELY(!(condition)))                               \
    while (::basic::status_macros::helper_log_always_return_true())       \
  return ::basic::status_macros::MakeErrorStream(FROM_HERE,      \
                                                ::basic::error::INTERNAL) \
      .with_log_stack_trace()                                            \
      .add_ret_check_failure(#condition)

///////
// Implementation code for RET_CHECK_EQ, RET_CHECK_NE, etc.

// Wraps a string*, allowing it to be written to an ostream and deleted.
// This is needed because the RET_CHECK_OP macro needs to free the memory
// after the error message is logged.
namespace internal {
struct ErrorDeleteStringHelper {
  explicit ErrorDeleteStringHelper(std::string* str_in) : str(str_in) { }
  ~ErrorDeleteStringHelper() { delete str; }
  std::string* str;

  // ErrorDeleteStringHelper is neither copyable nor movable.
  ErrorDeleteStringHelper(const ErrorDeleteStringHelper&) = delete;
  ErrorDeleteStringHelper& operator=(const ErrorDeleteStringHelper&) = delete;
};

}  // namespace internal

// Helper macros for binary operators.
// Don't use these macro directly in your code, use RET_CHECK_EQ et al below.

// The definition of RET_CHECK_OP is modeled after that of CHECK_OP_LOG in
// logging.h.

template<class t1, class t2>
std::string* MakeRetCheckOpString(
    const t1& v1, const t2& v2, const char* names) {
  std::stringstream ss;
  ss << names << " (" << v1 << " vs. " << v2 << ")";
  return new std::string(ss.str());
}
#define DEFINE_RET_CHECK_OP_IMPL(name, op)                             \
  template <class t1, class t2>                                        \
  inline std::string* RetCheck##name##Impl(const t1& v1, const t2& v2, \
                                           const char* names) {        \
    if (LIKELY(v1 op v2)) {                                 \
      return NULL;                                                     \
    } else {                                                           \
      LOG(ERROR) << "Return Error: "                                   \
                 << " at " << __FILE__ << ":" << __LINE__;             \
      return MakeRetCheckOpString(v1, v2, names);                      \
    }                                                                  \
  }                                                                    \
  inline std::string* RetCheck##name##Impl(int v1, int v2,             \
                                           const char* names) {        \
    return RetCheck##name##Impl<int, int>(v1, v2, names);              \
  }
DEFINE_RET_CHECK_OP_IMPL(_EQ, ==)
DEFINE_RET_CHECK_OP_IMPL(_NE, !=)
DEFINE_RET_CHECK_OP_IMPL(_LE, <=)
DEFINE_RET_CHECK_OP_IMPL(_LT, < )
DEFINE_RET_CHECK_OP_IMPL(_GE, >=)
DEFINE_RET_CHECK_OP_IMPL(_GT, > )
#undef DEFINE_RET_CHECK_OP_IMPL

#if defined(STATIC_ANALYSIS)
// Only for static analysis tool to know that it is equivalent to comparison.
#define RET_CHECK_OP(name, op, val1, val2) RET_CHECK((val1) op (val2))
#elif !defined(NDEBUG)
// In debug mode, avoid constructing CheckOpStrings if possible,
// to reduce the overhead of RET_CHECK statements.
#define RET_CHECK_OP(name, op, val1, val2) \
  while (std::string* _result = \
         ::basic::status_macros::RetCheck##name##Impl(      \
              google::GetReferenceableValue(val1),         \
              google::GetReferenceableValue(val2),         \
              #val1 " " #op " " #val2))                               \
    return ::basic::status_macros::MakeErrorStream(FROM_HERE, \
                                                  ::basic::error::INTERNAL) \
        .with_log_stack_trace() \
        .add_ret_check_failure( \
             ::basic::status_macros::internal::ErrorDeleteStringHelper( \
                 _result).str->c_str())
#else
// In optimized mode, use CheckOpString to hint to compiler that
// the while condition is unlikely.
#define RET_CHECK_OP(name, op, val1, val2) \
  while (CheckOpString _result = \
         ::basic::status_macros::RetCheck##name##Impl(      \
              google::GetReferenceableValue(val1),         \
              google::GetReferenceableValue(val2),         \
              #val1 " " #op " " #val2))                               \
    return ::basic::status_macros::MakeErrorStream(FROM_HERE, \
                                                  ::basic::error::INTERNAL) \
        .with_log_stack_trace() \
        .add_ret_check_failure( \
             ::basic::status_macros::internal::ErrorDeleteStringHelper( \
                 _result.str_).str->c_str())
#endif  // STATIC_ANALYSIS, !NDEBUG

// End of implementation code for RET_CHECK_EQ, RET_CHECK_NE, etc.
///////////////

// If the two values fail the comparison, this macro returns, from the current
// function, a ::basic::Status with code ::basic::error::INTERNAL.
// For example,
//   RET_CHECK_EQ(val1, val2) << message;
// is equivalent to
//   if(!(val1 == val2)) {
//     RETURN_ERROR() << message;
//   }
// Note that the RET_CHECK macro includes some more information in the error
// and logs a stack trace.
//
// Intended to be used as a replacement for CHECK_* where crashes are
// unacceptable. The containing function must return a ::basic::Status.
#define RET_CHECK_EQ(val1, val2) RET_CHECK_OP(_EQ, ==, val1, val2)
#define RET_CHECK_NE(val1, val2) RET_CHECK_OP(_NE, !=, val1, val2)
#define RET_CHECK_LE(val1, val2) RET_CHECK_OP(_LE, <=, val1, val2)
#define RET_CHECK_LT(val1, val2) RET_CHECK_OP(_LT, < , val1, val2)
#define RET_CHECK_GE(val1, val2) RET_CHECK_OP(_GE, >=, val1, val2)
#define RET_CHECK_GT(val1, val2) RET_CHECK_OP(_GT, > , val1, val2)

// Unconditionally returns an error.  Use in place of RET_CHECK(false).
// Example:
//   if (a) {
//     ...
//   } else if (b) {
//     ...
//   } else {
//     RET_CHECK_FAIL() << "Failed to satisfy a or b";
//   }
#define RET_CHECK_FAIL() \
  LOG(ERROR) << "Return Error: " << " at "                          \
             << __FILE__ << ":" << __LINE__;                        \
  return ::basic::status_macros::MakeErrorStream(FROM_HERE,         \
                                                ::basic::error::INTERNAL) \
      .with_log_stack_trace() \
      .add_ret_check_fail_failure()

/// \note use only in tests (gtest)
/// EXPECT_* yields a nonfatal failure, allowing the function to continue running
#ifndef EXPECT_OK
#define EXPECT_OK(x) \
  EXPECT_TRUE(x.ok()) << x
#endif // EXPECT_OK

#ifndef EXPECT_NOT_OK
#define EXPECT_NOT_OK(x) \
  ASSERT_FALSE(x.ok()) << x
#endif // EXPECT_NOT_OK

/// \note use only in tests (gtest)
/// ASSERT_* yields a fatal failure and returns from the current function
#ifndef ASSERT_OK
#define ASSERT_OK(x) \
  ASSERT_TRUE(x.ok()) << x
#endif // ASSERT_OK

#ifndef ASSERT_NOT_OK
#define ASSERT_NOT_OK(x) \
  ASSERT_FALSE(x.ok()) << x
#endif // ASSERT_NOT_OK

/// \note use only in tests (gtest)
/// EXPECT_* yields a nonfatal failure, allowing the function to continue running
//
// USAGE
//
// using namespace basic::error;
// EXPECT_ERROR_CODE(OUT_OF_RANGE, tryAddMoney(a, b));
//
#ifndef EXPECT_ERROR_CODE
#define EXPECT_ERROR_CODE(code, x) \
  EXPECT_EQ(code, x.error_code())
#endif // EXPECT_ERROR_CODE

/// \note use only in tests (gtest)
/// ASSERT_* yields a fatal failure and returns from the current function
//
// USAGE
//
// using namespace basic::error;
// ASSERT_ERROR_CODE(OUT_OF_RANGE, tryAddMoney(a, b));
//
#ifndef ASSERT_ERROR_CODE
#define ASSERT_ERROR_CODE(code, x) \
  ASSERT_EQ(code, x.error_code())
#endif // ASSERT_ERROR_CODE

// See also CONSUME_OR_RETURN
//
/// \note performs extra checks only in debug builds
//
// BEFORE
//
// basic::StatusOr<int64_t> status = varint.ToInt64();
// ASSERT_OK(status);
// uint64_t converted = RVALUE_CAST(status.ConsumeValueOrDie());
//
// AFTER
//
// int64_t converted = CONSUME_STATUSOR(varint.ToInt64());
//
#define CONSUME_STATUSOR(expr) \
  [&](){ \
    auto statusor = (expr); \
    DCHECK_OK(statusor) << #expr << " failed with " << statusor; \
    return RVALUE_CAST(statusor.ConsumeValueOrDie()); \
  }()

// See also CONSUME_OR_RETURN
//
/// \note performs extra checks only in debug builds
//
// BEFORE
//
// basic::StatusOr<int64_t> status = varint.ToInt64();
// ASSERT_OK(status);
// uint64_t converted = status.ValueOrDie();
//
// AFTER
//
// int64_t converted = EXTRACT_STATUSOR(varint.ToInt64());
//
#define EXTRACT_STATUSOR(expr) \
  [&](){ \
    auto statusor = (expr); \
    DCHECK_OK(statusor) << #expr << " failed with " << statusor; \
    return statusor.ValueOrDie(); \
  }()

// Creates error status with formatted error message
// (ok status can not have message so not need for substitute)
//
// USAGE
//
// basic::Status status = STATUS_SUBSTITUTE(
//   "Catalog manager of $0 is in shell mode, not the leader.", uuid);
//
#define STATUS_SUBSTITUTE(format_string, ...)                                  \
  ([&]() -> ::basic::status_macros::MakeErrorStream {                          \
    return ::basic::status_macros::MakeErrorStream(FROM_HERE)                  \
      << basic::Substitute(format_string, __VA_ARGS__);                         \
  })().without_logging()

// BEFORE:
//
// RETURN_ERROR()
//     << basic::Substitute("Decoded VarInt size as $1 but only $2 bytes provided"
//                         , decoded_varint_size, bytes_provided);
//
// AFTER:
//
// RETURN_STATUS_SUBSTITUTE("Decoded VarInt size as $1 but only $2 bytes provided"
//                          , decoded_varint_size, bytes_provided);
//
#define RETURN_STATUS_SUBSTITUTE(format_string, ...)                           \
  return STATUS_SUBSTITUTE(format_string, __VA_ARGS__)

// Similar to `STATUS_SUBSTITUTE`, but with custom error code
//
#define STATUS_EC_SUBSTITUTE(code, format_string, ...)                         \
  ([&]() -> ::basic::status_macros::MakeErrorStream {                          \
    return ::basic::status_macros::MakeErrorStream(FROM_HERE, code)            \
      << basic::Substitute(format_string, __VA_ARGS__);                         \
  })().without_logging()

// BEFORE:
//
// RETURN_ERROR(ERR_DEPENDENCY_NOT_FOUND)
//     << basic::Substitute("Decoded VarInt size as $1 but only $2 bytes provided"
//                         , decoded_varint_size, bytes_provided);
//
// AFTER:
//
// RETURN_STATUS_EC_SUBSTITUTE(ERR_DEPENDENCY_NOT_FOUND,
//                             "Decoded VarInt size as $1 but only $2 bytes provided"
//                             , decoded_varint_size, bytes_provided);
//
#define RETURN_STATUS_EC_SUBSTITUTE(code, format_string, ...)                           \
  return STATUS_EC_SUBSTITUTE(code, format_string, __VA_ARGS__)

}  // namespace status_macros
}  // namespace basic
