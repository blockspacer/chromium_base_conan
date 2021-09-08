// mojo/public/interfaces/bindings/tests/sample_import2.mojom-blink.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "mojo/public/interfaces/bindings/tests/sample_import2.mojom-blink.h"

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

#include "mojo/public/interfaces/bindings/tests/sample_import2.mojom-params-data.h"
#include "mojo/public/interfaces/bindings/tests/sample_import2.mojom-shared-message-ids.h"

#include "mojo/public/interfaces/bindings/tests/sample_import2.mojom-blink-import-headers.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"


#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_IMPORT2_MOJOM_BLINK_JUMBO_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_IMPORT2_MOJOM_BLINK_JUMBO_H_
#endif
namespace imported {
namespace blink {
Size::Size()
    : width(),
      height() {}

Size::Size(
    int32_t width_in,
    int32_t height_in)
    : width(std::move(width_in)),
      height(std::move(height_in)) {}

Size::~Size() = default;
size_t Size::Hash(size_t seed) const {
  seed = mojo::internal::WTFHash(seed, this->width);
  seed = mojo::internal::WTFHash(seed, this->height);
  return seed;
}

void Size::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "width"), this->width,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type int32_t>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "height"), this->height,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type int32_t>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool Size::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
Thing::Thing()
    : shape(::imported::blink::Shape::RECTANGLE),
      color(Color::BLACK),
      location(),
      size() {}

Thing::Thing(
    ::imported::blink::Shape shape_in,
    Color color_in,
    ::imported::blink::PointPtr location_in,
    SizePtr size_in)
    : shape(std::move(shape_in)),
      color(std::move(color_in)),
      location(std::move(location_in)),
      size(std::move(size_in)) {}

Thing::~Thing() = default;
size_t Thing::Hash(size_t seed) const {
  seed = mojo::internal::WTFHash(seed, this->shape);
  seed = mojo::internal::WTFHash(seed, this->color);
  seed = mojo::internal::WTFHash(seed, this->location);
  seed = mojo::internal::WTFHash(seed, this->size);
  return seed;
}

void Thing::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "shape"), this->shape,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type ::imported::blink::Shape>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "color"), this->color,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type Color>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "location"), this->location,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type ::imported::blink::PointPtr>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "size"), this->size,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type SizePtr>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool Thing::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
}  // namespace blink
}  // namespace imported

namespace mojo {


// static
bool StructTraits<::imported::blink::Size::DataView, ::imported::blink::SizePtr>::Read(
    ::imported::blink::Size::DataView input,
    ::imported::blink::SizePtr* output) {
  bool success = true;
  ::imported::blink::SizePtr result(::imported::blink::Size::New());
  
      if (success)
        result->width = input.width();
      if (success)
        result->height = input.height();
  *output = std::move(result);
  return success;
}


// static
bool StructTraits<::imported::blink::Thing::DataView, ::imported::blink::ThingPtr>::Read(
    ::imported::blink::Thing::DataView input,
    ::imported::blink::ThingPtr* output) {
  bool success = true;
  ::imported::blink::ThingPtr result(::imported::blink::Thing::New());
  
      if (success && !input.ReadShape(&result->shape))
        success = false;
      if (success && !input.ReadColor(&result->color))
        success = false;
      if (success && !input.ReadLocation(&result->location))
        success = false;
      if (success && !input.ReadSize(&result->size))
        success = false;
  *output = std::move(result);
  return success;
}

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif