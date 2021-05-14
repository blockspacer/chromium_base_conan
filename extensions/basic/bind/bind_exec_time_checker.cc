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
