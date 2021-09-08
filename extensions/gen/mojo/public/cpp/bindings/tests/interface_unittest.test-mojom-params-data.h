// mojo/public/cpp/bindings/tests/interface_unittest.test-mojom-params-data.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_TESTS_INTERFACE_UNITTEST_TEST_MOJOM_PARAMS_DATA_H_
#define MOJO_PUBLIC_CPP_BINDINGS_TESTS_INTERFACE_UNITTEST_TEST_MOJOM_PARAMS_DATA_H_

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
namespace interface_unittest {
namespace mojom {
namespace internal {
class  VeryCoolInterface_DoesNotMatter_Params_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;

 private:
  friend class mojo::internal::MessageFragment<VeryCoolInterface_DoesNotMatter_Params_Data>;

  VeryCoolInterface_DoesNotMatter_Params_Data();
  ~VeryCoolInterface_DoesNotMatter_Params_Data() = delete;
};
static_assert(sizeof(VeryCoolInterface_DoesNotMatter_Params_Data) == 8,
              "Bad sizeof(VeryCoolInterface_DoesNotMatter_Params_Data)");

}  // namespace internal


class VeryCoolInterface_DoesNotMatter_ParamsDataView {
 public:
  VeryCoolInterface_DoesNotMatter_ParamsDataView() {}

  VeryCoolInterface_DoesNotMatter_ParamsDataView(
      internal::VeryCoolInterface_DoesNotMatter_Params_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::VeryCoolInterface_DoesNotMatter_Params_Data* data_ = nullptr;
};



}  // namespace mojom
}  // namespace interface_unittest
}  // namespace test
}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif  // MOJO_PUBLIC_CPP_BINDINGS_TESTS_INTERFACE_UNITTEST_TEST_MOJOM_PARAMS_DATA_H_