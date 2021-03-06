#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/scattered_heap_buffer.h"
// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif
#include "protos/perfetto/trace/ftrace/ion.gen.h"

namespace perfetto {
namespace protos {
namespace gen {

IonStatFtraceEvent::IonStatFtraceEvent() = default;
IonStatFtraceEvent::~IonStatFtraceEvent() = default;
IonStatFtraceEvent::IonStatFtraceEvent(const IonStatFtraceEvent&) = default;
IonStatFtraceEvent& IonStatFtraceEvent::operator=(const IonStatFtraceEvent&) = default;
IonStatFtraceEvent::IonStatFtraceEvent(IonStatFtraceEvent&&) noexcept = default;
IonStatFtraceEvent& IonStatFtraceEvent::operator=(IonStatFtraceEvent&&) = default;

bool IonStatFtraceEvent::operator==(const IonStatFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && buffer_id_ == other.buffer_id_
   && len_ == other.len_
   && total_allocated_ == other.total_allocated_;
}

bool IonStatFtraceEvent::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* buffer_id */:
        field.get(&buffer_id_);
        break;
      case 2 /* len */:
        field.get(&len_);
        break;
      case 3 /* total_allocated */:
        field.get(&total_allocated_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string IonStatFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> IonStatFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void IonStatFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: buffer_id
  if (_has_field_[1]) {
    msg->AppendVarInt(1, buffer_id_);
  }

  // Field 2: len
  if (_has_field_[2]) {
    msg->AppendVarInt(2, len_);
  }

  // Field 3: total_allocated
  if (_has_field_[3]) {
    msg->AppendVarInt(3, total_allocated_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}

}  // namespace perfetto
}  // namespace protos
}  // namespace gen
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
