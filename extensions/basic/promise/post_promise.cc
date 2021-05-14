#include "basic/promise/post_promise.h" // IWYU pragma: associated

#include <utility>

#include "base/logging.h"
#include "base/task/scoped_set_task_priority_for_current_thread.h"
#include "base/task/task_executor.h"
#include "base/task/thread_pool/thread_pool_impl.h"
#include "basic/rvalue_cast.h"

namespace base {

namespace internal {

base::OnceClosure ClosureExecutePromise(base::WrappedPromise task) {
  return ::base::BindOnce(
    [](base::WrappedPromise task) {
      task.Execute();
    }
    , RVALUE_CAST(task));
}

bool PostPromiseHelperInternal(TaskRunner* task_runner
  , const Location& from_here
  , scoped_refptr<AbstractPromise> promise
  , TimeDelta delay)
{
  return task_runner->PostDelayedTask(from_here,
    ClosureExecutePromise(WrappedPromise(promise)), delay);
}

// To keep PostTask related binary size down we want to do this out of line.
PassedPromise PostPromiseInternal(
    TaskRunner* task_runner,
    const Location& from_here,
    internal::PromiseExecutor::Data&& executor_data,
    TimeDelta delay)
{
  scoped_refptr<AbstractPromise> promise =
    AbstractPromise::CreateNoPrerequisitePromise(
      from_here, RejectPolicy::kMustCatchRejection,
      internal::DependentList::ConstructUnresolved(),
      RVALUE_CAST(executor_data));

  if (!internal::PostPromiseHelperInternal(
        task_runner, from_here, promise, delay))
  {
    /// \todo return false if Post(Delayed)Task failed
    DCHECK(false);
    return PassedPromise();
  }

  return PassedPromise(RVALUE_CAST(promise));
}

}  // namespace internal

}  // namespace base
