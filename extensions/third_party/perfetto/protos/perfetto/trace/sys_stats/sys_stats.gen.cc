#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/scattered_heap_buffer.h"
// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif
#include "protos/perfetto/trace/sys_stats/sys_stats.gen.h"
#include "protos/perfetto/common/sys_stats_counters.gen.h"

namespace perfetto {
namespace protos {
namespace gen {

SysStats::SysStats() = default;
SysStats::~SysStats() = default;
SysStats::SysStats(const SysStats&) = default;
SysStats& SysStats::operator=(const SysStats&) = default;
SysStats::SysStats(SysStats&&) noexcept = default;
SysStats& SysStats::operator=(SysStats&&) = default;

bool SysStats::operator==(const SysStats& other) const {
  return unknown_fields_ == other.unknown_fields_
   && meminfo_ == other.meminfo_
   && vmstat_ == other.vmstat_
   && cpu_stat_ == other.cpu_stat_
   && num_forks_ == other.num_forks_
   && num_irq_total_ == other.num_irq_total_
   && num_irq_ == other.num_irq_
   && num_softirq_total_ == other.num_softirq_total_
   && num_softirq_ == other.num_softirq_
   && collection_end_timestamp_ == other.collection_end_timestamp_;
}

int SysStats::meminfo_size() const { return static_cast<int>(meminfo_.size()); }
void SysStats::clear_meminfo() { meminfo_.clear(); }
SysStats_MeminfoValue* SysStats::add_meminfo() { meminfo_.emplace_back(); return &meminfo_.back(); }
int SysStats::vmstat_size() const { return static_cast<int>(vmstat_.size()); }
void SysStats::clear_vmstat() { vmstat_.clear(); }
SysStats_VmstatValue* SysStats::add_vmstat() { vmstat_.emplace_back(); return &vmstat_.back(); }
int SysStats::cpu_stat_size() const { return static_cast<int>(cpu_stat_.size()); }
void SysStats::clear_cpu_stat() { cpu_stat_.clear(); }
SysStats_CpuTimes* SysStats::add_cpu_stat() { cpu_stat_.emplace_back(); return &cpu_stat_.back(); }
int SysStats::num_irq_size() const { return static_cast<int>(num_irq_.size()); }
void SysStats::clear_num_irq() { num_irq_.clear(); }
SysStats_InterruptCount* SysStats::add_num_irq() { num_irq_.emplace_back(); return &num_irq_.back(); }
int SysStats::num_softirq_size() const { return static_cast<int>(num_softirq_.size()); }
void SysStats::clear_num_softirq() { num_softirq_.clear(); }
SysStats_InterruptCount* SysStats::add_num_softirq() { num_softirq_.emplace_back(); return &num_softirq_.back(); }
bool SysStats::ParseFromArray(const void* raw, size_t size) {
  meminfo_.clear();
  vmstat_.clear();
  cpu_stat_.clear();
  num_irq_.clear();
  num_softirq_.clear();
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* meminfo */:
        meminfo_.emplace_back();
        meminfo_.back().ParseFromArray(field.data(), field.size());
        break;
      case 2 /* vmstat */:
        vmstat_.emplace_back();
        vmstat_.back().ParseFromArray(field.data(), field.size());
        break;
      case 3 /* cpu_stat */:
        cpu_stat_.emplace_back();
        cpu_stat_.back().ParseFromArray(field.data(), field.size());
        break;
      case 4 /* num_forks */:
        field.get(&num_forks_);
        break;
      case 5 /* num_irq_total */:
        field.get(&num_irq_total_);
        break;
      case 6 /* num_irq */:
        num_irq_.emplace_back();
        num_irq_.back().ParseFromArray(field.data(), field.size());
        break;
      case 7 /* num_softirq_total */:
        field.get(&num_softirq_total_);
        break;
      case 8 /* num_softirq */:
        num_softirq_.emplace_back();
        num_softirq_.back().ParseFromArray(field.data(), field.size());
        break;
      case 9 /* collection_end_timestamp */:
        field.get(&collection_end_timestamp_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string SysStats::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> SysStats::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void SysStats::Serialize(::protozero::Message* msg) const {
  // Field 1: meminfo
  for (auto& it : meminfo_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(1));
  }

  // Field 2: vmstat
  for (auto& it : vmstat_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(2));
  }

  // Field 3: cpu_stat
  for (auto& it : cpu_stat_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(3));
  }

  // Field 4: num_forks
  if (_has_field_[4]) {
    msg->AppendVarInt(4, num_forks_);
  }

  // Field 5: num_irq_total
  if (_has_field_[5]) {
    msg->AppendVarInt(5, num_irq_total_);
  }

  // Field 6: num_irq
  for (auto& it : num_irq_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(6));
  }

  // Field 7: num_softirq_total
  if (_has_field_[7]) {
    msg->AppendVarInt(7, num_softirq_total_);
  }

  // Field 8: num_softirq
  for (auto& it : num_softirq_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(8));
  }

  // Field 9: collection_end_timestamp
  if (_has_field_[9]) {
    msg->AppendVarInt(9, collection_end_timestamp_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


SysStats_InterruptCount::SysStats_InterruptCount() = default;
SysStats_InterruptCount::~SysStats_InterruptCount() = default;
SysStats_InterruptCount::SysStats_InterruptCount(const SysStats_InterruptCount&) = default;
SysStats_InterruptCount& SysStats_InterruptCount::operator=(const SysStats_InterruptCount&) = default;
SysStats_InterruptCount::SysStats_InterruptCount(SysStats_InterruptCount&&) noexcept = default;
SysStats_InterruptCount& SysStats_InterruptCount::operator=(SysStats_InterruptCount&&) = default;

bool SysStats_InterruptCount::operator==(const SysStats_InterruptCount& other) const {
  return unknown_fields_ == other.unknown_fields_
   && irq_ == other.irq_
   && count_ == other.count_;
}

bool SysStats_InterruptCount::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* irq */:
        field.get(&irq_);
        break;
      case 2 /* count */:
        field.get(&count_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string SysStats_InterruptCount::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> SysStats_InterruptCount::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void SysStats_InterruptCount::Serialize(::protozero::Message* msg) const {
  // Field 1: irq
  if (_has_field_[1]) {
    msg->AppendVarInt(1, irq_);
  }

  // Field 2: count
  if (_has_field_[2]) {
    msg->AppendVarInt(2, count_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


SysStats_CpuTimes::SysStats_CpuTimes() = default;
SysStats_CpuTimes::~SysStats_CpuTimes() = default;
SysStats_CpuTimes::SysStats_CpuTimes(const SysStats_CpuTimes&) = default;
SysStats_CpuTimes& SysStats_CpuTimes::operator=(const SysStats_CpuTimes&) = default;
SysStats_CpuTimes::SysStats_CpuTimes(SysStats_CpuTimes&&) noexcept = default;
SysStats_CpuTimes& SysStats_CpuTimes::operator=(SysStats_CpuTimes&&) = default;

bool SysStats_CpuTimes::operator==(const SysStats_CpuTimes& other) const {
  return unknown_fields_ == other.unknown_fields_
   && cpu_id_ == other.cpu_id_
   && user_ns_ == other.user_ns_
   && user_ice_ns_ == other.user_ice_ns_
   && system_mode_ns_ == other.system_mode_ns_
   && idle_ns_ == other.idle_ns_
   && io_wait_ns_ == other.io_wait_ns_
   && irq_ns_ == other.irq_ns_
   && softirq_ns_ == other.softirq_ns_;
}

bool SysStats_CpuTimes::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* cpu_id */:
        field.get(&cpu_id_);
        break;
      case 2 /* user_ns */:
        field.get(&user_ns_);
        break;
      case 3 /* user_ice_ns */:
        field.get(&user_ice_ns_);
        break;
      case 4 /* system_mode_ns */:
        field.get(&system_mode_ns_);
        break;
      case 5 /* idle_ns */:
        field.get(&idle_ns_);
        break;
      case 6 /* io_wait_ns */:
        field.get(&io_wait_ns_);
        break;
      case 7 /* irq_ns */:
        field.get(&irq_ns_);
        break;
      case 8 /* softirq_ns */:
        field.get(&softirq_ns_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string SysStats_CpuTimes::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> SysStats_CpuTimes::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void SysStats_CpuTimes::Serialize(::protozero::Message* msg) const {
  // Field 1: cpu_id
  if (_has_field_[1]) {
    msg->AppendVarInt(1, cpu_id_);
  }

  // Field 2: user_ns
  if (_has_field_[2]) {
    msg->AppendVarInt(2, user_ns_);
  }

  // Field 3: user_ice_ns
  if (_has_field_[3]) {
    msg->AppendVarInt(3, user_ice_ns_);
  }

  // Field 4: system_mode_ns
  if (_has_field_[4]) {
    msg->AppendVarInt(4, system_mode_ns_);
  }

  // Field 5: idle_ns
  if (_has_field_[5]) {
    msg->AppendVarInt(5, idle_ns_);
  }

  // Field 6: io_wait_ns
  if (_has_field_[6]) {
    msg->AppendVarInt(6, io_wait_ns_);
  }

  // Field 7: irq_ns
  if (_has_field_[7]) {
    msg->AppendVarInt(7, irq_ns_);
  }

  // Field 8: softirq_ns
  if (_has_field_[8]) {
    msg->AppendVarInt(8, softirq_ns_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


SysStats_VmstatValue::SysStats_VmstatValue() = default;
SysStats_VmstatValue::~SysStats_VmstatValue() = default;
SysStats_VmstatValue::SysStats_VmstatValue(const SysStats_VmstatValue&) = default;
SysStats_VmstatValue& SysStats_VmstatValue::operator=(const SysStats_VmstatValue&) = default;
SysStats_VmstatValue::SysStats_VmstatValue(SysStats_VmstatValue&&) noexcept = default;
SysStats_VmstatValue& SysStats_VmstatValue::operator=(SysStats_VmstatValue&&) = default;

bool SysStats_VmstatValue::operator==(const SysStats_VmstatValue& other) const {
  return unknown_fields_ == other.unknown_fields_
   && key_ == other.key_
   && value_ == other.value_;
}

bool SysStats_VmstatValue::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* key */:
        field.get(&key_);
        break;
      case 2 /* value */:
        field.get(&value_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string SysStats_VmstatValue::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> SysStats_VmstatValue::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void SysStats_VmstatValue::Serialize(::protozero::Message* msg) const {
  // Field 1: key
  if (_has_field_[1]) {
    msg->AppendVarInt(1, key_);
  }

  // Field 2: value
  if (_has_field_[2]) {
    msg->AppendVarInt(2, value_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


SysStats_MeminfoValue::SysStats_MeminfoValue() = default;
SysStats_MeminfoValue::~SysStats_MeminfoValue() = default;
SysStats_MeminfoValue::SysStats_MeminfoValue(const SysStats_MeminfoValue&) = default;
SysStats_MeminfoValue& SysStats_MeminfoValue::operator=(const SysStats_MeminfoValue&) = default;
SysStats_MeminfoValue::SysStats_MeminfoValue(SysStats_MeminfoValue&&) noexcept = default;
SysStats_MeminfoValue& SysStats_MeminfoValue::operator=(SysStats_MeminfoValue&&) = default;

bool SysStats_MeminfoValue::operator==(const SysStats_MeminfoValue& other) const {
  return unknown_fields_ == other.unknown_fields_
   && key_ == other.key_
   && value_ == other.value_;
}

bool SysStats_MeminfoValue::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* key */:
        field.get(&key_);
        break;
      case 2 /* value */:
        field.get(&value_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string SysStats_MeminfoValue::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> SysStats_MeminfoValue::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void SysStats_MeminfoValue::Serialize(::protozero::Message* msg) const {
  // Field 1: key
  if (_has_field_[1]) {
    msg->AppendVarInt(1, key_);
  }

  // Field 2: value
  if (_has_field_[2]) {
    msg->AppendVarInt(2, value_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}

}  // namespace perfetto
}  // namespace protos
}  // namespace gen
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif