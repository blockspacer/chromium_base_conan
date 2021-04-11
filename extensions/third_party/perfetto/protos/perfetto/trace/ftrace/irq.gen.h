// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_IRQ_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_IRQ_PROTO_CPP_H_

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
class IrqHandlerExitFtraceEvent;
class IrqHandlerEntryFtraceEvent;
class SoftirqRaiseFtraceEvent;
class SoftirqExitFtraceEvent;
class SoftirqEntryFtraceEvent;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {

class PERFETTO_EXPORT IrqHandlerExitFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kIrqFieldNumber = 1,
    kRetFieldNumber = 2,
  };

  IrqHandlerExitFtraceEvent();
  ~IrqHandlerExitFtraceEvent() override;
  IrqHandlerExitFtraceEvent(IrqHandlerExitFtraceEvent&&) noexcept;
  IrqHandlerExitFtraceEvent& operator=(IrqHandlerExitFtraceEvent&&);
  IrqHandlerExitFtraceEvent(const IrqHandlerExitFtraceEvent&);
  IrqHandlerExitFtraceEvent& operator=(const IrqHandlerExitFtraceEvent&);
  bool operator==(const IrqHandlerExitFtraceEvent&) const;
  bool operator!=(const IrqHandlerExitFtraceEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_irq() const { return _has_field_[1]; }
  int32_t irq() const { return irq_; }
  void set_irq(int32_t value) { irq_ = value; _has_field_.set(1); }

  bool has_ret() const { return _has_field_[2]; }
  int32_t ret() const { return ret_; }
  void set_ret(int32_t value) { ret_ = value; _has_field_.set(2); }

 private:
  int32_t irq_{};
  int32_t ret_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<3> _has_field_{};
};


class PERFETTO_EXPORT IrqHandlerEntryFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kIrqFieldNumber = 1,
    kNameFieldNumber = 2,
    kHandlerFieldNumber = 3,
  };

  IrqHandlerEntryFtraceEvent();
  ~IrqHandlerEntryFtraceEvent() override;
  IrqHandlerEntryFtraceEvent(IrqHandlerEntryFtraceEvent&&) noexcept;
  IrqHandlerEntryFtraceEvent& operator=(IrqHandlerEntryFtraceEvent&&);
  IrqHandlerEntryFtraceEvent(const IrqHandlerEntryFtraceEvent&);
  IrqHandlerEntryFtraceEvent& operator=(const IrqHandlerEntryFtraceEvent&);
  bool operator==(const IrqHandlerEntryFtraceEvent&) const;
  bool operator!=(const IrqHandlerEntryFtraceEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_irq() const { return _has_field_[1]; }
  int32_t irq() const { return irq_; }
  void set_irq(int32_t value) { irq_ = value; _has_field_.set(1); }

  bool has_name() const { return _has_field_[2]; }
  const std::string& name() const { return name_; }
  void set_name(const std::string& value) { name_ = value; _has_field_.set(2); }

  bool has_handler() const { return _has_field_[3]; }
  uint32_t handler() const { return handler_; }
  void set_handler(uint32_t value) { handler_ = value; _has_field_.set(3); }

 private:
  int32_t irq_{};
  std::string name_{};
  uint32_t handler_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<4> _has_field_{};
};


class PERFETTO_EXPORT SoftirqRaiseFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kVecFieldNumber = 1,
  };

  SoftirqRaiseFtraceEvent();
  ~SoftirqRaiseFtraceEvent() override;
  SoftirqRaiseFtraceEvent(SoftirqRaiseFtraceEvent&&) noexcept;
  SoftirqRaiseFtraceEvent& operator=(SoftirqRaiseFtraceEvent&&);
  SoftirqRaiseFtraceEvent(const SoftirqRaiseFtraceEvent&);
  SoftirqRaiseFtraceEvent& operator=(const SoftirqRaiseFtraceEvent&);
  bool operator==(const SoftirqRaiseFtraceEvent&) const;
  bool operator!=(const SoftirqRaiseFtraceEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_vec() const { return _has_field_[1]; }
  uint32_t vec() const { return vec_; }
  void set_vec(uint32_t value) { vec_ = value; _has_field_.set(1); }

 private:
  uint32_t vec_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<2> _has_field_{};
};


class PERFETTO_EXPORT SoftirqExitFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kVecFieldNumber = 1,
  };

  SoftirqExitFtraceEvent();
  ~SoftirqExitFtraceEvent() override;
  SoftirqExitFtraceEvent(SoftirqExitFtraceEvent&&) noexcept;
  SoftirqExitFtraceEvent& operator=(SoftirqExitFtraceEvent&&);
  SoftirqExitFtraceEvent(const SoftirqExitFtraceEvent&);
  SoftirqExitFtraceEvent& operator=(const SoftirqExitFtraceEvent&);
  bool operator==(const SoftirqExitFtraceEvent&) const;
  bool operator!=(const SoftirqExitFtraceEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_vec() const { return _has_field_[1]; }
  uint32_t vec() const { return vec_; }
  void set_vec(uint32_t value) { vec_ = value; _has_field_.set(1); }

 private:
  uint32_t vec_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<2> _has_field_{};
};


class PERFETTO_EXPORT SoftirqEntryFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kVecFieldNumber = 1,
  };

  SoftirqEntryFtraceEvent();
  ~SoftirqEntryFtraceEvent() override;
  SoftirqEntryFtraceEvent(SoftirqEntryFtraceEvent&&) noexcept;
  SoftirqEntryFtraceEvent& operator=(SoftirqEntryFtraceEvent&&);
  SoftirqEntryFtraceEvent(const SoftirqEntryFtraceEvent&);
  SoftirqEntryFtraceEvent& operator=(const SoftirqEntryFtraceEvent&);
  bool operator==(const SoftirqEntryFtraceEvent&) const;
  bool operator!=(const SoftirqEntryFtraceEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_vec() const { return _has_field_[1]; }
  uint32_t vec() const { return vec_; }
  void set_vec(uint32_t value) { vec_ = value; _has_field_.set(1); }

 private:
  uint32_t vec_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<2> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_IRQ_PROTO_CPP_H_