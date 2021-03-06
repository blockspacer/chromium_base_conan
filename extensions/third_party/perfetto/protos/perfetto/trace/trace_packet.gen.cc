#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/scattered_heap_buffer.h"
// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif
#include "protos/perfetto/trace/trace_packet.gen.h"
#include "protos/perfetto/trace/test_event.gen.h"
#include "protos/perfetto/trace/trigger.gen.h"
#include "protos/perfetto/trace/track_event/track_event.gen.h"
#include "protos/perfetto/trace/track_event/source_location.gen.h"
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
#include "protos/perfetto/trace/track_event/track_descriptor.gen.h"
#include "protos/perfetto/trace/track_event/counter_descriptor.gen.h"
#include "protos/perfetto/trace/track_event/thread_descriptor.gen.h"
#include "protos/perfetto/trace/track_event/process_descriptor.gen.h"
#include "protos/perfetto/trace/track_event/chrome_thread_descriptor.gen.h"
#include "protos/perfetto/trace/track_event/chrome_process_descriptor.gen.h"
#include "protos/perfetto/trace/track_event/thread_descriptor.gen.h"
#include "protos/perfetto/trace/track_event/process_descriptor.gen.h"
#include "protos/perfetto/trace/trace_packet_defaults.gen.h"
#include "protos/perfetto/trace/system_info/cpu_info.gen.h"
#include "protos/perfetto/trace/system_info.gen.h"
#include "protos/perfetto/trace/sys_stats/sys_stats.gen.h"
#include "protos/perfetto/common/sys_stats_counters.gen.h"
#include "protos/perfetto/trace/ps/process_tree.gen.h"
#include "protos/perfetto/trace/ps/process_stats.gen.h"
#include "protos/perfetto/trace/profiling/smaps.gen.h"
#include "protos/perfetto/trace/profiling/profile_packet.gen.h"
#include "protos/perfetto/trace/profiling/profile_common.gen.h"
#include "protos/perfetto/trace/profiling/profile_common.gen.h"
#include "protos/perfetto/trace/profiling/heap_graph.gen.h"
#include "protos/perfetto/trace/profiling/deobfuscation.gen.h"
#include "protos/perfetto/trace/profiling/deobfuscation.gen.h"
#include "protos/perfetto/trace/power/power_rails.gen.h"
#include "protos/perfetto/trace/power/battery_counters.gen.h"
#include "protos/perfetto/trace/perfetto/tracing_service_event.gen.h"
#include "protos/perfetto/trace/perfetto/perfetto_metatrace.gen.h"
#include "protos/perfetto/trace/memory_graph.gen.h"
#include "protos/perfetto/trace/interned_data/interned_data.gen.h"
#include "protos/perfetto/trace/gpu/gpu_render_stage_event.gen.h"
#include "protos/perfetto/trace/gpu/vulkan_api_event.gen.h"
#include "protos/perfetto/trace/gpu/vulkan_memory_event.gen.h"
#include "protos/perfetto/trace/gpu/gpu_render_stage_event.gen.h"
#include "protos/perfetto/trace/gpu/gpu_log.gen.h"
#include "protos/perfetto/trace/gpu/gpu_counter_event.gen.h"
#include "protos/perfetto/common/gpu_counter_descriptor.gen.h"
#include "protos/perfetto/trace/ftrace/ftrace_stats.gen.h"
#include "protos/perfetto/trace/ftrace/ftrace_event_bundle.gen.h"
#include "protos/perfetto/trace/ftrace/ftrace_event.gen.h"
#include "protos/perfetto/trace/ftrace/generic.gen.h"
#include "protos/perfetto/trace/ftrace/workqueue.gen.h"
#include "protos/perfetto/trace/ftrace/vmscan.gen.h"
#include "protos/perfetto/trace/ftrace/thermal.gen.h"
#include "protos/perfetto/trace/ftrace/task.gen.h"
#include "protos/perfetto/trace/ftrace/systrace.gen.h"
#include "protos/perfetto/trace/ftrace/sync.gen.h"
#include "protos/perfetto/trace/ftrace/signal.gen.h"
#include "protos/perfetto/trace/ftrace/sde.gen.h"
#include "protos/perfetto/trace/ftrace/scm.gen.h"
#include "protos/perfetto/trace/ftrace/sched.gen.h"
#include "protos/perfetto/trace/ftrace/regulator.gen.h"
#include "protos/perfetto/trace/ftrace/raw_syscalls.gen.h"
#include "protos/perfetto/trace/ftrace/power.gen.h"
#include "protos/perfetto/trace/ftrace/oom.gen.h"
#include "protos/perfetto/trace/ftrace/mm_event.gen.h"
#include "protos/perfetto/trace/ftrace/mdss.gen.h"
#include "protos/perfetto/trace/ftrace/mali.gen.h"
#include "protos/perfetto/trace/ftrace/lowmemorykiller.gen.h"
#include "protos/perfetto/trace/ftrace/kmem.gen.h"
#include "protos/perfetto/trace/ftrace/irq.gen.h"
#include "protos/perfetto/trace/ftrace/ipi.gen.h"
#include "protos/perfetto/trace/ftrace/ion.gen.h"
#include "protos/perfetto/trace/ftrace/i2c.gen.h"
#include "protos/perfetto/trace/ftrace/gpu_mem.gen.h"
#include "protos/perfetto/trace/ftrace/g2d.gen.h"
#include "protos/perfetto/trace/ftrace/ftrace.gen.h"
#include "protos/perfetto/trace/ftrace/filemap.gen.h"
#include "protos/perfetto/trace/ftrace/fence.gen.h"
#include "protos/perfetto/trace/ftrace/fastrpc.gen.h"
#include "protos/perfetto/trace/ftrace/f2fs.gen.h"
#include "protos/perfetto/trace/ftrace/ext4.gen.h"
#include "protos/perfetto/trace/ftrace/dpu.gen.h"
#include "protos/perfetto/trace/ftrace/cpuhp.gen.h"
#include "protos/perfetto/trace/ftrace/compaction.gen.h"
#include "protos/perfetto/trace/ftrace/clk.gen.h"
#include "protos/perfetto/trace/ftrace/cgroup.gen.h"
#include "protos/perfetto/trace/ftrace/block.gen.h"
#include "protos/perfetto/trace/ftrace/binder.gen.h"
#include "protos/perfetto/trace/filesystem/inode_file_map.gen.h"
#include "protos/perfetto/trace/clock_snapshot.gen.h"
#include "protos/perfetto/common/builtin_clock.gen.h"
#include "protos/perfetto/trace/chrome/chrome_trace_event.gen.h"
#include "protos/perfetto/trace/chrome/chrome_metadata.gen.h"
#include "protos/perfetto/trace/chrome/chrome_benchmark_metadata.gen.h"
#include "protos/perfetto/trace/android/packages_list.gen.h"
#include "protos/perfetto/trace/android/initial_display_state.gen.h"
#include "protos/perfetto/trace/android/graphics_frame_event.gen.h"
#include "protos/perfetto/trace/android/gpu_mem_event.gen.h"
#include "protos/perfetto/trace/android/frame_timeline_event.gen.h"
#include "protos/perfetto/trace/android/android_log.gen.h"
#include "protos/perfetto/common/android_log_constants.gen.h"
#include "protos/perfetto/trace/extension_descriptor.gen.h"
#include "protos/perfetto/common/descriptor.gen.h"
#include "protos/perfetto/config/trace_config.gen.h"
#include "protos/perfetto/config/data_source_config.gen.h"
#include "protos/perfetto/config/track_event/track_event_config.gen.h"
#include "protos/perfetto/config/test_config.gen.h"
#include "protos/perfetto/config/sys_stats/sys_stats_config.gen.h"
#include "protos/perfetto/config/profiling/perf_event_config.gen.h"
#include "protos/perfetto/config/profiling/java_hprof_config.gen.h"
#include "protos/perfetto/config/profiling/heapprofd_config.gen.h"
#include "protos/perfetto/config/process_stats/process_stats_config.gen.h"
#include "protos/perfetto/config/power/android_power_config.gen.h"
#include "protos/perfetto/config/interceptor_config.gen.h"
#include "protos/perfetto/config/interceptors/console_config.gen.h"
#include "protos/perfetto/config/inode_file/inode_file_config.gen.h"
#include "protos/perfetto/config/gpu/vulkan_memory_config.gen.h"
#include "protos/perfetto/config/gpu/gpu_counter_config.gen.h"
#include "protos/perfetto/config/ftrace/ftrace_config.gen.h"
#include "protos/perfetto/config/chrome/chrome_config.gen.h"
#include "protos/perfetto/config/android/packages_list_config.gen.h"
#include "protos/perfetto/config/android/android_polled_state_config.gen.h"
#include "protos/perfetto/config/android/android_log_config.gen.h"
#include "protos/perfetto/common/trace_stats.gen.h"

namespace perfetto {
namespace protos {
namespace gen {

TracePacket::TracePacket() = default;
TracePacket::~TracePacket() = default;
TracePacket::TracePacket(const TracePacket&) = default;
TracePacket& TracePacket::operator=(const TracePacket&) = default;
TracePacket::TracePacket(TracePacket&&) noexcept = default;
TracePacket& TracePacket::operator=(TracePacket&&) = default;

bool TracePacket::operator==(const TracePacket& other) const {
  return unknown_fields_ == other.unknown_fields_
   && timestamp_ == other.timestamp_
   && timestamp_clock_id_ == other.timestamp_clock_id_
   && process_tree_ == other.process_tree_
   && process_stats_ == other.process_stats_
   && inode_file_map_ == other.inode_file_map_
   && chrome_events_ == other.chrome_events_
   && clock_snapshot_ == other.clock_snapshot_
   && sys_stats_ == other.sys_stats_
   && track_event_ == other.track_event_
   && trace_config_ == other.trace_config_
   && ftrace_stats_ == other.ftrace_stats_
   && trace_stats_ == other.trace_stats_
   && profile_packet_ == other.profile_packet_
   && streaming_allocation_ == other.streaming_allocation_
   && streaming_free_ == other.streaming_free_
   && battery_ == other.battery_
   && power_rails_ == other.power_rails_
   && android_log_ == other.android_log_
   && system_info_ == other.system_info_
   && trigger_ == other.trigger_
   && packages_list_ == other.packages_list_
   && chrome_benchmark_metadata_ == other.chrome_benchmark_metadata_
   && perfetto_metatrace_ == other.perfetto_metatrace_
   && chrome_metadata_ == other.chrome_metadata_
   && gpu_counter_event_ == other.gpu_counter_event_
   && gpu_render_stage_event_ == other.gpu_render_stage_event_
   && streaming_profile_packet_ == other.streaming_profile_packet_
   && heap_graph_ == other.heap_graph_
   && graphics_frame_event_ == other.graphics_frame_event_
   && vulkan_memory_event_ == other.vulkan_memory_event_
   && gpu_log_ == other.gpu_log_
   && vulkan_api_event_ == other.vulkan_api_event_
   && perf_sample_ == other.perf_sample_
   && cpu_info_ == other.cpu_info_
   && smaps_packet_ == other.smaps_packet_
   && service_event_ == other.service_event_
   && initial_display_state_ == other.initial_display_state_
   && gpu_mem_total_event_ == other.gpu_mem_total_event_
   && memory_tracker_snapshot_ == other.memory_tracker_snapshot_
   && frame_timeline_event_ == other.frame_timeline_event_
   && profiled_frame_symbols_ == other.profiled_frame_symbols_
   && module_symbols_ == other.module_symbols_
   && deobfuscation_mapping_ == other.deobfuscation_mapping_
   && track_descriptor_ == other.track_descriptor_
   && process_descriptor_ == other.process_descriptor_
   && thread_descriptor_ == other.thread_descriptor_
   && ftrace_events_ == other.ftrace_events_
   && synchronization_marker_ == other.synchronization_marker_
   && compressed_packets_ == other.compressed_packets_
   && extension_descriptor_ == other.extension_descriptor_
   && for_testing_ == other.for_testing_
   && trusted_uid_ == other.trusted_uid_
   && trusted_packet_sequence_id_ == other.trusted_packet_sequence_id_
   && interned_data_ == other.interned_data_
   && sequence_flags_ == other.sequence_flags_
   && incremental_state_cleared_ == other.incremental_state_cleared_
   && trace_packet_defaults_ == other.trace_packet_defaults_
   && previous_packet_dropped_ == other.previous_packet_dropped_;
}

bool TracePacket::ParseFromArray(const void* raw, size_t size) {
  unknown_fields_.clear();
  bool packed_error = false;

  ::protozero::ProtoDecoder dec(raw, size);
  for (auto field = dec.ReadField(); field.valid(); field = dec.ReadField()) {
    if (field.id() < _has_field_.size()) {
      _has_field_.set(field.id());
    }
    switch (field.id()) {
      case 8 /* timestamp */:
        field.get(&timestamp_);
        break;
      case 58 /* timestamp_clock_id */:
        field.get(&timestamp_clock_id_);
        break;
      case 2 /* process_tree */:
        (*process_tree_).ParseFromArray(field.data(), field.size());
        break;
      case 9 /* process_stats */:
        (*process_stats_).ParseFromArray(field.data(), field.size());
        break;
      case 4 /* inode_file_map */:
        (*inode_file_map_).ParseFromArray(field.data(), field.size());
        break;
      case 5 /* chrome_events */:
        (*chrome_events_).ParseFromArray(field.data(), field.size());
        break;
      case 6 /* clock_snapshot */:
        (*clock_snapshot_).ParseFromArray(field.data(), field.size());
        break;
      case 7 /* sys_stats */:
        (*sys_stats_).ParseFromArray(field.data(), field.size());
        break;
      case 11 /* track_event */:
        (*track_event_).ParseFromArray(field.data(), field.size());
        break;
      case 33 /* trace_config */:
        (*trace_config_).ParseFromArray(field.data(), field.size());
        break;
      case 34 /* ftrace_stats */:
        (*ftrace_stats_).ParseFromArray(field.data(), field.size());
        break;
      case 35 /* trace_stats */:
        (*trace_stats_).ParseFromArray(field.data(), field.size());
        break;
      case 37 /* profile_packet */:
        (*profile_packet_).ParseFromArray(field.data(), field.size());
        break;
      case 74 /* streaming_allocation */:
        (*streaming_allocation_).ParseFromArray(field.data(), field.size());
        break;
      case 75 /* streaming_free */:
        (*streaming_free_).ParseFromArray(field.data(), field.size());
        break;
      case 38 /* battery */:
        (*battery_).ParseFromArray(field.data(), field.size());
        break;
      case 40 /* power_rails */:
        (*power_rails_).ParseFromArray(field.data(), field.size());
        break;
      case 39 /* android_log */:
        (*android_log_).ParseFromArray(field.data(), field.size());
        break;
      case 45 /* system_info */:
        (*system_info_).ParseFromArray(field.data(), field.size());
        break;
      case 46 /* trigger */:
        (*trigger_).ParseFromArray(field.data(), field.size());
        break;
      case 47 /* packages_list */:
        (*packages_list_).ParseFromArray(field.data(), field.size());
        break;
      case 48 /* chrome_benchmark_metadata */:
        (*chrome_benchmark_metadata_).ParseFromArray(field.data(), field.size());
        break;
      case 49 /* perfetto_metatrace */:
        (*perfetto_metatrace_).ParseFromArray(field.data(), field.size());
        break;
      case 51 /* chrome_metadata */:
        (*chrome_metadata_).ParseFromArray(field.data(), field.size());
        break;
      case 52 /* gpu_counter_event */:
        (*gpu_counter_event_).ParseFromArray(field.data(), field.size());
        break;
      case 53 /* gpu_render_stage_event */:
        (*gpu_render_stage_event_).ParseFromArray(field.data(), field.size());
        break;
      case 54 /* streaming_profile_packet */:
        (*streaming_profile_packet_).ParseFromArray(field.data(), field.size());
        break;
      case 56 /* heap_graph */:
        (*heap_graph_).ParseFromArray(field.data(), field.size());
        break;
      case 57 /* graphics_frame_event */:
        (*graphics_frame_event_).ParseFromArray(field.data(), field.size());
        break;
      case 62 /* vulkan_memory_event */:
        (*vulkan_memory_event_).ParseFromArray(field.data(), field.size());
        break;
      case 63 /* gpu_log */:
        (*gpu_log_).ParseFromArray(field.data(), field.size());
        break;
      case 65 /* vulkan_api_event */:
        (*vulkan_api_event_).ParseFromArray(field.data(), field.size());
        break;
      case 66 /* perf_sample */:
        (*perf_sample_).ParseFromArray(field.data(), field.size());
        break;
      case 67 /* cpu_info */:
        (*cpu_info_).ParseFromArray(field.data(), field.size());
        break;
      case 68 /* smaps_packet */:
        (*smaps_packet_).ParseFromArray(field.data(), field.size());
        break;
      case 69 /* service_event */:
        (*service_event_).ParseFromArray(field.data(), field.size());
        break;
      case 70 /* initial_display_state */:
        (*initial_display_state_).ParseFromArray(field.data(), field.size());
        break;
      case 71 /* gpu_mem_total_event */:
        (*gpu_mem_total_event_).ParseFromArray(field.data(), field.size());
        break;
      case 73 /* memory_tracker_snapshot */:
        (*memory_tracker_snapshot_).ParseFromArray(field.data(), field.size());
        break;
      case 76 /* frame_timeline_event */:
        (*frame_timeline_event_).ParseFromArray(field.data(), field.size());
        break;
      case 55 /* profiled_frame_symbols */:
        (*profiled_frame_symbols_).ParseFromArray(field.data(), field.size());
        break;
      case 61 /* module_symbols */:
        (*module_symbols_).ParseFromArray(field.data(), field.size());
        break;
      case 64 /* deobfuscation_mapping */:
        (*deobfuscation_mapping_).ParseFromArray(field.data(), field.size());
        break;
      case 60 /* track_descriptor */:
        (*track_descriptor_).ParseFromArray(field.data(), field.size());
        break;
      case 43 /* process_descriptor */:
        (*process_descriptor_).ParseFromArray(field.data(), field.size());
        break;
      case 44 /* thread_descriptor */:
        (*thread_descriptor_).ParseFromArray(field.data(), field.size());
        break;
      case 1 /* ftrace_events */:
        (*ftrace_events_).ParseFromArray(field.data(), field.size());
        break;
      case 36 /* synchronization_marker */:
        field.get(&synchronization_marker_);
        break;
      case 50 /* compressed_packets */:
        field.get(&compressed_packets_);
        break;
      case 72 /* extension_descriptor */:
        (*extension_descriptor_).ParseFromArray(field.data(), field.size());
        break;
      case 900 /* for_testing */:
        (*for_testing_).ParseFromArray(field.data(), field.size());
        break;
      case 3 /* trusted_uid */:
        field.get(&trusted_uid_);
        break;
      case 10 /* trusted_packet_sequence_id */:
        field.get(&trusted_packet_sequence_id_);
        break;
      case 12 /* interned_data */:
        (*interned_data_).ParseFromArray(field.data(), field.size());
        break;
      case 13 /* sequence_flags */:
        field.get(&sequence_flags_);
        break;
      case 41 /* incremental_state_cleared */:
        field.get(&incremental_state_cleared_);
        break;
      case 59 /* trace_packet_defaults */:
        (*trace_packet_defaults_).ParseFromArray(field.data(), field.size());
        break;
      case 42 /* previous_packet_dropped */:
        field.get(&previous_packet_dropped_);
        break;
      default:
        field.SerializeAndAppendTo(&unknown_fields_);
        break;
    }
  }
  return !packed_error && !dec.bytes_left();
}

std::string TracePacket::SerializeAsString() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsString();
}

std::vector<uint8_t> TracePacket::SerializeAsArray() const {
  ::protozero::HeapBuffered<::protozero::Message> msg;
  Serialize(msg.get());
  return msg.SerializeAsArray();
}

void TracePacket::Serialize(::protozero::Message* msg) const {
  // Field 8: timestamp
  if (_has_field_[8]) {
    msg->AppendVarInt(8, timestamp_);
  }

  // Field 58: timestamp_clock_id
  if (_has_field_[58]) {
    msg->AppendVarInt(58, timestamp_clock_id_);
  }

  // Field 2: process_tree
  if (_has_field_[2]) {
    (*process_tree_).Serialize(msg->BeginNestedMessage<::protozero::Message>(2));
  }

  // Field 9: process_stats
  if (_has_field_[9]) {
    (*process_stats_).Serialize(msg->BeginNestedMessage<::protozero::Message>(9));
  }

  // Field 4: inode_file_map
  if (_has_field_[4]) {
    (*inode_file_map_).Serialize(msg->BeginNestedMessage<::protozero::Message>(4));
  }

  // Field 5: chrome_events
  if (_has_field_[5]) {
    (*chrome_events_).Serialize(msg->BeginNestedMessage<::protozero::Message>(5));
  }

  // Field 6: clock_snapshot
  if (_has_field_[6]) {
    (*clock_snapshot_).Serialize(msg->BeginNestedMessage<::protozero::Message>(6));
  }

  // Field 7: sys_stats
  if (_has_field_[7]) {
    (*sys_stats_).Serialize(msg->BeginNestedMessage<::protozero::Message>(7));
  }

  // Field 11: track_event
  if (_has_field_[11]) {
    (*track_event_).Serialize(msg->BeginNestedMessage<::protozero::Message>(11));
  }

  // Field 33: trace_config
  if (_has_field_[33]) {
    (*trace_config_).Serialize(msg->BeginNestedMessage<::protozero::Message>(33));
  }

  // Field 34: ftrace_stats
  if (_has_field_[34]) {
    (*ftrace_stats_).Serialize(msg->BeginNestedMessage<::protozero::Message>(34));
  }

  // Field 35: trace_stats
  if (_has_field_[35]) {
    (*trace_stats_).Serialize(msg->BeginNestedMessage<::protozero::Message>(35));
  }

  // Field 37: profile_packet
  if (_has_field_[37]) {
    (*profile_packet_).Serialize(msg->BeginNestedMessage<::protozero::Message>(37));
  }

  // Field 74: streaming_allocation
  if (_has_field_[74]) {
    (*streaming_allocation_).Serialize(msg->BeginNestedMessage<::protozero::Message>(74));
  }

  // Field 75: streaming_free
  if (_has_field_[75]) {
    (*streaming_free_).Serialize(msg->BeginNestedMessage<::protozero::Message>(75));
  }

  // Field 38: battery
  if (_has_field_[38]) {
    (*battery_).Serialize(msg->BeginNestedMessage<::protozero::Message>(38));
  }

  // Field 40: power_rails
  if (_has_field_[40]) {
    (*power_rails_).Serialize(msg->BeginNestedMessage<::protozero::Message>(40));
  }

  // Field 39: android_log
  if (_has_field_[39]) {
    (*android_log_).Serialize(msg->BeginNestedMessage<::protozero::Message>(39));
  }

  // Field 45: system_info
  if (_has_field_[45]) {
    (*system_info_).Serialize(msg->BeginNestedMessage<::protozero::Message>(45));
  }

  // Field 46: trigger
  if (_has_field_[46]) {
    (*trigger_).Serialize(msg->BeginNestedMessage<::protozero::Message>(46));
  }

  // Field 47: packages_list
  if (_has_field_[47]) {
    (*packages_list_).Serialize(msg->BeginNestedMessage<::protozero::Message>(47));
  }

  // Field 48: chrome_benchmark_metadata
  if (_has_field_[48]) {
    (*chrome_benchmark_metadata_).Serialize(msg->BeginNestedMessage<::protozero::Message>(48));
  }

  // Field 49: perfetto_metatrace
  if (_has_field_[49]) {
    (*perfetto_metatrace_).Serialize(msg->BeginNestedMessage<::protozero::Message>(49));
  }

  // Field 51: chrome_metadata
  if (_has_field_[51]) {
    (*chrome_metadata_).Serialize(msg->BeginNestedMessage<::protozero::Message>(51));
  }

  // Field 52: gpu_counter_event
  if (_has_field_[52]) {
    (*gpu_counter_event_).Serialize(msg->BeginNestedMessage<::protozero::Message>(52));
  }

  // Field 53: gpu_render_stage_event
  if (_has_field_[53]) {
    (*gpu_render_stage_event_).Serialize(msg->BeginNestedMessage<::protozero::Message>(53));
  }

  // Field 54: streaming_profile_packet
  if (_has_field_[54]) {
    (*streaming_profile_packet_).Serialize(msg->BeginNestedMessage<::protozero::Message>(54));
  }

  // Field 56: heap_graph
  if (_has_field_[56]) {
    (*heap_graph_).Serialize(msg->BeginNestedMessage<::protozero::Message>(56));
  }

  // Field 57: graphics_frame_event
  if (_has_field_[57]) {
    (*graphics_frame_event_).Serialize(msg->BeginNestedMessage<::protozero::Message>(57));
  }

  // Field 62: vulkan_memory_event
  if (_has_field_[62]) {
    (*vulkan_memory_event_).Serialize(msg->BeginNestedMessage<::protozero::Message>(62));
  }

  // Field 63: gpu_log
  if (_has_field_[63]) {
    (*gpu_log_).Serialize(msg->BeginNestedMessage<::protozero::Message>(63));
  }

  // Field 65: vulkan_api_event
  if (_has_field_[65]) {
    (*vulkan_api_event_).Serialize(msg->BeginNestedMessage<::protozero::Message>(65));
  }

  // Field 66: perf_sample
  if (_has_field_[66]) {
    (*perf_sample_).Serialize(msg->BeginNestedMessage<::protozero::Message>(66));
  }

  // Field 67: cpu_info
  if (_has_field_[67]) {
    (*cpu_info_).Serialize(msg->BeginNestedMessage<::protozero::Message>(67));
  }

  // Field 68: smaps_packet
  if (_has_field_[68]) {
    (*smaps_packet_).Serialize(msg->BeginNestedMessage<::protozero::Message>(68));
  }

  // Field 69: service_event
  if (_has_field_[69]) {
    (*service_event_).Serialize(msg->BeginNestedMessage<::protozero::Message>(69));
  }

  // Field 70: initial_display_state
  if (_has_field_[70]) {
    (*initial_display_state_).Serialize(msg->BeginNestedMessage<::protozero::Message>(70));
  }

  // Field 71: gpu_mem_total_event
  if (_has_field_[71]) {
    (*gpu_mem_total_event_).Serialize(msg->BeginNestedMessage<::protozero::Message>(71));
  }

  // Field 73: memory_tracker_snapshot
  if (_has_field_[73]) {
    (*memory_tracker_snapshot_).Serialize(msg->BeginNestedMessage<::protozero::Message>(73));
  }

  // Field 76: frame_timeline_event
  if (_has_field_[76]) {
    (*frame_timeline_event_).Serialize(msg->BeginNestedMessage<::protozero::Message>(76));
  }

  // Field 55: profiled_frame_symbols
  if (_has_field_[55]) {
    (*profiled_frame_symbols_).Serialize(msg->BeginNestedMessage<::protozero::Message>(55));
  }

  // Field 61: module_symbols
  if (_has_field_[61]) {
    (*module_symbols_).Serialize(msg->BeginNestedMessage<::protozero::Message>(61));
  }

  // Field 64: deobfuscation_mapping
  if (_has_field_[64]) {
    (*deobfuscation_mapping_).Serialize(msg->BeginNestedMessage<::protozero::Message>(64));
  }

  // Field 60: track_descriptor
  if (_has_field_[60]) {
    (*track_descriptor_).Serialize(msg->BeginNestedMessage<::protozero::Message>(60));
  }

  // Field 43: process_descriptor
  if (_has_field_[43]) {
    (*process_descriptor_).Serialize(msg->BeginNestedMessage<::protozero::Message>(43));
  }

  // Field 44: thread_descriptor
  if (_has_field_[44]) {
    (*thread_descriptor_).Serialize(msg->BeginNestedMessage<::protozero::Message>(44));
  }

  // Field 1: ftrace_events
  if (_has_field_[1]) {
    (*ftrace_events_).Serialize(msg->BeginNestedMessage<::protozero::Message>(1));
  }

  // Field 36: synchronization_marker
  if (_has_field_[36]) {
    msg->AppendString(36, synchronization_marker_);
  }

  // Field 50: compressed_packets
  if (_has_field_[50]) {
    msg->AppendString(50, compressed_packets_);
  }

  // Field 72: extension_descriptor
  if (_has_field_[72]) {
    (*extension_descriptor_).Serialize(msg->BeginNestedMessage<::protozero::Message>(72));
  }

  // Field 900: for_testing
  if (_has_field_[900]) {
    (*for_testing_).Serialize(msg->BeginNestedMessage<::protozero::Message>(900));
  }

  // Field 3: trusted_uid
  if (_has_field_[3]) {
    msg->AppendVarInt(3, trusted_uid_);
  }

  // Field 10: trusted_packet_sequence_id
  if (_has_field_[10]) {
    msg->AppendVarInt(10, trusted_packet_sequence_id_);
  }

  // Field 12: interned_data
  if (_has_field_[12]) {
    (*interned_data_).Serialize(msg->BeginNestedMessage<::protozero::Message>(12));
  }

  // Field 13: sequence_flags
  if (_has_field_[13]) {
    msg->AppendVarInt(13, sequence_flags_);
  }

  // Field 41: incremental_state_cleared
  if (_has_field_[41]) {
    msg->AppendTinyVarInt(41, incremental_state_cleared_);
  }

  // Field 59: trace_packet_defaults
  if (_has_field_[59]) {
    (*trace_packet_defaults_).Serialize(msg->BeginNestedMessage<::protozero::Message>(59));
  }

  // Field 42: previous_packet_dropped
  if (_has_field_[42]) {
    msg->AppendTinyVarInt(42, previous_packet_dropped_);
  }

  msg->AppendRawProtoBytes(unknown_fields_.data(), unknown_fields_.size());
}

}  // namespace perfetto
}  // namespace protos
}  // namespace gen
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
