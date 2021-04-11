// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/trace/ftrace/ftrace_stats.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2fftrace_2fftrace_5fstats_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2fftrace_2fftrace_5fstats_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_util.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_protos_2fperfetto_2ftrace_2fftrace_2fftrace_5fstats_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_protos_2fperfetto_2ftrace_2fftrace_2fftrace_5fstats_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
namespace perfetto {
namespace protos {
class FtraceCpuStats;
class FtraceCpuStatsDefaultTypeInternal;
extern FtraceCpuStatsDefaultTypeInternal _FtraceCpuStats_default_instance_;
class FtraceStats;
class FtraceStatsDefaultTypeInternal;
extern FtraceStatsDefaultTypeInternal _FtraceStats_default_instance_;
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> ::perfetto::protos::FtraceCpuStats* Arena::CreateMaybeMessage<::perfetto::protos::FtraceCpuStats>(Arena*);
template<> ::perfetto::protos::FtraceStats* Arena::CreateMaybeMessage<::perfetto::protos::FtraceStats>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace perfetto {
namespace protos {

enum FtraceStats_Phase : int {
  FtraceStats_Phase_UNSPECIFIED = 0,
  FtraceStats_Phase_START_OF_TRACE = 1,
  FtraceStats_Phase_END_OF_TRACE = 2
};
bool FtraceStats_Phase_IsValid(int value);
constexpr FtraceStats_Phase FtraceStats_Phase_Phase_MIN = FtraceStats_Phase_UNSPECIFIED;
constexpr FtraceStats_Phase FtraceStats_Phase_Phase_MAX = FtraceStats_Phase_END_OF_TRACE;
constexpr int FtraceStats_Phase_Phase_ARRAYSIZE = FtraceStats_Phase_Phase_MAX + 1;

const std::string& FtraceStats_Phase_Name(FtraceStats_Phase value);
template<typename T>
inline const std::string& FtraceStats_Phase_Name(T enum_t_value) {
  static_assert(::std::is_same<T, FtraceStats_Phase>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function FtraceStats_Phase_Name.");
  return FtraceStats_Phase_Name(static_cast<FtraceStats_Phase>(enum_t_value));
}
bool FtraceStats_Phase_Parse(
    const std::string& name, FtraceStats_Phase* value);
// ===================================================================

class FtraceCpuStats :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:perfetto.protos.FtraceCpuStats) */ {
 public:
  FtraceCpuStats();
  virtual ~FtraceCpuStats();

  FtraceCpuStats(const FtraceCpuStats& from);
  FtraceCpuStats(FtraceCpuStats&& from) noexcept
    : FtraceCpuStats() {
    *this = ::std::move(from);
  }

  inline FtraceCpuStats& operator=(const FtraceCpuStats& from) {
    CopyFrom(from);
    return *this;
  }
  inline FtraceCpuStats& operator=(FtraceCpuStats&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const std::string& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline std::string* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const FtraceCpuStats& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const FtraceCpuStats* internal_default_instance() {
    return reinterpret_cast<const FtraceCpuStats*>(
               &_FtraceCpuStats_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(FtraceCpuStats& a, FtraceCpuStats& b) {
    a.Swap(&b);
  }
  inline void Swap(FtraceCpuStats* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline FtraceCpuStats* New() const final {
    return CreateMaybeMessage<FtraceCpuStats>(nullptr);
  }

  FtraceCpuStats* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<FtraceCpuStats>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)
    final;
  void CopyFrom(const FtraceCpuStats& from);
  void MergeFrom(const FtraceCpuStats& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  void DiscardUnknownFields();
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(FtraceCpuStats* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "perfetto.protos.FtraceCpuStats";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  std::string GetTypeName() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kCpuFieldNumber = 1,
    kEntriesFieldNumber = 2,
    kOverrunFieldNumber = 3,
    kCommitOverrunFieldNumber = 4,
    kBytesReadFieldNumber = 5,
    kOldestEventTsFieldNumber = 6,
    kNowTsFieldNumber = 7,
    kDroppedEventsFieldNumber = 8,
    kReadEventsFieldNumber = 9,
  };
  // optional uint64 cpu = 1;
  bool has_cpu() const;
  void clear_cpu();
  ::PROTOBUF_NAMESPACE_ID::uint64 cpu() const;
  void set_cpu(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // optional uint64 entries = 2;
  bool has_entries() const;
  void clear_entries();
  ::PROTOBUF_NAMESPACE_ID::uint64 entries() const;
  void set_entries(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // optional uint64 overrun = 3;
  bool has_overrun() const;
  void clear_overrun();
  ::PROTOBUF_NAMESPACE_ID::uint64 overrun() const;
  void set_overrun(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // optional uint64 commit_overrun = 4;
  bool has_commit_overrun() const;
  void clear_commit_overrun();
  ::PROTOBUF_NAMESPACE_ID::uint64 commit_overrun() const;
  void set_commit_overrun(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // optional uint64 bytes_read = 5;
  bool has_bytes_read() const;
  void clear_bytes_read();
  ::PROTOBUF_NAMESPACE_ID::uint64 bytes_read() const;
  void set_bytes_read(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // optional double oldest_event_ts = 6;
  bool has_oldest_event_ts() const;
  void clear_oldest_event_ts();
  double oldest_event_ts() const;
  void set_oldest_event_ts(double value);

  // optional double now_ts = 7;
  bool has_now_ts() const;
  void clear_now_ts();
  double now_ts() const;
  void set_now_ts(double value);

  // optional uint64 dropped_events = 8;
  bool has_dropped_events() const;
  void clear_dropped_events();
  ::PROTOBUF_NAMESPACE_ID::uint64 dropped_events() const;
  void set_dropped_events(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // optional uint64 read_events = 9;
  bool has_read_events() const;
  void clear_read_events();
  ::PROTOBUF_NAMESPACE_ID::uint64 read_events() const;
  void set_read_events(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // @@protoc_insertion_point(class_scope:perfetto.protos.FtraceCpuStats)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::uint64 cpu_;
  ::PROTOBUF_NAMESPACE_ID::uint64 entries_;
  ::PROTOBUF_NAMESPACE_ID::uint64 overrun_;
  ::PROTOBUF_NAMESPACE_ID::uint64 commit_overrun_;
  ::PROTOBUF_NAMESPACE_ID::uint64 bytes_read_;
  double oldest_event_ts_;
  double now_ts_;
  ::PROTOBUF_NAMESPACE_ID::uint64 dropped_events_;
  ::PROTOBUF_NAMESPACE_ID::uint64 read_events_;
  friend struct ::TableStruct_protos_2fperfetto_2ftrace_2fftrace_2fftrace_5fstats_2eproto;
};
// -------------------------------------------------------------------

class FtraceStats :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:perfetto.protos.FtraceStats) */ {
 public:
  FtraceStats();
  virtual ~FtraceStats();

  FtraceStats(const FtraceStats& from);
  FtraceStats(FtraceStats&& from) noexcept
    : FtraceStats() {
    *this = ::std::move(from);
  }

  inline FtraceStats& operator=(const FtraceStats& from) {
    CopyFrom(from);
    return *this;
  }
  inline FtraceStats& operator=(FtraceStats&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const std::string& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline std::string* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const FtraceStats& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const FtraceStats* internal_default_instance() {
    return reinterpret_cast<const FtraceStats*>(
               &_FtraceStats_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(FtraceStats& a, FtraceStats& b) {
    a.Swap(&b);
  }
  inline void Swap(FtraceStats* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline FtraceStats* New() const final {
    return CreateMaybeMessage<FtraceStats>(nullptr);
  }

  FtraceStats* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<FtraceStats>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)
    final;
  void CopyFrom(const FtraceStats& from);
  void MergeFrom(const FtraceStats& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  void DiscardUnknownFields();
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(FtraceStats* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "perfetto.protos.FtraceStats";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  std::string GetTypeName() const final;

  // nested types ----------------------------------------------------

  typedef FtraceStats_Phase Phase;
  static constexpr Phase UNSPECIFIED =
    FtraceStats_Phase_UNSPECIFIED;
  static constexpr Phase START_OF_TRACE =
    FtraceStats_Phase_START_OF_TRACE;
  static constexpr Phase END_OF_TRACE =
    FtraceStats_Phase_END_OF_TRACE;
  static inline bool Phase_IsValid(int value) {
    return FtraceStats_Phase_IsValid(value);
  }
  static constexpr Phase Phase_MIN =
    FtraceStats_Phase_Phase_MIN;
  static constexpr Phase Phase_MAX =
    FtraceStats_Phase_Phase_MAX;
  static constexpr int Phase_ARRAYSIZE =
    FtraceStats_Phase_Phase_ARRAYSIZE;
  template<typename T>
  static inline const std::string& Phase_Name(T enum_t_value) {
    static_assert(::std::is_same<T, Phase>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function Phase_Name.");
    return FtraceStats_Phase_Name(enum_t_value);
  }
  static inline bool Phase_Parse(const std::string& name,
      Phase* value) {
    return FtraceStats_Phase_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kCpuStatsFieldNumber = 2,
    kPhaseFieldNumber = 1,
    kKernelSymbolsParsedFieldNumber = 3,
    kKernelSymbolsMemKbFieldNumber = 4,
  };
  // repeated .perfetto.protos.FtraceCpuStats cpu_stats = 2;
  int cpu_stats_size() const;
  void clear_cpu_stats();
  ::perfetto::protos::FtraceCpuStats* mutable_cpu_stats(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::perfetto::protos::FtraceCpuStats >*
      mutable_cpu_stats();
  const ::perfetto::protos::FtraceCpuStats& cpu_stats(int index) const;
  ::perfetto::protos::FtraceCpuStats* add_cpu_stats();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::perfetto::protos::FtraceCpuStats >&
      cpu_stats() const;

  // optional .perfetto.protos.FtraceStats.Phase phase = 1;
  bool has_phase() const;
  void clear_phase();
  ::perfetto::protos::FtraceStats_Phase phase() const;
  void set_phase(::perfetto::protos::FtraceStats_Phase value);

  // optional uint32 kernel_symbols_parsed = 3;
  bool has_kernel_symbols_parsed() const;
  void clear_kernel_symbols_parsed();
  ::PROTOBUF_NAMESPACE_ID::uint32 kernel_symbols_parsed() const;
  void set_kernel_symbols_parsed(::PROTOBUF_NAMESPACE_ID::uint32 value);

  // optional uint32 kernel_symbols_mem_kb = 4;
  bool has_kernel_symbols_mem_kb() const;
  void clear_kernel_symbols_mem_kb();
  ::PROTOBUF_NAMESPACE_ID::uint32 kernel_symbols_mem_kb() const;
  void set_kernel_symbols_mem_kb(::PROTOBUF_NAMESPACE_ID::uint32 value);

  // @@protoc_insertion_point(class_scope:perfetto.protos.FtraceStats)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::perfetto::protos::FtraceCpuStats > cpu_stats_;
  int phase_;
  ::PROTOBUF_NAMESPACE_ID::uint32 kernel_symbols_parsed_;
  ::PROTOBUF_NAMESPACE_ID::uint32 kernel_symbols_mem_kb_;
  friend struct ::TableStruct_protos_2fperfetto_2ftrace_2fftrace_2fftrace_5fstats_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// FtraceCpuStats

// optional uint64 cpu = 1;
inline bool FtraceCpuStats::has_cpu() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FtraceCpuStats::clear_cpu() {
  cpu_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 FtraceCpuStats::cpu() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceCpuStats.cpu)
  return cpu_;
}
inline void FtraceCpuStats::set_cpu(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000001u;
  cpu_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.FtraceCpuStats.cpu)
}

// optional uint64 entries = 2;
inline bool FtraceCpuStats::has_entries() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void FtraceCpuStats::clear_entries() {
  entries_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 FtraceCpuStats::entries() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceCpuStats.entries)
  return entries_;
}
inline void FtraceCpuStats::set_entries(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000002u;
  entries_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.FtraceCpuStats.entries)
}

// optional uint64 overrun = 3;
inline bool FtraceCpuStats::has_overrun() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void FtraceCpuStats::clear_overrun() {
  overrun_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 FtraceCpuStats::overrun() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceCpuStats.overrun)
  return overrun_;
}
inline void FtraceCpuStats::set_overrun(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000004u;
  overrun_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.FtraceCpuStats.overrun)
}

// optional uint64 commit_overrun = 4;
inline bool FtraceCpuStats::has_commit_overrun() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void FtraceCpuStats::clear_commit_overrun() {
  commit_overrun_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000008u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 FtraceCpuStats::commit_overrun() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceCpuStats.commit_overrun)
  return commit_overrun_;
}
inline void FtraceCpuStats::set_commit_overrun(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000008u;
  commit_overrun_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.FtraceCpuStats.commit_overrun)
}

// optional uint64 bytes_read = 5;
inline bool FtraceCpuStats::has_bytes_read() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void FtraceCpuStats::clear_bytes_read() {
  bytes_read_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000010u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 FtraceCpuStats::bytes_read() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceCpuStats.bytes_read)
  return bytes_read_;
}
inline void FtraceCpuStats::set_bytes_read(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000010u;
  bytes_read_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.FtraceCpuStats.bytes_read)
}

// optional double oldest_event_ts = 6;
inline bool FtraceCpuStats::has_oldest_event_ts() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void FtraceCpuStats::clear_oldest_event_ts() {
  oldest_event_ts_ = 0;
  _has_bits_[0] &= ~0x00000020u;
}
inline double FtraceCpuStats::oldest_event_ts() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceCpuStats.oldest_event_ts)
  return oldest_event_ts_;
}
inline void FtraceCpuStats::set_oldest_event_ts(double value) {
  _has_bits_[0] |= 0x00000020u;
  oldest_event_ts_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.FtraceCpuStats.oldest_event_ts)
}

// optional double now_ts = 7;
inline bool FtraceCpuStats::has_now_ts() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void FtraceCpuStats::clear_now_ts() {
  now_ts_ = 0;
  _has_bits_[0] &= ~0x00000040u;
}
inline double FtraceCpuStats::now_ts() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceCpuStats.now_ts)
  return now_ts_;
}
inline void FtraceCpuStats::set_now_ts(double value) {
  _has_bits_[0] |= 0x00000040u;
  now_ts_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.FtraceCpuStats.now_ts)
}

// optional uint64 dropped_events = 8;
inline bool FtraceCpuStats::has_dropped_events() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void FtraceCpuStats::clear_dropped_events() {
  dropped_events_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000080u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 FtraceCpuStats::dropped_events() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceCpuStats.dropped_events)
  return dropped_events_;
}
inline void FtraceCpuStats::set_dropped_events(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000080u;
  dropped_events_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.FtraceCpuStats.dropped_events)
}

// optional uint64 read_events = 9;
inline bool FtraceCpuStats::has_read_events() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void FtraceCpuStats::clear_read_events() {
  read_events_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000100u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 FtraceCpuStats::read_events() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceCpuStats.read_events)
  return read_events_;
}
inline void FtraceCpuStats::set_read_events(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000100u;
  read_events_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.FtraceCpuStats.read_events)
}

// -------------------------------------------------------------------

// FtraceStats

// optional .perfetto.protos.FtraceStats.Phase phase = 1;
inline bool FtraceStats::has_phase() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FtraceStats::clear_phase() {
  phase_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::perfetto::protos::FtraceStats_Phase FtraceStats::phase() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceStats.phase)
  return static_cast< ::perfetto::protos::FtraceStats_Phase >(phase_);
}
inline void FtraceStats::set_phase(::perfetto::protos::FtraceStats_Phase value) {
  assert(::perfetto::protos::FtraceStats_Phase_IsValid(value));
  _has_bits_[0] |= 0x00000001u;
  phase_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.FtraceStats.phase)
}

// repeated .perfetto.protos.FtraceCpuStats cpu_stats = 2;
inline int FtraceStats::cpu_stats_size() const {
  return cpu_stats_.size();
}
inline void FtraceStats::clear_cpu_stats() {
  cpu_stats_.Clear();
}
inline ::perfetto::protos::FtraceCpuStats* FtraceStats::mutable_cpu_stats(int index) {
  // @@protoc_insertion_point(field_mutable:perfetto.protos.FtraceStats.cpu_stats)
  return cpu_stats_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::perfetto::protos::FtraceCpuStats >*
FtraceStats::mutable_cpu_stats() {
  // @@protoc_insertion_point(field_mutable_list:perfetto.protos.FtraceStats.cpu_stats)
  return &cpu_stats_;
}
inline const ::perfetto::protos::FtraceCpuStats& FtraceStats::cpu_stats(int index) const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceStats.cpu_stats)
  return cpu_stats_.Get(index);
}
inline ::perfetto::protos::FtraceCpuStats* FtraceStats::add_cpu_stats() {
  // @@protoc_insertion_point(field_add:perfetto.protos.FtraceStats.cpu_stats)
  return cpu_stats_.Add();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::perfetto::protos::FtraceCpuStats >&
FtraceStats::cpu_stats() const {
  // @@protoc_insertion_point(field_list:perfetto.protos.FtraceStats.cpu_stats)
  return cpu_stats_;
}

// optional uint32 kernel_symbols_parsed = 3;
inline bool FtraceStats::has_kernel_symbols_parsed() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void FtraceStats::clear_kernel_symbols_parsed() {
  kernel_symbols_parsed_ = 0u;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 FtraceStats::kernel_symbols_parsed() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceStats.kernel_symbols_parsed)
  return kernel_symbols_parsed_;
}
inline void FtraceStats::set_kernel_symbols_parsed(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000002u;
  kernel_symbols_parsed_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.FtraceStats.kernel_symbols_parsed)
}

// optional uint32 kernel_symbols_mem_kb = 4;
inline bool FtraceStats::has_kernel_symbols_mem_kb() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void FtraceStats::clear_kernel_symbols_mem_kb() {
  kernel_symbols_mem_kb_ = 0u;
  _has_bits_[0] &= ~0x00000004u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 FtraceStats::kernel_symbols_mem_kb() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.FtraceStats.kernel_symbols_mem_kb)
  return kernel_symbols_mem_kb_;
}
inline void FtraceStats::set_kernel_symbols_mem_kb(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000004u;
  kernel_symbols_mem_kb_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.FtraceStats.kernel_symbols_mem_kb)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace protos
}  // namespace perfetto

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::perfetto::protos::FtraceStats_Phase> : ::std::true_type {};

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2fftrace_2fftrace_5fstats_2eproto