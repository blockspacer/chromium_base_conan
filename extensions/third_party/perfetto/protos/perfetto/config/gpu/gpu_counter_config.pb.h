// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/config/gpu/gpu_counter_config.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2fconfig_2fgpu_2fgpu_5fcounter_5fconfig_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2fconfig_2fgpu_2fgpu_5fcounter_5fconfig_2eproto

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
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_protos_2fperfetto_2fconfig_2fgpu_2fgpu_5fcounter_5fconfig_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_protos_2fperfetto_2fconfig_2fgpu_2fgpu_5fcounter_5fconfig_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
namespace perfetto {
namespace protos {
class GpuCounterConfig;
class GpuCounterConfigDefaultTypeInternal;
extern GpuCounterConfigDefaultTypeInternal _GpuCounterConfig_default_instance_;
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> ::perfetto::protos::GpuCounterConfig* Arena::CreateMaybeMessage<::perfetto::protos::GpuCounterConfig>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace perfetto {
namespace protos {

// ===================================================================

class GpuCounterConfig :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:perfetto.protos.GpuCounterConfig) */ {
 public:
  GpuCounterConfig();
  virtual ~GpuCounterConfig();

  GpuCounterConfig(const GpuCounterConfig& from);
  GpuCounterConfig(GpuCounterConfig&& from) noexcept
    : GpuCounterConfig() {
    *this = ::std::move(from);
  }

  inline GpuCounterConfig& operator=(const GpuCounterConfig& from) {
    CopyFrom(from);
    return *this;
  }
  inline GpuCounterConfig& operator=(GpuCounterConfig&& from) noexcept {
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

  static const GpuCounterConfig& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GpuCounterConfig* internal_default_instance() {
    return reinterpret_cast<const GpuCounterConfig*>(
               &_GpuCounterConfig_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(GpuCounterConfig& a, GpuCounterConfig& b) {
    a.Swap(&b);
  }
  inline void Swap(GpuCounterConfig* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline GpuCounterConfig* New() const final {
    return CreateMaybeMessage<GpuCounterConfig>(nullptr);
  }

  GpuCounterConfig* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<GpuCounterConfig>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)
    final;
  void CopyFrom(const GpuCounterConfig& from);
  void MergeFrom(const GpuCounterConfig& from);
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
  void InternalSwap(GpuCounterConfig* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "perfetto.protos.GpuCounterConfig";
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
    kCounterIdsFieldNumber = 2,
    kCounterPeriodNsFieldNumber = 1,
    kInstrumentedSamplingFieldNumber = 3,
    kFixGpuClockFieldNumber = 4,
  };
  // repeated uint32 counter_ids = 2;
  int counter_ids_size() const;
  void clear_counter_ids();
  ::PROTOBUF_NAMESPACE_ID::uint32 counter_ids(int index) const;
  void set_counter_ids(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value);
  void add_counter_ids(::PROTOBUF_NAMESPACE_ID::uint32 value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
      counter_ids() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
      mutable_counter_ids();

  // optional uint64 counter_period_ns = 1;
  bool has_counter_period_ns() const;
  void clear_counter_period_ns();
  ::PROTOBUF_NAMESPACE_ID::uint64 counter_period_ns() const;
  void set_counter_period_ns(::PROTOBUF_NAMESPACE_ID::uint64 value);

  // optional bool instrumented_sampling = 3;
  bool has_instrumented_sampling() const;
  void clear_instrumented_sampling();
  bool instrumented_sampling() const;
  void set_instrumented_sampling(bool value);

  // optional bool fix_gpu_clock = 4;
  bool has_fix_gpu_clock() const;
  void clear_fix_gpu_clock();
  bool fix_gpu_clock() const;
  void set_fix_gpu_clock(bool value);

  // @@protoc_insertion_point(class_scope:perfetto.protos.GpuCounterConfig)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 > counter_ids_;
  ::PROTOBUF_NAMESPACE_ID::uint64 counter_period_ns_;
  bool instrumented_sampling_;
  bool fix_gpu_clock_;
  friend struct ::TableStruct_protos_2fperfetto_2fconfig_2fgpu_2fgpu_5fcounter_5fconfig_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// GpuCounterConfig

// optional uint64 counter_period_ns = 1;
inline bool GpuCounterConfig::has_counter_period_ns() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GpuCounterConfig::clear_counter_period_ns() {
  counter_period_ns_ = PROTOBUF_ULONGLONG(0);
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 GpuCounterConfig::counter_period_ns() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.GpuCounterConfig.counter_period_ns)
  return counter_period_ns_;
}
inline void GpuCounterConfig::set_counter_period_ns(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _has_bits_[0] |= 0x00000001u;
  counter_period_ns_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.GpuCounterConfig.counter_period_ns)
}

// repeated uint32 counter_ids = 2;
inline int GpuCounterConfig::counter_ids_size() const {
  return counter_ids_.size();
}
inline void GpuCounterConfig::clear_counter_ids() {
  counter_ids_.Clear();
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 GpuCounterConfig::counter_ids(int index) const {
  // @@protoc_insertion_point(field_get:perfetto.protos.GpuCounterConfig.counter_ids)
  return counter_ids_.Get(index);
}
inline void GpuCounterConfig::set_counter_ids(int index, ::PROTOBUF_NAMESPACE_ID::uint32 value) {
  counter_ids_.Set(index, value);
  // @@protoc_insertion_point(field_set:perfetto.protos.GpuCounterConfig.counter_ids)
}
inline void GpuCounterConfig::add_counter_ids(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  counter_ids_.Add(value);
  // @@protoc_insertion_point(field_add:perfetto.protos.GpuCounterConfig.counter_ids)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >&
GpuCounterConfig::counter_ids() const {
  // @@protoc_insertion_point(field_list:perfetto.protos.GpuCounterConfig.counter_ids)
  return counter_ids_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< ::PROTOBUF_NAMESPACE_ID::uint32 >*
GpuCounterConfig::mutable_counter_ids() {
  // @@protoc_insertion_point(field_mutable_list:perfetto.protos.GpuCounterConfig.counter_ids)
  return &counter_ids_;
}

// optional bool instrumented_sampling = 3;
inline bool GpuCounterConfig::has_instrumented_sampling() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void GpuCounterConfig::clear_instrumented_sampling() {
  instrumented_sampling_ = false;
  _has_bits_[0] &= ~0x00000002u;
}
inline bool GpuCounterConfig::instrumented_sampling() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.GpuCounterConfig.instrumented_sampling)
  return instrumented_sampling_;
}
inline void GpuCounterConfig::set_instrumented_sampling(bool value) {
  _has_bits_[0] |= 0x00000002u;
  instrumented_sampling_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.GpuCounterConfig.instrumented_sampling)
}

// optional bool fix_gpu_clock = 4;
inline bool GpuCounterConfig::has_fix_gpu_clock() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void GpuCounterConfig::clear_fix_gpu_clock() {
  fix_gpu_clock_ = false;
  _has_bits_[0] &= ~0x00000004u;
}
inline bool GpuCounterConfig::fix_gpu_clock() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.GpuCounterConfig.fix_gpu_clock)
  return fix_gpu_clock_;
}
inline void GpuCounterConfig::set_fix_gpu_clock(bool value) {
  _has_bits_[0] |= 0x00000004u;
  fix_gpu_clock_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.GpuCounterConfig.fix_gpu_clock)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protos
}  // namespace perfetto

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2fconfig_2fgpu_2fgpu_5fcounter_5fconfig_2eproto