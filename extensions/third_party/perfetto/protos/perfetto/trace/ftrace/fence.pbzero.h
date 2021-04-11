// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_FENCE_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_FENCE_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {


class FenceSignaledFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/4, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  FenceSignaledFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit FenceSignaledFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit FenceSignaledFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_context() const { return at<1>().valid(); }
  uint32_t context() const { return at<1>().as_uint32(); }
  bool has_driver() const { return at<2>().valid(); }
  ::protozero::ConstChars driver() const { return at<2>().as_string(); }
  bool has_seqno() const { return at<3>().valid(); }
  uint32_t seqno() const { return at<3>().as_uint32(); }
  bool has_timeline() const { return at<4>().valid(); }
  ::protozero::ConstChars timeline() const { return at<4>().as_string(); }
};

class FenceSignaledFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = FenceSignaledFtraceEvent_Decoder;
  enum : int32_t {
    kContextFieldNumber = 1,
    kDriverFieldNumber = 2,
    kSeqnoFieldNumber = 3,
    kTimelineFieldNumber = 4,
  };
  void set_context(uint32_t value) {
    AppendVarInt(1, value);
  }
  void set_driver(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_driver(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
  void set_seqno(uint32_t value) {
    AppendVarInt(3, value);
  }
  void set_timeline(const std::string& value) {
    AppendBytes(4, value.data(), value.size());
  }
  void set_timeline(const char* data, size_t size) {
    AppendBytes(4, data, size);
  }
};

class FenceEnableSignalFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/4, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  FenceEnableSignalFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit FenceEnableSignalFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit FenceEnableSignalFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_context() const { return at<1>().valid(); }
  uint32_t context() const { return at<1>().as_uint32(); }
  bool has_driver() const { return at<2>().valid(); }
  ::protozero::ConstChars driver() const { return at<2>().as_string(); }
  bool has_seqno() const { return at<3>().valid(); }
  uint32_t seqno() const { return at<3>().as_uint32(); }
  bool has_timeline() const { return at<4>().valid(); }
  ::protozero::ConstChars timeline() const { return at<4>().as_string(); }
};

class FenceEnableSignalFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = FenceEnableSignalFtraceEvent_Decoder;
  enum : int32_t {
    kContextFieldNumber = 1,
    kDriverFieldNumber = 2,
    kSeqnoFieldNumber = 3,
    kTimelineFieldNumber = 4,
  };
  void set_context(uint32_t value) {
    AppendVarInt(1, value);
  }
  void set_driver(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_driver(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
  void set_seqno(uint32_t value) {
    AppendVarInt(3, value);
  }
  void set_timeline(const std::string& value) {
    AppendBytes(4, value.data(), value.size());
  }
  void set_timeline(const char* data, size_t size) {
    AppendBytes(4, data, size);
  }
};

class FenceDestroyFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/4, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  FenceDestroyFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit FenceDestroyFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit FenceDestroyFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_context() const { return at<1>().valid(); }
  uint32_t context() const { return at<1>().as_uint32(); }
  bool has_driver() const { return at<2>().valid(); }
  ::protozero::ConstChars driver() const { return at<2>().as_string(); }
  bool has_seqno() const { return at<3>().valid(); }
  uint32_t seqno() const { return at<3>().as_uint32(); }
  bool has_timeline() const { return at<4>().valid(); }
  ::protozero::ConstChars timeline() const { return at<4>().as_string(); }
};

class FenceDestroyFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = FenceDestroyFtraceEvent_Decoder;
  enum : int32_t {
    kContextFieldNumber = 1,
    kDriverFieldNumber = 2,
    kSeqnoFieldNumber = 3,
    kTimelineFieldNumber = 4,
  };
  void set_context(uint32_t value) {
    AppendVarInt(1, value);
  }
  void set_driver(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_driver(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
  void set_seqno(uint32_t value) {
    AppendVarInt(3, value);
  }
  void set_timeline(const std::string& value) {
    AppendBytes(4, value.data(), value.size());
  }
  void set_timeline(const char* data, size_t size) {
    AppendBytes(4, data, size);
  }
};

class FenceInitFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/4, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  FenceInitFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit FenceInitFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit FenceInitFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_context() const { return at<1>().valid(); }
  uint32_t context() const { return at<1>().as_uint32(); }
  bool has_driver() const { return at<2>().valid(); }
  ::protozero::ConstChars driver() const { return at<2>().as_string(); }
  bool has_seqno() const { return at<3>().valid(); }
  uint32_t seqno() const { return at<3>().as_uint32(); }
  bool has_timeline() const { return at<4>().valid(); }
  ::protozero::ConstChars timeline() const { return at<4>().as_string(); }
};

class FenceInitFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = FenceInitFtraceEvent_Decoder;
  enum : int32_t {
    kContextFieldNumber = 1,
    kDriverFieldNumber = 2,
    kSeqnoFieldNumber = 3,
    kTimelineFieldNumber = 4,
  };
  void set_context(uint32_t value) {
    AppendVarInt(1, value);
  }
  void set_driver(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_driver(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
  void set_seqno(uint32_t value) {
    AppendVarInt(3, value);
  }
  void set_timeline(const std::string& value) {
    AppendBytes(4, value.data(), value.size());
  }
  void set_timeline(const char* data, size_t size) {
    AppendBytes(4, data, size);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.