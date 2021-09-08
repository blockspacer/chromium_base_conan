#include <basic/containers/invertible_map.h>

#include "base/logging.h"
#include "base/compiler_specific.h"
#include "base/bind.h"
#include "base/stl_util.h"
#include "base/callback.h"
#include "base/run_loop.h"

#include "base/test/task_environment.h"

#include "testing/gtest/include/gtest/gtest.h"

#include <cstdint>
#include <limits>
#include <random>
#include <set>

using namespace std;
using namespace basic;

namespace {

class InvertibleMapTest : public testing::Test {
 public:
  using KeyType = int;
  using ValueType = std::string;
 protected:
  InvertibleMap<KeyType, ValueType> map;
};

} // namespace

static const InvertibleMapTest::KeyType limits_min = 0;

static const InvertibleMapTest::KeyType limits_max = 1000;

TEST_F(InvertibleMapTest, empty) {
  EXPECT_TRUE(map.empty());

  for (KeyType c = limits_min; c < limits_max; ++c)
  {
    EXPECT_FALSE(map.containsKey(c));
    EXPECT_FALSE(map.containsValue(std::to_string(c)));
  }
}

TEST_F(InvertibleMapTest, each) {
  for (auto c = limits_min; c < limits_max; ++c) {
    map.insert(c, std::to_string(c));
    EXPECT_TRUE(map.containsKey(c));
    EXPECT_TRUE(map.containsValue(std::to_string(c)));
  }
}
