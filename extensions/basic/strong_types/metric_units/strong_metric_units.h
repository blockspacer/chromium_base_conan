#pragma once

#include <base/macros.h>
#include <base/numerics/safe_conversions.h>
#include <base/numerics/checked_math.h>
#include <base/numerics/clamped_math.h>

#include <utility>
#include <type_traits>

namespace base {
namespace internal {

DECLARE_STRONG_CHECKED_TYPE(CheckedMeters, uint64_t);
DECLARE_STRONG_CHECKED_TYPE(CheckedCentimeters, uint64_t);
DECLARE_STRONG_CHECKED_TYPE(CheckedMillimeters, uint64_t);
DECLARE_STRONG_CHECKED_TYPE(CheckedKilometers, uint64_t);

} // namespace internal
} // namespace base

namespace basic {

using CheckedMeters = ::base::internal::CheckedMeters;
using CheckedCentimeters = ::base::internal::CheckedCentimeters;
using CheckedMillimeters = ::base::internal::CheckedMillimeters;
using CheckedKilometers = ::base::internal::CheckedKilometers;

}  // namespace basic
