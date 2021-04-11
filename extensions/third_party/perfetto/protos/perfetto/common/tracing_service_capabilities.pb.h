// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/common/tracing_service_capabilities.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2fcommon_2ftracing_5fservice_5fcapabilities_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2fcommon_2ftracing_5fservice_5fcapabilities_2eproto

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
#include "protos/perfetto/common/observable_events.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_protos_2fperfetto_2fcommon_2ftracing_5fservice_5fcapabilities_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_protos_2fperfetto_2fcommon_2ftracing_5fservice_5fcapabilities_2eproto {
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
class TracingServiceCapabilities;
class TracingServiceCapabilitiesDefaultTypeInternal;
extern TracingServiceCapabilitiesDefaultTypeInternal _TracingServiceCapabilities_default_instance_;
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> ::perfetto::protos::TracingServiceCapabilities* Arena::CreateMaybeMessage<::perfetto::protos::TracingServiceCapabilities>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace perfetto {
namespace protos {

// ===================================================================

class TracingServiceCapabilities :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:perfetto.protos.TracingServiceCapabilities) */ {
 public:
  TracingServiceCapabilities();
  virtual ~TracingServiceCapabilities();

  TracingServiceCapabilities(const TracingServiceCapabilities& from);
  TracingServiceCapabilities(TracingServiceCapabilities&& from) noexcept
    : TracingServiceCapabilities() {
    *this = ::std::move(from);
  }

  inline TracingServiceCapabilities& operator=(const TracingServiceCapabilities& from) {
    CopyFrom(from);
    return *this;
  }
  inline TracingServiceCapabilities& operator=(TracingServiceCapabilities&& from) noexcept {
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

  static const TracingServiceCapabilities& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const TracingServiceCapabilities* internal_default_instance() {
    return reinterpret_cast<const TracingServiceCapabilities*>(
               &_TracingServiceCapabilities_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(TracingServiceCapabilities& a, TracingServiceCapabilities& b) {
    a.Swap(&b);
  }
  inline void Swap(TracingServiceCapabilities* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline TracingServiceCapabilities* New() const final {
    return CreateMaybeMessage<TracingServiceCapabilities>(nullptr);
  }

  TracingServiceCapabilities* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<TracingServiceCapabilities>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)
    final;
  void CopyFrom(const TracingServiceCapabilities& from);
  void MergeFrom(const TracingServiceCapabilities& from);
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
  void InternalSwap(TracingServiceCapabilities* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "perfetto.protos.TracingServiceCapabilities";
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
    kObservableEventsFieldNumber = 2,
    kHasQueryCapabilitiesFieldNumber = 1,
    kHasTraceConfigOutputPathFieldNumber = 3,
  };
  // repeated .perfetto.protos.ObservableEvents.Type observable_events = 2;
  int observable_events_size() const;
  void clear_observable_events();
  ::perfetto::protos::ObservableEvents_Type observable_events(int index) const;
  void set_observable_events(int index, ::perfetto::protos::ObservableEvents_Type value);
  void add_observable_events(::perfetto::protos::ObservableEvents_Type value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>& observable_events() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>* mutable_observable_events();

  // optional bool has_query_capabilities = 1;
  bool has_has_query_capabilities() const;
  void clear_has_query_capabilities();
  bool has_query_capabilities() const;
  void set_has_query_capabilities(bool value);

  // optional bool has_trace_config_output_path = 3;
  bool has_has_trace_config_output_path() const;
  void clear_has_trace_config_output_path();
  bool has_trace_config_output_path() const;
  void set_has_trace_config_output_path(bool value);

  // @@protoc_insertion_point(class_scope:perfetto.protos.TracingServiceCapabilities)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<int> observable_events_;
  bool has_query_capabilities_;
  bool has_trace_config_output_path_;
  friend struct ::TableStruct_protos_2fperfetto_2fcommon_2ftracing_5fservice_5fcapabilities_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// TracingServiceCapabilities

// optional bool has_query_capabilities = 1;
inline bool TracingServiceCapabilities::has_has_query_capabilities() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TracingServiceCapabilities::clear_has_query_capabilities() {
  has_query_capabilities_ = false;
  _has_bits_[0] &= ~0x00000001u;
}
inline bool TracingServiceCapabilities::has_query_capabilities() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.TracingServiceCapabilities.has_query_capabilities)
  return has_query_capabilities_;
}
inline void TracingServiceCapabilities::set_has_query_capabilities(bool value) {
  _has_bits_[0] |= 0x00000001u;
  has_query_capabilities_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.TracingServiceCapabilities.has_query_capabilities)
}

// repeated .perfetto.protos.ObservableEvents.Type observable_events = 2;
inline int TracingServiceCapabilities::observable_events_size() const {
  return observable_events_.size();
}
inline void TracingServiceCapabilities::clear_observable_events() {
  observable_events_.Clear();
}
inline ::perfetto::protos::ObservableEvents_Type TracingServiceCapabilities::observable_events(int index) const {
  // @@protoc_insertion_point(field_get:perfetto.protos.TracingServiceCapabilities.observable_events)
  return static_cast< ::perfetto::protos::ObservableEvents_Type >(observable_events_.Get(index));
}
inline void TracingServiceCapabilities::set_observable_events(int index, ::perfetto::protos::ObservableEvents_Type value) {
  assert(::perfetto::protos::ObservableEvents_Type_IsValid(value));
  observable_events_.Set(index, value);
  // @@protoc_insertion_point(field_set:perfetto.protos.TracingServiceCapabilities.observable_events)
}
inline void TracingServiceCapabilities::add_observable_events(::perfetto::protos::ObservableEvents_Type value) {
  assert(::perfetto::protos::ObservableEvents_Type_IsValid(value));
  observable_events_.Add(value);
  // @@protoc_insertion_point(field_add:perfetto.protos.TracingServiceCapabilities.observable_events)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>&
TracingServiceCapabilities::observable_events() const {
  // @@protoc_insertion_point(field_list:perfetto.protos.TracingServiceCapabilities.observable_events)
  return observable_events_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField<int>*
TracingServiceCapabilities::mutable_observable_events() {
  // @@protoc_insertion_point(field_mutable_list:perfetto.protos.TracingServiceCapabilities.observable_events)
  return &observable_events_;
}

// optional bool has_trace_config_output_path = 3;
inline bool TracingServiceCapabilities::has_has_trace_config_output_path() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TracingServiceCapabilities::clear_has_trace_config_output_path() {
  has_trace_config_output_path_ = false;
  _has_bits_[0] &= ~0x00000002u;
}
inline bool TracingServiceCapabilities::has_trace_config_output_path() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.TracingServiceCapabilities.has_trace_config_output_path)
  return has_trace_config_output_path_;
}
inline void TracingServiceCapabilities::set_has_trace_config_output_path(bool value) {
  _has_bits_[0] |= 0x00000002u;
  has_trace_config_output_path_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.TracingServiceCapabilities.has_trace_config_output_path)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protos
}  // namespace perfetto

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2fcommon_2ftracing_5fservice_5fcapabilities_2eproto