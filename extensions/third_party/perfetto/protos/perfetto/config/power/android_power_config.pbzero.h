// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_POWER_ANDROID_POWER_CONFIG_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_POWER_ANDROID_POWER_CONFIG_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {

enum AndroidPowerConfig_BatteryCounters : int32_t;

enum AndroidPowerConfig_BatteryCounters : int32_t {
  AndroidPowerConfig_BatteryCounters_BATTERY_COUNTER_UNSPECIFIED = 0,
  AndroidPowerConfig_BatteryCounters_BATTERY_COUNTER_CHARGE = 1,
  AndroidPowerConfig_BatteryCounters_BATTERY_COUNTER_CAPACITY_PERCENT = 2,
  AndroidPowerConfig_BatteryCounters_BATTERY_COUNTER_CURRENT = 3,
  AndroidPowerConfig_BatteryCounters_BATTERY_COUNTER_CURRENT_AVG = 4,
};

const AndroidPowerConfig_BatteryCounters AndroidPowerConfig_BatteryCounters_MIN = AndroidPowerConfig_BatteryCounters_BATTERY_COUNTER_UNSPECIFIED;
const AndroidPowerConfig_BatteryCounters AndroidPowerConfig_BatteryCounters_MAX = AndroidPowerConfig_BatteryCounters_BATTERY_COUNTER_CURRENT_AVG;

class AndroidPowerConfig_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  AndroidPowerConfig_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit AndroidPowerConfig_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit AndroidPowerConfig_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_battery_poll_ms() const { return at<1>().valid(); }
  uint32_t battery_poll_ms() const { return at<1>().as_uint32(); }
  bool has_battery_counters() const { return at<2>().valid(); }
  ::protozero::RepeatedFieldIterator<int32_t> battery_counters() const { return GetRepeated<int32_t>(2); }
  bool has_collect_power_rails() const { return at<3>().valid(); }
  bool collect_power_rails() const { return at<3>().as_bool(); }
};

class AndroidPowerConfig : public ::protozero::Message {
 public:
  using Decoder = AndroidPowerConfig_Decoder;
  enum : int32_t {
    kBatteryPollMsFieldNumber = 1,
    kBatteryCountersFieldNumber = 2,
    kCollectPowerRailsFieldNumber = 3,
  };
  using BatteryCounters = ::perfetto::protos::pbzero::AndroidPowerConfig_BatteryCounters;
  static const BatteryCounters BATTERY_COUNTER_UNSPECIFIED = AndroidPowerConfig_BatteryCounters_BATTERY_COUNTER_UNSPECIFIED;
  static const BatteryCounters BATTERY_COUNTER_CHARGE = AndroidPowerConfig_BatteryCounters_BATTERY_COUNTER_CHARGE;
  static const BatteryCounters BATTERY_COUNTER_CAPACITY_PERCENT = AndroidPowerConfig_BatteryCounters_BATTERY_COUNTER_CAPACITY_PERCENT;
  static const BatteryCounters BATTERY_COUNTER_CURRENT = AndroidPowerConfig_BatteryCounters_BATTERY_COUNTER_CURRENT;
  static const BatteryCounters BATTERY_COUNTER_CURRENT_AVG = AndroidPowerConfig_BatteryCounters_BATTERY_COUNTER_CURRENT_AVG;
  void set_battery_poll_ms(uint32_t value) {
    AppendVarInt(1, value);
  }
  void add_battery_counters(::perfetto::protos::pbzero::AndroidPowerConfig_BatteryCounters value) {
    AppendTinyVarInt(2, value);
  }
  void set_collect_power_rails(bool value) {
    AppendTinyVarInt(3, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
