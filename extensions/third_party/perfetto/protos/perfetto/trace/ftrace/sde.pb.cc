// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/trace/ftrace/sde.proto

#include "protos/perfetto/trace/ftrace/sde.pb.h"

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
class SdeTracingMarkWriteFtraceEventDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<SdeTracingMarkWriteFtraceEvent> _instance;
} _SdeTracingMarkWriteFtraceEvent_default_instance_;
}  // namespace protos
}  // namespace perfetto
static void InitDefaultsscc_info_SdeTracingMarkWriteFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fsde_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::perfetto::protos::_SdeTracingMarkWriteFtraceEvent_default_instance_;
    new (ptr) ::perfetto::protos::SdeTracingMarkWriteFtraceEvent();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::perfetto::protos::SdeTracingMarkWriteFtraceEvent::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_SdeTracingMarkWriteFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fsde_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_SdeTracingMarkWriteFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fsde_2eproto}, {}};

namespace perfetto {
namespace protos {

// ===================================================================

void SdeTracingMarkWriteFtraceEvent::InitAsDefaultInstance() {
}
class SdeTracingMarkWriteFtraceEvent::_Internal {
 public:
  using HasBits = decltype(std::declval<SdeTracingMarkWriteFtraceEvent>()._has_bits_);
  static void set_has_pid(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_trace_name(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_trace_type(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_value(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_trace_begin(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
};

SdeTracingMarkWriteFtraceEvent::SdeTracingMarkWriteFtraceEvent()
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:perfetto.protos.SdeTracingMarkWriteFtraceEvent)
}
SdeTracingMarkWriteFtraceEvent::SdeTracingMarkWriteFtraceEvent(const SdeTracingMarkWriteFtraceEvent& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  trace_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from.has_trace_name()) {
    trace_name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.trace_name_);
  }
  ::memcpy(&pid_, &from.pid_,
    static_cast<size_t>(reinterpret_cast<char*>(&trace_begin_) -
    reinterpret_cast<char*>(&pid_)) + sizeof(trace_begin_));
  // @@protoc_insertion_point(copy_constructor:perfetto.protos.SdeTracingMarkWriteFtraceEvent)
}

void SdeTracingMarkWriteFtraceEvent::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_SdeTracingMarkWriteFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fsde_2eproto.base);
  trace_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::memset(&pid_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&trace_begin_) -
      reinterpret_cast<char*>(&pid_)) + sizeof(trace_begin_));
}

SdeTracingMarkWriteFtraceEvent::~SdeTracingMarkWriteFtraceEvent() {
  // @@protoc_insertion_point(destructor:perfetto.protos.SdeTracingMarkWriteFtraceEvent)
  SharedDtor();
}

void SdeTracingMarkWriteFtraceEvent::SharedDtor() {
  trace_name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void SdeTracingMarkWriteFtraceEvent::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const SdeTracingMarkWriteFtraceEvent& SdeTracingMarkWriteFtraceEvent::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_SdeTracingMarkWriteFtraceEvent_protos_2fperfetto_2ftrace_2fftrace_2fsde_2eproto.base);
  return *internal_default_instance();
}


void SdeTracingMarkWriteFtraceEvent::Clear() {
// @@protoc_insertion_point(message_clear_start:perfetto.protos.SdeTracingMarkWriteFtraceEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    trace_name_.ClearNonDefaultToEmptyNoArena();
  }
  if (cached_has_bits & 0x0000001eu) {
    ::memset(&pid_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&trace_begin_) -
        reinterpret_cast<char*>(&pid_)) + sizeof(trace_begin_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* SdeTracingMarkWriteFtraceEvent::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional int32 pid = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_pid(&has_bits);
          pid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional string trace_name = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(mutable_trace_name(), ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional uint32 trace_type = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          _Internal::set_has_trace_type(&has_bits);
          trace_type_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional int32 value = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          _Internal::set_has_value(&has_bits);
          value_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional uint32 trace_begin = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 40)) {
          _Internal::set_has_trace_begin(&has_bits);
          trace_begin_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
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
bool SdeTracingMarkWriteFtraceEvent::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  ::PROTOBUF_NAMESPACE_ID::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:perfetto.protos.SdeTracingMarkWriteFtraceEvent)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 pid = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (8 & 0xFF)) {
          _Internal::set_has_pid(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32>(
                 input, &pid_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional string trace_name = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (18 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->mutable_trace_name()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint32 trace_type = 3;
      case 3: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (24 & 0xFF)) {
          _Internal::set_has_trace_type(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32>(
                 input, &trace_type_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional int32 value = 4;
      case 4: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (32 & 0xFF)) {
          _Internal::set_has_value(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32>(
                 input, &value_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint32 trace_begin = 5;
      case 5: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (40 & 0xFF)) {
          _Internal::set_has_trace_begin(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32>(
                 input, &trace_begin_)));
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
  // @@protoc_insertion_point(parse_success:perfetto.protos.SdeTracingMarkWriteFtraceEvent)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:perfetto.protos.SdeTracingMarkWriteFtraceEvent)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void SdeTracingMarkWriteFtraceEvent::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:perfetto.protos.SdeTracingMarkWriteFtraceEvent)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional int32 pid = 1;
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32(1, this->pid(), output);
  }

  // optional string trace_name = 2;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->trace_name(), output);
  }

  // optional uint32 trace_type = 3;
  if (cached_has_bits & 0x00000004u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32(3, this->trace_type(), output);
  }

  // optional int32 value = 4;
  if (cached_has_bits & 0x00000008u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32(4, this->value(), output);
  }

  // optional uint32 trace_begin = 5;
  if (cached_has_bits & 0x00000010u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32(5, this->trace_begin(), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:perfetto.protos.SdeTracingMarkWriteFtraceEvent)
}

size_t SdeTracingMarkWriteFtraceEvent::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:perfetto.protos.SdeTracingMarkWriteFtraceEvent)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    // optional string trace_name = 2;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->trace_name());
    }

    // optional int32 pid = 1;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
          this->pid());
    }

    // optional uint32 trace_type = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
          this->trace_type());
    }

    // optional int32 value = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
          this->value());
    }

    // optional uint32 trace_begin = 5;
    if (cached_has_bits & 0x00000010u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
          this->trace_begin());
    }

  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void SdeTracingMarkWriteFtraceEvent::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const SdeTracingMarkWriteFtraceEvent*>(
      &from));
}

void SdeTracingMarkWriteFtraceEvent::MergeFrom(const SdeTracingMarkWriteFtraceEvent& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:perfetto.protos.SdeTracingMarkWriteFtraceEvent)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000001fu) {
    if (cached_has_bits & 0x00000001u) {
      _has_bits_[0] |= 0x00000001u;
      trace_name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.trace_name_);
    }
    if (cached_has_bits & 0x00000002u) {
      pid_ = from.pid_;
    }
    if (cached_has_bits & 0x00000004u) {
      trace_type_ = from.trace_type_;
    }
    if (cached_has_bits & 0x00000008u) {
      value_ = from.value_;
    }
    if (cached_has_bits & 0x00000010u) {
      trace_begin_ = from.trace_begin_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void SdeTracingMarkWriteFtraceEvent::CopyFrom(const SdeTracingMarkWriteFtraceEvent& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:perfetto.protos.SdeTracingMarkWriteFtraceEvent)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SdeTracingMarkWriteFtraceEvent::IsInitialized() const {
  return true;
}

void SdeTracingMarkWriteFtraceEvent::InternalSwap(SdeTracingMarkWriteFtraceEvent* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  trace_name_.Swap(&other->trace_name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(pid_, other->pid_);
  swap(trace_type_, other->trace_type_);
  swap(value_, other->value_);
  swap(trace_begin_, other->trace_begin_);
}

std::string SdeTracingMarkWriteFtraceEvent::GetTypeName() const {
  return "perfetto.protos.SdeTracingMarkWriteFtraceEvent";
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::perfetto::protos::SdeTracingMarkWriteFtraceEvent* Arena::CreateMaybeMessage< ::perfetto::protos::SdeTracingMarkWriteFtraceEvent >(Arena* arena) {
  return Arena::CreateInternal< ::perfetto::protos::SdeTracingMarkWriteFtraceEvent >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
