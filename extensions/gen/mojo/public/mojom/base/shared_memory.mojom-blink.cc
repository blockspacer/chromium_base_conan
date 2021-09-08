// mojo/public/mojom/base/shared_memory.mojom-blink.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "mojo/public/mojom/base/shared_memory.mojom-blink.h"

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

#include "mojo/public/mojom/base/shared_memory.mojom-params-data.h"
#include "mojo/public/mojom/base/shared_memory.mojom-shared-message-ids.h"

#include "mojo/public/mojom/base/shared_memory.mojom-blink-import-headers.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"


#ifndef MOJO_PUBLIC_MOJOM_BASE_SHARED_MEMORY_MOJOM_BLINK_JUMBO_H_
#define MOJO_PUBLIC_MOJOM_BASE_SHARED_MEMORY_MOJOM_BLINK_JUMBO_H_
#endif
namespace mojo_base {
namespace mojom {
namespace blink {
ReadOnlySharedMemoryRegion::ReadOnlySharedMemoryRegion()
    : buffer() {}

ReadOnlySharedMemoryRegion::ReadOnlySharedMemoryRegion(
    ::mojo::ScopedSharedBufferHandle buffer_in)
    : buffer(std::move(buffer_in)) {}

ReadOnlySharedMemoryRegion::~ReadOnlySharedMemoryRegion() = default;

void ReadOnlySharedMemoryRegion::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "buffer"), this->buffer,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type ::mojo::ScopedSharedBufferHandle>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool ReadOnlySharedMemoryRegion::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
WritableSharedMemoryRegion::WritableSharedMemoryRegion()
    : buffer() {}

WritableSharedMemoryRegion::WritableSharedMemoryRegion(
    ::mojo::ScopedSharedBufferHandle buffer_in)
    : buffer(std::move(buffer_in)) {}

WritableSharedMemoryRegion::~WritableSharedMemoryRegion() = default;

void WritableSharedMemoryRegion::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "buffer"), this->buffer,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type ::mojo::ScopedSharedBufferHandle>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool WritableSharedMemoryRegion::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
UnsafeSharedMemoryRegion::UnsafeSharedMemoryRegion()
    : buffer() {}

UnsafeSharedMemoryRegion::UnsafeSharedMemoryRegion(
    ::mojo::ScopedSharedBufferHandle buffer_in)
    : buffer(std::move(buffer_in)) {}

UnsafeSharedMemoryRegion::~UnsafeSharedMemoryRegion() = default;

void UnsafeSharedMemoryRegion::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "buffer"), this->buffer,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type ::mojo::ScopedSharedBufferHandle>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool UnsafeSharedMemoryRegion::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
}  // namespace blink
}  // namespace mojom
}  // namespace mojo_base

namespace mojo {


// static
bool StructTraits<::mojo_base::mojom::blink::ReadOnlySharedMemoryRegion::DataView, ::mojo_base::mojom::blink::ReadOnlySharedMemoryRegionPtr>::Read(
    ::mojo_base::mojom::blink::ReadOnlySharedMemoryRegion::DataView input,
    ::mojo_base::mojom::blink::ReadOnlySharedMemoryRegionPtr* output) {
  bool success = true;
  ::mojo_base::mojom::blink::ReadOnlySharedMemoryRegionPtr result(::mojo_base::mojom::blink::ReadOnlySharedMemoryRegion::New());
  
      if (success)
        result->buffer = input.TakeBuffer();
  *output = std::move(result);
  return success;
}


// static
bool StructTraits<::mojo_base::mojom::blink::WritableSharedMemoryRegion::DataView, ::mojo_base::mojom::blink::WritableSharedMemoryRegionPtr>::Read(
    ::mojo_base::mojom::blink::WritableSharedMemoryRegion::DataView input,
    ::mojo_base::mojom::blink::WritableSharedMemoryRegionPtr* output) {
  bool success = true;
  ::mojo_base::mojom::blink::WritableSharedMemoryRegionPtr result(::mojo_base::mojom::blink::WritableSharedMemoryRegion::New());
  
      if (success)
        result->buffer = input.TakeBuffer();
  *output = std::move(result);
  return success;
}


// static
bool StructTraits<::mojo_base::mojom::blink::UnsafeSharedMemoryRegion::DataView, ::mojo_base::mojom::blink::UnsafeSharedMemoryRegionPtr>::Read(
    ::mojo_base::mojom::blink::UnsafeSharedMemoryRegion::DataView input,
    ::mojo_base::mojom::blink::UnsafeSharedMemoryRegionPtr* output) {
  bool success = true;
  ::mojo_base::mojom::blink::UnsafeSharedMemoryRegionPtr result(::mojo_base::mojom::blink::UnsafeSharedMemoryRegion::New());
  
      if (success)
        result->buffer = input.TakeBuffer();
  *output = std::move(result);
  return success;
}

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif