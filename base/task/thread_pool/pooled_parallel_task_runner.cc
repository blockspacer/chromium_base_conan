// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/task/thread_pool/pooled_parallel_task_runner.h"
#include "base/task/thread_pool/pooled_task_runner_delegate.h"

#include "base/task/thread_pool/sequence.h"

#if (defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
#include "emscripten/emscripten.h"
#endif

namespace base {
namespace internal {

PooledParallelTaskRunner::PooledParallelTaskRunner(
    const TaskTraits& traits,
    PooledTaskRunnerDelegate* pooled_task_runner_delegate)
    : traits_(traits),
      pooled_task_runner_delegate_(pooled_task_runner_delegate) {}

PooledParallelTaskRunner::~PooledParallelTaskRunner() = default;

bool PooledParallelTaskRunner::PostDelayedTask(const Location& from_here,
                                               OnceClosure closure,
                                               TimeDelta delay) {
#if defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS)
  std::move(closure).Run();

  /// __TODO__
  /*printf("PooledParallelTaskRunner::PostDelayedTask scheduled after %d\n", delay.InMilliseconds());
  /// \note struct must be freed in callback
  base::STClosure* stClosure = new base::STClosure(std::move(closure));
  void* data = reinterpret_cast<void*>(stClosure);
  DCHECK(data);
  emscripten_async_call([](void* data){
      printf("PooledParallelTaskRunner::PostDelayedTask fired\n");
      DCHECK(data);
      base::STClosure* stClosureData = reinterpret_cast<base::STClosure*>(data);
      std::move(stClosureData->onceClosure_).Run();
      delete stClosureData;
  }, data, delay.is_max() ? 1 : delay.InMilliseconds());*/

  // Returns true if the task may be run
  return true;
#else
  if (!PooledTaskRunnerDelegate::Exists())
    return false;

  // Post the task as part of a one-off single-task Sequence.
  scoped_refptr<Sequence> sequence = MakeRefCounted<Sequence>(
      traits_, this, TaskSourceExecutionMode::kParallel);

  {
    CheckedAutoLock auto_lock(lock_);
    sequences_.insert(sequence.get());
  }

  return pooled_task_runner_delegate_->PostTaskWithSequence(
      Task(from_here, std::move(closure), delay), std::move(sequence));
#endif
}

bool PooledParallelTaskRunner::RunsTasksInCurrentSequence() const {
  return pooled_task_runner_delegate_->IsRunningPoolWithTraits(traits_);
}

void PooledParallelTaskRunner::UnregisterSequence(Sequence* sequence) {
  DCHECK(sequence);

  CheckedAutoLock auto_lock(lock_);
  sequences_.erase(sequence);
}

}  // namespace internal
}  // namespace base
