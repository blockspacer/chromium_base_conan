#pragma once

#include <type_traits>

namespace basic {

/* Required wrapper for if constexpr
 *
 * Is dependent on a template parameter.
 * Is used in static_assert in a false branch to produce a compile error
 * with message containing provided type.
 * See an example with dependent_false at https://en.cppreference.com/w/cpp/language/if
 *
 * if constexpr (std::is_same<T, someType1>::value) {
 * } else if constexpr (std::is_same<T, someType2>::value) {
 * } else {
 *     static_assert(dependent_false<T>::value, "unknown type");
 * }
 */
template<class U>
struct dependent_false : std::false_type {};

// similar to dependent_false
// used to print type names in static_assert
template<typename ... typeclass>
struct typename_false : std::false_type {};

} // namespace basic
