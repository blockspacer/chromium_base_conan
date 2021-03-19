#pragma once

#include <base/logging.h>

#include <type_traits>
#include <typeinfo>

namespace basic {

// Does nothing if pointer of type `Base` points
// to something that is not exactly of type 'DerivedPtr'
template <class DerivedPtr, class Base>
DerivedPtr exact_pointer_cast(Base* basePtr)
{
  static_assert(std::is_pointer<DerivedPtr>::value);

  using Derived
    = typename std::remove_cv<
        typename std::remove_pointer<DerivedPtr>::type
      >::type;
  static_assert(std::is_final<Derived>::value);

  if (basePtr != nullptr
      && typeid(*basePtr) == typeid(Derived))
  {
    DCHECK_VALID_PTR(basePtr); // Supports memory tools like ASAN
    return static_cast<DerivedPtr>(basePtr);
  }

  return nullptr;
}

}  // namespace basic
