#pragma once

#include "base/base_export.h"

#include <memory>

namespace base {

// Thanks Scott M.
// See http://yacoder.guru/blog/2015/05/06/cpp-curiosities-one-does-not-simply-move-a-const-object/
// and https://groups.google.com/a/isocpp.org/forum/#!topic/std-proposals/ArfVLmJJ_Y4
//
// Example:
//
// m_queue.push(std::move(value));
// m_queue.push(rvalue_cast(value));
//
// If push throws, is the value moved-from?
// No. std::move is just an rvalue_cast
// i.e. object will NOT be destroyed if
// the move-assignment never happens.
// To understand why it is actually okay to use x afterward,
// remember that std::move is just a typecast that
// provides an rvalue reference
// that enables use of a move constructor or operator.
// std::move does not actually move anything.
// It could  more accurately be called rvalue_cast.
template <typename T>
constexpr std::remove_reference<T>::type&&
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

}  // namespace base

#endif  // BASE_BIG_ENDIAN_H_
