// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/build_time.h"
#include "base/generated_build_date.h"
#include "base/time/time.h"
#include "build/build_config.h"

#include "testing/gtest/include/gtest/gtest.h"

TEST(BuildTime, DateLooksValid) {
  char build_date[] = BUILD_DATE;

  EXPECT_EQ(20u, strlen(build_date));
  EXPECT_EQ(' ', build_date[3]);
  EXPECT_EQ(' ', build_date[6]);
  EXPECT_EQ(' ', build_date[11]);
#if !defined(OFFICIAL_BUILD)
  EXPECT_EQ('0', build_date[12]);
  EXPECT_EQ('7', build_date[13]);
#endif
  EXPECT_EQ(':', build_date[14]);
#if !defined(OFFICIAL_BUILD)
  EXPECT_EQ('2', build_date[15]);
  EXPECT_EQ('3', build_date[16]);
#endif
  EXPECT_EQ(':', build_date[17]);
#if !defined(OFFICIAL_BUILD)
  EXPECT_EQ('4', build_date[18]);
  EXPECT_EQ('7', build_date[19]);
#endif
}

#if defined(OS_FUCHSIA)
// TODO(https://crbug.com/1060357): Enable when RTC flake is fixed.
#define MAYBE_InThePast DISABLED_InThePast
#else
#define MAYBE_InThePast InThePast
#endif

TEST(BuildTime, MAYBE_InThePast) {
  EXPECT_LT(base::GetBuildTime(), base::Time::Now());
  EXPECT_LT(base::GetBuildTime(), base::Time::NowFromSystemTime());
}
