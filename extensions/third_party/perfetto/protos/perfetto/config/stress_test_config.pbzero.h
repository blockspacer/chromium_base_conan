// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_STRESS_TEST_CONFIG_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_STRESS_TEST_CONFIG_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {

class StressTestConfig_WriterTiming;
class TraceConfig;

class StressTestConfig_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/11, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  StressTestConfig_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit StressTestConfig_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit StressTestConfig_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_trace_config() const { return at<1>().valid(); }
  ::protozero::ConstBytes trace_config() const { return at<1>().as_bytes(); }
  bool has_shmem_size_kb() const { return at<2>().valid(); }
  uint32_t shmem_size_kb() const { return at<2>().as_uint32(); }
  bool has_shmem_page_size_kb() const { return at<3>().valid(); }
  uint32_t shmem_page_size_kb() const { return at<3>().as_uint32(); }
  bool has_num_processes() const { return at<4>().valid(); }
  uint32_t num_processes() const { return at<4>().as_uint32(); }
  bool has_num_threads() const { return at<5>().valid(); }
  uint32_t num_threads() const { return at<5>().as_uint32(); }
  bool has_max_events() const { return at<6>().valid(); }
  uint32_t max_events() const { return at<6>().as_uint32(); }
  bool has_nesting() const { return at<7>().valid(); }
  uint32_t nesting() const { return at<7>().as_uint32(); }
  bool has_steady_state_timings() const { return at<8>().valid(); }
  ::protozero::ConstBytes steady_state_timings() const { return at<8>().as_bytes(); }
  bool has_burst_period_ms() const { return at<9>().valid(); }
  uint32_t burst_period_ms() const { return at<9>().as_uint32(); }
  bool has_burst_duration_ms() const { return at<10>().valid(); }
  uint32_t burst_duration_ms() const { return at<10>().as_uint32(); }
  bool has_burst_timings() const { return at<11>().valid(); }
  ::protozero::ConstBytes burst_timings() const { return at<11>().as_bytes(); }
};

class StressTestConfig : public ::protozero::Message {
 public:
  using Decoder = StressTestConfig_Decoder;
  enum : int32_t {
    kTraceConfigFieldNumber = 1,
    kShmemSizeKbFieldNumber = 2,
    kShmemPageSizeKbFieldNumber = 3,
    kNumProcessesFieldNumber = 4,
    kNumThreadsFieldNumber = 5,
    kMaxEventsFieldNumber = 6,
    kNestingFieldNumber = 7,
    kSteadyStateTimingsFieldNumber = 8,
    kBurstPeriodMsFieldNumber = 9,
    kBurstDurationMsFieldNumber = 10,
    kBurstTimingsFieldNumber = 11,
  };
  using WriterTiming = ::perfetto::protos::pbzero::StressTestConfig_WriterTiming;
  template <typename T = TraceConfig> T* set_trace_config() {
    return BeginNestedMessage<T>(1);
  }

  void set_shmem_size_kb(uint32_t value) {
    AppendVarInt(2, value);
  }
  void set_shmem_page_size_kb(uint32_t value) {
    AppendVarInt(3, value);
  }
  void set_num_processes(uint32_t value) {
    AppendVarInt(4, value);
  }
  void set_num_threads(uint32_t value) {
    AppendVarInt(5, value);
  }
  void set_max_events(uint32_t value) {
    AppendVarInt(6, value);
  }
  void set_nesting(uint32_t value) {
    AppendVarInt(7, value);
  }
  template <typename T = StressTestConfig_WriterTiming> T* set_steady_state_timings() {
    return BeginNestedMessage<T>(8);
  }

  void set_burst_period_ms(uint32_t value) {
    AppendVarInt(9, value);
  }
  void set_burst_duration_ms(uint32_t value) {
    AppendVarInt(10, value);
  }
  template <typename T = StressTestConfig_WriterTiming> T* set_burst_timings() {
    return BeginNestedMessage<T>(11);
  }

};

class StressTestConfig_WriterTiming_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/5, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  StressTestConfig_WriterTiming_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit StressTestConfig_WriterTiming_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit StressTestConfig_WriterTiming_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_payload_mean() const { return at<1>().valid(); }
  double payload_mean() const { return at<1>().as_double(); }
  bool has_payload_stddev() const { return at<2>().valid(); }
  double payload_stddev() const { return at<2>().as_double(); }
  bool has_rate_mean() const { return at<3>().valid(); }
  double rate_mean() const { return at<3>().as_double(); }
  bool has_rate_stddev() const { return at<4>().valid(); }
  double rate_stddev() const { return at<4>().as_double(); }
  bool has_payload_write_time_ms() const { return at<5>().valid(); }
  uint32_t payload_write_time_ms() const { return at<5>().as_uint32(); }
};

class StressTestConfig_WriterTiming : public ::protozero::Message {
 public:
  using Decoder = StressTestConfig_WriterTiming_Decoder;
  enum : int32_t {
    kPayloadMeanFieldNumber = 1,
    kPayloadStddevFieldNumber = 2,
    kRateMeanFieldNumber = 3,
    kRateStddevFieldNumber = 4,
    kPayloadWriteTimeMsFieldNumber = 5,
  };
  void set_payload_mean(double value) {
    AppendFixed(1, value);
  }
  void set_payload_stddev(double value) {
    AppendFixed(2, value);
  }
  void set_rate_mean(double value) {
    AppendFixed(3, value);
  }
  void set_rate_stddev(double value) {
    AppendFixed(4, value);
  }
  void set_payload_write_time_ms(uint32_t value) {
    AppendVarInt(5, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.