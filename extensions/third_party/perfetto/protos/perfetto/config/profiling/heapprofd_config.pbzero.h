// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_PROFILING_HEAPPROFD_CONFIG_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_PROFILING_HEAPPROFD_CONFIG_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {

class HeapprofdConfig_ContinuousDumpConfig;

class HeapprofdConfig_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/25, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  HeapprofdConfig_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit HeapprofdConfig_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit HeapprofdConfig_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_sampling_interval_bytes() const { return at<1>().valid(); }
  uint64_t sampling_interval_bytes() const { return at<1>().as_uint64(); }
  bool has_adaptive_sampling_shmem_threshold() const { return at<24>().valid(); }
  uint64_t adaptive_sampling_shmem_threshold() const { return at<24>().as_uint64(); }
  bool has_adaptive_sampling_max_sampling_interval_bytes() const { return at<25>().valid(); }
  uint64_t adaptive_sampling_max_sampling_interval_bytes() const { return at<25>().as_uint64(); }
  bool has_process_cmdline() const { return at<2>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstChars> process_cmdline() const { return GetRepeated<::protozero::ConstChars>(2); }
  bool has_pid() const { return at<4>().valid(); }
  ::protozero::RepeatedFieldIterator<uint64_t> pid() const { return GetRepeated<uint64_t>(4); }
  bool has_heaps() const { return at<20>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstChars> heaps() const { return GetRepeated<::protozero::ConstChars>(20); }
  bool has_stream_allocations() const { return at<23>().valid(); }
  bool stream_allocations() const { return at<23>().as_bool(); }
  bool has_heap_sampling_intervals() const { return at<22>().valid(); }
  ::protozero::RepeatedFieldIterator<uint64_t> heap_sampling_intervals() const { return GetRepeated<uint64_t>(22); }
  bool has_all_heaps() const { return at<21>().valid(); }
  bool all_heaps() const { return at<21>().as_bool(); }
  bool has_all() const { return at<5>().valid(); }
  bool all() const { return at<5>().as_bool(); }
  bool has_min_anonymous_memory_kb() const { return at<15>().valid(); }
  uint32_t min_anonymous_memory_kb() const { return at<15>().as_uint32(); }
  bool has_max_heapprofd_memory_kb() const { return at<16>().valid(); }
  uint32_t max_heapprofd_memory_kb() const { return at<16>().as_uint32(); }
  bool has_max_heapprofd_cpu_secs() const { return at<17>().valid(); }
  uint64_t max_heapprofd_cpu_secs() const { return at<17>().as_uint64(); }
  bool has_skip_symbol_prefix() const { return at<7>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstChars> skip_symbol_prefix() const { return GetRepeated<::protozero::ConstChars>(7); }
  bool has_continuous_dump_config() const { return at<6>().valid(); }
  ::protozero::ConstBytes continuous_dump_config() const { return at<6>().as_bytes(); }
  bool has_shmem_size_bytes() const { return at<8>().valid(); }
  uint64_t shmem_size_bytes() const { return at<8>().as_uint64(); }
  bool has_block_client() const { return at<9>().valid(); }
  bool block_client() const { return at<9>().as_bool(); }
  bool has_block_client_timeout_us() const { return at<14>().valid(); }
  uint32_t block_client_timeout_us() const { return at<14>().as_uint32(); }
  bool has_no_startup() const { return at<10>().valid(); }
  bool no_startup() const { return at<10>().as_bool(); }
  bool has_no_running() const { return at<11>().valid(); }
  bool no_running() const { return at<11>().as_bool(); }
  bool has_dump_at_max() const { return at<13>().valid(); }
  bool dump_at_max() const { return at<13>().as_bool(); }
  bool has_disable_fork_teardown() const { return at<18>().valid(); }
  bool disable_fork_teardown() const { return at<18>().as_bool(); }
  bool has_disable_vfork_detection() const { return at<19>().valid(); }
  bool disable_vfork_detection() const { return at<19>().as_bool(); }
};

class HeapprofdConfig : public ::protozero::Message {
 public:
  using Decoder = HeapprofdConfig_Decoder;
  enum : int32_t {
    kSamplingIntervalBytesFieldNumber = 1,
    kAdaptiveSamplingShmemThresholdFieldNumber = 24,
    kAdaptiveSamplingMaxSamplingIntervalBytesFieldNumber = 25,
    kProcessCmdlineFieldNumber = 2,
    kPidFieldNumber = 4,
    kHeapsFieldNumber = 20,
    kStreamAllocationsFieldNumber = 23,
    kHeapSamplingIntervalsFieldNumber = 22,
    kAllHeapsFieldNumber = 21,
    kAllFieldNumber = 5,
    kMinAnonymousMemoryKbFieldNumber = 15,
    kMaxHeapprofdMemoryKbFieldNumber = 16,
    kMaxHeapprofdCpuSecsFieldNumber = 17,
    kSkipSymbolPrefixFieldNumber = 7,
    kContinuousDumpConfigFieldNumber = 6,
    kShmemSizeBytesFieldNumber = 8,
    kBlockClientFieldNumber = 9,
    kBlockClientTimeoutUsFieldNumber = 14,
    kNoStartupFieldNumber = 10,
    kNoRunningFieldNumber = 11,
    kDumpAtMaxFieldNumber = 13,
    kDisableForkTeardownFieldNumber = 18,
    kDisableVforkDetectionFieldNumber = 19,
  };
  using ContinuousDumpConfig = ::perfetto::protos::pbzero::HeapprofdConfig_ContinuousDumpConfig;
  void set_sampling_interval_bytes(uint64_t value) {
    AppendVarInt(1, value);
  }
  void set_adaptive_sampling_shmem_threshold(uint64_t value) {
    AppendVarInt(24, value);
  }
  void set_adaptive_sampling_max_sampling_interval_bytes(uint64_t value) {
    AppendVarInt(25, value);
  }
  void add_process_cmdline(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void add_process_cmdline(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
  void add_pid(uint64_t value) {
    AppendVarInt(4, value);
  }
  void add_heaps(const std::string& value) {
    AppendBytes(20, value.data(), value.size());
  }
  void add_heaps(const char* data, size_t size) {
    AppendBytes(20, data, size);
  }
  void set_stream_allocations(bool value) {
    AppendTinyVarInt(23, value);
  }
  void add_heap_sampling_intervals(uint64_t value) {
    AppendVarInt(22, value);
  }
  void set_all_heaps(bool value) {
    AppendTinyVarInt(21, value);
  }
  void set_all(bool value) {
    AppendTinyVarInt(5, value);
  }
  void set_min_anonymous_memory_kb(uint32_t value) {
    AppendVarInt(15, value);
  }
  void set_max_heapprofd_memory_kb(uint32_t value) {
    AppendVarInt(16, value);
  }
  void set_max_heapprofd_cpu_secs(uint64_t value) {
    AppendVarInt(17, value);
  }
  void add_skip_symbol_prefix(const std::string& value) {
    AppendBytes(7, value.data(), value.size());
  }
  void add_skip_symbol_prefix(const char* data, size_t size) {
    AppendBytes(7, data, size);
  }
  template <typename T = HeapprofdConfig_ContinuousDumpConfig> T* set_continuous_dump_config() {
    return BeginNestedMessage<T>(6);
  }

  void set_shmem_size_bytes(uint64_t value) {
    AppendVarInt(8, value);
  }
  void set_block_client(bool value) {
    AppendTinyVarInt(9, value);
  }
  void set_block_client_timeout_us(uint32_t value) {
    AppendVarInt(14, value);
  }
  void set_no_startup(bool value) {
    AppendTinyVarInt(10, value);
  }
  void set_no_running(bool value) {
    AppendTinyVarInt(11, value);
  }
  void set_dump_at_max(bool value) {
    AppendTinyVarInt(13, value);
  }
  void set_disable_fork_teardown(bool value) {
    AppendTinyVarInt(18, value);
  }
  void set_disable_vfork_detection(bool value) {
    AppendTinyVarInt(19, value);
  }
};

class HeapprofdConfig_ContinuousDumpConfig_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/6, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  HeapprofdConfig_ContinuousDumpConfig_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit HeapprofdConfig_ContinuousDumpConfig_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit HeapprofdConfig_ContinuousDumpConfig_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_dump_phase_ms() const { return at<5>().valid(); }
  uint32_t dump_phase_ms() const { return at<5>().as_uint32(); }
  bool has_dump_interval_ms() const { return at<6>().valid(); }
  uint32_t dump_interval_ms() const { return at<6>().as_uint32(); }
};

class HeapprofdConfig_ContinuousDumpConfig : public ::protozero::Message {
 public:
  using Decoder = HeapprofdConfig_ContinuousDumpConfig_Decoder;
  enum : int32_t {
    kDumpPhaseMsFieldNumber = 5,
    kDumpIntervalMsFieldNumber = 6,
  };
  void set_dump_phase_ms(uint32_t value) {
    AppendVarInt(5, value);
  }
  void set_dump_interval_ms(uint32_t value) {
    AppendVarInt(6, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
