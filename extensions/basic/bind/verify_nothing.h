#pragma once

#include <basic/core/bitmask.h>

#include <base/macros.h>
#include <base/sequence_checker.h>
#include <base/callback.h>
#include <base/optional.h>
#include <base/location.h>
#include <basic/rvalue_cast.h>
#include <base/strings/string_piece.h>
#include <base/threading/thread_collision_warner.h>

#include <functional>
#include <map>
#include <string>

namespace basic {

// Creates a callback that does nothing when called.
class BASE_EXPORT VerifyNothing {
 public:
  template <typename... Args>
  operator ::base::RepeatingCallback<bool(Args...)>() const {
    return Repeatedly<Args...>();
  }
  template <typename... Args>
  operator ::base::OnceCallback<bool(Args...)>() const {
    return Once<Args...>();
  }
  // Explicit way of specifying a specific callback type when the compiler can't
  // deduce it.
  template <typename... Args>
  static ::base::RepeatingCallback<bool(Args...)> Repeatedly() {
    return ::base::BindRepeating([](Args... /*args*/){ return true; });
  }
  template <typename... Args>
  static ::base::OnceCallback<bool(Args...)> Once() {
    return ::base::BindOnce([](Args... /*args*/) { return true; });
  }
};

} // namespace basic
