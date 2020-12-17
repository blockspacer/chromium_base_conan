#pragma once

#include "base/macros.h"
#include "base/logging.h"
#include "base/location.h"

#include <cstddef>
#include <limits>

// A helper to assert that a call is not recursive.
/// \note Use `FUNCTION_RECURSION_CHECKER_ONCE` instead.
#define RECURSION_CHECKER_ONCE(CHECKER_NAME) \
  base::RecursionChecker \
    CHECKER_NAME

// A helper to check recursion limit.
/// \note Use `FUNCTION_RECURSION_CHECKER_LIMIT` instead.
#define RECURSION_CHECKER_LIMIT(CHECKER_NAME, count) \
  base::RecursionChecker \
    CHECKER_NAME \
      {count}

#define AUTO_RECURSION_CHECKER_NAME(CHECKER_NAME) \
  assert_not_recursive_##CHECKER_NAME

#if !defined(NDEBUG)
/// \note Use `DCHECK_FUNCTION_RECURSION` instead.
#define DCHECK_RECURSION(CHECKER_NAME) \
  base::AutoRecursionChecker \
    AUTO_RECURSION_CHECKER_NAME(CHECKER_NAME) \
      (CHECKER_NAME, FROM_HERE)
#else // !defined(NDEBUG)
#define DCHECK_RECURSION(CHECKER_NAME) (void)(0)
#endif // !defined(NDEBUG)

// Builds name for recursion checker based on function name
#define FUNCTION_RECURSION_CHECKER_NAME(CHECKER_NAME) \
  recursion_checker_##CHECKER_NAME

// A helper to check recursion limit.
/// \note Can be used to detect infinite or redundant recursion.
#define FUNCTION_RECURSION_CHECKER_LIMIT(CHECKER_NAME, count) \
  RECURSION_CHECKER_LIMIT( \
    FUNCTION_RECURSION_CHECKER_NAME( \
      CHECKER_NAME), count)

/// \note Can be used to detect infinite or redundant recursion.
#define FUNCTION_RECURSION_CHECKER_LIMIT_999(CHECKER_NAME) \
  FUNCTION_RECURSION_CHECKER_LIMIT( \
    CHECKER_NAME, 999)

// A helper to assert that a call is not recursive.
#define FUNCTION_RECURSION_CHECKER_ONCE(CHECKER_NAME) \
  RECURSION_CHECKER_ONCE( \
    FUNCTION_RECURSION_CHECKER_NAME(CHECKER_NAME))

#if !defined(NDEBUG)
// Perform scoped checks for `base::RecursionChecker`
#define DCHECK_FUNCTION_RECURSION(CHECKER_NAME) \
  DCHECK_RECURSION( \
    FUNCTION_RECURSION_CHECKER_NAME(CHECKER_NAME))
#else // !defined(NDEBUG)
#define DCHECK_FUNCTION_RECURSION(CHECKER_NAME) (void)(0)
#endif // !defined(NDEBUG)

namespace base {

/**
 * A helper class to check recursion.
 *
 * USAGE
 *
 * class MyClass {
 *  public:
 *   void foo() const;
 *  private:
 *   // Or `FUNCTION_RECURSION_CHECKER_ONCE`, etc.
 *   mutable FUNCTION_RECURSION_CHECKER_LIMIT_999(dependsOnRecursionLimit);
 * }
 *
 * void MyClass::foo() const
 * {
 *   DCHECK_FUNCTION_RECURSION(dependsOnRecursionLimit);
 *   // You can not call infinetely `MyClass::foo()` from here.
 * }
 */
class RecursionChecker {
public:
  RecursionChecker(size_t recursionLimit = 1)
    : recursionLimit_(recursionLimit)
  {}

  void checkedEnter(
    const base::Location& from_here)
  {
    enteredTotal_++;

    CHECK(enteredTotal_
      < std::numeric_limits<size_t>::max())
      << from_here.ToString()
      << " : "
      << "Unable to represent function recursion in size_t";

    CHECK(enteredTotal_ < recursionLimit_)
      << from_here.ToString()
      << " : "
      << "A resource should be entered < "
      << recursionLimit_
      << " times";
  }

  void checkedExit(
    const base::Location& from_here)
  {
    enteredTotal_--;

    CHECK(enteredTotal_ >= 0)
      << from_here.ToString();
  }

private:
  size_t enteredTotal_ = 0;

  size_t recursionLimit_;

  DISALLOW_COPY_AND_ASSIGN(RecursionChecker);
};

class AutoRecursionChecker {
public:
  explicit AutoRecursionChecker(
    RecursionChecker& checker
    , const base::Location& from_here)
    : checker_(checker)
    , from_here_(from_here)
  {
    checker.checkedEnter(from_here_);
  }

  ~AutoRecursionChecker()
  {
    checker_.checkedExit(from_here_);
  }

private:
  RecursionChecker& checker_;

  const base::Location from_here_;

  DISALLOW_COPY_AND_ASSIGN(AutoRecursionChecker);
};

} // namespace base
