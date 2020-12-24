// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "base/hash/md5.h"
#include "base/hash/md5_constexpr_internal.h"

// EXAMPLE
//
// uint64_t GetTaskFlowId(uint32_t sequence_id, uint32_t order_num) {
//   // Xor with a mask to ensure that the flow id does not collide with non-gpu
//   // tasks.
//   static constexpr uint64_t kMask = base::MD5Hash64Constexpr("gpu::Scheduler");
//   return kMask ^ (sequence_id) ^ (static_cast<uint64_t>(order_num) << 32);
// }

namespace base {

// An constexpr implementation of the MD5 hash function. This is no longer
// considered cryptographically secure, but it is useful as a string hashing
// primitive.
//
// This is not the most efficient implementation, so it is not intended to be
// used at runtime. If you do attempt to use it at runtime you will see
// errors about missing symbols.

// Calculates the MD5 digest of the provided data. When passing |string| with
// no explicit length the terminating null will not be processed.
constexpr MD5Digest MD5SumConstexpr(const char* string);
constexpr MD5Digest MD5SumConstexpr(const char* data, uint32_t length);

// Calculates the first 32/64 bits of the MD5 digest of the provided data,
// returned as a uint32_t/uint64_t. When passing |string| with no explicit
// length the terminating null will not be processed. This abstracts away
// endianness so that the integer will read as the first 4 or 8 bytes of the
// MD5 sum, ensuring that the following outputs are equivalent for
// convenience:
//
// printf("%08x\n", MD5HashConstexpr32("foo"));
//
// MD5Digest d = MD5SumConstexpr("foo");
// printf("%02x%02x%02x%02x\n", d.a[0], d.a[1], d.a[2], d.a[3]);
constexpr uint64_t MD5Hash64Constexpr(const char* string);
constexpr uint64_t MD5Hash64Constexpr(const char* data, uint32_t length);
constexpr uint32_t MD5Hash32Constexpr(const char* string);
constexpr uint32_t MD5Hash32Constexpr(const char* data, uint32_t length);

}  // namespace base
