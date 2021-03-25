#pragma once

/**
 * @brief provides per-file debug logging based on |#define|-s with log levels
 * @note in most cases you must prefer |VLOG_LOC|
 * @note LOCAL_TRACE_LEVEL specifies minimal logging level
 * (will not log anything with bigger logging level)
 * @note LOCAL_ENABLE_CATEGORY_* can be used to filter logging by categories
 * (will not log anything when LOCAL_ENABLE_CATEGORY_* is 0)
 * make sure that you defined all possible categories, even if their value is 0
 * @note you can define custom TRACE_LOG_FUNC
 * @example
 *   #define LOCAL_TRACE_LEVEL 2
 *
 *   #define LOCAL_ENABLE_CATEGORY_DEB0 0
 *
 *   #if LOCAL_CATEGORY_ENABLED(DEB0)
 *     LTRACE; // will not print anything
 *   #endif // LOCAL_CATEGORY_ENABLED
 *
 *   #define LOCAL_ENABLE_CATEGORY_DEB0 1
 *
 *   #if LOCAL_CATEGORY_ENABLED(DEB0)
 *     LTRACEF_LEVEL(1, "started main %d\n", 123); // will print
 *   #endif // LOCAL_CATEGORY_ENABLED
 **/

#include <stdio.h>
#include <base/logging.h>

//#define __FUNC__ __PRETTY_FUNCTION__
#define __FUNC__ __func__

/* trace routines */
#if !defined(TRACE_LOG_FUNC)
#define TRACE_LOG_FUNC printf
#endif // defined(TRACE_LOG_FUNC)
#define TRACE_ENTRY TRACE_LOG_FUNC("%s: entry\n", __FUNC__)
#define TRACE_EXIT TRACE_LOG_FUNC("%s: exit\n", __FUNC__)
#define TRACE_ENTRY_OBJ TRACE_LOG_FUNC("%s: entry obj %p\n", __FUNC__, this)
#define TRACE_EXIT_OBJ TRACE_LOG_FUNC("%s: exit obj %p\n", __FUNC__, this)
#define TRACE TRACE_LOG_FUNC("%s:%d\n", __FUNC__, __LINE__)
#define TRACEF(str, x...)                           \
  do {                                              \
    TRACE_LOG_FUNC("%s:%d: " str, __FUNC__, __LINE__, ##x); \
  } while (0)

/* trace routines that work if LOCAL_TRACE_LEVEL is set */
#define LTRACE_ENTRY   \
  do {                 \
    if (LOCAL_TRACE_LEVEL) { \
      TRACE_ENTRY;     \
    }                  \
  } while (0)
#define LTRACE_EXIT    \
  do {                 \
    if (LOCAL_TRACE_LEVEL) { \
      TRACE_EXIT;      \
    }                  \
  } while (0)
#define LTRACE_ENTRY_OBJ \
  do {                   \
    if (LOCAL_TRACE_LEVEL) {   \
      TRACE_ENTRY_OBJ;   \
    }                    \
  } while (0)
#define LTRACE_EXIT_OBJ \
  do {                  \
    if (LOCAL_TRACE_LEVEL) {  \
      TRACE_EXIT_OBJ;   \
    }                   \
  } while (0)
#define LTRACE         \
  do {                 \
    if (LOCAL_TRACE_LEVEL) { \
      TRACE;           \
    }                  \
  } while (0)
#define LTRACEF(x...)  \
  do {                 \
    if (LOCAL_TRACE_LEVEL) { \
      TRACEF(x);       \
    }                  \
  } while (0)
#define LTRACEF_LEVEL(level, x...) \
  do {                             \
    if (LOCAL_TRACE_LEVEL >= (level)) {  \
      TRACEF(x);                   \
    }                              \
  } while (0)
#define LOCAL_CATEGORY_ENABLED(category)    \
 (LOCAL_ENABLE_CATEGORY_##category)
#define LOCAL_CATEGORY_AND_LEVEL_ENABLED(category, level)    \
 (LOCAL_ENABLE_CATEGORY_##category \
  && LOCAL_TRACE_LEVEL >= (level))
// Shorthand for the "check category, level and debug build"
#define DCHECK_LOCAL_CATEGORY_AND_LEVEL_ENABLED(category, level)    \
 (LOCAL_CATEGORY_AND_LEVEL_ENABLED(category, level) \
  && DCHECK_IS_ON())

