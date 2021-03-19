#include "basic/strong_types/strong_int.h"

#include <cstddef>
#include <cstdint>

#include "testing/gtest/include/gtest/gtest.h"

namespace base {

STRONGLY_TYPED_INT(foo);

DEFINE_STRONGLY_TYPED_INT(bar, int64_t);

TEST(StrongIntTest, Simple) {
  int num = 45;

  foo v1{num};
  EXPECT_TRUE(v1);
  // EXPECT_TRUE(v1 == 45); // ERROR
  EXPECT_EQ(v1, foo{45});
  EXPECT_GT(v1, foo{44});
  EXPECT_LT(v1, foo{46});
  // v1 = 45; // ERROR, no viable overloaded '='

  foo v4 = v1 || foo{0};
  EXPECT_TRUE(v4);

  // bar v2 = foo{56}; // ERROR, no implicit cast

  bar v5 = bar{1} && bar(0);
  EXPECT_FALSE(v5);

  // int v6 = v5; // ERROR, no implicit cast

  // bar baz0 = 421 + v5; // ERROR

  // bar baz1 = v5 + 421; // ERROR

  bar baz = bar{421} + v5;

  // EXPECT_TRUE(baz == bar{421UL}); // ERROR
  EXPECT_EQ(baz, bar{static_cast<bar::type>(421UL)});

  baz++;
  EXPECT_EQ(baz, bar{422});

  // bar baz2(std::numeric_limits<size_t>::max()); // static_assert failed
}

}  // namespace base
