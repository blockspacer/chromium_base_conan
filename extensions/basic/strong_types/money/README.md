# About

`Money` - Represents an amount of money with its currency type.

The primary advantage of using `Money` is that it forces you to think
about the conversions, rather than blindly applying the calculations
and forgetting about rounding.

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
