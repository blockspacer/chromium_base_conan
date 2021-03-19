// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <cstdint>
#include <limits>

#include "basic/numerics/pack_numbers.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace basic {

namespace test {

TEST(PackNumbersTest, CodeFixed32) {
  uint32_t num = 123;
  std::unique_ptr<char[]> buf(new char[sizeof(uint32_t)]);
  buf[0] = '\0';
  EncodeFixed32(buf.get(), num);
  EXPECT_EQ(DecodeFixed32(buf.get()), num);
}

TEST(PackNumbersTest, CodeFixed64) {
  uint64_t num = 123;
  std::unique_ptr<char[]> buf(new char[sizeof(uint64_t)]);
  buf[0] = '\0';
  EncodeFixed64(buf.get(), num);
  EXPECT_EQ(DecodeFixed64(buf.get()), num);
}

TEST(PackNumbersTest, Packing) {
  uint8_t x = 12;
  uint8_t y = 23;
  uint8_t z = 34;
  uint8_t w = 45;
  uint32_t packed = pack_to_uint32(x, y, z, w);
  EXPECT_EQ(unpack_unsigned<0>(packed), x);
  EXPECT_EQ(unpack_unsigned<1>(packed), y);
  EXPECT_EQ(unpack_unsigned<2>(packed), z);
  EXPECT_EQ(unpack_unsigned<3>(packed), w);
}

}  // namespace test

}  // namespace basic
