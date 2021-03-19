#pragma once

#include <base/logging.h>

namespace basic {

namespace internal {

inline void WarnEnumCastError(int value_of_int) {
    LOG(DFATAL) << "Bad enum value " << value_of_int;
}

} // namespace internal

// **** Enumeration Casts and Tests
//
// C++ requires that the value of an integer that is converted to an
// enumeration be within the value bounds of the enumeration.  Modern
// compilers can and do take advantage of this requirement to optimize
// programs.  So, using a raw static_cast with enums can be bad.  See
//
// The following templates and macros enable casting from an int to an enum
// with checking against the appropriate bounds.  First, when defining an
// enumeration, identify the limits of the values of its enumerators.
//
//   enum A { A_min = -18, A_max = 33 };
//   MAKE_ENUM_LIMITS(A, A_min, A_max)
//
// Convert an enum to an int in one of two ways.  The prefered way is a
// tight conversion, which ensures that A_min <= value <= A_max.
//
//   A var = tight_enum_cast<A>(3);
//
// However, the C++ language defines the set of possible values for an
// enumeration to be essentially the range of a bitfield that can represent
// all the enumerators, i.e. those within the nearest containing power
// of two.  In the example above, the nearest positive power of two is 64,
// and so the upper bound is 63.  The nearest negative power of two is
// -32 and so the lower bound is -32 (two's complement), which is upgraded
// to match the upper bound, becoming -64.  The values within this range
// of -64 to 63 are valid, according to the C++ standard.  You can cast
// values within this range as follows.
//
//   A var = loose_enum_cast<A>(45);
//
// These casts will log a message if the value does not reside within the
// specified range, and will be fatal when in debug mode.
//
// For those times when an assert too strong, there are test functions.
//
//   bool var = tight_enum_test<A>(3);
//   bool var = loose_enum_test<A>(45);
//
// For code that needs to use the enumeration value if and only if
// it is good, there is a function that both tests and casts.
//
//   int i = ....;
//   A var;
//   if (tight_enum_test_cast<A>(i, &var))
//     .... // use valid var with value as indicated by i
//   else
//     .... // handle invalid enum cast
//
// The enum test/cast facility is currently limited to enumerations that
// fit within an int.  It is also limited to two's complement ints.

// ** Implementation Description
//
// The enum_limits template class captures the minimum and maximum
// enumerator.  All uses of this template are intended to be of
// specializations, so the generic has a field to identify itself as
// not specialized.  The test/cast templates assert specialization.

template <typename Enum>
class enum_limits {
public:
    static const Enum min_enumerator = 0;
    static const Enum max_enumerator = 0;
    static const bool is_specialized = false;
};

// Now we define the macro to define the specialization for enum_limits.
// The specialization checks that the enumerators fit within an int.
// This checking relies on integral promotion.
//
// USAGE
//
// enum TestOp {
//   TEST_INSERT,
//   TEST_UPDATE,
//   TEST_DELETE,
//   TEST_FLUSH_OPS,
//   TEST_FLUSH_TABLET,
//   TEST_NUM_OP_TYPES // max value for enum
// };
//
// MAKE_ENUM_LIMITS(TestOp, TEST_INSERT, TEST_NUM_OP_TYPES);
//
// TestOp r = basic::tight_enum_cast<TestOp>(
//     rand_r(&random_seed) % basic::enum_limits<TestOp>::max_enumerator);
//
#define MAKE_ENUM_LIMITS(ENUM_TYPE, ENUM_MIN, ENUM_MAX)                       \
    template <>                                                               \
    class enum_limits<ENUM_TYPE> {                                            \
    public:                                                                   \
        static const ENUM_TYPE min_enumerator = ENUM_MIN;                     \
        static const ENUM_TYPE max_enumerator = ENUM_MAX;                     \
        static const bool is_specialized = true;                              \
        static_assert(ENUM_MIN >= INT_MIN, "enumerator_too_negative_for_int"); \
        static_assert(ENUM_MAX <= INT_MAX, "enumerator_too_positive_for_int"); \
    };

// The loose enum test/cast is actually the more complicated one,
// because of the problem of finding the bounds.
//
// The unary upper bound, ub, on a positive number is its positive
// saturation, i.e. for a value v within pow(2,k-1) <= v < pow(2,k),
// the upper bound is pow(2,k)-1.
//
// The unary lower bound, lb, on a negative number is its negative
// saturation, i.e. for a value v within -pow(2,k) <= v < -pow(2,k-1),
// the lower bound is -pow(2,k).
//
// The actual bounds are (1) the binary upper bound over the maximum
// enumerator and the one's complement of a negative minimum enumerator
// and (2) the binary lower bound over the minimum enumerator and the
// one's complement of the positive maximum enumerator, except that if no
// enumerators are negative, the lower bound is zero.
//
// The algorithm relies heavily on the observation that
//
//   a,b>0 then ub(a,b) == ub(a) | ub(b) == ub(a|b)
//   a,b<0 then lb(a,b) == lb(a) & lb(b) == lb(a&b)
//
// Note that the compiler will boil most of this code away
// because of value propagation on the constant enumerator bounds.

template <typename Enum>
inline bool loose_enum_test(int e_val) {
    static_assert(enum_limits<Enum>::is_specialized, "missing_MAKE_ENUM_LIMITS");
    const Enum e_min = enum_limits<Enum>::min_enumerator;
    const Enum e_max = enum_limits<Enum>::max_enumerator;
    static_assert(sizeof(e_val) == 4 || sizeof(e_val) == 8, "unexpected_int_size");

    // Find the unary bounding negative number of e_min and e_max.

    // Find the unary bounding negative number of e_max.
    // This would be b_min = e_max < 0 ? e_max : ~e_max,
    // but we want to avoid branches to help the compiler.
    int e_max_sign = e_max >> (sizeof(e_val) * 8 - 1);
    int b_min = ~e_max_sign ^ e_max;

    // Find the binary bounding negative of both e_min and e_max.
    b_min &= e_min;

    // However, if e_min is positive, the result will be positive.
    // Now clear all bits right of the most significant clear bit,
    // which is a negative saturation for negative numbers.
    // In the case of positive numbers, this is flush to zero.
    b_min &= b_min >> 1;
    b_min &= b_min >> 2;
    b_min &= b_min >> 4;
    b_min &= b_min >> 8;
    b_min &= b_min >> 16;
#if INT_MAX > 2147483647
    b_min &= b_min >> 32;
#endif

    // Find the unary bounding positive number of e_max.
    int b_max = e_max_sign ^ e_max;

    // Find the binary bounding positive number of that
    // and the unary bounding positive number of e_min.
    int e_min_sign = e_min >> (sizeof(e_val) * 8 - 1);
    b_max |= e_min_sign ^ e_min;

    // Now set all bits right of the most significant set bit,
    // which is a positive saturation for positive numbers.
    b_max |= b_max >> 1;
    b_max |= b_max >> 2;
    b_max |= b_max >> 4;
    b_max |= b_max >> 8;
    b_max |= b_max >> 16;
#if INT_MAX > 2147483647
    b_max |= b_max >> 32;
#endif

    // Finally test the bounds.
    return b_min <= e_val && e_val <= b_max;
}

template <typename Enum>
inline bool tight_enum_test(int e_val) {
    static_assert(enum_limits<Enum>::is_specialized, "missing_MAKE_ENUM_LIMITS");
    const Enum e_min = enum_limits<Enum>::min_enumerator;
    const Enum e_max = enum_limits<Enum>::max_enumerator;
    return e_min <= e_val && e_val <= e_max;
}

template <typename Enum>
inline bool loose_enum_test_cast(int e_val, Enum* e_var) {
    if (loose_enum_test<Enum>(e_val)) {
        *e_var = static_cast<Enum>(e_val);
        return true;
    } else {
        return false;
    }
}

template <typename Enum>
inline bool tight_enum_test_cast(int e_val, Enum* e_var) {
    if (tight_enum_test<Enum>(e_val)) {
        *e_var = static_cast<Enum>(e_val);
        return true;
    } else {
        return false;
    }
}

template <typename Enum>
inline Enum loose_enum_cast(int e_val) {
    if (!loose_enum_test<Enum>(e_val)) {
        basic::internal::WarnEnumCastError(e_val);
    }
    return static_cast<Enum>(e_val);
}

template <typename Enum>
inline Enum tight_enum_cast(int e_val) {
    if (!tight_enum_test<Enum>(e_val)) {
        basic::internal::WarnEnumCastError(e_val);
    }
    return static_cast<Enum>(e_val);
}

}  // namespace basic
