// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_CLK_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_CLK_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {


class ClkSetRateFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ClkSetRateFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ClkSetRateFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ClkSetRateFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
  bool has_rate() const { return at<2>().valid(); }
  uint64_t rate() const { return at<2>().as_uint64(); }
};

class ClkSetRateFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = ClkSetRateFtraceEvent_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
    kRateFieldNumber = 2,
  };
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_rate(uint64_t value) {
    AppendVarInt(2, value);
  }
};

class ClkDisableFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/1, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ClkDisableFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ClkDisableFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ClkDisableFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
};

class ClkDisableFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = ClkDisableFtraceEvent_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
  };
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
};

class ClkEnableFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/1, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ClkEnableFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ClkEnableFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ClkEnableFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
};

class ClkEnableFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = ClkEnableFtraceEvent_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
  };
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.