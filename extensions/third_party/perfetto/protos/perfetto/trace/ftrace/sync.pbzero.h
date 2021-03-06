// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_SYNC_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_SYNC_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {


class SyncWaitFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SyncWaitFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SyncWaitFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SyncWaitFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
  bool has_status() const { return at<2>().valid(); }
  int32_t status() const { return at<2>().as_int32(); }
  bool has_begin() const { return at<3>().valid(); }
  uint32_t begin() const { return at<3>().as_uint32(); }
};

class SyncWaitFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SyncWaitFtraceEvent_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
    kStatusFieldNumber = 2,
    kBeginFieldNumber = 3,
  };
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_status(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_begin(uint32_t value) {
    AppendVarInt(3, value);
  }
};

class SyncTimelineFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SyncTimelineFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SyncTimelineFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SyncTimelineFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
  bool has_value() const { return at<2>().valid(); }
  ::protozero::ConstChars value() const { return at<2>().as_string(); }
};

class SyncTimelineFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SyncTimelineFtraceEvent_Decoder;
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

class SyncPtFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SyncPtFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SyncPtFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SyncPtFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_timeline() const { return at<1>().valid(); }
  ::protozero::ConstChars timeline() const { return at<1>().as_string(); }
  bool has_value() const { return at<2>().valid(); }
  ::protozero::ConstChars value() const { return at<2>().as_string(); }
};

class SyncPtFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SyncPtFtraceEvent_Decoder;
  enum : int32_t {
    kTimelineFieldNumber = 1,
    kValueFieldNumber = 2,
  };
  void set_timeline(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_timeline(const char* data, size_t size) {
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
