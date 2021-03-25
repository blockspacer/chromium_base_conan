#pragma once

#include <cstdint>
#include <cstring>
#include <limits>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

#include <basic/portability/c_portability.h>
#include <basic/portability/traits.h>

namespace basic {
namespace hash {

//  twang_mix64
//
//  Thomas Wang 64 bit mix hash function.
BASIC_DISABLE_UNDEFINED_BEHAVIOR_SANITIZER("unsigned-integer-overflow")
constexpr uint64_t twang_mix64(uint64_t key) noexcept {
  key = (~key) + (key << 21); // key *= (1 << 21) - 1; key -= 1;
  key = key ^ (key >> 24);
  key = key + (key << 3) + (key << 8); // key *= 1 + (1 << 3) + (1 << 8)
  key = key ^ (key >> 14);
  key = key + (key << 2) + (key << 4); // key *= 1 + (1 << 2) + (1 << 4)
  key = key ^ (key >> 28);
  key = key + (key << 31); // key *= 1 + (1 << 31)
  return key;
}

//  twang_unmix64
//
//  Inverse of, and slower than, twang_mix64.
constexpr uint64_t twang_unmix64(uint64_t key) noexcept {
  // See the comments in jenkins_rev_unmix32 for an explanation as to how this
  // was generated
  key *= 4611686016279904257U;
  key ^= (key >> 28) ^ (key >> 56);
  key *= 14933078535860113213U;
  key ^= (key >> 14) ^ (key >> 28) ^ (key >> 42) ^ (key >> 56);
  key *= 15244667743933553977U;
  key ^= (key >> 24) ^ (key >> 48);
  key = (key + 1) * 9223367638806167551U;
  return key;
}

//  twang_32from64
//
//  Thomas Wang downscaling hash function.
constexpr uint32_t twang_32from64(uint64_t key) noexcept {
  key = (~key) + (key << 18);
  key = key ^ (key >> 31);
  key = key * 21;
  key = key ^ (key >> 11);
  key = key + (key << 6);
  key = key ^ (key >> 22);
  return static_cast<uint32_t>(key);
}

} // namespace hash
} // namespace basic
