// Copyright (c) 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_ALLOCATOR_PARTITION_ALLOCATOR_PARTITION_ALLOC_INL_H_
#define BASE_ALLOCATOR_PARTITION_ALLOCATOR_PARTITION_ALLOC_INL_H_

#include <cstring>

#include "base/allocator/partition_allocator/partition_cookie.h"
#include "base/allocator/partition_allocator/partition_ref_count.h"
#include "base/allocator/partition_allocator/random.h"
#include "base/partition_alloc_buildflags.h"
#include "build/build_config.h"

#if defined(OS_WIN)
#include <windows.h>
#endif

#define PARTITION_EXTRAS_REQUIRED \
  (DCHECK_IS_ON() || BUILDFLAG(USE_BACKUP_REF_PTR))

namespace base {

namespace internal {
// This is a `memset` that resists being optimized away. Adapted from
// boringssl/src/crypto/mem.c. (Copying and pasting is bad, but //base can't
// depend on //third_party, and this is small enough.)
ALWAYS_INLINE void SecureZero(void* p, size_t size) {
#if defined(OS_WIN)
  SecureZeroMemory(p, size);
#else
  memset(p, 0, size);

  // As best as we can tell, this is sufficient to break any optimisations that
  // might try to eliminate "superfluous" memsets. If there's an easy way to
  // detect memset_s, it would be better to use that.
  __asm__ __volatile__("" : : "r"(p) : "memory");
#endif
}

// Returns true if we've hit the end of a random-length period. We don't want to
// invoke `RandomValue` too often, because we call this function in a hot spot
// (`Free`), and `RandomValue` incurs the cost of atomics.
#if !DCHECK_IS_ON()
ALWAYS_INLINE bool RandomPeriod() {
  static thread_local uint8_t counter = 0;
  if (UNLIKELY(counter == 0)) {
    // It's OK to truncate this value.
    counter = static_cast<uint8_t>(base::RandomValue());
  }
  // If `counter` is 0, this will wrap. That is intentional and OK.
  counter--;
  return counter == 0;
}
#endif

}  // namespace internal

}  // namespace base

#endif  // BASE_ALLOCATOR_PARTITION_ALLOCATOR_PARTITION_ALLOC_INL_H_
