#pragma once

#include <ostream>
#include <utility>

#include <base/macros.h>
#include <base/template_util.h>

#include <basic/rvalue_cast.h>
#include <basic/macros.h>

#include <functional>
#include <initializer_list>
#include <type_traits>
#include <utility>
#include <string>

/// \note That `StrongAlias` implementation is bad for comilation time
/// (implementation uses SFINAE and `decltype` to conditionally add methods),
/// Prefer to create custom `UniquePerTypeStrongAlias` with same methods
/// as in aliased type.
/// Ideally, use code generator to 'copy' all methods from aliased type
/// into custom `UniquePerTypeStrongAlias`
//
// A type-safe alternative for a typedef or a 'using' directive.
//
// C++ currently does not support type-safe typedefs, despite multiple proposals
// (ex. http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3515.pdf). The
// next best thing is to try and emulate them in library code.
//
// The motivation is to disallow several classes of errors:
//
// using Orange = int;
// using Apple = int;
// Apple apple(2);
// Orange orange = apple;  // Orange should not be able to become an Apple.
// Orange x = orange + apple;  // Shouldn't add Oranges and Apples.
// if (orange > apple);  // Shouldn't compare Apples to Oranges.
// void foo(Orange);
// void foo(Apple);  // Redefinition.
// etc.
//
// StrongAlias may instead be used as follows:
//
// using Orange = ::basic::StrongAlias<class OrangeTag, int>;
// STRONGLY_TYPED(int, Apple);
//
// StrongAlias is a zero-cost abstraction, it's compiled away.
//
// TagType is an empty tag class (also called "phantom type") that only serves
// the type system to differentiate between different instantiations of the
// template.
// UnderlyingType may be almost any value type. Note that some methods of the
// StrongAlias may be unavailable (ie. produce elaborate compilation errors when
// used) if UnderlyingType doesn't support them.
//
// StrongAlias only directly exposes comparison operators (for convenient use in
// ordered containers) and a hash function (for unordered_map/set). It's
// impossible, without reflection, to expose all methods of the UnderlyingType
// in StrongAlias's interface. It's also potentially unwanted (ex. you don't
// want to be able to add two StrongAliases that represent socket handles).
// A getter is provided in case you need to access the UnderlyingType.
//
// See also
// - //styleguide/c++/blink-c++.md which provides recommendation and examples of
//   using StrongAlias<Tag, bool> instead of a bare bool.
// - ::basic::IdType<...> which provides helpers for specializing
//   StrongAlias to be used as an id.

// default tag for strong type
#define STRONG_TYPE_TAG_NAME UniqueTypeTag

// format tag name (concats strings)
#define STRONG_TYPE_TAG_CUSTOM_2(using_name, suffix) \
  using_name ## _ ## suffix

// STRONG_TYPE_TAG_CUSTOM(MyType, UniqueTypeTag) expands to `MyType_UniqueTypeTag`
#define STRONG_TYPE_TAG_CUSTOM(using_name, suffix) \
  STRONG_TYPE_TAG_CUSTOM_2(using_name,suffix)

/// \note Each `StrongAlias` must have UNIQUE tag.
/// We assume that provided `using_name` globally unique
/// (even between shared libs!)
// STRONG_TYPE_TAG(MyType) expands to `MyType_UniqueTypeTag`
#define STRONG_TYPE_TAG(using_name) \
  STRONG_TYPE_TAG_CUSTOM(using_name,STRONG_TYPE_TAG_NAME)

/// \note Prefer to add custom define like `#define STRONGLY_TYPED_...(TYPE)`
/// because `StrongAlias` lacks operators or methods
/// from original type, so avoid `StrongAlias` and create custom class
/// `UniquePerTypeStrongAlias`, `StrongAliasMyGUID`, etc.
/// Ideally, use code generator to 'copy' all methods from aliased type
/// into custom `UniquePerTypeStrongAlias`
#define STRONGLY_TYPED(TYPE, NAME) \
  using NAME = ::basic::StrongAlias<class STRONG_TYPE_TAG(NAME), TYPE>

// format function name (concats strings)
#define NAME_HAS_MEMBER_FUNCTION(content, suffix) \
  content ## _ ## suffix

// Attempt to call function and see if the return type is correct
// Inspired by `BOOST_TTI_HAS_MEMBER_FUNCTION` and stackoverflow.com/a/61482882.
//
#define HAS_MEMBER_FUNCTION(NAME) \
  template <typename T, typename... Args> \
  struct NAME_HAS_MEMBER_FUNCTION(has_func, NAME) { \
      template <class, class> \
      class checker; \
      /* `checker` with `true_type` will be overloaded if `decltype` succeded */ \
      template <typename U> \
      static std::true_type test( \
        checker< \
          U \
          , decltype(std::declval<U>().NAME( std::declval<Args>()... )) \
        > *); \
      template <typename U> \
      static std::false_type test(...); \
      static const bool value \
        = std::is_same< \
            std::true_type \
            , decltype(test<T>(nullptr)) \
          >::value; \
    }; \
  template <typename T, typename... Args> \
  struct NAME_HAS_MEMBER_FUNCTION(has_func_ignore_args, NAME) { \
      template <class, class> \
      class checker; \
      /* `checker` with `true_type` will be overloaded if `decltype` succeded */ \
      template <typename U> \
      static std::true_type test( \
        checker<U, decltype(&U::NAME)> *); \
      template <typename U> \
      static std::false_type test(...); \
      static const bool value \
        = std::is_same< \
            std::true_type \
            , decltype(test<T>(nullptr)) \
          >::value; \
    };

namespace basic {

// Specification:
// http://en.cppreference.com/w/cpp/utility/optional/nullopt_t
struct nullalias_t {
  constexpr explicit nullalias_t(int) {}
};

// Specification:
// http://en.cppreference.com/w/cpp/utility/optional/nullopt
constexpr nullalias_t nullopt(0);

namespace strong_alias_internal {

template <typename T, typename = void>
struct is_equality_comparable
  : std::false_type
  {};

/// \note std::declval<T&> to get the program to tell you whether
/// an lvalue of type T is comparable
/// (for example: rvalue of type `int` not comparable,
/// but lvalue of type `int` is comparable)
template <typename T>
struct is_equality_comparable<
    T,
    typename std::enable_if<
      std::is_convertible<
        decltype(std::declval<T&>() == std::declval<T&>())
        // result of `operator==` must be `bool`
        , bool
      >{}
    >::type
  > : public std::true_type
  {};

template <typename T, typename = void>
struct is_less_than_comparable
  : public std::false_type
  {};

/// \note std::declval<T&> to get the program to tell you whether
/// an lvalue of type T is comparable
/// (for example: rvalue of type `int` not comparable,
/// but lvalue of type `int` is comparable)
template <typename T>
struct is_less_than_comparable<
    T,
    typename std::enable_if<
      std::is_convertible<
        decltype(std::declval<T&>() < std::declval<T&>())
        // result of `operator<` must be `bool`
        , bool
      >{}
    >::type
  > : public std::true_type
  {};

template <typename T, typename = void>
struct has_pre_increment_member
  : public std::false_type
  {};

/// \note std::declval<T&> to get the program to tell you whether
/// an lvalue of type T is incrementable
/// (for example: rvalue of type `int` not incrementable,
/// but lvalue of type `int` is incrementable)
template <class T>
struct has_pre_increment_member<
    T
    , std::void_t< // detect validity of an expression
        decltype(++(std::declval<T&>()))
      >
  >
  : public std::true_type
  {};

template <typename T, typename = void>
struct has_post_increment_member
  : public std::false_type
  {};

/// \note std::declval<T&> to get the program to tell you whether
/// an lvalue of type T is incrementable
/// (for example: rvalue of type `int` not incrementable,
/// but lvalue of type `int` is incrementable)
template <class T>
struct has_post_increment_member<
    T
    , std::void_t< // detect validity of an expression
        decltype((std::declval<T&>()++))
      >
  >
  : public std::true_type
  {};

template <typename T, typename = void>
struct has_pre_decrement_member
  : public std::false_type
  {};

/// \note std::declval<T&> to get the program to tell you whether
/// an lvalue of type T is decrementable
/// (for example: rvalue of type `int` not decrementable,
/// but lvalue of type `int` is decrementable)
template <class T>
struct has_pre_decrement_member<
    T
    , std::void_t< // detect validity of an expression
        decltype(--(std::declval<T&>()))
      >
  >
  : public std::true_type
  {};

template <typename T, typename = void>
struct has_post_decrement_member
  : public std::false_type
  {};

/// \note std::declval<T&> to get the program to tell you whether
/// an lvalue of type T is decrementable
/// (for example: rvalue of type `int` not decrementable,
/// but lvalue of type `int` is decrementable)
template <class T>
struct has_post_decrement_member<
    T
    , std::void_t< // detect validity of an expression
        decltype((std::declval<T&>()--))
      >
  >
  : public std::true_type
  {};

template <typename T, typename = void>
struct is_iterable
  : public std::false_type
  {};

template <typename T>
struct is_iterable<
  T
  , std::void_t< // detect validity of an expression
      decltype(std::declval<T>().begin())
      , decltype(std::declval<T>().end())
    >
  >
  : public std::true_type {};

HAS_MEMBER_FUNCTION(ToString)

} // namespace strong_alias_internal

/**
 * \usage
    class FrameLoader {
    public:
      using ForReload = ::basic::StrongAlias<class ForReloadTag, bool>;

      bool ShouldClose(ForReload) {
        // A StrongAlias<_, bool> can be tested like a bool.
        if (for_reload) {
          ...
        } else {
          ...
        }
      }
    };

    // Using a StrongAlias makes it clear what the parameter is for.
    if (frame_->Loader().ShouldClose(FrameLoader::ForReload(false))) {
      // No need to use enums for boolean setters, since the meaning is clear.
      frame_->SetIsClosing(true);
 */
/// \todo make configurable similar
/// to strong_typedef_properties from https://github.com/anthonywilliams/strong_typedef
template <typename TagType, typename UnderlyingType>
class StrongAlias
{
 public:
  constexpr StrongAlias() = default;

  constexpr StrongAlias(nullalias_t) {}  // NOLINT(runtime/explicit)

  // Helper to conditionally enable converting constructors and assign operators.
  template <typename T, typename U>
  struct IsConvertibleFromStrongAlias
      : std::integral_constant<
            bool,
            std::is_constructible<T, StrongAlias<TagType,U>&>::value ||
                std::is_constructible<T, const StrongAlias<TagType,U>&>::value ||
                std::is_constructible<T, StrongAlias<TagType,U>&&>::value ||
                std::is_constructible<T, const StrongAlias<TagType,U>&&>::value ||
                std::is_convertible<StrongAlias<TagType,U>&, T>::value ||
                std::is_convertible<const StrongAlias<TagType,U>&, T>::value ||
                std::is_convertible<StrongAlias<TagType,U>&&, T>::value ||
                std::is_convertible<const StrongAlias<TagType,U>&&, T>::value> {};

  template <typename T, typename U>
  struct IsAssignableFromStrongAlias
      : std::integral_constant<
            bool,
            IsConvertibleFromStrongAlias<T, U>::value ||
                std::is_assignable<T&, StrongAlias<TagType,U>&>::value ||
                std::is_assignable<T&, const StrongAlias<TagType,U>&>::value ||
                std::is_assignable<T&, StrongAlias<TagType,U>&&>::value ||
                std::is_assignable<T&, const StrongAlias<TagType,U>&&>::value> {};

  // Forward compatibility for C++20.
  template <typename T>
  using RemoveCvRefT = std::remove_cv_t<std::remove_reference_t<T>>;

  // Converting copy constructor. "explicit" only if
  // std::is_convertible<const U&, T>::value is false. It is implemented by
  // declaring two almost same constructors, but that condition in enable_if_t
  // is different, so that either one is chosen, thanks to SFINAE.
  template <
      typename U,
      std::enable_if_t<std::is_constructible<UnderlyingType, const U&>::value &&
                           !IsConvertibleFromStrongAlias<UnderlyingType, U>::value &&
                           std::is_convertible<const U&, UnderlyingType>::value,
                       bool> = false>
  StrongAlias(const StrongAlias<TagType,U>& other)
    : value_(other.value_) {}

  template <
      typename U,
      std::enable_if_t<std::is_constructible<UnderlyingType, const U&>::value &&
                           !IsConvertibleFromStrongAlias<UnderlyingType, U>::value &&
                           !std::is_convertible<const U&, UnderlyingType>::value,
                       bool> = false>
  explicit StrongAlias(const StrongAlias<TagType,U>& other)
    : value_(other.value_) {}

  // Converting move constructor. Similar to converting copy constructor,
  // declaring two (explicit and non-explicit) constructors.
  template <
      typename U,
      std::enable_if_t<std::is_constructible<UnderlyingType, U&&>::value &&
                           !IsConvertibleFromStrongAlias<UnderlyingType, U>::value &&
                           std::is_convertible<U&&, UnderlyingType>::value,
                       bool> = false>
  StrongAlias(StrongAlias<TagType,U>&& other)
    : value_(RVALUE_CAST(other.value_)) {}

  template <
      typename U,
      std::enable_if_t<std::is_constructible<UnderlyingType, U&&>::value &&
                           !IsConvertibleFromStrongAlias<UnderlyingType, U>::value &&
                           !std::is_convertible<U&&, UnderlyingType>::value,
                       bool> = false>
  explicit StrongAlias(StrongAlias<TagType,U>&& other)
    : value_(RVALUE_CAST(other.value_)) {}

  template <class... Args>
  constexpr explicit StrongAlias(base::in_place_t, Args&&... args)
    : value_(FORWARD(args)...) {}

  // USAGE
  //
  // STRONGLY_TYPED(std::vector<int>, MyStrongVec);
  // MyStrongVec vec{base::in_place, {1,2,3,4}};
  // for(auto it = vec.begin(); it != vec.end(); it++){
  //   DLOG(INFO) << *it;
  // }
  template <
      class U,
      class... Args,
      class = std::enable_if_t<std::is_constructible<UnderlyingType,
                                                     std::initializer_list<U>&,
                                                     Args...>::value>>
  constexpr explicit StrongAlias(base::in_place_t,
                              std::initializer_list<U> il,
                              Args&&... args)
    : value_(il, FORWARD(args)...) {}

  // Forward value constructor. Similar to converting constructors,
  // conditionally explicit.
  template <
      typename U = UnderlyingType,
      std::enable_if_t<
          std::is_constructible<UnderlyingType, U&&>::value &&
              !std::is_same<RemoveCvRefT<U>, ::base::in_place_t>::value &&
              !std::is_same<RemoveCvRefT<U>, StrongAlias<TagType,UnderlyingType>>::value &&
              std::is_convertible<U&&, UnderlyingType>::value,
          bool> = false>
  constexpr StrongAlias(U&& value)
    : value_(FORWARD(value)) {}

  template <
      typename U = UnderlyingType,
      std::enable_if_t<
          std::is_constructible<UnderlyingType, U&&>::value &&
              !std::is_same<RemoveCvRefT<U>, ::base::in_place_t>::value &&
              !std::is_same<RemoveCvRefT<U>, StrongAlias<TagType,UnderlyingType>>::value &&
              !std::is_convertible<U&&, UnderlyingType>::value,
          bool> = false>
  constexpr explicit StrongAlias(U&& value)
    : value_(FORWARD(value)) {}

  constexpr UnderlyingType& value() & { return value_; }
  constexpr const UnderlyingType& value() const& { return value_; }
  constexpr UnderlyingType&& value() && { return RVALUE_CAST(value_); }
  constexpr const UnderlyingType&& value() const&& { return COPY_OR_MOVE(value_); }

  constexpr explicit operator UnderlyingType() const { return value_; }

  // Shortcut for `.value`
  //
  // BEFORE
  // DCHECK(obj.value().empty());
  //
  // AFTER
  // DCHECK((*obj).empty());
  constexpr const UnderlyingType& operator*() const
  {
    return value_;
  }

  constexpr UnderlyingType& operator*()
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
  constexpr const UnderlyingType* operator->() const
  {
    return &value_;
  }

  constexpr UnderlyingType* operator->()
  {
    return &value_;
  }

  // Adds `ToString()` method only if type can be converted to string
  // or has custom `ToString()` method.
  //
  // EXAMPLE
  //
  // struct CustomType{
  //   int a = 3;
  //   bool b{true};
  //
  //   std::string ToString()
  //   {
  //     return "hi2";
  //   }
  // };
  //
  // STRONGLY_TYPED(std::string, MyStrongString);
  // STRONGLY_TYPED(CustomType, MyStrongStringCustomType);
  // STRONGLY_TYPED(int, MyStrongStringInt);
  //
  // MyStrongString str1("hi");
  // DCHECK(str1.ToString() == "hi");
  //
  // MyStrongStringCustomType str2;
  // DCHECK(str2.ToString() == "hi2");
  //
  // MyStrongStringInt str3(3);
  // DCHECK(str3.ToString() == "3");
  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    // Custom (not basic!) type with `operator std::string`,
    // but without `ToString()` method.
    (
      (!std::is_void<T>{} && !std::is_fundamental<T>{})
       && (std::is_convertible<T, std::string>::value)
       && (!(strong_alias_internal::has_func_ToString<T>::value))
    )
    // Or `std::string`
    || (std::is_same<T, std::string>::value)
    || (std::is_base_of<std::string, T>::value),
    std::string
  >::type
  ToString()
  {
    return static_cast<std::string>(value_);
  }

  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    // any basic type can be converted via `std::to_string`
    (!std::is_void<T>{} && std::is_fundamental<T>{}),
    std::string
  >::type
  ToString()
  {
    return std::to_string(value_);
  }

  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::has_func_ToString<T>::value)
    , std::string
  >::type
  ToString()
  {
    return value_.ToString();
  }

  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::is_equality_comparable<T>::value),
    bool
  >::type
  operator==
  (const StrongAlias& other) const
  {
    return value_ == other.value_;
  }

  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::is_equality_comparable<T>::value),
    bool
  >::type
  operator!=
  (const StrongAlias& other) const
  {
    return value_ != other.value_;
  }

  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::is_less_than_comparable<T>::value),
    bool
  >::type
  operator<
  (const StrongAlias& other) const {
    return value_ < other.value_;
  }

  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::is_less_than_comparable<T>::value),
    bool
  >::type
  operator>
  (const StrongAlias& other) const {
    return value_ > other.value_;
  }

  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::is_equality_comparable<T>::value)
    && (strong_alias_internal::is_less_than_comparable<T>::value),
    bool
  >::type
  operator<=
  (const StrongAlias& other) const {
    return value_ <= other.value_;
  }

  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::is_equality_comparable<T>::value)
    && (strong_alias_internal::is_less_than_comparable<T>::value),
    bool
  >::type
  operator>=
  (const StrongAlias& other) const {
    return value_ >= other.value_;
  }

  // EXAMPLE
  //
  // MyStrongStringInt valInt(3);
  // valInt++;
  // DCHECK(valInt.ToString() == "4");
  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::has_pre_increment_member<T>::value),
    T& // prefix++ returns `T&`
  >::type
  operator++
  () {
    ++value_;
    return value_;
  }

  // EXAMPLE
  //
  // MyStrongStringInt valInt(3);
  // ++valInt;
  // valInt+=2;
  // DCHECK(valInt.ToString() == "6");
  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::has_post_increment_member<T>::value),
    T // postfix++ returns `T`
  >::type
  operator++
  (int val)
  {
    if( val != 0 ) {
      // argument can be passed via `i.operator++( 25 );`
      value_ += val;
    } else {
      value_++;
    }

    return value_;
  }

  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::has_pre_decrement_member<T>::value),
    T& // prefix-- returns `T&`
  >::type
  operator--
  () {
    --value_;
    return value_;
  }

  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::has_post_decrement_member<T>::value),
    T // postfix-- returns `T`
  >::type
  operator--
  (int val)
  {
    if( val != 0 ) {
      // argument can be passed via `i.operator--( 25 );`
      value_ -= val;
    } else {
      value_--;
    }

    return value_;
  }

  // USAGE
  //
  // STRONGLY_TYPED(std::vector<int>, MyStrongVec);
  // MyStrongVec vec{base::in_place, {1,2,3,4}};
  // for(auto it = vec.begin(); it != vec.end(); it++){
  //   DLOG(INFO) << *it;
  // }
  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::is_iterable<T>::value),
    decltype(std::declval<T>().begin())
  >::type
  begin
  () {
    return value_.begin();
  }

  template<typename T = UnderlyingType>
  constexpr
  typename std::enable_if<
    (strong_alias_internal::is_iterable<T>::value),
    decltype(std::declval<T>().end())
  >::type
  end
  () {
    return value_.begin();
  }

  // Hasher to use in std::unordered_map, std::unordered_set, etc.
  //
  // USAGE
  //
  // using FooAlias = StrongAlias<class FooTag, TypeParam>;
  // std::unordered_map<FooAlias, std::string, typename FooAlias::Hasher> map;
  //
  struct Hasher
  {
    using argument_type = StrongAlias;
    using result_type = std::size_t;
    result_type operator()(const argument_type& id) const
    {
      return std::hash<UnderlyingType>()(id.value());
    }
  };

 protected:
  UnderlyingType value_;
};

// Stream operator for convenience, streams the UnderlyingType.
template <typename TagType, typename UnderlyingType>
std::ostream& operator<<(std::ostream& stream,
                         const StrongAlias<TagType, UnderlyingType>& alias)
{
  return stream << alias.value();
}

}  // namespace basic
