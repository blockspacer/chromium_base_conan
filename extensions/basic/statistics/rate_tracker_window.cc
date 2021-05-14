// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/statistics/rate_tracker_window.h" // IWYU pragma: associated

#include <base/time/time.h>

#include <algorithm>

namespace basic {

RateTrackerWindow::RateTrackerWindow(base::TimeDelta time_window)
    : time_window_(time_window), sum_(0) {
  DCHECK_GT(time_window, base::TimeDelta());
}

RateTrackerWindow::~RateTrackerWindow() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
}

void RateTrackerWindow::Record(int64_t value) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  base::TimeTicks now = tick_clock_->NowTicks();
  EvictOldDataPoints(now);
  sum_ += value;
  data_points_.push(std::make_pair(now, value));
}

double RateTrackerWindow::Rate() const {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  // This is just to ensure the rate is up to date.
  const_cast<RateTrackerWindow*>(this)->EvictOldDataPoints(tick_clock_->NowTicks());
  return sum_ / time_window_.InSecondsF();
}

void RateTrackerWindow::EvictOldDataPoints(base::TimeTicks now) {
  // Remove data points outside of the window.
  base::TimeTicks window_start = now - time_window_;

  while (!data_points_.empty()) {
    if (data_points_.front().first > window_start)
      break;

    sum_ -= data_points_.front().second;
    data_points_.pop();
  }
}

} // namespace basic
