// Copyright (C) 2016-2020 Jonathan M?ller <jonathanmueller.dev@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#pragma once

#include <base/logging.h>
#include <base/check.h>

#include <new>
#include <type_traits>
#include <utility>

// EXAMPLE
//
// bool read_str_better(std::istream& in, basic::output_parameter<std::string> out)
// {
//     std::string result = ...;
//     auto empty = result.empty();    // we need to query here, because after move it might be empty
//     out        = std::move(result);
//     return !empty;
// }
//
// {
//     std::istringstream in("hello world");
//     std::string        str;
//     auto res = read_str_better(in, basic::out(str));
//     std::cout << res << ' ' << str << '\n';
// }
//
namespace basic
{

// A tiny wrapper to create an object without constructing it yet.
//
// This is useful if you have a type that is default constructible,
// but can't be initialized properly - yet.
// It works especially well with [basic::output_parameter]().
//
// It has two states:
// Either it is *initialized* in which case you can get its value,
// or it is *un-initialized* in which case you cannot get its value.
// All objects start out un-initialized.
// For consistency with [basic::basic_optional]() it provides a similar interface,
// yet it is not as flexible and does not allow to reset it to the uninitialized state,
// once initialized.
//
template <typename T>
class deferred_construction
{
public:
  using value_type = T;

  //=== constructors/assignment/destructor ===//
  /// Default constructor.
  /// \effects Creates it in the un-initialized state.
  deferred_construction() noexcept : initialized_(false) {}

  /// Copy constructor:
  /// \effects If `other` is un-initialized, it will be un-initialized as well.
  /// If `other` is initialized, it will copy the stored value.
  /// \throws Anything thrown by the copy constructor of `value_type` if `other` is initialized.
  deferred_construction(const deferred_construction& other) : initialized_(other.initialized_)
  {
    if (initialized_)
        ::new (as_void()) value_type(other.value());
  }

  /// Move constructor:
  /// \effects If `other` is un-initialized, it will be un-initialized as well.
  /// If `other` is initialized, it will copy the stored value.
  /// \throws Anything thrown by the move constructor of `value_type` if `other` is initialized.
  /// \notes `other` will still be initialized after the move operation,
  /// it is just in a moved-from state.
  deferred_construction(deferred_construction&& other) noexcept(
      std::is_nothrow_move_constructible<value_type>::value)
  : initialized_(other.initialized_)
  {
    if (initialized_)
        ::new (as_void()) value_type(std::move(other).value());
  }

  /// \notes You cannot construct it from the type directly.
  /// If you are able to do that, there is no need to use `defer_construction`!
  deferred_construction(value_type) = delete;

  /// \effects If it is initialized, it will destroy the value.
  /// Otherwise it has no effect.
  ~deferred_construction() noexcept
  {
    if (initialized_)
        value().~value_type();
  }

  /// \notes You cannot copy or move assign it.
  /// This is a deliberate design decision to guarantee,
  /// that an initialized object stays initialized, no matter what.
  deferred_construction& operator=(deferred_construction) = delete;

  /// \effects Same as `emplace(std::forward<U>(u))`.
  /// \requires `value_type` must be constructible from `U`.
  /// \notes You must not use this function to actually "assign" the value,
  /// like `emplace()`, the object must not be initialized.
  /// \synopsis_return deferred_construction&
  template <typename U>
  auto operator=(U&& u) ->
    typename std::enable_if<std::is_constructible<T, decltype(std::forward<U>(u))>::value,
                            deferred_construction&>::type
  {
    emplace(std::forward<U>(u));
    return *this;
  }

  //=== modifiers ===//
  /// \effects Initializes the object with the `value_type` constructed from `args`.
  /// \requires `has_value() == false`.
  /// \throws Anything thrown by the chosen constructor of `value_type`.
  /// \notes You must only call this function once,
  /// after the object has been initialized,
  /// you can use `value()` to assign to it.
  /// \output_section Modifiers
  template <typename... Args>
  void emplace(Args&&... args)
  {
    DCHECK(!has_value());
    ::new (as_void()) value_type(std::forward<Args>(args)...);
    initialized_ = true;
  }

  //=== observers ===//
  /// \returns `true` if the object is initialized, `false` otherwise.
  /// \output_section Observers
  bool has_value() const noexcept
  {
    return initialized_;
  }

  /// \returns The same as `has_value()`.
  explicit operator bool() const noexcept
  {
    return has_value();
  }

  /// Access the stored value.
  /// \returns A (`const`) (rvalue) reference to the stored value.
  /// \requires `has_value() == true`.
  /// \group value
  value_type& value() & noexcept
  {
    DCHECK(has_value());
    return *static_cast<value_type*>(as_void());
  }

  /// \group value
  const value_type& value() const & noexcept
  {
    DCHECK(has_value());
    return *static_cast<const value_type*>(as_void());
  }

  /// \group value
  value_type&& value() && noexcept
  {
    DCHECK(has_value());
    return std::move(*static_cast<value_type*>(as_void()));
  }

  /// \group value
  const value_type&& value() const&& noexcept
  {
    DCHECK(has_value());
    return std::move(*static_cast<const value_type*>(as_void()));
  }

private:
  void* as_void() noexcept
  {
    return static_cast<void*>(&storage_);
  }

  const void* as_void() const noexcept
  {
    return static_cast<const void*>(&storage_);
  }

  using storage_t = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
  storage_t storage_;
  bool      initialized_;
};

// A tiny wrapper modelling an output parameter of a function.
//
// An output parameter is a parameter that will be used to transport output of a function to its
// caller, like a return value does. Usually they are implemented with lvalue references. They have
// a couple of disadvantages though:
// * They require an already created object, i.e. a default constructor or similar.
// * It is not obvious when just looking at the call that the argument will be changed.
// * They make it easy to accidentally use them as regular parameters, i.e. reading their value,
// even though that was not intended.
//
// If you use this class as your output parameter type,
// you do not have these disadvantages.
// The creation is explicit, you cannot read the value,
// and it works with [basic::deferred_construction]().
//
// \notes While you could use this class in other locations besides parameters,
// this is not recommended.
//
template <typename T>
class output_parameter
{
public:
  using parameter_type = T;

  //=== constructors/assignment ===//
  /// \effects Creates it from an lvalue reference.
  /// All output will be assigned to the object referred by the reference.
  /// \requires The referred object must live as long as the function has not returned.
  explicit output_parameter(T& obj) noexcept : ptr_(&obj), is_normal_ptr_(true) {}

  /// \group delete_val
  output_parameter(const T&) = delete;
  /// \group delete_val
  output_parameter(T&&) = delete;
  /// \group delete_val
  output_parameter(const T&&) = delete;

  /// \effects Creates it from a [basic::deferred_construction]() object.
  /// All output will be assigned or created in the storage of the defer construction object,
  /// depending on wheter it is initialized.
  /// \requires The referred object must live as long as the function has not returned.
  explicit output_parameter(deferred_construction<T>& out) noexcept
  {
    if (out.has_value())
    {
      is_normal_ptr_ = true;
      ptr_           = &out.value();
    }
    else
    {
      is_normal_ptr_ = false;
      ptr_           = &out;
    }
  }

  /// \group delete_deferred
  output_parameter(const deferred_construction<T>&) = delete;
  /// \group delete_deferred
  output_parameter(deferred_construction<T>&&) = delete;
  /// \group delete_deferred
  output_parameter(const deferred_construction<T>&&) = delete;

  /// \effects Moves an output parameter.
  /// This will put `other` in an invalid state, it must not be used afterwards.
  /// \notes This constructor is only there because guaranteed copy elision isn't available
  /// and otherwise the `out()` function could not be implemented.
  /// It is not intended to use it otherwise.
  output_parameter(output_parameter&& other) noexcept
  : ptr_(other.ptr_), is_normal_ptr_(other.is_normal_ptr_)
  {
    other.ptr_ = nullptr;
  }

  ~output_parameter() noexcept = default;

  /// \group delete_assign
  output_parameter& operator=(const output_parameter&) = delete;
  /// \group delete_assign
  output_parameter& operator=(output_parameter&&) = delete;

  //=== modifiers ===//
  /// \effects Same as `assign(std::forward<U>(u))`.
  /// \returns A reference to the value that was assigned, *not* `*this` as normal "assignment"
  /// operators. \requires `value_type` must be constructible from `U`. \synopsis_return
  /// parameter_type&
  template <typename U>
  auto operator=(U&& u) ->
    typename std::enable_if<std::is_constructible<T, decltype(std::forward<U>(u))>::value,
                            parameter_type&>::type
  {
    return assign(std::forward<U>(u));
  }

  /// \effects If the output object is not already created, forwards `args` to the constructor.
  /// Otherwise if `args` is a single type and can be assigned to `T`, assigns it.
  /// Otherwise if `args` cannot be assigned directly, creates a temporary object and move assigns
  /// that. \returns A reference to the value that was assigned. \throws Anything thrown by the
  /// constructor for `T` or the chosen assignment operator. \requires `T` must be constructible
  /// from the arguments,
  // and `T` must be move-assignable.
  template <typename... Args>
  T& assign(Args&&... args)
  {
    if (is_normal_ptr_)
      assign_impl(std::forward<Args>(args)...);
    else
    {
      auto defer = static_cast<deferred_construction<T>*>(ptr_);
      defer->emplace(std::forward<Args>(args)...);
      ptr_           = &defer->value();
      is_normal_ptr_ = true;
    }

    DCHECK(is_normal_ptr_);
    return *static_cast<T*>(ptr_);
  }

private:
  template <typename U>
  auto assign_impl(U&& u) ->
      typename std::enable_if<std::is_assignable<T&, decltype(std::forward<U>(u))>::value>::type
  {
    *static_cast<T*>(ptr_) = std::forward<U>(u);
  }

  template <typename... Args>
  void assign_impl(Args&&... args)
  {
    *static_cast<T*>(ptr_) = T(std::forward<Args>(args)...);
  }

  void* ptr_;
  bool  is_normal_ptr_;
};

/// \returns A new [basic::output_parameter]() using the reference `obj` as output.
template <typename T>
output_parameter<T> out(T& obj) noexcept
{
  return output_parameter<T>(obj);
}

/// \returns A new [basic::output_parameter]() using the [basic::deferred_construction]() as output.
template <typename T>
output_parameter<T> out(deferred_construction<T>& o) noexcept
{
  return output_parameter<T>(o);
}

} // namespace basic
