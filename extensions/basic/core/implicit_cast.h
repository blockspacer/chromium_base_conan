#pragma once

#include <base/logging.h>

// Prefer implcit_cast to static_cast.
// implicit_cast is less powerful and safer than static_cast.
//
// You can down-cast with static_cast, bit not so with implicit_cast.
// Implicit_cast will only accept implicit conversions:
// no down-cast, no void*->T*, no U->T if T has only explicit constructors for U.
//
// `implicit_cast` is only needed in special circumstances
// in which the type of an expression must be exactly controlled,
// to avoid an overload, for example.
//
namespace basic {

namespace internal {

// The use of identity creates a non-deduced form, so that the
// explicit template argument must be supplied
template<class T> struct implicit_cast_identity
{
  typedef T type;
};

} // namespace internal

// Similar to std::implicit_cast (boost::implicit_cast).
//
// Use implicit_cast as a safe version of static_cast or const_cast
// for implicit conversions. For example:
// - Upcasting in a type hierarchy.
// - Performing arithmetic conversions (int32 to int64, int to double, etc.).
// - Adding const or volatile qualifiers.
//
// In general, implicit_cast can be used to convert this code
//   To to = from;
//   DoSomething(to);
// to this
//   DoSomething(implicit_cast<To>(from));
//
// `implicit_cast_identity` is used to make a non-deduced context, which
// forces all callers to explicitly specify the template argument.
template <typename To>
inline To implicit_cast(typename internal::implicit_cast_identity<To>::type to) {
    return to;
}

// This version of implicit_cast is used when two template arguments
// are specified. It's obsolete and should not be used.
template <typename To, typename From>
inline To implicit_cast(typename internal::implicit_cast_identity<From>::type const& f) {
    return f;
}

}  // namespace basic
