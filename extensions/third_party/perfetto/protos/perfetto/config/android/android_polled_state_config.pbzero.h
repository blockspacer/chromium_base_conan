// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_ANDROID_ANDROID_POLLED_STATE_CONFIG_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_CONFIG_ANDROID_ANDROID_POLLED_STATE_CONFIG_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {


class AndroidPolledStateConfig_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/1, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  AndroidPolledStateConfig_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit AndroidPolledStateConfig_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit AndroidPolledStateConfig_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_poll_ms() const { return at<1>().valid(); }
  uint32_t poll_ms() const { return at<1>().as_uint32(); }
};

class AndroidPolledStateConfig : public ::protozero::Message {
 public:
  using Decoder = AndroidPolledStateConfig_Decoder;
  enum : int32_t {
    kPollMsFieldNumber = 1,
  };
  void set_poll_ms(uint32_t value) {
    AppendVarInt(1, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
