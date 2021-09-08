// mojo/public/interfaces/bindings/tests/test_name_generator.mojom-shared.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/public/interfaces/bindings/tests/test_name_generator.mojom-shared.h"

#include <utility>

#include "base/stl_util.h"  // for base::size()
#include "base/strings/stringprintf.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/lib/validation_util.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/interfaces/bindings/tests/test_name_generator.mojom-params-data.h"
namespace sample {

std::string SupportedCasesToString(SupportedCases value) {
  switch(value) {
    case SupportedCases::lowerCamelCase:
      return "lowerCamelCase";
    case SupportedCases::UpperCamelCase:
      return "UpperCamelCase";
    case SupportedCases::snake_case:
      return "snake_case";
    case SupportedCases::MACRO_CASE:
      return "MACRO_CASE";
    case SupportedCases::kHungarianNotation:
      return "kHungarianNotation";
    case SupportedCases::upperACRONYMCase:
      return "upperACRONYMCase";
    default:
      return base::StringPrintf("Unknown SupportedCases value: %i", static_cast<int32_t>(value));
  }
}

std::ostream& operator<<(std::ostream& os, SupportedCases value) {
  return os << SupportedCasesToString(value);
}

namespace internal {

}  // namespace internal
}  // namespace sample

namespace perfetto {

// static
void TraceFormatTraits<::sample::SupportedCases>::WriteIntoTracedValue(
   perfetto::TracedValue context, ::sample::SupportedCases value) {
  return std::move(context).WriteString(::sample::SupportedCasesToString(value));
}

} // namespace perfetto
