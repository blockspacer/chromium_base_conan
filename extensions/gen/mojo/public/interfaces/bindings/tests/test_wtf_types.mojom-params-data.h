// mojo/public/interfaces/bindings/tests/test_wtf_types.mojom-params-data.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_WTF_TYPES_MOJOM_PARAMS_DATA_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_WTF_TYPES_MOJOM_PARAMS_DATA_H_

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
class  TestWTF_EchoString_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<mojo::internal::String_Data> str;

 private:
  friend class mojo::internal::MessageFragment<TestWTF_EchoString_Params_Data>;

  TestWTF_EchoString_Params_Data();
  ~TestWTF_EchoString_Params_Data() = delete;
};
static_assert(sizeof(TestWTF_EchoString_Params_Data) == 16,
              "Bad sizeof(TestWTF_EchoString_Params_Data)");
class  TestWTF_EchoString_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<mojo::internal::String_Data> str;

 private:
  friend class mojo::internal::MessageFragment<TestWTF_EchoString_ResponseParams_Data>;

  TestWTF_EchoString_ResponseParams_Data();
  ~TestWTF_EchoString_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestWTF_EchoString_ResponseParams_Data) == 16,
              "Bad sizeof(TestWTF_EchoString_ResponseParams_Data)");
class  TestWTF_EchoStringArray_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<mojo::internal::Array_Data<mojo::internal::Pointer<mojo::internal::String_Data>>> arr;

 private:
  friend class mojo::internal::MessageFragment<TestWTF_EchoStringArray_Params_Data>;

  TestWTF_EchoStringArray_Params_Data();
  ~TestWTF_EchoStringArray_Params_Data() = delete;
};
static_assert(sizeof(TestWTF_EchoStringArray_Params_Data) == 16,
              "Bad sizeof(TestWTF_EchoStringArray_Params_Data)");
class  TestWTF_EchoStringArray_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<mojo::internal::Array_Data<mojo::internal::Pointer<mojo::internal::String_Data>>> arr;

 private:
  friend class mojo::internal::MessageFragment<TestWTF_EchoStringArray_ResponseParams_Data>;

  TestWTF_EchoStringArray_ResponseParams_Data();
  ~TestWTF_EchoStringArray_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestWTF_EchoStringArray_ResponseParams_Data) == 16,
              "Bad sizeof(TestWTF_EchoStringArray_ResponseParams_Data)");
class  TestWTF_EchoStringMap_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<mojo::internal::Map_Data<mojo::internal::Pointer<mojo::internal::String_Data>, mojo::internal::Pointer<mojo::internal::String_Data>>> str_map;

 private:
  friend class mojo::internal::MessageFragment<TestWTF_EchoStringMap_Params_Data>;

  TestWTF_EchoStringMap_Params_Data();
  ~TestWTF_EchoStringMap_Params_Data() = delete;
};
static_assert(sizeof(TestWTF_EchoStringMap_Params_Data) == 16,
              "Bad sizeof(TestWTF_EchoStringMap_Params_Data)");
class  TestWTF_EchoStringMap_ResponseParams_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Pointer<mojo::internal::Map_Data<mojo::internal::Pointer<mojo::internal::String_Data>, mojo::internal::Pointer<mojo::internal::String_Data>>> str_map;

 private:
  friend class mojo::internal::MessageFragment<TestWTF_EchoStringMap_ResponseParams_Data>;

  TestWTF_EchoStringMap_ResponseParams_Data();
  ~TestWTF_EchoStringMap_ResponseParams_Data() = delete;
};
static_assert(sizeof(TestWTF_EchoStringMap_ResponseParams_Data) == 16,
              "Bad sizeof(TestWTF_EchoStringMap_ResponseParams_Data)");

}  // namespace internal


class TestWTF_EchoString_ParamsDataView {
 public:
  TestWTF_EchoString_ParamsDataView() {}

  TestWTF_EchoString_ParamsDataView(
      internal::TestWTF_EchoString_Params_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetStrDataView(
      mojo::StringDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadStr(UserType* output) {
    
static_assert(
    mojo::internal::IsValidUserTypeForOptionalValue<
        mojo::StringDataView, UserType>(),
    "Attempting to read the optional `str` field into a type which "
    "cannot represent a null value. Either wrap the destination object "
    "with base::Optional, ensure that any corresponding "
    "{Struct/Union/Array/String}Traits define the necessary IsNull and "
    "SetToNull methods, or use `MaybeReadStr` instead "
    "of `ReadStr if you're fine with null values being "
    "silently ignored in this case.");
    auto* pointer = data_->str.Get();
    return mojo::internal::Deserialize<mojo::StringDataView>(
        pointer, output, message_);
  }
 private:
  internal::TestWTF_EchoString_Params_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class TestWTF_EchoString_ResponseParamsDataView {
 public:
  TestWTF_EchoString_ResponseParamsDataView() {}

  TestWTF_EchoString_ResponseParamsDataView(
      internal::TestWTF_EchoString_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetStrDataView(
      mojo::StringDataView* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadStr(UserType* output) {
    
static_assert(
    mojo::internal::IsValidUserTypeForOptionalValue<
        mojo::StringDataView, UserType>(),
    "Attempting to read the optional `str` field into a type which "
    "cannot represent a null value. Either wrap the destination object "
    "with base::Optional, ensure that any corresponding "
    "{Struct/Union/Array/String}Traits define the necessary IsNull and "
    "SetToNull methods, or use `MaybeReadStr` instead "
    "of `ReadStr if you're fine with null values being "
    "silently ignored in this case.");
    auto* pointer = data_->str.Get();
    return mojo::internal::Deserialize<mojo::StringDataView>(
        pointer, output, message_);
  }
 private:
  internal::TestWTF_EchoString_ResponseParams_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class TestWTF_EchoStringArray_ParamsDataView {
 public:
  TestWTF_EchoStringArray_ParamsDataView() {}

  TestWTF_EchoStringArray_ParamsDataView(
      internal::TestWTF_EchoStringArray_Params_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetArrDataView(
      mojo::ArrayDataView<mojo::StringDataView>* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadArr(UserType* output) {
    
static_assert(
    mojo::internal::IsValidUserTypeForOptionalValue<
        mojo::ArrayDataView<mojo::StringDataView>, UserType>(),
    "Attempting to read the optional `arr` field into a type which "
    "cannot represent a null value. Either wrap the destination object "
    "with base::Optional, ensure that any corresponding "
    "{Struct/Union/Array/String}Traits define the necessary IsNull and "
    "SetToNull methods, or use `MaybeReadArr` instead "
    "of `ReadArr if you're fine with null values being "
    "silently ignored in this case.");
    auto* pointer = data_->arr.Get();
    return mojo::internal::Deserialize<mojo::ArrayDataView<mojo::StringDataView>>(
        pointer, output, message_);
  }
 private:
  internal::TestWTF_EchoStringArray_Params_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class TestWTF_EchoStringArray_ResponseParamsDataView {
 public:
  TestWTF_EchoStringArray_ResponseParamsDataView() {}

  TestWTF_EchoStringArray_ResponseParamsDataView(
      internal::TestWTF_EchoStringArray_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetArrDataView(
      mojo::ArrayDataView<mojo::StringDataView>* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadArr(UserType* output) {
    
static_assert(
    mojo::internal::IsValidUserTypeForOptionalValue<
        mojo::ArrayDataView<mojo::StringDataView>, UserType>(),
    "Attempting to read the optional `arr` field into a type which "
    "cannot represent a null value. Either wrap the destination object "
    "with base::Optional, ensure that any corresponding "
    "{Struct/Union/Array/String}Traits define the necessary IsNull and "
    "SetToNull methods, or use `MaybeReadArr` instead "
    "of `ReadArr if you're fine with null values being "
    "silently ignored in this case.");
    auto* pointer = data_->arr.Get();
    return mojo::internal::Deserialize<mojo::ArrayDataView<mojo::StringDataView>>(
        pointer, output, message_);
  }
 private:
  internal::TestWTF_EchoStringArray_ResponseParams_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class TestWTF_EchoStringMap_ParamsDataView {
 public:
  TestWTF_EchoStringMap_ParamsDataView() {}

  TestWTF_EchoStringMap_ParamsDataView(
      internal::TestWTF_EchoStringMap_Params_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetStrMapDataView(
      mojo::MapDataView<mojo::StringDataView, mojo::StringDataView>* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadStrMap(UserType* output) {
    
static_assert(
    mojo::internal::IsValidUserTypeForOptionalValue<
        mojo::MapDataView<mojo::StringDataView, mojo::StringDataView>, UserType>(),
    "Attempting to read the optional `str_map` field into a type which "
    "cannot represent a null value. Either wrap the destination object "
    "with base::Optional, ensure that any corresponding "
    "{Struct/Union/Array/String}Traits define the necessary IsNull and "
    "SetToNull methods, or use `MaybeReadStrMap` instead "
    "of `ReadStrMap if you're fine with null values being "
    "silently ignored in this case.");
    auto* pointer = data_->str_map.Get();
    return mojo::internal::Deserialize<mojo::MapDataView<mojo::StringDataView, mojo::StringDataView>>(
        pointer, output, message_);
  }
 private:
  internal::TestWTF_EchoStringMap_Params_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class TestWTF_EchoStringMap_ResponseParamsDataView {
 public:
  TestWTF_EchoStringMap_ResponseParamsDataView() {}

  TestWTF_EchoStringMap_ResponseParamsDataView(
      internal::TestWTF_EchoStringMap_ResponseParams_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  inline void GetStrMapDataView(
      mojo::MapDataView<mojo::StringDataView, mojo::StringDataView>* output);

  template <typename UserType>
  WARN_UNUSED_RESULT bool ReadStrMap(UserType* output) {
    
static_assert(
    mojo::internal::IsValidUserTypeForOptionalValue<
        mojo::MapDataView<mojo::StringDataView, mojo::StringDataView>, UserType>(),
    "Attempting to read the optional `str_map` field into a type which "
    "cannot represent a null value. Either wrap the destination object "
    "with base::Optional, ensure that any corresponding "
    "{Struct/Union/Array/String}Traits define the necessary IsNull and "
    "SetToNull methods, or use `MaybeReadStrMap` instead "
    "of `ReadStrMap if you're fine with null values being "
    "silently ignored in this case.");
    auto* pointer = data_->str_map.Get();
    return mojo::internal::Deserialize<mojo::MapDataView<mojo::StringDataView, mojo::StringDataView>>(
        pointer, output, message_);
  }
 private:
  internal::TestWTF_EchoStringMap_ResponseParams_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};


inline void TestWTF_EchoString_ParamsDataView::GetStrDataView(
    mojo::StringDataView* output) {
  auto pointer = data_->str.Get();
  *output = mojo::StringDataView(pointer, message_);
}


inline void TestWTF_EchoString_ResponseParamsDataView::GetStrDataView(
    mojo::StringDataView* output) {
  auto pointer = data_->str.Get();
  *output = mojo::StringDataView(pointer, message_);
}


inline void TestWTF_EchoStringArray_ParamsDataView::GetArrDataView(
    mojo::ArrayDataView<mojo::StringDataView>* output) {
  auto pointer = data_->arr.Get();
  *output = mojo::ArrayDataView<mojo::StringDataView>(pointer, message_);
}


inline void TestWTF_EchoStringArray_ResponseParamsDataView::GetArrDataView(
    mojo::ArrayDataView<mojo::StringDataView>* output) {
  auto pointer = data_->arr.Get();
  *output = mojo::ArrayDataView<mojo::StringDataView>(pointer, message_);
}


inline void TestWTF_EchoStringMap_ParamsDataView::GetStrMapDataView(
    mojo::MapDataView<mojo::StringDataView, mojo::StringDataView>* output) {
  auto pointer = data_->str_map.Get();
  *output = mojo::MapDataView<mojo::StringDataView, mojo::StringDataView>(pointer, message_);
}


inline void TestWTF_EchoStringMap_ResponseParamsDataView::GetStrMapDataView(
    mojo::MapDataView<mojo::StringDataView, mojo::StringDataView>* output) {
  auto pointer = data_->str_map.Get();
  *output = mojo::MapDataView<mojo::StringDataView, mojo::StringDataView>(pointer, message_);
}

}  // namespace test
}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_WTF_TYPES_MOJOM_PARAMS_DATA_H_