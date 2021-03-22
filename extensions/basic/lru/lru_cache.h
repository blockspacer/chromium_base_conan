// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <memory>

#include <base/containers/linked_list.h>
#include <base/logging.h>

#include <unordered_map>

/// \note See also `base::MRUCache` in `base/containers/mru_cache.h`.
//
// LruCache is a simple least-recently-used cache based on HashMap and
// DoublyLinkedList. Useful in situations where caching by using a HashMap is
// desirable but needs to be limited in size to not grow out of proportions.
// LruCache uses a HashMap to store cache entries, and uses a DoublyLinkedList
// in parallel to keep track of the age of entries. Accessing an entry using
// Get() refreshes its age, Put() places a new entry into the HashMap with
// youngest age as well. The least recently used entry of the list is pruned
// when a Put() call would otherwise exceed the max_size limit.
//
// USAGE
//
// const size_t kMaxSize = 2;
// LruCache<uint16_t, String> my_cache(kMaxSize);
// my_cache.Put(13, "first string");
// my_cache.Put(42, "second string");
// my_cache.Put(256, "third string"); // exceed kMaxSize, will prune `13`
// my_cache.Get(13) // -> nullptr, has been removed due to kMaxSize == 2.
// my_cache.Get(42) // -> String* "second string"
// my_cache.Get(256) // -> String* "third_string"
//
// See lru_cache_test.cc for more examples.

namespace base {
namespace trace_event {
namespace internal {

template <class LruCacheType>
size_t DoEstimateMemoryUsageForLruCache(const LruCacheType&);

template <class MappedListNodeWithKeyType>
size_t DoEstimateMemoryUsageForMappedListNodeWithKey(const MappedListNodeWithKeyType&);

} // namespace internal
} // namespace trace_event
} // namespace base

namespace basic {

template <typename KeyArg,
          typename MappedArg>
class MappedListNodeWithKey final
    : public base::LinkNode<MappedListNodeWithKey<KeyArg, MappedArg> > {
 public:
  friend class base::LinkNode<MappedListNodeWithKey<KeyArg, MappedArg> >;

  MappedListNodeWithKey(const KeyArg& key, MappedArg&& mapped_arg)
      : key_(key), mapped_value_(std::move(mapped_arg)) {}

  MappedArg* Value() { return &mapped_value_; }

  void SetValue(MappedArg&& mapped_arg) {
    mapped_value_ = std::move(mapped_arg);
  }

  const KeyArg& Key() const { return key_; }

  // Estimates dynamic memory usage.
  // See base/trace_event/memory_usage_estimator.h for more info.
  size_t EstimateMemoryUsage() const {
    return base::trace_event::internal::DoEstimateMemoryUsageForMappedListNodeWithKey(*this);
  }

  template <class NodeType>
  friend size_t base::trace_event::internal::DoEstimateMemoryUsageForMappedListNodeWithKey(
      const NodeType&);

 private:
  KeyArg key_;
  MappedArg mapped_value_;
  MappedListNodeWithKey* prev_{nullptr};
  MappedListNodeWithKey* next_{nullptr};
};

template <typename KeyArg,
          typename MappedArg>
class LruCache {
 public:
  using NodeWithKey
    = MappedListNodeWithKey<KeyArg, MappedArg>;

  using MappedListNode
    = std::unique_ptr<NodeWithKey>;

  using HashMapType
    = std::unordered_map<KeyArg, MappedListNode>;

  // Pass NO_AUTO_EVICT to not restrict the cache size.
  //
  // USAGE
  //
  // typedef base::MRUCache<int, CachedItem> Cache;
  // Cache cache(Cache::NO_AUTO_EVICT);
  //
  enum { NO_AUTO_EVICT = 0 };

  LruCache(size_t max_size) : max_size_(max_size) {}

  // Retrieve cache entry under |key| if it exists and refresh its age.
  // Returns: pointer to cache entry or nullptr if no entry is found for that
  // key.
  MappedArg* Get(const KeyArg& key) {
    if (map_.empty())
      return nullptr;

    typename HashMapType::iterator find_result = map_.find(key);
    if (find_result == map_.end())
      return nullptr;

    NodeWithKey* node = find_result->second.get();
    node->RemoveFromList();
    ordering_.Prepend(node);
    return node->Value();
  }

  // Retrieves the payload associated with a given key and returns it via
  // result without affecting the ordering (unlike Get).
  MappedArg* Peek(const KeyArg& key) {
    if (map_.empty())
      return nullptr;

    typename HashMapType::iterator find_result = map_.find(key);
    if (find_result == map_.end())
      return nullptr;

    NodeWithKey* node = find_result->second.get();

    return node->Value();
  }

  // Returns the Least Recently Used T _without_ removing it
  // or affecting the ordering (unlike Get).
  MappedArg* tail() {
    if (ordering_.empty()) return nullptr;
    base::LinkNode<NodeWithKey>* node = ordering_.tail();
    DCHECK(node);
    NodeWithKey* tail = node->value();
    return tail->Value();
  }

  MappedArg* head() {
    if (ordering_.empty()) return nullptr;
    base::LinkNode<NodeWithKey>* node = ordering_.head();
    DCHECK(node);
    NodeWithKey* tail = node->value();
    return tail->Value();
  }

  // Place entry in cache as new / youngest. Multiple calls to Put() with an
  // identical key but differing MappedArg will override the stored value and
  // refresh the age.
  void Put(const KeyArg& key, MappedArg&& arg) {
    {
      typename HashMapType::iterator find_result = map_.find(key);
      if (find_result != map_.end()) {
        NodeWithKey* node = find_result->second.get();
        node->SetValue(std::move(arg));
        node->RemoveFromList();
        ordering_.Prepend(node);
      } else {
        MappedListNode list_node =
            std::make_unique<NodeWithKey>(key, std::move(arg));
        std::pair<typename HashMapType::iterator, bool> add_result =
            map_.insert_or_assign(key, std::move(list_node));
        DCHECK(add_result.second); // is_new_entry
        NodeWithKey* stored_value = add_result.first->second.get();
        ordering_.Prepend(stored_value);
      }
    }

    if (max_size_ != NO_AUTO_EVICT && map_.size() > max_size_) {
      RemoveLeastRecentlyUsed();
    }
  }

  // Clear the cache, remove all elements.
  void Clear() {
    ordering_.clear();
    map_.clear();
  }

  size_t size() { return map_.size(); }

  bool empty() const { return map_.empty(); }

  void RemoveLeastRecentlyUsed() {
    if (ordering_.empty()) return;
    base::LinkNode<NodeWithKey>* tail_node = ordering_.tail();
    DCHECK(tail_node);
    NodeWithKey* tail = tail_node->value();
    tail->RemoveFromList();
    map_.erase(tail->Key());
  }

  // Estimates dynamic memory usage.
  // See base/trace_event/memory_usage_estimator.h for more info.
  size_t EstimateMemoryUsage() const {
    return base::trace_event::internal::DoEstimateMemoryUsageForLruCache(*this);
  }

  template <class LruCacheType>
  friend size_t base::trace_event::internal::DoEstimateMemoryUsageForLruCache(
      const LruCacheType&);

 private:
  HashMapType map_;
  base::LinkedList<NodeWithKey> ordering_;
  size_t max_size_;
};

}  // namespace basic
