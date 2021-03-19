// Copyright 2018 Google LLC
// Copyright 2018-present Open Networking Foundation
// SPDX-License-Identifier: Apache-2.0


#include "basic/status/status_macros.h" // IWYU pragma: associated
#include <basic/logging.h>

#include <algorithm>

#include <base/compiler_specific.h>
#include <base/logging.h>
#include <base/strings/strcat.h>
#include <base/strings/utf_string_conversions.h>
#include <base/debug/stack_trace.h>
#include <base/feature_list.h>

// If enabled `Status` will print stack trace on error by default.
// Can be changed using `.without_log_stack_trace()`.
constexpr char kFeaturePrintStatusStackTraceName[]
  = "print_status_macro_stack_trace";

// --enable-features=print_status_macro_stack_trace,...
const base::Feature kFeaturePrintStatusStackTrace {
  kFeaturePrintStatusStackTraceName, base::FEATURE_DISABLED_BY_DEFAULT
};

// If enabled, than status macros will print additional error into log.
constexpr char kFeaturePrintStatusMacroErrorName[]
  = "print_status_macro_error";

// --enable-features=print_status_macro_error,...
const base::Feature kFeaturePrintStatusMacroError {
  kFeaturePrintStatusMacroErrorName, base::FEATURE_DISABLED_BY_DEFAULT
};

namespace basic {
namespace status_macros {

using ::logging::LogMessage;
using ::logging::LogSeverity;
using ::logging::LOG_NUM_SEVERITIES;
using ::logging::LOG_ERROR;
using ::logging::LOG_FATAL;
using ::logging::LOG_INFO;
using ::logging::LOG_WARNING;

bool IsMacroErrorLoggedByDefault()
{
  return base::FeatureList::IsEnabled(kFeaturePrintStatusMacroError);
}

static ::basic::Status MakeStatus(const ::base::Location location, const ::basic::ErrorSpace* error_space, int code,
                                 const std::string& message) {
  return ::basic::Status(location, error_space, code, message);
}

// Log the error at the given severity, optionally with a stack trace.
// If log_severity is NUM_SEVERITIES, nothing is logged.
void LogError(const ::basic::Status& status
  , const ::base::Location location
  , LogSeverity log_severity
  , bool should_log_stack_trace)
{
  if (LIKELY(log_severity != ::logging::LOG_NUM_SEVERITIES)) {
    LogMessage log_message(location.file_name(), location.line_number(), log_severity);
    log_message.stream() << status;
    if(UNLIKELY(should_log_stack_trace))
    {
      ::base::debug::StackTrace trace;
      log_message.stream() << "\nStackTrace:\n"<< trace;
    }
    // Logging actually happens in LogMessage destructor.
  }
}

// Make a ::basic::Status with a code and error message, and also send
// it to LOG(<log_severity>) using the given filename and line (unless
// should_log is false, or log_severity is NUM_SEVERITIES).  If
// should_log_stack_trace is true, the stack trace is included in the log
// message (ignored if should_log is false).
static ::basic::Status MakeError(const ::base::Location location,
                                const ::basic::ErrorSpace* error_space, int code,
                                const std::string& message,
                                bool should_log, LogSeverity log_severity,
                                bool should_log_stack_trace) {
  if (UNLIKELY(code == ::basic::error::OK)) {
    LOG(DFATAL) << "Cannot create error with status OK";
    error_space = ::basic::Status::canonical_space();
    code = ::basic::error::UNKNOWN;
  }
  const ::basic::Status status = MakeStatus(location, error_space, code, message);
  if (UNLIKELY(should_log)) {
    LogError(status, location, log_severity, should_log_stack_trace);
  }
  return status;
}

/// \todo unused
// Returns appropriate log severity based on suppression level, or
// NUM_SEVERITIES to indicate that logging should be disabled.
static LogSeverity GetSuppressedSeverity(
    LogSeverity severity, int suppressed_level) {
  if (suppressed_level == -1) {
    return ::logging::LOG_WARNING;
  } else if (suppressed_level >= 0) {
    return VLOG_IS_ON(suppressed_level) ? ::logging::LOG_INFO : ::logging::LOG_NUM_SEVERITIES;
  } else {
    return severity;
  }
}

/// \todo unused
void LogErrorWithSuppression(const ::basic::Status& status
  , const ::base::Location location
  , int log_level)
{
  const LogSeverity severity = GetSuppressedSeverity(::logging::LOG_ERROR, log_level);
  LogError(status, location, severity,
           false /* should_log_stack_trace */);
}

// This method is written out-of-line rather than in the header to avoid
// generating a lot of inline code for error cases in all callers.
void MakeErrorStream::CheckNotDone() const {
  impl_->CheckNotDone();
}

MakeErrorStream::Impl::Impl(
    const ::base::Location& location, const ::basic::ErrorSpace* error_space, int code,
    MakeErrorStream* error_stream, bool is_logged_by_default)
    : location_(location), error_space_(error_space), code_(code),
      is_done_(false),
      should_log_(is_logged_by_default),
      log_severity_(::logging::LOG_ERROR),
      should_log_stack_trace_(base::FeatureList::IsEnabled(kFeaturePrintStatusStackTrace)) {}

MakeErrorStream::Impl::Impl(const ::basic::Status& status
  , const ::base::Location& location
  , MakeErrorStream* error_stream)
    : location_(location),
      // Make sure we show some error, even if the call is incorrect.
      error_space_(!status.ok() ? status.error_space()
                                : ::basic::Status::canonical_space()),
      code_(!status.ok() ? status.error_code() : ::basic::error::UNKNOWN),
      prior_message_(status.error_message()),
      is_done_(false),
      // Error code type is not visible here, so we can't call
      // IsLoggedByDefault.
      should_log_(IsMacroErrorLoggedByDefault()),
      log_severity_(::logging::LOG_ERROR),
      should_log_stack_trace_(base::FeatureList::IsEnabled(kFeaturePrintStatusStackTrace)) {
  DCHECK(!status.ok()) << "Attempted to append error text to status OK";
}

MakeErrorStream::Impl::~Impl() {
  // Note: error messages refer to the public MakeErrorStream class.

  LOG_IF(DFATAL, !is_done_)
      << "MakeErrorStream destructed without getting Status: "
      << location_.ToString() << " " << stream_.str();
}

::basic::Status MakeErrorStream::Impl::GetStatus() {
  // Note: error messages refer to the public MakeErrorStream class.

  // Getting a ::basic::Status object out more than once is not harmful, but
  // it doesn't match the expected pattern, where the stream is constructed
  // as a temporary, loaded with a message, and then casted to Status.
  LOG_IF(DFATAL, is_done_)
      << "MakeErrorStream got Status more than once: "
      << location_.ToString() << " " << stream_.str();

  is_done_ = true;

  const std::string& stream_str = stream_.str();
  std::string str = ::base::StrCat({prior_message_, stream_str});
  if (UNLIKELY(str.empty())) {
    return MakeError(
        location_, error_space_, code_,
        ::base::StrCat({str, "Error without message at ", location_.ToString()}),
        IsMacroErrorLoggedByDefault() /* should_log */, ::logging::LOG_ERROR /* log_severity */,
        should_log_stack_trace_);
  } else {
    const LogSeverity actual_severity = ::logging::LOG_ERROR;
    return MakeError(location_, error_space_, code_, str,
                     should_log_, actual_severity, should_log_stack_trace_);
  }
}

void MakeErrorStream::Impl::CheckNotDone() const {
  LOG_IF(DFATAL, is_done_)
      << "MakeErrorStream shift called after getting Status: "
      << location_.ToString() << " " << stream_.str();
}

}  // namespace status_macros
}  // namespace basic
