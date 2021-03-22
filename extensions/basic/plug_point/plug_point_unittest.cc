#include "basic/plug_point/plug_point.h"
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

STRONG_PLUG_POINT(PP_TestPointSingleCallback, base::Optional<bool>(const std::string&));

class PlugPointSingleCallbackTest : public testing::Test {
 public:
  void SetUp() override {
    PLUG_POINT(testPoint_) = PLUG_POINT_INSTANCE(PP_TestPointSingleCallback);
  }

  basic::Status testFunc(const std::string& err_message) {
    const base::Optional<bool> pluggedReturn
      = PLUG_POINT(testPoint_)->Run(REFERENCED(err_message));
    if(UNLIKELY(pluggedReturn))
    {
      RETURN_ERROR() << err_message;
    }
    RETURN_OK();
  }

 protected:
  base::test::TaskEnvironment task_environment;
  PP_TestPointSingleCallback* PLUG_POINT(testPoint_) = nullptr;
};

TEST_F(PlugPointSingleCallbackTest, TestPlugPointDisabled) {
  EXPECT_FALSE(PLUG_POINT(testPoint_)->isActive());

  EXPECT_OK(testFunc(""));

  EXPECT_OK(testFunc("123"));
}

TEST_F(PlugPointSingleCallbackTest, TestPlugPointDisabledCallback) {
  EXPECT_FALSE(PLUG_POINT(testPoint_)->isActive());

  std::unique_ptr<
    PP_TestPointSingleCallback::Subscription
  > subscription1 = PLUG_POINT(testPoint_)->setCallback(base::BindRepeating(
          [
          ](
            const std::string& err_message
          ) -> base::Optional<bool>
          {
            if(!err_message.empty()) {
              return true;
            }
            return base::nullopt;
          }
        ));

  EXPECT_OK(testFunc(""));

  EXPECT_OK(testFunc("123"));
}

TEST_F(PlugPointSingleCallbackTest, TestPlugPointSubscription) {
  PLUG_POINT(testPoint_)->enable();
  EXPECT_TRUE(PLUG_POINT(testPoint_)->isActive());

  std::atomic<bool> callback_done = false;

  /// \note subscription will remove registered callbacks on scope exit
  {
    std::unique_ptr<
      PP_TestPointSingleCallback::Subscription
    > subscription1 = PLUG_POINT(testPoint_)->setCallback(base::BindRepeating(
            [
            ](
              std::atomic<bool>& done
              , const std::string& err_message
            ) -> base::Optional<bool>
            {
              done = true;
              return base::nullopt;
            }
            , REFERENCED(callback_done)));
  }

  const base::Optional<bool> pluggedReturn
    = PLUG_POINT(testPoint_)->Run(
        "err_message");
  EXPECT_FALSE(callback_done.load());
}

TEST_F(PlugPointSingleCallbackTest, TestPlugPointEnabledCallbackOnThread) {
  PLUG_POINT(testPoint_)->enable();
  EXPECT_TRUE(PLUG_POINT(testPoint_)->isActive());

  std::unique_ptr<
    PP_TestPointSingleCallback::Subscription
  > subscription1 = PLUG_POINT(testPoint_)->setCallback(base::BindRepeating(
          [
          ](
            const std::string& err_message
          ) -> base::Optional<bool>
          {
            if(!err_message.empty()) {
              return true;
            }
            return base::nullopt;
          }
        ));

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
        &PlugPointSingleCallbackTest::testFunc
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

STRONG_PLUG_POINT_NOTIFIER(PP_TestPointNotifier, void(const std::string&, std::atomic<bool>&));

class PlugPointVoidCallbacksTest : public testing::Test {
 public:
  void SetUp() override {
    PLUG_POINT(testPoint_) = PLUG_POINT_INSTANCE(PP_TestPointNotifier);
  }

  basic::Status testFunc(const std::string& err_message) {
    PLUG_POINT(testPoint_)->Notify(REFERENCED(err_message)
                                   , REFERENCED(test_flag_));
    if(test_flag_.load())
    {
      RETURN_ERROR() << err_message;
    }
    RETURN_OK();
  }

 protected:
  base::test::TaskEnvironment task_environment;
  std::atomic<bool> test_flag_ = false;
  PP_TestPointNotifier* PLUG_POINT(testPoint_) = nullptr;
};

TEST_F(PlugPointVoidCallbacksTest, TestVoidPlugPointDisabled) {
  EXPECT_FALSE(PLUG_POINT(testPoint_)->isActive());

  EXPECT_OK(testFunc(""));

  EXPECT_OK(testFunc("123"));

  EXPECT_FALSE(test_flag_.load());
}

TEST_F(PlugPointVoidCallbacksTest, TestVoidPlugPointDisabledCallback) {
  EXPECT_FALSE(PLUG_POINT(testPoint_)->isActive());

  PLUG_POINT(testPoint_)->addCallback(basic::PlugPointPriority::Low
          , base::BindRepeating(
          [
          ](
            const std::string& err_message
            , std::atomic<bool>& test_flag
          )
          {
            // callback with High priority must set `test_flag`
            EXPECT_TRUE(test_flag.load());
          }
        ));

  PLUG_POINT(testPoint_)->addCallback(basic::PlugPointPriority::High
          , base::BindRepeating(
          [
          ](
            const std::string& err_message
            , std::atomic<bool>& test_flag
          )
          {
            if(!err_message.empty()) {
              test_flag = true;
            }
          }
        ));

  EXPECT_OK(testFunc(""));

  EXPECT_OK(testFunc("123"));

  EXPECT_FALSE(test_flag_.load());
}

TEST_F(PlugPointVoidCallbacksTest, TestVoidPlugPointEnabledCallbackOnThread) {
  PLUG_POINT(testPoint_)->enable();
  EXPECT_TRUE(PLUG_POINT(testPoint_)->isActive());

  PLUG_POINT(testPoint_)->addCallback(basic::PlugPointPriority::Low
          , base::BindRepeating(
          [
          ](
            const std::string& err_message
            , std::atomic<bool>& test_flag
          )
          {
            // callback with High priority must set `test_flag`
            EXPECT_TRUE(test_flag.load());
          }
        ));

  PLUG_POINT(testPoint_)->addCallback(basic::PlugPointPriority::High
          , base::BindRepeating(
          [
          ](
            const std::string& err_message
            , std::atomic<bool>& test_flag
          )
          {
            if(!err_message.empty()) {
              test_flag = true;
            }
          }
        ));

  base::RunLoop run_loop;

  // Kick off a thread that'll process "first", but not before
  // setting 'var' to true, which unblocks the main thread.
  ::base::Thread thread("Test thread");
  ASSERT_TRUE(thread.Start());
  // Without this call this test is racy.
  EXPECT_TRUE(thread.WaitUntilThreadStarted());

  base::PostPromise(FROM_HERE
    , thread.task_runner().get()
    , ::base::BindOnce(
        &PlugPointVoidCallbacksTest::testFunc
        , base::Unretained(this)
        , "TestErrMsg"
      )
  )
  .ThenOn(thread.task_runner()
    , FROM_HERE
    , ::base::BindOnce([](std::atomic<bool>& test_flag) {
          EXPECT_TRUE(test_flag.load());
      }, REFERENCED(test_flag_))
  )
  .ThenOn(thread.task_runner()
    , FROM_HERE
    , run_loop.QuitClosure()
  );

  run_loop.Run();

  thread.Stop();

  EXPECT_TRUE(test_flag_.load());
}

STRONG_PLUG_POINT_RUNNER(PP_TestPointRunner, base::Optional<bool>(const std::string&, std::atomic<bool>&));

class PlugPointCallbacksTest : public testing::Test {
 public:
  void SetUp() override {
    PLUG_POINT(testPoint_) = PLUG_POINT_INSTANCE(PP_TestPointRunner);
  }

  basic::Status testFunc(const std::string& err_message) {
    const base::Optional<bool> pluggedReturn
      = PLUG_POINT(testPoint_)->RunUntilReturnValueOrNullopt(
          REFERENCED(err_message), REFERENCED(test_flag_));
    if(UNLIKELY(pluggedReturn))
    {
      RETURN_ERROR() << err_message;
    }
    RETURN_OK();
  }

 protected:
  base::test::TaskEnvironment task_environment;
  std::atomic<bool> test_flag_ = false;
  PP_TestPointRunner* PLUG_POINT(testPoint_) = nullptr;
};

TEST_F(PlugPointCallbacksTest, TestCallbacksPlugPointDisabled) {
  EXPECT_FALSE(PLUG_POINT(testPoint_)->isActive());

  EXPECT_OK(testFunc(""));

  EXPECT_OK(testFunc("123"));

  EXPECT_FALSE(test_flag_.load());
}

TEST_F(PlugPointCallbacksTest, TestCallbacksPlugPointDisabledCallback) {
  EXPECT_FALSE(PLUG_POINT(testPoint_)->isActive());

  std::unique_ptr<
    PP_TestPointRunner::Subscription
  > subscription1 = PLUG_POINT(testPoint_)->addCallback(basic::PlugPointPriority::Low
          , base::BindRepeating(
          [
          ](
            const std::string& err_message
            , std::atomic<bool>& test_flag
          ) -> base::Optional<bool>
          {
            // callback with High priority must set `test_flag`
            EXPECT_TRUE(test_flag.load());
            return base::nullopt;
          }
        ));

  std::unique_ptr<
    PP_TestPointRunner::Subscription
  > subscription2 = PLUG_POINT(testPoint_)->addCallback(basic::PlugPointPriority::High
          , base::BindRepeating(
          [
          ](
            const std::string& err_message
            , std::atomic<bool>& test_flag
          ) -> base::Optional<bool>
          {
            if(!err_message.empty()) {
              test_flag = true;
              return true;
            }
            return base::nullopt;
          }
        ));

  EXPECT_OK(testFunc(""));

  EXPECT_OK(testFunc("123"));

  EXPECT_FALSE(test_flag_.load());
}

TEST_F(PlugPointCallbacksTest, TestCallbacksPlugPointSubscription) {
  PLUG_POINT(testPoint_)->enable();
  EXPECT_TRUE(PLUG_POINT(testPoint_)->isActive());

  /// \note subscription will remove registered callbacks on scope exit
  {
    std::unique_ptr<
      PP_TestPointRunner::Subscription
    > subscription1 = PLUG_POINT(testPoint_)->addCallback(basic::PlugPointPriority::Low
            , base::BindRepeating(
            [
            ](
              const std::string& err_message
              , std::atomic<bool>& done
            ) -> base::Optional<bool>
            {
              done = true;
              return base::nullopt;
            }
          ));

    std::unique_ptr<
      PP_TestPointRunner::Subscription
    > subscription2 = PLUG_POINT(testPoint_)->addCallback(basic::PlugPointPriority::High
            , base::BindRepeating(
            [
            ](
              const std::string& err_message
              , std::atomic<bool>& done
            ) -> base::Optional<bool>
            {
              done = true;
              return base::nullopt;
            }
          ));
  }

  std::atomic<bool> any_callback_done = false;
  const base::Optional<bool> pluggedReturn
    = PLUG_POINT(testPoint_)->RunUntilReturnValueOrNullopt(
        "err_message", REFERENCED(any_callback_done));
  EXPECT_FALSE(any_callback_done.load());
}

TEST_F(PlugPointCallbacksTest, TestCallbacksPlugPointEnabledCallbackOnThread) {
  PLUG_POINT(testPoint_)->enable();
  EXPECT_TRUE(PLUG_POINT(testPoint_)->isActive());

  std::unique_ptr<
    PP_TestPointRunner::Subscription
  > subscription1 = PLUG_POINT(testPoint_)->addCallback(basic::PlugPointPriority::Low
          , base::BindRepeating(
          [
          ](
            const std::string& err_message
            , std::atomic<bool>& test_flag
          ) -> base::Optional<bool>
          {
            // callback with High priority must set `test_flag`
            EXPECT_TRUE(test_flag.load());
            return base::nullopt;
          }
        ));

  std::unique_ptr<
    PP_TestPointRunner::Subscription
  > subscription2 = PLUG_POINT(testPoint_)->addCallback(basic::PlugPointPriority::High
          , base::BindRepeating(
          [
          ](
            const std::string& err_message
            , std::atomic<bool>& test_flag
          ) -> base::Optional<bool>
          {
            if(!err_message.empty()) {
              test_flag = true;
              return true;
            }
            return base::nullopt;
          }
        ));

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
        &PlugPointCallbacksTest::testFunc
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

  EXPECT_TRUE(test_flag_.load());
}

} // namespace basic
