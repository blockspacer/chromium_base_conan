// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protos/perfetto/trace/clock_snapshot.proto

#include "protos/perfetto/trace/clock_snapshot.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ClockSnapshot_Clock_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto;
namespace perfetto {
namespace protos {
class ClockSnapshot_ClockDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ClockSnapshot_Clock> _instance;
} _ClockSnapshot_Clock_default_instance_;
class ClockSnapshotDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ClockSnapshot> _instance;
} _ClockSnapshot_default_instance_;
}  // namespace protos
}  // namespace perfetto
static void InitDefaultsscc_info_ClockSnapshot_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::perfetto::protos::_ClockSnapshot_default_instance_;
    new (ptr) ::perfetto::protos::ClockSnapshot();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::perfetto::protos::ClockSnapshot::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_ClockSnapshot_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsscc_info_ClockSnapshot_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto}, {
      &scc_info_ClockSnapshot_Clock_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto.base,}};

static void InitDefaultsscc_info_ClockSnapshot_Clock_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::perfetto::protos::_ClockSnapshot_Clock_default_instance_;
    new (ptr) ::perfetto::protos::ClockSnapshot_Clock();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::perfetto::protos::ClockSnapshot_Clock::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_ClockSnapshot_Clock_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_ClockSnapshot_Clock_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto}, {}};

namespace perfetto {
namespace protos {
bool ClockSnapshot_Clock_BuiltinClocks_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 63:
      return true;
    default:
      return false;
  }
}

static ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<std::string> ClockSnapshot_Clock_BuiltinClocks_strings[8] = {};

static const char ClockSnapshot_Clock_BuiltinClocks_names[] =
  "BOOTTIME"
  "BUILTIN_CLOCK_MAX_ID"
  "MONOTONIC"
  "MONOTONIC_COARSE"
  "MONOTONIC_RAW"
  "REALTIME"
  "REALTIME_COARSE"
  "UNKNOWN";

static const ::PROTOBUF_NAMESPACE_ID::internal::EnumEntry ClockSnapshot_Clock_BuiltinClocks_entries[] = {
  { {ClockSnapshot_Clock_BuiltinClocks_names + 0, 8}, 6 },
  { {ClockSnapshot_Clock_BuiltinClocks_names + 8, 20}, 63 },
  { {ClockSnapshot_Clock_BuiltinClocks_names + 28, 9}, 3 },
  { {ClockSnapshot_Clock_BuiltinClocks_names + 37, 16}, 4 },
  { {ClockSnapshot_Clock_BuiltinClocks_names + 53, 13}, 5 },
  { {ClockSnapshot_Clock_BuiltinClocks_names + 66, 8}, 1 },
  { {ClockSnapshot_Clock_BuiltinClocks_names + 74, 15}, 2 },
  { {ClockSnapshot_Clock_BuiltinClocks_names + 89, 7}, 0 },
};

static const int ClockSnapshot_Clock_BuiltinClocks_entries_by_number[] = {
  7, // 0 -> UNKNOWN
  5, // 1 -> REALTIME
  6, // 2 -> REALTIME_COARSE
  2, // 3 -> MONOTONIC
  3, // 4 -> MONOTONIC_COARSE
  4, // 5 -> MONOTONIC_RAW
  0, // 6 -> BOOTTIME
  1, // 63 -> BUILTIN_CLOCK_MAX_ID
};

const std::string& ClockSnapshot_Clock_BuiltinClocks_Name(
    ClockSnapshot_Clock_BuiltinClocks value) {
  static const bool dummy =
      ::PROTOBUF_NAMESPACE_ID::internal::InitializeEnumStrings(
          ClockSnapshot_Clock_BuiltinClocks_entries,
          ClockSnapshot_Clock_BuiltinClocks_entries_by_number,
          8, ClockSnapshot_Clock_BuiltinClocks_strings);
  (void) dummy;
  int idx = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumName(
      ClockSnapshot_Clock_BuiltinClocks_entries,
      ClockSnapshot_Clock_BuiltinClocks_entries_by_number,
      8, value);
  return idx == -1 ? ::PROTOBUF_NAMESPACE_ID::internal::GetEmptyString() :
                     ClockSnapshot_Clock_BuiltinClocks_strings[idx].get();
}
bool ClockSnapshot_Clock_BuiltinClocks_Parse(
    const std::string& name, ClockSnapshot_Clock_BuiltinClocks* value) {
  int int_value;
  bool success = ::PROTOBUF_NAMESPACE_ID::internal::LookUpEnumValue(
      ClockSnapshot_Clock_BuiltinClocks_entries, 8, name, &int_value);
  if (success) {
    *value = static_cast<ClockSnapshot_Clock_BuiltinClocks>(int_value);
  }
  return success;
}
#if (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)
constexpr ClockSnapshot_Clock_BuiltinClocks ClockSnapshot_Clock::UNKNOWN;
constexpr ClockSnapshot_Clock_BuiltinClocks ClockSnapshot_Clock::REALTIME;
constexpr ClockSnapshot_Clock_BuiltinClocks ClockSnapshot_Clock::REALTIME_COARSE;
constexpr ClockSnapshot_Clock_BuiltinClocks ClockSnapshot_Clock::MONOTONIC;
constexpr ClockSnapshot_Clock_BuiltinClocks ClockSnapshot_Clock::MONOTONIC_COARSE;
constexpr ClockSnapshot_Clock_BuiltinClocks ClockSnapshot_Clock::MONOTONIC_RAW;
constexpr ClockSnapshot_Clock_BuiltinClocks ClockSnapshot_Clock::BOOTTIME;
constexpr ClockSnapshot_Clock_BuiltinClocks ClockSnapshot_Clock::BUILTIN_CLOCK_MAX_ID;
constexpr ClockSnapshot_Clock_BuiltinClocks ClockSnapshot_Clock::BuiltinClocks_MIN;
constexpr ClockSnapshot_Clock_BuiltinClocks ClockSnapshot_Clock::BuiltinClocks_MAX;
constexpr int ClockSnapshot_Clock::BuiltinClocks_ARRAYSIZE;
#endif  // (__cplusplus < 201703) && (!defined(_MSC_VER) || _MSC_VER >= 1900)

// ===================================================================

void ClockSnapshot_Clock::InitAsDefaultInstance() {
}
class ClockSnapshot_Clock::_Internal {
 public:
  using HasBits = decltype(std::declval<ClockSnapshot_Clock>()._has_bits_);
  static void set_has_clock_id(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_timestamp(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_is_incremental(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_unit_multiplier_ns(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
};

ClockSnapshot_Clock::ClockSnapshot_Clock()
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:perfetto.protos.ClockSnapshot.Clock)
}
ClockSnapshot_Clock::ClockSnapshot_Clock(const ClockSnapshot_Clock& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&timestamp_, &from.timestamp_,
    static_cast<size_t>(reinterpret_cast<char*>(&unit_multiplier_ns_) -
    reinterpret_cast<char*>(&timestamp_)) + sizeof(unit_multiplier_ns_));
  // @@protoc_insertion_point(copy_constructor:perfetto.protos.ClockSnapshot.Clock)
}

void ClockSnapshot_Clock::SharedCtor() {
  ::memset(&timestamp_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&unit_multiplier_ns_) -
      reinterpret_cast<char*>(&timestamp_)) + sizeof(unit_multiplier_ns_));
}

ClockSnapshot_Clock::~ClockSnapshot_Clock() {
  // @@protoc_insertion_point(destructor:perfetto.protos.ClockSnapshot.Clock)
  SharedDtor();
}

void ClockSnapshot_Clock::SharedDtor() {
}

void ClockSnapshot_Clock::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ClockSnapshot_Clock& ClockSnapshot_Clock::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ClockSnapshot_Clock_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto.base);
  return *internal_default_instance();
}


void ClockSnapshot_Clock::Clear() {
// @@protoc_insertion_point(message_clear_start:perfetto.protos.ClockSnapshot.Clock)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    ::memset(&timestamp_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&unit_multiplier_ns_) -
        reinterpret_cast<char*>(&timestamp_)) + sizeof(unit_multiplier_ns_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* ClockSnapshot_Clock::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional uint32 clock_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_clock_id(&has_bits);
          clock_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional uint64 timestamp = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_timestamp(&has_bits);
          timestamp_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional bool is_incremental = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          _Internal::set_has_is_incremental(&has_bits);
          is_incremental_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional uint64 unit_multiplier_ns = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          _Internal::set_has_unit_multiplier_ns(&has_bits);
          unit_multiplier_ns_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
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
bool ClockSnapshot_Clock::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  ::PROTOBUF_NAMESPACE_ID::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:perfetto.protos.ClockSnapshot.Clock)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 clock_id = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (8 & 0xFF)) {
          _Internal::set_has_clock_id(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT32>(
                 input, &clock_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint64 timestamp = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (16 & 0xFF)) {
          _Internal::set_has_timestamp(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint64, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT64>(
                 input, &timestamp_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bool is_incremental = 3;
      case 3: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (24 & 0xFF)) {
          _Internal::set_has_is_incremental(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   bool, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_BOOL>(
                 input, &is_incremental_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional uint64 unit_multiplier_ns = 4;
      case 4: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (32 & 0xFF)) {
          _Internal::set_has_unit_multiplier_ns(&_has_bits_);
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::uint64, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_UINT64>(
                 input, &unit_multiplier_ns_)));
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
  // @@protoc_insertion_point(parse_success:perfetto.protos.ClockSnapshot.Clock)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:perfetto.protos.ClockSnapshot.Clock)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void ClockSnapshot_Clock::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:perfetto.protos.ClockSnapshot.Clock)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional uint32 clock_id = 1;
  if (cached_has_bits & 0x00000002u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32(1, this->clock_id(), output);
  }

  // optional uint64 timestamp = 2;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64(2, this->timestamp(), output);
  }

  // optional bool is_incremental = 3;
  if (cached_has_bits & 0x00000004u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBool(3, this->is_incremental(), output);
  }

  // optional uint64 unit_multiplier_ns = 4;
  if (cached_has_bits & 0x00000008u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64(4, this->unit_multiplier_ns(), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:perfetto.protos.ClockSnapshot.Clock)
}

size_t ClockSnapshot_Clock::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:perfetto.protos.ClockSnapshot.Clock)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    // optional uint64 timestamp = 2;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
          this->timestamp());
    }

    // optional uint32 clock_id = 1;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
          this->clock_id());
    }

    // optional bool is_incremental = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 + 1;
    }

    // optional uint64 unit_multiplier_ns = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
          this->unit_multiplier_ns());
    }

  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ClockSnapshot_Clock::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const ClockSnapshot_Clock*>(
      &from));
}

void ClockSnapshot_Clock::MergeFrom(const ClockSnapshot_Clock& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:perfetto.protos.ClockSnapshot.Clock)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      timestamp_ = from.timestamp_;
    }
    if (cached_has_bits & 0x00000002u) {
      clock_id_ = from.clock_id_;
    }
    if (cached_has_bits & 0x00000004u) {
      is_incremental_ = from.is_incremental_;
    }
    if (cached_has_bits & 0x00000008u) {
      unit_multiplier_ns_ = from.unit_multiplier_ns_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void ClockSnapshot_Clock::CopyFrom(const ClockSnapshot_Clock& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:perfetto.protos.ClockSnapshot.Clock)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ClockSnapshot_Clock::IsInitialized() const {
  return true;
}

void ClockSnapshot_Clock::InternalSwap(ClockSnapshot_Clock* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(timestamp_, other->timestamp_);
  swap(clock_id_, other->clock_id_);
  swap(is_incremental_, other->is_incremental_);
  swap(unit_multiplier_ns_, other->unit_multiplier_ns_);
}

std::string ClockSnapshot_Clock::GetTypeName() const {
  return "perfetto.protos.ClockSnapshot.Clock";
}


// ===================================================================

void ClockSnapshot::InitAsDefaultInstance() {
}
class ClockSnapshot::_Internal {
 public:
  using HasBits = decltype(std::declval<ClockSnapshot>()._has_bits_);
  static void set_has_primary_trace_clock(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

ClockSnapshot::ClockSnapshot()
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:perfetto.protos.ClockSnapshot)
}
ClockSnapshot::ClockSnapshot(const ClockSnapshot& from)
  : ::PROTOBUF_NAMESPACE_ID::MessageLite(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_),
      clocks_(from.clocks_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  primary_trace_clock_ = from.primary_trace_clock_;
  // @@protoc_insertion_point(copy_constructor:perfetto.protos.ClockSnapshot)
}

void ClockSnapshot::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_ClockSnapshot_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto.base);
  primary_trace_clock_ = 0;
}

ClockSnapshot::~ClockSnapshot() {
  // @@protoc_insertion_point(destructor:perfetto.protos.ClockSnapshot)
  SharedDtor();
}

void ClockSnapshot::SharedDtor() {
}

void ClockSnapshot::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ClockSnapshot& ClockSnapshot::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ClockSnapshot_protos_2fperfetto_2ftrace_2fclock_5fsnapshot_2eproto.base);
  return *internal_default_instance();
}


void ClockSnapshot::Clear() {
// @@protoc_insertion_point(message_clear_start:perfetto.protos.ClockSnapshot)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  clocks_.Clear();
  primary_trace_clock_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* ClockSnapshot::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // repeated .perfetto.protos.ClockSnapshot.Clock clocks = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(add_clocks(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<::PROTOBUF_NAMESPACE_ID::uint8>(ptr) == 10);
        } else goto handle_unusual;
        continue;
      // optional .perfetto.protos.BuiltinClock primary_trace_clock = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
          if (PROTOBUF_PREDICT_TRUE(::perfetto::protos::BuiltinClock_IsValid(val))) {
            set_primary_trace_clock(static_cast<::perfetto::protos::BuiltinClock>(val));
          } else {
            ::PROTOBUF_NAMESPACE_ID::internal::WriteVarint(2, val, mutable_unknown_fields());
          }
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
bool ClockSnapshot::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  ::PROTOBUF_NAMESPACE_ID::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:perfetto.protos.ClockSnapshot)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .perfetto.protos.ClockSnapshot.Clock clocks = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadMessage(
                input, add_clocks()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional .perfetto.protos.BuiltinClock primary_trace_clock = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (16 & 0xFF)) {
          int value = 0;
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   int, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::perfetto::protos::BuiltinClock_IsValid(value)) {
            set_primary_trace_clock(static_cast< ::perfetto::protos::BuiltinClock >(value));
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
  // @@protoc_insertion_point(parse_success:perfetto.protos.ClockSnapshot)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:perfetto.protos.ClockSnapshot)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void ClockSnapshot::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:perfetto.protos.ClockSnapshot)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .perfetto.protos.ClockSnapshot.Clock clocks = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->clocks_size()); i < n; i++) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteMessage(
      1,
      this->clocks(static_cast<int>(i)),
      output);
  }

  cached_has_bits = _has_bits_[0];
  // optional .perfetto.protos.BuiltinClock primary_trace_clock = 2;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnum(
      2, this->primary_trace_clock(), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:perfetto.protos.ClockSnapshot)
}

size_t ClockSnapshot::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:perfetto.protos.ClockSnapshot)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .perfetto.protos.ClockSnapshot.Clock clocks = 1;
  {
    unsigned int count = static_cast<unsigned int>(this->clocks_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          this->clocks(static_cast<int>(i)));
    }
  }

  // optional .perfetto.protos.BuiltinClock primary_trace_clock = 2;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->primary_trace_clock());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ClockSnapshot::CheckTypeAndMergeFrom(
    const ::PROTOBUF_NAMESPACE_ID::MessageLite& from) {
  MergeFrom(*::PROTOBUF_NAMESPACE_ID::internal::DownCast<const ClockSnapshot*>(
      &from));
}

void ClockSnapshot::MergeFrom(const ClockSnapshot& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:perfetto.protos.ClockSnapshot)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  clocks_.MergeFrom(from.clocks_);
  if (from.has_primary_trace_clock()) {
    set_primary_trace_clock(from.primary_trace_clock());
  }
}

void ClockSnapshot::CopyFrom(const ClockSnapshot& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:perfetto.protos.ClockSnapshot)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ClockSnapshot::IsInitialized() const {
  return true;
}

void ClockSnapshot::InternalSwap(ClockSnapshot* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  CastToBase(&clocks_)->InternalSwap(CastToBase(&other->clocks_));
  swap(primary_trace_clock_, other->primary_trace_clock_);
}

std::string ClockSnapshot::GetTypeName() const {
  return "perfetto.protos.ClockSnapshot";
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace protos
}  // namespace perfetto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::perfetto::protos::ClockSnapshot_Clock* Arena::CreateMaybeMessage< ::perfetto::protos::ClockSnapshot_Clock >(Arena* arena) {
  return Arena::CreateInternal< ::perfetto::protos::ClockSnapshot_Clock >(arena);
}
template<> PROTOBUF_NOINLINE ::perfetto::protos::ClockSnapshot* Arena::CreateMaybeMessage< ::perfetto::protos::ClockSnapshot >(Arena* arena) {
  return Arena::CreateInternal< ::perfetto::protos::ClockSnapshot >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>