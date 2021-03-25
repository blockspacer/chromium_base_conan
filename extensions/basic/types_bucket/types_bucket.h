/**
 * Based on code from entt v3.4.0
 * See https://github.com/skypjack/entt/blob/v3.4.0/src/entt/entity/registry.hpp
 * Made modifications to fully access `std::vector<variable_data> vars{};`
 * and perform thread-safety validations.
**/

#pragma once

#include <base/macros.h>
#include <base/logging.h>
#include <base/location.h>
#include <base/optional.h>
#include <base/sequenced_task_runner.h>
#include <base/threading/thread_checker.h>
#include <base/memory/weak_ptr.h>
#include <base/memory/ref_counted.h>
#include <base/memory/scoped_refptr.h>
#include <basic/rvalue_cast.h>
#include <base/threading/thread_collision_warner.h>

#include <vector>
#include <string>
#include <atomic>

namespace base {

class SingleThreadTaskRunner;

template <typename T>
struct DefaultSingletonTraits;

} // namespace base

namespace basic {

// `reset_or_create_var` works only with `base::Optional` for now
namespace unsafe_context_internal {
template <typename T>
struct is_optional : std::false_type {};

template <typename T>
struct is_optional<base::Optional<T>> : std::true_type {};
} // namespace unsafe_context_internal

using idType = std::uint32_t;

// Stores vector of arbitrary typed objects,
// each object can be found by its type (using typeIndex).
/// \note API is not thread-safe
// Inspired by entt context, see for details:
// https://github.com/skypjack/entt/wiki/Crash-Course:-entity-component-system
class TypesBucket
{
 public:
  // Returns the sequential identifier of a given type.
  template<typename Type, typename = void>
  idType typeIndex() NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    // `static` because unique per each `Type`
    static const idType value = typeCounter_++;
    return value;
  }

  TypesBucket();

  ~TypesBucket();

  TypesBucket(
    TypesBucket&& other)
    : TypesBucket()
    {
      vars_ = RVALUE_CAST(other.vars_);

      typeCounter_ = RVALUE_CAST(other.typeCounter_);
    }

  // Move assignment operator
  //
  // MOTIVATION
  //
  // To use type as ECS component
  // it must be `move-constructible` and `move-assignable`
  TypesBucket& operator=(TypesBucket&& rhs)
  {
    if (this != &rhs)
    {
      vars_ = RVALUE_CAST(rhs.vars_);

      typeCounter_ = RVALUE_CAST(rhs.typeCounter_);
    }

    return *this;
  }

  struct variable_data {
    idType type_id;
    std::unique_ptr<void, void(*)(void *)> value;
  };

  /**
   * @brief Binds an object to the context of the registry.
   *
   * A new instance of the given type is created and initialized
   * with the arguments provided.
   *
   * @tparam Type Type of object to set.
   * @tparam Args Types of arguments to use to construct the object.
   * @param args Parameters to use to initialize the value.
   * @return A reference to the newly created object.
   */
  template<typename Type, typename... Args>
  Type & set(Args &&... args)
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    DCHECK(!try_ctx<Type>());

    vars_.push_back(
      variable_data
      {
        typeIndex<Type>()
        , { new Type{FORWARD(args)...}
            // custom deleter for `unique_ptr`
            , [](void *instance)
              {
                delete static_cast<Type*>(instance);
              }
          }
      }
    );

    return *static_cast<Type*>(vars_.back().value.get());
  }

  /**
   * @brief Unsets a context variable if it exists.
   * @tparam Type Type of object to set.
   */
  template<typename Type>
  void unset()
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    vars_.erase(
      std::remove_if(
        vars_.begin()
        , vars_.end()
        , [this](auto &&var) {
            return var.type_id == typeIndex<Type>();
          }
      )
      , vars_.end()
    );
  }

  /**
   * @brief Binds an object to the context of the registry.
   *
   * In case the context doesn't contain the given object, the parameters
   * provided are used to construct it.
   *
   * @tparam Type Type of object to set.
   * @tparam Args Types of arguments to use to construct the object.
   * @param args Parameters to use to initialize the object.
   * @return A reference to the object in the context of the registry.
   */
  template<typename Type, typename... Args>
  MUST_USE_RETURN_VALUE
  Type & ctx_or_set(Args &&... args)
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    auto *value = try_ctx<Type>();
    return value
      ? *value
      : set<Type>(FORWARD(args)...);
  }

  /**
   * @brief Unsets a context variable if it exists, than binds an object
   * to the context of the registry.
   * @tparam Type Type of object to set.
   * @tparam Args Types of arguments to use to construct the object.
   * @param args Parameters to use to initialize the value.
   * @return A reference to the newly created object.
   */
  template<typename Type, typename... Args>
  MUST_USE_RETURN_VALUE
  Type & reset(Args &&... args)
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    if(try_ctx<Type>()) {
      unset<Type>();
    }

    return set<Type>(FORWARD(args)...);
  }

  /**
   * @brief Returns a pointer to an object in the context of the registry.
   * @tparam Type Type of object to get.
   * @return A pointer to the object if it exists in the context of the
   * registry, a null pointer otherwise.
   */
  template<typename Type>
  MUST_USE_RETURN_VALUE
  Type* try_ctx()
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    auto it = std::find_if(
      vars_.cbegin()
      , vars_.cend()
      , [this](auto &&var)
        {
          return var.type_id == typeIndex<Type>();
        });
    return it == vars_.cend()
      ? nullptr
      : static_cast<Type*>(it->value.get());
  }

  /**
   * @brief Returns a reference to an object in the context of the registry.
   *
   * @warning
   * Attempting to get a context variable that doesn't exist results in
   * undefined behavior.<br/>
   * An assertion will abort the execution at runtime in debug mode in case of
   * invalid requests.
   *
   * @tparam Type Type of object to get.
   * @return A valid reference to the object in the context of the registry.
   */
  template<typename Type>
  MUST_USE_RETURN_VALUE
  Type& ctx()
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    auto *instance = try_ctx<Type>();
    DCHECK(instance);
    return *instance;
  }

  /**
   * @brief Visits a registry and returns the types for its context variables.
   *
   * The signature of the function should be equivalent to the following:
   *
   * @code{.cpp}
   * void(const id_type);
   * @endcode
   *
   * Returned identifiers are those of the context variables currently set.
   *
   * @sa type_info
   *
   * @warning
   * It's not specified whether a context variable created during the visit is
   * returned or not to the caller.
   *
   * @tparam Func Type of the function object to invoke.
   * @param func A valid function object.
   */
  template<typename Func>
  void ctx(Func func) const
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    for(auto pos = vars_.size(); pos; --pos) {
      func(vars_[pos-1].type_id);
    }
  }

  std::vector<variable_data>& vars()
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return vars_;
  }

  const std::vector<variable_data>& vars() const
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return vars_;
  }

  size_t size() const
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return vars_.size();
  }

  bool empty() const
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return vars_.empty();
  }

 private:
  // per-sequence counter for thread-safety reasons
  idType typeCounter_{};

  // Stores objects in the context of the registry.
  std::vector<variable_data> vars_{};

  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);

  DISALLOW_COPY_AND_ASSIGN(TypesBucket);
};

} // namespace basic
