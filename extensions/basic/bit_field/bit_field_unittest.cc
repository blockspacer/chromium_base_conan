// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/bit_field/bit_field.h"

#include <base/test/gtest_util.h>
#include <base/check_op.h>
#include <base/logging.h>

#include "testing/gtest/include/gtest/gtest.h"
#include "testing/gmock/include/gmock/gmock.h"

using namespace base;

namespace basic {

class BitFieldTest : public ::testing::Test {};

TEST_F(BitFieldTest, BitFieldDefaultCtor) {
  using BitField = SingleThreadedBitField<uint32_t>;
  using Value1 = BitField::DefineFirstValue<uint32_t, 31>;
  using Value2 = Value1::DefineNextValue<uint32_t, 1>;

  SingleThreadedBitField<uint32_t> bit_field;
  EXPECT_EQ(0u, bit_field.get<Value1>());
  EXPECT_EQ(0u, bit_field.get<Value2>());
}

TEST_F(BitFieldTest, BitFieldCtor) {
  using BitField = SingleThreadedBitField<uint32_t>;
  using Value1 = BitField::DefineFirstValue<uint32_t, 31>;
  using Value2 = Value1::DefineNextValue<uint32_t, 1>;

  SingleThreadedBitField<uint32_t> bit_field(0xdeadbeef);
  EXPECT_EQ(0x5eadbeefu, bit_field.get<Value1>());
  EXPECT_EQ(1u, bit_field.get<Value2>());
}

TEST_F(BitFieldTest, SplitBitField) {
  using BitField = SingleThreadedBitField<uint32_t>;
  using Value1 = BitField::DefineFirstValue<uint16_t, 16>;
  using Value2 = Value1::DefineNextValue<uint16_t, 8>;
  using Value3 = Value2::DefineNextValue<uint16_t, 8>;

  SingleThreadedBitField<uint32_t> bit_field(0xdeadbeef);
  EXPECT_EQ(0xde, bit_field.get<Value3>());
  EXPECT_EQ(0xad, bit_field.get<Value2>());
  EXPECT_EQ(0xbeef, bit_field.get<Value1>());
}

TEST_F(BitFieldTest, BitFieldBits) {
  using BitField = SingleThreadedBitField<uint8_t>;
  using Value1 = BitField::DefineFirstValue<bool, 1>;
  using Value2 = Value1::DefineNextValue<bool, 1>;
  using Value3 = Value2::DefineNextValue<bool, 1>;
  using Value4 = Value3::DefineNextValue<bool, 1>;
  using Value5 = Value4::DefineNextValue<bool, 1>;
  using Value6 = Value5::DefineNextValue<bool, 1>;
  using Value7 = Value6::DefineNextValue<bool, 1>;
  using Value8 = Value7::DefineNextValue<bool, 1>;

  SingleThreadedBitField<uint32_t> bit_field(0b10101010);
  EXPECT_FALSE(bit_field.get<Value1>());
  EXPECT_TRUE(bit_field.get<Value2>());
  EXPECT_FALSE(bit_field.get<Value3>());
  EXPECT_TRUE(bit_field.get<Value4>());
  EXPECT_FALSE(bit_field.get<Value5>());
  EXPECT_TRUE(bit_field.get<Value6>());
  EXPECT_FALSE(bit_field.get<Value7>());
  EXPECT_TRUE(bit_field.get<Value8>());
}

TEST_F(BitFieldTest, BitFieldSetValue) {
  using BitField = SingleThreadedBitField<uint32_t>;
  using Value1 = BitField::DefineFirstValue<uint16_t, 16>;
  using Value2 = Value1::DefineNextValue<uint16_t, 16>;

  SingleThreadedBitField<uint32_t> bit_field;
  CHECK_EQ(0u, bit_field.get<Value1>());
  CHECK_EQ(0u, bit_field.get<Value2>());
  bit_field.set<Value1>(1337);
  EXPECT_EQ(1337u, bit_field.get<Value1>());
  EXPECT_EQ(0u, bit_field.get<Value2>());
}

TEST_F(BitFieldTest, ConcurrentBitFieldGettersReturnTheSame) {
  using BitField = SingleThreadedBitField<uint32_t>;
  using Value1 = BitField::DefineFirstValue<uint16_t, 16>;
  using Value2 = Value1::DefineNextValue<uint16_t, 16>;

  ConcurrentlyReadBitField<uint32_t> bit_field(0xdeadbeef);
  CHECK_EQ(0xbeef, bit_field.get<Value1>());
  CHECK_EQ(0xdead, bit_field.get<Value2>());
  EXPECT_EQ(bit_field.get_concurrently<Value1>(), bit_field.get<Value1>());
  EXPECT_EQ(bit_field.get_concurrently<Value2>(), bit_field.get<Value2>());
}

TEST_F(BitFieldTest, ConcurrentBitFieldSetValue) {
  using BitField = SingleThreadedBitField<uint32_t>;
  using Value1 = BitField::DefineFirstValue<uint16_t, 16>;
  using Value2 = Value1::DefineNextValue<uint16_t, 16>;

  /// \note can not add extra `uint16_t` field (limited by `uint32_t`)
  // static_assert failed due to requirement '32UL < 8 * sizeof(unsigned int)'
  // "Field offset in bit field must be smaller than the bit field size"
  // using Value3 = Value2::DefineNextValue<uint16_t, 16>;

  /// \note can not add extra `bool` field (limited by `uint32_t`)
  // using Value3 = Value2::DefineNextValue<bool, 1, basic::BitFieldValueConstness::kConst>;

  /// \note can not add extra `bool` field (limited by `uint32_t`)
  // static_assert failed due to requirement '32UL < 8 * sizeof(unsigned int)'
  // "Field offset in bit field must be smaller than the bit field size"
  // using Value4 = Value3::DefineNextValue<bool, 1, basic::BitFieldValueConstness::kConst>;

  ConcurrentlyReadBitField<uint32_t> bit_field;
  CHECK_EQ(0u, bit_field.get_concurrently<Value1>());
  CHECK_EQ(0u, bit_field.get_concurrently<Value2>());
  bit_field.set<Value1>(1337);
  EXPECT_EQ(1337u, bit_field.get_concurrently<Value1>());
  bit_field.set<Value1>(2456);
  EXPECT_EQ(2456u, bit_field.get_concurrently<Value1>());
  EXPECT_EQ(0u, bit_field.get_concurrently<Value2>());
  bit_field.set<Value2>(9);
  EXPECT_EQ(2456u, bit_field.get_concurrently<Value1>());
  EXPECT_EQ(9u, bit_field.get_concurrently<Value2>());
}

TEST_F(BitFieldTest, ConcurrentBitFieldSetValueSmall) {
  using BitField = SingleThreadedBitField<uint32_t>;
  using Value1 = BitField::DefineFirstValue<uint16_t, 16>;
  /// \note smaller size than 16
  using Value2 = Value1::DefineNextValue<uint16_t, 4>;
  /// \note but can add `bool` field
  using Value3 = Value2::DefineNextValue<bool, 1, basic::BitFieldValueConstness::kConst>;
  /// \note can add extra `bool` field
  using Value4 = Value3::DefineNextValue<bool, 1, basic::BitFieldValueConstness::kConst>;

  /// \note can not add extra `uint16_t` field (limited by `uint32_t`)
  //using ValueX = Value4::DefineNextValue<uint16_t, 16>;

  ConcurrentlyReadBitField<uint32_t> bit_field;
  CHECK_EQ(0u, bit_field.get_concurrently<Value1>());
  CHECK_EQ(0u, bit_field.get_concurrently<Value2>());
  bit_field.set<Value1>(1337);
  EXPECT_EQ(1337u, bit_field.get_concurrently<Value1>());
  bit_field.set<Value1>(2456);
  EXPECT_EQ(2456u, bit_field.get_concurrently<Value1>());
  EXPECT_EQ(0u, bit_field.get_concurrently<Value2>());
  bit_field.set<Value2>(9);
  bit_field.set<Value3>(true);
  bit_field.set<Value4>(true);
  EXPECT_EQ(2456u, bit_field.get_concurrently<Value1>());
  EXPECT_EQ(9u, bit_field.get_concurrently<Value2>());
  EXPECT_EQ(true, bit_field.get_concurrently<Value3>());
  EXPECT_EQ(true, bit_field.get_concurrently<Value4>());

  // Value2 limited by 4 bits, crash!
  EXPECT_DCHECK_DEATH({ bit_field.set<Value2>(1686u); });
}

}  // namespace basic
