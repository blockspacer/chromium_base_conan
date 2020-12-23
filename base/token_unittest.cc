// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/base_token.h"
#include GTEST_HEADER_INCLUDE

namespace base {

// Verifies that we can support constexpr Token construction.
constexpr BaseToken kTestToken{1234, 5678};

TEST(TokenTest, Constructors) {
  BaseToken zero_token;
  EXPECT_EQ(0u, zero_token.high());
  EXPECT_EQ(0u, zero_token.low());
  EXPECT_TRUE(zero_token.is_zero());

  BaseToken token_with_explicit_values{1234, 5678};
  EXPECT_EQ(1234u, token_with_explicit_values.high());
  EXPECT_EQ(5678u, token_with_explicit_values.low());
  EXPECT_FALSE(token_with_explicit_values.is_zero());

  BaseToken random_token = BaseToken::CreateRandom();
  EXPECT_FALSE(random_token.is_zero());

  EXPECT_EQ(1234u, kTestToken.high());
  EXPECT_EQ(5678u, kTestToken.low());
  EXPECT_FALSE(kTestToken.is_zero());
}

TEST(TokenTest, Equality) {
  EXPECT_EQ(BaseToken(), BaseToken(0, 0));
  EXPECT_EQ(BaseToken(0, 0), BaseToken(0, 0));
  EXPECT_EQ(BaseToken(1, 2), BaseToken(1, 2));
  EXPECT_NE(BaseToken(1, 2), BaseToken(1, 3));
  EXPECT_NE(BaseToken(1, 2), BaseToken(2, 2));
  EXPECT_NE(BaseToken(1, 2), BaseToken(3, 4));
}

TEST(TokenTest, Ordering) {
  EXPECT_LT(BaseToken(0, 0), BaseToken(0, 1));
  EXPECT_LT(BaseToken(0, 1), BaseToken(0, 2));
  EXPECT_LT(BaseToken(0, 1), BaseToken(1, 0));
  EXPECT_LT(BaseToken(0, 2), BaseToken(1, 0));
}

TEST(TokenTest, ToString) {
  EXPECT_EQ("00000000000000000000000000000000", BaseToken(0, 0).ToString());
  EXPECT_EQ("00000000000000010000000000000002", BaseToken(1, 2).ToString());
  EXPECT_EQ("0123456789ABCDEF5A5A5A5AA5A5A5A5",
            BaseToken(0x0123456789abcdefull, 0x5a5a5a5aa5a5a5a5ull).ToString());
  EXPECT_EQ("FFFFFFFFFFFFFFFDFFFFFFFFFFFFFFFE",
            BaseToken(0xfffffffffffffffdull, 0xfffffffffffffffeull).ToString());
}

}  // namespace base
