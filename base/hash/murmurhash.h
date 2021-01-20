//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.
//
// The following only applies to changes made to this file as part of YugaByte development.
//
// Portions Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//
/*
  Murmurhash from http://sites.google.com/site/murmurhash/

  All code is released to the public domain. For business purposes, Murmurhash is
  under the MIT license.
*/

#pragma once

#include <cstdint>

#include "base/containers/span.h"

// Allow slice to be hashable by murmur hash.
namespace basis {

#if defined(__x86_64__)

#define MURMUR_HASH MurmurHash64A

// The same caveats as 32-bit MurmurHash2 apply here - beware of alignment
// and endian-ness issues if used across multiple platforms.
//
// 64-bit hash for 64-bit platforms
uint64_t MurmurHash64A ( const void * key, int len, unsigned int seed );

#define MurmurHash MurmurHash64A

typedef uint64_t murmur_t;

#elif defined(__i386__)

#define MURMUR_HASH MurmurHash2

// Note - This code makes a few assumptions about how your machine behaves -
//
// 1. We can read a 4-byte value from any address without crashing
// 2. sizeof(int) == 4
//
// And it has a few limitations -
//
// 1. It will not work incrementally.
// 2. It will not produce the same results on little-endian and big-endian
//    machines.
unsigned int MurmurHash2 ( const void * key, int len, unsigned int seed );

#define MurmurHash MurmurHash2

typedef unsigned int murmur_t;

#else

#define MURMUR_HASH MurmurHashNeutral2

unsigned int MurmurHashNeutral2 ( const void * key, int len, unsigned int seed );

#define MurmurHash MurmurHashNeutral2

typedef unsigned int murmur_t;

#endif

struct murmur_hash {
  size_t operator()(const base::span<const uint8_t>& slice) const {
    return operator()(slice, 0);
  }

  size_t operator()(const base::span<const uint8_t>& slice, unsigned int seed) const {
    return MurmurHash(slice.data(), static_cast<int>(slice.size()), seed);
  }
};

// Murmur2 hash implementation returning 64-bit hashes.
/// \note Unlike `MurmurHash64A` that function must not depend on platform.
uint64_t MurmurHash2_64(const void* input, int len, uint64_t seed);

}  // basis
