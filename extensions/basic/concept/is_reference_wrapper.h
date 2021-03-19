#pragma once

#include <type_traits>

namespace basic {

template <class T>
struct is_reference_wrapper
  : std::false_type {};

template <class U>
struct is_reference_wrapper<std::reference_wrapper<U> >
  : std::true_type {};

}  // namespace basic
