#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/scattered_heap_buffer.h"
// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif
#include "protos/perfetto/trace/filesystem/inode_file_map.gen.h"

namespace perfetto {
namespace protos {
namespace gen {

InodeFileMap::InodeFileMap() = default;
InodeFileMap::~InodeFileMap() = default;
InodeFileMap::InodeFileMap(const InodeFileMap&) = default;
InodeFileMap& InodeFileMap::operator=(const InodeFileMap&) = default;
InodeFileMap::InodeFileMap(InodeFileMap&&) noexcept = default;
InodeFileMap& InodeFileMap::operator=(InodeFileMap&&) = default;

bool InodeFileMap::operator==(const InodeFileMap& other) const {
  return unknown_fields_ == other.unknown_fields_
   && block_device_id_ == other.block_device_id_
   && mount_points_ == other.mount_points_
   && entries_ == other.entries_;
}

int InodeFileMap::entries_size() const { return static_cast<int>(entries_.size()); }
void InodeFileMap::clear_entries() { entries_.clear(); }
InodeFileMap_Entry* InodeFileMap::add_entries() { entries_.emplace_back(); return &entries_.back(); }
bool InodeFileMap::ParseFromArray(const void* raw, size_t size) {
  mount_points_.clear();
  entries_.clear();
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* block_device_id */:
        field.get(&block_device_id_);
        break;
      case 2 /* mount_points */:
        mount_points_.emplace_back();
        field.get(&mount_points_.back());
        break;
      case 3 /* entries */:
        entries_.emplace_back();
        entries_.back().ParseFromArray(field.data(), field.size());
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string InodeFileMap::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> InodeFileMap::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void InodeFileMap::Serialize(::protozero::Message* msg) const {
  // Field 1: block_device_id
  if (_has_field_[1]) {
    msg->AppendVarInt(1, block_device_id_);
  }

  // Field 2: mount_points
  for (auto& it : mount_points_) {
    msg->AppendString(2, it);
  }

  // Field 3: entries
  for (auto& it : entries_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(3));
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


InodeFileMap_Entry::InodeFileMap_Entry() = default;
InodeFileMap_Entry::~InodeFileMap_Entry() = default;
InodeFileMap_Entry::InodeFileMap_Entry(const InodeFileMap_Entry&) = default;
InodeFileMap_Entry& InodeFileMap_Entry::operator=(const InodeFileMap_Entry&) = default;
InodeFileMap_Entry::InodeFileMap_Entry(InodeFileMap_Entry&&) noexcept = default;
InodeFileMap_Entry& InodeFileMap_Entry::operator=(InodeFileMap_Entry&&) = default;

bool InodeFileMap_Entry::operator==(const InodeFileMap_Entry& other) const {
  return unknown_fields_ == other.unknown_fields_
   && inode_number_ == other.inode_number_
   && paths_ == other.paths_
   && type_ == other.type_;
}

bool InodeFileMap_Entry::ParseFromArray(const void* raw, size_t size) {
  paths_.clear();
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* inode_number */:
        field.get(&inode_number_);
        break;
      case 2 /* paths */:
        paths_.emplace_back();
        field.get(&paths_.back());
        break;
      case 3 /* type */:
        field.get(&type_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string InodeFileMap_Entry::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> InodeFileMap_Entry::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void InodeFileMap_Entry::Serialize(::protozero::Message* msg) const {
  // Field 1: inode_number
  if (_has_field_[1]) {
    msg->AppendVarInt(1, inode_number_);
  }

  // Field 2: paths
  for (auto& it : paths_) {
    msg->AppendString(2, it);
  }

  // Field 3: type
  if (_has_field_[3]) {
    msg->AppendVarInt(3, type_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}

}  // namespace perfetto
}  // namespace protos
}  // namespace gen
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
