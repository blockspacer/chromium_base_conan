#pragma once

#include "base/logging.h"
#include "base/check.h"

#include <unordered_map>
#include <memory>
#include <cstddef>

namespace basic {

// Traditional Disjoint-Set datastructure with path compression.
//
// Disjoint-Set datastructure, also called a union–find data structure
// or merge–find set, is a data structure that stores a collection
// of disjoint (non-overlapping) sets.
//
// USAGE
//
//  DisjointSets<int> sets;
//  sets.MarkSet(1);
//  sets.MarkSet(2);
//  sets.MarkSet(3);
//
//  sets.Union(1, 3);
//
//  if (sets.IsSameSet(2, 3))
//   ....
//
template <typename NodeType>
class DisjointSets {
 public:
  DisjointSets(const DisjointSets& other) = delete;
  DisjointSets(DisjointSets&& other);
  DisjointSets();
  ~DisjointSets() = default;

  DisjointSets& operator=(const DisjointSets& other) = delete;
  DisjointSets& operator=(DisjointSets&& other);

  void AddToSet(NodeType);
  bool IsInSameSet(NodeType lhs, NodeType rhs) const;
  void UnionMerge(NodeType lhs, NodeType rhs);

 private:
  // Set element with rank and representative.
  // All the elements that belong to the same set are part of the same tree, and
  // utimately represented by the root of that tree.
  struct SetRep {
    // The element.
    NodeType const element_;
    // Parent in the tree used to encode the set.
    SetRep* leader_;
    // Rank in the tree, used to figure out how to compress the path to the root
    // of the tree.
    size_t rank_;

    explicit SetRep(NodeType element)
      : element_(element)
      , leader_(this)
      , rank_(0)
    {}

    ~SetRep() = default;

   private:
    DISALLOW_COPY_AND_ASSIGN(SetRep);
  };

  // Find leader (representative) for element
  // Each set is represented by its representative (leader or parent) which is one of its members.
  SetRep* FindLeaderOrNull(NodeType element) const;

  // Find element in `storage_`
  SetRep* FindInStorageOrNull(NodeType element) const;

  std::unordered_map<NodeType, std::unique_ptr<SetRep>> storage_;
};

template <typename NodeType>
DisjointSets<NodeType>::DisjointSets(DisjointSets&& other)
  : storage_(std::move(other.storage_))
{}

template <typename NodeType>
DisjointSets<NodeType>::DisjointSets()
{}

template <typename NodeType>
DisjointSets<NodeType>& DisjointSets<NodeType>::operator=(DisjointSets&& other)
{
  storage_ = std::move(other.storage_);
  return *this;
}

template <typename NodeType>
typename DisjointSets<NodeType>::SetRep* DisjointSets<NodeType>::FindLeaderOrNull(
  NodeType element) const
{
  DisjointSets<NodeType>::SetRep* const set = FindInStorageOrNull(element);

  if(!set) return nullptr;

  // Return the representative for the set, which is the root of the tree. Apply
  // path compression to speedup future queries.
  DCHECK(set->leader_);
  if (set->leader_ != set)
  {
    // Same as `set->leader_ = FindLeaderOrNull(set->leader_->element_);`
    SetRep* node = set;
    SetRep* root = set->leader_;
    DCHECK(root);
    while (root != root->leader_) {
      root = root->leader_;
      DCHECK(root);
    }
    while (node->leader_ != root) {
      SetRep* next = node->leader_;
      node->leader_ = root;
      node = next;
      DCHECK(node);
    }
  }

  return set->leader_;
}

template <typename NodeType>
typename DisjointSets<NodeType>::SetRep* DisjointSets<NodeType>::FindInStorageOrNull(
  NodeType element) const
{
  auto const it = storage_.find(element);

  if(it == storage_.end()) return nullptr;

  return it->second.get();
}

template <typename NodeType>
bool DisjointSets<NodeType>::IsInSameSet(NodeType lhs, NodeType rhs) const
{
  return FindLeaderOrNull(lhs) == FindLeaderOrNull(rhs);
}

template <typename NodeType>
void DisjointSets<NodeType>::AddToSet(NodeType element)
{
  DCHECK(!storage_.count(element));
  storage_[element] = std::make_unique<SetRep>(element);
}

template <typename NodeType>
void DisjointSets<NodeType>::UnionMerge(
  NodeType lhs, NodeType rhs)
{
  DisjointSets<NodeType>::SetRep* const set1 = FindLeaderOrNull(lhs);
  DisjointSets<NodeType>::SetRep* const set2 = FindLeaderOrNull(rhs);
  // already in the same set
  if (set1 == set2) {
    return;
  }
  DCHECK(set1);
  DCHECK(set2);
  // not in same set, so we merge them
  if (set1->rank_ < set2->rank_) {
    set1->leader_ = set2;
    return;
  }
  if (set1->rank_ > set2->rank_) {
    set2->leader_ = set1;
    return;
  }
  set2->leader_ = set1;
  ++set1->rank_;
}

} // namespace basic
