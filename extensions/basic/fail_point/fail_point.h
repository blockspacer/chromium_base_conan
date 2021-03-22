#pragma once

#include <base/macros.h>
#include <base/logging.h>
#include <base/values.h>
#include <base/sequence_checker.h>
#include <base/threading/thread_collision_warner.h>
#include <base/location.h>
#include <base/no_destructor.h>
#include <basic/rvalue_cast.h>
#include <base/callback_list.h>

#include <basic/strong_types/strong_string.h>

#include <functional>
#include <string>

// USAGE
//
// STRONG_FAIL_POINT(FailPoint_RecievedData);
//
#define STRONG_FAIL_POINT(VAR) \
  using VAR \
    = ::basic::StrongFailPoint< \
          class FP_##VAR##Tag \
        >

// Build fail point name
#define FAIL_POINT(VAR) \
  FP_##VAR

// Enables fail point if command line has switch with provided name
//
// USAGE
//
// #include "basic/fail_point/fail_point.h"
// #include "base/command_line.h"
// ENABLE_FAIL_POINT_IF_HAS_SWITCH(
//   my_ns::FailPoint_RecievedData, switches::kMyFailPoint);
//
#define ENABLE_FAIL_POINT_IF_HAS_SWITCH(VAR, FLAG_NAME)                        \
  [&](){                                                                       \
    const base::CommandLine* internal_command_line                             \
      = base::CommandLine::ForCurrentProcess();                                \
    if (internal_command_line->HasSwitch(FLAG_NAME)) {                         \
      VAR->setFailure();                                                       \
      VAR->enable();                                                           \
    }                                                                          \
  }()

// USAGE
//
// STRONG_FAIL_POINT(FP_AcceptedConnectionAborted);
// // class member var.
// FP_AcceptedConnectionAborted* fp_AcceptedConnectionAborted_ = nullptr;
// // in class constructor
// fp_AcceptedConnectionAborted_ = FAIL_POINT_INSTANCE(FP_AcceptedConnectionAborted);
//
#define FAIL_POINT_INSTANCE(...) \
    __VA_ARGS__::GetInstance(FROM_HERE, \
      ::basic::FailPointName{STRINGIFY_VA_ARG(__VA_ARGS__)})

/// \note Avoid `ASSIGN_FAIL_POINT`,
/// prefer to cache pointer using `FAIL_POINT_INSTANCE`
//
// USAGE
//
// ASSIGN_FAIL_POINT(failPoint, FailPoint_FP1);
// if(UNLIKELY(failPoint->checkFail()))
// {
//   DCHECK_EQ(failPoint->data().FindIntPath("int_key").value(), 1234);
// }
#define ASSIGN_FAIL_POINT(VAR, ...) \
  __VA_ARGS__* VAR = FAIL_POINT_INSTANCE(__VA_ARGS__)

// USAGE
//
// ASSIGN_FAIL_POINT(failPointPtr, flexnet::ws::FailPoint_RecievedData);
// IF_FAIL_POINT(failPointPtr) {
//   return {"something"}
// };
#define IF_FAIL_POINT(failPoint) \
  if(UNLIKELY(failPoint->checkFail()))

// USAGE
//
// ASSIGN_FAIL_POINT(failPointPtr, flexnet::ws::FailPoint_RecievedData);
// RETURN_IF_FAIL_POINT_FAIL(failPointPtr, REFERENCED(message));
#define RETURN_IF_FAIL_POINT(failPoint, ...) \
  do {                                       \
    IF_FAIL_POINT(failPoint->checkFail())    \
    {                                        \
      return;                                \
    }                                        \
  } while (0)

// USAGE
//
// ASSIGN_FAIL_POINT(failPointPtr, flexnet::ws::FailPoint_RecievedData);
// SET_IF_FAIL_POINT(failPointPtr, forceClosing = true);
#define SET_IF_FAIL_POINT(failPoint, ...) \
  do {                                    \
    if(UNLIKELY(failPoint->checkFail()))  \
    {                                     \
      __VA_ARGS__;                        \
    }                                     \
  } while (0)

// A FailPoint is a hook mechanism allowing testing behavior to occur
// at prearranged execution points.
//
// Use FailPoint for fault injection (to conditionally cause system failure).
//
// FailsPoint-s can be activated and deactivated, and configured to hold data.
//
// EXAMPLE
//
// // my_fail_points.hpp
// using FailPoint_FP1 = ::basic::StrongFailPoint<class FailPointFP1Tag>;
//
// // on `plugin A` thread, before app started
// {
//   // `plugin A` includes "my_fail_points.hpp"
//
//   FailPoint_FP1* failPoint
//     = FailPoint_FP1::GetInstance(FROM_HERE, ::basic::FailPointName{"failPoint"});
//
//   failPoint->setFailure();
//
//   failPoint->enable();
//
//   ::base::Value val1(::base::Value::Type::DICTIONARY);
//   val1.SetKey("bool_key", ::base::Value{false});
//   val1.SetKey("int_key", ::base::Value{1234});
//   val1.SetKey("double_key", ::base::Value{12.34567});
//   val1.SetKey("string_key", ::base::Value{"str"});
//   failPoint->setData(val1);
// }
//
// // on `plugin B` thread, while app is running
// {
//   // `plugin B` includes "my_fail_points.hpp"
//
//   FailPoint_FP1* failPoint
//     = FailPoint_FP1::GetInstance(FROM_HERE, ::basic::FailPointName{"failPoint"});
//   if(UNLIKELY(failPoint->checkFail()))
//   {
//     DCHECK_EQ(failPoint->data().FindIntPath("int_key").value(), 1234);
//   }
// }
//
namespace basic {

// can be used for debug purposes
STRONGLY_TYPED_STRING(FailPointName);

// Storage with thread-safety checks
//
/// \note API must be fast (fail points may exist in any production code),
/// so do not use thread synchronization primitives (like `atomic`) here.
//
/// \note API allowed to call from multiple threads, but not concurrently.
/// Usually that means that you must setup all fail points
/// during app construction (or that you must pause app
/// before modification of fail points).
//
class FailPointStorage
{
 public:
  explicit FailPointStorage(const ::base::Location& location, const FailPointName& name)
    : name_(name)
    , location_(location)
    , is_active_(false)
    , has_failure_(false)
    , data_(::base::Value::Type::DICTIONARY)
  {
  }

  MUST_USE_RETURN_VALUE
  const FailPointName& getName() const NO_EXCEPTION
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

  void setFailure() NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    has_failure_ = true;
  }

  void unsetFailure() NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    has_failure_ = false;
  }

  // Each fail point can have arbitrary data (::base::Value) associated with it.
  MUST_USE_RETURN_VALUE
  const ::base::Value& data() const NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return data_;
  }

  void setData(const ::base::Value& data) NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    DCHECK_EQ(data.type(), ::base::Value::Type::DICTIONARY);
    data_ = data.Clone();
  }

  void setData(::base::Value&& data) NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    DCHECK_EQ(data.type(), ::base::Value::Type::DICTIONARY);
    data_ = RVALUE_CAST(data);
  }

  void clearData() NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    data_ = base::Value(::base::Value::Type::DICTIONARY);
  }

  MUST_USE_RETURN_VALUE
  bool checkFail() const NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return has_failure_ && is_active_;
  }

 private:
  MUST_USE_RETURN_VALUE
  bool hasFailure() const NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return has_failure_;
  }

 private:
  FailPointName name_;

  base::Location location_;

  bool is_active_;

  bool has_failure_;

  ::base::Value data_;

  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);

  DISALLOW_COPY_AND_ASSIGN(FailPointStorage);
};

// Each fail point is unique object (uses `GetInstance`)
// and unique data type (uses type-tag similar to StrongAlias)
//
// MOTIVATION
//
// API must be fast (fail points may exist in any production code),
// so do not use map<string, FailPoint>.
//
// Use `GetInstance` for fast access to individual fail point.
//
// PERFORMANCE TIPS
//
// Re-use (cache) pointer returned by `GetInstance` for max. performance
// i.e. use `auto* fp = MyFailPoint::GetInstance(); fp->...; fp->...;`
//
// Use `UNLIKELY` near `checkFail()` for max. performance
// (we assume that usually most of fail points are disabled).
//
template<
  typename Tag
>
class StrongFailPoint
{
 public:
  MUST_USE_RETURN_VALUE
  static StrongFailPoint<Tag>* GetInstance(
    const ::base::Location& location, const FailPointName& name)
  {
    /// \note construction assumed to be thread-safe due to `base::NoDestructor`
    /// and constructed on first access
    static ::base::NoDestructor<StrongFailPoint<Tag>>
      instance(location, name);
    DCHECK_EQ(instance.get()->getName(), name)
      << "debug name must match real name";
    return instance.get();
  }

  MUST_USE_RETURN_VALUE
  const FailPointName& getName() const NO_EXCEPTION
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

  auto setFailure() NO_EXCEPTION
  {
    return value_.setFailure();
  }

  auto unsetFailure() NO_EXCEPTION
  {
    return value_.unsetFailure();
  }

  MUST_USE_RETURN_VALUE
  const ::base::Value& data() const NO_EXCEPTION
  {
    return value_.data();
  }

  void setData(const ::base::Value& data) NO_EXCEPTION
  {
    return value_.setData(data);
  }

  void setData(::base::Value&& data) NO_EXCEPTION
  {
    return value_.setData(RVALUE_CAST(data));
  }

  void clearData() NO_EXCEPTION
  {
    return value_.clearData();
  }

  MUST_USE_RETURN_VALUE
  bool checkFail() const NO_EXCEPTION
  {
    return value_.checkFail();
  }

private:
  friend class ::base::NoDestructor<StrongFailPoint<Tag>>;

  // private constructor due to `base::NoDestructor`
  StrongFailPoint() = delete;

  // private destructor due to `base::NoDestructor`
  ~StrongFailPoint() = delete;

  // private constructor due to `base::NoDestructor`
  explicit StrongFailPoint(
    const ::base::Location& location
    , const FailPointName& name)
    : value_(location, name)
  {}

 private:
  FailPointStorage value_;
};

} // namespace basic
