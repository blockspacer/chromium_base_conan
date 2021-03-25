#include "basic/bind/bind_exec_time_checker.h" // IWYU pragma: associated
#include <basic/strong_types/strong_alias.h>

#include <base/threading/sequenced_task_runner_handle.h>
#include <base/memory/singleton.h>
#include <base/no_destructor.h>
#include <base/task/post_task.h>
#include <base/threading/sequence_local_storage_slot.h>
#include <base/threading/sequenced_task_runner_handle.h>
#include <base/memory/ptr_util.h>
#include <base/lazy_instance.h>

#include <memory>

namespace base {

// Keep the global TLSElapsedTimeStore in a TLS slot so it is impossible to
// incorrectly from the wrong thread.
static base::LazyInstance<
    base::ThreadLocalPointer<TLSElapsedTimeStore>>::DestructorAtExit lazy_tls =
    LAZY_INSTANCE_INITIALIZER;

// static
TLSElapsedTimeStore* TLSElapsedTimeStore::current() {
  return lazy_tls.Pointer()->Get();
}

TLSElapsedTimeStore::TLSElapsedTimeStore() {
  lazy_tls.Pointer()->Set(this);
}

TLSElapsedTimeStore::~TLSElapsedTimeStore() {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  lazy_tls.Pointer()->Set(NULL);
}

void TLSElapsedTimeStore::Set(const base::Time& value) {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  value_ = value;
}

void TLSElapsedTimeStore::SetNow() {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  value_ = ::base::Time::Now();
}

#if 0
using LocalStorageTime = base::Time;

namespace {
base::LazyInstance<
    ::base::SequenceLocalStorageSlot<
      std::unique_ptr<LocalStorageTime>
    >
>::DestructorAtExit
  g_sls_current_sequence_local_storage = LAZY_INSTANCE_INITIALIZER;

}  // namespace

void perSequenceStoreTimeBeforeCallbackExecution()
{
  DCHECK(base::SequencedTaskRunnerHandle::IsSet())
    << "Sequence must be set "
    << FROM_HERE.ToString();

  auto slot = g_sls_current_sequence_local_storage.Get().GetValuePointer();

  if(slot) {
    LOG(ERROR)
      << "Unable to set LocalStorageTime twice in one thread";
    DCHECK(false);
    return;
  }

  std::unique_ptr<LocalStorageTime> local_storage_time
    = std::make_unique<LocalStorageTime>(::base::Time::Now());

  g_sls_current_sequence_local_storage.Get().emplace(std::move(local_storage_time));
}

base::Time perSequenceGetTimeBeforeCallbackExecution()
{
  DCHECK(base::SequencedTaskRunnerHandle::IsSet())
    << "Sequence must be set "
    << FROM_HERE.ToString();

  auto slot = g_sls_current_sequence_local_storage.Get().GetValuePointer();

  if(!slot) {
    LOG(ERROR)
      << "Unable to get LocalStorageTime";
    DCHECK(false);
    return ::base::Time::Now();
  }

  std::unique_ptr<LocalStorageTime>& local_storage_time = *slot;

  return (*local_storage_time);
}

void perSequenceClearTimeBeforeCallbackExecution()
{
  DCHECK(base::SequencedTaskRunnerHandle::IsSet())
    << "Sequence must be set "
    << FROM_HERE.ToString();

  auto slot = g_sls_current_sequence_local_storage.Get().GetValuePointer();

  if(!g_sls_current_sequence_local_storage.Get().GetValuePointer()) {
    std::unique_ptr<LocalStorageTime>& result = *slot;

    result.reset(nullptr);
  }
}
#endif

TLSElapsedTimeStore* ExecTimeChecker::GetTLSElapsedTimeStore()
{
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);

  if (!elapedTimeStore_.get())
    elapedTimeStore_.reset(new TLSElapsedTimeStore);
  return elapedTimeStore_.get();
}

ExecTimeChecker bindExecTimeChecker(
  const ::base::Location& location
  , const ::base::TimeDelta& val)
{
  return ExecTimeChecker{
    location
    , val
  };
}

} // namespace base
