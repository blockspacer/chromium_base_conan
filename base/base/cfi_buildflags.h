#pragma once

#include "build/buildflag.h"

// see https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1968

// TODO(pcc): remove CFI_CAST_CHECK, see https://crbug.com/626794.
#define BUILDFLAG_INTERNAL_CFI_CAST_CHECK() (0)
#define BUILDFLAG_INTERNAL_CFI_ICALL_CHECK() (0)
#define BUILDFLAG_INTERNAL_CFI_ENFORCEMENT_TRAP() (0)
#define BUILDFLAG_INTERNAL_CFI_ENFORCEMENT_DIAGNOSTIC() (0)
