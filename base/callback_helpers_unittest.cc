// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/callback_helpers.h"

#include <functional>
#include <type_traits>

#include "base/bind.h"
#include "base/callback.h"
#include "base/test/gtest_util.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace {

TEST(CallbackHelpersTest, IsBaseCallback) {
  // Check that base::{Once,Repeating}Closures and references to them are
  // considered base::{Once,Repeating}Callbacks.
  static_assert(base::IsBaseCallback<base::OnceClosure>::value, "");
  static_assert(base::IsBaseCallback<base::RepeatingClosure>::value, "");
  static_assert(base::IsBaseCallback<base::OnceClosure&&>::value, "");
  static_assert(base::IsBaseCallback<const base::RepeatingClosure&>::value, "");

  // Check that base::Callbacks with a given RunType and references to them are
  // considered base::Callbacks.
  static_assert(base::IsBaseCallback<base::OnceCallback<int(int)>>::value, "");
  static_assert(base::IsBaseCallback<base::RepeatingCallback<int(int)>>::value,
                "");
  static_assert(base::IsBaseCallback<base::OnceCallback<int(int)>&&>::value,
                "");
  static_assert(
      base::IsBaseCallback<const base::RepeatingCallback<int(int)>&>::value,
      "");

  // Check that POD types are not considered base::Callbacks.
  static_assert(!base::IsBaseCallback<bool>::value, "");
  static_assert(!base::IsBaseCallback<int>::value, "");
  static_assert(!base::IsBaseCallback<double>::value, "");

  // Check that the closely related std::function is not considered a
  // base::Callback.
  static_assert(!base::IsBaseCallback<std::function<void()>>::value, "");
  static_assert(!base::IsBaseCallback<const std::function<void()>&>::value, "");
  static_assert(!base::IsBaseCallback<std::function<void()>&&>::value, "");
}

TEST(CallbackHelpersTest, IsOnceCallback) {
  // Check that base::OnceClosures and references to them are considered
  // base::OnceCallbacks, but base::RepeatingClosures are not.
  static_assert(base::IsOnceCallback<base::OnceClosure>::value, "");
  static_assert(!base::IsOnceCallback<base::RepeatingClosure>::value, "");
  static_assert(base::IsOnceCallback<base::OnceClosure&&>::value, "");
  static_assert(!base::IsOnceCallback<const base::RepeatingClosure&>::value,
                "");

  // Check that base::OnceCallbacks with a given RunType and references to them
  // are considered base::OnceCallbacks, but base::RepeatingCallbacks are not.
  static_assert(base::IsOnceCallback<base::OnceCallback<int(int)>>::value, "");
  static_assert(!base::IsOnceCallback<base::RepeatingCallback<int(int)>>::value,
                "");
  static_assert(base::IsOnceCallback<base::OnceCallback<int(int)>&&>::value,
                "");
  static_assert(
      !base::IsOnceCallback<const base::RepeatingCallback<int(int)>&>::value,
      "");

  // Check that POD types are not considered base::OnceCallbacks.
  static_assert(!base::IsOnceCallback<bool>::value, "");
  static_assert(!base::IsOnceCallback<int>::value, "");
  static_assert(!base::IsOnceCallback<double>::value, "");

  // Check that the closely related std::function is not considered a
  // base::OnceCallback.
  static_assert(!base::IsOnceCallback<std::function<void()>>::value, "");
  static_assert(!base::IsOnceCallback<const std::function<void()>&>::value, "");
  static_assert(!base::IsOnceCallback<std::function<void()>&&>::value, "");

  // Check that the result of BindOnce is a OnceCallback, but not if it's
  // wrapped in AdaptCallbackForRepeating.
  auto cb = base::BindOnce([](int* count) { ++*count; });
  static_assert(base::IsOnceCallback<decltype(cb)>::value, "");
  auto wrapped = base::AdaptCallbackForRepeating(std::move(cb));
  static_assert(!base::IsOnceCallback<decltype(wrapped)>::value, "");
}

void Increment(int* value) {
  (*value)++;
}

TEST(CallbackHelpersTest, ScopedClosureRunnerHasClosure) {
  base::ScopedClosureRunner runner1;
  EXPECT_FALSE(runner1);

  base::ScopedClosureRunner runner2{base::DoNothing()};
  EXPECT_TRUE(runner2);
}

TEST(CallbackHelpersTest, ScopedClosureRunnerExitScope) {
  int run_count = 0;
  {
    base::ScopedClosureRunner runner(base::BindOnce(&Increment, &run_count));
    EXPECT_EQ(0, run_count);
  }
  EXPECT_EQ(1, run_count);
}

TEST(CallbackHelpersTest, ScopedClosureRunnerRelease) {
  int run_count = 0;
  base::OnceClosure c;
  {
    base::ScopedClosureRunner runner(base::BindOnce(&Increment, &run_count));
    c = runner.Release();
    EXPECT_EQ(0, run_count);
  }
  EXPECT_EQ(0, run_count);
  std::move(c).Run();
  EXPECT_EQ(1, run_count);
}

TEST(CallbackHelpersTest, ScopedClosureRunnerReplaceClosure) {
  int run_count_1 = 0;
  int run_count_2 = 0;
  {
    base::ScopedClosureRunner runner;
    runner.ReplaceClosure(base::BindOnce(&Increment, &run_count_1));
    runner.ReplaceClosure(base::BindOnce(&Increment, &run_count_2));
    EXPECT_EQ(0, run_count_1);
    EXPECT_EQ(0, run_count_2);
  }
  EXPECT_EQ(0, run_count_1);
  EXPECT_EQ(1, run_count_2);
}

TEST(CallbackHelpersTest, ScopedClosureRunnerRunAndResetNonNull) {
  int run_count_3 = 0;
  {
    base::ScopedClosureRunner runner(base::BindOnce(&Increment, &run_count_3));
    EXPECT_EQ(0, run_count_3);
    runner.RunAndReset();
    EXPECT_EQ(1, run_count_3);
  }
  EXPECT_EQ(1, run_count_3);
}

TEST(CallbackHelpersTest, ScopedClosureRunnerRunAndResetNull) {
  base::ScopedClosureRunner runner;
  runner.RunAndReset();  // Should not crash.
}

TEST(CallbackHelpersTest, ScopedClosureRunnerMoveConstructor) {
  int run_count = 0;
  {
    std::unique_ptr<base::ScopedClosureRunner> runner(
        new base::ScopedClosureRunner(base::BindOnce(&Increment, &run_count)));
    base::ScopedClosureRunner runner2(std::move(*runner));
    runner.reset();
    EXPECT_EQ(0, run_count);
  }
  EXPECT_EQ(1, run_count);
}

TEST(CallbackHelpersTest, ScopedClosureRunnerMoveAssignment) {
  int run_count_1 = 0;
  int run_count_2 = 0;
  {
    base::ScopedClosureRunner runner(base::BindOnce(&Increment, &run_count_1));
    {
      base::ScopedClosureRunner runner2(
          base::BindOnce(&Increment, &run_count_2));
      runner = std::move(runner2);
      EXPECT_EQ(1, run_count_1);
      EXPECT_EQ(0, run_count_2);
    }
    EXPECT_EQ(1, run_count_1);
    EXPECT_EQ(0, run_count_2);
  }
  EXPECT_EQ(1, run_count_1);
  EXPECT_EQ(1, run_count_2);
}

TEST(CallbackHelpersTest, AdaptCallbackForRepeating) {
  int count = 0;
  base::OnceCallback<void(int*)> cb =
      base::BindOnce([](int* count) { ++*count; });

  base::RepeatingCallback<void(int*)> wrapped =
      base::AdaptCallbackForRepeating(std::move(cb));

  EXPECT_EQ(0, count);
  wrapped.Run(&count);
  EXPECT_EQ(1, count);
  wrapped.Run(&count);
  EXPECT_EQ(1, count);
}

TEST(CallbackHelpersTest, SplitOnceCallback_FirstCallback) {
  int count = 0;
  base::OnceCallback<void(int*)> cb =
      base::BindOnce([](int* count) { ++*count; });

  auto split = base::SplitOnceCallback(std::move(cb));

  static_assert(std::is_same<decltype(split),
                             std::pair<base::OnceCallback<void(int*)>,
                                       base::OnceCallback<void(int*)>>>::value,
                "");

  EXPECT_EQ(0, count);
  std::move(split.first).Run(&count);
  EXPECT_EQ(1, count);

#if GTEST_HAS_DEATH_TEST
  EXPECT_CHECK_DEATH(std::move(split.second).Run(&count));
#endif  // GTEST_HAS_DEATH_TEST
}

TEST(CallbackHelpersTest, SplitOnceCallback_SecondCallback) {
  int count = 0;
  base::OnceCallback<void(int*)> cb =
      base::BindOnce([](int* count) { ++*count; });

  auto split = base::SplitOnceCallback(std::move(cb));

  static_assert(std::is_same<decltype(split),
                             std::pair<base::OnceCallback<void(int*)>,
                                       base::OnceCallback<void(int*)>>>::value,
                "");

  EXPECT_EQ(0, count);
  std::move(split.second).Run(&count);
  EXPECT_EQ(1, count);

#if GTEST_HAS_DEATH_TEST
  EXPECT_CHECK_DEATH(std::move(split.first).Run(&count));
#endif  // GTEST_HAS_DEATH_TEST
}

}  // namespace
