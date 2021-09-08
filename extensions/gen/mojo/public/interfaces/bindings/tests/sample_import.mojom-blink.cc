// mojo/public/interfaces/bindings/tests/sample_import.mojom-blink.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif

#include "mojo/public/interfaces/bindings/tests/sample_import.mojom-blink.h"

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

#include "mojo/public/interfaces/bindings/tests/sample_import.mojom-params-data.h"
#include "mojo/public/interfaces/bindings/tests/sample_import.mojom-shared-message-ids.h"

#include "mojo/public/interfaces/bindings/tests/sample_import.mojom-blink-import-headers.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"


#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_IMPORT_MOJOM_BLINK_JUMBO_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_IMPORT_MOJOM_BLINK_JUMBO_H_
#endif
namespace imported {
namespace blink {
Point::Point()
    : x(),
      y() {}

Point::Point(
    int32_t x_in,
    int32_t y_in)
    : x(std::move(x_in)),
      y(std::move(y_in)) {}

Point::~Point() = default;
size_t Point::Hash(size_t seed) const {
  seed = mojo::internal::WTFHash(seed, this->x);
  seed = mojo::internal::WTFHash(seed, this->y);
  return seed;
}

void Point::WriteIntoTracedValue(perfetto::TracedValue context) const {
  auto dict = std::move(context).WriteDictionary();
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "x"), this->x,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type int32_t>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
  perfetto::WriteIntoTracedValueWithFallback(
    dict.AddItem(
      "y"), this->y,
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      "<value of type int32_t>"
#else
      "<value>"
#endif  // BUILDFLAG(MOJO_TRACE_ENABLED)
    );
}

bool Point::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}
PointOrShape::PointOrShape() : tag_(Tag::POINT) {
  data_.point = new PointPtr;
}

PointOrShape::~PointOrShape() {
  DestroyActive();
}


void PointOrShape::set_point(
    PointPtr point) {
  if (tag_ == Tag::POINT) {
    *(data_.point) = std::move(point);
  } else {
    DestroyActive();
    tag_ = Tag::POINT;
    data_.point = new PointPtr(
        std::move(point));
  }
}
void PointOrShape::set_shape(
    Shape shape) {
  if (tag_ != Tag::SHAPE) {
    DestroyActive();
    tag_ = Tag::SHAPE;
  }
  data_.shape = shape;
}

void PointOrShape::DestroyActive() {
  switch (tag_) {

    case Tag::POINT:

      delete data_.point;
      break;
    case Tag::SHAPE:

      break;
  }
}
size_t PointOrShape::Hash(size_t seed) const {
  seed = mojo::internal::HashCombine(seed, static_cast<uint32_t>(tag_));
  switch (tag_) {

    case Tag::POINT:
      return mojo::internal::WTFHash(seed, data_.point);
    case Tag::SHAPE:
      return mojo::internal::WTFHash(seed, data_.shape);
    default:
      NOTREACHED();
      return seed;
  }
}

bool PointOrShape::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context, false);
}
const char ImportedInterface::Name_[] = "imported.ImportedInterface";

ImportedInterfaceProxy::ImportedInterfaceProxy(mojo::MessageReceiverWithResponder* receiver)
    : receiver_(receiver) {
}

void ImportedInterfaceProxy::DoSomething(
    ) {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
  TRACE_EVENT0("mojom", "imported::ImportedInterface::DoSomething");
#endif
  const bool kExpectsResponse = false;
  const bool kIsSync = false;
  
  const uint32_t kFlags =
      ((kExpectsResponse) ? mojo::Message::kFlagExpectsResponse : 0) |
      ((kIsSync) ? mojo::Message::kFlagIsSync : 0);
  
  mojo::Message message(
      internal::kImportedInterface_DoSomething_Name, kFlags, 0, 0, nullptr);
  mojo::internal::MessageFragment<
      ::imported::internal::ImportedInterface_DoSomething_Params_Data> params(
          message);
  params.Allocate();

#if defined(ENABLE_IPC_FUZZER)
  message.set_interface_name(ImportedInterface::Name_);
  message.set_method_name("DoSomething");
#endif
  // This return value may be ignored as false implies the Connector has
  // encountered an error, which will be visible through other means.
  ignore_result(receiver_->Accept(&message));
}

// static
bool ImportedInterfaceStubDispatch::Accept(
    ImportedInterface* impl,
    mojo::Message* message) {
  switch (message->header()->name) {
    case internal::kImportedInterface_DoSomething_Name: {
#if BUILDFLAG(MOJO_TRACE_ENABLED)
      TRACE_EVENT1(
          "mojom",
          "(Impl)imported::ImportedInterface::DoSomething",
          "message", message->name());
#endif
      static constexpr uint32_t kMessageHash = base::MD5Hash32Constexpr(
              "(Impl)imported::ImportedInterface::DoSomething");
      base::TaskAnnotator::ScopedSetIpcHash scoped_ipc_hash(kMessageHash);

      DCHECK(message->is_serialized());
      internal::ImportedInterface_DoSomething_Params_Data* params =
          reinterpret_cast<internal::ImportedInterface_DoSomething_Params_Data*>(
              message->mutable_payload());
      
      bool success = true;
      ImportedInterface_DoSomething_ParamsDataView input_data_view(params, message);
      
      if (!success) {
        ReportValidationErrorForMessage(
            message,
            mojo::internal::VALIDATION_ERROR_DESERIALIZATION_FAILED,
            ImportedInterface::Name_, 0, false);
        return false;
      }
      // A null |impl| means no implementation was bound.
      DCHECK(impl);
      impl->DoSomething();
      return true;
    }
  }
  return false;
}

// static
bool ImportedInterfaceStubDispatch::AcceptWithResponder(
    ImportedInterface* impl,
    mojo::Message* message,
    std::unique_ptr<mojo::MessageReceiverWithStatus> responder) {
  const bool message_is_sync = message->has_flag(mojo::Message::kFlagIsSync);
  const uint64_t request_id = message->request_id();
  ALLOW_UNUSED_LOCAL(message_is_sync);
  ALLOW_UNUSED_LOCAL(request_id);
  switch (message->header()->name) {
    case internal::kImportedInterface_DoSomething_Name: {
      break;
    }
  }
  return false;
}


static const std::pair<uint32_t, mojo::internal::GenericValidationInfo> kImportedInterfaceValidationInfo[] = {
    {internal::kImportedInterface_DoSomething_Name,
     {&internal::ImportedInterface_DoSomething_Params_Data::Validate,
      nullptr /* no response */}},
};

bool ImportedInterfaceRequestValidator::Accept(mojo::Message* message) {
  const char* name = ::imported::blink::ImportedInterface::Name_;
  return mojo::internal::ValidateRequestGeneric(message, name, kImportedInterfaceValidationInfo);
}

}  // namespace blink
}  // namespace imported

namespace mojo {


// static
bool StructTraits<::imported::blink::Point::DataView, ::imported::blink::PointPtr>::Read(
    ::imported::blink::Point::DataView input,
    ::imported::blink::PointPtr* output) {
  bool success = true;
  ::imported::blink::PointPtr result(::imported::blink::Point::New());
  
      if (success)
        result->x = input.x();
      if (success)
        result->y = input.y();
  *output = std::move(result);
  return success;
}

// static
bool UnionTraits<::imported::blink::PointOrShape::DataView, ::imported::blink::PointOrShapePtr>::Read(
    ::imported::blink::PointOrShape::DataView input,
    ::imported::blink::PointOrShapePtr* output) {
  using UnionType = ::imported::blink::PointOrShape;
  using Tag = UnionType::Tag;

  switch (input.tag()) {
    case Tag::POINT: {
      ::imported::blink::PointPtr result_point;
      if (!input.ReadPoint(&result_point))
        return false;

      *output = UnionType::NewPoint(
          std::move(result_point));
      break;
    }
    case Tag::SHAPE: {
      ::imported::blink::Shape result_shape;
      if (!input.ReadShape(&result_shape))
        return false;

      *output = UnionType::NewShape(result_shape);
      break;
    }
    default:
      return false;
  }
  return true;
}

}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif