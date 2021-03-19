#pragma once

#include <memory>

#include <basic/rvalue_cast.h>

// MOTIVATION
//
// Comparing and hashing pointers using pointed-to values
// instead of pointer addresses.
//
// USAGE
//
//  std::multiset<
//    shared_ptr<string>, ptr_element_less<shared_ptr<string>>
//  > _multiset;
//
//  std::unordered_map<
//    shared_ptr<string>
//    , bool
//    , ptr_element_hash<shared_ptr<string>>
//    , ptr_element_equal_to<shared_ptr<string>>
//  > _unordered_map;
//
namespace basic {

template<
  typename Pointer
  , typename Equal
      = std::equal_to<typename std::pointer_traits<Pointer>::element_type>
>
struct ptr_element_equal_to
{
  Equal _eq;

  ptr_element_equal_to(Equal eq = Equal())
    : _eq(RVALUE_CAST(eq))
  {}

  bool operator()(const Pointer& i1, const Pointer& i2) const
  {
    if (bool(i1) ^ bool(i2))
    {
      return false;
    }

    return !i1 || _eq(*i1, *i2);
  }
};

template<
  typename Pointer
  , typename Less
      = std::less<typename std::pointer_traits<Pointer>::element_type>
>
struct ptr_element_less
{
    Less _cmp;

    ptr_element_less(Less cmp = Less())
      : _cmp(RVALUE_CAST(cmp))
    {}

    bool operator()(const Pointer& i1, const Pointer& i2) const
    {
      if (i1 && i2) {
        return _cmp(*i1, *i2);
      }
      return !i1 && i2;
    }
};

template<
  typename Pointer
  , typename Hash
      = std::hash<typename std::pointer_traits<Pointer>::element_type>
>
struct ptr_element_hash {
  Hash _h;

  ptr_element_hash(Hash h = Hash())
    : _h(RVALUE_CAST(h))
  {}

  size_t operator()(const Pointer& p) const
  {
    if (p) {
        return _h(*p);
    }
    return 0;
  }
};

} // namespace basic
