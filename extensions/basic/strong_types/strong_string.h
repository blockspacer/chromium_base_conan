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
#define STRONG_STRING_TAG_NAME UniqueStringTypeTag

// format tag name (concats strings)
#define STRONG_STRING_TAG_CUSTOM_2(using_name, suffix) \
  using_name ## _ ## suffix

// STRONG_STRING_TAG_CUSTOM(MyType, UniqueTypeTag) expands to `MyType_UniqueTypeTag`
#define STRONG_STRING_TAG_CUSTOM(using_name, suffix) \
  STRONG_STRING_TAG_CUSTOM_2(using_name,suffix)

/// \note Each `StrongAlias` must have UNIQUE tag.
/// We assume that provided `using_name` globally unique
/// (even between shared libs!)
// STRONG_STRING_TAG(MyType) expands to `MyType_UniqueTypeTag`
#define STRONG_STRING_TAG(using_name) \
  STRONG_STRING_TAG_CUSTOM(using_name,STRONG_STRING_TAG_NAME)

#define STRONGLY_TYPED_STRING(NAME) \
  using NAME = basic::StrongString<class STRONG_STRING_TAG(NAME)>

namespace basic {

// Type-safe string
//
// StrongString objects are type-safe string values
// that cannot be implicitly casted to untyped strings,
// or different StrongString types while still
// provides all relevant operators.
//
// StrongString template parameter is a tag type
// that is going to be used to distinguish strings
// of different types.
//
// EXAMPLE
//
// #include <basic/strong_types/strong_string.h>
//
// STRONGLY_TYPED_STRING(fooStr);
//
// STRONGLY_TYPED_STRING(barStr);
//
template<
  typename Tag
>
class StrongString
{
  // Types:
public:
  typedef std::string::traits_type traits_type;
  typedef std::string::value_type value_type;
  typedef std::string::allocator_type allocator_type;
  typedef std::string::size_type size_type;
  typedef std::string::difference_type difference_type;
  typedef std::string::reference reference;
  typedef std::string::const_reference const_reference;
  typedef std::string::pointer pointer;
  typedef std::string::const_pointer const_pointer;
  typedef std::string::iterator iterator;
  typedef std::string::const_iterator const_iterator;
  typedef std::string::const_reverse_iterator const_reverse_iterator;
  typedef std::string::reverse_iterator reverse_iterator;

  ///  Value returned by various member functions when they fail.
  static constexpr size_type npos = static_cast<size_type>(-1);

public:
  static const StrongString<Tag> kEmpty;

  /// Constructs a StrongString object initialised to \c "".
  constexpr StrongString() NO_EXCEPTION
    : value_("")
  {}

  /// Constructs a StrongString object initialised to \c v.
  constexpr explicit StrongString(const std::string& v) NO_EXCEPTION
    : value_(v)
  {}

  constexpr explicit StrongString(std::string&& v) NO_EXCEPTION
    : value_(v)
  {}

  /// Casts a StrongString object to an untyped \c string.
  explicit operator std::string() const NO_EXCEPTION
  {
    return value_;
  }

  const std::string& get() const NO_EXCEPTION
  {
    return value_;
  }

  const std::string& ToString() const NO_EXCEPTION
  {
    return value_;
  }

  constexpr std::string& value() & { return value_; }
  constexpr const std::string& value() const& { return value_; }
  constexpr std::string&& value() && { return RVALUE_CAST(value_); }
  constexpr const std::string&& value() const&& { return COPY_OR_MOVE(value_); }

  // Shortcut for `.value`
  //
  // BEFORE
  // DCHECK(obj.value().empty());
  //
  // AFTER
  // DCHECK((*obj).empty());
  constexpr const std::string& operator*() const
  {
    return value_;
  }

  constexpr std::string& operator*()
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
  constexpr const std::string* operator->() const
  {
    return &value_;
  }

  constexpr std::string* operator->()
  {
    return &value_;
  }

  /// Equal-to operator.
  friend bool operator==(
    const StrongString& x, const StrongString& y) NO_EXCEPTION
  {
    return x.value_ == y.value_;
  }

#if __cplusplus <= 201703L
  /// Not-equal-to operator.
  friend bool operator!=(
    const StrongString& x, const StrongString& y) NO_EXCEPTION
  {
    return x.value_ != y.value_;
  }
#endif

  /// Prints StrongString value to an output stream.
  friend std::ostream& operator<<(
    std::ostream& os, const StrongString& v)
  {
    return os << v.value_;
  }

  // Hasher to use in std::unordered_map, std::unordered_set, etc.
  //
  // USAGE
  //
  // using FooAlias = StrongBool<class FooTag>;
  // std::unordered_map<FooAlias, std::string, typename FooAlias::Hasher> map;
  //
  struct Hasher {
    using argument_type = StrongString;
    using result_type = std::size_t;
    result_type operator()(const argument_type& id) const
    {
      return std::hash<std::string>()(id.get());
    }
  };

  template<
    typename... Args
  >
  auto at(Args&&... args)
  {
    return value_.at(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto assign(Args&&... args)
  {
    return value_.assign(FORWARD(args)...);
  }

  auto get_allocator()
  {
    return value_.get_allocator();
  }

  auto front()
  {
    return value_.front();
  }

  auto back()
  {
    return value_.back();
  }

  auto data()
  {
    return value_.data();
  }

  auto c_str()
  {
    return value_.c_str();
  }

  auto begin()
  {
    return value_.begin();
  }

  auto cbegin()
  {
    return value_.cbegin();
  }

  auto end()
  {
    return value_.end();
  }

  auto cend()
  {
    return value_.cend();
  }

  auto rbegin()
  {
    return value_.rbegin();
  }

  auto crbegin()
  {
    return value_.crbegin();
  }

  auto rend()
  {
    return value_.rend();
  }

  auto crend()
  {
    return value_.crend();
  }

  auto empty()
  {
    return value_.empty();
  }

  auto size()
  {
    return value_.size();
  }

  auto length()
  {
    return value_.length();
  }

  auto max_size()
  {
    return value_.max_size();
  }

  template<
    typename... Args
  >
  auto reserve(Args&&... args)
  {
    return value_.reserve(FORWARD(args)...);
  }

  auto capacity()
  {
    return value_.capacity();
  }

  auto shrink_to_fit()
  {
    return value_.shrink_to_fit();
  }

  auto clear()
  {
    return value_.clear();
  }

  template<
    typename... Args
  >
  auto insert(Args&&... args)
  {
    return value_.insert(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto erase(Args&&... args)
  {
    return value_.erase(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto push_back(Args&&... args)
  {
    return value_.push_back(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto pop_back(Args&&... args)
  {
    return value_.pop_back(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto append(Args&&... args)
  {
    return value_.append(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto compare(Args&&... args)
  {
    return value_.compare(FORWARD(args)...);
  }

#if __cplusplus > 201703L
  template<
    typename... Args
  >
  auto starts_with(Args&&... args)
  {
    return value_.starts_with(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto ends_with(Args&&... args)
  {
    return value_.ends_with(FORWARD(args)...);
  }
#endif // C++20

  template<
    typename... Args
  >
  auto replace(Args&&... args)
  {
    return value_.replace(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto substr(Args&&... args)
  {
    return value_.substr(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto copy(Args&&... args)
  {
    return value_.copy(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto resize(Args&&... args)
  {
    return value_.resize(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto swap(Args&&... args)
  {
    return value_.swap(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto find(Args&&... args)
  {
    return value_.find(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto rfind(Args&&... args)
  {
    return value_.rfind(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto find_first_of(Args&&... args)
  {
    return value_.find_first_of(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto find_first_not_of(Args&&... args)
  {
    return value_.find_first_not_of(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto find_last_of(Args&&... args)
  {
    return value_.find_last_of(FORWARD(args)...);
  }

  template<
    typename... Args
  >
  auto find_last_not_of(Args&&... args)
  {
    return value_.find_last_not_of(FORWARD(args)...);
  }

  template<
    typename CharT
    , typename Traits
  >
  explicit operator std::basic_string_view<CharT, Traits>() const NO_EXCEPTION
  {
    return value_;
  }

  template<
    typename... Args
  >
  auto operator[](Args&&... args)
  {
    return value_.operator[](FORWARD(args)...);
  }

  friend bool operator==(
    const std::string& x, const StrongString& y) NO_EXCEPTION
  {
    return x == y.value_;
  }

#if __cplusplus <= 201703L
  friend bool operator!=(
    const std::string& x, const StrongString& y) NO_EXCEPTION
  {
    return x != y.value_;
  }
#endif

  template<
    typename charT
  >
  friend bool operator==(
    const charT* x, const StrongString& y) NO_EXCEPTION
  {
    return x == y.value_;
  }

#if __cplusplus <= 201703L
  template<
    typename charT
  >
  friend bool operator!=(
    const charT* x, const StrongString& y) NO_EXCEPTION
  {
    return x != y.value_;
  }
#endif

private:
  std::string value_;
};

template<typename Tag>
const StrongString<Tag>
  StrongString<Tag>::kEmpty { "" };

}  // namespace basic

namespace std {

// Allow StrongString to be used as a key to hashable containers.
template<typename Tag>
struct hash<basic::StrongString<Tag> >
{
  size_t operator()(
      const basic::StrongString<Tag> &idx) const
  {
    return hash<std::string>()(idx.value());
  }
};

}  // namespace std
