#pragma once

#include <base/logging.h>

namespace basic {

template<class Out, class In>
inline Out pointer_cast(In* in) {
  void* temp = in;
  return static_cast<Out>(temp);
}

template<class Out, class In>
inline Out pointer_cast(const In* in) {
  const void* temp = in;
  return static_cast<Out>(temp);
}

}  // namespace basic
