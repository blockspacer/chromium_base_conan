#pragma once

#include "build/buildflag.h"

#define BUILDFLAG_INTERNAL_USE_ALLOCATOR_SHIM() (0)

#if defined(__linux__) || defined(__unix__ ) || defined(__EMSCRIPTEN__)
#define BUILDFLAG_INTERNAL_USE_NEW_TCMALLOC() (1)
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define BUILDFLAG_INTERNAL_USE_NEW_TCMALLOC() (0)
#else
#error "unknown platform"
#endif
