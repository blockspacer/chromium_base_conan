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

#include "basic/statistics/percentile_filter.h"

#include <base/logging.h>

#include <list>

namespace basic {

// Class to efficiently get moving median filter from a stream of samples.
//
// The moving median isn’t as popular as the moving average,
// but offers some interesting capabilities.
// The moving median provides a more robust estimate of the trend
// compare to the moving average.
// It isn’t affected by outliers: in fact, it removes them!
//
// Moving medians are commonly used to smooth or remove the noise of a time series.
// Use it for robust statistics that shouldn’t be affected by outliers or anomalies.
//
// The moving median matches the definition of a robust statistic.
// "A minor error [the anomaly] in the mathematical model [the moving median]
// should cause only a small error in the final conclusions".
//
template <typename T>
class MovingMedianFilter {
 public:
  // Construct filter. |window_size| is how many latest samples are stored and
  // used to take median. |window_size| must be positive.
  explicit MovingMedianFilter(size_t window_size);

  // Insert a new sample.
  void Insert(const T& value);

  // Removes all samples;
  void Reset();

  // Get median over the latest window.
  T GetFilteredValue() const;

  // The number of samples that are currently stored.
  size_t GetNumberOfSamplesStored() const;

 private:
  PercentileFilter<T> percentile_filter_;
  std::list<T> samples_;
  size_t samples_stored_;
  const size_t window_size_;

  DISALLOW_COPY_AND_ASSIGN(MovingMedianFilter);
};

template <typename T>
MovingMedianFilter<T>::MovingMedianFilter(size_t window_size)
    : percentile_filter_(0.5f), samples_stored_(0), window_size_(window_size) {
  CHECK_GT(window_size, 0);
}

template <typename T>
void MovingMedianFilter<T>::Insert(const T& value) {
  percentile_filter_.Insert(value);
  samples_.emplace_back(value);
  ++samples_stored_;
  if (samples_stored_ > window_size_) {
    percentile_filter_.Erase(samples_.front());
    samples_.pop_front();
    --samples_stored_;
  }
}

template <typename T>
T MovingMedianFilter<T>::GetFilteredValue() const {
  return percentile_filter_.GetPercentileValue();
}

template <typename T>
void MovingMedianFilter<T>::Reset() {
  percentile_filter_.Reset();
  samples_.clear();
  samples_stored_ = 0;
}

template <typename T>
size_t MovingMedianFilter<T>::GetNumberOfSamplesStored() const {
  return samples_stored_;
}

} // namespace basic
