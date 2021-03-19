#pragma once

#include "basic/concept/dependent_false.h"

#include <vector>
#include <string>

// MOTIVATION
//
// Maps some types with custom (provided by API user) string names.
// You can use it for debug puproses.
// (bool to "boolean", not "bool" i.e. no code generation possible here).
//
// USAGE
//
// // add custom type to `type_name()`
// DECLARE_TYPE_NAME(MyType, "my_type_is_super_cool")
//
// class CustomTypeNameGeneratorTag;
//
// // add same custom type to `type_name()`, but with other generator
// DECLARE_CUSTOM_TYPE_NAME(MyType, "my_type_is_super_cool", CustomTypeNameGeneratorTag)
//
namespace basic {

// Usage: `type_name<Type, DefaultTypeNameGeneratorTag>()`
class DefaultTypeNameGeneratorTag;

// the string representation of type name
/// \note You can create custom `NameGeneratorTag`
/// to prevent `type_name()` collision.
template<typename T, typename NameGeneratorTag = ::basic::DefaultTypeNameGeneratorTag>
inline const char* type_name() {
  static_assert(dependent_false<T>::value
    , "type_name() does not support provided type.");
  return "";
}

// macro to quickly declare traits information
#define DECLARE_CUSTOM_TYPE_NAME(Type, Name, Tag)     \
  template<>                                          \
  inline const char* type_name<Type, Tag>() {         \
    return Name;                                      \
  }

// macro to quickly declare traits information
#define DECLARE_TYPE_NAME(Type, Name)                 \
  DECLARE_CUSTOM_TYPE_NAME(Type, Name, ::basic::DefaultTypeNameGeneratorTag)

DECLARE_TYPE_NAME(int32_t, "int32")

// int (non-negative)
DECLARE_TYPE_NAME(uint32_t, "uint32")

DECLARE_TYPE_NAME(int64_t, "int64")

// long (non-negative)
DECLARE_TYPE_NAME(uint64_t, "uint64")

DECLARE_TYPE_NAME(std::string, "std::string")

DECLARE_TYPE_NAME(bool, "boolean")

DECLARE_TYPE_NAME(float, "float")

DECLARE_TYPE_NAME(double, "double")

// redefinition
//DECLARE_TYPE_NAME(size_t, "size_t")

// redefinition
// DECLARE_TYPE_NAME(unsigned, "unsigned")

// redefinition
// DECLARE_TYPE_NAME(int, "int")

}  // namespace basic
