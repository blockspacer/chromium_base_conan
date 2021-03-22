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
 * distributed under the License is distributed on an "AS IS" basic,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <atomic>
#include <cassert>
#include <cstdlib>
#include <memory>
#include <type_traits>
#include <utility>
#include <cstddef>
#include <cstdint>

#ifndef FOLLY_ARM
#if defined(__arm__)
#define FOLLY_ARM 1
#else
#define FOLLY_ARM 0
#endif
#endif // FOLLY_ARM

#if !defined(FOLLY_MOBILE)
#if defined(__ANDROID__) || \
    (defined(__APPLE__) &&  \
     (TARGET_IPHONE_SIMULATOR || TARGET_OS_SIMULATOR || TARGET_OS_IPHONE))
#define FOLLY_MOBILE 1
#else
#define FOLLY_MOBILE 0
#endif
#endif // FOLLY_MOBILE

#if defined(__linux__) && !FOLLY_MOBILE
constexpr auto kIsLinux = true;
#else
constexpr auto kIsLinux = false;
#endif

#if __cpp_exceptions
#include <exception>
#include <stdexcept>
# define __try      try
# define __catch(X) catch(X)
# define __throw_exception_again throw
#else
# define __try      if (true)
# define __catch(X) if (false)
# define __throw_exception_again
#endif

namespace basic {

constexpr bool kIsArchArm = FOLLY_ARM == 1;

//  has_extended_alignment
//
//  True if it may be presumed that the platform has static extended alignment;
//  false if it may not be so presumed, even when the platform might actually
//  have it. Static extended alignment refers to extended alignment of objects
//  with automatic, static, or thread storage. Whether the there is support for
//  dynamic extended alignment is a property of the allocator which is used for
//  each given dynamic allocation.
//
//  Currently, very heuristical - only non-mobile 64-bit linux gets the extended
//  alignment treatment. Theoretically, this could be tuned better.
constexpr bool has_extended_alignment =
    kIsLinux && sizeof(void*) >= sizeof(std::uint64_t);

namespace detail {

// Implemented this way because of a bug in Clang for ARMv7, which gives the
// wrong result for `alignof` a `union` with a field of each scalar type.
template <typename... Ts>
struct max_align_t_ {
  static constexpr std::size_t value() {
    std::size_t const values[] = {0u, alignof(Ts)...};
    std::size_t r = 0u;
    for (auto const v : values) {
      r = r < v ? v : r;
    }
    return r;
  }
};
using max_align_v_ = max_align_t_<
    long double,
    double,
    float,
    long long int,
    long int,
    int,
    short int,
    bool,
    char,
    char16_t,
    char32_t,
    wchar_t,
    void*,
    std::max_align_t>;

} // namespace detail

// max_align_v is the alignment of max_align_t.
//
// max_align_t is a type which is aligned at least as strictly as the
// most-aligned basic type (see the specification of std::max_align_t). This
// implementation exists because 32-bit iOS platforms have a broken
// std::max_align_t (see below).
//
// You should refer to this as `::folly::max_align_t` in portable code, even if
// you have `using namespace folly;` because C11 defines a global namespace
// `max_align_t` type.
//
// To be certain, we consider every non-void fundamental type specified by the
// standard. On most platforms `long double` would be enough, but iOS 32-bit
// has an 8-byte aligned `double` and `long long int` and a 4-byte aligned
// `long double`.
//
// So far we've covered locals and other non-allocated storage, but we also need
// confidence that allocated storage from `malloc`, `new`, etc will also be
// suitable for objects with this alignment requirement.
//
// Apple document that their implementation of malloc will issue 16-byte
// granularity chunks for small allocations (large allocations are page-size
// granularity and page-aligned). We think that allocated storage will be
// suitable for these objects based on the following assumptions:
//
// 1. 16-byte granularity also means 16-byte aligned.
// 2. `new` and other allocators follow the `malloc` rules.
//
// We also have some anecdotal evidence: we don't see lots of misaligned-storage
// crashes on 32-bit iOS apps that use `double`.
//
// Apple's allocation reference: http://bit.ly/malloc-small
constexpr std::size_t max_align_v = detail::max_align_v_::value();
struct alignas(max_align_v) max_align_t {};

//  Memory locations within the same cache line are subject to destructive
//  interference, also known as false sharing, which is when concurrent
//  accesses to these different memory locations from different cores, where at
//  least one of the concurrent accesses is or involves a store operation,
//  induce contention and harm performance.
//
//  Microbenchmarks indicate that pairs of cache lines also see destructive
//  interference under heavy use of atomic operations, as observed for atomic
//  increment on Sandy Bridge.
//
//  We assume a cache line size of 64, so we use a cache line pair size of 128
//  to avoid destructive interference.
//
//  mimic: std::hardware_destructive_interference_size, C++17
constexpr std::size_t hardware_destructive_interference_size =
    kIsArchArm ? 64 : 128;
static_assert(hardware_destructive_interference_size >= max_align_v, "math?");

//  Memory locations within the same cache line are subject to constructive
//  interference, also known as true sharing, which is when accesses to some
//  memory locations induce all memory locations within the same cache line to
//  be cached, benefiting subsequent accesses to different memory locations
//  within the same cache line and heping performance.
//
//  mimic: std::hardware_constructive_interference_size, C++17
constexpr std::size_t hardware_constructive_interference_size = 64;
static_assert(hardware_constructive_interference_size >= max_align_v, "math?");

//  A value corresponding to hardware_constructive_interference_size but which
//  may be used with alignas, since hardware_constructive_interference_size may
//  be too large on some platforms to be used with alignas.
constexpr std::size_t cacheline_align_v = has_extended_alignment
    ? hardware_constructive_interference_size
    : max_align_v;
struct alignas(cacheline_align_v) cacheline_align_t {};

/*
 * LockFreeProducerConsumerQueue is a one producer and one consumer queue
 * without locks.
 */
template <class T>
struct LockFreeProducerConsumerQueue {
  typedef T value_type;

  LockFreeProducerConsumerQueue(const LockFreeProducerConsumerQueue&) = delete;
  LockFreeProducerConsumerQueue& operator=(const LockFreeProducerConsumerQueue&) = delete;

  // size must be >= 2.
  //
  // Also, note that the number of usable slots in the queue at any
  // given time is actually (size-1), so if you start with an empty queue,
  // isFull() will return true after size-1 insertions.
  explicit LockFreeProducerConsumerQueue(uint32_t size)
      : size_(size),
        records_(static_cast<T*>(std::malloc(sizeof(T) * size))),
        readIndex_(0),
        writeIndex_(0) {
    assert(size >= 2);
    if (!records_) {
#if __cpp_exceptions
      throw std::bad_alloc();
#else
      assert(false);
#endif
    }
  }

  ~LockFreeProducerConsumerQueue() {
    // We need to destruct anything that may still exist in our queue.
    // (No real synchronization needed at destructor time: only one
    // thread can be doing this.)
    if (!std::is_trivially_destructible<T>::value) {
      size_t readIndex = readIndex_;
      size_t endIndex = writeIndex_;
      while (readIndex != endIndex) {
        records_[readIndex].~T();
        if (++readIndex == size_) {
          readIndex = 0;
        }
      }
    }

    std::free(records_);
  }

  template <class... Args>
  bool write(Args&&... recordArgs) {
    auto const currentWrite = writeIndex_.load(std::memory_order_relaxed);
    auto nextRecord = currentWrite + 1;
    if (nextRecord == size_) {
      nextRecord = 0;
    }
    if (nextRecord != readIndex_.load(std::memory_order_acquire)) {
      new (&records_[currentWrite]) T(std::forward(recordArgs)...);
      writeIndex_.store(nextRecord, std::memory_order_release);
      return true;
    }

    // queue is full
    return false;
  }

  // move (or copy) the value at the front of the queue to given variable
  bool read(T& record) {
    auto const currentRead = readIndex_.load(std::memory_order_relaxed);
    if (currentRead == writeIndex_.load(std::memory_order_acquire)) {
      // queue is empty
      return false;
    }

    auto nextRecord = currentRead + 1;
    if (nextRecord == size_) {
      nextRecord = 0;
    }
    record = std::move(records_[currentRead]);
    records_[currentRead].~T();
    readIndex_.store(nextRecord, std::memory_order_release);
    return true;
  }

  // pointer to the value at the front of the queue (for use in-place) or
  // nullptr if empty.
  T* frontPtr() {
    auto const currentRead = readIndex_.load(std::memory_order_relaxed);
    if (currentRead == writeIndex_.load(std::memory_order_acquire)) {
      // queue is empty
      return nullptr;
    }
    return &records_[currentRead];
  }

  // queue must not be empty
  void popFront() {
    auto const currentRead = readIndex_.load(std::memory_order_relaxed);
    assert(currentRead != writeIndex_.load(std::memory_order_acquire));

    auto nextRecord = currentRead + 1;
    if (nextRecord == size_) {
      nextRecord = 0;
    }
    records_[currentRead].~T();
    readIndex_.store(nextRecord, std::memory_order_release);
  }

  bool isEmpty() const {
    return readIndex_.load(std::memory_order_acquire) ==
        writeIndex_.load(std::memory_order_acquire);
  }

  bool isFull() const {
    auto nextRecord = writeIndex_.load(std::memory_order_acquire) + 1;
    if (nextRecord == size_) {
      nextRecord = 0;
    }
    if (nextRecord != readIndex_.load(std::memory_order_acquire)) {
      return false;
    }
    // queue is full
    return true;
  }

  // * If called by consumer, then true size may be more (because producer may
  //   be adding items concurrently).
  // * If called by producer, then true size may be less (because consumer may
  //   be removing items concurrently).
  // * It is undefined to call this from any other thread.
  size_t sizeGuess() const {
    int ret = writeIndex_.load(std::memory_order_acquire) -
        readIndex_.load(std::memory_order_acquire);
    if (ret < 0) {
      ret += size_;
    }
    return ret;
  }

  // maximum number of items in the queue.
  size_t capacity() const {
    return size_ - 1;
  }

 private:
  using AtomicIndex = std::atomic<unsigned int>;

  char pad0_[hardware_destructive_interference_size];
  const uint32_t size_;
  T* const records_;

  alignas(hardware_destructive_interference_size) AtomicIndex readIndex_;
  alignas(hardware_destructive_interference_size) AtomicIndex writeIndex_;

  char pad1_[hardware_destructive_interference_size - sizeof(AtomicIndex)];
};

} // namespace basic
