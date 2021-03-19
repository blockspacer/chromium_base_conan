#pragma once

#include <bitset>
#include <string>

#include <third_party/boost_preprocessor/include/boost/preprocessor/cat.hpp>
#include <third_party/boost_preprocessor/include/boost/preprocessor/expr_if.hpp>
#include <third_party/boost_preprocessor/include/boost/preprocessor/if.hpp>
#include <third_party/boost_preprocessor/include/boost/preprocessor/stringize.hpp>
#include <third_party/boost_preprocessor/include/boost/preprocessor/facilities/apply.hpp>
#include <third_party/boost_preprocessor/include/boost/preprocessor/punctuation/is_begin_parens.hpp>
#include <third_party/boost_preprocessor/include/boost/preprocessor/seq/for_each.hpp>
#include <third_party/boost_preprocessor/include/boost/preprocessor/seq/fold_left.hpp>

#include <base/macros.h>
#include <base/notreached.h>
#include <base/logging.h>
#include <base/location.h>
#include <base/numerics/safe_conversions.h>

#include <basic/macros.h>

#include <unordered_map>

// __has_include is currently supported by GCC and Clang. However GCC 4.9 may have issues and
// returns 1 for 'defined( __has_include )', while '__has_include' is actually not supported:
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63662
#if defined( __has_include ) && (!defined( BOOST_GCC ) || (__GNUC__ + 0) >= 5)
# if __has_include(<cxxabi.h>)
#  define TYPED_ENUM_HAS_CXXABI_H
# endif
#elif defined( __GLIBCXX__ ) || defined( __GLIBCPP__ )
# define TYPED_ENUM_HAS_CXXABI_H
#endif

#if defined( TYPED_ENUM_HAS_CXXABI_H )
# include <cxxabi.h>
// For some archtectures (mips, mips64, x86, x86_64) cxxabi.h in Android NDK is implemented by gabi++ library
// (https://android.googlesource.com/platform/ndk/+/master/sources/cxx-stl/gabi++/), which does not implement
// abi::__cxa_demangle(). We detect this implementation by checking the include guard here.
# if defined( __GABIXX_CXXABI_H__ )
#  undef TYPED_ENUM_HAS_CXXABI_H
# else
#  include <cstdlib>
#  include <cstddef>
# endif
#endif

/// \note `TYPED_ENUM` can be used as `BitMask`
//
// Creates enum class with string conversion functions and provides helpers
// (enum as bit set (bit flags), enum iteration, enum size, etc.)
//
// USAGE
//
//  TYPED_ENUM(MyEnum, int, (kFoo)(kBar)(kBaz))
//
//  MyEnum myEnum = MyEnum::kFoo;
//
//  // converting a value of MyEnum to std::string
//  // (or diagnostic string for invalid values)
//  // kFoo
//  DVLOG(9)
//    << ToString(myEnum);
//
//  // stream output operator
//  // kFoo
//  DVLOG(9)
//    << myEnum;
//
//  // converting an enum value to a C string
//  // (or nullptr for invalid values)
//  // kFoo
//  DVLOG(9)
//    << ToCString(myEnum);
//
//  // TypedEnumSize = 3
//  DVLOG(9)
//    << "TypedEnumSize = "
//    << ::basic::typedEnumSize<MyEnum>();
//
//  using MyEnumConstIterator
//    = ::basic::TypedEnumConstIterator<MyEnum>;
//
//  // prints:
//  // iterated enum = kFoo with id = 0
//  // found enum = kFoo with id = 0
//  // iterated enum = kBar with id = 1
//  // iterated enum = kBaz with id = 2
//  for(MyEnumConstIterator iter = ::basic::typedEnumBegin<MyEnum>()
//    ; iter != ::basic::typedEnumEnd<MyEnum>()
//    ; iter++)
//  {
//    DVLOG(9)
//      << "iterated enum = "
//      << *iter
//      << " with id = "
//      << ::basic::underlying_type(*iter);
//
//    if(*iter == myEnum)
//    {
//      DVLOG(9)
//        << "found enum = "
//        << *iter
//        << " with id = "
//        << ::basic::underlying_type(*iter);
//    }
//  }
//
//  // use `TypedEnumHasher` as 3rd template-parameter of std::unordered_map
//  const std::unordered_map<MyEnum, const char*, ::basic::TypedEnumHasher> kMyEnumMessage {
//    { MyEnum::kFoo, "kFooMessage (not same as ToString(myEnum::kFoo))" },
//    { MyEnum::kBar, "kBarMessage (not same as ToString(myEnum::kBar))" },
//    { MyEnum::kBaz, "kBazMessage (not same as ToString(myEnum::kBaz))" },
//  };
//
//  using MyEnumFlags = ::basic::TypedEnumBitSet<MyEnum>;
//
//  MyEnumFlags myEnumFlags = MyEnumFlags();
//  myEnumFlags.Set(MyEnum::kFoo);
//  DCHECK(myEnumFlags.Test(MyEnum::kFoo));
//  DCHECK(!myEnumFlags.Test(MyEnum::kBaz));
//
//  MyEnumFlags otherEnumFlags = MyEnumFlags({MyEnum::kFoo, MyEnum::kBaz});
//  otherEnumFlags.Unset(MyEnum::kFoo);
//  DCHECK(!otherEnumFlags.Test(MyEnum::kFoo));
//  DCHECK(otherEnumFlags.Test(MyEnum::kBaz));

namespace basic {

namespace detail {

inline char const * demangle_alloc( char const * name ) NO_EXCEPTION;
inline void demangle_free( char const * name ) NO_EXCEPTION;

class scoped_demangled_name
{
private:
    char const * m_p;

public:
    explicit scoped_demangled_name( char const * name ) NO_EXCEPTION :
        m_p( demangle_alloc( name ) )
    {
    }

    ~scoped_demangled_name() NO_EXCEPTION
    {
        demangle_free( m_p );
    }

    char const * get() const NO_EXCEPTION
    {
        return m_p;
    }

    DELETE_FUNCTION(scoped_demangled_name( scoped_demangled_name const& ));
    DELETE_FUNCTION(scoped_demangled_name& operator= ( scoped_demangled_name const& ));
};

#if defined( TYPED_ENUM_HAS_CXXABI_H )

inline char const * demangle_alloc( char const * name ) NO_EXCEPTION
{
    int status = 0;
    std::size_t size = 0;
    return abi::__cxa_demangle( name, NULL, &size, &status );
}

inline void demangle_free( char const * name ) NO_EXCEPTION
{
    std::free( const_cast< char* >( name ) );
}

inline std::string demangle( char const * name )
{
    scoped_demangled_name demangled_name( name );
    char const * p = demangled_name.get();
    if( !p )
        p = name;
    return p;
}

#else

inline char const * demangle_alloc( char const * name ) NO_EXCEPTION
{
    return name;
}

inline void demangle_free( char const * ) NO_EXCEPTION
{
}

inline std::string demangle( char const * name )
{
    return name;
}

#endif

} // namespace detail

// Convert a strongly typed enum to its underlying type.
template <typename EnumType>
constexpr typename std::underlying_type<EnumType>::type
  underlying_type(EnumType enumeration)
{
  using UnderlyingEnumType = typename std::underlying_type<EnumType>::type;
  return static_cast<UnderlyingEnumType>(enumeration);
}

template<typename EnumType>
using TypedEnumConstIterator
  = typename decltype(TypedEnumAsList(static_cast<EnumType*>(nullptr)))::const_iterator;

namespace typed_enum_internal {

template <class Type>
constexpr Type constexprMax(
  const Type& lhs
  , const Type& rhs)
{
  return
    (lhs > rhs)
    ? lhs
    : rhs;
}

template<typename T>
std::string GetDemangledTypeName() {
  char const* type_name = typeid(T).name();
  detail::scoped_demangled_name type_name_demangled(type_name);

  // From https://stackoverflow.com/questions/1488186/stringifying-template-arguments:
  return type_name_demangled.get() ? type_name_demangled.get() : type_name;
}

template<typename Enum>
ATTRIBUTE_NORETURN void LogInvalidEnumValue(
    const char* enumName,
    const std::string& valueStr,
    Enum enumValue,
    const char* expressionStr,
    const ::base::Location& location)
{
  LOG(ERROR)
      << location.ToString()
      << " : Invalid value of enum " << enumName << " ("
      << "enum type: " << GetDemangledTypeName<Enum>() << ", "
      << "expression: " << expressionStr << "): "
      << valueStr << (!valueStr.empty() ? " (" : "")
      << std::to_string(underlying_type(enumValue))
      << (!valueStr.empty() ? ")" : "") << ".";

  NOTREACHED();
}

} // namespace typed_enum_internal

// Functor object to calculate hash of enum class
//
// USAGE
//
// // use `TypedEnumHasher` as 3rd template-parameter of std::unordered_map
// const std::unordered_map<EnumCode, const char*, ::basic::TypedEnumHasher>
//   kErrorMessage
// {
//   { EnumCode::SUCCESS, "Success" },
//   { EnumCode::WARNING, "Warning" },
//   { EnumCode::NOTFOUND, "Not Found" },
// }
struct TypedEnumHasher {
  template <class T>
  size_t operator()(T t) const
  {
    return underlying_type(t);
  }
};

template <class EnumType>
constexpr size_t typedEnumSize()
{
  return TypedEnumSize(static_cast<EnumType*>(nullptr));
}

template <class EnumType>
constexpr auto typedEnumBegin()
{
  return TypedEnumAsList(static_cast<EnumType*>(nullptr)).begin();
}

template <class EnumType>
constexpr auto typedEnumEnd()
{
  return TypedEnumAsList(static_cast<EnumType*>(nullptr)).end();
}

template <typename Key>
using UnorderedMapHashType
  = typename std::conditional<
      std::is_enum<Key>::value
      , ::basic::TypedEnumHasher
      , std::hash<Key>
    >::type;

// You can use `TypedEnumUnorderedMap` with enum class or another type:
// TypedEnumUnorderedMap<int, int> myMap2;
// TypedEnumUnorderedMap<MyEnum, int> myMap3;
// TypedEnumUnorderedMap<MyEnum, std::string> myMap4;
template <typename EnumKey, typename T>
using TypedEnumUnorderedMap
  = std::unordered_map<EnumKey, T, UnorderedMapHashType<EnumKey>>;

#define TYPED_ENUM_ITEM_NAME(elem) \
    BOOST_PP_IF(BOOST_PP_IS_BEGIN_PARENS(elem), BOOST_PP_TUPLE_ELEM(2, 0, elem), elem)

#define TYPED_ENUM_ITEM_VALUE(elem) \
    BOOST_PP_EXPR_IF(BOOST_PP_IS_BEGIN_PARENS(elem), = BOOST_PP_TUPLE_ELEM(2, 1, elem))

#define TYPED_ENUM_ITEM(s, data, elem) \
    BOOST_PP_CAT(BOOST_PP_APPLY(data), TYPED_ENUM_ITEM_NAME(elem)) TYPED_ENUM_ITEM_VALUE(elem),

#define TYPED_ENUM_LIST_ITEM(s, data, elem) \
    BOOST_PP_TUPLE_ELEM(2, 0, data):: \
        BOOST_PP_CAT(BOOST_PP_APPLY(BOOST_PP_TUPLE_ELEM(2, 1, data)), TYPED_ENUM_ITEM_NAME(elem)),

#define TYPED_ENUM_CASE_NAME(s, data, elem) \
  case BOOST_PP_TUPLE_ELEM(2, 0, data):: \
      BOOST_PP_CAT(BOOST_PP_APPLY(BOOST_PP_TUPLE_ELEM(2, 1, data)), TYPED_ENUM_ITEM_NAME(elem)): \
          return BOOST_PP_STRINGIZE(TYPED_ENUM_ITEM_NAME(elem));

#define TYPED_ENUM_MAX_ENUM_NAME(enum_name, prefix, value) enum_name
#define TYPED_ENUM_MAX_PREFIX(enum_name, prefix, value) prefix
#define TYPED_ENUM_MAX_VALUE(enum_name, prefix, value) value
#define TYPED_ENUM_MAX_OP(s, data, x) \
    (TYPED_ENUM_MAX_ENUM_NAME data, \
     TYPED_ENUM_MAX_PREFIX data, \
     ::basic::typed_enum_internal::constexprMax(TYPED_ENUM_MAX_VALUE data, TYPED_ENUM_MAX_ENUM_NAME data::TYPED_ENUM_ITEM_NAME(x)))

#define TYPED_ENUM_IMPL(enum_name, enum_type, prefix, list) \
  enum class enum_name : enum_type \
  { \
    BOOST_PP_SEQ_FOR_EACH(TYPED_ENUM_ITEM, prefix, list) \
  }; \
  \
  inline ATTRIBUTE_UNUSED const char* ToCString(enum_name value) { \
    switch(value) { \
    BOOST_PP_SEQ_FOR_EACH(TYPED_ENUM_CASE_NAME, (enum_name, prefix), list); \
    } \
    return nullptr; \
  } \
  \
  inline ATTRIBUTE_UNUSED std::string ToString(enum_name value) { \
    const char* c_str = ToCString(value); \
    if (c_str != nullptr) \
      return c_str; \
    return "<unknown " BOOST_PP_STRINGIZE(enum_name) " : " + \
           std::to_string(::basic::underlying_type(value)) + ">"; \
  } \
  inline ATTRIBUTE_UNUSED std::ostream& operator<<(std::ostream& out, enum_name value) { \
    return out << ToString(value); \
  } \
  \
  constexpr ATTRIBUTE_UNUSED size_t BOOST_PP_CAT(kElementsIn, enum_name) = \
      BOOST_PP_SEQ_SIZE(list); \
  constexpr ATTRIBUTE_UNUSED size_t BOOST_PP_CAT(k, BOOST_PP_CAT(enum_name, TypedEnumSize)) = \
      static_cast<size_t>(BOOST_PP_TUPLE_ELEM(3, 2, \
          BOOST_PP_SEQ_FOLD_LEFT( \
              TYPED_ENUM_MAX_OP, \
              (enum_name, prefix, enum_name::TYPED_ENUM_ITEM_NAME(BOOST_PP_SEQ_HEAD(list))), \
              BOOST_PP_SEQ_TAIL(list)))) + 1; \
  constexpr ATTRIBUTE_UNUSED std::initializer_list<enum_name> \
      BOOST_PP_CAT(k, BOOST_PP_CAT(enum_name, List)) = {\
          BOOST_PP_SEQ_FOR_EACH(TYPED_ENUM_LIST_ITEM, (enum_name, prefix), list) \
  };\
  /* Functions returning kEnumTypedEnumSize and kEnumList that could be used in templates. */ \
  constexpr ATTRIBUTE_UNUSED size_t TypedEnumSize(enum_name*) { \
    return BOOST_PP_CAT(k, BOOST_PP_CAT(enum_name, TypedEnumSize)); \
  } \
  constexpr ATTRIBUTE_UNUSED auto TypedEnumAsList(enum_name*) { \
    return BOOST_PP_CAT(k, BOOST_PP_CAT(enum_name, List)); \
  } \
  /**/

// Please see the usage of basic_DEFINE_ENUM before the auxiliary macros above.
#define TYPED_ENUM(enum_name, enum_type, list) \
  TYPED_ENUM_IMPL(enum_name, enum_type, BOOST_PP_NIL, list)

/// \todo support for custom prefix
// USAGE
//
// PREFIXED_TYPED_ENUM(MyEnum, int, k, (Foo)(Bar)(Baz))
#define PREFIXED_TYPED_ENUM(enum_name, enum_type, prefix, list) \
  TYPED_ENUM_IMPL(enum_name, enum_type, (prefix), list)

// This macro can be used after exhaustive (compile-time-checked) switches on enums without a
// default clause to handle invalid values due to memory corruption.
//
// switch (my_enum_value) {
//   case MyEnum::FOO:
//     // some handling
//     return;
//   . . .
//   case MyEnum::BAR:
//     // some handling
//     return;
// }
// FATAL_INVALID_ENUM_VALUE(MyEnum, my_enum_value);
//
// This uses a function marked with ATTRIBUTE_NORETURN
// so that the compiler will not complain about
// functions not returning a value.
//
// We need to specify the enum name because there does not seem to be an non-RTTI way to get
// a type name string from a type in a template.
#define FATAL_INVALID_ENUM_VALUE(enum_type, value_macro_arg) \
    do { \
      auto _value_copy = (value_macro_arg); \
      static_assert( \
          std::is_same<decltype(_value_copy), enum_type>::value, \
          "Type of enum value passed to FATAL_INVALID_ENUM_VALUE must be " \
          BOOST_PP_STRINGIZE(enum_type)); \
      ::basic::typed_enum_internal::LogInvalidEnumValue<enum_type>( \
          BOOST_PP_STRINGIZE(enum_type), std::string(), _value_copy, \
          BOOST_PP_STRINGIZE(value_macro_arg), FROM_HERE); \
    } while (0)

#define FATAL_INVALID_PB_ENUM_VALUE(enum_type, value_macro_arg) \
    do { \
      auto _value_copy = (value_macro_arg); \
      static_assert( \
          std::is_same<decltype(_value_copy), enum_type>::value, \
          "Type of enum value passed to FATAL_INVALID_ENUM_VALUE must be " \
          BOOST_PP_STRINGIZE(enum_type)); \
      ::basic::typed_enum_internal::LogInvalidEnumValue<enum_type>( \
          BOOST_PP_STRINGIZE(enum_type), BOOST_PP_CAT(enum_type, _Name)(_value_copy), _value_copy, \
          BOOST_PP_STRINGIZE(value_macro_arg), FROM_HERE); \
    } while (0)

// ------------------------------------------------------------------------------------------------
// Enum bit set
// ------------------------------------------------------------------------------------------------

template <class EnumType>
class TypedEnumBitSetIterator {
 public:
  typedef ::basic::TypedEnumConstIterator<EnumType> ImplIterator;
  typedef std::bitset<basic::typedEnumSize<EnumType>()> BitSet;

  TypedEnumBitSetIterator(
    ImplIterator iter
    , const BitSet* set)
    : iter_(iter)
    , set_(set)
  {
    FindNextSetBit();
  }

  EnumType operator*() const
  {
    return *iter_;
  }

  TypedEnumBitSetIterator& operator++()
  {
    ++iter_;
    FindNextSetBit();
    return *this;
  }

  TypedEnumBitSetIterator operator++(int)
  {
    TypedEnumBitSetIterator result(*this);
    ++(*this);
    return result;
  }

 private:
  void FindNextSetBit()
  {
    while (iter_ != ::basic::typedEnumEnd<EnumType>()
           && !set_->test(underlying_type(*iter_)))
    {
      ++iter_;
    }
  }

  friend bool operator!=(
    const TypedEnumBitSetIterator<EnumType>& lhs
    , const TypedEnumBitSetIterator<EnumType>& rhs)
  {
    return lhs.iter_ != rhs.iter_;
  }

  ImplIterator iter_;
  const BitSet* set_;
};

// TypedEnumBitSet wraps std::bitset for enum type,
// to avoid casting to/from underlying type for each
// operation.
// Also adds type safety.
template <class EnumType>
class TypedEnumBitSet {
 public:
  typedef TypedEnumBitSetIterator<EnumType> const_iterator;

  TypedEnumBitSet() = default;
  explicit TypedEnumBitSet(uint64_t value) : impl_(value) {}

  explicit TypedEnumBitSet(const std::initializer_list<EnumType>& inp)
  {
    for (auto i : inp) {
      DCHECK(underlying_type(i) >= 0
        && ::base::checked_cast<size_t>(underlying_type(i))
            < ::basic::typedEnumSize<EnumType>());
      impl_.set(underlying_type(i));
    }
  }

  bool Test(EnumType value) const
  {
    DCHECK(underlying_type(value) >= 0
      && ::base::checked_cast<size_t>(underlying_type(value))
           < ::basic::typedEnumSize<EnumType>());
    return impl_.test(underlying_type(value));
  }

  uintptr_t ToUIntPtr() const {
    return impl_.to_ulong();
  }

  bool None() const {
    return impl_.none();
  }

  bool Any() const {
    return impl_.any();
  }

  bool All() const {
    return impl_.all();
  }

  // returns the number of bits set to true
  size_t CountSet() const {
    return impl_.count();
  }

  // returns the number of bits that the bitset holds
  size_t Size() const {
    return impl_.size();
  }

  // Sets the bit to true.
  TypedEnumBitSet& Set(EnumType value)
  {
    DCHECK(underlying_type(value) >= 0
      && ::base::checked_cast<size_t>(underlying_type(value))
           < ::basic::typedEnumSize<EnumType>());
    impl_.set(underlying_type(value));
    return *this;
  }

  // Sets the bit to false.
  TypedEnumBitSet& Unset(EnumType value)
  {
    DCHECK(underlying_type(value) >= 0
      && ::base::checked_cast<size_t>(underlying_type(value))
           < ::basic::typedEnumSize<EnumType>());
    impl_.reset(underlying_type(value));
    return *this;
  }

  // Toggles the value of bit
  TypedEnumBitSet& Flip(EnumType value)
  {
    DCHECK(underlying_type(value) >= 0
      && ::base::checked_cast<size_t>(underlying_type(value))
           < ::basic::typedEnumSize<EnumType>());
    impl_.flip(underlying_type(value));
    return *this;
  }

  const_iterator begin() const {
    return const_iterator(basic::typedEnumBegin<EnumType>(), &impl_);
  }

  const_iterator end() const {
    return const_iterator(basic::typedEnumEnd<EnumType>(), &impl_);
  }

  TypedEnumBitSet<EnumType>& operator|=(const TypedEnumBitSet& rhs) {
    impl_ |= rhs.impl_;
    return *this;
  }

  TypedEnumBitSet<EnumType>& operator&=(const TypedEnumBitSet& rhs) {
    impl_ &= rhs.impl_;
    return *this;
  }

  bool operator==(const TypedEnumBitSet<EnumType>& rhs) const {
    return impl_ == rhs.impl_;
  }

  bool operator!=(const TypedEnumBitSet<EnumType>& rhs) const {
    return impl_ != rhs.impl_;
  }

  bool operator<(const TypedEnumBitSet<EnumType>& rhs) const {
    return impl_.to_ullong() < rhs.impl_.to_ullong();
  }

  bool operator>(const TypedEnumBitSet<EnumType>& rhs) const {
    return impl_.to_ullong() > rhs.impl_.to_ullong();
  }

 private:
  std::bitset<basic::typedEnumSize<EnumType>()> impl_;

  friend TypedEnumBitSet<EnumType> operator&
    (const TypedEnumBitSet& lhs, const TypedEnumBitSet& rhs)
  {
    TypedEnumBitSet<EnumType> result;
    result.impl_ = lhs.impl_ & rhs.impl_;
    return result;
  }

  friend TypedEnumBitSet<EnumType> operator|
    (const TypedEnumBitSet& lhs, const TypedEnumBitSet& rhs)
  {
    TypedEnumBitSet<EnumType> result;
    result.impl_ = lhs.impl_ | rhs.impl_;
    return result;
  }
};

}  // namespace basic
