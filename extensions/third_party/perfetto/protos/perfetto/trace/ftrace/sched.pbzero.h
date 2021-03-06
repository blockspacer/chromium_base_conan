// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_SCHED_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_FTRACE_SCHED_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {


class SchedProcessWaitFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SchedProcessWaitFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SchedProcessWaitFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SchedProcessWaitFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_comm() const { return at<1>().valid(); }
  ::protozero::ConstChars comm() const { return at<1>().as_string(); }
  bool has_pid() const { return at<2>().valid(); }
  int32_t pid() const { return at<2>().as_int32(); }
  bool has_prio() const { return at<3>().valid(); }
  int32_t prio() const { return at<3>().as_int32(); }
};

class SchedProcessWaitFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SchedProcessWaitFtraceEvent_Decoder;
  enum : int32_t {
    kCommFieldNumber = 1,
    kPidFieldNumber = 2,
    kPrioFieldNumber = 3,
  };
  void set_comm(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_comm(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_pid(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_prio(int32_t value) {
    AppendVarInt(3, value);
  }
};

class SchedProcessHangFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/2, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SchedProcessHangFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SchedProcessHangFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SchedProcessHangFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_comm() const { return at<1>().valid(); }
  ::protozero::ConstChars comm() const { return at<1>().as_string(); }
  bool has_pid() const { return at<2>().valid(); }
  int32_t pid() const { return at<2>().as_int32(); }
};

class SchedProcessHangFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SchedProcessHangFtraceEvent_Decoder;
  enum : int32_t {
    kCommFieldNumber = 1,
    kPidFieldNumber = 2,
  };
  void set_comm(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_comm(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_pid(int32_t value) {
    AppendVarInt(2, value);
  }
};

class SchedProcessFreeFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SchedProcessFreeFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SchedProcessFreeFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SchedProcessFreeFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_comm() const { return at<1>().valid(); }
  ::protozero::ConstChars comm() const { return at<1>().as_string(); }
  bool has_pid() const { return at<2>().valid(); }
  int32_t pid() const { return at<2>().as_int32(); }
  bool has_prio() const { return at<3>().valid(); }
  int32_t prio() const { return at<3>().as_int32(); }
};

class SchedProcessFreeFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SchedProcessFreeFtraceEvent_Decoder;
  enum : int32_t {
    kCommFieldNumber = 1,
    kPidFieldNumber = 2,
    kPrioFieldNumber = 3,
  };
  void set_comm(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_comm(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_pid(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_prio(int32_t value) {
    AppendVarInt(3, value);
  }
};

class SchedProcessForkFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/4, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SchedProcessForkFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SchedProcessForkFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SchedProcessForkFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_parent_comm() const { return at<1>().valid(); }
  ::protozero::ConstChars parent_comm() const { return at<1>().as_string(); }
  bool has_parent_pid() const { return at<2>().valid(); }
  int32_t parent_pid() const { return at<2>().as_int32(); }
  bool has_child_comm() const { return at<3>().valid(); }
  ::protozero::ConstChars child_comm() const { return at<3>().as_string(); }
  bool has_child_pid() const { return at<4>().valid(); }
  int32_t child_pid() const { return at<4>().as_int32(); }
};

class SchedProcessForkFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SchedProcessForkFtraceEvent_Decoder;
  enum : int32_t {
    kParentCommFieldNumber = 1,
    kParentPidFieldNumber = 2,
    kChildCommFieldNumber = 3,
    kChildPidFieldNumber = 4,
  };
  void set_parent_comm(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_parent_comm(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_parent_pid(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_child_comm(const std::string& value) {
    AppendBytes(3, value.data(), value.size());
  }
  void set_child_comm(const char* data, size_t size) {
    AppendBytes(3, data, size);
  }
  void set_child_pid(int32_t value) {
    AppendVarInt(4, value);
  }
};

class SchedProcessExitFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/4, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SchedProcessExitFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SchedProcessExitFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SchedProcessExitFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_comm() const { return at<1>().valid(); }
  ::protozero::ConstChars comm() const { return at<1>().as_string(); }
  bool has_pid() const { return at<2>().valid(); }
  int32_t pid() const { return at<2>().as_int32(); }
  bool has_tgid() const { return at<3>().valid(); }
  int32_t tgid() const { return at<3>().as_int32(); }
  bool has_prio() const { return at<4>().valid(); }
  int32_t prio() const { return at<4>().as_int32(); }
};

class SchedProcessExitFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SchedProcessExitFtraceEvent_Decoder;
  enum : int32_t {
    kCommFieldNumber = 1,
    kPidFieldNumber = 2,
    kTgidFieldNumber = 3,
    kPrioFieldNumber = 4,
  };
  void set_comm(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_comm(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_pid(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_tgid(int32_t value) {
    AppendVarInt(3, value);
  }
  void set_prio(int32_t value) {
    AppendVarInt(4, value);
  }
};

class SchedProcessExecFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SchedProcessExecFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SchedProcessExecFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SchedProcessExecFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_filename() const { return at<1>().valid(); }
  ::protozero::ConstChars filename() const { return at<1>().as_string(); }
  bool has_pid() const { return at<2>().valid(); }
  int32_t pid() const { return at<2>().as_int32(); }
  bool has_old_pid() const { return at<3>().valid(); }
  int32_t old_pid() const { return at<3>().as_int32(); }
};

class SchedProcessExecFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SchedProcessExecFtraceEvent_Decoder;
  enum : int32_t {
    kFilenameFieldNumber = 1,
    kPidFieldNumber = 2,
    kOldPidFieldNumber = 3,
  };
  void set_filename(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_filename(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_pid(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_old_pid(int32_t value) {
    AppendVarInt(3, value);
  }
};

class SchedWakeupNewFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/5, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SchedWakeupNewFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SchedWakeupNewFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SchedWakeupNewFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_comm() const { return at<1>().valid(); }
  ::protozero::ConstChars comm() const { return at<1>().as_string(); }
  bool has_pid() const { return at<2>().valid(); }
  int32_t pid() const { return at<2>().as_int32(); }
  bool has_prio() const { return at<3>().valid(); }
  int32_t prio() const { return at<3>().as_int32(); }
  bool has_success() const { return at<4>().valid(); }
  int32_t success() const { return at<4>().as_int32(); }
  bool has_target_cpu() const { return at<5>().valid(); }
  int32_t target_cpu() const { return at<5>().as_int32(); }
};

class SchedWakeupNewFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SchedWakeupNewFtraceEvent_Decoder;
  enum : int32_t {
    kCommFieldNumber = 1,
    kPidFieldNumber = 2,
    kPrioFieldNumber = 3,
    kSuccessFieldNumber = 4,
    kTargetCpuFieldNumber = 5,
  };
  void set_comm(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_comm(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_pid(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_prio(int32_t value) {
    AppendVarInt(3, value);
  }
  void set_success(int32_t value) {
    AppendVarInt(4, value);
  }
  void set_target_cpu(int32_t value) {
    AppendVarInt(5, value);
  }
};

class SchedWakingFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/5, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SchedWakingFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SchedWakingFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SchedWakingFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_comm() const { return at<1>().valid(); }
  ::protozero::ConstChars comm() const { return at<1>().as_string(); }
  bool has_pid() const { return at<2>().valid(); }
  int32_t pid() const { return at<2>().as_int32(); }
  bool has_prio() const { return at<3>().valid(); }
  int32_t prio() const { return at<3>().as_int32(); }
  bool has_success() const { return at<4>().valid(); }
  int32_t success() const { return at<4>().as_int32(); }
  bool has_target_cpu() const { return at<5>().valid(); }
  int32_t target_cpu() const { return at<5>().as_int32(); }
};

class SchedWakingFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SchedWakingFtraceEvent_Decoder;
  enum : int32_t {
    kCommFieldNumber = 1,
    kPidFieldNumber = 2,
    kPrioFieldNumber = 3,
    kSuccessFieldNumber = 4,
    kTargetCpuFieldNumber = 5,
  };
  void set_comm(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_comm(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_pid(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_prio(int32_t value) {
    AppendVarInt(3, value);
  }
  void set_success(int32_t value) {
    AppendVarInt(4, value);
  }
  void set_target_cpu(int32_t value) {
    AppendVarInt(5, value);
  }
};

class SchedCpuHotplugFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SchedCpuHotplugFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SchedCpuHotplugFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SchedCpuHotplugFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_affected_cpu() const { return at<1>().valid(); }
  int32_t affected_cpu() const { return at<1>().as_int32(); }
  bool has_error() const { return at<2>().valid(); }
  int32_t error() const { return at<2>().as_int32(); }
  bool has_status() const { return at<3>().valid(); }
  int32_t status() const { return at<3>().as_int32(); }
};

class SchedCpuHotplugFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SchedCpuHotplugFtraceEvent_Decoder;
  enum : int32_t {
    kAffectedCpuFieldNumber = 1,
    kErrorFieldNumber = 2,
    kStatusFieldNumber = 3,
  };
  void set_affected_cpu(int32_t value) {
    AppendVarInt(1, value);
  }
  void set_error(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_status(int32_t value) {
    AppendVarInt(3, value);
  }
};

class SchedBlockedReasonFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/3, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SchedBlockedReasonFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SchedBlockedReasonFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SchedBlockedReasonFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_pid() const { return at<1>().valid(); }
  int32_t pid() const { return at<1>().as_int32(); }
  bool has_caller() const { return at<2>().valid(); }
  uint64_t caller() const { return at<2>().as_uint64(); }
  bool has_io_wait() const { return at<3>().valid(); }
  uint32_t io_wait() const { return at<3>().as_uint32(); }
};

class SchedBlockedReasonFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SchedBlockedReasonFtraceEvent_Decoder;
  enum : int32_t {
    kPidFieldNumber = 1,
    kCallerFieldNumber = 2,
    kIoWaitFieldNumber = 3,
  };
  void set_pid(int32_t value) {
    AppendVarInt(1, value);
  }
  void set_caller(uint64_t value) {
    AppendVarInt(2, value);
  }
  void set_io_wait(uint32_t value) {
    AppendVarInt(3, value);
  }
};

class SchedWakeupFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/5, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SchedWakeupFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SchedWakeupFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SchedWakeupFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_comm() const { return at<1>().valid(); }
  ::protozero::ConstChars comm() const { return at<1>().as_string(); }
  bool has_pid() const { return at<2>().valid(); }
  int32_t pid() const { return at<2>().as_int32(); }
  bool has_prio() const { return at<3>().valid(); }
  int32_t prio() const { return at<3>().as_int32(); }
  bool has_success() const { return at<4>().valid(); }
  int32_t success() const { return at<4>().as_int32(); }
  bool has_target_cpu() const { return at<5>().valid(); }
  int32_t target_cpu() const { return at<5>().as_int32(); }
};

class SchedWakeupFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SchedWakeupFtraceEvent_Decoder;
  enum : int32_t {
    kCommFieldNumber = 1,
    kPidFieldNumber = 2,
    kPrioFieldNumber = 3,
    kSuccessFieldNumber = 4,
    kTargetCpuFieldNumber = 5,
  };
  void set_comm(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_comm(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_pid(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_prio(int32_t value) {
    AppendVarInt(3, value);
  }
  void set_success(int32_t value) {
    AppendVarInt(4, value);
  }
  void set_target_cpu(int32_t value) {
    AppendVarInt(5, value);
  }
};

class SchedSwitchFtraceEvent_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/7, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  SchedSwitchFtraceEvent_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit SchedSwitchFtraceEvent_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit SchedSwitchFtraceEvent_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_prev_comm() const { return at<1>().valid(); }
  ::protozero::ConstChars prev_comm() const { return at<1>().as_string(); }
  bool has_prev_pid() const { return at<2>().valid(); }
  int32_t prev_pid() const { return at<2>().as_int32(); }
  bool has_prev_prio() const { return at<3>().valid(); }
  int32_t prev_prio() const { return at<3>().as_int32(); }
  bool has_prev_state() const { return at<4>().valid(); }
  int64_t prev_state() const { return at<4>().as_int64(); }
  bool has_next_comm() const { return at<5>().valid(); }
  ::protozero::ConstChars next_comm() const { return at<5>().as_string(); }
  bool has_next_pid() const { return at<6>().valid(); }
  int32_t next_pid() const { return at<6>().as_int32(); }
  bool has_next_prio() const { return at<7>().valid(); }
  int32_t next_prio() const { return at<7>().as_int32(); }
};

class SchedSwitchFtraceEvent : public ::protozero::Message {
 public:
  using Decoder = SchedSwitchFtraceEvent_Decoder;
  enum : int32_t {
    kPrevCommFieldNumber = 1,
    kPrevPidFieldNumber = 2,
    kPrevPrioFieldNumber = 3,
    kPrevStateFieldNumber = 4,
    kNextCommFieldNumber = 5,
    kNextPidFieldNumber = 6,
    kNextPrioFieldNumber = 7,
  };
  void set_prev_comm(const std::string& value) {
    AppendBytes(1, value.data(), value.size());
  }
  void set_prev_comm(const char* data, size_t size) {
    AppendBytes(1, data, size);
  }
  void set_prev_pid(int32_t value) {
    AppendVarInt(2, value);
  }
  void set_prev_prio(int32_t value) {
    AppendVarInt(3, value);
  }
  void set_prev_state(int64_t value) {
    AppendVarInt(4, value);
  }
  void set_next_comm(const std::string& value) {
    AppendBytes(5, value.data(), value.size());
  }
  void set_next_comm(const char* data, size_t size) {
    AppendBytes(5, data, size);
  }
  void set_next_pid(int32_t value) {
    AppendVarInt(6, value);
  }
  void set_next_prio(int32_t value) {
    AppendVarInt(7, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
