// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_MEMORY_GRAPH_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_MEMORY_GRAPH_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {

class MemoryTrackerSnapshot_ProcessSnapshot;
class MemoryTrackerSnapshot_ProcessSnapshot_MemoryEdge;
class MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode;
class MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry;
enum MemoryTrackerSnapshot_LevelOfDetail : int32_t;
enum MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units : int32_t;

enum MemoryTrackerSnapshot_LevelOfDetail : int32_t {
  MemoryTrackerSnapshot_LevelOfDetail_DETAIL_FULL = 0,
  MemoryTrackerSnapshot_LevelOfDetail_DETAIL_LIGHT = 1,
  MemoryTrackerSnapshot_LevelOfDetail_DETAIL_BACKGROUND = 2,
};

const MemoryTrackerSnapshot_LevelOfDetail MemoryTrackerSnapshot_LevelOfDetail_MIN = MemoryTrackerSnapshot_LevelOfDetail_DETAIL_FULL;
const MemoryTrackerSnapshot_LevelOfDetail MemoryTrackerSnapshot_LevelOfDetail_MAX = MemoryTrackerSnapshot_LevelOfDetail_DETAIL_BACKGROUND;

enum MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units : int32_t {
  MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units_UNSPECIFIED = 0,
  MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units_BYTES = 1,
  MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units_COUNT = 2,
};

const MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units_MIN = MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units_UNSPECIFIED;
const MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units_MAX = MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units_COUNT;

class MemoryTrackerSnapshot_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  MemoryTrackerSnapshot_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit MemoryTrackerSnapshot_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit MemoryTrackerSnapshot_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_global_dump_id() const { return at<1>().valid(); }
  uint64_t global_dump_id() const { return at<1>().as_uint64(); }
  bool has_level_of_detail() const { return at<2>().valid(); }
  int32_t level_of_detail() const { return at<2>().as_int32(); }
  bool has_process_memory_dumps() const { return at<3>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> process_memory_dumps() const { return GetRepeated<::protozero::ConstBytes>(3); }
};

class MemoryTrackerSnapshot : public ::protozero::Message {
 public:
  using Decoder = MemoryTrackerSnapshot_Decoder;
  enum : int32_t {
    kGlobalDumpIdFieldNumber = 1,
    kLevelOfDetailFieldNumber = 2,
    kProcessMemoryDumpsFieldNumber = 3,
  };
  using ProcessSnapshot = ::perfetto::protos::pbzero::MemoryTrackerSnapshot_ProcessSnapshot;
  using LevelOfDetail = ::perfetto::protos::pbzero::MemoryTrackerSnapshot_LevelOfDetail;
  static const LevelOfDetail DETAIL_FULL = MemoryTrackerSnapshot_LevelOfDetail_DETAIL_FULL;
  static const LevelOfDetail DETAIL_LIGHT = MemoryTrackerSnapshot_LevelOfDetail_DETAIL_LIGHT;
  static const LevelOfDetail DETAIL_BACKGROUND = MemoryTrackerSnapshot_LevelOfDetail_DETAIL_BACKGROUND;
  void set_global_dump_id(uint64_t value) {
    AppendVarInt(1, value);
  }
  void set_level_of_detail(::perfetto::protos::pbzero::MemoryTrackerSnapshot_LevelOfDetail value) {
    AppendTinyVarInt(2, value);
  }
  template <typename T = MemoryTrackerSnapshot_ProcessSnapshot> T* add_process_memory_dumps() {
    return BeginNestedMessage<T>(3);
  }

};

class MemoryTrackerSnapshot_ProcessSnapshot_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  MemoryTrackerSnapshot_ProcessSnapshot_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit MemoryTrackerSnapshot_ProcessSnapshot_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit MemoryTrackerSnapshot_ProcessSnapshot_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_pid() const { return at<1>().valid(); }
  int32_t pid() const { return at<1>().as_int32(); }
  bool has_allocator_dumps() const { return at<2>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> allocator_dumps() const { return GetRepeated<::protozero::ConstBytes>(2); }
  bool has_memory_edges() const { return at<3>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> memory_edges() const { return GetRepeated<::protozero::ConstBytes>(3); }
};

class MemoryTrackerSnapshot_ProcessSnapshot : public ::protozero::Message {
 public:
  using Decoder = MemoryTrackerSnapshot_ProcessSnapshot_Decoder;
  enum : int32_t {
    kPidFieldNumber = 1,
    kAllocatorDumpsFieldNumber = 2,
    kMemoryEdgesFieldNumber = 3,
  };
  using MemoryNode = ::perfetto::protos::pbzero::MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode;
  using MemoryEdge = ::perfetto::protos::pbzero::MemoryTrackerSnapshot_ProcessSnapshot_MemoryEdge;
  void set_pid(int32_t value) {
    AppendVarInt(1, value);
  }
  template <typename T = MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode> T* add_allocator_dumps() {
    return BeginNestedMessage<T>(2);
  }

  template <typename T = MemoryTrackerSnapshot_ProcessSnapshot_MemoryEdge> T* add_memory_edges() {
    return BeginNestedMessage<T>(3);
  }

};

class MemoryTrackerSnapshot_ProcessSnapshot_MemoryEdge_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/4, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  MemoryTrackerSnapshot_ProcessSnapshot_MemoryEdge_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit MemoryTrackerSnapshot_ProcessSnapshot_MemoryEdge_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit MemoryTrackerSnapshot_ProcessSnapshot_MemoryEdge_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_source_id() const { return at<1>().valid(); }
  uint64_t source_id() const { return at<1>().as_uint64(); }
  bool has_target_id() const { return at<2>().valid(); }
  uint64_t target_id() const { return at<2>().as_uint64(); }
  bool has_importance() const { return at<3>().valid(); }
  uint32_t importance() const { return at<3>().as_uint32(); }
  bool has_overridable() const { return at<4>().valid(); }
  bool overridable() const { return at<4>().as_bool(); }
};

class MemoryTrackerSnapshot_ProcessSnapshot_MemoryEdge : public ::protozero::Message {
 public:
  using Decoder = MemoryTrackerSnapshot_ProcessSnapshot_MemoryEdge_Decoder;
  enum : int32_t {
    kSourceIdFieldNumber = 1,
    kTargetIdFieldNumber = 2,
    kImportanceFieldNumber = 3,
    kOverridableFieldNumber = 4,
  };
  void set_source_id(uint64_t value) {
    AppendVarInt(1, value);
  }
  void set_target_id(uint64_t value) {
    AppendVarInt(2, value);
  }
  void set_importance(uint32_t value) {
    AppendVarInt(3, value);
  }
  void set_overridable(bool value) {
    AppendTinyVarInt(4, value);
  }
};

class MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/5, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_id() const { return at<1>().valid(); }
  uint64_t id() const { return at<1>().as_uint64(); }
  bool has_absolute_name() const { return at<2>().valid(); }
  ::protozero::ConstChars absolute_name() const { return at<2>().as_string(); }
  bool has_weak() const { return at<3>().valid(); }
  bool weak() const { return at<3>().as_bool(); }
  bool has_size_bytes() const { return at<4>().valid(); }
  uint64_t size_bytes() const { return at<4>().as_uint64(); }
  bool has_entries() const { return at<5>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> entries() const { return GetRepeated<::protozero::ConstBytes>(5); }
};

class MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode : public ::protozero::Message {
 public:
  using Decoder = MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_Decoder;
  enum : int32_t {
    kIdFieldNumber = 1,
    kAbsoluteNameFieldNumber = 2,
    kWeakFieldNumber = 3,
    kSizeBytesFieldNumber = 4,
    kEntriesFieldNumber = 5,
  };
  using MemoryNodeEntry = ::perfetto::protos::pbzero::MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry;
  void set_id(uint64_t value) {
    AppendVarInt(1, value);
  }
  void set_absolute_name(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_absolute_name(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
  void set_weak(bool value) {
    AppendTinyVarInt(3, value);
  }
  void set_size_bytes(uint64_t value) {
    AppendVarInt(4, value);
  }
  template <typename T = MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry> T* add_entries() {
    return BeginNestedMessage<T>(5);
  }

};

class MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/4, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
  bool has_units() const { return at<2>().valid(); }
  int32_t units() const { return at<2>().as_int32(); }
  bool has_value_uint64() const { return at<3>().valid(); }
  uint64_t value_uint64() const { return at<3>().as_uint64(); }
  bool has_value_string() const { return at<4>().valid(); }
  ::protozero::ConstChars value_string() const { return at<4>().as_string(); }
};

class MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry : public ::protozero::Message {
 public:
  using Decoder = MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
    kUnitsFieldNumber = 2,
    kValueUint64FieldNumber = 3,
    kValueStringFieldNumber = 4,
  };
  using Units = ::perfetto::protos::pbzero::MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units;
  static const Units UNSPECIFIED = MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units_UNSPECIFIED;
  static const Units BYTES = MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units_BYTES;
  static const Units COUNT = MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units_COUNT;
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_units(::perfetto::protos::pbzero::MemoryTrackerSnapshot_ProcessSnapshot_MemoryNode_MemoryNodeEntry_Units value) {
    AppendTinyVarInt(2, value);
  }
  void set_value_uint64(uint64_t value) {
    AppendVarInt(3, value);
  }
  void set_value_string(const std::string& value) {
    AppendBytes(4, value.data(), value.size());
  }
  void set_value_string(const char* data, size_t size) {
    AppendBytes(4, data, size);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
