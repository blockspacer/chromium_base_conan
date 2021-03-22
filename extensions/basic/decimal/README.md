# About

The primary advantage of using `Decimal*` is that it forces you to think
about the conversions, rather than blindly applying the calculations
and forgetting about rounding.

Unlike floating point in a Decimal type we manually restrict how many digits
after the decimal point we can have.
This is called fixed-point number representation.

Human computation and communication of numeric values
almost always uses decimal arithmetic, and decimal notations.
Laboratory notes, scientific papers, legal documents, business reports
and financial statements all record numeric values in decimal form.
When numeric data are given to a program or are displayed to a user,
binary to-and-from decimal conversion is required.
There are inherent rounding errors involved in such conversions;
decimal fractions cannot, in general, be represented exactly
by floating-point values. These errors often cause usability
and efficiency problems, depending on the application.

Decimal arithmetic provides a robust, reliable framework
for financial applications that are often subject to legal requirements
concerning rounding and precision of the results in the areas of banking,
telephone billing, tax calculation, currency conversion, insurance,
or accounting in general.

The binary floating-point arithmetic that computers use
does not always satisfy the existing accuracy requirements.
For example, (7.00 / 10000.0) * 10000.0 calculated in single precision
is 6.9999997504, and not 7.00.
Similar examples can be found for double precision,
or any other binary floating-point format.
The underlying cause is that most decimal fractions, such as 0.1,
cannot be represented exactly in binary floating-point format.

Decimal fractions cannot be represented accurately in binary floating point,
which is a problem for programs that interact with humans,
and is dangerous in programs that manipulate money.
In decimal formats, the mantissa is scaled by powers of 10 instead of 2.

Inspired by:

* http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n1977.html
* http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2009/n2849.pdf
* http://open-std.org/JTC1/SC22/WG21/docs/papers/2014/n3871.html
* https://software.intel.com/content/www/us/en/develop/blogs/intel-decimal-floating-point-math-library.html
* http://speleotrove.com/decimal/decnumber.html
* https://en.wikipedia.org/wiki/Decimal_floating_point
* https://www.crockford.com/dec64.html
* https://github.com/GaryHughes/stddecimal

## Do not have false sense of security with decimal

Decimal* types do not save from rounding errors!

The Decimal type does not eliminate the need for rounding.

Rather, it minimizes errors due to rounding.

Decimal floating points cannot represent the result of all operations exactly.

For example, the result of a division with a prime other than 2 and 5 will,
in general, be rounded.

If you want to avoid rounding errors - use approach similar to `basis/strong_types/money`.

## Problems of Floating Points (binary floating-point)

* Floating Points - FP are not real numbers,
  they are an approximation or a computer representation for real numbers.
* Floating Points can only represent a finite and limited amount of real numbers.
* Not all real numbers can be exactly represented due to
  the quantiazation or discretization error.
* Operations are not commutative
* Loss of precision
* Cancellation aka catastrophic cancellation which is the total loss
  of precision when subtracting two large and very close real numbers.

See https://slate.com/technology/2019/10/round-floor-software-errors-stock-market-battlefield.html

Decimal* has few advantages over the binary floating-point we all have in our CPUs already

## Motivation

`Money` does not use floating point numbers, do not use floats for currency!
The float and double types are particularly ill-suited
for monetary calculations because it is impossible to represent 0.1
(or any other negative power of ten) as a float or double exactly.

See 'You Should Never Use Float and Double for Monetary Calculations'
https://dzone.com/articles/never-use-float-and-double-for-monetary-calculatio

Floating-point numbers in our computers are binary (base 2).
This means there are some base-10 numbers that can't be represented exactly
when converting between the two. Let's look at a few concrete examples.

* 0.1 + 0.2: This equals 0.3, but in floating-point: (0.1 + 0.2) == 0.3 is false.
  This is because 0.1, 0.2 and 0.3 cannot be precisely represented in base 2 floating-point.
  See Bruce Dawson's explanation for details.
  https://randomascii.wordpress.com/2017/06/19/sometimes-floating-point-math-is-perfect/
* 1.40 * 165: produces 230.99999999999997 but should be exactly 231.
  This can cause errors when computing the total price for a purchase order,
  particularly if we truncate the output instead of rounding.
* Round half to nearest even to 2 decimal places (e.g. Python 3):
  round(2.675, 2) produces 2.67 but should produce 2.68, since 2.675
  is halfway between 2.67 and 2.68, and it should round to the even digit.
  This is because 2.675 is actually 2.6749999999999998,
  which is slightly below half. The opposite error happens with round(2.665, 2)
  which produces 2.67 but should produce 2.66.
* 1.25% of $0.40. This is equivalent to 0.0125*0.40 which should produce 0.005000,
  which if using round to even rounds to $0.00. However, in floating-point numbers,
  it is above the halfway point (0.00500000000000000097), so it rounds up.

## decimal32

decimal32 can precisely represent decimal fractions with 7 decimal places (decimal digits of precision)

See `decimal_numeric_limits.hpp`

## decimal64

decimal64 can precisely represent decimal fractions with 16 decimal places (decimal digits of precision),
which makes it very well suited to all applications that are concerned with money.

decimal64 can represent values as gargantuan as 3.6028797018963967E+143
or as measly as 1.0E-127, which makes it well suited to most scientific applications.

decimal64 represents numbers as 64 bit values composed of 2 two’s complement components:
a 56 bit coefficient and an 8 bit exponent.

See `decimal_numeric_limits.hpp`

## decimal128

decimal128 can precisely represent decimal fractions with 34 decimal places (decimal digits of precision)

See `decimal_numeric_limits.hpp`

## BigDecimal

Do not forget to configure BigDecimal.

Defaults may be precision of 10 and a scale of 0,
i.e. 15.37 will be stored as 15!

## Language-independent testcases for General Decimal Arithmetic

See http://speleotrove.com/decimal/dectest.html

# See also

* `base/numerics/double_summation.h`
* `base/numerics/floating_point_comparison.h`
* banker's rounding stackoverflow.com/questions/45223778/is-bankers-rounding-really-more-numerically-stable
