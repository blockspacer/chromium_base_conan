#pragma once

#include <type_traits>

namespace basic {

/// \note Prefer to use `basic/core/typed_enum.hpp` where possible
//
/// \note See also `basic/core/enum_set.hpp` and `basic/core/typed_enum.hpp`
//
// see http://blog.bitwigglers.org/using-enum-classes-as-type-safe-bitmasks/
//
// USAGE
//
// namespace basic {
// enum class MyCollectionPermissions
// {
//   Nothing = 0
//   , Addable
//       = 1 << 1
//   , Removable
//       = 1 << 2
//   , All
//       = MyCollectionPermissions::Addable
//         | MyCollectionPermissions::Removable
// };
// ALLOW_BITMASK_OPERATORS(MyCollectionPermissions)
// } // namespace basic
//
// namespace my_ns {
// class MyCollection
// {
//   using Permissions
//     = MyCollectionPermissions;
// };
// } // namespace my_ns

template<typename Enum>
struct EnableBitMaskOperators
{
  static const bool enable = false;
};

#define ALLOW_BITMASK_OPERATORS(Enum)  \
template<>                           \
struct EnableBitMaskOperators<Enum>     \
{                                    \
  static const bool enable = true; \
}; \
inline bool hasBit(const Enum& bitMask, \
  typename std::underlying_type<Enum>::type bit) \
{ \
  /* Has permission */ \
  return static_cast<bool>(bitMask & static_cast<Enum>(bit)); \
} \
inline bool hasBit(const Enum& bitMask, \
  const Enum& bit) \
{ \
  /* Has permission */ \
  return static_cast<bool>(bitMask & bit); \
} \
inline void addBit(Enum& bitMask, \
  typename std::underlying_type<Enum>::type bit) \
{ \
  /* Add permission */ \
  bitMask |= static_cast<Enum>(bit); \
} \
inline void addBit(Enum& bitMask, \
  const Enum& bit) \
{ \
  /* Add permission */ \
  bitMask |= bit; \
} \
inline void removeBit(Enum& bitMask, \
  typename std::underlying_type<Enum>::type bit) \
{ \
  /* Remove permission */ \
  bitMask &= ~static_cast<Enum>(bit); \
} \
inline void removeBit(Enum& bitMask, \
  const Enum& bit) \
{ \
  /* Remove permission */ \
  bitMask &= ~bit; \
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator &(Enum lhs, Enum rhs)
{
  using underlying = typename std::underlying_type<Enum>::type;
  return static_cast<Enum> (
      static_cast<underlying>(lhs) &
      static_cast<underlying>(rhs)
  );
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator ^(Enum lhs, Enum rhs)
{
  using underlying = typename std::underlying_type<Enum>::type;
  return static_cast<Enum> (
      static_cast<underlying>(lhs) ^
      static_cast<underlying>(rhs)
  );
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator ~(Enum rhs)
{
  using underlying = typename std::underlying_type<Enum>::type;
  return static_cast<Enum> (
      ~static_cast<underlying>(rhs)
  );
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator |(Enum lhs, Enum rhs)
{
  using underlying = typename std::underlying_type<Enum>::type;
  return static_cast<Enum> (
      static_cast<underlying>(lhs) |
      static_cast<underlying>(rhs)
  );
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
operator &=(Enum& lhs, Enum rhs)
{
  using underlying = typename std::underlying_type<Enum>::type;
  lhs = static_cast<Enum> (
      static_cast<underlying>(lhs) &
      static_cast<underlying>(rhs)
  );
  return lhs;
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type&
operator ^=(Enum& lhs, Enum rhs)
{
  using underlying = typename std::underlying_type<Enum>::type;
  lhs = static_cast<Enum> (
      static_cast<underlying>(lhs) ^
      static_cast<underlying>(rhs)
  );
  return lhs;
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum&>::type
operator |=(Enum& lhs, Enum rhs)
{
  using underlying = typename std::underlying_type<Enum>::type;
  lhs = static_cast<Enum> (
      static_cast<underlying>(lhs) |
      static_cast<underlying>(rhs)
  );
  return lhs;
}

} // namespace basic
