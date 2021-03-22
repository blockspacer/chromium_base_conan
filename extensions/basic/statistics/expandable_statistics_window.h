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

#include <base/logging.h>
#include <base/optional.h>
#include <base/check_op.h>

#include <basic/numerics/math_utils.h>

#include <cstdint>
#include <cstdlib>
#include <cmath>

namespace basic {

// tl;dr: Robust and efficient online computation of statistics,
//        using Welford's method for variance. [1]
//
// This should be your go-to class if you ever need to compute
// min, max, mean, variance and standard deviation
// and you do not need to remove samples from window.
//
/// \note `ExpandableStatisticsWindow` does not store added samples,
/// only re-computes min, max, mean, variance and standard deviation.
/// So you can use `ExpandableStatisticsWindow` to analize infinite data stream
/// without need to worry about window size limit
/// (unlike `MovingStatisticsWindow`).
//
/// \note RemoveSample() won't affect min and max.
/// If you want a full-fledged moving window over N last samples,
/// please use `MovingStatisticsWindow`.
//
// The measures return base::nullopt if no samples were fed (Size() == 0),
// otherwise the returned optional is guaranteed to contain a value.
//
// [1]
// https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm
//
// USAGE
//
// ExpandableStatisticsWindow<int> stats;
// stats.AddSample(2);
// stats.AddSample(2);
// stats.AddSample(-1);
// stats.AddSample(5);
//
// EXPECT_DOUBLE_EQ(*stats.GetMean(), 2.0);
// EXPECT_DOUBLE_EQ(*stats.GetVariance(), 4.5);
// EXPECT_DOUBLE_EQ(*stats.GetStandardDeviation(), sqrt(4.5));

// The type T is a scalar which must be convertible to double.
// Rationale: we often need greater precision for measures
//            than for the samples themselves.
template <typename T>
class ExpandableStatisticsWindow {
 public:
  // Update stats ////////////////////////////////////////////

  // Add a value participating in the statistics in O(1) time.
  void AddSample(T sample) {
    max_ = std::max(max_, sample);
    min_ = std::min(min_, sample);
    ++size_;
    // Welford's incremental update.
    const double delta = sample - mean_;
    mean_ += delta / size_;
    const double delta2 = sample - mean_;
    cumul_ += delta * delta2;
  }

  /// \note It is safe to remove samples if you need to compute
  /// mean, variance and standard deviation.
  /// But min and max may become invalid after removal (not updated).
  //
  // Remove a previously added value in O(1) time.
  // Nb: This doesn't affect min or max.
  // Calling RemoveSample when Size()==0 is incorrect.
  void RemoveSample(T sample) {
    DCHECK_GT(Size(), 0);
    // In production, just saturate at 0.
    if (Size() == 0) {
      return;
    }
    // Since samples order doesn't matter, this is the
    // exact reciprocal of Welford's incremental update.
    --size_;
    const double delta = sample - mean_;
    mean_ -= delta / size_;
    const double delta2 = sample - mean_;
    cumul_ -= delta * delta2;
  }

  // Merge other stats, as if samples were added one by one, but in O(1).
  void MergeStatistics(const ExpandableStatisticsWindow<T>& other) {
    if (other.size_ == 0) {
      return;
    }
    max_ = std::max(max_, other.max_);
    min_ = std::min(min_, other.min_);
    const int64_t new_size = size_ + other.size_;
    const double new_mean =
        (mean_ * size_ + other.mean_ * other.size_) / new_size;
    // Each cumulant must be corrected.
    //   * from: sum((x_i - mean_)?)
    //   * to:   sum((x_i - new_mean)?)
    auto delta = [new_mean](const ExpandableStatisticsWindow<T>& stats) {
      return stats.size_ * (new_mean * (new_mean - 2 * stats.mean_) +
                            stats.mean_ * stats.mean_);
    };
    cumul_ = cumul_ + delta(*this) + other.cumul_ + delta(other);
    mean_ = new_mean;
    size_ = new_size;
  }

  // Get Measures ////////////////////////////////////////////

  // Returns number of samples involved via AddSample() or MergeStatistics(),
  // minus number of times RemoveSample() was called.
  int64_t Size() const { return size_; }

  // Returns minimum among all seen samples, in O(1) time.
  // This isn't affected by RemoveSample().
  base::Optional<T> GetMin() const {
    if (size_ == 0) {
      return base::nullopt;
    }
    return min_;
  }

  // Returns maximum among all seen samples, in O(1) time.
  // This isn't affected by RemoveSample().
  base::Optional<T> GetMax() const {
    if (size_ == 0) {
      return base::nullopt;
    }
    return max_;
  }

  // Returns mean in O(1) time.
  base::Optional<double> GetMean() const {
    if (size_ == 0) {
      return base::nullopt;
    }
    return mean_;
  }

  // Returns unbiased sample variance in O(1) time.
  base::Optional<double> GetVariance() const {
    if (size_ == 0) {
      return base::nullopt;
    }
    return cumul_ / size_;
  }

  // Returns unbiased standard deviation in O(1) time.
  base::Optional<double> GetStandardDeviation() const {
    if (size_ == 0) {
      return base::nullopt;
    }
    return std::sqrt(*GetVariance());
  }

 private:
  int64_t size_ = 0;  // Samples seen.
  T min_ = infinity_or_max<T>();
  T max_ = minus_infinity_or_min<T>();
  double mean_ = 0;
  double cumul_ = 0;  // Variance * size_, sometimes noted m2.
};

} // namespace basic
