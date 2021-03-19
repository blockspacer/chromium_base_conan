#pragma once

#include <base/macros.h>
#include <base/numerics/safe_conversions.h>
#include <base/numerics/checked_math.h>
#include <base/numerics/clamped_math.h>

#include <utility>
#include <type_traits>

namespace base {
namespace internal {

DECLARE_STRONG_CHECKED_TYPE(CheckedSeconds, uint64_t);
DECLARE_STRONG_CHECKED_TYPE(CheckedMilliseconds, uint64_t);
DECLARE_STRONG_CHECKED_TYPE(CheckedMicroseconds, uint64_t);
DECLARE_STRONG_CHECKED_TYPE(CheckedNanoseconds, uint64_t);

} // namespace internal
} // namespace base

namespace basic {

using CheckedSeconds = ::base::internal::CheckedSeconds;
using CheckedMilliseconds = ::base::internal::CheckedMilliseconds;
using CheckedMicroseconds = ::base::internal::CheckedMicroseconds;
using CheckedNanoseconds = ::base::internal::CheckedNanoseconds;

// USAGE
//
// basic::CheckedMilliseconds valMs{2500};
// CHECK(basic::millisecondsToSeconds(valMs).ValueOrDie() == 2);
//
inline CheckedSeconds millisecondsToSeconds(CheckedMilliseconds valMs)
{
  CheckedSeconds result(valMs.ValueOrDie());
  using type = CheckedSeconds::type;
  result /= ::base::saturated_cast<type>(1000UL);
  return result;
}

}  // namespace basic
