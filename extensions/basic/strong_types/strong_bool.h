#pragma once

#include <base/macros.h>
#include <base/template_util.h>

#include <basic/rvalue_cast.h>
#include <basic/macros.h>

#include <ostream>
#include <utility>
#include <functional>
#include <string>

// default tag for strong type
#define STRONG_BOOL_TAG_NAME UniqueBoolTypeTag

// format tag name (concats strings)
#define STRONG_BOOL_TAG_CUSTOM_2(using_name, suffix) \
  using_name ## _ ## suffix

// STRONG_BOOL_TAG_CUSTOM(MyType, UniqueTypeTag) expands to `MyType_UniqueTypeTag`
#define STRONG_BOOL_TAG_CUSTOM(using_name, suffix) \
  STRONG_BOOL_TAG_CUSTOM_2(using_name,suffix)

/// \note Each `StrongAlias` must have UNIQUE tag.
/// We assume that provided `using_name` globally unique
/// (even between shared libs!)
// STRONG_BOOL_TAG(MyType) expands to `MyType_UniqueTypeTag`
#define STRONG_BOOL_TAG(using_name) \
  STRONG_BOOL_TAG_CUSTOM(using_name,STRONG_BOOL_TAG_NAME)

#define STRONGLY_TYPED_BOOL(NAME) \
  using NAME = basic::StrongBool<class STRONG_BOOL_TAG(NAME)>

namespace basic {

// Type-safe boolean
//
// StrongBool objects are type-safe boolean values
// that cannot be implicitly casted to untyped bools,
// integers or different StrongBool types while still
// provides all relevant logical and comparison operators.
//
// StrongBool template parameter is a tag type
// that is going to be used to distinguish booleans
// of different types.
//
// EXAMPLE
//
// #include <basic/strong_types/strong_bool.h>
//
// STRONGLY_TYPED_BOOL(foo);
//
// STRONGLY_TYPED_BOOL(bar);
//
template<
  typename Tag
>
class StrongBool
{
public:
  static const StrongBool<Tag> kTrue;

  static const StrongBool<Tag> kFalse;

  static const std::initializer_list<StrongBool<Tag>> kValues;

  /// Constructs a StrongBool object initialised to \c false.
  constexpr StrongBool() NO_EXCEPTION
    : value_(false)
  {}

  /// Constructs a StrongBool object initialised to \c v.
  constexpr explicit StrongBool(bool v) NO_EXCEPTION
    : value_(v)
  {}

  //constexpr explicit StrongBool(const StrongBool<Tag>& v) NO_EXCEPTION
  //  : value_(v.get())
  //{}
  //
  //constexpr explicit StrongBool(StrongBool<Tag>&& v) NO_EXCEPTION
  //  : value_(RVALUE_CAST(v.value()))
  //{}
  //
  //// Assignment operator.
  //StrongBool& operator=(StrongBool other) {
  //  value_ = other.value();
  //  return *this;
  //}

  /// Casts a StrongBool object to an untyped \c bool.
  constexpr explicit operator bool() const NO_EXCEPTION
  {
    return value_;
  }

  bool get() const NO_EXCEPTION
  {
    return value_;
  }

  constexpr bool& value() & { return value_; }
  constexpr const bool& value() const& { return value_; }
  constexpr bool&& value() && { return RVALUE_CAST(value_); }
  constexpr const bool&& value() const&& { return COPY_OR_MOVE(value_); }

  // Shortcut for `.value`
  //
  // BEFORE
  // DCHECK(obj.value().empty());
  //
  // AFTER
  // DCHECK((*obj).empty());
  constexpr const bool& operator*() const
  {
    return value_;
  }

  constexpr bool& operator*()
  {
    return value_;
  }

  // Shortcut for `.value`
  //
  // BEFORE
  // DCHECK(obj.value().empty());
  //
  // AFTER
  // DCHECK(obj->empty());
  constexpr const bool* operator->() const
  {
    return &value_;
  }

  constexpr bool* operator->()
  {
    return &value_;
  }

  /// Logical OR.
  friend StrongBool operator||(
    StrongBool x, StrongBool y) NO_EXCEPTION
  {
    return StrongBool(x.value_ || y.value_);
  }

  /// Logical AND.
  friend StrongBool operator&&(
    StrongBool x, StrongBool y) NO_EXCEPTION
  {
    return StrongBool(x.value_ && y.value_);
  }

  /// Logical NOT.
  friend StrongBool operator!(
    StrongBool x) NO_EXCEPTION
  {
    return StrongBool(!x.value_);
  }

  /// Equal-to operator.
  friend bool operator==(
    StrongBool x, StrongBool y) NO_EXCEPTION
  {
    return x.value_ == y.value_;
  }

#if __cplusplus <= 201703L
  /// Not-equal-to operator.
  friend bool operator!=(
    StrongBool x, StrongBool y) NO_EXCEPTION
  {
    return x.value_ != y.value_;
  }
#endif

  /// Equal-to operator.
  friend bool operator==(
    bool x, const StrongBool& y) NO_EXCEPTION
  {
    return x == y.value_;
  }

#if __cplusplus <= 201703L
  /// Not-equal-to operator.
  friend bool operator!=(
    bool x, const StrongBool& y) NO_EXCEPTION
  {
    return x != y.value_;
  }
#endif

  const std::string ToString() const NO_EXCEPTION
  {
    return (value_ ? "true" : "false");
  }

  /// Prints StrongBool value to an output stream.
  friend std::ostream& operator<<(
    std::ostream& os, StrongBool v)
  {
    return os << (v.ToString());
  }

  // Hasher to use in std::unordered_map, std::unordered_set, etc.
  //
  // USAGE
  //
  // using FooAlias = StrongBool<class FooTag>;
  // std::unordered_map<FooAlias, std::string, typename FooAlias::Hasher> map;
  //
  struct Hasher
  {
    using argument_type = StrongBool;
    using result_type = std::size_t;
    result_type operator()(const argument_type& id) const
    {
      return std::hash<bool>()(id.get());
    }
  };

private:
  bool value_;
};

template<typename Tag>
const StrongBool<Tag>
  StrongBool<Tag>::kTrue { true };

template<typename Tag>
const StrongBool<Tag>
  StrongBool<Tag>::kFalse { false };

// USAGE
//
// for (auto use_hash : UseHash::kValues) {
//   Init(use_hash);
// }
template <class Tag>
const std::initializer_list<StrongBool<Tag>>
  StrongBool<Tag>::kValues
  {
    StrongBool<Tag>::kFalse,
    StrongBool<Tag>::kTrue
  };

}  // namespace basic

namespace std {

// Allow StrongBool to be used as a key to hashable containers.
template<typename Tag>
struct hash<basic::StrongBool<Tag> >
{
  size_t operator()(
      const basic::StrongBool<Tag> &idx) const
  {
    return hash<bool>()(idx.value());
  }
};

}  // namespace std
