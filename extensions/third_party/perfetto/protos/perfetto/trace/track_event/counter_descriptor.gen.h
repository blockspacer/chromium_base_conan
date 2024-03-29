// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_COUNTER_DESCRIPTOR_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_COUNTER_DESCRIPTOR_PROTO_CPP_H_

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
class CounterDescriptor;
enum CounterDescriptor_BuiltinCounterType : int;
enum CounterDescriptor_Unit : int;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {
enum CounterDescriptor_BuiltinCounterType : int {
  CounterDescriptor_BuiltinCounterType_COUNTER_UNSPECIFIED = 0,
  CounterDescriptor_BuiltinCounterType_COUNTER_THREAD_TIME_NS = 1,
  CounterDescriptor_BuiltinCounterType_COUNTER_THREAD_INSTRUCTION_COUNT = 2,
};
enum CounterDescriptor_Unit : int {
  CounterDescriptor_Unit_UNIT_UNSPECIFIED = 0,
  CounterDescriptor_Unit_UNIT_TIME_NS = 1,
  CounterDescriptor_Unit_UNIT_COUNT = 2,
  CounterDescriptor_Unit_UNIT_SIZE_BYTES = 3,
};

class PERFETTO_EXPORT CounterDescriptor : public ::protozero::CppMessageObj {
 public:
  using BuiltinCounterType = CounterDescriptor_BuiltinCounterType;
  static constexpr auto COUNTER_UNSPECIFIED = CounterDescriptor_BuiltinCounterType_COUNTER_UNSPECIFIED;
  static constexpr auto COUNTER_THREAD_TIME_NS = CounterDescriptor_BuiltinCounterType_COUNTER_THREAD_TIME_NS;
  static constexpr auto COUNTER_THREAD_INSTRUCTION_COUNT = CounterDescriptor_BuiltinCounterType_COUNTER_THREAD_INSTRUCTION_COUNT;
  static constexpr auto BuiltinCounterType_MIN = CounterDescriptor_BuiltinCounterType_COUNTER_UNSPECIFIED;
  static constexpr auto BuiltinCounterType_MAX = CounterDescriptor_BuiltinCounterType_COUNTER_THREAD_INSTRUCTION_COUNT;
  using Unit = CounterDescriptor_Unit;
  static constexpr auto UNIT_UNSPECIFIED = CounterDescriptor_Unit_UNIT_UNSPECIFIED;
  static constexpr auto UNIT_TIME_NS = CounterDescriptor_Unit_UNIT_TIME_NS;
  static constexpr auto UNIT_COUNT = CounterDescriptor_Unit_UNIT_COUNT;
  static constexpr auto UNIT_SIZE_BYTES = CounterDescriptor_Unit_UNIT_SIZE_BYTES;
  static constexpr auto Unit_MIN = CounterDescriptor_Unit_UNIT_UNSPECIFIED;
  static constexpr auto Unit_MAX = CounterDescriptor_Unit_UNIT_SIZE_BYTES;
  enum FieldNumbers {
    kTypeFieldNumber = 1,
    kCategoriesFieldNumber = 2,
    kUnitFieldNumber = 3,
    kUnitMultiplierFieldNumber = 4,
    kIsIncrementalFieldNumber = 5,
  };

  CounterDescriptor();
  ~CounterDescriptor() override;
  CounterDescriptor(CounterDescriptor&&) noexcept;
  CounterDescriptor& operator=(CounterDescriptor&&);
  CounterDescriptor(const CounterDescriptor&);
  CounterDescriptor& operator=(const CounterDescriptor&);
  bool operator==(const CounterDescriptor&) const;
  bool operator!=(const CounterDescriptor& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_type() const { return _has_field_[1]; }
  CounterDescriptor_BuiltinCounterType type() const { return type_; }
  void set_type(CounterDescriptor_BuiltinCounterType value) { type_ = value; _has_field_.set(1); }

  const std::vector<std::string>& categories() const { return categories_; }
  std::vector<std::string>* mutable_categories() { return &categories_; }
  int categories_size() const { return static_cast<int>(categories_.size()); }
  void clear_categories() { categories_.clear(); }
  void add_categories(std::string value) { categories_.emplace_back(value); }
  std::string* add_categories() { categories_.emplace_back(); return &categories_.back(); }

  bool has_unit() const { return _has_field_[3]; }
  CounterDescriptor_Unit unit() const { return unit_; }
  void set_unit(CounterDescriptor_Unit value) { unit_ = value; _has_field_.set(3); }

  bool has_unit_multiplier() const { return _has_field_[4]; }
  int64_t unit_multiplier() const { return unit_multiplier_; }
  void set_unit_multiplier(int64_t value) { unit_multiplier_ = value; _has_field_.set(4); }

  bool has_is_incremental() const { return _has_field_[5]; }
  bool is_incremental() const { return is_incremental_; }
  void set_is_incremental(bool value) { is_incremental_ = value; _has_field_.set(5); }

 private:
  CounterDescriptor_BuiltinCounterType type_{};
  std::vector<std::string> categories_;
  CounterDescriptor_Unit unit_{};
  int64_t unit_multiplier_{};
  bool is_incremental_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<6> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_COUNTER_DESCRIPTOR_PROTO_CPP_H_
