// mojo/public/mojom/base/memory_pressure_level.mojom-shared.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/public/mojom/base/memory_pressure_level.mojom-shared.h"

#include <utility>

#include "base/stl_util.h"  // for base::size()
#include "base/strings/stringprintf.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/lib/validation_util.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/mojom/base/memory_pressure_level.mojom-params-data.h"
namespace mojo_base {
namespace mojom {

std::string MemoryPressureLevelToString(MemoryPressureLevel value) {
  switch(value) {
    case MemoryPressureLevel::NONE:
      return "NONE";
    case MemoryPressureLevel::MODERATE:
      return "MODERATE";
    case MemoryPressureLevel::CRITICAL:
      return "CRITICAL";
    default:
      return base::StringPrintf("Unknown MemoryPressureLevel value: %i", static_cast<int32_t>(value));
  }
}

std::ostream& operator<<(std::ostream& os, MemoryPressureLevel value) {
  return os << MemoryPressureLevelToString(value);
}

namespace internal {

}  // namespace internal
}  // namespace mojom
}  // namespace mojo_base

namespace perfetto {

// static
void TraceFormatTraits<::mojo_base::mojom::MemoryPressureLevel>::WriteIntoTracedValue(
   perfetto::TracedValue context, ::mojo_base::mojom::MemoryPressureLevel value) {
  return std::move(context).WriteString(::mojo_base::mojom::MemoryPressureLevelToString(value));
}

} // namespace perfetto
