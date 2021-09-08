// mojo/public/interfaces/bindings/tests/test_import.mojom-blink.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "mojo/public/interfaces/bindings/tests/test_import.mojom-blink.h"

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

#include "mojo/public/interfaces/bindings/tests/test_import.mojom-params-data.h"
#include "mojo/public/interfaces/bindings/tests/test_import.mojom-shared-message-ids.h"

#include "mojo/public/interfaces/bindings/tests/test_import.mojom-blink-import-headers.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"


#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_IMPORT_MOJOM_BLINK_JUMBO_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_IMPORT_MOJOM_BLINK_JUMBO_H_
#endif
namespace mojo {
namespace test {
namespace test_import {
namespace blink {
ImportingStruct::ImportingStruct()
    : strings() {}

ImportingStruct::ImportingStruct(
    ::mojo::test::test_export::blink::StringPairPtr strings_in)
    : strings(std::move(strings_in)) {}

ImportingStruct::~ImportingStruct() = default;
size_t ImportingStruct::Hash(size_t seed) const {
  seed = mojo::internal::WTFHash(seed, this->strings);
  return seed;
}

void ImportingStruct::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "strings"), this->strings,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type ::mojo::test::test_export::blink::StringPairPtr>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool ImportingStruct::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
}  // namespace blink
}  // namespace test_import
}  // namespace test
}  // namespace mojo

namespace mojo {


// static
bool StructTraits<::mojo::test::test_import::blink::ImportingStruct::DataView, ::mojo::test::test_import::blink::ImportingStructPtr>::Read(
    ::mojo::test::test_import::blink::ImportingStruct::DataView input,
    ::mojo::test::test_import::blink::ImportingStructPtr* output) {
  bool success = true;
  ::mojo::test::test_import::blink::ImportingStructPtr result(::mojo::test::test_import::blink::ImportingStruct::New());
  
      if (success && !input.ReadStrings(&result->strings))
        success = false;
  *output = std::move(result);
  return success;
}

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif