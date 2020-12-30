#pragma once

#include "base/base_export.h"

#include <memory>

namespace base {

// Thanks Scott Meyers (Effective Modern C++)
// See http://yacoder.guru/blog/2015/05/06/cpp-curiosities-one-does-not-simply-move-a-const-object/
// See https://groups.google.com/a/isocpp.org/forum/#!topic/std-proposals/ArfVLmJJ_Y4
// See `6. std::move() does not move, it casts.` on https://www.chromium.org/rvalue-references
//
// MOTIVATION
//
// Unlike `std::move` can detect attempts to move const values
// (moving of const value fallbacks to copy of const value without any `move`).
//
// EXAMPLE
//
// m_queue.push(rvalue_cast(value));
// // If you can not use rvalue_cast,
// // than add some comments why (i.e. use `COPY_OR_MOVE` etc.)
// m_queue.push(COPY_OR_MOVE(const_value));
//
// If `m_queue.push` throws, is the value moved-from?
// No. std::move is just an rvalue_cast
// i.e. object will NOT be destroyed if
// the move-assignment never happens.
// To understand why it is actually okay to use `x` after `m_queue.push(x)`,
// remember that std::move is just a typecast that
// provides an rvalue reference
// that enables use of a move constructor or operator.
// std::move does not actually move anything.
// It could  more accurately be called rvalue_cast.
template <typename T>
constexpr typename std::remove_reference<T>::type&&
  rvalue_cast(T&& t) noexcept
{
  static_assert(
    !std::is_const<typename std::remove_reference<T>::type>::value
    , "You have attempted a cast to a const rvalue reference. "
    "Make sure you are not trying to move a const object, "
    "as this would likely result in a copy not a move. "
    "If you need it for real, call rvalue_cast(...) instead.");

   return std::move(t);
}

// BEFORE:
// std::forward<Args>(args)...
// std::forward<CallbackT>(task)
//
// AFTER:
// FORWARD(args)...
// FORWARD(task)
//
#define FORWARD(...) \
  static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)

// safe alternative to `std::move()`
#define RVALUE_CAST(x) \
  ::base::rvalue_cast(x)

}  // namespace base
