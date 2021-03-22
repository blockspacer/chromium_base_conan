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
#pragma once

#include "basic/macros.h"
#include "basic/compiler_specific.h"

#include <base/logging.h>
#include <base/atomicops.h>
#include <base/threading/thread_local.h>
#include <base/threading/platform_thread.h>
#include <base/lazy_instance.h>
#include <base/compiler_specific.h>

#include <atomic>
#include <map>
#include <memory>
#include <string>
#include <vector>

#ifndef ARCH_CPU_64_BITS
#error "ARCH NOT SUPPORTED"
#endif // ARCH_CPU_64_BITS

namespace basic {

class Concurrent64;

namespace concurrent64 {
namespace internal {

struct HashCode {
 public:
  HashCode();
  uint64_t code_;
};

#define ATOMIC_INT_SIZE sizeof(base::subtle::Atomic64)
// Padded POD container for Atomic64. This prevents false sharing of cache lines.
class Cell {
 public:
  Cell();
  inline bool CompareAndSet(int64_t cmp, int64_t value) {
    return base::subtle::NoBarrier_CompareAndSwap(&value_, cmp, value) == cmp;
  }

  // Padding advice from Herb Sutter:
  // http://www.drdobbs.com/parallel/eliminate-false-sharing/217500206?pgno=4
  base::subtle::Atomic64 value_;

  // Padding is a strategy to reduce CPU cache contention by trying
  // to make sure that different cells do not land in the same cache line.
  // It has been found to bring significant performance improvements.
  // http://jsr166-concurrency.10961.n7.nabble.com/Thoughts-about-LongAdder-td1631.html
  char pad[BASE_CACHELINE_SIZE > ATOMIC_INT_SIZE ?
           BASE_CACHELINE_SIZE - ATOMIC_INT_SIZE : 1];

  DISALLOW_COPY_AND_ASSIGN(Cell);
} BASE_CACHELINE_ALIGNED;
#undef ATOMIC_INT_SIZE

} // namespace internal
} // namespace concurrent64

// The basic concept of a Striped64 is that it holds a hash table of Cells
// (think of each Cell as an AtomicLong).
// When two threads try to add something to a LongAdder – which is a Striped64
// – then there is a good chance that the threads will try to add their value to different Cells
// in that hash table. This reduces the contention to a near minimum.
//
// This set of classes is heavily derived from JSR166e, released into the public domain
// by Doug Lea and the other authors.
//
// See: http://gee.cs.oswego.edu/cgi-bin/viewcvs.cgi/jsr166/src/jsr166e/Striped64.java?view=co
// See: http://gee.cs.oswego.edu/cgi-bin/viewcvs.cgi/jsr166/src/jsr166e/LongAdder.java?view=co
// See: https://docs.microsoft.com/ru-ru/dotnet/api/java.util.concurrent.atomic.striped64?view=xamarin-android-sdk-9
//
// The Concurrent64 (aka Striped64) and LongAdder implementations here are simplified versions of what's present in
// JSR166e. However, the core ideas remain the same.
//
// Updating a single AtomicInteger in a multi-threaded environment can be quite slow:
//
//   1. False sharing of cache lines with other counters.
//   2. Cache line bouncing from high update rates, especially with many cores.
//
// These two problems are addressed by Striped64. When there is no contention,
// it uses CAS (compare and swap) on a single base counter to store updates.
// However, when Striped64 detects contention
// (via a failed CAS operation), it will allocate a small, fixed size hashtable of Cells.
// A Cell is a simple POD that pads out an AtomicInt to 64 bytes to prevent
// sharing a cache line.
//
// Reading the value of a Striped64 requires traversing the hashtable to calculate the true sum.
//
// Each updating thread uses a thread-local hashcode to determine its Cell in the hashtable.
// If a thread fails to CAS its hashed Cell, it will do a lightweight rehash operation to try
// and find an uncontended bucket. Because the hashcode is thread-local, this rehash affects all
// Striped64's accessed by the thread. This is good, since contention on one Striped64 is
// indicative of contention elsewhere too.
//
// The hashtable is statically sized to the nearest power of 2 greater than or equal to the
// number of CPUs. This is sufficient, since this guarantees the existence of a perfect hash
// function. Due to the random rehashing, the threads should eventually converge to this function.
// In practice, this scheme has shown to be sufficient.
//
// The biggest simplification of this implementation compared to JSR166e is that we do not
// dynamically grow the table, instead immediately allocating it to the full size.
// We also do not lazily allocate each Cell, instead allocating the entire array at once.
// This means we waste some additional memory in low contention scenarios, and initial allocation
// will also be slower. Some of the micro-optimizations were also elided for readability.
// See http://gee.cs.oswego.edu/cgi-bin/viewcvs.cgi/jsr166/src/jsr166e/LongAdder.java
class Concurrent64 {
 public:
  Concurrent64();
  virtual ~Concurrent64();

  // Class holds common representation and mechanics for classes supporting dynamic striping on 64bit values.
  //
  // Class maintains a lazily-initialized table of atomically updated variables, plus an extra base field.
  // The table size is a power of two. Indexing uses masked per-thread hash codes.
  // Nearly all methods on this class are private, accessed directly by subclasses.
  //
  // Table entries are of class Cell;
  // a variant of AtomicLong padded to reduce cache contention on most processors.
  // Padding is overkill for most Atomics because they are usually irregularly scattered in memory
  // and thus don't interfere much with each other.
  // But Atomic objects residing in arrays will tend to be placed adjacent to each other,
  // and so will most often share cache lines (with a huge negative performance impact) without this precaution.
  //
  // In part because +Cell+s are relatively large, we avoid creating them until they are needed.
  // When there is no contention, all updates are made to the base field.
  // Upon first contention (a failed CAS on base update), the table is initialized to size 2.
  // The table size is doubled upon further contention until reaching the nearest power of two greater than or equal to the number of CPUS.
  // Table slots remain empty (nil) until they are needed.
  //
  // A single spinlock (busy) is used for initializing and resizing the table, as well as populating slots with new +Cell+s.
  // There is no need for a blocking lock: When the lock is not available, threads try other slots (or the base).
  // During these retries, there is increased contention and reduced locality, which is still better than alternatives.
  //
  // Per-thread hash codes are initialized to random values.
  // Contention and/or table collisions are indicated by failed CASes when performing an update operation (see method retry_update).
  // Upon a collision, if the table size is less than the capacity, it is doubled in size unless some other thread holds the lock.
  // If a hashed slot is empty, and lock is available, a new Cell is created.
  // Otherwise, if the slot exists, a CAS is tried.
  // Retries proceed by "double hashing", using a secondary hash (XorShift) to try to find a free slot.
  //
  // The table size is capped because, when there are more threads than CPUs, supposing that each thread were bound to a CPU,
  // there would exist a perfect hash function mapping threads to slots that eliminates collisions. When we reach capacity,
  // we search for this mapping by randomly varying the hash codes of colliding threads.
  // Because search is random, and collisions only become known via CAS failures,
  // convergence can be slow, and because threads are typically not bound to CPUS forever,
  // may not occur at all. However, despite these limitations, observed contention rates are typically low in these cases.
  //
  // It is possible for a Cell to become unused when threads that once hashed to it terminate,
  // as well as in the case where doubling the table causes no thread to hash to it under expanded mask.
  // We do not try to detect or remove such cells, under the assumption that for long-running instances,
  // observed contention levels will recur, so the cells will eventually be needed again;
  // and for short-lived ones, it does not matter.
  //
 protected:

  enum Rehash {
    kRehash,
    kNoRehash
  };

  // CAS (compare and swap) the base field.
  // CAS operations are a fast and thread safe way to update the value of a variable and get feedback
  // on whether the operation was successful or whether there was contention.
  bool CasBase(int64_t cmp, int64_t val) { return base_.CompareAndSet(cmp, val); }

  // CAS the busy field from 0 to 1 to acquire the lock.
  bool CasBusy() {
    return base::subtle::NoBarrier_CompareAndSwap(&busy_, 0, 1) == 0;
  }

  // Computes the function of the current and new value. Used in RetryUpdate.
  virtual int64_t Fn(int64_t current_value, int64_t new_value) = 0;

  // Handles cases of updates involving initialization, resizing, creating new Cells, and/or
  // contention. See above for further explanation.
  void RetryUpdate(int64_t x, Rehash to_rehash);

  // Sets base and all cells to the given value.
  void InternalReset(int64_t initialValue);

  // Base value, used mainly when there is no contention, but also as a fallback during
  // table initialization races. Updated via CAS.
  concurrent64::internal::Cell base_;

  // CAS lock used when resizing and/or creating cells.
  base::subtle::Atomic32 busy_;

  // Backing buffer for cells_, used for alignment.
  void* cell_buffer_;

  // Table of cells. When non-null, size is the nearest power of 2 >= NCPU.
  concurrent64::internal::Cell* cells_;
  int32_t num_cells_;

  // Static hash code per-thread. Shared across all instances to limit thread-local pollution.
  // Also, if a thread hits a collision on one Concurrent64, it's also likely to collide on
  // other Concurrent64-s too.
  static base::LazyInstance<
    base::ThreadLocalOwnedPointer<concurrent64::internal::HashCode>
  >::Leaky hashcode_;

 private:

  // Number of CPUs, to place bound on table size.
  static const uint32_t kNumCpus;

};

// The idea of LongAdder is to avoid contention by making each thread work on a different variable.
//
// A 64-bit number optimized for high-volume concurrent updates.
// See Concurrent64 for a longer explanation of the inner workings.
// See: http://gee.cs.oswego.edu/cgi-bin/viewcvs.cgi/jsr166/src/jsr166e/LongAdder.java?view=co
// See: https://docs.oracle.com/javase/8/docs/api/java/util/concurrent/atomic/LongAdder.html
class Concurrent64LongAdder : Concurrent64 {
 public:
  Concurrent64LongAdder() {}
  void IncrementBy(int64_t x);
  void Increment() { IncrementBy(1); }
  void Decrement() { IncrementBy(-1); }
  void DecrementBy(int64_t x) { IncrementBy(x); }

  // Returns the current value.
  // Note this is not an atomic snapshot in the presence of concurrent updates.
  int64_t Value() const;

  // Resets the counter state to zero.
  void Reset() { InternalReset(0); }

 private:
  int64_t Fn(int64_t current_value, int64_t new_value) override {
    return current_value + new_value;
  }

  DISALLOW_COPY_AND_ASSIGN(Concurrent64LongAdder);
};

} // namespace basic
