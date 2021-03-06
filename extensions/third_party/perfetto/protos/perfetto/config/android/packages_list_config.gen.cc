#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/scattered_heap_buffer.h"
// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif
#include "protos/perfetto/config/android/packages_list_config.gen.h"

namespace perfetto {
namespace protos {
namespace gen {

PackagesListConfig::PackagesListConfig() = default;
PackagesListConfig::~PackagesListConfig() = default;
PackagesListConfig::PackagesListConfig(const PackagesListConfig&) = default;
PackagesListConfig& PackagesListConfig::operator=(const PackagesListConfig&) = default;
PackagesListConfig::PackagesListConfig(PackagesListConfig&&) noexcept = default;
PackagesListConfig& PackagesListConfig::operator=(PackagesListConfig&&) = default;

bool PackagesListConfig::operator==(const PackagesListConfig& other) const {
  return unknown_fields_ == other.unknown_fields_
   && package_name_filter_ == other.package_name_filter_;
}

bool PackagesListConfig::ParseFromArray(const void* raw, size_t size) {
  package_name_filter_.clear();
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* package_name_filter */:
        package_name_filter_.emplace_back();
        field.get(&package_name_filter_.back());
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string PackagesListConfig::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> PackagesListConfig::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void PackagesListConfig::Serialize(::protozero::Message* msg) const {
  // Field 1: package_name_filter
  for (auto& it : package_name_filter_) {
    msg->AppendString(1, it);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}

}  // namespace perfetto
}  // namespace protos
}  // namespace gen
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
