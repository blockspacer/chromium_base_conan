// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_GPU_VULKAN_API_EVENT_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_GPU_VULKAN_API_EVENT_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {

class VulkanApiEvent_VkDebugUtilsObjectName;
class VulkanApiEvent_VkQueueSubmit;

class VulkanApiEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  VulkanApiEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit VulkanApiEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit VulkanApiEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_vk_debug_utils_object_name() const { return at<1>().valid(); }
  ::protozero::ConstBytes vk_debug_utils_object_name() const { return at<1>().as_bytes(); }
  bool has_vk_queue_submit() const { return at<2>().valid(); }
  ::protozero::ConstBytes vk_queue_submit() const { return at<2>().as_bytes(); }
};

class VulkanApiEvent : public ::protozero::Message {
 public:
  using Decoder = VulkanApiEvent_Decoder;
  enum : int32_t {
    kVkDebugUtilsObjectNameFieldNumber = 1,
    kVkQueueSubmitFieldNumber = 2,
  };
  using VkDebugUtilsObjectName = ::perfetto::protos::pbzero::VulkanApiEvent_VkDebugUtilsObjectName;
  using VkQueueSubmit = ::perfetto::protos::pbzero::VulkanApiEvent_VkQueueSubmit;
  template <typename T = VulkanApiEvent_VkDebugUtilsObjectName> T* set_vk_debug_utils_object_name() {
    return BeginNestedMessage<T>(1);
  }

  template <typename T = VulkanApiEvent_VkQueueSubmit> T* set_vk_queue_submit() {
    return BeginNestedMessage<T>(2);
  }

};

class VulkanApiEvent_VkQueueSubmit_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/6, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  VulkanApiEvent_VkQueueSubmit_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit VulkanApiEvent_VkQueueSubmit_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit VulkanApiEvent_VkQueueSubmit_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_duration_ns() const { return at<1>().valid(); }
  uint64_t duration_ns() const { return at<1>().as_uint64(); }
  bool has_pid() const { return at<2>().valid(); }
  uint32_t pid() const { return at<2>().as_uint32(); }
  bool has_tid() const { return at<3>().valid(); }
  uint32_t tid() const { return at<3>().as_uint32(); }
  bool has_vk_queue() const { return at<4>().valid(); }
  uint64_t vk_queue() const { return at<4>().as_uint64(); }
  bool has_vk_command_buffers() const { return at<5>().valid(); }
  ::protozero::RepeatedFieldIterator<uint64_t> vk_command_buffers() const { return GetRepeated<uint64_t>(5); }
  bool has_submission_id() const { return at<6>().valid(); }
  uint32_t submission_id() const { return at<6>().as_uint32(); }
};

class VulkanApiEvent_VkQueueSubmit : public ::protozero::Message {
 public:
  using Decoder = VulkanApiEvent_VkQueueSubmit_Decoder;
  enum : int32_t {
    kDurationNsFieldNumber = 1,
    kPidFieldNumber = 2,
    kTidFieldNumber = 3,
    kVkQueueFieldNumber = 4,
    kVkCommandBuffersFieldNumber = 5,
    kSubmissionIdFieldNumber = 6,
  };
  void set_duration_ns(uint64_t value) {
    AppendVarInt(1, value);
  }
  void set_pid(uint32_t value) {
    AppendVarInt(2, value);
  }
  void set_tid(uint32_t value) {
    AppendVarInt(3, value);
  }
  void set_vk_queue(uint64_t value) {
    AppendVarInt(4, value);
  }
  void add_vk_command_buffers(uint64_t value) {
    AppendVarInt(5, value);
  }
  void set_submission_id(uint32_t value) {
    AppendVarInt(6, value);
  }
};

class VulkanApiEvent_VkDebugUtilsObjectName_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/5, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  VulkanApiEvent_VkDebugUtilsObjectName_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit VulkanApiEvent_VkDebugUtilsObjectName_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit VulkanApiEvent_VkDebugUtilsObjectName_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_pid() const { return at<1>().valid(); }
  uint32_t pid() const { return at<1>().as_uint32(); }
  bool has_vk_device() const { return at<2>().valid(); }
  uint64_t vk_device() const { return at<2>().as_uint64(); }
  bool has_object_type() const { return at<3>().valid(); }
  int32_t object_type() const { return at<3>().as_int32(); }
  bool has_object() const { return at<4>().valid(); }
  uint64_t object() const { return at<4>().as_uint64(); }
  bool has_object_name() const { return at<5>().valid(); }
  ::protozero::ConstChars object_name() const { return at<5>().as_string(); }
};

class VulkanApiEvent_VkDebugUtilsObjectName : public ::protozero::Message {
 public:
  using Decoder = VulkanApiEvent_VkDebugUtilsObjectName_Decoder;
  enum : int32_t {
    kPidFieldNumber = 1,
    kVkDeviceFieldNumber = 2,
    kObjectTypeFieldNumber = 3,
    kObjectFieldNumber = 4,
    kObjectNameFieldNumber = 5,
  };
  void set_pid(uint32_t value) {
    AppendVarInt(1, value);
  }
  void set_vk_device(uint64_t value) {
    AppendVarInt(2, value);
  }
  void set_object_type(int32_t value) {
    AppendVarInt(3, value);
  }
  void set_object(uint64_t value) {
    AppendVarInt(4, value);
  }
  void set_object_name(const std::string& value) {
    AppendBytes(5, value.data(), value.size());
  }
  void set_object_name(const char* data, size_t size) {
    AppendBytes(5, data, size);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
