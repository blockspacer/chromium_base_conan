// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
// The following only applies to changes made to this file as part of YugaByte development.
//
// Portions Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//

#include "base/test/task_environment.h"
#include "basic/concurrency/concurrent_int64.h"
#include "basic/strings/substitute.h"

#include <base/atomicops.h>
#include <base/threading/thread_local.h>
#include <base/threading/platform_thread.h>
#include <base/synchronization/lock.h>
#include <base/threading/thread.h>
#include <base/run_loop.h>

#include "testing/gtest/include/gtest/gtest.h"

#include <memory>

namespace basic {

// Number of operations to perform
static int kNumOperations = 10*1000;

// Number of worker threads
static int kNumThreads = 4;

class Striped64Test : public testing::Test {
 public:
  Striped64Test() = default;
  void SetUp() override {
  }

 protected:
  base::test::TaskEnvironment task_environment;
};

// Test some basic operations
TEST_F(Striped64Test, TestBasic) {
  Concurrent64LongAdder adder;
  ASSERT_EQ(adder.Value(), 0);
  adder.IncrementBy(100);
  ASSERT_EQ(adder.Value(), 100);
  adder.Increment();
  ASSERT_EQ(adder.Value(), 101);
  adder.Decrement();
  ASSERT_EQ(adder.Value(), 100);
  adder.IncrementBy(-200);
  ASSERT_EQ(adder.Value(), -100);
  adder.Reset();
  ASSERT_EQ(adder.Value(), 0);
}

template <class Adder>
class MultiThreadTest {
 public:
  typedef std::vector<std::unique_ptr<base::Thread> > thread_vec_t;

  MultiThreadTest(int64_t num_operations, int64_t num_threads)
      : num_operations_(num_operations),
        num_threads_(num_threads) {
  }

  void IncrementerThread(const int64_t num) {
    for (int i = 0; i < num; i++) {
      adder_.Increment();
    }
  }

  void DecrementerThread(const int64_t num) {
    for (int i = 0; i < num; i++) {
      adder_.Decrement();
    }
  }

  void Run() {
    // Increment
    for (int i = 0; i < num_threads_; i++) {
      threads_.push_back(std::make_unique<base::Thread>("Striped64Incrementer"));
      threads_.back()->Start();
      threads_.back()->WaitUntilThreadStarted();
      threads_.back()->task_runner()->PostTask(
          FROM_HERE, base::BindOnce(&MultiThreadTest::IncrementerThread,
                                    base::Unretained(this), num_operations_));
    }

    {
      base::RunLoop run_loop;
      threads_.back()->task_runner()->PostTask(FROM_HERE, run_loop.QuitClosure());
      run_loop.Run();
    }

    for (std::unique_ptr<base::Thread> &t : threads_) {
      t->Stop();
      t.reset();
    }
    ASSERT_EQ(num_threads_*num_operations_, adder_.Value());
    threads_.clear();

    // Decrement back to zero
    for (int i = 0; i < num_threads_; i++) {
      threads_.push_back(std::make_unique<base::Thread>("Striped64Decrementer"));
      threads_.back()->Start();
      threads_.back()->WaitUntilThreadStarted();
      threads_.back()->task_runner()->PostTask(
          FROM_HERE, base::BindOnce(&MultiThreadTest::DecrementerThread,
                                    base::Unretained(this), num_operations_));
    }

    {
      base::RunLoop run_loop;
      threads_.back()->task_runner()->PostTask(FROM_HERE, run_loop.QuitClosure());
      run_loop.Run();
    }

    for (std::unique_ptr<base::Thread> &t : threads_) {
      t->Stop();
      t.reset();
    }
    ASSERT_EQ(0, adder_.Value());
  }

  Adder adder_;

  int64_t num_operations_;
  // This is rounded down to the nearest even number
  int32_t num_threads_;
  thread_vec_t threads_;
};

// Test adder implemented by a single AtomicInt for comparison
class BasicAdder {
 public:
  BasicAdder() : value_(0) {}
  void IncrementBy(int64_t x) { base::subtle::NoBarrier_AtomicIncrement(&value_, x); }
  inline void Increment() { IncrementBy(1); }
  inline void Decrement() { IncrementBy(-1); }
  int64_t Value() {
    return base::subtle::NoBarrier_Load(&value_);
  }
 private:
  base::subtle::Atomic64 value_;
};

void RunMultiTest(int64_t num_operations, int64_t num_threads) {
  base::Time start = base::Time::Now();
  MultiThreadTest<BasicAdder> basicTest(num_operations, num_threads);
  basicTest.Run();
  base::Time end1 = base::Time::Now();
  MultiThreadTest<Concurrent64LongAdder> test(num_operations, num_threads);
  test.Run();
  base::Time end2 = base::Time::Now();

  LOG(INFO) << "Basic counter took   " << base::TimeDelta(end1 - start).InMilliseconds() << "ms.";
  LOG(INFO) << "Striped counter took " << base::TimeDelta(end2 - start).InMilliseconds() << "ms.";
}

// Compare a single-thread workload. Demonstrates the overhead of LongAdder over AtomicInt.
TEST_F(Striped64Test, TestSingleIncrDecr) {
  RunMultiTest(kNumOperations, 1);
}

// Compare a multi-threaded workload. LongAdder should show improvements here.
TEST_F(Striped64Test, TestMultiIncrDecr) {
  RunMultiTest(kNumOperations, kNumThreads);
}

}  // namespace basic
