// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mojo_fuzzer.proto

#include "mojo_fuzzer.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace mojo_proto_fuzzer {
class MojoFuzzerMessagesDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<MojoFuzzerMessages> _instance;
} _MojoFuzzerMessages_default_instance_;
}  // namespace mojo_proto_fuzzer
static void InitDefaultsscc_info_MojoFuzzerMessages_mojo_5ffuzzer_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::mojo_proto_fuzzer::_MojoFuzzerMessages_default_instance_;
    new (ptr) ::mojo_proto_fuzzer::MojoFuzzerMessages();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_MojoFuzzerMessages_mojo_5ffuzzer_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_MojoFuzzerMessages_mojo_5ffuzzer_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_mojo_5ffuzzer_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_mojo_5ffuzzer_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_mojo_5ffuzzer_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_mojo_5ffuzzer_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mojo_proto_fuzzer::MojoFuzzerMessages, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::mojo_proto_fuzzer::MojoFuzzerMessages, messages_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::mojo_proto_fuzzer::MojoFuzzerMessages)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::mojo_proto_fuzzer::_MojoFuzzerMessages_default_instance_),
};

const char descriptor_table_protodef_mojo_5ffuzzer_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021mojo_fuzzer.proto\022\021mojo_proto_fuzzer\"&"
  "\n\022MojoFuzzerMessages\022\020\n\010messages\030\001 \003(\014"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_mojo_5ffuzzer_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_mojo_5ffuzzer_2eproto_sccs[1] = {
  &scc_info_MojoFuzzerMessages_mojo_5ffuzzer_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_mojo_5ffuzzer_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_mojo_5ffuzzer_2eproto = {
  false, false, descriptor_table_protodef_mojo_5ffuzzer_2eproto, "mojo_fuzzer.proto", 78,
  &descriptor_table_mojo_5ffuzzer_2eproto_once, descriptor_table_mojo_5ffuzzer_2eproto_sccs, descriptor_table_mojo_5ffuzzer_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_mojo_5ffuzzer_2eproto::offsets,
  file_level_metadata_mojo_5ffuzzer_2eproto, 1, file_level_enum_descriptors_mojo_5ffuzzer_2eproto, file_level_service_descriptors_mojo_5ffuzzer_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_mojo_5ffuzzer_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_mojo_5ffuzzer_2eproto)), true);
namespace mojo_proto_fuzzer {

// ===================================================================

class MojoFuzzerMessages::_Internal {
 public:
};

MojoFuzzerMessages::MojoFuzzerMessages(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  messages_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:mojo_proto_fuzzer.MojoFuzzerMessages)
}
MojoFuzzerMessages::MojoFuzzerMessages(const MojoFuzzerMessages& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      messages_(from.messages_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:mojo_proto_fuzzer.MojoFuzzerMessages)
}

void MojoFuzzerMessages::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_MojoFuzzerMessages_mojo_5ffuzzer_2eproto.base);
}

MojoFuzzerMessages::~MojoFuzzerMessages() {
  // @@protoc_insertion_point(destructor:mojo_proto_fuzzer.MojoFuzzerMessages)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void MojoFuzzerMessages::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void MojoFuzzerMessages::ArenaDtor(void* object) {
  MojoFuzzerMessages* _this = reinterpret_cast< MojoFuzzerMessages* >(object);
  (void)_this;
}
void MojoFuzzerMessages::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void MojoFuzzerMessages::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const MojoFuzzerMessages& MojoFuzzerMessages::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_MojoFuzzerMessages_mojo_5ffuzzer_2eproto.base);
  return *internal_default_instance();
}


void MojoFuzzerMessages::Clear() {
// @@protoc_insertion_point(message_clear_start:mojo_proto_fuzzer.MojoFuzzerMessages)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  messages_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MojoFuzzerMessages::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // repeated bytes messages = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_messages();
            ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* MojoFuzzerMessages::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mojo_proto_fuzzer.MojoFuzzerMessages)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated bytes messages = 1;
  for (int i = 0, n = this->_internal_messages_size(); i < n; i++) {
    const auto& s = this->_internal_messages(i);
    target = stream->WriteBytes(1, s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mojo_proto_fuzzer.MojoFuzzerMessages)
  return target;
}

size_t MojoFuzzerMessages::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mojo_proto_fuzzer.MojoFuzzerMessages)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated bytes messages = 1;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(messages_.size());
  for (int i = 0, n = messages_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
      messages_.Get(i));
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void MojoFuzzerMessages::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:mojo_proto_fuzzer.MojoFuzzerMessages)
  GOOGLE_DCHECK_NE(&from, this);
  const MojoFuzzerMessages* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<MojoFuzzerMessages>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:mojo_proto_fuzzer.MojoFuzzerMessages)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:mojo_proto_fuzzer.MojoFuzzerMessages)
    MergeFrom(*source);
  }
}

void MojoFuzzerMessages::MergeFrom(const MojoFuzzerMessages& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:mojo_proto_fuzzer.MojoFuzzerMessages)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  messages_.MergeFrom(from.messages_);
}

void MojoFuzzerMessages::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:mojo_proto_fuzzer.MojoFuzzerMessages)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MojoFuzzerMessages::CopyFrom(const MojoFuzzerMessages& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mojo_proto_fuzzer.MojoFuzzerMessages)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MojoFuzzerMessages::IsInitialized() const {
  return true;
}

void MojoFuzzerMessages::InternalSwap(MojoFuzzerMessages* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  messages_.InternalSwap(&other->messages_);
}

::PROTOBUF_NAMESPACE_ID::Metadata MojoFuzzerMessages::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace mojo_proto_fuzzer
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mojo_proto_fuzzer::MojoFuzzerMessages* Arena::CreateMaybeMessage< ::mojo_proto_fuzzer::MojoFuzzerMessages >(Arena* arena) {
  return Arena::CreateMessageInternal< ::mojo_proto_fuzzer::MojoFuzzerMessages >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>