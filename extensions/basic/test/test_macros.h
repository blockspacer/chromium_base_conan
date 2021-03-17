#pragma once

#include <string>
#include <sstream>
#include <set>

// USAGE
//
// std::vector<int> vecA{1,2,3};
// EXPECT_ELEMENTS_EQ(vecA, 1, 2, 3) << "Some failure";
//
#define EXPECT_ELEMENTS_EQ(x, ...) \
  EXPECT_THAT(x, testing::ElementsAre(__VA_ARGS__))

// USAGE
//
// std::vector<int> vecA{1,2,3};
// EXPECT_ELEMENTS_EQ_ARRAY(vecA, std::vector<int>{1, 2, 3}) << "Some failure";
//
#define EXPECT_ELEMENTS_EQ_ARRAY(x, ...) \
  EXPECT_THAT(x, testing::ElementsAre(__VA_ARGS__))

// USAGE
//
// ASSERT_STR_CONTAINS("abcd", "bc") << "Some failure";
//
#ifndef ASSERT_STR_CONTAINS
#define ASSERT_STR_CONTAINS(x, substr) \
  ASSERT_THAT(x, testing::HasSubstr(substr))
#endif // ASSERT_STR_CONTAINS

// USAGE
//
// ASSERT_STR_NOT_CONTAIN("abcd", "bc") << "Some failure";
//
#ifndef ASSERT_STR_NOT_CONTAINS
#define ASSERT_STR_NOT_CONTAINS(x, substr) \
  ASSERT_THAT(x, testing::Not(testing::HasSubstr(substr)))
#endif // ASSERT_STR_NOT_CONTAINS

// Gives ability to define custom parent class for test fixture.
//
// class DriverTest : public ... {
//  public:
//   void SetUp() override {}
// };
//class CppDriverTestSlow : public DriverTest {
// public:
//  std::vector<std::string> ExtraData() override {
//    auto flags = DriverTest::ExtraData();
//    flags.push_back("--TEST_slowdown_backfill_alter_table_rpcs_ms=200");
//    return flags;
//  }
//};
// TEST_F_EX(DriverTest, TestIndex, CppDriverTestSlow) {
//   // ...
// }
#define TEST_F_EX(test_case_name, test_name, parent_class) \
  GTEST_TEST_(test_case_name, test_name, parent_class, \
              ::testing::internal::GetTypeId<test_case_name>())
