// Copyright (c) YugaByte, Inc.
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

#include "basic/varint/varint.h"

#include "base/test/task_environment.h"

#include "basic/strings/substitute.h"

#include <openssl/bn.h>

#include "testing/gtest/include/gtest/gtest.h"

namespace basic {

const std::string kTooSmall = "-9223372036854775809";
const std::string kTooBig = "9223372036854775808";

class VarIntTest : public testing::Test {
 protected:
  void SetUp() override {
    // Should be ordered by value, since it is used in comparison tests.
    std::vector<std::string> inputs = {
      "-37618632178637216379216387",
      kTooSmall,
      std::to_string(std::numeric_limits<int64_t>::min()),
      std::to_string(std::numeric_limits<int>::min() - 1LL),
      std::to_string(std::numeric_limits<int>::min()),
      "-129",
      "-128",
      "-127",
      "-23",
      "0",
      "38",
      std::to_string(std::numeric_limits<int>::max()),
      std::to_string(std::numeric_limits<int>::max() + 1LL),
      std::to_string(std::numeric_limits<int64_t>::max()),
      kTooBig,
      "8429024091289482183283928321",
    };

    values_.reserve(inputs.size());

    for (const auto& input : inputs) {
      basic::StatusOr<VarInt> status = VarInt::CreateFromString(input);
      ASSERT_OK(status);
      values_.push_back(RVALUE_CAST(status.ConsumeValueOrDie()));
    }
  }

  std::string ToDebugString(const std::string& input) {
    size_t num_bytes = input.size();
    std::string output = "[ ";
    for (size_t i = 0; i < num_bytes; i++) {
      for (size_t j = 0; j < 8; j++) {
        output += '0' + static_cast<char>(input[i] >> (7 - j) & 1);
      }
      output += ' ';
    }
    output += ']';
    return output;
  }

  std::vector<VarInt> values_;
  base::test::TaskEnvironment task_environment;
};

TEST_F(VarIntTest, TestComparableEncoding) {
  std::vector<std::string> expected = {
      "[ 00000000 00000111 11100000 11100001 11110001 11011101 00000001 00110000 "
        "11011100 11111011 11101101 01011101 11111100 ]", // -37618632178637216379216387
      "[ 00000000 00111111 01111111 11111111 11111111 11111111 11111111 11111111 11111111 "
        "11111110 ]", // kTooSmall,
      "[ 00000000 00111111 01111111 11111111 11111111 11111111 11111111 11111111 11111111 "
        "11111111 ]", // std::to_string(std::numeric_limits<int64_t>::min()),
      "[ 00000111 01111111 11111111 11111111 11111110 ]",
          // std::to_string(std::numeric_limits<int>::min() - 1LL),
      "[ 00000111 01111111 11111111 11111111 11111111 ]",
          // std::to_string(std::numeric_limits<int>::min()),
      "[ 00111111 01111110 ]", // -129
      "[ 00111111 01111111 ]", // -128
      "[ 00111111 10000000 ]", // -127
      "[ 01101000 ]", // -23
      "[ 10000000 ]", // 0
      "[ 10100110 ]", // 38
      "[ 11111000 01111111 11111111 11111111 11111111 ]",
          // std::to_string(std::numeric_limits<int>::max()),
      "[ 11111000 10000000 00000000 00000000 00000000 ]",
          // std::to_string(std::numeric_limits<int>::max() + 1LL),
      "[ 11111111 11000000 01111111 11111111 11111111 11111111 11111111 11111111 11111111 "
        "11111111 ]", // std::to_string(std::numeric_limits<int64_t>::max()),
      "[ 11111111 11000000 10000000 00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 ]", // kTooBig,
      "[ 11111111 11111100 00011011 00111100 01010011 01000111 10010101 11011111 "
        "00011011 00001010 01111011 11111101 01101101 00000001 ]" // 8429024091289482183283928321
  };
  ASSERT_EQ(expected.size(), values_.size());
  for (size_t i = 0; i != values_.size(); ++i) {
    SCOPED_TRACE(basic::Substitute("Index: $1, value: $2", i, values_[i]));
    auto encoded = values_[i].EncodeToComparable();
    EXPECT_EQ(expected[i], ToDebugString(encoded));
    VarInt decoded;
    size_t size;
    ASSERT_OK(decoded.DecodeFromComparable(encoded, &size));
    EXPECT_EQ(encoded.size(), size);
    EXPECT_EQ(values_[i], decoded);
  }
}

TEST_F(VarIntTest, TestTwosComplementEncoding) {
  std::vector<std::string> expected = {
      "[ 11100000 11100001 11110001 11011101 00000001 00110000 11011100 11111011 "
        "11101101 01011101 11111101 ]", // -37618632178637216379216387
      "[ 11111111 01111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 ]",
          // kTooSmall
      "[ 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 ]",
          // std::to_string(std::numeric_limits<int64_t>::min())
      "[ 11111111 01111111 11111111 11111111 11111111 ]",
          // std::to_string(std::numeric_limits<int>::min() - 1LL)
      "[ 10000000 00000000 00000000 00000000 ]", // std::to_string(std::numeric_limits<int>::min())
      "[ 11111111 01111111 ]", // -129
      "[ 10000000 ]", // -128
      "[ 10000001 ]", // -127
      "[ 11101001 ]", // -23
      "[ 00000000 ]", // 0
      "[ 00100110 ]", // 38
      "[ 01111111 11111111 11111111 11111111 ]", // std::to_string(std::numeric_limits<int>::max())
      "[ 00000000 10000000 00000000 00000000 00000000 ]",
          // std::to_string(std::numeric_limits<int>::max() + 1LL)
      "[ 01111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111 ]",
          // std::to_string(std::numeric_limits<int64_t>::max())
      "[ 00000000 10000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 ]",
          // kTooBig
      "[ 00011011 00111100 01010011 01000111 10010101 11011111 00011011 00001010 "
        "01111011 11111101 01101101 00000001 ]" // 8429024091289482183283928321
  };
  ASSERT_EQ(expected.size(), values_.size());
  for (size_t i = 0; i != values_.size(); ++i) {
    SCOPED_TRACE(basic::Substitute("Index: $1, value: $2", i, values_[i]));
    auto encoded = values_[i].EncodeToTwosComplement();
    EXPECT_EQ(expected[i], ToDebugString(encoded));
    VarInt decoded;
    ASSERT_OK(decoded.DecodeFromTwosComplement(encoded));
    EXPECT_EQ(values_[i], decoded);
  }
}

TEST_F(VarIntTest, TestTypeConversionsMax) {
  int64_t max = std::numeric_limits<int64_t>::max();

  VarInt varint(max);
  ASSERT_EQ(std::to_string(max), varint.ToString());
  int64_t converted = varint.ToInt64().ValueOrDie();
  ASSERT_EQ(max, converted);
}

TEST_F(VarIntTest, TestTypeConversionsMin) {
  int64_t min = std::numeric_limits<int64_t>::min();

  VarInt varint(min);
  ASSERT_EQ(std::to_string(min), varint.ToString());
  int64_t converted = varint.ToInt64().ValueOrDie();
  ASSERT_EQ(min, converted);
}

TEST_F(VarIntTest, TestTypeConversionsNegative) {
  int64_t negative = -380;

  VarInt varint(negative);
  ASSERT_EQ(std::to_string(negative), varint.ToString());
  int64_t converted = varint.ToInt64().ValueOrDie();
  ASSERT_EQ(negative, converted);
}

TEST_F(VarIntTest, TestTypeConversionsZero) {
  int64_t zero = 0;

  VarInt varint(zero);
  ASSERT_EQ(std::to_string(zero), varint.ToString());
  int64_t converted = varint.ToInt64().ValueOrDie();
  ASSERT_EQ(zero, converted);
}

TEST_F(VarIntTest, TestTypeOverflowLarge) {
  basic::StatusOr<VarInt> status = VarInt::CreateFromString("9223372036854775808");
  ASSERT_OK(status);
  VarInt too_big = RVALUE_CAST(status.ConsumeValueOrDie());
  ASSERT_EQ(too_big.ToString(), "9223372036854775808");
  ASSERT_FALSE(too_big.ToInt64().ok());
}

TEST_F(VarIntTest, TestTypeOverflowSmall) {
  basic::StatusOr<VarInt> status = VarInt::CreateFromString("-9223372036854775809");
  ASSERT_OK(status);
  VarInt too_small = RVALUE_CAST(status.ConsumeValueOrDie());
  ASSERT_EQ(too_small.ToString(), "-9223372036854775809");
  ASSERT_FALSE(too_small.ToInt64().ok());
}

TEST_F(VarIntTest, TestTypeOverflowLarger) {
  basic::StatusOr<VarInt> status = VarInt::CreateFromString("99999999999999999999999");
  ASSERT_OK(status);
  VarInt very_big = RVALUE_CAST(status.ConsumeValueOrDie());
  ASSERT_EQ(very_big.ToString(), "99999999999999999999999");
  ASSERT_FALSE(very_big.ToInt64().ok());
}

TEST_F(VarIntTest, TestTypeOverflowSmaller) {
  basic::StatusOr<VarInt> status = VarInt::CreateFromString("-99999999999999999999999");
  ASSERT_OK(status);
  VarInt very_small = RVALUE_CAST(status.ConsumeValueOrDie());
  ASSERT_EQ(very_small.ToString(), "-99999999999999999999999");
  ASSERT_FALSE(very_small.ToInt64().ok());
}

TEST_F(VarIntTest, TestComparison) {
  std::vector<std::string> encoded;
  encoded.reserve(values_.size());

  for (const auto& value : values_) {
    encoded.push_back(value.EncodeToComparable());
  }

  for (size_t i = 0; i != values_.size(); ++i) {
    for (size_t j = 0; j != values_.size(); ++j) {
      ASSERT_EQ(i < j, values_[i] < values_[j]);
      ASSERT_EQ(i <= j, values_[i] <= values_[j]);
      ASSERT_EQ(i == j, values_[i] == values_[j]);
      ASSERT_EQ(i >= j, values_[i] >= values_[j]);
      ASSERT_EQ(i > j, values_[i] > values_[j]);

      ASSERT_EQ(i < j, encoded[i] < encoded[j]);
      ASSERT_EQ(i <= j, encoded[i] <= encoded[j]);
      ASSERT_EQ(i == j, encoded[i] == encoded[j]);
      ASSERT_EQ(i >= j, encoded[i] >= encoded[j]);
      ASSERT_EQ(i > j, encoded[i] > encoded[j]);
    }
  }
}

TEST_F(VarIntTest, TestArithmetic) {
  ASSERT_EQ(VarInt(74), VarInt(28) + VarInt(46));
  ASSERT_EQ(VarInt(-113), VarInt(28) - VarInt(141));
  ASSERT_EQ(VarInt(0), VarInt(23) + VarInt(3) + VarInt(-26));
  ASSERT_EQ(VarInt(1), VarInt(23) + VarInt(3) + VarInt(-25));
  ASSERT_EQ(VarInt(-1), VarInt(23) + VarInt(3) + VarInt(-27));
}

TEST_F(VarIntTest, ComparableEncodingWithReserve) {
  constexpr int kNumReservedBits = 2;
  for (int i = 0; i != 0xffff; ++i) {
    SCOPED_TRACE(basic::Substitute("i: $1", i));
    VarInt v(i);
    auto encoded = v.EncodeToComparable(kNumReservedBits);
    VarInt decoded;
    size_t decoded_size = 0;
    ASSERT_OK(decoded.DecodeFromComparable(encoded, &decoded_size, kNumReservedBits));
    ASSERT_EQ(v, decoded);
    ASSERT_EQ(encoded.size(), decoded_size);
  }
}

} // namespace basic
