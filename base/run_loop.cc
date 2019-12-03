// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/run_loop.h"

#include "base/bind.h"
#include "base/callback.h"
#include "base/cancelable_callback.h"
#include "base/lazy_instance.h"
#include "base/message_loop/message_loop.h"
#include "base/no_destructor.h"
#include "base/single_thread_task_runner.h"
#include "base/threading/thread_local.h"
#include "base/threading/thread_task_runner_handle.h"
#include "build/build_config.h"

/*#if (defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
#include "base/task/sequence_manager/thread_controller_with_message_pump_impl.h"
#include "base/bind.h"
#include "base/bind_helpers.h"
#include "base/memory/scoped_refptr.h"
#include "base/single_thread_task_runner.h"
#include "base/threading/thread_task_runner_handle.h"

static bool g_initialized = false;
#endif*/

namespace base {

namespace {

LazyInstance<ThreadLocalPointer<RunLoop::Delegate>>::Leaky tls_delegate =
    LAZY_INSTANCE_INITIALIZER;

//std::unique_ptr<RunLoop::Delegate> g_tls_delegate;

// Runs |closure| immediately if this is called on |task_runner|, otherwise
// forwards |closure| to it.
void ProxyToTaskRunner(scoped_refptr<SequencedTaskRunner> task_runner,
                       OnceClosure closure) {
  if (task_runner->RunsTasksInCurrentSequence()) {
    std::move(closure).Run();
    return;
  }
  task_runner->PostTask(FROM_HERE, std::move(closure));
}

ThreadLocalPointer<RunLoop::ScopedRunTimeoutForTest>*
ScopedRunTimeoutForTestTLS() {
  static NoDestructor<ThreadLocalPointer<RunLoop::ScopedRunTimeoutForTest>> tls;
  return tls.get();
}

void OnRunTimeout(RunLoop* run_loop, OnceClosure on_timeout) {
#if !(defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  run_loop->Quit();
  std::move(on_timeout).Run();
#endif
}

}  // namespace

RunLoop::ScopedRunTimeoutForTest::ScopedRunTimeoutForTest(
    TimeDelta timeout,
    RepeatingClosure on_timeout)
    : timeout_(timeout),
      on_timeout_(std::move(on_timeout)),
      nested_timeout_(ScopedRunTimeoutForTestTLS()->Get()) {
  DCHECK_GT(timeout_, TimeDelta());
  DCHECK(on_timeout_);
  ScopedRunTimeoutForTestTLS()->Set(this);
}

RunLoop::ScopedRunTimeoutForTest::~ScopedRunTimeoutForTest() {
  ScopedRunTimeoutForTestTLS()->Set(nested_timeout_);
}

// static
const RunLoop::ScopedRunTimeoutForTest*
RunLoop::ScopedRunTimeoutForTest::Current() {
  return ScopedRunTimeoutForTestTLS()->Get();
}

RunLoop::ScopedDisableRunTimeoutForTest::ScopedDisableRunTimeoutForTest()
    : nested_timeout_(ScopedRunTimeoutForTestTLS()->Get()) {
  ScopedRunTimeoutForTestTLS()->Set(nullptr);
}

RunLoop::ScopedDisableRunTimeoutForTest::~ScopedDisableRunTimeoutForTest() {
  ScopedRunTimeoutForTestTLS()->Set(nested_timeout_);
}

RunLoop::Delegate::Delegate() {
  // The Delegate can be created on another thread. It is only bound in
  // RegisterDelegateForCurrentThread().
  DETACH_FROM_THREAD(bound_thread_checker_);
}

RunLoop::Delegate::~Delegate() {

/*#if (defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  // nothing
#else*/
  DCHECK_CALLED_ON_VALID_THREAD(bound_thread_checker_);
  // A RunLoop::Delegate may be destroyed before it is bound, if so it may still
  // be on its creation thread (e.g. a Thread that fails to start) and
  // shouldn't disrupt that thread's state.
  if (bound_)
    tls_delegate.Get().Set(nullptr);
//#endif
}

bool RunLoop::Delegate::ShouldQuitWhenIdle() {
#if (defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  return false;
#else
  return active_run_loops_.top()->quit_when_idle_received_;
#endif
}

// static
void RunLoop::RegisterDelegateForCurrentThread(Delegate* delegate) {

/*#if (defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  if(!g_initialized) {
    g_initialized = true;

    // Bind |delegate| to this thread.
    DCHECK(!delegate->bound_);
    DCHECK_CALLED_ON_VALID_THREAD(delegate->bound_thread_checker_);

    // There can only be one RunLoop::Delegate per thread.
    DCHECK(!tls_delegate.Get().Get())
        << "Error: Multiple RunLoop::Delegates registered on the same thread.\n\n"
           "Hint: You perhaps instantiated a second "
           "MessageLoop/ScopedTaskEnvironment on a thread that already had one?";
    tls_delegate.Get().Set(delegate);
    delegate->bound_ = true;
  }
#else*/
#if !(defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  // Bind |delegate| to this thread.
  DCHECK(!delegate->bound_);
  DCHECK_CALLED_ON_VALID_THREAD(delegate->bound_thread_checker_);

  // There can only be one RunLoop::Delegate per thread.
  DCHECK(!tls_delegate.Get().Get())
      << "Error: Multiple RunLoop::Delegates registered on the same thread.\n\n"
         "Hint: You perhaps instantiated a second "
         "MessageLoop/ScopedTaskEnvironment on a thread that already had one?";
#endif

  tls_delegate.Get().Set(delegate);
  delegate->bound_ = true;
//#endif
}

RunLoop::RunLoop(Type type)
    : delegate_(tls_delegate.Get().Get()),
      type_(type),
      origin_task_runner_(ThreadTaskRunnerHandle::Get()),
      weak_factory_(this) {
  DCHECK(delegate_) << "A RunLoop::Delegate must be bound to this thread prior "
                       "to using RunLoop.";
  DCHECK(origin_task_runner_);
}

RunLoop::~RunLoop() {
  // TODO(gab): Fix bad usage and enable this check, http://crbug.com/715235.
  // DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
}

void RunLoop::Run() {
  RunWithTimeout(TimeDelta::Max());
}

void RunLoop::RunWithTimeout(TimeDelta timeout) {
  //P_LOG("RunLoop::RunWithTimeout 1()\n");
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  if (!BeforeRun())
    return;
  //P_LOG("RunLoop::RunWithTimeout 2()\n");

  // If there is a ScopedRunTimeoutForTest active then set the timeout.
  // TODO(crbug.com/905412): Use real-time for Run() timeouts so that they
  // can be applied even in tests which mock TimeTicks::Now().
  CancelableOnceClosure cancelable_timeout;
  ScopedRunTimeoutForTest* run_timeout = ScopedRunTimeoutForTestTLS()->Get();
  if (run_timeout) {
    cancelable_timeout.Reset(
        BindOnce(&OnRunTimeout, Unretained(this), run_timeout->on_timeout()));
    ThreadTaskRunnerHandle::Get()->PostDelayedTask(
        FROM_HERE, cancelable_timeout.callback(), run_timeout->timeout());
  }
  //P_LOG("RunLoop::RunWithTimeout 3()\n");

  if(!delegate_) {
    printf("invalid delegate in RunLoop\n");
  }

#if (defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  //P_LOG("RunLoop::RunWithTimeout 3.1()\n");
  const bool application_tasks_allowed = false;
#else
  //P_LOG("RunLoop::RunWithTimeout 3.2()\n");

  // It is okay to access this RunLoop from another sequence while Run() is
  // active as this RunLoop won't touch its state until after that returns (if
  // the RunLoop's state is accessed while processing Run(), it will be re-bound
  // to the accessing sequence for the remainder of that Run() -- accessing from
  // multiple sequences is still disallowed).
  DETACH_FROM_SEQUENCE(sequence_checker_);

  DCHECK_EQ(this, delegate_->active_run_loops_.top());
  const bool application_tasks_allowed =
      delegate_->active_run_loops_.size() == 1U ||
      type_ == Type::kNestableTasksAllowed;

  //P_LOG("RunLoop::RunWithTimeout 3.5()\n");
  delegate_->Run(application_tasks_allowed, timeout);
#endif
  //P_LOG("RunLoop::RunWithTimeout 4()\n");

  // Rebind this RunLoop to the current thread after Run().
  DETACH_FROM_SEQUENCE(sequence_checker_);
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

#if (defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  // TODO: delegate_->Run is async, so we reached function end immediately
#else
  AfterRun();
#endif
  //P_LOG("RunLoop::RunWithTimeout 5()\n");
}

void RunLoop::RunUntilIdle() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  quit_when_idle_received_ = true;
  Run();
}

void RunLoop::Quit() {
  // Thread-safe.

  DCHECK(origin_task_runner_);

  // This can only be hit if run_loop->Quit() is called directly (QuitClosure()
  // proxies through ProxyToTaskRunner() as it can only deref its WeakPtr on
  // |origin_task_runner_|).
  if (!origin_task_runner_->RunsTasksInCurrentSequence()) {
    origin_task_runner_->PostTask(FROM_HERE,
                                  BindOnce(&RunLoop::Quit, Unretained(this)));
    return;
  }

  quit_called_ = true;
#if !(defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  if (running_ && delegate_->active_run_loops_.top() == this) {
    // This is the inner-most RunLoop, so quit now.
    delegate_->Quit();
  }
#endif
}

void RunLoop::QuitWhenIdle() {
  // Thread-safe.

  DCHECK(origin_task_runner_);

  // This can only be hit if run_loop->QuitWhenIdle() is called directly
  // (QuitWhenIdleClosure() proxies through ProxyToTaskRunner() as it can only
  // deref its WeakPtr on |origin_task_runner_|).
  if (!origin_task_runner_->RunsTasksInCurrentSequence()) {
    origin_task_runner_->PostTask(
        FROM_HERE, BindOnce(&RunLoop::QuitWhenIdle, Unretained(this)));
    return;
  }

  quit_when_idle_received_ = true;
}

Closure RunLoop::QuitClosure() {
  // TODO(gab): Fix bad usage and enable this check, http://crbug.com/715235.
  // DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  allow_quit_current_deprecated_ = false;

  DCHECK(origin_task_runner_);

  // Need to use ProxyToTaskRunner() as WeakPtrs vended from
  // |weak_factory_| may only be accessed on |origin_task_runner_|.
  // TODO(gab): It feels wrong that QuitClosure() is bound to a WeakPtr.
  return Bind(&ProxyToTaskRunner, origin_task_runner_,
              Bind(&RunLoop::Quit, weak_factory_.GetWeakPtr()));
}

Closure RunLoop::QuitWhenIdleClosure() {
  // TODO(gab): Fix bad usage and enable this check, http://crbug.com/715235.
  // DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  allow_quit_current_deprecated_ = false;

  // Need to use ProxyToTaskRunner() as WeakPtrs vended from
  // |weak_factory_| may only be accessed on |origin_task_runner_|.
  // TODO(gab): It feels wrong that QuitWhenIdleClosure() is bound to a WeakPtr.
  return Bind(&ProxyToTaskRunner, origin_task_runner_,
              Bind(&RunLoop::QuitWhenIdle, weak_factory_.GetWeakPtr()));
}

// static
bool RunLoop::IsRunningOnCurrentThread() {
#if (defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  return true;
#else
  Delegate* delegate = tls_delegate.Get().Get();
  return delegate && !delegate->active_run_loops_.empty();
#endif
}

// static
bool RunLoop::IsNestedOnCurrentThread() {
#if (defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  return false;
#else
  Delegate* delegate = tls_delegate.Get().Get();
  return delegate && delegate->active_run_loops_.size() > 1;
#endif
}

// static
void RunLoop::AddNestingObserverOnCurrentThread(NestingObserver* observer) {
//#if !(defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  Delegate* delegate = tls_delegate.Get().Get();
  DCHECK(delegate);
  delegate->nesting_observers_.AddObserver(observer);
//#endif
}

// static
void RunLoop::RemoveNestingObserverOnCurrentThread(NestingObserver* observer) {
//#if !(defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  Delegate* delegate = tls_delegate.Get().Get();
  DCHECK(delegate);
  delegate->nesting_observers_.RemoveObserver(observer);
//#endif
}

// static
void RunLoop::QuitCurrentDeprecated() {
#if !(defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  DCHECK(IsRunningOnCurrentThread());
  Delegate* delegate = tls_delegate.Get().Get();
  DCHECK(delegate->active_run_loops_.top()->allow_quit_current_deprecated_)
      << "Please migrate off QuitCurrentDeprecated(), e.g. to QuitClosure().";
  delegate->active_run_loops_.top()->Quit();
#endif
}

// static
void RunLoop::QuitCurrentWhenIdleDeprecated() {
#if !(defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  DCHECK(IsRunningOnCurrentThread());
  Delegate* delegate = tls_delegate.Get().Get();
  DCHECK(delegate->active_run_loops_.top()->allow_quit_current_deprecated_)
      << "Please migrate off QuitCurrentWhenIdleDeprecated(), e.g. to "
         "QuitWhenIdleClosure().";
  delegate->active_run_loops_.top()->QuitWhenIdle();
#endif
}

// static
Closure RunLoop::QuitCurrentWhenIdleClosureDeprecated() {
  // TODO(844016): Fix callsites and enable this check, or remove the API.
  // Delegate* delegate = tls_delegate.Get().Get();
  // DCHECK(delegate->active_run_loops_.top()->allow_quit_current_deprecated_)
  //     << "Please migrate off QuitCurrentWhenIdleClosureDeprecated(), e.g to "
  //        "QuitWhenIdleClosure().";
  return Bind(&RunLoop::QuitCurrentWhenIdleDeprecated);
}

#if !DCHECK_IS_ON() || (defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
// Defined out of line so that the compiler doesn't inline these and realize
// the scope has no effect and then throws an "unused variable" warning in
// non-dcheck builds.
RunLoop::ScopedDisallowRunningForTesting::ScopedDisallowRunningForTesting() =
    default;
RunLoop::ScopedDisallowRunningForTesting::~ScopedDisallowRunningForTesting() =
    default;
#elif DCHECK_IS_ON()
RunLoop::ScopedDisallowRunningForTesting::ScopedDisallowRunningForTesting()
    : current_delegate_(tls_delegate.Get().Get()),
      previous_run_allowance_(
          current_delegate_ ? current_delegate_->allow_running_for_testing_
                            : false) {
  if (current_delegate_)
    current_delegate_->allow_running_for_testing_ = false;
}

RunLoop::ScopedDisallowRunningForTesting::~ScopedDisallowRunningForTesting() {
  DCHECK_EQ(current_delegate_, tls_delegate.Get().Get());
  if (current_delegate_)
    current_delegate_->allow_running_for_testing_ = previous_run_allowance_;
}
#endif  // DCHECK_IS_ON()

bool RunLoop::BeforeRun() {
  //P_LOG("RunLoop::BeforeRun 1\n");
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

#if DCHECK_IS_ON() && !(defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  DCHECK(delegate_->allow_running_for_testing_)
      << "RunLoop::Run() isn't allowed in the scope of a "
         "ScopedDisallowRunningForTesting. Hint: if mixing "
         "TestMockTimeTaskRunners on same thread, use TestMockTimeTaskRunner's "
         "API instead of RunLoop to drive individual task runners.";

  DCHECK(!run_called_);
  run_called_ = true;

  // Allow Quit to be called before Run.
  if (quit_called_)
    return false;
#endif  // DCHECK_IS_ON()

  //P_LOG("RunLoop::BeforeRun 2\n");

#if !(defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  auto& active_run_loops_ = delegate_->active_run_loops_;
  active_run_loops_.push(this);
#endif

  //P_LOG("RunLoop::BeforeRun 3\n");

#if !(defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  const bool is_nested = active_run_loops_.size() > 1;

  //P_LOG("RunLoop::BeforeRun 4\n");
  if (is_nested) {
    for (auto& observer : delegate_->nesting_observers_)
      observer.OnBeginNestedRunLoop();

    //P_LOG("RunLoop::BeforeRun 5\n");
    if (type_ == Type::kNestableTasksAllowed)
      delegate_->EnsureWorkScheduled();
  }
#endif

  //P_LOG("RunLoop::BeforeRun 6\n");

  running_ = true;
  return true;
}

void RunLoop::AfterRun() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  running_ = false;

#if !(defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
  auto& active_run_loops_ = delegate_->active_run_loops_;
  DCHECK_EQ(active_run_loops_.top(), this);
  active_run_loops_.pop();

  RunLoop* previous_run_loop =
      active_run_loops_.empty() ? nullptr : active_run_loops_.top();

  if (previous_run_loop) {
    for (auto& observer : delegate_->nesting_observers_)
      observer.OnExitNestedRunLoop();
  }

  // Execute deferred Quit, if any:
  if (previous_run_loop && previous_run_loop->quit_called_)
    delegate_->Quit();
#endif
}

}  // namespace base
