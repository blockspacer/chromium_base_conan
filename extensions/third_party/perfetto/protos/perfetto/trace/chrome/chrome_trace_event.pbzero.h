// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_CHROME_CHROME_TRACE_EVENT_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_CHROME_CHROME_TRACE_EVENT_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {

class ChromeLegacyJsonTrace;
class ChromeMetadata;
class ChromeStringTableEntry;
class ChromeTraceEvent;
class ChromeTraceEvent_Arg;
class ChromeTracedValue;
enum ChromeLegacyJsonTrace_TraceType : int32_t;
enum ChromeTracedValue_NestedType : int32_t;

enum ChromeLegacyJsonTrace_TraceType : int32_t {
  ChromeLegacyJsonTrace_TraceType_USER_TRACE = 0,
  ChromeLegacyJsonTrace_TraceType_SYSTEM_TRACE = 1,
};

const ChromeLegacyJsonTrace_TraceType ChromeLegacyJsonTrace_TraceType_MIN = ChromeLegacyJsonTrace_TraceType_USER_TRACE;
const ChromeLegacyJsonTrace_TraceType ChromeLegacyJsonTrace_TraceType_MAX = ChromeLegacyJsonTrace_TraceType_SYSTEM_TRACE;

enum ChromeTracedValue_NestedType : int32_t {
  ChromeTracedValue_NestedType_DICT = 0,
  ChromeTracedValue_NestedType_ARRAY = 1,
};

const ChromeTracedValue_NestedType ChromeTracedValue_NestedType_MIN = ChromeTracedValue_NestedType_DICT;
const ChromeTracedValue_NestedType ChromeTracedValue_NestedType_MAX = ChromeTracedValue_NestedType_ARRAY;

class ChromeEventBundle_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/5, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  ChromeEventBundle_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ChromeEventBundle_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ChromeEventBundle_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_trace_events() const { return at<1>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> trace_events() const { return GetRepeated<::protozero::ConstBytes>(1); }
  bool has_metadata() const { return at<2>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> metadata() const { return GetRepeated<::protozero::ConstBytes>(2); }
  bool has_legacy_ftrace_output() const { return at<4>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstChars> legacy_ftrace_output() const { return GetRepeated<::protozero::ConstChars>(4); }
  bool has_legacy_json_trace() const { return at<5>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> legacy_json_trace() const { return GetRepeated<::protozero::ConstBytes>(5); }
  bool has_string_table() const { return at<3>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> string_table() const { return GetRepeated<::protozero::ConstBytes>(3); }
};

class ChromeEventBundle : public ::protozero::Message {
 public:
  using Decoder = ChromeEventBundle_Decoder;
  enum : int32_t {
    kTraceEventsFieldNumber = 1,
    kMetadataFieldNumber = 2,
    kLegacyFtraceOutputFieldNumber = 4,
    kLegacyJsonTraceFieldNumber = 5,
    kStringTableFieldNumber = 3,
  };
  template <typename T = ChromeTraceEvent> T* add_trace_events() {
    return BeginNestedMessage<T>(1);
  }

  template <typename T = ChromeMetadata> T* add_metadata() {
    return BeginNestedMessage<T>(2);
  }

  void add_legacy_ftrace_output(const std::string& value) {
    AppendBytes(4, value.data(), value.size());
  }
  void add_legacy_ftrace_output(const char* data, size_t size) {
    AppendBytes(4, data, size);
  }
  template <typename T = ChromeLegacyJsonTrace> T* add_legacy_json_trace() {
    return BeginNestedMessage<T>(5);
  }

  template <typename T = ChromeStringTableEntry> T* add_string_table() {
    return BeginNestedMessage<T>(3);
  }

};

class ChromeLegacyJsonTrace_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ChromeLegacyJsonTrace_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ChromeLegacyJsonTrace_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ChromeLegacyJsonTrace_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_type() const { return at<1>().valid(); }
  int32_t type() const { return at<1>().as_int32(); }
  bool has_data() const { return at<2>().valid(); }
  ::protozero::ConstChars data() const { return at<2>().as_string(); }
};

class ChromeLegacyJsonTrace : public ::protozero::Message {
 public:
  using Decoder = ChromeLegacyJsonTrace_Decoder;
  enum : int32_t {
    kTypeFieldNumber = 1,
    kDataFieldNumber = 2,
  };
  using TraceType = ::perfetto::protos::pbzero::ChromeLegacyJsonTrace_TraceType;
  static const TraceType USER_TRACE = ChromeLegacyJsonTrace_TraceType_USER_TRACE;
  static const TraceType SYSTEM_TRACE = ChromeLegacyJsonTrace_TraceType_SYSTEM_TRACE;
  void set_type(::perfetto::protos::pbzero::ChromeLegacyJsonTrace_TraceType value) {
    AppendTinyVarInt(1, value);
  }
  void set_data(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_data(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
};

class ChromeMetadata_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/5, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ChromeMetadata_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ChromeMetadata_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ChromeMetadata_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
  bool has_string_value() const { return at<2>().valid(); }
  ::protozero::ConstChars string_value() const { return at<2>().as_string(); }
  bool has_bool_value() const { return at<3>().valid(); }
  bool bool_value() const { return at<3>().as_bool(); }
  bool has_int_value() const { return at<4>().valid(); }
  int64_t int_value() const { return at<4>().as_int64(); }
  bool has_json_value() const { return at<5>().valid(); }
  ::protozero::ConstChars json_value() const { return at<5>().as_string(); }
};

class ChromeMetadata : public ::protozero::Message {
 public:
  using Decoder = ChromeMetadata_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
    kStringValueFieldNumber = 2,
    kBoolValueFieldNumber = 3,
    kIntValueFieldNumber = 4,
    kJsonValueFieldNumber = 5,
  };
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_string_value(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void set_string_value(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
  void set_bool_value(bool value) {
    AppendTinyVarInt(3, value);
  }
  void set_int_value(int64_t value) {
    AppendVarInt(4, value);
  }
  void set_json_value(const std::string& value) {
    AppendBytes(5, value.data(), value.size());
  }
  void set_json_value(const char* data, size_t size) {
    AppendBytes(5, data, size);
  }
};

class ChromeTraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/16, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  ChromeTraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ChromeTraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ChromeTraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
  bool has_timestamp() const { return at<2>().valid(); }
  int64_t timestamp() const { return at<2>().as_int64(); }
  bool has_phase() const { return at<3>().valid(); }
  int32_t phase() const { return at<3>().as_int32(); }
  bool has_thread_id() const { return at<4>().valid(); }
  int32_t thread_id() const { return at<4>().as_int32(); }
  bool has_duration() const { return at<5>().valid(); }
  int64_t duration() const { return at<5>().as_int64(); }
  bool has_thread_duration() const { return at<6>().valid(); }
  int64_t thread_duration() const { return at<6>().as_int64(); }
  bool has_scope() const { return at<7>().valid(); }
  ::protozero::ConstChars scope() const { return at<7>().as_string(); }
  bool has_id() const { return at<8>().valid(); }
  uint64_t id() const { return at<8>().as_uint64(); }
  bool has_flags() const { return at<9>().valid(); }
  uint32_t flags() const { return at<9>().as_uint32(); }
  bool has_category_group_name() const { return at<10>().valid(); }
  ::protozero::ConstChars category_group_name() const { return at<10>().as_string(); }
  bool has_process_id() const { return at<11>().valid(); }
  int32_t process_id() const { return at<11>().as_int32(); }
  bool has_thread_timestamp() const { return at<12>().valid(); }
  int64_t thread_timestamp() const { return at<12>().as_int64(); }
  bool has_bind_id() const { return at<13>().valid(); }
  uint64_t bind_id() const { return at<13>().as_uint64(); }
  bool has_args() const { return at<14>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> args() const { return GetRepeated<::protozero::ConstBytes>(14); }
  bool has_name_index() const { return at<15>().valid(); }
  uint32_t name_index() const { return at<15>().as_uint32(); }
  bool has_category_group_name_index() const { return at<16>().valid(); }
  uint32_t category_group_name_index() const { return at<16>().as_uint32(); }
};

class ChromeTraceEvent : public ::protozero::Message {
 public:
  using Decoder = ChromeTraceEvent_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
    kTimestampFieldNumber = 2,
    kPhaseFieldNumber = 3,
    kThreadIdFieldNumber = 4,
    kDurationFieldNumber = 5,
    kThreadDurationFieldNumber = 6,
    kScopeFieldNumber = 7,
    kIdFieldNumber = 8,
    kFlagsFieldNumber = 9,
    kCategoryGroupNameFieldNumber = 10,
    kProcessIdFieldNumber = 11,
    kThreadTimestampFieldNumber = 12,
    kBindIdFieldNumber = 13,
    kArgsFieldNumber = 14,
    kNameIndexFieldNumber = 15,
    kCategoryGroupNameIndexFieldNumber = 16,
  };
  using Arg = ::perfetto::protos::pbzero::ChromeTraceEvent_Arg;
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_timestamp(int64_t value) {
    AppendVarInt(2, value);
  }
  void set_phase(int32_t value) {
    AppendVarInt(3, value);
  }
  void set_thread_id(int32_t value) {
    AppendVarInt(4, value);
  }
  void set_duration(int64_t value) {
    AppendVarInt(5, value);
  }
  void set_thread_duration(int64_t value) {
    AppendVarInt(6, value);
  }
  void set_scope(const std::string& value) {
    AppendBytes(7, value.data(), value.size());
  }
  void set_scope(const char* data, size_t size) {
    AppendBytes(7, data, size);
  }
  void set_id(uint64_t value) {
    AppendVarInt(8, value);
  }
  void set_flags(uint32_t value) {
    AppendVarInt(9, value);
  }
  void set_category_group_name(const std::string& value) {
    AppendBytes(10, value.data(), value.size());
  }
  void set_category_group_name(const char* data, size_t size) {
    AppendBytes(10, data, size);
  }
  void set_process_id(int32_t value) {
    AppendVarInt(11, value);
  }
  void set_thread_timestamp(int64_t value) {
    AppendVarInt(12, value);
  }
  void set_bind_id(uint64_t value) {
    AppendVarInt(13, value);
  }
  template <typename T = ChromeTraceEvent_Arg> T* add_args() {
    return BeginNestedMessage<T>(14);
  }

  void set_name_index(uint32_t value) {
    AppendVarInt(15, value);
  }
  void set_category_group_name_index(uint32_t value) {
    AppendVarInt(16, value);
  }
};

class ChromeTraceEvent_Arg_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/10, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ChromeTraceEvent_Arg_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ChromeTraceEvent_Arg_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ChromeTraceEvent_Arg_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_name() const { return at<1>().valid(); }
  ::protozero::ConstChars name() const { return at<1>().as_string(); }
  bool has_bool_value() const { return at<2>().valid(); }
  bool bool_value() const { return at<2>().as_bool(); }
  bool has_uint_value() const { return at<3>().valid(); }
  uint64_t uint_value() const { return at<3>().as_uint64(); }
  bool has_int_value() const { return at<4>().valid(); }
  int64_t int_value() const { return at<4>().as_int64(); }
  bool has_double_value() const { return at<5>().valid(); }
  double double_value() const { return at<5>().as_double(); }
  bool has_string_value() const { return at<6>().valid(); }
  ::protozero::ConstChars string_value() const { return at<6>().as_string(); }
  bool has_pointer_value() const { return at<7>().valid(); }
  uint64_t pointer_value() const { return at<7>().as_uint64(); }
  bool has_json_value() const { return at<8>().valid(); }
  ::protozero::ConstChars json_value() const { return at<8>().as_string(); }
  bool has_traced_value() const { return at<10>().valid(); }
  ::protozero::ConstBytes traced_value() const { return at<10>().as_bytes(); }
  bool has_name_index() const { return at<9>().valid(); }
  uint32_t name_index() const { return at<9>().as_uint32(); }
};

class ChromeTraceEvent_Arg : public ::protozero::Message {
 public:
  using Decoder = ChromeTraceEvent_Arg_Decoder;
  enum : int32_t {
    kNameFieldNumber = 1,
    kBoolValueFieldNumber = 2,
    kUintValueFieldNumber = 3,
    kIntValueFieldNumber = 4,
    kDoubleValueFieldNumber = 5,
    kStringValueFieldNumber = 6,
    kPointerValueFieldNumber = 7,
    kJsonValueFieldNumber = 8,
    kTracedValueFieldNumber = 10,
    kNameIndexFieldNumber = 9,
  };
  void set_name(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_name(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_bool_value(bool value) {
    AppendTinyVarInt(2, value);
  }
  void set_uint_value(uint64_t value) {
    AppendVarInt(3, value);
  }
  void set_int_value(int64_t value) {
    AppendVarInt(4, value);
  }
  void set_double_value(double value) {
    AppendFixed(5, value);
  }
  void set_string_value(const std::string& value) {
    AppendBytes(6, value.data(), value.size());
  }
  void set_string_value(const char* data, size_t size) {
    AppendBytes(6, data, size);
  }
  void set_pointer_value(uint64_t value) {
    AppendVarInt(7, value);
  }
  void set_json_value(const std::string& value) {
    AppendBytes(8, value.data(), value.size());
  }
  void set_json_value(const char* data, size_t size) {
    AppendBytes(8, data, size);
  }
  template <typename T = ChromeTracedValue> T* set_traced_value() {
    return BeginNestedMessage<T>(10);
  }

  void set_name_index(uint32_t value) {
    AppendVarInt(9, value);
  }
};

class ChromeStringTableEntry_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ChromeStringTableEntry_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ChromeStringTableEntry_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ChromeStringTableEntry_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_value() const { return at<1>().valid(); }
  ::protozero::ConstChars value() const { return at<1>().as_string(); }
  bool has_index() const { return at<2>().valid(); }
  int32_t index() const { return at<2>().as_int32(); }
};

class ChromeStringTableEntry : public ::protozero::Message {
 public:
  using Decoder = ChromeStringTableEntry_Decoder;
  enum : int32_t {
    kValueFieldNumber = 1,
    kIndexFieldNumber = 2,
  };
  void set_value(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_value(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_index(int32_t value) {
    AppendVarInt(2, value);
  }
};

class ChromeTracedValue_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/8, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  ChromeTracedValue_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ChromeTracedValue_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ChromeTracedValue_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_nested_type() const { return at<1>().valid(); }
  int32_t nested_type() const { return at<1>().as_int32(); }
  bool has_dict_keys() const { return at<2>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstChars> dict_keys() const { return GetRepeated<::protozero::ConstChars>(2); }
  bool has_dict_values() const { return at<3>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> dict_values() const { return GetRepeated<::protozero::ConstBytes>(3); }
  bool has_array_values() const { return at<4>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> array_values() const { return GetRepeated<::protozero::ConstBytes>(4); }
  bool has_int_value() const { return at<5>().valid(); }
  int32_t int_value() const { return at<5>().as_int32(); }
  bool has_double_value() const { return at<6>().valid(); }
  double double_value() const { return at<6>().as_double(); }
  bool has_bool_value() const { return at<7>().valid(); }
  bool bool_value() const { return at<7>().as_bool(); }
  bool has_string_value() const { return at<8>().valid(); }
  ::protozero::ConstChars string_value() const { return at<8>().as_string(); }
};

class ChromeTracedValue : public ::protozero::Message {
 public:
  using Decoder = ChromeTracedValue_Decoder;
  enum : int32_t {
    kNestedTypeFieldNumber = 1,
    kDictKeysFieldNumber = 2,
    kDictValuesFieldNumber = 3,
    kArrayValuesFieldNumber = 4,
    kIntValueFieldNumber = 5,
    kDoubleValueFieldNumber = 6,
    kBoolValueFieldNumber = 7,
    kStringValueFieldNumber = 8,
  };
  using NestedType = ::perfetto::protos::pbzero::ChromeTracedValue_NestedType;
  static const NestedType DICT = ChromeTracedValue_NestedType_DICT;
  static const NestedType ARRAY = ChromeTracedValue_NestedType_ARRAY;
  void set_nested_type(::perfetto::protos::pbzero::ChromeTracedValue_NestedType value) {
    AppendTinyVarInt(1, value);
  }
  void add_dict_keys(const std::string& value) {
    AppendBytes(2, value.data(), value.size());
  }
  void add_dict_keys(const char* data, size_t size) {
    AppendBytes(2, data, size);
  }
  template <typename T = ChromeTracedValue> T* add_dict_values() {
    return BeginNestedMessage<T>(3);
  }

  template <typename T = ChromeTracedValue> T* add_array_values() {
    return BeginNestedMessage<T>(4);
  }

  void set_int_value(int32_t value) {
    AppendVarInt(5, value);
  }
  void set_double_value(double value) {
    AppendFixed(6, value);
  }
  void set_bool_value(bool value) {
    AppendTinyVarInt(7, value);
  }
  void set_string_value(const std::string& value) {
    AppendBytes(8, value.data(), value.size());
  }
  void set_string_value(const char* data, size_t size) {
    AppendBytes(8, data, size);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
