#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/scattered_heap_buffer.h"
// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif
#include "protos/perfetto/trace/extension_descriptor.gen.h"
#include "protos/perfetto/common/descriptor.gen.h"

namespace perfetto {
namespace protos {
namespace gen {

ExtensionDescriptor::ExtensionDescriptor() = default;
ExtensionDescriptor::~ExtensionDescriptor() = default;
ExtensionDescriptor::ExtensionDescriptor(const ExtensionDescriptor&) = default;
ExtensionDescriptor& ExtensionDescriptor::operator=(const ExtensionDescriptor&) = default;
ExtensionDescriptor::ExtensionDescriptor(ExtensionDescriptor&&) noexcept = default;
ExtensionDescriptor& ExtensionDescriptor::operator=(ExtensionDescriptor&&) = default;

bool ExtensionDescriptor::operator==(const ExtensionDescriptor& other) const {
  return unknown_fields_ == other.unknown_fields_
   && extension_set_ == other.extension_set_;
}

bool ExtensionDescriptor::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* extension_set */:
        (*extension_set_).ParseFromArray(field.data(), field.size());
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string ExtensionDescriptor::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> ExtensionDescriptor::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void ExtensionDescriptor::Serialize(::protozero::Message* msg) const {
  // Field 1: extension_set
  if (_has_field_[1]) {
    (*extension_set_).Serialize(msg->BeginNestedMessage<::protozero::Message>(1));
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}

}  // namespace perfetto
}  // namespace protos
}  // namespace gen
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
