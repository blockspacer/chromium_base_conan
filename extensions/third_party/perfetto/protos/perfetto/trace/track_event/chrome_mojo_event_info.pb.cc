// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/trace/track_event/chrome_mojo_event_info.proto

#include "protos/perfetto/trace/track_event/chrome_mojo_event_info.pb.h"

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
class ChromeMojoEventInfoDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ChromeMojoEventInfo> _instance;
} _ChromeMojoEventInfo_default_instance_;
}  // namespace protos
}  // namespace perfetto
static void InitDefaultsscc_info_ChromeMojoEventInfo_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fmojo_5fevent_5finfo_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::perfetto::protos::_ChromeMojoEventInfo_default_instance_;
    new (ptr) ::perfetto::protos::ChromeMojoEventInfo();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::perfetto::protos::ChromeMojoEventInfo::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ChromeMojoEventInfo_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fmojo_5fevent_5finfo_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_ChromeMojoEventInfo_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fmojo_5fevent_5finfo_2eproto}, {}};

namespace perfetto {
namespace protos {

// ===================================================================

void ChromeMojoEventInfo::InitAsDefaultInstance() {
}
class ChromeMojoEventInfo::_Internal {
 public:
  using HasBits = decltype(std::declval<ChromeMojoEventInfo>()._has_bits_);
  static void set_has_watcher_notify_interface_tag(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

ChromeMojoEventInfo::ChromeMojoEventInfo()
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:perfetto.protos.ChromeMojoEventInfo)
}
ChromeMojoEventInfo::ChromeMojoEventInfo(const ChromeMojoEventInfo& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  watcher_notify_interface_tag_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from.has_watcher_notify_interface_tag()) {
    watcher_notify_interface_tag_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.watcher_notify_interface_tag_);
  }
  // @@protoc_insertion_point(copy_constructor:perfetto.protos.ChromeMojoEventInfo)
}

void ChromeMojoEventInfo::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_ChromeMojoEventInfo_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fmojo_5fevent_5finfo_2eproto.base);
  watcher_notify_interface_tag_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

ChromeMojoEventInfo::~ChromeMojoEventInfo() {
  // @@protoc_insertion_point(destructor:perfetto.protos.ChromeMojoEventInfo)
  SharedDtor();
}

void ChromeMojoEventInfo::SharedDtor() {
  watcher_notify_interface_tag_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void ChromeMojoEventInfo::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ChromeMojoEventInfo& ChromeMojoEventInfo::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ChromeMojoEventInfo_protos_2fperfetto_2ftrace_2ftrack_5fevent_2fchrome_5fmojo_5fevent_5finfo_2eproto.base);
  return *internal_default_instance();
}


void ChromeMojoEventInfo::Clear() {
// @@protoc_insertion_point(message_clear_start:perfetto.protos.ChromeMojoEventInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    watcher_notify_interface_tag_.ClearNonDefaultToEmptyNoArena();
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* ChromeMojoEventInfo::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional string watcher_notify_interface_tag = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(mutable_watcher_notify_interface_tag(), ptr, ctx);
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
bool ChromeMojoEventInfo::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  ::PROTOBUF_NAMESPACE_ID::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:perfetto.protos.ChromeMojoEventInfo)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string watcher_notify_interface_tag = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->mutable_watcher_notify_interface_tag()));
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
  // @@protoc_insertion_point(parse_success:perfetto.protos.ChromeMojoEventInfo)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:perfetto.protos.ChromeMojoEventInfo)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void ChromeMojoEventInfo::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:perfetto.protos.ChromeMojoEventInfo)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional string watcher_notify_interface_tag = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->watcher_notify_interface_tag(), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:perfetto.protos.ChromeMojoEventInfo)
}

size_t ChromeMojoEventInfo::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:perfetto.protos.ChromeMojoEventInfo)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional string watcher_notify_interface_tag = 1;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->watcher_notify_interface_tag());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ChromeMojoEventInfo::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const ChromeMojoEventInfo*>(
      &from));
}

void ChromeMojoEventInfo::MergeFrom(const ChromeMojoEventInfo& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:perfetto.protos.ChromeMojoEventInfo)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_watcher_notify_interface_tag()) {
    _has_bits_[0] |= 0x00000001u;
    watcher_notify_interface_tag_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.watcher_notify_interface_tag_);
  }
}

void ChromeMojoEventInfo::CopyFrom(const ChromeMojoEventInfo& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:perfetto.protos.ChromeMojoEventInfo)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ChromeMojoEventInfo::IsInitialized() const {
  return true;
}

void ChromeMojoEventInfo::InternalSwap(ChromeMojoEventInfo* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  watcher_notify_interface_tag_.Swap(&other->watcher_notify_interface_tag_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
}

std::string ChromeMojoEventInfo::GetTypeName() const {
  return "perfetto.protos.ChromeMojoEventInfo";
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::perfetto::protos::ChromeMojoEventInfo* Arena::CreateMaybeMessage< ::perfetto::protos::ChromeMojoEventInfo >(Arena* arena) {
  return Arena::CreateInternal< ::perfetto::protos::ChromeMojoEventInfo >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>