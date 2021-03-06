// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_TEST_BUNDLE_WRAPPER_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_TEST_BUNDLE_WRAPPER_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {

class FtraceEventBundle;

class TestBundleWrapper_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/true> {
 public:
  TestBundleWrapper_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit TestBundleWrapper_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit TestBundleWrapper_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_before() const { return at<1>().valid(); }
  ::protozero::ConstChars before() const { return at<1>().as_string(); }
  bool has_bundle() const { return at<2>().valid(); }
  ::protozero::RepeatedFieldIterator<::protozero::ConstBytes> bundle() const { return GetRepeated<::protozero::ConstBytes>(2); }
  bool has_after() const { return at<3>().valid(); }
  ::protozero::ConstChars after() const { return at<3>().as_string(); }
};

class TestBundleWrapper : public ::protozero::Message {
 public:
  using Decoder = TestBundleWrapper_Decoder;
  enum : int32_t {
    kBeforeFieldNumber = 1,
    kBundleFieldNumber = 2,
    kAfterFieldNumber = 3,
  };
  void set_before(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_before(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  template <typename T = FtraceEventBundle> T* add_bundle() {
    return BeginNestedMessage<T>(2);
  }

  void set_after(const std::string& value) {
    AppendBytes(3, value.data(), value.size());
  }
  void set_after(const char* data, size_t size) {
    AppendBytes(3, data, size);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
