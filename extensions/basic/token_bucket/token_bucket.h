/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <basic/strong_types/strong_double.h>

#include <base/macros.h>
#include <base/optional.h>
#include <base/check.h>
#include <base/compiler_specific.h>
#include <base/time/time.h>
#include <base/threading/platform_thread.h>

#include <atomic>
#include <algorithm>
#include <new>

namespace basic {

namespace token_bucket_detail {

//  Memory locations within the same cache line are subject to destructive
//  interference, also known as false sharing, which is when concurrent
//  accesses to these different memory locations from different cores, where at
//  least one of the concurrent accesses is or involves a store operation,
//  induce contention and harm performance.
//
//  Microbenchmarks indicate that pairs of cache lines also see destructive
//  interference under heavy use of atomic operations, as observed for atomic
//  increment on Sandy Bridge.
//
// False-sharing is a harmful pattern to performance that happens
// in a multicores system where each core has its own L1 cache.
// Under such system, caches are designed to remain coherent
// so update of memory by one core is properly broadcasted* to other cores.
// In another word, the data in all the L1 caches are always correct,
// even when they are pointing to the same memory.
// See https://norrischiu.github.io/2018/09/08/Cpp-jargon-1.html
//
#ifdef __cpp_lib_hardware_interference_size
  using std::hardware_constructive_interference_size;
  using std::hardware_destructive_interference_size;
#else
  // Lucky guess ? __cacheline_aligned ? L1_CACHE_BYTES ? L1_CACHE_SHIFT ? ...
  constexpr std::size_t hardware_constructive_interference_size
      = 2 * sizeof(std::max_align_t);
  constexpr std::size_t hardware_destructive_interference_size
      = 2 * sizeof(std::max_align_t);
#endif

} // namespace token_bucket_detail

// Lock-free implementation of the token bucket rate limit algorithm.
//
// A token bucket (http://en.wikipedia.org/wiki/Token_bucket) models a stream
// of events with an average rate and some amount of burstiness. The canonical
// example is a packet switched network: the network can accept some number of
// bytes per second and the bytes come in finite packets (bursts). A token
// bucket stores up to a fixed number of tokens (the burst size). Some number
// of tokens are removed when an event occurs. The tokens are replenished at a
// fixed rate. Failure to allocate tokens implies resource is unavailable and
// caller needs to implement its own retry mechanism. For simple cases where
// caller is okay with a FIFO starvation-free scheduling behavior, there are
// also APIs to 'borrow' from the future effectively assigning a start time to
// the caller when it should proceed with using the resource. It is also
// possible to 'return' previously allocated tokens to make them available to
// other users. Returns in excess of burstSize are considered expired and
// will not be available to later callers.
//
// This implementation records the last time it was updated. This allows the
// token bucket to add tokens "just in time" when tokens are requested.
//
// The "dynamic" base variant allows the token generation rate and maximum
// burst size to change with every token consumption.
//
class BasicDynamicTokenBucket {
 public:
  /**
   * Constructor.
   *
   * @param zeroTime Initial time at which to consider the token bucket
   *                 starting to fill. Defaults to 0, so by default token
   *                 buckets are "full" after construction.
   */
  explicit BasicDynamicTokenBucket(double zeroTime = 0) noexcept
      : zeroTime_(zeroTime) {}

  /**
   * Copy constructor.
   *
   * Thread-safe. (Copy constructors of derived classes may not be thread-safe
   * however.)
   */
  BasicDynamicTokenBucket(const BasicDynamicTokenBucket& other) noexcept
      : zeroTime_(other.zeroTime_.load()) {}

  /**
   * Copy-assignment operator.
   *
   * Warning: not thread safe for the object being assigned to (including
   * self-assignment). Thread-safe for the other object.
   */
  BasicDynamicTokenBucket& operator=(
      const BasicDynamicTokenBucket& other) noexcept {
    zeroTime_ = other.zeroTime_.load();
    return *this;
  }

  /**
   * Re-initialize token bucket.
   *
   * Thread-safe.
   *
   * @param zeroTime Initial time at which to consider the token bucket
   *                 starting to fill. Defaults to 0, so by default token
   *                 bucket is reset to "full".
   */
  void reset(double zeroTime = 0) noexcept { zeroTime_ = zeroTime; }

  /**
   * Returns the current time in seconds since Epoch.
   */
  static double defaultClockNow() noexcept {
    const int nowMs = (base::Time::Now() - base::Time::UnixEpoch()).InMicroseconds();
    /// \todo converts int to double? refactor!
    return static_cast<double>(nowMs) / 1'000'000;
  }

  /**
   * Attempts to consume some number of tokens. Tokens are first added to the
   * bucket based on the time elapsed since the last attempt to consume tokens.
   * Note: Attempts to consume more tokens than the burst size will always
   * fail.
   *
   * Thread-safe.
   *
   * @param toConsume The number of tokens to consume.
   * @param rate Number of tokens to generate per second.
   * @param burstSize Maximum burst size. Must be greater than 0.
   * @param nowInSeconds Current time in seconds. Should be monotonically
   *                     increasing from the nowInSeconds specified in
   *                     this token bucket's constructor.
   * @return True if the rate limit check passed, false otherwise.
   */
  bool consume(
      double toConsume,
      double rate,
      double burstSize,
      double nowInSeconds = defaultClockNow()) {
    DCHECK(rate > 0);
    DCHECK(burstSize > 0);

    if (nowInSeconds <= zeroTime_.load()) {
      return 0;
    }

    return consumeImpl(
        rate, burstSize, nowInSeconds, [toConsume](double& tokens) {
          if (tokens < toConsume) {
            return false;
          }
          tokens -= toConsume;
          return true;
        });
  }

  /**
   * Similar to consume, but always consumes some number of tokens.  If the
   * bucket contains enough tokens - consumes toConsume tokens.  Otherwise the
   * bucket is drained.
   *
   * Thread-safe.
   *
   * @param toConsume The number of tokens to consume.
   * @param rate Number of tokens to generate per second.
   * @param burstSize Maximum burst size. Must be greater than 0.
   * @param nowInSeconds Current time in seconds. Should be monotonically
   *                     increasing from the nowInSeconds specified in
   *                     this token bucket's constructor.
   * @return number of tokens that were consumed.
   */
  double consumeOrDrain(
      double toConsume,
      double rate,
      double burstSize,
      double nowInSeconds = defaultClockNow()) {
    DCHECK(rate > 0);
    DCHECK(burstSize > 0);

    if (nowInSeconds <= zeroTime_.load()) {
      return 0;
    }

    double consumed;
    consumeImpl(
        rate, burstSize, nowInSeconds, [&consumed, toConsume](double& tokens) {
          if (tokens < toConsume) {
            consumed = tokens;
            tokens = 0.0;
          } else {
            consumed = toConsume;
            tokens -= toConsume;
          }
          return true;
        });
    return consumed;
  }

  /**
   * Return extra tokens back to the bucket. This will move the zeroTime_
   * value back based on the rate.
   *
   * Thread-safe.
   */
  void returnTokens(double tokensToReturn, double rate) {
    DCHECK(rate > 0);
    DCHECK(tokensToReturn > 0);

    returnTokensImpl(tokensToReturn, rate);
  }

  /**
   * Like consumeOrDrain but the call will always satisfy the asked for count.
   * It does so by borrowing tokens from the future (zeroTime_ will move
   * forward) if the currently available count isn't sufficient.
   *
   * Returns a Optional<double>. The optional wont be set if the request
   * cannot be satisfied: only case is when it is larger than burstSize. The
   * value of the optional is a double indicating the time in seconds that the
   * caller needs to wait at which the reservation becomes valid. The caller
   * could simply sleep for the returned duration to smooth out the allocation
   * to match the rate limiter or do some other computation in the meantime. In
   * any case, any regular consume or consumeOrDrain calls will fail to allocate
   * any tokens until the future time is reached.
   *
   * Note: It is assumed the caller will not ask for a very large count nor use
   * it immediately (if not waiting inline) as that would break the burst
   * prevention the limiter is meant to be used for.
   *
   * Thread-safe.
   */
  base::Optional<double> consumeWithBorrowNonBlocking(
      double toConsume,
      double rate,
      double burstSize,
      double nowInSeconds = defaultClockNow()) {
    DCHECK(rate > 0);
    DCHECK(burstSize > 0);

    if (burstSize < toConsume) {
      return base::nullopt;
    }

    while (toConsume > 0) {
      double consumed =
          consumeOrDrain(toConsume, rate, burstSize, nowInSeconds);
      if (consumed > 0) {
        toConsume -= consumed;
      } else {
        double zeroTimeNew = returnTokensImpl(-toConsume, rate);
        double napTime = std::max(0.0, zeroTimeNew - nowInSeconds);
        return napTime;
      }
    }
    return 0;
  }

  /**
   * Convenience wrapper around non-blocking borrow to sleep inline until
   * reservation is valid.
   */
  bool consumeWithBorrowAndWait(
      double toConsume,
      double rate,
      double burstSize,
      double nowInSeconds = defaultClockNow()) {
    auto res =
        consumeWithBorrowNonBlocking(toConsume, rate, burstSize, nowInSeconds);
    if (res.value_or(0) > 0) {
      int64_t napUSec = res.value() * 1000000;
      base::PlatformThread::Sleep(base::TimeDelta::FromMicroseconds(napUSec));
    }
    return res.has_value();
  }

  /**
   * Returns the number of tokens currently available.
   *
   * Thread-safe (but returned value may immediately be outdated).
   */
  double available(
      double rate,
      double burstSize,
      double nowInSeconds = defaultClockNow()) const noexcept {
    DCHECK(rate > 0);
    DCHECK(burstSize > 0);

    double zt = this->zeroTime_.load();
    if (nowInSeconds <= zt) {
      return 0;
    }
    return std::min((nowInSeconds - zt) * rate, burstSize);
  }

 private:
  template <typename TCallback>
  bool consumeImpl(
      double rate,
      double burstSize,
      double nowInSeconds,
      const TCallback& callback) {
    auto zeroTimeOld = zeroTime_.load();
    double zeroTimeNew;
    do {
      auto tokens = std::min((nowInSeconds - zeroTimeOld) * rate, burstSize);
      if (!callback(tokens)) {
        return false;
      }
      zeroTimeNew = nowInSeconds - tokens / rate;
    } while (
        UNLIKELY(!zeroTime_.compare_exchange_weak(zeroTimeOld, zeroTimeNew)));

    return true;
  }

  /**
   * Adjust zeroTime based on rate and tokenCount and return the new value of
   * zeroTime_. Note: Token count can be negative to move the zeroTime_ value
   * into the future.
   */
  double returnTokensImpl(double tokenCount, double rate) {
    auto zeroTimeOld = zeroTime_.load();
    double zeroTimeNew;
    do {
      zeroTimeNew = zeroTimeOld - tokenCount / rate;
    } while (
        UNLIKELY(!zeroTime_.compare_exchange_weak(zeroTimeOld, zeroTimeNew)));
    return zeroTimeNew;
  }

  alignas(token_bucket_detail::hardware_destructive_interference_size)
    std::atomic<double> zeroTime_;
};


// Rate of tokens per second to replenish in the token bucket
STRONGLY_TYPED_DOUBLE(TokenBucketRefillRate);

// Burst size - Maximum number of tokens that can be stored in token bucket
STRONGLY_TYPED_DOUBLE(TokenBucketBurst);

/**
 * Specialization of BasicDynamicTokenBucket with a fixed token
 * generation rate and a fixed maximum burst size.
 */
class BasicTokenBucket {
 private:
  using Impl = BasicDynamicTokenBucket;

 public:
  /**
   * Construct a token bucket with a specific maximum rate and burst size.
   *
   * @param genRate Number of tokens to generate per second.
   * @param burstSize Maximum burst size. Must be greater than 0.
   * @param zeroTime Initial time at which to consider the token bucket
   *                 starting to fill. Defaults to 0, so by default token
   *                 bucket is "full" after construction.
   */
  BasicTokenBucket(
      TokenBucketRefillRate genRate, TokenBucketBurst burstSize, double zeroTime = 0) noexcept
      : tokenBucket_(zeroTime), rate_(static_cast<double>(genRate)), burstSize_(static_cast<double>(burstSize)) {
    DCHECK(rate_ > 0);
    DCHECK(burstSize_ > 0);
  }

  /**
   * Copy constructor.
   *
   * Warning: not thread safe!
   */
  BasicTokenBucket(const BasicTokenBucket& other) noexcept = default;

  /**
   * Copy-assignment operator.
   *
   * Warning: not thread safe!
   */
  BasicTokenBucket& operator=(const BasicTokenBucket& other) noexcept = default;

  /**
   * Returns the current time in seconds since Epoch.
   */
  static double defaultClockNow() noexcept(noexcept(Impl::defaultClockNow())) {
    return Impl::defaultClockNow();
  }

  /**
   * Change rate and burst size.
   *
   * Warning: not thread safe!
   *
   * @param genRate Number of tokens to generate per second.
   * @param burstSize Maximum burst size. Must be greater than 0.
   * @param nowInSeconds Current time in seconds. Should be monotonically
   *                     increasing from the nowInSeconds specified in
   *                     this token bucket's constructor.
   */
  void reset(
      TokenBucketRefillRate genRate,
      TokenBucketBurst burstSize,
      double nowInSeconds = defaultClockNow()) noexcept {
    const double availTokens = available(nowInSeconds);
    rate_ = static_cast<double>(genRate);
    burstSize_ = static_cast<double>(burstSize);
    DCHECK(rate_ > 0);
    DCHECK(burstSize_ > 0);
    setCapacity(availTokens, nowInSeconds);
  }

  /**
   * Change number of tokens in bucket.
   *
   * Warning: not thread safe!
   *
   * @param tokens Desired number of tokens in bucket after the call.
   * @param nowInSeconds Current time in seconds. Should be monotonically
   *                     increasing from the nowInSeconds specified in
   *                     this token bucket's constructor.
   */
  void setCapacity(double tokens, double nowInSeconds) noexcept {
    tokenBucket_.reset(nowInSeconds - tokens / rate_);
  }

  /**
   * Attempts to consume some number of tokens. Tokens are first added to the
   * bucket based on the time elapsed since the last attempt to consume tokens.
   * Note: Attempts to consume more tokens than the burst size will always
   * fail.
   *
   * Thread-safe.
   *
   * @param toConsume The number of tokens to consume.
   * @param nowInSeconds Current time in seconds. Should be monotonically
   *                     increasing from the nowInSeconds specified in
   *                     this token bucket's constructor.
   * @return True if the rate limit check passed, false otherwise.
   */
  bool consume(double toConsume, double nowInSeconds = defaultClockNow()) {
    return tokenBucket_.consume(toConsume, rate_, burstSize_, nowInSeconds);
  }

  /**
   * Similar to consume, but always consumes some number of tokens.  If the
   * bucket contains enough tokens - consumes toConsume tokens.  Otherwise the
   * bucket is drained.
   *
   * Thread-safe.
   *
   * @param toConsume The number of tokens to consume.
   * @param nowInSeconds Current time in seconds. Should be monotonically
   *                     increasing from the nowInSeconds specified in
   *                     this token bucket's constructor.
   * @return number of tokens that were consumed.
   */
  double consumeOrDrain(
      double toConsume, double nowInSeconds = defaultClockNow()) {
    return tokenBucket_.consumeOrDrain(
        toConsume, rate_, burstSize_, nowInSeconds);
  }

  /**
   * Returns extra token back to the bucket.
   */
  void returnTokens(double tokensToReturn) {
    return tokenBucket_.returnTokens(tokensToReturn, rate_);
  }

  /**
   * Reserve tokens and return time to wait for in order for the reservation to
   * be compatible with the bucket configuration.
   */
  base::Optional<double> consumeWithBorrowNonBlocking(
      double toConsume, double nowInSeconds = defaultClockNow())
  {
    return tokenBucket_.consumeWithBorrowNonBlocking(
        toConsume, rate_, burstSize_, nowInSeconds);
  }

  /**
   * Reserve tokens. Blocks if need be until reservation is satisfied.
   */
  bool consumeWithBorrowAndWait(
      double toConsume, double nowInSeconds = defaultClockNow()) {
    return tokenBucket_.consumeWithBorrowAndWait(
        toConsume, rate_, burstSize_, nowInSeconds);
  }

  /**
   * Returns the number of tokens currently available.
   *
   * Thread-safe (but returned value may immediately be outdated).
   */
  double available(double nowInSeconds = defaultClockNow()) const {
    return tokenBucket_.available(rate_, burstSize_, nowInSeconds);
  }

  /**
   * Returns the number of tokens generated per second.
   *
   * Thread-safe (but returned value may immediately be outdated).
   */
  double rate() const noexcept { return rate_; }

  /**
   * Returns the maximum burst size.
   *
   * Thread-safe (but returned value may immediately be outdated).
   */
  double burst() const noexcept { return burstSize_; }

 private:
  Impl tokenBucket_;
  double rate_;
  double burstSize_;
};

using TokenBucket = BasicTokenBucket;
using DynamicTokenBucket = BasicDynamicTokenBucket;

} // namespace basic
