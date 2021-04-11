// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/trace/track_event/chrome_legacy_ipc.proto

#include "protos/perfetto/trace/track_event/chrome_legacy_ipc.pb.h"

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
class ChromeLegacyIpcDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ChromeLegacyIpc> _instance;
} _ChromeLegacyIpc_default_instance_;
}  // namespace protos
}  // namespace perfetto
static void InitDefaultsscc_info_ChromeLegacyIpc_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5flegacy_5fipc_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::perfetto::protos::_ChromeLegacyIpc_default_instance_;
    new (ptr) ::perfetto::protos::ChromeLegacyIpc();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::perfetto::protos::ChromeLegacyIpc::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ChromeLegacyIpc_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5flegacy_5fipc_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_ChromeLegacyIpc_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5flegacy_5fipc_2eproto}, {}};

namespace perfetto {
namespace protos {
bool ChromeLegacyIpc_MessageClass_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
      return true;
    default:
      return false;
  }
}

static ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<std::string> ChromeLegacyIpc_MessageClass_strings[38] = {};

static const char ChromeLegacyIpc_MessageClass_names[] =
  "CLASS_ACCESSIBILITY"
  "CLASS_ANDROID_WEB_VIEW"
  "CLASS_AUTOMATION"
  "CLASS_BLINK_TEST"
  "CLASS_BROWSER_PLUGIN"
  "CLASS_CAST"
  "CLASS_CHROME"
  "CLASS_CHROME_UTILITY_PRINTING"
  "CLASS_CHROMOTING"
  "CLASS_DRAG"
  "CLASS_ENCRYPTED_MEDIA"
  "CLASS_EXTENSION"
  "CLASS_EXTENSIONS_GUEST_VIEW"
  "CLASS_EXTENSION_WORKER"
  "CLASS_FRAME"
  "CLASS_GIN_JAVA_BRIDGE"
  "CLASS_GPU_CHANNEL"
  "CLASS_GUEST_VIEW"
  "CLASS_INPUT"
  "CLASS_MEDIA"
  "CLASS_MEDIA_PLAYER_DELEGATE"
  "CLASS_NACL"
  "CLASS_NACL_HOST"
  "CLASS_NETWORK_HINTS"
  "CLASS_OZONE_GPU"
  "CLASS_PAGE"
  "CLASS_PPAPI"
  "CLASS_PRERENDER"
  "CLASS_PRINT"
  "CLASS_SUBRESOURCE_FILTER"
  "CLASS_TEST"
  "CLASS_TEXT_INPUT_CLIENT"
  "CLASS_UNFREEZABLE_FRAME"
  "CLASS_UNSPECIFIED"
  "CLASS_VIEW"
  "CLASS_WEB_TEST"
  "CLASS_WIDGET"
  "CLASS_WORKER";

static const ::PROTOBUF_NAMESPACE_ID::internal::EnumEntry ChromeLegacyIpc_MessageClass_entries[] = {
  { {ChromeLegacyIpc_MessageClass_names + 0, 19}, 19 },
  { {ChromeLegacyIpc_MessageClass_names + 19, 22}, 23 },
  { {ChromeLegacyIpc_MessageClass_names + 41, 16}, 1 },
  { {ChromeLegacyIpc_MessageClass_names + 57, 16}, 18 },
  { {ChromeLegacyIpc_MessageClass_names + 73, 20}, 22 },
  { {ChromeLegacyIpc_MessageClass_names + 93, 10}, 26 },
  { {ChromeLegacyIpc_MessageClass_names + 103, 12}, 13 },
  { {ChromeLegacyIpc_MessageClass_names + 115, 29}, 28 },
  { {ChromeLegacyIpc_MessageClass_names + 144, 16}, 21 },
  { {ChromeLegacyIpc_MessageClass_names + 160, 10}, 14 },
  { {ChromeLegacyIpc_MessageClass_names + 170, 21}, 25 },
  { {ChromeLegacyIpc_MessageClass_names + 191, 15}, 16 },
  { {ChromeLegacyIpc_MessageClass_names + 206, 27}, 32 },
  { {ChromeLegacyIpc_MessageClass_names + 233, 22}, 35 },
  { {ChromeLegacyIpc_MessageClass_names + 255, 11}, 2 },
  { {ChromeLegacyIpc_MessageClass_names + 266, 21}, 27 },
  { {ChromeLegacyIpc_MessageClass_names + 287, 17}, 10 },
  { {ChromeLegacyIpc_MessageClass_names + 304, 16}, 33 },
  { {ChromeLegacyIpc_MessageClass_names + 320, 11}, 6 },
  { {ChromeLegacyIpc_MessageClass_names + 331, 11}, 11 },
  { {ChromeLegacyIpc_MessageClass_names + 342, 27}, 34 },
  { {ChromeLegacyIpc_MessageClass_names + 369, 10}, 9 },
  { {ChromeLegacyIpc_MessageClass_names + 379, 15}, 24 },
  { {ChromeLegacyIpc_MessageClass_names + 394, 19}, 31 },
  { {ChromeLegacyIpc_MessageClass_names + 413, 15}, 29 },
  { {ChromeLegacyIpc_MessageClass_names + 428, 10}, 3 },
  { {ChromeLegacyIpc_MessageClass_names + 438, 11}, 12 },
  { {ChromeLegacyIpc_MessageClass_names + 449, 15}, 20 },
  { {ChromeLegacyIpc_MessageClass_names + 464, 11}, 15 },
  { {ChromeLegacyIpc_MessageClass_names + 475, 24}, 36 },
  { {ChromeLegacyIpc_MessageClass_names + 499, 10}, 7 },
  { {ChromeLegacyIpc_MessageClass_names + 509, 23}, 17 },
  { {ChromeLegacyIpc_MessageClass_names + 532, 23}, 37 },
  { {ChromeLegacyIpc_MessageClass_names + 555, 17}, 0 },
  { {ChromeLegacyIpc_MessageClass_names + 572, 10}, 4 },
  { {ChromeLegacyIpc_MessageClass_names + 582, 14}, 30 },
  { {ChromeLegacyIpc_MessageClass_names + 596, 12}, 5 },
  { {ChromeLegacyIpc_MessageClass_names + 608, 12}, 8 },
};

static const int ChromeLegacyIpc_MessageClass_entries_by_number[] = {
  33, // 0 -> CLASS_UNSPECIFIED
  2, // 1 -> CLASS_AUTOMATION
  14, // 2 -> CLASS_FRAME
  25, // 3 -> CLASS_PAGE
  34, // 4 -> CLASS_VIEW
  36, // 5 -> CLASS_WIDGET
  18, // 6 -> CLASS_INPUT
  30, // 7 -> CLASS_TEST
  37, // 8 -> CLASS_WORKER
  21, // 9 -> CLASS_NACL
  16, // 10 -> CLASS_GPU_CHANNEL
  19, // 11 -> CLASS_MEDIA
  26, // 12 -> CLASS_PPAPI
  6, // 13 -> CLASS_CHROME
  9, // 14 -> CLASS_DRAG
  28, // 15 -> CLASS_PRINT
  11, // 16 -> CLASS_EXTENSION
  31, // 17 -> CLASS_TEXT_INPUT_CLIENT
  3, // 18 -> CLASS_BLINK_TEST
  0, // 19 -> CLASS_ACCESSIBILITY
  27, // 20 -> CLASS_PRERENDER
  8, // 21 -> CLASS_CHROMOTING
  4, // 22 -> CLASS_BROWSER_PLUGIN
  1, // 23 -> CLASS_ANDROID_WEB_VIEW
  22, // 24 -> CLASS_NACL_HOST
  10, // 25 -> CLASS_ENCRYPTED_MEDIA
  5, // 26 -> CLASS_CAST
  15, // 27 -> CLASS_GIN_JAVA_BRIDGE
  7, // 28 -> CLASS_CHROME_UTILITY_PRINTING
  24, // 29 -> CLASS_OZONE_GPU
  35, // 30 -> CLASS_WEB_TEST
  23, // 31 -> CLASS_NETWORK_HINTS
  12, // 32 -> CLASS_EXTENSIONS_GUEST_VIEW
  17, // 33 -> CLASS_GUEST_VIEW
  20, // 34 -> CLASS_MEDIA_PLAYER_DELEGATE
  13, // 35 -> CLASS_EXTENSION_WORKER
  29, // 36 -> CLASS_SUBRESOURCE_FILTER
  32, // 37 -> CLASS_UNFREEZABLE_FRAME
};

const std::string& ChromeLegacyIpc_MessageClass_Name(
    ChromeLegacyIpc_MessageClass value) {
  static const bool dummy =
      ::PROTOBUF_NAMESPACE_ID::internal::InitializeEnumStrings(
          ChromeLegacyIpc_MessageClass_entries,
          ChromeLegacyIpc_MessageClass_entries_by_number,
          38, ChromeLegacyIpc_MessageClass_strings);
  (void) dummy;
  int idx = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumName(
      ChromeLegacyIpc_MessageClass_entries,
      ChromeLegacyIpc_MessageClass_entries_by_number,
      38, value);
  return idx == -1 ? ::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString() :
                     ChromeLegacyIpc_MessageClass_strings[idx].get();
}
bool ChromeLegacyIpc_MessageClass_Parse(
    const std::string& name, ChromeLegacyIpc_MessageClass* value) {
  int int_value;
  bool success = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumValue(
      ChromeLegacyIpc_MessageClass_entries, 38, name, &int_value);
  if (success) {
    *value = static_cast<ChromeLegacyIpc_MessageClass>(int_value);
  }
  return success;
}
#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_UNSPECIFIED;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_AUTOMATION;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_FRAME;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_PAGE;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_VIEW;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_WIDGET;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_INPUT;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_TEST;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_WORKER;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_NACL;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_GPU_CHANNEL;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_MEDIA;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_PPAPI;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_CHROME;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_DRAG;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_PRINT;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_EXTENSION;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_TEXT_INPUT_CLIENT;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_BLINK_TEST;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_ACCESSIBILITY;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_PRERENDER;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_CHROMOTING;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_BROWSER_PLUGIN;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_ANDROID_WEB_VIEW;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_NACL_HOST;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_ENCRYPTED_MEDIA;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_CAST;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_GIN_JAVA_BRIDGE;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_CHROME_UTILITY_PRINTING;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_OZONE_GPU;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_WEB_TEST;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_NETWORK_HINTS;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_EXTENSIONS_GUEST_VIEW;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_GUEST_VIEW;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_MEDIA_PLAYER_DELEGATE;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_EXTENSION_WORKER;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_SUBRESOURCE_FILTER;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::CLASS_UNFREEZABLE_FRAME;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::MessageClass_MIN;
constexpr ChromeLegacyIpc_MessageClass ChromeLegacyIpc::MessageClass_MAX;
constexpr int ChromeLegacyIpc::MessageClass_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

void ChromeLegacyIpc::InitAsDefaultInstance() {
}
class ChromeLegacyIpc::_Internal {
 public:
  using HasBits = decltype(std::declval<ChromeLegacyIpc>()._has_bits_);
  static void set_has_message_class(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_message_line(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
};

ChromeLegacyIpc::ChromeLegacyIpc()
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:perfetto.protos.ChromeLegacyIpc)
}
ChromeLegacyIpc::ChromeLegacyIpc(const ChromeLegacyIpc& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&message_class_, &from.message_class_,
    static_cast<size_t>(reinterpret_cast<char*>(&message_line_) -
    reinterpret_cast<char*>(&message_class_)) + sizeof(message_line_));
  // @@protoc_insertion_point(copy_constructor:perfetto.protos.ChromeLegacyIpc)
}

void ChromeLegacyIpc::SharedCtor() {
  ::memset(&message_class_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&message_line_) -
      reinterpret_cast<char*>(&message_class_)) + sizeof(message_line_));
}

ChromeLegacyIpc::~ChromeLegacyIpc() {
  // @@protoc_insertion_point(destructor:perfetto.protos.ChromeLegacyIpc)
  SharedDtor();
}

void ChromeLegacyIpc::SharedDtor() {
}

void ChromeLegacyIpc::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ChromeLegacyIpc& ChromeLegacyIpc::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ChromeLegacyIpc_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5flegacy_5fipc_2eproto.base);
  return *internal_default_instance();
}


void ChromeLegacyIpc::Clear() {
// @@protoc_insertion_point(message_clear_start:perfetto.protos.ChromeLegacyIpc)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    ::memset(&message_class_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&message_line_) -
        reinterpret_cast<char*>(&message_class_)) + sizeof(message_line_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* ChromeLegacyIpc::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional .perfetto.protos.ChromeLegacyIpc.MessageClass message_class = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::perfetto::protos::ChromeLegacyIpc_MessageClass_IsValid(val))) {
            set_message_class(static_cast<::perfetto::protos::ChromeLegacyIpc_MessageClass>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(1, val, mutable_unknown_fields());
          }
        } else goto handle_unusual;
        continue;
      // optional uint32 message_line = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_message_line(&has_bits);
          message_line_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
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
bool ChromeLegacyIpc::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  ::PROTOBUF_NAMESPACE_ID::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:perfetto.protos.ChromeLegacyIpc)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .perfetto.protos.ChromeLegacyIpc.MessageClass message_class = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (8 & 0xFF)) {
          int value = 0;
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   int, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::perfetto::protos::ChromeLegacyIpc_MessageClass_IsValid(value)) {
            set_message_class(static_cast< ::perfetto::protos::ChromeLegacyIpc_MessageClass >(value));
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

      // optional uint32 message_line = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (16 & 0xFF)) {
          _Internal::set_has_message_line(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32>(
                 input, &message_line_)));
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
  // @@protoc_insertion_point(parse_success:perfetto.protos.ChromeLegacyIpc)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:perfetto.protos.ChromeLegacyIpc)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void ChromeLegacyIpc::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:perfetto.protos.ChromeLegacyIpc)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional .perfetto.protos.ChromeLegacyIpc.MessageClass message_class = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnum(
      1, this->message_class(), output);
  }

  // optional uint32 message_line = 2;
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32(2, this->message_line(), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:perfetto.protos.ChromeLegacyIpc)
}

size_t ChromeLegacyIpc::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:perfetto.protos.ChromeLegacyIpc)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional .perfetto.protos.ChromeLegacyIpc.MessageClass message_class = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->message_class());
    }

    // optional uint32 message_line = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
          this->message_line());
    }

  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ChromeLegacyIpc::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const ChromeLegacyIpc*>(
      &from));
}

void ChromeLegacyIpc::MergeFrom(const ChromeLegacyIpc& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:perfetto.protos.ChromeLegacyIpc)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      message_class_ = from.message_class_;
    }
    if (cached_has_bits & 0x00000002u) {
      message_line_ = from.message_line_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void ChromeLegacyIpc::CopyFrom(const ChromeLegacyIpc& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:perfetto.protos.ChromeLegacyIpc)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ChromeLegacyIpc::IsInitialized() const {
  return true;
}

void ChromeLegacyIpc::InternalSwap(ChromeLegacyIpc* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(message_class_, other->message_class_);
  swap(message_line_, other->message_line_);
}

std::string ChromeLegacyIpc::GetTypeName() const {
  return "perfetto.protos.ChromeLegacyIpc";
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::perfetto::protos::ChromeLegacyIpc* Arena::CreateMaybeMessage< ::perfetto::protos::ChromeLegacyIpc >(Arena* arena) {
  return Arena::CreateInternal< ::perfetto::protos::ChromeLegacyIpc >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>