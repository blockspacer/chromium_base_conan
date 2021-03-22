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

#include <cstdint>
#include <cstdlib>
#include <memory>

namespace basic {

// USAGE
//
//  // For fps: Low means low enough to be bad, high means high enough to be good
//  const int kLowFpsThreshold = 12;
//  const int kHighFpsThreshold = 14;
//  const int kNumMeasurements = 10;
//
//  basic::QualityThreshold fps_threshold(kLowFpsThreshold,
//                     kHighFpsThreshold,
//                     kBadFraction,
//                     kNumMeasurements);
//
//  bool prev_fps_bad = !fps_threshold.IsHigh().value_or(true);
//  if(prev_fps_bad) { VLOG(9) << "Bad prev. fps"; }
//
//  double fps = render_fps_tracker.ComputeRateForIntervalNow(now - last_sample_time_);
//  fps_threshold.AddMeasurement(static_cast<int>(fps));
//
//  base::Optional<double> fps_variance_opt = fps_threshold.CalculateVariance();
//
//  bool fps_bad = !fps_threshold.IsHigh().value_or(true);
//  if(fps_bad) { VLOG(9) << "Bad fps"; }
//
//  const int kBadCallMinRequiredSamples = 10;
//  base::Optional<double> fps_fraction =
//      fps_threshold.FractionHigh(kBadCallMinRequiredSamples);
//  if (fps_fraction) {
//    HISTOGRAM_PERCENTAGE("App.Video.BadCall.FrameRate",
//                             static_cast<int>(100 * (1 - *fps_fraction)));
//  }
//
class QualityThreshold {
 public:
  // Both thresholds are inclusive, i.e. measurement >= high signifies a high
  // state, while measurement <= low signifies a low state.
  QualityThreshold(int low_threshold,
                   int high_threshold,
                   float fraction,
                   int max_measurements);
  ~QualityThreshold();

  void AddMeasurement(int measurement);
  base::Optional<bool> IsHigh() const;
  base::Optional<double> CalculateVariance() const;
  base::Optional<double> FractionHigh(int min_required_samples) const;

 private:
  const std::unique_ptr<int[]> buffer_;
  const int max_measurements_;
  const float fraction_;
  const int low_threshold_;
  const int high_threshold_;
  int until_full_;
  int next_index_;
  base::Optional<bool> is_high_;
  int sum_;
  int count_low_;
  int count_high_;
  int num_high_states_;
  int num_certain_states_;
};

} // namespace basic
