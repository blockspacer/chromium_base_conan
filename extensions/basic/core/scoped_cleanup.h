// Copyright 2014 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <functional>
#include <type_traits>

#include "base/macros.h"
#include "base/logging.h"
#include "basic/rvalue_cast.h"

namespace basic {

/// \note see also basic/value_saver.h
//
// A scoped cleanup action that is performed on destruction.  The action can be
// cancelled by calling Cancel().
//
// This can take any sort of callable argument including functors, function
// pointers, member-function pointers (const or not), and lambdas.
//
// If you are trying to do RAII-style resource management, consider UniqueValue
// instead, which builds on top of ScopedCleanup.
//
// Examples:
//
//  // Functor arg.
//  ScopedCleanup bing{CloseFileFunctor(fd)};
//
//  // Function arg.
//  ScopedCleanup bang{::abort};
//  ScopedCleanup bong{::close, fd};
//
//  // Member function arg.
//  ScopedCleanup boom{&Database::Reset, &db};
//  ScopedCleanup boing{&Database::Close, &db, fd};
//
//  // Lambda arg.
//  ScopedCleanup bump{[fd]() { ::close(fd); }};
//
// This class is thread-compatible.
class ScopedCleanup final {
 public:
  // Makes a ScopedCleanup from a callback function.  The args parameters are
  // copied and bound to the function; the result must be a nullary function.
  template<typename T, typename... Args>
  explicit ScopedCleanup(T callable, const Args&... args)
      : active_(true), cleanup_(::std::bind(callable, args...))
  {
    DCHECK(cleanup_);
  }

  ScopedCleanup(
    ScopedCleanup&& other)
  {
    active_ = RVALUE_CAST(other.active_);
    cleanup_ = RVALUE_CAST(other.cleanup_);
    DCHECK(cleanup_);

    /// \note can not run moved out |cleanup_|
    other.active_ = false;
  }

  ScopedCleanup& operator=(
    ScopedCleanup&& other)
  {
    active_ = RVALUE_CAST(other.active_);
    cleanup_ = RVALUE_CAST(other.cleanup_);
    DCHECK(cleanup_);

    /// \note can not run moved out |cleanup_|
    other.active_ = false;

    return *this;
  }

  ~ScopedCleanup() {
    if (active_) {
      DCHECK(cleanup_);
      cleanup_();
    }
  }

  // Cancels a ScopedCleanup.  Once called, this cleanup action will not run.
  void Cancel() {
    active_ = false;
  }

 private:
  // The actual cleanup object.  Cleanup is triggered by destruction.
  bool active_;
  ::std::function<void()> cleanup_;

  DISALLOW_COPY_AND_ASSIGN(ScopedCleanup);
};

}  // namespace basic
