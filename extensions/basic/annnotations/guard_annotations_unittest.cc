// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/annnotations/guard_annotations.h"

#include <array>
#include <deque>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "base/containers/queue.h"
#include "base/strings/string16.h"
#include "base/strings/utf_string_conversions.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

using namespace base;

namespace basic {

template <typename T>
using AnnotatedType
  = ::basic::AnnotateLockable<
      T
    >;

TEST(GuardAnnotationsTest, AnnotatedType) {
  int value = 3;
  AnnotatedType<int> annotated;
  (*annotated) = value;
  EXPECT_EQ((*annotated), value);
}

}  // namespace basic
