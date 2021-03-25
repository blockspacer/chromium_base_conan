#include "basic/types_bucket/types_bucket.h"
#include "basic/types_bucket/thread_local_types_bucket.h"
#include "basic/strings/substitute.h"
#include "basic/promise/promise.h"
#include "basic/promise/do_nothing_promise.h"
#include "basic/promise/post_promise.h"

#include "base/bind.h"
#include "base/test/bind.h"
#include "base/macros.h"
#include "base/time/tick_clock.h"
#include "base/test/task_environment.h"
#include <base/atomicops.h>
#include <base/threading/thread_local.h>
#include <base/threading/platform_thread.h>
#include <base/synchronization/lock.h>
#include <base/threading/thread.h>
#include <base/run_loop.h>

#include "testing/gtest/include/gtest/gtest.h"

#include <memory>

using namespace base;

namespace basic {

struct MyTypeA {
  int foo;
  char bar;
};

// Number of operations to perform
static int kNumOperations = 10*1000;

// Number of worker threads
static int kNumThreads = 4;

class ThreadLocalTypesBucketTest : public testing::Test {
 public:
  ThreadLocalTypesBucketTest() = default;
  void SetUp() override {
  }

 protected:
  base::test::TaskEnvironment task_environment;
};

void validateMyTypeAOnThread(scoped_refptr<SingleThreadTaskRunner> task_runner, int foo, char bar)
{
  base::RunLoop run_loop;
  task_runner->PostTask(
        FROM_HERE, BindLambdaForTesting([&]() {
          TypesBucket& typesBucket = ThreadLocalTypesBucket::CurrentTypesBucket();
          const auto& var = typesBucket.ctx<MyTypeA>();
          EXPECT_EQ(var.foo, foo);
          EXPECT_EQ(var.bar, bar);
        }));
  task_runner->PostTask(FROM_HERE, run_loop.QuitClosure());
  run_loop.Run();
}

void resetMyTypeAOnThread(scoped_refptr<SingleThreadTaskRunner> task_runner, int foo, char bar)
{
  base::RunLoop run_loop;
  task_runner->PostTask(
      FROM_HERE, BindLambdaForTesting([&]() {
        TypesBucket& typesBucket = ThreadLocalTypesBucket::CurrentTypesBucket();

        const auto& var = typesBucket.reset<MyTypeA>(foo, bar);
        ALLOW_UNUSED_LOCAL(var);
      }));
  task_runner->PostTask(FROM_HERE, run_loop.QuitClosure());
  run_loop.Run();

  validateMyTypeAOnThread(task_runner, foo, bar);
}

TEST_F(ThreadLocalTypesBucketTest, TestSimple) {
  base::Thread threadA("TypesBucketThreadA");
  threadA.Start();
  threadA.WaitUntilThreadStarted();

  base::Thread threadB("TypesBucketThreadB");
  threadB.Start();
  threadB.WaitUntilThreadStarted();

  resetMyTypeAOnThread(::base::ThreadTaskRunnerHandle::Get(), 42, 'c');

  validateMyTypeAOnThread(::base::ThreadTaskRunnerHandle::Get(), 42, 'c');

  resetMyTypeAOnThread(threadA.task_runner(), 78, 'G');

  validateMyTypeAOnThread(::base::ThreadTaskRunnerHandle::Get(), 42, 'c');

  resetMyTypeAOnThread(threadB.task_runner(), 96, 'j');

  validateMyTypeAOnThread(::base::ThreadTaskRunnerHandle::Get(), 42, 'c');

  validateMyTypeAOnThread(threadA.task_runner(), 78, 'G');

  resetMyTypeAOnThread(::base::ThreadTaskRunnerHandle::Get(), 99, 'k');

  validateMyTypeAOnThread(threadB.task_runner(), 96, 'j');

  validateMyTypeAOnThread(::base::ThreadTaskRunnerHandle::Get(), 99, 'k');

  threadB.Stop();
  threadA.Stop();
}

class MultiThreadTest {
 public:
  typedef std::vector<std::unique_ptr<base::Thread> > thread_vec_t;

  MultiThreadTest(int64_t num_operations, int64_t num_threads)
      : num_operations_(num_operations),
        num_threads_(num_threads) {
  }

  int& GetOrCreateInt() {
    TypesBucket& typesBucket = ThreadLocalTypesBucket::CurrentTypesBucket();
    return typesBucket.ctx_or_set<int>(int{0});
  }

  void InitThreadBucket(const int64_t thread_id, const int64_t num) {
    GetOrCreateInt() = thread_id;
    for (int i = 0; i < num; i++) {
      GetOrCreateInt()++;
    }
  }

  void ValidateThreadBucket(const int64_t thread_id, const int64_t num) {
    const int result = thread_id + num;
    ASSERT_EQ(GetOrCreateInt(), result);
  }

  void Run() {
    std::vector<Promise<void, base::NoReject>> promises;

    base::RunLoop run_loop;

    for (int i = 0; i < num_threads_; i++) {
      threads_.push_back(std::make_unique<base::Thread>("ThreadLocalTypesBucketTestThread"));
      threads_.back()->Start();
      threads_.back()->WaitUntilThreadStarted();

      Promise<void, base::NoReject> promise = base::PostPromise(FROM_HERE
        , threads_.back()->task_runner().get()
        , ::base::BindOnce(
             &MultiThreadTest::InitThreadBucket
             , base::Unretained(this)
             , i
             , num_operations_
          )
      )
      .ThenOn(threads_.back()->task_runner().get(), FROM_HERE
              , ::base::BindOnce(
                  &MultiThreadTest::ValidateThreadBucket
                  , base::Unretained(this)
                  , i
                  , num_operations_));

      promises.push_back(promise);
    }

    Promises::All(FROM_HERE, promises)
    .ThenHere(FROM_HERE,
              BindLambdaForTesting([&]() {
                run_loop.Quit();
              }));

    run_loop.Run();

    for (std::unique_ptr<base::Thread> &t : threads_) {
      t->Stop();
      t.reset();
    }
  }

  int64_t num_operations_;
  // This is rounded down to the nearest even number
  int32_t num_threads_;
  thread_vec_t threads_;
};

// Compare a single-thread workload.
TEST_F(ThreadLocalTypesBucketTest, TestSingle) {
  MultiThreadTest basicTest(kNumOperations, 1);
  basicTest.Run();
}

// Compare a multi-threaded workload.
TEST_F(ThreadLocalTypesBucketTest, TestMulti) {
  MultiThreadTest basicTest(kNumOperations, kNumThreads);
  basicTest.Run();
}

}  // namespace basic
