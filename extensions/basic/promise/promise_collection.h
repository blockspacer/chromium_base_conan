#pragma once

#include <set>

#include <base/macros.h>
#include <base/location.h>
#include <base/logging.h>
#include <base/sequence_checker.h>

#include <basic/core/bitmask.h>
#include <basic/promise/promise.h>
#include <basic/promise/promise_value.h>

namespace basic {

#if DCHECK_IS_ON()
enum class PromiseCollectionPermissions
{
  Nothing = 0
  , Addable
      = 1 << 1
  , Removable
      = 1 << 2
  , All
      = PromiseCollectionPermissions::Addable
        | PromiseCollectionPermissions::Removable
};
ALLOW_BITMASK_OPERATORS(PromiseCollectionPermissions)
#endif // DCHECK_IS_ON

template <
  typename ResolveType
  , typename RejectType = ::base::NoReject
  >
class PromiseCollection
{
public:
#if DCHECK_IS_ON()
  using Permissions
    = PromiseCollectionPermissions;
#endif // DCHECK_IS_ON

  using PromiseType
    = ::base::Promise<ResolveType, RejectType>;

  // Define a total order based on the |task_runner| affinity, so that MDPs
  // belonging to the same SequencedTaskRunner are adjacent in the set.
  struct PromiseComparator {
    bool operator()(const PromiseType& a,
                    const PromiseType& b) const
    {
      return a.GetScopedRefptrForTesting()
             < b.GetScopedRefptrForTesting();
    }
  };

  using PromiseContainer
    = std::set<SHARED_LIFETIME(PromiseType), PromiseComparator>;

  bool empty() const
  {
    return promiseContainer_.empty();
  }

  typename PromiseContainer::size_type size() const
  {
    return promiseContainer_.size();
  }

  PromiseCollection()
  {
    DETACH_FROM_SEQUENCE(sequence_checker_);
  }

  ~PromiseCollection()
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  }

  // Can be used to async-wait for resolving of promises
  // that are currently stored in container
  /// \note `All()` will return |base::Promises::All|,
  /// but only for currently collected promises
  /// i.e. after adding new promises to collection
  /// you may want to call `All()` again.
  PromiseType All(const ::base::Location& from_here)
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

    if(!promiseContainer_.empty()) {
      return ::base::Promises::All(FROM_HERE, promiseContainer_);
    }

    // dummy promise
    return PromiseType::CreateResolved(FROM_HERE);
  }

  void add(
    SHARED_LIFETIME(PromiseType) promise)
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

    DCHECK(hasBit(permissions, Permissions::Addable));

    promiseContainer_.emplace(promise);
  }

  void remove(
    SHARED_LIFETIME(PromiseType) boundPromise)
  {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

    DCHECK(hasBit(permissions, Permissions::Removable));

    bool removedOnce = false;

    ::base::EraseIf(
      promiseContainer_,
      [
        SHARED_LIFETIME(boundPromise)
        , &removedOnce
      ](
        const PromiseType& key
        )
      {
        // expect that removal happens only onece
        DCHECK(!removedOnce);

        removedOnce
          = key.GetScopedRefptrForTesting()
              == boundPromise.GetScopedRefptrForTesting();
        return removedOnce;
      });

    // expect that removal done
    DCHECK(removedOnce);
  }

public:
#if DCHECK_IS_ON()
  // usually we want to block modification after `All()` called
  // i.e. when we async-wait for resolving of collected promises
  Permissions permissions
    = Permissions::All
    LIVES_ON(sequence_checker_);
#endif // DCHECK_IS_ON

private:
  SEQUENCE_CHECKER(sequence_checker_);

  PromiseContainer promiseContainer_
    LIVES_ON(sequence_checker_);
};

}  // namespace basic
