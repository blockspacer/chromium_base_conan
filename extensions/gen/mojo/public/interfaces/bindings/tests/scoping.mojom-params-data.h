// mojo/public/interfaces/bindings/tests/scoping.mojom-params-data.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SCOPING_MOJOM_PARAMS_DATA_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SCOPING_MOJOM_PARAMS_DATA_H_

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
class  A_GetB_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Handle_Data b;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<A_GetB_Params_Data>;

  A_GetB_Params_Data();
  ~A_GetB_Params_Data() = delete;
};
static_assert(sizeof(A_GetB_Params_Data) == 16,
              "Bad sizeof(A_GetB_Params_Data)");
class  B_GetC_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::Handle_Data c;
  uint8_t padfinal_[4];

 private:
  friend class mojo::internal::MessageFragment<B_GetC_Params_Data>;

  B_GetC_Params_Data();
  ~B_GetC_Params_Data() = delete;
};
static_assert(sizeof(B_GetC_Params_Data) == 16,
              "Bad sizeof(B_GetC_Params_Data)");
class  C_D_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<C_D_Params_Data>;

  C_D_Params_Data();
  ~C_D_Params_Data() = delete;
};
static_assert(sizeof(C_D_Params_Data) == 8,
              "Bad sizeof(C_D_Params_Data)");

}  // namespace internal


class A_GetB_ParamsDataView {
 public:
  A_GetB_ParamsDataView() {}

  A_GetB_ParamsDataView(
      internal::A_GetB_Params_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  template <typename UserType>
  UserType TakeB() {
    UserType result;
    bool ret =
        mojo::internal::Deserialize<mojo::InterfaceRequestDataView<::mojo::test::BInterfaceBase>>(
            &data_->b, &result, message_);
    DCHECK(ret);
    return result;
  }
 private:
  internal::A_GetB_Params_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class B_GetC_ParamsDataView {
 public:
  B_GetC_ParamsDataView() {}

  B_GetC_ParamsDataView(
      internal::B_GetC_Params_Data* data,
      mojo::Message* message)
      : data_(data), message_(message) {}

  bool is_null() const { return !data_; }
  template <typename UserType>
  UserType TakeC() {
    UserType result;
    bool ret =
        mojo::internal::Deserialize<mojo::InterfaceRequestDataView<::mojo::test::CInterfaceBase>>(
            &data_->c, &result, message_);
    DCHECK(ret);
    return result;
  }
 private:
  internal::B_GetC_Params_Data* data_ = nullptr;
  mojo::Message* message_ = nullptr;
};



class C_D_ParamsDataView {
 public:
  C_D_ParamsDataView() {}

  C_D_ParamsDataView(
      internal::C_D_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::C_D_Params_Data* data_ = nullptr;
};







}  // namespace test
}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SCOPING_MOJOM_PARAMS_DATA_H_