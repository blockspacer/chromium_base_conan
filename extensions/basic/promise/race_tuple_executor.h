#pragma once

#include <tuple>

#include "base/macros.h"

#include "basic/promise/abstract_promise.h"
#include "basic/promise/helpers.h"
#include "basic/type_id.h"

namespace base {
namespace internal {

// For Promises::Race(Promise<Ts>... promises)
template <
  typename ThenResolve, // is is UnionOfVarArgTypes
  typename ThenReject,
  typename... Promises
>
class RacePromiseVariantTypeExecutor {
 public:
  using ResolveT = Resolved<ThenResolve/*typename PromiseType::ResolveT*/>;
  using RejectT = Rejected<ThenReject/*typename PromiseType::RejectT*/>;
  
  bool IsCancelled() const { return false; }

  static constexpr PromiseExecutor::PrerequisitePolicy kPrerequisitePolicy =
      PromiseExecutor::PrerequisitePolicy::kAny;

  void Execute(AbstractPromise* promise) {
    // Race is rejected if any prerequisites are rejected.
    AbstractPromise* first_settled = promise->GetFirstSettledPrerequisite();

    if (first_settled) {
      // Race is rejected if any prerequisites are rejected.
      if (first_settled->IsRejected()) {
        VariantRejectHelper<
            ThenReject,
            AbstractPromise,
            Rejected<typename Promises::RejectT>...>::Assign(promise,
                                                              first_settled);
        return;
      }

      // Race is resolved if any prerequisites are resolved.
      if (first_settled->IsResolved()) {
        VariantResolveHelper<
            ThenResolve,
            AbstractPromise,
            Resolved<typename Promises::ResolveT>...>::Assign(promise,
                                                              first_settled);
        return;
      }
    }

    NOTREACHED();
  }

#if DCHECK_IS_ON()
  PromiseExecutor::ArgumentPassingType ResolveArgumentPassingType() const {
    return UseMoveSemantics<ThenResolve>::argument_passing_type;
  }

  PromiseExecutor::ArgumentPassingType RejectArgumentPassingType() const {
    return UseMoveSemantics<ThenReject>::argument_passing_type;
  }

  bool CanResolve() const { return VariantCanResolveHelper<ThenResolve>::value; }

  bool CanReject() const { return !std::is_same<ThenReject, NoReject>::value; }
#endif
};

// For Promises::Race(Promise<Ts>... promises)
template <typename ResolveType, typename RejectType>
class RaceAllPromiseExecutor {
 public:
  bool IsCancelled() const { return false; }

  static constexpr PromiseExecutor::PrerequisitePolicy kPrerequisitePolicy =
      PromiseExecutor::PrerequisitePolicy::kAny;

  void Execute(AbstractPromise* promise) {
    // Race is rejected if any prerequisites are rejected.
    AbstractPromise* first_settled = promise->GetFirstSettledPrerequisite();

    // Race is resolved if any prerequisites are resolved.
    if (first_settled) {
      // Race is rejected if any prerequisites are rejected.
      if (first_settled->IsRejected()) {
        AllPromiseRejectHelper<Rejected<RejectType>>
          ::Reject(promise, first_settled);
        return;
      }

      // Race is resolved if any prerequisites are resolved.
      if (first_settled->IsResolved()) {
        const std::vector<DependentList::Node>* prerequisite_list =
            promise->prerequisite_list();
        DCHECK(prerequisite_list);
        TupleConstructor<ResolveType>
          ::ConstructOptionallyResolvedTuple(prerequisite_list, promise);
        return;
      }
    }

    NOTREACHED();
  }

#if DCHECK_IS_ON()
  PromiseExecutor::ArgumentPassingType ResolveArgumentPassingType() const {
    return UseMoveSemantics<ResolveType>::argument_passing_type;
  }

  PromiseExecutor::ArgumentPassingType RejectArgumentPassingType() const {
    return UseMoveSemantics<RejectType>::argument_passing_type;
  }

  bool CanResolve() const { return TupleCanResolveHelper<ResolveType>::value; }

  bool CanReject() const { return !std::is_same<RejectType, NoReject>::value; }
#endif
};

}  // namespace internal
}  // namespace base
