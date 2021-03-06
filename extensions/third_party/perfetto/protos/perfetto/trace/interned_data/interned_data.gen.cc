#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/scattered_heap_buffer.h"
// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif
#include "protos/perfetto/trace/interned_data/interned_data.gen.h"
#include "protos/perfetto/trace/profiling/profile_common.gen.h"
#include "protos/perfetto/trace/track_event/source_location.gen.h"
#include "protos/perfetto/trace/track_event/track_event.gen.h"
#include "protos/perfetto/trace/track_event/chrome_window_handle_event_info.gen.h"
#include "protos/perfetto/trace/track_event/chrome_user_event.gen.h"
#include "protos/perfetto/trace/track_event/chrome_renderer_scheduler_state.gen.h"
#include "protos/perfetto/trace/track_event/chrome_mojo_event_info.gen.h"
#include "protos/perfetto/trace/track_event/chrome_message_pump.gen.h"
#include "protos/perfetto/trace/track_event/chrome_legacy_ipc.gen.h"
#include "protos/perfetto/trace/track_event/chrome_latency_info.gen.h"
#include "protos/perfetto/trace/track_event/chrome_keyed_service.gen.h"
#include "protos/perfetto/trace/track_event/chrome_histogram_sample.gen.h"
#include "protos/perfetto/trace/track_event/chrome_frame_reporter.gen.h"
#include "protos/perfetto/trace/track_event/chrome_content_settings_event_info.gen.h"
#include "protos/perfetto/trace/track_event/chrome_compositor_scheduler_state.gen.h"
#include "protos/perfetto/trace/track_event/chrome_application_state_info.gen.h"
#include "protos/perfetto/trace/track_event/task_execution.gen.h"
#include "protos/perfetto/trace/track_event/log_message.gen.h"
#include "protos/perfetto/trace/track_event/debug_annotation.gen.h"
#include "protos/perfetto/trace/track_event/log_message.gen.h"
#include "protos/perfetto/trace/track_event/debug_annotation.gen.h"
#include "protos/perfetto/trace/track_event/chrome_histogram_sample.gen.h"
#include "protos/perfetto/trace/gpu/gpu_render_stage_event.gen.h"

namespace perfetto {
namespace protos {
namespace gen {

InternedData::InternedData() = default;
InternedData::~InternedData() = default;
InternedData::InternedData(const InternedData&) = default;
InternedData& InternedData::operator=(const InternedData&) = default;
InternedData::InternedData(InternedData&&) noexcept = default;
InternedData& InternedData::operator=(InternedData&&) = default;

bool InternedData::operator==(const InternedData& other) const {
  return unknown_fields_ == other.unknown_fields_
   && event_categories_ == other.event_categories_
   && event_names_ == other.event_names_
   && debug_annotation_names_ == other.debug_annotation_names_
   && source_locations_ == other.source_locations_
   && log_message_body_ == other.log_message_body_
   && histogram_names_ == other.histogram_names_
   && build_ids_ == other.build_ids_
   && mapping_paths_ == other.mapping_paths_
   && source_paths_ == other.source_paths_
   && function_names_ == other.function_names_
   && profiled_frame_symbols_ == other.profiled_frame_symbols_
   && mappings_ == other.mappings_
   && frames_ == other.frames_
   && callstacks_ == other.callstacks_
   && vulkan_memory_keys_ == other.vulkan_memory_keys_
   && graphics_contexts_ == other.graphics_contexts_
   && gpu_specifications_ == other.gpu_specifications_
   && kernel_symbols_ == other.kernel_symbols_;
}

int InternedData::event_categories_size() const { return static_cast<int>(event_categories_.size()); }
void InternedData::clear_event_categories() { event_categories_.clear(); }
EventCategory* InternedData::add_event_categories() { event_categories_.emplace_back(); return &event_categories_.back(); }
int InternedData::event_names_size() const { return static_cast<int>(event_names_.size()); }
void InternedData::clear_event_names() { event_names_.clear(); }
EventName* InternedData::add_event_names() { event_names_.emplace_back(); return &event_names_.back(); }
int InternedData::debug_annotation_names_size() const { return static_cast<int>(debug_annotation_names_.size()); }
void InternedData::clear_debug_annotation_names() { debug_annotation_names_.clear(); }
DebugAnnotationName* InternedData::add_debug_annotation_names() { debug_annotation_names_.emplace_back(); return &debug_annotation_names_.back(); }
int InternedData::source_locations_size() const { return static_cast<int>(source_locations_.size()); }
void InternedData::clear_source_locations() { source_locations_.clear(); }
SourceLocation* InternedData::add_source_locations() { source_locations_.emplace_back(); return &source_locations_.back(); }
int InternedData::log_message_body_size() const { return static_cast<int>(log_message_body_.size()); }
void InternedData::clear_log_message_body() { log_message_body_.clear(); }
LogMessageBody* InternedData::add_log_message_body() { log_message_body_.emplace_back(); return &log_message_body_.back(); }
int InternedData::histogram_names_size() const { return static_cast<int>(histogram_names_.size()); }
void InternedData::clear_histogram_names() { histogram_names_.clear(); }
HistogramName* InternedData::add_histogram_names() { histogram_names_.emplace_back(); return &histogram_names_.back(); }
int InternedData::build_ids_size() const { return static_cast<int>(build_ids_.size()); }
void InternedData::clear_build_ids() { build_ids_.clear(); }
InternedString* InternedData::add_build_ids() { build_ids_.emplace_back(); return &build_ids_.back(); }
int InternedData::mapping_paths_size() const { return static_cast<int>(mapping_paths_.size()); }
void InternedData::clear_mapping_paths() { mapping_paths_.clear(); }
InternedString* InternedData::add_mapping_paths() { mapping_paths_.emplace_back(); return &mapping_paths_.back(); }
int InternedData::source_paths_size() const { return static_cast<int>(source_paths_.size()); }
void InternedData::clear_source_paths() { source_paths_.clear(); }
InternedString* InternedData::add_source_paths() { source_paths_.emplace_back(); return &source_paths_.back(); }
int InternedData::function_names_size() const { return static_cast<int>(function_names_.size()); }
void InternedData::clear_function_names() { function_names_.clear(); }
InternedString* InternedData::add_function_names() { function_names_.emplace_back(); return &function_names_.back(); }
int InternedData::profiled_frame_symbols_size() const { return static_cast<int>(profiled_frame_symbols_.size()); }
void InternedData::clear_profiled_frame_symbols() { profiled_frame_symbols_.clear(); }
ProfiledFrameSymbols* InternedData::add_profiled_frame_symbols() { profiled_frame_symbols_.emplace_back(); return &profiled_frame_symbols_.back(); }
int InternedData::mappings_size() const { return static_cast<int>(mappings_.size()); }
void InternedData::clear_mappings() { mappings_.clear(); }
Mapping* InternedData::add_mappings() { mappings_.emplace_back(); return &mappings_.back(); }
int InternedData::frames_size() const { return static_cast<int>(frames_.size()); }
void InternedData::clear_frames() { frames_.clear(); }
Frame* InternedData::add_frames() { frames_.emplace_back(); return &frames_.back(); }
int InternedData::callstacks_size() const { return static_cast<int>(callstacks_.size()); }
void InternedData::clear_callstacks() { callstacks_.clear(); }
Callstack* InternedData::add_callstacks() { callstacks_.emplace_back(); return &callstacks_.back(); }
int InternedData::vulkan_memory_keys_size() const { return static_cast<int>(vulkan_memory_keys_.size()); }
void InternedData::clear_vulkan_memory_keys() { vulkan_memory_keys_.clear(); }
InternedString* InternedData::add_vulkan_memory_keys() { vulkan_memory_keys_.emplace_back(); return &vulkan_memory_keys_.back(); }
int InternedData::graphics_contexts_size() const { return static_cast<int>(graphics_contexts_.size()); }
void InternedData::clear_graphics_contexts() { graphics_contexts_.clear(); }
InternedGraphicsContext* InternedData::add_graphics_contexts() { graphics_contexts_.emplace_back(); return &graphics_contexts_.back(); }
int InternedData::gpu_specifications_size() const { return static_cast<int>(gpu_specifications_.size()); }
void InternedData::clear_gpu_specifications() { gpu_specifications_.clear(); }
InternedGpuRenderStageSpecification* InternedData::add_gpu_specifications() { gpu_specifications_.emplace_back(); return &gpu_specifications_.back(); }
int InternedData::kernel_symbols_size() const { return static_cast<int>(kernel_symbols_.size()); }
void InternedData::clear_kernel_symbols() { kernel_symbols_.clear(); }
InternedString* InternedData::add_kernel_symbols() { kernel_symbols_.emplace_back(); return &kernel_symbols_.back(); }
bool InternedData::ParseFromArray(const void* raw, size_t size) {
  event_categories_.clear();
  event_names_.clear();
  debug_annotation_names_.clear();
  source_locations_.clear();
  log_message_body_.clear();
  histogram_names_.clear();
  build_ids_.clear();
  mapping_paths_.clear();
  source_paths_.clear();
  function_names_.clear();
  profiled_frame_symbols_.clear();
  mappings_.clear();
  frames_.clear();
  callstacks_.clear();
  vulkan_memory_keys_.clear();
  graphics_contexts_.clear();
  gpu_specifications_.clear();
  kernel_symbols_.clear();
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 1 /* event_categories */:
        event_categories_.emplace_back();
        event_categories_.back().ParseFromArray(field.data(), field.size());
        break;
      case 2 /* event_names */:
        event_names_.emplace_back();
        event_names_.back().ParseFromArray(field.data(), field.size());
        break;
      case 3 /* debug_annotation_names */:
        debug_annotation_names_.emplace_back();
        debug_annotation_names_.back().ParseFromArray(field.data(), field.size());
        break;
      case 4 /* source_locations */:
        source_locations_.emplace_back();
        source_locations_.back().ParseFromArray(field.data(), field.size());
        break;
      case 20 /* log_message_body */:
        log_message_body_.emplace_back();
        log_message_body_.back().ParseFromArray(field.data(), field.size());
        break;
      case 25 /* histogram_names */:
        histogram_names_.emplace_back();
        histogram_names_.back().ParseFromArray(field.data(), field.size());
        break;
      case 16 /* build_ids */:
        build_ids_.emplace_back();
        build_ids_.back().ParseFromArray(field.data(), field.size());
        break;
      case 17 /* mapping_paths */:
        mapping_paths_.emplace_back();
        mapping_paths_.back().ParseFromArray(field.data(), field.size());
        break;
      case 18 /* source_paths */:
        source_paths_.emplace_back();
        source_paths_.back().ParseFromArray(field.data(), field.size());
        break;
      case 5 /* function_names */:
        function_names_.emplace_back();
        function_names_.back().ParseFromArray(field.data(), field.size());
        break;
      case 21 /* profiled_frame_symbols */:
        profiled_frame_symbols_.emplace_back();
        profiled_frame_symbols_.back().ParseFromArray(field.data(), field.size());
        break;
      case 19 /* mappings */:
        mappings_.emplace_back();
        mappings_.back().ParseFromArray(field.data(), field.size());
        break;
      case 6 /* frames */:
        frames_.emplace_back();
        frames_.back().ParseFromArray(field.data(), field.size());
        break;
      case 7 /* callstacks */:
        callstacks_.emplace_back();
        callstacks_.back().ParseFromArray(field.data(), field.size());
        break;
      case 22 /* vulkan_memory_keys */:
        vulkan_memory_keys_.emplace_back();
        vulkan_memory_keys_.back().ParseFromArray(field.data(), field.size());
        break;
      case 23 /* graphics_contexts */:
        graphics_contexts_.emplace_back();
        graphics_contexts_.back().ParseFromArray(field.data(), field.size());
        break;
      case 24 /* gpu_specifications */:
        gpu_specifications_.emplace_back();
        gpu_specifications_.back().ParseFromArray(field.data(), field.size());
        break;
      case 26 /* kernel_symbols */:
        kernel_symbols_.emplace_back();
        kernel_symbols_.back().ParseFromArray(field.data(), field.size());
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string InternedData::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> InternedData::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void InternedData::Serialize(::protozero::Message* msg) const {
  // Field 1: event_categories
  for (auto& it : event_categories_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(1));
  }

  // Field 2: event_names
  for (auto& it : event_names_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(2));
  }

  // Field 3: debug_annotation_names
  for (auto& it : debug_annotation_names_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(3));
  }

  // Field 4: source_locations
  for (auto& it : source_locations_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(4));
  }

  // Field 20: log_message_body
  for (auto& it : log_message_body_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(20));
  }

  // Field 25: histogram_names
  for (auto& it : histogram_names_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(25));
  }

  // Field 16: build_ids
  for (auto& it : build_ids_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(16));
  }

  // Field 17: mapping_paths
  for (auto& it : mapping_paths_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(17));
  }

  // Field 18: source_paths
  for (auto& it : source_paths_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(18));
  }

  // Field 5: function_names
  for (auto& it : function_names_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(5));
  }

  // Field 21: profiled_frame_symbols
  for (auto& it : profiled_frame_symbols_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(21));
  }

  // Field 19: mappings
  for (auto& it : mappings_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(19));
  }

  // Field 6: frames
  for (auto& it : frames_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(6));
  }

  // Field 7: callstacks
  for (auto& it : callstacks_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(7));
  }

  // Field 22: vulkan_memory_keys
  for (auto& it : vulkan_memory_keys_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(22));
  }

  // Field 23: graphics_contexts
  for (auto& it : graphics_contexts_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(23));
  }

  // Field 24: gpu_specifications
  for (auto& it : gpu_specifications_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(24));
  }

  // Field 26: kernel_symbols
  for (auto& it : kernel_symbols_) {
    it.Serialize(msg->BeginNestedMessage<::protozero::Message>(26));
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}

}  // namespace perfetto
}  // namespace protos
}  // namespace gen
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
