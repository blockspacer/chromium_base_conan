// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <tuple>

#include "basic/rvalue_cast.h"

#include "basic/promise/abstract_promise.h"
#include "basic/promise/helpers.h"
#include "basic/promise/no_op_promise_executor.h"

namespace base {
namespace internal {

// For Promises::All(std::vector<Promise<T>& promises)
template <typename ResolveType, typename RejectType>
class AllContainerPromiseExecutor {
 public:
  bool IsCancelled() const { return false; }

  static constexpr PromiseExecutor::PrerequisitePolicy kPrerequisitePolicy =
      PromiseExecutor::PrerequisitePolicy::kAll;

  struct VoidResolveType {};
  struct NonVoidResolveType {};

  using ResolveTypeTag = std::conditional_t<std::is_void<ResolveType>::value,
                                            VoidResolveType,
                                            NonVoidResolveType>;

  void Execute(AbstractPromise* promise) {
    // All is rejected if any prerequisites are rejected.
    AbstractPromise* first_settled = promise->GetFirstSettledPrerequisite();
    if (first_settled && first_settled->IsRejected()) {
      AllPromiseRejectHelper<Rejected<RejectType>>::Reject(promise,
                                                           first_settled);
      return;
    }

    ResolveInternal(promise, ResolveTypeTag());
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

 private:
  // For containers of Promise<void> there is no point resolving with
  // std::vector<Void>.
  void ResolveInternal(AbstractPromise* promise, VoidResolveType) {
    promise->emplace(Resolved<void>());
  }

  void ResolveInternal(AbstractPromise* promise, NonVoidResolveType) {
    using NonVoidResolveType = ToNonVoidT<ResolveType>;
    Resolved<std::vector<NonVoidResolveType>> result;

    const std::vector<DependentList::Node>* prerequisite_list =
        promise->prerequisite_list();
    DCHECK(prerequisite_list);
    result.value.reserve(prerequisite_list->size());

    for (const auto& node : *prerequisite_list) {
      DCHECK(node.prerequisite()->IsResolved());
      result.value.push_back(
          ArgMoveSemanticsHelper<
              NonVoidResolveType,
              Resolved<NonVoidResolveType>>::Get(node.prerequisite()));
    }

    promise->emplace(RVALUE_CAST(result));
  }
};

template <typename Container, typename ContainerT>
struct AllContainerHelper;

template <typename Container, typename ResolveType, typename RejectType>
struct AllContainerHelper<Container, Promise<ResolveType, RejectType>> {
  using PromiseResolve = std::vector<ToNonVoidT<ResolveType>>;

  // As an optimization we don't return std::vector<ResolveType> for void
  // ResolveType.
  using PromiseType = std::conditional_t<std::is_void<ResolveType>::value,
                                         Promise<void, RejectType>,
                                         Promise<PromiseResolve, RejectType>>;

  static PromiseType All(const Location& from_here, const Container& promises) {
    size_t i = 0;
    std::vector<DependentList::Node> prerequisite_list(promises.size());
    // TODO(alexclarke): Move construction of this list and AbstractPromise out
    // of line to reduce template bloat.
    for (auto& promise : promises) {
      prerequisite_list[i++].SetPrerequisite(promise.abstract_promise_.get());
    }

    internal::PromiseExecutor::Data executor_data(
        (in_place_type_t<
            AllContainerPromiseExecutor<ResolveType, RejectType>>()));

    return PromiseType(AbstractPromise::Create(
        nullptr, from_here,
        std::make_unique<AbstractPromise::AdjacencyList>(
            RVALUE_CAST(prerequisite_list)),
        RejectPolicy::kMustCatchRejection, DependentList::ConstructUnresolved(),
        RVALUE_CAST(executor_data)));
  }
};

// TODO(alexclarke): Maybe specalize to support containers of variants.
// E.g. Promises::All(std::vector<Variant<Promise<T>...>>& promises)
//
// https://chromium.googlesource.com/chromium/src/+/589fb96673c255dadfd6e929593050545a68eb14/base/promise/all_promise_executor.h
//
// This template helps assign the reject value from a prerequisite into the
// rejection storage type.
// template <typename RejectT>
// struct AllPromiseRejectAssignHelper {
//   static void Assign(RejectT& dest,
//                      const scoped_refptr<AbstractPromise>& prerequisite) {
//     dest.value = std::move(Get<RejectT>(&prerequisite->value()).value);
//   }
// };
// template <typename... Ts>
// struct AllPromiseRejectAssignHelper<Rejected<Variant<Ts...>>> {
//   static void Assign(Rejected<Variant<Ts...>>& dest,
//                      const scoped_refptr<AbstractPromise>& prerequisite) {
//     VariantAssignHelper<Rejected<Variant<Ts...>>, Rejected<Ts>...>::Assign(
//         dest, prerequisite);
//   }
// };
// template <size_t index>
// struct AllVariantContainerPromiseExecutorHelper {
//   template <typename... Ts>
//   static void Assign(AbstractVariant* abstract_variant,
//                      Variant<Ts...>* variant) {
//     using ResolvedT =
//         base::Resolved<UndoToNonVoidT<TypeAtHelper<index, Ts...>>>;
//     ResolvedT* resolved = GetIf<ResolvedT>(abstract_variant);
//     if (resolved) {
//       *variant = std::move(resolved->value);
//     } else {
//       AllVariantContainerPromiseExecutorHelper<index - 1>::Assign(
//           abstract_variant, variant);
//     }
//   }
// };
// template <>
// struct AllVariantContainerPromiseExecutorHelper<0> {
//   template <typename... Ts>
//   static void Assign(AbstractVariant* abstract_variant,
//                      Variant<Ts...>* variant) {
//     using ResolvedT = base::Resolved<UndoToNonVoidT<TypeAtHelper<0, Ts...>>>;
//     *variant = std::move(Get<ResolvedT>(abstract_variant).value);
//   }
// };
// template <typename T>
// struct VariantSizeHelper;
// template <typename... Ts>
// struct VariantSizeHelper<Variant<Ts...>> {
//   static constexpr int size = sizeof...(Ts);
// };
// template <typename VectorT, typename RejectT>
// class AllVariantContainerPromiseExecutor : public AbstractPromise::Executor {
//  public:
//   AllVariantContainerPromiseExecutor() {}
//   ~AllVariantContainerPromiseExecutor() override {}
//   bool IsCancelled() const override { return false; }
//   void Execute(AbstractPromise* promise) override {
//     for (const auto& prerequisite : promise->prerequisites()) {
//       if (prerequisite->IsRejected()) {
//         RejectT& rejected = promise->value().template emplace<RejectT>();
//         AllPromiseRejectAssignHelper<RejectT>::Assign(rejected, prerequisite);
//         return;
//       }
//     }
//     Resolved<VectorT> result{VectorT(promise->prerequisites().size())};
//     for (size_t i = 0; i < promise->prerequisites().size(); i++) {
//       DCHECK(promise->prerequisites()[i]->IsResolved());
//       constexpr size_t varant_dimension =
//           VariantSizeHelper<typename VectorT::value_type>::size;
//       AllVariantContainerPromiseExecutorHelper<varant_dimension - 1>::Assign(
//           &promise->prerequisites()[i]->value(), &result.value[i]);
//     }
//     bool success = promise->value().TryAssign(std::move(result));
//     DCHECK(success);
//   }
// };
// template <typename Container, typename... Promises>
// struct AllContainerHelper<Container, Variant<Promises...>> {
//   using PromiseResolve = std::vector<
//       typename UnionOfVarArgTypes<typename Promises::ResolveT...>::type>;
//   using PromiseReject = typename internal::SanatizeRejectVariant<
//       typename UnionOfVarArgTypes<typename Promises::RejectT...>::type>::type;
//   using PromiseType = Promise<PromiseResolve, PromiseReject>;
//   static PromiseType All(const Container& promises) {
//     if (promises.empty()) {
//       return ResolvedPromiseHelper<PromiseResolve,
//                                    PromiseReject>::CreateResolved();
//     }
//     std::vector<scoped_refptr<AbstractPromise>> prerequistes;
//     prerequistes.reserve(promises.size());
//     for (typename Container::const_iterator it = promises.begin();
//          it != promises.end(); ++it) {
//       prerequistes.push_back(
//           VariantPromiseHelper<0, Promises...>::GetAbstractPromise(*it));
//     }
//     return PromiseType(subtle::AdoptRefIfNeeded(
//         new AbstractPromise(
//             AbstractPromise::ConstructWith<PromiseResolve, PromiseReject>(),
//             internal::GetCurrentSequence(), FROM_HERE,
//             AbstractPromise::PrerequisitePolicy::ALL, std::move(prerequistes),
//             RejectPolicy::kMustCatchRejection,
//             std::make_unique<AllVariantContainerPromiseExecutor<
//                 PromiseResolve, Rejected<PromiseReject>>>()),
//         AbstractPromise::kRefCountPreference));
//   }
// };

}  // namespace internal
}  // namespace base
