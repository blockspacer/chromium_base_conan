#include "basic/fail_point/fail_point.h"
#include "basic/status/status_macros.h"
#include "basic/promise/post_task_executor.h"
#include "basic/promise/post_promise.h"
#include "basic/promise/do_nothing_promise.h"
#include "basic/promise/abstract_promise.h"
#include "basic/promise/helpers.h"
#include "basic/rvalue_cast.h"

#include "base/test/gtest_util.h"
#include "base/test/test_mock_time_task_runner.h"
#include "base/test/task_environment.h"
#include "base/bind.h"
#include "base/run_loop.h"
#include "base/threading/thread.h"
#include "base/task_runner.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace basic {

STRONG_FAIL_POINT(FP_TestPoint);

class FailPointTest : public testing::Test {
 public:
  void SetUp() override {
    FAIL_POINT(testPoint_) = FAIL_POINT_INSTANCE(FP_TestPoint);
  }

  basic::Status testFunc(const std::string& err_message) {
    if(UNLIKELY(FAIL_POINT(testPoint_)->checkFail()))
    {
      RETURN_ERROR() << err_message;
    }
    RETURN_OK();
  }

 protected:
  base::test::TaskEnvironment task_environment;
  FP_TestPoint* FAIL_POINT(testPoint_) = nullptr;
};

TEST_F(FailPointTest, TestDisabled) {
  EXPECT_FALSE(FAIL_POINT(testPoint_)->isActive());

  EXPECT_OK(testFunc(""));

  EXPECT_OK(testFunc("123"));
}

TEST_F(FailPointTest, TestUnset) {
  FAIL_POINT(testPoint_)->enable();
  EXPECT_TRUE(FAIL_POINT(testPoint_)->isActive());
  FAIL_POINT(testPoint_)->setFailure();
  FAIL_POINT(testPoint_)->unsetFailure();

  EXPECT_OK(testFunc(""));

  EXPECT_OK(testFunc("123"));
}

TEST_F(FailPointTest, TestEnabled) {
  FAIL_POINT(testPoint_)->enable();
  EXPECT_TRUE(FAIL_POINT(testPoint_)->isActive());
  FAIL_POINT(testPoint_)->setFailure();

  EXPECT_NOT_OK(testFunc(""));

  EXPECT_NOT_OK(testFunc("123"));
}

TEST_F(FailPointTest, TestEnabledOnThread) {
  FAIL_POINT(testPoint_)->enable();
  EXPECT_TRUE(FAIL_POINT(testPoint_)->isActive());
  FAIL_POINT(testPoint_)->setFailure();

  base::RunLoop run_loop;

  // Kick off a thread that'll process "first", but not before
  // setting 'var' to true, which unblocks the main thread.
  ::base::Thread thread("Test thread");
  ASSERT_TRUE(thread.Start());
  // Without this call this test is racy.
  EXPECT_TRUE(thread.WaitUntilThreadStarted());

  base::PostTaskAndReplyWithPromise(thread.task_runner().get()
    , FROM_HERE
    , ::base::BindOnce(
        &FailPointTest::testFunc
        , base::Unretained(this)
        , "TestErrMsg"
      )
    , ::base::BindOnce([](basic::Status testFuncResult) {
        EXPECT_NOT_OK(testFuncResult);
    })
  )
  .ThenOn(thread.task_runner()
    , FROM_HERE
    , run_loop.QuitClosure()
  );

  run_loop.Run();

  thread.Stop();
}

} // namespace basic
