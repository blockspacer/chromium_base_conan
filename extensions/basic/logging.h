#pragma once

#include <stddef.h>

#include <cassert>
#include <cstdint>
#include <sstream>
#include <string>

#include "base/dcheck_is_on.h"
#include "base/check.h"
#include "base/check_op.h"
#include "base/base_export.h"
#include "base/macros.h"
#include "base/compiler_specific.h"

/// \todo support custom log sinks
/// like in https://source.chromium.org/chromium/chromium/src/+/master:third_party/webrtc/rtc_base/logging.h
///
/// TEST_F(StreamingLogTest, log_at) {
///   ::logging::StringSink log_str;
///   ::logging::LogSink* old_sink = ::logging::SetLogSink(&log_str);
///   LOG_AT(FATAL, "specified_file.cc", 12345) << "file/line is specified";
///   // the file:line part should be using the argument given by us.
///   ASSERT_NE(std::string::npos, log_str.find("specified_file.cc:12345"));
///   // restore the old sink.
///   ::logging::SetLogSink(old_sink);
/// }

// USAGE
//
// using ::logging::noEndl;
// using ::logging::noFormat;
// using ::logging::doNothing;
// using ::logging::info;
//
// std::vector<std::string> items{"item1", "item2", "item3"};
// LOG(INFO) << "Items:" << noEndl;
// for (auto it = items.begin(); it != items.end(); ++it) {
//   LOG(INFO) << ' ' << *it << noFormat << noEndl;
// }
// LOG(INFO) << '\n' << noFormat << noEndl;
//
// int n = 10;
// for(int i = 0; i < n; i++)
// {
//   /// \note There is no std::endl
//   /// \note FATAL may cause coredump
//   // LOG(FATAL) << "Unusual thing happened ..." << "...";
//
//   // DLOG: Print logs only when NDEBUG is not defined.
//   DLOG(INFO) << "Something just took place..." << "...";
//
//   /// \note glog doesn't have NOTICE.
//   /// Generally you should not use NOTICE
//   /// as it is intended for important logs.
//   LOG_IF(NOTICE, i > 8) << "This log will only be printed when i > 8";
//   // Prints with errno:
//   // Fail to call function setting errno: File exists (17)
//   PLOG(WARNING) << "Fail to call function setting errno";
//   VLOG(1) << "verbose log tier 1, see --vmodule";
//
//   #include "base/threading/platform_thread.h"
//   base::PlatformThread::Sleep(base::TimeDelta::FromMilliseconds(300));
//
//   LOG_EVERY_N_US(INFO, 800000L) << "High-frequent logs (every 800ms)";
//   LOG_EVERY_SECOND(INFO) << "High-frequent logs (every 1sec)";
//   LOG_EVERY_N_TIMES(ERROR, 3) << "High-frequent logs (every 3 times)";
//   LOG_FIRST_N_TIMES(INFO, 5) << "Logs that prints for at most 5 times";
//   LOG_ONCE(WARNING) << "Logs that only prints once";
//   VLOG2("a/b/c", 3) << "being filtered by a/b/c rather than public/foo/bar";
// }

#define LOG_DCHECK LOGGING_DCHECK
#define LOG_NUM_SEVERITIES LOGGING_NUM_SEVERITIES

#define RAW_CHECK(condition)                               \
  do {                                                     \
    if (!(condition))                                      \
      ::logging::RawLog(::logging::LOG_FATAL,              \
                        "Check failed: " #condition "\n"); \
  } while (0)

#define VLOG_EVERY_N_TIMES(verbose_level, N)                                  \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(VLOG_IF, verbose_level, true, N)
#define VLOG_IF_EVERY_N_TIMES(verbose_level, condition, N)                    \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(VLOG_IF, verbose_level, condition, N)

#define VLOG_FIRST_N_TIMES(verbose_level, N)                                  \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(VLOG_IF, verbose_level, true, N)
#define VLOG_IF_FIRST_N_TIMES(verbose_level, condition, N)                    \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(VLOG_IF, verbose_level, condition, N)

#define VLOG_ONCE(verbose_level) VLOG_FIRST_N_TIMES(verbose_level, 1)
#define VLOG_IF_ONCE(verbose_level, condition) VLOG_IF_FIRST_N_TIMES(verbose_level, condition, 1)

#define VLOG_EVERY_SECOND(verbose_level)                        \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(VLOG_IF, verbose_level, true)
#define VLOG_IF_EVERY_SECOND(verbose_level, condition)                  \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(VLOG_IF, verbose_level, condition)
#define VLOG_EVERY_N_US(verbose_level, periodInMicroseconds)                        \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(VLOG_IF, verbose_level, true, periodInMicroseconds)
#define VLOG_IF_EVERY_N_US(verbose_level, condition, periodInMicroseconds)                  \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(VLOG_IF, verbose_level, condition, periodInMicroseconds)

#define VLOG_EVERY_N_MS(verbose_level, periodInMilliseconds)                             \
  VLOG_EVERY_N_US(verbose_level, ((periodInMilliseconds) * 1000.0) )
#define VLOG_IF_EVERY_M_US(verbose_level, condition, periodInMilliseconds)                       \
  VLOG_IF_EVERY_N_US(verbose_level, condition, ((periodInMilliseconds) * 1000.0) )


// You can assign virtual path to VLOG instead of physical filename.
// [public/foo/bar.cpp]
// VLOG2("a/b/c", 2) << "being filtered by a/b/c rather than public/foo/bar";
#define VLOG2(virtual_path, verbose_level)                              \
    LAZY_STREAM(VLOG_STREAM(verbose_level),                       \
                INTERNAL_VLOG_IS_ON(verbose_level, virtual_path))

#define VLOG2_IF(virtual_path, verbose_level, condition)                \
    LAZY_STREAM(VLOG_STREAM(verbose_level),                       \
                INTERNAL_VLOG_IS_ON(verbose_level, virtual_path) && (condition))

#define DVLOG2(virtual_path, verbose_level)             \
    VLOG2_IF(virtual_path, verbose_level, ENABLE_DLOG)

#define DVLOG2_IF(virtual_path, verbose_level, condition)               \
    VLOG2_IF(virtual_path, verbose_level, ENABLE_DLOG && (condition))

#define VPLOG2(virtual_path, verbose_level)                             \
    LAZY_STREAM(VPLOG_STREAM(verbose_level),                      \
                INTERNAL_VLOG_IS_ON(verbose_level, virtual_path))

#define VPLOG2_IF(virtual_path, verbose_level, condition)               \
    LAZY_STREAM(VPLOG_STREAM(verbose_level),                      \
                INTERNAL_VLOG_IS_ON(verbose_level, virtual_path) && (condition))

#define DVPLOG2(virtual_path, verbose_level)                            \
    VPLOG2_IF(virtual_path, verbose_level, ENABLE_DLOG)

#define DVPLOG2_IF(virtual_path, verbose_level, condition)              \
    VPLOG2_IF(virtual_path, verbose_level, ENABLE_DLOG && (condition))

#define DLOG_EVERY_N_TIMES(severity, N)                               \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(DLOG_IF, severity, true, N)
#define DLOG_IF_EVERY_N_TIMES(severity, condition, N)                 \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(DLOG_IF, severity, condition, N)
#define DLOG_FIRST_N_TIMES(severity, N)                               \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(DLOG_IF, severity, true, N)
#define DLOG_IF_FIRST_N_TIMES(severity, condition, N)                 \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(DLOG_IF, severity, condition, N)
#define DLOG_ONCE(severity) DLOG_FIRST_N_TIMES(severity, 1)
#define DLOG_IF_ONCE(severity, condition) DLOG_IF_FIRST_N_TIMES(severity, condition, 1)
#define DLOG_EVERY_SECOND(severity)                             \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(DLOG_IF, severity, true)
#define DLOG_IF_EVERY_SECOND(severity, condition)                       \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(DLOG_IF, severity, condition)
#define DLOG_EVERY_N_US(severity, periodInMicroseconds)                             \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(DLOG_IF, severity, true, periodInMicroseconds)
#define DLOG_IF_EVERY_N_US(severity, condition, periodInMicroseconds)                       \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(DLOG_IF, severity, condition, periodInMicroseconds)

#define DPLOG_EVERY_N_TIMES(severity, N)                               \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(DPLOG_IF, severity, true, N)
#define DPLOG_IF_EVERY_N_TIMES(severity, condition, N)                 \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(DPLOG_IF, severity, condition, N)
#define DPLOG_FIRST_N_TIMES(severity, N)                               \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(DPLOG_IF, severity, true, N)
#define DPLOG_IF_FIRST_N_TIMES(severity, condition, N)                 \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(DPLOG_IF, severity, condition, N)
#define DPLOG_ONCE(severity) DPLOG_FIRST_N_TIMES(severity, 1)
#define DPLOG_IF_ONCE(severity, condition) DPLOG_IF_FIRST_N_TIMES(severity, condition, 1)
#define DPLOG_EVERY_SECOND(severity)                             \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(DPLOG_IF, severity, true)
#define DPLOG_IF_EVERY_SECOND(severity, condition)                       \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(DPLOG_IF, severity, condition)
#define DPLOG_EVERY_N_US(severity, periodInMicroseconds)                             \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(DPLOG_IF, severity, true, periodInMicroseconds)
#define DPLOG_IF_EVERY_N_US(severity, condition, periodInMicroseconds)                       \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(DPLOG_IF, severity, condition, periodInMicroseconds)

#define DVLOG_EVERY_N_TIMES(verbose_level, N)                               \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(DVLOG_IF, verbose_level, true, N)
#define DVLOG_IF_EVERY_N_TIMES(verbose_level, condition, N)                 \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(DVLOG_IF, verbose_level, condition, N)
#define DVLOG_FIRST_N_TIMES(verbose_level, N)                               \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(DVLOG_IF, verbose_level, true, N)
#define DVLOG_IF_FIRST_N_TIMES(verbose_level, condition, N)                 \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(DVLOG_IF, verbose_level, condition, N)
#define DVLOG_ONCE(verbose_level) DVLOG_FIRST_N_TIMES(verbose_level, 1)
#define DVLOG_IF_ONCE(verbose_level, condition) DVLOG_IF_FIRST_N_TIMES(verbose_level, condition, 1)
#define DVLOG_EVERY_SECOND(verbose_level)                             \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(DVLOG_IF, verbose_level, true)
#define DVLOG_IF_EVERY_SECOND(verbose_level, condition)                       \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(DVLOG_IF, verbose_level, condition)
#define DVLOG_EVERY_N_US(verbose_level, periodInMicroseconds)                             \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(DVLOG_IF, verbose_level, true, periodInMicroseconds)
#define DVLOG_IF_EVERY_N_US(verbose_level, condition, periodInMicroseconds)                       \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(DVLOG_IF, verbose_level, condition, periodInMicroseconds)
#define DVLOG_EVERY_N_MS(verbose_level, periodInMilliseconds)                             \
  DVLOG_EVERY_N_US(verbose_level, ((periodInMilliseconds) * 1000.0) )
#define DVLOG_IF_EVERY_M_US(verbose_level, condition, periodInMilliseconds)                       \
  DVLOG_IF_EVERY_N_US(verbose_level, condition, ((periodInMilliseconds) * 1000.0) )

#define DVPLOG_EVERY_N_TIMES(verbose_level, N)                               \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(DVPLOG_IF, verbose_level, true, N)
#define DVPLOG_IF_EVERY_N_TIMES(verbose_level, condition, N)                 \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(DVPLOG_IF, verbose_level, condition, N)
#define DVPLOG_FIRST_N_TIMES(verbose_level, N)                               \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(DVPLOG_IF, verbose_level, true, N)
#define DVPLOG_IF_FIRST_N_TIMES(verbose_level, condition, N)                 \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(DVPLOG_IF, verbose_level, condition, N)
#define DVPLOG_ONCE(verbose_level) DVPLOG_FIRST_N_TIMES(verbose_level, 1)
#define DVPLOG_IF_ONCE(verbose_level, condition) DVPLOG_IF_FIRST_N_TIMES(verbose_level, condition, 1)
#define DVPLOG_EVERY_SECOND(verbose_level)                             \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(DVPLOG_IF, verbose_level, true)
#define DVPLOG_IF_EVERY_SECOND(verbose_level, condition)                       \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(DVPLOG_IF, verbose_level, condition)
#define DVPLOG_EVERY_N_US(verbose_level, periodInMicroseconds)                             \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(DVPLOG_IF, verbose_level, true, periodInMicroseconds)
#define DVPLOG_IF_EVERY_N_US(verbose_level, condition, periodInMicroseconds)                       \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(DVPLOG_IF, verbose_level, condition, periodInMicroseconds)
#define DVPLOG_EVERY_N_MS(verbose_level, periodInMilliseconds)                             \
  DVPLOG_EVERY_N_US(verbose_level, ((periodInMilliseconds) * 1000.0) )
#define DVPLOG_IF_EVERY_M_US(verbose_level, condition, periodInMilliseconds)                       \
  DVPLOG_IF_EVERY_N_US(verbose_level, condition, ((periodInMilliseconds) * 1000.0) )

// Helper macro included by all *_EVERY_N macros.
#define INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(logifmacro, severity, condition, N)   \
  static ::base::subtle::Atomic32 STR_CONCAT(logeveryn_, __LINE__) = -1; \
  const static int STR_CONCAT(logeveryn_sc_, __LINE__) = (N);       \
  const int STR_CONCAT(logeveryn_c_, __LINE__) =                    \
      ::base::subtle::NoBarrier_AtomicIncrement(&STR_CONCAT(logeveryn_, __LINE__), 1); \
  logifmacro(severity, (condition) && STR_CONCAT(logeveryn_c_, __LINE__) / \
             STR_CONCAT(logeveryn_sc_, __LINE__) * STR_CONCAT(logeveryn_sc_, __LINE__) \
             == STR_CONCAT(logeveryn_c_, __LINE__))

/// \note Do not add `INTERNAL_LOG_IF_ONCE*` beacuse you can use `OneShotEvent` like so:
/// base::OneShotEvent event; if(!event.is_signaled()) { LOG(INFO) << "..."; event.Signal(); }
//
// Helper macro included by all *_FIRST_N macros.
#define INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(logifmacro, severity, condition, N)   \
  static ::base::subtle::Atomic32 STR_CONCAT(logfstn_, __LINE__) = 0; \
  logifmacro(severity, (condition) && STR_CONCAT(logfstn_, __LINE__) < N && \
             ::base::subtle::NoBarrier_AtomicIncrement(&STR_CONCAT(logfstn_, __LINE__), 1) <= N)

// Helper macro included by all *_EVERY_SECOND macros.
#define INTERNAL_LOG_IF_EVERY_N_US_IMPL(logifmacro, severity, condition, periodInMicroseconds) \
  static ::base::subtle::Atomic64 STR_CONCAT(logeverys_, __LINE__) = 0; \
  const int64_t STR_CONCAT(logeverys_ts_, __LINE__) = (base::Time::Now() - base::Time::UnixEpoch()).InMicroseconds(); \
  const int64_t STR_CONCAT(logeverys_seen_, __LINE__) = STR_CONCAT(logeverys_, __LINE__); \
  logifmacro(severity, (condition) && STR_CONCAT(logeverys_ts_, __LINE__) >= \
             (STR_CONCAT(logeverys_seen_, __LINE__) + periodInMicroseconds) &&  \
             ::base::subtle::NoBarrier_CompareAndSwap(                \
                 &STR_CONCAT(logeverys_, __LINE__),                 \
                 STR_CONCAT(logeverys_seen_, __LINE__),             \
                 STR_CONCAT(logeverys_ts_, __LINE__))               \
             == STR_CONCAT(logeverys_seen_, __LINE__))

// 1000000 microseconds equals 1 second
#define INTERNAL_LOG_IF_EVERY_SECOND_IMPL(logifmacro, severity, condition) \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(logifmacro, severity, condition, 1000000L)

// ===============================================================

// Print a log for at most once. (not present in glog)
// Almost zero overhead when the log was printed.
#ifndef LOG_ONCE
# define LOG_ONCE(severity) LOG_FIRST_N_TIMES(severity, 1)
# define LOG_IF_ONCE(severity, condition) LOG_IF_FIRST_N_TIMES(severity, condition, 1)
#endif

// Print a log after every N calls. First call always prints.
// Each call to this macro has a cost of relaxed atomic increment.
// The corresponding macro in glog is not thread-safe while this is.
#ifndef LOG_EVERY_N_TIMES
# define LOG_EVERY_N_TIMES(severity, N)                                \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(LOG_IF, severity, true, N)
# define LOG_IF_EVERY_N_TIMES(severity, condition, N)                  \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(LOG_IF, severity, condition, N)
#endif

// Print logs for first N calls.
// Almost zero overhead when the log was printed for N times
// The corresponding macro in glog is not thread-safe while this is.
#ifndef LOG_FIRST_N_TIMES
# define LOG_FIRST_N_TIMES(severity, N)                                \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(LOG_IF, severity, true, N)
# define LOG_IF_FIRST_N_TIMES(severity, condition, N)                  \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(LOG_IF, severity, condition, N)
#endif

// Print a log every second. (not present in glog). First call always prints.
// Each call to this macro has a cost of calling gettimeofday.
#ifndef LOG_EVERY_SECOND
# define LOG_EVERY_SECOND(severity)                                \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(LOG_IF, severity, true)
# define LOG_IF_EVERY_SECOND(severity, condition)                \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(LOG_IF, severity, condition)
#endif

#ifndef LOG_EVERY_N_US
# define LOG_EVERY_N_US(severity, periodInMicroseconds)                                \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(LOG_IF, severity, true, periodInMicroseconds)
# define LOG_IF_EVERY_N_US(severity, condition, periodInMicroseconds)                \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(LOG_IF, severity, condition, periodInMicroseconds)
#endif

// USAGE
//
// #include "base/command_line.h"
// #include "base/strings/string_number_conversions.h"
//
// // ... in my_switches.hpp ...
//
// namespace switches {
//
// extern const char kMyLogFreq[];
//
// }  // namespace switches
//
// // ... in my_switches.cc ...
//
// namespace switches {
//
// // Total number of shards. Must be the same for all shards.
// const char switches::kMyLogFreqMs[] =
//     "my-log-freq-ms";
//
// }  // namespace switches
//
// // ... in my_code.cc ...
//
// const CommandLine* command_line = base::CommandLine::ForCurrentProcess();
//
// int my_log_freq_ms = 0;
//
// if (command_line->HasSwitch(switches::kMyLogFreqMs)) {
//     if (!base::StringToInt(
//             command_line->GetSwitchValueASCII(
//                 switches::kMyLogFreqMs),
//             &my_log_freq_ms)) {
//       LOG(ERROR)
//          << "Invalid value for " << switches::kMyLogFreqMs
//          << " Fallback to " << my_log_freq_ms;
//       return false;
//     }
// }
//
// LOG_EVERY_N_MS(INFO, my_log_freq_ms) << "My logs";
//
#ifndef LOG_EVERY_N_MS
# define LOG_EVERY_N_MS(severity, periodInMilliseconds)                                \
  LOG_EVERY_N_US(severity, ((periodInMilliseconds) * 1000.0))
# define LOG_IF_EVERY_N_MS(severity, condition, periodInMilliseconds)                \
  LOG_IF_EVERY_N_US(severity, condition, ((periodInMilliseconds) * 1000.0))
#endif

#ifndef PLOG_EVERY_N_TIMES
# define PLOG_EVERY_N_TIMES(severity, N)                               \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(PLOG_IF, severity, true, N)
# define PLOG_IF_EVERY_N_TIMES(severity, condition, N)                 \
  INTERNAL_LOG_IF_EVERY_N_TIMES_IMPL(PLOG_IF, severity, condition, N)
#endif

#ifndef PLOG_FIRST_N_TIMES
# define PLOG_FIRST_N_TIMES(severity, N)                               \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(PLOG_IF, severity, true, N)
# define PLOG_IF_FIRST_N_TIMES(severity, condition, N)                 \
  INTERNAL_LOG_IF_FIRST_N_TIMES_IMPL(PLOG_IF, severity, condition, N)
#endif

#ifndef PLOG_ONCE
# define PLOG_ONCE(severity) PLOG_FIRST_N_TIMES(severity, 1)
# define PLOG_IF_ONCE(severity, condition) PLOG_IF_FIRST_N_TIMES(severity, condition, 1)
#endif

#ifndef PLOG_EVERY_SECOND
# define PLOG_EVERY_SECOND(severity)                             \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(PLOG_IF, severity, true)
# define PLOG_IF_EVERY_SECOND(severity, condition)                       \
  INTERNAL_LOG_IF_EVERY_SECOND_IMPL(PLOG_IF, severity, condition)
#endif

#ifndef PLOG_EVERY_N_US
# define PLOG_EVERY_N_US(severity, periodInMicroseconds)                             \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(PLOG_IF, severity, true, periodInMicroseconds)
# define PLOG_IF_EVERY_N_US(severity, condition, periodInMicroseconds)                       \
  INTERNAL_LOG_IF_EVERY_N_US_IMPL(PLOG_IF, severity, condition, periodInMicroseconds)
#endif

#ifndef PLOG_EVERY_N_MS
# define PLOG_EVERY_N_MS(severity, periodInMilliseconds)                             \
  PLOG_EVERY_N_US(severity, ((periodInMilliseconds) * 1000.0) )
# define PLOG_IF_EVERY_N_MS(severity, condition, periodInMilliseconds )                       \
  PLOG_IF_EVERY_N_US(severity, condition, ((periodInMilliseconds) * 1000.0) )
#endif

// DEBUG_MODE is for uses like
//   if (DEBUG_MODE) foo.CheckThatFoo();
// instead of
//   #ifndef NDEBUG
//     foo.CheckThatFoo();
//   #endif
//
// We tie its state to ENABLE_DLOG.
enum { DEBUG_MODE = DCHECK_IS_ON() };

namespace internal {
// Helper for `CHECK_VALID_PTR_OR`.
/// \note checks that object is alive if you use memory tool like ASAN
template <typename T>
// do not add `MUST_USE_RESULT` here
// because we also want to use it outside of constructor (similar to `CHECK`)
T sanitizedCheckNotNull(
  const char* file
  , int line
  , const char* exprtext
  , T&& t) NO_EXCEPTION
{
  UNREFERENCED_PARAMETER(file);
  UNREFERENCED_PARAMETER(line);
  CHECK(t != nullptr) << exprtext;
  // Works with `-fsanitize=address,undefined`
#if defined(MEMORY_TOOL_REPLACES_ALLOCATOR)
  if (t)
    reinterpret_cast<const volatile uint8_t*>(t)[0];
#endif
  return std::forward<T>(t);
}
} // namespace internal


// MOTIVATION
//
// Unlike `CHECK(x != nullptr) << "..."` can be used in constructor.
//
/// \note Also checks that object is alive if you use memory tool like ASAN.
//
// EXAMPLE
//
// DiagService::DiagService(OperationMode mode, SwitchInterface* switch_interface,
//                          AuthPolicyChecker* auth_policy_checker,
//                          ErrorBuffer* error_buffer)
//     : mode_(mode),
//       switch_interface_(CHECK_VALID_PTR_OR(switch_interface)),
//       auth_policy_checker_(CHECK_VALID_PTR_OR(auth_policy_checker)),
//       error_buffer_(CHECK_VALID_PTR_OR(error_buffer)) {}
//
#ifndef CHECK_VALID_PTR_OR
#define CHECK_VALID_PTR_OR(val) \
  ::internal::sanitizedCheckNotNull(__FILE__, __LINE__, #val, (val))
#endif

#ifndef CHECK_VALID_PTR
#define CHECK_VALID_PTR(val) \
  ignore_result(::internal::sanitizedCheckNotNull(__FILE__, __LINE__, #val, (val)))
#endif


// In debug builds checks that pointer is valid
// or returns pointer without any checks (in other build types).
//
/// \note Also checks that object is alive if you use memory tool like ASAN.
//
// BAD:
//
// DCHECK_VALID_PTR_OR(switch_interface);
// switch_interface->doSmth();
//
// GOOD:
//
// DCHECK_VALID_PTR_OR(switch_interface)->doSmth();
//
#ifndef DCHECK_VALID_PTR_OR
#if DCHECK_IS_ON()
#define DCHECK_VALID_PTR_OR(val) \
  ::internal::sanitizedCheckNotNull(__FILE__, __LINE__, #val, (val))
#else // DCHECK_IS_ON()
#define DCHECK_VALID_PTR_OR(val) \
  val
#endif // DCHECK_IS_ON()
#endif

#ifndef DCHECK_VALID_PTR
#if DCHECK_IS_ON()
#define DCHECK_VALID_PTR(val) \
  ignore_result(::internal::sanitizedCheckNotNull(__FILE__, __LINE__, #val, (val)))
#else // DCHECK_IS_ON()
#define DCHECK_VALID_PTR(val) ((void)(0))
#endif // DCHECK_IS_ON()
#endif

// Same as `CHECK_VALID_PTR(ptr)`, but documents that pointer is not owned.
// Use it is `MyClass` destructor that has unowned objects
// that must outlive `MyClass`.
#ifndef CHECK_UNOWNED_PTR
#define CHECK_UNOWNED_PTR(...) CHECK_VALID_PTR(__VA_ARGS__)
#endif

// Same as `DCHECK_VALID_PTR(ptr)`, but documents that pointer is not owned.
// Use it is `MyClass` destructor that has unowned objects
// that must outlive `MyClass`.
#ifndef DCHECK_UNOWNED_PTR
#define DCHECK_UNOWNED_PTR(...) DCHECK_VALID_PTR(__VA_ARGS__)
#endif

// Same as `DCHECK_VALID_PTR(&ref)`, but documents that reference is not owned.
// Use it is `MyClass` destructor that has unowned objects
// that must outlive `MyClass`.
#ifndef CHECK_UNOWNED_REF
#define CHECK_UNOWNED_REF(x) CHECK_VALID_PTR(&x)
#endif

// Same as `DCHECK_VALID_PTR(&ref)`, but documents that reference is not owned.
// Use it is `MyClass` destructor that has unowned objects
// that must outlive `MyClass`.
#ifndef DCHECK_UNOWNED_REF
#define DCHECK_UNOWNED_REF(x) DCHECK_VALID_PTR(&x)
#endif

#define CHECK_BETWEEN(val, lower_bound, upper_bound) \
  do { CHECK_GE(val, lower_bound); CHECK_LE(val, upper_bound); } while(false)

#ifndef NDEBUG
#define DCHECK_BETWEEN(val, lower_bound, upper_bound) CHECK_BETWEEN(val, lower_bound, upper_bound)
#else
#define DCHECK_BETWEEN(val, lower_bound, upper_bound) \
  MSVC_PUSH_DISABLE_WARNING(4127) \
  while (false) \
    MSVC_POP_WARNING() CHECK_BETWEEN(val, lower_bound, upper_bound)
#endif

// Helper for CHECK_STRxx(s1,s2) macros.
#define CHECK_STROP(s1, s2, sense)                                         \
  if (LIKELY((strcmp(s1, s2) == 0) == sense))                              \
    ;                                                                      \
  else                                                                     \
    LOG(FATAL) << "Check failed: "                                         \
               << "\"" << s1 << "\""                                       \
               << (sense ? " == " : " != ") << "\"" << s2 << "\""

// Check for string (const char*) equality between s1 and s2, LOG(FATAL) if not.
#define CHECK_STREQ(s1, s2) CHECK_STROP(s1, s2, true)
#define CHECK_STRNE(s1, s2) CHECK_STROP(s1, s2, false)

#ifndef NDEBUG
#define DCHECK_STREQ(s1, s2) CHECK_STREQ(s1, s2)
#define DCHECK_STRNE(s1, s2) CHECK_STRNE(s1, s2)
#else
#define DCHECK_STREQ(s1, s2)
#define DCHECK_STRNE(s1, s2)
#endif

#define DCHECK_AT(assertion, file, line)                            \
  LAZY_STREAM(logging::LogMessage(file, line, #assertion).stream(), \
              DCHECK_IS_ON() ? !(assertion) : false)

// Users must test "#if ENABLE_SECURITY_ASSERT", which helps ensure that code
// testing this macro has included this header.
#if defined(ADDRESS_SANITIZER) || DCHECK_IS_ON()
#define ENABLE_SECURITY_ASSERT 1
#else
#define ENABLE_SECURITY_ASSERT 0
#endif

// SECURITY_DCHECK and SECURITY_CHECK
// Use in places where failure of the assertion indicates a possible security
// vulnerability. Classes of these vulnerabilities include bad casts, out of
// bounds accesses, use-after-frees, etc. Please be sure to file bugs for these
// failures using the security template:
//    https://bugs.chromium.org/p/chromium/issues/entry?template=Security%20Bug
#if ENABLE_SECURITY_ASSERT
#define SECURITY_DCHECK(condition) \
  LOG_IF(DCHECK, !(condition)) << "Security DCHECK failed: " #condition ". "
// A SECURITY_CHECK failure is actually not vulnerable.
#define SECURITY_CHECK(condition) \
  LOG_IF(FATAL, !(condition)) << "Security CHECK failed: " #condition ". "
#else
#define SECURITY_DCHECK(condition) ((void)0)
#define SECURITY_CHECK(condition) CHECK(condition)
#endif
