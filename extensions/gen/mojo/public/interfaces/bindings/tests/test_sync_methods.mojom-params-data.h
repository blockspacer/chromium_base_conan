// mojo/public/interfaces/bindings/tests/test_sync_methods.mojom-params-data.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_SYNC_METHODS_MOJOM_PARAMS_DATA_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_SYNC_METHODS_MOJOM_PARAMS_DATA_H_

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
class  TestSyncCodeGeneration_NoInput_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestSyncCodeGeneration_NoInput_Params_Data>;

  TestSyncCodeGeneration_NoInput_Params_Data();
  ~TestSyncCodeGeneration_NoInput_Params_Data() = delete;
};
static_assert(sizeof(TestSyncCodeGeneration_NoInput_Params_Data) == 8,
              "Bad sizeof(TestSyncCodeGeneration_NoInput_Params_Data)");
class  TestSyncCodeGeneration_NoInput_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t result;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<TestSyncCodeGeneration_NoInput_ResponseParams_Data>;

  TestSyncCodeGeneration_NoInput_ResponseParams_Data();
  ~TestSyncCodeGeneration_NoInput_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestSyncCodeGeneration_NoInput_ResponseParams_Data) == 16,
              "Bad sizeof(TestSyncCodeGeneration_NoInput_ResponseParams_Data)");
class  TestSyncCodeGeneration_NoOutput_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t value;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<TestSyncCodeGeneration_NoOutput_Params_Data>;

  TestSyncCodeGeneration_NoOutput_Params_Data();
  ~TestSyncCodeGeneration_NoOutput_Params_Data() = delete;
};
static_assert(sizeof(TestSyncCodeGeneration_NoOutput_Params_Data) == 16,
              "Bad sizeof(TestSyncCodeGeneration_NoOutput_Params_Data)");
class  TestSyncCodeGeneration_NoOutput_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestSyncCodeGeneration_NoOutput_ResponseParams_Data>;

  TestSyncCodeGeneration_NoOutput_ResponseParams_Data();
  ~TestSyncCodeGeneration_NoOutput_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestSyncCodeGeneration_NoOutput_ResponseParams_Data) == 8,
              "Bad sizeof(TestSyncCodeGeneration_NoOutput_ResponseParams_Data)");
class  TestSyncCodeGeneration_NoInOut_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestSyncCodeGeneration_NoInOut_Params_Data>;

  TestSyncCodeGeneration_NoInOut_Params_Data();
  ~TestSyncCodeGeneration_NoInOut_Params_Data() = delete;
};
static_assert(sizeof(TestSyncCodeGeneration_NoInOut_Params_Data) == 8,
              "Bad sizeof(TestSyncCodeGeneration_NoInOut_Params_Data)");
class  TestSyncCodeGeneration_NoInOut_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestSyncCodeGeneration_NoInOut_ResponseParams_Data>;

  TestSyncCodeGeneration_NoInOut_ResponseParams_Data();
  ~TestSyncCodeGeneration_NoInOut_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestSyncCodeGeneration_NoInOut_ResponseParams_Data) == 8,
              "Bad sizeof(TestSyncCodeGeneration_NoInOut_ResponseParams_Data)");
class  TestSyncCodeGeneration_HaveInOut_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t value1;
  int32_t value2;

 private:
  friend class mojo::internal::MessageFragment<TestSyncCodeGeneration_HaveInOut_Params_Data>;

  TestSyncCodeGeneration_HaveInOut_Params_Data();
  ~TestSyncCodeGeneration_HaveInOut_Params_Data() = delete;
};
static_assert(sizeof(TestSyncCodeGeneration_HaveInOut_Params_Data) == 16,
              "Bad sizeof(TestSyncCodeGeneration_HaveInOut_Params_Data)");
class  TestSyncCodeGeneration_HaveInOut_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t result1;
  int32_t result2;

 private:
  friend class mojo::internal::MessageFragment<TestSyncCodeGeneration_HaveInOut_ResponseParams_Data>;

  TestSyncCodeGeneration_HaveInOut_ResponseParams_Data();
  ~TestSyncCodeGeneration_HaveInOut_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestSyncCodeGeneration_HaveInOut_ResponseParams_Data) == 16,
              "Bad sizeof(TestSyncCodeGeneration_HaveInOut_ResponseParams_Data)");
class  TestSync_Ping_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestSync_Ping_Params_Data>;

  TestSync_Ping_Params_Data();
  ~TestSync_Ping_Params_Data() = delete;
};
static_assert(sizeof(TestSync_Ping_Params_Data) == 8,
              "Bad sizeof(TestSync_Ping_Params_Data)");
class  TestSync_Ping_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestSync_Ping_ResponseParams_Data>;

  TestSync_Ping_ResponseParams_Data();
  ~TestSync_Ping_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestSync_Ping_ResponseParams_Data) == 8,
              "Bad sizeof(TestSync_Ping_ResponseParams_Data)");
class  TestSync_Echo_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t value;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<TestSync_Echo_Params_Data>;

  TestSync_Echo_Params_Data();
  ~TestSync_Echo_Params_Data() = delete;
};
static_assert(sizeof(TestSync_Echo_Params_Data) == 16,
              "Bad sizeof(TestSync_Echo_Params_Data)");
class  TestSync_Echo_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t result;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<TestSync_Echo_ResponseParams_Data>;

  TestSync_Echo_ResponseParams_Data();
  ~TestSync_Echo_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestSync_Echo_ResponseParams_Data) == 16,
              "Bad sizeof(TestSync_Echo_ResponseParams_Data)");
class  TestSync_AsyncEcho_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t value;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<TestSync_AsyncEcho_Params_Data>;

  TestSync_AsyncEcho_Params_Data();
  ~TestSync_AsyncEcho_Params_Data() = delete;
};
static_assert(sizeof(TestSync_AsyncEcho_Params_Data) == 16,
              "Bad sizeof(TestSync_AsyncEcho_Params_Data)");
class  TestSync_AsyncEcho_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t result;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<TestSync_AsyncEcho_ResponseParams_Data>;

  TestSync_AsyncEcho_ResponseParams_Data();
  ~TestSync_AsyncEcho_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestSync_AsyncEcho_ResponseParams_Data) == 16,
              "Bad sizeof(TestSync_AsyncEcho_ResponseParams_Data)");
class  TestSyncPrimary_Ping_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestSyncPrimary_Ping_Params_Data>;

  TestSyncPrimary_Ping_Params_Data();
  ~TestSyncPrimary_Ping_Params_Data() = delete;
};
static_assert(sizeof(TestSyncPrimary_Ping_Params_Data) == 8,
              "Bad sizeof(TestSyncPrimary_Ping_Params_Data)");
class  TestSyncPrimary_Ping_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<TestSyncPrimary_Ping_ResponseParams_Data>;

  TestSyncPrimary_Ping_ResponseParams_Data();
  ~TestSyncPrimary_Ping_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestSyncPrimary_Ping_ResponseParams_Data) == 8,
              "Bad sizeof(TestSyncPrimary_Ping_ResponseParams_Data)");
class  TestSyncPrimary_Echo_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t value;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<TestSyncPrimary_Echo_Params_Data>;

  TestSyncPrimary_Echo_Params_Data();
  ~TestSyncPrimary_Echo_Params_Data() = delete;
};
static_assert(sizeof(TestSyncPrimary_Echo_Params_Data) == 16,
              "Bad sizeof(TestSyncPrimary_Echo_Params_Data)");
class  TestSyncPrimary_Echo_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t result;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<TestSyncPrimary_Echo_ResponseParams_Data>;

  TestSyncPrimary_Echo_ResponseParams_Data();
  ~TestSyncPrimary_Echo_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestSyncPrimary_Echo_ResponseParams_Data) == 16,
              "Bad sizeof(TestSyncPrimary_Echo_ResponseParams_Data)");
class  TestSyncPrimary_AsyncEcho_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t value;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<TestSyncPrimary_AsyncEcho_Params_Data>;

  TestSyncPrimary_AsyncEcho_Params_Data();
  ~TestSyncPrimary_AsyncEcho_Params_Data() = delete;
};
static_assert(sizeof(TestSyncPrimary_AsyncEcho_Params_Data) == 16,
              "Bad sizeof(TestSyncPrimary_AsyncEcho_Params_Data)");
class  TestSyncPrimary_AsyncEcho_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t result;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<TestSyncPrimary_AsyncEcho_ResponseParams_Data>;

  TestSyncPrimary_AsyncEcho_ResponseParams_Data();
  ~TestSyncPrimary_AsyncEcho_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestSyncPrimary_AsyncEcho_ResponseParams_Data) == 16,
              "Bad sizeof(TestSyncPrimary_AsyncEcho_ResponseParams_Data)");
class  TestSyncPrimary_SendRemote_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::AssociatedInterface_Data remote;

 private:
  friend class mojo::internal::MessageFragment<TestSyncPrimary_SendRemote_Params_Data>;

  TestSyncPrimary_SendRemote_Params_Data();
  ~TestSyncPrimary_SendRemote_Params_Data() = delete;
};
static_assert(sizeof(TestSyncPrimary_SendRemote_Params_Data) == 16,
              "Bad sizeof(TestSyncPrimary_SendRemote_Params_Data)");
class  TestSyncPrimary_SendReceiver_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::AssociatedEndpointHandle_Data receiver;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<TestSyncPrimary_SendReceiver_Params_Data>;

  TestSyncPrimary_SendReceiver_Params_Data();
  ~TestSyncPrimary_SendReceiver_Params_Data() = delete;
};
static_assert(sizeof(TestSyncPrimary_SendReceiver_Params_Data) == 16,
              "Bad sizeof(TestSyncPrimary_SendReceiver_Params_Data)");

}  // namespace internal


class TestSyncCodeGeneration_NoInput_ParamsDataView {
 public:
  TestSyncCodeGeneration_NoInput_ParamsDataView() {}

  TestSyncCodeGeneration_NoInput_ParamsDataView(
      internal::TestSyncCodeGeneration_NoInput_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestSyncCodeGeneration_NoInput_Params_Data* data_ = nullptr;
};



class TestSyncCodeGeneration_NoInput_ResponseParamsDataView {
 public:
  TestSyncCodeGeneration_NoInput_ResponseParamsDataView() {}

  TestSyncCodeGeneration_NoInput_ResponseParamsDataView(
      internal::TestSyncCodeGeneration_NoInput_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t result() const {
    return data_->result;
  }
 private:
  internal::TestSyncCodeGeneration_NoInput_ResponseParams_Data* data_ = nullptr;
};



class TestSyncCodeGeneration_NoOutput_ParamsDataView {
 public:
  TestSyncCodeGeneration_NoOutput_ParamsDataView() {}

  TestSyncCodeGeneration_NoOutput_ParamsDataView(
      internal::TestSyncCodeGeneration_NoOutput_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t value() const {
    return data_->value;
  }
 private:
  internal::TestSyncCodeGeneration_NoOutput_Params_Data* data_ = nullptr;
};



class TestSyncCodeGeneration_NoOutput_ResponseParamsDataView {
 public:
  TestSyncCodeGeneration_NoOutput_ResponseParamsDataView() {}

  TestSyncCodeGeneration_NoOutput_ResponseParamsDataView(
      internal::TestSyncCodeGeneration_NoOutput_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestSyncCodeGeneration_NoOutput_ResponseParams_Data* data_ = nullptr;
};



class TestSyncCodeGeneration_NoInOut_ParamsDataView {
 public:
  TestSyncCodeGeneration_NoInOut_ParamsDataView() {}

  TestSyncCodeGeneration_NoInOut_ParamsDataView(
      internal::TestSyncCodeGeneration_NoInOut_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestSyncCodeGeneration_NoInOut_Params_Data* data_ = nullptr;
};



class TestSyncCodeGeneration_NoInOut_ResponseParamsDataView {
 public:
  TestSyncCodeGeneration_NoInOut_ResponseParamsDataView() {}

  TestSyncCodeGeneration_NoInOut_ResponseParamsDataView(
      internal::TestSyncCodeGeneration_NoInOut_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestSyncCodeGeneration_NoInOut_ResponseParams_Data* data_ = nullptr;
};



class TestSyncCodeGeneration_HaveInOut_ParamsDataView {
 public:
  TestSyncCodeGeneration_HaveInOut_ParamsDataView() {}

  TestSyncCodeGeneration_HaveInOut_ParamsDataView(
      internal::TestSyncCodeGeneration_HaveInOut_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t value1() const {
    return data_->value1;
  }
  int32_t value2() const {
    return data_->value2;
  }
 private:
  internal::TestSyncCodeGeneration_HaveInOut_Params_Data* data_ = nullptr;
};



class TestSyncCodeGeneration_HaveInOut_ResponseParamsDataView {
 public:
  TestSyncCodeGeneration_HaveInOut_ResponseParamsDataView() {}

  TestSyncCodeGeneration_HaveInOut_ResponseParamsDataView(
      internal::TestSyncCodeGeneration_HaveInOut_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t result1() const {
    return data_->result1;
  }
  int32_t result2() const {
    return data_->result2;
  }
 private:
  internal::TestSyncCodeGeneration_HaveInOut_ResponseParams_Data* data_ = nullptr;
};



class TestSync_Ping_ParamsDataView {
 public:
  TestSync_Ping_ParamsDataView() {}

  TestSync_Ping_ParamsDataView(
      internal::TestSync_Ping_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestSync_Ping_Params_Data* data_ = nullptr;
};



class TestSync_Ping_ResponseParamsDataView {
 public:
  TestSync_Ping_ResponseParamsDataView() {}

  TestSync_Ping_ResponseParamsDataView(
      internal::TestSync_Ping_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestSync_Ping_ResponseParams_Data* data_ = nullptr;
};



class TestSync_Echo_ParamsDataView {
 public:
  TestSync_Echo_ParamsDataView() {}

  TestSync_Echo_ParamsDataView(
      internal::TestSync_Echo_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t value() const {
    return data_->value;
  }
 private:
  internal::TestSync_Echo_Params_Data* data_ = nullptr;
};



class TestSync_Echo_ResponseParamsDataView {
 public:
  TestSync_Echo_ResponseParamsDataView() {}

  TestSync_Echo_ResponseParamsDataView(
      internal::TestSync_Echo_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t result() const {
    return data_->result;
  }
 private:
  internal::TestSync_Echo_ResponseParams_Data* data_ = nullptr;
};



class TestSync_AsyncEcho_ParamsDataView {
 public:
  TestSync_AsyncEcho_ParamsDataView() {}

  TestSync_AsyncEcho_ParamsDataView(
      internal::TestSync_AsyncEcho_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t value() const {
    return data_->value;
  }
 private:
  internal::TestSync_AsyncEcho_Params_Data* data_ = nullptr;
};



class TestSync_AsyncEcho_ResponseParamsDataView {
 public:
  TestSync_AsyncEcho_ResponseParamsDataView() {}

  TestSync_AsyncEcho_ResponseParamsDataView(
      internal::TestSync_AsyncEcho_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t result() const {
    return data_->result;
  }
 private:
  internal::TestSync_AsyncEcho_ResponseParams_Data* data_ = nullptr;
};



class TestSyncPrimary_Ping_ParamsDataView {
 public:
  TestSyncPrimary_Ping_ParamsDataView() {}

  TestSyncPrimary_Ping_ParamsDataView(
      internal::TestSyncPrimary_Ping_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestSyncPrimary_Ping_Params_Data* data_ = nullptr;
};



class TestSyncPrimary_Ping_ResponseParamsDataView {
 public:
  TestSyncPrimary_Ping_ResponseParamsDataView() {}

  TestSyncPrimary_Ping_ResponseParamsDataView(
      internal::TestSyncPrimary_Ping_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestSyncPrimary_Ping_ResponseParams_Data* data_ = nullptr;
};



class TestSyncPrimary_Echo_ParamsDataView {
 public:
  TestSyncPrimary_Echo_ParamsDataView() {}

  TestSyncPrimary_Echo_ParamsDataView(
      internal::TestSyncPrimary_Echo_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t value() const {
    return data_->value;
  }
 private:
  internal::TestSyncPrimary_Echo_Params_Data* data_ = nullptr;
};



class TestSyncPrimary_Echo_ResponseParamsDataView {
 public:
  TestSyncPrimary_Echo_ResponseParamsDataView() {}

  TestSyncPrimary_Echo_ResponseParamsDataView(
      internal::TestSyncPrimary_Echo_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t result() const {
    return data_->result;
  }
 private:
  internal::TestSyncPrimary_Echo_ResponseParams_Data* data_ = nullptr;
};



class TestSyncPrimary_AsyncEcho_ParamsDataView {
 public:
  TestSyncPrimary_AsyncEcho_ParamsDataView() {}

  TestSyncPrimary_AsyncEcho_ParamsDataView(
      internal::TestSyncPrimary_AsyncEcho_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t value() const {
    return data_->value;
  }
 private:
  internal::TestSyncPrimary_AsyncEcho_Params_Data* data_ = nullptr;
};



class TestSyncPrimary_AsyncEcho_ResponseParamsDataView {
 public:
  TestSyncPrimary_AsyncEcho_ResponseParamsDataView() {}

  TestSyncPrimary_AsyncEcho_ResponseParamsDataView(
      internal::TestSyncPrimary_AsyncEcho_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t result() const {
    return data_->result;
  }
 private:
  internal::TestSyncPrimary_AsyncEcho_ResponseParams_Data* data_ = nullptr;
};



class TestSyncPrimary_SendRemote_ParamsDataView {
 public:
  TestSyncPrimary_SendRemote_ParamsDataView() {}

  TestSyncPrimary_SendRemote_ParamsDataView(
      internal::TestSyncPrimary_SendRemote_Params_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  template <typename UserType>
  UserType TakeRemote() {
    UserType result;
    bool ret =
        mojo::internal::Deserialize<::mojo::test::TestSyncAssociatedPtrInfoDataView>(
            &data_->remote, &result, message_);
    DCHECK(ret);
    return result;
  }
 private:
  internal::TestSyncPrimary_SendRemote_Params_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class TestSyncPrimary_SendReceiver_ParamsDataView {
 public:
  TestSyncPrimary_SendReceiver_ParamsDataView() {}

  TestSyncPrimary_SendReceiver_ParamsDataView(
      internal::TestSyncPrimary_SendReceiver_Params_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  template <typename UserType>
  UserType TakeReceiver() {
    UserType result;
    bool ret =
        mojo::internal::Deserialize<::mojo::test::TestSyncAssociatedRequestDataView>(
            &data_->receiver, &result, message_);
    DCHECK(ret);
    return result;
  }
 private:
  internal::TestSyncPrimary_SendReceiver_Params_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};













































}  // namespace test
}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_SYNC_METHODS_MOJOM_PARAMS_DATA_H_