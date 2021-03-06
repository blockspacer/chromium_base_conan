// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_POWER_BATTERY_COUNTERS_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_POWER_BATTERY_COUNTERS_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {


class BatteryCounters_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/4, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  BatteryCounters_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit BatteryCounters_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit BatteryCounters_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_charge_counter_uah() const { return at<1>().valid(); }
  int64_t charge_counter_uah() const { return at<1>().as_int64(); }
  bool has_capacity_percent() const { return at<2>().valid(); }
  float capacity_percent() const { return at<2>().as_float(); }
  bool has_current_ua() const { return at<3>().valid(); }
  int64_t current_ua() const { return at<3>().as_int64(); }
  bool has_current_avg_ua() const { return at<4>().valid(); }
  int64_t current_avg_ua() const { return at<4>().as_int64(); }
};

class BatteryCounters : public ::protozero::Message {
 public:
  using Decoder = BatteryCounters_Decoder;
  enum : int32_t {
    kChargeCounterUahFieldNumber = 1,
    kCapacityPercentFieldNumber = 2,
    kCurrentUaFieldNumber = 3,
    kCurrentAvgUaFieldNumber = 4,
  };
  void set_charge_counter_uah(int64_t value) {
    AppendVarInt(1, value);
  }
  void set_capacity_percent(float value) {
    AppendFixed(2, value);
  }
  void set_current_ua(int64_t value) {
    AppendVarInt(3, value);
  }
  void set_current_avg_ua(int64_t value) {
    AppendVarInt(4, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
