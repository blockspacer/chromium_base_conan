/*
 *  Copyright 2012 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "basic/statistics/rate_tracker.h"

#include "testing/gtest/include/gtest/gtest.h"

#include <cmath>

namespace basic {
namespace {
const uint32_t kBucketIntervalMs = 100;
}  // namespace

class RateTrackerForTest : public RateTracker {
 public:
  RateTrackerForTest() : RateTracker(kBucketIntervalMs, 10u), time_(0) {}
  int64_t Time() const override { return time_; }
  void AdvanceTime(int delta) { time_ += delta; }

 private:
  int64_t time_;
};

TEST(RateTrackerTest, TestBandwidth) {
  const uint64_t kNumBytesTotal = 65'535; // transfer 65'535bytes
  const int kTotalDurationMs = 220; // over 0.220s
  const uint64_t kNumIterations = 5; // split 0.220s into 5 iterations

  const int64_t kNumBytesPerStep = 13107; // 13107bytes each iteration (65'535bytes summary)
  EXPECT_EQ(kNumBytesTotal, kNumBytesPerStep * kNumIterations)
    << "rounding error";
  const int kDurationPerStep = 44; // 44ms each iteration (0.220s summary)
  EXPECT_EQ(kTotalDurationMs, kDurationPerStep * kNumIterations)
    << "rounding error";
  RateTrackerForTest tracker;
  int64_t bytes_sum = 0;
  int64_t time_sum = 0;
  for (size_t i = 0; i < kNumIterations; ++i) {
    tracker.AddSamplesNow(kNumBytesPerStep);
    tracker.AdvanceTime(kDurationPerStep);
    time_sum += kDurationPerStep;
    bytes_sum += kNumBytesPerStep;
  }

  EXPECT_EQ(kNumBytesTotal, bytes_sum);
  EXPECT_EQ(kTotalDurationMs, time_sum);

  EXPECT_EQ(kNumBytesTotal, tracker.TotalSampleCount());
  EXPECT_EQ(kTotalDurationMs, tracker.ElapsedTime());
  // Max Bandwidth = 65'535bytes / 0.220s = 297886.36 B/s
  const double kExpected = static_cast<double>(tracker.TotalSampleCount()) / static_cast<double>(tracker.ElapsedTime()) * 1000.0;

  EXPECT_DOUBLE_EQ(kExpected, tracker.ComputeRateForIntervalNow(kTotalDurationMs));
  EXPECT_DOUBLE_EQ(kExpected, tracker.ComputeRateNow());
}

TEST(RateTrackerTest, Test30FPS) {
  RateTrackerForTest tracker;

  for (int i = 0; i < 300; ++i) {
    tracker.AddSamplesNow(1);
    tracker.AdvanceTime(33);
    if (i % 3 == 0) {
      tracker.AdvanceTime(1);
    }
  }
  EXPECT_DOUBLE_EQ(30.0, tracker.ComputeRateForIntervalNow(50000));
}

TEST(RateTrackerTest, Test60FPS) {
  RateTrackerForTest tracker;

  for (int i = 0; i < 300; ++i) {
    tracker.AddSamplesNow(1);
    tracker.AdvanceTime(16);
    if (i % 3 != 0) {
      tracker.AdvanceTime(1);
    }
  }
  EXPECT_DOUBLE_EQ(60.0, tracker.ComputeRateForIntervalNow(1000));
}

TEST(RateTrackerTest, TestRateTrackerBasics) {
  RateTrackerForTest tracker;
  EXPECT_DOUBLE_EQ(0.0, tracker.ComputeRateForIntervalNow(1000));

  // Add a sample.
  tracker.AddSamplesNow(1234);
  // Advance the clock by less than one bucket interval (no rate returned).
  tracker.AdvanceTime(kBucketIntervalMs - 1);
  EXPECT_DOUBLE_EQ(0.0, tracker.ComputeRateNow());
  // Advance the clock by 100 ms (one bucket interval).
  tracker.AdvanceTime(1);
  EXPECT_DOUBLE_EQ(12340.0, tracker.ComputeRateForIntervalNow(1000));
  EXPECT_DOUBLE_EQ(12340.0, tracker.ComputeRateNow());
  EXPECT_EQ(1234U, tracker.TotalSampleCount());
  EXPECT_DOUBLE_EQ(12340.0, tracker.ComputeTotalRateNow());

  // Repeat.
  tracker.AddSamplesNow(1234);
  tracker.AdvanceTime(100);
  EXPECT_DOUBLE_EQ(12340.0, tracker.ComputeRateForIntervalNow(1000));
  EXPECT_DOUBLE_EQ(12340.0, tracker.ComputeRateNow());
  EXPECT_EQ(1234U * 2, tracker.TotalSampleCount());
  EXPECT_DOUBLE_EQ(12340.0, tracker.ComputeTotalRateNow());

  // Advance the clock by 800 ms, so we've elapsed a full second.
  // units_second should now be filled in properly.
  tracker.AdvanceTime(800);
  EXPECT_DOUBLE_EQ(1234.0 * 2.0, tracker.ComputeRateForIntervalNow(1000));
  EXPECT_DOUBLE_EQ(1234.0 * 2.0, tracker.ComputeRateNow());
  EXPECT_EQ(1234U * 2, tracker.TotalSampleCount());
  EXPECT_DOUBLE_EQ(1234.0 * 2.0, tracker.ComputeTotalRateNow());

  // Poll the tracker again immediately. The reported rate should stay the same.
  EXPECT_DOUBLE_EQ(1234.0 * 2.0, tracker.ComputeRateForIntervalNow(1000));
  EXPECT_DOUBLE_EQ(1234.0 * 2.0, tracker.ComputeRateNow());
  EXPECT_EQ(1234U * 2, tracker.TotalSampleCount());
  EXPECT_DOUBLE_EQ(1234.0 * 2.0, tracker.ComputeTotalRateNow());

  // Do nothing and advance by a second. We should drop down to zero.
  tracker.AdvanceTime(1000);
  EXPECT_DOUBLE_EQ(0.0, tracker.ComputeRateForIntervalNow(1000));
  EXPECT_DOUBLE_EQ(0.0, tracker.ComputeRateNow());
  EXPECT_EQ(1234U * 2, tracker.TotalSampleCount());
  EXPECT_DOUBLE_EQ(1234.0, tracker.ComputeTotalRateNow());

  // Send a bunch of data at a constant rate for 5.5 "seconds".
  // We should report the rate properly.
  for (int i = 0; i < 5500; i += 100) {
    tracker.AddSamplesNow(9876U);
    tracker.AdvanceTime(100);
  }
  EXPECT_DOUBLE_EQ(9876.0 * 10.0, tracker.ComputeRateForIntervalNow(1000));
  EXPECT_DOUBLE_EQ(9876.0 * 10.0, tracker.ComputeRateNow());
  EXPECT_EQ(1234U * 2 + 9876U * 55, tracker.TotalSampleCount());
  EXPECT_DOUBLE_EQ((1234.0 * 2.0 + 9876.0 * 55.0) / 7.5,
                   tracker.ComputeTotalRateNow());

  // Advance the clock by 500 ms. Since we sent nothing over this half-second,
  // the reported rate should be reduced by half.
  tracker.AdvanceTime(500);
  EXPECT_DOUBLE_EQ(9876.0 * 5.0, tracker.ComputeRateForIntervalNow(1000));
  EXPECT_DOUBLE_EQ(9876.0 * 5.0, tracker.ComputeRateNow());
  EXPECT_EQ(1234U * 2 + 9876U * 55, tracker.TotalSampleCount());
  EXPECT_DOUBLE_EQ((1234.0 * 2.0 + 9876.0 * 55.0) / 8.0,
                   tracker.ComputeTotalRateNow());

  // Rate over the last half second should be zero.
  EXPECT_DOUBLE_EQ(0.0, tracker.ComputeRateForIntervalNow(500));
}

TEST(RateTrackerTest, TestLongPeriodBetweenSamples) {
  RateTrackerForTest tracker;
  tracker.AddSamplesNow(1);
  tracker.AdvanceTime(1000);
  EXPECT_DOUBLE_EQ(1.0, tracker.ComputeRateNow());

  tracker.AdvanceTime(2000);
  EXPECT_DOUBLE_EQ(0.0, tracker.ComputeRateNow());

  tracker.AdvanceTime(2000);
  tracker.AddSamplesNow(1);
  EXPECT_DOUBLE_EQ(1.0, tracker.ComputeRateNow());
}

TEST(RateTrackerTest, TestRolloff) {
  RateTrackerForTest tracker;
  for (int i = 0; i < 10; ++i) {
    tracker.AddSamplesNow(1U);
    tracker.AdvanceTime(100);
  }
  EXPECT_DOUBLE_EQ(10.0, tracker.ComputeRateNow());

  for (int i = 0; i < 10; ++i) {
    tracker.AddSamplesNow(1U);
    tracker.AdvanceTime(50);
  }
  EXPECT_DOUBLE_EQ(15.0, tracker.ComputeRateNow());
  EXPECT_DOUBLE_EQ(20.0, tracker.ComputeRateForIntervalNow(500));

  for (int i = 0; i < 10; ++i) {
    tracker.AddSamplesNow(1U);
    tracker.AdvanceTime(50);
  }
  EXPECT_DOUBLE_EQ(20.0, tracker.ComputeRateNow());
}

TEST(RateTrackerTest, TestGetUnitSecondsAfterInitialValue) {
  RateTrackerForTest tracker;
  tracker.AddSamplesNow(1234);
  tracker.AdvanceTime(1000);
  EXPECT_DOUBLE_EQ(1234.0, tracker.ComputeRateForIntervalNow(1000));
}

TEST(RateTrackerTest, TestLargeNumbers) {
  RateTrackerForTest tracker;
  const uint64_t large_number = 0x100000000;
  tracker.AddSamplesNow(large_number);
  tracker.AdvanceTime(1000);
  tracker.AddSamplesNow(large_number);
  EXPECT_DOUBLE_EQ(large_number * 2, tracker.ComputeRateNow());
}

}  // namespace basic
