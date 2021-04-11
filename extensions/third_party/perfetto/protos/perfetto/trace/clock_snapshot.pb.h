// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/trace/clock_snapshot.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto

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
#include "protos/perfetto/common/builtin_clock.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto {
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
class ClockSnapshot;
class ClockSnapshotDefaultTypeInternal;
extern ClockSnapshotDefaultTypeInternal _ClockSnapshot_default_instance_;
class ClockSnapshot_Clock;
class ClockSnapshot_ClockDefaultTypeInternal;
extern ClockSnapshot_ClockDefaultTypeInternal _ClockSnapshot_Clock_default_instance_;
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> ::perfetto::protos::ClockSnapshot* Arena::CreateMaybeMessage<::perfetto::protos::ClockSnapshot>(Arena*);
template<> ::perfetto::protos::ClockSnapshot_Clock* Arena::CreateMaybeMessage<::perfetto::protos::ClockSnapshot_Clock>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace perfetto {
namespace protos {

enum ClockSnapshot_Clock_BuiltinClocks : int {
  ClockSnapshot_Clock_BuiltinClocks_UNKNOWN = 0,
  ClockSnapshot_Clock_BuiltinClocks_REALTIME = 1,
  ClockSnapshot_Clock_BuiltinClocks_REALTIME_COARSE = 2,
  ClockSnapshot_Clock_BuiltinClocks_MONOTONIC = 3,
  ClockSnapshot_Clock_BuiltinClocks_MONOTONIC_COARSE = 4,
  ClockSnapshot_Clock_BuiltinClocks_MONOTONIC_RAW = 5,
  ClockSnapshot_Clock_BuiltinClocks_BOOTTIME = 6,
  ClockSnapshot_Clock_BuiltinClocks_BUILTIN_CLOCK_MAX_ID = 63
};
bool ClockSnapshot_Clock_BuiltinClocks_IsValid(int value);
constexpr ClockSnapshot_Clock_BuiltinClocks ClockSnapshot_Clock_BuiltinClocks_BuiltinClocks_MIN = ClockSnapshot_Clock_BuiltinClocks_UNKNOWN;
constexpr ClockSnapshot_Clock_BuiltinClocks ClockSnapshot_Clock_BuiltinClocks_BuiltinClocks_MAX = ClockSnapshot_Clock_BuiltinClocks_BUILTIN_CLOCK_MAX_ID;
constexpr int ClockSnapshot_Clock_BuiltinClocks_BuiltinClocks_ARRAYSIZE = ClockSnapshot_Clock_BuiltinClocks_BuiltinClocks_MAX + 1;

const std::string& ClockSnapshot_Clock_BuiltinClocks_Name(ClockSnapshot_Clock_BuiltinClocks value);
template<typename T>
inline const std::string& ClockSnapshot_Clock_BuiltinClocks_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ClockSnapshot_Clock_BuiltinClocks>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ClockSnapshot_Clock_BuiltinClocks_Name.");
  return ClockSnapshot_Clock_BuiltinClocks_Name(static_cast<ClockSnapshot_Clock_BuiltinClocks>(enum_t_value));
}
bool ClockSnapshot_Clock_BuiltinClocks_Parse(
    const std::string& name, ClockSnapshot_Clock_BuiltinClocks* value);
// ===================================================================

class ClockSnapshot_Clock :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:perfetto.protos.ClockSnapshot.Clock) */ {
 public:
  ClockSnapshot_Clock();
  virtual ~ClockSnapshot_Clock();

  ClockSnapshot_Clock(const ClockSnapshot_Clock& from);
  ClockSnapshot_Clock(ClockSnapshot_Clock&& from) noexcept
    : ClockSnapshot_Clock() {
    *this = ::std::move(from);
  }

  inline ClockSnapshot_Clock& operator=(const ClockSnapshot_Clock& from) {
    CopyFrom(from);
    return *this;
  }
  inline ClockSnapshot_Clock& operator=(ClockSnapshot_Clock&& from) noexcept {
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

  static const ClockSnapshot_Clock& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ClockSnapshot_Clock* internal_default_instance() {
    return reinterpret_cast<const ClockSnapshot_Clock*>(
               &_ClockSnapshot_Clock_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ClockSnapshot_Clock& a, ClockSnapshot_Clock& b) {
    a.Swap(&b);
  }
  inline void Swap(ClockSnapshot_Clock* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ClockSnapshot_Clock* New() const final {
    return CreateMaybeMessage<ClockSnapshot_Clock>(nullptr);
  }

  ClockSnapshot_Clock* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ClockSnapshot_Clock>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)
    final;
  void CopyFrom(const ClockSnapshot_Clock& from);
  void MergeFrom(const ClockSnapshot_Clock& from);
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
  void InternalSwap(ClockSnapshot_Clock* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "perfetto.protos.ClockSnapshot.Clock";
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

  typedef ClockSnapshot_Clock_BuiltinClocks BuiltinClocks;
  static constexpr BuiltinClocks UNKNOWN =
    ClockSnapshot_Clock_BuiltinClocks_UNKNOWN;
  static constexpr BuiltinClocks REALTIME =
    ClockSnapshot_Clock_BuiltinClocks_REALTIME;
  static constexpr BuiltinClocks REALTIME_COARSE =
    ClockSnapshot_Clock_BuiltinClocks_REALTIME_COARSE;
  static constexpr BuiltinClocks MONOTONIC =
    ClockSnapshot_Clock_BuiltinClocks_MONOTONIC;
  static constexpr BuiltinClocks MONOTONIC_COARSE =
    ClockSnapshot_Clock_BuiltinClocks_MONOTONIC_COARSE;
  static constexpr BuiltinClocks MONOTONIC_RAW =
    ClockSnapshot_Clock_BuiltinClocks_MONOTONIC_RAW;
  static constexpr BuiltinClocks BOOTTIME =
    ClockSnapshot_Clock_BuiltinClocks_BOOTTIME;
  static constexpr BuiltinClocks BUILTIN_CLOCK_MAX_ID =
    ClockSnapshot_Clock_BuiltinClocks_BUILTIN_CLOCK_MAX_ID;
  static inline bool BuiltinClocks_IsValid(int value) {
    return ClockSnapshot_Clock_BuiltinClocks_IsValid(value);
  }
  static constexpr BuiltinClocks BuiltinClocks_MIN =
    ClockSnapshot_Clock_BuiltinClocks_BuiltinClocks_MIN;
  static constexpr BuiltinClocks BuiltinClocks_MAX =
    ClockSnapshot_Clock_BuiltinClocks_BuiltinClocks_MAX;
  static constexpr int BuiltinClocks_ARRAYSIZE =
    ClockSnapshot_Clock_BuiltinClocks_BuiltinClocks_ARRAYSIZE;
  template<typename T>
  static inline const std::string& BuiltinClocks_Name(T enum_t_value) {
    static_assert(::std::is_same<T, BuiltinClocks>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function BuiltinClocks_Name.");
    return ClockSnapshot_Clock_BuiltinClocks_Name(enum_t_value);
  }
  static inline bool BuiltinClocks_Parse(const std::string& name,
      BuiltinClocks* value) {
    return ClockSnapshot_Clock_BuiltinClocks_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kTimestampFieldNumber = 2,
    kClockIdFieldNumber = 1,
    kIsIncrementalFieldNumber = 3,
    kUnitMultiplierNsFieldNumber = 4,
  };
  // optional uint64 timestamp = 2;
  bool has_timestamp() const;
  void clear_timestamp();
  ::PROTOBUF_NAMESPACE_ID::uint64 timestamp() const;
  void set_timestamp(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // optional uint32 clock_id = 1;
  bool has_clock_id() const;
  void clear_clock_id();
  ::PROTOBUF_NAMESPACE_ID::uint32 clock_id() const;
  void set_clock_id(::PROTOBUF_NAMESPACE_ID::uint32 value);

  // optional bool is_incremental = 3;
  bool has_is_incremental() const;
  void clear_is_incremental();
  bool is_incremental() const;
  void set_is_incremental(bool value);

  // optional uint64 unit_multiplier_ns = 4;
  bool has_unit_multiplier_ns() const;
  void clear_unit_multiplier_ns();
  ::PROTOBUF_NAMESPACE_ID::uint64 unit_multiplier_ns() const;
  void set_unit_multiplier_ns(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // @@protoc_insertion_point(class_scope:perfetto.protos.ClockSnapshot.Clock)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::uint64 timestamp_;
  ::PROTOBUF_NAMESPACE_ID::uint32 clock_id_;
  bool is_incremental_;
  ::PROTOBUF_NAMESPACE_ID::uint64 unit_multiplier_ns_;
  friend struct ::TableStruct_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto;
};
// -------------------------------------------------------------------

class ClockSnapshot :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:perfetto.protos.ClockSnapshot) */ {
 public:
  ClockSnapshot();
  virtual ~ClockSnapshot();

  ClockSnapshot(const ClockSnapshot& from);
  ClockSnapshot(ClockSnapshot&& from) noexcept
    : ClockSnapshot() {
    *this = ::std::move(from);
  }

  inline ClockSnapshot& operator=(const ClockSnapshot& from) {
    CopyFrom(from);
    return *this;
  }
  inline ClockSnapshot& operator=(ClockSnapshot&& from) noexcept {
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

  static const ClockSnapshot& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ClockSnapshot* internal_default_instance() {
    return reinterpret_cast<const ClockSnapshot*>(
               &_ClockSnapshot_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(ClockSnapshot& a, ClockSnapshot& b) {
    a.Swap(&b);
  }
  inline void Swap(ClockSnapshot* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ClockSnapshot* New() const final {
    return CreateMaybeMessage<ClockSnapshot>(nullptr);
  }

  ClockSnapshot* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ClockSnapshot>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)
    final;
  void CopyFrom(const ClockSnapshot& from);
  void MergeFrom(const ClockSnapshot& from);
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
  void InternalSwap(ClockSnapshot* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "perfetto.protos.ClockSnapshot";
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

  typedef ClockSnapshot_Clock Clock;

  // accessors -------------------------------------------------------

  enum : int {
    kClocksFieldNumber = 1,
    kPrimaryTraceClockFieldNumber = 2,
  };
  // repeated .perfetto.protos.ClockSnapshot.Clock clocks = 1;
  int clocks_size() const;
  void clear_clocks();
  ::perfetto::protos::ClockSnapshot_Clock* mutable_clocks(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::perfetto::protos::ClockSnapshot_Clock >*
      mutable_clocks();
  const ::perfetto::protos::ClockSnapshot_Clock& clocks(int index) const;
  ::perfetto::protos::ClockSnapshot_Clock* add_clocks();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::perfetto::protos::ClockSnapshot_Clock >&
      clocks() const;

  // optional .perfetto.protos.BuiltinClock primary_trace_clock = 2;
  bool has_primary_trace_clock() const;
  void clear_primary_trace_clock();
  ::perfetto::protos::BuiltinClock primary_trace_clock() const;
  void set_primary_trace_clock(::perfetto::protos::BuiltinClock value);

  // @@protoc_insertion_point(class_scope:perfetto.protos.ClockSnapshot)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::perfetto::protos::ClockSnapshot_Clock > clocks_;
  int primary_trace_clock_;
  friend struct ::TableStruct_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ClockSnapshot_Clock

// optional uint32 clock_id = 1;
inline bool ClockSnapshot_Clock::has_clock_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ClockSnapshot_Clock::clear_clock_id() {
  clock_id_ = 0u;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 ClockSnapshot_Clock::clock_id() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ClockSnapshot.Clock.clock_id)
  return clock_id_;
}
inline void ClockSnapshot_Clock::set_clock_id(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _has_bits_[0] |= 0x00000002u;
  clock_id_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ClockSnapshot.Clock.clock_id)
}

// optional uint64 timestamp = 2;
inline bool ClockSnapshot_Clock::has_timestamp() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ClockSnapshot_Clock::clear_timestamp() {
  timestamp_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 ClockSnapshot_Clock::timestamp() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ClockSnapshot.Clock.timestamp)
  return timestamp_;
}
inline void ClockSnapshot_Clock::set_timestamp(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000001u;
  timestamp_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ClockSnapshot.Clock.timestamp)
}

// optional bool is_incremental = 3;
inline bool ClockSnapshot_Clock::has_is_incremental() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ClockSnapshot_Clock::clear_is_incremental() {
  is_incremental_ = false;
  _has_bits_[0] &= ~0x00000004u;
}
inline bool ClockSnapshot_Clock::is_incremental() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ClockSnapshot.Clock.is_incremental)
  return is_incremental_;
}
inline void ClockSnapshot_Clock::set_is_incremental(bool value) {
  _has_bits_[0] |= 0x00000004u;
  is_incremental_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ClockSnapshot.Clock.is_incremental)
}

// optional uint64 unit_multiplier_ns = 4;
inline bool ClockSnapshot_Clock::has_unit_multiplier_ns() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ClockSnapshot_Clock::clear_unit_multiplier_ns() {
  unit_multiplier_ns_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000008u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 ClockSnapshot_Clock::unit_multiplier_ns() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ClockSnapshot.Clock.unit_multiplier_ns)
  return unit_multiplier_ns_;
}
inline void ClockSnapshot_Clock::set_unit_multiplier_ns(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000008u;
  unit_multiplier_ns_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ClockSnapshot.Clock.unit_multiplier_ns)
}

// -------------------------------------------------------------------

// ClockSnapshot

// repeated .perfetto.protos.ClockSnapshot.Clock clocks = 1;
inline int ClockSnapshot::clocks_size() const {
  return clocks_.size();
}
inline void ClockSnapshot::clear_clocks() {
  clocks_.Clear();
}
inline ::perfetto::protos::ClockSnapshot_Clock* ClockSnapshot::mutable_clocks(int index) {
  // @@protoc_insertion_point(field_mutable:perfetto.protos.ClockSnapshot.clocks)
  return clocks_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::perfetto::protos::ClockSnapshot_Clock >*
ClockSnapshot::mutable_clocks() {
  // @@protoc_insertion_point(field_mutable_list:perfetto.protos.ClockSnapshot.clocks)
  return &clocks_;
}
inline const ::perfetto::protos::ClockSnapshot_Clock& ClockSnapshot::clocks(int index) const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ClockSnapshot.clocks)
  return clocks_.Get(index);
}
inline ::perfetto::protos::ClockSnapshot_Clock* ClockSnapshot::add_clocks() {
  // @@protoc_insertion_point(field_add:perfetto.protos.ClockSnapshot.clocks)
  return clocks_.Add();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::perfetto::protos::ClockSnapshot_Clock >&
ClockSnapshot::clocks() const {
  // @@protoc_insertion_point(field_list:perfetto.protos.ClockSnapshot.clocks)
  return clocks_;
}

// optional .perfetto.protos.BuiltinClock primary_trace_clock = 2;
inline bool ClockSnapshot::has_primary_trace_clock() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ClockSnapshot::clear_primary_trace_clock() {
  primary_trace_clock_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::perfetto::protos::BuiltinClock ClockSnapshot::primary_trace_clock() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.ClockSnapshot.primary_trace_clock)
  return static_cast< ::perfetto::protos::BuiltinClock >(primary_trace_clock_);
}
inline void ClockSnapshot::set_primary_trace_clock(::perfetto::protos::BuiltinClock value) {
  assert(::perfetto::protos::BuiltinClock_IsValid(value));
  _has_bits_[0] |= 0x00000001u;
  primary_trace_clock_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.ClockSnapshot.primary_trace_clock)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace protos
}  // namespace perfetto

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::perfetto::protos::ClockSnapshot_Clock_BuiltinClocks> : ::std::true_type {};

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto