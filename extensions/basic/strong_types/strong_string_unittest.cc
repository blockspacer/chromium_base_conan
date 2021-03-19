#include "basic/strong_types/strong_string.h"

#include <cstddef>
#include <cstdint>

#include "testing/gtest/include/gtest/gtest.h"

namespace base {

STRONGLY_TYPED_STRING(fooStr);

STRONGLY_TYPED_STRING(barStr);

TEST(StrongBoolTest, Simple) {
  fooStr v1{"12345"}; // OK
  EXPECT_EQ(v1[0], '1');
  // EXPECT_EQ(v1, "12345"); // ERROR
  EXPECT_EQ(v1, fooStr{"12345"});
  EXPECT_NE(v1.find('5'), fooStr::npos);
  EXPECT_NE(v1.find('5'), std::string::npos);
  EXPECT_EQ(v1.find('9'), fooStr::npos);
  EXPECT_EQ(v1.find('9'), std::string::npos);

  // v1 = "12345"; // ERROR, no viable overloaded '='

  barStr v2{"34233"}; // OK
  EXPECT_EQ(v2[2], '2');

  // fooStr v3 = "12345"; // ERROR
  // barStr v4 = "34233"; // ERROR
  // std::string v6 = v1; // ERROR, no implicit cast

  fooStr v5 = fooStr::kEmpty;
  EXPECT_EQ(v5, fooStr::kEmpty);

  // EXPECT_EQ(v5, ""); // ERROR
  EXPECT_EQ(v5, fooStr{""});
}

}  // namespace base
