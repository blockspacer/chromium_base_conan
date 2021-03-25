#include "basic/types_bucket/types_bucket.h"
#include "basic/strings/substitute.h"

#include "base/bind.h"
#include "base/test/bind.h"
#include "base/macros.h"
#include "base/time/tick_clock.h"
#include "base/test/task_environment.h"
#include <base/run_loop.h>

#include "testing/gtest/include/gtest/gtest.h"

#include <memory>

using namespace base;

namespace basic {

struct MyTypeA {
  int foo;
  char bar;
};

class TypesBucketTest : public testing::Test {
 public:
  TypesBucketTest() = default;
  void SetUp() override {
  }

 protected:
  base::test::TaskEnvironment task_environment;
};

TEST_F(TypesBucketTest, TryCtx) {
  TypesBucket typesBucket;

  EXPECT_FALSE(typesBucket.try_ctx<MyTypeA>());

  int foo = 1;
  char bar = 'h';

  typesBucket.set<MyTypeA>(foo, bar);

  EXPECT_TRUE(typesBucket.try_ctx<MyTypeA>());
  auto& var = typesBucket.ctx<MyTypeA>();
  EXPECT_EQ(var.foo, foo);
  EXPECT_EQ(var.bar, bar);
}

TEST_F(TypesBucketTest, Reset) {
  TypesBucket typesBucket;

  EXPECT_FALSE(typesBucket.try_ctx<MyTypeA>());

  {
    int foo = 1;
    char bar = 'h';
    auto& var = typesBucket.reset<MyTypeA>(foo, bar);
    EXPECT_TRUE(typesBucket.try_ctx<MyTypeA>());
    EXPECT_EQ(var.foo, foo);
    EXPECT_EQ(var.bar, bar);
  }

  {
    int foo = 76;
    char bar = 'l';
    auto& var = typesBucket.reset<MyTypeA>(foo, bar);
    EXPECT_TRUE(typesBucket.try_ctx<MyTypeA>());
    EXPECT_EQ(var.foo, foo);
    EXPECT_EQ(var.bar, bar);
  }
}

}  // namespace basic
