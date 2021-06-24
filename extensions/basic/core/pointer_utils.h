// Copyright 2014 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <cstdint>
#include <cstdio>
#include <cinttypes>

namespace basic {

// AdvancePointer() is a helper function to advance void pointer by
// |byte_offset| bytes. Both const and non-const overloads are provided.
inline void* AdvancePointer(void* pointer, ssize_t byte_offset) {
  return reinterpret_cast<uint8_t*>(pointer) + byte_offset;
}

inline const void* AdvancePointer(const void* pointer, ssize_t byte_offset) {
  return reinterpret_cast<const uint8_t*>(pointer) + byte_offset;
}

} // namespace basic
