#pragma once

#include <base/logging.h>
#include "base/check.h"

#include <chrono> /// \todo replace with `base/time/time.h`

namespace basic {

// Can be used in hot loop (think about update loop of game server).
// Assumed to be updated with each loop iteration
// based on elapsed time interval (time delta).
//
// Do not forget to call `Reset()` if `timer.Passed()`.
//
// EXAMPLE
//
// // timer will fire every 100 nanoseconds, but only if update loop frequent enough.
// const std::chrono::nanoseconds& interval = 100ns;
// ::basic::DeltaTimer timer(interval);
//
// while(...) {
//   const std::chrono::nanoseconds& current_frame_elapsed_dt = ...;
//
//   timer.Update(current_frame_elapsed_dt);
//
//   if(timer.Passed()) {
//     task.Run(current_frame_elapsed_dt, /*last_call_elapsed_dt*/ job.timer.GetCurrent());
//     timer.Reset();
//   }
// }
//
// PERFORMANCE
//
// `DeltaTimer` must be optimized for performance-critical code.
// We `inline` almost all functions due to performance reasons.
//
struct DeltaTimer
{
 public:
  DeltaTimer();

  DeltaTimer(const std::chrono::nanoseconds& interval);

  inline /* `inline` to eleminate function call overhead */
  void Update(const std::chrono::nanoseconds& diff) noexcept
  {
    DCHECK(diff > std::chrono::nanoseconds::min()
      && diff < std::chrono::nanoseconds::max());

    _current += diff;

    if (_current < std::chrono::nanoseconds{0})
      _current = std::chrono::nanoseconds{0};
  }

  inline /* `inline` to eleminate function call overhead */
  bool Passed() noexcept
  {
    return _current >= _interval;
  }

  /// \note keeps remainder by `%= _interval`
  inline /* `inline` to eleminate function call overhead */
  void Reset() noexcept
  {
    DCHECK(_interval != std::chrono::nanoseconds{0});

    if (_current >= _interval)
      _current %= _interval;
  }

  inline /* `inline` to eleminate function call overhead */
  const std::chrono::nanoseconds GetCurrent() const noexcept
  {
    return _current;
  }

  inline /* `inline` to eleminate function call overhead */
  const std::chrono::nanoseconds GetPeriod() const noexcept
  {
    return _interval;
  }

  void SetCurrent(const std::chrono::nanoseconds& current);

  void SetPeriod(const std::chrono::nanoseconds& interval);

 private:
  std::chrono::nanoseconds _interval;
  std::chrono::nanoseconds _current;
};

} // namespace basic
