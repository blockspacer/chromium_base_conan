// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_GPU_GPU_RENDER_STAGE_EVENT_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_GPU_GPU_RENDER_STAGE_EVENT_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {

class GpuRenderStageEvent_ExtraData;
class GpuRenderStageEvent_Specifications;
class GpuRenderStageEvent_Specifications_ContextSpec;
class GpuRenderStageEvent_Specifications_Description;
enum InternedGpuRenderStageSpecification_RenderStageCategory : int32_t;
enum InternedGraphicsContext_Api : int32_t;

enum InternedGpuRenderStageSpecification_RenderStageCategory : int32_t {
  InternedGpuRenderStageSpecification_RenderStageCategory_OTHER = 0,
  InternedGpuRenderStageSpecification_RenderStageCategory_GRAPHICS = 1,
  InternedGpuRenderStageSpecification_RenderStageCategory_COMPUTE = 2,
};

const InternedGpuRenderStageSpecification_RenderStageCategory InternedGpuRenderStageSpecification_RenderStageCategory_MIN = InternedGpuRenderStageSpecification_RenderStageCategory_OTHER;
const InternedGpuRenderStageSpecification_RenderStageCategory InternedGpuRenderStageSpecification_RenderStageCategory_MAX = InternedGpuRenderStageSpecification_RenderStageCategory_COMPUTE;

enum InternedGraphicsContext_Api : int32_t {
  InternedGraphicsContext_Api_UNDEFINED = 0,
  InternedGraphicsContext_Api_OPEN_GL = 1,
  InternedGraphicsContext_Api_VULKAN = 2,
  InternedGraphicsContext_Api_OPEN_CL = 3,
};

const InternedGraphicsContext_Api InternedGraphicsContext_Api_MIN = InternedGraphicsContext_Api_UNDEFINED;
const InternedGraphicsContext_Api InternedGraphicsContext_Api_MAX = InternedGraphicsContext_Api_OPEN_CL;

class InternedGpuRenderStageSpecification_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/4, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  InternedGpuRenderStageSpecification_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit InternedGpuRenderStageSpecification_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit InternedGpuRenderStageSpecification_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_iid() const { return at<1>().valid(); }
  uint64_t iid() const { return at<1>().as_uint64(); }
  bool has_name() const { return at<2>().valid(); }
  ::protozero::ConstChars name() const { return at<2>().as_string(); }
  bool has_description() const { return at<3>().valid(); }
  ::protozero::ConstChars description() const { return at<3>().as_string(); }
  bool has_category() const { return at<4>().valid(); }
  int32_t category() const { return at<4>().as_int32(); }
};

class InternedGpuRenderStageSpecification : public ::protozero::Message {
 public:
  using Decoder = InternedGpuRenderStageSpecification_Decoder;
  enum : int32_t {
    kIidFieldNumber = 1,
    kNameFieldNumber = 2,
    kDescriptionFieldNumber = 3,
    kCategoryFieldNumber = 4,
  };
  using RenderStageCategory = ::perfetto::protos::pbzero::InternedGpuRenderStageSpecification_RenderStageCategory;
  static const RenderStageCategory OTHER = InternedGpuRenderStageSpecification_RenderStageCategory_OTHER;
  static const RenderStageCategory GRAPHICS = InternedGpuRenderStageSpecification_RenderStageCategory_GRAPHICS;
  static const RenderStageCategory COMPUTE = InternedGpuRenderStageSpecification_RenderStageCategory_COMPUTE;
  void set_iid(uint64_t value) {
    AppendVarInt(1, value);
  }
  void set_name(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
  void set_description(const std::string& value) {
    AppendBytes(3, value.data(), value.size());
  }
  void set_description(const char* data, size_t size) {
    AppendBytes(3, data, size);
  }
  void set_category(::perfetto::protos::pbzero::InternedGpuRenderStageSpecification_RenderStageCategory value) {
    AppendTinyVarInt(4, value);
  }
};

class InternedGraphicsContext_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  InternedGraphicsContext_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit InternedGraphicsContext_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit InternedGraphicsContext_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_iid() const { return at<1>().valid(); }
  uint64_t iid() const { return at<1>().as_uint64(); }
  bool has_pid() const { return at<2>().valid(); }
  int32_t pid() const { return at<2>().as_int32(); }
  bool has_api() const { return at<3>().valid(); }
  int32_t api() const { return at<3>().as_int32(); }
};

class InternedGraphicsContext : public ::protozero::Message {
 public:
  using Decoder = InternedGraphicsContext_Decoder;
  enum : int32_t {
    kIidFieldNumber = 1,
    kPidFieldNumber = 2,
    kApiFieldNumber = 3,
  };
  using Api = ::perfetto::protos::pbzero::InternedGraphicsContext_Api;
  static const Api UNDEFINED = InternedGraphicsContext_Api_UNDEFINED;
  static const Api OPEN_GL = InternedGraphicsContext_Api_OPEN_GL;
  static const Api VULKAN = InternedGraphicsContext_Api_VULKAN;
  static const Api OPEN_CL = InternedGraphicsContext_Api_OPEN_CL;
  void set_iid(uint64_t value) {
    AppendVarInt(1, value);
  }
  void set_pid(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_api(::perfetto::protos::pbzero::InternedGraphicsContext_Api value) {
    AppendTinyVarInt(3, value);
  }
};

class GpuRenderStageEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/15, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  GpuRenderStageEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit GpuRenderStageEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit GpuRenderStageEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_event_id() const { return at<1>().valid(); }
  uint64_t event_id() const { return at<1>().as_uint64(); }
  bool has_duration() const { return at<2>().valid(); }
  uint64_t duration() const { return at<2>().as_uint64(); }
  bool has_hw_queue_iid() const { return at<13>().valid(); }
  uint64_t hw_queue_iid() const { return at<13>().as_uint64(); }
  bool has_stage_iid() const { return at<14>().valid(); }
  uint64_t stage_iid() const { return at<14>().as_uint64(); }
  bool has_gpu_id() const { return at<11>().valid(); }
  int32_t gpu_id() const { return at<11>().as_int32(); }
  bool has_context() const { return at<5>().valid(); }
  uint64_t context() const { return at<5>().as_uint64(); }
  bool has_render_target_handle() const { return at<8>().valid(); }
  uint64_t render_target_handle() const { return at<8>().as_uint64(); }
  bool has_submission_id() const { return at<10>().valid(); }
  uint32_t submission_id() const { return at<10>().as_uint32(); }
  bool has_extra_data() const { return at<6>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> extra_data() const { return GetRepeated<::protozero::ConstBytes>(6); }
  bool has_render_pass_handle() const { return at<9>().valid(); }
  uint64_t render_pass_handle() const { return at<9>().as_uint64(); }
  bool has_render_subpass_index_mask() const { return at<15>().valid(); }
  ::protozero::RepeatedFieldIterator<uint64_t> render_subpass_index_mask() const { return GetRepeated<uint64_t>(15); }
  bool has_command_buffer_handle() const { return at<12>().valid(); }
  uint64_t command_buffer_handle() const { return at<12>().as_uint64(); }
  bool has_specifications() const { return at<7>().valid(); }
  ::protozero::ConstBytes specifications() const { return at<7>().as_bytes(); }
  bool has_hw_queue_id() const { return at<3>().valid(); }
  int32_t hw_queue_id() const { return at<3>().as_int32(); }
  bool has_stage_id() const { return at<4>().valid(); }
  int32_t stage_id() const { return at<4>().as_int32(); }
};

class GpuRenderStageEvent : public ::protozero::Message {
 public:
  using Decoder = GpuRenderStageEvent_Decoder;
  enum : int32_t {
    kEventIdFieldNumber = 1,
    kDurationFieldNumber = 2,
    kHwQueueIidFieldNumber = 13,
    kStageIidFieldNumber = 14,
    kGpuIdFieldNumber = 11,
    kContextFieldNumber = 5,
    kRenderTargetHandleFieldNumber = 8,
    kSubmissionIdFieldNumber = 10,
    kExtraDataFieldNumber = 6,
    kRenderPassHandleFieldNumber = 9,
    kRenderSubpassIndexMaskFieldNumber = 15,
    kCommandBufferHandleFieldNumber = 12,
    kSpecificationsFieldNumber = 7,
    kHwQueueIdFieldNumber = 3,
    kStageIdFieldNumber = 4,
  };
  using ExtraData = ::perfetto::protos::pbzero::GpuRenderStageEvent_ExtraData;
  using Specifications = ::perfetto::protos::pbzero::GpuRenderStageEvent_Specifications;
  void set_event_id(uint64_t value) {
    AppendVarInt(1, value);
  }
  void set_duration(uint64_t value) {
    AppendVarInt(2, value);
  }
  void set_hw_queue_iid(uint64_t value) {
    AppendVarInt(13, value);
  }
  void set_stage_iid(uint64_t value) {
    AppendVarInt(14, value);
  }
  void set_gpu_id(int32_t value) {
    AppendVarInt(11, value);
  }
  void set_context(uint64_t value) {
    AppendVarInt(5, value);
  }
  void set_render_target_handle(uint64_t value) {
    AppendVarInt(8, value);
  }
  void set_submission_id(uint32_t value) {
    AppendVarInt(10, value);
  }
  template <typename T = GpuRenderStageEvent_ExtraData> T* add_extra_data() {
    return BeginNestedMessage<T>(6);
  }

  void set_render_pass_handle(uint64_t value) {
    AppendVarInt(9, value);
  }
  void add_render_subpass_index_mask(uint64_t value) {
    AppendVarInt(15, value);
  }
  void set_command_buffer_handle(uint64_t value) {
    AppendVarInt(12, value);
  }
  template <typename T = GpuRenderStageEvent_Specifications> T* set_specifications() {
    return BeginNestedMessage<T>(7);
  }

  void set_hw_queue_id(int32_t value) {
    AppendVarInt(3, value);
  }
  void set_stage_id(int32_t value) {
    AppendVarInt(4, value);
  }
};

class GpuRenderStageEvent_Specifications_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  GpuRenderStageEvent_Specifications_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit GpuRenderStageEvent_Specifications_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit GpuRenderStageEvent_Specifications_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_context_spec() const { return at<1>().valid(); }
  ::protozero::ConstBytes context_spec() const { return at<1>().as_bytes(); }
  bool has_hw_queue() const { return at<2>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> hw_queue() const { return GetRepeated<::protozero::ConstBytes>(2); }
  bool has_stage() const { return at<3>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> stage() const { return GetRepeated<::protozero::ConstBytes>(3); }
};

class GpuRenderStageEvent_Specifications : public ::protozero::Message {
 public:
  using Decoder = GpuRenderStageEvent_Specifications_Decoder;
  enum : int32_t {
    kContextSpecFieldNumber = 1,
    kHwQueueFieldNumber = 2,
    kStageFieldNumber = 3,
  };
  using ContextSpec = ::perfetto::protos::pbzero::GpuRenderStageEvent_Specifications_ContextSpec;
  using Description = ::perfetto::protos::pbzero::GpuRenderStageEvent_Specifications_Description;
  template <typename T = GpuRenderStageEvent_Specifications_ContextSpec> T* set_context_spec() {
    return BeginNestedMessage<T>(1);
  }

  template <typename T = GpuRenderStageEvent_Specifications_Description> T* add_hw_queue() {
    return BeginNestedMessage<T>(2);
  }

  template <typename T = GpuRenderStageEvent_Specifications_Description> T* add_stage() {
    return BeginNestedMessage<T>(3);
  }

};

class GpuRenderStageEvent_Specifications_Description_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  GpuRenderStageEvent_Specifications_Description_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit GpuRenderStageEvent_Specifications_Description_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit GpuRenderStageEvent_Specifications_Description_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
  bool has_description() const { return at<2>().valid(); }
  ::protozero::ConstChars description() const { return at<2>().as_string(); }
};

class GpuRenderStageEvent_Specifications_Description : public ::protozero::Message {
 public:
  using Decoder = GpuRenderStageEvent_Specifications_Description_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
    kDescriptionFieldNumber = 2,
  };
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_description(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_description(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
};

class GpuRenderStageEvent_Specifications_ContextSpec_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  GpuRenderStageEvent_Specifications_ContextSpec_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit GpuRenderStageEvent_Specifications_ContextSpec_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit GpuRenderStageEvent_Specifications_ContextSpec_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_context() const { return at<1>().valid(); }
  uint64_t context() const { return at<1>().as_uint64(); }
  bool has_pid() const { return at<2>().valid(); }
  int32_t pid() const { return at<2>().as_int32(); }
};

class GpuRenderStageEvent_Specifications_ContextSpec : public ::protozero::Message {
 public:
  using Decoder = GpuRenderStageEvent_Specifications_ContextSpec_Decoder;
  enum : int32_t {
    kContextFieldNumber = 1,
    kPidFieldNumber = 2,
  };
  void set_context(uint64_t value) {
    AppendVarInt(1, value);
  }
  void set_pid(int32_t value) {
    AppendVarInt(2, value);
  }
};

class GpuRenderStageEvent_ExtraData_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  GpuRenderStageEvent_ExtraData_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit GpuRenderStageEvent_ExtraData_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit GpuRenderStageEvent_ExtraData_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
  bool has_value() const { return at<2>().valid(); }
  ::protozero::ConstChars value() const { return at<2>().as_string(); }
};

class GpuRenderStageEvent_ExtraData : public ::protozero::Message {
 public:
  using Decoder = GpuRenderStageEvent_ExtraData_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
    kValueFieldNumber = 2,
  };
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_value(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_value(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
