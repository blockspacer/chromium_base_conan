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

#include <cstdint>
#include <cstdlib>

namespace basic {

// Computes units per second over a given interval by tracking the units over
// each bucket of a given size and calculating the instantaneous rate assuming
// that over each bucket the rate was constant.
//
// See also GCRA, Token Bucket and a Leaky Bucket algorithms.
//
// USAGE
//
// basic::RateTracker render_fps_tracker(/*bucket_milliseconds*/ 100, /*bucket_count*/ 10u);
//
// render_fps_tracker.AddSamples(1);
//
// double fps =
//     render_fps_tracker.ComputeRateForIntervalNow(now - last_sample_time_);
// VLOG(9) << "App.FrameTime " << rendered_fps;
//
// const int kMinRequiredSamples = 200;
// int samples = static_cast<int>(render_fps_tracker.TotalSampleCount());
// if (samples >= kMinRequiredSamples) {
//   int rendered_fps = round(render_fps_tracker.ComputeTotalRateNow());
//   HISTOGRAM_COUNTS_100("App.RenderFramesPerSecond",
//                            rendered_fps);
//   VLOG(9) << "App.RenderFramesPerSecond " << rendered_fps;
//   HISTOGRAM_COUNTS_100000(
//       "App.RenderSqrtPixelsPerSecond",
//       round(render_pixel_tracker_.ComputeTotalRateNow()));
// }
//
class RateTracker {
 public:
  RateTracker(int64_t bucket_milliseconds, size_t bucket_count);
  virtual ~RateTracker();

  // Computes the average rate over the most recent interval_milliseconds,
  // or if the first sample was added within this period, computes the rate
  // since the first sample was added.
  double ComputeRateForIntervalNow(int64_t interval_milliseconds) const;

  // for tests
  double ComputeRateForIntervalWithTs(
      int64_t interval_milliseconds
      , int64_t current_time) const;

  // Computes the average rate over the rate tracker's recording interval
  // of bucket_milliseconds * bucket_count.
  double ComputeRateNow() const {
    return ComputeRateForIntervalWithTs(bucket_milliseconds_ *
                                  static_cast<int64_t>(bucket_count_), Time());
  }

  // Computes the average rate since the first sample was added to the
  // rate tracker.
  double ComputeTotalRateNow() const;

  // for tests
  double ComputeTotalRateWithTs(int64_t current_time) const;

  // The total number of samples added.
  int64_t TotalSampleCount() const;

  // (time now - time first added sample added)
  // in milliseconds
  int64_t ElapsedTime() const;

  // (provided time - time first added sample added)
  // in milliseconds
  int64_t ElapsedTimeWithTs(int64_t current_time) const;

  // Reads the current time in order to determine the appropriate bucket for
  // these samples, and increments the count for that bucket by sample_count.
  void AddSamplesNow(int64_t sample_count);

  // for tests
  void AddSamplesWithTs(int64_t sample_count, int64_t current_time);

 protected:
  // overrideable for tests
  virtual int64_t Time() const;

 private:
  void EnsureInitializedWithTs(int64_t current_time);
  size_t NextBucketIndex(size_t bucket_index) const;

  const int64_t bucket_milliseconds_;
  const size_t bucket_count_;
  int64_t* sample_buckets_;
  size_t total_sample_count_;
  // A bucket represents a time interval over which aggregated data is computed.
  // For example, a bucket can represent user's average speed
  // and average heart rate over a 1 hour interval
  size_t current_bucket_;
  int64_t bucket_start_time_milliseconds_;
  int64_t initialization_time_milliseconds_;
};

} // namespace basic
