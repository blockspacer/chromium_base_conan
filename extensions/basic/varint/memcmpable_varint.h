// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
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
// is distributed on an "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//
// This is an alternate varint format, borrowed from sqlite4, that differs from the
// varint in util/coding.h in that its serialized form can be compared with memcmp(),
// yielding the same result as comparing the original integers.
//
// The serialized form also has the property that multiple such varints can be strung
// together to form a composite key, which itself is memcmpable.
//
// See memcmpable_varint.cc for further description.

#pragma once

#include "basic/status/status_macros.h"
#include "base/strings/string_piece.h"

namespace basic {

namespace memcmpable_varint_detail {

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

} // namespace memcmpable_varint_detail

// Appends the varint to the end of the string.
void PutMemcmpableVarint64(std::string *dst, uint64_t value);

#if TODO
// Appends the varint to the end of the string.
void PutMemcmpableVarint64(faststring *dst, uint64_t value);
#endif

// Standard Get... routines parse a value from the beginning of a Slice
// and advance the slice past the parsed value.
basic::Status GetMemcmpableVarint64(base::StringPiece* input, uint64_t *value);

} // namespace basic
