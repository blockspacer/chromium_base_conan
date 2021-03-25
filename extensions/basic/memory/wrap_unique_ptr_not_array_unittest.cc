#include "basic/memory/wrap_unique_ptr_not_array.h"

#include "testing/gtest/include/gtest/gtest.h"

#include <cstddef>

namespace basic {

namespace {

class DeleteCounter {
 public:
  DeleteCounter() { ++count_; }
  ~DeleteCounter() { --count_; }

  static size_t count() { return count_; }

 private:
  static size_t count_;
};

size_t DeleteCounter::count_ = 0;

}  // namespace

TEST(PtrUtilTest, WrapUniqueNotArray) {
  EXPECT_EQ(0u, DeleteCounter::count());
  DeleteCounter* counter = new DeleteCounter;
  EXPECT_EQ(1u, DeleteCounter::count());
  std::unique_ptr<DeleteCounter> owned_counter = WrapUniqueNotArray(counter);
  EXPECT_EQ(1u, DeleteCounter::count());
  owned_counter.reset();
  EXPECT_EQ(0u, DeleteCounter::count());
}

}  // namespace basic
