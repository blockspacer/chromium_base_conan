#pragma once

#include <basic/rvalue_cast.h>
#include <base/bind.h>

#include <basic/annotations/guard_annotations.h>

namespace base {

// Check lifetime of pointer, use memory tool like ASAN
//
// USAGE
//
// {
//   // ERROR: AddressSanitizer: stack-use-after-scope
//   ::base::ThreadTaskRunnerHandle::Get()->PostTask(
//     FROM_HERE
//     , ::base::bindCheckedOnce(
//         DEBUG_BIND_CHECKS(
//           PTR_CHECKER(&tmpClass)
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
#define PTR_CHECKER(PTR_NAME) \
  ::base::bindPtrChecker(FROM_HERE, PTR_NAME)

#if DCHECK_IS_ON()
#define DEBUG_PTR_CHECKER(PTR_NAME) \
  PTR_CHECKER(PTR_NAME)
#else
#define DEBUG_PTR_CHECKER(PTR_NAME) \
  DUMMY_CHECKER(PTR_NAME)
#endif

template <typename PtrType>
class PtrChecker
{
 public:
  template <typename U>
  explicit
  PtrChecker(
    const ::base::Location& location
    , U* ptr)
    : ptr_(ptr)
    , location_(location)
  {
    /// \note disallows nullptr
    CHECK(ptr_)
      << location_.ToString();
    checkForLifetimeIssues();
  }

  // called on callback destruction
  ~PtrChecker()
  {
  }

  PtrChecker(PtrChecker<PtrType>&& other)
    : ptr_{RVALUE_CAST(other.ptr_)}
    , location_{RVALUE_CAST(other.location_)}
  {}

  PtrChecker& operator=(
    PtrChecker<PtrType>&& other)
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
  PtrType* ptr_ = nullptr;

  ::base::Location location_;

  DISALLOW_COPY_AND_ASSIGN(PtrChecker);
};

template <typename PtrType>
PtrChecker<PtrType> bindPtrChecker(
  const ::base::Location& location
  , PtrType* ptr)
{
  return PtrChecker<PtrType>{location, ptr};
}

} // namespace base
