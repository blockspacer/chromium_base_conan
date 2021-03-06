// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_CHROME_CHROME_BENCHMARK_METADATA_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_CHROME_CHROME_BENCHMARK_METADATA_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {


class ChromeBenchmarkMetadata_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/9, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  ChromeBenchmarkMetadata_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ChromeBenchmarkMetadata_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ChromeBenchmarkMetadata_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_benchmark_start_time_us() const { return at<1>().valid(); }
  int64_t benchmark_start_time_us() const { return at<1>().as_int64(); }
  bool has_story_run_time_us() const { return at<2>().valid(); }
  int64_t story_run_time_us() const { return at<2>().as_int64(); }
  bool has_benchmark_name() const { return at<3>().valid(); }
  ::protozero::ConstChars benchmark_name() const { return at<3>().as_string(); }
  bool has_benchmark_description() const { return at<4>().valid(); }
  ::protozero::ConstChars benchmark_description() const { return at<4>().as_string(); }
  bool has_label() const { return at<5>().valid(); }
  ::protozero::ConstChars label() const { return at<5>().as_string(); }
  bool has_story_name() const { return at<6>().valid(); }
  ::protozero::ConstChars story_name() const { return at<6>().as_string(); }
  bool has_story_tags() const { return at<7>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstChars> story_tags() const { return GetRepeated<::protozero::ConstChars>(7); }
  bool has_story_run_index() const { return at<8>().valid(); }
  int32_t story_run_index() const { return at<8>().as_int32(); }
  bool has_had_failures() const { return at<9>().valid(); }
  bool had_failures() const { return at<9>().as_bool(); }
};

class ChromeBenchmarkMetadata : public ::protozero::Message {
 public:
  using Decoder = ChromeBenchmarkMetadata_Decoder;
  enum : int32_t {
    kBenchmarkStartTimeUsFieldNumber = 1,
    kStoryRunTimeUsFieldNumber = 2,
    kBenchmarkNameFieldNumber = 3,
    kBenchmarkDescriptionFieldNumber = 4,
    kLabelFieldNumber = 5,
    kStoryNameFieldNumber = 6,
    kStoryTagsFieldNumber = 7,
    kStoryRunIndexFieldNumber = 8,
    kHadFailuresFieldNumber = 9,
  };
  void set_benchmark_start_time_us(int64_t value) {
    AppendVarInt(1, value);
  }
  void set_story_run_time_us(int64_t value) {
    AppendVarInt(2, value);
  }
  void set_benchmark_name(const std::string& value) {
    AppendBytes(3, value.data(), value.size());
  }
  void set_benchmark_name(const char* data, size_t size) {
    AppendBytes(3, data, size);
  }
  void set_benchmark_description(const std::string& value) {
    AppendBytes(4, value.data(), value.size());
  }
  void set_benchmark_description(const char* data, size_t size) {
    AppendBytes(4, data, size);
  }
  void set_label(const std::string& value) {
    AppendBytes(5, value.data(), value.size());
  }
  void set_label(const char* data, size_t size) {
    AppendBytes(5, data, size);
  }
  void set_story_name(const std::string& value) {
    AppendBytes(6, value.data(), value.size());
  }
  void set_story_name(const char* data, size_t size) {
    AppendBytes(6, data, size);
  }
  void add_story_tags(const std::string& value) {
    AppendBytes(7, value.data(), value.size());
  }
  void add_story_tags(const char* data, size_t size) {
    AppendBytes(7, data, size);
  }
  void set_story_run_index(int32_t value) {
    AppendVarInt(8, value);
  }
  void set_had_failures(bool value) {
    AppendTinyVarInt(9, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
