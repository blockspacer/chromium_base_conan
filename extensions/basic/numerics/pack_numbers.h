#pragma once

#include "build/build_config.h"

#include <base/macros.h>
#include <base/logging.h>
#include <base/check.h>

#include <cstdint>
#include <cstring>

/// \note Take care of byte order (endianess).
/// Usually data pack'd on one architecture
/// will not be usable on one with the opposite endianness.
/// Use fixed-width integers (uint8_t, int16_t, etc.) and size_t.

namespace basic {

// USAGE
//
// uint32_t value = 123;
// char encoded[sizeof(uint32_t)];
// EncodeFixed32(encoded, value);
// uint32_t res = DecodeFixed32(encoded); // same as value
//
inline void EncodeFixed32(char* buf, uint32_t value) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
  memcpy(buf, &value, sizeof(value));
#else
  buf[0] = value & 0xff;
  buf[1] = (value >> 8) & 0xff;
  buf[2] = (value >> 16) & 0xff;
  buf[3] = (value >> 24) & 0xff;
#endif
}


// USAGE
//
// uint64_t value = 123;
// char encoded[sizeof(uint64_t)];
// EncodeFixed64(encoded, value);
// uint32_t res = DecodeFixed32(encoded); // same as value
//
inline void EncodeFixed64(char* buf, uint64_t value) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
  memcpy(buf, &value, sizeof(value));
#else
  buf[0] = value & 0xff;
  buf[1] = (value >> 8) & 0xff;
  buf[2] = (value >> 16) & 0xff;
  buf[3] = (value >> 24) & 0xff;
  buf[4] = (value >> 32) & 0xff;
  buf[5] = (value >> 40) & 0xff;
  buf[6] = (value >> 48) & 0xff;
  buf[7] = (value >> 56) & 0xff;
#endif
}

inline uint32_t DecodeFixed32(const char* ptr) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
    // Load the raw bytes
    uint32_t result;
    memcpy(&result, ptr, sizeof(result));  // gcc optimizes this to a plain load
    return result;
#else
    return ((static_cast<uint32_t>(static_cast<unsigned char>(ptr[0])))
        | (static_cast<uint32_t>(static_cast<unsigned char>(ptr[1])) << 8)
        | (static_cast<uint32_t>(static_cast<unsigned char>(ptr[2])) << 16)
        | (static_cast<uint32_t>(static_cast<unsigned char>(ptr[3])) << 24));
#endif
}

inline uint32_t DecodeFixed32(const uint8_t* ptr) {
  // CHAR_BIT depends on platform. See stackoverflow.com/a/12894178
  // Check that char* and uint8_t* are interoperable types.
  // The reinterpret_cast<> between the pointers are used to simplify data loading.
  static_assert(std::is_same<uint8_t, char>::value ||
                std::is_same<uint8_t, unsigned char>::value,
                "unexpected uint8_t type size");
  return DecodeFixed32(reinterpret_cast<const char*>(ptr));
}

inline uint64_t DecodeFixed64(const char* ptr) {
#if defined(ARCH_CPU_LITTLE_ENDIAN)
    // Load the raw bytes
    uint64_t result;
    memcpy(&result, ptr, sizeof(result));  // gcc optimizes this to a plain load
    return result;
#else
    uint64_t lo = DecodeFixed32(ptr);
    uint64_t hi = DecodeFixed32(ptr + 4);
    return (hi << 32) | lo;
#endif
}

inline uint64_t DecodeFixed64(const uint8_t* ptr) {
  // CHAR_BIT depends on platform. See stackoverflow.com/a/12894178
  // Check that char* and uint8_t* are interoperable types.
  // The reinterpret_cast<> between the pointers are used to simplify data loading.
  static_assert(std::is_same<uint8_t, char>::value ||
                std::is_same<uint8_t, unsigned char>::value,
                "unexpected uint8_t type size");
  return DecodeFixed64(reinterpret_cast<const char*>(ptr));
}

// pack mix of (up to 4) uint8_t into one uint32_t
//
// EXAMPLE
//
// uint32_t packed = pack_to_uint32(4u,5u,6u,7u);
// std::cout << (int)unpack_unsigned<0>(packed) << "\n";
// std::cout << (int)unpack_unsigned<1>(packed) << "\n";
// std::cout << (int)unpack_unsigned<3>(packed) << "\n";
// std::cout << (int)unpack_unsigned<3>(packed) << "\n";
//
inline uint32_t pack_to_uint32(
  uint8_t x, uint8_t y, uint8_t z, uint8_t w)
{
  return (static_cast<uint32_t>(w) << 24)
         | (static_cast<uint32_t>(z) << 16)
         | (static_cast<uint32_t>(y) << 8)
         | static_cast<uint32_t>(x);
}

template <int N>
uint8_t unpack_unsigned(uint32_t packed)
{
  // cast to avoid potential warnings for implicit narrowing conversion
  return static_cast<uint8_t>(packed >> (N*8));
}

// pack 4 normalized floats [-1, 1] to uint32_t
//
// EXAMPLE
//
// uint32_t packed = pack_nf_to_uint32_t(0.3f,0.2f,0.45f,0.99f);
// float x = (float(unpack_unsigned<0>(packed)) - 128.0f) * 1.0f/127.0f;
// float y = (float(unpack_unsigned<1>(packed)) - 128.0f) * 1.0f/127.0f;
//
inline uint32_t pack_nf_to_uint32_t(
  float x, float y = 0.0f, float z = 0.0f, float w = 0.0f)
{
  DCHECK(x >= -1.0f);
  DCHECK(x <= 1.0f);
  const uint8_t xx = uint8_t(x * 127.0f + 128.0f);

  DCHECK(y >= -1.0f);
  DCHECK(y <= 1.0f);
  const uint8_t yy = uint8_t(y * 127.0f + 128.0f);

  DCHECK(z >= -1.0f);
  DCHECK(z <= 1.0f);
  const uint8_t zz = uint8_t(z * 127.0f + 128.0f);

  DCHECK(w >= -1.0f);
  DCHECK(w <= 1.0f);
  const uint8_t ww = uint8_t(w * 127.0f + 128.0f);

  return pack_to_uint32(xx, yy, zz, ww);
}

// pack 4 unsigned floats [0, 1] to uint32_t
//
// EXAMPLE
//
// uint32_t packed = pack_uf_to_uint32_t(0.3f,0.2f,0.45f,0.99f);
// float x = float(unpack_unsigned<0>(packed)) * 1.0f/255.0f;
// float y = float(unpack_unsigned<1>(packed)) * 1.0f/255.0f;
//
inline uint32_t pack_uf_to_uint32_t(
  float x, float y = 0.0f, float z = 0.0f, float w = 0.0f)
{
  DCHECK(x >= 0.0f);
  DCHECK(x <= 1.0f);
  const uint8_t xx = uint8_t(x * 255.f);

  DCHECK(y >= 0.0f);
  DCHECK(y <= 1.0f);
  const uint8_t yy = uint8_t(y * 255.f);

  DCHECK(z >= 0.0f);
  DCHECK(z <= 1.0f);
  const uint8_t zz = uint8_t(z * 255.f);

  DCHECK(w >= 0.0f);
  DCHECK(w <= 1.0f);
  const uint8_t ww = uint8_t(w * 255.f);

  return pack_to_uint32(xx, yy, zz, ww);
}

} // namespace basic
