// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Derived from google3/util/gtl/stl_util.h

#ifndef BASE_STL_UTIL_H_
#define BASE_STL_UTIL_H_

#include <algorithm>
#include <deque>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <numeric>

#include "base/logging.h"
#include "base/optional.h"

namespace base {

namespace internal {

// Returns a char* pointing to the beginning of a string's internal buffer.
// The result is a valid "null-terminated byte string", even if *str is empty.
// Up to C++14 it is not valid to *write* to the null terminator; as of C++17,
// it is valid to write zero to the null terminator (but not any other value).
inline char* string_as_array(std::string* str) { return &*str->begin(); }

// The following vector_as_array functions return raw pointers to the underlying
// data buffer. The return value is unspecified (but valid) if the input range
// is empty.
template <typename T, typename Allocator>
inline T* vector_as_array(std::vector<T, Allocator>* v) {
  return v->data();
}

template <typename T, typename Allocator>
inline const T* vector_as_array(const std::vector<T, Allocator>* v) {
  return v->data();
}

// Calls erase on iterators of matching elements.
template <typename Container, typename Predicate>
void IterateAndEraseIf(Container& container, Predicate pred) {
  for (auto it = container.begin(); it != container.end();) {
    if (pred(*it))
      it = container.erase(it);
    else
      ++it;
  }
}

}  // namespace internal

// C++14 implementation of C++17's std::size():
// http://en.cppreference.com/w/cpp/iterator/size
template <typename Container>
constexpr auto size(const Container& c) -> decltype(c.size()) {
  return c.size();
}

template <typename T, size_t N>
constexpr size_t size(const T (&array)[N]) noexcept {
  return N;
}

// C++14 implementation of C++17's std::empty():
// http://en.cppreference.com/w/cpp/iterator/empty
template <typename Container>
constexpr auto empty(const Container& c) -> decltype(c.empty()) {
  return c.empty();
}

template <typename T, size_t N>
constexpr bool empty(const T (&array)[N]) noexcept {
  return false;
}

template <typename T>
constexpr bool empty(std::initializer_list<T> il) noexcept {
  return il.size() == 0;
}

// C++14 implementation of C++17's std::data():
// http://en.cppreference.com/w/cpp/iterator/data
template <typename Container>
constexpr auto data(Container& c) -> decltype(c.data()) {
  return c.data();
}

// std::basic_string::data() had no mutable overload prior to C++17 [1].
// Hence this overload is provided.
// Note: str[0] is safe even for empty strings, as they are guaranteed to be
// null-terminated [2].
//
// [1] http://en.cppreference.com/w/cpp/string/basic_string/data
// [2] http://en.cppreference.com/w/cpp/string/basic_string/operator_at
template <typename CharT, typename Traits, typename Allocator>
CharT* data(std::basic_string<CharT, Traits, Allocator>& str) {
  return std::addressof(str[0]);
}

template <typename Container>
constexpr auto data(const Container& c) -> decltype(c.data()) {
  return c.data();
}

template <typename T, size_t N>
constexpr T* data(T (&array)[N]) noexcept {
  return array;
}

template <typename T>
constexpr const T* data(std::initializer_list<T> il) noexcept {
  return il.begin();
}

// Returns a const reference to the underlying container of a container adapter.
// Works for std::priority_queue, std::queue, and std::stack.
template <class A>
const typename A::container_type& GetUnderlyingContainer(const A& adapter) {
  struct ExposedAdapter : A {
    using A::c;
  };
  return adapter.*&ExposedAdapter::c;
}

// Clears internal memory of an STL object.
// STL clear()/reserve(0) does not always free internal memory allocated
// This function uses swap/destructor to ensure the internal memory is freed.
template<class T>
void STLClearObject(T* obj) {
  T tmp;
  tmp.swap(*obj);
  // Sometimes "T tmp" allocates objects with memory (arena implementation?).
  // Hence using additional reserve(0) even if it doesn't always work.
  obj->reserve(0);
}

// Counts the number of instances of val in a container.
template <typename Container, typename T>
typename std::iterator_traits<
    typename Container::const_iterator>::difference_type
STLCount(const Container& container, const T& val) {
  return std::count(container.begin(), container.end(), val);
}

// Test to see if a set or map contains a particular key.
// Returns true if the key is in the collection.
template <typename Collection, typename Key>
bool ContainsKey(const Collection& collection, const Key& key) {
  return collection.find(key) != collection.end();
}

// Returns true iff the given collection contains the given key-value pair.
template <class Collection, class Key, class Value>
bool ContainsKeyValuePair(const Collection& collection, const Key& key, const Value& value) {
    typedef typename Collection::const_iterator const_iterator;
    std::pair<const_iterator, const_iterator> range = collection.equal_range(key);
    for (const_iterator it = range.first; it != range.second; ++it) {
        if (it->second == value) {
            return true;
        }
    }
    return false;
}

// Returns a pointer to the const value associated with the given key if it
// exists, or NULL otherwise.
template <class Collection>
const typename Collection::value_type::second_type* FindOrNull(
    const Collection& collection,
    const typename Collection::value_type::first_type& key) {
  typename Collection::const_iterator it = collection.find(key);
  if (it == collection.end()) {
    return 0;
  }
  return &it->second;
}

// Same as above but returns a pointer to the non-const value.
template <class Collection>
typename Collection::value_type::second_type* FindOrNull(
    Collection& collection,
    const typename Collection::value_type::first_type& key) {
  typename Collection::iterator it = collection.find(key);
  if (it == collection.end()) {
    return 0;
  }
  return &it->second;
}

// Returns a pointer to the const value associated with the greatest key
// that's less than or equal to the given key, or NULL if no such key exists.
template <class Collection>
const typename Collection::mapped_type* FindFloorOrNull(const Collection& collection,
                                                        const typename Collection::key_type& key) {
    auto it = collection.upper_bound(key);
    if (it == collection.begin()) {
        return 0;
    }
    return &(--it)->second;
}

// Same as above but returns a pointer to the non-const value.
template <class Collection>
typename Collection::mapped_type* FindFloorOrNull(Collection& collection, // NOLINT
                                                  const typename Collection::key_type& key) {
    auto it = collection.upper_bound(key);
    if (it == collection.begin()) {
        return 0;
    }
    return &(--it)->second;
}

// Returns a const-reference to the value associated with the greatest key
// that's less than or equal to the given key, or crashes if it does not exist.
template <class Collection>
const typename Collection::mapped_type& FindFloorOrDie(const Collection& collection,
                                                       const typename Collection::key_type& key) {
    auto it = collection.upper_bound(key);
    CHECK(it != collection.begin());
    return (--it)->second;
}

// Same as above, but returns a non-const reference.
template <class Collection>
typename Collection::mapped_type& FindFloorOrDie(Collection& collection,
                                                 const typename Collection::key_type& key) {
    auto it = collection.upper_bound(key);
    CHECK(it != collection.begin());
    return (--it)->second;
}

// Returns the pointer value associated with the given key. If none is found,
// NULL is returned. The function is designed to be used with a map of keys to
// pointers.
//
// This function does not distinguish between a missing key and a key mapped
// to a NULL value.
template <class Collection>
typename Collection::value_type::second_type FindPtrOrNull(
    const Collection& collection,
    const typename Collection::value_type::first_type& key) {
  typename Collection::const_iterator it = collection.find(key);
  if (it == collection.end()) {
    return typename Collection::value_type::second_type();
  }
  return it->second;
}

// FindPtrOrNull like function for maps whose value is a smart pointer like shared_ptr or
// unique_ptr.
// Returns the raw pointer contained in the smart pointer for the first found key, if it exists,
// or null if it doesn't.
template <class Collection>
typename Collection::mapped_type::element_type* FindPointeeOrNull(
        const Collection& collection, // NOLINT,
        const typename Collection::key_type& key) {
    auto it = collection.find(key);
    if (it == collection.end()) {
        return nullptr;
    }
    return it->second.get();
}

// Finds the value associated with the given key and copies it to *value (if not
// NULL). Returns false if the key was not found, true otherwise.
template <class Collection, class Key, class Value>
bool FindCopy(const Collection& collection, const Key& key, Value* const value) {
    auto it = collection.find(key);
    if (it == collection.end()) {
        return false;
    }
    if (value) {
        *value = it->second;
    }
    return true;
}

// Returns a const reference to the value associated with the given key if it
// exists. Crashes otherwise.
//
// This is intended as a replacement for operator[] as an rvalue (for reading)
// when the key is guaranteed to exist.
//
// operator[] for lookup is discouraged for several reasons:
//  * It has a side-effect of inserting missing keys
//  * It is not thread-safe (even when it is not inserting, it can still
//      choose to resize the underlying storage)
//  * It invalidates iterators (when it chooses to resize)
//  * It default constructs a value object even if it doesn't need to
//
// This version assumes the key is printable, and includes it in the fatal log
// message.
template <class Collection>
const typename Collection::value_type::second_type& FindOrDie(
    const Collection& collection,
    const typename Collection::value_type::first_type& key) {
  typename Collection::const_iterator it = collection.find(key);
  CHECK(it != collection.end()) << "Map key not found: " << key;
  return it->second;
}

// Same as above, but returns a non-const reference.
template <class Collection>
typename Collection::value_type::second_type& FindOrDie(
    Collection& collection,  // NOLINT
    const typename Collection::value_type::first_type& key) {
  typename Collection::iterator it = collection.find(key);
  CHECK(it != collection.end()) << "Map key not found: " << key;
  return it->second;
}

// Returns a const reference to the value associated with the given key if it
// exists, otherwise returns a const reference to the provided default value.
//
// WARNING: If a temporary object is passed as the default "value,"
// this function will return a reference to that temporary object,
// which will be destroyed at the end of the statement. A common
// example: if you have a map with string values, and you pass a char*
// as the default "value," either use the returned value immediately
// or store it in a string (not string&).
template <class Collection>
const typename Collection::value_type::second_type& FindWithDefault(
    const Collection& collection,
    const typename Collection::value_type::first_type& key,
    const typename Collection::value_type::second_type& value) {
  typename Collection::const_iterator it = collection.find(key);
  if (it == collection.end()) {
    return value;
  }
  return it->second;
}

// Inserts the given key-value pair into the collection. Returns true if and
// only if the key from the given pair didn't previously exist. Otherwise, the
// value in the map is replaced with the value from the given pair.
template <class Collection>
bool InsertOrUpdate(Collection* const collection,
                    const typename Collection::value_type& vt) {
  std::pair<typename Collection::iterator, bool> ret = collection->insert(vt);
  if (!ret.second) {
    // update
    ret.first->second = vt.second;
    return false;
  }
  return true;
}

// Same as above, except that the key and value are passed separately.
template <class Collection>
bool InsertOrUpdate(Collection* const collection,
                    const typename Collection::value_type::first_type& key,
                    const typename Collection::value_type::second_type& value) {
  return InsertOrUpdate(collection,
                        typename Collection::value_type(key, value));
}

// Inserts/updates all the key-value pairs from the range defined by the
// iterators "first" and "last" into the given collection.
template <class Collection, class InputIterator>
void InsertOrUpdateMany(Collection* const collection, InputIterator first, InputIterator last) {
    for (; first != last; ++first) {
        InsertOrUpdate(collection, *first);
    }
}

// Change the value associated with a particular key in a map or hash_map
// of the form map<Key, Value*> which owns the objects pointed to by the
// value pointers.  If there was an existing value for the key, it is deleted.
// True indicates an insert took place, false indicates an update + delete.
template <class Collection>
bool InsertAndDeleteExisting(Collection* const collection, const typename Collection::key_type& key,
                             const typename Collection::mapped_type& value) {
    std::pair<typename Collection::iterator, bool> ret =
            collection->insert(typename Collection::value_type(key, value));
    if (!ret.second) {
        delete ret.first->second;
        ret.first->second = value;
        return false;
    }
    return true;
}

// Inserts the given key and value into the given collection if and only if the
// given key did NOT already exist in the collection. If the key previously
// existed in the collection, the value is not changed. Returns true if the
// key-value pair was inserted; returns false if the key was already present.
template <class Collection>
bool InsertIfNotPresent(Collection* const collection,
                        const typename Collection::value_type& vt) {
  return collection->insert(vt).second;
}

// Same as above except the key and value are passed separately.
template <class Collection>
bool InsertIfNotPresent(
    Collection* const collection,
    const typename Collection::value_type::first_type& key,
    const typename Collection::value_type::second_type& value) {
  return InsertIfNotPresent(collection,
                            typename Collection::value_type(key, value));
}

// Same as InsertIfNotPresent except dies if the key already exists
// in the collection.
template <class Collection>
void InsertOrDie(Collection* const collection,
                 const typename Collection::value_type& vt) {
  CHECK(InsertIfNotPresent(collection, vt));
}

// Same as above except the key-value are passed separately.
template <class Collection>
void InsertOrDie(Collection* const collection,
                 const typename Collection::value_type::first_type& key,
                 const typename Collection::value_type::second_type& value) {
  CHECK(InsertIfNotPresent(collection, key, value));
}

// Inserts a new key and default-initialized value. Dies if the key was already
// present. Returns a reference to the value. Example usage:
//
// map<int, SomeProto> m;
// SomeProto& proto = InsertKeyOrDie(&m, 3);
// proto.set_field("foo");
template <class Collection>
typename Collection::mapped_type& InsertKeyOrDie(Collection* const collection,
                                                 const typename Collection::key_type& key) {
    typedef typename Collection::value_type value_type;
    std::pair<typename Collection::iterator, bool> res =
            collection->insert(value_type(key, typename Collection::mapped_type()));
    CHECK(res.second) << "duplicate key: " << key;
    return res.first->second;
}

//
// Emplace*()
//
template <class Collection, class... Args>
bool EmplaceIfNotPresent(Collection* const collection, Args&&... args) {
    return collection->emplace(std::forward<Args>(args)...).second;
}

// Emplaces the given key-value pair into the collection. Returns true if the
// given key didn't previously exist. If the given key already existed in the
// map, its value is changed to the given "value" and false is returned.
template <class Collection>
bool EmplaceOrUpdate(Collection* const collection, const typename Collection::key_type& key,
                     typename Collection::mapped_type&& value) {
    typedef typename Collection::mapped_type mapped_type;
    auto it = collection->find(key);
    if (it == collection->end()) {
        collection->emplace(key, std::forward<mapped_type>(value));
        return true;
    }
    it->second = std::forward<mapped_type>(value);
    return false;
}

template <class Collection, class... Args>
void EmplaceOrDie(Collection* const collection, Args&&... args) {
    CHECK(EmplaceIfNotPresent(collection, std::forward<Args>(args)...)) << "duplicate value";
}

// Looks up a given key and value pair in a collection and inserts the key-value
// pair if it's not already present. Returns a reference to the value associated
// with the key.
template <class Collection>
typename Collection::value_type::second_type& LookupOrInsert(
    Collection* const collection, const typename Collection::value_type& vt) {
  return collection->insert(vt).first->second;
}

// Same as above except the key-value are passed separately.
template <class Collection>
typename Collection::value_type::second_type& LookupOrInsert(
    Collection* const collection,
    const typename Collection::value_type::first_type& key,
    const typename Collection::value_type::second_type& value) {
  return LookupOrInsert(collection,
                        typename Collection::value_type(key, value));
}

// It's similar to LookupOrInsert() but uses the emplace and r-value mechanics
// to achieve the desired results. The constructor of the new element is called
// with exactly the same arguments as supplied to emplace, forwarded via
// std::forward<Args>(args). The element may be constructed even if there
// already is an element with the same key in the container, in which case the
// newly constructed element will be destroyed immediately.
// For details, see
//   https://en.cppreference.com/w/cpp/container/map/emplace
//   https://en.cppreference.com/w/cpp/container/unordered_map/emplace
template <class Collection, class... Args>
typename Collection::mapped_type& LookupOrEmplace(Collection* const collection, Args&&... args) {
    return collection->emplace(std::forward<Args>(args)...).first->second;
}

// Counts the number of equivalent elements in the given "sequence", and stores
// the results in "count_map" with element as the key and count as the value.
//
// Example:
//   vector<string> v = {"a", "b", "c", "a", "b"};
//   map<string, int> m;
//   AddTokenCounts(v, 1, &m);
//   assert(m["a"] == 2);
//   assert(m["b"] == 2);
//   assert(m["c"] == 1);
template <typename Sequence, typename Collection>
void AddTokenCounts(const Sequence& sequence, const typename Collection::mapped_type& increment,
                    Collection* const count_map) {
    for (typename Sequence::const_iterator it = sequence.begin(); it != sequence.end(); ++it) {
        typename Collection::mapped_type& value =
                LookupOrInsert(count_map, *it, typename Collection::mapped_type());
        value += increment;
    }
}


// Helpers for LookupOrInsertNew(), needed to create a new value type when the
// type itself is a pointer, i.e., these extract the actual type from a pointer.
template <class T>
void MapUtilAssignNewDefaultInstance(T** location) {
    *location = new T();
}

template <class T, class Arg>
void MapUtilAssignNewInstance(T** location, const Arg& arg) {
    *location = new T(arg);
}

// Returns a reference to the value associated with key. If not found, a value
// is default constructed on the heap and added to the map.
//
// This function is useful for containers of the form map<Key, Value*>, where
// inserting a new key, value pair involves constructing a new heap-allocated
// Value, and storing a pointer to that in the collection.
template <class Collection>
typename Collection::mapped_type& LookupOrInsertNew(Collection* const collection,
                                                    const typename Collection::key_type& key) {
    std::pair<typename Collection::iterator, bool> ret =
            collection->insert(typename Collection::value_type(
                    key, static_cast<typename Collection::mapped_type>(NULL)));
    if (ret.second) {
        // This helper is needed to 'extract' the Value type from the type of the
        // container value, which is (Value*).
        MapUtilAssignNewDefaultInstance(&(ret.first->second));
    }
    return ret.first->second;
}

// Same as above but constructs the value using the single-argument constructor
// and the given "arg".
template <class Collection, class Arg>
typename Collection::mapped_type& LookupOrInsertNew(Collection* const collection,
                                                    const typename Collection::key_type& key,
                                                    const Arg& arg) {
    std::pair<typename Collection::iterator, bool> ret =
            collection->insert(typename Collection::value_type(
                    key, static_cast<typename Collection::mapped_type>(NULL)));
    if (ret.second) {
        // This helper is needed to 'extract' the Value type from the type of the
        // container value, which is (Value*).
        MapUtilAssignNewInstance(&(ret.first->second), arg);
    }
    return ret.first->second;
}

// Lookup of linked/shared pointers is used in two scenarios:
//
// Use LookupOrInsertSharedPtr if the container does not own the elements
// for their whole lifetime. This is typically the case when a reader allows
// parallel updates to the container. In this case a Mutex only needs to lock
// container operations, but all element operations must be performed on the
// shared pointer. Finding an element must be performed using FindPtr*() and
// cannot be done with FindLinkedPtr*() even though it compiles.

// Lookup a key in a map or hash_map whose values are shared_ptrs.  If it is
// missing, set collection[key].reset(new Value::element_type). Unlike
// LookupOrInsertNewLinkedPtr, this function returns the shared_ptr instead of
// the raw pointer. Value::element_type must be default constructable.
template <class Collection>
typename Collection::mapped_type& LookupOrInsertNewSharedPtr(
        Collection* const collection, const typename Collection::key_type& key) {
    typedef typename Collection::mapped_type SharedPtr;
    typedef typename Collection::mapped_type::element_type Element;
    std::pair<typename Collection::iterator, bool> ret =
            collection->insert(typename Collection::value_type(key, SharedPtr()));
    if (ret.second) {
        ret.first->second.reset(new Element());
    }
    return ret.first->second;
}

// A variant of LookupOrInsertNewSharedPtr where the value is constructed using
// a single-parameter constructor.  Note: the constructor argument is computed
// even if it will not be used, so only values cheap to compute should be passed
// here.  On the other hand it does not matter how expensive the construction of
// the actual stored value is, as that only occurs if necessary.
template <class Collection, class Arg>
typename Collection::mapped_type& LookupOrInsertNewSharedPtr(
        Collection* const collection, const typename Collection::key_type& key, const Arg& arg) {
    typedef typename Collection::mapped_type SharedPtr;
    typedef typename Collection::mapped_type::element_type Element;
    std::pair<typename Collection::iterator, bool> ret =
            collection->insert(typename Collection::value_type(key, SharedPtr()));
    if (ret.second) {
        ret.first->second.reset(new Element(arg));
    }
    return ret.first->second;
}


// Updates the value associated with the given key. If the key was not already
// present, then the key-value pair are inserted and "previous" is unchanged. If
// the key was already present, the value is updated and "*previous" will
// contain a copy of the old value.
//
// InsertOrReturnExisting has complementary behavior that returns the
// address of an already existing value, rather than updating it.
template <class Collection>
bool UpdateReturnCopy(Collection* const collection, const typename Collection::key_type& key,
                      const typename Collection::mapped_type& value,
                      typename Collection::mapped_type* previous) {
    std::pair<typename Collection::iterator, bool> ret =
            collection->insert(typename Collection::value_type(key, value));
    if (!ret.second) {
        // update
        if (previous) {
            *previous = ret.first->second;
        }
        ret.first->second = value;
        return true;
    }
    return false;
}

// Same as above except that the key and value are passed as a pair.
template <class Collection>
bool UpdateReturnCopy(Collection* const collection, const typename Collection::value_type& vt,
                      typename Collection::mapped_type* previous) {
    std::pair<typename Collection::iterator, bool> ret = collection->insert(vt);
    if (!ret.second) {
        // update
        if (previous) {
            *previous = ret.first->second;
        }
        ret.first->second = vt.second;
        return true;
    }
    return false;
}

// Tries to insert the given key-value pair into the collection. Returns NULL if
// the insert succeeds. Otherwise, returns a pointer to the existing value.
//
// This complements UpdateReturnCopy in that it allows to update only after
// verifying the old value and still insert quickly without having to look up
// twice. Unlike UpdateReturnCopy this also does not come with the issue of an
// undefined previous* in case new data was inserted.
template <class Collection>
typename Collection::mapped_type* const InsertOrReturnExisting(
        Collection* const collection, const typename Collection::value_type& vt) {
    std::pair<typename Collection::iterator, bool> ret = collection->insert(vt);
    if (ret.second) {
        return NULL; // Inserted, no existing previous value.
    } else {
        return &ret.first->second; // Return address of already existing value.
    }
}

// Same as above, except for explicit key and data.
template <class Collection>
typename Collection::mapped_type* const InsertOrReturnExisting(
        Collection* const collection, const typename Collection::key_type& key,
        const typename Collection::mapped_type& data) {
    return InsertOrReturnExisting(collection, typename Collection::value_type(key, data));
}

// Saves the reverse mapping into reverse. Key/value pairs are inserted in the
// order the iterator returns them.
template <class Collection, class ReverseCollection>
void ReverseMap(const Collection& collection, ReverseCollection* const reverse) {
    CHECK(reverse != NULL);
    for (typename Collection::const_iterator it = collection.begin(); it != collection.end();
         ++it) {
        InsertOrUpdate(reverse, it->second, it->first);
    }
}


// Erases the collection item identified by the given key, and returns the value
// associated with that key. It is assumed that the value (i.e., the
// mapped_type) is a pointer. Returns NULL if the key was not found in the
// collection.
//
// Examples:
//   map<string, MyType*> my_map;
//
// One line cleanup:
//     delete EraseKeyReturnValuePtr(&my_map, "abc");
//
// Use returned value:
//     gscoped_ptr<MyType> value_ptr(EraseKeyReturnValuePtr(&my_map, "abc"));
//     if (value_ptr.get())
//       value_ptr->DoSomething();
//
// Note: if 'collection' is a multimap, this will only erase and return the
// first value.
template <class Collection>
typename Collection::mapped_type EraseKeyReturnValuePtr(Collection* const collection,
                                                        const typename Collection::key_type& key) {
    auto it = collection->find(key);
    if (it == collection->end()) {
        return typename Collection::mapped_type();
    }
    typename Collection::mapped_type v = std::move(it->second);
    collection->erase(it);
    return v;
}

// Inserts all the keys from map_container into key_container, which must
// support insert(MapContainer::key_type).
//
// Note: any initial contents of the key_container are not cleared.
template <class MapContainer, class KeyContainer>
void InsertKeysFromMap(const MapContainer& map_container, KeyContainer* key_container) {
    CHECK(key_container != NULL);
    for (typename MapContainer::const_iterator it = map_container.begin();
         it != map_container.end(); ++it) {
        key_container->insert(it->first);
    }
}

// Appends all the keys from map_container into key_container, which must
// support push_back(MapContainer::key_type).
//
// Note: any initial contents of the key_container are not cleared.
template <class MapContainer, class KeyContainer>
void AppendKeysFromMap(const MapContainer& map_container, KeyContainer* key_container) {
    CHECK(key_container != NULL);
    for (typename MapContainer::const_iterator it = map_container.begin();
         it != map_container.end(); ++it) {
        key_container->push_back(it->first);
    }
}

// A more specialized overload of AppendKeysFromMap to optimize reallocations
// for the common case in which we're appending keys to a vector and hence can
// (and sometimes should) call reserve() first.
//
// (It would be possible to play SFINAE games to call reserve() for any
// container that supports it, but this seems to get us 99% of what we need
// without the complexity of a SFINAE-based solution.)
template <class MapContainer, class KeyType>
void AppendKeysFromMap(const MapContainer& map_container, std::vector<KeyType>* key_container) {
    CHECK(key_container != NULL);
    // We now have the opportunity to call reserve(). Calling reserve() every
    // time is a bad idea for some use cases: libstdc++'s implementation of
    // vector<>::reserve() resizes the vector's backing store to exactly the
    // given size (unless it's already at least that big). Because of this,
    // the use case that involves appending a lot of small maps (total size
    // N) one by one to a vector would be O(N^2). But never calling reserve()
    // loses the opportunity to improve the use case of adding from a large
    // map to an empty vector (this improves performance by up to 33%). A
    // number of heuristics are possible; see the discussion in
    // cl/34081696. Here we use the simplest one.
    if (key_container->empty()) {
        key_container->reserve(map_container.size());
    }
    for (typename MapContainer::const_iterator it = map_container.begin();
         it != map_container.end(); ++it) {
        key_container->push_back(it->first);
    }
}

// Inserts all the values from map_container into value_container, which must
// support push_back(MapContainer::mapped_type).
//
// Note: any initial contents of the value_container are not cleared.
template <class MapContainer, class ValueContainer>
void AppendValuesFromMap(const MapContainer& map_container, ValueContainer* value_container) {
    CHECK(value_container != NULL);
    for (typename MapContainer::const_iterator it = map_container.begin();
         it != map_container.end(); ++it) {
        value_container->push_back(it->second);
    }
}

template <class MapContainer, class ValueContainer>
void EmplaceValuesFromMap(MapContainer&& map_container, ValueContainer* value_container) {
    CHECK(value_container != nullptr);
    // See AppendKeysFromMap for why this is done.
    if (value_container->empty()) {
        value_container->reserve(map_container.size());
    }
    for (auto&& entry : map_container) {
        value_container->emplace_back(std::move(entry.second));
    }
}

// A more specialized overload of AppendValuesFromMap to optimize reallocations
// for the common case in which we're appending values to a vector and hence
// can (and sometimes should) call reserve() first.
//
// (It would be possible to play SFINAE games to call reserve() for any
// container that supports it, but this seems to get us 99% of what we need
// without the complexity of a SFINAE-based solution.)
template <class MapContainer, class ValueType>
void AppendValuesFromMap(const MapContainer& map_container,
                         std::vector<ValueType>* value_container) {
    EmplaceValuesFromMap(map_container, value_container);
}

// Compute and insert new value if it's absent from the map. Return a pair with a reference to the
// value and a bool indicating whether it was absent at first.
//
// This inspired on a similar java construct (url split in two lines):
// https://docs.oracle.com/javase/8/docs/api/java/util/concurrent/ConcurrentHashMap.html
// #computeIfAbsent-K-java.util.function.Function
//
// It takes a reference to the key and a lambda function. If the key exists in the map, returns
// a pair with a pointer to the current value and 'false'. If the key does not exist in the map,
// it uses the lambda function to create a value, inserts it into the map, and returns a pair with
// a pointer to the new value and 'true'.
//
// Example usage:
//
// auto result = ComputeIfAbsentReturnAbsense(&my_collection,
//                                            my_key,
//                                            [] { return new_value; });
// MyValue* const value = result.first;
// if (result.second) ....
//
// The ComputePair* variants expect a lambda that creates a pair<k, v>. This
// can be useful if the key is a StringPiece pointing to external state to
// avoid excess memory for the keys, while being safer in multi-threaded
// contexts, e.g. in case the key goes out of scope before the container does.
//
// Example usage:
//
// map<StringPiece, int, GoodFastHash<StringPiece>> string_to_idx;
// vector<unique_ptr<StringPB>> pbs;
// auto result = ComputePairIfAbsentReturnAbsense(&string_to_idx, my_key,
//     [&]() {
//       unique_ptr<StringPB> s = new StringPB();
//       s->set_string(my_key);
//       int idx = pbs.size();
//       pbs.emplace_back(s.release());
//       return make_pair(StringPiece(pbs.back()->string()), idx);
//     });
template <class MapContainer, typename Function>
std::pair<typename MapContainer::mapped_type* const, bool> ComputePairIfAbsentReturnAbsense(
        MapContainer* container, const typename MapContainer::key_type& key,
        Function compute_pair_func) {
    typename MapContainer::iterator iter = container->find(key);
    bool new_value = iter == container->end();
    if (new_value) {
        auto p = compute_pair_func();
        std::pair<typename MapContainer::iterator, bool> result =
                container->emplace(std::move(p.first), std::move(p.second));
        DCHECK(result.second) << "duplicate key: " << key;
        iter = result.first;
    }
    return std::make_pair(&iter->second, new_value);
}
template <class MapContainer, typename Function>
std::pair<typename MapContainer::mapped_type* const, bool> ComputeIfAbsentReturnAbsense(
        MapContainer* container, const typename MapContainer::key_type& key,
        Function compute_func) {
    return ComputePairIfAbsentReturnAbsense(
            container, key, [&key, &compute_func] { return std::make_pair(key, compute_func()); });
};

// Like the above but doesn't return a pair, just returns a pointer to the value.
// Example usage:
//
// MyValue* const value = ComputeIfAbsent(&my_collection,
//                                        my_key,
//                                        [] { return new_value; });
//
template <class MapContainer, typename Function>
typename MapContainer::mapped_type* const ComputeIfAbsent(
        MapContainer* container, const typename MapContainer::key_type& key,
        Function compute_func) {
    return ComputeIfAbsentReturnAbsense(container, key, compute_func).first;
};

template <class MapContainer, typename Function>
typename MapContainer::mapped_type* const ComputePairIfAbsent(
        MapContainer* container, const typename MapContainer::key_type& key,
        Function compute_pair_func) {
    return ComputePairIfAbsentReturnAbsense<MapContainer, Function>(container, key,
                                                                    compute_pair_func)
            .first;
};

namespace internal {

template <typename Collection>
class HasKeyType {
  template <typename C>
  static std::true_type test(typename C::key_type*);
  template <typename C>
  static std::false_type test(...);

 public:
  static constexpr bool value = decltype(test<Collection>(nullptr))::value;
};

}  // namespace internal

// Test to see if a collection like a vector contains a particular value.
// Returns true if the value is in the collection.
// Don't use this on collections such as sets or maps. This is enforced by
// disabling this method if the collection defines a key_type.
template <typename Collection,
          typename Value,
          typename std::enable_if<!internal::HasKeyType<Collection>::value,
                                  int>::type = 0>
bool ContainsValue(const Collection& collection, const Value& value) {
  return std::find(std::begin(collection), std::end(collection), value) !=
         std::end(collection);
}

// Returns true if the container is sorted.
template <typename Container>
bool STLIsSorted(const Container& cont) {
  return std::is_sorted(std::begin(cont), std::end(cont));
}

// Returns a new ResultType containing the difference of two sorted containers.
template <typename ResultType, typename Arg1, typename Arg2>
ResultType STLSetDifference(const Arg1& a1, const Arg2& a2) {
  DCHECK(STLIsSorted(a1));
  DCHECK(STLIsSorted(a2));
  ResultType difference;
  std::set_difference(a1.begin(), a1.end(),
                      a2.begin(), a2.end(),
                      std::inserter(difference, difference.end()));
  return difference;
}

// Returns a new ResultType containing the union of two sorted containers.
template <typename ResultType, typename Arg1, typename Arg2>
ResultType STLSetUnion(const Arg1& a1, const Arg2& a2) {
  DCHECK(STLIsSorted(a1));
  DCHECK(STLIsSorted(a2));
  ResultType result;
  std::set_union(a1.begin(), a1.end(),
                 a2.begin(), a2.end(),
                 std::inserter(result, result.end()));
  return result;
}

// Returns a new ResultType containing the intersection of two sorted
// containers.
template <typename ResultType, typename Arg1, typename Arg2>
ResultType STLSetIntersection(const Arg1& a1, const Arg2& a2) {
  DCHECK(STLIsSorted(a1));
  DCHECK(STLIsSorted(a2));
  ResultType result;
  std::set_intersection(a1.begin(), a1.end(),
                        a2.begin(), a2.end(),
                        std::inserter(result, result.end()));
  return result;
}

// Returns true if the sorted container |a1| contains all elements of the sorted
// container |a2|.
template <typename Arg1, typename Arg2>
bool STLIncludes(const Arg1& a1, const Arg2& a2) {
  DCHECK(STLIsSorted(a1));
  DCHECK(STLIsSorted(a2));
  return std::includes(a1.begin(), a1.end(),
                       a2.begin(), a2.end());
}

// Erase/EraseIf are based on library fundamentals ts v2 erase/erase_if
// http://en.cppreference.com/w/cpp/experimental/lib_extensions_2
// They provide a generic way to erase elements from a container.
// The functions here implement these for the standard containers until those
// functions are available in the C++ standard.
// For Chromium containers overloads should be defined in their own headers
// (like standard containers).
// Note: there is no std::erase for standard associative containers so we don't
// have it either.

template <typename CharT, typename Traits, typename Allocator, typename Value>
void Erase(std::basic_string<CharT, Traits, Allocator>& container,
           const Value& value) {
  container.erase(std::remove(container.begin(), container.end(), value),
                  container.end());
}

template <typename CharT, typename Traits, typename Allocator, class Predicate>
void EraseIf(std::basic_string<CharT, Traits, Allocator>& container,
             Predicate pred) {
  container.erase(std::remove_if(container.begin(), container.end(), pred),
                  container.end());
}

template <class T, class Allocator, class Value>
void Erase(std::deque<T, Allocator>& container, const Value& value) {
  container.erase(std::remove(container.begin(), container.end(), value),
                  container.end());
}

template <class T, class Allocator, class Predicate>
void EraseIf(std::deque<T, Allocator>& container, Predicate pred) {
  container.erase(std::remove_if(container.begin(), container.end(), pred),
                  container.end());
}

template <class T, class Allocator, class Value>
void Erase(std::vector<T, Allocator>& container, const Value& value) {
  container.erase(std::remove(container.begin(), container.end(), value),
                  container.end());
}

template <class T, class Allocator, class Predicate>
void EraseIf(std::vector<T, Allocator>& container, Predicate pred) {
  container.erase(std::remove_if(container.begin(), container.end(), pred),
                  container.end());
}

template <class T, class Allocator, class Value>
void Erase(std::forward_list<T, Allocator>& container, const Value& value) {
  // Unlike std::forward_list::remove, this function template accepts
  // heterogeneous types and does not force a conversion to the container's
  // value type before invoking the == operator.
  container.remove_if([&](const T& cur) { return cur == value; });
}

template <class T, class Allocator, class Predicate>
void EraseIf(std::forward_list<T, Allocator>& container, Predicate pred) {
  container.remove_if(pred);
}

template <class T, class Allocator, class Value>
void Erase(std::list<T, Allocator>& container, const Value& value) {
  // Unlike std::list::remove, this function template accepts heterogeneous
  // types and does not force a conversion to the container's value type before
  // invoking the == operator.
  container.remove_if([&](const T& cur) { return cur == value; });
}

template <class T, class Allocator, class Predicate>
void EraseIf(std::list<T, Allocator>& container, Predicate pred) {
  container.remove_if(pred);
}

template <class Key, class T, class Compare, class Allocator, class Predicate>
void EraseIf(std::map<Key, T, Compare, Allocator>& container, Predicate pred) {
  internal::IterateAndEraseIf(container, pred);
}

template <class Key, class T, class Compare, class Allocator, class Predicate>
void EraseIf(std::multimap<Key, T, Compare, Allocator>& container,
             Predicate pred) {
  internal::IterateAndEraseIf(container, pred);
}

template <class Key, class Compare, class Allocator, class Predicate>
void EraseIf(std::set<Key, Compare, Allocator>& container, Predicate pred) {
  internal::IterateAndEraseIf(container, pred);
}

template <class Key, class Compare, class Allocator, class Predicate>
void EraseIf(std::multiset<Key, Compare, Allocator>& container,
             Predicate pred) {
  internal::IterateAndEraseIf(container, pred);
}

template <class Key,
          class T,
          class Hash,
          class KeyEqual,
          class Allocator,
          class Predicate>
void EraseIf(std::unordered_map<Key, T, Hash, KeyEqual, Allocator>& container,
             Predicate pred) {
  internal::IterateAndEraseIf(container, pred);
}

template <class Key,
          class T,
          class Hash,
          class KeyEqual,
          class Allocator,
          class Predicate>
void EraseIf(
    std::unordered_multimap<Key, T, Hash, KeyEqual, Allocator>& container,
    Predicate pred) {
  internal::IterateAndEraseIf(container, pred);
}

template <class Key,
          class Hash,
          class KeyEqual,
          class Allocator,
          class Predicate>
void EraseIf(std::unordered_set<Key, Hash, KeyEqual, Allocator>& container,
             Predicate pred) {
  internal::IterateAndEraseIf(container, pred);
}

template <class Key,
          class Hash,
          class KeyEqual,
          class Allocator,
          class Predicate>
void EraseIf(std::unordered_multiset<Key, Hash, KeyEqual, Allocator>& container,
             Predicate pred) {
  internal::IterateAndEraseIf(container, pred);
}

// A helper class to be used as the predicate with |EraseIf| to implement
// in-place set intersection. Helps implement the algorithm of going through
// each container an element at a time, erasing elements from the first
// container if they aren't in the second container. Requires each container be
// sorted. Note that the logic below appears inverted since it is returning
// whether an element should be erased.
template <class Collection>
class IsNotIn {
 public:
  explicit IsNotIn(const Collection& collection)
      : i_(collection.begin()), end_(collection.end()) {}

  bool operator()(const typename Collection::value_type& x) {
    while (i_ != end_ && *i_ < x)
      ++i_;
    if (i_ == end_)
      return true;
    if (*i_ == x) {
      ++i_;
      return false;
    }
    return true;
  }

 private:
  typename Collection::const_iterator i_;
  const typename Collection::const_iterator end_;
};

// Helper for returning the optional value's address, or nullptr.
template <class T>
T* OptionalOrNullptr(base::Optional<T>& optional) {
  return optional.has_value() ? &optional.value() : nullptr;
}

template <class T>
const T* OptionalOrNullptr(const base::Optional<T>& optional) {
  return optional.has_value() ? &optional.value() : nullptr;
}

// Map is a higher-order function that applies a function
// to the elements of a range and
// returns a new range in the same order.
//
// USAGE
//
// auto vnums =
//   std::vector<int>{0, 2, -3, 5, -1, 6, 8, -4, 9};
// auto r = mapf([](int const i) {
//   return std::abs(i); }, vnums);
// // r = {0, 2, 3, 5, 1, 6, 8, 4, 9}
//
// auto lnums = std::list<int>{1, 2, 3, 4, 5};
// auto l = mapf([](int const i) {
//   return i*i; }, lnums);
// // l = {1, 4, 9, 16, 25}
//
// template<class T = double>
// struct fround
// {
//   typename std::enable_if_t<
//   std::is_floating_point_v<T>, T>
//   operator()(const T& value) const
//   {
//     return std::round(value);
//   }
// };
// auto amounts =
//   std::array<double, 5> {10.42, 2.50, 100.0, 23.75, 12.99};
// auto a = mapf(fround<>(), amounts);
// // a = {10.0, 3.0, 100.0, 24.0, 13.0}
//
// auto words = std::map<std::string, int>{
//  {"one", 1}, {"two", 2}, {"three", 3}
// };
// auto m =   mapf(
//  [](std::pair<std::string, int> const kvp) {
//    return std::make_pair(
//    mapf(toupper, kvp.first),
//    kvp.second);
//  }, words);
// // m = {{"ONE", 1}, {"TWO", 2}, {"THREE", 3}}
//
// auto priorities = std::queue<int>();
// priorities.push(10);
// priorities.push(20);
// priorities.push(30);
// priorities.push(40);
// priorities.push(50);
// auto p = mapf(
//   [](int const i) { return i > 30 ? 2 : 1; },
//   priorities);
// // p = {1, 1, 1, 2, 2}
//
template <typename F, typename R>
R mapf(F&& func, R range)
{
  std::transform(std::begin(range), std::end(range), std::begin(range)
    , std::forward<F>(func));
  return range;
}

template<typename F, typename T, typename U>
std::map<T, U> mapf(F&& func, std::map<T, U> const & m)
{
 std::map<T, U> r;
 for (auto const kvp : m)
   r.insert(func(kvp));
 return r;
}

template<typename F, typename T>
std::queue<T> mapf(F&& func, std::queue<T> q)
{
  std::queue<T> r;
  while (!q.empty())
  {
    r.push(func(q.front()));
    q.pop();
  }
  return r;
}

// Fold is a higher-order function that applies a combining function to the elements
// of the range to produce a single result. Since the order of the processing can be
// important, there are usually two versions of this function. One is foldleft, which
// processes elements from left to right, while the other is foldright, which combines
// the elements from right to left.
//
// As an example, the mapping operation could transform a range of strings into a
// range of integers representing the length of each string. The fold operation could
// then add these lengths to determine the combined length of all the strings.
//
// USAGE
//
// auto vnums =
//   std::vector<int>{0, 2, -3, 5, -1, 6, 8, -4, 9};
// auto s1 = foldleft(
//   [](const int s, const int n) {return s + n; },
//   vnums, 0); // s1 = 22
// auto s2 = foldleft(
//   std::plus<>(), vnums, 0); // s2 = 22
//
// auto texts =
//   std::vector<std::string>{"hello"s, " "s, "world"s, "!"s};
// auto txt1 = foldleft(
//   [](std::string const & s, std::string const & n) {
//   return s + n;}, texts, ""s); // txt1 = "hello world!"
//
// char chars[] = {'c','i','v','i','c'};
// auto str1 = foldleft(std::plus<>(), chars, ""s);
// // str1 = "civic"
//
// auto words = std::map<std::string, int>{
//   {"one", 1}, {"two", 2}, {"three", 3} };
// auto count = foldleft(
//   [](int const s, std::pair<std::string, int> const kvp) {
//   return s + kvp.second; }, words, 0); // count = 6
//
// auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
// auto s = foldleft(
//   std::plus<>(),
//   mapf( [](int const i) {return i*i; },
//   mapf( [](int const i) {return std::abs(i); },
//   vnums)),
//   0); // s = 236
//
template <typename F, typename R, typename T>
constexpr T foldleft(F&& func, R&& range, T init)
{
  return std::accumulate(
  std::begin(range), std::end(range),
  std::move(init),
  std::forward<F>(func));
}

// foldright combines the elements from right to left.
//
// USAGE
//
// auto vnums =
//   std::vector<int>{0, 2, -3, 5, -1, 6, 8, -4, 9};
// auto s3 = foldright(
//   [](const int s, const int n) {return s + n; },
//   vnums, 0); // s3 = 22
//
// auto texts =
//   std::vector<std::string>{"hello"s, " "s, "world"s, "!"s};
// auto txt2 = foldright(
//   [](std::string const & s, std::string const & n) {
//   return s + n; }, texts, ""s); // txt2 = "!world hello"
//
// char chars[] = {'c','i','v','i','c'};
// auto str2 = foldright(std::plus<>(), chars, ""s);
// // str2 = "civic"
//
template <typename F, typename R, typename T>
constexpr T foldright(F&& func, R&& range, T init)
{
  return std::accumulate(
  std::rbegin(range), std::rend(range),
  std::move(init),
  std::forward<F>(func));
}

template <typename F, typename T>
constexpr T foldleft(F&& func, std::queue<T> q, T init)
{
  while (!q.empty())
  {
    init = func(init, q.front());
    q.pop();
  }
  return init;
}

// USAGE
//
// auto s1 = foldleft(std::plus<>(), 1, 2, 3, 4, 5);
// // s1 = 15
// auto s2 = foldleft(std::plus<>(), "hello"s, ' ', "world"s, '!');
// // s2 = "hello world!"
// auto s3 = foldleft(std::plus<>(), 1); // error, too few arguments
//
template <typename F, typename T1, typename T2>
auto foldleft(F&&f, T1 arg1, T2 arg2)
{
  return f(arg1, arg2);
}

template <typename F, typename T, typename... Ts>
auto foldleft(F&& f, T head, Ts... rest)
{
  return f(head, foldleft(std::forward<F>(f), rest...));
}

// compose functions into a higher-order function
//
// USAGE
//
// auto v = compose(
//   [](int const n) {return std::to_string(n); },
//   [](int const n) {return n * n; })(-3); // v = "9"
//
template <typename F, typename G>
auto compose(F&& f, G&& g)
{
  return [=](auto x) { return f(g(x)); };
}

// USAGE
//
// auto n = compose(
//   [](int const n) {return std::to_string(n); },
//   [](int const n) {return n * n; },
//   [](int const n) {return n + n; },
//   [](int const n) {return std::abs(n); })(-3); // n = "36"
//
// auto s = compose(
//   [](std::vector<int> const & v) {
//   return foldleft(std::plus<>(), v, 0); },
//   [](std::vector<int> const & v) {
//   return mapf([](int const i) {return i + i; }, v); },
//   [](std::vector<int> const & v) {
//   return mapf([](int const i) {return std::abs(i); }, v); })(vnums);
//
template <typename F, typename... R>
auto compose(F&& f, R&&... r)
{
  return [=](auto x) { return f(compose(r...)(x)); };
}

// Clamp the value to make sure it is in the range [low, high].
//
template <typename T>
inline const T& Clamp(const T& value, const T& low, const T& high) {
#if __cplusplus >= 201703L
  return std::clamp(value, low, high);
#else
  DCHECK( !(high < low) );
  return value < low ? low : (value > high ? high : value);
#endif
}

// Count the elements of [first, last).
//
template <typename Iterator>
int CountElements(Iterator first, Iterator last) {
  auto n = std::distance(first, last);
  DCHECK_GE(n, 0);
  DCHECK_LE(n, std::numeric_limits<int>::max())
    << "We only support INT_MAX elements at most.";

  return static_cast<int>(n);
}

// Sorting and keeping track of indexes
//
// Get the sorted indices of [first, last)
//
// For example, vector of samples A : [5, 2, 1, 4, 3].
// I want to sort these to be B : [1,2,3,4,5],
// but I also want to remember the original indexes of the values,
// so I can get another set which would be: C : [2, 1, 4, 3, 0 ],
// which corresponds to the index of each element in 'B', in the original 'A'.
//
// USAGE
//
// std::vector<std::string> data{"G", "A", "C", "B"};
// std::vector<size_t> sorted_indexes;
// base::IndexSort(data.begin(), data.end(), &sorted_indexes);
template <typename Iterator, typename Compare =
          std::less<typename std::iterator_traits<Iterator>::value_type> >
void IndexSort(Iterator first, Iterator last, std::vector<size_t>* indices) {
  DCHECK(indices);

  auto n = std::distance(first, last);
  indices->resize(n);
  // initialize original index locations
  std::iota(indices->begin(), indices->end(), 0);

  Compare compare;
  // sort indexes based on comparing values
  std::sort(indices->begin(), indices->end(), [&](size_t a, size_t b) {
            return compare(first[a], first[b]);
  });
}

}  // namespace base

#endif  // BASE_STL_UTIL_H_
