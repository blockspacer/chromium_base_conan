#pragma once

#include <base/logging.h>

#include <basic/strong_types/money/money.h>
#include <basic/status/statusor.h>
#include <basic/status/status_macros.h>
#include <basic/macros.h>

#define CHECK_MONEY_VALID(money) \
  do { \
    CHECK(::basic::validateMoney(money).ok()); \
    CHECK_MONEY_NANOS(money); \
  } while (0)

#define CHECK_MONEY_NANOS(money) \
  do { \
    CHECK(money.units > 0 ? money.nanos >= 0 : true) \
      << "If `units` is positive, `nanos` must be positive or zero."; \
    CHECK(money.units < 0 ? money.nanos <= 0 : true) \
      << "If `units` is negative, `nanos` must be negative or zero."; \
  } while (0)

#define CHECK_MONEY_NOT_NEGATIVE(money) \
  do { \
    CHECK_GE(money.units, 0); \
    CHECK_MONEY_NANOS(money); \
  } while (0)

#define CHECK_MONEY_NOT_POSITIVE(money) \
  do { \
    CHECK_LE(money.units, 0); \
    CHECK_MONEY_NANOS(money); \
  } while (0)

namespace basic {

// Returns OK if the given money is a valid value. The possible validation
// errors include invalid currency_code format, nanos out of range, and
// the signs of units and nanos disagree. In all error cases the error
// code is INVALID_ARGUMENT, with an error message.
//
// EXAMPLE
//
// validateMoney{"USD", units(1), nanos(1000000000)}
// results in INVALID_ARGUMENT due to out of range
//
// validateMoney{"USD", units(1), nanos(-1)}
// results in INVALID_ARGUMENT due to sign inconsistency
//
// validateMoney{"A__INVALID", units(1), nanos(1)}
// results in INVALID_ARGUMENT due to invalid currency code
//
MUST_USE_RETURN_VALUE
Status validateMoney(
  const Money& money);

// Returns 1 if the given money has a positive amount, 0 if money has zero
// amount, and -1 if money has a negative amount.
// The given money must be valid (see Validate) or the result may be wrong.
//
// EXAMPLE
//
// Sign of $-2.75 is -1.
// Sign of $8.3 is 1.
// Sign of $0.0 is 0.
MUST_USE_RETURN_VALUE
int getAmountSign(const Money& money);

MUST_USE_RETURN_VALUE
bool isPositive(const Money& money);

MUST_USE_RETURN_VALUE
bool isNegative(const Money& money);

MUST_USE_RETURN_VALUE
bool isZero(const Money& money);

// Adds a and b together into sum. The caller owns the lifetime of sum. Both
// a and b must be valid money values (see ValidateMoney), otherwise sum may
// contain invalid value.
// Returns OK if successful. There are two possible errors:
// (1) If the currency_code of a and b are different, sum is cleared and
// INVALID_ARGUMENT is returned.
// (2) If arithmetic overflow occurs during the additions, sum is set to the
// maximum positive or minimum negative amount depending on the direction of
// the overflow, and OUT_OF_RANGE is returned.
MUST_USE_RETURN_VALUE
StatusOr<Money> tryAddMoney(const Money& a
  , const Money& b
  , bool fail_on_overflow = true);

/// \note If `saturatedAddMoney` overflows, than value will be saturated
/// (ex. if you add 123 to INT64_MAX it result in INT64_MAX)
/// Prefer `tryAddMoney` if you want to check for overflow i.e. `OUT_OF_RANGE`.
//
// Returns the sum of a and b. Both a and b must be valid money values (see
// ValidateMoney), otherwise the result may contain invalid value. The
// caller must ensure a and b have the same currency_code, otherwise it's a
// fatal error.
//
MUST_USE_RETURN_VALUE
StatusOr<Money> saturatedAddMoney(const Money& a
  , const Money& b);

} // namespace basic
