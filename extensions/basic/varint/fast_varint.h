// Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//

#pragma once

#include <string>

#include "basic/status/status_macros.h"

#include "base/strings/string_piece.h"
#include "base/containers/span.h"

// USAGE
//
// // 1. To send over network:
//
// uint64_t value = 123;
// uint8_t* buf = big_buffer.data() + kMaxVarIntBufferSize * i;
// size_t size = 0;
// FastEncodeUnsignedVarInt(value, buf, &size);
//
// // ... send buf over network ...
//
// // 2. To recieve over network:
//
// uint64_t decoded_value;
// size_t decoded_size = 0;
// RETURN_WITH_MESSAGE_IF_NOT_OK(FastDecodeUnsignedVarInt(buf, size, &decoded_value, &decoded_size))
//   << "Data not fully decoded.";
//
// // ... use decoded_value ...
//
namespace basic {

namespace fast_varint_detail {

inline uint8_t* to_uchar_ptr(char *ptr) {
  // CHAR_BIT depends on platform. See stackoverflow.com/a/12894178
  // Check that char* and uint8_t* are interoperable types.
  // The reinterpret_cast<> between the pointers are used to simplify data loading.
  static_assert(std::is_same<uint8_t, char>::value ||
                std::is_same<uint8_t, unsigned char>::value,
                "unexpected uint8_t type size");
  return reinterpret_cast<uint8_t *>(ptr);
}

inline const uint8_t* to_uchar_ptr(const char *ptr) {
  // CHAR_BIT depends on platform. See stackoverflow.com/a/12894178
  // Check that char* and uint8_t* are interoperable types.
  // The reinterpret_cast<> between the pointers are used to simplify data loading.
  static_assert(std::is_same<uint8_t, char>::value ||
                std::is_same<uint8_t, unsigned char>::value,
                "unexpected uint8_t type size");
  return reinterpret_cast<const uint8_t *>(ptr);
}

inline char* to_char_ptr(uint8_t *ptr) {
  // CHAR_BIT depends on platform. See stackoverflow.com/a/12894178
  // Check that char* and uint8_t* are interoperable types.
  // The reinterpret_cast<> between the pointers are used to simplify data loading.
  static_assert(std::is_same<uint8_t, char>::value ||
                std::is_same<uint8_t, unsigned char>::value,
                "unexpected uint8_t type size");
  return reinterpret_cast<char *>(ptr);
}

inline const char* to_char_ptr(const uint8_t *ptr) {
  // CHAR_BIT depends on platform. See stackoverflow.com/a/12894178
  // Check that char* and uint8_t* are interoperable types.
  // The reinterpret_cast<> between the pointers are used to simplify data loading.
  static_assert(std::is_same<uint8_t, char>::value ||
                std::is_same<uint8_t, unsigned char>::value,
                "unexpected uint8_t type size");
  return reinterpret_cast<const char *>(ptr);
}

} // namespace fast_varint_detail

constexpr size_t kMaxVarIntBufferSize = 16;

// Computes the number of bytes needed to represent the given number as a signed VarInt.
int SignedPositiveVarIntLength(uint64_t v);

void FastEncodeSignedVarInt(int64_t v, uint8_t *dest, size_t *size);
std::string FastEncodeSignedVarIntToStr(int64_t v);

template <class Buffer>
void FastAppendSignedVarIntToBuffer(int64_t v, Buffer* dest) {
  char buf[kMaxVarIntBufferSize];
  size_t len = 0;
  FastEncodeSignedVarInt(v, fast_varint_detail::to_uchar_ptr(buf), &len);
  DCHECK_LE(len, 10);
  dest->append(buf, len);
}

// Consumes decoded part of the slice.
basic::StatusOr<int64_t> FastDecodeSignedVarInt(base::span<const uint8_t>* slice);
basic::Status FastDecodeSignedVarInt(const uint8_t* src,
                                      size_t src_size,
                                      int64_t* v,
                                      size_t* decoded_size);

// The same as FastDecodeSignedVarInt but takes a regular char pointer.
inline basic::Status FastDecodeSignedVarInt(
    const char* src, size_t src_size, int64_t* v, size_t* decoded_size) {
  return FastDecodeSignedVarInt(fast_varint_detail::to_uchar_ptr(src), src_size, v, decoded_size);
}

basic::Status FastDecodeSignedVarInt(const std::string& encoded, int64_t* v, size_t* decoded_size);

// Encoding a "descending VarInt" is simply decoding -v as a VarInt.
inline char* FastEncodeDescendingSignedVarInt(int64_t v, char *buf) {
  size_t size = 0;
  FastEncodeSignedVarInt(-v, fast_varint_detail::to_uchar_ptr(buf), &size);
  return buf + size;
}

inline void FastEncodeDescendingSignedVarInt(int64_t v, std::string *dest) {
  char buf[kMaxVarIntBufferSize];
  auto* end = FastEncodeDescendingSignedVarInt(v, buf);
  dest->append(buf, end);
}

// Decode a "descending VarInt" encoded by FastEncodeDescendingSignedVarInt.
basic::Status FastDecodeDescendingSignedVarInt(base::span<const uint8_t>* slice, int64_t *dest);
basic::StatusOr<int64_t> FastDecodeDescendingSignedVarInt(base::span<const uint8_t>* slice);

size_t UnsignedVarIntLength(uint64_t v);
void FastAppendUnsignedVarIntToStr(uint64_t v, std::string* dest);
void FastEncodeUnsignedVarInt(uint64_t v, uint8_t *dest, size_t *size);
basic::Status FastDecodeUnsignedVarInt(
    const uint8_t* src, size_t src_size, uint64_t* v, size_t* decoded_size);
basic::StatusOr<uint64_t> FastDecodeUnsignedVarInt(base::span<const uint8_t>* slice);
basic::StatusOr<uint64_t> FastDecodeUnsignedVarInt(const base::span<const uint8_t>& slice);

}  // namespace basic
