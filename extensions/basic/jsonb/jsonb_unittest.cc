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

#include "basic/jsonb/jsonb.h"

#include <memory>
#include <string>
#include <vector>

#include "base/json/json_reader.h"
#include "base/strings/string_piece.h"
#include "base/values.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace basic {

std::string ParseJson(const std::string& json) {
  Jsonb jsonb;
  LOG(INFO) << "Parsing json...";
  EXPECT_OK(jsonb.FromString(json));
  EXPECT_FALSE(jsonb.SerializedJsonb().empty());

  auto result = jsonb.ToJsonString();

  EXPECT_OK(result);

  LOG(INFO) << "Deserialized json: " << result.ValueOrDie();

  return result.ValueOrDie();
}

void VerifyArray(const base::Value& val) {
  ASSERT_TRUE(val.is_list());
  EXPECT_TRUE(!val.GetList().empty());
  const auto& list = val.GetList();
  ASSERT_EQ(1, list[0].GetInt());
  ASSERT_EQ(2, list[1].GetInt());
  ASSERT_DOUBLE_EQ(3.0, list[2].GetDouble());
  ASSERT_TRUE(list[3].is_bool());
  ASSERT_TRUE(list[4].is_bool());
  ASSERT_TRUE(list[5].is_dict());
  ASSERT_EQ(1, list[5].FindKey("k1")->GetInt());
  ASSERT_TRUE(list[5].FindKey("k2")->is_list());
  ASSERT_EQ(100, list[5].FindKey("k2")->GetList()[0].GetInt());
  ASSERT_EQ(200, list[5].FindKey("k2")->GetList()[1].GetInt());
  ASSERT_EQ(300, list[5].FindKey("k2")->GetList()[2].GetInt());
  ASSERT_TRUE(list[5].FindKey("k3")->is_bool());
}

TEST(JsonbTest, TestJsonbSerialization) {
  std::string document = ParseJson(R"#(
      {
        "b" : 1,
        "a1" : [1, 2, 3.0, false, true, { "k1" : 1, "k2" : [100, 200, 300], "k3" : true}],
        "a" :
        {
          "d" : true,
          "q" :
          {
            "p" : 4294967295,
            "r" : -2147483648,
            "s" : 2147483647
          },
          "g" : -100,
          "c" : false,
          "f" : "hello",
          "x" : 2.1,
          "y" : 9223372036854775807,
          "z" : -9223372036854775808,
          "u" : 18446744073709551615,
          "l" : 2147483647.123123e+75,
          "e" : null
        }
      })#");

  // Parse the json document.
  ::base::JSONReader::ValueWithError root =
    ::base::JSONReader::ReadAndReturnValueWithError(document);
  EXPECT_TRUE(root.value);

  const base::DictionaryValue* dictionary =
      static_cast<const base::DictionaryValue*>(&(*root.value));

  // Verify the json.
  ASSERT_TRUE((*dictionary).HasKey("a"));
  ASSERT_TRUE((*dictionary).FindKey("a")->is_dict());

  ASSERT_TRUE((*dictionary).FindKey("a")->FindBoolPath("c"));
  ASSERT_TRUE((*dictionary).FindKey("a")->FindBoolPath("d"));
  ASSERT_TRUE((*dictionary).FindKey("a")->FindKey("e")->is_none());
  ASSERT_TRUE((*dictionary).FindKey("a")->FindStringPath("f"));

  ASSERT_EQ("hello", std::string((*dictionary).FindKey("a")->FindKey("f")->GetString()));

  ASSERT_TRUE((*dictionary).FindKey("a")->FindKey("g")->is_int());
  ASSERT_EQ(-100, (*dictionary).FindKey("a")->FindKey("g")->GetInt());

  ASSERT_TRUE((*dictionary).FindKey("a")->FindKey("q")->is_dict());

  /// \todo double
  ///ASSERT_TRUE((*dictionary).FindKey("a")->FindKey("q")->FindKey("p")->is_int())
  ///  << (*dictionary).FindKey("a")->FindKey("q")->FindKey("p")->type();
  ///ASSERT_EQ(4294967295, (*dictionary).FindKey("a")->FindKey("q")->FindKey("p")->GetInt());
  ASSERT_EQ(4294967295, (*dictionary).FindKey("a")->FindKey("q")->FindKey("p")->GetDouble());

  ASSERT_TRUE((*dictionary).FindKey("a")->FindKey("q")->FindKey("r")->is_int());
  ASSERT_EQ(-2147483648, (*dictionary).FindKey("a")->FindKey("q")->FindKey("r")->GetInt());

  ASSERT_TRUE((*dictionary).FindKey("a")->FindKey("q")->FindKey("s")->is_int());
  ASSERT_EQ(2147483647, (*dictionary).FindKey("a")->FindKey("q")->FindKey("s")->GetInt());

  ASSERT_TRUE((*dictionary).FindKey("a")->FindKey("x")->is_double());
  ASSERT_FLOAT_EQ(2.1f, (*dictionary).FindKey("a")->FindKey("x")->GetDouble());

  /// \todo double
  //ASSERT_TRUE((*dictionary).FindKey("a")->FindKey("u")->is_int());
  //ASSERT_EQ(18446744073709551615ULL, (*dictionary).FindKey("a")->FindKey("u")->GetInt());
  ASSERT_EQ(18446744073709551615ULL, (*dictionary).FindKey("a")->FindKey("u")->GetDouble());

  /// \todo double
  ///ASSERT_TRUE((*dictionary).FindKey("a")->FindKey("y")->is_int());
  ///ASSERT_EQ(9223372036854775807LL, (*dictionary).FindKey("a")->FindKey("y")->GetInt());
  ASSERT_EQ(9223372036854775807LL, (*dictionary).FindKey("a")->FindKey("y")->GetDouble());

  /// \todo double -9.22337e+18
  ///ASSERT_TRUE((*dictionary).FindKey("a")->FindKey("z")->is_int());
  ///ASSERT_EQ(-9223372036854775808ULL, (*dictionary).FindKey("a")->FindKey("z")->GetInt());
  ///ASSERT_EQ(-9223372036854775808ULL, (*dictionary).FindKey("a")->FindKey("z")->GetDouble());

  ASSERT_TRUE((*dictionary).FindKey("a")->FindKey("l")->is_double());
  ASSERT_DOUBLE_EQ(2147483647.123123e+75, (*dictionary).FindKey("a")->FindKey("l")->GetDouble());

  ASSERT_TRUE((*dictionary).FindKey("b")->is_int());
  ASSERT_EQ(1, (*dictionary).FindKey("b")->GetInt());

  // Test array.
  ASSERT_TRUE((*dictionary).FindKey("a1")->is_list());
  VerifyArray(*((*dictionary).FindKey("a1")));
}

TEST(JsonbTest, TestArrays) {
  std::string document = ParseJson(R"#(
        [1, 2, 3.0, false, true, { "k1" : 1, "k2" : [100, 200, 300], "k3" : true}]
      )#");
  base::Optional<base::Value> val = base::JSONReader::Read(document);
  ASSERT_TRUE(val);
  VerifyArray(*val);
}

TEST(JsonbTest, Simple) {
  Jsonb jsonb;

  LOG(INFO) << "Parsing json...";

  EXPECT_OK(jsonb.FromString(R"#(
        [1, 2, 3.0, false, true, { "k1" : 1, "k2" : [100, 200, 300], "k3" : true}]
      )#"));

  EXPECT_FALSE(jsonb.SerializedJsonb().empty());
}

}  // namespace basic
