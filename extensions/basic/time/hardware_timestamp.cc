/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <basic/time/hardware_timestamp.h>

#include "build/build_config.h"

#include <base/compiler_specific.h>
#include <base/logging.h>

#include <chrono>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
extern "C" std::uint64_t __rdtsc();
#pragma intrinsic(__rdtsc)
#endif

#if defined(OS_WIN)
#include <io.h>
#include <windows.h>
typedef HANDLE FileHandle;
// Windows warns on using write().  It prefers _write().
#define write(fd, buf, count) _write(fd, buf, static_cast<unsigned int>(count))
// Windows doesn't define STDERR_FILENO.  Define it here.
#define STDERR_FILENO 2

#elif defined(OS_APPLE)
// In MacOS 10.12 and iOS 10.0 and later ASL (Apple System Log) was deprecated
// in favor of OS_LOG (Unified Logging).
#include <AvailabilityMacros.h>
#if defined(OS_IOS)
#if !defined(__IPHONE_10_0) || __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_10_0
#define USE_ASL
#endif
#else  // !defined(OS_IOS)
#if !defined(MAC_OS_X_VERSION_10_12) || \
    MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_12
#define USE_ASL
#endif
#endif  // defined(OS_IOS)

#if defined(USE_ASL)
#include <asl.h>
#else
#include <os/log.h>
#endif

#include <CoreFoundation/CoreFoundation.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <mach-o/dyld.h>

#elif defined(OS_POSIX) || defined(OS_FUCHSIA) || defined(OS_EMSCRIPTEN)
#if defined(OS_NACL) || defined(OS_EMSCRIPTEN)
#include <sys/time.h>  // timespec doesn't seem to be in <time.h>
#endif
#include <time.h>
#endif

namespace basic {

uint64_t GetClockTickCount() {
#if defined(OS_WIN)
  return GetTickCount();
#elif defined(OS_EMSCRIPTEN)
  // this goes above x86-specific code because old versions of Emscripten
  // define __x86_64__, although they have nothing to do with it.
  /// \note The result is not an absolute time,
  /// and is only meaningful in comparison to other calls to this function (!!!)
  // emscripten_get_now() returns a wallclock time as a float in milliseconds (1e-3).
  return static_cast<int64_t>(emscripten_get_now() * 1e+6);
#elif defined(OS_FUCHSIA)
  return zx_clock_get_monotonic() /
         static_cast<zx_time_t>(base::Time::kNanosecondsPerMicrosecond);
#elif defined(OS_APPLE)
  return mach_absolute_time();
#elif defined(OS_NACL)
  // NaCl sadly does not have _POSIX_TIMERS enabled in sys/features.h
  // So we have to use clock() for now.
  return clock();
#elif defined(OS_POSIX)
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);

  uint64_t absolute_micro = static_cast<int64_t>(ts.tv_sec) * 1000000 +
                            static_cast<int64_t>(ts.tv_nsec) / 1000;

  return absolute_micro;
#endif
}

// number of clock cycles since the last reset
std::uint64_t hardware_timestamp() {
#ifdef __EMSCRIPTEN__
  // this goes above x86-specific code because old versions of Emscripten
  // define __x86_64__, although they have nothing to do with it.
  /// \note The result is not an absolute time,
  /// and is only meaningful in comparison to other calls to this function (!!!)
  // emscripten_get_now() returns a wallclock time as a float in milliseconds (1e-3).
  return static_cast<int64_t>(emscripten_get_now() * 1e+6);
#elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
  return __rdtsc();
#elif defined(__GNUC__) && (defined(__i386__) || BASIC_X64)
  return __builtin_ia32_rdtsc();
#else
  // use steady_clock::now() as an approximation for the timestamp counter on
  // non-x86 systems
  return std::chrono::steady_clock::now().time_since_epoch().count();
#endif
}

} // namespace basic
