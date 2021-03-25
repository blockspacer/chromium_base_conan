#pragma once

#include <basic/rvalue_cast.h>
#include <base/bind.h>

#include <basic/annotations/guard_annotations.h>

// -----------------------------------------------------------------------------
// Usage documentation
// -----------------------------------------------------------------------------
//
// Overview:
// `bindChecked*` runs custom checks before and after callback execution.
// ::base::bindCheckedOnce() and ::base::bindCheckedRepeating() are helpers for creating
// ::base::OnceCallback and ::base::RepeatingCallback objects respectively and performing
// checks upon callback usage.
//
// MOTIVATION
//
// Some callbacks must be annotated by custom guarantees (checks)
// for documentation purposes.
//
// Example motivation:
// If callback must be used within lifetime of some object
// (think about lifetime of `this` object in `base::Unretained(this)`), then
// use `REF_CHECKER` or `PTR_CHECKER` and run tests under ASAN.
//
// Example motivation:
// `PostTask` may fail (for example, if system ran out of memory),
// but some callbacks guaranteed to be executed at least once
// (see `CALLED_AT_LEAST_ONCE_CHECKER()`)
// or exactly once (see `CALLED_EXACTLY_ONCE_CHECKER()`).
//
// Example motivation:
// Performance-critical code can use `EXEC_TIME_LIMIT_CHECKER`, so you will
// be able to guarantee that callback will be executed within some time.
//
// EXAMPLE
//
// #include <basic/bind/bind_checked.h>
// #include <basic/bind/bind_dummy_checker.h>
// #include <basic/bind/bind_ptr_checker.h>
// #include <basic/bind/bind_ref_checker.h>
// #include <basic/bind/bind_call_count_checker.h>
// #include <basic/bind/bind_delay_time_checker.h>
// #include <basic/bind/bind_exec_time_checker.h>
//
// class TmpClass
// {
//  public:
//   TmpClass(){}
//
//   void TestMe(const ::base::Location& location)
//   {
//     LOG_CALL(DVLOG(99))
//       << " a "
//       << a
//       << " b "
//       << b
//       << " location.ToString() "
//       << location.ToString();
//
//     ::base::PlatformThread::Sleep(base::TimeDelta::FromSeconds(1));
//   }
//
//   int a = 6;
//   std::string b = "hi!";
// };
//
// ::base::OnceCallback<int(const std::string&, int)> test1
//   = ::base::bindCheckedOnce(
//       DEBUG_BIND_CHECKS(
//         REF_CHECKER(runLoop)
//         , PTR_CHECKER(&runLoop)
//         , CALLED_AT_LEAST_ONCE_CHECKER()
//       )
//       , [
//       ](
//         const std::string&, int
//       ){
//         return 4;
//       }
//     );
// DCHECK(RVALUE_CAST(test1).Run("hi", 2) == 4);
//
// DCHECK(::base::ThreadPoolInstance::Get());
// scoped_refptr<::base::SequencedTaskRunner> task_runner =
//   ::base::ThreadPool::CreateSequencedTaskRunner(
//     ::base::TaskTraits{
//       ::base::TaskPriority::BEST_EFFORT
//       , ::base::MayBlock()
//       , ::base::TaskShutdownBehavior::BLOCK_SHUTDOWN
//     }
//   );
//
// TmpClass tmpClass;
// {
//   ::base::ThreadTaskRunnerHandle::Get()->PostTask(
//     FROM_HERE
//     , ::base::bindCheckedOnce(
//         DEBUG_BIND_CHECKS(
//           REF_CHECKER(tmpClass)
//           , PTR_CHECKER(&tmpClass)
//           , EXACT_CALL_COUNT_CHECKER(1)
//         )
//         , &TmpClass::TestMe
//         , ::base::Unretained(&tmpClass)
//         , ::base::Passed(FROM_HERE))
//   );
//
//   task_runner->PostTask(
//     FROM_HERE
//     , ::base::bindCheckedOnce(
//         DEBUG_BIND_CHECKS(
//           REF_CHECKER(tmpClass)
//           , PTR_CHECKER(&tmpClass)
//           , EXACT_CALL_COUNT_CHECKER(1)
//         )
//         , &TmpClass::TestMe
//         , ::base::Unretained(&tmpClass)
//         , ::base::Passed(FROM_HERE))
//   );
//
//   ::base::RepeatingCallback<void(const ::base::Location& location)> repCb
//     = ::base::bindCheckedRepeating(
//         DEBUG_BIND_CHECKS(
//           REF_CHECKER(tmpClass)
//           , PTR_CHECKER(&tmpClass)
//           , AT_LEAST_CALL_COUNT_CHECKER(4)
//           , EXEC_TIME_LIMIT_CHECKER(base::TimeDelta::FromSeconds(14))
//           , DELAY_TIME_LIMIT_CHECKER(base::TimeDelta::FromSeconds(15))
//         )
//         , &TmpClass::TestMe
//         , ::base::Unretained(&tmpClass)
//     );
//
//   repCb.Run(FROM_HERE);
//
//   ::base::PlatformThread::Sleep(base::TimeDelta::FromSeconds(1));
//
//   repCb.Run(FROM_HERE);
//
//   ::base::ThreadTaskRunnerHandle::Get()->PostTask(
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

namespace base {

// BindChecks<>
//
// This stores all the state passed into bindChecked().
/// \note each type in `typename... BoundArgs` must have
/// `runCheckBeforeInvoker()` and `runCheckAfterInvoker()` methods.
template <typename... BoundArgs>
struct BindChecks final
{
  template <typename... ForwardBoundArgs>
  explicit BindChecks(ForwardBoundArgs&&... bound_args)
    : bound_checks_(FORWARD(bound_args)...)
  {}

  template <typename... ForwardBoundArgs>
  BindChecks(BindChecks<ForwardBoundArgs...>&& other)
    : bound_checks_{RVALUE_CAST(other.bound_checks_)}
  {}

  template <typename... ForwardBoundArgs>
  BindChecks& operator=(
    BindChecks<ForwardBoundArgs...>&& other)
  {
    bound_checks_ = RVALUE_CAST(other.bound_checks_);
    return *this;
  }

  template <typename... ForwardBoundArgs>
  BindChecks(const BindChecks<ForwardBoundArgs...>& other) = delete;

  template <typename... ForwardBoundArgs>
  BindChecks& operator=(
    const BindChecks<ForwardBoundArgs...>& other) = delete;

  ~BindChecks() = default;

  std::tuple<BoundArgs...> bound_checks_;

 private:
  DISALLOW_COPY_AND_ASSIGN(BindChecks);
};

/// \note prefer `DEBUG_BIND_CHECKS` for performance reasons
#define BIND_CHECKS(...) \
  ::base::buildBindChecks(__VA_ARGS__)

#if DCHECK_IS_ON()
#define DEBUG_BIND_CHECKS(...) \
  BIND_CHECKS(__VA_ARGS__)
#else
#define DEBUG_BIND_CHECKS(...) \
  BIND_CHECKS()
#endif

template <typename... ForwardBoundArgs>
BindChecks<ForwardBoundArgs...> buildBindChecks(
  ForwardBoundArgs&&... bound_args)
{
  return BindChecks<ForwardBoundArgs...>{
    FORWARD(bound_args)...
  };
}

namespace internal {

// CheckedBindState<>
//
// This stores all the state passed into Bind().
template <typename CheckerType, typename Functor, typename... BoundArgs>
struct CheckedBindState final : BindStateBase {
  using IsCancellable = std::integral_constant<
      bool,
      CallbackCancellationTraits<Functor,
                                 std::tuple<BoundArgs...>>::is_cancellable>;

  template <
    typename Checker
    , typename ForwardFunctor
    , typename... ForwardBoundArgs
  >
  static CheckedBindState* Create(BindStateBase::InvokeFuncStorage invoke_func,
                           Checker&& checker,
                           ForwardFunctor&& functor,
                           ForwardBoundArgs&&... bound_args) {
    // Ban ref counted receivers that were not yet fully constructed to avoid
    // a common pattern of racy situation.
    BanUnconstructedRefCountedReceiver<ForwardFunctor>(bound_args...);

    // IsCancellable is std::false_type if
    // CallbackCancellationTraits<>::IsCancelled returns always false.
    // Otherwise, it's std::true_type.
    return new CheckedBindState(IsCancellable{}, invoke_func,
                         RVALUE_CAST(checker),
                         FORWARD(functor),
                         FORWARD(bound_args)...);
  }

  CheckerType checker_;
  Functor functor_;
  std::tuple<BoundArgs...> bound_args_;

 private:
  template <
    typename Checker
    , typename ForwardFunctor
    , typename... ForwardBoundArgs
  >
  explicit CheckedBindState(std::true_type,
                     BindStateBase::InvokeFuncStorage invoke_func,
                     Checker&& checker,
                     ForwardFunctor&& functor,
                     ForwardBoundArgs&&... bound_args)
      : BindStateBase(invoke_func,
                      &Destroy,
                      &QueryCancellationTraits<CheckedBindState>),
        checker_{RVALUE_CAST(checker)},
        functor_(FORWARD(functor)),
        bound_args_(FORWARD(bound_args)...)
  {
    DCHECK(!IsNull(functor_));
  }

  template <
    typename Checker
    , typename ForwardFunctor
    , typename... ForwardBoundArgs
  >
  explicit CheckedBindState(std::false_type,
                     BindStateBase::InvokeFuncStorage invoke_func,
                     Checker&& checker,
                     ForwardFunctor&& functor,
                     ForwardBoundArgs&&... bound_args)
      : BindStateBase(invoke_func, &Destroy),
        checker_{RVALUE_CAST(checker)},
        functor_(FORWARD(functor)),
        bound_args_(FORWARD(bound_args)...)
  {
    DCHECK(!IsNull(functor_));
  }

  ~CheckedBindState()
  {
  }

  static void Destroy(const BindStateBase* self)
  {
    delete static_cast<const CheckedBindState*>(self);
  }
};

// Used to implement MakeCheckedBindStateType.
template <
  typename CheckerType,
  bool is_method,
  typename Functor,
  typename... BoundArgs
>
struct MakeCheckedBindStateTypeImpl;

template <
  typename CheckerType,
  typename Functor,
  typename... BoundArgs
>
struct MakeCheckedBindStateTypeImpl<CheckerType, false, Functor, BoundArgs...> {
  static_assert(!HasRefCountedTypeAsRawPtr<std::decay_t<BoundArgs>...>::value,
                "A parameter is a refcounted type and needs scoped_refptr.");
  using Type = CheckedBindState<CheckerType, std::decay_t<Functor>, std::decay_t<BoundArgs>...>;
};

template <
  typename CheckerType,
  typename Functor
>
struct MakeCheckedBindStateTypeImpl<CheckerType, true, Functor> {
  using Type = CheckedBindState<CheckerType, std::decay_t<Functor>>;
};

template <
  typename CheckerType,
  typename Functor,
  typename Receiver,
  typename... BoundArgs
>
struct MakeCheckedBindStateTypeImpl<CheckerType, true, Functor, Receiver, BoundArgs...> {
 private:
  using DecayedReceiver = std::decay_t<Receiver>;

  static_assert(!std::is_array<std::remove_reference_t<Receiver>>::value,
                "First bound argument to a method cannot be an array.");
  static_assert(
      !std::is_pointer<DecayedReceiver>::value ||
          IsRefCountedType<std::remove_pointer_t<DecayedReceiver>>::value,
      "Receivers may not be raw pointers. If using a raw pointer here is safe"
      " and has no lifetime concerns, use ::base::Unretained() and document why"
      " it's safe.");
  static_assert(!HasRefCountedTypeAsRawPtr<std::decay_t<BoundArgs>...>::value,
                "A parameter is a refcounted type and needs scoped_refptr.");

 public:
  using Type = CheckedBindState<
      CheckerType,
      std::decay_t<Functor>,
      std::conditional_t<std::is_pointer<DecayedReceiver>::value,
                         scoped_refptr<std::remove_pointer_t<DecayedReceiver>>,
                         DecayedReceiver>,
      std::decay_t<BoundArgs>...>;
};

template <typename CheckerType, typename Functor, typename... BoundArgs>
using MakeCheckedBindStateType =
    typename MakeCheckedBindStateTypeImpl<
                                   CheckerType,
                                   MakeFunctorTraits<Functor>::is_method,
                                   Functor,
                                   BoundArgs...>::Type;

// InvokerWithChecks<>
//
// See description at the top of the file.
template <typename StorageType, typename UnboundRunType>
struct InvokerWithChecks;

template <typename StorageType, typename R, typename... UnboundArgs>
struct InvokerWithChecks<StorageType, R(UnboundArgs...)>
{
  using UnboundRunType = R(UnboundArgs...);
  using WrappedInvoker = internal::Invoker<StorageType, UnboundRunType>;

  static R RunOnce(BindStateBase* base,
                   PassingType<UnboundArgs>... unbound_args)
  {
    StorageType* storage = static_cast<StorageType*>(base);

    static constexpr size_t num_bound_checks =
        std::tuple_size<decltype(storage->checker_.bound_checks_)>::value;

    runBindCheckersBeforeInvoker(
      storage->checker_.bound_checks_
      , std::make_index_sequence<num_bound_checks>());

    if constexpr (std::is_void_v<R>)
    {
      WrappedInvoker::RunOnce(
            base
            , FORWARD(unbound_args)...);

      runBindCheckersAfterInvoker(
        storage->checker_.bound_checks_
        , std::make_index_sequence<num_bound_checks>());
    }
    else
    {
      R result
        = WrappedInvoker::RunOnce(
            base
            , FORWARD(unbound_args)...);

      runBindCheckersAfterInvoker(
        storage->checker_.bound_checks_
        , std::make_index_sequence<num_bound_checks>());

      return result;
    }
  }

  static R Run(BindStateBase* base, PassingType<UnboundArgs>... unbound_args) {

    StorageType* storage = static_cast<StorageType*>(base);

    static constexpr size_t num_bound_checks =
        std::tuple_size<decltype(storage->checker_.bound_checks_)>::value;

    runBindCheckersBeforeInvoker(
      storage->checker_.bound_checks_
      , std::make_index_sequence<num_bound_checks>());

    if constexpr (std::is_void_v<R>)
    {
      WrappedInvoker::RunOnce(
            base
            , FORWARD(unbound_args)...);

      runBindCheckersAfterInvoker(
        storage->checker_.bound_checks_
        , std::make_index_sequence<num_bound_checks>());
    }
    else
    {
      R result
        = WrappedInvoker::RunOnce(
            base
            , FORWARD(unbound_args)...);

      runBindCheckersAfterInvoker(
        storage->checker_.bound_checks_
        , std::make_index_sequence<num_bound_checks>());

      return result;
    }
  }

 private:
  template<typename... Args>
  static inline void runBindCheckerBeforeInvoker(Args&&... passedArgs)
  {
    /// \note fold expression requires C++17
    ((void)(passedArgs.runCheckBeforeInvoker()), ...);
  }

  template <typename BoundChecksTuple, size_t... indices>
  static inline void runBindCheckersBeforeInvoker(
    BoundChecksTuple&& bound
    , std::index_sequence<indices...>)
  {
    using DecayedArgsTuple = std::decay_t<BoundChecksTuple>;

    runBindCheckerBeforeInvoker(std::get<indices>(FORWARD(bound))...);
  }

  template<typename... Args>
  static inline void runBindCheckerAfterInvoker(Args&&... passedArgs)
  {
    /// \note fold expression requires C++17
    ((void)(passedArgs.runCheckAfterInvoker()), ...);
  }

  template <typename BoundChecksTuple, size_t... indices>
  static inline void runBindCheckersAfterInvoker(
    BoundChecksTuple&& bound
    , std::index_sequence<indices...>)
  {
    using DecayedArgsTuple = std::decay_t<BoundChecksTuple>;

    runBindCheckerAfterInvoker(std::get<indices>(FORWARD(bound))...);
  }
};

} // namespace internal

// Bind as OnceCallback.
template <typename CheckerType, typename Functor, typename... Args>
inline OnceCallback<MakeUnboundRunType<Functor, Args...>>
bindCheckedOnce(CheckerType&& checker
  , Functor&& functor
  , Args&&... args)
{
  static_assert(!internal::IsOnceCallback<std::decay_t<Functor>>() ||
                    (std::is_rvalue_reference<Functor&&>() &&
                     !std::is_const<std::remove_reference_t<Functor>>()),
                "bindCheckedOnce requires non-const rvalue for OnceCallback binding."
                " I.e.: bindCheckedOnce(std::move(callback)).");

  // This block checks if each |args| matches to the corresponding params of the
  // target function. This check does not affect the behavior of Bind, but its
  // error message should be more readable.
  using Helper = internal::BindTypeHelper<Functor, Args...>;
  using FunctorTraits = typename Helper::FunctorTraits;
  using BoundArgsList = typename Helper::BoundArgsList;
  using UnwrappedArgsList =
      internal::MakeUnwrappedTypeList<true, FunctorTraits::is_method,
                                      Args&&...>;
  using BoundParamsList = typename Helper::BoundParamsList;
  static_assert(internal::AssertBindArgsValidity<
                    std::make_index_sequence<Helper::num_bounds>, BoundArgsList,
                    UnwrappedArgsList, BoundParamsList>::ok,
                "The bound args need to be convertible to the target params.");

  using CheckedBindState = internal::MakeCheckedBindStateType<
      CheckerType, Functor, Args...
    >;
  using UnboundRunType = MakeUnboundRunType<Functor, Args...>;
  using CheckedInvoker = internal::InvokerWithChecks<CheckedBindState, UnboundRunType>;
  using CallbackType = OnceCallback<UnboundRunType>;

  // Store the invoke func into PolymorphicInvoke before casting it to
  // InvokeFuncStorage, so that we can ensure its type matches to
  // PolymorphicInvoke, to which CallbackType will cast back.
  using PolymorphicInvoke = typename CallbackType::PolymorphicInvoke;
  PolymorphicInvoke invoke_func = &CheckedInvoker::RunOnce;

  using InvokeFuncStorage = internal::BindStateBase::InvokeFuncStorage;
  CallbackType result = CallbackType(CheckedBindState::Create(
      reinterpret_cast<InvokeFuncStorage>(invoke_func),
      RVALUE_CAST(checker),
      FORWARD(functor), FORWARD(args)...));

  return result;
}

// Special cases for binding to a ::base::Callback without extra bound arguments.
template <typename Signature>
OnceCallback<Signature> bindCheckedOnce(OnceCallback<Signature> closure) {
  return closure;
}

// Bind as RepeatingCallback.
template <typename CheckerType, typename Functor, typename... Args>
inline RepeatingCallback<MakeUnboundRunType<Functor, Args...>>
bindCheckedRepeating(CheckerType&& checker, Functor&& functor, Args&&... args) {
  static_assert(
      !internal::IsOnceCallback<std::decay_t<Functor>>(),
      "bindCheckedRepeating cannot bind OnceCallback. Use BindOnce with std::move().");

  // This block checks if each |args| matches to the corresponding params of the
  // target function. This check does not affect the behavior of Bind, but its
  // error message should be more readable.
  using Helper = internal::BindTypeHelper<Functor, Args...>;
  using FunctorTraits = typename Helper::FunctorTraits;
  using BoundArgsList = typename Helper::BoundArgsList;
  using UnwrappedArgsList =
      internal::MakeUnwrappedTypeList<false, FunctorTraits::is_method,
                                      Args&&...>;
  using BoundParamsList = typename Helper::BoundParamsList;
  static_assert(internal::AssertBindArgsValidity<
                    std::make_index_sequence<Helper::num_bounds>, BoundArgsList,
                    UnwrappedArgsList, BoundParamsList>::ok,
                "The bound args need to be convertible to the target params.");

  using CheckedBindState = internal::MakeCheckedBindStateType<
      CheckerType, Functor, Args...
    >;
  using UnboundRunType = MakeUnboundRunType<Functor, Args...>;
  using CheckedInvoker = internal::InvokerWithChecks<CheckedBindState, UnboundRunType>;
  using CallbackType = RepeatingCallback<UnboundRunType>;

  // Store the invoke func into PolymorphicInvoke before casting it to
  // InvokeFuncStorage, so that we can ensure its type matches to
  // PolymorphicInvoke, to which CallbackType will cast back.
  using PolymorphicInvoke = typename CallbackType::PolymorphicInvoke;
  PolymorphicInvoke invoke_func = &CheckedInvoker::Run;

  using InvokeFuncStorage = internal::BindStateBase::InvokeFuncStorage;
  return CallbackType(CheckedBindState::Create(
      reinterpret_cast<InvokeFuncStorage>(invoke_func),
      RVALUE_CAST(checker),
      FORWARD(functor), FORWARD(args)...));
}

template <typename Signature>
RepeatingCallback<Signature> bindCheckedRepeating(
    RepeatingCallback<Signature> closure) {
  return closure;
}

} // namespace base
