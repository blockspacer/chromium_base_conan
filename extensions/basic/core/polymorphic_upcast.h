#pragma once

#include <base/logging.h>

// Use `polymorphic_upcast` when casting from a base to a derived class.
// Similar to `implicit_cast` it keeps you safe if you confuse both classes.

namespace basic {

namespace internal {

// The use of identity creates a non-deduced form, so that the
// explicit template argument must be supplied
template<class T> struct polymorphic_upcast_identity
{
  typedef T type;
};

} // namespace internal

/// \note `polymorphic_upcast` usually safe (unlike `polymorphic_downcast`),
/// so prefer it for documentation purposes (not because of extra checks)
//
// `polymorphic_upcast` similar to std::implicit_cast (boost::implicit_cast)
// std::implicit_cast would have been part of the C++ standard library,
// but the proposal was submitted too late. It will probably make
// its way into the language in the future.
//
// Upcasting means casting from a derived class to a base class.
//
// EXAMPLE:
//   ...
//   class Fruit { public: virtual ~Fruit(){}; ... };
//   class Banana : public Fruit { ... };
//   ...
//   void f( Banana * banana ) {
//   // ... logic which leads us to believe it is a fruit
//     Fruit * fruit = polymorphic_upcast<Fruit*>(banana);
//     ...
template <typename Base, typename Derived>
inline Base polymorphic_upcast(
  typename internal::polymorphic_upcast_identity<Derived>::type derived)
{
#if DCHECK_IS_ON()
  DCHECK(dynamic_cast<Base>(derived) == derived);
#endif // DCHECK_IS_ON
  return derived; // implicit cast from Derived to Base
}

}  // namespace basic
