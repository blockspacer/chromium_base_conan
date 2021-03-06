// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <stdint.h>

namespace basic {

// Calculates the weighted mean (and variance) of a set of values. Values can be
// added to or removed from the mean.
class WeightedMean {
 public:
  WeightedMean();

  double weighted_mean() const { return weighted_mean_; }
  // The weighted variance should be calculated as variance_sum()/sum_weights().
  double variance_sum() const { return variance_sum_; }
  double sum_weights() const { return sum_weights_; }
  double sum_squared_weights() const { return sum_squared_weights_; }

  // Adds |value| to the mean if |weight| is positive. Removes |value| from
  // the mean if |weight| is negative. Has no effect if |weight| is 0.
  void AddSample(int64_t value, double weight);

 private:
  double weighted_mean_;
  double variance_sum_;
  double sum_weights_;
  double sum_squared_weights_;
};

}  // namespace basic
