#pragma once

#include "basic/types_bucket/types_bucket.h"

#include <base/macros.h>
#include <base/logging.h>
#include <base/location.h>
#include <base/sequenced_task_runner.h>
#include <base/threading/thread_checker.h>
#include <base/memory/weak_ptr.h>
#include <base/memory/ref_counted.h>
#include <base/memory/scoped_refptr.h>
#include <basic/rvalue_cast.h>

#include <vector>
#include <string>
#include <atomic>

namespace base {

class SingleThreadTaskRunner;

template <typename T>
struct DefaultSingletonTraits;

} // namespace base

namespace basic {

class ThreadLocalTypesBucket {
 public:
  // Returns the ThreadLocalTypesBucket for the current thread. Allocates a
  // ThreadLocalTypesBucket in TLS if not already present.
  static ThreadLocalTypesBucket* GetForCurrentThread();

  static TypesBucket& CurrentTypesBucket() {
    DCHECK(ThreadLocalTypesBucket::GetForCurrentThread());
    return ThreadLocalTypesBucket::GetForCurrentThread()->GetTypesBucket();
  }

  // Public to support unique_ptr<ThreadLocalTypesBucket>.
  ~ThreadLocalTypesBucket();

  ThreadLocalTypesBucket(const ThreadLocalTypesBucket&) = delete;
  ThreadLocalTypesBucket& operator=(const ThreadLocalTypesBucket&) = delete;

  TypesBucket& GetTypesBucket() {
    DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
    return value_;
  }

private:
  ThreadLocalTypesBucket();

 private:
  TypesBucket value_;

  // Thread-affine per use of TLS in impl.
  THREAD_CHECKER(thread_checker_);
};

} // namespace basic
