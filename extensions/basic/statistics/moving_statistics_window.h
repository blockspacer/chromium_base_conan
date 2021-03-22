/*
 *  Copyright 2012 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#pragma once

#include "basic/statistics/expandable_statistics_window.h"

#include <base/logging.h>

#include <cstdint>
#include <cstdlib>
#include <cstddef>
#include <algorithm>
#include <vector>

namespace basic {

// MovingStatisticsWindow stores and reports statistics
// over N most recent samples
// i.e. removes oldest sample if reached max. for stored samples count.
//
// MovingStatisticsWindow is full-fledged moving window over N last samples
// (unlike `ExpandableStatisticsWindow`).
//
// T is assumed to be an int, long, double or float.
//
/// \note `MovingStatisticsWindow` stores only last N added samples.
/// So you can NOT use `MovingStatisticsWindow` to analize infinite data stream
/// (unlike `ExpandableStatisticsWindow`).
//
// USAGE
//
// // max. 10 samples, but added 12
//
// MovingStatisticsWindow<int> accum(10);
// for (int i = 0; i < 12; ++i) {
//   accum.AddSample(i);
// }
//
// EXPECT_EQ(10U, accum.count());
// EXPECT_DOUBLE_EQ(6.5, accum.ComputeMean());
// EXPECT_NEAR(10.0, accum.ComputeWeightedMean(kLearningRate), 0.01);
// EXPECT_NEAR(9.0, accum.EstimatedVariance(), 1.0);
// EXPECT_EQ(2, accum.ComputeMin());
// EXPECT_EQ(11, accum.ComputeMax());
//
template <typename T>
class MovingStatisticsWindow {
 public:
  explicit MovingStatisticsWindow(size_t max_count) : samples_(max_count) {
    DCHECK(max_count > 0);
    Reset();
  }
  ~MovingStatisticsWindow() {}

  size_t max_count() const { return samples_.size(); }

  size_t count() const { return static_cast<size_t>(stats_.Size()); }

  void Reset() {
    stats_ = basic::ExpandableStatisticsWindow<T>();
    next_index_ = 0U;
    max_ = T();
    max_stale_ = false;
    min_ = T();
    min_stale_ = false;
  }

  void AddSample(T sample) {
    if (count() == max_count()) {
      // Remove oldest sample.
      T sample_to_remove = samples_[next_index_];
      stats_.RemoveSample(sample_to_remove);
      if (sample_to_remove >= max_) {
        max_stale_ = true;
      }
      if (sample_to_remove <= min_) {
        min_stale_ = true;
      }
    }
    // Add new sample.
    samples_[next_index_] = sample;
    if (count() == 0 || sample >= max_) {
      max_ = sample;
      max_stale_ = false;
    }
    if (count() == 0 || sample <= min_) {
      min_ = sample;
      min_stale_ = false;
    }
    stats_.AddSample(sample);
    // Update next_index_.
    next_index_ = (next_index_ + 1) % max_count();
  }

  double ComputeMean() const { return stats_.GetMean().value_or(0); }

  /// \note loops over last N stored samples,
  /// so take care of performance
  T ComputeMax() const {
    if (max_stale_) {
      DCHECK(count() > 0)
          << "It shouldn't be possible for max_stale_ && count() == 0";
      max_ = samples_[next_index_];
      for (size_t i = 1u; i < count(); i++) {
        max_ = std::max(max_, samples_[(next_index_ + i) % max_count()]);
      }
      max_stale_ = false;
    }
    return max_;
  }

  /// \note loops over last N stored samples,
  /// so take care of performance
  T ComputeMin() const {
    if (min_stale_) {
      DCHECK(count() > 0)
          << "It shouldn't be possible for min_stale_ && count() == 0";
      min_ = samples_[next_index_];
      for (size_t i = 1u; i < count(); i++) {
        min_ = std::min(min_, samples_[(next_index_ + i) % max_count()]);
      }
      min_stale_ = false;
    }
    return min_;
  }

  // O(n) time complexity.
  // Weights nth sample with weight (learning_rate)^n. Learning_rate should be
  // between (0.0, 1.0], otherwise the non-weighted mean is returned.
  //
  /// \note loops over last N stored samples,
  /// so take care of performance
  double ComputeWeightedMean(double learning_rate) const {
    if (count() < 1 || learning_rate <= 0.0 || learning_rate >= 1.0) {
      return ComputeMean();
    }
    double weighted_mean = 0.0;
    double current_weight = 1.0;
    double weight_sum = 0.0;
    const size_t max_size = max_count();
    for (size_t i = 0; i < count(); ++i) {
      current_weight *= learning_rate;
      weight_sum += current_weight;
      // Add max_size to prevent underflow.
      size_t index = (next_index_ + max_size - i - 1) % max_size;
      weighted_mean += current_weight * samples_[index];
    }
    return weighted_mean / weight_sum;
  }

  // Compute estimated variance.
  // Estimation is more accurate
  // as the number of samples grows.
  double EstimatedVariance() const { return stats_.GetVariance().value_or(0); }

 private:
  basic::ExpandableStatisticsWindow<T> stats_;
  size_t next_index_;
  mutable T max_;
  mutable bool max_stale_;
  mutable T min_;
  mutable bool min_stale_;
  std::vector<T> samples_;

  DISALLOW_COPY_AND_ASSIGN(MovingStatisticsWindow);
};

} // namespace basic
