// mojo/public/mojom/base/message_pump_type.mojom-shared.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/public/mojom/base/message_pump_type.mojom-shared.h"

#include <utility>

#include "base/stl_util.h"  // for base::size()
#include "base/strings/stringprintf.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/lib/validation_util.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/mojom/base/message_pump_type.mojom-params-data.h"
namespace mojo_base {
namespace mojom {

std::string MessagePumpTypeToString(MessagePumpType value) {
  switch(value) {
    case MessagePumpType::kDefault:
      return "kDefault";
    case MessagePumpType::kUi:
      return "kUi";
    case MessagePumpType::kCustom:
      return "kCustom";
    case MessagePumpType::kIo:
      return "kIo";
    default:
      return base::StringPrintf("Unknown MessagePumpType value: %i", static_cast<int32_t>(value));
  }
}

std::ostream& operator<<(std::ostream& os, MessagePumpType value) {
  return os << MessagePumpTypeToString(value);
}

namespace internal {

}  // namespace internal
}  // namespace mojom
}  // namespace mojo_base

namespace perfetto {

// static
void TraceFormatTraits<::mojo_base::mojom::MessagePumpType>::WriteIntoTracedValue(
   perfetto::TracedValue context, ::mojo_base::mojom::MessagePumpType value) {
  return std::move(context).WriteString(::mojo_base::mojom::MessagePumpTypeToString(value));
}

} // namespace perfetto