// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TEST_EVENT_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TEST_EVENT_PROTO_CPP_H_

#include <stdint.h>
#include <bitset>
#include <vector>
#include <string>
#include <type_traits>

#include "perfetto/protozero/cpp_message_obj.h"
#include "perfetto/protozero/copyable_ptr.h"
#include "perfetto/base/export.h"

namespace perfetto {
namespace protos {
namespace gen {
class TestEvent;
class TestEvent_TestPayload;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {

class PERFETTO_EXPORT TestEvent : public ::protozero::CppMessageObj {
 public:
  using TestPayload = TestEvent_TestPayload;
  enum FieldNumbers {
    kStrFieldNumber = 1,
    kSeqValueFieldNumber = 2,
    kCounterFieldNumber = 3,
    kIsLastFieldNumber = 4,
    kPayloadFieldNumber = 5,
  };

  TestEvent();
  ~TestEvent() override;
  TestEvent(TestEvent&&) noexcept;
  TestEvent& operator=(TestEvent&&);
  TestEvent(const TestEvent&);
  TestEvent& operator=(const TestEvent&);
  bool operator==(const TestEvent&) const;
  bool operator!=(const TestEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_str() const { return _has_field_[1]; }
  const std::string& str() const { return str_; }
  void set_str(const std::string& value) { str_ = value; _has_field_.set(1); }

  bool has_seq_value() const { return _has_field_[2]; }
  uint32_t seq_value() const { return seq_value_; }
  void set_seq_value(uint32_t value) { seq_value_ = value; _has_field_.set(2); }

  bool has_counter() const { return _has_field_[3]; }
  uint64_t counter() const { return counter_; }
  void set_counter(uint64_t value) { counter_ = value; _has_field_.set(3); }

  bool has_is_last() const { return _has_field_[4]; }
  bool is_last() const { return is_last_; }
  void set_is_last(bool value) { is_last_ = value; _has_field_.set(4); }

  bool has_payload() const { return _has_field_[5]; }
  const TestEvent_TestPayload& payload() const { return *payload_; }
  TestEvent_TestPayload* mutable_payload() { _has_field_.set(5); return payload_.get(); }

 private:
  std::string str_{};
  uint32_t seq_value_{};
  uint64_t counter_{};
  bool is_last_{};
  ::protozero::CopyablePtr<TestEvent_TestPayload> payload_;

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<6> _has_field_{};
};


class PERFETTO_EXPORT TestEvent_TestPayload : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kStrFieldNumber = 1,
    kNestedFieldNumber = 2,
    kRemainingNestingDepthFieldNumber = 3,
  };

  TestEvent_TestPayload();
  ~TestEvent_TestPayload() override;
  TestEvent_TestPayload(TestEvent_TestPayload&&) noexcept;
  TestEvent_TestPayload& operator=(TestEvent_TestPayload&&);
  TestEvent_TestPayload(const TestEvent_TestPayload&);
  TestEvent_TestPayload& operator=(const TestEvent_TestPayload&);
  bool operator==(const TestEvent_TestPayload&) const;
  bool operator!=(const TestEvent_TestPayload& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  const std::vector<std::string>& str() const { return str_; }
  std::vector<std::string>* mutable_str() { return &str_; }
  int str_size() const { return static_cast<int>(str_.size()); }
  void clear_str() { str_.clear(); }
  void add_str(std::string value) { str_.emplace_back(value); }
  std::string* add_str() { str_.emplace_back(); return &str_.back(); }

  const std::vector<TestEvent_TestPayload>& nested() const { return nested_; }
  std::vector<TestEvent_TestPayload>* mutable_nested() { return &nested_; }
  int nested_size() const;
  void clear_nested();
  TestEvent_TestPayload* add_nested();

  bool has_remaining_nesting_depth() const { return _has_field_[3]; }
  uint32_t remaining_nesting_depth() const { return remaining_nesting_depth_; }
  void set_remaining_nesting_depth(uint32_t value) { remaining_nesting_depth_ = value; _has_field_.set(3); }

 private:
  std::vector<std::string> str_;
  std::vector<TestEvent_TestPayload> nested_;
  uint32_t remaining_nesting_depth_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<4> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TEST_EVENT_PROTO_CPP_H_