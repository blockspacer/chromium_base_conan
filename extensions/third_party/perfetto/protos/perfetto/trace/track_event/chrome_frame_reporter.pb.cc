// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/trace/track_event/chrome_frame_reporter.proto

#include "protos/perfetto/trace/track_event/chrome_frame_reporter.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace perfetto {
namespace protos {
class ChromeFrameReporterDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ChromeFrameReporter> _instance;
} _ChromeFrameReporter_default_instance_;
}  // namespace protos
}  // namespace perfetto
static void InitDefaultsscc_info_ChromeFrameReporter_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fframe_5freporter_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::perfetto::protos::_ChromeFrameReporter_default_instance_;
    new (ptr) ::perfetto::protos::ChromeFrameReporter();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::perfetto::protos::ChromeFrameReporter::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ChromeFrameReporter_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fframe_5freporter_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_ChromeFrameReporter_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fframe_5freporter_2eproto}, {}};

namespace perfetto {
namespace protos {
bool ChromeFrameReporter_State_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

static ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<std::string> ChromeFrameReporter_State_strings[4] = {};

static const char ChromeFrameReporter_State_names[] =
  "STATE_DROPPED"
  "STATE_NO_UPDATE_DESIRED"
  "STATE_PRESENTED_ALL"
  "STATE_PRESENTED_PARTIAL";

static const ::PROTOBUF_NAMESPACE_ID::internal::EnumEntry ChromeFrameReporter_State_entries[] = {
  { {ChromeFrameReporter_State_names + 0, 13}, 3 },
  { {ChromeFrameReporter_State_names + 13, 23}, 0 },
  { {ChromeFrameReporter_State_names + 36, 19}, 1 },
  { {ChromeFrameReporter_State_names + 55, 23}, 2 },
};

static const int ChromeFrameReporter_State_entries_by_number[] = {
  1, // 0 -> STATE_NO_UPDATE_DESIRED
  2, // 1 -> STATE_PRESENTED_ALL
  3, // 2 -> STATE_PRESENTED_PARTIAL
  0, // 3 -> STATE_DROPPED
};

const std::string& ChromeFrameReporter_State_Name(
    ChromeFrameReporter_State value) {
  static const bool dummy =
      ::PROTOBUF_NAMESPACE_ID::internal::InitializeEnumStrings(
          ChromeFrameReporter_State_entries,
          ChromeFrameReporter_State_entries_by_number,
          4, ChromeFrameReporter_State_strings);
  (void) dummy;
  int idx = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumName(
      ChromeFrameReporter_State_entries,
      ChromeFrameReporter_State_entries_by_number,
      4, value);
  return idx == -1 ? ::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString() :
                     ChromeFrameReporter_State_strings[idx].get();
}
bool ChromeFrameReporter_State_Parse(
    const std::string& name, ChromeFrameReporter_State* value) {
  int int_value;
  bool success = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumValue(
      ChromeFrameReporter_State_entries, 4, name, &int_value);
  if (success) {
    *value = static_cast<ChromeFrameReporter_State>(int_value);
  }
  return success;
}
#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr ChromeFrameReporter_State ChromeFrameReporter::STATE_NO_UPDATE_DESIRED;
constexpr ChromeFrameReporter_State ChromeFrameReporter::STATE_PRESENTED_ALL;
constexpr ChromeFrameReporter_State ChromeFrameReporter::STATE_PRESENTED_PARTIAL;
constexpr ChromeFrameReporter_State ChromeFrameReporter::STATE_DROPPED;
constexpr ChromeFrameReporter_State ChromeFrameReporter::State_MIN;
constexpr ChromeFrameReporter_State ChromeFrameReporter::State_MAX;
constexpr int ChromeFrameReporter::State_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
bool ChromeFrameReporter_FrameDropReason_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

static ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<std::string> ChromeFrameReporter_FrameDropReason_strings[4] = {};

static const char ChromeFrameReporter_FrameDropReason_names[] =
  "REASON_CLIENT_COMPOSITOR"
  "REASON_DISPLAY_COMPOSITOR"
  "REASON_MAIN_THREAD"
  "REASON_UNSPECIFIED";

static const ::PROTOBUF_NAMESPACE_ID::internal::EnumEntry ChromeFrameReporter_FrameDropReason_entries[] = {
  { {ChromeFrameReporter_FrameDropReason_names + 0, 24}, 3 },
  { {ChromeFrameReporter_FrameDropReason_names + 24, 25}, 1 },
  { {ChromeFrameReporter_FrameDropReason_names + 49, 18}, 2 },
  { {ChromeFrameReporter_FrameDropReason_names + 67, 18}, 0 },
};

static const int ChromeFrameReporter_FrameDropReason_entries_by_number[] = {
  3, // 0 -> REASON_UNSPECIFIED
  1, // 1 -> REASON_DISPLAY_COMPOSITOR
  2, // 2 -> REASON_MAIN_THREAD
  0, // 3 -> REASON_CLIENT_COMPOSITOR
};

const std::string& ChromeFrameReporter_FrameDropReason_Name(
    ChromeFrameReporter_FrameDropReason value) {
  static const bool dummy =
      ::PROTOBUF_NAMESPACE_ID::internal::InitializeEnumStrings(
          ChromeFrameReporter_FrameDropReason_entries,
          ChromeFrameReporter_FrameDropReason_entries_by_number,
          4, ChromeFrameReporter_FrameDropReason_strings);
  (void) dummy;
  int idx = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumName(
      ChromeFrameReporter_FrameDropReason_entries,
      ChromeFrameReporter_FrameDropReason_entries_by_number,
      4, value);
  return idx == -1 ? ::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString() :
                     ChromeFrameReporter_FrameDropReason_strings[idx].get();
}
bool ChromeFrameReporter_FrameDropReason_Parse(
    const std::string& name, ChromeFrameReporter_FrameDropReason* value) {
  int int_value;
  bool success = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumValue(
      ChromeFrameReporter_FrameDropReason_entries, 4, name, &int_value);
  if (success) {
    *value = static_cast<ChromeFrameReporter_FrameDropReason>(int_value);
  }
  return success;
}
#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr ChromeFrameReporter_FrameDropReason ChromeFrameReporter::REASON_UNSPECIFIED;
constexpr ChromeFrameReporter_FrameDropReason ChromeFrameReporter::REASON_DISPLAY_COMPOSITOR;
constexpr ChromeFrameReporter_FrameDropReason ChromeFrameReporter::REASON_MAIN_THREAD;
constexpr ChromeFrameReporter_FrameDropReason ChromeFrameReporter::REASON_CLIENT_COMPOSITOR;
constexpr ChromeFrameReporter_FrameDropReason ChromeFrameReporter::FrameDropReason_MIN;
constexpr ChromeFrameReporter_FrameDropReason ChromeFrameReporter::FrameDropReason_MAX;
constexpr int ChromeFrameReporter::FrameDropReason_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
bool ChromeFrameReporter_ScrollState_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

static ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<std::string> ChromeFrameReporter_ScrollState_strings[3] = {};

static const char ChromeFrameReporter_ScrollState_names[] =
  "SCROLL_COMPOSITOR_THREAD"
  "SCROLL_MAIN_THREAD"
  "SCROLL_NONE";

static const ::PROTOBUF_NAMESPACE_ID::internal::EnumEntry ChromeFrameReporter_ScrollState_entries[] = {
  { {ChromeFrameReporter_ScrollState_names + 0, 24}, 2 },
  { {ChromeFrameReporter_ScrollState_names + 24, 18}, 1 },
  { {ChromeFrameReporter_ScrollState_names + 42, 11}, 0 },
};

static const int ChromeFrameReporter_ScrollState_entries_by_number[] = {
  2, // 0 -> SCROLL_NONE
  1, // 1 -> SCROLL_MAIN_THREAD
  0, // 2 -> SCROLL_COMPOSITOR_THREAD
};

const std::string& ChromeFrameReporter_ScrollState_Name(
    ChromeFrameReporter_ScrollState value) {
  static const bool dummy =
      ::PROTOBUF_NAMESPACE_ID::internal::InitializeEnumStrings(
          ChromeFrameReporter_ScrollState_entries,
          ChromeFrameReporter_ScrollState_entries_by_number,
          3, ChromeFrameReporter_ScrollState_strings);
  (void) dummy;
  int idx = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumName(
      ChromeFrameReporter_ScrollState_entries,
      ChromeFrameReporter_ScrollState_entries_by_number,
      3, value);
  return idx == -1 ? ::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString() :
                     ChromeFrameReporter_ScrollState_strings[idx].get();
}
bool ChromeFrameReporter_ScrollState_Parse(
    const std::string& name, ChromeFrameReporter_ScrollState* value) {
  int int_value;
  bool success = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumValue(
      ChromeFrameReporter_ScrollState_entries, 3, name, &int_value);
  if (success) {
    *value = static_cast<ChromeFrameReporter_ScrollState>(int_value);
  }
  return success;
}
#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr ChromeFrameReporter_ScrollState ChromeFrameReporter::SCROLL_NONE;
constexpr ChromeFrameReporter_ScrollState ChromeFrameReporter::SCROLL_MAIN_THREAD;
constexpr ChromeFrameReporter_ScrollState ChromeFrameReporter::SCROLL_COMPOSITOR_THREAD;
constexpr ChromeFrameReporter_ScrollState ChromeFrameReporter::ScrollState_MIN;
constexpr ChromeFrameReporter_ScrollState ChromeFrameReporter::ScrollState_MAX;
constexpr int ChromeFrameReporter::ScrollState_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

void ChromeFrameReporter::InitAsDefaultInstance() {
}
class ChromeFrameReporter::_Internal {
 public:
  using HasBits = decltype(std::declval<ChromeFrameReporter>()._has_bits_);
  static void set_has_state(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_reason(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_frame_source(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_frame_sequence(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_affects_smoothness(HasBits* has_bits) {
    (*has_bits)[0] |= 32u;
  }
  static void set_has_scroll_state(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
  static void set_has_has_main_animation(HasBits* has_bits) {
    (*has_bits)[0] |= 64u;
  }
  static void set_has_has_compositor_animation(HasBits* has_bits) {
    (*has_bits)[0] |= 128u;
  }
  static void set_has_has_smooth_input_main(HasBits* has_bits) {
    (*has_bits)[0] |= 256u;
  }
};

ChromeFrameReporter::ChromeFrameReporter()
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:perfetto.protos.ChromeFrameReporter)
}
ChromeFrameReporter::ChromeFrameReporter(const ChromeFrameReporter& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&state_, &from.state_,
    static_cast<size_t>(reinterpret_cast<char*>(&has_smooth_input_main_) -
    reinterpret_cast<char*>(&state_)) + sizeof(has_smooth_input_main_));
  // @@protoc_insertion_point(copy_constructor:perfetto.protos.ChromeFrameReporter)
}

void ChromeFrameReporter::SharedCtor() {
  ::memset(&state_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&has_smooth_input_main_) -
      reinterpret_cast<char*>(&state_)) + sizeof(has_smooth_input_main_));
}

ChromeFrameReporter::~ChromeFrameReporter() {
  // @@protoc_insertion_point(destructor:perfetto.protos.ChromeFrameReporter)
  SharedDtor();
}

void ChromeFrameReporter::SharedDtor() {
}

void ChromeFrameReporter::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ChromeFrameReporter& ChromeFrameReporter::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ChromeFrameReporter_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fframe_5freporter_2eproto.base);
  return *internal_default_instance();
}


void ChromeFrameReporter::Clear() {
// @@protoc_insertion_point(message_clear_start:perfetto.protos.ChromeFrameReporter)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x000000ffu) {
    ::memset(&state_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&has_compositor_animation_) -
        reinterpret_cast<char*>(&state_)) + sizeof(has_compositor_animation_));
  }
  has_smooth_input_main_ = false;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* ChromeFrameReporter::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional .perfetto.protos.ChromeFrameReporter.State state = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::perfetto::protos::ChromeFrameReporter_State_IsValid(val))) {
            set_state(static_cast<::perfetto::protos::ChromeFrameReporter_State>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(1, val, mutable_unknown_fields());
          }
        } else goto handle_unusual;
        continue;
      // optional .perfetto.protos.ChromeFrameReporter.FrameDropReason reason = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::perfetto::protos::ChromeFrameReporter_FrameDropReason_IsValid(val))) {
            set_reason(static_cast<::perfetto::protos::ChromeFrameReporter_FrameDropReason>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(2, val, mutable_unknown_fields());
          }
        } else goto handle_unusual;
        continue;
      // optional uint64 frame_source = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          _Internal::set_has_frame_source(&has_bits);
          frame_source_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional uint64 frame_sequence = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          _Internal::set_has_frame_sequence(&has_bits);
          frame_sequence_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional bool affects_smoothness = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 40)) {
          _Internal::set_has_affects_smoothness(&has_bits);
          affects_smoothness_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional .perfetto.protos.ChromeFrameReporter.ScrollState scroll_state = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 48)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::perfetto::protos::ChromeFrameReporter_ScrollState_IsValid(val))) {
            set_scroll_state(static_cast<::perfetto::protos::ChromeFrameReporter_ScrollState>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(6, val, mutable_unknown_fields());
          }
        } else goto handle_unusual;
        continue;
      // optional bool has_main_animation = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 56)) {
          _Internal::set_has_has_main_animation(&has_bits);
          has_main_animation_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional bool has_compositor_animation = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 64)) {
          _Internal::set_has_has_compositor_animation(&has_bits);
          has_compositor_animation_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional bool has_smooth_input_main = 9;
      case 9:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 72)) {
          _Internal::set_has_has_smooth_input_main(&has_bits);
          has_smooth_input_main_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool ChromeFrameReporter::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  ::PROTOBUF_NAMESPACE_ID::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:perfetto.protos.ChromeFrameReporter)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .perfetto.protos.ChromeFrameReporter.State state = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (8 & 0xFF)) {
          int value = 0;
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   int, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::perfetto::protos::ChromeFrameReporter_State_IsValid(value)) {
            set_state(static_cast< ::perfetto::protos::ChromeFrameReporter_State >(value));
          } else {
            unknown_fields_stream.WriteVarint32(8u);
            unknown_fields_stream.WriteVarint32(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint32>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional .perfetto.protos.ChromeFrameReporter.FrameDropReason reason = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (16 & 0xFF)) {
          int value = 0;
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   int, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::perfetto::protos::ChromeFrameReporter_FrameDropReason_IsValid(value)) {
            set_reason(static_cast< ::perfetto::protos::ChromeFrameReporter_FrameDropReason >(value));
          } else {
            unknown_fields_stream.WriteVarint32(16u);
            unknown_fields_stream.WriteVarint32(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint32>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint64 frame_source = 3;
      case 3: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (24 & 0xFF)) {
          _Internal::set_has_frame_source(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint64, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT64>(
                 input, &frame_source_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint64 frame_sequence = 4;
      case 4: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (32 & 0xFF)) {
          _Internal::set_has_frame_sequence(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint64, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT64>(
                 input, &frame_sequence_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool affects_smoothness = 5;
      case 5: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (40 & 0xFF)) {
          _Internal::set_has_affects_smoothness(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   bool, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_BOOL>(
                 input, &affects_smoothness_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional .perfetto.protos.ChromeFrameReporter.ScrollState scroll_state = 6;
      case 6: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (48 & 0xFF)) {
          int value = 0;
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   int, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::perfetto::protos::ChromeFrameReporter_ScrollState_IsValid(value)) {
            set_scroll_state(static_cast< ::perfetto::protos::ChromeFrameReporter_ScrollState >(value));
          } else {
            unknown_fields_stream.WriteVarint32(48u);
            unknown_fields_stream.WriteVarint32(
                static_cast<::PROTOBUF_NAMESPACE_ID::uint32>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool has_main_animation = 7;
      case 7: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (56 & 0xFF)) {
          _Internal::set_has_has_main_animation(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   bool, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_BOOL>(
                 input, &has_main_animation_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool has_compositor_animation = 8;
      case 8: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (64 & 0xFF)) {
          _Internal::set_has_has_compositor_animation(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   bool, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_BOOL>(
                 input, &has_compositor_animation_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool has_smooth_input_main = 9;
      case 9: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (72 & 0xFF)) {
          _Internal::set_has_has_smooth_input_main(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   bool, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_BOOL>(
                 input, &has_smooth_input_main_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SkipField(
            input, tag, &unknown_fields_stream));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:perfetto.protos.ChromeFrameReporter)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:perfetto.protos.ChromeFrameReporter)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void ChromeFrameReporter::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:perfetto.protos.ChromeFrameReporter)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional .perfetto.protos.ChromeFrameReporter.State state = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnum(
      1, this->state(), output);
  }

  // optional .perfetto.protos.ChromeFrameReporter.FrameDropReason reason = 2;
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnum(
      2, this->reason(), output);
  }

  // optional uint64 frame_source = 3;
  if (cached_has_bits & 0x00000004u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64(3, this->frame_source(), output);
  }

  // optional uint64 frame_sequence = 4;
  if (cached_has_bits & 0x00000008u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64(4, this->frame_sequence(), output);
  }

  // optional bool affects_smoothness = 5;
  if (cached_has_bits & 0x00000020u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBool(5, this->affects_smoothness(), output);
  }

  // optional .perfetto.protos.ChromeFrameReporter.ScrollState scroll_state = 6;
  if (cached_has_bits & 0x00000010u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnum(
      6, this->scroll_state(), output);
  }

  // optional bool has_main_animation = 7;
  if (cached_has_bits & 0x00000040u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBool(7, this->has_main_animation(), output);
  }

  // optional bool has_compositor_animation = 8;
  if (cached_has_bits & 0x00000080u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBool(8, this->has_compositor_animation(), output);
  }

  // optional bool has_smooth_input_main = 9;
  if (cached_has_bits & 0x00000100u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBool(9, this->has_smooth_input_main(), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:perfetto.protos.ChromeFrameReporter)
}

size_t ChromeFrameReporter::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:perfetto.protos.ChromeFrameReporter)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x000000ffu) {
    // optional .perfetto.protos.ChromeFrameReporter.State state = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->state());
    }

    // optional .perfetto.protos.ChromeFrameReporter.FrameDropReason reason = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->reason());
    }

    // optional uint64 frame_source = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
          this->frame_source());
    }

    // optional uint64 frame_sequence = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
          this->frame_sequence());
    }

    // optional .perfetto.protos.ChromeFrameReporter.ScrollState scroll_state = 6;
    if (cached_has_bits & 0x00000010u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->scroll_state());
    }

    // optional bool affects_smoothness = 5;
    if (cached_has_bits & 0x00000020u) {
      total_size += 1 + 1;
    }

    // optional bool has_main_animation = 7;
    if (cached_has_bits & 0x00000040u) {
      total_size += 1 + 1;
    }

    // optional bool has_compositor_animation = 8;
    if (cached_has_bits & 0x00000080u) {
      total_size += 1 + 1;
    }

  }
  // optional bool has_smooth_input_main = 9;
  if (cached_has_bits & 0x00000100u) {
    total_size += 1 + 1;
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ChromeFrameReporter::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const ChromeFrameReporter*>(
      &from));
}

void ChromeFrameReporter::MergeFrom(const ChromeFrameReporter& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:perfetto.protos.ChromeFrameReporter)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x000000ffu) {
    if (cached_has_bits & 0x00000001u) {
      state_ = from.state_;
    }
    if (cached_has_bits & 0x00000002u) {
      reason_ = from.reason_;
    }
    if (cached_has_bits & 0x00000004u) {
      frame_source_ = from.frame_source_;
    }
    if (cached_has_bits & 0x00000008u) {
      frame_sequence_ = from.frame_sequence_;
    }
    if (cached_has_bits & 0x00000010u) {
      scroll_state_ = from.scroll_state_;
    }
    if (cached_has_bits & 0x00000020u) {
      affects_smoothness_ = from.affects_smoothness_;
    }
    if (cached_has_bits & 0x00000040u) {
      has_main_animation_ = from.has_main_animation_;
    }
    if (cached_has_bits & 0x00000080u) {
      has_compositor_animation_ = from.has_compositor_animation_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
  if (cached_has_bits & 0x00000100u) {
    set_has_smooth_input_main(from.has_smooth_input_main());
  }
}

void ChromeFrameReporter::CopyFrom(const ChromeFrameReporter& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:perfetto.protos.ChromeFrameReporter)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ChromeFrameReporter::IsInitialized() const {
  return true;
}

void ChromeFrameReporter::InternalSwap(ChromeFrameReporter* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(state_, other->state_);
  swap(reason_, other->reason_);
  swap(frame_source_, other->frame_source_);
  swap(frame_sequence_, other->frame_sequence_);
  swap(scroll_state_, other->scroll_state_);
  swap(affects_smoothness_, other->affects_smoothness_);
  swap(has_main_animation_, other->has_main_animation_);
  swap(has_compositor_animation_, other->has_compositor_animation_);
  swap(has_smooth_input_main_, other->has_smooth_input_main_);
}

std::string ChromeFrameReporter::GetTypeName() const {
  return "perfetto.protos.ChromeFrameReporter";
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::perfetto::protos::ChromeFrameReporter* Arena::CreateMaybeMessage< ::perfetto::protos::ChromeFrameReporter >(Arena* arena) {
  return Arena::CreateInternal< ::perfetto::protos::ChromeFrameReporter >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>