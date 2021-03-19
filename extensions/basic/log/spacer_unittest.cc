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

#include "basic/log/spacer.h"

#include <cstddef>
#include <sstream>
#include <string>

#include "testing/gtest/include/gtest/gtest.h"

namespace basic {
namespace {

TEST(SpacerTest, DefaultSpaces) {
  for (size_t i = 0; i < 10; ++i) {
    const Spacer s(i);  // default to ' '
    std::ostringstream stream;
    stream << s;
    EXPECT_EQ(stream.str(), std::string(i, ' '));
  }
}

TEST(SpacerTest, CustomSpaces) {
  constexpr char test_char = '.';
  for (size_t i = 0; i < 10; ++i) {
    const Spacer s(i, test_char);
    std::ostringstream stream;
    stream << s;
    EXPECT_EQ(stream.str(), std::string(i, test_char));
  }
}

}  // namespace
}  // namespace basic
