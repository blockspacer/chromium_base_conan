// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
// The following only applies to changes made to this file as part of YugaByte development.
//
// Portions Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//

#include "basic/bloom_filter/counting_bloom.h"
#include <basic/recursion_checker.h>
#include <basic/strings/substitute.h>

#include <base/test/gtest_util.h>
#include "base/test/task_environment.h"
#include <base/strings/string_number_conversions.h>
#include <base/rand_util.h>

#include "testing/gtest/include/gtest/gtest.h"

#include <cstdio>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <vector>

namespace basic {

TEST(TestCountingBloomFilter, Simple) {
  // Verify that the keys we inserted all return true when queried.
  CountingBloomFilter<12> bf;

  const unsigned identifier_hashes[3]{1, 2, 3};

  bf.Add(identifier_hashes[1]);
  EXPECT_TRUE(bf.MayContain(identifier_hashes[1]));

  bf.Add(identifier_hashes[2]);
  EXPECT_TRUE(bf.MayContain(identifier_hashes[2]));

  bf.Remove(identifier_hashes[1]);
  bf.Remove(identifier_hashes[2]);

#if DCHECK_IS_ON()
  EXPECT_TRUE(bf.LikelyEmpty());
#endif // DCHECK_IS_ON()
}

} // namespace basic
