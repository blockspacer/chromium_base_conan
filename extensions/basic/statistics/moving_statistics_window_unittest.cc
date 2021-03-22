/*
 *  Copyright 2012 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "basic/statistics/moving_statistics_window.h" // IWYU pragma: associated

#include "testing/gtest/include/gtest/gtest.h"

#include <random>

namespace basic {

namespace {

const double kLearningRate = 0.5;

// Add |n| samples drawn from uniform distribution in [a;b].
void FillStatsFromUniformDistribution(MovingStatisticsWindow<double>& stats,
                                      int n,
                                      double a,
                                      double b) {
  std::mt19937 gen{std::random_device()()};
  std::uniform_real_distribution<> dis(a, b);

  for (int i = 1; i <= n; i++) {
    stats.AddSample(dis(gen));
  }
}
}  // namespace

TEST(MovingStatisticsWindowTest, ZeroSamples) {
  MovingStatisticsWindow<int> accum(10);

  EXPECT_EQ(0U, accum.count());
  EXPECT_DOUBLE_EQ(0.0, accum.ComputeMean());
  EXPECT_DOUBLE_EQ(0.0, accum.EstimatedVariance());
  EXPECT_EQ(0, accum.ComputeMin());
  EXPECT_EQ(0, accum.ComputeMax());
}

TEST(MovingStatisticsWindowTest, SomeSamples) {
  MovingStatisticsWindow<int> accum(10);
  for (int i = 0; i < 4; ++i) {
    accum.AddSample(i);
  }

  EXPECT_EQ(4U, accum.count());
  EXPECT_DOUBLE_EQ(1.5, accum.ComputeMean());
  EXPECT_NEAR(2.26666, accum.ComputeWeightedMean(kLearningRate), 0.01);
  EXPECT_DOUBLE_EQ(1.25, accum.EstimatedVariance());
  EXPECT_EQ(0, accum.ComputeMin());
  EXPECT_EQ(3, accum.ComputeMax());
}

TEST(MovingStatisticsWindowTest, RollingSamples) {
  MovingStatisticsWindow<int> accum(10);
  for (int i = 0; i < 12; ++i) {
    accum.AddSample(i);
  }

  EXPECT_EQ(10U, accum.count());
  EXPECT_DOUBLE_EQ(6.5, accum.ComputeMean());
  EXPECT_NEAR(10.0, accum.ComputeWeightedMean(kLearningRate), 0.01);
  EXPECT_NEAR(9.0, accum.EstimatedVariance(), 1.0);
  EXPECT_EQ(2, accum.ComputeMin());
  EXPECT_EQ(11, accum.ComputeMax());
}

TEST(MovingStatisticsWindowTest, ResetSamples) {
  MovingStatisticsWindow<int> accum(10);

  for (int i = 0; i < 10; ++i) {
    accum.AddSample(100);
  }
  EXPECT_EQ(10U, accum.count());
  EXPECT_DOUBLE_EQ(100.0, accum.ComputeMean());
  EXPECT_EQ(100, accum.ComputeMin());
  EXPECT_EQ(100, accum.ComputeMax());

  accum.Reset();
  EXPECT_EQ(0U, accum.count());

  for (int i = 0; i < 5; ++i) {
    accum.AddSample(i);
  }

  EXPECT_EQ(5U, accum.count());
  EXPECT_DOUBLE_EQ(2.0, accum.ComputeMean());
  EXPECT_EQ(0, accum.ComputeMin());
  EXPECT_EQ(4, accum.ComputeMax());
}

TEST(MovingStatisticsWindowTest, RollingSamplesDouble) {
  MovingStatisticsWindow<double> accum(10);
  for (int i = 0; i < 23; ++i) {
    accum.AddSample(5 * i);
  }

  EXPECT_EQ(10u, accum.count());
  EXPECT_DOUBLE_EQ(87.5, accum.ComputeMean());
  EXPECT_NEAR(105.049, accum.ComputeWeightedMean(kLearningRate), 0.1);
  EXPECT_NEAR(229.166667, accum.EstimatedVariance(), 25);
  EXPECT_DOUBLE_EQ(65.0, accum.ComputeMin());
  EXPECT_DOUBLE_EQ(110.0, accum.ComputeMax());
}

TEST(MovingStatisticsWindowTest, ComputeWeightedMeanCornerCases) {
  MovingStatisticsWindow<int> accum(10);
  EXPECT_DOUBLE_EQ(0.0, accum.ComputeWeightedMean(kLearningRate));
  EXPECT_DOUBLE_EQ(0.0, accum.ComputeWeightedMean(0.0));
  EXPECT_DOUBLE_EQ(0.0, accum.ComputeWeightedMean(1.1));

  for (int i = 0; i < 8; ++i) {
    accum.AddSample(i);
  }

  EXPECT_DOUBLE_EQ(3.5, accum.ComputeMean());
  EXPECT_DOUBLE_EQ(3.5, accum.ComputeWeightedMean(0));
  EXPECT_DOUBLE_EQ(3.5, accum.ComputeWeightedMean(1.1));
  EXPECT_NEAR(6.0, accum.ComputeWeightedMean(kLearningRate), 0.1);
}

TEST(MovingStatisticsWindowTest, VarianceFromUniformDistribution) {
  // Check variance converge to 1/12 for [0;1) uniform distribution.
  // Acts as a sanity check for NumericStabilityForVariance test.
  MovingStatisticsWindow<double> stats(/*max_count=*/0.5e6);
  FillStatsFromUniformDistribution(stats, 1e6, 0, 1);

  EXPECT_NEAR(stats.EstimatedVariance(), 1. / 12, 1e-3);
}

TEST(MovingStatisticsWindowTest, NumericStabilityForVariance) {
  // Same test as VarianceFromUniformDistribution,
  // except the range is shifted to [1e9;1e9+1).
  // Variance should also converge to 1/12.
  // NB: Although we lose precision for the samples themselves, the fractional
  //     part still enjoys 22 bits of mantissa and errors should even out,
  //     so that couldn't explain a mismatch.
  MovingStatisticsWindow<double> stats(/*max_count=*/0.5e6);
  FillStatsFromUniformDistribution(stats, 1e6, 1e9, 1e9 + 1);

  EXPECT_NEAR(stats.EstimatedVariance(), 1. / 12, 1e-3);
}

} // namespace basic
