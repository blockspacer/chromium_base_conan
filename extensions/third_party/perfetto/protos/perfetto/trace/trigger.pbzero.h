// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRIGGER_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRIGGER_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {


class Trigger_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  Trigger_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit Trigger_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit Trigger_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_trigger_name() const { return at<1>().valid(); }
  ::protozero::ConstChars trigger_name() const { return at<1>().as_string(); }
  bool has_producer_name() const { return at<2>().valid(); }
  ::protozero::ConstChars producer_name() const { return at<2>().as_string(); }
  bool has_trusted_producer_uid() const { return at<3>().valid(); }
  int32_t trusted_producer_uid() const { return at<3>().as_int32(); }
};

class Trigger : public ::protozero::Message {
 public:
  using Decoder = Trigger_Decoder;
  enum : int32_t {
    kTriggerNameFieldNumber = 1,
    kProducerNameFieldNumber = 2,
    kTrustedProducerUidFieldNumber = 3,
  };
  void set_trigger_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_trigger_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_producer_name(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_producer_name(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
  void set_trusted_producer_uid(int32_t value) {
    AppendVarInt(3, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
