#pragma once

#include <basic/rvalue_cast.h>
#include <base/bind.h>

#include <basic/annotations/guard_annotations.h>

#include <atomic>

namespace base {

// Check that callback will be invoked only once
//
// USAGE
//
// {
//   ::base::MessageLoop::current().task_runner()->PostTask(
//     FROM_HERE
//     , ::base::bindCheckedOnce(
//         DEBUG_BIND_CHECKS(
//           CALLED_EXACTLY_ONCE_CHECKER()
//         )
//         , &TmpClass::TestMe
//         , ::base::Unretained(&tmpClass)
//         , ::base::Passed(FROM_HERE))
//   );
// }
#define CALLED_EXACTLY_ONCE_CHECKER() \
  ::base::bindExactCallCountChecker(FROM_HERE, 1)

#if DCHECK_IS_ON()
#define DEBUG_CALLED_EXACTLY_ONCE_CHECKER(PTR_NAME) \
  CALLED_EXACTLY_ONCE_CHECKER(PTR_NAME)
#else
#define DEBUG_CALLED_EXACTLY_ONCE_CHECKER(PTR_NAME) \
  DUMMY_CHECKER(PTR_NAME)
#endif

// Check that callback will be invoked at least once
//
// USAGE
//
// {
//   ::base::MessageLoop::current().task_runner()->PostTask(
//     FROM_HERE
//     , ::base::bindCheckedOnce(
//         DEBUG_BIND_CHECKS(
//           CALLED_AT_LEAST_ONCE_CHECKER()
//         )
//         , &TmpClass::TestMe
//         , ::base::Unretained(&tmpClass)
//         , ::base::Passed(FROM_HERE))
//   );
// }
#define CALLED_AT_LEAST_ONCE_CHECKER() \
  ::base::bindAtLeastCallCountChecker(FROM_HERE, 1)

#if DCHECK_IS_ON()
#define DEBUG_CALLED_AT_LEAST_ONCE_CHECKER(PTR_NAME) \
  CALLED_AT_LEAST_ONCE_CHECKER(PTR_NAME)
#else
#define DEBUG_CALLED_AT_LEAST_ONCE_CHECKER(PTR_NAME) \
  DUMMY_CHECKER(PTR_NAME)
#endif

// Check that callback will be invoked exactly `PARAM` times
//
// USAGE
//
// {
//   ::base::RepeatingCallback<void(const ::base::Location& location)> repCb
//     = ::base::bindCheckedRepeating(
//         DEBUG_BIND_CHECKS(
//           EXACT_CALL_COUNT_CHECKER(4)
//         )
//         , &TmpClass::TestMe
//         , ::base::Unretained(&tmpClass)
//     );
//
//   repCb.Run(FROM_HERE);
//
//   repCb.Run(FROM_HERE);
//
//   ::base::MessageLoop::current().task_runner()->PostTask(
//     FROM_HERE
//     , ::base::BindOnce(
//         repCb
//         , FROM_HERE
//       )
//   );
//
//   task_runner->PostTask(
//     FROM_HERE
//     , ::base::BindOnce(
//         repCb
//         , FROM_HERE
//       )
//   );
// }
#define EXACT_CALL_COUNT_CHECKER(PARAM) \
  ::base::bindExactCallCountChecker(FROM_HERE, PARAM)

#if DCHECK_IS_ON()
#define DEBUG_EXACT_CALL_COUNT_CHECKER(PTR_NAME) \
  EXACT_CALL_COUNT_CHECKER(PTR_NAME)
#else
#define DEBUG_EXACT_CALL_COUNT_CHECKER(PTR_NAME) \
  DUMMY_CHECKER(PTR_NAME)
#endif

// Check that callback will be invoked at least `PARAM` times
//
// USAGE
//
// {
//   ::base::RepeatingCallback<void(const ::base::Location& location)> repCb
//     = ::base::bindCheckedRepeating(
//         DEBUG_BIND_CHECKS(
//           AT_LEAST_CALL_COUNT_CHECKER(4)
//         )
//         , &TmpClass::TestMe
//         , ::base::Unretained(&tmpClass)
//     );
//
//   repCb.Run(FROM_HERE);
//
//   repCb.Run(FROM_HERE);
//
//   ::base::MessageLoop::current().task_runner()->PostTask(
//     FROM_HERE
//     , ::base::BindOnce(
//         repCb
//         , FROM_HERE
//       )
//   );
//
//   task_runner->PostTask(
//     FROM_HERE
//     , ::base::BindOnce(
//         repCb
//         , FROM_HERE
//       )
//   );
// }
#define AT_LEAST_CALL_COUNT_CHECKER(PARAM) \
  ::base::bindAtLeastCallCountChecker(FROM_HERE, PARAM)

#if DCHECK_IS_ON()
#define DEBUG_AT_LEAST_CALL_COUNT_CHECKER(PTR_NAME) \
  AT_LEAST_CALL_COUNT_CHECKER(PTR_NAME)
#else
#define DEBUG_AT_LEAST_CALL_COUNT_CHECKER(PTR_NAME) \
  DUMMY_CHECKER(PTR_NAME)
#endif

enum class CallCountCheckPolicy {
  Exact,  // ==
  AtLeast // >=
};

template <
  typename CounterType = size_t
  , CallCountCheckPolicy CheckPolicy = CallCountCheckPolicy::Exact
>
class CallCountChecker
{
 public:
  static constexpr CounterType kZeroCallCount = 0;

  CallCountChecker(
    const ::base::Location& location
    , const CounterType& expectedCallCount)
    : expectedCallCount_(expectedCallCount)
    , location_(location)
  {
    DCHECK_GE(expectedCallCount_, kZeroCallCount)
      << location_.ToString()
      << " Expected call count expected to be >= 0";

    callCount_.store(kZeroCallCount);
  }

  /// \note Performs actual check not in `runCheck*()`, but in destructor.
  // check call count on callback destruction
  ~CallCountChecker()
  {
    if(is_moved_out_.load())
    {
      return;
    }

    if constexpr (CheckPolicy == CallCountCheckPolicy::AtLeast)
    {
      CHECK_GE(callCount_.load(), expectedCallCount_)
        << location_.ToString()
        << " Call count expected to be at least: "
        << std::to_string(expectedCallCount_);
    }
    else if constexpr (CheckPolicy == CallCountCheckPolicy::Exact)
    {
      CHECK_EQ(callCount_.load(), expectedCallCount_)
        << location_.ToString()
        << " Call count expected to be exactly: "
        << std::to_string(expectedCallCount_);
    }
    else
    {
      NOTREACHED();
    }
  }

  CallCountChecker(CallCountChecker<CounterType, CheckPolicy>&& other)
    : expectedCallCount_{RVALUE_CAST(other.expectedCallCount_)}
    , location_{RVALUE_CAST(other.location_)}
  {
    other.is_moved_out_.store(true);

    callCount_.store(other.callCount_.load());
  }

  CallCountChecker& operator=(
    CallCountChecker<CounterType, CheckPolicy>&& other)
  {
    callCount_.store(other.callCount_.load());
    expectedCallCount_ = RVALUE_CAST(other.expectedCallCount_);
    location_ = RVALUE_CAST(other.location_);
    other.is_moved_out_.store(true);
    return *this;
  }

  // inc call count on callback invocation
  void runCheckBeforeInvoker()
  {
    DCHECK(!is_moved_out_.load());

    DCHECK_LE(callCount_.load(), std::numeric_limits<CounterType>::max())
      << location_.ToString()
      << " Unable to represent call count in CounterType";

    callCount_.store(callCount_.load() + 1);
  }

  void runCheckAfterInvoker()
  {}

 private:
  std::atomic<CounterType> callCount_;

  CounterType expectedCallCount_;

  ::base::Location location_;

  std::atomic<bool> is_moved_out_{false};

  DISALLOW_COPY_AND_ASSIGN(CallCountChecker);
};

template <typename CounterType>
CallCountChecker<size_t, CallCountCheckPolicy::Exact> bindExactCallCountChecker(
  const ::base::Location& location
  , const CounterType& val)
{
  return CallCountChecker<size_t, CallCountCheckPolicy::Exact>{
    location
    , ::base::checked_cast<size_t>(val)
  };
}

template <typename CounterType>
CallCountChecker<size_t, CallCountCheckPolicy::AtLeast> bindAtLeastCallCountChecker(
  const ::base::Location& location
  , const CounterType& val)
{
  return CallCountChecker<size_t, CallCountCheckPolicy::AtLeast>{
    location
    , ::base::checked_cast<size_t>(val)
  };
}

} // namespace base
