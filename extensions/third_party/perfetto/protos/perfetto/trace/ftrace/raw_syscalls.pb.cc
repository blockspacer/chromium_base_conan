// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/trace/ftrace/raw_syscalls.proto

#include "protos/perfetto/trace/ftrace/raw_syscalls.pb.h"

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
class SysEnterFtraceEventDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<SysEnterFtraceEvent> _instance;
} _SysEnterFtraceEvent_default_instance_;
class SysExitFtraceEventDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<SysExitFtraceEvent> _instance;
} _SysExitFtraceEvent_default_instance_;
}  // namespace protos
}  // namespace perfetto
static void InitDefaultsscc_info_SysEnterFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fraw_5fsyscalls_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::perfetto::protos::_SysEnterFtraceEvent_default_instance_;
    new (ptr) ::perfetto::protos::SysEnterFtraceEvent();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::perfetto::protos::SysEnterFtraceEvent::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_SysEnterFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fraw_5fsyscalls_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_SysEnterFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fraw_5fsyscalls_2eproto}, {}};

static void InitDefaultsscc_info_SysExitFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fraw_5fsyscalls_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::perfetto::protos::_SysExitFtraceEvent_default_instance_;
    new (ptr) ::perfetto::protos::SysExitFtraceEvent();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::perfetto::protos::SysExitFtraceEvent::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_SysExitFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fraw_5fsyscalls_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_SysExitFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fraw_5fsyscalls_2eproto}, {}};

namespace perfetto {
namespace protos {

// ===================================================================

void SysEnterFtraceEvent::InitAsDefaultInstance() {
}
class SysEnterFtraceEvent::_Internal {
 public:
  using HasBits = decltype(std::declval<SysEnterFtraceEvent>()._has_bits_);
  static void set_has_id(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

SysEnterFtraceEvent::SysEnterFtraceEvent()
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:perfetto.protos.SysEnterFtraceEvent)
}
SysEnterFtraceEvent::SysEnterFtraceEvent(const SysEnterFtraceEvent& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  id_ = from.id_;
  // @@protoc_insertion_point(copy_constructor:perfetto.protos.SysEnterFtraceEvent)
}

void SysEnterFtraceEvent::SharedCtor() {
  id_ = PROTOBUF_LONGLONG(0);
}

SysEnterFtraceEvent::~SysEnterFtraceEvent() {
  // @@protoc_insertion_point(destructor:perfetto.protos.SysEnterFtraceEvent)
  SharedDtor();
}

void SysEnterFtraceEvent::SharedDtor() {
}

void SysEnterFtraceEvent::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const SysEnterFtraceEvent& SysEnterFtraceEvent::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_SysEnterFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fraw_5fsyscalls_2eproto.base);
  return *internal_default_instance();
}


void SysEnterFtraceEvent::Clear() {
// @@protoc_insertion_point(message_clear_start:perfetto.protos.SysEnterFtraceEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  id_ = PROTOBUF_LONGLONG(0);
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* SysEnterFtraceEvent::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional int64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_id(&has_bits);
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
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
bool SysEnterFtraceEvent::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  ::PROTOBUF_NAMESPACE_ID::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:perfetto.protos.SysEnterFtraceEvent)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int64 id = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (8 & 0xFF)) {
          _Internal::set_has_id(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::int64, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT64>(
                 input, &id_)));
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
  // @@protoc_insertion_point(parse_success:perfetto.protos.SysEnterFtraceEvent)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:perfetto.protos.SysEnterFtraceEvent)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void SysEnterFtraceEvent::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:perfetto.protos.SysEnterFtraceEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int64 id = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64(1, this->id(), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:perfetto.protos.SysEnterFtraceEvent)
}

size_t SysEnterFtraceEvent::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:perfetto.protos.SysEnterFtraceEvent)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional int64 id = 1;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
        this->id());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void SysEnterFtraceEvent::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const SysEnterFtraceEvent*>(
      &from));
}

void SysEnterFtraceEvent::MergeFrom(const SysEnterFtraceEvent& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:perfetto.protos.SysEnterFtraceEvent)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_id()) {
    set_id(from.id());
  }
}

void SysEnterFtraceEvent::CopyFrom(const SysEnterFtraceEvent& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:perfetto.protos.SysEnterFtraceEvent)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SysEnterFtraceEvent::IsInitialized() const {
  return true;
}

void SysEnterFtraceEvent::InternalSwap(SysEnterFtraceEvent* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(id_, other->id_);
}

std::string SysEnterFtraceEvent::GetTypeName() const {
  return "perfetto.protos.SysEnterFtraceEvent";
}


// ===================================================================

void SysExitFtraceEvent::InitAsDefaultInstance() {
}
class SysExitFtraceEvent::_Internal {
 public:
  using HasBits = decltype(std::declval<SysExitFtraceEvent>()._has_bits_);
  static void set_has_id(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_ret(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
};

SysExitFtraceEvent::SysExitFtraceEvent()
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:perfetto.protos.SysExitFtraceEvent)
}
SysExitFtraceEvent::SysExitFtraceEvent(const SysExitFtraceEvent& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&id_, &from.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&ret_) -
    reinterpret_cast<char*>(&id_)) + sizeof(ret_));
  // @@protoc_insertion_point(copy_constructor:perfetto.protos.SysExitFtraceEvent)
}

void SysExitFtraceEvent::SharedCtor() {
  ::memset(&id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&ret_) -
      reinterpret_cast<char*>(&id_)) + sizeof(ret_));
}

SysExitFtraceEvent::~SysExitFtraceEvent() {
  // @@protoc_insertion_point(destructor:perfetto.protos.SysExitFtraceEvent)
  SharedDtor();
}

void SysExitFtraceEvent::SharedDtor() {
}

void SysExitFtraceEvent::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const SysExitFtraceEvent& SysExitFtraceEvent::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_SysExitFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fraw_5fsyscalls_2eproto.base);
  return *internal_default_instance();
}


void SysExitFtraceEvent::Clear() {
// @@protoc_insertion_point(message_clear_start:perfetto.protos.SysExitFtraceEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    ::memset(&id_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&ret_) -
        reinterpret_cast<char*>(&id_)) + sizeof(ret_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* SysExitFtraceEvent::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional int64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_id(&has_bits);
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional int64 ret = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_ret(&has_bits);
          ret_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
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
bool SysExitFtraceEvent::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  ::PROTOBUF_NAMESPACE_ID::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:perfetto.protos.SysExitFtraceEvent)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int64 id = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (8 & 0xFF)) {
          _Internal::set_has_id(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::int64, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT64>(
                 input, &id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional int64 ret = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (16 & 0xFF)) {
          _Internal::set_has_ret(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::int64, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT64>(
                 input, &ret_)));
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
  // @@protoc_insertion_point(parse_success:perfetto.protos.SysExitFtraceEvent)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:perfetto.protos.SysExitFtraceEvent)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void SysExitFtraceEvent::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:perfetto.protos.SysExitFtraceEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int64 id = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64(1, this->id(), output);
  }

  // optional int64 ret = 2;
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64(2, this->ret(), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:perfetto.protos.SysExitFtraceEvent)
}

size_t SysExitFtraceEvent::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:perfetto.protos.SysExitFtraceEvent)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional int64 id = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
          this->id());
    }

    // optional int64 ret = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
          this->ret());
    }

  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void SysExitFtraceEvent::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const SysExitFtraceEvent*>(
      &from));
}

void SysExitFtraceEvent::MergeFrom(const SysExitFtraceEvent& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:perfetto.protos.SysExitFtraceEvent)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      id_ = from.id_;
    }
    if (cached_has_bits & 0x00000002u) {
      ret_ = from.ret_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void SysExitFtraceEvent::CopyFrom(const SysExitFtraceEvent& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:perfetto.protos.SysExitFtraceEvent)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SysExitFtraceEvent::IsInitialized() const {
  return true;
}

void SysExitFtraceEvent::InternalSwap(SysExitFtraceEvent* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(id_, other->id_);
  swap(ret_, other->ret_);
}

std::string SysExitFtraceEvent::GetTypeName() const {
  return "perfetto.protos.SysExitFtraceEvent";
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::perfetto::protos::SysEnterFtraceEvent* Arena::CreateMaybeMessage< ::perfetto::protos::SysEnterFtraceEvent >(Arena* arena) {
  return Arena::CreateInternal< ::perfetto::protos::SysEnterFtraceEvent >(arena);
}
template<> PROTOBUF_NOINLINE ::perfetto::protos::SysExitFtraceEvent* Arena::CreateMaybeMessage< ::perfetto::protos::SysExitFtraceEvent >(Arena* arena) {
  return Arena::CreateInternal< ::perfetto::protos::SysExitFtraceEvent >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>