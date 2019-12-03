#pragma once

// see
// https://chromium.googlesource.com/aosp/platform/external/libchrome/+/refs/heads/master/base/debug/debugging_flags.h
// see https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1980

#include "build/buildflag.h"

#define BUILDFLAG_INTERNAL_ENABLE_LOCATION_SOURCE() (1)
#define BUILDFLAG_INTERNAL_ENABLE_PROFILING() (0)
#define BUILDFLAG_INTERNAL_CAN_UNWIND_WITH_FRAME_POINTERS() (0)
#define BUILDFLAG_INTERNAL_UNSAFE_DEVELOPER_BUILD() (0)
#define BUILDFLAG_INTERNAL_CAN_UNWIND_WITH_CFI_TABLE() (0)
#define BUILDFLAG_INTERNAL_ENABLE_MEMORY_TASK_PROFILER() (0)

// https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1992
// https://github.com/chromium/chromium/blob/master/base/debug/debugger_posix.cc#L181
#define BUILDFLAG_INTERNAL_ENABLE_GDBINIT_WARNING() (0)
