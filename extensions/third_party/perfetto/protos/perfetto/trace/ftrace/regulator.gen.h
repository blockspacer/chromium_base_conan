// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_REGULATOR_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_REGULATOR_PROTO_CPP_H_

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
class RegulatorSetVoltageCompleteFtraceEvent;
class RegulatorSetVoltageFtraceEvent;
class RegulatorEnableDelayFtraceEvent;
class RegulatorEnableCompleteFtraceEvent;
class RegulatorEnableFtraceEvent;
class RegulatorDisableCompleteFtraceEvent;
class RegulatorDisableFtraceEvent;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {

class PERFETTO_EXPORT RegulatorSetVoltageCompleteFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kNameFieldNumber = 1,
    kValFieldNumber = 2,
  };

  RegulatorSetVoltageCompleteFtraceEvent();
  ~RegulatorSetVoltageCompleteFtraceEvent() override;
  RegulatorSetVoltageCompleteFtraceEvent(RegulatorSetVoltageCompleteFtraceEvent&&) noexcept;
  RegulatorSetVoltageCompleteFtraceEvent& operator=(RegulatorSetVoltageCompleteFtraceEvent&&);
  RegulatorSetVoltageCompleteFtraceEvent(const RegulatorSetVoltageCompleteFtraceEvent&);
  RegulatorSetVoltageCompleteFtraceEvent& operator=(const RegulatorSetVoltageCompleteFtraceEvent&);
  bool operator==(const RegulatorSetVoltageCompleteFtraceEvent&) const;
  bool operator!=(const RegulatorSetVoltageCompleteFtraceEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_name() const { return _has_field_[1]; }
  const std::string& name() const { return name_; }
  void set_name(const std::string& value) { name_ = value; _has_field_.set(1); }

  bool has_val() const { return _has_field_[2]; }
  uint32_t val() const { return val_; }
  void set_val(uint32_t value) { val_ = value; _has_field_.set(2); }

 private:
  std::string name_{};
  uint32_t val_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<3> _has_field_{};
};


class PERFETTO_EXPORT RegulatorSetVoltageFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kNameFieldNumber = 1,
    kMinFieldNumber = 2,
    kMaxFieldNumber = 3,
  };

  RegulatorSetVoltageFtraceEvent();
  ~RegulatorSetVoltageFtraceEvent() override;
  RegulatorSetVoltageFtraceEvent(RegulatorSetVoltageFtraceEvent&&) noexcept;
  RegulatorSetVoltageFtraceEvent& operator=(RegulatorSetVoltageFtraceEvent&&);
  RegulatorSetVoltageFtraceEvent(const RegulatorSetVoltageFtraceEvent&);
  RegulatorSetVoltageFtraceEvent& operator=(const RegulatorSetVoltageFtraceEvent&);
  bool operator==(const RegulatorSetVoltageFtraceEvent&) const;
  bool operator!=(const RegulatorSetVoltageFtraceEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_name() const { return _has_field_[1]; }
  const std::string& name() const { return name_; }
  void set_name(const std::string& value) { name_ = value; _has_field_.set(1); }

  bool has_min() const { return _has_field_[2]; }
  int32_t min() const { return min_; }
  void set_min(int32_t value) { min_ = value; _has_field_.set(2); }

  bool has_max() const { return _has_field_[3]; }
  int32_t max() const { return max_; }
  void set_max(int32_t value) { max_ = value; _has_field_.set(3); }

 private:
  std::string name_{};
  int32_t min_{};
  int32_t max_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<4> _has_field_{};
};


class PERFETTO_EXPORT RegulatorEnableDelayFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kNameFieldNumber = 1,
  };

  RegulatorEnableDelayFtraceEvent();
  ~RegulatorEnableDelayFtraceEvent() override;
  RegulatorEnableDelayFtraceEvent(RegulatorEnableDelayFtraceEvent&&) noexcept;
  RegulatorEnableDelayFtraceEvent& operator=(RegulatorEnableDelayFtraceEvent&&);
  RegulatorEnableDelayFtraceEvent(const RegulatorEnableDelayFtraceEvent&);
  RegulatorEnableDelayFtraceEvent& operator=(const RegulatorEnableDelayFtraceEvent&);
  bool operator==(const RegulatorEnableDelayFtraceEvent&) const;
  bool operator!=(const RegulatorEnableDelayFtraceEvent& other) const { return !(*this == other); }

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


class PERFETTO_EXPORT RegulatorEnableCompleteFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kNameFieldNumber = 1,
  };

  RegulatorEnableCompleteFtraceEvent();
  ~RegulatorEnableCompleteFtraceEvent() override;
  RegulatorEnableCompleteFtraceEvent(RegulatorEnableCompleteFtraceEvent&&) noexcept;
  RegulatorEnableCompleteFtraceEvent& operator=(RegulatorEnableCompleteFtraceEvent&&);
  RegulatorEnableCompleteFtraceEvent(const RegulatorEnableCompleteFtraceEvent&);
  RegulatorEnableCompleteFtraceEvent& operator=(const RegulatorEnableCompleteFtraceEvent&);
  bool operator==(const RegulatorEnableCompleteFtraceEvent&) const;
  bool operator!=(const RegulatorEnableCompleteFtraceEvent& other) const { return !(*this == other); }

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


class PERFETTO_EXPORT RegulatorEnableFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kNameFieldNumber = 1,
  };

  RegulatorEnableFtraceEvent();
  ~RegulatorEnableFtraceEvent() override;
  RegulatorEnableFtraceEvent(RegulatorEnableFtraceEvent&&) noexcept;
  RegulatorEnableFtraceEvent& operator=(RegulatorEnableFtraceEvent&&);
  RegulatorEnableFtraceEvent(const RegulatorEnableFtraceEvent&);
  RegulatorEnableFtraceEvent& operator=(const RegulatorEnableFtraceEvent&);
  bool operator==(const RegulatorEnableFtraceEvent&) const;
  bool operator!=(const RegulatorEnableFtraceEvent& other) const { return !(*this == other); }

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


class PERFETTO_EXPORT RegulatorDisableCompleteFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kNameFieldNumber = 1,
  };

  RegulatorDisableCompleteFtraceEvent();
  ~RegulatorDisableCompleteFtraceEvent() override;
  RegulatorDisableCompleteFtraceEvent(RegulatorDisableCompleteFtraceEvent&&) noexcept;
  RegulatorDisableCompleteFtraceEvent& operator=(RegulatorDisableCompleteFtraceEvent&&);
  RegulatorDisableCompleteFtraceEvent(const RegulatorDisableCompleteFtraceEvent&);
  RegulatorDisableCompleteFtraceEvent& operator=(const RegulatorDisableCompleteFtraceEvent&);
  bool operator==(const RegulatorDisableCompleteFtraceEvent&) const;
  bool operator!=(const RegulatorDisableCompleteFtraceEvent& other) const { return !(*this == other); }

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


class PERFETTO_EXPORT RegulatorDisableFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kNameFieldNumber = 1,
  };

  RegulatorDisableFtraceEvent();
  ~RegulatorDisableFtraceEvent() override;
  RegulatorDisableFtraceEvent(RegulatorDisableFtraceEvent&&) noexcept;
  RegulatorDisableFtraceEvent& operator=(RegulatorDisableFtraceEvent&&);
  RegulatorDisableFtraceEvent(const RegulatorDisableFtraceEvent&);
  RegulatorDisableFtraceEvent& operator=(const RegulatorDisableFtraceEvent&);
  bool operator==(const RegulatorDisableFtraceEvent&) const;
  bool operator!=(const RegulatorDisableFtraceEvent& other) const { return !(*this == other); }

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

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_REGULATOR_PROTO_CPP_H_
