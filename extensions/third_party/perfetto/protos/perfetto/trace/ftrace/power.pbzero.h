// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_POWER_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_POWER_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {


class GpuFrequencyFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  GpuFrequencyFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit GpuFrequencyFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit GpuFrequencyFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_gpu_id() const { return at<1>().valid(); }
  uint32_t gpu_id() const { return at<1>().as_uint32(); }
  bool has_state() const { return at<2>().valid(); }
  uint32_t state() const { return at<2>().as_uint32(); }
};

class GpuFrequencyFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = GpuFrequencyFtraceEvent_Decoder;
  enum : int32_t {
    kGpuIdFieldNumber = 1,
    kStateFieldNumber = 2,
  };
  void set_gpu_id(uint32_t value) {
    AppendVarInt(1, value);
  }
  void set_state(uint32_t value) {
    AppendVarInt(2, value);
  }
};

class SuspendResumeFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SuspendResumeFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SuspendResumeFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SuspendResumeFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_action() const { return at<1>().valid(); }
  ::protozero::ConstChars action() const { return at<1>().as_string(); }
  bool has_val() const { return at<2>().valid(); }
  int32_t val() const { return at<2>().as_int32(); }
  bool has_start() const { return at<3>().valid(); }
  uint32_t start() const { return at<3>().as_uint32(); }
};

class SuspendResumeFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SuspendResumeFtraceEvent_Decoder;
  enum : int32_t {
    kActionFieldNumber = 1,
    kValFieldNumber = 2,
    kStartFieldNumber = 3,
  };
  void set_action(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_action(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_val(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_start(uint32_t value) {
    AppendVarInt(3, value);
  }
};

class ClockSetRateFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ClockSetRateFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ClockSetRateFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ClockSetRateFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
  bool has_state() const { return at<2>().valid(); }
  uint64_t state() const { return at<2>().as_uint64(); }
  bool has_cpu_id() const { return at<3>().valid(); }
  uint64_t cpu_id() const { return at<3>().as_uint64(); }
};

class ClockSetRateFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = ClockSetRateFtraceEvent_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
    kStateFieldNumber = 2,
    kCpuIdFieldNumber = 3,
  };
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_state(uint64_t value) {
    AppendVarInt(2, value);
  }
  void set_cpu_id(uint64_t value) {
    AppendVarInt(3, value);
  }
};

class ClockDisableFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ClockDisableFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ClockDisableFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ClockDisableFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
  bool has_state() const { return at<2>().valid(); }
  uint64_t state() const { return at<2>().as_uint64(); }
  bool has_cpu_id() const { return at<3>().valid(); }
  uint64_t cpu_id() const { return at<3>().as_uint64(); }
};

class ClockDisableFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = ClockDisableFtraceEvent_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
    kStateFieldNumber = 2,
    kCpuIdFieldNumber = 3,
  };
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_state(uint64_t value) {
    AppendVarInt(2, value);
  }
  void set_cpu_id(uint64_t value) {
    AppendVarInt(3, value);
  }
};

class ClockEnableFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ClockEnableFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ClockEnableFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ClockEnableFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
  bool has_state() const { return at<2>().valid(); }
  uint64_t state() const { return at<2>().as_uint64(); }
  bool has_cpu_id() const { return at<3>().valid(); }
  uint64_t cpu_id() const { return at<3>().as_uint64(); }
};

class ClockEnableFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = ClockEnableFtraceEvent_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
    kStateFieldNumber = 2,
    kCpuIdFieldNumber = 3,
  };
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_state(uint64_t value) {
    AppendVarInt(2, value);
  }
  void set_cpu_id(uint64_t value) {
    AppendVarInt(3, value);
  }
};

class CpuIdleFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  CpuIdleFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit CpuIdleFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit CpuIdleFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_state() const { return at<1>().valid(); }
  uint32_t state() const { return at<1>().as_uint32(); }
  bool has_cpu_id() const { return at<2>().valid(); }
  uint32_t cpu_id() const { return at<2>().as_uint32(); }
};

class CpuIdleFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = CpuIdleFtraceEvent_Decoder;
  enum : int32_t {
    kStateFieldNumber = 1,
    kCpuIdFieldNumber = 2,
  };
  void set_state(uint32_t value) {
    AppendVarInt(1, value);
  }
  void set_cpu_id(uint32_t value) {
    AppendVarInt(2, value);
  }
};

class CpuFrequencyLimitsFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  CpuFrequencyLimitsFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit CpuFrequencyLimitsFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit CpuFrequencyLimitsFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_min_freq() const { return at<1>().valid(); }
  uint32_t min_freq() const { return at<1>().as_uint32(); }
  bool has_max_freq() const { return at<2>().valid(); }
  uint32_t max_freq() const { return at<2>().as_uint32(); }
  bool has_cpu_id() const { return at<3>().valid(); }
  uint32_t cpu_id() const { return at<3>().as_uint32(); }
};

class CpuFrequencyLimitsFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = CpuFrequencyLimitsFtraceEvent_Decoder;
  enum : int32_t {
    kMinFreqFieldNumber = 1,
    kMaxFreqFieldNumber = 2,
    kCpuIdFieldNumber = 3,
  };
  void set_min_freq(uint32_t value) {
    AppendVarInt(1, value);
  }
  void set_max_freq(uint32_t value) {
    AppendVarInt(2, value);
  }
  void set_cpu_id(uint32_t value) {
    AppendVarInt(3, value);
  }
};

class CpuFrequencyFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  CpuFrequencyFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit CpuFrequencyFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit CpuFrequencyFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_state() const { return at<1>().valid(); }
  uint32_t state() const { return at<1>().as_uint32(); }
  bool has_cpu_id() const { return at<2>().valid(); }
  uint32_t cpu_id() const { return at<2>().as_uint32(); }
};

class CpuFrequencyFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = CpuFrequencyFtraceEvent_Decoder;
  enum : int32_t {
    kStateFieldNumber = 1,
    kCpuIdFieldNumber = 2,
  };
  void set_state(uint32_t value) {
    AppendVarInt(1, value);
  }
  void set_cpu_id(uint32_t value) {
    AppendVarInt(2, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
