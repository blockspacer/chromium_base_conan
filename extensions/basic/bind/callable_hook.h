#pragma once

#include "base/macros.h"
#include "base/logging.h"
#include "base/no_destructor.h"
#include "base/threading/thread_collision_warner.h"
#include "basic/rvalue_cast.h"
#include "base/bind.h"
#include "base/callback.h"

#include <basic/core/polymorphic_downcast.h>
#include <basic/strong_types/strong_int.h>
#include <basic/annotations/guard_annotations.h>
#include <basic/logging.h>

#include <map>
#include <string>
#include <memory>

namespace basic {

/// \note Prefer `basic/plug_point` instead.
//
// The `CallableHook` mechanism allows for the creation of
// "weak-symbol-like" functions  which can have
// implementations injected into a link target
// without creating a link dependency.
//
/// \note avoid `CallableHook` mechanism in performance-critical code
//
/// \note Slot modification restricted to single sequence
/// (uses `SEQUENCE_CHECKER`).
//
/// \note User can map string key to function only once
/// i.e. if two string key collide,
/// then we must store only function with bigger priority.
//
// HOW IT WORKS
//
// It maps string key to function i.e. uses `map<string, func>`
//
// USAGE
//
// class MyClass {
//  public:
//   MyClass()
//     : weakInvoker_("badSqr")
//   {}
//
//  double badSqr(double x) {
//    // Use a WeakFunction to allow injected implementations of badSqr.
//    // Notice that the function type of `double(double)` is implicitly determined.
//    return weakInvoker_(x);
//  }
//
//  private:
//  ::basic::CallableHookInvoker<double(double)> weakInvoker_;
// };
//
// class MyClassImpl {
//   public:
//    double badSqrImpl(double x) {
//      return x * x;
//    }
// };
//
// static MyClass myClass{};
// static MyClassImpl myClassImpl{};
//
// ::basic::CallableHookRegistrationData<double(double)> badSqrHook =
//   ::basic::CallableHookRegistrationData(FROM_HERE
//     , "badSqr"
//     , ::base::BindRepeating(
//         &MyClassImpl::badSqrImpl, ::base::Unretained(&myClassImpl))
//     , ::basic::CallableHookPriority{0});
//
// LOG(INFO)
//   << "myClass.badSqr(2)"
//   << myClass.badSqr(2);
//
// LOG(INFO)
//   << "myClass.badSqr(3)"
//   << myClass.badSqr(3);
//
STRONGLY_TYPED_INT(CallableHookPriority);

class GlobalCallableHooksRegistry {
 public:
  // base class for `*Slot`, used to store arbitrary slots in `map`.
  class CallableSlot {
  public:
    virtual ~CallableSlot();
  };

  // stores `Ref` to function with specific signature
  template <typename Func>
  class RepeatingCallbackSlot : public CallableSlot
  {
  public:
    RepeatingCallbackSlot()
      : optFuncRef(base::nullopt)
    {}

    explicit RepeatingCallbackSlot(const ::base::RepeatingCallback<Func>& cb)
      : optFuncRef(REFERENCED(cb))
    {}

    CallableHookPriority priority{0};

    ::base::Optional<
      const ::base::RepeatingCallback<Func>&
    > optFuncRef;

    DISALLOW_COPY_AND_ASSIGN(RepeatingCallbackSlot);
  };

  static GlobalCallableHooksRegistry* GetInstance();

  /**
   * Get the function slot for `key`.
   * Creating a new empty slot if necessary.
   * The slot thus created is permanently associated with function type `Func`.
   * Throws if `key` is not associated with the requested function type `Func`.
   */
  template <typename Func>
  RepeatingCallbackSlot<Func>* getOrCreateSlot(const std::string& key)
  {
    DCHECK_RUN_ON(&sequence_checker_);

    // If a key already exists in the container, does nothing.
    // Otherwise, emplaces `nullptr`.
    auto [iter, isInserted] = slots_.try_emplace(key, nullptr);
    if (isInserted) {
      // replace `nullptr` with `Slot`
      iter->second = std::make_unique<RepeatingCallbackSlot<Func>>();
    }

    CallableSlot* basicSlot = iter->second.get();

    RepeatingCallbackSlot<Func>* slot
      = ::basic::polymorphic_downcast<RepeatingCallbackSlot<Func>*>(basicSlot);

    CHECK(slot)
      << "key "
      << key
      << " mapped to wrong function type";

    return slot;
  }

  /**
   * Make `Func` the implementation of function `key`.
   * Subsequent `getOrCreateSlot<F>(key)` calls
   * will return a slot mapped to a function object that invokes `f` when called.
   *
   * Throws if a previous call with the same `key` and `priority` was made.
   * If keys collide, but at differing priorities,
   * the function that was installed with the
   * greater priority gets the slot.
   */
  template <typename Func>
  bool setSlot(const std::string& key
    , const ::base::RepeatingCallback<Func>& impl
    , CallableHookPriority priority)
  {
    RepeatingCallbackSlot<Func>* RepeatingCallbackSlot = getOrCreateSlot<Func>(key);
    DCHECK_VALID_PTR(RepeatingCallbackSlot);

    if (priority < RepeatingCallbackSlot->priority)
    {
      // already bound function with greater priority
      return false;
    }

    if(RepeatingCallbackSlot->priority == priority
       && RepeatingCallbackSlot->optFuncRef.has_value())
    {
      NOTREACHED()
        << "key collision: " << key;
    }

    RepeatingCallbackSlot->priority = priority;
    RepeatingCallbackSlot->optFuncRef = REFERENCED(impl);

    return true;
  }

 private:
  // private constructor due to `base::NoDestructor`
  GlobalCallableHooksRegistry()
  {
    DETACH_FROM_SEQUENCE(sequence_checker_);
  }

  // private destructor due to `base::NoDestructor`
  ~GlobalCallableHooksRegistry() = delete;

 private:
  std::map<std::string, std::unique_ptr<CallableSlot>> slots_
    GUARDED_BY(&sequence_checker_);

  // check sequence on which class was constructed/destructed/configured
  SEQUENCE_CHECKER(sequence_checker_);

  friend class ::base::NoDestructor<GlobalCallableHooksRegistry>;

  DISALLOW_COPY_AND_ASSIGN(GlobalCallableHooksRegistry);
};

template <typename Func>
class CallableHookRegistrationData
{
 public:
  CallableHookRegistrationData(
    const ::base::Location& location
    , std::string&& key
    , ::base::RepeatingCallback<Func>&& impl
    , CallableHookPriority priority = CallableHookPriority{0})
    : funcStorage_(RVALUE_CAST(impl))
  {
    Init(location
        , RVALUE_CAST(key)
        , REFERENCED(funcStorage_)
        , priority);
  }

  CallableHookRegistrationData(
    const ::base::Location& location
    , std::string&& key
    , const ::base::RepeatingCallback<Func>& impl
    , CallableHookPriority priority = CallableHookPriority{0})
    : funcStorage_(COPIED(impl))
  {
    Init(location
        , RVALUE_CAST(key)
        , REFERENCED(funcStorage_)
        , priority);
  }

 private:
  void Init(const ::base::Location& location
    , std::string&& key
    , const ::base::RepeatingCallback<Func>& impl
    , CallableHookPriority priority = CallableHookPriority{0})
  {
    GlobalCallableHooksRegistry* instance
      = GlobalCallableHooksRegistry::GetInstance();
    DCHECK_VALID_PTR(instance);
    bool result
      = instance->setSlot<Func>(key, REFERENCED(impl), priority);
    DVLOG(99)
      << (result ? "Registered" : "Failed to register")
      << " callable hook with key = "
      << key
      << " from location "
      << location.ToString();
  }

 private:
  ::base::RepeatingCallback<Func> funcStorage_;

  DISALLOW_COPY_AND_ASSIGN(CallableHookRegistrationData);
};

/// \note store CallableHookInvoker as var. to avoid calling `getOrCreateSlot`
/// on each function call (calls in `operator()`)
//
// USAGE
//
// double badSqr(double x) {
//   static auto weak = CallableHookInvoker<double(double)>("badSqr");
//   return weak(x);
// }
template <typename Func>
class CallableHookInvoker
{
 public:
  explicit CallableHookInvoker(std::string&& key)
    : instance_(DCHECK_VALID_PTR_OR(GlobalCallableHooksRegistry::GetInstance()))
    , key_(RVALUE_CAST(key))
    , callSlot_(DCHECK_VALID_PTR_OR(instance_->getOrCreateSlot<Func>(key_)))
  {}

  template <typename... Args>
  decltype(auto) operator()(Args&&... args) const {
    // call function by pointer
    DCHECK(callSlot_->optFuncRef);
    return callSlot_->optFuncRef.Run(FORWARD(args)...);
  }

private:
  GlobalCallableHooksRegistry* instance_;

  std::string key_;

  const GlobalCallableHooksRegistry::RepeatingCallbackSlot<Func>* callSlot_;

  DISALLOW_COPY_AND_ASSIGN(CallableHookInvoker);
};

} // namespace basic

/**
 * Wrapper for the CallableHookRegistrationData constructor call.
 * Declares a registration object that registers the function `impl` as the implementation
 * of any CallableHook objects mapped to the key `func`.
 * See CallableHookRegistrationData documentation for an example.
 */
#define DEFINE_CALLABLE_HOOK_WITH_PRIORITY(func, impl, priority) \
  ::basic::CallableHookRegistrationData(FROM_HERE, #func, impl, priority)

/** Usually we don't specify a priority, so this uses default priority 0. */
#define DEFINE_CALLABLE_HOOK(func, impl) \
  DEFINE_CALLABLE_HOOK_WITH_PRIORITY(func, impl, 0)

// Wrapper for the CallableHook constructor call
// to create a CallableHook that agrees with the
// type signature of the declared function `func`,
// and uses func's name as a key.
//
// USAGE
//
// static auto weak = CALLABLE_HOOK_INVOKER(badSqr);
// auto result = weak(x);
//
#define CALLABLE_HOOK_INVOKER(func) \
  ::basic::CallableHookInvoker<decltype(func)>(#func)
