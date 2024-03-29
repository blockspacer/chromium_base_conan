// mojo/public/interfaces/bindings/tests/sample_interfaces.mojom-params-data.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_INTERFACES_MOJOM_PARAMS_DATA_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_INTERFACES_MOJOM_PARAMS_DATA_H_

#include "base/macros.h"
#include "mojo/public/cpp/bindings/lib/bindings_internal.h"
#include "mojo/public/cpp/bindings/lib/buffer.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif
namespace sample {
namespace internal {
class  PingTest_Ping_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<PingTest_Ping_Params_Data>;

  PingTest_Ping_Params_Data();
  ~PingTest_Ping_Params_Data() = delete;
};
static_assert(sizeof(PingTest_Ping_Params_Data) == 8,
              "Bad sizeof(PingTest_Ping_Params_Data)");
class  PingTest_Ping_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<PingTest_Ping_ResponseParams_Data>;

  PingTest_Ping_ResponseParams_Data();
  ~PingTest_Ping_ResponseParams_Data() = delete;
};
static_assert(sizeof(PingTest_Ping_ResponseParams_Data) == 8,
              "Bad sizeof(PingTest_Ping_ResponseParams_Data)");
class  Provider_EchoString_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<mojo::internal::String_Data> a;

 private:
  friend class mojo::internal::MessageFragment<Provider_EchoString_Params_Data>;

  Provider_EchoString_Params_Data();
  ~Provider_EchoString_Params_Data() = delete;
};
static_assert(sizeof(Provider_EchoString_Params_Data) == 16,
              "Bad sizeof(Provider_EchoString_Params_Data)");
class  Provider_EchoString_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<mojo::internal::String_Data> a;

 private:
  friend class mojo::internal::MessageFragment<Provider_EchoString_ResponseParams_Data>;

  Provider_EchoString_ResponseParams_Data();
  ~Provider_EchoString_ResponseParams_Data() = delete;
};
static_assert(sizeof(Provider_EchoString_ResponseParams_Data) == 16,
              "Bad sizeof(Provider_EchoString_ResponseParams_Data)");
class  Provider_EchoStrings_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<mojo::internal::String_Data> a;
  mojo::internal::Pointer<mojo::internal::String_Data> b;

 private:
  friend class mojo::internal::MessageFragment<Provider_EchoStrings_Params_Data>;

  Provider_EchoStrings_Params_Data();
  ~Provider_EchoStrings_Params_Data() = delete;
};
static_assert(sizeof(Provider_EchoStrings_Params_Data) == 24,
              "Bad sizeof(Provider_EchoStrings_Params_Data)");
class  Provider_EchoStrings_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<mojo::internal::String_Data> a;
  mojo::internal::Pointer<mojo::internal::String_Data> b;

 private:
  friend class mojo::internal::MessageFragment<Provider_EchoStrings_ResponseParams_Data>;

  Provider_EchoStrings_ResponseParams_Data();
  ~Provider_EchoStrings_ResponseParams_Data() = delete;
};
static_assert(sizeof(Provider_EchoStrings_ResponseParams_Data) == 24,
              "Bad sizeof(Provider_EchoStrings_ResponseParams_Data)");
class  Provider_EchoMessagePipeHandle_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Handle_Data a;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<Provider_EchoMessagePipeHandle_Params_Data>;

  Provider_EchoMessagePipeHandle_Params_Data();
  ~Provider_EchoMessagePipeHandle_Params_Data() = delete;
};
static_assert(sizeof(Provider_EchoMessagePipeHandle_Params_Data) == 16,
              "Bad sizeof(Provider_EchoMessagePipeHandle_Params_Data)");
class  Provider_EchoMessagePipeHandle_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Handle_Data a;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<Provider_EchoMessagePipeHandle_ResponseParams_Data>;

  Provider_EchoMessagePipeHandle_ResponseParams_Data();
  ~Provider_EchoMessagePipeHandle_ResponseParams_Data() = delete;
};
static_assert(sizeof(Provider_EchoMessagePipeHandle_ResponseParams_Data) == 16,
              "Bad sizeof(Provider_EchoMessagePipeHandle_ResponseParams_Data)");
class  Provider_EchoEnum_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t a;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<Provider_EchoEnum_Params_Data>;

  Provider_EchoEnum_Params_Data();
  ~Provider_EchoEnum_Params_Data() = delete;
};
static_assert(sizeof(Provider_EchoEnum_Params_Data) == 16,
              "Bad sizeof(Provider_EchoEnum_Params_Data)");
class  Provider_EchoEnum_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t a;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<Provider_EchoEnum_ResponseParams_Data>;

  Provider_EchoEnum_ResponseParams_Data();
  ~Provider_EchoEnum_ResponseParams_Data() = delete;
};
static_assert(sizeof(Provider_EchoEnum_ResponseParams_Data) == 16,
              "Bad sizeof(Provider_EchoEnum_ResponseParams_Data)");
class  Provider_EchoInt_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t a;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<Provider_EchoInt_Params_Data>;

  Provider_EchoInt_Params_Data();
  ~Provider_EchoInt_Params_Data() = delete;
};
static_assert(sizeof(Provider_EchoInt_Params_Data) == 16,
              "Bad sizeof(Provider_EchoInt_Params_Data)");
class  Provider_EchoInt_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int32_t a;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<Provider_EchoInt_ResponseParams_Data>;

  Provider_EchoInt_ResponseParams_Data();
  ~Provider_EchoInt_ResponseParams_Data() = delete;
};
static_assert(sizeof(Provider_EchoInt_ResponseParams_Data) == 16,
              "Bad sizeof(Provider_EchoInt_ResponseParams_Data)");
class  IntegerAccessor_GetInteger_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<IntegerAccessor_GetInteger_Params_Data>;

  IntegerAccessor_GetInteger_Params_Data();
  ~IntegerAccessor_GetInteger_Params_Data() = delete;
};
static_assert(sizeof(IntegerAccessor_GetInteger_Params_Data) == 8,
              "Bad sizeof(IntegerAccessor_GetInteger_Params_Data)");
class  IntegerAccessor_GetInteger_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int64_t data;
  int32_t type;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<IntegerAccessor_GetInteger_ResponseParams_Data>;

  IntegerAccessor_GetInteger_ResponseParams_Data();
  ~IntegerAccessor_GetInteger_ResponseParams_Data() = delete;
};
static_assert(sizeof(IntegerAccessor_GetInteger_ResponseParams_Data) == 24,
              "Bad sizeof(IntegerAccessor_GetInteger_ResponseParams_Data)");
class  IntegerAccessor_SetInteger_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  int64_t data;
  int32_t type;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<IntegerAccessor_SetInteger_Params_Data>;

  IntegerAccessor_SetInteger_Params_Data();
  ~IntegerAccessor_SetInteger_Params_Data() = delete;
};
static_assert(sizeof(IntegerAccessor_SetInteger_Params_Data) == 24,
              "Bad sizeof(IntegerAccessor_SetInteger_Params_Data)");
class  InterfaceFactory_BindInterface_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<::mojo_base::mojom::internal::GenericPendingReceiver_Data> receiver;

 private:
  friend class mojo::internal::MessageFragment<InterfaceFactory_BindInterface_Params_Data>;

  InterfaceFactory_BindInterface_Params_Data();
  ~InterfaceFactory_BindInterface_Params_Data() = delete;
};
static_assert(sizeof(InterfaceFactory_BindInterface_Params_Data) == 16,
              "Bad sizeof(InterfaceFactory_BindInterface_Params_Data)");

}  // namespace internal


class PingTest_Ping_ParamsDataView {
 public:
  PingTest_Ping_ParamsDataView() {}

  PingTest_Ping_ParamsDataView(
      internal::PingTest_Ping_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::PingTest_Ping_Params_Data* data_ = nullptr;
};



class PingTest_Ping_ResponseParamsDataView {
 public:
  PingTest_Ping_ResponseParamsDataView() {}

  PingTest_Ping_ResponseParamsDataView(
      internal::PingTest_Ping_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::PingTest_Ping_ResponseParams_Data* data_ = nullptr;
};



class Provider_EchoString_ParamsDataView {
 public:
  Provider_EchoString_ParamsDataView() {}

  Provider_EchoString_ParamsDataView(
      internal::Provider_EchoString_Params_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetADataView(
      mojo::StringDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadA(UserType* output) {
    
    auto* pointer = data_->a.Get();
    return mojo::internal::Deserialize<mojo::StringDataView>(
        pointer, output, message_);
  }
 private:
  internal::Provider_EchoString_Params_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class Provider_EchoString_ResponseParamsDataView {
 public:
  Provider_EchoString_ResponseParamsDataView() {}

  Provider_EchoString_ResponseParamsDataView(
      internal::Provider_EchoString_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetADataView(
      mojo::StringDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadA(UserType* output) {
    
    auto* pointer = data_->a.Get();
    return mojo::internal::Deserialize<mojo::StringDataView>(
        pointer, output, message_);
  }
 private:
  internal::Provider_EchoString_ResponseParams_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class Provider_EchoStrings_ParamsDataView {
 public:
  Provider_EchoStrings_ParamsDataView() {}

  Provider_EchoStrings_ParamsDataView(
      internal::Provider_EchoStrings_Params_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetADataView(
      mojo::StringDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadA(UserType* output) {
    
    auto* pointer = data_->a.Get();
    return mojo::internal::Deserialize<mojo::StringDataView>(
        pointer, output, message_);
  }
  inline void GetBDataView(
      mojo::StringDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadB(UserType* output) {
    
    auto* pointer = data_->b.Get();
    return mojo::internal::Deserialize<mojo::StringDataView>(
        pointer, output, message_);
  }
 private:
  internal::Provider_EchoStrings_Params_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class Provider_EchoStrings_ResponseParamsDataView {
 public:
  Provider_EchoStrings_ResponseParamsDataView() {}

  Provider_EchoStrings_ResponseParamsDataView(
      internal::Provider_EchoStrings_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetADataView(
      mojo::StringDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadA(UserType* output) {
    
    auto* pointer = data_->a.Get();
    return mojo::internal::Deserialize<mojo::StringDataView>(
        pointer, output, message_);
  }
  inline void GetBDataView(
      mojo::StringDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadB(UserType* output) {
    
    auto* pointer = data_->b.Get();
    return mojo::internal::Deserialize<mojo::StringDataView>(
        pointer, output, message_);
  }
 private:
  internal::Provider_EchoStrings_ResponseParams_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class Provider_EchoMessagePipeHandle_ParamsDataView {
 public:
  Provider_EchoMessagePipeHandle_ParamsDataView() {}

  Provider_EchoMessagePipeHandle_ParamsDataView(
      internal::Provider_EchoMessagePipeHandle_Params_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  mojo::ScopedMessagePipeHandle TakeA() {
    mojo::ScopedMessagePipeHandle result;
    bool ret =
        mojo::internal::Deserialize<mojo::ScopedMessagePipeHandle>(
            &data_->a, &result, message_);
    DCHECK(ret);
    return result;
  }
 private:
  internal::Provider_EchoMessagePipeHandle_Params_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class Provider_EchoMessagePipeHandle_ResponseParamsDataView {
 public:
  Provider_EchoMessagePipeHandle_ResponseParamsDataView() {}

  Provider_EchoMessagePipeHandle_ResponseParamsDataView(
      internal::Provider_EchoMessagePipeHandle_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  mojo::ScopedMessagePipeHandle TakeA() {
    mojo::ScopedMessagePipeHandle result;
    bool ret =
        mojo::internal::Deserialize<mojo::ScopedMessagePipeHandle>(
            &data_->a, &result, message_);
    DCHECK(ret);
    return result;
  }
 private:
  internal::Provider_EchoMessagePipeHandle_ResponseParams_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class Provider_EchoEnum_ParamsDataView {
 public:
  Provider_EchoEnum_ParamsDataView() {}

  Provider_EchoEnum_ParamsDataView(
      internal::Provider_EchoEnum_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadA(UserType* output) const {
    auto data_value = data_->a;
    return mojo::internal::Deserialize<::sample::Enum>(
        data_value, output);
  }
  Enum a() const {
    return ::mojo::internal::ToKnownEnumValueHelper(
          static_cast<::sample::Enum>(data_->a));
  }
 private:
  internal::Provider_EchoEnum_Params_Data* data_ = nullptr;
};



class Provider_EchoEnum_ResponseParamsDataView {
 public:
  Provider_EchoEnum_ResponseParamsDataView() {}

  Provider_EchoEnum_ResponseParamsDataView(
      internal::Provider_EchoEnum_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadA(UserType* output) const {
    auto data_value = data_->a;
    return mojo::internal::Deserialize<::sample::Enum>(
        data_value, output);
  }
  Enum a() const {
    return ::mojo::internal::ToKnownEnumValueHelper(
          static_cast<::sample::Enum>(data_->a));
  }
 private:
  internal::Provider_EchoEnum_ResponseParams_Data* data_ = nullptr;
};



class Provider_EchoInt_ParamsDataView {
 public:
  Provider_EchoInt_ParamsDataView() {}

  Provider_EchoInt_ParamsDataView(
      internal::Provider_EchoInt_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t a() const {
    return data_->a;
  }
 private:
  internal::Provider_EchoInt_Params_Data* data_ = nullptr;
};



class Provider_EchoInt_ResponseParamsDataView {
 public:
  Provider_EchoInt_ResponseParamsDataView() {}

  Provider_EchoInt_ResponseParamsDataView(
      internal::Provider_EchoInt_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int32_t a() const {
    return data_->a;
  }
 private:
  internal::Provider_EchoInt_ResponseParams_Data* data_ = nullptr;
};



class IntegerAccessor_GetInteger_ParamsDataView {
 public:
  IntegerAccessor_GetInteger_ParamsDataView() {}

  IntegerAccessor_GetInteger_ParamsDataView(
      internal::IntegerAccessor_GetInteger_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::IntegerAccessor_GetInteger_Params_Data* data_ = nullptr;
};



class IntegerAccessor_GetInteger_ResponseParamsDataView {
 public:
  IntegerAccessor_GetInteger_ResponseParamsDataView() {}

  IntegerAccessor_GetInteger_ResponseParamsDataView(
      internal::IntegerAccessor_GetInteger_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int64_t data() const {
    return data_->data;
  }
  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadType(UserType* output) const {
    auto data_value = data_->header_.version >= 2
                      ? data_->type : 0;
    return mojo::internal::Deserialize<::sample::Enum>(
        data_value, output);
  }
  Enum type() const {
    if (data_->header_.version < 2)
      return Enum{};
    return ::mojo::internal::ToKnownEnumValueHelper(
          static_cast<::sample::Enum>(data_->type));
  }
 private:
  internal::IntegerAccessor_GetInteger_ResponseParams_Data* data_ = nullptr;
};



class IntegerAccessor_SetInteger_ParamsDataView {
 public:
  IntegerAccessor_SetInteger_ParamsDataView() {}

  IntegerAccessor_SetInteger_ParamsDataView(
      internal::IntegerAccessor_SetInteger_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
  int64_t data() const {
    return data_->data;
  }
  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadType(UserType* output) const {
    auto data_value = data_->header_.version >= 3
                      ? data_->type : 0;
    return mojo::internal::Deserialize<::sample::Enum>(
        data_value, output);
  }
  Enum type() const {
    if (data_->header_.version < 3)
      return Enum{};
    return ::mojo::internal::ToKnownEnumValueHelper(
          static_cast<::sample::Enum>(data_->type));
  }
 private:
  internal::IntegerAccessor_SetInteger_Params_Data* data_ = nullptr;
};



class InterfaceFactory_BindInterface_ParamsDataView {
 public:
  InterfaceFactory_BindInterface_ParamsDataView() {}

  InterfaceFactory_BindInterface_ParamsDataView(
      internal::InterfaceFactory_BindInterface_Params_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetReceiverDataView(
      ::mojo_base::mojom::GenericPendingReceiverDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadReceiver(UserType* output) {
    
    auto* pointer = data_->receiver.Get();
    return mojo::internal::Deserialize<::mojo_base::mojom::GenericPendingReceiverDataView>(
        pointer, output, message_);
  }
 private:
  internal::InterfaceFactory_BindInterface_Params_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};






inline void Provider_EchoString_ParamsDataView::GetADataView(
    mojo::StringDataView* output) {
  auto pointer = data_->a.Get();
  *output = mojo::StringDataView(pointer, message_);
}


inline void Provider_EchoString_ResponseParamsDataView::GetADataView(
    mojo::StringDataView* output) {
  auto pointer = data_->a.Get();
  *output = mojo::StringDataView(pointer, message_);
}


inline void Provider_EchoStrings_ParamsDataView::GetADataView(
    mojo::StringDataView* output) {
  auto pointer = data_->a.Get();
  *output = mojo::StringDataView(pointer, message_);
}
inline void Provider_EchoStrings_ParamsDataView::GetBDataView(
    mojo::StringDataView* output) {
  auto pointer = data_->b.Get();
  *output = mojo::StringDataView(pointer, message_);
}


inline void Provider_EchoStrings_ResponseParamsDataView::GetADataView(
    mojo::StringDataView* output) {
  auto pointer = data_->a.Get();
  *output = mojo::StringDataView(pointer, message_);
}
inline void Provider_EchoStrings_ResponseParamsDataView::GetBDataView(
    mojo::StringDataView* output) {
  auto pointer = data_->b.Get();
  *output = mojo::StringDataView(pointer, message_);
}




















inline void InterfaceFactory_BindInterface_ParamsDataView::GetReceiverDataView(
    ::mojo_base::mojom::GenericPendingReceiverDataView* output) {
  auto pointer = data_->receiver.Get();
  *output = ::mojo_base::mojom::GenericPendingReceiverDataView(pointer, message_);
}

}  // namespace sample

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_INTERFACES_MOJOM_PARAMS_DATA_H_