//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.
//
// The following only applies to changes made to this file as part of YugaByte development.
//
// Portions Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//
// Copyright (c) 2012 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#pragma once

#include <cstdlib>

#include "basic/bloom_filter/filter_policy.h"
#include "basic/numerics/pack_numbers.h"
#include "basic/macros.h"
#include "basic/compiler_specific.h"

#include <string>
#include <memory>
#include <cmath>

#include <base/macros.h>
#include <base/logging.h>
#include <basic/rvalue_cast.h>
#include <base/bind.h>
#include <base/strings/string_piece.h>
#include <base/hash/hash.h>
#include <base/compiler_specific.h>

namespace basic {

class FullFilterBitsBuilder : public FilterBitsBuilder {
 public:
  explicit FullFilterBitsBuilder(const size_t bits_per_key,
                                 const size_t num_probes)
      : bits_per_key_(bits_per_key),
        num_probes_(num_probes) {
    DCHECK(bits_per_key_);
  }

  ~FullFilterBitsBuilder() {}

  void AddKey(const base::StringPiece& key) override;

  // Create a filter that for hashes [0, n-1], the filter is allocated here
  // When creating filter, it is ensured that
  // total_bits = num_lines * BASE_CACHELINE_SIZE * 8
  // dst len is >= kMetaDataSize (5), 1 for num_probes, 4 for num_lines
  // Then total_bits = (len - kMetaDataSize) * 8, and BASE_CACHELINE_SIZE could be calculated
  // +----------------------------------------------------------------+
  // |              filter data with length total_bits / 8            |
  // +----------------------------------------------------------------+
  // |                                                                |
  // | ...                                                            |
  // |                                                                |
  // +----------------------------------------------------------------+
  // | ...                | num_probes : 1 byte | num_lines : 4 bytes |
  // +----------------------------------------------------------------+
  base::StringPiece Finish(std::unique_ptr<const char[]>* buf) override;

  virtual bool IsFull() const override { return false; }

  static constexpr size_t kMetaDataSize = 5; // in bytes

 private:
  size_t bits_per_key_;
  size_t num_probes_;
  std::vector<uint32_t> hash_entries_;

  // Get totalbits that optimized for cpu cache line
  uint32_t GetTotalBitsForLocality(uint32_t total_bits);

  // Reserve space for new filter
  char* ReserveSpace(const int num_entry, uint32_t* total_bits,
      uint32_t* num_lines);

  // No Copy allowed
  FullFilterBitsBuilder(const FullFilterBitsBuilder&);
  void operator=(const FullFilterBitsBuilder&);
};

class FullFilterBitsReader : public FilterBitsReader {
 public:
  explicit FullFilterBitsReader(const base::StringPiece& contents);

  ~FullFilterBitsReader() {}

  // Can tell you that:
  // A) given element is definitely not in the set, or
  // B) given element is maybe in the set.
  bool MayMatch(const base::StringPiece& entry) override;

 private:
  // Filter meta data
  char* data_;
  uint32_t data_len_;
  size_t num_probes_;
  uint32_t num_lines_;

  // Get num_probes, and num_lines from filter
  // If filter format broken, set both to 0.
  void GetFilterMeta(const base::StringPiece& filter, size_t* num_probes,
                             uint32_t* num_lines);

  // "filter" contains the data appended by a preceding call to
  // CreateFilterFromHash() on this class.  This method must return true if
  // the key was in the list of keys passed to CreateFilter().
  // This method may return true or false if the key was not on the
  // list, but it should aim to return false with a high probability.
  //
  // hash: target to be checked
  // filter: the whole filter, including meta data bytes
  // num_probes: number of probes, read before hand
  // num_lines: filter metadata, read before hand
  // Before calling this function, need to ensure the input meta data
  // is valid.
  bool HashMayMatch(const uint32_t hash, const base::StringPiece& filter,
      const size_t num_probes, const uint32_t num_lines);

  // No Copy allowed
  FullFilterBitsReader(const FullFilterBitsReader&);
  void operator=(const FullFilterBitsReader&);
};

// An implementation of filter policy
class BloomFilterPolicy : public FilterPolicy {
 public:
  explicit BloomFilterPolicy(int bits_per_key, bool use_block_based_builder);

  ~BloomFilterPolicy() {}

  FilterPolicy::FilterType GetFilterType() const override;

  const char* Name() const override {
    return "basic.BuiltinBloomFilter";
  }

  void CreateFilter(const base::StringPiece* keys, int n,
                            std::string* dst) const override;

  bool KeyMayMatch(const base::StringPiece& key,
                           const base::StringPiece& bloom_filter) const override;

  FilterBitsBuilder* GetFilterBitsBuilder() const override;

  FilterBitsReader* GetFilterBitsReader(const base::StringPiece& contents) const override;

  // If choose to use block based builder
  bool UseBlockBasedBuilder() { return use_block_based_builder_; }

 private:
  size_t bits_per_key_;
  size_t num_probes_;
  uint32_t (*hash_func_)(const std::string& key);

  const bool use_block_based_builder_;

  void initialize();
};

// A fixed size filter bits builder will build (with memory allocation)
// and return a Bloom filter of given size and expected false positive rate.
//
// The fixed size Bloom filter has the following encoding:
// For a given number of total bits M and the error rate p,
// we will return a block of M + 40 bits, with 40 bits for metadata
// and M bits for filter data.
// For compliance with FullFilter, the metadata will be encoded
// the same way as in FullFilter.
//
// For detailed proofs on the optimal number of keys and hash functions
// please refer to https://en.wikipedia.org/wiki/Bloom_filter.
//
// The number of hash function given error rate p is -ln p / ln 2.
// The maximum number of keys that can be inserted in a Bloom filter of m bits
// so that one maintains the false positive error rate p is -m (ln 2)^2 / ln p.
class FixedSizeFilterBitsBuilder : public FilterBitsBuilder {
 public:
  FixedSizeFilterBitsBuilder(const FixedSizeFilterBitsBuilder&) = delete;
  void operator=(const FixedSizeFilterBitsBuilder&) = delete;

  FixedSizeFilterBitsBuilder(uint32_t total_bits, double error_rate);

  virtual void AddKey(const base::StringPiece& key) override;

  virtual bool IsFull() const override;

  virtual base::StringPiece Finish(std::unique_ptr<const char[]>* buf) override;

  // Serialization format is the same as for FullFilter.
  static constexpr size_t kMetaDataSize = FullFilterBitsBuilder::kMetaDataSize;

  static const double kLog2; // std::log(2);

 private:
  inline size_t FilterSize() { return total_bits_ / 8 + kMetaDataSize; }

  std::unique_ptr<char[]> data_;
  size_t max_keys_;
  size_t keys_added_;
  uint32_t total_bits_; // total number of bits used for filter (excluding metadata)
  uint32_t num_lines_;
  double error_rate_;
  size_t num_probes_; // number of hash functions
};


class FixedSizeFilterBitsReader : public FullFilterBitsReader {
 public:
  FixedSizeFilterBitsReader(const FixedSizeFilterBitsReader&) = delete;
  void operator=(const FixedSizeFilterBitsReader&) = delete;

  explicit FixedSizeFilterBitsReader(const base::StringPiece& contents)
      : FullFilterBitsReader(contents) {}
};

class FixedSizeFilterPolicy : public FilterPolicy {
 public:
  explicit FixedSizeFilterPolicy(uint32_t total_bits, double error_rate);

  virtual FilterPolicy::FilterType GetFilterType() const override {
    return FilterType::kFixedSizeFilter;
  }

  virtual const char* Name() const override {
    return "basic.FixedSizeBloomFilter";
  }

  // Not used in FixedSizeFilter. GetFilterBitsBuilder/Reader interface should be used.
  virtual void CreateFilter(const base::StringPiece* keys, int n,
                            std::string* dst) const override {
    DCHECK(false) << "FixedSizeFilterPolicy::CreateFilter is not supported";
  }

  virtual bool KeyMayMatch(const base::StringPiece& key, const base::StringPiece& filter) const override {
    DCHECK(false) << "FixedSizeFilterPolicy::KeyMayMatch is not supported";
    return true;
  }

  virtual FilterBitsBuilder* GetFilterBitsBuilder() const override;

  virtual FilterBitsReader* GetFilterBitsReader(const base::StringPiece& contents) const override;

  static const double kLog2; // std::log(2);

 private:
  uint32_t total_bits_;
  double error_rate_;
};

const FilterPolicy* NewBloomFilterPolicy(int bits_per_key,
                                         bool use_block_based_builder);

const FilterPolicy* NewFixedSizeFilterPolicy(uint32_t total_bits,
                                             double error_rate);

}  // namespace basic
