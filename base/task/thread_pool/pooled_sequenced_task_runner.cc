// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/task/thread_pool/pooled_sequenced_task_runner.h"

#include "base/sequence_token.h"

#if (defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS))
#include "emscripten/emscripten.h"
#endif

namespace base {
namespace internal {

PooledSequencedTaskRunner::PooledSequencedTaskRunner(
    const TaskTraits& traits,
    PooledTaskRunnerDelegate* pooled_task_runner_delegate)
    : pooled_task_runner_delegate_(pooled_task_runner_delegate),
      sequence_(MakeRefCounted<Sequence>(traits,
                                         this,
                                         TaskSourceExecutionMode::kSequenced)) {
}

PooledSequencedTaskRunner::~PooledSequencedTaskRunner() = default;

bool PooledSequencedTaskRunner::PostDelayedTask(const Location& from_here,
                                                OnceClosure closure,
                                                TimeDelta delay) {
#if defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS)
  std::move(closure).Run();

  /// __TODO__
  /*printf("PooledSequencedTaskRunner::PostDelayedTask scheduled after %d\n", delay.InMilliseconds());
  /// \note struct must be freed in callback
  base::STClosure* stClosure = new base::STClosure(std::move(closure));
  void* data = reinterpret_cast<void*>(stClosure);
  DCHECK(data);
  emscripten_async_call([](void* data){
      printf("PooledSequencedTaskRunner::PostDelayedTask fired\n");
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

  Task task(from_here, std::move(closure), delay);

  // Post the task as part of |sequence_|.
  return pooled_task_runner_delegate_->PostTaskWithSequence(std::move(task),
                                                            sequence_);
#endif
}

bool PooledSequencedTaskRunner::PostNonNestableDelayedTask(
    const Location& from_here,
    OnceClosure closure,
    TimeDelta delay) {
  // Tasks are never nested within the thread pool.
  return PostDelayedTask(from_here, std::move(closure), delay);
}

bool PooledSequencedTaskRunner::RunsTasksInCurrentSequence() const {
  return sequence_->token() == SequenceToken::GetForCurrentThread();
}

void PooledSequencedTaskRunner::UpdatePriority(TaskPriority priority) {
  pooled_task_runner_delegate_->UpdatePriority(sequence_, priority);
}

}  // namespace internal
}  // namespace base
