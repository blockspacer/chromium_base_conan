#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/scattered_heap_buffer.h"
// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif
#include "protos/perfetto/trace/chrome/chrome_trace_event.gen.h"

namespace perfetto {
namespace protos {
namespace gen {

ChromeEventBundle::ChromeEventBundle() = default;
ChromeEventBundle::~ChromeEventBundle() = default;
ChromeEventBundle::ChromeEventBundle(const ChromeEventBundle&) = default;
ChromeEventBundle& ChromeEventBundle::operator=(const ChromeEventBundle&) = default;
ChromeEventBundle::ChromeEventBundle(ChromeEventBundle&&) noexcept = default;
ChromeEventBundle& ChromeEventBundle::operator=(ChromeEventBundle&&) = default;

bool ChromeEventBundle::operator==(const ChromeEventBundle& other) const {
  return unknown_fields_ == other.unknown_fields_
   && trace_events_ == other.trace_events_
   && metadata_ == other.metadata_
   && legacy_ftrace_output_ == other.legacy_ftrace_output_
   && legacy_json_trace_ == other.legacy_json_trace_
   && string_table_ == other.string_table_;
}

int ChromeEventBundle::trace_events_size() const { return static_cast<int>(trace_events_.size()); }
void ChromeEventBundle::clear_trace_events() { trace_events_.clear(); }
ChromeTraceEvent* ChromeEventBundle::add_trace_events() { trace_events_.emplace_back(); return &trace_events_.back(); }
int ChromeEventBundle::metadata_size() const { return static_cast<int>(metadata_.size()); }
void ChromeEventBundle::clear_metadata() { metadata_.clear(); }
ChromeMetadata* ChromeEventBundle::add_metadata() { metadata_.emplace_back(); return &metadata_.back(); }
int ChromeEventBundle::legacy_json_trace_size() const { return static_cast<int>(legacy_json_trace_.size()); }
void ChromeEventBundle::clear_legacy_json_trace() { legacy_json_trace_.clear(); }
ChromeLegacyJsonTrace* ChromeEventBundle::add_legacy_json_trace() { legacy_json_trace_.emplace_back(); return &legacy_json_trace_.back(); }
int ChromeEventBundle::string_table_size() const { return static_cast<int>(string_table_.size()); }
void ChromeEventBundle::clear_string_table() { string_table_.clear(); }
ChromeStringTableEntry* ChromeEventBundle::add_string_table() { string_table_.emplace_back(); return &string_table_.back(); }
bool ChromeEventBundle::ParseFromArray(const void* raw, size_t size) {
  trace_events_.clear();
  metadata_.clear();
  legacy_ftrace_output_.clear();
  legacy_json_trace_.clear();
  string_table_.clear();
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* trace_events */:
        trace_events_.emplace_back();
        trace_events_.back().ParseFromArray(field.data(), field.size());
        break;
      case 2 /* metadata */:
        metadata_.emplace_back();
        metadata_.back().ParseFromArray(field.data(), field.size());
        break;
      case 4 /* legacy_ftrace_output */:
        legacy_ftrace_output_.emplace_back();
        field.get(&legacy_ftrace_output_.back());
        break;
      case 5 /* legacy_json_trace */:
        legacy_json_trace_.emplace_back();
        legacy_json_trace_.back().ParseFromArray(field.data(), field.size());
        break;
      case 3 /* string_table */:
        string_table_.emplace_back();
        string_table_.back().ParseFromArray(field.data(), field.size());
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string ChromeEventBundle::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> ChromeEventBundle::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void ChromeEventBundle::Serialize(::protozero::Message* msg) const {
  // Field 1: trace_events
  for (auto& it : trace_events_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(1));
  }

  // Field 2: metadata
  for (auto& it : metadata_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(2));
  }

  // Field 4: legacy_ftrace_output
  for (auto& it : legacy_ftrace_output_) {
    msg->AppendString(4, it);
  }

  // Field 5: legacy_json_trace
  for (auto& it : legacy_json_trace_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(5));
  }

  // Field 3: string_table
  for (auto& it : string_table_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(3));
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


ChromeStringTableEntry::ChromeStringTableEntry() = default;
ChromeStringTableEntry::~ChromeStringTableEntry() = default;
ChromeStringTableEntry::ChromeStringTableEntry(const ChromeStringTableEntry&) = default;
ChromeStringTableEntry& ChromeStringTableEntry::operator=(const ChromeStringTableEntry&) = default;
ChromeStringTableEntry::ChromeStringTableEntry(ChromeStringTableEntry&&) noexcept = default;
ChromeStringTableEntry& ChromeStringTableEntry::operator=(ChromeStringTableEntry&&) = default;

bool ChromeStringTableEntry::operator==(const ChromeStringTableEntry& other) const {
  return unknown_fields_ == other.unknown_fields_
   && value_ == other.value_
   && index_ == other.index_;
}

bool ChromeStringTableEntry::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* value */:
        field.get(&value_);
        break;
      case 2 /* index */:
        field.get(&index_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string ChromeStringTableEntry::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> ChromeStringTableEntry::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void ChromeStringTableEntry::Serialize(::protozero::Message* msg) const {
  // Field 1: value
  if (_has_field_[1]) {
    msg->AppendString(1, value_);
  }

  // Field 2: index
  if (_has_field_[2]) {
    msg->AppendVarInt(2, index_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


ChromeLegacyJsonTrace::ChromeLegacyJsonTrace() = default;
ChromeLegacyJsonTrace::~ChromeLegacyJsonTrace() = default;
ChromeLegacyJsonTrace::ChromeLegacyJsonTrace(const ChromeLegacyJsonTrace&) = default;
ChromeLegacyJsonTrace& ChromeLegacyJsonTrace::operator=(const ChromeLegacyJsonTrace&) = default;
ChromeLegacyJsonTrace::ChromeLegacyJsonTrace(ChromeLegacyJsonTrace&&) noexcept = default;
ChromeLegacyJsonTrace& ChromeLegacyJsonTrace::operator=(ChromeLegacyJsonTrace&&) = default;

bool ChromeLegacyJsonTrace::operator==(const ChromeLegacyJsonTrace& other) const {
  return unknown_fields_ == other.unknown_fields_
   && type_ == other.type_
   && data_ == other.data_;
}

bool ChromeLegacyJsonTrace::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* type */:
        field.get(&type_);
        break;
      case 2 /* data */:
        field.get(&data_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string ChromeLegacyJsonTrace::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> ChromeLegacyJsonTrace::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void ChromeLegacyJsonTrace::Serialize(::protozero::Message* msg) const {
  // Field 1: type
  if (_has_field_[1]) {
    msg->AppendVarInt(1, type_);
  }

  // Field 2: data
  if (_has_field_[2]) {
    msg->AppendString(2, data_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


ChromeMetadata::ChromeMetadata() = default;
ChromeMetadata::~ChromeMetadata() = default;
ChromeMetadata::ChromeMetadata(const ChromeMetadata&) = default;
ChromeMetadata& ChromeMetadata::operator=(const ChromeMetadata&) = default;
ChromeMetadata::ChromeMetadata(ChromeMetadata&&) noexcept = default;
ChromeMetadata& ChromeMetadata::operator=(ChromeMetadata&&) = default;

bool ChromeMetadata::operator==(const ChromeMetadata& other) const {
  return unknown_fields_ == other.unknown_fields_
   && name_ == other.name_
   && string_value_ == other.string_value_
   && bool_value_ == other.bool_value_
   && int_value_ == other.int_value_
   && json_value_ == other.json_value_;
}

bool ChromeMetadata::ParseFromArray(const void* raw, size_t size) {
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
      case 2 /* string_value */:
        field.get(&string_value_);
        break;
      case 3 /* bool_value */:
        field.get(&bool_value_);
        break;
      case 4 /* int_value */:
        field.get(&int_value_);
        break;
      case 5 /* json_value */:
        field.get(&json_value_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string ChromeMetadata::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> ChromeMetadata::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void ChromeMetadata::Serialize(::protozero::Message* msg) const {
  // Field 1: name
  if (_has_field_[1]) {
    msg->AppendString(1, name_);
  }

  // Field 2: string_value
  if (_has_field_[2]) {
    msg->AppendString(2, string_value_);
  }

  // Field 3: bool_value
  if (_has_field_[3]) {
    msg->AppendTinyVarInt(3, bool_value_);
  }

  // Field 4: int_value
  if (_has_field_[4]) {
    msg->AppendVarInt(4, int_value_);
  }

  // Field 5: json_value
  if (_has_field_[5]) {
    msg->AppendString(5, json_value_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


ChromeTraceEvent::ChromeTraceEvent() = default;
ChromeTraceEvent::~ChromeTraceEvent() = default;
ChromeTraceEvent::ChromeTraceEvent(const ChromeTraceEvent&) = default;
ChromeTraceEvent& ChromeTraceEvent::operator=(const ChromeTraceEvent&) = default;
ChromeTraceEvent::ChromeTraceEvent(ChromeTraceEvent&&) noexcept = default;
ChromeTraceEvent& ChromeTraceEvent::operator=(ChromeTraceEvent&&) = default;

bool ChromeTraceEvent::operator==(const ChromeTraceEvent& other) const {
  return unknown_fields_ == other.unknown_fields_
   && name_ == other.name_
   && timestamp_ == other.timestamp_
   && phase_ == other.phase_
   && thread_id_ == other.thread_id_
   && duration_ == other.duration_
   && thread_duration_ == other.thread_duration_
   && scope_ == other.scope_
   && id_ == other.id_
   && flags_ == other.flags_
   && category_group_name_ == other.category_group_name_
   && process_id_ == other.process_id_
   && thread_timestamp_ == other.thread_timestamp_
   && bind_id_ == other.bind_id_
   && args_ == other.args_
   && name_index_ == other.name_index_
   && category_group_name_index_ == other.category_group_name_index_;
}

int ChromeTraceEvent::args_size() const { return static_cast<int>(args_.size()); }
void ChromeTraceEvent::clear_args() { args_.clear(); }
ChromeTraceEvent_Arg* ChromeTraceEvent::add_args() { args_.emplace_back(); return &args_.back(); }
bool ChromeTraceEvent::ParseFromArray(const void* raw, size_t size) {
  args_.clear();
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
      case 2 /* timestamp */:
        field.get(&timestamp_);
        break;
      case 3 /* phase */:
        field.get(&phase_);
        break;
      case 4 /* thread_id */:
        field.get(&thread_id_);
        break;
      case 5 /* duration */:
        field.get(&duration_);
        break;
      case 6 /* thread_duration */:
        field.get(&thread_duration_);
        break;
      case 7 /* scope */:
        field.get(&scope_);
        break;
      case 8 /* id */:
        field.get(&id_);
        break;
      case 9 /* flags */:
        field.get(&flags_);
        break;
      case 10 /* category_group_name */:
        field.get(&category_group_name_);
        break;
      case 11 /* process_id */:
        field.get(&process_id_);
        break;
      case 12 /* thread_timestamp */:
        field.get(&thread_timestamp_);
        break;
      case 13 /* bind_id */:
        field.get(&bind_id_);
        break;
      case 14 /* args */:
        args_.emplace_back();
        args_.back().ParseFromArray(field.data(), field.size());
        break;
      case 15 /* name_index */:
        field.get(&name_index_);
        break;
      case 16 /* category_group_name_index */:
        field.get(&category_group_name_index_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string ChromeTraceEvent::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> ChromeTraceEvent::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void ChromeTraceEvent::Serialize(::protozero::Message* msg) const {
  // Field 1: name
  if (_has_field_[1]) {
    msg->AppendString(1, name_);
  }

  // Field 2: timestamp
  if (_has_field_[2]) {
    msg->AppendVarInt(2, timestamp_);
  }

  // Field 3: phase
  if (_has_field_[3]) {
    msg->AppendVarInt(3, phase_);
  }

  // Field 4: thread_id
  if (_has_field_[4]) {
    msg->AppendVarInt(4, thread_id_);
  }

  // Field 5: duration
  if (_has_field_[5]) {
    msg->AppendVarInt(5, duration_);
  }

  // Field 6: thread_duration
  if (_has_field_[6]) {
    msg->AppendVarInt(6, thread_duration_);
  }

  // Field 7: scope
  if (_has_field_[7]) {
    msg->AppendString(7, scope_);
  }

  // Field 8: id
  if (_has_field_[8]) {
    msg->AppendVarInt(8, id_);
  }

  // Field 9: flags
  if (_has_field_[9]) {
    msg->AppendVarInt(9, flags_);
  }

  // Field 10: category_group_name
  if (_has_field_[10]) {
    msg->AppendString(10, category_group_name_);
  }

  // Field 11: process_id
  if (_has_field_[11]) {
    msg->AppendVarInt(11, process_id_);
  }

  // Field 12: thread_timestamp
  if (_has_field_[12]) {
    msg->AppendVarInt(12, thread_timestamp_);
  }

  // Field 13: bind_id
  if (_has_field_[13]) {
    msg->AppendVarInt(13, bind_id_);
  }

  // Field 14: args
  for (auto& it : args_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(14));
  }

  // Field 15: name_index
  if (_has_field_[15]) {
    msg->AppendVarInt(15, name_index_);
  }

  // Field 16: category_group_name_index
  if (_has_field_[16]) {
    msg->AppendVarInt(16, category_group_name_index_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


ChromeTraceEvent_Arg::ChromeTraceEvent_Arg() = default;
ChromeTraceEvent_Arg::~ChromeTraceEvent_Arg() = default;
ChromeTraceEvent_Arg::ChromeTraceEvent_Arg(const ChromeTraceEvent_Arg&) = default;
ChromeTraceEvent_Arg& ChromeTraceEvent_Arg::operator=(const ChromeTraceEvent_Arg&) = default;
ChromeTraceEvent_Arg::ChromeTraceEvent_Arg(ChromeTraceEvent_Arg&&) noexcept = default;
ChromeTraceEvent_Arg& ChromeTraceEvent_Arg::operator=(ChromeTraceEvent_Arg&&) = default;

bool ChromeTraceEvent_Arg::operator==(const ChromeTraceEvent_Arg& other) const {
  return unknown_fields_ == other.unknown_fields_
   && name_ == other.name_
   && bool_value_ == other.bool_value_
   && uint_value_ == other.uint_value_
   && int_value_ == other.int_value_
   && double_value_ == other.double_value_
   && string_value_ == other.string_value_
   && pointer_value_ == other.pointer_value_
   && json_value_ == other.json_value_
   && traced_value_ == other.traced_value_
   && name_index_ == other.name_index_;
}

bool ChromeTraceEvent_Arg::ParseFromArray(const void* raw, size_t size) {
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
      case 2 /* bool_value */:
        field.get(&bool_value_);
        break;
      case 3 /* uint_value */:
        field.get(&uint_value_);
        break;
      case 4 /* int_value */:
        field.get(&int_value_);
        break;
      case 5 /* double_value */:
        field.get(&double_value_);
        break;
      case 6 /* string_value */:
        field.get(&string_value_);
        break;
      case 7 /* pointer_value */:
        field.get(&pointer_value_);
        break;
      case 8 /* json_value */:
        field.get(&json_value_);
        break;
      case 10 /* traced_value */:
        (*traced_value_).ParseFromArray(field.data(), field.size());
        break;
      case 9 /* name_index */:
        field.get(&name_index_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string ChromeTraceEvent_Arg::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> ChromeTraceEvent_Arg::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void ChromeTraceEvent_Arg::Serialize(::protozero::Message* msg) const {
  // Field 1: name
  if (_has_field_[1]) {
    msg->AppendString(1, name_);
  }

  // Field 2: bool_value
  if (_has_field_[2]) {
    msg->AppendTinyVarInt(2, bool_value_);
  }

  // Field 3: uint_value
  if (_has_field_[3]) {
    msg->AppendVarInt(3, uint_value_);
  }

  // Field 4: int_value
  if (_has_field_[4]) {
    msg->AppendVarInt(4, int_value_);
  }

  // Field 5: double_value
  if (_has_field_[5]) {
    msg->AppendFixed(5, double_value_);
  }

  // Field 6: string_value
  if (_has_field_[6]) {
    msg->AppendString(6, string_value_);
  }

  // Field 7: pointer_value
  if (_has_field_[7]) {
    msg->AppendVarInt(7, pointer_value_);
  }

  // Field 8: json_value
  if (_has_field_[8]) {
    msg->AppendString(8, json_value_);
  }

  // Field 10: traced_value
  if (_has_field_[10]) {
    (*traced_value_).Serialize(msg->BeginNestedMessage<::protozero::Message>(10));
  }

  // Field 9: name_index
  if (_has_field_[9]) {
    msg->AppendVarInt(9, name_index_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}


ChromeTracedValue::ChromeTracedValue() = default;
ChromeTracedValue::~ChromeTracedValue() = default;
ChromeTracedValue::ChromeTracedValue(const ChromeTracedValue&) = default;
ChromeTracedValue& ChromeTracedValue::operator=(const ChromeTracedValue&) = default;
ChromeTracedValue::ChromeTracedValue(ChromeTracedValue&&) noexcept = default;
ChromeTracedValue& ChromeTracedValue::operator=(ChromeTracedValue&&) = default;

bool ChromeTracedValue::operator==(const ChromeTracedValue& other) const {
  return unknown_fields_ == other.unknown_fields_
   && nested_type_ == other.nested_type_
   && dict_keys_ == other.dict_keys_
   && dict_values_ == other.dict_values_
   && array_values_ == other.array_values_
   && int_value_ == other.int_value_
   && double_value_ == other.double_value_
   && bool_value_ == other.bool_value_
   && string_value_ == other.string_value_;
}

int ChromeTracedValue::dict_values_size() const { return static_cast<int>(dict_values_.size()); }
void ChromeTracedValue::clear_dict_values() { dict_values_.clear(); }
ChromeTracedValue* ChromeTracedValue::add_dict_values() { dict_values_.emplace_back(); return &dict_values_.back(); }
int ChromeTracedValue::array_values_size() const { return static_cast<int>(array_values_.size()); }
void ChromeTracedValue::clear_array_values() { array_values_.clear(); }
ChromeTracedValue* ChromeTracedValue::add_array_values() { array_values_.emplace_back(); return &array_values_.back(); }
bool ChromeTracedValue::ParseFromArray(const void* raw, size_t size) {
  dict_keys_.clear();
  dict_values_.clear();
  array_values_.clear();
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* nested_type */:
        field.get(&nested_type_);
        break;
      case 2 /* dict_keys */:
        dict_keys_.emplace_back();
        field.get(&dict_keys_.back());
        break;
      case 3 /* dict_values */:
        dict_values_.emplace_back();
        dict_values_.back().ParseFromArray(field.data(), field.size());
        break;
      case 4 /* array_values */:
        array_values_.emplace_back();
        array_values_.back().ParseFromArray(field.data(), field.size());
        break;
      case 5 /* int_value */:
        field.get(&int_value_);
        break;
      case 6 /* double_value */:
        field.get(&double_value_);
        break;
      case 7 /* bool_value */:
        field.get(&bool_value_);
        break;
      case 8 /* string_value */:
        field.get(&string_value_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string ChromeTracedValue::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> ChromeTracedValue::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void ChromeTracedValue::Serialize(::protozero::Message* msg) const {
  // Field 1: nested_type
  if (_has_field_[1]) {
    msg->AppendVarInt(1, nested_type_);
  }

  // Field 2: dict_keys
  for (auto& it : dict_keys_) {
    msg->AppendString(2, it);
  }

  // Field 3: dict_values
  for (auto& it : dict_values_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(3));
  }

  // Field 4: array_values
  for (auto& it : array_values_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(4));
  }

  // Field 5: int_value
  if (_has_field_[5]) {
    msg->AppendVarInt(5, int_value_);
  }

  // Field 6: double_value
  if (_has_field_[6]) {
    msg->AppendFixed(6, double_value_);
  }

  // Field 7: bool_value
  if (_has_field_[7]) {
    msg->AppendTinyVarInt(7, bool_value_);
  }

  // Field 8: string_value
  if (_has_field_[8]) {
    msg->AppendString(8, string_value_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}

}  // namespace perfetto
}  // namespace protos
}  // namespace gen
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
