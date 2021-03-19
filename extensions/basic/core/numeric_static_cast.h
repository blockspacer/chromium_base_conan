#pragma once

#include <limits>
#include <base/logging.h>

/// \note in most cases use `saturated_cast` or `strict_cast`
/// see `base/numerics/safe_conversions.h`

#define DCHECK_NOT_TRUNCATED(ValueType, CastType, value) \
  DCHECK(static_cast<ValueType>(static_cast<CastType>(value)) == value \
           && "Cast truncates value"); \
  DCHECK(value >= std::numeric_limits<CastType>::min()); \
  DCHECK(value <= std::numeric_limits<CastType>::max())

// checks during runtime (only in DEBUG builds!)
// if there is a value overflow/underflow when using static_cast
//
// EXAMPLE:
// int main() {
//   std::int64_t ll
//     = std::numeric_limits<std::int64_t>::max();
//   ++ll;
//   std::cout << ll << "\n"; // -9223372036854775808
//   std::int32_t t
//     = static_cast<std::int32_t>(ll);
//   std::cout << t << "\n"; // 0
//   std::int32_t m
//     = numeric_static_cast<std::int32_t>(ll);
//   std::cout << m << "\n"; // DCHECK failed with "Cast truncates value"'.
// }
template <typename CastType, typename ValueType>
CastType numeric_static_cast(ValueType value)
{
  DCHECK_NOT_TRUNCATED(ValueType, CastType, value);
  return static_cast<CastType>(value);
}
