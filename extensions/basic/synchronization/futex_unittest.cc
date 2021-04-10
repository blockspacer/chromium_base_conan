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

#include <basic/synchronization/futex.h>
#include <basic/test/deterministic_schedule.h>

#include <chrono>
#include <condition_variable>
#include <functional>
#include <ratio>

#include "base/logging.h"
#include "base/test/gtest_util.h"
#include "base/test/task_environment.h"
#include "base/run_loop.h"
#include "base/threading/platform_thread.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace basic {
namespace chrono {

struct coarse_steady_clock {
  using rep = std::chrono::milliseconds::rep;
  using period = std::chrono::milliseconds::period;
  using duration = std::chrono::duration<rep, period>;
  using time_point = std::chrono::time_point<coarse_steady_clock, duration>;
  constexpr static bool is_steady = true;

  static time_point now() noexcept {
#ifndef CLOCK_MONOTONIC_COARSE
    return time_point(std::chrono::duration_cast<duration>(
        std::chrono::steady_clock::now().time_since_epoch()));
#else
    timespec ts;
    auto ret = clock_gettime(CLOCK_MONOTONIC_COARSE, &ts);
    if (kIsDebug && (ret != 0)) {
      CHECK(false)
        << "Error using CLOCK_MONOTONIC_COARSE.";
    }

    return time_point(std::chrono::duration_cast<duration>(
        std::chrono::seconds(ts.tv_sec) +
        std::chrono::nanoseconds(ts.tv_nsec)));
#endif
  }
};

} // namespace chrono
} // namespace basic

using namespace basic;
using namespace basic::detail;
using namespace base;
using namespace std;
using namespace std::chrono;
using basic::test::DeterministicSchedule;
using basic::test::DeterministicAtomic;

using basic::chrono::coarse_steady_clock;
typedef DeterministicSchedule DSched;

template <template <typename> class Atom>
void run_basic_thread(Futex<Atom>& f) {
  EXPECT_EQ(FutexResult::AWOKEN, futexWait(&f, 0));
}

template <template <typename> class Atom>
void run_basic_tests() {
  Futex<Atom> f(0);

  EXPECT_EQ(FutexResult::VALUE_CHANGED, futexWait(&f, 1));
  EXPECT_EQ(futexWake(&f), 0);

  std::unique_ptr<basic::test::DSchedThreadWrapper> thr = DSched::thread(
    std::bind(run_basic_thread<Atom>, std::ref(f)));

  while (futexWake(&f) != 1) {
    base::PlatformThread::YieldCurrentThread();
  }

  DSched::join(*thr);
}

template <template <typename> class Atom, typename Clock, typename Duration>
void liveClockWaitUntilTests() {
  Futex<Atom> f(0);

  for (int stress = 0; stress < 1000; ++stress) {
    auto fp = &f; // workaround for t5336595
    std::unique_ptr<basic::test::DSchedThreadWrapper> thrA = DSched::thread([fp, stress] {
      while (true) {
        const auto deadline = time_point_cast<Duration>(
            Clock::now() + microseconds(1 << (stress % 20)));
        const auto res = futexWaitUntil(fp, 0, deadline);
        EXPECT_TRUE(res == FutexResult::TIMEDOUT || res == FutexResult::AWOKEN);
        if (res == FutexResult::AWOKEN) {
          break;
        }
      }
    });

    while (futexWake(&f) != 1) {
      base::PlatformThread::YieldCurrentThread();
    }

    DSched::join(*thrA);
  }

  {
    const auto start = Clock::now();
    const auto deadline = time_point_cast<Duration>(start + milliseconds(100));
    EXPECT_EQ(futexWaitUntil(&f, 0, deadline), FutexResult::TIMEDOUT);
    LOG(INFO) << "Futex wait timed out after waiting for "
              << duration_cast<milliseconds>(Clock::now() - start).count()
              << "ms using clock with " << Duration::period::den
              << " precision, should be ~100ms";
  }

  {
    const auto start = Clock::now();
    const auto deadline =
        time_point_cast<Duration>(start - 2 * start.time_since_epoch());
    EXPECT_EQ(futexWaitUntil(&f, 0, deadline), FutexResult::TIMEDOUT);
    LOG(INFO) << "Futex wait with invalid deadline timed out after waiting for "
              << duration_cast<milliseconds>(Clock::now() - start).count()
              << "ms using clock with " << Duration::period::den
              << " precision, should be ~0ms";
  }
}

template <typename Clock>
void deterministicAtomicWaitUntilTests() {
  Futex<DeterministicAtomic> f(0);

  // Futex wait must eventually fail with either FutexResult::TIMEDOUT or
  // FutexResult::INTERRUPTED
  const auto res = futexWaitUntil(&f, 0, Clock::now() + milliseconds(100));
  EXPECT_TRUE(res == FutexResult::TIMEDOUT || res == FutexResult::INTERRUPTED);
}

template <template <typename> class Atom>
void run_wait_until_tests() {
  liveClockWaitUntilTests<Atom, system_clock, system_clock::duration>();
  liveClockWaitUntilTests<Atom, steady_clock, steady_clock::duration>();
  liveClockWaitUntilTests<Atom, steady_clock, coarse_steady_clock::duration>();

  typedef duration<int64_t, std::ratio<1, 10000000>> decimicroseconds;
  liveClockWaitUntilTests<Atom, system_clock, decimicroseconds>();
}

template <>
void run_wait_until_tests<DeterministicAtomic>() {
  deterministicAtomicWaitUntilTests<system_clock>();
  deterministicAtomicWaitUntilTests<steady_clock>();
  deterministicAtomicWaitUntilTests<coarse_steady_clock>();
}

template <template <typename> class Atom>
void run_wake_blocked_test() {
  for (auto delay = 1;; delay *= 2) {
    bool success = false;
    Futex<Atom> f(0);
    std::unique_ptr<basic::test::DSchedThreadWrapper> thr = DSched::thread(
        [&] { success = FutexResult::AWOKEN == futexWait(&f, 0); });
    /* sleep override */ base::PlatformThread::Sleep(base::TimeDelta::FromMilliseconds(delay));
    f.store(1);
    futexWake(&f, 1);
    DSched::join(*thr);
    LOG(INFO) << "delay=" << delay << "_ms, success=" << success;
    if (success) {
      break;
    }
  }
}

// Only Linux platforms currently use the futex() syscall.
// This syscall requires timeouts to either use CLOCK_REALTIME or
// CLOCK_MONOTONIC but the API we expose takes a std::chrono::system_clock or
// steady_clock. These just happen to be thin wrappers over
// CLOCK_REALTIME/CLOCK_MONOTONIC in current implementations, and we assume that
// this is the case. Check here that this is a valid assumption.
#ifdef __linux__

uint64_t diff(uint64_t a, uint64_t b) {
  return a > b ? a - b : b - a;
}

void run_system_clock_test() {
  /* Test to verify that system_clock uses clock_gettime(CLOCK_REALTIME, ...)
   * for the time_points */
  struct timespec ts;
  const int maxIters = 1000;
  int iter = 0;
  const uint64_t delta = 10000000 /* 10 ms */;

  /** The following loop is only to make the test more robust in the presence of
   * clock adjustments that can occur. We just run the loop maxIter times and
   * expect with very high probability that there will be atleast one iteration
   * of the test during which clock adjustments > delta have not occurred. */
  while (iter < maxIters) {
    uint64_t a =
        duration_cast<nanoseconds>(system_clock::now().time_since_epoch())
            .count();

    clock_gettime(CLOCK_REALTIME, &ts);
    uint64_t b = ts.tv_sec * 1000000000ULL + ts.tv_nsec;

    uint64_t c =
        duration_cast<nanoseconds>(system_clock::now().time_since_epoch())
            .count();

    if (diff(a, b) <= delta && diff(b, c) <= delta && diff(a, c) <= 2 * delta) {
      /* Success! system_clock uses CLOCK_REALTIME for time_points */
      break;
    }
    iter++;
  }
  EXPECT_TRUE(iter < maxIters);
}

void run_steady_clock_test() {
  /* Test to verify that steady_clock uses clock_gettime(CLOCK_MONOTONIC, ...)
   * for the time_points */
  EXPECT_TRUE(steady_clock::is_steady);

  const uint64_t A =
      duration_cast<nanoseconds>(steady_clock::now().time_since_epoch())
          .count();

  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  const uint64_t B = ts.tv_sec * 1000000000ULL + ts.tv_nsec;

  const uint64_t C =
      duration_cast<nanoseconds>(steady_clock::now().time_since_epoch())
          .count();
  EXPECT_TRUE(A <= B && B <= C);
}

namespace {

class FutexTest : public testing::Test {
 protected:
  ~FutexTest() override { base::RunLoop().RunUntilIdle(); }

 private:
  base::test::TaskEnvironment task_environment_;
};

}  // namespace

TEST_F(FutexTest, clock_source) {
  run_system_clock_test();

  /* On some systems steady_clock is just an alias for system_clock. So,
   * we must skip run_steady_clock_test if the two clocks are the same. */
  if (!std::is_same<system_clock, steady_clock>::value) {
    run_steady_clock_test();
  }
}

#endif // __linux__

TEST_F(FutexTest, basic_live) {
  run_basic_tests<std::atomic>();
  run_wait_until_tests<std::atomic>();
}

TEST_F(FutexTest, basic_emulated) {
  run_basic_tests<EmulatedFutexAtomic>();
  run_wait_until_tests<EmulatedFutexAtomic>();
}

TEST_F(FutexTest, basic_deterministic) {
  DSched sched(DSched::uniform(0));
  run_basic_tests<DeterministicAtomic>();
  run_wait_until_tests<DeterministicAtomic>();
}

TEST_F(FutexTest, wake_blocked_live) {
  run_wake_blocked_test<std::atomic>();
}

TEST_F(FutexTest, wake_blocked_emulated) {
  run_wake_blocked_test<EmulatedFutexAtomic>();
}
