#include "basic/types_bucket/thread_local_types_bucket.h" // IWYU pragma: associated

#include <base/memory/singleton.h>
#include <base/no_destructor.h>
#include <base/task/post_task.h>
#include <base/threading/sequence_local_storage_slot.h>
#include <base/threading/sequenced_task_runner_handle.h>
#include <base/memory/ptr_util.h>
#include <base/lazy_instance.h>
#include "base/memory/ptr_util.h"
#include "base/no_destructor.h"
#include "base/threading/thread_local.h"

#include <memory>

using namespace base;

namespace basic {

// static
ThreadLocalTypesBucket* ThreadLocalTypesBucket::GetForCurrentThread() {
  static NoDestructor<ThreadLocalOwnedPointer<ThreadLocalTypesBucket>> instance;
  if (!instance->Get())
    instance->Set(WrapUnique(new ThreadLocalTypesBucket));
  return instance->Get();
}

ThreadLocalTypesBucket::ThreadLocalTypesBucket() {}

ThreadLocalTypesBucket::~ThreadLocalTypesBucket() {}

} // namespace basic
