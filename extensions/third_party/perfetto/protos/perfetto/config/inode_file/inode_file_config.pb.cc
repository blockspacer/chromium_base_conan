// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/config/inode_file/inode_file_config.proto

#include "protos/perfetto/config/inode_file/inode_file_config.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_InodeFileConfig_MountPointMappingEntry_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto;
namespace perfetto {
namespace protos {
class InodeFileConfig_MountPointMappingEntryDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<InodeFileConfig_MountPointMappingEntry> _instance;
} _InodeFileConfig_MountPointMappingEntry_default_instance_;
class InodeFileConfigDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<InodeFileConfig> _instance;
} _InodeFileConfig_default_instance_;
}  // namespace protos
}  // namespace perfetto
static void InitDefaultsscc_info_InodeFileConfig_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::perfetto::protos::_InodeFileConfig_default_instance_;
    new (ptr) ::perfetto::protos::InodeFileConfig();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::perfetto::protos::InodeFileConfig::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_InodeFileConfig_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsscc_info_InodeFileConfig_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto}, {
      &scc_info_InodeFileConfig_MountPointMappingEntry_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto.base,}};

static void InitDefaultsscc_info_InodeFileConfig_MountPointMappingEntry_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::perfetto::protos::_InodeFileConfig_MountPointMappingEntry_default_instance_;
    new (ptr) ::perfetto::protos::InodeFileConfig_MountPointMappingEntry();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::perfetto::protos::InodeFileConfig_MountPointMappingEntry::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_InodeFileConfig_MountPointMappingEntry_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_InodeFileConfig_MountPointMappingEntry_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto}, {}};

namespace perfetto {
namespace protos {

// ===================================================================

void InodeFileConfig_MountPointMappingEntry::InitAsDefaultInstance() {
}
class InodeFileConfig_MountPointMappingEntry::_Internal {
 public:
  using HasBits = decltype(std::declval<InodeFileConfig_MountPointMappingEntry>()._has_bits_);
  static void set_has_mountpoint(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

InodeFileConfig_MountPointMappingEntry::InodeFileConfig_MountPointMappingEntry()
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:perfetto.protos.InodeFileConfig.MountPointMappingEntry)
}
InodeFileConfig_MountPointMappingEntry::InodeFileConfig_MountPointMappingEntry(const InodeFileConfig_MountPointMappingEntry& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_),
      scan_roots_(from.scan_roots_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  mountpoint_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from.has_mountpoint()) {
    mountpoint_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.mountpoint_);
  }
  // @@protoc_insertion_point(copy_constructor:perfetto.protos.InodeFileConfig.MountPointMappingEntry)
}

void InodeFileConfig_MountPointMappingEntry::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_InodeFileConfig_MountPointMappingEntry_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto.base);
  mountpoint_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

InodeFileConfig_MountPointMappingEntry::~InodeFileConfig_MountPointMappingEntry() {
  // @@protoc_insertion_point(destructor:perfetto.protos.InodeFileConfig.MountPointMappingEntry)
  SharedDtor();
}

void InodeFileConfig_MountPointMappingEntry::SharedDtor() {
  mountpoint_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void InodeFileConfig_MountPointMappingEntry::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const InodeFileConfig_MountPointMappingEntry& InodeFileConfig_MountPointMappingEntry::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_InodeFileConfig_MountPointMappingEntry_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto.base);
  return *internal_default_instance();
}


void InodeFileConfig_MountPointMappingEntry::Clear() {
// @@protoc_insertion_point(message_clear_start:perfetto.protos.InodeFileConfig.MountPointMappingEntry)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  scan_roots_.Clear();
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    mountpoint_.ClearNonDefaultToEmptyNoArena();
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* InodeFileConfig_MountPointMappingEntry::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional string mountpoint = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(mutable_mountpoint(), ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // repeated string scan_roots = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(add_scan_roots(), ptr, ctx);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<::PROTOBUF_NAMESPACE_ID::uint8>(ptr) == 18);
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
bool InodeFileConfig_MountPointMappingEntry::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  ::PROTOBUF_NAMESPACE_ID::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:perfetto.protos.InodeFileConfig.MountPointMappingEntry)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string mountpoint = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->mutable_mountpoint()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated string scan_roots = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (18 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->add_scan_roots()));
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
  // @@protoc_insertion_point(parse_success:perfetto.protos.InodeFileConfig.MountPointMappingEntry)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:perfetto.protos.InodeFileConfig.MountPointMappingEntry)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void InodeFileConfig_MountPointMappingEntry::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:perfetto.protos.InodeFileConfig.MountPointMappingEntry)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional string mountpoint = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->mountpoint(), output);
  }

  // repeated string scan_roots = 2;
  for (int i = 0, n = this->scan_roots_size(); i < n; i++) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteString(
      2, this->scan_roots(i), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:perfetto.protos.InodeFileConfig.MountPointMappingEntry)
}

size_t InodeFileConfig_MountPointMappingEntry::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:perfetto.protos.InodeFileConfig.MountPointMappingEntry)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated string scan_roots = 2;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(this->scan_roots_size());
  for (int i = 0, n = this->scan_roots_size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      this->scan_roots(i));
  }

  // optional string mountpoint = 1;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->mountpoint());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void InodeFileConfig_MountPointMappingEntry::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const InodeFileConfig_MountPointMappingEntry*>(
      &from));
}

void InodeFileConfig_MountPointMappingEntry::MergeFrom(const InodeFileConfig_MountPointMappingEntry& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:perfetto.protos.InodeFileConfig.MountPointMappingEntry)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  scan_roots_.MergeFrom(from.scan_roots_);
  if (from.has_mountpoint()) {
    _has_bits_[0] |= 0x00000001u;
    mountpoint_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.mountpoint_);
  }
}

void InodeFileConfig_MountPointMappingEntry::CopyFrom(const InodeFileConfig_MountPointMappingEntry& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:perfetto.protos.InodeFileConfig.MountPointMappingEntry)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool InodeFileConfig_MountPointMappingEntry::IsInitialized() const {
  return true;
}

void InodeFileConfig_MountPointMappingEntry::InternalSwap(InodeFileConfig_MountPointMappingEntry* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  scan_roots_.InternalSwap(CastToBase(&other->scan_roots_));
  mountpoint_.Swap(&other->mountpoint_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
}

std::string InodeFileConfig_MountPointMappingEntry::GetTypeName() const {
  return "perfetto.protos.InodeFileConfig.MountPointMappingEntry";
}


// ===================================================================

void InodeFileConfig::InitAsDefaultInstance() {
}
class InodeFileConfig::_Internal {
 public:
  using HasBits = decltype(std::declval<InodeFileConfig>()._has_bits_);
  static void set_has_scan_interval_ms(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_scan_delay_ms(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_scan_batch_size(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_do_not_scan(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
};

InodeFileConfig::InodeFileConfig()
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:perfetto.protos.InodeFileConfig)
}
InodeFileConfig::InodeFileConfig(const InodeFileConfig& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_),
      scan_mount_points_(from.scan_mount_points_),
      mount_point_mapping_(from.mount_point_mapping_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&scan_interval_ms_, &from.scan_interval_ms_,
    static_cast<size_t>(reinterpret_cast<char*>(&do_not_scan_) -
    reinterpret_cast<char*>(&scan_interval_ms_)) + sizeof(do_not_scan_));
  // @@protoc_insertion_point(copy_constructor:perfetto.protos.InodeFileConfig)
}

void InodeFileConfig::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_InodeFileConfig_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto.base);
  ::memset(&scan_interval_ms_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&do_not_scan_) -
      reinterpret_cast<char*>(&scan_interval_ms_)) + sizeof(do_not_scan_));
}

InodeFileConfig::~InodeFileConfig() {
  // @@protoc_insertion_point(destructor:perfetto.protos.InodeFileConfig)
  SharedDtor();
}

void InodeFileConfig::SharedDtor() {
}

void InodeFileConfig::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const InodeFileConfig& InodeFileConfig::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_InodeFileConfig_protos_2fperfetto_2fconfig_2finode_5ffile_2finode_5ffile_5fconfig_2eproto.base);
  return *internal_default_instance();
}


void InodeFileConfig::Clear() {
// @@protoc_insertion_point(message_clear_start:perfetto.protos.InodeFileConfig)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  scan_mount_points_.Clear();
  mount_point_mapping_.Clear();
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    ::memset(&scan_interval_ms_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&do_not_scan_) -
        reinterpret_cast<char*>(&scan_interval_ms_)) + sizeof(do_not_scan_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* InodeFileConfig::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional uint32 scan_interval_ms = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_scan_interval_ms(&has_bits);
          scan_interval_ms_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional uint32 scan_delay_ms = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_scan_delay_ms(&has_bits);
          scan_delay_ms_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional uint32 scan_batch_size = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          _Internal::set_has_scan_batch_size(&has_bits);
          scan_batch_size_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional bool do_not_scan = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          _Internal::set_has_do_not_scan(&has_bits);
          do_not_scan_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // repeated string scan_mount_points = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(add_scan_mount_points(), ptr, ctx);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<::PROTOBUF_NAMESPACE_ID::uint8>(ptr) == 42);
        } else goto handle_unusual;
        continue;
      // repeated .perfetto.protos.InodeFileConfig.MountPointMappingEntry mount_point_mapping = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 50)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(add_mount_point_mapping(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<::PROTOBUF_NAMESPACE_ID::uint8>(ptr) == 50);
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
bool InodeFileConfig::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  ::PROTOBUF_NAMESPACE_ID::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:perfetto.protos.InodeFileConfig)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 scan_interval_ms = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (8 & 0xFF)) {
          _Internal::set_has_scan_interval_ms(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32>(
                 input, &scan_interval_ms_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint32 scan_delay_ms = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (16 & 0xFF)) {
          _Internal::set_has_scan_delay_ms(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32>(
                 input, &scan_delay_ms_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint32 scan_batch_size = 3;
      case 3: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (24 & 0xFF)) {
          _Internal::set_has_scan_batch_size(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32>(
                 input, &scan_batch_size_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool do_not_scan = 4;
      case 4: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (32 & 0xFF)) {
          _Internal::set_has_do_not_scan(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   bool, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_BOOL>(
                 input, &do_not_scan_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated string scan_mount_points = 5;
      case 5: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (42 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->add_scan_mount_points()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .perfetto.protos.InodeFileConfig.MountPointMappingEntry mount_point_mapping = 6;
      case 6: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (50 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadMessage(
                input, add_mount_point_mapping()));
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
  // @@protoc_insertion_point(parse_success:perfetto.protos.InodeFileConfig)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:perfetto.protos.InodeFileConfig)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void InodeFileConfig::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:perfetto.protos.InodeFileConfig)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional uint32 scan_interval_ms = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32(1, this->scan_interval_ms(), output);
  }

  // optional uint32 scan_delay_ms = 2;
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32(2, this->scan_delay_ms(), output);
  }

  // optional uint32 scan_batch_size = 3;
  if (cached_has_bits & 0x00000004u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32(3, this->scan_batch_size(), output);
  }

  // optional bool do_not_scan = 4;
  if (cached_has_bits & 0x00000008u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBool(4, this->do_not_scan(), output);
  }

  // repeated string scan_mount_points = 5;
  for (int i = 0, n = this->scan_mount_points_size(); i < n; i++) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteString(
      5, this->scan_mount_points(i), output);
  }

  // repeated .perfetto.protos.InodeFileConfig.MountPointMappingEntry mount_point_mapping = 6;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->mount_point_mapping_size()); i < n; i++) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteMessage(
      6,
      this->mount_point_mapping(static_cast<int>(i)),
      output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:perfetto.protos.InodeFileConfig)
}

size_t InodeFileConfig::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:perfetto.protos.InodeFileConfig)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated string scan_mount_points = 5;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(this->scan_mount_points_size());
  for (int i = 0, n = this->scan_mount_points_size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
      this->scan_mount_points(i));
  }

  // repeated .perfetto.protos.InodeFileConfig.MountPointMappingEntry mount_point_mapping = 6;
  {
    unsigned int count = static_cast<unsigned int>(this->mount_point_mapping_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          this->mount_point_mapping(static_cast<int>(i)));
    }
  }

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    // optional uint32 scan_interval_ms = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
          this->scan_interval_ms());
    }

    // optional uint32 scan_delay_ms = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
          this->scan_delay_ms());
    }

    // optional uint32 scan_batch_size = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
          this->scan_batch_size());
    }

    // optional bool do_not_scan = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 + 1;
    }

  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void InodeFileConfig::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const InodeFileConfig*>(
      &from));
}

void InodeFileConfig::MergeFrom(const InodeFileConfig& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:perfetto.protos.InodeFileConfig)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  scan_mount_points_.MergeFrom(from.scan_mount_points_);
  mount_point_mapping_.MergeFrom(from.mount_point_mapping_);
  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      scan_interval_ms_ = from.scan_interval_ms_;
    }
    if (cached_has_bits & 0x00000002u) {
      scan_delay_ms_ = from.scan_delay_ms_;
    }
    if (cached_has_bits & 0x00000004u) {
      scan_batch_size_ = from.scan_batch_size_;
    }
    if (cached_has_bits & 0x00000008u) {
      do_not_scan_ = from.do_not_scan_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void InodeFileConfig::CopyFrom(const InodeFileConfig& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:perfetto.protos.InodeFileConfig)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool InodeFileConfig::IsInitialized() const {
  return true;
}

void InodeFileConfig::InternalSwap(InodeFileConfig* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  scan_mount_points_.InternalSwap(CastToBase(&other->scan_mount_points_));
  CastToBase(&mount_point_mapping_)->InternalSwap(CastToBase(&other->mount_point_mapping_));
  swap(scan_interval_ms_, other->scan_interval_ms_);
  swap(scan_delay_ms_, other->scan_delay_ms_);
  swap(scan_batch_size_, other->scan_batch_size_);
  swap(do_not_scan_, other->do_not_scan_);
}

std::string InodeFileConfig::GetTypeName() const {
  return "perfetto.protos.InodeFileConfig";
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::perfetto::protos::InodeFileConfig_MountPointMappingEntry* Arena::CreateMaybeMessage< ::perfetto::protos::InodeFileConfig_MountPointMappingEntry >(Arena* arena) {
  return Arena::CreateInternal< ::perfetto::protos::InodeFileConfig_MountPointMappingEntry >(arena);
}
template<> PROTOBUF_NOINLINE ::perfetto::protos::InodeFileConfig* Arena::CreateMaybeMessage< ::perfetto::protos::InodeFileConfig >(Arena* arena) {
  return Arena::CreateInternal< ::perfetto::protos::InodeFileConfig >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
