// mojo/public/mojom/base/file_info.mojom-blink.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "mojo/public/mojom/base/file_info.mojom-blink.h"

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

#include "mojo/public/mojom/base/file_info.mojom-params-data.h"
#include "mojo/public/mojom/base/file_info.mojom-shared-message-ids.h"

#include "mojo/public/mojom/base/file_info.mojom-blink-import-headers.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"


#ifndef MOJO_PUBLIC_MOJOM_BASE_FILE_INFO_MOJOM_BLINK_JUMBO_H_
#define MOJO_PUBLIC_MOJOM_BASE_FILE_INFO_MOJOM_BLINK_JUMBO_H_
#endif
namespace mojo_base {
namespace mojom {
namespace blink {
FileInfo::FileInfo()
    : size(),
      is_directory(),
      is_symbolic_link(),
      last_modified(),
      last_accessed(),
      creation_time() {}

FileInfo::FileInfo(
    int64_t size_in,
    bool is_directory_in,
    bool is_symbolic_link_in,
    ::base::Time last_modified_in,
    ::base::Time last_accessed_in,
    ::base::Time creation_time_in)
    : size(std::move(size_in)),
      is_directory(std::move(is_directory_in)),
      is_symbolic_link(std::move(is_symbolic_link_in)),
      last_modified(std::move(last_modified_in)),
      last_accessed(std::move(last_accessed_in)),
      creation_time(std::move(creation_time_in)) {}

FileInfo::~FileInfo() = default;

void FileInfo::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "size"), this->size,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type int64_t>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "is_directory"), this->is_directory,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type bool>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "is_symbolic_link"), this->is_symbolic_link,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type bool>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "last_modified"), this->last_modified,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type ::base::Time>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "last_accessed"), this->last_accessed,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type ::base::Time>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "creation_time"), this->creation_time,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type ::base::Time>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool FileInfo::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
}  // namespace blink
}  // namespace mojom
}  // namespace mojo_base

namespace mojo {


// static
bool StructTraits<::mojo_base::mojom::blink::FileInfo::DataView, ::mojo_base::mojom::blink::FileInfoPtr>::Read(
    ::mojo_base::mojom::blink::FileInfo::DataView input,
    ::mojo_base::mojom::blink::FileInfoPtr* output) {
  bool success = true;
  ::mojo_base::mojom::blink::FileInfoPtr result(::mojo_base::mojom::blink::FileInfo::New());
  
      if (success)
        result->size = input.size();
      if (success)
        result->is_directory = input.is_directory();
      if (success)
        result->is_symbolic_link = input.is_symbolic_link();
      if (success && !input.ReadLastModified(&result->last_modified))
        success = false;
      if (success && !input.ReadLastAccessed(&result->last_accessed))
        success = false;
      if (success && !input.ReadCreationTime(&result->creation_time))
        success = false;
  *output = std::move(result);
  return success;
}

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif