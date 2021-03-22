#pragma once

#include <base/macros.h>
#include <base/logging.h>
#include <base/values.h>
#include <base/sequence_checker.h>
#include <base/threading/thread_collision_warner.h>
#include <base/location.h>
#include <base/no_destructor.h>
#include <base/optional.h>
#include <base/callback.h>
#include <base/callback_list.h>

#include <basic/strong_types/strong_string.h>
#include <basic/rvalue_cast.h>

#include <functional>
#include <string>

/// \note `StrongPlugPoint` can store only one callback.
/// If you want to support multiple callbacks, than use
/// `PlugPointNotifier` or `PlugPointRunner.
/// Registered callback can be removed.
//
// USAGE
//
// STRONG_PLUG_POINT(PlugPoint_RecievedData, base::Optional<bool>(const std::string&));
//
#define STRONG_PLUG_POINT(VAR, ...) \
  using VAR \
    = ::basic::StrongPlugPoint< \
          class PP_##VAR##Tag \
          , __VA_ARGS__ \
        >

/// \note Can support multiple void callbacks with same args.
/// Registered callbacks can NOT be removed.
///
//
// USAGE
//
// STRONG_PLUG_POINT_NOTIFIER(PlugPoint_RecievedData, void(const std::string&));
//
#define STRONG_PLUG_POINT_NOTIFIER(VAR, ...) \
  using VAR \
    = ::basic::StrongPlugPointNotifier< \
          class PP_##VAR##Tag \
          , __VA_ARGS__ \
        >

/// \note Can support multiple callbacks with same signature (return type and args).
/// Registered callbacks can be removed.
//
// USAGE
//
// STRONG_PLUG_POINT_RUNNER(PlugPoint_RecievedData, base::Optional<bool>(const std::string&));
//
#define STRONG_PLUG_POINT_RUNNER(VAR, ...) \
  using VAR \
    = ::basic::StrongPlugPointRunner< \
          class PP_##VAR##Tag \
          , __VA_ARGS__ \
        >

// Build plug point name
#define PLUG_POINT(VAR) \
  PP_##VAR

// USAGE
//
// STRONG_PLUG_POINT(PP_AcceptedConnectionAborted);
// // class member var.
// PP_AcceptedConnectionAborted* pp_AcceptedConnectionAborted_ = nullptr;
// // in class constructor
// pp_AcceptedConnectionAborted_ = PLUG_POINT_INSTANCE(PP_AcceptedConnectionAborted);
//
#define PLUG_POINT_INSTANCE(...) \
  __VA_ARGS__::GetInstance(FROM_HERE, \
      ::basic::PlugPointName{STRINGIFY_VA_ARG(__VA_ARGS__)})

/// \note Avoid `ASSIGN_PLUG_POINT`,
/// prefer to cache pointer using `PLUG_POINT_INSTANCE`
//
// USAGE
//
// ASSIGN_PLUG_POINT(plugPoint, FailPoint_FP1);
// const base::Optional<bool> pluggedReturn = plugPoint->Run(int{1}, double{3.0});
// if(UNLIKELY(pluggedReturn))
// {
//   return pluggedReturn.value();
// }
#define ASSIGN_PLUG_POINT(VAR, ...) \
  __VA_ARGS__* VAR = PLUG_POINT_INSTANCE(__VA_ARGS__)

// USAGE
//
// ASSIGN_PLUG_POINT(plugPointPtr, flexnet::ws::PlugPoint_RecievedData);
// IF_PLUG_POINT_HAS_VALUE(plugPointPtr, REFERENCED(message)) {
//   return {"something"}
// };
#define IF_PLUG_POINT_HAS_VALUE(plugPoint, ...) \
  if(const base::Optional<bool> pluggedReturn         \
      = plugPoint->Run(__VA_ARGS__);                  \
      UNLIKELY(pluggedReturn))

// USAGE
//
// ASSIGN_PLUG_POINT(plugPointPtr, flexnet::ws::PlugPoint_RecievedData);
// RETURN_IF_PLUG_POINT_HAS_VALUE(plugPointPtr, REFERENCED(message));
#define RETURN_IF_PLUG_POINT_HAS_VALUE(plugPoint, ...) \
  do {                                                 \
    IF_PLUG_POINT_HAS_VALUE(plugPoint, __VA_ARGS__)    \
    {                                                  \
      return;                                          \
    }                                                  \
  } while (0)

// USAGE
//
// ASSIGN_PLUG_POINT(plugPointPtr, flexnet::ws::PlugPoint_RecievedData);
// RETURN_IF_PLUG_POINT_WITH_VALUE(plugPointPtr, REFERENCED(message));
#define RETURN_IF_PLUG_POINT_WITH_VALUE(plugPoint, ...) \
  do {                                                  \
    const base::Optional<std::string> pluggedReturn     \
      = plugPoint->Run(__VA_ARGS__);                    \
    if(UNLIKELY(pluggedReturn))                         \
    {                                                   \
      return pluggedReturn.value();                     \
    }                                                   \
  } while (0)

// A PlugPoint is a hook mechanism allowing custom behavior to occur
// at prearranged execution points.
//
// PlugPoint-s can be used as alternative to `sigslot` (Unlike FailPoins)
//
// PlugPoint-s can be activated and deactivated.
//
// PlugPoint-s can not hold arbitrary data,
// only base::Callback-s (Unlike FailPoins)
//
// Usually you want to use `::basic::StrongPlugPointRunner` (see below)
//
namespace basic {

// `PlugPoint` works only with `base::Optional` for now
namespace plug_point_internal {
template <typename T>
struct is_optional : std::false_type {};

template <typename T>
struct is_optional<base::Optional<T>> : std::true_type {};
} // namespace plug_point_internal

// Priority sorted from Highest (0) to Lowest (6)
enum class PlugPointPriority
{
  Highest = 0
  , VeryHigh = 1
  , High = 2
  , Medium = 3
  , Low = 4
  , VeryLow = 5
  , Lowest = 6
  , TOTAL
};

// can be used for debug purposes
STRONGLY_TYPED_STRING(PlugPointName);

// Storage with thread-safety checks
//
/// \note API must be fast (plug points may exist in any production code),
/// so do not use thread synchronization primitives (like `atomic`) here.
//
/// \note API allowed to call from multiple threads, but not concurrently.
/// Usually that means that you must setup all plug points
/// during app construction (or that you must pause app
/// before modification of plug points).
//
template<
  typename RetType
  , typename... ArgsType
>
class PlugPointStorage
{
 public:
  static_assert(basic::plug_point_internal::is_optional<RetType>::value,
                "Use PlugPointStorage only if callback returns base::Optional.");

  using CallbackType
    = ::base::RepeatingCallback<RetType(ArgsType...)>;

  // Use subscription to remove registered callbacks
  class Subscription {
   public:
    Subscription(PlugPointStorage* plug_storage)
      : plug_storage_(plug_storage)
    {}

    ~Subscription() {
      plug_storage_->resetCallback();

      /// \todo do we need callback(s) upon removal like in `base::CallbackList`?
      //if (!plug_storage_->removal_callback_.is_null())
      //  plug_storage_->removal_callback_.Run();
    }

   private:
    PlugPointStorage* plug_storage_;

    DISALLOW_COPY_AND_ASSIGN(Subscription);
  };

  explicit PlugPointStorage(const ::base::Location& location, const PlugPointName& name)
    : name_(name)
    , location_(location)
    , is_active_(false)
    , callback_()
  {
  }

  MUST_USE_RETURN_VALUE
  const PlugPointName& getName() const NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return name_;
  }

  MUST_USE_RETURN_VALUE
  bool isActive() const NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return is_active_;
  }

  void disable() NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    is_active_ = false;
  }

  void enable() NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    is_active_ = true;
  }

  template <typename... Args>
  MUST_USE_RETURN_VALUE
  RetType Run(Args&&... args) const NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    if(!isActive() || !callback_)
    {
      return base::nullopt;
    }

    DCHECK(callback_.value());

    return callback_.value().Run(FORWARD(args)...);
  }

  template <typename... Args>
  MUST_USE_RETURN_VALUE
  RetType operator()(Args&&... args) const NO_EXCEPTION
  {
    return Run(FORWARD(args)...);
  }

  MUST_USE_RETURN_VALUE
  std::unique_ptr<Subscription> setCallback(const CallbackType& callback) NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    callback_ = callback;
    return std::make_unique<Subscription>(this);
  }

  MUST_USE_RETURN_VALUE
  std::unique_ptr<Subscription> setCallback(CallbackType&& callback) NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    callback_ = RVALUE_CAST(callback);
    return std::make_unique<Subscription>(this);
  }

  void resetCallback() NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    callback_ = base::nullopt;
  }

 private:
  PlugPointName name_;

  base::Location location_;

  bool is_active_;

  base::Optional<CallbackType> callback_;

  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);

  DISALLOW_COPY_AND_ASSIGN(PlugPointStorage);
};

// Each plug point is unique object (uses `GetInstance`)
// and unique data type (uses type-tag similar to StrongAlias)
//
// MOTIVATION
//
// API must be fast (plug points may exist in any production code),
// so do not use map<string, PlugPoint>.
//
// Use `GetInstance` for fast access to individual plug point.
//
// PERFORMANCE TIPS
//
// Re-use (cache) pointer returned by `GetInstance` for max. performance
// i.e. use `auto* fp = MyPlugPoint::GetInstance(); fp->...; fp->...;`
//
// Use `UNLIKELY` near `isActive()` for max. performance
// (we assume that usually most of plug points are disabled).
//
template<typename Tag, typename T>
class StrongPlugPoint;

/// \note `StrongPlugPoint` can store only one callback.
/// If you want to support multiple callbacks, than use
/// `PlugPointNotifier` or `PlugPointRunner`.
/// Registered callback can be removed.
//
// USE CASE
//
// Multiple plugins can provide callback to process some file,
// but only one callback must be run to process file only once.
//
// USAGE
//
//  // my_plug_points.hpp
//  using PlugPoint_FP1
//    = ::basic::StrongPlugPoint<
//          class PlugPointFP1Tag
//          , base::Optional<bool>(int, double)
//        >;
//
//  std::unique_ptr<PlugPoint_FP1::Subscription> subscription;
//
//  // on `plugin A` thread, before app started
//  {
//    // `plugin A` includes "my_plug_points.hpp"
//
//    PlugPoint_FP1* plugPoint
//      = PlugPoint_FP1::GetInstance(FROM_HERE, ::basic::PlugPointName{"plugPoint"});
//
//    plugPoint->enable();
//
//    subscription = plugPoint->setCallback(base::BindRepeating(
//      [
//      ](
//        int a
//        , double b
//      ) -> base::Optional<bool>
//      {
//        return base::nullopt;
//      }
//    ));
//  }
//
//  // on `plugin B` thread, while app is running
//  {
//    // `plugin B` includes "my_plug_points.hpp"
//
//    PlugPoint_FP1* plugPoint
//      = PlugPoint_FP1::GetInstance(FROM_HERE, ::basic::PlugPointName{"plugPoint"});
//    const base::Optional<bool> pluggedReturn = plugPoint->Run(int{1}, double{3.0});
//    if(UNLIKELY(pluggedReturn))
//    {
//      return pluggedReturn.value();
//    }
//  }
//
template<
  typename Tag
  , typename RetType
  , typename... ArgsType
>
class StrongPlugPoint<Tag, RetType(ArgsType...)>
{
 public:
  static_assert(basic::plug_point_internal::is_optional<RetType>::value,
                "Use StrongPlugPoint only if callback returns base::Optional.");

  using CallbackType
    = ::base::RepeatingCallback<RetType(ArgsType...)>;

  using Subscription
    = typename PlugPointStorage<RetType, ArgsType...>::Subscription;

  MUST_USE_RETURN_VALUE
  static StrongPlugPoint* GetInstance(
    const ::base::Location& location, const PlugPointName& name)
  {
    /// \note construction assumed to be thread-safe due to `base::NoDestructor`
    /// and constructed on first access
    static ::base::NoDestructor<StrongPlugPoint>
      instance(location, name);
    DCHECK_EQ(instance.get()->getName(), name)
      << "debug name must match real name";
    return instance.get();
  }

  MUST_USE_RETURN_VALUE
  const PlugPointName& getName() const NO_EXCEPTION
  {
    return value_.getName();
  }

  MUST_USE_RETURN_VALUE
  bool isActive() const NO_EXCEPTION
  {
    return value_.isActive();
  }

  void disable() NO_EXCEPTION
  {
    return value_.disable();
  }

  void enable() NO_EXCEPTION
  {
    return value_.enable();
  }

  template <typename... Args>
  MUST_USE_RETURN_VALUE
  RetType Run(Args&&... args) const NO_EXCEPTION
  {
    return value_.Run(FORWARD(args)...);
  }

  template <typename... Args>
  MUST_USE_RETURN_VALUE
  RetType operator()(Args&&... args) const NO_EXCEPTION
  {
    return Run(FORWARD(args)...);
  }

  MUST_USE_RETURN_VALUE
  std::unique_ptr<
    Subscription
  >
    setCallback(const CallbackType& callback) NO_EXCEPTION
  {
    return value_.setCallback(callback);
  }

  MUST_USE_RETURN_VALUE
  std::unique_ptr<
    Subscription
  >
    setCallback(CallbackType&& callback) NO_EXCEPTION
  {
    return value_.setCallback(RVALUE_CAST(callback));
  }

  void resetCallback() NO_EXCEPTION
  {
    value_.resetCallback();
  }

private:
  friend class ::base::NoDestructor<StrongPlugPoint>;

  // private constructor due to `base::NoDestructor`
  StrongPlugPoint() = delete;

  // private destructor due to `base::NoDestructor`
  ~StrongPlugPoint() = delete;

  // private constructor due to `base::NoDestructor`
  explicit StrongPlugPoint(
    const ::base::Location& location
    , const PlugPointName& name)
    : value_(location, name)
  {}

 private:
  PlugPointStorage<RetType, ArgsType...> value_;
};

// Storage with thread-safety checks
//
/// \note API must be fast (plug points may exist in any production code),
/// so do not use thread synchronization primitives (like `atomic`) here.
//
/// \note API allowed to call from multiple threads, but not concurrently.
/// Usually that means that you must setup all plug points
/// during app construction (or that you must pause app
/// before modification of plug points).
//
template<
  typename RetType
  , typename... ArgsType
>
class PlugPointNotifierStorage
{
  static_assert(std::is_same<RetType, void>::value,
                "Use PlugPointNotifierStorage only if callback returns void.");

 public:
  using CallbackType
    = ::base::RepeatingCallback<RetType(ArgsType...)>;

  using CBList
    = ::std::vector<CallbackType>;

  explicit PlugPointNotifierStorage(const ::base::Location& location, const PlugPointName& name)
    : name_(name)
    , location_(location)
    , is_active_(false)
    , priority_callbacks_()
  {
  }

  MUST_USE_RETURN_VALUE
  const PlugPointName& getName() const NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return name_;
  }

  MUST_USE_RETURN_VALUE
  bool isActive() const NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return is_active_;
  }

  void disable() NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    is_active_ = false;
  }

  void enable() NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    is_active_ = true;
  }

  template <typename... Args>
  void Notify(Args&&... args) NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    if(!isActive())
    {
      return;
    }

    for(size_t i = 0; i < priority_callbacks_.size(); i++)
    {
      CBList& cb_list = priority_callbacks_[i];
      for(CallbackType& task : cb_list)
      {
        task.Run(FORWARD(args)...);
      }
    }
  }

  template <typename... Args>
  void operator()(Args&&... args) NO_EXCEPTION
  {
    Notify(FORWARD(args)...);
  }

  void addCallback(PlugPointPriority priority
      , const CallbackType& callback) NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    CBList& cb_list = priority_callbacks_[static_cast<size_t>(priority)];
    cb_list.push_back(callback);
  }

  void addCallback(PlugPointPriority priority
      , CallbackType&& callback) NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    CBList& cb_list = priority_callbacks_[static_cast<size_t>(priority)];
    cb_list.push_back(RVALUE_CAST(callback));
  }

 private:
  PlugPointName name_;

  base::Location location_;

  bool is_active_;

  std::array<CBList, static_cast<size_t>(PlugPointPriority::TOTAL)> priority_callbacks_;

  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);

  DISALLOW_COPY_AND_ASSIGN(PlugPointNotifierStorage);
};

/// \note Registered callbacks can NOT be removed.
//
// Each plug point is unique object (uses `GetInstance`)
// and unique data type (uses type-tag similar to StrongAlias)
//
// USE CASE
//
// Multiple plugins can provide callback to process some file,
// and all registered callbacks must be run to process file.
// All callbacks return `void` because they do not affect original logic
// (i.e. they watch data, but do not change it).
//
// MOTIVATION
//
// API must be fast (plug points may exist in any production code),
// so do not use map<string, PlugPoint>.
//
// Use `GetInstance` for fast access to individual plug point.
//
// PERFORMANCE TIPS
//
// Re-use (cache) pointer returned by `GetInstance` for max. performance
// i.e. use `auto* fp = MyPlugPoint::GetInstance(); fp->...; fp->...;`
//
// Use `UNLIKELY` near `isActive()` for max. performance
// (we assume that usually most of plug points are disabled).
//
template<typename Tag, typename T>
class StrongPlugPointNotifier;

/// \note works only with callbacks that return void
//
// USAGE
//
//  // my_plug_points.hpp
//  using PlugPointNotifier_FP1
//    = ::basic::StrongPlugPointNotifier<
//          class PlugPointFP1Tag
//          , void(int, double)
//        >;
//
//  // on `plugin A` thread, before app started
//  {
//    // `plugin A` includes "my_plug_points.hpp"
//
//    PlugPointNotifier_FP1* plugPoint
//      = PlugPointNotifier_FP1::GetInstance(FROM_HERE, ::basic::PlugPointName{"plugPoint"});
//
//    plugPoint->enable();
//
//    plugPoint->addCallback(basic::PlugPointPriority::High,
//      base::BindRepeating(
//        [
//        ](
//          int a
//          , double b
//        ) -> void
//        {
//          return;
//        }
//      ));
//
//    plugPoint->addCallback(basic::PlugPointPriority::Lowest,
//      base::BindRepeating(
//        [
//        ](
//          int a
//          , double b
//        ) -> void
//        {
//          return;
//        }
//      ));
//  }
//
//  // on `plugin B` thread, while app is running
//  {
//    // `plugin B` includes "my_plug_points.hpp"
//
//    PlugPointNotifier_FP1* plugPoint
//      = PlugPointNotifier_FP1::GetInstance(FROM_HERE, ::basic::PlugPointName{"plugPoint"});
//    plugPoint->Notify(int{1}, double{3.0});
//  }
//
template<
  typename Tag
  , typename RetType
  , typename... ArgsType
>
class StrongPlugPointNotifier<Tag, RetType(ArgsType...)>
{
  static_assert(std::is_same<RetType, void>::value,
                "Use StrongPlugPointNotifier only if callback returns void.");

 public:
  using CallbackType
    = ::base::RepeatingCallback<RetType(ArgsType...)>;

  using CBList
    = ::base::CallbackList<
        RetType(ArgsType...)
      >;

  MUST_USE_RETURN_VALUE
  static StrongPlugPointNotifier* GetInstance(
    const ::base::Location& location, const PlugPointName& name)
  {
    /// \note construction assumed to be thread-safe due to `base::NoDestructor`
    /// and constructed on first access
    static ::base::NoDestructor<StrongPlugPointNotifier>
      instance(location, name);
    DCHECK_EQ(instance.get()->getName(), name);
    return instance.get();
  }

  MUST_USE_RETURN_VALUE
  const PlugPointName& getName() const NO_EXCEPTION
  {
    return value_.getName();
  }

  MUST_USE_RETURN_VALUE
  bool isActive() const NO_EXCEPTION
  {
    return value_.isActive();
  }

  void disable() NO_EXCEPTION
  {
    return value_.disable();
  }

  void enable() NO_EXCEPTION
  {
    return value_.enable();
  }

  template <typename... Args>
  void Notify(Args&&... args) NO_EXCEPTION
  {
    value_.Notify(FORWARD(args)...);
  }

  template <typename... Args>
  void operator()(Args&&... args) NO_EXCEPTION
  {
    Notify(FORWARD(args)...);
  }

  void addCallback(PlugPointPriority priority
      , const CallbackType& callback) NO_EXCEPTION
  {
    value_.addCallback(priority, callback);
  }

  void addCallback(PlugPointPriority priority
      , CallbackType&& callback) NO_EXCEPTION
  {
    value_.addCallback(priority, RVALUE_CAST(callback));
  }

private:
  friend class ::base::NoDestructor<StrongPlugPointNotifier>;

  // private constructor due to `base::NoDestructor`
  StrongPlugPointNotifier() = delete;

  // private destructor due to `base::NoDestructor`
  ~StrongPlugPointNotifier() = delete;

  // private constructor due to `base::NoDestructor`
  explicit StrongPlugPointNotifier(
    const ::base::Location& location
    , const PlugPointName& name)
    : value_(location, name)
  {}

 private:
  PlugPointNotifierStorage<RetType, ArgsType...> value_;
};

namespace internal {

template <typename CallbackType>
class CallbackListRunnerBase {
 public:
  // Use subscription to remove registered callbacks
  class Subscription {
   public:
    Subscription(CallbackListRunnerBase<CallbackType>* list,
                 typename std::list<CallbackType>::iterator iter)
        : list_(list),
          iter_(iter) {
    }

    ~Subscription() {
      if (list_->active_iterator_count_) {
        iter_->Reset();
      } else {
        list_->callbacks_.erase(iter_);
        if (!list_->removal_callback_.is_null())
          list_->removal_callback_.Run();
      }
    }

   private:
    CallbackListRunnerBase<CallbackType>* list_;
    typename std::list<CallbackType>::iterator iter_;

    DISALLOW_COPY_AND_ASSIGN(Subscription);
  };

  // Add a callback to the list. The callback will remain registered until the
  // returned Subscription is destroyed, which must occur before the
  // CallbackListRunner is destroyed.
  std::unique_ptr<Subscription> Add(const CallbackType& cb) WARN_UNUSED_RESULT {
    DCHECK(!cb.is_null());
    return std::make_unique<Subscription>(
        this, callbacks_.insert(callbacks_.end(), cb));
  }

  // Sets a callback which will be run when a subscription list is changed.
  void set_removal_callback(const ::base::RepeatingClosure& callback) {
    removal_callback_ = callback;
  }

  // Returns true if there are no subscriptions. This is only valid to call when
  // not looping through the list.
  bool empty() {
    DCHECK_EQ(0, active_iterator_count_);
    return callbacks_.empty();
  }

 protected:
  // An iterator class that can be used to access the list of callbacks.
  class Iterator {
   public:
    explicit Iterator(CallbackListRunnerBase<CallbackType>* list)
        : list_(list),
          list_iter_(list_->callbacks_.begin()) {
      ++list_->active_iterator_count_;
    }

    Iterator(const Iterator& iter)
        : list_(iter.list_),
          list_iter_(iter.list_iter_) {
      ++list_->active_iterator_count_;
    }

    ~Iterator() {
      if (list_ && --list_->active_iterator_count_ == 0) {
        list_->Compact();
      }
    }

    CallbackType* GetNext() {
      while ((list_iter_ != list_->callbacks_.end()) && list_iter_->is_null())
        ++list_iter_;

      CallbackType* cb = nullptr;
      if (list_iter_ != list_->callbacks_.end()) {
        cb = &(*list_iter_);
        ++list_iter_;
      }
      return cb;
    }

   private:
    CallbackListRunnerBase<CallbackType>* list_;
    typename std::list<CallbackType>::iterator list_iter_;
  };

  CallbackListRunnerBase() : active_iterator_count_(0) {}

  ~CallbackListRunnerBase() {
    DCHECK_EQ(0, active_iterator_count_);
    DCHECK_EQ(0U, callbacks_.size());
  }

  // Returns an instance of a CallbackListRunnerBase::Iterator which can be used
  // to run callbacks.
  Iterator GetIterator() {
    return Iterator(this);
  }

  // Compact the list: remove any entries which were nulled out during
  // iteration.
  void Compact() {
    auto it = callbacks_.begin();
    bool updated = false;
    while (it != callbacks_.end()) {
      if ((*it).is_null()) {
        updated = true;
        it = callbacks_.erase(it);
      } else {
        ++it;
      }
    }

    if (updated && !removal_callback_.is_null())
      removal_callback_.Run();
  }

 private:
  std::list<CallbackType> callbacks_;
  int active_iterator_count_;
  ::base::RepeatingClosure removal_callback_;

  DISALLOW_COPY_AND_ASSIGN(CallbackListRunnerBase);
};

}  // namespace internal

template <typename Sig> class CallbackListRunner;

template <typename RetType, typename... Args>
class CallbackListRunner<RetType(Args...)>
    : public internal::CallbackListRunnerBase<::base::RepeatingCallback<RetType(Args...)>> {
 public:
  static_assert(basic::plug_point_internal::is_optional<RetType>::value,
                "Use CallbackListRunner only if callback returns base::Optional.");

  using CallbackType
    = ::base::RepeatingCallback<RetType(Args...)>;

  CallbackListRunner() = default;

  /// \note Returns result of first iterated callback that has value
  /// i.e. returns if result of iterated callback not `base::nullopt`.
  /// If all callbacks resulted in `base::nullopt`, than returns `base::nullopt`.
  template <typename... RunArgs>
  RetType RunUntilReturnValueOrNullopt(RunArgs&&... args) {
    auto it = this->GetIterator();
    CallbackType* cb;
    while ((cb = it.GetNext()) != nullptr) {
      /// \note patched with FORWARD
      auto optReturn = cb->Run(FORWARD(args)...);
      if(optReturn)
      {
        // returns if result of iterated callback not `base::nullopt`.
        return optReturn;
      }
    }
    return base::nullopt;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(CallbackListRunner);
};

// Storage with thread-safety checks
//
/// \note API must be fast (plug points may exist in any production code),
/// so do not use thread synchronization primitives (like `atomic`) here.
//
/// \note API allowed to call from multiple threads, but not concurrently.
/// Usually that means that you must setup all plug points
/// during app construction (or that you must pause app
/// before modification of plug points).
//
template<
  typename RetType
  , typename... ArgsType
>
class PlugPointRunnerStorage
{
  static_assert(basic::plug_point_internal::is_optional<RetType>::value,
                "Use PlugPointRunnerStorage only if callback returns base::Optional.");

 public:
  using CallbackType
    = ::base::RepeatingCallback<RetType(ArgsType...)>;

  using CBList
    = ::basic::CallbackListRunner<
        RetType(ArgsType...)
      >;

  using Subscription
    = typename CBList::Subscription;

  explicit PlugPointRunnerStorage(const ::base::Location& location, const PlugPointName& name)
    : name_(name)
    , location_(location)
    , is_active_(false)
    , priority_callbacks_()
  {
  }

  MUST_USE_RETURN_VALUE
  const PlugPointName& getName() const NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return name_;
  }

  MUST_USE_RETURN_VALUE
  bool isActive() const NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return is_active_;
  }

  void disable() NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    is_active_ = false;
  }

  void enable() NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    is_active_ = true;
  }

  template <typename... Args>
  MUST_USE_RETURN_VALUE
  RetType RunUntilReturnValueOrNullopt(Args&&... args) NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    if(!isActive())
    {
      return base::nullopt;
    }

    for(size_t i = 0; i < priority_callbacks_.size(); i++)
    {
      RetType result
        = priority_callbacks_[i].RunUntilReturnValueOrNullopt(FORWARD(args)...);

      if(result)
      {
        // returns if result of iterated callback not `base::nullopt`.
        return result;
      }
    }

    return base::nullopt;
  }

  template <typename... Args>
  MUST_USE_RETURN_VALUE
  RetType operator()(Args&&... args) NO_EXCEPTION
  {
    return RunUntilReturnValueOrNullopt(FORWARD(args)...);
  }

  std::unique_ptr<
    Subscription
  >
    addCallback(PlugPointPriority priority
      , const CallbackType& callback) NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return priority_callbacks_[static_cast<size_t>(priority)].Add(callback);
  }

  std::unique_ptr<
    Subscription
  >
    addCallback(PlugPointPriority priority
      , CallbackType&& callback) NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return priority_callbacks_[static_cast<size_t>(priority)].Add(RVALUE_CAST(callback));
  }

 private:
  PlugPointName name_;

  base::Location location_;

  bool is_active_;

  std::array<CBList, static_cast<size_t>(PlugPointPriority::TOTAL)> priority_callbacks_;

  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);

  DISALLOW_COPY_AND_ASSIGN(PlugPointRunnerStorage);
};

// Each plug point is unique object (uses `GetInstance`)
// and unique data type (uses type-tag similar to StrongAlias)
//
// USE CASE
//
// Multiple plugins can provide callback to process some file,
// and all registered callbacks must be run to process file.
// All callbacks return NOT `void` result because they DO affect original logic
// (i.e. they watch data AND change it).
//
// MOTIVATION
//
// API must be fast (plug points may exist in any production code),
// so do not use map<string, PlugPoint>.
//
// Use `GetInstance` for fast access to individual plug point.
//
// PERFORMANCE TIPS
//
// Re-use (cache) pointer returned by `GetInstance` for max. performance
// i.e. use `auto* fp = MyPlugPoint::GetInstance(); fp->...; fp->...;`
//
// Use `UNLIKELY` near `isActive()` for max. performance
// (we assume that usually most of plug points are disabled).
//
template<typename Tag, typename T>
class StrongPlugPointRunner;

/// \note works only with callbacks that return base::Optional<T>
//
// USAGE
//
//  // my_plug_points.hpp
//  using PlugPointRunner_FP1
//    = ::basic::StrongPlugPointRunner<
//          class PlugPointFP1Tag
//          , base::Optional<bool>(int, double)
//        >;
//
//  std::vector<
//    std::unique_ptr<
//      PlugPointRunner_FP1::Subscription
//    >
//  > runner_subscriptions;
//
//  // on `plugin A` thread, before app started
//  {
//    // `plugin A` includes "my_plug_points.hpp"
//
//    PlugPointRunner_FP1* plugPoint
//      = PlugPointRunner_FP1::GetInstance(FROM_HERE, ::basic::PlugPointName{"plugPoint"});
//
//    plugPoint->enable();
//
//    runner_subscriptions.push_back(plugPoint->addCallback(basic::PlugPointPriority::High
//      , base::BindRepeating(
//        [
//        ](
//          int a
//          , double b
//        ) -> base::Optional<bool>
//        {
//          return base::nullopt;
//        }
//      )));
//
//    runner_subscriptions.push_back(plugPoint->addCallback(basic::PlugPointPriority::Lowest
//      , base::BindRepeating(
//        [
//        ](
//          int a
//          , double b
//        ) -> base::Optional<bool>
//        {
//          return base::nullopt;
//        }
//      )));
//  }
//
//  // on `plugin B` thread, while app is running
//  {
//    // `plugin B` includes "my_plug_points.hpp"
//
//    PlugPointRunner_FP1* plugPoint
//      = PlugPointRunner_FP1::GetInstance(FROM_HERE, ::basic::PlugPointName{"plugPoint"});
//    const base::Optional<bool> pluggedReturn = plugPoint->RunUntilReturnValueOrNullopt(int{1}, double{3.0});
//    if(UNLIKELY(pluggedReturn))
//    {
//      return pluggedReturn.value();
//    }
//  }
//
template<
  typename Tag
  , typename RetType
  , typename... ArgsType
>
class StrongPlugPointRunner<Tag, RetType(ArgsType...)>
{
  static_assert(basic::plug_point_internal::is_optional<RetType>::value,
                "Use StrongPlugPointRunner only if callback returns base::Optional.");

 public:
  using CallbackType
    = ::base::RepeatingCallback<RetType(ArgsType...)>;

  using CBList
    = ::basic::CallbackListRunner<
        RetType(ArgsType...)
      >;

  using Subscription
    = typename CBList::Subscription;

  MUST_USE_RETURN_VALUE
  static StrongPlugPointRunner* GetInstance(
    const ::base::Location& location, const PlugPointName& name)
  {
    /// \note construction assumed to be thread-safe due to `base::NoDestructor`
    /// and constructed on first access
    static ::base::NoDestructor<StrongPlugPointRunner>
      instance(location, name);
    DCHECK_EQ(instance.get()->getName(), name);
    return instance.get();
  }

  MUST_USE_RETURN_VALUE
  const PlugPointName& getName() const NO_EXCEPTION
  {
    return value_.getName();
  }

  MUST_USE_RETURN_VALUE
  bool isActive() const NO_EXCEPTION
  {
    return value_.isActive();
  }

  void disable() NO_EXCEPTION
  {
    return value_.disable();
  }

  void enable() NO_EXCEPTION
  {
    return value_.enable();
  }

  template <typename... Args>
  MUST_USE_RETURN_VALUE
  RetType RunUntilReturnValueOrNullopt(Args&&... args) NO_EXCEPTION
  {
    return value_.RunUntilReturnValueOrNullopt(FORWARD(args)...);
  }

  template <typename... Args>
  MUST_USE_RETURN_VALUE
  RetType operator()(Args&&... args) NO_EXCEPTION
  {
    return RunUntilReturnValueOrNullopt(FORWARD(args)...);
  }

  std::unique_ptr<
    Subscription
  >
    addCallback(PlugPointPriority priority
      , const CallbackType& callback) NO_EXCEPTION
  {
    return value_.addCallback(priority, callback);
  }

  std::unique_ptr<
    Subscription
  >
    addCallback(PlugPointPriority priority
      , CallbackType&& callback) NO_EXCEPTION
  {
    return value_.addCallback(priority, RVALUE_CAST(callback));
  }

private:
  friend class ::base::NoDestructor<StrongPlugPointRunner>;

  // private constructor due to `base::NoDestructor`
  StrongPlugPointRunner() = delete;

  // private destructor due to `base::NoDestructor`
  ~StrongPlugPointRunner() = delete;

  // private constructor due to `base::NoDestructor`
  explicit StrongPlugPointRunner(
    const ::base::Location& location
    , const PlugPointName& name)
    : value_(location, name)
  {}

 private:
  PlugPointRunnerStorage<RetType, ArgsType...> value_;
};

} // namespace basic
