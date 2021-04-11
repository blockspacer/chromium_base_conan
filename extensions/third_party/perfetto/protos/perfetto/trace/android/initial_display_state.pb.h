// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/trace/android/initial_display_state.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2fandroid_2finitial_5fdisplay_5fstate_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2fandroid_2finitial_5fdisplay_5fstate_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_protos_2fperfetto_2ftrace_2fandroid_2finitial_5fdisplay_5fstate_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_protos_2fperfetto_2ftrace_2fandroid_2finitial_5fdisplay_5fstate_2eproto {
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
class InitialDisplayState;
class InitialDisplayStateDefaultTypeInternal;
extern InitialDisplayStateDefaultTypeInternal _InitialDisplayState_default_instance_;
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> ::perfetto::protos::InitialDisplayState* Arena::CreateMaybeMessage<::perfetto::protos::InitialDisplayState>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace perfetto {
namespace protos {

// ===================================================================

class InitialDisplayState :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:perfetto.protos.InitialDisplayState) */ {
 public:
  InitialDisplayState();
  virtual ~InitialDisplayState();

  InitialDisplayState(const InitialDisplayState& from);
  InitialDisplayState(InitialDisplayState&& from) noexcept
    : InitialDisplayState() {
    *this = ::std::move(from);
  }

  inline InitialDisplayState& operator=(const InitialDisplayState& from) {
    CopyFrom(from);
    return *this;
  }
  inline InitialDisplayState& operator=(InitialDisplayState&& from) noexcept {
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

  static const InitialDisplayState& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const InitialDisplayState* internal_default_instance() {
    return reinterpret_cast<const InitialDisplayState*>(
               &_InitialDisplayState_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(InitialDisplayState& a, InitialDisplayState& b) {
    a.Swap(&b);
  }
  inline void Swap(InitialDisplayState* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline InitialDisplayState* New() const final {
    return CreateMaybeMessage<InitialDisplayState>(nullptr);
  }

  InitialDisplayState* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<InitialDisplayState>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)
    final;
  void CopyFrom(const InitialDisplayState& from);
  void MergeFrom(const InitialDisplayState& from);
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
  void InternalSwap(InitialDisplayState* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "perfetto.protos.InitialDisplayState";
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
    kBrightnessFieldNumber = 2,
    kDisplayStateFieldNumber = 1,
  };
  // optional double brightness = 2;
  bool has_brightness() const;
  void clear_brightness();
  double brightness() const;
  void set_brightness(double value);

  // optional int32 display_state = 1;
  bool has_display_state() const;
  void clear_display_state();
  ::PROTOBUF_NAMESPACE_ID::int32 display_state() const;
  void set_display_state(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:perfetto.protos.InitialDisplayState)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  double brightness_;
  ::PROTOBUF_NAMESPACE_ID::int32 display_state_;
  friend struct ::TableStruct_protos_2fperfetto_2ftrace_2fandroid_2finitial_5fdisplay_5fstate_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// InitialDisplayState

// optional int32 display_state = 1;
inline bool InitialDisplayState::has_display_state() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void InitialDisplayState::clear_display_state() {
  display_state_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 InitialDisplayState::display_state() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.InitialDisplayState.display_state)
  return display_state_;
}
inline void InitialDisplayState::set_display_state(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000002u;
  display_state_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.InitialDisplayState.display_state)
}

// optional double brightness = 2;
inline bool InitialDisplayState::has_brightness() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void InitialDisplayState::clear_brightness() {
  brightness_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline double InitialDisplayState::brightness() const {
  // @@protoc_insertion_point(field_get:perfetto.protos.InitialDisplayState.brightness)
  return brightness_;
}
inline void InitialDisplayState::set_brightness(double value) {
  _has_bits_[0] |= 0x00000001u;
  brightness_ = value;
  // @@protoc_insertion_point(field_set:perfetto.protos.InitialDisplayState.brightness)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protos
}  // namespace perfetto

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_protos_2fperfetto_2ftrace_2fandroid_2finitial_5fdisplay_5fstate_2eproto