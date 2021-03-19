#pragma once

#include <basic/rvalue_cast.h>
#include <base/bind.h>

#include <basic/annotations/guard_annotations.h>

namespace base {

// Check lifetime of reference, use memory tool like ASAN
//
// USAGE
//
// {
//   // ERROR: AddressSanitizer: stack-use-after-scope
//   ::base::MessageLoop::current().task_runner()->PostTask(
//     FROM_HERE
//     , ::base::bindCheckedOnce(
//         DEBUG_BIND_CHECKS(
//           REF_CHECKER(tmpClass)
//         )
//         , &TmpClass::TestMe
//         , ::base::Unretained(&tmpClass)
//         , ::base::Passed(FROM_HERE))
//   );
//
//   DVLOG(9)
//     << "TmpClass freed before `runLoop.Run()`"
//     << " i.e. before `PostTask` execution"
//     << " Build with `-fsanitize=address,undefined`"
//     << " to detect `AddressSanitizer: stack-use-after-scope`";
// }
#define CONST_REF_CHECKER(REF_NAME) \
  ::base::bindRefChecker(FROM_HERE, CONST_REFERENCED(REF_NAME))

#if DCHECK_IS_ON()
#define DEBUG_CONST_REF_CHECKER(PTR_NAME) \
  CONST_REF_CHECKER(PTR_NAME)
#else
#define DEBUG_CONST_REF_CHECKER(PTR_NAME) \
  DUMMY_CHECKER(PTR_NAME)
#endif

template <typename RefType>
class RefChecker
{
 public:
  template <typename U>
  explicit
  RefChecker(
    const ::base::Location& location
    , U& ref)
    : ptr_(&ref)
    , location_(location)
  {
    /// \note disallows nullptr
    CHECK(ptr_)
      << location_.ToString();
    checkForLifetimeIssues();
  }

  // called on callback destruction
  ~RefChecker()
  {
  }

  RefChecker(RefChecker<RefType>&& other)
    : ptr_{RVALUE_CAST(other.ptr_)}
    , location_{RVALUE_CAST(other.location_)}
  {}

  RefChecker& operator=(
    RefChecker<RefType>&& other)
  {
    ptr_ = RVALUE_CAST(other.ptr_);
    location_ = RVALUE_CAST(other.location_);
    return *this;
  }

  void runCheckBeforeInvoker()
  {
    /// \note disallows nullptr
    CHECK(ptr_)
      << location_.ToString();
    checkForLifetimeIssues();
  }

  void runCheckAfterInvoker()
  {}

 private:
  // check that object is alive, use memory tool like ASAN
  /// \note ignores nullptr
  inline void checkForLifetimeIssues() const
  {
    // Works with `-fsanitize=address,undefined`
#if defined(MEMORY_TOOL_REPLACES_ALLOCATOR)
    if (ptr_ != nullptr)
      reinterpret_cast<const volatile uint8_t*>(ptr_)[0];
#endif
  }

 private:
  RefType* ptr_ = nullptr;

  ::base::Location location_;

  DISALLOW_COPY_AND_ASSIGN(RefChecker);
};

template <typename RefType>
RefChecker<RefType> bindRefChecker(
  const ::base::Location& location
  , std::reference_wrapper<RefType> ref)
{
  return RefChecker<RefType>{location, ref.get()};
}

} // namespace base
