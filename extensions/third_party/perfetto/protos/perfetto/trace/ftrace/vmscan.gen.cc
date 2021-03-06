#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/scattered_heap_buffer.h"
// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif
#include "protos/perfetto/trace/ftrace/vmscan.gen.h"

namespace perfetto {
namespace protos {
namespace gen {

MmVmscanKswapdSleepFtraceEvent::MmVmscanKswapdSleepFtraceEvent() = default;
MmVmscanKswapdSleepFtraceEvent::~MmVmscanKswapdSleepFtraceEvent() = default;
MmVmscanKswapdSleepFtraceEvent::MmVmscanKswapdSleepFtraceEvent(const MmVmscanKswapdSleepFtraceEvent&) = default;
MmVmscanKswapdSleepFtraceEvent& MmVmscanKswapdSleepFtraceEvent::operator=(const MmVmscanKswapdSleepFtraceEvent&) = default;
MmVmscanKswapdSleepFtraceEvent::MmVmscanKswapdSleepFtraceEvent(MmVmscanKswapdSleepFtraceEvent&&) noexcept = default;
MmVmscanKswapdSleepFtraceEvent& MmVmscanKswapdSleepFtraceEvent::operator=(MmVmscanKswapdSleepFtraceEvent&&) = default;

bool MmVmscanKswapdSleepFtraceEvent::operator==(const MmVmscanKswapdSleepFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && nid_ == other.nid_;
}

bool MmVmscanKswapdSleepFtraceEvent::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* nid */:
        field.get(&nid_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string MmVmscanKswapdSleepFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> MmVmscanKswapdSleepFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void MmVmscanKswapdSleepFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: nid
  if (_has_field_[1]) {
    msg->AppendVarInt(1, nid_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


MmVmscanKswapdWakeFtraceEvent::MmVmscanKswapdWakeFtraceEvent() = default;
MmVmscanKswapdWakeFtraceEvent::~MmVmscanKswapdWakeFtraceEvent() = default;
MmVmscanKswapdWakeFtraceEvent::MmVmscanKswapdWakeFtraceEvent(const MmVmscanKswapdWakeFtraceEvent&) = default;
MmVmscanKswapdWakeFtraceEvent& MmVmscanKswapdWakeFtraceEvent::operator=(const MmVmscanKswapdWakeFtraceEvent&) = default;
MmVmscanKswapdWakeFtraceEvent::MmVmscanKswapdWakeFtraceEvent(MmVmscanKswapdWakeFtraceEvent&&) noexcept = default;
MmVmscanKswapdWakeFtraceEvent& MmVmscanKswapdWakeFtraceEvent::operator=(MmVmscanKswapdWakeFtraceEvent&&) = default;

bool MmVmscanKswapdWakeFtraceEvent::operator==(const MmVmscanKswapdWakeFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && nid_ == other.nid_
   && order_ == other.order_;
}

bool MmVmscanKswapdWakeFtraceEvent::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* nid */:
        field.get(&nid_);
        break;
      case 2 /* order */:
        field.get(&order_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string MmVmscanKswapdWakeFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> MmVmscanKswapdWakeFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void MmVmscanKswapdWakeFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: nid
  if (_has_field_[1]) {
    msg->AppendVarInt(1, nid_);
  }

  // Field 2: order
  if (_has_field_[2]) {
    msg->AppendVarInt(2, order_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


MmVmscanDirectReclaimEndFtraceEvent::MmVmscanDirectReclaimEndFtraceEvent() = default;
MmVmscanDirectReclaimEndFtraceEvent::~MmVmscanDirectReclaimEndFtraceEvent() = default;
MmVmscanDirectReclaimEndFtraceEvent::MmVmscanDirectReclaimEndFtraceEvent(const MmVmscanDirectReclaimEndFtraceEvent&) = default;
MmVmscanDirectReclaimEndFtraceEvent& MmVmscanDirectReclaimEndFtraceEvent::operator=(const MmVmscanDirectReclaimEndFtraceEvent&) = default;
MmVmscanDirectReclaimEndFtraceEvent::MmVmscanDirectReclaimEndFtraceEvent(MmVmscanDirectReclaimEndFtraceEvent&&) noexcept = default;
MmVmscanDirectReclaimEndFtraceEvent& MmVmscanDirectReclaimEndFtraceEvent::operator=(MmVmscanDirectReclaimEndFtraceEvent&&) = default;

bool MmVmscanDirectReclaimEndFtraceEvent::operator==(const MmVmscanDirectReclaimEndFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && nr_reclaimed_ == other.nr_reclaimed_;
}

bool MmVmscanDirectReclaimEndFtraceEvent::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* nr_reclaimed */:
        field.get(&nr_reclaimed_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string MmVmscanDirectReclaimEndFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> MmVmscanDirectReclaimEndFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void MmVmscanDirectReclaimEndFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: nr_reclaimed
  if (_has_field_[1]) {
    msg->AppendVarInt(1, nr_reclaimed_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


MmVmscanDirectReclaimBeginFtraceEvent::MmVmscanDirectReclaimBeginFtraceEvent() = default;
MmVmscanDirectReclaimBeginFtraceEvent::~MmVmscanDirectReclaimBeginFtraceEvent() = default;
MmVmscanDirectReclaimBeginFtraceEvent::MmVmscanDirectReclaimBeginFtraceEvent(const MmVmscanDirectReclaimBeginFtraceEvent&) = default;
MmVmscanDirectReclaimBeginFtraceEvent& MmVmscanDirectReclaimBeginFtraceEvent::operator=(const MmVmscanDirectReclaimBeginFtraceEvent&) = default;
MmVmscanDirectReclaimBeginFtraceEvent::MmVmscanDirectReclaimBeginFtraceEvent(MmVmscanDirectReclaimBeginFtraceEvent&&) noexcept = default;
MmVmscanDirectReclaimBeginFtraceEvent& MmVmscanDirectReclaimBeginFtraceEvent::operator=(MmVmscanDirectReclaimBeginFtraceEvent&&) = default;

bool MmVmscanDirectReclaimBeginFtraceEvent::operator==(const MmVmscanDirectReclaimBeginFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && order_ == other.order_
   && may_writepage_ == other.may_writepage_
   && gfp_flags_ == other.gfp_flags_;
}

bool MmVmscanDirectReclaimBeginFtraceEvent::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* order */:
        field.get(&order_);
        break;
      case 2 /* may_writepage */:
        field.get(&may_writepage_);
        break;
      case 3 /* gfp_flags */:
        field.get(&gfp_flags_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string MmVmscanDirectReclaimBeginFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> MmVmscanDirectReclaimBeginFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void MmVmscanDirectReclaimBeginFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: order
  if (_has_field_[1]) {
    msg->AppendVarInt(1, order_);
  }

  // Field 2: may_writepage
  if (_has_field_[2]) {
    msg->AppendVarInt(2, may_writepage_);
  }

  // Field 3: gfp_flags
  if (_has_field_[3]) {
    msg->AppendVarInt(3, gfp_flags_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}

}  // namespace perfetto
}  // namespace protos
}  // namespace gen
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
