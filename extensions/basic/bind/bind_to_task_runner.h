// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <memory>
#include <utility>

#include "base/bind.h"
#include "base/callback.h"
#include "base/location.h"
#include "base/memory/ref_counted.h"
#include "base/task_runner.h"
#include "base/threading/sequenced_task_runner_handle.h"
#include "base/threading/thread_task_runner_handle.h"
#include "basic/rvalue_cast.h"

// This is a helper utility for Bind()ing callbacks to a given TaskRunner.
// The typical use is when |a| (of class |A|) wants to hand a callback such as
// ::base::BindOnce(&A::AMethod, a) to |b|, but needs to ensure that when |b|
// executes the callback, it does so on a specific TaskRunner (for example,
// |a|'s current MessageLoop).
//
// Typical usage: request to be called back on the current thread:
// other->StartAsyncProcessAndCallMeBack(
//    BindToTaskRunner(my_task_runner_,
//                     ::base::BindOnce(&MyClass::MyMethod, this)));
//
// Note that the callback is always posted to the target TaskRunner.
//
// As a convenience, you can use BindToCurrentThread() to bind to the
// TaskRunner for the current thread (ie, ::base::ThreadTaskRunnerHandle::Get()).

namespace basic {
namespace bind_helpers {

template <typename Sig>
struct BindToTaskRunnerTrampoline;

template <typename... Args>
struct BindToTaskRunnerTrampoline<void(Args...)> {
  static void Run(base::TaskRunner* task_runner,
                  ::base::OnceCallback<void(Args...)> callback,
                  Args... args) {
    task_runner->PostTask(
        FROM_HERE,
        ::base::BindOnce(RVALUE_CAST(callback), FORWARD(args)...));
  }
};

}  // namespace bind_helpers

template <typename T>
base::OnceCallback<T> BindToTaskRunner(
    scoped_refptr<::base::TaskRunner> task_runner,
    ::base::OnceCallback<T> callback) {
  return ::base::BindOnce(&bind_helpers::BindToTaskRunnerTrampoline<T>::Run,
                        ::base::RetainedRef(RVALUE_CAST(task_runner)),
                        RVALUE_CAST(callback));
}

template <typename T>
base::RepeatingCallback<T> BindToTaskRunner(
    scoped_refptr<::base::TaskRunner> task_runner,
    ::base::RepeatingCallback<T> callback) {
  return ::base::BindRepeating(&bind_helpers::BindToTaskRunnerTrampoline<T>::Run,
                             ::base::RetainedRef(RVALUE_CAST(task_runner)),
                             RVALUE_CAST(callback));
}

template <typename T>
base::OnceCallback<T> BindToCurrentThread(base::OnceCallback<T> callback) {
  return BindToTaskRunner(base::ThreadTaskRunnerHandle::Get(),
                          RVALUE_CAST(callback));
}

template <typename T>
base::RepeatingCallback<T> BindToCurrentThread(
    ::base::RepeatingCallback<T> callback) {
  return BindToTaskRunner(base::ThreadTaskRunnerHandle::Get(),
                          RVALUE_CAST(callback));
}

template <typename T>
base::OnceCallback<T> BindToCurrentSequence(base::OnceCallback<T> callback) {
  return BindToTaskRunner(base::SequencedTaskRunnerHandle::Get(),
                          RVALUE_CAST(callback));
}

template <typename T>
base::RepeatingCallback<T> BindToCurrentSequence(
    ::base::RepeatingCallback<T> callback) {
  return BindToTaskRunner(base::SequencedTaskRunnerHandle::Get(),
                          RVALUE_CAST(callback));
}

}  // namespace basic
