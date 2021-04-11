// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_IPI_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_IPI_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {


class IpiRaiseFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  IpiRaiseFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit IpiRaiseFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit IpiRaiseFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_target_cpus() const { return at<1>().valid(); }
  uint32_t target_cpus() const { return at<1>().as_uint32(); }
  bool has_reason() const { return at<2>().valid(); }
  ::protozero::ConstChars reason() const { return at<2>().as_string(); }
};

class IpiRaiseFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = IpiRaiseFtraceEvent_Decoder;
  enum : int32_t {
    kTargetCpusFieldNumber = 1,
    kReasonFieldNumber = 2,
  };
  void set_target_cpus(uint32_t value) {
    AppendVarInt(1, value);
  }
  void set_reason(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_reason(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
};

class IpiExitFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/1, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  IpiExitFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit IpiExitFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit IpiExitFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_reason() const { return at<1>().valid(); }
  ::protozero::ConstChars reason() const { return at<1>().as_string(); }
};

class IpiExitFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = IpiExitFtraceEvent_Decoder;
  enum : int32_t {
    kReasonFieldNumber = 1,
  };
  void set_reason(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_reason(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
};

class IpiEntryFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/1, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  IpiEntryFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit IpiEntryFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit IpiEntryFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_reason() const { return at<1>().valid(); }
  ::protozero::ConstChars reason() const { return at<1>().as_string(); }
};

class IpiEntryFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = IpiEntryFtraceEvent_Decoder;
  enum : int32_t {
    kReasonFieldNumber = 1,
  };
  void set_reason(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_reason(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.