#pragma once

#include "build/buildflag.h"

// Do not enable PI mutexes without consulting the security team
// see https://github.com/geanix/courgette/blob/master/gen/base/synchronization/synchronization_buildflags.h
#define BUILDFLAG_INTERNAL_ENABLE_MUTEX_PRIORITY_INHERITANCE() (@BUILDFLAG_INTERNAL_ENABLE_MUTEX_PRIORITY_INHERITANCE@)
