// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_MM_EVENT_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_MM_EVENT_PROTO_CPP_H_

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
class MmEventRecordFtraceEvent;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {

class PERFETTO_EXPORT MmEventRecordFtraceEvent : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kAvgLatFieldNumber = 1,
    kCountFieldNumber = 2,
    kMaxLatFieldNumber = 3,
    kTypeFieldNumber = 4,
  };

  MmEventRecordFtraceEvent();
  ~MmEventRecordFtraceEvent() override;
  MmEventRecordFtraceEvent(MmEventRecordFtraceEvent&&) noexcept;
  MmEventRecordFtraceEvent& operator=(MmEventRecordFtraceEvent&&);
  MmEventRecordFtraceEvent(const MmEventRecordFtraceEvent&);
  MmEventRecordFtraceEvent& operator=(const MmEventRecordFtraceEvent&);
  bool operator==(const MmEventRecordFtraceEvent&) const;
  bool operator!=(const MmEventRecordFtraceEvent& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_avg_lat() const { return _has_field_[1]; }
  uint32_t avg_lat() const { return avg_lat_; }
  void set_avg_lat(uint32_t value) { avg_lat_ = value; _has_field_.set(1); }

  bool has_count() const { return _has_field_[2]; }
  uint32_t count() const { return count_; }
  void set_count(uint32_t value) { count_ = value; _has_field_.set(2); }

  bool has_max_lat() const { return _has_field_[3]; }
  uint32_t max_lat() const { return max_lat_; }
  void set_max_lat(uint32_t value) { max_lat_ = value; _has_field_.set(3); }

  bool has_type() const { return _has_field_[4]; }
  uint32_t type() const { return type_; }
  void set_type(uint32_t value) { type_ = value; _has_field_.set(4); }

 private:
  uint32_t avg_lat_{};
  uint32_t count_{};
  uint32_t max_lat_{};
  uint32_t type_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<5> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_MM_EVENT_PROTO_CPP_H_
