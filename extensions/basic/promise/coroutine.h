// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <basic/portability/portability.h>

#if BASIC_HAS_COROUTINES

#include "basic/promise/promise.h"
#include "basic/promise/abstract_promise.h"
#include "basic/promise/finally_executor.h"
#include "basic/promise/helpers.h"
#include "basic/promise/no_op_promise_executor.h"
#include "basic/promise/promise_result.h"
#include "basic/promise/then_and_catch_executor.h"
#include "basic/rvalue_cast.h"
#include <basic/concept/dependent_false.h>

#include "base/threading/sequenced_task_runner_handle.h"
#include "basic/rvalue_cast.h"
#include "base/callback_helpers.h"
#include "base/run_loop.h"
#include "base/task/task_traits.h"
#include "base/task/post_task.h"
#include "base/sequenced_task_runner.h"

#include <tuple>
#include <type_traits>
#include <variant>

#if __has_include(<coroutine>)
#include <coroutine>
#else
#include <experimental/coroutine>
#endif

/*
How does this work?

The messageloop runs the promise executor. In the case of a coroutine
the callback returns a promise for the result of the coroutine
callback.  This promise is treated exactly like currying a promise.
If the coroutine exits normally (via co_return or reaching the end of
the method) the promise is resolved.

If the coroutine co_awaits a promise AbstractPromiseAwaiter comes
into play.  If the promise is settled, await_ready returns true and
the co_await returns immediatly.  Otherwise a resume promise
dependant on the promise we're awaiting is posted and the
co_routine exits back to the message loop.

When the dependant promise resolves, the resume promise's executor
runs which resumes the coroutine.
*/
namespace base {
namespace internal {

template <typename ResolveType, typename RejectType>
class ContinuationExecutor {
 public:
  static constexpr PromiseExecutor::PrerequisitePolicy kPrerequisitePolicy =
      PromiseExecutor::PrerequisitePolicy::kAll;

  ContinuationExecutor(std::experimental::coroutine_handle<> coro_handle)
    : coro_handle_(coro_handle) {}

  ~ContinuationExecutor() {}

  bool IsCancelled() const {
    return false;
  }

  void Execute(AbstractPromise* promise) {
    DCHECK(promise);

    static_assert(!std::is_same<NoResolve, ResolveType>::value
                  || !std::is_same<NoReject, RejectType>::value,
                  "A NoResolve and NoReject promise not supported in coroutine executor.");

    if constexpr (!std::is_same<ResolveType, NoResolve>::value)
    {
      promise->emplace(Resolved<void>());
      coro_handle_.resume();
      return;
    }

    if constexpr (!std::is_same<RejectType, NoReject>::value)
    {
      promise->emplace(Rejected<void>());
      coro_handle_.resume();
      return;
    }

    NOTREACHED()
      << "A NoResolve and NoReject promise not supported in coroutine executor.";
  }

#if DCHECK_IS_ON()
  PromiseExecutor::ArgumentPassingType ResolveArgumentPassingType() const {
    return UseMoveSemantics<ResolveType>::argument_passing_type;
  }

  PromiseExecutor::ArgumentPassingType RejectArgumentPassingType() const {
    return UseMoveSemantics<RejectType>::argument_passing_type;
  }

  bool CanResolve() const {
    return !std::is_same<ResolveType, NoResolve>::value;
  }

  bool CanReject() const { return !std::is_same<RejectType, NoReject>::value; }
#endif

private:
 std::experimental::coroutine_handle<> coro_handle_;
};

template <typename T>
struct ResumeResultHelper;

template <typename T>
struct NoRejectResumeResultHelper;

template <typename T>
struct NoResolveResumeResultHelper;

template <typename FinallyCb>
static auto FinallyHere(const Location& from_here,
                 FinallyCb finally_callback,
                 AbstractPromise* abstract_promise_) noexcept {
  // Extract properties from |finally_callback| callback.
  using CallbackTraits = internal::CallbackTraits<FinallyCb>;
  using ReturnedPromiseResolveT = typename CallbackTraits::ResolveType;
  using ReturnedPromiseRejectT = typename CallbackTraits::RejectType;

  using CallbackArgT = typename CallbackTraits::ArgType;
  static_assert(std::is_void<CallbackArgT>::value,
                "|finally_callback| callback must have no arguments");

  return Promise<ReturnedPromiseResolveT, ReturnedPromiseRejectT>(
      ConstructHereAbstractPromiseWithSinglePrerequisite(
          from_here, abstract_promise_,
          internal::PromiseExecutor::Data(
              in_place_type_t<internal::FinallyExecutor<
                  OnceCallback<typename CallbackTraits::ReturnType()>,
                  Resolved<ReturnedPromiseResolveT>,
                  Rejected<ReturnedPromiseRejectT>>>(),
              internal::ToCallbackBase(RVALUE_CAST(finally_callback)))));
}

// Waits until the promise has settled and if resolved it returns the resolved
// value.
template <typename T,
          std::enable_if_t<!std::is_reference<T>::value &&
                           !std::is_void<T>::value>* = nullptr>
static T TakeResolveValue(AbstractPromise* abstract_promise_) {
  static_assert(!std::is_same<NoResolve, T>::value,
                "A NoResolve promise can't resolve.");
  DCHECK(abstract_promise_->IsSettled());
  if (!abstract_promise_->IsSettled()) {
    RunLoop run_loop;
    FinallyHere(FROM_HERE, run_loop.QuitClosure(), abstract_promise_);
    run_loop.Run();
  }
  DCHECK(abstract_promise_->IsResolved())
      << "Can't take resolved value, promise wasn't resolved.";
  return RVALUE_CAST(abstract_promise_->TakeValue()
                       .value()
                       .template Get<Resolved<T>>()
                       ->value);
}

// Waits until the promise has settled and if rejected it returns the rejected
// value.
template <typename T,
          std::enable_if_t<!std::is_reference<T>::value &&
                           !std::is_void<T>::value>* = nullptr>
static T TakeRejectValue(AbstractPromise* abstract_promise_) {
  static_assert(!std::is_same<NoReject, T>::value,
                "A NoReject promise can't reject.");
  DCHECK(abstract_promise_->IsSettled());
  if (!abstract_promise_->IsSettled()) {
    RunLoop run_loop;
    FinallyHere(FROM_HERE, run_loop.QuitClosure(), abstract_promise_);
    run_loop.Run();
  }
  abstract_promise_->IgnoreUncaughtCatchForTesting();
  DCHECK(abstract_promise_->IsRejected())
      << "Can't take rejected value, promise wasn't rejected.";
  return RVALUE_CAST(abstract_promise_->TakeValue()
                       .value()
                       .template Get<Rejected<T>>()
                       ->value);
}

template <
  typename ResolveType
  , typename RejectType
>
struct NoRejectResumeResultHelper<Promise<ResolveType, RejectType>> {
  using ReturnType = ResolveType;

  static ReturnType GetResumeResult(AbstractPromise* promise) {
    DCHECK(promise);

    static_assert(std::is_same<RejectType, NoReject>::value || std::is_same<RejectType, void>::value,
                  "Expected NoReject or void promise in NoRejectResumeResultHelper.");

    static_assert(!std::is_same<NoResolve, ResolveType>::value,
                  "A NoResolve promise not supported in NoRejectResumeResultHelper.");

    DCHECK(promise->IsResolved() || promise->IsRejected())
      << "A NoResolve and NoReject promise not supported in NoRejectResumeResultHelper.";

    if constexpr (!std::is_same<ResolveType, NoResolve>::value)
    {
      if(promise->IsResolved())
        return TakeResolveValue<ResolveType>(promise);
    }

    NOTREACHED()
      << "The promise should have been resolved or rejected.";
  }
};

template <
  typename ResolveType
  , typename RejectType
>
struct NoResolveResumeResultHelper<Promise<ResolveType, RejectType>> {
  using ReturnType = RejectType;

  static ReturnType GetResumeResult(AbstractPromise* promise) {
    DCHECK(promise);

    static_assert(std::is_same<ResolveType, NoResolve>::value || std::is_same<ResolveType, void>::value,
                  "Expected NoResolve or void promise in NoResolveResumeResultHelper.");

    static_assert(!std::is_same<NoReject, RejectType>::value,
                  "A NoReject promise not supported in NoResolveResumeResultHelper.");

    DCHECK(promise->IsResolved() || promise->IsRejected())
      << "A NoResolve and NoReject promise not supported in NoResolveResumeResultHelper.";

    if constexpr (!std::is_same<RejectType, NoReject>::value)
    {
      if(promise->IsRejected())
        return TakeRejectValue<RejectType>(promise);
    }

    NOTREACHED()
      << "The promise should have been resolved or rejected.";
  }
};

template <
  typename ResolveType
  , typename RejectType
>
struct ResumeResultHelper<Promise<ResolveType, RejectType>> {
  using ReturnType = std::variant<ResolveType, RejectType>;

  static ReturnType GetResumeResult(AbstractPromise* promise) {
    DCHECK(promise);

    static_assert(!std::is_same<ResolveType, NoResolve>::value ||
                  !std::is_same<RejectType, base::NoReject>::value,
                  "A NoResolve and NoReject promise not supported in ResumeResultHelper.");

    DCHECK(promise->IsResolved() || promise->IsRejected())
      << "A NoResolve and NoReject promise not supported in ResumeResultHelper.";

    if constexpr (!std::is_same<ResolveType, NoResolve>::value)
    {
      if(promise->IsResolved())
        return ReturnType(/*Resolved*/{TakeResolveValue<ResolveType>(promise)});
    }

    if constexpr (!std::is_same<RejectType, NoReject>::value)
    {
      if(promise->IsRejected())
        return ReturnType(/*Rejected*/{TakeRejectValue<RejectType>(promise)});
    }

    NOTREACHED()
      << "The promise should have been resolved or rejected.";
  }
};

template <typename ResolveType, typename RejectType>
class AbstractPromiseAwaiter {
 public:
  AbstractPromiseAwaiter(const Promise<ResolveType, RejectType>& p)
      : promise_to_await_(p.abstract_promise_) {}

  AbstractPromiseAwaiter(AbstractPromiseAwaiter&) = delete;

  AbstractPromiseAwaiter(AbstractPromiseAwaiter&& other) noexcept
      : promise_to_await_(std::move(other.promise_to_await_)) {}

  ~AbstractPromiseAwaiter() {}

  static scoped_refptr<AbstractPromise>
  get_return_object_on_allocation_failure() {
    return nullptr;
  }

  bool await_ready() {
    if(promise_to_await_->IsSettled()
       && (promise_to_await_->IsRejected()
           || promise_to_await_->IsResolved()))
      return true;

    return false;
  }

  void await_suspend(std::experimental::coroutine_handle<> coro_handle) noexcept {
    DCHECK(promise_to_await_);

    internal::PromiseExecutor::Data executor_data(
        (in_place_type_t<
            ContinuationExecutor<ResolveType, RejectType>>())
        , std::move(coro_handle)
    );

    AbstractPromise::Create(
      SequencedTaskRunnerHandle::Get(), FROM_HERE,
      std::make_unique<AbstractPromise::AdjacencyList>(promise_to_await_.get()),
      /// \todo RejectPolicy
      //promise_to_await_.reject_policy_,
      //RejectPolicy::kMustCatchRejection,
      RejectPolicy::kCatchNotRequired,
      DependentList::ConstructUnresolved(),
      RVALUE_CAST(executor_data));
  }

  auto await_resume() {
    DCHECK(promise_to_await_);

    if constexpr (std::is_same<ResolveType, NoResolve>::value || std::is_same<ResolveType, void>::value) {
      return NoResolveResumeResultHelper<Promise<ResolveType, RejectType>>::
          GetResumeResult(promise_to_await_.get());
    }
    else if constexpr (std::is_same<RejectType, NoReject>::value || std::is_same<RejectType, void>::value) {
      return NoRejectResumeResultHelper<Promise<ResolveType, RejectType>>::
          GetResumeResult(promise_to_await_.get());
    } 
    else if constexpr (!std::is_same<ResolveType, NoResolve>::value && !std::is_same<ResolveType, void>::value
                       && !std::is_same<RejectType, NoReject>::value && !std::is_same<RejectType, void>::value) {
      return ResumeResultHelper<Promise<ResolveType, RejectType>>::
          GetResumeResult(promise_to_await_.get());
    } 
    else {
      // dependent_false yields false only if
      // previous if branches yield false
      static_assert(basic::dependent_false<Promise<ResolveType, RejectType>>::value);
    }
  }

  auto initial_suspend() noexcept { return std::experimental::suspend_always{}; }

  auto final_suspend() noexcept { return std::experimental::suspend_always{}; }

  void unhandled_exception() { std::terminate(); }

  scoped_refptr<AbstractPromise> promise_to_await_;
};
}  // namespace internal

template <typename ResolveType, typename RejectType>
internal::AbstractPromiseAwaiter<ResolveType, RejectType> operator co_await(
    const Promise<ResolveType, RejectType>& p) {
  return internal::AbstractPromiseAwaiter<ResolveType, RejectType>(p);
}

}  // namespace base

namespace std {
namespace experimental {

template <typename RejectType, typename... Args>
struct coroutine_traits<base::Promise<void, RejectType>, Args...> {
  struct promise_type {
    promise_type() : promise_resolver_(FROM_HERE) {}

    base::Promise<void, RejectType> get_return_object() {
      return promise_resolver_.promise();
    }

    void set_exception(exception_ptr const&) noexcept {}

    auto initial_suspend() noexcept { return std::experimental::suspend_never{}; }

    auto final_suspend() noexcept { return std::experimental::suspend_always{}; }

    void return_void() noexcept { promise_resolver_.Resolve(); }

    void unhandled_exception() { std::terminate(); }

    base::ManualPromiseResolver<void, RejectType> promise_resolver_;
  };
};

template <typename ResolveType, typename RejectType, typename... Args>
struct coroutine_traits<base::Promise<ResolveType, RejectType>, Args...> {
  struct promise_type {
    promise_type() : promise_resolver_(FROM_HERE) {}

    base::Promise<ResolveType, RejectType> get_return_object() {
      return promise_resolver_.promise();
    }

    void set_exception(exception_ptr const&) noexcept {}

    auto initial_suspend() noexcept { return std::experimental::suspend_never{}; }

    auto final_suspend() noexcept { return std::experimental::suspend_always{}; }

    void return_value(ResolveType value) noexcept {
      promise_resolver_.Resolve(value);
    }

    void unhandled_exception() { std::terminate(); }

    base::ManualPromiseResolver<ResolveType, RejectType> promise_resolver_;
  };
};

}  // namespace experimental
}  // namespace std

#endif // BASIC_HAS_COROUTINES
