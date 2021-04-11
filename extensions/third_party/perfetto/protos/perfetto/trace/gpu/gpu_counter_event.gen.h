// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_GPU_GPU_COUNTER_EVENT_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_GPU_GPU_COUNTER_EVENT_PROTO_CPP_H_

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
class GpuCounterEvent;
class GpuCounterEvent_GpuCounter;
class GpuCounterDescriptor;
class GpuCounterDescriptor_GpuCounterBlock;
class GpuCounterDescriptor_GpuCounterSpec;
enum GpuCounterDescriptor_GpuCounterGroup : int;
enum GpuCounterDescriptor_MeasureUnit : int;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {

class PERFETTO_EXPORT GpuCounterEvent : public ::protozero::CppMessageObj {
 public:
  using GpuCounter = GpuCounterEvent_GpuCounter;
  enum FieldNumbers {
    kCounterDescriptorFieldNumber = 1,
    kCountersFieldNumber = 2,
    kGpuIdFieldNumber = 3,
  };

  GpuCounterEvent();
  ~GpuCounterEvent() override;
  GpuCounterEvent(GpuCounterEvent&&) noexcept;
  GpuCounterEvent& operator=(GpuCounterEvent&&);
  GpuCounterEvent(const GpuCounterEvent&);
  GpuCounterEvent& operator=(const GpuCounterEvent&);
  bool operator==(const GpuCounterEvent&) const;
  bool operator!=(const GpuCounterEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_counter_descriptor() const { return _has_field_[1]; }
  const GpuCounterDescriptor& counter_descriptor() const { return *counter_descriptor_; }
  GpuCounterDescriptor* mutable_counter_descriptor() { _has_field_.set(1); return counter_descriptor_.get(); }

  const std::vector<GpuCounterEvent_GpuCounter>& counters() const { return counters_; }
  std::vector<GpuCounterEvent_GpuCounter>* mutable_counters() { return &counters_; }
  int counters_size() const;
  void clear_counters();
  GpuCounterEvent_GpuCounter* add_counters();

  bool has_gpu_id() const { return _has_field_[3]; }
  int32_t gpu_id() const { return gpu_id_; }
  void set_gpu_id(int32_t value) { gpu_id_ = value; _has_field_.set(3); }

 private:
  ::protozero::CopyablePtr<GpuCounterDescriptor> counter_descriptor_;
  std::vector<GpuCounterEvent_GpuCounter> counters_;
  int32_t gpu_id_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<4> _has_field_{};
};


class PERFETTO_EXPORT GpuCounterEvent_GpuCounter : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kCounterIdFieldNumber = 1,
    kIntValueFieldNumber = 2,
    kDoubleValueFieldNumber = 3,
  };

  GpuCounterEvent_GpuCounter();
  ~GpuCounterEvent_GpuCounter() override;
  GpuCounterEvent_GpuCounter(GpuCounterEvent_GpuCounter&&) noexcept;
  GpuCounterEvent_GpuCounter& operator=(GpuCounterEvent_GpuCounter&&);
  GpuCounterEvent_GpuCounter(const GpuCounterEvent_GpuCounter&);
  GpuCounterEvent_GpuCounter& operator=(const GpuCounterEvent_GpuCounter&);
  bool operator==(const GpuCounterEvent_GpuCounter&) const;
  bool operator!=(const GpuCounterEvent_GpuCounter& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_counter_id() const { return _has_field_[1]; }
  uint32_t counter_id() const { return counter_id_; }
  void set_counter_id(uint32_t value) { counter_id_ = value; _has_field_.set(1); }

  bool has_int_value() const { return _has_field_[2]; }
  int64_t int_value() const { return int_value_; }
  void set_int_value(int64_t value) { int_value_ = value; _has_field_.set(2); }

  bool has_double_value() const { return _has_field_[3]; }
  double double_value() const { return double_value_; }
  void set_double_value(double value) { double_value_ = value; _has_field_.set(3); }

 private:
  uint32_t counter_id_{};
  int64_t int_value_{};
  double double_value_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<4> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_GPU_GPU_COUNTER_EVENT_PROTO_CPP_H_