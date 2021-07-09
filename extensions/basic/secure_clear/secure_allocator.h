// Copyright 2018 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <openssl/crypto.h>

#include <base/callback_helpers.h>
#include <base/check.h>
#include <base/check_op.h>
#include <base/logging.h>

#include <basic/secure_clear/secure_string.h>

#include <basic/portability/sysmman.h>
#include <basic/portability/unistd.h>
#include <basic/portability/portability.h>
#include <basic/portability/utility.h>

#include <errno.h>

#include <limits>
#include <memory>

namespace basic {

// SecureAllocator is a stateless derivation of std::allocator that clears
// the contents of the object on deallocation. Additionally, to prevent the
// memory from being leaked, we use the following defensive mechanisms:
//
// 1. Use page-aligned memory so that it can be locked (therefore, use mmap()
//    instead of malloc()). Note that mlock()s are not inherited over fork(),
//
// 2. Always allocate memory in multiples of pages: this adds a memory overhead
//    of ~1 page for each object. Moreover, the extra memory is not available
//    for the allocated object to expand into: the container expects that the
//    memory allocated to it matches the size set in reserve().
// TODO(sarthakkukreti): Figure out if it is possible to propagate the real
// capacity to the container without an intrusive change to the STL.
// [Example: allow __recommend() override in allocators for containers.]
//
// 3. Mark the memory segments as undumpable, unmergeable.
//
// 4. Use MADV_WIPEONFORK:
//    this results in a new anonymous vma instead of copying over the contents
//    of the secure object after a fork(). By default [MADV_DOFORK], the vma is
//    marked as copy-on-write, and the first process which writes to the secure
//    object after fork get a new copy. This may break the security guarantees
//    setup above. Another alternative is to use MADV_DONTFORK which results in
//    the memory mapping not getting copied over to child process at all: this
//    may result in cases where if the child process gets segmentation faults
//    on attempts to access virtual addresses in the secure object's address
//    range,
//
//    With MADV_WIPEONFORK, the child processes can access the secure object
//    memory safely, but the contents of the secure object appear as zero to
//    the child process. Note that threads share the virtual address space and
//    secure objects would be transparent across threads.
// TODO(sarthakkukreti): Figure out patterns to pass secure data over fork().

template <typename T>
class BASE_EXPORT SecureAllocator {
 public:
  using pointer = typename std::allocator<T>::pointer;
  using size_type = typename std::allocator<T>::size_type;
  using value_type = typename std::allocator<T>::value_type;

  // Allocators are equal if they are stateless. i.e., one allocator can
  // deallocate objects created by another allocator.
  // See https://en.cppreference.com/w/cpp/memory/allocator/operator_cmp and
  // https://en.cppreference.com/w/cpp/named_req/Allocator.
  using is_always_equal = std::true_type;

  // Constructors that wrap over std::allocator.
  // Makes sure that the allocator's static members are only allocated once.
  SecureAllocator() noexcept = default;

  SecureAllocator(const SecureAllocator& other) noexcept = default;

  template <class U>
  SecureAllocator(const SecureAllocator<U>& other) noexcept {}

  template <typename U>
  struct rebind {
    typedef SecureAllocator<U> other;
  };

  // Returns cached max_size.
  size_type max_size() const { return max_size_; }

  // Allocation: allocates ceil(size/pagesize) for holding the data.
  pointer allocate(size_type n, pointer hint = nullptr) {
    pointer buffer = nullptr;
    // Check if n can be theoretically allocated.
    CHECK_LT(n, max_size());
    // std::allocator is expected to throw a std::bad_alloc on failing to
    // allocate the memory correctly. Instead of returning a nullptr, which
    // confuses the standard template library, use CHECK(false) to crash on
    // the failure path.
    base::ScopedClosureRunner fail_on_allocation_error(base::Bind([]() {
      PLOG(ERROR) << "Failed to allocate secure memory";
      CHECK(false);
    }));
    // Check if n = 0: there's nothing to allocate;
    if (n == 0)
      return nullptr;
    // Calculate the page-aligned buffer size.
    size_type buffer_size = CalculatePageAlignedBufferSize(n);
    // Memory locking granularity is per-page: mmap ceil(size/page size) pages.
    buffer = reinterpret_cast<pointer>(
        mmap(nullptr, buffer_size, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
    if (buffer == MAP_FAILED)
      return nullptr;
    // Lock buffer into physical memory.
    if (mlock(buffer, buffer_size)) {
      CHECK_NE(errno, ENOMEM) << "It is likely that SecureAllocator has "
                                 "exceeded the RLIMIT_MEMLOCK limit";
      return nullptr;
    }
    // Mark memory as non dumpable in a core dump.
    if (madvise(buffer, buffer_size, MADV_DONTDUMP))
      return nullptr;
    // Mark memory as non mergeable with another page, even if the contents
    // are the same.
    if (madvise(buffer, buffer_size, MADV_UNMERGEABLE)) {
      // MADV_UNMERGEABLE is only available if the kernel has been configured
      // with CONFIG_KSM set. If the CONFIG_KSM flag has not been set, then
      // pages are not mergeable so this madvise option is not necessary.
      //
      // In the case where CONFIG_KSM is not set, EINVAL is the error set.
      // Since this error value is expected in some cases, we don't return a
      // nullptr.
      if (errno != EINVAL)
        return nullptr;
    }
    // Make this mapping available to child processes but don't copy data from
    // the secure object's pages during fork. With MADV_DONTFORK, the
    // vma is not mapped in the child process which leads to segmentation
    // faults if the child process tries to access this address. For example,
    // if the parent process creates a SecureObject, forks() and the child
    // process tries to call the destructor at the virtual address.
    if (madvise(buffer, buffer_size, MADV_WIPEONFORK))
      return nullptr;
    ignore_result(fail_on_allocation_error.Release());
    // Allocation was successful.
    return buffer;
  }

  // Destroys object before deallocation.
  // After destroying the object, clears the contents of where the object was
  // stored.
  template <class U>
  void destroy(U* p) {
    // Return if the pointer is invalid.
    if (!p)
      return;
    p->~U();
    clear_contents(p, sizeof(U));
  }

  void deallocate(pointer p, size_type n) {
    // Check if n can be theoretically deallocated.
    CHECK_LT(n, max_size());
    // Check if n = 0 or p is a nullptr: there's nothing to deallocate;
    if (n == 0 || !p)
      return;
    // Calculate the page-aligned buffer size.
    size_type buffer_size = CalculatePageAlignedBufferSize(n);
    clear_contents(p, buffer_size);
    munlock(p, buffer_size);
    munmap(p, buffer_size);
  }

 protected:
  // Zero-out all bytes in the allocated buffer.
  virtual void clear_contents(pointer v, size_type n) {
    if (!v)
      return;
    // This is guaranteed not to be optimized out.
    SecureClearBytes(v, n);
  }

 private:
  // Calculates the page-aligned buffer size.
  size_t CalculatePageAlignedBufferSize(size_type n) {
    size_type real_size = n * sizeof(value_type);
    size_type page_aligned_remainder = real_size % page_size_;
    size_type padding =
        page_aligned_remainder != 0 ? page_size_ - page_aligned_remainder : 0;
    return real_size + padding;
  }

  static size_t CalculatePageSize() {
    long ret = sysconf(_SC_PAGESIZE);  // NOLINT [runtime/int]
    // Initialize page size.
    CHECK_GT(ret, 0L);
    return ret;
  }

  // Since the allocator reuses page size and max size consistently,
  // cache these values initially and reuse.
  static size_t GetMaxSizeForType(size_t page_size) {
    // Initialize max size that can be theoretically allocated.
    // Calculate the max size that is page-aligned.
    size_t max_theoretical_size = std::numeric_limits<size_type>::max();
    size_t max_page_aligned_size =
        max_theoretical_size - (max_theoretical_size % page_size);
    return max_page_aligned_size / sizeof(value_type);
  }

  // Page size on system.
  static inline const size_type page_size_ = CalculatePageSize();

  // Max theoretical count for type on system.
  static inline const size_type max_size_ = GetMaxSizeForType(page_size_);
};

// Allocators are equal if they are stateless. i.e., one allocator can
// deallocate objects created by another allocator.
// See https://en.cppreference.com/w/cpp/memory/allocator/operator_cmp.
// TODO(https://issuetracker.google.com/173431121): It seems like this should be
// removed with C++17's std::allocator_traits::is_always_equal trait, but it
// is still used by std::vector:
// https://github.com/llvm/llvm-project/blob/67fa016ac1e24cd0f32a43d6d2ed43e347f1e74b/libcxx/include/vector#L1370
template <class T, class U>
bool operator==(const SecureAllocator<T>&, const SecureAllocator<U>&) noexcept {
  return true;
}

template <class T, class U>
bool operator!=(const SecureAllocator<T>& x,
                const SecureAllocator<U>& y) noexcept {
  return !(x == y);
}

}  // namespace basic
