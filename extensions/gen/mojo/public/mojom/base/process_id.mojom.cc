// mojo/public/mojom/base/process_id.mojom.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "mojo/public/mojom/base/process_id.mojom.h"

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

#include "mojo/public/mojom/base/process_id.mojom-params-data.h"
#include "mojo/public/mojom/base/process_id.mojom-shared-message-ids.h"

#include "mojo/public/mojom/base/process_id.mojom-import-headers.h"


#ifndef MOJO_PUBLIC_MOJOM_BASE_PROCESS_ID_MOJOM_JUMBO_H_
#define MOJO_PUBLIC_MOJOM_BASE_PROCESS_ID_MOJOM_JUMBO_H_
#endif
namespace mojo_base {
namespace mojom {
ProcessId::ProcessId()
    : pid() {}

ProcessId::ProcessId(
    uint32_t pid_in)
    : pid(std::move(pid_in)) {}

ProcessId::~ProcessId() = default;

void ProcessId::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "pid"), this->pid,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type uint32_t>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool ProcessId::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
}  // namespace mojom
}  // namespace mojo_base

namespace mojo {


// static
bool StructTraits<::mojo_base::mojom::ProcessId::DataView, ::mojo_base::mojom::ProcessIdPtr>::Read(
    ::mojo_base::mojom::ProcessId::DataView input,
    ::mojo_base::mojom::ProcessIdPtr* output) {
  bool success = true;
  ::mojo_base::mojom::ProcessIdPtr result(::mojo_base::mojom::ProcessId::New());
  
      if (success)
        result->pid = input.pid();
  *output = std::move(result);
  return success;
}

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif