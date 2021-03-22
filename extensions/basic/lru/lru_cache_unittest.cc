// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/test/test_macros.h"
#include "basic/lru/lru_cache.h"
#include "basic/lru/estimate_memory_usage_for_lru_cache.h"

#include "testing/gtest/include/gtest/gtest.h"
#include "testing/gmock/include/gmock/gmock.h"

#include <string>
#include <vector>

namespace basic {

using String = std::string;

template<typename T>
using Vector = std::vector<T>;

using ::testing::ElementsAre;

TEST(LruCacheTest, TestEmpty) {
  LruCache<int, int> test_cache(1);
  EXPECT_EQ(test_cache.Get(0), nullptr);
  EXPECT_EQ(test_cache.tail(), nullptr);
  EXPECT_EQ(test_cache.head(), nullptr);
}

TEST(LruCacheTest, TestString) {
  const size_t kMaxSize = 4;
  const char* test_strings[] = {"1_testing", "2_LruCache", "3_using",
                                "4_several", "5_random",   "6_strings"};
  LruCache<uint16_t, String> test_cache(kMaxSize);
  uint16_t counter = 1;
  EXPECT_EQ(test_cache.size(), 0u);
  for (auto* test_string : test_strings) {
    test_cache.Put(counter, test_string);
    counter++;
  }
  EXPECT_EQ(test_cache.size(), kMaxSize);
  EXPECT_FALSE(test_cache.empty());
  EXPECT_EQ(test_cache.Get(1), nullptr);
  EXPECT_EQ(test_cache.Get(2), nullptr);
  EXPECT_EQ(*test_cache.Get(3), String(test_strings[2]));
  EXPECT_EQ(*test_cache.tail(), String(test_strings[3])); // 4_several
  EXPECT_EQ(*test_cache.head(), String(test_strings[2])); // 3_using
  EXPECT_EQ(*test_cache.Get(4), String(test_strings[3]));
  EXPECT_EQ(*test_cache.tail(), String(test_strings[4])); // 5_random
  EXPECT_EQ(*test_cache.head(), String(test_strings[3])); // 4_several
  EXPECT_EQ(*test_cache.Get(5), String(test_strings[4]));
  EXPECT_EQ(*test_cache.Get(6), String(test_strings[5]));
  test_cache.Put(1, test_strings[0]);
  EXPECT_EQ(*test_cache.Get(1), String(test_strings[0]));
  EXPECT_EQ(test_cache.Get(3), nullptr);
  EXPECT_EQ(*test_cache.Get(4), String(test_strings[3]));
  EXPECT_EQ(*test_cache.Get(5), String(test_strings[4]));
  EXPECT_EQ(*test_cache.Get(6), String(test_strings[5]));
  test_cache.Clear();
  EXPECT_EQ(test_cache.size(), 0u);
}

TEST(LruCacheTest, TestInstantiation) {
  const int kMaxSize = 10;
  const int kOffset = 1000;
  LruCache<int, int> test_cache(kMaxSize);
  EXPECT_EQ(test_cache.size(), 0u);
  for (size_t i = 1; i < kMaxSize * 10; ++i) {
    test_cache.Put(i, kOffset + i);
  }
  EXPECT_EQ(test_cache.size(), kMaxSize * 1u);
  EXPECT_EQ(*test_cache.Get(kMaxSize * 10 - 1), kOffset + (kMaxSize * 10 - 1));
  EXPECT_EQ(*test_cache.Get(kMaxSize * 10 - 2), kOffset + (kMaxSize * 10 - 2));
  EXPECT_EQ(test_cache.Get(89), nullptr);
  EXPECT_EQ(test_cache.Get(1), nullptr);
  test_cache.Clear();
  EXPECT_EQ(test_cache.size(), 0u);
}

TEST(LruCacheTest, TestOverrideKey) {
  const size_t kMaxSize = 2;
  const char* test_strings[] = {"original_value", "override"};
  LruCache<uint16_t, String> test_cache(kMaxSize);
  EXPECT_EQ(test_cache.size(), 0u);
  test_cache.Put(1, test_strings[0]);
  test_cache.Put(1, test_strings[1]);
  EXPECT_EQ(*test_cache.Get(1), String(test_strings[1]));
  EXPECT_EQ(*test_cache.tail(), String(test_strings[1]));
  EXPECT_EQ(*test_cache.head(), String(test_strings[1]));
}

TEST(LruCacheTest, StringToVector) {
  const size_t kMaxSize = 4u;
  LruCache<String, Vector<String>> typeface_cache(kMaxSize);

  struct FontFallbackExample {
    String locale;
    String typeface_name;
  } example_typefaces[] = {{"en_us", "Arial"},
                           {"ko", "Malgun Gothic"},
                           {"ja", "Yu Gothic UI"},
                           {"en_us", "Times New Roman"},
                           {"en_us", "Calibri"},
                           {"km", "Leelawadee UI"},
                           {"zh-Hans", "Microsoft Yahei UI"},
                           {"bn", "Nirmala UI"}};
  for (auto& example : example_typefaces) {
    Vector<String>* cache_for_locale = typeface_cache.Get(example.locale);
    if (cache_for_locale) {
      cache_for_locale->push_back(example.typeface_name);
    } else {
      Vector<String> new_cache_for_locale;
      new_cache_for_locale.push_back(example.typeface_name);
      typeface_cache.Put(String(example.locale),
                         std::move(new_cache_for_locale));
    }
  }
  Vector<String>* vector_for_latin = typeface_cache.Get("en_us");
  EXPECT_TRUE(vector_for_latin);
  EXPECT_EQ(vector_for_latin->size(), 3u);
  EXPECT_EQ(typeface_cache.Get("zh-Hant"), nullptr);
  EXPECT_EQ(typeface_cache.Get("ko"), nullptr);
  EXPECT_EQ(typeface_cache.Get("ja"), nullptr);
  EXPECT_THAT(*typeface_cache.tail(), ElementsAre("Leelawadee UI"));
  EXPECT_THAT(*typeface_cache.head(), ElementsAre("Arial", "Times New Roman", "Calibri"));
}

TEST(LRUCacheTest, EstimateMemory) {
  LruCache<std::string, int> cache(10);

  const std::string key(100u, 'a');
  cache.Put(key, 1);

  EXPECT_GT(base::trace_event::EstimateMemoryUsage(cache),
            base::trace_event::EstimateMemoryUsage(key));
}

}  // namespace basic
