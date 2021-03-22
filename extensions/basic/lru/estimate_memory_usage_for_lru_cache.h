#pragma once

#include <basic/lru/lru_cache.h>

#include <base/trace_event/memory_usage_estimator.h>

namespace base {
namespace trace_event {

namespace internal {

template <class NodeType>
size_t DoEstimateMemoryUsageForMappedListNodeWithKey(const NodeType& node) {
  return base::trace_event::EstimateMemoryUsage(node.key_)
         + sizeof(decltype(node.mapped_value_))
         + sizeof(decltype(node.prev_))
         + sizeof(decltype(node.next_));
}

template <class LruCacheType>
size_t DoEstimateMemoryUsageForLruCache(const LruCacheType& mru_cache) {
  return base::trace_event::EstimateMemoryUsage(mru_cache.ordering_) +
         base::trace_event::EstimateMemoryUsage(mru_cache.map_);
}

}  // namespace internal

template <class Key,
          class Payload>
size_t EstimateMemoryUsage(
    const typename basic::MappedListNodeWithKey<Key, Payload>& node) {
  return internal::DoEstimateMemoryUsageForMappedListNodeWithKey(node);
}

template <class Key,
          class Payload>
size_t EstimateMemoryUsage(
    const basic::LruCache<Key, Payload>& mru_cache) {
  return internal::DoEstimateMemoryUsageForLruCache(mru_cache);
}

}  // namespace trace_event
}  // namespace base
