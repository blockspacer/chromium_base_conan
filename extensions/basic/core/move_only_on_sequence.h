#pragma once

#include "base/macros.h"
#include "base/logging.h"
#include "base/sequence_checker.h"
#include "basic/rvalue_cast.h"

#include <basic/macros.h>
#include <basic/concept/dependent_false.h>

#include <type_traits>

/// \note Avoid `MoveOnlyOnSequence` if you can.
/// You can use `RVALUE_CAST` to guarantee that value will be moved
/// (remember that `RVALUE_CAST` may copy const value without moving!).
//
/// \note Sometimes `MoveOnlyOnSequence<T>` is better than `optional<T>` because `optional<T>`
/// has not obvious behavior after you move out stored value
/// ( do not use `optional<T>` to represent ownership ).
/// Also `MoveOnlyOnSequence` able to do custom checks (like thread-safety checks)
/// unlike `optional<T>`.
//
// Why `optional<T>` bad if you want to move value out? See code below:
//
// #include <iostream>
// #include <optional>
// #include <string>
//
// class MyObj
// {
//     public:
//
//     MyObj(const std::string& val) : val(val)
//     {
//         std::cout << "constructed" << std::endl;
//     }
//
//     MyObj() {
//         std::cout << "constructor" << this << std::endl;
//     }
//
//     MyObj(const MyObj& a) {
//         std::cout << "copy constructor" << std::endl;
//         val = a.val;
//     }
//
//     MyObj(MyObj&& a) {
//         std::cout << "move constructor" << std::endl;
//         val = RVALUE_CAST(a.val);
//     }
//
//     MyObj& operator=(const MyObj& a) {
//         std::cout << "copy assignment" << std::endl;
//         val = a.val;
//         return *this;
//     }
//
//     MyObj& operator=(MyObj&& a) {
//         std::cout << "move assignment" << std::endl;
//         val = RVALUE_CAST(a.val);
//         return *this;
//     }
//
//     ~MyObj()
//     {
//         std::cout << "destructed" << std::endl;
//     }
//
//     std::string val;
// };
//
//
// /// \note no warnings or errors with clang 11 and
// // -fsanitize=address,undefined -std=c++20 -pedantic -Wall -Wextra -g -O0 -UNDEBUG
// /*
// OUTPUT:
// constructed
// move constructor
// myObj says
// movedOut says HI!
// destructed
// destructed
// */
// int main()
// {
//     std::optional<MyObj> myObj(std::in_place, "HI!");
//
//     MyObj movedOut = RVALUE_CAST(myObj.value());
//
//     /// \note no CRASH!!!
//     std::cout << "myObj says " << myObj.value().val << std::endl;
//
//     /// \note try to add here `myObj.reset();` and compare output
//
//     std::cout << "movedOut says " << movedOut.val << std::endl;
//
//     return 0;
// }
//
// Now compare with:
//
// /// As expected, error upon `myObj.Take().val` with clang 11 and
// // -fsanitize=address,undefined -std=c++20 -pedantic -Wall -Wextra -g -O0 -UNDEBUG
// /*
// OUTPUT:
// constructed
// move constructor
// move constructor
// movedOut says HI!
// destructed
// destructed
// destructed
// */
// int main()
// {
//     MyObj obj("HI!");
//
//     basic::MoveOnlyOnSequence<MyObj> myObj = basic::MoveOnlyOnSequence<MyObj>::moveFrom(RVALUE_CAST(obj));
//
//     basic::MoveOnlyOnSequence<MyObj> movedOut = basic::MoveOnlyOnSequence<MyObj>::moveFrom(myObj.Take());
//
//     // Uncomment to get SEGV: ASAN detects problem and crashes as expected
//     // std::cout << "myObj says " << myObj.Take().val << std::endl;
//
//     std::cout << "movedOut says " << movedOut.Take().val << std::endl;
//
//     return 0;
// }
namespace basic {

// Use it to make sure that you `copy-only-once` (see `MoveOnlyOnSequence::copyFrom`)
// or only `move` (see `MoveOnlyOnSequence::moveFrom` and all operators).
// It is good practice to document `copy-only-once-or-only-move` operation
// via |MoveOnlyOnSequence| for large data types.
/// \note |MoveOnlyOnSequence| made movable but NOT copiable
/// to ensure that large data type will be copied ONLY ONCE!
template <
  class T
  , typename = void
  >
class MoveOnlyOnSequence
{
  static_assert(
    typename_false<T>::value
    , "unable to find MoveOnlyOnSequence implementation");
};

template <
  class T
  >
class MoveOnlyOnSequence<
  T
  , std::enable_if_t<
      !std::is_const<T> {}
      // you may want to use |UnownedPtr|
      // if you want to wrap pointer
      && !std::is_pointer<T>{}
      , void
    >
>
{
private:
  // Made private bacause it makes
  // `move` operation implicit.
  // Use |moveFrom| instead.
  explicit MoveOnlyOnSequence(T&& scoper)
    : is_valid_(true)
    , scoper_(RVALUE_CAST(scoper))
  {
  }

public:
  // We want to explicitly document that `copy` operation will happen
  static MoveOnlyOnSequence copyFrom(COPIED(const T & scoper))
  {
    T tmp = scoper;
    return MoveOnlyOnSequence(RVALUE_CAST(tmp));
  }

  // We want to explicitly document that `move` operation will happen
  static MoveOnlyOnSequence moveFrom(T&& scoper)
  {
    return MoveOnlyOnSequence(RVALUE_CAST(scoper));
  }

  /// \note |MoveOnlyOnSequence| must be movable but NOT copiable
  MoveOnlyOnSequence(MoveOnlyOnSequence&& other)
    : is_valid_(other.is_valid_)
    , scoper_(RVALUE_CAST(other.scoper_))
  {
  }

  MUST_USE_RETURN_VALUE
  T&& Take() const
  {
    // call |Take()| only once and only from one thread
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
    CHECK(is_valid_);
    is_valid_ = false;
    return RVALUE_CAST(scoper_);
  }

  MoveOnlyOnSequence(MoveOnlyOnSequence const&) = delete;

  MoveOnlyOnSequence& operator=(MoveOnlyOnSequence const&) = delete;

private:
  // is_valid_ is distinct from NULL
  mutable bool is_valid_;

  mutable T scoper_;

  SEQUENCE_CHECKER(sequence_checker_);

  DISALLOW_NEW_OPERATOR(MoveOnlyOnSequence);
};

// version of |MoveOnlyOnSequence| for `const T` data types
template <
  class T
  >
class MoveOnlyOnSequence<
  const T
  , std::enable_if_t<
      // you may want to use |UnownedPtr|
      // if you want to wrap pointer
      !std::is_pointer<T> {}
      , void
    >
>
{
private:
  // Made private bacause it makes
  // `move` operation implicit.
  // Use |moveFrom| instead.
  explicit MoveOnlyOnSequence(T&& scoper)
    : is_valid_(true)
    , scoper_(RVALUE_CAST(scoper))
  {
  }

public:
  // We want to explicitly document that `copy` operation will happen
  static MoveOnlyOnSequence copyFrom(COPIED(const T & scoper))
  {
    T tmp = scoper;
    return MoveOnlyOnSequence(RVALUE_CAST(tmp));
  }

  // We want to explicitly document that `move` operation will happen
  static MoveOnlyOnSequence moveFrom(T&& scoper)
  {
    return MoveOnlyOnSequence(RVALUE_CAST(scoper));
  }

  /// \note |MoveOnlyOnSequence| must be movable but NOT copiable
  MoveOnlyOnSequence(MoveOnlyOnSequence&& other)
    : is_valid_(other.is_valid_)
    , scoper_(RVALUE_CAST(other.scoper_))
  {
  }

  MUST_USE_RETURN_VALUE
  const T&& TakeConst() const
  {
    // call |Take()| only once and only from one thread
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
    CHECK(is_valid_);
    is_valid_ = false;
    return RVALUE_CAST(scoper_);
  }

  MoveOnlyOnSequence(MoveOnlyOnSequence const&) = delete;

  MoveOnlyOnSequence& operator=(MoveOnlyOnSequence const&) = delete;

private:
  // is_valid_ is distinct from NULL
  mutable bool is_valid_;

  mutable T scoper_;

  SEQUENCE_CHECKER(sequence_checker_);

  DISALLOW_NEW_OPERATOR(MoveOnlyOnSequence);
};

} // namespace basic
