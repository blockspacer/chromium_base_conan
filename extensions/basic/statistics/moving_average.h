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

namespace basic {

// Calculates average over fixed size window. If there are less than window
// size elements, calculates average of all inserted so far elements.
//
// Moving averages are commonly used to smooth or remove the noise of a time series.
// It works well, but the presence of anomalies can affect the underlying trend calculation.
// See `MovingMedianFilter` for robust statistics that shouldn’t be affected by outliers or anomalies.
//
// USAGE
// // need to detect freeze
// basic::MovingAverage render_interframe_delays;
//
// const uint32_t kMinFrameSamplesToDetectFreeze = 5;
// const uint32_t kMinIncreaseForFreezeMs = 150;
//
// // interframe_delay_ms - updates per each rendered frame
// render_interframe_delays.AddSample(interframe_delay_ms);
//
// bool was_freeze = false;
// if (render_interframe_delays.Size() >= kMinFrameSamplesToDetectFreeze) {
//   const base::Optional<int64_t> avg_interframe_delay =
//       render_interframe_delays.GetAverageRoundedDown();
//   DCHECK(avg_interframe_delay);
//   was_freeze = interframe_delay_ms >=
//                std::max(3 * *avg_interframe_delay,
//                         *avg_interframe_delay + kMinIncreaseForFreezeMs);
// }
//
class MovingAverage {
 public:
  // Maximum supported window size is 2^32 - 1.
  explicit MovingAverage(size_t window_size);
  ~MovingAverage();
  // MovingAverage is neither copyable nor movable.
  MovingAverage(const MovingAverage&) = delete;
  MovingAverage& operator=(const MovingAverage&) = delete;

  // Adds new sample. If the window is full, the oldest element is pushed out.
  void AddSample(int sample);

  // Returns rounded down average of last |window_size| elements or all
  // elements if there are not enough of them. Returns nullopt if there were
  // no elements added.
  base::Optional<int> GetAverageRoundedDown() const;

  // Same as above but rounded to the closest integer.
  base::Optional<int> GetAverageRoundedToClosest() const;

  // Returns unrounded average over the window.
  base::Optional<double> GetUnroundedAverage() const;

  // Resets to the initial state before any elements were added.
  void Reset();

  // Returns number of elements in the window.
  size_t Size() const;

 private:
  // Total number of samples added to the class since last reset.
  size_t count_ = 0;
  // Sum of the samples in the moving window.
  int64_t sum_ = 0;
  // Circular buffer for all the samples in the moving window.
  // Size is always |window_size|
  std::vector<int> history_;
};

} // namespace basic
