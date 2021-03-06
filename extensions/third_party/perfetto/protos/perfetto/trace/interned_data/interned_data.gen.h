// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_INTERNED_DATA_INTERNED_DATA_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_INTERNED_DATA_INTERNED_DATA_PROTO_CPP_H_

#include <stdint.h>
#include <bitset>
#include <vector>
#include <string>
#include <type_traits>

#include "perfetto/protozero/cpp_message_obj.h"
#include "perfetto/protozero/copyable_ptr.h"
#include "perfetto/base/export.h"

namespace perfetto {
namespace protos {
namespace gen {
class InternedData;
class InternedString;
class InternedGpuRenderStageSpecification;
class InternedGraphicsContext;
class Callstack;
class Frame;
class Mapping;
class ProfiledFrameSymbols;
class HistogramName;
class LogMessageBody;
class SourceLocation;
class DebugAnnotationName;
class EventName;
class EventCategory;
enum InternedGpuRenderStageSpecification_RenderStageCategory : int;
enum InternedGraphicsContext_Api : int;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {

class PERFETTO_EXPORT InternedData : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kEventCategoriesFieldNumber = 1,
    kEventNamesFieldNumber = 2,
    kDebugAnnotationNamesFieldNumber = 3,
    kSourceLocationsFieldNumber = 4,
    kLogMessageBodyFieldNumber = 20,
    kHistogramNamesFieldNumber = 25,
    kBuildIdsFieldNumber = 16,
    kMappingPathsFieldNumber = 17,
    kSourcePathsFieldNumber = 18,
    kFunctionNamesFieldNumber = 5,
    kProfiledFrameSymbolsFieldNumber = 21,
    kMappingsFieldNumber = 19,
    kFramesFieldNumber = 6,
    kCallstacksFieldNumber = 7,
    kVulkanMemoryKeysFieldNumber = 22,
    kGraphicsContextsFieldNumber = 23,
    kGpuSpecificationsFieldNumber = 24,
    kKernelSymbolsFieldNumber = 26,
  };

  InternedData();
  ~InternedData() override;
  InternedData(InternedData&&) noexcept;
  InternedData& operator=(InternedData&&);
  InternedData(const InternedData&);
  InternedData& operator=(const InternedData&);
  bool operator==(const InternedData&) const;
  bool operator!=(const InternedData& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  const std::vector<EventCategory>& event_categories() const { return event_categories_; }
  std::vector<EventCategory>* mutable_event_categories() { return &event_categories_; }
  int event_categories_size() const;
  void clear_event_categories();
  EventCategory* add_event_categories();

  const std::vector<EventName>& event_names() const { return event_names_; }
  std::vector<EventName>* mutable_event_names() { return &event_names_; }
  int event_names_size() const;
  void clear_event_names();
  EventName* add_event_names();

  const std::vector<DebugAnnotationName>& debug_annotation_names() const { return debug_annotation_names_; }
  std::vector<DebugAnnotationName>* mutable_debug_annotation_names() { return &debug_annotation_names_; }
  int debug_annotation_names_size() const;
  void clear_debug_annotation_names();
  DebugAnnotationName* add_debug_annotation_names();

  const std::vector<SourceLocation>& source_locations() const { return source_locations_; }
  std::vector<SourceLocation>* mutable_source_locations() { return &source_locations_; }
  int source_locations_size() const;
  void clear_source_locations();
  SourceLocation* add_source_locations();

  const std::vector<LogMessageBody>& log_message_body() const { return log_message_body_; }
  std::vector<LogMessageBody>* mutable_log_message_body() { return &log_message_body_; }
  int log_message_body_size() const;
  void clear_log_message_body();
  LogMessageBody* add_log_message_body();

  const std::vector<HistogramName>& histogram_names() const { return histogram_names_; }
  std::vector<HistogramName>* mutable_histogram_names() { return &histogram_names_; }
  int histogram_names_size() const;
  void clear_histogram_names();
  HistogramName* add_histogram_names();

  const std::vector<InternedString>& build_ids() const { return build_ids_; }
  std::vector<InternedString>* mutable_build_ids() { return &build_ids_; }
  int build_ids_size() const;
  void clear_build_ids();
  InternedString* add_build_ids();

  const std::vector<InternedString>& mapping_paths() const { return mapping_paths_; }
  std::vector<InternedString>* mutable_mapping_paths() { return &mapping_paths_; }
  int mapping_paths_size() const;
  void clear_mapping_paths();
  InternedString* add_mapping_paths();

  const std::vector<InternedString>& source_paths() const { return source_paths_; }
  std::vector<InternedString>* mutable_source_paths() { return &source_paths_; }
  int source_paths_size() const;
  void clear_source_paths();
  InternedString* add_source_paths();

  const std::vector<InternedString>& function_names() const { return function_names_; }
  std::vector<InternedString>* mutable_function_names() { return &function_names_; }
  int function_names_size() const;
  void clear_function_names();
  InternedString* add_function_names();

  const std::vector<ProfiledFrameSymbols>& profiled_frame_symbols() const { return profiled_frame_symbols_; }
  std::vector<ProfiledFrameSymbols>* mutable_profiled_frame_symbols() { return &profiled_frame_symbols_; }
  int profiled_frame_symbols_size() const;
  void clear_profiled_frame_symbols();
  ProfiledFrameSymbols* add_profiled_frame_symbols();

  const std::vector<Mapping>& mappings() const { return mappings_; }
  std::vector<Mapping>* mutable_mappings() { return &mappings_; }
  int mappings_size() const;
  void clear_mappings();
  Mapping* add_mappings();

  const std::vector<Frame>& frames() const { return frames_; }
  std::vector<Frame>* mutable_frames() { return &frames_; }
  int frames_size() const;
  void clear_frames();
  Frame* add_frames();

  const std::vector<Callstack>& callstacks() const { return callstacks_; }
  std::vector<Callstack>* mutable_callstacks() { return &callstacks_; }
  int callstacks_size() const;
  void clear_callstacks();
  Callstack* add_callstacks();

  const std::vector<InternedString>& vulkan_memory_keys() const { return vulkan_memory_keys_; }
  std::vector<InternedString>* mutable_vulkan_memory_keys() { return &vulkan_memory_keys_; }
  int vulkan_memory_keys_size() const;
  void clear_vulkan_memory_keys();
  InternedString* add_vulkan_memory_keys();

  const std::vector<InternedGraphicsContext>& graphics_contexts() const { return graphics_contexts_; }
  std::vector<InternedGraphicsContext>* mutable_graphics_contexts() { return &graphics_contexts_; }
  int graphics_contexts_size() const;
  void clear_graphics_contexts();
  InternedGraphicsContext* add_graphics_contexts();

  const std::vector<InternedGpuRenderStageSpecification>& gpu_specifications() const { return gpu_specifications_; }
  std::vector<InternedGpuRenderStageSpecification>* mutable_gpu_specifications() { return &gpu_specifications_; }
  int gpu_specifications_size() const;
  void clear_gpu_specifications();
  InternedGpuRenderStageSpecification* add_gpu_specifications();

  const std::vector<InternedString>& kernel_symbols() const { return kernel_symbols_; }
  std::vector<InternedString>* mutable_kernel_symbols() { return &kernel_symbols_; }
  int kernel_symbols_size() const;
  void clear_kernel_symbols();
  InternedString* add_kernel_symbols();

 private:
  std::vector<EventCategory> event_categories_;
  std::vector<EventName> event_names_;
  std::vector<DebugAnnotationName> debug_annotation_names_;
  std::vector<SourceLocation> source_locations_;
  std::vector<LogMessageBody> log_message_body_;
  std::vector<HistogramName> histogram_names_;
  std::vector<InternedString> build_ids_;
  std::vector<InternedString> mapping_paths_;
  std::vector<InternedString> source_paths_;
  std::vector<InternedString> function_names_;
  std::vector<ProfiledFrameSymbols> profiled_frame_symbols_;
  std::vector<Mapping> mappings_;
  std::vector<Frame> frames_;
  std::vector<Callstack> callstacks_;
  std::vector<InternedString> vulkan_memory_keys_;
  std::vector<InternedGraphicsContext> graphics_contexts_;
  std::vector<InternedGpuRenderStageSpecification> gpu_specifications_;
  std::vector<InternedString> kernel_symbols_;

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<27> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_INTERNED_DATA_INTERNED_DATA_PROTO_CPP_H_
