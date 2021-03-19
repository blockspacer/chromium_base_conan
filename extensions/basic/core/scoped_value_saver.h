// Copyright 2017-2020 The Verible Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

namespace basic {

// An object of this type modifies a given variable in the constructor
// and restores its original value in the destructor.
template <typename T>
class ScopedValueSaver {
 public:
  ScopedValueSaver(T* p, const T& newval) : ptr_(p), oldval_(*ptr_) {
    *ptr_ = newval;
  }
  // The one-arg version just uses the current value as newval.
  explicit ScopedValueSaver(T* p) : ptr_(p), oldval_(*ptr_) {}

  ~ScopedValueSaver() { *ptr_ = oldval_; }

  ScopedValueSaver(ScopedValueSaver&&) = delete;
  ScopedValueSaver(const ScopedValueSaver&) = delete;
  ScopedValueSaver& operator=(const ScopedValueSaver&) = delete;

 private:
  T* const ptr_;
  const T oldval_;
};

}  // namespace basic
