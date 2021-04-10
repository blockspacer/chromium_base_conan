#pragma once

#include "basic/promise/abstract_promise.h"
#include "basic/promise/helpers.h"
#include "basic/promise/no_op_promise_executor.h"
#include "basic/rvalue_cast.h"

namespace base {
namespace internal {

template <typename ResolveType, typename RejectType>
class RacePromiseSingleTypeExecutor {
public:
 bool IsCancelled() const { return false; }

 static constexpr PromiseExecutor::PrerequisitePolicy kPrerequisitePolicy =
     PromiseExecutor::PrerequisitePolicy::kAny;

 public:
 void Execute(AbstractPromise* promise) {
   AbstractPromise* first_settled = promise->GetFirstSettledPrerequisite();
   if (first_settled) {
     // Race is rejected if any prerequisites are rejected.
     if (first_settled->IsRejected()) {
       AllPromiseRejectHelper<Rejected<RejectType>>
         ::Reject(promise, first_settled);
       return;
     }

     // Race is resolved if any prerequisites are resolved.
     if (first_settled->IsResolved()) {
       AllPromiseResolveHelper<Resolved<ResolveType>>
         ::Resolve(promise, first_settled);
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

  bool CanResolve() const {
    return !std::is_same<ResolveType, NoResolve>::value;
  }

  bool CanReject() const { return !std::is_same<RejectType, NoReject>::value; }
#endif
};

// Helper for constructing Race promises.
template <typename Container, typename ContainerT>
struct RaceContainerHelper;

template <typename Container, typename ResolveType, typename RejectType>
struct RaceContainerHelper<Container, Promise<ResolveType, RejectType>> {

  // As an optimization we don't return std::vector<ResolveType> for void
  // ResolveType.
  using PromiseType = std::conditional_t<std::is_void<ResolveType>::value,
                                         Promise<void, RejectType>,
                                         Promise<ResolveType, RejectType>>;

  static PromiseType Race(const Location& from_here, const Container& promises) {
    size_t i = 0;
    std::vector<DependentList::Node> prerequisite_list(promises.size());
    // TODO(alexclarke): Move construction of this list and AbstractPromise out
    // of line to reduce template bloat.
    for (auto& promise : promises) {
      prerequisite_list[i++].SetPrerequisite(promise.abstract_promise_.get());
    }

    internal::PromiseExecutor::Data executor_data(
        (in_place_type_t<
            RacePromiseSingleTypeExecutor<ResolveType, RejectType>>()));

    return PromiseType(AbstractPromise::Create(
        nullptr, from_here,
        std::make_unique<AbstractPromise::AdjacencyList>(
            RVALUE_CAST(prerequisite_list)),
        RejectPolicy::kMustCatchRejection, DependentList::ConstructUnresolved(),
        RVALUE_CAST(executor_data)));
  }
};

}  // namespace internal
}  // namespace base
