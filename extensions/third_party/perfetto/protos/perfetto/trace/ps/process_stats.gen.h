// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_PS_PROCESS_STATS_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_PS_PROCESS_STATS_PROTO_CPP_H_

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
class ProcessStats;
class ProcessStats_Process;
class ProcessStats_Thread;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {

class PERFETTO_EXPORT ProcessStats : public ::protozero::CppMessageObj {
 public:
  using Thread = ProcessStats_Thread;
  using Process = ProcessStats_Process;
  enum FieldNumbers {
    kProcessesFieldNumber = 1,
    kCollectionEndTimestampFieldNumber = 2,
  };

  ProcessStats();
  ~ProcessStats() override;
  ProcessStats(ProcessStats&&) noexcept;
  ProcessStats& operator=(ProcessStats&&);
  ProcessStats(const ProcessStats&);
  ProcessStats& operator=(const ProcessStats&);
  bool operator==(const ProcessStats&) const;
  bool operator!=(const ProcessStats& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  const std::vector<ProcessStats_Process>& processes() const { return processes_; }
  std::vector<ProcessStats_Process>* mutable_processes() { return &processes_; }
  int processes_size() const;
  void clear_processes();
  ProcessStats_Process* add_processes();

  bool has_collection_end_timestamp() const { return _has_field_[2]; }
  uint64_t collection_end_timestamp() const { return collection_end_timestamp_; }
  void set_collection_end_timestamp(uint64_t value) { collection_end_timestamp_ = value; _has_field_.set(2); }

 private:
  std::vector<ProcessStats_Process> processes_;
  uint64_t collection_end_timestamp_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<3> _has_field_{};
};


class PERFETTO_EXPORT ProcessStats_Process : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kPidFieldNumber = 1,
    kVmSizeKbFieldNumber = 2,
    kVmRssKbFieldNumber = 3,
    kRssAnonKbFieldNumber = 4,
    kRssFileKbFieldNumber = 5,
    kRssShmemKbFieldNumber = 6,
    kVmSwapKbFieldNumber = 7,
    kVmLockedKbFieldNumber = 8,
    kVmHwmKbFieldNumber = 9,
    kOomScoreAdjFieldNumber = 10,
    kThreadsFieldNumber = 11,
    kIsPeakRssResettableFieldNumber = 12,
    kChromePrivateFootprintKbFieldNumber = 13,
    kChromePeakResidentSetKbFieldNumber = 14,
  };

  ProcessStats_Process();
  ~ProcessStats_Process() override;
  ProcessStats_Process(ProcessStats_Process&&) noexcept;
  ProcessStats_Process& operator=(ProcessStats_Process&&);
  ProcessStats_Process(const ProcessStats_Process&);
  ProcessStats_Process& operator=(const ProcessStats_Process&);
  bool operator==(const ProcessStats_Process&) const;
  bool operator!=(const ProcessStats_Process& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_pid() const { return _has_field_[1]; }
  int32_t pid() const { return pid_; }
  void set_pid(int32_t value) { pid_ = value; _has_field_.set(1); }

  bool has_vm_size_kb() const { return _has_field_[2]; }
  uint64_t vm_size_kb() const { return vm_size_kb_; }
  void set_vm_size_kb(uint64_t value) { vm_size_kb_ = value; _has_field_.set(2); }

  bool has_vm_rss_kb() const { return _has_field_[3]; }
  uint64_t vm_rss_kb() const { return vm_rss_kb_; }
  void set_vm_rss_kb(uint64_t value) { vm_rss_kb_ = value; _has_field_.set(3); }

  bool has_rss_anon_kb() const { return _has_field_[4]; }
  uint64_t rss_anon_kb() const { return rss_anon_kb_; }
  void set_rss_anon_kb(uint64_t value) { rss_anon_kb_ = value; _has_field_.set(4); }

  bool has_rss_file_kb() const { return _has_field_[5]; }
  uint64_t rss_file_kb() const { return rss_file_kb_; }
  void set_rss_file_kb(uint64_t value) { rss_file_kb_ = value; _has_field_.set(5); }

  bool has_rss_shmem_kb() const { return _has_field_[6]; }
  uint64_t rss_shmem_kb() const { return rss_shmem_kb_; }
  void set_rss_shmem_kb(uint64_t value) { rss_shmem_kb_ = value; _has_field_.set(6); }

  bool has_vm_swap_kb() const { return _has_field_[7]; }
  uint64_t vm_swap_kb() const { return vm_swap_kb_; }
  void set_vm_swap_kb(uint64_t value) { vm_swap_kb_ = value; _has_field_.set(7); }

  bool has_vm_locked_kb() const { return _has_field_[8]; }
  uint64_t vm_locked_kb() const { return vm_locked_kb_; }
  void set_vm_locked_kb(uint64_t value) { vm_locked_kb_ = value; _has_field_.set(8); }

  bool has_vm_hwm_kb() const { return _has_field_[9]; }
  uint64_t vm_hwm_kb() const { return vm_hwm_kb_; }
  void set_vm_hwm_kb(uint64_t value) { vm_hwm_kb_ = value; _has_field_.set(9); }

  bool has_oom_score_adj() const { return _has_field_[10]; }
  int64_t oom_score_adj() const { return oom_score_adj_; }
  void set_oom_score_adj(int64_t value) { oom_score_adj_ = value; _has_field_.set(10); }

  const std::vector<ProcessStats_Thread>& threads() const { return threads_; }
  std::vector<ProcessStats_Thread>* mutable_threads() { return &threads_; }
  int threads_size() const;
  void clear_threads();
  ProcessStats_Thread* add_threads();

  bool has_is_peak_rss_resettable() const { return _has_field_[12]; }
  bool is_peak_rss_resettable() const { return is_peak_rss_resettable_; }
  void set_is_peak_rss_resettable(bool value) { is_peak_rss_resettable_ = value; _has_field_.set(12); }

  bool has_chrome_private_footprint_kb() const { return _has_field_[13]; }
  uint32_t chrome_private_footprint_kb() const { return chrome_private_footprint_kb_; }
  void set_chrome_private_footprint_kb(uint32_t value) { chrome_private_footprint_kb_ = value; _has_field_.set(13); }

  bool has_chrome_peak_resident_set_kb() const { return _has_field_[14]; }
  uint32_t chrome_peak_resident_set_kb() const { return chrome_peak_resident_set_kb_; }
  void set_chrome_peak_resident_set_kb(uint32_t value) { chrome_peak_resident_set_kb_ = value; _has_field_.set(14); }

 private:
  int32_t pid_{};
  uint64_t vm_size_kb_{};
  uint64_t vm_rss_kb_{};
  uint64_t rss_anon_kb_{};
  uint64_t rss_file_kb_{};
  uint64_t rss_shmem_kb_{};
  uint64_t vm_swap_kb_{};
  uint64_t vm_locked_kb_{};
  uint64_t vm_hwm_kb_{};
  int64_t oom_score_adj_{};
  std::vector<ProcessStats_Thread> threads_;
  bool is_peak_rss_resettable_{};
  uint32_t chrome_private_footprint_kb_{};
  uint32_t chrome_peak_resident_set_kb_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<15> _has_field_{};
};


class PERFETTO_EXPORT ProcessStats_Thread : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kTidFieldNumber = 1,
    kCpuFreqIndicesFieldNumber = 2,
    kCpuFreqTicksFieldNumber = 3,
    kCpuFreqFullFieldNumber = 4,
  };

  ProcessStats_Thread();
  ~ProcessStats_Thread() override;
  ProcessStats_Thread(ProcessStats_Thread&&) noexcept;
  ProcessStats_Thread& operator=(ProcessStats_Thread&&);
  ProcessStats_Thread(const ProcessStats_Thread&);
  ProcessStats_Thread& operator=(const ProcessStats_Thread&);
  bool operator==(const ProcessStats_Thread&) const;
  bool operator!=(const ProcessStats_Thread& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_tid() const { return _has_field_[1]; }
  int32_t tid() const { return tid_; }
  void set_tid(int32_t value) { tid_ = value; _has_field_.set(1); }

  const std::vector<uint32_t>& cpu_freq_indices() const { return cpu_freq_indices_; }
  std::vector<uint32_t>* mutable_cpu_freq_indices() { return &cpu_freq_indices_; }
  int cpu_freq_indices_size() const { return static_cast<int>(cpu_freq_indices_.size()); }
  void clear_cpu_freq_indices() { cpu_freq_indices_.clear(); }
  void add_cpu_freq_indices(uint32_t value) { cpu_freq_indices_.emplace_back(value); }
  uint32_t* add_cpu_freq_indices() { cpu_freq_indices_.emplace_back(); return &cpu_freq_indices_.back(); }

  const std::vector<uint64_t>& cpu_freq_ticks() const { return cpu_freq_ticks_; }
  std::vector<uint64_t>* mutable_cpu_freq_ticks() { return &cpu_freq_ticks_; }
  int cpu_freq_ticks_size() const { return static_cast<int>(cpu_freq_ticks_.size()); }
  void clear_cpu_freq_ticks() { cpu_freq_ticks_.clear(); }
  void add_cpu_freq_ticks(uint64_t value) { cpu_freq_ticks_.emplace_back(value); }
  uint64_t* add_cpu_freq_ticks() { cpu_freq_ticks_.emplace_back(); return &cpu_freq_ticks_.back(); }

  bool has_cpu_freq_full() const { return _has_field_[4]; }
  bool cpu_freq_full() const { return cpu_freq_full_; }
  void set_cpu_freq_full(bool value) { cpu_freq_full_ = value; _has_field_.set(4); }

 private:
  int32_t tid_{};
  std::vector<uint32_t> cpu_freq_indices_;
  std::vector<uint64_t> cpu_freq_ticks_;
  bool cpu_freq_full_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<5> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_PS_PROCESS_STATS_PROTO_CPP_H_
