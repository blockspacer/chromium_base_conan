// mojo/public/interfaces/bindings/tests/test_bad_messages.mojom-params-data.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_BAD_MESSAGES_MOJOM_PARAMS_DATA_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_BAD_MESSAGES_MOJOM_PARAMS_DATA_H_

#include "base/macros.h"
#include "mojo/public/cpp/bindings/lib/bindings_internal.h"
#include "mojo/public/cpp/bindings/lib/buffer.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif
namespace mojo {
namespace test {
namespace internal {
class  TestBadMessages_RejectEventually_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestBadMessages_RejectEventually_Params_Data>;

  TestBadMessages_RejectEventually_Params_Data();
  ~TestBadMessages_RejectEventually_Params_Data() = delete;
};
static_assert(sizeof(TestBadMessages_RejectEventually_Params_Data) == 8,
              "Bad sizeof(TestBadMessages_RejectEventually_Params_Data)");
class  TestBadMessages_RejectEventually_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestBadMessages_RejectEventually_ResponseParams_Data>;

  TestBadMessages_RejectEventually_ResponseParams_Data();
  ~TestBadMessages_RejectEventually_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestBadMessages_RejectEventually_ResponseParams_Data) == 8,
              "Bad sizeof(TestBadMessages_RejectEventually_ResponseParams_Data)");
class  TestBadMessages_RequestResponse_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestBadMessages_RequestResponse_Params_Data>;

  TestBadMessages_RequestResponse_Params_Data();
  ~TestBadMessages_RequestResponse_Params_Data() = delete;
};
static_assert(sizeof(TestBadMessages_RequestResponse_Params_Data) == 8,
              "Bad sizeof(TestBadMessages_RequestResponse_Params_Data)");
class  TestBadMessages_RequestResponse_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestBadMessages_RequestResponse_ResponseParams_Data>;

  TestBadMessages_RequestResponse_ResponseParams_Data();
  ~TestBadMessages_RequestResponse_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestBadMessages_RequestResponse_ResponseParams_Data) == 8,
              "Bad sizeof(TestBadMessages_RequestResponse_ResponseParams_Data)");
class  TestBadMessages_RejectSync_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestBadMessages_RejectSync_Params_Data>;

  TestBadMessages_RejectSync_Params_Data();
  ~TestBadMessages_RejectSync_Params_Data() = delete;
};
static_assert(sizeof(TestBadMessages_RejectSync_Params_Data) == 8,
              "Bad sizeof(TestBadMessages_RejectSync_Params_Data)");
class  TestBadMessages_RejectSync_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestBadMessages_RejectSync_ResponseParams_Data>;

  TestBadMessages_RejectSync_ResponseParams_Data();
  ~TestBadMessages_RejectSync_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestBadMessages_RejectSync_ResponseParams_Data) == 8,
              "Bad sizeof(TestBadMessages_RejectSync_ResponseParams_Data)");
class  TestBadMessages_RequestResponseSync_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestBadMessages_RequestResponseSync_Params_Data>;

  TestBadMessages_RequestResponseSync_Params_Data();
  ~TestBadMessages_RequestResponseSync_Params_Data() = delete;
};
static_assert(sizeof(TestBadMessages_RequestResponseSync_Params_Data) == 8,
              "Bad sizeof(TestBadMessages_RequestResponseSync_Params_Data)");
class  TestBadMessages_RequestResponseSync_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestBadMessages_RequestResponseSync_ResponseParams_Data>;

  TestBadMessages_RequestResponseSync_ResponseParams_Data();
  ~TestBadMessages_RequestResponseSync_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestBadMessages_RequestResponseSync_ResponseParams_Data) == 8,
              "Bad sizeof(TestBadMessages_RequestResponseSync_ResponseParams_Data)");

}  // namespace internal


class TestBadMessages_RejectEventually_ParamsDataView {
 public:
  TestBadMessages_RejectEventually_ParamsDataView() {}

  TestBadMessages_RejectEventually_ParamsDataView(
      internal::TestBadMessages_RejectEventually_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestBadMessages_RejectEventually_Params_Data* data_ = nullptr;
};



class TestBadMessages_RejectEventually_ResponseParamsDataView {
 public:
  TestBadMessages_RejectEventually_ResponseParamsDataView() {}

  TestBadMessages_RejectEventually_ResponseParamsDataView(
      internal::TestBadMessages_RejectEventually_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestBadMessages_RejectEventually_ResponseParams_Data* data_ = nullptr;
};



class TestBadMessages_RequestResponse_ParamsDataView {
 public:
  TestBadMessages_RequestResponse_ParamsDataView() {}

  TestBadMessages_RequestResponse_ParamsDataView(
      internal::TestBadMessages_RequestResponse_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestBadMessages_RequestResponse_Params_Data* data_ = nullptr;
};



class TestBadMessages_RequestResponse_ResponseParamsDataView {
 public:
  TestBadMessages_RequestResponse_ResponseParamsDataView() {}

  TestBadMessages_RequestResponse_ResponseParamsDataView(
      internal::TestBadMessages_RequestResponse_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestBadMessages_RequestResponse_ResponseParams_Data* data_ = nullptr;
};



class TestBadMessages_RejectSync_ParamsDataView {
 public:
  TestBadMessages_RejectSync_ParamsDataView() {}

  TestBadMessages_RejectSync_ParamsDataView(
      internal::TestBadMessages_RejectSync_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestBadMessages_RejectSync_Params_Data* data_ = nullptr;
};



class TestBadMessages_RejectSync_ResponseParamsDataView {
 public:
  TestBadMessages_RejectSync_ResponseParamsDataView() {}

  TestBadMessages_RejectSync_ResponseParamsDataView(
      internal::TestBadMessages_RejectSync_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestBadMessages_RejectSync_ResponseParams_Data* data_ = nullptr;
};



class TestBadMessages_RequestResponseSync_ParamsDataView {
 public:
  TestBadMessages_RequestResponseSync_ParamsDataView() {}

  TestBadMessages_RequestResponseSync_ParamsDataView(
      internal::TestBadMessages_RequestResponseSync_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestBadMessages_RequestResponseSync_Params_Data* data_ = nullptr;
};



class TestBadMessages_RequestResponseSync_ResponseParamsDataView {
 public:
  TestBadMessages_RequestResponseSync_ResponseParamsDataView() {}

  TestBadMessages_RequestResponseSync_ResponseParamsDataView(
      internal::TestBadMessages_RequestResponseSync_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestBadMessages_RequestResponseSync_ResponseParams_Data* data_ = nullptr;
};

















}  // namespace test
}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_BAD_MESSAGES_MOJOM_PARAMS_DATA_H_