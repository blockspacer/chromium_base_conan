#pragma once

#include <vector>
#include <string>

namespace base {

// safely get the beginning address of a vector
template<typename T>
inline T* beginningAddress(
  std::vector<T>& vec)
{
  if (vec.size() == 0) {
    return nullptr;
  }
  return &vec[0];
}

// safely get the beginning address of a vector
// (const overload)
template<typename T>
inline const T* beginningAddress(
  const std::vector<T>& vec)
{
  if (vec.size() == 0) {
    return nullptr;
  }
  return &vec[0];
}


// safely get the beginning address of a string
inline char* beginningAddress(
  std::string& str)
{
  if (str.length() == 0) {
    return nullptr;
  }
  return &str[0];
}

// safely get the beginning address of a string
// (const overload)
inline const char* beginningAddress(
  const std::string& str)
{
  if (str.length() == 0) {
    return nullptr;
  }
  return &str[0];
}

}  // namespace base
