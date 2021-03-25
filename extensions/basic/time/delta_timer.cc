#include "basic/time/delta_timer.h" // IWYU pragma: associated

#include "base/check.h"

namespace basic {

void DeltaTimer::SetCurrent(const std::chrono::nanoseconds& current)
{
  DCHECK(current > std::chrono::nanoseconds::min()
    && current < std::chrono::nanoseconds::max());

  _current = current;
}

void DeltaTimer::SetPeriod(const std::chrono::nanoseconds& interval)
{
  DCHECK(interval > std::chrono::nanoseconds{0}
    && interval < std::chrono::nanoseconds::max());

  _interval = interval;
}

DeltaTimer::DeltaTimer()
  : _interval(std::chrono::nanoseconds{0}), _current(std::chrono::nanoseconds{0})
{
}

DeltaTimer::DeltaTimer(const std::chrono::nanoseconds& interval)
  : _interval(interval), _current(std::chrono::nanoseconds{0})
{
}

} // namespace basic
