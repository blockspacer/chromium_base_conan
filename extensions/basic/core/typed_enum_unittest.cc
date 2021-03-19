// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/core/typed_enum.h"

#include "base/test/task_environment.h"
#include "base/bind.h"
#include "base/run_loop.h"
#include "base/threading/thread.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace basic {

TYPED_ENUM(TypedTestEnum, int, (kFullFilter)(kFixedSizeFilter))

TEST(TypedEnumTest, TypeConversionConstructorUninitializedAssignment) {
  TypedTestEnum enum1 = TypedTestEnum::kFullFilter;
  enum1 = TypedTestEnum::kFixedSizeFilter;
  EXPECT_EQ(enum1, TypedTestEnum::kFixedSizeFilter);
  EXPECT_NE(enum1, TypedTestEnum::kFullFilter);
}

}  // namespace basic
