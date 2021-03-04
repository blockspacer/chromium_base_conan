﻿// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_LOGGING_H_
#define BASE_LOGGING_H_

#include <stddef.h>

#include <chrono>

#include <cassert>
#include <cstring>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "base/dcheck_is_on.h"
#include "base/base_export.h"
#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/debug/debugger.h"
#include "base/macros.h"
#include "base/scoped_clear_last_error.h"
#include "base/strings/string_piece_forward.h"
#include "base/template_util.h"
#include "base/basictypes.h"
#include "build/build_config.h"
#include "base/check.h"
#include "base/check_op.h"
#include "base/notreached.h"
#include "base/immediate_crash.h"

#if defined(OS_EMSCRIPTEN)
#include <emscripten/emscripten.h>
#endif

#if defined(STARBOARD)
#include "starboard/common/log.h"
#include "starboard/system.h"
#include "starboard/types.h"
#endif

//
// Optional message capabilities
// -----------------------------
// Assertion failed messages and fatal errors are displayed in a dialog box
// before the application exits. However, running this UI creates a message
// loop, which causes application messages to be processed and potentially
// dispatched to existing application windows. Since the application is in a
// bad state when this assertion dialog is displayed, these messages may not
// get processed and hang the dialog, or the application might go crazy.
//
// Therefore, it can be beneficial to display the error dialog in a separate
// process from the main application. When the logging system needs to display
// a fatal error dialog box, it will look for a program called
// "DebugMessage.exe" in the same directory as the application executable. It
// will run this application with the message as the command line, and will
// not include the name of the application as is traditional for easier
// parsing.
//
// The code for DebugMessage.exe is only one line. In WinMain, do:
//   MessageBox(NULL, GetCommandLineW(), L"Fatal Error", 0);
//
// If DebugMessage.exe is not found, the logging code will use a normal
// MessageBox, potentially causing the problems discussed above.

// Instructions
// ------------
//
// Make a bunch of macros for logging.  The way to log things is to stream
// things to LOG(<a particular severity level>).  E.g.,
//
//   LOG(INFO) << "Found " << num_cookies << " cookies";
//
// You can also do conditional logging:
//
//   LOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";
//
// The CHECK(condition) macro is active in both debug and release builds and
// effectively performs a LOG(FATAL) which terminates the process and
// generates a crashdump unless a debugger is attached.
//
// There are also "debug mode" logging macros like the ones above:
//
//   DLOG(INFO) << "Found cookies";
//
//   DLOG_IF(INFO, num_cookies > 10) << "Got lots of cookies";
//
// All "debug mode" logging is compiled away to nothing for non-debug mode
// compiles.  LOG_IF and development flags also work well together
// because the code can be compiled away sometimes.
//
// We also have
//
//   LOG_ASSERT(assertion);
//   DLOG_ASSERT(assertion);
//
// which is syntactic sugar for {,D}LOG_IF(FATAL, assert fails) << assertion;
//
// There are "verbose level" logging macros.  They look like
//
//   VLOG(1) << "I'm printed when you run the program with --v=1 or more";
//   VLOG(2) << "I'm printed when you run the program with --v=2 or more";
//
// These always log at the INFO log level (when they log at all).
// The verbose logging can also be turned on module-by-module.  For instance,
//    --vmodule=profile=2,icon_loader=1,browser_*=3,*/chromeos/*=4 --v=0
// will cause:
//   a. VLOG(2) and lower messages to be printed from profile.{h,cc}
//   b. VLOG(1) and lower messages to be printed from icon_loader.{h,cc}
//   c. VLOG(3) and lower messages to be printed from files prefixed with
//      "browser"
//   d. VLOG(4) and lower messages to be printed from files under a
//     "chromeos" directory.
//   e. VLOG(0) and lower messages to be printed from elsewhere
//
// The wildcarding functionality shown by (c) supports both '*' (match
// 0 or more characters) and '?' (match any single character)
// wildcards.  Any pattern containing a forward or backward slash will
// be tested against the whole pathname and not just the module.
// E.g., "*/foo/bar/*=2" would change the logging level for all code
// in source files under a "foo/bar" directory.
//
// There's also VLOG_IS_ON(n) "verbose level" condition macro. To be used as
//
//   if (VLOG_IS_ON(2)) {
//     // do some logging preparation and logging
//     // that can't be accomplished with just VLOG(2) << ...;
//   }
//
// There is also a VLOG_IF "verbose level" condition macro for sample
// cases, when some extra computation and preparation for logs is not
// needed.
//
//   VLOG_IF(1, (size > 1024))
//      << "I'm printed when size is more than 1024 and when you run the "
//         "program with --v=1 or more";
//
// We also override the standard 'assert' to use 'DLOG_ASSERT'.
//
// Lastly, there is:
//
//   PLOG(ERROR) << "Couldn't do foo";
//   DPLOG(ERROR) << "Couldn't do foo";
//   PLOG_IF(ERROR, cond) << "Couldn't do foo";
//   DPLOG_IF(ERROR, cond) << "Couldn't do foo";
//   PCHECK(condition) << "Couldn't do foo";
//   DPCHECK(condition) << "Couldn't do foo";
//
// which append the last system error to the message in string form (taken from
// GetLastError() on Windows and errno on POSIX).
//
// The supported severity levels for macros that allow you to specify one
// are (in increasing order of severity) INFO, WARNING, ERROR, and FATAL.
//
// Very important: logging a message at the FATAL severity level causes
// the program to terminate (after the message is logged).
//
// There is the special severity of DFATAL, which logs FATAL in debug mode,
// ERROR in normal mode.
//
// Output is of the format, for example:
// [3816:3877:0812/234555.406952:VERBOSE1:drm_device_handle.cc(90)] Succeeded
// authenticating /dev/dri/card0 in 0 ms with 1 attempt(s)
//
// The colon separated fields inside the brackets are as follows:
// 0. An optional Logfile prefix (not included in this example)
// 1. Process ID
// 2. Thread ID
// 3. The date/time of the log message, in MMDD/HHMMSS.Milliseconds format
// 4. The log level
// 5. The filename and line number where the log was instantiated
//
// Note that the visibility can be changed by setting preferences in
// SetLogItems()
//
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

namespace logging {

// TODO(avi): do we want to do a unification of character types here?
#if defined(OS_WIN)
typedef base::char16 PathChar;
#elif defined(OS_POSIX) || defined(OS_FUCHSIA)
typedef char PathChar;
#endif

// Where to record logging output? A flat file and/or system debug log
// via OutputDebugString.
enum LoggingDestination {
  LOG_NONE                = 0,
  LOG_TO_FILE             = 1 << 0,
  LOG_TO_SYSTEM_DEBUG_LOG = 1 << 1,

  LOG_TO_ALL = LOG_TO_FILE | LOG_TO_SYSTEM_DEBUG_LOG,

  // On Windows, use a file next to the exe; on POSIX platforms, where
  // it may not even be possible to locate the executable on disk, use
  // stderr.
#if defined(OS_WIN)
  LOG_DEFAULT = LOG_TO_FILE,
#elif defined(OS_EMSCRIPTEN)
  LOG_DEFAULT = LOG_TO_SYSTEM_DEBUG_LOG,
#elif defined(STARBOARD) || defined(OS_FUCHSIA) \
    || defined(OS_POSIX)
  LOG_DEFAULT = LOG_TO_SYSTEM_DEBUG_LOG,
#endif
};

// Indicates that the log file should be locked when being written to.
// Unless there is only one single-threaded process that is logging to
// the log file, the file should be locked during writes to make each
// log output atomic. Other writers will block.
//
// All processes writing to the log file must have their locking set for it to
// work properly. Defaults to LOCK_LOG_FILE.
enum LogLockingState { LOCK_LOG_FILE, DONT_LOCK_LOG_FILE };

// On startup, should we delete or append to an existing log file (if any)?
// Defaults to APPEND_TO_OLD_LOG_FILE.
enum OldFileDeletionState { DELETE_OLD_LOG_FILE, APPEND_TO_OLD_LOG_FILE };

struct BASE_EXPORT LoggingSettings {
  // The defaults values are:
  //
  //  logging_dest: LOG_DEFAULT
  //  log_file:     NULL
  //  lock_log:     LOCK_LOG_FILE
  //  delete_old:   APPEND_TO_OLD_LOG_FILE
  LoggingSettings();

  LoggingDestination logging_dest;

  // The three settings below have an effect only when LOG_TO_FILE is
  // set in |logging_dest|.
  const PathChar* log_file;
  LogLockingState lock_log;
  OldFileDeletionState delete_old;
};

// Define different names for the BaseInitLoggingImpl() function depending on
// whether NDEBUG is defined or not so that we'll fail to link if someone tries
// to compile logging.cc with NDEBUG but includes logging.h without defining it,
// or vice versa.
#if defined(NDEBUG)
#define BaseInitLoggingImpl BaseInitLoggingImpl_built_with_NDEBUG
#else
#define BaseInitLoggingImpl BaseInitLoggingImpl_built_without_NDEBUG
#endif

// Implementation of the InitLogging() method declared below.  We use a
// more-specific name so we can #define it above without affecting other code
// that has named stuff "InitLogging".
BASE_EXPORT bool BaseInitLoggingImpl(const LoggingSettings& settings);

// Sets the log file name and other global logging state. Calling this function
// is recommended, and is normally done at the beginning of application init.
// If you don't call it, all the flags will be initialized to their default
// values, and there is a race condition that may leak a critical section
// object if two threads try to do the first log at the same time.
// See the definition of the enums above for descriptions and default values.
//
// The default log file is initialized to "debug.log" in the application
// directory. You probably don't want this, especially since the program
// directory may not be writable on an enduser's system.
//
// This function may be called a second time to re-direct logging (e.g after
// loging in to a user partition), however it should never be called more than
// twice.
inline bool InitLogging(const LoggingSettings& settings) {
  return BaseInitLoggingImpl(settings);
}

// Sets the log level. Anything at or above this level will be written to the
// log file/displayed to the user (if applicable). Anything below this level
// will be silently ignored. The log level defaults to 0 (everything is logged
// up to level INFO) if this function is not called.
// Note that log messages for VLOG(x) are logged at level -x, so setting
// the min log level to negative values enables verbose logging.
BASE_EXPORT void SetMinLogLevel(int level);

// Gets the current log level.
BASE_EXPORT int GetMinLogLevel();

// Used by LOG_IS_ON to lazy-evaluate stream arguments.
BASE_EXPORT bool ShouldCreateLogMessage(int severity);

// Gets the VLOG default verbosity level.
BASE_EXPORT int GetVlogVerbosity();

// Note that |N| is the size *with* the null terminator.
BASE_EXPORT int GetVlogLevelHelper(const char* file_start, size_t N);

// Gets the current vlog level for the given file (usually taken from __FILE__).
template <size_t N>
int GetVlogLevel(const char (&file)[N]) {
  return GetVlogLevelHelper(file, N);
}

// Sets the common items you want to be prepended to each log message.
// process and thread IDs default to off, the timestamp defaults to on.
// If this function is not called, logging defaults to writing the timestamp
// only.
BASE_EXPORT void SetLogItems(bool enable_process_id, bool enable_thread_id,
                             bool enable_timestamp, bool enable_tickcount);

// Sets an optional prefix to add to each log message. |prefix| is not copied
// and should be a raw string constant. |prefix| must only contain ASCII letters
// to avoid confusion with PIDs and timestamps. Pass null to remove the prefix.
// Logging defaults to no prefix.
BASE_EXPORT void SetLogPrefix(const char* prefix);

// Sets whether or not you'd like to see fatal debug messages popped up in
// a dialog box or not.
// Dialogs are not shown by default.
BASE_EXPORT void SetShowErrorDialogs(bool enable_dialogs);

// Sets the Log Assert Handler that will be used to notify of check failures.
// Resets Log Assert Handler on object destruction.
// The default handler shows a dialog box and then terminate the process,
// however clients can use this function to override with their own handling
// (e.g. a silent one for Unit Tests)
using LogAssertHandlerFunction =
    base::RepeatingCallback<void(const char* file,
                                 int line,
                                 const base::StringPiece message,
                                 const base::StringPiece stack_trace)>;

class BASE_EXPORT ScopedLogAssertHandler {
 public:
  explicit ScopedLogAssertHandler(LogAssertHandlerFunction handler);
  ~ScopedLogAssertHandler();

 private:
  DISALLOW_COPY_AND_ASSIGN(ScopedLogAssertHandler);
};

// Sets the Log Message Handler that gets passed every log message before
// it's sent to other log destinations (if any).
// Returns true to signal that it handled the message and the message
// should not be sent to other log destinations.
typedef bool (*LogMessageHandlerFunction)(int severity,
    const char* file, int line, size_t message_start, const std::string& str);
BASE_EXPORT void SetLogMessageHandler(LogMessageHandlerFunction handler);
BASE_EXPORT LogMessageHandlerFunction GetLogMessageHandler();

// The ANALYZER_ASSUME_TRUE(bool arg) macro adds compiler-specific hints
// to Clang which control what code paths are statically analyzed,
// and is meant to be used in conjunction with assert & assert-like functions.
// The expression is passed straight through if analysis isn't enabled.
//
// ANALYZER_SKIP_THIS_PATH() suppresses static analysis for the current
// codepath and any other branching codepaths that might follow.
#if defined(__clang_analyzer__)

inline constexpr bool AnalyzerNoReturn() __attribute__((analyzer_noreturn)) {
  return false;
}

inline constexpr bool AnalyzerAssumeTrue(bool arg) {
  // AnalyzerNoReturn() is invoked and analysis is terminated if |arg| is
  // false.
  return arg || AnalyzerNoReturn();
}

#define ANALYZER_ASSUME_TRUE(arg) logging::AnalyzerAssumeTrue(!!(arg))
#define ANALYZER_SKIP_THIS_PATH() \
  static_cast<void>(::logging::AnalyzerNoReturn())
#define ANALYZER_ALLOW_UNUSED(var) static_cast<void>(var);

#else  // !defined(__clang_analyzer__)

#define ANALYZER_ASSUME_TRUE(arg) (arg)
#define ANALYZER_SKIP_THIS_PATH()
#define ANALYZER_ALLOW_UNUSED(var) static_cast<void>(var);

#endif  // defined(__clang_analyzer__)

typedef int LogSeverity;
const LogSeverity LOG_VERBOSE = -1;  // This is level 1 verbosity
// Note: the log severities are used to index into the array of names,
// see log_severity_names.
const LogSeverity LOG_INFO = 0;
const LogSeverity LOG_NOTICE = 1;
const LogSeverity LOG_WARNING = 2;
const LogSeverity LOG_ERROR = 3;
const LogSeverity LOG_FATAL = 4;
const LogSeverity LOG_NUM_SEVERITIES = 5;

// LOG_DFATAL is LOG_FATAL in debug mode, ERROR in normal mode
#if defined(NDEBUG)
const LogSeverity LOG_DFATAL = LOG_ERROR;
#else
const LogSeverity LOG_DFATAL = LOG_FATAL;
#endif

#define LOGGING_VERBOSE LOG_VERBOSE
#define LOGGING_INFO LOG_INFO
#define LOGGING_NOTICE LOG_NOTICE
#define LOGGING_WARNING LOG_WARNING
#define LOGGING_ERROR LOG_ERROR
#define LOGGING_FATAL LOG_FATAL
#define LOGGING_NUM_SEVERITIES LOG_NUM_SEVERITIES
#define LOGGING_DFATAL LOG_DFATAL

// A few definitions of macros that don't generate much code. These are used
// by LOG() and LOG_IF, etc. Since these are used all over our code, it's
// better to have compact code for these operations.
#define COMPACT_GOOGLE_LOG_EX_INFO(ClassName, ...) \
  ::logging::ClassName(__FILE__, __LINE__, ::logging::LOG_INFO, ##__VA_ARGS__)
#define COMPACT_GOOGLE_LOG_EX_NOTICE(ClassName, ...) \
  ::logging::ClassName(__FILE__, __LINE__, ::logging::LOG_NOTICE, ##__VA_ARGS__)
#define COMPACT_GOOGLE_LOG_EX_WARNING(ClassName, ...)              \
  ::logging::ClassName(__FILE__, __LINE__, ::logging::LOG_WARNING, \
                       ##__VA_ARGS__)
#define COMPACT_GOOGLE_LOG_EX_ERROR(ClassName, ...) \
  ::logging::ClassName(__FILE__, __LINE__, ::logging::LOG_ERROR, ##__VA_ARGS__)
#define COMPACT_GOOGLE_LOG_EX_FATAL(ClassName, ...) \
  ::logging::ClassName(__FILE__, __LINE__, ::logging::LOG_FATAL, ##__VA_ARGS__)
#define COMPACT_GOOGLE_LOG_EX_DFATAL(ClassName, ...) \
  ::logging::ClassName(__FILE__, __LINE__, ::logging::LOG_DFATAL, ##__VA_ARGS__)
#define COMPACT_GOOGLE_LOG_EX_DCHECK(ClassName, ...) \
  ::logging::ClassName(__FILE__, __LINE__, ::logging::LOG_DCHECK, ##__VA_ARGS__)

#define COMPACT_GOOGLE_LOG_INFO COMPACT_GOOGLE_LOG_EX_INFO(LogMessage)
#define COMPACT_GOOGLE_LOG_NOTICE COMPACT_GOOGLE_LOG_EX_NOTICE(LogMessage)
#define COMPACT_GOOGLE_LOG_WARNING COMPACT_GOOGLE_LOG_EX_WARNING(LogMessage)
#define COMPACT_GOOGLE_LOG_ERROR COMPACT_GOOGLE_LOG_EX_ERROR(LogMessage)
#define COMPACT_GOOGLE_LOG_FATAL COMPACT_GOOGLE_LOG_EX_FATAL(LogMessage)
#define COMPACT_GOOGLE_LOG_DFATAL COMPACT_GOOGLE_LOG_EX_DFATAL(LogMessage)
#define COMPACT_GOOGLE_LOG_DCHECK COMPACT_GOOGLE_LOG_EX_DCHECK(LogMessage)

#if defined(OS_WIN)
// wingdi.h defines ERROR to be 0. When we call LOG(ERROR), it gets
// substituted with 0, and it expands to COMPACT_GOOGLE_LOG_0. To allow us
// to keep using this syntax, we define this macro to do the same thing
// as COMPACT_GOOGLE_LOG_ERROR, and also define ERROR the same way that
// the Windows SDK does for consistency.
#define ERROR 0
#define COMPACT_GOOGLE_LOG_EX_0(ClassName, ...) \
  COMPACT_GOOGLE_LOG_EX_ERROR(ClassName , ##__VA_ARGS__)
#define COMPACT_GOOGLE_LOG_0 COMPACT_GOOGLE_LOG_ERROR
// Needed for LOG_IS_ON(ERROR).
const LogSeverity LOG_0 = LOG_ERROR;
#define LOGGING_0 LOG_0
#endif

// As special cases, we can assume that LOG_IS_ON(FATAL) always holds. Also,
// LOG_IS_ON(DFATAL) always holds in debug mode. In particular, CHECK()s will
// always fire if they fail.
#define LOG_IS_ON(severity) \
  (::logging::ShouldCreateLogMessage(::logging::LOG_##severity))

#define INTERNAL_VLOG_IS_ON(verboselevel, file) \
  ((verboselevel) <= ::logging::GetVlogLevel(file))

// We don't do any caching tricks with VLOG_IS_ON() like the
// google-glog version since it increases binary size.  This means
// that using the v-logging functions in conjunction with --vmodule
// may be slow.
#define VLOG_IS_ON(verboselevel) \
  INTERNAL_VLOG_IS_ON(verboselevel, __FILE__)

// Helper macro which avoids evaluating the arguments to a stream if
// the condition doesn't hold. Condition is evaluated once and only once.
#define LAZY_STREAM(stream, condition)                                  \
  !(condition) ? (void) 0 : ::logging::LogMessageVoidify() & (stream)

// We use the preprocessor's merging operator, "##", so that, e.g.,
// LOG(INFO) becomes the token COMPACT_GOOGLE_LOG_INFO.  There's some funny
// subtle difference between ostream member streaming functions (e.g.,
// ostream::operator<<(int) and ostream non-member streaming functions
// (e.g., ::operator<<(ostream&, string&): it turns out that it's
// impossible to stream something like a string directly to an unnamed
// ostream. We employ a neat hack by calling the stream() member
// function of LogMessage which seems to avoid the problem.
#define LOG_STREAM(severity) COMPACT_GOOGLE_LOG_ ## severity.stream()

#define LOG(severity) LAZY_STREAM(LOG_STREAM(severity), LOG_IS_ON(severity))
#define LOG_IF(severity, condition) \
  LAZY_STREAM(LOG_STREAM(severity), LOG_IS_ON(severity) && (condition))

// The VLOG macros log with negative verbosities.
#define VLOG_STREAM(verbose_level) \
  ::logging::LogMessage(__FILE__, __LINE__, -verbose_level).stream()

#define VLOG(verbose_level) \
  LAZY_STREAM(VLOG_STREAM(verbose_level), VLOG_IS_ON(verbose_level))

#define VLOG_IF(verbose_level, condition) \
  LAZY_STREAM(VLOG_STREAM(verbose_level), \
      VLOG_IS_ON(verbose_level) && (condition))

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

#if defined (OS_WIN)
#define VPLOG_STREAM(verbose_level) \
  ::logging::Win32ErrorLogMessage(__FILE__, __LINE__, -verbose_level, \
    ::logging::GetLastSystemErrorCode()).stream()
#elif defined(OS_POSIX) || defined(OS_FUCHSIA)
#define VPLOG_STREAM(verbose_level) \
  ::logging::ErrnoLogMessage(__FILE__, __LINE__, -verbose_level, \
    ::logging::GetLastSystemErrorCode()).stream()
#endif

#define VPLOG(verbose_level) \
  LAZY_STREAM(VPLOG_STREAM(verbose_level), VLOG_IS_ON(verbose_level))

#define VPLOG_IF(verbose_level, condition) \
  LAZY_STREAM(VPLOG_STREAM(verbose_level), \
    VLOG_IS_ON(verbose_level) && (condition))

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

#define LOG_ASSERT(condition)                       \
  LOG_IF(FATAL, !(ANALYZER_ASSUME_TRUE(condition))) \
      << "Assert failed: " #condition ". "

#if defined(OS_WIN)
#define PLOG_STREAM(severity) \
  COMPACT_GOOGLE_LOG_EX_ ## severity(Win32ErrorLogMessage, \
      ::logging::GetLastSystemErrorCode()).stream()
#elif defined(OS_POSIX) || defined(OS_FUCHSIA)
#define PLOG_STREAM(severity) \
  COMPACT_GOOGLE_LOG_EX_ ## severity(ErrnoLogMessage, \
      ::logging::GetLastSystemErrorCode()).stream()
#endif

// Prints the string corresponding to the error code in errno,
// like %m in printf.
// foo.conf does not exist, errno was set to ENOENT
// int fd = open("foo.conf", O_RDONLY);
// if (fd < 0) {
//     // "Fail to open foo.conf: No such file or directory"
//     PLOG(FATAL) << "Fail to open foo.conf";
//     return -1;
// }
#define PLOG(severity)                                          \
  LAZY_STREAM(PLOG_STREAM(severity), LOG_IS_ON(severity))

#define PLOG_IF(severity, condition) \
  LAZY_STREAM(PLOG_STREAM(severity), LOG_IS_ON(severity) && (condition))

BASE_EXPORT extern std::ostream* g_swallow_stream;

// Note that g_swallow_stream is used instead of an arbitrary LOG() stream to
// avoid the creation of an object with a non-trivial destructor (LogMessage).
// On MSVC x86 (checked on 2015 Update 3), this causes a few additional
// pointless instructions to be emitted even at full optimization level, even
// though the : arm of the ternary operator is clearly never executed. Using a
// simpler object to be &'d with Voidify() avoids these extra instructions.
// Using a simpler POD object with a templated operator<< also works to avoid
// these instructions. However, this causes warnings on statically defined
// implementations of operator<<(std::ostream, ...) in some .cc files, because
// they become defined-but-unreferenced functions. A reinterpret_cast of 0 to an
// ostream* also is not suitable, because some compilers warn of undefined
// behavior.
#define EAT_STREAM_PARAMETERS \
  true ? (void)0              \
       : ::logging::LogMessageVoidify() & (*::logging::g_swallow_stream)

// Crashes in the fastest possible way with no attempt at logging.
// There are different constraints to satisfy here, see http://crbug.com/664209
// for more context:
// - The trap instructions, and hence the PC value at crash time, have to be
//   distinct and not get folded into the same opcode by the compiler.
//   On Linux/Android this is tricky because GCC still folds identical
//   asm volatile blocks. The workaround is generating distinct opcodes for
//   each CHECK using the __COUNTER__ macro.
// - The debug info for the trap instruction has to be attributed to the source
//   line that has the CHECK(), to make crash reports actionable. This rules
//   out the ability of using a inline function, at least as long as clang
//   doesn't support attribute(artificial).
// - Failed CHECKs should produce a signal that is distinguishable from an
//   invalid memory access, to improve the actionability of crash reports.
// - The compiler should treat the CHECK as no-return instructions, so that the
//   trap code can be efficiently packed in the prologue of the function and
//   doesn't interfere with the main execution flow.
// - When debugging, developers shouldn't be able to accidentally step over a
//   CHECK. This is achieved by putting opcodes that will cause a non
//   continuable exception after the actual trap instruction.
// - Don't cause too much binary bloat.
#if defined(__EMSCRIPTEN__)
  // see emscripten/bits/signal.h
  #define TRAP_SEQUENCE() raise(SIGTRAP)
#elif defined(COMPILER_GCC)

#if defined(ARCH_CPU_X86_FAMILY) && !defined(OS_NACL)
// int 3 will generate a SIGTRAP.
#define TRAP_SEQUENCE() \
  asm volatile(         \
      "int3; ud2; push %0;" ::"i"(static_cast<unsigned char>(__COUNTER__)))

#elif defined(ARCH_CPU_ARMEL) && !defined(OS_NACL)
// bkpt will generate a SIGBUS when running on armv7 and a SIGTRAP when running
// as a 32 bit userspace app on arm64. There doesn't seem to be any way to
// cause a SIGTRAP from userspace without using a syscall (which would be a
// problem for sandboxing).
#define TRAP_SEQUENCE() \
  asm volatile("bkpt #0; udf %0;" ::"i"(__COUNTER__ % 256))

#elif defined(ARCH_CPU_ARM64) && !defined(OS_NACL)
// This will always generate a SIGTRAP on arm64.
#define TRAP_SEQUENCE() \
  asm volatile("brk #0; hlt %0;" ::"i"(__COUNTER__ % 65536))

#else
// Crash report accuracy will not be guaranteed on other architectures, but at
// least this will crash as expected.
#define TRAP_SEQUENCE() __builtin_trap()
#endif  // ARCH_CPU_*

#elif defined(COMPILER_MSVC)

// Clang is cleverer about coalescing int3s, so we need to add a unique-ish
// instruction following the __debugbreak() to have it emit distinct locations
// for CHECKs rather than collapsing them all together. It would be nice to use
// a short intrinsic to do this (and perhaps have only one implementation for
// both clang and MSVC), however clang-cl currently does not support intrinsics.
// On the flip side, MSVC x64 doesn't support inline asm. So, we have to have
// two implementations. Normally clang-cl's version will be 5 bytes (1 for
// `int3`, 2 for `ud2`, 2 for `push byte imm`, however, TODO(scottmg):
// https://crbug.com/694670 clang-cl doesn't currently support %'ing
// __COUNTER__, so eventually it will emit the dword form of push.
// TODO(scottmg): Reinvestigate a short sequence that will work on both
// compilers once clang supports more intrinsics. See https://crbug.com/693713.
#if !defined(__clang__)
#define TRAP_SEQUENCE() __debugbreak()
#elif defined(ARCH_CPU_ARM64)
#define TRAP_SEQUENCE() \
  __asm volatile("brk #0\n hlt %0\n" ::"i"(__COUNTER__ % 65536));
#else
#define TRAP_SEQUENCE() ({ {__asm int 3 __asm ud2 __asm push __COUNTER__}; })
#endif  // __clang__

#else
#error Port
#endif  // COMPILER_GCC

// Definitions for DLOG et al.

#if DCHECK_IS_ON()

#define DLOG_IS_ON(severity) LOG_IS_ON(severity)
#define DLOG_IF(severity, condition) LOG_IF(severity, condition)
#define DLOG_ASSERT(condition) LOG_ASSERT(condition)
#define DPLOG_IF(severity, condition) PLOG_IF(severity, condition)
#define DVLOG_IF(verboselevel, condition) VLOG_IF(verboselevel, condition)
#define DVPLOG_IF(verboselevel, condition) VPLOG_IF(verboselevel, condition)

#else  // DCHECK_IS_ON()

// If !DCHECK_IS_ON(), we want to avoid emitting any references to |condition|
// (which may reference a variable defined only if DCHECK_IS_ON()).
// Contrast this with DCHECK et al., which has different behavior.

#define DLOG_IS_ON(severity) false
#define DLOG_IF(severity, condition) EAT_STREAM_PARAMETERS
#define DLOG_ASSERT(condition) EAT_STREAM_PARAMETERS
#define DPLOG_IF(severity, condition) EAT_STREAM_PARAMETERS
#define DVLOG_IF(verboselevel, condition) EAT_STREAM_PARAMETERS
#define DVPLOG_IF(verboselevel, condition) EAT_STREAM_PARAMETERS

#endif  // DCHECK_IS_ON()

#define DLOG(severity)                                          \
  LAZY_STREAM(LOG_STREAM(severity), DLOG_IS_ON(severity))

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

#define DPLOG(severity)                                         \
  LAZY_STREAM(PLOG_STREAM(severity), DLOG_IS_ON(severity))

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

#define DVLOG(verboselevel) DVLOG_IF(verboselevel, true)

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

#define DVPLOG(verboselevel) DVPLOG_IF(verboselevel, true)

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

// Definitions for DCHECK et al.

#if DCHECK_IS_ON()

#if defined(DCHECK_IS_CONFIGURABLE)
BASE_EXPORT extern LogSeverity LOG_DCHECK;
#else
const LogSeverity LOG_DCHECK = LOG_FATAL;
#endif  // defined(DCHECK_IS_CONFIGURABLE)

#else  // DCHECK_IS_ON()

// There may be users of LOG_DCHECK that are enabled independently
// of DCHECK_IS_ON(), so default to FATAL logging for those.
const LogSeverity LOG_DCHECK = LOG_FATAL;

#endif  // DCHECK_IS_ON()

#define LOGGING_DCHECK LOG_DCHECK

// Redefine the standard assert to use our nice log files
#undef assert
#define assert(x) DLOG_ASSERT(x)

#if defined(OS_WIN)
typedef unsigned long SystemErrorCode;
#elif defined(OS_POSIX) || defined(OS_FUCHSIA)
typedef int SystemErrorCode;
#endif

// Alias for ::GetLastError() on Windows and errno on POSIX. Avoids having to
// pull in windows.h just for GetLastError() and DWORD.
BASE_EXPORT SystemErrorCode GetLastSystemErrorCode();
BASE_EXPORT std::string SystemErrorCodeToString(SystemErrorCode error_code);

class LogStringStream
  : public std::ostringstream
{
public:
  LogStringStream()
    : std::ostringstream()
    , file_("-")
    , line_(0)
    , severity_(0)
    , noEndl_(false)
    , noFormat_(false)
  {}

  ~LogStringStream() {
    noEndl_ = false;
    noFormat_ = false;
  }

  inline LogStringStream& operator<<(LogStringStream& (*m)(LogStringStream&)) {
    return m(*this);
  }

  inline LogStringStream& operator<<(std::ostream& (*m)(std::ostream&)) {
    m(*(std::ostream*)this);
    return *this;
  }

  template <typename T> inline LogStringStream& operator<<(T const& t) {
    *(std::ostream*)this << t;
    return *this;
  }

  LogStringStream& SetPosition(const char* file, int line, LogSeverity);

  LogStringStream& dontEndlOnce()
  {
    noEndl_ = true;
    return *this;
  }

  LogStringStream& dontFormatOnce()
  {
    noFormat_ = true;
    return *this;
  }

  const char* file() const { return file_; }

  int line() const { return line_; }

  LogSeverity severity() const { return severity_; }

  // Returns false if stream must continue on same line
  bool needEndl() const
  {
    return !noEndl_;
  }

  bool needFormat() const
  {
    return !noFormat_;
  }

private:
  const char* file_;
  int line_;
  LogSeverity severity_;
  bool noEndl_;
  bool noFormat_;
};

/// \todo support custom log sinks
/// like in https://source.chromium.org/chromium/chromium/src/+/master:third_party/webrtc/rtc_base/logging.h
//
// This class more or less represents a particular log message.  You
// create an instance of LogMessage and then stream stuff to it.
// When you finish streaming to it, ~LogMessage is called and the
// full message gets streamed to the appropriate destination.
//
// You shouldn't actually use LogMessage's constructor to log things,
// though.  You should use the LOG() macro (and variants thereof)
// above.
class BASE_EXPORT LogMessage {
 public:
  using LogStreamType
    = std::ostream;

  using LogStringStreamType
    = LogStringStream;

  // Used for LOG(severity).
  LogMessage(const char* file, int line, LogSeverity severity);

  // Used for CHECK().  Implied severity = LOG_FATAL.
  LogMessage(const char* file, int line, const char* condition);

  // Used for CHECK_EQ(), etc. Takes ownership of the given string.
  // Implied severity = LOG_FATAL.
  LogMessage(const char* file, int line, std::string* result);

  // Used for DCHECK_EQ(), etc. Takes ownership of the given string.
  LogMessage(const char* file, int line, LogSeverity severity,
             std::string* result);

  ~LogMessage();

  LogStreamType& stream() { return logStream_; }

  LogSeverity severity() { return severity_; }

  std::string str() { return logStream_.str(); }

 private:
  void Init(const char* file, int line, LogSeverity severity);

  LogSeverity severity_;
  // The real data is inside LogStream which may be cached thread-locally.
  LogStringStreamType logStream_;
  size_t message_start_;  // Offset of the start of the message (past prefix
                          // info).
  // The file and line information passed in to the constructor.
  const char* file_;
  const int line_;

  // This is useful since the LogMessage class uses a lot of Win32 calls
  // that will lose the value of GLE and the code that called the log function
  // will have lost the thread error value when the log call returns.
  base::internal::ScopedClearLastError last_error_;
};

// This class is used to explicitly ignore values in the conditional
// logging macros.  This avoids compiler warnings like "value computed
// is not used" and "statement has no effect".
class LogMessageVoidify {
 public:
  LogMessageVoidify() = default;
  // This has to be an operator with a precedence lower than << but
  // higher than ?:
  void operator&(std::ostream&) { }
};

#if defined(OS_WIN)
// Appends a formatted system message of the GetLastError() type.
class BASE_EXPORT Win32ErrorLogMessage : public LogMessage {
 public:
  Win32ErrorLogMessage(const char* file,
                       int line,
                       LogSeverity severity,
                       SystemErrorCode err);

  // Appends the error message before destructing the encapsulated class.
  ~Win32ErrorLogMessage();

  Win32ErrorLogMessage& operator=(const Win32ErrorLogMessage&) = delete;

  LogMessage::LogStreamType& stream() { return stream(); }

 private:
  SystemErrorCode err_;
};
#elif defined(OS_POSIX) || defined(OS_FUCHSIA)
// Appends a formatted system message of the errno type
class BASE_EXPORT ErrnoLogMessage : public LogMessage {
 public:
  ErrnoLogMessage(const char* file,
                  int line,
                  LogSeverity severity,
                  SystemErrorCode err);

  // Appends the error message before destructing the encapsulated class.
  ~ErrnoLogMessage();

  ErrnoLogMessage& operator=(const ErrnoLogMessage&) = delete;

  LogMessage::LogStreamType& stream() { return stream(); }

 private:
  SystemErrorCode err_;
};
#endif  // OS_WIN

// Closes the log file explicitly if open.
// NOTE: Since the log file is opened as necessary by the action of logging
//       statements, there's no guarantee that it will stay closed
//       after this call.
BASE_EXPORT void CloseLogFile();

// Async signal safe logging mechanism.
BASE_EXPORT void RawLog(int level, const char* message);

#define RAW_LOG(level, message) \
  ::logging::RawLog(::logging::LOG_##level, message)

#define RAW_CHECK(condition)                               \
  do {                                                     \
    if (!(condition))                                      \
      ::logging::RawLog(::logging::LOG_FATAL,              \
                        "Check failed: " #condition "\n"); \
  } while (0)

#if defined(OS_WIN)
// Returns true if logging to file is enabled.
BASE_EXPORT bool IsLoggingToFileEnabled();

// Returns the default log file path.
BASE_EXPORT base::string16 GetLogFileFullPath();
#endif

// Do not append endl after each log message
inline LogStringStream& noEndl(LogStringStream& ls)
{
  ls.dontEndlOnce();
  return ls;
}

// Do not append extra information before each log message
// that looks similar to:
// [25583:25583:1113/185640.856387:39412343570:INFO:main.cc(375)]
inline LogStringStream& noFormat(LogStringStream& ls)
{
  ls.dontFormatOnce();
  return ls;
}

LogStringStream& info(LogStringStream& ls);

// Can be used in conditions
//
// USAGE
//
// using ::logging::doNothing;
//
// for (auto it = items.begin(); it != items.end(); ++it) {
//   const bool isLastElem
//     = it == (items.end() - 1);
//   LOG(INFO) << ' ' << *it << noFormat
//             << (!isLastElem ? noEndl : doNothing);
// }
inline LogStringStream& doNothing(LogStringStream& ls)
{
  return ls;
}

}  // namespace logging

// Note that "The behavior of a C++ program is undefined if it adds declarations
// or definitions to namespace std or to a namespace within namespace std unless
// otherwise specified." --C++11[namespace.std]
//
// We've checked that this particular definition has the intended behavior on
// our implementations, but it's prone to breaking in the future, and please
// don't imitate this in your own definitions without checking with some
// standard library experts.
namespace std {
// These functions are provided as a convenience for logging, which is where we
// use streams (it is against Google style to use streams in other places). It
// is designed to allow you to emit non-ASCII Unicode strings to the log file,
// which is normally ASCII. It is relatively slow, so try not to use it for
// common cases. Non-ASCII characters will be converted to UTF-8 by these
// operators.
BASE_EXPORT std::ostream& operator<<(std::ostream& out, const wchar_t* wstr);
BASE_EXPORT std::ostream& operator<<(std::ostream& out,
                                     const std::wstring& wstr);

BASE_EXPORT std::ostream& operator<<(std::ostream& out, const char16_t* str16);
BASE_EXPORT std::ostream& operator<<(std::ostream& out,
                                     const std::u16string& str16);
}  // namespace std

// The NOTIMPLEMENTED() macro annotates codepaths which have not been
// implemented yet. If output spam is a serious concern,
// NOTIMPLEMENTED_LOG_ONCE can be used.

#if defined(COMPILER_GCC)
// On Linux, with GCC, we can use __PRETTY_FUNCTION__ to get the demangled name
// of the current function in the NOTIMPLEMENTED message.
#define NOTIMPLEMENTED_MSG "Not implemented reached in " << __PRETTY_FUNCTION__
#else
#define NOTIMPLEMENTED_MSG "NOT IMPLEMENTED"
#endif

#define NOTIMPLEMENTED() DLOG(ERROR) << NOTIMPLEMENTED_MSG
#define NOTIMPLEMENTED_LOG_ONCE()                       \
  do {                                                  \
    static bool logged_once = false;                    \
    DLOG_IF(ERROR, !logged_once) << NOTIMPLEMENTED_MSG; \
    logged_once = true;                                 \
  } while (0);                                          \
  EAT_STREAM_PARAMETERS

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

#endif  // BASE_LOGGING_H_
