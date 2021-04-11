#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/scattered_heap_buffer.h"
// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif
#include "protos/perfetto/common/data_source_descriptor.gen.h"

namespace perfetto {
namespace protos {
namespace gen {

DataSourceDescriptor::DataSourceDescriptor() = default;
DataSourceDescriptor::~DataSourceDescriptor() = default;
DataSourceDescriptor::DataSourceDescriptor(const DataSourceDescriptor&) = default;
DataSourceDescriptor& DataSourceDescriptor::operator=(const DataSourceDescriptor&) = default;
DataSourceDescriptor::DataSourceDescriptor(DataSourceDescriptor&&) noexcept = default;
DataSourceDescriptor& DataSourceDescriptor::operator=(DataSourceDescriptor&&) = default;

bool DataSourceDescriptor::operator==(const DataSourceDescriptor& other) const {
  return unknown_fields_ == other.unknown_fields_
   && name_ == other.name_
   && will_notify_on_stop_ == other.will_notify_on_stop_
   && will_notify_on_start_ == other.will_notify_on_start_
   && handles_incremental_state_clear_ == other.handles_incremental_state_clear_
   && gpu_counter_descriptor_ == other.gpu_counter_descriptor_
   && track_event_descriptor_ == other.track_event_descriptor_;
}

bool DataSourceDescriptor::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* name */:
        field.get(&name_);
        break;
      case 2 /* will_notify_on_stop */:
        field.get(&will_notify_on_stop_);
        break;
      case 3 /* will_notify_on_start */:
        field.get(&will_notify_on_start_);
        break;
      case 4 /* handles_incremental_state_clear */:
        field.get(&handles_incremental_state_clear_);
        break;
      case 5 /* gpu_counter_descriptor */:
        gpu_counter_descriptor_ = field.as_std_string();
        break;
      case 6 /* track_event_descriptor */:
        track_event_descriptor_ = field.as_std_string();
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string DataSourceDescriptor::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> DataSourceDescriptor::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void DataSourceDescriptor::Serialize(::protozero::Message* msg) const {
  // Field 1: name
  if (_has_field_[1]) {
    msg->AppendString(1, name_);
  }

  // Field 2: will_notify_on_stop
  if (_has_field_[2]) {
    msg->AppendTinyVarInt(2, will_notify_on_stop_);
  }

  // Field 3: will_notify_on_start
  if (_has_field_[3]) {
    msg->AppendTinyVarInt(3, will_notify_on_start_);
  }

  // Field 4: handles_incremental_state_clear
  if (_has_field_[4]) {
    msg->AppendTinyVarInt(4, handles_incremental_state_clear_);
  }

  // Field 5: gpu_counter_descriptor
  if (_has_field_[5]) {
    msg->AppendString(5, gpu_counter_descriptor_);
  }

  // Field 6: track_event_descriptor
  if (_has_field_[6]) {
    msg->AppendString(6, track_event_descriptor_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}

}  // namespace perfetto
}  // namespace protos
}  // namespace gen
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif