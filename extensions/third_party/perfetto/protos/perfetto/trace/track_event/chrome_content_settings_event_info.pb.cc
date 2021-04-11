// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/trace/track_event/chrome_content_settings_event_info.proto

#include "protos/perfetto/trace/track_event/chrome_content_settings_event_info.pb.h"

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
class ChromeContentSettingsEventInfoDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ChromeContentSettingsEventInfo> _instance;
} _ChromeContentSettingsEventInfo_default_instance_;
}  // namespace protos
}  // namespace perfetto
static void InitDefaultsscc_info_ChromeContentSettingsEventInfo_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fcontent_5fsettings_5fevent_5finfo_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::perfetto::protos::_ChromeContentSettingsEventInfo_default_instance_;
    new (ptr) ::perfetto::protos::ChromeContentSettingsEventInfo();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::perfetto::protos::ChromeContentSettingsEventInfo::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ChromeContentSettingsEventInfo_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fcontent_5fsettings_5fevent_5finfo_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_ChromeContentSettingsEventInfo_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fcontent_5fsettings_5fevent_5finfo_2eproto}, {}};

namespace perfetto {
namespace protos {

// ===================================================================

void ChromeContentSettingsEventInfo::InitAsDefaultInstance() {
}
class ChromeContentSettingsEventInfo::_Internal {
 public:
  using HasBits = decltype(std::declval<ChromeContentSettingsEventInfo>()._has_bits_);
  static void set_has_number_of_exceptions(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

ChromeContentSettingsEventInfo::ChromeContentSettingsEventInfo()
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:perfetto.protos.ChromeContentSettingsEventInfo)
}
ChromeContentSettingsEventInfo::ChromeContentSettingsEventInfo(const ChromeContentSettingsEventInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  number_of_exceptions_ = from.number_of_exceptions_;
  // @@protoc_insertion_point(copy_constructor:perfetto.protos.ChromeContentSettingsEventInfo)
}

void ChromeContentSettingsEventInfo::SharedCtor() {
  number_of_exceptions_ = 0u;
}

ChromeContentSettingsEventInfo::~ChromeContentSettingsEventInfo() {
  // @@protoc_insertion_point(destructor:perfetto.protos.ChromeContentSettingsEventInfo)
  SharedDtor();
}

void ChromeContentSettingsEventInfo::SharedDtor() {
}

void ChromeContentSettingsEventInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ChromeContentSettingsEventInfo& ChromeContentSettingsEventInfo::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ChromeContentSettingsEventInfo_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fcontent_5fsettings_5fevent_5finfo_2eproto.base);
  return *internal_default_instance();
}


void ChromeContentSettingsEventInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:perfetto.protos.ChromeContentSettingsEventInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  number_of_exceptions_ = 0u;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* ChromeContentSettingsEventInfo::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional uint32 number_of_exceptions = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_number_of_exceptions(&has_bits);
          number_of_exceptions_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
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
bool ChromeContentSettingsEventInfo::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  ::PROTOBUF_NAMESPACE_ID::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:perfetto.protos.ChromeContentSettingsEventInfo)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 number_of_exceptions = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (8 & 0xFF)) {
          _Internal::set_has_number_of_exceptions(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32>(
                 input, &number_of_exceptions_)));
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
  // @@protoc_insertion_point(parse_success:perfetto.protos.ChromeContentSettingsEventInfo)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:perfetto.protos.ChromeContentSettingsEventInfo)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void ChromeContentSettingsEventInfo::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:perfetto.protos.ChromeContentSettingsEventInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional uint32 number_of_exceptions = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32(1, this->number_of_exceptions(), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:perfetto.protos.ChromeContentSettingsEventInfo)
}

size_t ChromeContentSettingsEventInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:perfetto.protos.ChromeContentSettingsEventInfo)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional uint32 number_of_exceptions = 1;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->number_of_exceptions());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ChromeContentSettingsEventInfo::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const ChromeContentSettingsEventInfo*>(
      &from));
}

void ChromeContentSettingsEventInfo::MergeFrom(const ChromeContentSettingsEventInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:perfetto.protos.ChromeContentSettingsEventInfo)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_number_of_exceptions()) {
    set_number_of_exceptions(from.number_of_exceptions());
  }
}

void ChromeContentSettingsEventInfo::CopyFrom(const ChromeContentSettingsEventInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:perfetto.protos.ChromeContentSettingsEventInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ChromeContentSettingsEventInfo::IsInitialized() const {
  return true;
}

void ChromeContentSettingsEventInfo::InternalSwap(ChromeContentSettingsEventInfo* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(number_of_exceptions_, other->number_of_exceptions_);
}

std::string ChromeContentSettingsEventInfo::GetTypeName() const {
  return "perfetto.protos.ChromeContentSettingsEventInfo";
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::perfetto::protos::ChromeContentSettingsEventInfo* Arena::CreateMaybeMessage< ::perfetto::protos::ChromeContentSettingsEventInfo >(Arena* arena) {
  return Arena::CreateInternal< ::perfetto::protos::ChromeContentSettingsEventInfo >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>