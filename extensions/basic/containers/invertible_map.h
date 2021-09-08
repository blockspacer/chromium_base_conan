#pragma once

#include <fstream>
#include <iterator>
#include <utility>
#include <map>
#include <unordered_map>
#include <string>

namespace basic
{

//
// This data structure indexes by keys as well as values,
// allowing constant amortized lookup time by key or value.
// All keys and values must be unique.
//
template <class Key, class Value>
class InvertibleMap
{
 public:
  InvertibleMap();

  //
  // returns whether the invertible map is empty
  //
  bool empty() const;

  //
  // returns the number of elements in the invertible map
  //
  size_t size() const;

  //
  // returns a key given a value
  //
  Key getKey(const Value& valueToSearchBy) const;

  //
  // returns a value given a key
  //
  Value getValue(const Key& keyToSearchFor) const;

  //
  // returns whether the map contains the given key
  //
  bool containsKey(const Key& keyToSearchFor) const;

  //
  // returns whether the map contains the given value
  //
  bool containsValue(const Value& valueToSearchFor) const;

  //
  // Inserts a (key, value) pair into the invertible map
  //
  void insert(const Key& keyToInsert, const Value& valueToInsert);

  //
  // Convenience function to add a (key, value)
  // pair into the invertible
  // map.
  void insert(const std::pair<Key, Value>& pairToAdd);

  //
  // Frees all keys from this object.
  //
  void clear();

  //
  // The "inner" iterator representation of the InvertibleMap.
  //
  typedef typename std::unordered_map
      <Key, Value>::const_iterator InnerIterator;

  //
  // The InvertibleMap iterator is really just a wrapper
  // for the forward (key -> value) unordered_map iterator.
  // Use this iterator class the
  // same way you'd use it on an unordered_map.
  //
  class Iterator : public std::iterator
                   <std::bidirectional_iterator_tag,
                    InnerIterator>
  {
    private:
      // The iterator of the underlying unordered_map
      InnerIterator iter;

    public:
      Iterator()
      {}

      Iterator(const InnerIterator& other) : iter{other}
      {}

      Iterator& operator++()
      {
        ++iter;
        return *this;
      }

      Iterator operator++(int)
      {
        InnerIterator save = iter;
        ++iter;
        return Iterator{save};
      }

      Iterator& operator--()
      {
        --iter;
        return *this;
      }

      Iterator operator--(int)
      {
        InnerIterator save = iter;
        --iter;
        return Iterator{save};
      }

      bool operator==(const Iterator& other)
      {
        return iter == other.iter;
      }

      bool operator!=(const Iterator& other)
      {
        return iter != other.iter;
      }

      //
      // Dereference operator. Returns the underlying value_type,
      //  which will always be a std::pair<Key, Value>
      // returns reference to the value of the object that is dereferenced
      //
      const typename InnerIterator::value_type& operator*()
      {
        return *iter;
      }

      //
      // Arrow operator. Returns a pointer to the underlying
      // value_type, which will always be a std::pair<Key, Value>
      // returns a pointer to the value of the object that is dereferenced
      //
      const typename InnerIterator::value_type* operator->()
      {
        return &(*iter);
      }
  };

  //
  // Easier typename to deal with if capital, also lets const_iterator
  // share same name
  //
  typedef Iterator iterator;

  // Lets const_iterator be interchangeable with "iterator"
  typedef Iterator const_iterator;

  //
  // returns iterator to the beginning of this container
  //
  const_iterator begin() const;

  //
  // returns iterator to the end of this container
  //
  const_iterator end() const;

private:
  // The internal map representing Key -> Value pairs
  std::unordered_map<Key, Value> forward_;

  // The internal map representing Value -> Key pairs
  std::unordered_map<Value, Key> backward_;

public:
  //
  // Basic exception for InvertibleMap interactions.
  //
  class InvertibleMap_exception : public std::runtime_error
  {
    public:
      using std::runtime_error::runtime_error;
  };
};

template <class Key, class Value>
InvertibleMap<Key, Value>::InvertibleMap()
{}

template <class Key, class Value>
bool InvertibleMap<Key, Value>::empty() const
{
  return forward_.empty();
}

template <class Key, class Value>
void InvertibleMap<Key, Value>::clear()
{
  forward_.clear();
  backward_.clear();
}

template <class Key, class Value>
size_t InvertibleMap<Key, Value>::size() const
{
  return forward_.size();
}

template <class Key, class Value>
Key InvertibleMap<Key, Value>::getKey(
  const Value& valueToSearchBy) const
{
  auto it = backward_.find(valueToSearchBy);
  if (it == backward_.end())
    return Key();
  return it->second;
}

template <class Key, class Value>
Value InvertibleMap<Key, Value>::getValue(
  const Key& keyToSearchFor) const
{
  auto it = forward_.find(keyToSearchFor);
  if (it == forward_.end())
    return Value{};
  return it->second;
}

template <class Key, class Value>
bool InvertibleMap<Key, Value>::containsKey(
  const Key& keyToSearchFor) const
{
  return forward_.find(keyToSearchFor) != forward_.end();
}

template <class Key, class Value>
bool InvertibleMap<Key, Value>::containsValue(
  const Value& valueToSearchFor) const
{
  return backward_.find(valueToSearchFor) != backward_.end();
}

template <class Key, class Value>
void InvertibleMap<Key, Value>::insert(
  const Key& keyToInsert, const Value& valueToInsert)
{
  forward_.insert(std::make_pair(keyToInsert, valueToInsert));
  backward_.insert(std::make_pair(valueToInsert, keyToInsert));
}

template <class Key, class Value>
void InvertibleMap<Key, Value>::insert(
  const std::pair<Key, Value>& pairToAdd)
{
  forward_.insert(pairToAdd);
  backward_.insert(std::make_pair(
    pairToAdd.second, pairToAdd.first));
}

template <class Key, class Value>
typename InvertibleMap<Key, Value>::const_iterator
InvertibleMap<Key, Value>::begin() const
{
  return Iterator{forward_.begin()};
}

template <class Key, class Value>
typename InvertibleMap<Key, Value>::const_iterator
InvertibleMap<Key, Value>::end() const
{
  return Iterator{forward_.end()};
}

} // namespace basic
