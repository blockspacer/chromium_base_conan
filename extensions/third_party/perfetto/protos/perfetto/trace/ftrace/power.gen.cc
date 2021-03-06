#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/scattered_heap_buffer.h"
// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif
#include "protos/perfetto/trace/ftrace/power.gen.h"

namespace perfetto {
namespace protos {
namespace gen {

GpuFrequencyFtraceEvent::GpuFrequencyFtraceEvent() = default;
GpuFrequencyFtraceEvent::~GpuFrequencyFtraceEvent() = default;
GpuFrequencyFtraceEvent::GpuFrequencyFtraceEvent(const GpuFrequencyFtraceEvent&) = default;
GpuFrequencyFtraceEvent& GpuFrequencyFtraceEvent::operator=(const GpuFrequencyFtraceEvent&) = default;
GpuFrequencyFtraceEvent::GpuFrequencyFtraceEvent(GpuFrequencyFtraceEvent&&) noexcept = default;
GpuFrequencyFtraceEvent& GpuFrequencyFtraceEvent::operator=(GpuFrequencyFtraceEvent&&) = default;

bool GpuFrequencyFtraceEvent::operator==(const GpuFrequencyFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && gpu_id_ == other.gpu_id_
   && state_ == other.state_;
}

bool GpuFrequencyFtraceEvent::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* gpu_id */:
        field.get(&gpu_id_);
        break;
      case 2 /* state */:
        field.get(&state_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string GpuFrequencyFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> GpuFrequencyFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void GpuFrequencyFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: gpu_id
  if (_has_field_[1]) {
    msg->AppendVarInt(1, gpu_id_);
  }

  // Field 2: state
  if (_has_field_[2]) {
    msg->AppendVarInt(2, state_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


SuspendResumeFtraceEvent::SuspendResumeFtraceEvent() = default;
SuspendResumeFtraceEvent::~SuspendResumeFtraceEvent() = default;
SuspendResumeFtraceEvent::SuspendResumeFtraceEvent(const SuspendResumeFtraceEvent&) = default;
SuspendResumeFtraceEvent& SuspendResumeFtraceEvent::operator=(const SuspendResumeFtraceEvent&) = default;
SuspendResumeFtraceEvent::SuspendResumeFtraceEvent(SuspendResumeFtraceEvent&&) noexcept = default;
SuspendResumeFtraceEvent& SuspendResumeFtraceEvent::operator=(SuspendResumeFtraceEvent&&) = default;

bool SuspendResumeFtraceEvent::operator==(const SuspendResumeFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && action_ == other.action_
   && val_ == other.val_
   && start_ == other.start_;
}

bool SuspendResumeFtraceEvent::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* action */:
        field.get(&action_);
        break;
      case 2 /* val */:
        field.get(&val_);
        break;
      case 3 /* start */:
        field.get(&start_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string SuspendResumeFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> SuspendResumeFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void SuspendResumeFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: action
  if (_has_field_[1]) {
    msg->AppendString(1, action_);
  }

  // Field 2: val
  if (_has_field_[2]) {
    msg->AppendVarInt(2, val_);
  }

  // Field 3: start
  if (_has_field_[3]) {
    msg->AppendVarInt(3, start_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


ClockSetRateFtraceEvent::ClockSetRateFtraceEvent() = default;
ClockSetRateFtraceEvent::~ClockSetRateFtraceEvent() = default;
ClockSetRateFtraceEvent::ClockSetRateFtraceEvent(const ClockSetRateFtraceEvent&) = default;
ClockSetRateFtraceEvent& ClockSetRateFtraceEvent::operator=(const ClockSetRateFtraceEvent&) = default;
ClockSetRateFtraceEvent::ClockSetRateFtraceEvent(ClockSetRateFtraceEvent&&) noexcept = default;
ClockSetRateFtraceEvent& ClockSetRateFtraceEvent::operator=(ClockSetRateFtraceEvent&&) = default;

bool ClockSetRateFtraceEvent::operator==(const ClockSetRateFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && name_ == other.name_
   && state_ == other.state_
   && cpu_id_ == other.cpu_id_;
}

bool ClockSetRateFtraceEvent::ParseFromArray(const void* raw, size_t size) {
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
      case 2 /* state */:
        field.get(&state_);
        break;
      case 3 /* cpu_id */:
        field.get(&cpu_id_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string ClockSetRateFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> ClockSetRateFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void ClockSetRateFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: name
  if (_has_field_[1]) {
    msg->AppendString(1, name_);
  }

  // Field 2: state
  if (_has_field_[2]) {
    msg->AppendVarInt(2, state_);
  }

  // Field 3: cpu_id
  if (_has_field_[3]) {
    msg->AppendVarInt(3, cpu_id_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


ClockDisableFtraceEvent::ClockDisableFtraceEvent() = default;
ClockDisableFtraceEvent::~ClockDisableFtraceEvent() = default;
ClockDisableFtraceEvent::ClockDisableFtraceEvent(const ClockDisableFtraceEvent&) = default;
ClockDisableFtraceEvent& ClockDisableFtraceEvent::operator=(const ClockDisableFtraceEvent&) = default;
ClockDisableFtraceEvent::ClockDisableFtraceEvent(ClockDisableFtraceEvent&&) noexcept = default;
ClockDisableFtraceEvent& ClockDisableFtraceEvent::operator=(ClockDisableFtraceEvent&&) = default;

bool ClockDisableFtraceEvent::operator==(const ClockDisableFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && name_ == other.name_
   && state_ == other.state_
   && cpu_id_ == other.cpu_id_;
}

bool ClockDisableFtraceEvent::ParseFromArray(const void* raw, size_t size) {
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
      case 2 /* state */:
        field.get(&state_);
        break;
      case 3 /* cpu_id */:
        field.get(&cpu_id_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string ClockDisableFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> ClockDisableFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void ClockDisableFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: name
  if (_has_field_[1]) {
    msg->AppendString(1, name_);
  }

  // Field 2: state
  if (_has_field_[2]) {
    msg->AppendVarInt(2, state_);
  }

  // Field 3: cpu_id
  if (_has_field_[3]) {
    msg->AppendVarInt(3, cpu_id_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


ClockEnableFtraceEvent::ClockEnableFtraceEvent() = default;
ClockEnableFtraceEvent::~ClockEnableFtraceEvent() = default;
ClockEnableFtraceEvent::ClockEnableFtraceEvent(const ClockEnableFtraceEvent&) = default;
ClockEnableFtraceEvent& ClockEnableFtraceEvent::operator=(const ClockEnableFtraceEvent&) = default;
ClockEnableFtraceEvent::ClockEnableFtraceEvent(ClockEnableFtraceEvent&&) noexcept = default;
ClockEnableFtraceEvent& ClockEnableFtraceEvent::operator=(ClockEnableFtraceEvent&&) = default;

bool ClockEnableFtraceEvent::operator==(const ClockEnableFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && name_ == other.name_
   && state_ == other.state_
   && cpu_id_ == other.cpu_id_;
}

bool ClockEnableFtraceEvent::ParseFromArray(const void* raw, size_t size) {
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
      case 2 /* state */:
        field.get(&state_);
        break;
      case 3 /* cpu_id */:
        field.get(&cpu_id_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string ClockEnableFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> ClockEnableFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void ClockEnableFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: name
  if (_has_field_[1]) {
    msg->AppendString(1, name_);
  }

  // Field 2: state
  if (_has_field_[2]) {
    msg->AppendVarInt(2, state_);
  }

  // Field 3: cpu_id
  if (_has_field_[3]) {
    msg->AppendVarInt(3, cpu_id_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


CpuIdleFtraceEvent::CpuIdleFtraceEvent() = default;
CpuIdleFtraceEvent::~CpuIdleFtraceEvent() = default;
CpuIdleFtraceEvent::CpuIdleFtraceEvent(const CpuIdleFtraceEvent&) = default;
CpuIdleFtraceEvent& CpuIdleFtraceEvent::operator=(const CpuIdleFtraceEvent&) = default;
CpuIdleFtraceEvent::CpuIdleFtraceEvent(CpuIdleFtraceEvent&&) noexcept = default;
CpuIdleFtraceEvent& CpuIdleFtraceEvent::operator=(CpuIdleFtraceEvent&&) = default;

bool CpuIdleFtraceEvent::operator==(const CpuIdleFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && state_ == other.state_
   && cpu_id_ == other.cpu_id_;
}

bool CpuIdleFtraceEvent::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* state */:
        field.get(&state_);
        break;
      case 2 /* cpu_id */:
        field.get(&cpu_id_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string CpuIdleFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> CpuIdleFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void CpuIdleFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: state
  if (_has_field_[1]) {
    msg->AppendVarInt(1, state_);
  }

  // Field 2: cpu_id
  if (_has_field_[2]) {
    msg->AppendVarInt(2, cpu_id_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


CpuFrequencyLimitsFtraceEvent::CpuFrequencyLimitsFtraceEvent() = default;
CpuFrequencyLimitsFtraceEvent::~CpuFrequencyLimitsFtraceEvent() = default;
CpuFrequencyLimitsFtraceEvent::CpuFrequencyLimitsFtraceEvent(const CpuFrequencyLimitsFtraceEvent&) = default;
CpuFrequencyLimitsFtraceEvent& CpuFrequencyLimitsFtraceEvent::operator=(const CpuFrequencyLimitsFtraceEvent&) = default;
CpuFrequencyLimitsFtraceEvent::CpuFrequencyLimitsFtraceEvent(CpuFrequencyLimitsFtraceEvent&&) noexcept = default;
CpuFrequencyLimitsFtraceEvent& CpuFrequencyLimitsFtraceEvent::operator=(CpuFrequencyLimitsFtraceEvent&&) = default;

bool CpuFrequencyLimitsFtraceEvent::operator==(const CpuFrequencyLimitsFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && min_freq_ == other.min_freq_
   && max_freq_ == other.max_freq_
   && cpu_id_ == other.cpu_id_;
}

bool CpuFrequencyLimitsFtraceEvent::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* min_freq */:
        field.get(&min_freq_);
        break;
      case 2 /* max_freq */:
        field.get(&max_freq_);
        break;
      case 3 /* cpu_id */:
        field.get(&cpu_id_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string CpuFrequencyLimitsFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> CpuFrequencyLimitsFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void CpuFrequencyLimitsFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: min_freq
  if (_has_field_[1]) {
    msg->AppendVarInt(1, min_freq_);
  }

  // Field 2: max_freq
  if (_has_field_[2]) {
    msg->AppendVarInt(2, max_freq_);
  }

  // Field 3: cpu_id
  if (_has_field_[3]) {
    msg->AppendVarInt(3, cpu_id_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


CpuFrequencyFtraceEvent::CpuFrequencyFtraceEvent() = default;
CpuFrequencyFtraceEvent::~CpuFrequencyFtraceEvent() = default;
CpuFrequencyFtraceEvent::CpuFrequencyFtraceEvent(const CpuFrequencyFtraceEvent&) = default;
CpuFrequencyFtraceEvent& CpuFrequencyFtraceEvent::operator=(const CpuFrequencyFtraceEvent&) = default;
CpuFrequencyFtraceEvent::CpuFrequencyFtraceEvent(CpuFrequencyFtraceEvent&&) noexcept = default;
CpuFrequencyFtraceEvent& CpuFrequencyFtraceEvent::operator=(CpuFrequencyFtraceEvent&&) = default;

bool CpuFrequencyFtraceEvent::operator==(const CpuFrequencyFtraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && state_ == other.state_
   && cpu_id_ == other.cpu_id_;
}

bool CpuFrequencyFtraceEvent::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* state */:
        field.get(&state_);
        break;
      case 2 /* cpu_id */:
        field.get(&cpu_id_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string CpuFrequencyFtraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> CpuFrequencyFtraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void CpuFrequencyFtraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: state
  if (_has_field_[1]) {
    msg->AppendVarInt(1, state_);
  }

  // Field 2: cpu_id
  if (_has_field_[2]) {
    msg->AppendVarInt(2, cpu_id_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}

}  // namespace perfetto
}  // namespace protos
}  // namespace gen
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
