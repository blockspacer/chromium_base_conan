// Copyright 2017-2020 The Verible Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" basic,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "basic/status/with_details.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace basic {
namespace {

// Example of a priority-ordered function.
static WithDetails<const char*> FizzBuzzer(int i) {
  if (i % 3 == 0) {
    if (i % 5 == 0) {
      return {"fizzbuzz", FROM_HERE, "value is divisible by 3 and 5."};
    }
    return {"fizz", FROM_HERE, "value is only divisible by 3."};
  }

  if (i % 5 == 0) return {"buzz", FROM_HERE, "value is only divisible by 5."};

  return {".", FROM_HERE, "value is neither divisible by 3 nor 5."};
}

TEST(WithDetails, Fizz) {
  const auto result = FizzBuzzer(6);
  EXPECT_EQ(result.value, "fizz");
  EXPECT_EQ(result.reason, "value is only divisible by 3.");
}

TEST(WithDetails, Buzz) {
  const auto result = FizzBuzzer(10);
  EXPECT_EQ(result.value, "buzz");
  EXPECT_EQ(result.reason, "value is only divisible by 5.");
}

TEST(WithDetails, Neither) {
  const auto result = FizzBuzzer(16);
  EXPECT_EQ(result.value, ".");
  EXPECT_EQ(result.reason, "value is neither divisible by 3 nor 5.");
}

TEST(WithDetails, Both) {
  const auto result = FizzBuzzer(30);
  EXPECT_EQ(result.value, "fizzbuzz");
  EXPECT_EQ(result.reason, "value is divisible by 3 and 5.");
}

}  // namespace
}  // namespace basic
