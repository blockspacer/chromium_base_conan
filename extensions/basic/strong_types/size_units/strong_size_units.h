#pragma once

#include <base/macros.h>
#include <base/numerics/safe_conversions.h>
#include <base/numerics/checked_math.h>
#include <base/numerics/clamped_math.h>

#include <utility>
#include <type_traits>

namespace base {
namespace internal {

DECLARE_STRONG_CHECKED_TYPE(CheckedBytes, uint64_t);
DECLARE_STRONG_CHECKED_TYPE(CheckedKilobytes, uint64_t);
DECLARE_STRONG_CHECKED_TYPE(CheckedMegabytes, uint64_t);
DECLARE_STRONG_CHECKED_TYPE(CheckedGigabytes, uint64_t);

} // namespace internal
} // namespace base

namespace basic {

using CheckedBytes = ::base::internal::CheckedBytes;
using CheckedKilobytes = ::base::internal::CheckedKilobytes;
using CheckedMegabytes = ::base::internal::CheckedMegabytes;
using CheckedGigabytes = ::base::internal::CheckedGigabytes;

// USAGE
//
// basic::CheckedBytes valBytes{2500000};
// CHECK(basic::bytesToMegabytes(valBytes).ValueOrDie() == 2);
//
inline CheckedMegabytes bytesToMegabytes(CheckedBytes bytes)
{
  CheckedMegabytes result(bytes.ValueOrDie());
  using type = CheckedMegabytes::type;
  result >>= ::base::saturated_cast<type>(20UL);
  return result;
}

// USAGE
//
// basic::CheckedKilobytes valKb{5};
// CHECK(basic::kilobytesToBytes(valKb).ValueOrDie() == 5120);
//
inline CheckedBytes kilobytesToBytes(CheckedKilobytes kilobytes)
{
  CheckedBytes result(kilobytes.ValueOrDie());
  using type = CheckedBytes::type;
  result <<= ::base::saturated_cast<type>(10UL);
  return result;
}

// USAGE
//
// basic::CheckedMegabytes valMb{1};
// CHECK(basic::megabytesToBytes(valMb).ValueOrDie() == 1048576);
//
inline CheckedBytes megabytesToBytes(CheckedMegabytes megabytes)
{
  CheckedBytes result(megabytes.ValueOrDie());
  using type = CheckedBytes::type;
  result <<= ::base::saturated_cast<type>(20UL);
  return result;
}

// USAGE
//
// basic::CheckedGigabytes valGb{1};
// CHECK(basic::gigabytesToBytes(valGb).ValueOrDie() == 1073741824);
//
inline CheckedBytes gigabytesToBytes(CheckedGigabytes gigabytes)
{
  CheckedBytes result(gigabytes.ValueOrDie());
  using type = CheckedBytes::type;
  result <<= ::base::saturated_cast<type>(30UL);
  return result;
}

}  // namespace basic
