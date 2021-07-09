// Copyright 2014 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <basic/containers/any_dictionary.h>

#include "base/test/copy_only_int.h"
#include "base/test/gtest_util.h"
#include "base/test/move_only_int.h"
#include "testing/gtest/include/gtest/gtest.h"

#include <string>
#include <any>

using namespace base;
using namespace basic;

using basic::GetValuePtr;
using basic::AnyDictionary;

TEST(AnyDictionary, GetValuePtr) {
  AnyDictionary dictionary;
  dictionary.emplace("a", 1);
  dictionary.emplace("b", "string");
  // Test values that are present in the AnyDictionary.
  EXPECT_EQ(1, *GetValuePtr<int>(dictionary, "a"));
  EXPECT_EQ("string", *GetValuePtr<const char*>(dictionary, "b"));
  // Test that missing keys result in defaults.
  EXPECT_EQ(nullptr, GetValuePtr<std::string>(dictionary, "missing"));
  EXPECT_EQ(nullptr, GetValuePtr<int>(dictionary, "missing"));
}
