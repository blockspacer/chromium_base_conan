#include <basic/strong_types/money/money_util.h> // IWYU pragma: associated
#include <basic/macros.h>

namespace basic {

// The money value must be between -999,999,999 and +999,999,999 inclusive.
static const int kBillion = 1000000000;

Status validateMoney(const Money& money)
{
  using namespace ::basic::error;

  // The three-letter currency code defined in ISO 4217.
  if (money.currency_code().empty() || money.currency_code().length() != 3)
  {
    RETURN_ERROR(INVALID_ARGUMENT)
      << "The currency_code field in Money must be 3 letters long.";
  }

  if ((money.units() > 0 && money.nanos() < 0) ||
      (money.units() < 0 && money.nanos() > 0))
  {
    RETURN_ERROR(INVALID_ARGUMENT)
      << "The signs of units and nanos field in Money must agree.";
  }

  const int kMaxNanos = 999999999;
  if (money.nanos() < -kMaxNanos || money.nanos() > kMaxNanos)
  {
    RETURN_ERROR(INVALID_ARGUMENT)
      << "The nanos field in Money must be between -999999999 and "
         "999999999 inclusive.";
  }

  RETURN_OK();
}

int getAmountSign(const Money& money)
{
  DCHECK(::basic::validateMoney(money).ok())
    << "The given money must be valid or the result may be wrong.";

  if (money.units() > 0) {
    return 1;
  } else if (money.units() < 0) {
    return -1;
  } else if (money.nanos() > 0) {
    return 1;
  } else if (money.nanos() < 0) {
    return -1;
  } else {
    return 0;
  }
}

MUST_USE_RETURN_VALUE
bool isPositive(const Money& money)
{
  // Sign of $8.3 is 1.
  return getAmountSign(money) == 1;
}

MUST_USE_RETURN_VALUE
bool isNegative(const Money& money)
{
  // Sign of $-2.75 is -1.
  return getAmountSign(money) == -1;
}

MUST_USE_RETURN_VALUE
bool isZero(const Money& money)
{
  // Sign of $0.0 is 0.
  return getAmountSign(money) == 0;
}

StatusOr<Money> tryAddMoney(const Money& a
  , const Money& b
  , bool fail_on_overflow)
{
  using namespace ::basic::error;

  Money sum;

  DCHECK(::basic::validateMoney(a).ok())
    << "The given money must be valid or the result may be wrong.";

  DCHECK(::basic::validateMoney(b).ok())
    << "The given money must be valid or the result may be wrong.";

  if (a.currency_code() != b.currency_code()) {
    sum.clear_currency_code();
    sum.clear_units();
    sum.clear_nanos();
    RETURN_ERROR(INVALID_ARGUMENT)
      << "Money values must have the same currency_code to add";
  }
  sum.set_currency_code(a.currency_code());

  // The unit value carried from adding nanos
  //
  // EXAMPLE
  //
  // $0.5 + $0.6 = $1.1 => carry = 1
  // -$0.5 - $0.6 = -$1.1 => carry = -1
  // $0.5 + $0.1 = $0.6 => carry = 0
  // $0.1 - $0.1 = $0.0 => carry = 0
  // $0.0 + $0.0 = $0.0 => carry = 0
  int carry = 0;

  // Calculate the sum of nanos.
  int sum_nanos = a.nanos() + b.nanos();
  if (sum_nanos >= kBillion) {
    carry = 1;
    sum_nanos -= kBillion;
  } else if (sum_nanos <= -kBillion) {
    carry = -1;
    sum_nanos += kBillion;
  }

  // Calculate the sum of units.
  int64_t sum_units_no_carry = a.units() + b.units();
  int64_t sum_units = sum_units_no_carry + carry;
  // It's possible the sum_units and sum_nanos now have different signs,
  // for example $5.3 - $2.7 (sum_units = 3, sum_nanos = -4) is
  // a.units=-2, a.nanos=-7, b.units=5, b.nanos=3. Adjust if
  // necessary.
  if (sum_units > 0 && sum_nanos < 0) {
    --sum_units;
    sum_nanos += kBillion;
  } else if (sum_units < 0 && sum_nanos > 0) {
    ++sum_units;
    sum_nanos -= kBillion;
  }

  // Get the sign of a and b in order to detect overflow.
  int sign_a = getAmountSign(a);
  int sign_b = getAmountSign(b);

  // Detect positive overflow.
  if (sign_a > 0 && sign_b > 0 && sum_units <= 0) {
    sum.set_units(INT64_MAX);
    sum.set_nanos(kBillion - 1);
    if(LIKELY(fail_on_overflow))
    {
      RETURN_ERROR(OUT_OF_RANGE)
        << "Money addition positive overflow";
    }
    return {sum};
  }

  // Detect negative overflow. Note there is a tricky case that can only happen
  // to negative overflow: sum_units_no_carry overflows to 0 but adding the
  // carry makes sum_units a negative number again. So we must check both
  // sum_units_no_carry and sum_units here. This doesn't happen in the
  // positive overflow case because two MAX values 0x7FF...FF adds to
  // 0xFF...FE and the carry won't affect the sign.
  if (sign_a < 0 && sign_b < 0 && (sum_units_no_carry >= 0 || sum_units >= 0)) {
    sum.set_units(INT64_MIN);
    sum.set_nanos(-kBillion + 1);
    if(LIKELY(fail_on_overflow))
    {
      RETURN_ERROR(OUT_OF_RANGE)
        << "Money addition negative overflow";
    }
    return {sum};
  }

  // The success case.
  sum.set_units(sum_units);
  sum.set_nanos(sum_nanos);

  DCHECK(::basic::validateMoney(sum).ok())
    << "The given money must be valid or the result may be wrong.";

  return {sum};
}

StatusOr<Money> saturatedAddMoney(const Money& a, const Money& b)
{
  using namespace ::basic::error;

  DCHECK(::basic::validateMoney(a).ok())
    << "The given money must be valid or the result may be wrong.";

  DCHECK(::basic::validateMoney(b).ok())
    << "The given money must be valid or the result may be wrong.";

  StatusOr<Money> statusor = tryAddMoney(a, b,
    // Ignore overflow errors.
    false);

  if(statusor.ok())
  {
    DCHECK(::basic::validateMoney(statusor.ConsumeValueOrDie()).ok())
      << "The given money must be valid or the result may be wrong.";
    return {statusor.ValueOrDie()};
  }

  // Do not ignore errors like `INVALID_ARGUMENT`.
  RETURN_APPEND_ERROR(statusor.status())
    << " Saturated money addition failed.";
}

} // namespace basic
