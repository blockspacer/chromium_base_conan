#pragma once

#include "basic/bind/verify_nothing.h"
#include <basic/core/bitmask.h>

#include <base/macros.h>
#include <base/sequence_checker.h>
#include <base/callback.h>
#include <base/location.h>
#include <basic/rvalue_cast.h>
#include <base/threading/thread_collision_warner.h>
#include <base/sequenced_task_runner.h>
#include <base/thread_annotations.h>
#include <base/guid.h>

#include <functional>
#include <map>
#include <string>

// -----------------------------------------------------------------------------
// Usage documentation
// -----------------------------------------------------------------------------
//
// Overview:
// We can use approach similar to `base::AutoLock` and ``GUARDED_BY`
// to perform checks on scope entry (and/or exit) and require 'custom locks'
// in code (guard code) using Clang Thread-Safety annotations
// i.e. we create custom types like `base::CustomThreadAutoLock myCustomThreadLock_`
// and then we can use annotations like `GUARDED_BY(myCustomThreadLock_)`.
//
// MOTIVATION
//
// We use Clang Thread-Safety annotations to:
//
// * Guard usage of some data or method with custom checks (like conditional validity)
// * Guard usage of some data or method with memory safety checks
//   See `CREATE_UNOWNED_REF_LIFETIME_GUARD` and ``CREATE_UNOWNED_PTR_LIFETIME_GUARD``
// * Guard some data or method with thread id (single-thread-bound)
//   sequence id (sequence-bound), strand id check (asio strand-bound), etc.
//   See `PRIVATE_METHOD_RUN_ON(&sequence_checker_)`,
//  `PUBLIC_METHOD_RUN_ON(&perConnectionStrand_)` etc.
// * Document that you must take care of thread-safety while using some data or method
//   See `CREATE_METHOD_GUARD`, `CREATE_NOT_THREAD_BOUND_GUARD`,
//   `GUARD_NOT_THREAD_BOUND_METHOD`, `DCHECK_NOT_THREAD_BOUND_GUARD`,
//   `DCHECK_NOT_THREAD_BOUND_GUARD` etc.
//
// USAGE
//
// class MyClass() {
//  public:
//   MyClass(ECS::SafeRegistry& registry)
//     : UNOWNED_REF_LIFETIME_GUARD(registry_)(&registry) // calls constructor
//     , registry_(registry)
//   {}
//
//   void allocateTcpResourceAndAccept()
//     PRIVATE_METHOD_RUN_ON(registry_) // same as exclusive_locks_required
//   {
//     DCHECK_NOT_THREAD_BOUND_GUARD(registry_);
//     DCHECK_UNOWNED_REF_LIFETIME_GUARD(registry_);
//     DCHECK_NOT_THREAD_BOUND_GUARD(fp_AcceptedConnectionAborted_);
//
//     DCHECK(registry_.RunsTasksInCurrentSequence());
//
//     // ...
//   }
//
//  private:
//   // Documents that you must take care of thread-safety while using `registry_`
//   CREATE_NOT_THREAD_BOUND_GUARD(registry_);
//   // Checks memory-validity via `DCHECK_UNOWNED_REF_LIFETIME_GUARD`
//   CREATE_UNOWNED_REF_LIFETIME_GUARD(registry_, ECS::SafeRegistry);
//   // On each access to ECS registry
//   // we must perform thread-safety and memory-validity checks
//   // due to `GUARDED_BY` (similar to `GUARDED_BY` with mutex-es)
//   ECS::SafeRegistry& registry_
//     // note that you can use multiple `GUARDED_BY`
//     GUARDED_BY(NOT_THREAD_BOUND_GUARD(registry_))
//     // note that you can use multiple `GUARDED_BY`
//     GUARDED_BY(UNOWNED_REF_LIFETIME_GUARD(registry_));
//   // Allowed to call from multiple threads, but not concurrently (thread_collision_warner.h).
//   FP_AcceptedConnectionAborted* fp_AcceptedConnectionAborted_
//     GUARD_MEMBER_DISALLOW_THREAD_COLLISION(fp_AcceptedConnectionAborted_);
// };
//
namespace basic {

// Allows to use `Type` with clang thread-safety annotations like `GUARDED_BY`.
// See http://clang.llvm.org/docs/ThreadSafetyAnalysis.html
template<typename Type>
struct LOCKABLE AnnotateLockable
{
  template <class... Args>
  AnnotateLockable(
    Args&&... args)
    : data(FORWARD(args)...)
  {}

  constexpr const Type& operator*() const
  {
    return data;
  }

  constexpr Type& operator*()
  {
    return data;
  }

  constexpr const Type* operator->() const
  {
    return &data;
  }

  constexpr Type* operator->()
  {
    return &data;
  }

  using StoredType = Type;

  Type data;
};

// Helper class used by DCHECK_RUN_ON
class SCOPED_LOCKABLE SequenceCheckerScope {
 public:
  explicit SequenceCheckerScope(
    const ::base::SequenceChecker* thread_like_object)
      EXCLUSIVE_LOCK_FUNCTION(thread_like_object) {}

  SequenceCheckerScope(
    const SequenceCheckerScope&) = delete;

  SequenceCheckerScope& operator=(
    const SequenceCheckerScope&) = delete;

  ~SequenceCheckerScope() UNLOCK_FUNCTION() {}

  static bool CalledOnValidSequence(
    const ::base::SequenceChecker* thread_like_object)
  {
    return thread_like_object->CalledOnValidSequence();
  }
};

// Helper class used by DCHECK_RUN_ON
class SCOPED_LOCKABLE SequencedTaskRunnerScope {
 public:
  explicit SequencedTaskRunnerScope(
    const ::base::SequencedTaskRunner* thread_like_object)
      EXCLUSIVE_LOCK_FUNCTION(thread_like_object) {}

  SequencedTaskRunnerScope(
    const SequencedTaskRunnerScope&) = delete;

  SequencedTaskRunnerScope& operator=(
    const SequencedTaskRunnerScope&) = delete;

  ~SequencedTaskRunnerScope() UNLOCK_FUNCTION() {}

  static bool RunsTasksInCurrentSequence(
    const ::base::SequencedTaskRunner* thread_like_object)
  {
    return thread_like_object->RunsTasksInCurrentSequence();
  }
};

#define CGEN_CAT(a, b) CGEN_CAT_I(a, b)
#define CGEN_CAT_I(a, b) CGEN_CAT_II(~, a ## b)
#define CGEN_CAT_II(p, res) res

#define CGEN_UNIQUE_NAME(base) CGEN_CAT(base, __COUNTER__)

// RUN_ON/GUARDED_BY/DCHECK_RUN_ON macros allows to annotate
// variables are accessed from same thread/task queue.
// Using tools designed to check mutexes, it checks at compile time everywhere
// variable is access, there is a run-time dcheck thread/task queue is correct.
//
// class ThreadExample {
//  public:
//   void NeedVar1() {
//     DCHECK_RUN_ON(network_thread_);
//     transport_->Send();
//   }
//
//  private:
//   Thread* network_thread_;
//   int transport_ GUARDED_BY(network_thread_);
// };
//
// class SequenceCheckerExample {
//  public:
//   int CalledFromPacer() RUN_ON(pacer_sequence_checker_) {
//     return var2_;
//   }
//
//   void CallMeFromPacer() {
//     DCHECK_RUN_ON(&pacer_sequence_checker_)
//        << "Should be called from pacer";
//     CalledFromPacer();
//   }
//
//  private:
//   int pacer_var_ GUARDED_BY(pacer_sequence_checker_);
//   SequenceChecker pacer_sequence_checker_;
// };
//
// class TaskQueueExample {
//  public:
//   class Encoder {
//    public:
//     TaskQueue* Queue() { return encoder_queue_; }
//     void Encode() {
//       DCHECK_RUN_ON(encoder_queue_);
//       DoSomething(var_);
//     }
//
//    private:
//     TaskQueue* const encoder_queue_;
//     Frame var_ GUARDED_BY(encoder_queue_);
//   };
//
//   void Encode() {
//     // Will fail at runtime when DCHECK is enabled:
//     // encoder_->Encode();
//     // Will work:
//     scoped_refptr<Encoder> encoder = encoder_;
//     encoder_->Queue()->PostTask([encoder] { encoder->Encode(); });
//   }
//
//  private:
//   scoped_refptr<Encoder> encoder_;
// }

// Document if a function expected to be called from same thread/task queue.
/// \note use it with functions in `private` API (that can NOT call `DCHECK_RUN_ON*`)
//
// EXAMPLE
//
// class MyClass {
// protected:
//  void internalRunLoop() NO_EXCEPTION
//    RUN_ON(&sequence_checker_);
// };
#define THREAD_ANNOTATION_ATTRIBUTE__RUN_ON(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(exclusive_locks_required(__VA_ARGS__))

#define PRIVATE_METHOD_RUN_ON(...) \
  THREAD_ANNOTATION_ATTRIBUTE__RUN_ON(__VA_ARGS__)

#define PROTECTED_METHOD_RUN_ON(...) \
  THREAD_ANNOTATION_ATTRIBUTE__RUN_ON(__VA_ARGS__)

/// \note use it with functions in `public` API (that can call `DCHECK_RUN_ON*`)
//
// EXAMPLE
//
// class MyClass {
// public:
//  void runLoop() NO_EXCEPTION
//    THREAD_ANNOTATION_ATTRIBUTE__RUN_ON_LOCKS_EXCLUDED(&sequence_checker_);
// };
#define THREAD_ANNOTATION_ATTRIBUTE__RUN_ON_LOCKS_EXCLUDED(...) \
  LOCKS_EXCLUDED(__VA_ARGS__)

#define PUBLIC_METHOD_RUN_ON(...) \
  THREAD_ANNOTATION_ATTRIBUTE__RUN_ON_LOCKS_EXCLUDED(__VA_ARGS__)

#define ANNOTATE_NOT_RUN_ON(...) \
  LOCKS_EXCLUDED(__VA_ARGS__)

// Type of `x` is `base::SequenceChecker*`
#define DCHECK_RUN_ON(x)                                              \
  ::basic::SequenceCheckerScope seq_check_scope(x); \
  DCHECK((x)); \
  DCHECK((x)->CalledOnValidSequence())

// Type of `x` is `base::SequencedTaskRunner*`
//
// USAGE
//
// CREATE_NOT_THREAD_BOUND_GUARD(periodicVerifyRunner_);
// scoped_refptr<::base::SequencedTaskRunner> periodicVerifyRunner_
//   // It safe to read value from any thread because its storage
//   // expected to be not modified (if properly initialized)
//   GUARDED_BY(NOT_THREAD_BOUND_GUARD(periodicVerifyRunner_));
// // ...
// DCHECK_THREAD_GUARD_SCOPE(periodicVerifyRunner_);
// DCHECK(periodicVerifyRunner_);
// DCHECK_RUN_ON_SEQUENCED_RUNNER(periodicVerifyRunner_.get());
#define DCHECK_RUN_ON_SEQUENCED_RUNNER(x)                                              \
  ::basic::SequencedTaskRunnerScope seq_task_runner_scope(x); \
  DCHECK((x)); \
  DCHECK((x)->RunsTasksInCurrentSequence())

// Will call `callback_.Run()` in any builds (including release),
// so take care of performance
struct FakeLockPolicyAlways
{
  /// \todo refactor to `enum class { isDebug, isSkip, isAlways }`
  static constexpr bool isDebugOnly = false;
  static constexpr bool isSkip = false;
  static constexpr bool isAlways = true;
};

// Will call `callback_.Run()` only in debug builds,
// prefer for performance reasons
struct FakeLockPolicyDebugOnly
{
  /// \todo refactor to `enum class { isDebug, isSkip, isAlways }`
  static constexpr bool isDebugOnly = true;
  static constexpr bool isSkip = false;
  static constexpr bool isAlways = false;
};

/// \note avoid `FakeLockPolicySkip` if you can
// Can be used to implement custom verification logic
struct FakeLockPolicySkip
{
  /// \todo refactor to `enum class { isDebug, isSkip, isAlways }`
  static constexpr bool isDebugOnly = false;
  static constexpr bool isSkip = true;
  static constexpr bool isAlways = false;
};

struct FakeLockCheckWholeScope
{
  /// \todo refactor to `enum class`
  static constexpr bool isWholeScope = true;
  static constexpr bool isOnlyEnterScope = false;
  static constexpr bool isOnlyExitScope = false;
};

struct FakeLockCheckEnterScope
{
  /// \todo refactor to `enum class`
  static constexpr bool isWholeScope = false;
  static constexpr bool isOnlyEnterScope = true;
  static constexpr bool isOnlyExitScope = false;
};

struct FakeLockCheckExitScope
{
  /// \todo refactor to `enum class`
  static constexpr bool isWholeScope = false;
  static constexpr bool isOnlyEnterScope = false;
  static constexpr bool isOnlyExitScope = true;
};


enum class LockPolicy {
  FakeMutex
  , Mutex
};

template <
  typename T
>
class LOCKABLE FakeLockWithLifetimeCheck {
public:
  FakeLockWithLifetimeCheck(T* ptr) : ptr_(ptr) {}

  ~FakeLockWithLifetimeCheck() { checkForLifetimeIssues(); }

  MUST_USE_RETURN_VALUE
  bool Acquire() const NO_EXCEPTION EXCLUSIVE_LOCK_FUNCTION()
  {
    checkForLifetimeIssues();
    return true;
  }

  MUST_USE_RETURN_VALUE
  bool Release() const NO_EXCEPTION UNLOCK_FUNCTION()
  {
    checkForLifetimeIssues();
    return true;
  }

  // check that object is alive, use memory tool like ASAN
  /// \note ignores nullptr
  inline void checkForLifetimeIssues() const
  {
    // Works with `-fsanitize=address,undefined`
    DCHECK_UNOWNED_PTR(ptr_);
  }

 private:
  // See `checkForLifetimeIssues()`
  T* ptr_ = nullptr;

  DISALLOW_COPY_AND_ASSIGN(FakeLockWithLifetimeCheck);
};

template <
  typename T
  // FakeLockCheckType::isDebugOnly performs check only in debug builds
  // FakeLockCheckType::isSkip does not perform any checks
  // FakeLockCheckType::isAlways performs checks in all builds
  , typename FakeLockPolicyType
  // FakeLockCheckType::isWholeScope performs check on both scope enter and exit
  // FakeLockCheckType::isOnlyEnterScope performs check only on scope enter
  // FakeLockCheckType::isOnlyEnterScope performs check only on scope exit
  , typename FakeLockCheckType
>
class SCOPED_LOCKABLE ScopedFakeLockWithLifetimeCheck
{
 public:
  ScopedFakeLockWithLifetimeCheck(
    const FakeLockWithLifetimeCheck<T>& lock
    , ::base::Location from_here)
    EXCLUSIVE_LOCK_FUNCTION(lock)
    : lock_(lock)
    , from_here_(from_here)
  {
    if constexpr (!FakeLockCheckType::isOnlyExitScope)
    {
      if constexpr (FakeLockPolicyType::isDebugOnly
        && DCHECK_IS_ON())
      {
        DCHECK(lock_.Acquire())
          << from_here_.ToString();
      }
      // all except `isSkip` run check always
      if constexpr (!FakeLockPolicyType::isSkip)
      {
        CHECK(lock_.Acquire())
          << from_here_.ToString();
      }
    }
  }

  ~ScopedFakeLockWithLifetimeCheck() UNLOCK_FUNCTION()
  {
    if constexpr (!FakeLockCheckType::isOnlyEnterScope)
    {
      if constexpr (FakeLockPolicyType::isDebugOnly
        && DCHECK_IS_ON())
      {
        DCHECK(lock_.Release())
          << from_here_.ToString();
      }
      // all except `isSkip` run check always
      if constexpr (!FakeLockPolicyType::isSkip)
      {
        CHECK(lock_.Release())
          << from_here_.ToString();
      }
    }
  }

 private:
  // takes care of limetime
  const FakeLockWithLifetimeCheck<T>& lock_;

  ::base::Location from_here_;

  DISALLOW_COPY_AND_ASSIGN(ScopedFakeLockWithLifetimeCheck);
};

template <
  LockPolicy LockPolicyType
  , typename Signature
>
class FakeLockWithChecks;

template <
  LockPolicy LockPolicyType
  // FakeLockCheckType::isDebugOnly performs check only in debug builds
  // FakeLockCheckType::isSkip does not perform any checks
  // FakeLockCheckType::isAlways performs checks in all builds
  , typename FakeLockPolicyType
  // FakeLockCheckType::isWholeScope performs check on both scope enter and exit
  // FakeLockCheckType::isOnlyEnterScope performs check only on scope enter
  // FakeLockCheckType::isOnlyEnterScope performs check only on scope exit
  , typename FakeLockCheckType
  , typename Signature
>
class ScopedFakeLockWithChecks;

/// \note Prefer instead `DCHECK_RUN_ON` to `FakeLockWithChecks` where possible.
/// \note It is not real lock, only annotated as lock.
/// It just calls callback on scope entry AND exit.
/// \note Need to build with `-Wthread-safety-analysis`
/// flag to see some effect.
/// see https://pspdfkit.com/blog/2020/the-cpp-lifetime-profile/
/// see http://clang.llvm.org/docs/ThreadSafetyAnalysis.html
/// see https://github.com/isocpp/CppCoreGuidelines/blob/master/docs/Lifetime.pdf
template<
  LockPolicy LockPolicyType
  , typename R
  , typename... Args
>
class LOCKABLE
  FakeLockWithChecks<LockPolicyType, R(Args...)>
{
 public:
  using RunType = R(Args...);

  using CallbackType
    = ::base::RepeatingCallback<RunType>;

  using CallbackId = std::string;

  using CallbacksStorage
    = ::std::map<
        CallbackId
        , CallbackType
      >;

  class Subscription {
   public:
    Subscription(FakeLockWithChecks* owner, CallbackId callbackId)
      : owner_(owner), callbackId_(callbackId)
    {}

    ~Subscription() {
      owner_->removeCheck(callbackId_);

      /// \todo do we need callback(s) upon removal like in `base::CallbackList`?
      //if (!owner_->removal_callback_.is_null())
      //  owner_->removal_callback_.Run();
    }

   private:
    FakeLockWithChecks* owner_;

    CallbackId callbackId_;

    DISALLOW_COPY_AND_ASSIGN(Subscription);
  };

  void removeCheck(const CallbackId& guid)
  {
    auto task = [&]() {
      auto it = callbacks_.find(guid);
      if (it == callbacks_.end()) return;
      callbacks_.erase(it);
    };

    if constexpr (LockPolicyType == basic::LockPolicy::FakeMutex)
    {
      DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
      task();
    }
    else if constexpr (LockPolicyType == basic::LockPolicy::Mutex)
    {
      base::AutoLock auto_lock(lock_);
      task();
    }
  }

  std::unique_ptr<
    Subscription
  >
    addRemovableCheck(CallbackType&& callback) NO_EXCEPTION
  {
    auto task = [&]() {
      CallbackId guid = base::GenerateGUID();
      addCheck(RVALUE_CAST(callback), guid);
      return std::make_unique<Subscription>(this, guid);
    };

    if constexpr (LockPolicyType == basic::LockPolicy::FakeMutex)
    {
      DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
      return task();
    }
    else if constexpr (LockPolicyType == basic::LockPolicy::Mutex)
    {
      base::AutoLock auto_lock(lock_);
      return task();
    }
  }

  std::unique_ptr<
    Subscription
  >
    addRemovableCheck(const CallbackType& callback) NO_EXCEPTION
  {
    auto task = [&]() {
      CallbackId guid = base::GenerateGUID();
      addCheck(callback, guid);
      return std::make_unique<Subscription>(this, guid);
    };

    if constexpr (LockPolicyType == basic::LockPolicy::FakeMutex)
    {
      DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
      return task();
    }
    else if constexpr (LockPolicyType == basic::LockPolicy::Mutex)
    {
      base::AutoLock auto_lock(lock_);
      return task();
    }
  }

  void addCheck(CallbackType&& callback, CallbackId guid = base::GenerateGUID()) NO_EXCEPTION
  {
    auto task = [&]() {
      DCHECK(callbacks_.find(guid) == callbacks_.end());
      callbacks_[guid] = callback;
    };

    if constexpr (LockPolicyType == basic::LockPolicy::FakeMutex)
    {
      DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
      task();
    }
    else if constexpr (LockPolicyType == basic::LockPolicy::Mutex)
    {
      base::AutoLock auto_lock(lock_);
      task();
    }
  }

  void addCheck(const CallbackType& callback, CallbackId guid = base::GenerateGUID()) NO_EXCEPTION
  {
    auto task = [&]() {
      DCHECK(callbacks_.find(guid) == callbacks_.end());
      callbacks_[guid] = RVALUE_CAST(callback);
    };

    if constexpr (LockPolicyType == basic::LockPolicy::FakeMutex)
    {
      DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
      task();
    }
    else if constexpr (LockPolicyType == basic::LockPolicy::Mutex)
    {
      base::AutoLock auto_lock(lock_);
      task();
    }
  }

  FakeLockWithChecks(
    const ::base::RepeatingCallback<RunType>& callback)
  {
    addCheck(callback);
  }

  FakeLockWithChecks(
    ::base::RepeatingCallback<RunType>&& callback)
  {
    addCheck(RVALUE_CAST(callback));
  }

  MUST_USE_RETURN_VALUE
  bool Acquire() const NO_EXCEPTION EXCLUSIVE_LOCK_FUNCTION()
  {
    auto task = [&]() {
      for(const auto& [guid, cb] : callbacks_) {
        if(!cb.Run()) {
          return false;
        }
      }
      return true;
    };

    if constexpr (LockPolicyType == basic::LockPolicy::FakeMutex)
    {
      DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
      return task();
    }
    else if constexpr (LockPolicyType == basic::LockPolicy::Mutex)
    {
      base::AutoLock auto_lock(lock_);
      return task();
    }
  }

  MUST_USE_RETURN_VALUE
  bool Release() const NO_EXCEPTION UNLOCK_FUNCTION()
  {
    auto task = [&]() {
      for(const auto& [guid, cb] : callbacks_) {
        if(!cb.Run()) {
          return false;
        }
      }
      return true;
    };

    if constexpr (LockPolicyType == basic::LockPolicy::FakeMutex)
    {
      DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
      return task();
    }
    else if constexpr (LockPolicyType == basic::LockPolicy::Mutex)
    {
      base::AutoLock auto_lock(lock_);
      return task();
    }
  }

 private:
  CallbacksStorage callbacks_{};

  mutable base::Lock lock_;

  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);

  DISALLOW_COPY_AND_ASSIGN(FakeLockWithChecks);
};

// Will call `FakeLockWithChecks::callback_.Run()`
// on scope entry AND exit.
//
// USAGE
//  class MyClass {
//    // ...
//
//    using FakeLockRunType = bool();
//
//    using FakeLockPolicy = ::basic::FakeLockPolicyDebugOnly;
//
//    MUST_USE_RETURN_VALUE
//    ::base::WeakPtr<Listener> weakSelf() const NO_EXCEPTION
//    {
//      /// \note `FakeLockPolicySkip` will NOT perform any checks.
//      /// No need to check thread-safety because `weak_this_`
//      /// can be passed safely between threads if not modified.
//      ::basic::ScopedFakeLockWithChecks<LockPolicy::Mutex, basic::FakeLockPolicySkip, FakeLockRunType>
//        auto_lock(fakeLockToSequence_, FROM_HERE);
//
//      // It is thread-safe to copy |base::WeakPtr|.
//      // Weak pointers may be passed safely between sequences, but must always be
//      // dereferenced and invalidated on the same SequencedTaskRunner otherwise
//      // checking the pointer would be racey.
//      return weak_this_;
//    }
//
//    // After constructing |weak_ptr_factory_|
//    // we immediately construct a WeakPtr
//    // in order to bind the WeakPtr object to its thread.
//    // When we need a WeakPtr, we copy construct this,
//    // which is safe to do from any
//    // thread according to weak_ptr.h (versus calling
//    // |weak_ptr_factory_.GetWeakPtr() which is not).
//    const ::base::WeakPtr<Listener> weak_this_
//      GUARDED_BY(fakeLockToSequence_);
//
//    /// \note It is not real lock, only annotated as lock.
//    /// It just calls callback on scope entry AND exit.
//    ::basic::FakeLockWithChecks<FakeLockRunType> fakeLockToSequence_{
//        ::base::BindRepeating(
//          &base::SequenceChecker::CalledOnValidSequence
//          , ::base::Unretained(&sequence_checker_)
//        )
//    };
//
//    // ...
//  };
template <
  basic::LockPolicy LockPolicyType
  , typename FakeLockPolicyType
  , typename FakeLockCheckType
  , typename R
  , typename... Args
>
class SCOPED_LOCKABLE
  ScopedFakeLockWithChecks<
    LockPolicyType
    , FakeLockPolicyType
    , FakeLockCheckType
    , R(Args...)
  >
{
 public:
  using RunType = R(Args...);

  ScopedFakeLockWithChecks(
    const FakeLockWithChecks<LockPolicyType, RunType>& lock
    , ::base::Location from_here)
    EXCLUSIVE_LOCK_FUNCTION(lock)
    : lock_(lock)
    , from_here_(from_here)
  {
    if constexpr (!FakeLockCheckType::isOnlyExitScope)
    {
      if constexpr (FakeLockPolicyType::isDebugOnly
        && DCHECK_IS_ON())
      {
        DCHECK(lock_.Acquire())
          << from_here_.ToString();
      }
      // all except `isSkip` run check always
      if constexpr (!FakeLockPolicyType::isSkip)
      {
        CHECK(lock_.Acquire())
          << from_here_.ToString();
      }
    }
  }

  ~ScopedFakeLockWithChecks() UNLOCK_FUNCTION()
  {
    if constexpr (!FakeLockCheckType::isOnlyEnterScope)
    {
      if constexpr (FakeLockPolicyType::isDebugOnly
        && DCHECK_IS_ON())
      {
        DCHECK(lock_.Release())
          << from_here_.ToString();
      }
      // all except `isSkip` run check always
      if constexpr (!FakeLockPolicyType::isSkip)
      {
        CHECK(lock_.Release())
          << from_here_.ToString();
      }
    }
  }

 private:
  /// \note take care of reference limetime
  const FakeLockWithChecks<LockPolicyType, RunType>& lock_;

  ::base::Location from_here_;

  DISALLOW_COPY_AND_ASSIGN(ScopedFakeLockWithChecks);
};

#define CREATE_FAKE_THREAD_GUARD(Name) \
  ::basic::FakeLockWithChecks<basic::LockPolicy::Mutex, bool()> \
    Name { \
    ::basic::VerifyNothing::Repeatedly() \
  }

// See `GUARD_MEMBER_WITH_CHECK`
#define CREATE_FAKE_THREAD_GUARD_WITH_CHECK(Name, Callback) \
  ::basic::FakeLockWithChecks<basic::LockPolicy::Mutex, bool()> \
    Name { \
    Callback \
  }

// Prefer instead `GUARD_MEMBER_WITH_CHECK` to `SET_THREAD_GUARD_WITH_CHECK`
#define SET_THREAD_GUARD_WITH_CHECK(Name, Callback) \
  GUARDED_BY(Name); \
  CREATE_FAKE_THREAD_GUARD_WITH_CHECK(Name, Callback)

// See `GUARD_MEMBER_WITH_DYNAMIC_CHECK`
#define CREATE_DYNAMIC_THREAD_GUARD_WITH_CHECK(Name, Callback) \
  ::basic::FakeLockWithChecks<basic::LockPolicy::Mutex, bool()> Name{ \
    ::basic::VerifyNothing::Repeatedly())}

// Similar to `SET_THREAD_GUARD_WITH_CHECK`, but does not require to pass
// callback into `FakeLockWithChecks` constructor.
//
// Prefer instead `GUARD_MEMBER_WITH_DYNAMIC_CHECK` to `SET_DYNAMIC_THREAD_GUARD`
//
#define SET_DYNAMIC_THREAD_GUARD(Name) \
  GUARDED_BY(Name); \
  CREATE_DYNAMIC_THREAD_GUARD_WITH_CHECK(Name)

/// \notes requires to include:
/// #include <base/threading/thread_collision_warner.h>
/// #include <base/macros.h>
#define CREATE_RECURSIVE_THREAD_COLLISION_GUARD(Name, MutexName) \
  DFAKE_MUTEX(MutexName); \
  CREATE_FAKE_THREAD_GUARD_WITH_CHECK(Name \
    , ::base::BindRepeating( \
      [ \
      ]( \
        ::base::ThreadCollisionWarner& debug_collision_warner \
      ){ \
        DFAKE_SCOPED_RECURSIVE_LOCK(debug_collision_warner); \
        return true; \
      } \
      , REFERENCED(MutexName) \
    ) \
  )

// See `thread_collision_warner.h`
// Sets thread collision warner to ensure that API is not called concurrently.
// API allowed to call from multiple threads, but not concurrently.
// Usually it means that var. can be used only by one thread at some
// moment of time (but different threads can use it overall).
// Imagine (as example) chain of `base::Promise` that uses same object
// on multiple threads, but all accesses are sequential
// (without thread collision).
#define SET_THREAD_COLLISION_GUARD(Name) \
  GUARDED_BY(Name); \
  CREATE_RECURSIVE_THREAD_COLLISION_GUARD( \
    Name, CGEN_UNIQUE_NAME(fake_mutex_))

/// \note Prefer instead RUN_ON(Name, m1, m2)
// Per-variable alternative to `RUN_ON`
// Documents that you must take care of thread safety somehow.
// That allows to notice (find & debug & fix) code
// that can be used from multiple threads.
#define THREAD_ANNOTATION_ATTRIBUTE__USE_CUSTOM_THREAD_GUARD(Name) \
  THREAD_ANNOTATION_ATTRIBUTE__(exclusive_locks_required(Name))

// Guard name for member variable
#define MEMBER_GUARD(Name) \
  member_guard_##Name

// Guard name for member variable
#define NOT_THREAD_BOUND_GUARD(Name) \
  not_thread_bound_guard_##Name

// Guard name for member variable
#define UNOWNED_REF_LIFETIME_GUARD(Name) \
  unowned_ref_lifetime_guard_##Name

// Guard name for member variable
#define UNOWNED_PTR_LIFETIME_GUARD(Name) \
  unowned_ptr_lifetime_guard_##Name

// Guard name for function
#define FUNC_GUARD(Name) \
  func_guard_##Name

// Per-variable alternative to `DCHECK_RUN_ON`
// Documents that you must take care of thread safety somehow.
// That allows to notice (find & debug & fix) code
// that can be used from multiple threads.
#define FAKE_CUSTOM_THREAD_GUARD(Name, Policy, Scope) \
  ::basic::ScopedFakeLockWithChecks<\
    basic::LockPolicy::Mutex \
    , Policy\
    , Scope\
    , bool()\
  > \
    CGEN_UNIQUE_NAME(auto_lock_run_on_) \
      (Name, FROM_HERE)

// FakeLockCheckType::isWholeScope performs check on both scope enter and exit
#define DCHECK_THREAD_GUARD_SCOPE(Name) \
  FAKE_CUSTOM_THREAD_GUARD(Name, \
    ::basic::FakeLockPolicyDebugOnly, \
    ::basic::FakeLockCheckWholeScope)

// FakeLockCheckType::isOnlyEnterScope performs check only on scope enter
//
// EXAMPLE
//  /// \note `is_stream_valid_` may become invalid on scope exit,
//  /// so check it only on beginning of function scope,
//  /// but not at the end of function.
//  DCHECK_THREAD_GUARD_SCOPE_ENTER(MEMBER_GUARD(perConnectionStrand_));
#define DCHECK_THREAD_GUARD_SCOPE_ENTER(Name) \
  FAKE_CUSTOM_THREAD_GUARD(Name, \
    ::basic::FakeLockPolicyDebugOnly, \
    ::basic::FakeLockCheckEnterScope)

// See `thread_collision_warner.h`
//
// USAGE
//
// ::basic::PeriodicValidateUntil periodicValidateUntil_
//   GUARD_MEMBER_DISALLOW_THREAD_COLLISION(periodicValidateUntil_);
// // ...
// DCHECK_MEMBER_GUARD(periodicValidateUntil_);
//
#define GUARD_MEMBER_DISALLOW_THREAD_COLLISION(Name) \
  SET_THREAD_COLLISION_GUARD(MEMBER_GUARD(Name))

/// \note `GUARD_MEMBER_WITH_CHECK` assumed to be used with one check that
/// passed to constructor as repeating callback.
/// You also can add checks dynamically using `addCheck`,
/// see `GUARD_MEMBER_WITH_DYNAMIC_CHECK`
//
// USAGE
//
//  ::basis::AnnotatedStrand<ExecutorType> perConnectionStrand_
//    GUARD_MEMBER_WITH_CHECK(
//      perConnectionStrand_
//      // 1. It safe to read value from any thread
//      // because its storage expected to be not modified.
//      // 2. On each access to strand check that stream valid
//      // otherwise `::boost::asio::post` may fail.
//      , ::base::BindRepeating(
//          [] \
//          (HttpChannel* self) -> bool {
//            DCHECK_THREAD_GUARD_SCOPE(self->guard_is_stream_valid_);
//            /// \note |perConnectionStrand_|
//            /// is valid as long as |stream_| valid
//            /// i.e. valid util |stream_| moved out
//            /// (it uses executor from stream).
//            return self->is_stream_valid_.load();
//          }
//          , ::base::Unretained(this)
//        )
//    );
//
// // ...
//
// DCHECK_MEMBER_GUARD(perConnectionStrand_);
//
#define GUARD_MEMBER_WITH_CHECK(Name, Callback) \
  SET_THREAD_GUARD_WITH_CHECK(MEMBER_GUARD(Name), Callback)

// EXAMPLE
//
// int myVar_ GUARD_MEMBER_WITH_DYNAMIC_CHECK(myVar_);
// MEMBER_GUARD(myVar_).addCheck(base::bindRepeating(
//   &MyClass::doMyCheck1
//   , base::Unretained(this))
// );
// MEMBER_GUARD(myVar_).addCheck(base::BindRepeating(
//   &base::SequenceChecker::CalledOnValidSequence
//   , base::Unretained(&sequence_checker_)
// ));
// MEMBER_GUARD(myVar_).addCheck(base::BindRepeating(
//   &base::SequencedTaskRunner::RunsTasksInCurrentSequence
//   , base::Unretained(registry_->taskRunner().get())
// ));
//
#define GUARD_MEMBER_WITH_DYNAMIC_CHECK(Name) \
  SET_DYNAMIC_THREAD_GUARD(MEMBER_GUARD(Name))

// FakeLockCheckType::isOnlyEnterScope performs check only on scope exit
#define DCHECK_THREAD_GUARD_SCOPE_EXIT(Name) \
  FAKE_CUSTOM_THREAD_GUARD(Name, \
    ::basic::FakeLockPolicyDebugOnly, \
    ::basic::FakeLockCheckExitScope)

/// \note avoid `DCHECK_CUSTOM_THREAD_GUARD_NOTHING` if you can
#define DCHECK_CUSTOM_THREAD_GUARD_NOTHING(Name) \
  FAKE_CUSTOM_THREAD_GUARD(Name, \
    ::basic::FakeLockPolicySkip, \
    ::basic::FakeLockCheckExitScope)

// Documents that variable allowed to be used from any thread
// and you MUST take care of thread-safety somehow.
//
// USE CASE EXAMPLES
//
// 1. Unmodified global variable can be used from any thread
// (if properly initialized).
// It safe to read value from any thread
// because its storage expected to be not modified,
// we just need to check storage validity.
// 2. Thread-safe type (like atomic).
#define THREAD_ANNOTATION_ATTRIBUTE_GUARDED_BY_ANY_THREAD(Name) \
  GUARDED_BY(Name)

/// \note Prefer instead `RUN_ON_ANY_THREAD_LOCKS_EXCLUDED`
// `RUN_ON_ANY_THREAD` can be used to force API users
// to use `DCHECK_NOT_THREAD_BOUND_GUARD` on each call to some function because
// function is NOT thread-safe and must be avoided
// i.e. it makes API ugly intentionally
/// \note Alternatively you can combine it with multiple `mutexes`
/// like so: `RUN_ON(ANY_THREAD_GUARD(), m1, m2)`
// Documents that function allowed to be used from any thread
// and you MUST take care of thread-safety somehow.
//
// USAGE
//
//   void logFailure(const ErrorCode& ec, char const* what)
//     RUN_ON_ANY_THREAD(logFailure); // documents about thread-safety
//
//   // ...
//   CREATE_FAKE_THREAD_GUARD(logFailure);
//   // ...
//
//   {
//     DCHECK_NOT_THREAD_BOUND_METHOD(logFailure); // documents about thread-safety
//     logFailure(ec, "open");
//   }
//
// EXAMPLE
//
//   // can be used to acess registry on task runner
//   MUST_USE_RETURN_VALUE
//   ALWAYS_INLINE
//   ECS::Registry& registry() NO_EXCEPTION
//     /// \note force API users to use `DCHECK_NOT_THREAD_BOUND_METHOD`
//     /// on each call to `registry()` because
//     /// function is NOT thread-safe and must be avoided
//     /// in preference to `operator*()` or `operator->()`
//     RUN_ON_ANY_THREAD(fn_registry) // documents about thread-safety
//   {
//     DCHECK_THREAD_GUARD_SCOPE(guard_registry_);
//
//     return registry_;
//   }
#define THREAD_ANNOTATION_ATTRIBUTE__RUN_ON_ANY_THREAD(Name) \
  THREAD_ANNOTATION_ATTRIBUTE__(exclusive_locks_required(Name))

// Use `RUN_ON_ANY_THREAD_LOCKS_EXCLUDED` if you want to
// document that function may be NOT thread-safe.
/// \note Alternatively you can combine it with multiple `mutexes`
/// like so: `LOCKS_EXCLUDED(Name, m1, m2)`
// Documents that function allowed to be used from any thread
// and you MUST take care of thread-safety somehow.
//
// USAGE
//
//   void logFailure(const ErrorCode& ec, char const* what)
//    RUN_ON_ANY_THREAD_LOCKS_EXCLUDED(logFailure) // documents about thread-safety
//  {
//    DCHECK_NOT_THREAD_BOUND_METHOD(logFailure); // documents about thread-safety
//
//    // ...
//  }
//
//   // ...
//   CREATE_FAKE_THREAD_GUARD(logFailure);
//   // ...
//
//   {
//     logFailure(ec, "open");
//   }
#define THREAD_ANNOTATION_ATTRIBUTE__RUN_ON_ANY_THREAD_LOCKS_EXCLUDED(Name) \
  LOCKS_EXCLUDED(Name)

#define DCHECK_MEMBER_GUARD(Name) \
  DCHECK_THREAD_GUARD_SCOPE_ENTER(MEMBER_GUARD(Name))

// Document that you must take care of thread-safety while using some data.
//
// NOTE: Do not mark each not thread-bound data member with it.
// NOTE: Do not use it with `std::atomic<>` because it is
// obvious that you can use `std::atomic<>` safely in multiple threads.
// NOTE: Do not use it with `const MyType` because it is usually
// obvious that you can use `const` safely (not always!) in multiple threads.
// NOTE: Do not use it with global unowned objects (`MyType&`) because it is usually
// obvious that you can use them safely (not always!) in multiple threads.
// It is because references are always const
// i.e. `X& const x` is functionally equivalent to `X& x`.
#define DCHECK_NOT_THREAD_BOUND_GUARD(Name) \
  DCHECK_THREAD_GUARD_SCOPE_ENTER(NOT_THREAD_BOUND_GUARD(Name))

// Allow to use code that can be used from any thread
// (in current scope only).
//
// Used for documentation purposes, so it is good idea
// to pass affected function names, variable names, etc.
//
// EXAMPLE
// class MySharedClass {
//   // ...
//   CREATE_FAKE_THREAD_GUARD(MySharedClassDestructor);
//   // ...
//   ~MySharedClass()
//   {
//     // documents that destructor called from any thread
//     DCHECK_NOT_THREAD_BOUND_METHOD(MySharedClassDestructor);
//   }
// };
#define DCHECK_NOT_THREAD_BOUND_METHOD(Name) \
  DCHECK_THREAD_GUARD_SCOPE_ENTER(FUNC_GUARD(Name))

// Will check if pointer is valid on scope exit.
// Can be used with safety annotations (GUARDED_BY).
//
// USAGE
//
// class Ex1 {
//  // ...
//  int* my_ptr;
//  SCOPED_UNOWNED_PTR_CHECKER(my_ptr);
//  int data_that_requires_my_ptr
//    GUARDED_BY(UNOWNED_PTR_LIFETIME_GUARD(my_ptr));
//  // ...
//  DCHECK_UNOWNED_PTR_LIFETIME_GUARD(data_that_requires_my_ptr);
//  data_that_requires_my_ptr = (*my_ptr) * 123;
// }
//
#define SCOPED_UNOWNED_PTR_CHECKER(Name) \
  ::basic::FakeLockWithLifetimeCheck< \
    const void  \
  > UNOWNED_PTR_LIFETIME_GUARD(Name) { static_cast<const void*>( Name ) }; \
  ::basic::ScopedFakeLockWithLifetimeCheck<\
    const void \
    , ::basic::FakeLockPolicyDebugOnly \
    , ::basic::FakeLockCheckExitScope \
  > \
    CGEN_UNIQUE_NAME(auto_lock_ptr_lifetime_checker_)  \
      { UNOWNED_PTR_LIFETIME_GUARD(Name), ::base::Location::CreateFromHere(__FILE__) }

// Will check if reference is valid on scope exit.
// Can be used with safety annotations (GUARDED_BY).
//
// USAGE
//
// class Ex1 {
//  // ...
//  int& my_ref;
//  SCOPED_UNOWNED_REF_CHECKER(my_ref);
//  int data_that_requires_my_ref
//    GUARDED_BY(UNOWNED_REF_LIFETIME_GUARD(my_ref));
//  // ...
//  DCHECK_UNOWNED_REF_LIFETIME_GUARD(data_that_requires_my_ref);
//  data_that_requires_my_ref = my_ref * 123;
// }
#define SCOPED_UNOWNED_REF_CHECKER(Name) \
  ::basic::FakeLockWithLifetimeCheck< \
    const void  \
  > UNOWNED_REF_LIFETIME_GUARD(Name){static_cast<const void*>(&Name)}; \
  ::basic::ScopedFakeLockWithLifetimeCheck<\
    const void \
    , ::basic::FakeLockPolicyDebugOnly \
    , ::basic::FakeLockCheckExitScope \
  > \
    CGEN_UNIQUE_NAME(auto_lock_ref_lifetime_checker_) \
     { UNOWNED_REF_LIFETIME_GUARD(Name), ::base::Location::CreateFromHere(__FILE__) }

#define DCHECK_UNOWNED_REF_LIFETIME_GUARD(Name) \
  ::basic::ScopedFakeLockWithLifetimeCheck<\
    std::remove_reference_t<decltype(Name)> \
    , ::basic::FakeLockPolicyDebugOnly \
    , ::basic::FakeLockCheckWholeScope \
  > \
    CGEN_UNIQUE_NAME(auto_lock_ref_lifetime_guard_) \
      (UNOWNED_REF_LIFETIME_GUARD(Name), FROM_HERE)

#define DCHECK_UNOWNED_PTR_LIFETIME_GUARD(Name) \
  ::basic::ScopedFakeLockWithLifetimeCheck<\
    std::remove_reference_t<decltype(Name)> \
    , ::basic::FakeLockPolicyDebugOnly \
    , ::basic::FakeLockCheckWholeScope \
  > \
    CGEN_UNIQUE_NAME(auto_lock_ptr_lifetime_guard_) \
      (UNOWNED_PTR_LIFETIME_GUARD(Name), FROM_HERE)

// Documents that class (or struct, etc.)
// member is not thread-bound
// i.e. can be used by multiple threads.
//
// For example, it MAY be safe to read value from any thread
// if its storage expected to be not modified
// (if properly initialized)
#define CREATE_NOT_THREAD_BOUND_GUARD(Name) \
  CREATE_FAKE_THREAD_GUARD(NOT_THREAD_BOUND_GUARD(Name))

/// \note Do not forget to init created UNOWNED_REF_LIFETIME_GUARD(Name)
/// in constructor.
//
// USAGE
//
// CREATE_NOT_THREAD_BOUND_GUARD(registry_);
// CREATE_UNOWNED_REF_LIFETIME_GUARD(registry_, ECS::SafeRegistry);
// // used to create `per-connection entity`
// ECS::SafeRegistry& registry_
//   GUARDED_BY(NOT_THREAD_BOUND_GUARD(registry_))
//   GUARDED_BY(UNOWNED_REF_LIFETIME_GUARD(registry_));
// // ... in constructor ...
// : UNOWNED_REF_LIFETIME_GUARD(Name){&registry_}
#define CREATE_UNOWNED_REF_LIFETIME_GUARD(Name, ...) \
  ::basic::FakeLockWithLifetimeCheck< \
      __VA_ARGS__  \
    > \
    UNOWNED_REF_LIFETIME_GUARD(Name)

/// \note Do not forget to init created UNOWNED_PTR_LIFETIME_GUARD(Name)
/// in constructor.
//
// USAGE
//
// CREATE_NOT_THREAD_BOUND_GUARD(registry_);
// CREATE_UNOWNED_PTR_LIFETIME_GUARD(registry_, ECS::SafeRegistry);
// // used to create `per-connection entity`
// ECS::SafeRegistry* registry_
//   GUARDED_BY(NOT_THREAD_BOUND_GUARD(registry_))
//   GUARDED_BY(UNOWNED_PTR_LIFETIME_GUARD(registry_));
// // ... in constructor ...
// : UNOWNED_PTR_LIFETIME_GUARD(Name){&registry_}
//
#define CREATE_UNOWNED_PTR_LIFETIME_GUARD(Name, ...) \
  ::basic::FakeLockWithLifetimeCheck< \
      __VA_ARGS__  \
    > UNOWNED_PTR_LIFETIME_GUARD(Name)

// Documents that class (or struct, etc.)
// `public:` member fuction is not thread-bound
// i.e. can be used by multiple threads.
#define GUARD_NOT_THREAD_BOUND_METHOD(Name) \
  THREAD_ANNOTATION_ATTRIBUTE__RUN_ON_ANY_THREAD_LOCKS_EXCLUDED(FUNC_GUARD(Name))

#define CREATE_METHOD_GUARD(Name) \
  CREATE_FAKE_THREAD_GUARD(FUNC_GUARD(Name))

#define CREATE_MEMBER_GUARD(Name) \
  CREATE_FAKE_THREAD_GUARD(MEMBER_GUARD(Name))

} // namespace basic
