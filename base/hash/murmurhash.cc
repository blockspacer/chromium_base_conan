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
#include "murmurhash.h"

#include "base/macros.h"
#include "base/logging.h"

namespace basis {

static const uint64_t MURMUR_PRIME = 0xc6a4a7935bd1e995;
static const int MURMUR_R = 47;

#if defined(__x86_64__)

// -------------------------------------------------------------------
//
// The same caveats as 32-bit MurmurHash2 apply here - beware of alignment
// and endian-ness issues if used across multiple platforms.
//
// 64-bit hash for 64-bit platforms

uint64_t MurmurHash64A ( const void * key, int len, unsigned int seed )
{
    const uint64_t m = MURMUR_PRIME;
    const int r = MURMUR_R;

    uint64_t h = seed ^ (len * m);

    const uint64_t * data = (const uint64_t *)key;
    const uint64_t * end = data + (len/8); // 8 must be sizeof(uint64_t)

    while(data != end)
    {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char * data2 = (const unsigned char*)data;

    switch(len & 7)
    {
    case 7: h ^= ((uint64_t)data2[6]) << 48; FALL_THROUGH_BREAK;
    case 6: h ^= ((uint64_t)data2[5]) << 40; FALL_THROUGH_BREAK;
    case 5: h ^= ((uint64_t)data2[4]) << 32; FALL_THROUGH_BREAK;
    case 4: h ^= ((uint64_t)data2[3]) << 24; FALL_THROUGH_BREAK;
    case 3: h ^= ((uint64_t)data2[2]) << 16; FALL_THROUGH_BREAK;
    case 2: h ^= ((uint64_t)data2[1]) << 8; FALL_THROUGH_BREAK;
    case 1: h ^= ((uint64_t)data2[0]);
        h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

#elif defined(__i386__)

// -------------------------------------------------------------------
//
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

unsigned int MurmurHash2 ( const void * key, int len, unsigned int seed )
{
    // 'm' and 'r' are mixing constants generated offline.
    // They're not really 'magic', they just happen to work well.

    const unsigned int m = 0x5bd1e995;
    const int r = 24;

    // Initialize the hash to a 'random' value

    unsigned int h = seed ^ len;

    // Mix 4 bytes at a time into the hash

    const unsigned char * data = (const unsigned char *)key;

    while(len >= 4)
    {
        unsigned int k = *(unsigned int *)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    // Handle the last few bytes of the input array

    switch(len)
    {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
        h *= m;
    };

    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

#else

// -------------------------------------------------------------------
//
// Same as MurmurHash2, but endian- and alignment-neutral.
// Half the speed though, alas.

unsigned int MurmurHashNeutral2 ( const void * key, int len, unsigned int seed )
{
    const unsigned int m = 0x5bd1e995;
    const int r = 24;

    unsigned int h = seed ^ len;

    const unsigned char * data = (const unsigned char *)key;

    while(len >= 4)
    {
        unsigned int k;

        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch(len)
    {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
        h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

#endif

uint64_t MurmurHash2_64(const void* input, int len, uint64_t seed) {
  uint64_t h = seed ^ (len * MURMUR_PRIME);

  const uint64_t* data = reinterpret_cast<const uint64_t*>(input);
  const uint64_t* end = data + (len / sizeof(uint64_t));

  while (data != end) {
    uint64_t k = *data++;
    k *= MURMUR_PRIME;
    k ^= k >> MURMUR_R;
    k *= MURMUR_PRIME;
    h ^= k;
    h *= MURMUR_PRIME;
  }

  const uint8_t* data2 = reinterpret_cast<const uint8_t*>(data);
  switch (len & 7) {
    case 7: h ^= static_cast<uint64_t>(data2[6]) << 48; FALL_THROUGH_BREAK;
    case 6: h ^= static_cast<uint64_t>(data2[5]) << 40; FALL_THROUGH_BREAK;
    case 5: h ^= static_cast<uint64_t>(data2[4]) << 32; FALL_THROUGH_BREAK;
    case 4: h ^= static_cast<uint64_t>(data2[3]) << 24; FALL_THROUGH_BREAK;
    case 3: h ^= static_cast<uint64_t>(data2[2]) << 16; FALL_THROUGH_BREAK;
    case 2: h ^= static_cast<uint64_t>(data2[1]) << 8; FALL_THROUGH_BREAK;
    case 1: h ^= static_cast<uint64_t>(data2[0]);
            h *= MURMUR_PRIME;
  }

  h ^= h >> MURMUR_R;
  h *= MURMUR_PRIME;
  h ^= h >> MURMUR_R;
  return h;
}

} // namespace basis
