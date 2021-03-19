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

#include "basic/bloom_filter/bloom.h" // IWYU pragma: associated
#include "basic/compiler_specific.h"

namespace basic {

namespace {

template <class T>
constexpr T ceil_div(const T& n, const T& div) {
  return (n + div - 1) / div;
}

inline void AddHash(uint32_t h, char* data, uint32_t num_lines, uint32_t total_bits,
    size_t num_probes) {
  DCHECK_GT(num_lines, 0);
  DCHECK_GT(total_bits, 0);
  DCHECK_EQ(num_lines % 2, 1);

  const uint32_t delta = (h >> 17) | (h << 15);  // Rotate right 17 bits
  uint32_t b = (h % num_lines) * (BASE_CACHELINE_SIZE * 8);

  for (uint32_t i = 0; i < num_probes; ++i) {
    // Since BASE_CACHELINE_SIZE is defined as 2^n, this line will be optimized
    // to a simple operation by compiler.
    const uint32_t bitpos = b + (h % (BASE_CACHELINE_SIZE * 8));
    DCHECK(bitpos < total_bits);
    data[bitpos / 8] |= (1 << (bitpos % 8));

    h += delta;
  }
}

}  // namespace

void FullFilterBitsBuilder::AddKey(const base::StringPiece& key) {
  uint32_t hash = base::Hash(key.as_string());
  if (hash_entries_.size() == 0 || hash != hash_entries_.back()) {
    hash_entries_.push_back(hash);
  }
}

base::StringPiece FullFilterBitsBuilder::Finish(std::unique_ptr<const char[]>* buf) {
  uint32_t total_bits, num_lines;
  char* data = ReserveSpace(static_cast<int>(hash_entries_.size()),
                            &total_bits, &num_lines);
  DCHECK(data);

  if (total_bits != 0 && num_lines != 0) {
    for (auto h : hash_entries_) {
      AddHash(h, data, num_lines, total_bits, num_probes_);
    }
  }
  data[total_bits / 8] = static_cast<char>(num_probes_);
  EncodeFixed32(data + total_bits / 8 + 1, static_cast<uint32_t>(num_lines));

  const char* const_data = data;
  buf->reset(const_data);
  hash_entries_.clear();

  return base::StringPiece(data, total_bits / 8 + kMetaDataSize);
}

uint32_t FullFilterBitsBuilder::GetTotalBitsForLocality(uint32_t total_bits) {
  uint32_t num_lines = ceil_div(total_bits, (uint32_t)BASE_CACHELINE_SIZE * 8u);

  // Make num_lines an odd number to make sure more bits are involved
  // when determining which block.
  if (num_lines % 2 == 0) {
    num_lines++;
  }
  return num_lines * (BASE_CACHELINE_SIZE * 8);
}

char* FullFilterBitsBuilder::ReserveSpace(const int num_entry,
    uint32_t* total_bits, uint32_t* num_lines) {
  DCHECK(bits_per_key_);
  char* data = nullptr;
  if (num_entry != 0) {
    uint32_t total_bits_tmp = num_entry * static_cast<uint32_t>(bits_per_key_);

    *total_bits = GetTotalBitsForLocality(total_bits_tmp);
    *num_lines = *total_bits / (BASE_CACHELINE_SIZE * 8);
    DCHECK(*total_bits > 0 && *total_bits % 8 == 0);
  } else {
    // filter is empty, just leave space for metadata
    *total_bits = 0;
    *num_lines = 0;
  }

  // Reserve space for Filter
  uint32_t sz = *total_bits / 8;
  sz += kMetaDataSize;  // 4 bytes for num_lines, 1 byte for num_probes

  data = new char[sz];
  memset(data, 0, sz);
  return data;
}

FullFilterBitsReader::FullFilterBitsReader(const base::StringPiece& contents)
    : data_(const_cast<char*>(contents.data())),
      data_len_(static_cast<uint32_t>(contents.size())),
      num_probes_(0),
      num_lines_(0) {
  DCHECK(data_);
  GetFilterMeta(contents, &num_probes_, &num_lines_);
  // Sanitize broken parameters
  if (num_lines_ != 0 && data_len_ != num_lines_ * BASE_CACHELINE_SIZE +
      FullFilterBitsBuilder::kMetaDataSize) {

#if !DCHECK_IS_ON()
    NOTREACHED();
#endif // !DCHECK_IS_ON()

    num_lines_ = 0;
    num_probes_ = 0;
  }
}

bool FullFilterBitsReader::MayMatch(const base::StringPiece& entry) {
  if (data_len_ <= FullFilterBitsBuilder::kMetaDataSize) { // remain same with original filter
    return false;
  }
  // Other Error params, including a broken filter, regarded as match
  if (num_probes_ == 0 || num_lines_ == 0) return true;
  uint32_t hash = base::Hash(entry.as_string());
  return HashMayMatch(hash, base::StringPiece(data_, data_len_),
                      num_probes_, num_lines_);
}

void FullFilterBitsReader::GetFilterMeta(const base::StringPiece& filter,
    size_t* num_probes, uint32_t* num_lines) {
  uint32_t len = static_cast<uint32_t>(filter.size());
  if (len <= FullFilterBitsBuilder::kMetaDataSize) {
    // filter is empty or broken
    *num_probes = 0;
    *num_lines = 0;
    return;
  }

  *num_probes = filter.data()[len - FullFilterBitsBuilder::kMetaDataSize];
  *num_lines = DecodeFixed32(filter.data() + len - 4);
}

inline bool FullFilterBitsReader::HashMayMatch(const uint32_t hash, const base::StringPiece& filter,
    const size_t num_probes, const uint32_t num_lines) {
  uint32_t len = static_cast<uint32_t>(filter.size());
  if (len <= FullFilterBitsBuilder::kMetaDataSize)
    return false; // Remain the same with original filter.

  // It is ensured the params are valid before calling it
  DCHECK(num_probes != 0);
  DCHECK(num_lines != 0 &&
      (len - FullFilterBitsBuilder::kMetaDataSize) % num_lines == 0);
  // cacheline_size is calculated here based on filter metadata instead of using BASE_CACHELINE_SIZE.
  // The reason may be to support deserialization of filters which are already persisted in case we
  // change cacheline_size or if machine architecture is changed.
  uint32_t cacheline_size = (len - FullFilterBitsBuilder::kMetaDataSize) / num_lines;
  const char* data = filter.data();

  uint32_t h = hash;
  const uint32_t delta = (h >> 17) | (h << 15);  // Rotate right 17 bits
  uint32_t b = (h % num_lines) * (cacheline_size * 8);

  for (uint32_t i = 0; i < num_probes; ++i) {
    // Since BASE_CACHELINE_SIZE is defined as 2^n, this line will be optimized
    //  to a simple and operation by compiler.
    const uint32_t bitpos = b + (h % (cacheline_size * 8));
    if (((data[bitpos / 8]) & (1 << (bitpos % 8))) == 0) {
      return false;
    }

    h += delta;
  }

  return true;
}

void BloomFilterPolicy::initialize() {
  // We intentionally round down to reduce probing cost a little bit
  num_probes_ = static_cast<size_t>(bits_per_key_ * 0.69);  // 0.69 =~ ln(2)
  if (num_probes_ < 1) num_probes_ = 1;
  if (num_probes_ > 30) num_probes_ = 30;
}

FilterBitsBuilder* BloomFilterPolicy::GetFilterBitsBuilder() const {
  if (use_block_based_builder_) {
    return nullptr;
  }

  return new FullFilterBitsBuilder(bits_per_key_, num_probes_);
}

FilterBitsReader* BloomFilterPolicy::GetFilterBitsReader(const base::StringPiece& contents) const {
  return new FullFilterBitsReader(contents);
}

BloomFilterPolicy::BloomFilterPolicy(int bits_per_key, bool use_block_based_builder)
    : bits_per_key_(bits_per_key), hash_func_(base::Hash),
      use_block_based_builder_(use_block_based_builder) {
  initialize();
}

FilterPolicy::FilterType BloomFilterPolicy::GetFilterType() const {
  return use_block_based_builder_ ?
    FilterPolicy::FilterType::kBlockBasedFilter
    : FilterPolicy::FilterType::kFullFilter;
}

void BloomFilterPolicy::CreateFilter(const base::StringPiece* keys, int n,
                          std::string* dst) const {
  // Compute bloom filter size (in both bits and bytes)
  size_t bits = n * bits_per_key_;

  // For small n, we can see a very high false positive rate.  Fix it
  // by enforcing a minimum bloom filter length.
  bits = std::max<size_t>(bits, 128);

  size_t bytes = (bits + 7) / 8;
  bits = bytes * 8;

  const size_t init_size = dst->size();
  dst->resize(init_size + bytes, 0);
  dst->push_back(static_cast<char>(num_probes_));  // Remember # of probes
  char* array = &(*dst)[init_size];
  for (size_t i = 0; i < (size_t)n; i++) {
    // Use double-hashing to generate a sequence of hash values.
    // See analysis in [Kirsch,Mitzenmacher 2006].
    uint32_t h = hash_func_(keys[i].as_string());
    const uint32_t delta = (h >> 17) | (h << 15);  // Rotate right 17 bits
    for (size_t j = 0; j < num_probes_; j++) {
      const uint32_t bitpos = h % bits;
      array[bitpos / 8] |= (1 << (bitpos % 8));
      h += delta;
    }
  }
}

bool BloomFilterPolicy::KeyMayMatch(const base::StringPiece& key,
                         const base::StringPiece& bloom_filter) const {
  const size_t len = bloom_filter.size();
  if (len < 2) return false;

  const char* array = bloom_filter.data();
  const size_t bits = (len - 1) * 8;

  // Use the encoded k so that we can read filters generated by
  // bloom filters created using different parameters.
  const size_t k = array[len-1];
  if (k > 30) {
    // Reserved for potentially new encodings for short bloom filters.
    // Consider it a match.
    return true;
  }

  uint32_t h = hash_func_(key.as_string());
  const uint32_t delta = (h >> 17) | (h << 15);  // Rotate right 17 bits
  for (size_t j = 0; j < k; j++) {
    const uint32_t bitpos = h % bits;
    if ((array[bitpos / 8] & (1 << (bitpos % 8))) == 0) return false;
    h += delta;
  }
  return true;
}

FixedSizeFilterBitsBuilder::FixedSizeFilterBitsBuilder(uint32_t total_bits, double error_rate)
    : error_rate_(error_rate) {
  DCHECK_GT(error_rate, 0);
  DCHECK_GT(total_bits, 0);
  num_lines_ = ceil_div(total_bits, (uint32_t)BASE_CACHELINE_SIZE * 8u);
  // AddHash implementation gives much higher false positive rate when num_lines_ is even, so
  // make sure it is odd.
  if (num_lines_ % 2 == 0) {
    // For small filter blocks - add one line, so we can have enough keys in block.
    // For bigger filter block - remove one line, so filter block will fit desired size.
    if (num_lines_ * BASE_CACHELINE_SIZE < 4096) {
      num_lines_++;
    } else {
      num_lines_--;
    }
  }
  total_bits_ = num_lines_ * BASE_CACHELINE_SIZE * 8;

  const double minus_log_error_rate = -std::log(error_rate_);
  DCHECK_GT(minus_log_error_rate, 0);
  num_probes_ = static_cast<size_t> (minus_log_error_rate / kLog2);
  num_probes_ = std::max<size_t>(num_probes_, 1);
  num_probes_ = std::min<size_t>(num_probes_, 255);
  const double max_keys = total_bits_ * kLog2 * kLog2 / minus_log_error_rate;
  DCHECK_LT(max_keys, std::numeric_limits<size_t>::max());
  max_keys_ = static_cast<size_t> (max_keys);
  keys_added_ = 0;

  // TODO - add tests verifying that after inserting max_keys we will have required error rate

  data_.reset(new char[FilterSize()]);
  memset(data_.get(), 0, FilterSize());
}

void FixedSizeFilterBitsBuilder::AddKey(const base::StringPiece& key) {
  ++keys_added_;
  uint32_t hash = base::Hash(key.as_string());
  AddHash(hash, data_.get(), num_lines_, total_bits_, num_probes_);
}

bool FixedSizeFilterBitsBuilder::IsFull() const { return keys_added_ >= max_keys_; }

base::StringPiece FixedSizeFilterBitsBuilder::Finish(std::unique_ptr<const char[]>* buf) {
  data_[total_bits_ / 8] = static_cast<char>(num_probes_);
  EncodeFixed32(data_.get() + total_bits_ / 8 + 1, static_cast<uint32_t>(num_lines_));
  buf->reset(data_.release());
  return base::StringPiece(buf->get(), FilterSize());
}

FixedSizeFilterPolicy::FixedSizeFilterPolicy(uint32_t total_bits, double error_rate)
    : total_bits_(total_bits),
      error_rate_(error_rate)
{
  DCHECK_GT(error_rate, 0);
  // Make sure num_probes > 0.
  DCHECK_GT(static_cast<int64_t> (-std::log(error_rate) / kLog2), 0);
}

FilterBitsBuilder* FixedSizeFilterPolicy::GetFilterBitsBuilder() const {
  return new FixedSizeFilterBitsBuilder(total_bits_, error_rate_);
}

FilterBitsReader* FixedSizeFilterPolicy::GetFilterBitsReader(const base::StringPiece& contents) const {
  return new FixedSizeFilterBitsReader(contents);
}

// static
const double FixedSizeFilterBitsBuilder::kLog2 = std::log(2);

// static
const double FixedSizeFilterPolicy::kLog2 = std::log(2);

const FilterPolicy* NewBloomFilterPolicy(int bits_per_key,
                                         bool use_block_based_builder) {
  return new BloomFilterPolicy(bits_per_key, use_block_based_builder);
  // TODO - replace by NewFixedSizeFilterPolicy and check tests.
}

const FilterPolicy* NewFixedSizeFilterPolicy(uint32_t total_bits,
                                             double error_rate) {
  return new FixedSizeFilterPolicy(total_bits, error_rate);
}

}  // namespace basic
