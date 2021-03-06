// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_CLK_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_CLK_PROTO_CPP_H_

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
class ClkSetRateFtraceEvent;
class ClkDisableFtraceEvent;
class ClkEnableFtraceEvent;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {

class PERFETTO_EXPORT ClkSetRateFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kNameFieldNumber = 1,
    kRateFieldNumber = 2,
  };

  ClkSetRateFtraceEvent();
  ~ClkSetRateFtraceEvent() override;
  ClkSetRateFtraceEvent(ClkSetRateFtraceEvent&&) noexcept;
  ClkSetRateFtraceEvent& operator=(ClkSetRateFtraceEvent&&);
  ClkSetRateFtraceEvent(const ClkSetRateFtraceEvent&);
  ClkSetRateFtraceEvent& operator=(const ClkSetRateFtraceEvent&);
  bool operator==(const ClkSetRateFtraceEvent&) const;
  bool operator!=(const ClkSetRateFtraceEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_name() const { return _has_field_[1]; }
  const std::string& name() const { return name_; }
  void set_name(const std::string& value) { name_ = value; _has_field_.set(1); }

  bool has_rate() const { return _has_field_[2]; }
  uint64_t rate() const { return rate_; }
  void set_rate(uint64_t value) { rate_ = value; _has_field_.set(2); }

 private:
  std::string name_{};
  uint64_t rate_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<3> _has_field_{};
};


class PERFETTO_EXPORT ClkDisableFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kNameFieldNumber = 1,
  };

  ClkDisableFtraceEvent();
  ~ClkDisableFtraceEvent() override;
  ClkDisableFtraceEvent(ClkDisableFtraceEvent&&) noexcept;
  ClkDisableFtraceEvent& operator=(ClkDisableFtraceEvent&&);
  ClkDisableFtraceEvent(const ClkDisableFtraceEvent&);
  ClkDisableFtraceEvent& operator=(const ClkDisableFtraceEvent&);
  bool operator==(const ClkDisableFtraceEvent&) const;
  bool operator!=(const ClkDisableFtraceEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_name() const { return _has_field_[1]; }
  const std::string& name() const { return name_; }
  void set_name(const std::string& value) { name_ = value; _has_field_.set(1); }

 private:
  std::string name_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<2> _has_field_{};
};


class PERFETTO_EXPORT ClkEnableFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kNameFieldNumber = 1,
  };

  ClkEnableFtraceEvent();
  ~ClkEnableFtraceEvent() override;
  ClkEnableFtraceEvent(ClkEnableFtraceEvent&&) noexcept;
  ClkEnableFtraceEvent& operator=(ClkEnableFtraceEvent&&);
  ClkEnableFtraceEvent(const ClkEnableFtraceEvent&);
  ClkEnableFtraceEvent& operator=(const ClkEnableFtraceEvent&);
  bool operator==(const ClkEnableFtraceEvent&) const;
  bool operator!=(const ClkEnableFtraceEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_name() const { return _has_field_[1]; }
  const std::string& name() const { return name_; }
  void set_name(const std::string& value) { name_ = value; _has_field_.set(1); }

 private:
  std::string name_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<2> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_CLK_PROTO_CPP_H_
