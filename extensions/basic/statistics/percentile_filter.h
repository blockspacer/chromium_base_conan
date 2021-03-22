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
#include <base/check_op.h>

#include <set>

namespace basic {

// Class to efficiently get the percentile value from a group of observations.
// The percentile is the value below which a given percentage of the
// observations fall.
//
// Percentile is a number where a certain percentage of scores
// fall below that number.
// You might know that you scored 67 out of 90 on a test.
// But that figure has no real meaning unless you know
// what percentile you fall into.
// If you know that your score is in the 90th percentile,
// that means you scored better than 90% of people who took the test.
// For example, the 70th percentile on the 2013 GRE test was 156.
// That means if you scored 156 on the exam,
// your score was better than 70 percent of test takers.
//
// The 25th percentile is also called the first quartile.
// The 50th percentile is generally the median.
// The 75th percentile is also called the third quartile.
//
// For example, the 90th percentile (abbreviated as p90)
// indicates that 90% of the sample is below that value
// and the rest of the values (that is, the other 10%) are above it.
//
// USAGE
// // use case: you need to estimate time needed to decode frame in some video
//
// Return the |kPercentile| value in RequiredDecodeTimeMs().
// const float kPercentile = 0.95f;
//
// // data structure that allows efficient retrieval of the percentile value.
// basic::PercentileFilter<int64_t> filter(kPercentile);
//
// // Insert new decode time value.
// filter.Insert(decode_time_ms);
//
// // Pop old decode time values.
// while (!history_.empty() &&
//        now_ms - history_.front().sample_time_ms > kTimeLimitMs) {
//   filter.Erase(history_.front().decode_time_ms);
//   history_.pop();
// }
//
// // time needed to decode frame in some video
// int64_t requiredDecodeTimeMs = filter.GetPercentileValue();
//
template <typename T>
class PercentileFilter {
 public:
  // Construct filter. |percentile| should be between 0 and 1.
  explicit PercentileFilter(float percentile);

  // Insert one observation. The complexity of this operation is logarithmic in
  // the size of the container.
  void Insert(const T& value);

  // Remove one observation or return false if |value| doesn't exist in the
  // container. The complexity of this operation is logarithmic in the size of
  // the container.
  bool Erase(const T& value);

  // Get the percentile value. The complexity of this operation is constant.
  T GetPercentileValue() const;

  // Removes all the stored observations.
  void Reset();

 private:
  // Update iterator and index to point at target percentile value.
  void UpdatePercentileIterator();

  const float percentile_;
  std::multiset<T> set_;
  // Maintain iterator and index of current target percentile value.
  typename std::multiset<T>::iterator percentile_it_;
  int64_t percentile_index_;
};

template <typename T>
PercentileFilter<T>::PercentileFilter(float percentile)
    : percentile_(percentile),
      percentile_it_(set_.begin()),
      percentile_index_(0) {
  CHECK_GE(percentile, 0.0f);
  CHECK_LE(percentile, 1.0f);
}

template <typename T>
void PercentileFilter<T>::Insert(const T& value) {
  // Insert element at the upper bound.
  set_.insert(value);
  if (set_.size() == 1u) {
    // First element inserted - initialize percentile iterator and index.
    percentile_it_ = set_.begin();
    percentile_index_ = 0;
  } else if (value < *percentile_it_) {
    // If new element is before us, increment |percentile_index_|.
    ++percentile_index_;
  }
  UpdatePercentileIterator();
}

template <typename T>
bool PercentileFilter<T>::Erase(const T& value) {
  typename std::multiset<T>::const_iterator it = set_.lower_bound(value);
  // Ignore erase operation if the element is not present in the current set.
  if (it == set_.end() || *it != value)
    return false;
  if (it == percentile_it_) {
    // If same iterator, update to the following element. Index is not
    // affected.
    percentile_it_ = set_.erase(it);
  } else {
    set_.erase(it);
    // If erased element was before us, decrement |percentile_index_|.
    if (value <= *percentile_it_)
      --percentile_index_;
  }
  UpdatePercentileIterator();
  return true;
}

template <typename T>
void PercentileFilter<T>::UpdatePercentileIterator() {
  if (set_.empty())
    return;
  const int64_t index = static_cast<int64_t>(percentile_ * (set_.size() - 1));
  std::advance(percentile_it_, index - percentile_index_);
  percentile_index_ = index;
}

template <typename T>
T PercentileFilter<T>::GetPercentileValue() const {
  return set_.empty() ? 0 : *percentile_it_;
}

template <typename T>
void PercentileFilter<T>::Reset() {
  set_.clear();
  percentile_it_ = set_.begin();
  percentile_index_ = 0;
}

} // namespace basic
