#include "basic/bind/delay_time_checker.h" // IWYU pragma: associated

namespace base {

DelayTimeChecker bindDelayTimeChecker(
  const ::base::Location& location
  , const ::base::TimeDelta& val)
{
  return DelayTimeChecker{
    location
    , val
  };
}

} // namespace base
