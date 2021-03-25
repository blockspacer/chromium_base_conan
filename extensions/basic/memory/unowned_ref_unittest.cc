#include <utility>
#include <vector>

#include "testing/gtest/include/gtest/gtest.h"

#include "basic/memory/unowned_ref.h"

namespace basic {
namespace {

class Clink {
 public:
  UnownedRef<Clink> next_;
};

}  // namespace

TEST(UnownedRef, PtrOk) {
  Clink* ptr1 = new Clink();
  Clink* ptr2 = new Clink();
  ptr2->next_ = std::ref(*ptr1);
}

}  // namespace basic
