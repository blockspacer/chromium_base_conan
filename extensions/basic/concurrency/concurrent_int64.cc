// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
// The following only applies to changes made to this file as part of YugaByte development.
//
// Portions Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//
#include "basic/concurrency/concurrent_int64.h" // IWYU pragma: associated
#include "basic/rvalue_cast.h"

#include <base/rand_util.h>
#include <base/macros.h>
#include <base/logging.h>
#include <base/location.h>
#include <base/sequenced_task_runner.h>
#include <base/threading/thread_local_storage.h>
#include <base/threading/sequence_local_storage_slot.h>
#include <base/threading/thread_checker.h>
#include <base/memory/weak_ptr.h>
#include <base/memory/ref_counted.h>
#include <base/memory/scoped_refptr.h>
#include <base/system/sys_info.h>

#include <vector>
#include <string>
#include <atomic>

#if defined(COMPILER_MSVC)
#include <malloc.h>
#else
#include <stdlib.h>
#endif

#if defined(OS_ANDROID)
#include <malloc.h>
#endif

using basic::concurrent64::internal::HashCode;
using basic::concurrent64::internal::Cell;

namespace basic {

namespace concurrent64 {
namespace internal {
//
// HashCode
//

HashCode::HashCode() {
  const uint64_t hash = base::RandUint64();
  code_ = (hash == 0) ? 1 : hash;  // Avoid zero to allow xorShift rehash
}

//
// Cell
//

Cell::Cell()
    : value_(0) {
}
} // namespace internal
} // namespace concurrent64

//
// Concurrent64
//
const uint32_t Concurrent64::kNumCpus = base::SysInfo::NumberOfProcessors();

// static
base::LazyInstance<
  base::ThreadLocalOwnedPointer<concurrent64::internal::HashCode>
>::Leaky Concurrent64::hashcode_ = LAZY_INSTANCE_INITIALIZER;

Concurrent64::Concurrent64()
    : busy_(0),
      cell_buffer_(nullptr),
      cells_(nullptr),
      num_cells_(0) {
}

Concurrent64::~Concurrent64() {
  // Cell is a POD, so no need to destruct each one.
  free(cell_buffer_);
}

void Concurrent64::RetryUpdate(int64_t x, Rehash contention) {
  DCHECK(hashcode_.Pointer()->Get());
  uint64_t h = hashcode_.Pointer()->Get()->code_;
  // There are three operations in this loop.
  //
  // 1. Try to add to the Cell hash table entry for the thread if the table exists.
  //    When there's contention, rehash to try a different Cell.
  // 2. Try to initialize the hash table.
  // 3. Try to update the base counter.
  //
  // These are predicated on successful CAS operations, which is why it's all wrapped in an
  // infinite retry loop.
  while (true) {
    int32_t n = base::subtle::Acquire_Load(&num_cells_);
    if (n > 0) {
      if (contention == kRehash) {
        // CAS failed already, rehash before trying to increment.
        contention = kNoRehash;
      } else {
        Cell *cell = &(cells_[(n - 1) & h]);
        int64_t v = base::subtle::NoBarrier_Load(&cell->value_);
        if (cell->CompareAndSet(v, Fn(v, x))) {
          // Successfully CAS'd the corresponding cell, done.
          break;
        }
      }
      // Rehash since we failed to CAS, either previously or just now.
      h ^= h << 13;
      h ^= h >> 17;
      h ^= h << 5;
    } else if (n == 0 && CasBusy()) {
      // We think table hasn't been initialized yet, try to do so.
      // Recheck preconditions, someone else might have init'd in the meantime.
      n = base::subtle::Acquire_Load(&num_cells_);
      if (n == 0) {
        n = 1;
        // Calculate the size. Nearest power of two >= NCPU.
        // Also handle a negative NCPU, can happen if sysconf name is unknown
        while (kNumCpus > n) {
          n <<= 1;
        }

#if defined(COMPILER_MSVC)
        cell_buffer_ = _aligned_malloc(sizeof(Cell)*n, BASE_CACHELINE_SIZE);
// Android technically supports posix_memalign(), but does not expose it in
// the current version of the library headers used by Chrome.  Luckily,
// memalign() on Android returns pointers which can safely be used with
// free(), so we can use it instead.  Issue filed to document this:
// http://code.google.com/p/android/issues/detail?id=35391
#elif defined(OS_ANDROID)
        cell_buffer_ = memalign(BASE_CACHELINE_SIZE, sizeof(Cell)*n);
#else
        if (int ret = posix_memalign(&cell_buffer_, BASE_CACHELINE_SIZE, sizeof(Cell)*n)) {
          DLOG(ERROR) << "posix_memalign() returned with error " << ret;
          cell_buffer_ = nullptr;
        }
#endif

        // Initialize the table
        cells_ = new (cell_buffer_) Cell[n];
        base::subtle::Release_Store(&num_cells_, n);
      }
      // End critical section
      base::subtle::NoBarrier_Store(&busy_, 0);
    } else {
      // Fallback to adding to the base value.
      // Means the table wasn't initialized or we failed to init it.
      int64_t v = base::subtle::NoBarrier_Load(&base_.value_);
      if (CasBase(v, Fn(v, x))) {
        break;
      }
    }
  }
  // Record index for next time
  hashcode_.Pointer()->Get()->code_ = h;
}

void Concurrent64::InternalReset(int64_t initialValue) {
  const int32_t n = base::subtle::Acquire_Load(&num_cells_);
  base::subtle::NoBarrier_Store(&base_.value_, initialValue);
  for (int i = 0; i < n; i++) {
    base::subtle::NoBarrier_Store(&cells_[i].value_, initialValue);
  }
}

void Concurrent64LongAdder::IncrementBy(int64_t x) {
  {
    auto hashcode = std::make_unique<concurrent64::internal::HashCode>();
    hashcode_.Pointer()->Set(std::move(hashcode));
  }

  // Use hash table if present. If that fails, call RetryUpdate to rehash and retry.
  // If no hash table, try to CAS the base counter. If that fails, RetryUpdate to init the table.
  const int32_t n = base::subtle::Acquire_Load(&num_cells_);
  if (n > 0) {
    Cell *cell = &(cells_[(n - 1) & hashcode_.Pointer()->Get()->code_]);
    DCHECK_EQ(0, reinterpret_cast<const uintptr_t>(cell) & (sizeof(Cell) - 1))
        << " unaligned Cell not allowed for Concurrent64";
    const int64_t old = base::subtle::NoBarrier_Load(&cell->value_);
    if (!cell->CompareAndSet(old, old + x)) {
      // When we hit a hash table contention, signal RetryUpdate to rehash.
      RetryUpdate(x, kRehash);
    }
  } else {
    int64_t b = base::subtle::Acquire_Load(&base_.value_);
    if (!base_.CompareAndSet(b, b + x)) {
      // Attempt to initialize the table. No need to rehash since the contention was for the
      // base counter, not the hash table.
      RetryUpdate(x, kNoRehash);
    }
  }
}

//
// LongAdder
//

int64_t Concurrent64LongAdder::Value() const {
  int64_t sum = base::subtle::NoBarrier_Load(&base_.value_);
  const int32_t n = base::subtle::Acquire_Load(&num_cells_);
  for (int i = 0; i < n; i++) {
    sum += base::subtle::Acquire_Load(&cells_[i].value_);
  }
  return sum;
}

} // namespace basic
