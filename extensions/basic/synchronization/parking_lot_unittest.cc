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

#include <basic/synchronization/parking_lot.h>

#include <base/logging.h>

#include <thread>

// #include <folly/synchronization/Baton.h>

#include "testing/gtest/include/gtest/gtest.h"
#include "testing/gmock/include/gmock/gmock.h"

using namespace base;
using namespace basic;

#if TODO
TEST(ParkingLot, multilot) {
  using SmallLot = ParkingLot<bool>;
  using LargeLot = ParkingLot<uint64_t>;
  SmallLot smalllot;
  LargeLot largelot;
  folly::Baton<> sb;
  folly::Baton<> lb;

  std::thread small([&]() {
    smalllot.park(
        0, false, [] { return true; }, [&]() { sb.post(); });
  });
  std::thread large([&]() {
    largelot.park(
        0, true, [] { return true; }, [&]() { lb.post(); });
  });
  sb.wait();
  lb.wait();

  int count = 0;
  smalllot.unpark(0, [&](bool data) {
    count++;
    EXPECT_EQ(data, false);
    return UnparkControl::RemoveContinue;
  });
  EXPECT_EQ(count, 1);
  count = 0;
  largelot.unpark(0, [&](bool data) {
    count++;
    EXPECT_EQ(data, true);
    return UnparkControl::RemoveContinue;
  });
  EXPECT_EQ(count, 1);

  small.join();
  large.join();
}
#endif

// This is not possible to implement with Futex, because futex
// and the native linux syscall are 32-bit only.
TEST(ParkingLot, LargeWord) {
  ParkingLot<uint64_t> lot;
  std::atomic<uint64_t> w{0};

  lot.park(
      0, false, [&]() { return w == 1; }, []() {});

  // Validate should return false, will hang otherwise.
}

class WaitableMutex : public std::mutex {
  using Lot = ParkingLot<std::function<bool(void)>>;
  static Lot lot;

 public:
  void unlock() {
    bool unparked = false;
    lot.unpark(uint64_t(this), [&](std::function<bool(void)> wfunc) {
      if (wfunc()) {
        unparked = true;
        return UnparkControl::RemoveBreak;
      } else {
        return UnparkControl::RemoveContinue;
      }
    });
    if (!unparked) {
      std::mutex::unlock();
    }
    // Otherwise, we pass mutex directly to waiter without needing to unlock.
  }

  template <typename Wait>
  void wait(Wait wfunc) {
    lot.park(
        uint64_t(this),
        wfunc,
        [&]() { return !wfunc(); },
        [&]() { std::mutex::unlock(); });
  }
};

WaitableMutex::Lot WaitableMutex::lot;

TEST(ParkingLot, WaitableMutexTest) {
  if (kIsSanitizeThread) {
    return;
  }
  std::atomic<bool> go{false};
  WaitableMutex mu;
  std::thread t([&]() {
    std::lock_guard<WaitableMutex> g(mu);
    mu.wait([&]() { return go == true; });
  });
  sleep(1);

  {
    std::lock_guard<WaitableMutex> g(mu);
    go = true;
  }
  t.join();
}
