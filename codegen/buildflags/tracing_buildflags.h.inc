#pragma once

#include "build/buildflag.h"

// Compile with Control Flow Integrity to protect virtual calls and casts.
// See http://clang.llvm.org/docs/ControlFlowIntegrity.html
// see https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1968

// TODO(pcc): remove CFI_CAST_CHECK, see https://crbug.com/626794.
#define BUILDFLAG_INTERNAL_ENABLE_BASE_TRACING() (@BUILDFLAG_INTERNAL_ENABLE_BASE_TRACING@)
#define BUILDFLAG_INTERNAL_USE_PERFETTO_CLIENT_LIBRARY() (@BUILDFLAG_INTERNAL_USE_PERFETTO_CLIENT_LIBRARY@)
#define BUILDFLAG_INTERNAL_OPTIONAL_TRACE_EVENTS_ENABLED() (@BUILDFLAG_INTERNAL_OPTIONAL_TRACE_EVENTS_ENABLED@)
