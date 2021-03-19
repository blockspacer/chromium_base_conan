#include "basic/strong_types/strong_bool.h"

#include <cstddef>
#include <cstdint>

#include "testing/gtest/include/gtest/gtest.h"

namespace base {

STRONGLY_TYPED_BOOL(foo);

STRONGLY_TYPED_BOOL(bar);

TEST(StrongBoolTest, Simple) {
  foo v1 = foo::kTrue;
  // EXPECT_EQ(v1, true); // ERROR
  // EXPECT_EQ(v1, bar::kTrue); // ERROR
  // EXPECT_EQ(v1, bar{true}); // ERROR
  EXPECT_EQ(v1, foo{true});
  EXPECT_EQ(v1, foo::kTrue);
  EXPECT_NE(v1, foo::kFalse);
  EXPECT_NE(v1, foo{false});

  // v1 = true; // ERROR, no viable overloaded '='

  // bar v2 = foo::kTrue; // ERROR, no implicit cast

  foo v4 = v1 || foo::kFalse;
  bar v5 = bar::kTrue && bar(false);
  EXPECT_FALSE(v5);

  // bool v6 = v5; // ERROR, no implicit cast

  bool boolean = true;
  foo v8{boolean};
  EXPECT_TRUE(v8);
  v8 = foo{false};
  EXPECT_FALSE(v8);
}

}  // namespace base
