// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_CLOCK_SNAPSHOT_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_CLOCK_SNAPSHOT_PROTO_CPP_H_

#include <stdint.h>
#include <bitset>
#include <vector>
#include <string>
#include <type_traits>

#include "perfetto/protozero/cpp_message_obj.h"
#include "perfetto/protozero/copyable_ptr.h"
#include "perfetto/base/export.h"

namespace perfetto {
namespace protos {
namespace gen {
class ClockSnapshot;
class ClockSnapshot_Clock;
enum BuiltinClock : int;
enum ClockSnapshot_Clock_BuiltinClocks : int;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {
enum ClockSnapshot_Clock_BuiltinClocks : int {
  ClockSnapshot_Clock_BuiltinClocks_UNKNOWN = 0,
  ClockSnapshot_Clock_BuiltinClocks_REALTIME = 1,
  ClockSnapshot_Clock_BuiltinClocks_REALTIME_COARSE = 2,
  ClockSnapshot_Clock_BuiltinClocks_MONOTONIC = 3,
  ClockSnapshot_Clock_BuiltinClocks_MONOTONIC_COARSE = 4,
  ClockSnapshot_Clock_BuiltinClocks_MONOTONIC_RAW = 5,
  ClockSnapshot_Clock_BuiltinClocks_BOOTTIME = 6,
  ClockSnapshot_Clock_BuiltinClocks_BUILTIN_CLOCK_MAX_ID = 63,
};

class PERFETTO_EXPORT ClockSnapshot : public ::protozero::CppMessageObj {
 public:
  using Clock = ClockSnapshot_Clock;
  enum FieldNumbers {
    kClocksFieldNumber = 1,
    kPrimaryTraceClockFieldNumber = 2,
  };

  ClockSnapshot();
  ~ClockSnapshot() override;
  ClockSnapshot(ClockSnapshot&&) noexcept;
  ClockSnapshot& operator=(ClockSnapshot&&);
  ClockSnapshot(const ClockSnapshot&);
  ClockSnapshot& operator=(const ClockSnapshot&);
  bool operator==(const ClockSnapshot&) const;
  bool operator!=(const ClockSnapshot& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  const std::vector<ClockSnapshot_Clock>& clocks() const { return clocks_; }
  std::vector<ClockSnapshot_Clock>* mutable_clocks() { return &clocks_; }
  int clocks_size() const;
  void clear_clocks();
  ClockSnapshot_Clock* add_clocks();

  bool has_primary_trace_clock() const { return _has_field_[2]; }
  BuiltinClock primary_trace_clock() const { return primary_trace_clock_; }
  void set_primary_trace_clock(BuiltinClock value) { primary_trace_clock_ = value; _has_field_.set(2); }

 private:
  std::vector<ClockSnapshot_Clock> clocks_;
  BuiltinClock primary_trace_clock_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<3> _has_field_{};
};


class PERFETTO_EXPORT ClockSnapshot_Clock : public ::protozero::CppMessageObj {
 public:
  using BuiltinClocks = ClockSnapshot_Clock_BuiltinClocks;
  static constexpr auto UNKNOWN = ClockSnapshot_Clock_BuiltinClocks_UNKNOWN;
  static constexpr auto REALTIME = ClockSnapshot_Clock_BuiltinClocks_REALTIME;
  static constexpr auto REALTIME_COARSE = ClockSnapshot_Clock_BuiltinClocks_REALTIME_COARSE;
  static constexpr auto MONOTONIC = ClockSnapshot_Clock_BuiltinClocks_MONOTONIC;
  static constexpr auto MONOTONIC_COARSE = ClockSnapshot_Clock_BuiltinClocks_MONOTONIC_COARSE;
  static constexpr auto MONOTONIC_RAW = ClockSnapshot_Clock_BuiltinClocks_MONOTONIC_RAW;
  static constexpr auto BOOTTIME = ClockSnapshot_Clock_BuiltinClocks_BOOTTIME;
  static constexpr auto BUILTIN_CLOCK_MAX_ID = ClockSnapshot_Clock_BuiltinClocks_BUILTIN_CLOCK_MAX_ID;
  static constexpr auto BuiltinClocks_MIN = ClockSnapshot_Clock_BuiltinClocks_UNKNOWN;
  static constexpr auto BuiltinClocks_MAX = ClockSnapshot_Clock_BuiltinClocks_BUILTIN_CLOCK_MAX_ID;
  enum FieldNumbers {
    kClockIdFieldNumber = 1,
    kTimestampFieldNumber = 2,
    kIsIncrementalFieldNumber = 3,
    kUnitMultiplierNsFieldNumber = 4,
  };

  ClockSnapshot_Clock();
  ~ClockSnapshot_Clock() override;
  ClockSnapshot_Clock(ClockSnapshot_Clock&&) noexcept;
  ClockSnapshot_Clock& operator=(ClockSnapshot_Clock&&);
  ClockSnapshot_Clock(const ClockSnapshot_Clock&);
  ClockSnapshot_Clock& operator=(const ClockSnapshot_Clock&);
  bool operator==(const ClockSnapshot_Clock&) const;
  bool operator!=(const ClockSnapshot_Clock& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_clock_id() const { return _has_field_[1]; }
  uint32_t clock_id() const { return clock_id_; }
  void set_clock_id(uint32_t value) { clock_id_ = value; _has_field_.set(1); }

  bool has_timestamp() const { return _has_field_[2]; }
  uint64_t timestamp() const { return timestamp_; }
  void set_timestamp(uint64_t value) { timestamp_ = value; _has_field_.set(2); }

  bool has_is_incremental() const { return _has_field_[3]; }
  bool is_incremental() const { return is_incremental_; }
  void set_is_incremental(bool value) { is_incremental_ = value; _has_field_.set(3); }

  bool has_unit_multiplier_ns() const { return _has_field_[4]; }
  uint64_t unit_multiplier_ns() const { return unit_multiplier_ns_; }
  void set_unit_multiplier_ns(uint64_t value) { unit_multiplier_ns_ = value; _has_field_.set(4); }

 private:
  uint32_t clock_id_{};
  uint64_t timestamp_{};
  bool is_incremental_{};
  uint64_t unit_multiplier_ns_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<5> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_CLOCK_SNAPSHOT_PROTO_CPP_H_