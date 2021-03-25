#pragma once

#include <base/logging.h>
#include <base/macros.h>
#include <base/check.h>
#include <base/threading/thread_collision_warner.h>

#include <cassert>
#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <functional>

namespace basic {

/**
 * CxxAllocatorAdaptor
 *
 * A type conforming to C++ concept Allocator, delegating operations to an
 * unowned Inner which has this required interface:
 *
 *   void* allocate(std::size_t)
 *   void deallocate(void*, std::size_t)
 *
 * Note that Inner is *not* a C++ Allocator.
 */
template <typename T, class Inner, bool FallbackToStdAlloc = false>
class CxxAllocatorAdaptor : private std::allocator<T> {
 private:
  using Self = CxxAllocatorAdaptor<T, Inner, FallbackToStdAlloc>;

  template <typename U, typename UInner, bool UFallback>
  friend class CxxAllocatorAdaptor;

  Inner* inner_ = nullptr;

 public:
  using value_type = T;

  using propagate_on_container_copy_assignment = std::true_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;

  template <bool X = FallbackToStdAlloc, std::enable_if_t<X, int> = 0>
  constexpr explicit CxxAllocatorAdaptor() {}

  constexpr explicit CxxAllocatorAdaptor(Inner& ref) : inner_(&ref) {}

  constexpr CxxAllocatorAdaptor(CxxAllocatorAdaptor const&) = default;

  template <typename U, std::enable_if_t<!std::is_same<U, T>::value, int> = 0>
  constexpr CxxAllocatorAdaptor(
      CxxAllocatorAdaptor<U, Inner, FallbackToStdAlloc> const& other)
      : inner_(other.inner_) {}

  T* allocate(std::size_t n) {
    if (FallbackToStdAlloc && inner_ == nullptr) {
      return std::allocator<T>::allocate(n);
    }
    return static_cast<T*>(inner_->allocate(sizeof(T) * n));
  }

  void deallocate(T* p, std::size_t n) {
    if (inner_ != nullptr) {
      inner_->deallocate(p, sizeof(T) * n);
    } else {
      assert(FallbackToStdAlloc);
      std::allocator<T>::deallocate(p, n);
    }
  }

  friend bool operator==(Self const& a, Self const& b) noexcept {
    return a.inner_ == b.inner_;
  }
  friend bool operator!=(Self const& a, Self const& b) noexcept {
    return a.inner_ != b.inner_;
  }

  template <typename U>
  struct rebind {
    using other = CxxAllocatorAdaptor<U, Inner, FallbackToStdAlloc>;
  };
};

}  // namespace basic
