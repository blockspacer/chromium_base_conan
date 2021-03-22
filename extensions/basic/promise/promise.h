// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "basic/promise/all_container_executor.h"
#include "basic/promise/all_tuple_executor.h"
#include "basic/promise/race_container_executor.h"
#include "basic/promise/race_tuple_executor.h"
#include "basic/promise/finally_executor.h"
#include "basic/promise/helpers.h"
#include "basic/promise/no_op_promise_executor.h"
#include "basic/promise/promise_result.h"
#include "basic/promise/then_and_catch_executor.h"

#include "base/run_loop.h"
#include "base/task/task_traits.h"
#include "base/task/post_task.h"
#include "base/sequenced_task_runner.h"
#include "basic/rvalue_cast.h"

namespace base {

// Used by `ThenOn` and `ThenNestedPromiseOn`
struct IsNestedPromise
{
  operator bool() const { return isNested; }

  bool isNested = false;
};

// Used by `ThenOn` and `ThenNestedPromiseOn`
template <typename Type>
struct DisallowNestedPromise
{
  static constexpr bool check_passed = true;
};

template <typename ResolveT, typename RejectT>
struct DisallowNestedPromise<Promise<ResolveT, RejectT>>
{
  static constexpr bool check_passed = false;
};

template <typename Type>
struct AllowOnlyNestedPromise
{
  static constexpr bool check_passed = false;
};

template <typename ResolveT, typename RejectT>
struct AllowOnlyNestedPromise<Promise<ResolveT, RejectT>>
{
  static constexpr bool check_passed = true;
};

// We can't include post_task.h here so we forward declare it.
BASE_EXPORT scoped_refptr<::base::SequencedTaskRunner> CreateSequencedTaskRunner(
    const TaskTraits& traits);

// Inspired by ES6 promises, Promise<> is a PostTask based callback system for
// asynchronous operations. An operation can resolve (succeed) with a value and
// optionally reject (fail) with a different result. Interested parties can be
// notified using ThenOn() and CatchOn() which schedule callbacks to run as
// appropriate on the specified task runner or task traits. If a promise is
// settled when a ThenOn() / CatchOn() / FinallyOn() statement is added, the
// callback will be posted immediately, otherwise it has to wait.
//
// Promise<> is copyable, moveable and thread safe. Under the hood
// AbstractPromise is refcounted so retaining multiple Promises<> will
// prevent that part of the promise graph from being released.
template <typename ResolveType, typename RejectType = NoReject>
class Promise : public internal::BasePromise {
 public:
  Promise() = default;

  explicit Promise(
      scoped_refptr<internal::AbstractPromise> abstract_promise) noexcept
      : BasePromise(RVALUE_CAST(abstract_promise)) {}

  // Every PostTask calls this constructor so we need to be careful to avoid
  // unnecessary binary bloat.
  explicit Promise(internal::PassedPromise passed_promise) noexcept
      : BasePromise(RVALUE_CAST(passed_promise),
                    BasePromise::InlineConstructor()) {}

  ~Promise() = default;

  bool IsCancelledForTesting() const { return abstract_promise_->IsCanceled(); }

  // Waits until the promise has settled and if resolved it returns the resolved
  // value.
  template <typename T = ResolveType,
            std::enable_if_t<!std::is_reference<T>::value &&
                             !std::is_void<T>::value>* = nullptr>
  T TakeResolveValueForTesting() {
    static_assert(!std::is_same<NoResolve, T>::value,
                  "A NoResolve promise can't resolve.");
    if (!abstract_promise_->IsSettled()) {
      RunLoop run_loop;
      FinallyHere(FROM_HERE, run_loop.QuitClosure());
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
  template <typename T = RejectType,
            std::enable_if_t<!std::is_reference<T>::value &&
                             !std::is_void<T>::value>* = nullptr>
  T TakeRejectValueForTesting() {
    static_assert(!std::is_same<NoReject, T>::value,
                  "A NoReject promise can't reject.");
    if (!abstract_promise_->IsSettled()) {
      RunLoop run_loop;
      FinallyHere(FROM_HERE, run_loop.QuitClosure());
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

  bool IsResolvedForTesting() const {
    DCHECK(abstract_promise_);
    return abstract_promise_->IsResolvedForTesting();
  }

  bool IsRejectedForTesting() const {
    DCHECK(abstract_promise_);
    return abstract_promise_->IsRejectedForTesting();
  }

  // A task to execute |on_reject| is posted on |task_runner| as soon as this
  // promise (or an uncaught ancestor) is rejected. A Promise<> for the return
  // value of |on_reject| is returned.
  //
  // The following callback return types have special meanings:
  // 1. PromiseResult<Resolve, Reject> lets the callback resolve, reject or
  //    curry a Promise<Resolve, Reject>
  // 2. Promise<Resolve, Reject> where the result is a curried promise.
  //
  // If a promise has multiple Catches they will be run in order of creation.
  //
  // |task_runner| is const-ref to avoid bloat due the destructor (which posts a
  // task).
  template <typename CatchCb>
  auto CatchOn(const scoped_refptr<TaskRunner>& task_runner,
               const Location& from_here,
               CatchCb on_reject) noexcept {
    DCHECK(!on_reject.is_null());

    // Extract properties from the |on_reject| callback.
    using CatchCallbackTraits = internal::CallbackTraits<CatchCb>;
    using CatchCallbackArgT = typename CatchCallbackTraits::ArgType;

    // Compute the resolve and reject types of the returned Promise.
    using ReturnedPromiseTraits =
        internal::PromiseCombiner<ResolveType,
                                  NoReject,  // We've caught the reject case.
                                  typename CatchCallbackTraits::ResolveType,
                                  typename CatchCallbackTraits::RejectType>;
    using ReturnedPromiseResolveT = typename ReturnedPromiseTraits::ResolveType;
    using ReturnedPromiseRejectT = typename ReturnedPromiseTraits::RejectType;

    static_assert(!std::is_same<NoReject, RejectType>::value,
                  "Can't catch a NoReject promise.");

    // Check we wouldn't need to return Promise<Variant<...>, ...>
    static_assert(ReturnedPromiseTraits::valid,
                  "Ambiguous promise resolve type");
    static_assert(
        internal::IsValidPromiseArg<RejectType, CatchCallbackArgT>::value ||
            std::is_void<CatchCallbackArgT>::value,
        "|on_reject| callback must accept Promise::RejectType or void.");

    return Promise<ReturnedPromiseResolveT, ReturnedPromiseRejectT>(
        ConstructAbstractPromiseWithSinglePrerequisite(
            task_runner, from_here, abstract_promise_.get(),
            internal::PromiseExecutor::Data(
                in_place_type_t<internal::ThenAndCatchExecutor<
                    OnceClosure,  // Never called.
                    OnceCallback<typename CatchCallbackTraits::SignatureType>,
                    internal::NoCallback, RejectType,
                    Resolved<ReturnedPromiseResolveT>,
                    Rejected<ReturnedPromiseRejectT>>>(),
                OnceClosure(),
                internal::ToCallbackBase(RVALUE_CAST(on_reject)))));
  }

  template <typename CatchCb>
  auto CatchOn(const TaskTraits& traits,
               const Location& from_here,
               CatchCb&& on_reject) noexcept {
    return CatchOn(CreateSequencedTaskRunner(traits), from_here,
                   FORWARD(on_reject));
  }

  template <typename CatchCb>
  auto CatchHere(const Location& from_here, CatchCb&& on_reject) noexcept {
    DCHECK(!on_reject.is_null());

    // Extract properties from the |on_reject| callback.
    using CatchCallbackTraits = internal::CallbackTraits<CatchCb>;
    using CatchCallbackArgT = typename CatchCallbackTraits::ArgType;

    // Compute the resolve and reject types of the returned Promise.
    using ReturnedPromiseTraits =
        internal::PromiseCombiner<ResolveType,
                                  NoReject,  // We've caught the reject case.
                                  typename CatchCallbackTraits::ResolveType,
                                  typename CatchCallbackTraits::RejectType>;
    using ReturnedPromiseResolveT = typename ReturnedPromiseTraits::ResolveType;
    using ReturnedPromiseRejectT = typename ReturnedPromiseTraits::RejectType;

    static_assert(!std::is_same<NoReject, RejectType>::value,
                  "Can't catch a NoReject promise.");

    // Check we wouldn't need to return Promise<Variant<...>, ...>
    static_assert(ReturnedPromiseTraits::valid,
                  "Ambiguous promise resolve type");
    static_assert(
        internal::IsValidPromiseArg<RejectType, CatchCallbackArgT>::value ||
            std::is_void<CatchCallbackArgT>::value,
        "|on_reject| callback must accept Promise::RejectType or void.");

    return Promise<ReturnedPromiseResolveT, ReturnedPromiseRejectT>(
        ConstructHereAbstractPromiseWithSinglePrerequisite(
            from_here, abstract_promise_.get(),
            internal::PromiseExecutor::Data(
                in_place_type_t<internal::ThenAndCatchExecutor<
                    OnceClosure,  // Never called.
                    OnceCallback<typename CatchCallbackTraits::SignatureType>,
                    internal::NoCallback, RejectType,
                    Resolved<ReturnedPromiseResolveT>,
                    Rejected<ReturnedPromiseRejectT>>>(),
                OnceClosure(),
                internal::ToCallbackBase(RVALUE_CAST(on_reject)))));
  }

  // A task to execute |on_resolve| is posted on |task_runner| as soon as this
  // promise (or an unhandled ancestor) is resolved. A Promise<> for the return
  // value of |on_resolve| is returned.
  //
  // The following callback return types have special meanings:
  // 1. PromiseResult<Resolve, Reject> lets the callback resolve, reject or
  //    curry a Promise<Resolve, Reject>
  // 2. Promise<Resolve, Reject> where the result is a curried promise.
  //
  // If a promise has multiple Thens they will be run in order of creation.
  //
  // |task_runner| is const-ref to avoid bloat due the destructor (which posts a
  // task).
  template <typename ThenCb>
  auto ThenOn(const scoped_refptr<TaskRunner>& task_runner,
              const Location& from_here,
              ThenCb on_resolve,
              // If callback returns promise,
              // then resolving will be done based on `nested` promise
              // (may be not when callback finished).
              // Must be true if callback returns promise, otherwise false.
              // Checks if callback returns promise only in debug mode.
              IsNestedPromise isNestedPromise = IsNestedPromise()) noexcept {
    DCHECK(!on_resolve.is_null());

    // Extract properties from the |on_resolve| callback.
    using ThenCallbackTraits = internal::CallbackTraits<std::decay_t<ThenCb>>;
    using ThenCallbackArgT = typename ThenCallbackTraits::ArgType;

    // Compute the resolve and reject types of the returned Promise.
    using ReturnedPromiseTraits =
        internal::PromiseCombiner<NoResolve,  // We've caught the resolve case.
                                  RejectType,
                                  typename ThenCallbackTraits::ResolveType,
                                  typename ThenCallbackTraits::RejectType>;
    using ReturnedPromiseResolveT = typename ReturnedPromiseTraits::ResolveType;
    using ReturnedPromiseRejectT = typename ReturnedPromiseTraits::RejectType;

    // Check we wouldn't need to return Promise<..., Variant<...>>
    static_assert(ReturnedPromiseTraits::valid,
                  "Ambiguous promise reject type");

    static_assert(
        internal::IsValidPromiseArg<ResolveType, ThenCallbackArgT>::value ||
            std::is_void<ThenCallbackArgT>::value,
        "|on_resolve| callback must accept Promise::ResolveType or void.");

    if(isNestedPromise) {
      DCHECK(
        AllowOnlyNestedPromise<typename ThenCallbackTraits::ReturnType>::check_passed)
          << "Nested promise not allowed. Promise posted from "
          << from_here.ToString();
    } else {
      DCHECK(
        DisallowNestedPromise<typename ThenCallbackTraits::ReturnType>::check_passed)
          << "Nested promise not found. Promise posted from "
          << from_here.ToString();
    }

    return Promise<ReturnedPromiseResolveT, ReturnedPromiseRejectT>(
        ConstructAbstractPromiseWithSinglePrerequisite(
            task_runner, from_here, abstract_promise_.get(),
            internal::PromiseExecutor::Data(
                in_place_type_t<internal::ThenAndCatchExecutor<
                    OnceCallback<typename ThenCallbackTraits::SignatureType>,
                    OnceClosure, ResolveType, internal::NoCallback,
                    Resolved<ReturnedPromiseResolveT>,
                    Rejected<ReturnedPromiseRejectT>>>(),
                internal::ToCallbackBase(RVALUE_CAST(on_resolve)),
                OnceClosure())));
  }

  // Wraps passed promise into callback that returns it as nested promise.
  template <typename ResolveT, typename RejectT>
  auto ThenNestedPromiseOn(const scoped_refptr<TaskRunner>& task_runner,
              const Location& from_here,
              Promise<ResolveT, RejectT> on_resolve) noexcept
  {
    return ThenOn(task_runner, from_here,
                  internal::wrapPromiseIntoOnceCallback(on_resolve)
                  , ::base::IsNestedPromise{true});
  }

  // Wraps passed promise into callback that returns it as nested promise.
  template <typename ResolveT, typename RejectT>
  auto ThenNestedPromiseOn(const scoped_refptr<TaskRunner>& task_runner,
              const Location& from_here,
              Promise<ResolveT, RejectT> on_resolve,
              Promise<ResolveT, RejectT> on_reject) noexcept
  {
    return ThenOn(
      task_runner
      , from_here
      , internal::wrapPromiseIntoOnceCallback(on_resolve)
      , internal::wrapPromiseIntoOnceCallback(on_reject)
      , ::base::IsNestedPromise{true});
  }

  template <typename ThenCb>
  auto ThenOn(const TaskTraits& traits,
              const Location& from_here,
              ThenCb&& on_resolve,
              // If callback returns promise,
              // then resolving will be done based on `nested` promise
              // (may be not when callback finished).
              // Must be true if callback returns promise, otherwise false.
              // Checks if callback returns promise only in debug mode.
              IsNestedPromise isNestedPromise = IsNestedPromise()) noexcept {
    return ThenOn(CreateSequencedTaskRunner(traits), from_here,
                  FORWARD(on_resolve), isNestedPromise);
  }

  template <typename ThenCb>
  auto ThenHere(const Location& from_here, ThenCb&& on_resolve, IsNestedPromise isNestedPromise = IsNestedPromise()) noexcept {
    DCHECK(!on_resolve.is_null());

    // Extract properties from the |on_resolve| callback.
    using ThenCallbackTraits = internal::CallbackTraits<std::decay_t<ThenCb>>;
    using ThenCallbackArgT = typename ThenCallbackTraits::ArgType;

    // Compute the resolve and reject types of the returned Promise.
    using ReturnedPromiseTraits =
        internal::PromiseCombiner<NoResolve,  // We've caught the resolve case.
                                  RejectType,
                                  typename ThenCallbackTraits::ResolveType,
                                  typename ThenCallbackTraits::RejectType>;
    using ReturnedPromiseResolveT = typename ReturnedPromiseTraits::ResolveType;
    using ReturnedPromiseRejectT = typename ReturnedPromiseTraits::RejectType;

    if(isNestedPromise) {
      DCHECK(
        AllowOnlyNestedPromise<typename ThenCallbackTraits::ReturnType>::check_passed)
          << "Nested promise not allowed. Promise posted from "
          << from_here.ToString();
    } else {
      DCHECK(
        DisallowNestedPromise<typename ThenCallbackTraits::ReturnType>::check_passed)
          << "Nested promise not found. Promise posted from "
          << from_here.ToString();
    }

    // Check we wouldn't need to return Promise<..., Variant<...>>
    static_assert(ReturnedPromiseTraits::valid,
                  "Ambiguous promise reject type");

    static_assert(
        internal::IsValidPromiseArg<ResolveType, ThenCallbackArgT>::value ||
            std::is_void<ThenCallbackArgT>::value,
        "|on_resolve| callback must accept Promise::ResolveType or void.");

    return Promise<ReturnedPromiseResolveT, ReturnedPromiseRejectT>(
        ConstructHereAbstractPromiseWithSinglePrerequisite(
            from_here, abstract_promise_.get(),
            internal::PromiseExecutor::Data(
                in_place_type_t<internal::ThenAndCatchExecutor<
                    OnceCallback<typename ThenCallbackTraits::SignatureType>,
                    OnceClosure, ResolveType, internal::NoCallback,
                    Resolved<ReturnedPromiseResolveT>,
                    Rejected<ReturnedPromiseRejectT>>>(),
                internal::ToCallbackBase(RVALUE_CAST(on_resolve)),
                OnceClosure())));
  }

  // A task to execute |on_reject| is posted on |task_runner| as soon as this
  // promise (or an uncaught ancestor) is rejected. Likewise a task to execute
  // |on_resolve| is posted on |task_runner| as soon as this promise (or an
  // unhandled ancestor) is resolved. A Promise<> for the return value of
  // |on_resolve| or |on_reject| is returned.
  //
  // The following callback return types have special meanings:
  // 1. PromiseResult<Resolve, Reject> lets the callback resolve, reject or
  //    curry a Promise<Resolve, Reject>
  // 2. Promise<Resolve, Reject> where the result is a curried promise.
  //
  // If a promise has multiple Catches/ Thens, they will be run in order of
  // creation.
  //
  // Note if either |on_resolve| or |on_reject| are canceled (due to weak
  // pointer invalidation), then the other must be canceled at the same time as
  // well. This restriction only applies to this form of ThenOn/ThenHere.
  //
  // |task_runner| is const-ref to avoid bloat due the destructor (which posts a
  // task).
  template <typename ThenCb, typename CatchCb>
  auto ThenOn(const scoped_refptr<TaskRunner>& task_runner,
              const Location& from_here,
              ThenCb on_resolve,
              CatchCb on_reject,
              // If callback returns promise,
              // then resolving will be done based on `nested` promise
              // (may be not when callback finished).
              // Must be true if callback returns promise, otherwise false.
              // Checks if callback returns promise only in debug mode.
              IsNestedPromise isNestedPromise = IsNestedPromise()) noexcept {
    DCHECK(!on_resolve.is_null());
    DCHECK(!on_reject.is_null());

    // Extract properties from the |on_resolve| and |on_reject| callbacks.
    using ThenCallbackTraits = internal::CallbackTraits<ThenCb>;
    using CatchCallbackTraits = internal::CallbackTraits<CatchCb>;
    using ThenCallbackArgT = typename ThenCallbackTraits::ArgType;
    using CatchCallbackArgT = typename CatchCallbackTraits::ArgType;

    // Compute the resolve and reject types of the returned Promise.
    using ReturnedPromiseTraits =
        internal::PromiseCombiner<typename ThenCallbackTraits::ResolveType,
                                  typename ThenCallbackTraits::RejectType,
                                  typename CatchCallbackTraits::ResolveType,
                                  typename CatchCallbackTraits::RejectType>;
    using ReturnedPromiseResolveT = typename ReturnedPromiseTraits::ResolveType;
    using ReturnedPromiseRejectT = typename ReturnedPromiseTraits::RejectType;

    static_assert(!std::is_same<NoReject, RejectType>::value,
                  "Can't catch a NoReject promise.");

    static_assert(ReturnedPromiseTraits::valid,
                  "|on_resolve| callback and |on_resolve| callback must return "
                  "compatible types.");

    static_assert(
        internal::IsValidPromiseArg<ResolveType, ThenCallbackArgT>::value ||
            std::is_void<ThenCallbackArgT>::value,
        "|on_resolve| callback must accept Promise::ResolveType or void.");

    static_assert(
        internal::IsValidPromiseArg<RejectType, CatchCallbackArgT>::value ||
            std::is_void<CatchCallbackArgT>::value,
        "|on_reject| callback must accept Promise::RejectType or void.");

    if(isNestedPromise) {
      DCHECK(
        AllowOnlyNestedPromise<typename ThenCallbackTraits::ReturnType>::check_passed)
          << "Nested promise not allowed. Promise posted from "
          << from_here.ToString();
    } else {
      DCHECK(
        DisallowNestedPromise<typename ThenCallbackTraits::ReturnType>::check_passed)
          << "Nested promise not found. Promise posted from "
          << from_here.ToString();
    }

    return Promise<ReturnedPromiseResolveT, ReturnedPromiseRejectT>(
        ConstructAbstractPromiseWithSinglePrerequisite(
            task_runner, from_here, abstract_promise_.get(),
            internal::PromiseExecutor::Data(
                in_place_type_t<internal::ThenAndCatchExecutor<
                    OnceCallback<typename ThenCallbackTraits::SignatureType>,
                    OnceCallback<typename CatchCallbackTraits::SignatureType>,
                    ResolveType, RejectType, Resolved<ReturnedPromiseResolveT>,
                    Rejected<ReturnedPromiseRejectT>>>(),
                internal::ToCallbackBase(RVALUE_CAST(on_resolve)),
                internal::ToCallbackBase(RVALUE_CAST(on_reject)))));
  }

  template <typename ThenCb, typename CatchCb>
  auto ThenOn(const TaskTraits& traits,
              const Location& from_here,
              ThenCb on_resolve,
              CatchCb on_reject,
              // If callback returns promise,
              // then resolving will be done based on `nested` promise
              // (may be not when callback finished).
              // Must be true if callback returns promise, otherwise false.
              // Checks if callback returns promise only in debug mode.
              IsNestedPromise isNestedPromise = IsNestedPromise()) noexcept {
    return ThenOn(CreateSequencedTaskRunner(traits), from_here,
                  FORWARD(on_resolve),
                  FORWARD(on_reject),
                  isNestedPromise);
  }

  // Wraps passed promise into callback that returns it as nested promise.
  template <typename ResolveT, typename RejectT>
  auto ThenNestedPromiseHere(const Location& from_here,
              Promise<ResolveT, RejectT> on_resolve,
              Promise<ResolveT, RejectT> on_reject) noexcept
  {
    return ThenHere(from_here
      , internal::wrapPromiseIntoOnceCallback(on_resolve)
      , internal::wrapPromiseIntoOnceCallback(on_reject)
      , ::base::IsNestedPromise{true});
  }

  template <typename ThenCb, typename CatchCb>
  auto ThenHere(const Location& from_here,
                ThenCb on_resolve,
                CatchCb on_reject,
                // If callback returns promise,
                // then resolving will be done based on `nested` promise
                // (may be not when callback finished).
                // Must be true if callback returns promise, otherwise false.
                // Checks if callback returns promise only in debug mode.
                IsNestedPromise isNestedPromise = IsNestedPromise()) noexcept {
    DCHECK(!on_resolve.is_null());
    DCHECK(!on_reject.is_null());

    // Extract properties from the |on_resolve| and |on_reject| callbacks.
    using ThenCallbackTraits = internal::CallbackTraits<ThenCb>;
    using CatchCallbackTraits = internal::CallbackTraits<CatchCb>;
    using ThenCallbackArgT = typename ThenCallbackTraits::ArgType;
    using CatchCallbackArgT = typename CatchCallbackTraits::ArgType;

    // Compute the resolve and reject types of the returned Promise.
    using ReturnedPromiseTraits =
        internal::PromiseCombiner<typename ThenCallbackTraits::ResolveType,
                                  typename ThenCallbackTraits::RejectType,
                                  typename CatchCallbackTraits::ResolveType,
                                  typename CatchCallbackTraits::RejectType>;
    using ReturnedPromiseResolveT = typename ReturnedPromiseTraits::ResolveType;
    using ReturnedPromiseRejectT = typename ReturnedPromiseTraits::RejectType;

    static_assert(!std::is_same<NoReject, RejectType>::value,
                  "Can't catch a NoReject promise.");

    static_assert(ReturnedPromiseTraits::valid,
                  "|on_resolve| callback and |on_resolve| callback must return "
                  "compatible types.");

    static_assert(
        internal::IsValidPromiseArg<ResolveType, ThenCallbackArgT>::value ||
            std::is_void<ThenCallbackArgT>::value,
        "|on_resolve| callback must accept Promise::ResolveType or void.");

    static_assert(
        internal::IsValidPromiseArg<RejectType, CatchCallbackArgT>::value ||
            std::is_void<CatchCallbackArgT>::value,
        "|on_reject| callback must accept Promise::RejectType or void.");

    if(isNestedPromise) {
      DCHECK(
        AllowOnlyNestedPromise<typename ThenCallbackTraits::ReturnType>::check_passed)
          << "Nested promise not allowed. Promise posted from "
          << from_here.ToString();
    } else {
      DCHECK(
        DisallowNestedPromise<typename ThenCallbackTraits::ReturnType>::check_passed)
          << "Nested promise not found. Promise posted from "
          << from_here.ToString();
    }

    return Promise<ReturnedPromiseResolveT, ReturnedPromiseRejectT>(
        ConstructHereAbstractPromiseWithSinglePrerequisite(
            from_here, abstract_promise_.get(),
            internal::PromiseExecutor::Data(
                in_place_type_t<internal::ThenAndCatchExecutor<
                    OnceCallback<typename ThenCallbackTraits::SignatureType>,
                    OnceCallback<typename CatchCallbackTraits::SignatureType>,
                    ResolveType, RejectType, Resolved<ReturnedPromiseResolveT>,
                    Rejected<ReturnedPromiseRejectT>>>(),
                internal::ToCallbackBase(RVALUE_CAST(on_resolve)),
                internal::ToCallbackBase(RVALUE_CAST(on_reject)))));
  }

  // Wraps passed promise into callback that returns it as nested promise.
  template <typename ResolveT, typename RejectT>
  auto ThenNestedPromiseHere(const Location& from_here,
              Promise<ResolveT, RejectT> on_resolve) noexcept
  {
    return ThenHere(from_here
      , internal::wrapPromiseIntoOnceCallback(on_resolve)
      , ::base::IsNestedPromise{true});
  }

  // A task to execute |finally_callback| on |task_runner| is posted after the
  // parent promise is resolved or rejected. |finally_callback| is not executed
  // if the parent promise is cancelled. Unlike the finally() in Javascript
  // promises, this doesn't return a Promise that is resolved or rejected with
  // the parent's value if |finally_callback| returns void. (We could support
  // this if needed it but it seems unlikely to be used).
  //
  // |task_runner| is const-ref to avoid bloat due the destructor (which posts a
  // task).
  template <typename FinallyCb>
  auto FinallyOn(const scoped_refptr<TaskRunner>& task_runner,
                 const Location& from_here,
                 FinallyCb finally_callback) noexcept {
    // Extract properties from |finally_callback| callback.
    using CallbackTraits = internal::CallbackTraits<FinallyCb>;
    using ReturnedPromiseResolveT = typename CallbackTraits::ResolveType;
    using ReturnedPromiseRejectT = typename CallbackTraits::RejectType;

    using CallbackArgT = typename CallbackTraits::ArgType;
    static_assert(std::is_void<CallbackArgT>::value,
                  "|finally_callback| callback must have no arguments");

    return Promise<ReturnedPromiseResolveT, ReturnedPromiseRejectT>(
        ConstructAbstractPromiseWithSinglePrerequisite(
            task_runner, from_here, abstract_promise_.get(),
            internal::PromiseExecutor::Data(
                in_place_type_t<internal::FinallyExecutor<
                    OnceCallback<typename CallbackTraits::ReturnType()>,
                    Resolved<ReturnedPromiseResolveT>,
                    Rejected<ReturnedPromiseRejectT>>>(),
                internal::ToCallbackBase(RVALUE_CAST(finally_callback)))));
  }

  template <typename FinallyCb>
  auto FinallyOn(const TaskTraits& traits,
                 const Location& from_here,
                 FinallyCb finally_callback) noexcept {
    return FinallyOn(CreateSequencedTaskRunner(traits), from_here,
                     RVALUE_CAST(finally_callback));
  }

  template <typename FinallyCb>
  auto FinallyHere(const Location& from_here,
                   FinallyCb finally_callback) noexcept {
    // Extract properties from |finally_callback| callback.
    using CallbackTraits = internal::CallbackTraits<FinallyCb>;
    using ReturnedPromiseResolveT = typename CallbackTraits::ResolveType;
    using ReturnedPromiseRejectT = typename CallbackTraits::RejectType;

    using CallbackArgT = typename CallbackTraits::ArgType;
    static_assert(std::is_void<CallbackArgT>::value,
                  "|finally_callback| callback must have no arguments");

    return Promise<ReturnedPromiseResolveT, ReturnedPromiseRejectT>(
        ConstructHereAbstractPromiseWithSinglePrerequisite(
            from_here, abstract_promise_.get(),
            internal::PromiseExecutor::Data(
                in_place_type_t<internal::FinallyExecutor<
                    OnceCallback<typename CallbackTraits::ReturnType()>,
                    Resolved<ReturnedPromiseResolveT>,
                    Rejected<ReturnedPromiseRejectT>>>(),
                internal::ToCallbackBase(RVALUE_CAST(finally_callback)))));
  }

  template <typename... Args>
  NOINLINE static Promise<ResolveType, RejectType> CreateResolved(
      const Location& from_here,
      Args&&... args) noexcept {
    internal::PromiseExecutor::Data executor_data(
        in_place_type_t<internal::NoOpPromiseExecutor>(),
        /* can_resolve */ true,
        /* can_reject */ false);

    scoped_refptr<internal::AbstractPromise> promise(
        internal::AbstractPromise::Create(
            nullptr, from_here, nullptr, RejectPolicy::kMustCatchRejection,
            internal::DependentList::ConstructResolved(),
            RVALUE_CAST(executor_data)));
    promise->emplace(in_place_type_t<Resolved<ResolveType>>(),
                     FORWARD(args)...);
    return Promise<ResolveType, RejectType>(RVALUE_CAST(promise));
  }

  template <typename... Args>
  NOINLINE static Promise<ResolveType, RejectType> CreateRejected(
      const Location& from_here,
      Args&&... args) noexcept {
    ((void)(UNREFERENCED_PARAMETER(args)), ...);
    internal::PromiseExecutor::Data executor_data(
        in_place_type_t<internal::NoOpPromiseExecutor>(),
        /* can_resolve */ false,
        /* can_reject */ true);

    scoped_refptr<internal::AbstractPromise> promise(
        internal::AbstractPromise::Create(
            nullptr, from_here, nullptr, RejectPolicy::kMustCatchRejection,
            internal::DependentList::ConstructResolved(),
            RVALUE_CAST(executor_data)));
    return Promise<ResolveType, RejectType>(RVALUE_CAST(promise));
  }

  using ResolveT = ResolveType;
  using RejectT = RejectType;

  void IgnoreUncaughtCatchForTesting() {
    abstract_promise_->IgnoreUncaughtCatchForTesting();
  }

  const scoped_refptr<internal::AbstractPromise>& GetScopedRefptrForTesting()
      const {
    return abstract_promise_;
  }

 private:
  template <typename A, typename B>
  friend class Promise;

  friend class Promises;

  template <typename A, typename B>
  friend class PromiseResult;

  template <typename Container, typename ContainerT>
  friend struct internal::AllContainerHelper;

  template <typename Container, typename ContainerT>
  friend struct internal::RaceContainerHelper;

  template <typename RejectStorage, typename ResultStorage>
  friend struct internal::EmplaceHelper;

  template <typename A, typename B>
  friend class ManualPromiseResolver;
};

// Used for manually resolving and rejecting a Promise. This is for
// compatibility with old code and will eventually be removed.
template <typename ResolveType, typename RejectType = NoReject>
class ManualPromiseResolver {
 public:
  using ResolveHelper = std::conditional_t<
      std::is_void<ResolveType>::value,
      internal::PromiseCallbackHelper<void>,
      internal::PromiseCallbackHelper<ResolveType, ResolveType>>;

  using RejectHelper = std::conditional_t<
      std::is_void<RejectType>::value,
      internal::PromiseCallbackHelper<void>,
      internal::PromiseCallbackHelper<RejectType, RejectType>>;

  ManualPromiseResolver(
      const Location& from_here,
      RejectPolicy reject_policy = RejectPolicy::kMustCatchRejection) {
    promise_ = Promise<ResolveType, RejectType>(
        internal::ConstructManualPromiseResolverPromise(
            from_here, reject_policy,
            /* can_resolve */ !std::is_same<ResolveType, NoResolve>::value,
            /* can_reject */ !std::is_same<RejectType, NoReject>::value));
  }

  ~ManualPromiseResolver() = default;

  void Resolve(Promise<ResolveType, RejectType> promise) noexcept {
    promise_.abstract_promise_->emplace(RVALUE_CAST(promise.abstract_promise_));
    promise_.abstract_promise_->OnResolved();
  }

  template <typename... Args>
  void Resolve(Args&&... arg) noexcept {
    DCHECK(!promise_.abstract_promise_->IsSettled());
    static_assert(!std::is_same<NoResolve, ResolveType>::value,
                  "Can't resolve a NoResolve promise.");
    promise_.abstract_promise_->emplace(
        Resolved<ResolveType>{FORWARD(arg)...});
    promise_.abstract_promise_->OnResolved();
  }

  template <typename... Args>
  void Reject(Args&&... arg) noexcept {
    DCHECK(!promise_.abstract_promise_->IsSettled());
    static_assert(!std::is_same<NoReject, RejectType>::value,
                  "Can't reject a NoReject promise.");
    promise_.abstract_promise_->emplace(
        Rejected<RejectType>{FORWARD(arg)...});
    promise_.abstract_promise_->OnRejected();
  }

  typename ResolveHelper::Callback GetResolveCallback() {
    static_assert(!std::is_same<ResolveType, NoResolve>::value,
                  "Cant resolve a NoResolve promise");
    return ResolveHelper::GetResolveCallback(promise_.abstract_promise_);
  }

  template <typename... Args>
  auto GetResolveCallback() {
    static_assert(!std::is_same<ResolveType, NoResolve>::value,
                  "Cant resolve a NoResolve promise");
    using Helper = internal::PromiseCallbackHelper<ResolveType, Args...>;
    return Helper::GetResolveCallback(promise_.abstract_promise_);
  }

  typename ResolveHelper::RepeatingCallback GetRepeatingResolveCallback() {
    static_assert(!std::is_same<ResolveType, NoResolve>::value,
                  "Cant resolve a NoResolve promise");
    return ResolveHelper::GetRepeatingResolveCallback(
        promise_.abstract_promise_);
  }

  template <typename... Args>
  auto GetRepeatingResolveCallback() {
    static_assert(!std::is_same<ResolveType, NoResolve>::value,
                  "Cant resolve a NoResolve promise");
    using Helper = internal::PromiseCallbackHelper<ResolveType, Args...>;
    return Helper::GetRepeatingResolveCallback(promise_.abstract_promise_);
  }

  typename RejectHelper::Callback GetRejectCallback() {
    static_assert(!std::is_same<NoReject, RejectType>::value,
                  "Can't reject a NoReject promise.");
    return RejectHelper::GetRejectCallback(promise_.abstract_promise_);
  }

  template <typename... Args>
  auto GetRejectCallback() {
    static_assert(!std::is_same<NoReject, RejectType>::value,
                  "Can't reject a NoReject promise.");
    using Helper = internal::PromiseCallbackHelper<RejectType, Args...>;
    return Helper::GetRejectCallback(promise_.abstract_promise_);
  }

  typename RejectHelper::RepeatingCallback GetRepeatingRejectCallback() {
    static_assert(!std::is_same<NoReject, RejectType>::value,
                  "Can't reject a NoReject promise.");
    return RejectHelper::GetRepeatingRejectCallback(promise_.abstract_promise_);
  }

  template <typename... Args>
  auto GetRepeatingRejectCallback() {
    static_assert(!std::is_same<NoReject, RejectType>::value,
                  "Can't reject a NoReject promise.");
    using Helper = internal::PromiseCallbackHelper<RejectType, Args...>;
    return Helper::GetRepeatingRejectCallback(promise_.abstract_promise_);
  }

  Promise<ResolveType, RejectType>& promise() { return promise_; }

 private:
  Promise<ResolveType, RejectType> promise_;
};

class Promises {
 public:
  // Accepts a container of Promise<Resolve, Reject> and returns a
  // Promise<std::vector<Resolve>, Reject>. This is resolved when all
  // prerequisite promises are resolved returning a vector of all the Resolve
  // values, or rejects with the Reject value of the first promise to do so.
  //
  // TODO(alexclarke): Maybe support a container of Variants of promises.
  template <typename Container>
  static auto All(const Location& from_here, const Container& promises) {
    using PromiseType = typename internal::AllContainerHelper<
        Container, typename Container::value_type>::PromiseType;
    if (promises.empty()) {
      DCHECK(false) << "nothing passed to Promise::All";
      return PromiseType::CreateResolved(from_here);
    }
    return internal::AllContainerHelper<
        Container, typename Container::value_type>::All(from_here, promises);
  }

  // Accepts one or more promises and returns a
  // Promise<std::tuple<Resolve> ...>, Reject> which is resolved when all
  // promises resolve or rejects with the Reject value of the first promise to
  // do so.
  //
  // TODO(alexclarke): Support multiple Reject types via variants.
  template <typename... Resolve, typename Reject>
  static auto All(const Location& from_here,
                  Promise<Resolve, Reject>... promises) {
    using ReturnedPromiseResolveT =
        std::tuple<internal::ToNonVoidT<Resolve>...>;
    using ReturnedPromiseRejectT = Reject;

    std::vector<internal::DependentList::Node> prerequisite_list(
        sizeof...(promises));
    int i = 0;
    for (auto&& p : {promises.abstract_promise_.get()...}) {
      prerequisite_list[i++].SetPrerequisite(p);
    }

    internal::PromiseExecutor::Data executor_data(
        (in_place_type_t<internal::AllTuplePromiseExecutor<
             ReturnedPromiseResolveT, ReturnedPromiseRejectT>>()));

    return Promise<ReturnedPromiseResolveT, ReturnedPromiseRejectT>(
        internal::AbstractPromise::Create(
            nullptr, from_here,
            std::make_unique<internal::AbstractPromise::AdjacencyList>(
                RVALUE_CAST(prerequisite_list)),
            RejectPolicy::kMustCatchRejection,
            internal::DependentList::ConstructUnresolved(),
            RVALUE_CAST(executor_data)));
  }

  // All for one Promise equals to that Promise
  template <typename Resolve, typename Reject>
  static Promise<Resolve, Reject> All(const Location& from_here,
                                      Promise<Resolve, Reject> promise) {
    // log about possible error
    DVLOG(9)
      << "only one Promise passed to Promise::All from "
      << from_here.ToString();
    return promise;
  }

  /*
   * Resolved when any
   * input promise is resolved or rejected.
   */
  template <typename Container>
  static auto
  Race(const Location& from_here, const Container& promises) {
    using PromiseType = typename internal::RaceContainerHelper<
        Container, typename Container::value_type>::PromiseType;
    if (promises.empty()) {
      DCHECK(false) << "nothing passed to Promise::Race";
      return PromiseType::CreateResolved(from_here);
    }
    return internal::RaceContainerHelper<
        Container, typename Container::value_type>::Race(from_here, promises);
  }

  /*
   * Resolved when any
   * input promise is resolved or rejected.
   */
  template <typename... Resolve, typename Reject>
  static auto Race(const Location& from_here,
                  Promise<Resolve, Reject>... promises) {
    using ReturnedPromiseResolveT =
        std::tuple<internal::ToNonVoidT<Resolve>...>;
    using ReturnedPromiseRejectT = Reject;

    std::vector<internal::DependentList::Node> prerequisite_list(
        sizeof...(promises));
    int i = 0;
    for (auto&& p : {promises.abstract_promise_.get()...}) {
      prerequisite_list[i++].SetPrerequisite(p);
    }

    internal::PromiseExecutor::Data executor_data(
        (in_place_type_t<internal::RaceTuplePromiseExecutor<
             ReturnedPromiseResolveT, ReturnedPromiseRejectT>>()));

    return Promise<ReturnedPromiseResolveT, ReturnedPromiseRejectT>(
        internal::AbstractPromise::Create(
            nullptr, from_here,
            std::make_unique<internal::AbstractPromise::AdjacencyList>(
                RVALUE_CAST(prerequisite_list)),
            RejectPolicy::kMustCatchRejection,
            internal::DependentList::ConstructUnresolved(),
            RVALUE_CAST(executor_data)));
  }

  // Race for one Promise equals to that Promise
  template <typename Resolve, typename Reject>
  static Promise<Resolve, Reject> Race(const Location& from_here,
                                      Promise<Resolve, Reject> promise) {
    // log about possible error
    DVLOG(9)
      << "only one Promise passed to Promise::Race from "
      << from_here.ToString();
    return promise;
  }
};

}  // namespace base
