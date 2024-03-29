// Copyright 2021 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/trace_event/traced_value_support.h"

#include "base/memory/ref_counted.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "third_party/perfetto/include/perfetto/test/traced_value_test_support.h"

namespace base {
namespace trace_event {

namespace {

struct RefCountedData : RefCounted<RefCountedData> {
 public:
  explicit RefCountedData(std::string data) : data_(data) {}

  void WriteIntoTracedValue(perfetto::TracedValue context) const {
    std::move(context).WriteString(data_);
  }

 private:
  ~RefCountedData() = default;
  friend class RefCounted<RefCountedData>;

  std::string data_;
};

struct WeakData {
 public:
  explicit WeakData(std::string data) : data_(data) {}

  void WriteIntoTracedValue(perfetto::TracedValue context) const {
    std::move(context).WriteString(data_);
  }

  base::WeakPtr<WeakData> GetWeakPtr() const {
    return weak_ptr_factory_.GetWeakPtr();
  }

 private:
  std::string data_;

  base::WeakPtrFactory<WeakData> weak_ptr_factory_{this};
};

}  // namespace

TEST(TracedValueSupportTest, ScopedRefPtr) {
  EXPECT_EQ(
      perfetto::TracedValueToString(scoped_refptr<RefCountedData>(nullptr)),
      "0x0");
  scoped_refptr<RefCountedData> data =
      base::MakeRefCounted<RefCountedData>("refcounted");
  EXPECT_EQ(perfetto::TracedValueToString(data), "refcounted");
}

TEST(TracedValueSupportTest, Optional) {
  EXPECT_EQ(perfetto::TracedValueToString(base::Optional<int>()), "0x0");
  EXPECT_EQ(perfetto::TracedValueToString(base::Optional<const int>(42)), "42");
}

TEST(TracedValueSupportTest, WeakPtr) {
  std::unique_ptr<WeakData> data = std::make_unique<WeakData>("weak");
  base::WeakPtr<WeakData> weak_ptr = data->GetWeakPtr();
  EXPECT_EQ(perfetto::TracedValueToString(weak_ptr), "weak");
  data.reset();
  EXPECT_EQ(perfetto::TracedValueToString(weak_ptr), "0x0");
}

TEST(TracedValueSupportTest, Time) {
  EXPECT_EQ(
      perfetto::TracedValueToString(base::TimeDelta::FromMicroseconds(42)),
      "42");
  EXPECT_EQ(perfetto::TracedValueToString(
                base::Time() + base::TimeDelta::FromMicroseconds(42)),
            "42");
  EXPECT_EQ(perfetto::TracedValueToString(
                base::TimeTicks() + base::TimeDelta::FromMicroseconds(42)),
            "42");
}

TEST(TracedValueSupportTest, UnguessableToken) {
  auto token = UnguessableToken::Create();
  EXPECT_EQ(perfetto::TracedValueToString(token), token.ToString());
}

}  // namespace trace_event
}  // namespace base
