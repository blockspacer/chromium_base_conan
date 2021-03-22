/*
 *  Copyright 2012 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "basic/statistics/moving_average.h" // IWYU pragma: associated

#include "base/check_op.h"

#include <algorithm>

namespace basic {

MovingAverage::MovingAverage(size_t window_size) : history_(window_size, 0) {
  // Limit window size to avoid overflow.
  DCHECK_LE(window_size, (int64_t{1} << 32) - 1);
}

MovingAverage::~MovingAverage() = default;

void MovingAverage::AddSample(int sample) {
  count_++;
  size_t index = count_ % history_.size();
  if (count_ > history_.size())
    sum_ -= history_[index];
  sum_ += sample;
  history_[index] = sample;
}

base::Optional<int> MovingAverage::GetAverageRoundedDown() const {
  if (count_ == 0)
    return base::nullopt;
  return sum_ / Size();
}

base::Optional<int> MovingAverage::GetAverageRoundedToClosest() const {
  if (count_ == 0)
    return base::nullopt;
  return (sum_ + Size() / 2) / Size();
}

base::Optional<double> MovingAverage::GetUnroundedAverage() const {
  if (count_ == 0)
    return base::nullopt;
  return sum_ / static_cast<double>(Size());
}

void MovingAverage::Reset() {
  count_ = 0;
  sum_ = 0;
}

size_t MovingAverage::Size() const {
  return std::min(count_, history_.size());
}


} // namespace basic
