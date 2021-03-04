#pragma once

// see
// https://chromium.googlesource.com/aosp/platform/external/libchrome/+/refs/heads/master/base/debug/debugging_flags.h
// see https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1980

#include "build/buildflag.h"

#define BUILDFLAG_INTERNAL_EXPENSIVE_DCHECKS_ARE_ON() (0)

#define BUILDFLAG_INTERNAL_ENABLE_LOCATION_SOURCE() (@ENABLE_LOCATION_SOURCE@)
#define BUILDFLAG_INTERNAL_ENABLE_PROFILING() (@USE_PROFILING@)
#define BUILDFLAG_INTERNAL_CAN_UNWIND_WITH_FRAME_POINTERS() (@CAN_UNWIND_WITH_FRAME_POINTERS@)
#define BUILDFLAG_INTERNAL_CAN_UNWIND_WITH_CFI_TABLE() (@CAN_UNWIND_WITH_CFI_TABLE@)
#define BUILDFLAG_INTERNAL_ENABLE_MEMORY_TASK_PROFILER() (@ENABLE_MEMORY_TASK_PROFILER@)

// https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1992
// https://github.com/chromium/chromium/blob/master/base/debug/debugger_posix.cc#L181
#define BUILDFLAG_INTERNAL_ENABLE_GDBINIT_WARNING() (@ENABLE_GDBINIT_WARNING@)
#define BUILDFLAG_INTERNAL_UNSAFE_DEVELOPER_BUILD() (@IS_UNSAFE_DEVELOPER_BUILD@)
