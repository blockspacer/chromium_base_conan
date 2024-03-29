// mojo/public/js/ts/bindings/tests/export2.test-mojom-blink.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "mojo/public/js/ts/bindings/tests/export2.test-mojom-blink.h"

#include <math.h>
#include <stdint.h>
#include <utility>

#include "base/hash/md5_constexpr.h"
#include "base/run_loop.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/common/task_annotator.h"
#include "base/trace_event/trace_event.h"
#include "mojo/public/cpp/bindings/lib/generated_code_util.h"
#include "mojo/public/cpp/bindings/lib/message_internal.h"
#include "mojo/public/cpp/bindings/lib/serialization_util.h"
#include "mojo/public/cpp/bindings/lib/unserialized_message_context.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/mojo_buildflags.h"
#include "mojo/public/interfaces/bindings/interface_control_messages.mojom.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/js/ts/bindings/tests/export2.test-mojom-params-data.h"
#include "mojo/public/js/ts/bindings/tests/export2.test-mojom-shared-message-ids.h"

#include "mojo/public/js/ts/bindings/tests/export2.test-mojom-blink-import-headers.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"


#ifndef MOJO_PUBLIC_JS_TS_BINDINGS_TESTS_EXPORT2_TEST_MOJOM_BLINK_JUMBO_H_
#define MOJO_PUBLIC_JS_TS_BINDINGS_TESTS_EXPORT2_TEST_MOJOM_BLINK_JUMBO_H_
#endif
namespace mojo {
namespace tstest {
namespace exported {
namespace blink {
ExportedStructTwo::ExportedStructTwo()
    : value() {}

ExportedStructTwo::ExportedStructTwo(
    bool value_in)
    : value(std::move(value_in)) {}

ExportedStructTwo::~ExportedStructTwo() = default;
size_t ExportedStructTwo::Hash(size_t seed) const {
  seed = mojo::internal::WTFHash(seed, this->value);
  return seed;
}

void ExportedStructTwo::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "value"), this->value,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type bool>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool ExportedStructTwo::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
}  // namespace blink
}  // namespace exported
}  // namespace tstest
}  // namespace mojo

namespace mojo {


// static
bool StructTraits<::mojo::tstest::exported::blink::ExportedStructTwo::DataView, ::mojo::tstest::exported::blink::ExportedStructTwoPtr>::Read(
    ::mojo::tstest::exported::blink::ExportedStructTwo::DataView input,
    ::mojo::tstest::exported::blink::ExportedStructTwoPtr* output) {
  bool success = true;
  ::mojo::tstest::exported::blink::ExportedStructTwoPtr result(::mojo::tstest::exported::blink::ExportedStructTwo::New());
  
      if (success)
        result->value = input.value();
  *output = std::move(result);
  return success;
}

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif