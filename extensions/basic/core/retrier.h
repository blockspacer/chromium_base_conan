#pragma once

#include <cstddef>
#include <utility>

#include <base/bind.h>
#include <base/compiler_specific.h>
#include <base/location.h>
#include <base/logging.h>
#include <base/macros.h>
#include <base/memory/ref_counted.h>
#include <base/memory/weak_ptr.h>
#include <base/sequenced_task_runner.h>
#include <base/files/file_util.h>
#include <base/time/time_override.h>
#include <base/threading/platform_thread.h>

// USAGE
//
// constexpr auto kMaxRetryDuration = base::TimeDelta::FromMilliseconds(1000);
// constexpr auto kSleepDuration = base::TimeDelta::FromMilliseconds(10);
// constexpr size_t kMaxAttempts = 10U;
//
// basic::RetrierWithDuration retrierDuration(kMaxRetryDuration, kSleepDuration);
// basic::RetrierWithCounter retrierCounter(kMaxAttempts);
//
// base::File::Error error = base::File::FILE_OK;
// do {
//   error = filesystem_->RenameFile(src_file_path, destination);
//   if (error == base::File::FILE_OK)
//     return result;
// } while (retrierDuration.ShouldKeepTrying() && retrierCounter.ShouldKeepTrying());
//
namespace basic {

/// \note blocking API (uses `PlatformThread::Sleep`)
//
class RetrierWithDuration {
 public:
  RetrierWithDuration(
    // The maximum time for the |RetrierWithDuration|
    // to indicate that an operation should be retried.
    const base::TimeDelta& max_retry_duration
    , const base::TimeDelta& time_to_sleep
    , const base::TimeTicks start = base::subtle::TimeTicksNowIgnoringOverride())
    : start_(start)
    , limit_(start_ + max_retry_duration)
    , last_(start_)
    , time_to_sleep_(time_to_sleep) {}

  ~RetrierWithDuration() = default;

  inline bool ShouldKeepTrying() noexcept {
    if (last_ < limit_) {
      base::PlatformThread::Sleep(time_to_sleep_);
      last_ = base::subtle::TimeTicksNowIgnoringOverride();
      return true;
    }
    return false;
  }

 private:
  const base::TimeTicks start_;
  base::TimeTicks limit_;
  base::TimeTicks last_;
  base::TimeDelta time_to_sleep_;
  DISALLOW_COPY_AND_ASSIGN(RetrierWithDuration);
};

/// \note See also `base::BarrierClosure`
//
class RetrierWithCounter {
 public:
  RetrierWithCounter(
    const size_t max_attempts
    , const size_t start = 0U)
    : start_(start)
    , limit_(max_attempts)
    , last_(start_)
    {}

  ~RetrierWithCounter() = default;

  inline bool ShouldKeepTrying() noexcept {
    if (last_ < limit_) {
      last_++;
      return true;
    }
    return false;
  }

 private:
  size_t limit_;
  size_t last_;
  DISALLOW_COPY_AND_ASSIGN(RetrierWithCounter);
};

}  // namespace basic
