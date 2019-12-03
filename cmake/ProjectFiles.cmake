include_guard( DIRECTORY )

if(ENABLE_UKM)
  list(APPEND BASE_SOURCES
     ${BASE_SOURCES_PATH}metrics/ukm_source_id.cc
     ${BASE_SOURCES_PATH}metrics/ukm_source_id.h
  )
endif(ENABLE_UKM)

if(BASE_USE_JSON)
  list(APPEND BASE_SOURCES
     ${BASE_SOURCES_PATH}json/json_file_value_serializer.cc
     ${BASE_SOURCES_PATH}json/json_file_value_serializer.h
     ${BASE_SOURCES_PATH}json/json_parser.cc
     ${BASE_SOURCES_PATH}json/json_parser.h
     ${BASE_SOURCES_PATH}json/json_reader.cc
     ${BASE_SOURCES_PATH}json/json_reader.h
     ${BASE_SOURCES_PATH}json/json_string_value_serializer.cc
     ${BASE_SOURCES_PATH}json/json_string_value_serializer.h
     ${BASE_SOURCES_PATH}json/json_value_converter.cc
     ${BASE_SOURCES_PATH}json/json_value_converter.h
     ${BASE_SOURCES_PATH}json/json_writer.cc
     ${BASE_SOURCES_PATH}json/json_writer.h
     ${BASE_SOURCES_PATH}json/string_escape.cc
     ${BASE_SOURCES_PATH}json/string_escape.h
  )
endif(BASE_USE_JSON)

list(APPEND BASE_SOURCES
  # sources = [
  #${BASE_SOURCES_PATH}critical_closure_internal_ios.mm
  ${BASE_SOURCES_PATH}debug/activity_analyzer.cc
  ${BASE_SOURCES_PATH}debug/activity_analyzer.h
  ${BASE_SOURCES_PATH}debug/activity_tracker.cc
  ${BASE_SOURCES_PATH}debug/activity_tracker.h
  ###${BASE_SOURCES_PATH}debug/alias.cc
  ###${BASE_SOURCES_PATH}debug/alias.h
  ### ${BASE_SOURCES_PATH}debug/asan_invalid_access.cc
  ### ${BASE_SOURCES_PATH}debug/asan_invalid_access.h
  #${BASE_SOURCES_PATH}debug/close_handle_hook_win.cc
  #${BASE_SOURCES_PATH}debug/close_handle_hook_win.h
  ${BASE_SOURCES_PATH}debug/crash_logging.cc
  ${BASE_SOURCES_PATH}debug/crash_logging.h
  ${BASE_SOURCES_PATH}debug/debugger.cc
  ${BASE_SOURCES_PATH}debug/debugger.h
  #${BASE_SOURCES_PATH}debug/debugger_win.cc
  ${BASE_SOURCES_PATH}debug/dump_without_crashing.cc
  ${BASE_SOURCES_PATH}debug/dump_without_crashing.h
  #${BASE_SOURCES_PATH}debug/gdi_debug_util_win.cc
  #${BASE_SOURCES_PATH}debug/gdi_debug_util_win.h
  #${BASE_SOURCES_PATH}debug/invalid_access_win.cc
  #${BASE_SOURCES_PATH}debug/invalid_access_win.h
  ${BASE_SOURCES_PATH}debug/leak_annotations.h
  ${BASE_SOURCES_PATH}debug/leak_tracker.h
  ${BASE_SOURCES_PATH}debug/profiler.cc
  ${BASE_SOURCES_PATH}debug/profiler.h
  ${BASE_SOURCES_PATH}debug/stack_trace.cc
  ${BASE_SOURCES_PATH}debug/stack_trace.h
  #${BASE_SOURCES_PATH}debug/stack_trace_android.cc
  #${BASE_SOURCES_PATH}debug/stack_trace_win.cc
  ${BASE_SOURCES_PATH}debug/task_trace.cc
  ${BASE_SOURCES_PATH}debug/task_trace.h
  ${BASE_SOURCES_PATH}i18n/base_i18n_export.h
  ${BASE_SOURCES_PATH}i18n/base_i18n_switches.cc
  ${BASE_SOURCES_PATH}i18n/base_i18n_switches.h
  ${BASE_SOURCES_PATH}i18n/break_iterator.cc
  ${BASE_SOURCES_PATH}i18n/break_iterator.h
  ${BASE_SOURCES_PATH}i18n/case_conversion.cc
  ${BASE_SOURCES_PATH}i18n/case_conversion.h
  ${BASE_SOURCES_PATH}i18n/char_iterator.cc
  ${BASE_SOURCES_PATH}i18n/char_iterator.h
  ${BASE_SOURCES_PATH}i18n/character_encoding.cc
  ${BASE_SOURCES_PATH}i18n/character_encoding.h
  ${BASE_SOURCES_PATH}i18n/encoding_detection.cc
  ${BASE_SOURCES_PATH}i18n/encoding_detection.h
  ${BASE_SOURCES_PATH}i18n/file_util_icu.cc
  ${BASE_SOURCES_PATH}i18n/file_util_icu.h
  ${BASE_SOURCES_PATH}i18n/i18n_constants.cc
  ${BASE_SOURCES_PATH}i18n/i18n_constants.h
  ${BASE_SOURCES_PATH}i18n/icu_string_conversions.cc
  ${BASE_SOURCES_PATH}i18n/icu_string_conversions.h
  ${BASE_SOURCES_PATH}i18n/icu_util.cc
  ${BASE_SOURCES_PATH}i18n/icu_util.h
  ${BASE_SOURCES_PATH}i18n/message_formatter.cc
  ${BASE_SOURCES_PATH}i18n/message_formatter.h
  ${BASE_SOURCES_PATH}i18n/number_formatting.cc
  ${BASE_SOURCES_PATH}i18n/number_formatting.h
  ${BASE_SOURCES_PATH}i18n/rtl.cc
  ${BASE_SOURCES_PATH}i18n/rtl.h
  ${BASE_SOURCES_PATH}i18n/streaming_utf8_validator.cc
  ${BASE_SOURCES_PATH}i18n/streaming_utf8_validator.h
  ${BASE_SOURCES_PATH}i18n/string_compare.cc
  ${BASE_SOURCES_PATH}i18n/string_compare.h
  ${BASE_SOURCES_PATH}i18n/string_search.cc
  ${BASE_SOURCES_PATH}i18n/string_search.h
  ${BASE_SOURCES_PATH}i18n/time_formatting.cc
  ${BASE_SOURCES_PATH}i18n/time_formatting.h
  ${BASE_SOURCES_PATH}i18n/timezone.cc
  ${BASE_SOURCES_PATH}i18n/timezone.h
  ${BASE_SOURCES_PATH}i18n/unicodestring.h
  ${BASE_SOURCES_PATH}i18n/utf8_validator_tables.cc
  ${BASE_SOURCES_PATH}i18n/utf8_validator_tables.h
  # ]
  # defines = [ "BASE_I18N_IMPLEMENTATION" ]
  # configs += [ "//build/config/compiler:wexit_time_destructors" ]
  # public_deps = [
  #   "//third_party/ced",
  #   "//third_party/icu",
  # ]
  #
  ${BASE_SOURCES_PATH}allocator/allocator_check.cc
  ${BASE_SOURCES_PATH}allocator/allocator_check.h
  ${BASE_SOURCES_PATH}allocator/allocator_extension.cc
  ${BASE_SOURCES_PATH}allocator/allocator_extension.h
  #${BASE_SOURCES_PATH}allocator/allocator_interception_mac.h
  #${BASE_SOURCES_PATH}allocator/allocator_interception_mac.mm
  #${BASE_SOURCES_PATH}allocator/malloc_zone_functions_mac.cc
  #${BASE_SOURCES_PATH}allocator/malloc_zone_functions_mac.h
  ${BASE_SOURCES_PATH}at_exit.cc
  ${BASE_SOURCES_PATH}at_exit.h
  ${BASE_SOURCES_PATH}atomic_ref_count.h
  ${BASE_SOURCES_PATH}atomic_sequence_num.h
  ${BASE_SOURCES_PATH}atomicops.h
  ${BASE_SOURCES_PATH}atomicops_internals_atomicword_compat.h
  #${BASE_SOURCES_PATH}atomicops_internals_x86_msvc.h
  ${BASE_SOURCES_PATH}auto_reset.h
  ${BASE_SOURCES_PATH}barrier_closure.cc
  ${BASE_SOURCES_PATH}barrier_closure.h
  ${BASE_SOURCES_PATH}base64.cc
  ${BASE_SOURCES_PATH}base64.h
  ${BASE_SOURCES_PATH}base64url.cc
  ${BASE_SOURCES_PATH}base64url.h
  ${BASE_SOURCES_PATH}base_export.h
  ${BASE_SOURCES_PATH}base_switches.h
  ${BASE_SOURCES_PATH}big_endian.cc
  ${BASE_SOURCES_PATH}big_endian.h
  ${BASE_SOURCES_PATH}bind.h
  ${BASE_SOURCES_PATH}bind_helpers.h
  ${BASE_SOURCES_PATH}bind_internal.h
  ${BASE_SOURCES_PATH}bit_cast.h
  ${BASE_SOURCES_PATH}bits.h
  ${BASE_SOURCES_PATH}build_time.cc
  ${BASE_SOURCES_PATH}build_time.h
  ${BASE_SOURCES_PATH}callback.h
  ${BASE_SOURCES_PATH}callback_forward.h
  ${BASE_SOURCES_PATH}callback_helpers.cc
  ${BASE_SOURCES_PATH}callback_helpers.h
  ${BASE_SOURCES_PATH}callback_internal.cc
  ${BASE_SOURCES_PATH}callback_internal.h
  ${BASE_SOURCES_PATH}callback_list.h
  ${BASE_SOURCES_PATH}cancelable_callback.h
  ${BASE_SOURCES_PATH}command_line.cc
  ${BASE_SOURCES_PATH}command_line.h
  ${BASE_SOURCES_PATH}compiler_specific.h
  ${BASE_SOURCES_PATH}component_export.h
  ${BASE_SOURCES_PATH}containers/adapters.h
  ${BASE_SOURCES_PATH}containers/any_internal.cc
  ${BASE_SOURCES_PATH}containers/any_internal.h
  ${BASE_SOURCES_PATH}containers/buffer_iterator.h
  ${BASE_SOURCES_PATH}containers/checked_iterators.h
  ${BASE_SOURCES_PATH}containers/circular_deque.h
  ${BASE_SOURCES_PATH}containers/flat_map.h
  ${BASE_SOURCES_PATH}containers/flat_set.h
  ${BASE_SOURCES_PATH}containers/flat_tree.h
  ${BASE_SOURCES_PATH}containers/id_map.h
  ${BASE_SOURCES_PATH}containers/linked_list.h
  ${BASE_SOURCES_PATH}containers/mru_cache.h
  ${BASE_SOURCES_PATH}containers/small_map.h
  ${BASE_SOURCES_PATH}containers/span.h
  ${BASE_SOURCES_PATH}containers/stack.h
  ${BASE_SOURCES_PATH}containers/stack_container.h
  ${BASE_SOURCES_PATH}containers/unique_any.cc
  ${BASE_SOURCES_PATH}containers/unique_any.h
  ${BASE_SOURCES_PATH}containers/unique_ptr_adapters.h
  ${BASE_SOURCES_PATH}containers/util.h
  ${BASE_SOURCES_PATH}containers/vector_buffer.h
  ${BASE_SOURCES_PATH}cpu.cc
  ${BASE_SOURCES_PATH}cpu.h
  ${BASE_SOURCES_PATH}critical_closure.h
  #${BASE_SOURCES_PATH}critical_closure_internal_ios.mm
  ## ${BASE_SOURCES_PATH}debug/activity_analyzer.cc
  ## ${BASE_SOURCES_PATH}debug/activity_analyzer.h
  ## ${BASE_SOURCES_PATH}debug/activity_tracker.cc
  ## ${BASE_SOURCES_PATH}debug/activity_tracker.h
  ${BASE_SOURCES_PATH}debug/alias.cc
  ${BASE_SOURCES_PATH}debug/alias.h
  ## ### ${BASE_SOURCES_PATH}debug/asan_invalid_access.cc
  ## ### ${BASE_SOURCES_PATH}debug/asan_invalid_access.h
  ## ${BASE_SOURCES_PATH}debug/crash_logging.cc
  ## ${BASE_SOURCES_PATH}debug/crash_logging.h
  ## ${BASE_SOURCES_PATH}debug/debugger.cc
  ## ${BASE_SOURCES_PATH}debug/debugger.h
  ## ${BASE_SOURCES_PATH}debug/dump_without_crashing.cc
  ## ${BASE_SOURCES_PATH}debug/dump_without_crashing.h
  ## ${BASE_SOURCES_PATH}debug/leak_annotations.h
  ## ${BASE_SOURCES_PATH}debug/leak_tracker.h
  ## ${BASE_SOURCES_PATH}debug/profiler.cc
  ## ${BASE_SOURCES_PATH}debug/profiler.h
  ## ${BASE_SOURCES_PATH}debug/stack_trace.cc
  ## ${BASE_SOURCES_PATH}debug/stack_trace.h
  ## #${BASE_SOURCES_PATH}debug/stack_trace_android.cc
  ## ${BASE_SOURCES_PATH}debug/task_trace.cc
  ## ${BASE_SOURCES_PATH}debug/task_trace.h
  ${BASE_SOURCES_PATH}deferred_sequenced_task_runner.cc
  ${BASE_SOURCES_PATH}deferred_sequenced_task_runner.h
  ${BASE_SOURCES_PATH}enterprise_util.h
  #${BASE_SOURCES_PATH}enterprise_util_mac.mm
  ${BASE_SOURCES_PATH}environment.cc
  ${BASE_SOURCES_PATH}environment.h
  ${BASE_SOURCES_PATH}export_template.h
  ${BASE_SOURCES_PATH}feature_list.cc
  ${BASE_SOURCES_PATH}feature_list.h
  ${BASE_SOURCES_PATH}file_version_info.h
  #${BASE_SOURCES_PATH}file_version_info_mac.h
  #${BASE_SOURCES_PATH}file_version_info_mac.mm
  ${BASE_SOURCES_PATH}files/dir_reader_fallback.h
  ${BASE_SOURCES_PATH}files/file.cc
  ${BASE_SOURCES_PATH}files/file.h
  ${BASE_SOURCES_PATH}files/file_enumerator.cc
  ${BASE_SOURCES_PATH}files/file_enumerator.h
  ${BASE_SOURCES_PATH}files/file_path.cc
  ${BASE_SOURCES_PATH}files/file_path.h
  ${BASE_SOURCES_PATH}files/file_path_constants.cc
  ${BASE_SOURCES_PATH}files/file_path_watcher.cc
  ${BASE_SOURCES_PATH}files/file_path_watcher.h
  #${BASE_SOURCES_PATH}files/file_path_watcher_mac.cc
  ${BASE_SOURCES_PATH}files/file_proxy.cc
  ${BASE_SOURCES_PATH}files/file_proxy.h
  ${BASE_SOURCES_PATH}files/file_tracing.cc
  ${BASE_SOURCES_PATH}files/file_tracing.h
  ${BASE_SOURCES_PATH}files/file_util.cc
  ${BASE_SOURCES_PATH}files/file_util.h
  #${BASE_SOURCES_PATH}files/file_util_android.cc
  #${BASE_SOURCES_PATH}files/file_util_mac.mm
  #TODO file_util_emscripten.cc
  ${BASE_SOURCES_PATH}files/important_file_writer.cc
  ${BASE_SOURCES_PATH}files/important_file_writer.h
  ${BASE_SOURCES_PATH}files/memory_mapped_file.cc
  ${BASE_SOURCES_PATH}files/memory_mapped_file.h
  ${BASE_SOURCES_PATH}files/platform_file.h
  ${BASE_SOURCES_PATH}files/scoped_file.cc
  ${BASE_SOURCES_PATH}files/scoped_file.h
  #${BASE_SOURCES_PATH}files/scoped_file_android.cc
  ${BASE_SOURCES_PATH}files/scoped_temp_dir.cc
  ${BASE_SOURCES_PATH}files/scoped_temp_dir.h
  ${BASE_SOURCES_PATH}format_macros.h
  # TODO ${BASE_SOURCES_PATH}gtest_prod_util.h
  ${BASE_SOURCES_PATH}guid.cc
  ${BASE_SOURCES_PATH}guid.h
  ${BASE_SOURCES_PATH}hash/hash.cc
  ${BASE_SOURCES_PATH}hash/hash.h
  ${BASE_SOURCES_PATH}hash/md5.cc
  ${BASE_SOURCES_PATH}hash/md5.h
  ${BASE_SOURCES_PATH}hash/sha1.cc
  ${BASE_SOURCES_PATH}hash/sha1.h
  #${BASE_SOURCES_PATH}ios/block_types.h
  #${BASE_SOURCES_PATH}ios/crb_protocol_observers.h
  #${BASE_SOURCES_PATH}ios/crb_protocol_observers.mm
  #${BASE_SOURCES_PATH}ios/device_util.h
  #${BASE_SOURCES_PATH}ios/device_util.mm
  #${BASE_SOURCES_PATH}ios/ios_util.h
  #${BASE_SOURCES_PATH}ios/ios_util.mm
  #${BASE_SOURCES_PATH}ios/ns_error_util.h
  #${BASE_SOURCES_PATH}ios/ns_error_util.mm
  #${BASE_SOURCES_PATH}ios/scoped_critical_action.h
  #${BASE_SOURCES_PATH}ios/scoped_critical_action.mm
  #${BASE_SOURCES_PATH}ios/weak_nsobject.h
  #${BASE_SOURCES_PATH}ios/weak_nsobject.mm
  ${BASE_SOURCES_PATH}lazy_instance.h
  ${BASE_SOURCES_PATH}lazy_instance_helpers.cc
  ${BASE_SOURCES_PATH}lazy_instance_helpers.h
  ${BASE_SOURCES_PATH}location.cc
  ${BASE_SOURCES_PATH}location.h
  ${BASE_SOURCES_PATH}logging.cc
  ${BASE_SOURCES_PATH}logging.h
  #${BASE_SOURCES_PATH}mac/authorization_util.h
  #${BASE_SOURCES_PATH}mac/authorization_util.mm
  #${BASE_SOURCES_PATH}mac/availability.h
  #${BASE_SOURCES_PATH}mac/bundle_locations.h
  #${BASE_SOURCES_PATH}mac/bundle_locations.mm
  #${BASE_SOURCES_PATH}mac/call_with_eh_frame.cc
  #${BASE_SOURCES_PATH}mac/call_with_eh_frame.h
  #${BASE_SOURCES_PATH}mac/call_with_eh_frame_asm.S
  #${BASE_SOURCES_PATH}mac/close_nocancel.cc
  #${BASE_SOURCES_PATH}mac/dispatch_source_mach.cc
  #${BASE_SOURCES_PATH}mac/dispatch_source_mach.h
  #${BASE_SOURCES_PATH}mac/foundation_util.h
  #${BASE_SOURCES_PATH}mac/foundation_util.mm
  #${BASE_SOURCES_PATH}mac/launch_services_util.h
  #${BASE_SOURCES_PATH}mac/launch_services_util.mm
  #${BASE_SOURCES_PATH}mac/launchd.cc
  #${BASE_SOURCES_PATH}mac/launchd.h
  #${BASE_SOURCES_PATH}mac/mac_logging.h
  #${BASE_SOURCES_PATH}mac/mac_logging.mm
  #${BASE_SOURCES_PATH}mac/mac_util.h
  #${BASE_SOURCES_PATH}mac/mac_util.mm
  #${BASE_SOURCES_PATH}mac/mach_logging.cc
  #${BASE_SOURCES_PATH}mac/mach_logging.h
  #${BASE_SOURCES_PATH}mac/mach_port_broker.h
  #${BASE_SOURCES_PATH}mac/mach_port_broker.mm
  #${BASE_SOURCES_PATH}mac/mach_port_rendezvous.cc
  #${BASE_SOURCES_PATH}mac/mach_port_rendezvous.h
  #${BASE_SOURCES_PATH}mac/mach_port_util.cc
  #${BASE_SOURCES_PATH}mac/mach_port_util.h
  #${BASE_SOURCES_PATH}mac/objc_release_properties.h
  #${BASE_SOURCES_PATH}mac/objc_release_properties.mm
  #${BASE_SOURCES_PATH}mac/os_crash_dumps.cc
  #${BASE_SOURCES_PATH}mac/os_crash_dumps.h
  #${BASE_SOURCES_PATH}mac/scoped_aedesc.h
  #${BASE_SOURCES_PATH}mac/scoped_authorizationref.h
  #${BASE_SOURCES_PATH}mac/scoped_block.h
  #${BASE_SOURCES_PATH}mac/scoped_cffiledescriptorref.h
  #${BASE_SOURCES_PATH}mac/scoped_cftyperef.h
  #${BASE_SOURCES_PATH}mac/scoped_dispatch_object.h
  #${BASE_SOURCES_PATH}mac/scoped_ionotificationportref.h
  #${BASE_SOURCES_PATH}mac/scoped_ioobject.h
  #${BASE_SOURCES_PATH}mac/scoped_ioplugininterface.h
  #${BASE_SOURCES_PATH}mac/scoped_launch_data.h
  #${BASE_SOURCES_PATH}mac/scoped_mach_msg_destroy.h
  #${BASE_SOURCES_PATH}mac/scoped_mach_port.cc
  #${BASE_SOURCES_PATH}mac/scoped_mach_port.h
  #${BASE_SOURCES_PATH}mac/scoped_mach_vm.cc
  #${BASE_SOURCES_PATH}mac/scoped_mach_vm.h
  #${BASE_SOURCES_PATH}mac/scoped_nsautorelease_pool.h
  #${BASE_SOURCES_PATH}mac/scoped_nsautorelease_pool.mm
  #${BASE_SOURCES_PATH}mac/scoped_nsobject.h
  #${BASE_SOURCES_PATH}mac/scoped_nsobject.mm
  #${BASE_SOURCES_PATH}mac/scoped_objc_class_swizzler.h
  #${BASE_SOURCES_PATH}mac/scoped_objc_class_swizzler.mm
  #${BASE_SOURCES_PATH}mac/scoped_sending_event.h
  #${BASE_SOURCES_PATH}mac/scoped_sending_event.mm
  #${BASE_SOURCES_PATH}mac/sdk_forward_declarations.h
  #${BASE_SOURCES_PATH}mac/sdk_forward_declarations.mm
  ${BASE_SOURCES_PATH}macros.h
  ${BASE_SOURCES_PATH}memory/aligned_memory.cc
  ${BASE_SOURCES_PATH}memory/aligned_memory.h
  ${BASE_SOURCES_PATH}memory/discardable_memory.cc
  ${BASE_SOURCES_PATH}memory/discardable_memory.h
  ${BASE_SOURCES_PATH}memory/discardable_memory_allocator.cc
  ${BASE_SOURCES_PATH}memory/discardable_memory_allocator.h
  ${BASE_SOURCES_PATH}memory/discardable_shared_memory.cc
  ${BASE_SOURCES_PATH}memory/discardable_shared_memory.h
  ${BASE_SOURCES_PATH}memory/free_deleter.h
  ${BASE_SOURCES_PATH}memory/memory_pressure_listener.cc
  ${BASE_SOURCES_PATH}memory/memory_pressure_listener.h
  ${BASE_SOURCES_PATH}memory/memory_pressure_monitor.cc
  ${BASE_SOURCES_PATH}memory/memory_pressure_monitor.h
  #${BASE_SOURCES_PATH}memory/memory_pressure_monitor_chromeos.cc
  #${BASE_SOURCES_PATH}memory/memory_pressure_monitor_chromeos.h
  #${BASE_SOURCES_PATH}memory/memory_pressure_monitor_mac.cc
  #${BASE_SOURCES_PATH}memory/memory_pressure_monitor_mac.h
  #${BASE_SOURCES_PATH}memory/memory_pressure_monitor_notifying_chromeos.cc
  #${BASE_SOURCES_PATH}memory/memory_pressure_monitor_notifying_chromeos.h
  ${BASE_SOURCES_PATH}memory/platform_shared_memory_region.cc
  ${BASE_SOURCES_PATH}memory/platform_shared_memory_region.h
  ${BASE_SOURCES_PATH}memory/protected_memory.cc
  ${BASE_SOURCES_PATH}memory/protected_memory.h
  #${BASE_SOURCES_PATH}memory/protected_memory_cfi.h
  ${BASE_SOURCES_PATH}memory/ptr_util.h
  ${BASE_SOURCES_PATH}memory/raw_scoped_refptr_mismatch_checker.h
  ${BASE_SOURCES_PATH}memory/read_only_shared_memory_region.cc
  ${BASE_SOURCES_PATH}memory/read_only_shared_memory_region.h
  ${BASE_SOURCES_PATH}memory/ref_counted.cc
  ${BASE_SOURCES_PATH}memory/ref_counted.h
  ${BASE_SOURCES_PATH}memory/ref_counted_delete_on_sequence.h
  ${BASE_SOURCES_PATH}memory/ref_counted_memory.cc
  ${BASE_SOURCES_PATH}memory/ref_counted_memory.h
  ${BASE_SOURCES_PATH}memory/scoped_policy.h
  ${BASE_SOURCES_PATH}memory/scoped_refptr.h
  ${BASE_SOURCES_PATH}memory/shared_memory.h
  ${BASE_SOURCES_PATH}memory/shared_memory_handle.cc
  ${BASE_SOURCES_PATH}memory/shared_memory_handle.h
  ${BASE_SOURCES_PATH}memory/shared_memory_hooks.h
  ${BASE_SOURCES_PATH}memory/shared_memory_mapping.cc
  ${BASE_SOURCES_PATH}memory/shared_memory_mapping.h
  ${BASE_SOURCES_PATH}memory/shared_memory_tracker.cc
  ${BASE_SOURCES_PATH}memory/shared_memory_tracker.h
  ${BASE_SOURCES_PATH}memory/singleton.h
  ${BASE_SOURCES_PATH}memory/unsafe_shared_memory_region.cc
  ${BASE_SOURCES_PATH}memory/unsafe_shared_memory_region.h
  ${BASE_SOURCES_PATH}memory/weak_ptr.cc
  ${BASE_SOURCES_PATH}memory/weak_ptr.h
  ${BASE_SOURCES_PATH}memory/writable_shared_memory_region.cc
  ${BASE_SOURCES_PATH}memory/writable_shared_memory_region.h
  ${BASE_SOURCES_PATH}message_loop/message_loop.cc
  ${BASE_SOURCES_PATH}message_loop/message_loop.h
  ${BASE_SOURCES_PATH}message_loop/message_loop_current.cc
  ${BASE_SOURCES_PATH}message_loop/message_loop_current.h
  ${BASE_SOURCES_PATH}message_loop/message_pump.cc
  ${BASE_SOURCES_PATH}message_loop/message_pump.h
  #${BASE_SOURCES_PATH}message_loop/message_pump_android.cc
  #${BASE_SOURCES_PATH}message_loop/message_pump_android.h
  ${BASE_SOURCES_PATH}message_loop/message_pump_default.cc
  ${BASE_SOURCES_PATH}message_loop/message_pump_default.h
  ${BASE_SOURCES_PATH}message_loop/message_pump_for_io.h
  ${BASE_SOURCES_PATH}message_loop/message_pump_for_ui.h
  #${BASE_SOURCES_PATH}message_loop/message_pump_glib.cc
  #${BASE_SOURCES_PATH}message_loop/message_pump_glib.h
  #${BASE_SOURCES_PATH}message_loop/message_pump_io_ios.cc
  #${BASE_SOURCES_PATH}message_loop/message_pump_io_ios.h
  #${BASE_SOURCES_PATH}message_loop/message_pump_mac.h
  #${BASE_SOURCES_PATH}message_loop/message_pump_mac.mm
  ${BASE_SOURCES_PATH}message_loop/timer_slack.h
  ${BASE_SOURCES_PATH}message_loop/work_id_provider.cc
  ${BASE_SOURCES_PATH}message_loop/work_id_provider.h
  ${BASE_SOURCES_PATH}metrics/bucket_ranges.cc
  ${BASE_SOURCES_PATH}metrics/bucket_ranges.h
  ${BASE_SOURCES_PATH}metrics/dummy_histogram.cc
  ${BASE_SOURCES_PATH}metrics/dummy_histogram.h
  ${BASE_SOURCES_PATH}metrics/field_trial.cc
  ${BASE_SOURCES_PATH}metrics/field_trial.h
  ${BASE_SOURCES_PATH}metrics/field_trial_param_associator.cc
  ${BASE_SOURCES_PATH}metrics/field_trial_param_associator.h
  ${BASE_SOURCES_PATH}metrics/field_trial_params.cc
  ${BASE_SOURCES_PATH}metrics/field_trial_params.h
  ${BASE_SOURCES_PATH}metrics/histogram.cc
  ${BASE_SOURCES_PATH}metrics/histogram.h
  ${BASE_SOURCES_PATH}metrics/histogram_base.cc
  ${BASE_SOURCES_PATH}metrics/histogram_base.h
  ${BASE_SOURCES_PATH}metrics/histogram_delta_serialization.cc
  ${BASE_SOURCES_PATH}metrics/histogram_delta_serialization.h
  ${BASE_SOURCES_PATH}metrics/histogram_flattener.h
  ${BASE_SOURCES_PATH}metrics/histogram_functions.cc
  ${BASE_SOURCES_PATH}metrics/histogram_functions.h
  ${BASE_SOURCES_PATH}metrics/histogram_macros.h
  ${BASE_SOURCES_PATH}metrics/histogram_macros_internal.h
  ${BASE_SOURCES_PATH}metrics/histogram_macros_local.h
  ${BASE_SOURCES_PATH}metrics/histogram_samples.cc
  ${BASE_SOURCES_PATH}metrics/histogram_samples.h
  ${BASE_SOURCES_PATH}metrics/histogram_snapshot_manager.cc
  ${BASE_SOURCES_PATH}metrics/histogram_snapshot_manager.h
  ${BASE_SOURCES_PATH}metrics/metrics_hashes.cc
  ${BASE_SOURCES_PATH}metrics/metrics_hashes.h
  ${BASE_SOURCES_PATH}metrics/persistent_histogram_allocator.cc
  ${BASE_SOURCES_PATH}metrics/persistent_histogram_allocator.h
  ${BASE_SOURCES_PATH}metrics/persistent_memory_allocator.cc
  ${BASE_SOURCES_PATH}metrics/persistent_memory_allocator.h
  ${BASE_SOURCES_PATH}metrics/persistent_sample_map.cc
  ${BASE_SOURCES_PATH}metrics/persistent_sample_map.h
  ${BASE_SOURCES_PATH}metrics/record_histogram_checker.h
  ${BASE_SOURCES_PATH}metrics/sample_map.cc
  ${BASE_SOURCES_PATH}metrics/sample_map.h
  ${BASE_SOURCES_PATH}metrics/sample_vector.cc
  ${BASE_SOURCES_PATH}metrics/sample_vector.h
  ${BASE_SOURCES_PATH}metrics/single_sample_metrics.cc
  ${BASE_SOURCES_PATH}metrics/single_sample_metrics.h
  ${BASE_SOURCES_PATH}metrics/sparse_histogram.cc
  ${BASE_SOURCES_PATH}metrics/sparse_histogram.h
  ${BASE_SOURCES_PATH}metrics/statistics_recorder.cc
  ${BASE_SOURCES_PATH}metrics/statistics_recorder.h
  ${BASE_SOURCES_PATH}metrics/user_metrics.cc
  ${BASE_SOURCES_PATH}metrics/user_metrics.h
  ${BASE_SOURCES_PATH}metrics/user_metrics_action.h
  ${BASE_SOURCES_PATH}native_library.cc
  ${BASE_SOURCES_PATH}native_library.h
  #${BASE_SOURCES_PATH}native_library_ios.mm
  #${BASE_SOURCES_PATH}native_library_mac.mm
  ${BASE_SOURCES_PATH}no_destructor.h
  ${BASE_SOURCES_PATH}observer_list.h
  ${BASE_SOURCES_PATH}observer_list_internal.cc
  ${BASE_SOURCES_PATH}observer_list_internal.h
  ${BASE_SOURCES_PATH}observer_list_threadsafe.cc
  ${BASE_SOURCES_PATH}observer_list_threadsafe.h
  ${BASE_SOURCES_PATH}observer_list_types.cc
  ${BASE_SOURCES_PATH}observer_list_types.h
  ${BASE_SOURCES_PATH}one_shot_event.cc
  ${BASE_SOURCES_PATH}one_shot_event.h
  ${BASE_SOURCES_PATH}optional.h
  #${BASE_SOURCES_PATH}os_compat_android.cc
  #${BASE_SOURCES_PATH}os_compat_android.h
  #${BASE_SOURCES_PATH}os_compat_nacl.cc
  #${BASE_SOURCES_PATH}os_compat_nacl.h
  ${BASE_SOURCES_PATH}parameter_pack.h
  ${BASE_SOURCES_PATH}path_service.cc
  ${BASE_SOURCES_PATH}path_service.h
  ${BASE_SOURCES_PATH}pending_task.cc
  ${BASE_SOURCES_PATH}pending_task.h
  ${BASE_SOURCES_PATH}pickle.cc
  ${BASE_SOURCES_PATH}pickle.h
  ${BASE_SOURCES_PATH}post_task_and_reply_with_result_internal.h
  ${BASE_SOURCES_PATH}power_monitor/power_monitor.cc
  ${BASE_SOURCES_PATH}power_monitor/power_monitor.h
  ${BASE_SOURCES_PATH}power_monitor/power_monitor_device_source.cc
  ${BASE_SOURCES_PATH}power_monitor/power_monitor_device_source.h
  ${BASE_SOURCES_PATH}power_monitor/power_monitor_source.cc
  ${BASE_SOURCES_PATH}power_monitor/power_monitor_source.h
  ${BASE_SOURCES_PATH}power_monitor/power_observer.h
  ${BASE_SOURCES_PATH}process/environment_internal.cc
  ${BASE_SOURCES_PATH}process/environment_internal.h
  ${BASE_SOURCES_PATH}process/kill.cc
  ${BASE_SOURCES_PATH}process/kill.h
  #${BASE_SOURCES_PATH}process/kill_mac.cc
  ${BASE_SOURCES_PATH}process/launch.cc
  ${BASE_SOURCES_PATH}process/launch.h
  #${BASE_SOURCES_PATH}process/launch_ios.cc
  #${BASE_SOURCES_PATH}process/launch_mac.cc
  ${BASE_SOURCES_PATH}process/memory.cc
  ${BASE_SOURCES_PATH}process/memory.h
  #${BASE_SOURCES_PATH}process/memory_mac.mm
  #${BASE_SOURCES_PATH}process/port_provider_mac.cc
  #${BASE_SOURCES_PATH}process/port_provider_mac.h
  ${BASE_SOURCES_PATH}process/process.h
  ${BASE_SOURCES_PATH}process/process_handle.cc
  ${BASE_SOURCES_PATH}process/process_handle.h
  #${BASE_SOURCES_PATH}process/process_handle_mac.cc
  ${BASE_SOURCES_PATH}process/process_info.h
  ${BASE_SOURCES_PATH}process/process_iterator.cc
  ${BASE_SOURCES_PATH}process/process_iterator.h
  #${BASE_SOURCES_PATH}process/process_mac.cc
  ${BASE_SOURCES_PATH}process/process_metrics.cc
  ${BASE_SOURCES_PATH}process/process_metrics.h
  #${BASE_SOURCES_PATH}process/process_metrics_ios.cc
  #${BASE_SOURCES_PATH}process/process_metrics_mac.cc
  ${BASE_SOURCES_PATH}profiler/frame.cc
  ${BASE_SOURCES_PATH}profiler/frame.h
  ${BASE_SOURCES_PATH}profiler/metadata_recorder.cc
  ${BASE_SOURCES_PATH}profiler/metadata_recorder.h
  ${BASE_SOURCES_PATH}profiler/native_unwinder.h
  #${BASE_SOURCES_PATH}profiler/native_unwinder_mac.cc
  #${BASE_SOURCES_PATH}profiler/native_unwinder_mac.h
  ${BASE_SOURCES_PATH}profiler/profile_builder.h
  ${BASE_SOURCES_PATH}profiler/register_context.h
  ${BASE_SOURCES_PATH}profiler/sample_metadata.cc
  ${BASE_SOURCES_PATH}profiler/sample_metadata.h
  ${BASE_SOURCES_PATH}profiler/stack_sampler.cc
  ${BASE_SOURCES_PATH}profiler/stack_sampler.h
  ${BASE_SOURCES_PATH}profiler/stack_sampler_impl.cc
  ${BASE_SOURCES_PATH}profiler/stack_sampler_impl.h
  #${BASE_SOURCES_PATH}profiler/stack_sampler_mac.cc
  ${BASE_SOURCES_PATH}profiler/stack_sampling_profiler.cc
  ${BASE_SOURCES_PATH}profiler/stack_sampling_profiler.h
  ${BASE_SOURCES_PATH}profiler/thread_delegate.h
  #${BASE_SOURCES_PATH}profiler/thread_delegate_mac.cc
  #${BASE_SOURCES_PATH}profiler/thread_delegate_mac.h
  ${BASE_SOURCES_PATH}profiler/unwinder.h
  ${BASE_SOURCES_PATH}rand_util.cc
  ${BASE_SOURCES_PATH}rand_util.h
  #${BASE_SOURCES_PATH}rand_util_nacl.cc
  ${BASE_SOURCES_PATH}run_loop.cc
  ${BASE_SOURCES_PATH}run_loop.h
  ${BASE_SOURCES_PATH}sampling_heap_profiler/lock_free_address_hash_set.cc
  ${BASE_SOURCES_PATH}sampling_heap_profiler/lock_free_address_hash_set.h
  ${BASE_SOURCES_PATH}sampling_heap_profiler/module_cache.cc
  ${BASE_SOURCES_PATH}sampling_heap_profiler/module_cache.h
  #${BASE_SOURCES_PATH}sampling_heap_profiler/module_cache_mac.cc
  ${BASE_SOURCES_PATH}sampling_heap_profiler/poisson_allocation_sampler.cc
  ${BASE_SOURCES_PATH}sampling_heap_profiler/poisson_allocation_sampler.h
  ${BASE_SOURCES_PATH}sampling_heap_profiler/sampling_heap_profiler.cc
  ${BASE_SOURCES_PATH}sampling_heap_profiler/sampling_heap_profiler.h
  ${BASE_SOURCES_PATH}scoped_clear_last_error.h
  ${BASE_SOURCES_PATH}scoped_generic.h
  ${BASE_SOURCES_PATH}scoped_native_library.cc
  ${BASE_SOURCES_PATH}scoped_native_library.h
  ${BASE_SOURCES_PATH}scoped_observer.h
  ${BASE_SOURCES_PATH}sequence_checker.h
  ${BASE_SOURCES_PATH}sequence_checker_impl.cc
  ${BASE_SOURCES_PATH}sequence_checker_impl.h
  ${BASE_SOURCES_PATH}sequence_token.cc
  ${BASE_SOURCES_PATH}sequence_token.h
  ${BASE_SOURCES_PATH}sequenced_task_runner.cc
  ${BASE_SOURCES_PATH}sequenced_task_runner.h
  ${BASE_SOURCES_PATH}sequenced_task_runner_helpers.h
  ${BASE_SOURCES_PATH}single_thread_task_runner.h
  ${BASE_SOURCES_PATH}single_thread_task_runner.cc
  ${BASE_SOURCES_PATH}stl_util.h
  ${BASE_SOURCES_PATH}strings/char_traits.h
  ${BASE_SOURCES_PATH}strings/latin1_string_conversions.cc
  ${BASE_SOURCES_PATH}strings/latin1_string_conversions.h
  ${BASE_SOURCES_PATH}strings/nullable_string16.cc
  ${BASE_SOURCES_PATH}strings/nullable_string16.h
  ${BASE_SOURCES_PATH}strings/pattern.cc
  ${BASE_SOURCES_PATH}strings/pattern.h
  ${BASE_SOURCES_PATH}strings/safe_sprintf.cc
  ${BASE_SOURCES_PATH}strings/safe_sprintf.h
  ${BASE_SOURCES_PATH}strings/strcat.cc
  ${BASE_SOURCES_PATH}strings/strcat.h
  ${BASE_SOURCES_PATH}strings/string16.h
  ${BASE_SOURCES_PATH}strings/string_number_conversions.cc
  ${BASE_SOURCES_PATH}strings/string_number_conversions.h
  ${BASE_SOURCES_PATH}strings/string_piece.cc
  ${BASE_SOURCES_PATH}strings/string_piece.h
  ${BASE_SOURCES_PATH}strings/string_piece_forward.h
  ${BASE_SOURCES_PATH}strings/string_split.cc
  ${BASE_SOURCES_PATH}strings/string_split.h
  ${BASE_SOURCES_PATH}strings/string_tokenizer.h
  ${BASE_SOURCES_PATH}strings/string_util.cc
  ${BASE_SOURCES_PATH}strings/string_util.h
  ${BASE_SOURCES_PATH}strings/string_util_constants.cc
  ${BASE_SOURCES_PATH}strings/stringize_macros.h
  ${BASE_SOURCES_PATH}strings/stringprintf.cc
  ${BASE_SOURCES_PATH}strings/stringprintf.h
  ${BASE_SOURCES_PATH}strings/sys_string_conversions.h
  #${BASE_SOURCES_PATH}strings/sys_string_conversions_mac.mm
  ${BASE_SOURCES_PATH}strings/utf_offset_string_conversions.cc
  ${BASE_SOURCES_PATH}strings/utf_offset_string_conversions.h
  ${BASE_SOURCES_PATH}strings/utf_string_conversion_utils.cc
  ${BASE_SOURCES_PATH}strings/utf_string_conversion_utils.h
  ${BASE_SOURCES_PATH}strings/utf_string_conversions.cc
  ${BASE_SOURCES_PATH}strings/utf_string_conversions.h
  ${BASE_SOURCES_PATH}supports_user_data.cc
  ${BASE_SOURCES_PATH}supports_user_data.h
  ${BASE_SOURCES_PATH}sync_socket.h
  ${BASE_SOURCES_PATH}synchronization/atomic_flag.cc
  ${BASE_SOURCES_PATH}synchronization/atomic_flag.h
  ${BASE_SOURCES_PATH}synchronization/cancellation_flag.h
  ${BASE_SOURCES_PATH}synchronization/condition_variable.h
  ${BASE_SOURCES_PATH}synchronization/lock.cc
  ${BASE_SOURCES_PATH}synchronization/lock.h
  ${BASE_SOURCES_PATH}synchronization/lock_impl.h
  ${BASE_SOURCES_PATH}synchronization/spin_wait.h
  ${BASE_SOURCES_PATH}synchronization/waitable_event.h
  #${BASE_SOURCES_PATH}synchronization/waitable_event_mac.cc
  ${BASE_SOURCES_PATH}synchronization/waitable_event_watcher.h
  #${BASE_SOURCES_PATH}synchronization/waitable_event_watcher_mac.cc
  ${BASE_SOURCES_PATH}sys_byteorder.h
  ${BASE_SOURCES_PATH}syslog_logging.cc
  ${BASE_SOURCES_PATH}syslog_logging.h
  ${BASE_SOURCES_PATH}system/sys_info.cc
  ${BASE_SOURCES_PATH}system/sys_info.h
  ${BASE_SOURCES_PATH}system/sys_info_internal.h
  ${BASE_SOURCES_PATH}system/system_monitor.cc
  ${BASE_SOURCES_PATH}system/system_monitor.h
  ${BASE_SOURCES_PATH}task/cancelable_task_tracker.cc
  ${BASE_SOURCES_PATH}task/cancelable_task_tracker.h
  ${BASE_SOURCES_PATH}task/common/checked_lock.h
  ${BASE_SOURCES_PATH}task/common/checked_lock_impl.cc
  ${BASE_SOURCES_PATH}task/common/checked_lock_impl.h
  ${BASE_SOURCES_PATH}task/common/intrusive_heap.h
  ${BASE_SOURCES_PATH}task/common/operations_controller.cc
  ${BASE_SOURCES_PATH}task/common/operations_controller.h
  ${BASE_SOURCES_PATH}task/common/task_annotator.cc
  ${BASE_SOURCES_PATH}task/common/task_annotator.h
  ${BASE_SOURCES_PATH}task/lazy_task_runner.cc
  ${BASE_SOURCES_PATH}task/lazy_task_runner.h
  ${BASE_SOURCES_PATH}task/post_task.cc
  ${BASE_SOURCES_PATH}task/post_task.h
  ${BASE_SOURCES_PATH}task/promise/dependent_list.cc
  ${BASE_SOURCES_PATH}task/promise/dependent_list.h
  ${BASE_SOURCES_PATH}task/scoped_set_task_priority_for_current_thread.cc
  ${BASE_SOURCES_PATH}task/scoped_set_task_priority_for_current_thread.h
  ${BASE_SOURCES_PATH}task/sequence_manager/associated_thread_id.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/associated_thread_id.h
  ${BASE_SOURCES_PATH}task/sequence_manager/atomic_flag_set.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/atomic_flag_set.h
  ${BASE_SOURCES_PATH}task/sequence_manager/enqueue_order.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/enqueue_order.h
  ${BASE_SOURCES_PATH}task/sequence_manager/lazily_deallocated_deque.h
  ${BASE_SOURCES_PATH}task/sequence_manager/lazy_now.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/lazy_now.h
  ${BASE_SOURCES_PATH}task/sequence_manager/real_time_domain.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/real_time_domain.h
  ${BASE_SOURCES_PATH}task/sequence_manager/sequence_manager.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/sequence_manager.h
  ${BASE_SOURCES_PATH}task/sequence_manager/sequence_manager_impl.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/sequence_manager_impl.h
  ${BASE_SOURCES_PATH}task/sequence_manager/sequenced_task_source.h
  ${BASE_SOURCES_PATH}task/sequence_manager/task_queue.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/task_queue.h
  ${BASE_SOURCES_PATH}task/sequence_manager/task_queue_impl.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/task_queue_impl.h
  ${BASE_SOURCES_PATH}task/sequence_manager/task_queue_selector.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/task_queue_selector.h
  ${BASE_SOURCES_PATH}task/sequence_manager/task_queue_selector_logic.h
  ${BASE_SOURCES_PATH}task/sequence_manager/task_time_observer.h
  ${BASE_SOURCES_PATH}task/sequence_manager/tasks.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/tasks.h
  ${BASE_SOURCES_PATH}task/sequence_manager/thread_controller.h
  ${BASE_SOURCES_PATH}task/sequence_manager/thread_controller_impl.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/thread_controller_impl.h
  ${BASE_SOURCES_PATH}task/sequence_manager/thread_controller_with_message_pump_impl.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/thread_controller_with_message_pump_impl.h
  ${BASE_SOURCES_PATH}task/sequence_manager/time_domain.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/time_domain.h
  ${BASE_SOURCES_PATH}task/sequence_manager/work_deduplicator.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/work_deduplicator.h
  ${BASE_SOURCES_PATH}task/sequence_manager/work_queue.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/work_queue.h
  ${BASE_SOURCES_PATH}task/sequence_manager/work_queue_sets.cc
  ${BASE_SOURCES_PATH}task/sequence_manager/work_queue_sets.h
  ${BASE_SOURCES_PATH}task/single_thread_task_runner_thread_mode.h
  ${BASE_SOURCES_PATH}task/task_executor.cc
  ${BASE_SOURCES_PATH}task/task_executor.h
  ${BASE_SOURCES_PATH}task/task_features.cc
  ${BASE_SOURCES_PATH}task/task_features.h
  ${BASE_SOURCES_PATH}task/task_observer.h
  ${BASE_SOURCES_PATH}task/task_traits.cc
  ${BASE_SOURCES_PATH}task/task_traits.h
  ${BASE_SOURCES_PATH}task/task_traits_extension.h
  ${BASE_SOURCES_PATH}task/thread_pool/delayed_task_manager.cc
  ${BASE_SOURCES_PATH}task/thread_pool/delayed_task_manager.h
  ${BASE_SOURCES_PATH}task/thread_pool/environment_config.cc
  ${BASE_SOURCES_PATH}task/thread_pool/environment_config.h
  ${BASE_SOURCES_PATH}task/thread_pool/initialization_util.cc
  ${BASE_SOURCES_PATH}task/thread_pool/initialization_util.h
  ${BASE_SOURCES_PATH}task/thread_pool/pooled_parallel_task_runner.cc
  ${BASE_SOURCES_PATH}task/thread_pool/pooled_parallel_task_runner.h
  ${BASE_SOURCES_PATH}task/thread_pool/pooled_sequenced_task_runner.cc
  ${BASE_SOURCES_PATH}task/thread_pool/pooled_sequenced_task_runner.h
  ${BASE_SOURCES_PATH}task/thread_pool/pooled_single_thread_task_runner_manager.cc
  ${BASE_SOURCES_PATH}task/thread_pool/pooled_single_thread_task_runner_manager.h
  ${BASE_SOURCES_PATH}task/thread_pool/pooled_task_runner_delegate.cc
  ${BASE_SOURCES_PATH}task/thread_pool/pooled_task_runner_delegate.h
  ${BASE_SOURCES_PATH}task/thread_pool/priority_queue.cc
  ${BASE_SOURCES_PATH}task/thread_pool/priority_queue.h
  ${BASE_SOURCES_PATH}task/thread_pool/sequence.cc
  ${BASE_SOURCES_PATH}task/thread_pool/sequence.h
  ${BASE_SOURCES_PATH}task/thread_pool/sequence_sort_key.cc
  ${BASE_SOURCES_PATH}task/thread_pool/sequence_sort_key.h
  ${BASE_SOURCES_PATH}task/thread_pool/service_thread.cc
  ${BASE_SOURCES_PATH}task/thread_pool/service_thread.h
  ${BASE_SOURCES_PATH}task/thread_pool/task.cc
  ${BASE_SOURCES_PATH}task/thread_pool/task.h
  ${BASE_SOURCES_PATH}task/thread_pool/task_source.cc
  ${BASE_SOURCES_PATH}task/thread_pool/task_source.h
  ${BASE_SOURCES_PATH}task/thread_pool/task_tracker.cc
  ${BASE_SOURCES_PATH}task/thread_pool/task_tracker.h
  ${BASE_SOURCES_PATH}task/thread_pool/thread_group.cc
  ${BASE_SOURCES_PATH}task/thread_pool/thread_group.h
  ${BASE_SOURCES_PATH}task/thread_pool/thread_group_impl.cc
  ${BASE_SOURCES_PATH}task/thread_pool/thread_group_impl.h
  ${BASE_SOURCES_PATH}task/thread_pool/thread_group_native.cc
  ${BASE_SOURCES_PATH}task/thread_pool/thread_group_native.h
  #${BASE_SOURCES_PATH}task/thread_pool/thread_group_native_mac.h
  #${BASE_SOURCES_PATH}task/thread_pool/thread_group_native_mac.mm
  ${BASE_SOURCES_PATH}task/thread_pool/thread_group_params.cc
  ${BASE_SOURCES_PATH}task/thread_pool/thread_group_params.h
  ${BASE_SOURCES_PATH}task/thread_pool/thread_pool.cc
  ${BASE_SOURCES_PATH}task/thread_pool/thread_pool.h
  ${BASE_SOURCES_PATH}task/thread_pool/thread_pool_impl.cc
  ${BASE_SOURCES_PATH}task/thread_pool/thread_pool_impl.h
  ${BASE_SOURCES_PATH}task/thread_pool/tracked_ref.h
  ${BASE_SOURCES_PATH}task/thread_pool/worker_thread.cc
  ${BASE_SOURCES_PATH}task/thread_pool/worker_thread.h
  ${BASE_SOURCES_PATH}task/thread_pool/worker_thread_observer.h
  ${BASE_SOURCES_PATH}task/thread_pool/worker_thread_params.h
  ${BASE_SOURCES_PATH}task/thread_pool/worker_thread_stack.cc
  ${BASE_SOURCES_PATH}task/thread_pool/worker_thread_stack.h
  ${BASE_SOURCES_PATH}task_runner.cc
  ${BASE_SOURCES_PATH}task_runner.h
  ${BASE_SOURCES_PATH}task_runner_util.h
  ${BASE_SOURCES_PATH}template_util.h
  ${BASE_SOURCES_PATH}test/malloc_wrapper.h
  ${BASE_SOURCES_PATH}third_party/dmg_fp/dmg_fp.h
  ${BASE_SOURCES_PATH}third_party/dmg_fp/dtoa_wrapper.cc
  ${BASE_SOURCES_PATH}third_party/dmg_fp/g_fmt.cc
  ${BASE_SOURCES_PATH}third_party/icu/icu_utf.cc
  ${BASE_SOURCES_PATH}third_party/icu/icu_utf.h
  ${BASE_SOURCES_PATH}third_party/nspr/prtime.cc
  ${BASE_SOURCES_PATH}third_party/nspr/prtime.h
  ${BASE_SOURCES_PATH}third_party/superfasthash/superfasthash.c
  ${BASE_SOURCES_PATH}thread_annotations.h
  ${BASE_SOURCES_PATH}threading/platform_thread.cc
  ${BASE_SOURCES_PATH}threading/platform_thread.h
  #${BASE_SOURCES_PATH}threading/platform_thread_android.cc
  #${BASE_SOURCES_PATH}threading/platform_thread_mac.mm
  ${BASE_SOURCES_PATH}threading/post_task_and_reply_impl.cc
  ${BASE_SOURCES_PATH}threading/post_task_and_reply_impl.h
  ${BASE_SOURCES_PATH}threading/scoped_blocking_call.cc
  ${BASE_SOURCES_PATH}threading/scoped_blocking_call.h
  ${BASE_SOURCES_PATH}threading/sequence_bound.h
  ${BASE_SOURCES_PATH}threading/sequence_local_storage_map.cc
  ${BASE_SOURCES_PATH}threading/sequence_local_storage_map.h
  ${BASE_SOURCES_PATH}threading/sequence_local_storage_slot.cc
  ${BASE_SOURCES_PATH}threading/sequence_local_storage_slot.h
  ${BASE_SOURCES_PATH}threading/sequenced_task_runner_handle.cc
  ${BASE_SOURCES_PATH}threading/sequenced_task_runner_handle.h
  ${BASE_SOURCES_PATH}threading/simple_thread.cc
  ${BASE_SOURCES_PATH}threading/simple_thread.h
  ${BASE_SOURCES_PATH}threading/thread.cc
  ${BASE_SOURCES_PATH}threading/thread.h
  ${BASE_SOURCES_PATH}threading/thread_checker.h
  ${BASE_SOURCES_PATH}threading/thread_checker_impl.cc
  ${BASE_SOURCES_PATH}threading/thread_checker_impl.h
  ${BASE_SOURCES_PATH}threading/thread_collision_warner.cc
  ${BASE_SOURCES_PATH}threading/thread_collision_warner.h
  ${BASE_SOURCES_PATH}threading/thread_id_name_manager.cc
  ${BASE_SOURCES_PATH}threading/thread_id_name_manager.h
  ${BASE_SOURCES_PATH}threading/thread_local.h
  ${BASE_SOURCES_PATH}threading/thread_local_internal.h
  ${BASE_SOURCES_PATH}threading/thread_local_storage.cc
  ${BASE_SOURCES_PATH}threading/thread_local_storage.h
  ${BASE_SOURCES_PATH}threading/thread_restrictions.cc
  ${BASE_SOURCES_PATH}threading/thread_restrictions.h
  ${BASE_SOURCES_PATH}threading/thread_task_runner_handle.cc
  ${BASE_SOURCES_PATH}threading/thread_task_runner_handle.h
  ${BASE_SOURCES_PATH}threading/watchdog.cc
  ${BASE_SOURCES_PATH}threading/watchdog.h
  ${BASE_SOURCES_PATH}time/clock.cc
  ${BASE_SOURCES_PATH}time/clock.h
  ${BASE_SOURCES_PATH}time/default_clock.cc
  ${BASE_SOURCES_PATH}time/default_clock.h
  ${BASE_SOURCES_PATH}time/default_tick_clock.cc
  ${BASE_SOURCES_PATH}time/default_tick_clock.h
  ${BASE_SOURCES_PATH}time/tick_clock.cc
  ${BASE_SOURCES_PATH}time/tick_clock.h
  ${BASE_SOURCES_PATH}time/time.cc
  ${BASE_SOURCES_PATH}time/time.h
  ${BASE_SOURCES_PATH}time/time_override.cc
  ${BASE_SOURCES_PATH}time/time_override.h
  ${BASE_SOURCES_PATH}time/time_to_iso8601.cc
  ${BASE_SOURCES_PATH}time/time_to_iso8601.h
  ${BASE_SOURCES_PATH}timer/elapsed_timer.cc
  ${BASE_SOURCES_PATH}timer/elapsed_timer.h
  ${BASE_SOURCES_PATH}timer/hi_res_timer_manager.h
  ${BASE_SOURCES_PATH}timer/lap_timer.cc
  ${BASE_SOURCES_PATH}timer/lap_timer.h
  ${BASE_SOURCES_PATH}timer/timer.cc
  ${BASE_SOURCES_PATH}timer/timer.h
  #${BASE_SOURCES_PATH}token.cc
  #${BASE_SOURCES_PATH}token.h
  ${BASE_SOURCES_PATH}base_token.cc
  ${BASE_SOURCES_PATH}base_token.h
  ${BASE_SOURCES_PATH}trace_event/auto_open_close_event.h
  ${BASE_SOURCES_PATH}trace_event/blame_context.cc
  ${BASE_SOURCES_PATH}trace_event/blame_context.h
  ${BASE_SOURCES_PATH}trace_event/builtin_categories.cc
  ${BASE_SOURCES_PATH}trace_event/builtin_categories.h
  ${BASE_SOURCES_PATH}trace_event/category_registry.cc
  ${BASE_SOURCES_PATH}trace_event/category_registry.h
  #${BASE_SOURCES_PATH}trace_event/common/trace_event_common.h
  #${BASE_SOURCES_PATH}trace_event/cpufreq_monitor_android.cc
  #${BASE_SOURCES_PATH}trace_event/cpufreq_monitor_android.h
  ${BASE_SOURCES_PATH}trace_event/event_name_filter.cc
  ${BASE_SOURCES_PATH}trace_event/event_name_filter.h
  ${BASE_SOURCES_PATH}trace_event/heap_profiler.h
  ${BASE_SOURCES_PATH}trace_event/heap_profiler_allocation_context.cc
  ${BASE_SOURCES_PATH}trace_event/heap_profiler_allocation_context.h
  ${BASE_SOURCES_PATH}trace_event/heap_profiler_allocation_context_tracker.cc
  ${BASE_SOURCES_PATH}trace_event/heap_profiler_allocation_context_tracker.h
  ${BASE_SOURCES_PATH}trace_event/heap_profiler_event_filter.cc
  ${BASE_SOURCES_PATH}trace_event/heap_profiler_event_filter.h
  #${BASE_SOURCES_PATH}trace_event/java_heap_dump_provider_android.cc
  #${BASE_SOURCES_PATH}trace_event/java_heap_dump_provider_android.h
  ${BASE_SOURCES_PATH}trace_event/malloc_dump_provider.cc
  ${BASE_SOURCES_PATH}trace_event/malloc_dump_provider.h
  ${BASE_SOURCES_PATH}trace_event/memory_allocator_dump.cc
  ${BASE_SOURCES_PATH}trace_event/memory_allocator_dump.h
  ${BASE_SOURCES_PATH}trace_event/memory_allocator_dump_guid.cc
  ${BASE_SOURCES_PATH}trace_event/memory_allocator_dump_guid.h
  ${BASE_SOURCES_PATH}trace_event/memory_dump_manager.cc
  ${BASE_SOURCES_PATH}trace_event/memory_dump_manager.h
  ${BASE_SOURCES_PATH}trace_event/memory_dump_manager_test_utils.h
  ${BASE_SOURCES_PATH}trace_event/memory_dump_provider.h
  ${BASE_SOURCES_PATH}trace_event/memory_dump_provider_info.cc
  ${BASE_SOURCES_PATH}trace_event/memory_dump_provider_info.h
  ${BASE_SOURCES_PATH}trace_event/memory_dump_request_args.cc
  ${BASE_SOURCES_PATH}trace_event/memory_dump_request_args.h
  ${BASE_SOURCES_PATH}trace_event/memory_dump_scheduler.cc
  ${BASE_SOURCES_PATH}trace_event/memory_dump_scheduler.h
  ${BASE_SOURCES_PATH}trace_event/memory_infra_background_whitelist.cc
  ${BASE_SOURCES_PATH}trace_event/memory_infra_background_whitelist.h
  ${BASE_SOURCES_PATH}trace_event/memory_usage_estimator.cc
  ${BASE_SOURCES_PATH}trace_event/memory_usage_estimator.h
  ${BASE_SOURCES_PATH}trace_event/process_memory_dump.cc
  ${BASE_SOURCES_PATH}trace_event/process_memory_dump.h
  ${BASE_SOURCES_PATH}trace_event/thread_instruction_count.cc
  ${BASE_SOURCES_PATH}trace_event/thread_instruction_count.h
  ${BASE_SOURCES_PATH}trace_event/trace_arguments.cc
  ${BASE_SOURCES_PATH}trace_event/trace_arguments.h
  ${BASE_SOURCES_PATH}trace_event/trace_buffer.cc
  ${BASE_SOURCES_PATH}trace_event/trace_buffer.h
  ${BASE_SOURCES_PATH}trace_event/trace_category.h
  ${BASE_SOURCES_PATH}trace_event/trace_config.cc
  ${BASE_SOURCES_PATH}trace_event/trace_config.h
  ${BASE_SOURCES_PATH}trace_event/trace_config_category_filter.cc
  ${BASE_SOURCES_PATH}trace_event/trace_config_category_filter.h
  ${BASE_SOURCES_PATH}trace_event/trace_event.h
  #${BASE_SOURCES_PATH}trace_event/trace_event_android.cc
  ${BASE_SOURCES_PATH}trace_event/trace_event_filter.cc
  ${BASE_SOURCES_PATH}trace_event/trace_event_filter.h
  ${BASE_SOURCES_PATH}trace_event/trace_event_impl.cc
  ${BASE_SOURCES_PATH}trace_event/trace_event_impl.h
  ${BASE_SOURCES_PATH}trace_event/trace_event_memory_overhead.cc
  ${BASE_SOURCES_PATH}trace_event/trace_event_memory_overhead.h
  ${BASE_SOURCES_PATH}trace_event/trace_log.cc
  ${BASE_SOURCES_PATH}trace_event/trace_log.h
  ${BASE_SOURCES_PATH}trace_event/trace_log_constants.cc
  ${BASE_SOURCES_PATH}trace_event/traced_value.cc
  ${BASE_SOURCES_PATH}trace_event/traced_value.h
  ${BASE_SOURCES_PATH}trace_event/tracing_agent.cc
  ${BASE_SOURCES_PATH}trace_event/tracing_agent.h
  ${BASE_SOURCES_PATH}traits_bag.h
  ${BASE_SOURCES_PATH}tuple.h
  ${BASE_SOURCES_PATH}type_id.cc
  ${BASE_SOURCES_PATH}type_id.h
  ${BASE_SOURCES_PATH}unguessable_token.cc
  ${BASE_SOURCES_PATH}unguessable_token.h
  ${BASE_SOURCES_PATH}updateable_sequenced_task_runner.h
  ${BASE_SOURCES_PATH}value_conversions.cc
  ${BASE_SOURCES_PATH}value_conversions.h
  ${BASE_SOURCES_PATH}value_iterators.cc
  ${BASE_SOURCES_PATH}value_iterators.h
  ${BASE_SOURCES_PATH}values.cc
  ${BASE_SOURCES_PATH}values.h
  ${BASE_SOURCES_PATH}version.cc
  ${BASE_SOURCES_PATH}version.h
  ${BASE_SOURCES_PATH}vlog.cc
  ${BASE_SOURCES_PATH}vlog.h
  # base_static ###
  ${BASE_SOURCES_PATH}base_switches.cc
  ${BASE_SOURCES_PATH}base_switches.h
  # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1929
  ## "power_monitor/power_monitor_device_source_stub.cc"
  # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L2747
  ## ${BASE_SOURCES_PATH}files/dir_reader_posix_unittest.cc
  ## ${BASE_SOURCES_PATH}files/file_descriptor_watcher_posix_unittest.cc
  ## ${BASE_SOURCES_PATH}message_loop/message_loop_io_posix_unittest.cc
  ## ${BASE_SOURCES_PATH}posix/file_descriptor_shuffle_unittest.cc
  ## ${BASE_SOURCES_PATH}posix/unix_domain_socket_unittest.cc
  ## ${BASE_SOURCES_PATH}task/thread_pool/task_tracker_posix_unittest.cc
  ### build ###
  #${BUILD_CONFIG_PARENT_PATH}/build_config.h
)

if(BASE_USE_PARTITION_ALLOCATOR)
  list(APPEND BASE_SOURCES
    # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1633
    ${BASE_SOURCES_PATH}allocator/partition_allocator/address_space_randomization.cc
    ${BASE_SOURCES_PATH}allocator/partition_allocator/address_space_randomization.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/oom.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/oom_callback.cc
    ${BASE_SOURCES_PATH}allocator/partition_allocator/oom_callback.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/page_allocator.cc
    ${BASE_SOURCES_PATH}allocator/partition_allocator/page_allocator.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/page_allocator_internal.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_alloc.cc
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_alloc.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_alloc_constants.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_bucket.cc
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_bucket.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_cookie.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_direct_map_extent.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_freelist_entry.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_oom.cc
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_oom.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_page.cc
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_page.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_root_base.cc
    ${BASE_SOURCES_PATH}allocator/partition_allocator/partition_root_base.h
    ${BASE_SOURCES_PATH}allocator/partition_allocator/spin_lock.cc
    ${BASE_SOURCES_PATH}allocator/partition_allocator/spin_lock.h
  )
else()
  message(FATAL_ERROR "only BASE_USE_PARTITION_ALLOCATOR supported for now")
endif(BASE_USE_PARTITION_ALLOCATOR)

if(TARGET_EMSCRIPTEN OR TARGET_LINUX)
  if(BASE_USE_PARTITION_ALLOCATOR)
    list(APPEND BASE_SOURCES
      # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1665
      ${BASE_SOURCES_PATH}allocator/partition_allocator/page_allocator_internals_posix.h
    )
  endif(BASE_USE_PARTITION_ALLOCATOR)
  list(APPEND BASE_SOURCES
    ${BASE_SOURCES_PATH}debug/stack_trace_posix.cc
    # see https://github.com/chromium/chromium/blob/9db0b5162b8648833c3a6b1af044cebd9d7d3855/base/BUILD.gn#L1772
    ${BASE_SOURCES_PATH}strings/string16.cc
    ${BASE_SOURCES_PATH}memory/shared_memory_helper.cc
    ${BASE_SOURCES_PATH}memory/shared_memory_helper.h
    ${BASE_SOURCES_PATH}file_descriptor_store.cc
    ${BASE_SOURCES_PATH}file_descriptor_store.h
    ${BASE_SOURCES_PATH}debug/proc_maps_linux.cc
    ${BASE_SOURCES_PATH}debug/proc_maps_linux.h
    #${BASE_SOURCES_PATH}atomicops_internals_portable.h
    #${BASE_SOURCES_PATH}critical_closure_internal_ios.mm
    ${BASE_SOURCES_PATH}debug/activity_analyzer.cc
    ${BASE_SOURCES_PATH}debug/activity_analyzer.h
    ${BASE_SOURCES_PATH}debug/activity_tracker.cc
    ${BASE_SOURCES_PATH}debug/activity_tracker.h
    ###${BASE_SOURCES_PATH}debug/alias.cc
    ###${BASE_SOURCES_PATH}debug/alias.h
    ### ${BASE_SOURCES_PATH}debug/asan_invalid_access.cc
    ### ${BASE_SOURCES_PATH}debug/asan_invalid_access.h
    #${BASE_SOURCES_PATH}debug/close_handle_hook_win.cc
    #${BASE_SOURCES_PATH}debug/close_handle_hook_win.h
    ${BASE_SOURCES_PATH}debug/crash_logging.cc
    ${BASE_SOURCES_PATH}debug/crash_logging.h
    ${BASE_SOURCES_PATH}debug/debugger.cc
    ${BASE_SOURCES_PATH}debug/debugger.h
    #${BASE_SOURCES_PATH}debug/debugger_win.cc
    ${BASE_SOURCES_PATH}debug/dump_without_crashing.cc
    ${BASE_SOURCES_PATH}debug/dump_without_crashing.h
    #${BASE_SOURCES_PATH}debug/gdi_debug_util_win.cc
    #${BASE_SOURCES_PATH}debug/gdi_debug_util_win.h
    #${BASE_SOURCES_PATH}debug/invalid_access_win.cc
    #${BASE_SOURCES_PATH}debug/invalid_access_win.h
    ${BASE_SOURCES_PATH}debug/leak_annotations.h
    ${BASE_SOURCES_PATH}debug/leak_tracker.h
    ${BASE_SOURCES_PATH}debug/profiler.cc
    ${BASE_SOURCES_PATH}debug/profiler.h
    ${BASE_SOURCES_PATH}debug/stack_trace.cc
    ${BASE_SOURCES_PATH}debug/stack_trace.h
    #${BASE_SOURCES_PATH}debug/stack_trace_android.cc
    #${BASE_SOURCES_PATH}debug/stack_trace_win.cc
    ${BASE_SOURCES_PATH}debug/task_trace.cc
    ${BASE_SOURCES_PATH}debug/task_trace.h
    ${BASE_SOURCES_PATH}posix/eintr_wrapper.h
    ${BASE_SOURCES_PATH}posix/file_descriptor_shuffle.cc
    ${BASE_SOURCES_PATH}posix/file_descriptor_shuffle.h
    ${BASE_SOURCES_PATH}posix/global_descriptors.cc
    ${BASE_SOURCES_PATH}posix/global_descriptors.h
    ${BASE_SOURCES_PATH}posix/can_lower_nice_to.cc
    ${BASE_SOURCES_PATH}posix/can_lower_nice_to.h
    # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1929
    ${BASE_SOURCES_PATH}power_monitor/power_monitor_device_source_stub.cc
    # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1903
    ${BASE_SOURCES_PATH}memory/platform_shared_memory_region_posix.cc
    ${BASE_SOURCES_PATH}memory/shared_memory_handle_posix.cc
    # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1910
    ${BASE_SOURCES_PATH}memory/shared_memory_posix.cc
    # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1914
    ${BASE_SOURCES_PATH}time/time_conversion_posix.cc
    ${BASE_SOURCES_PATH}time/time_exploded_posix.cc
    ${BASE_SOURCES_PATH}time/time_now_posix.cc
    # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L2747
    ###${BASE_SOURCES_PATH}files/dir_reader_posix_unittest.cc
    ###${BASE_SOURCES_PATH}files/file_descriptor_watcher_posix_unittest.cc
    ###${BASE_SOURCES_PATH}message_loop/message_loop_io_posix_unittest.cc
    ###${BASE_SOURCES_PATH}posix/file_descriptor_shuffle_unittest.cc
    ###${BASE_SOURCES_PATH}posix/unix_domain_socket_unittest.cc
    ###${BASE_SOURCES_PATH}task/thread_pool/task_tracker_posix_unittest.cc
    ${BASE_SOURCES_PATH}debug/debugger_posix.cc
    ${BASE_SOURCES_PATH}files/file_enumerator_posix.cc
    ${BASE_SOURCES_PATH}files/file_posix.cc
    ${BASE_SOURCES_PATH}posix/unix_domain_socket.cc
    ${BASE_SOURCES_PATH}posix/unix_domain_socket.h
    ${BASE_SOURCES_PATH}process/launch_posix.cc
    ${BASE_SOURCES_PATH}base_paths_posix.h
    # posix
    ${BASE_SOURCES_PATH}base_paths_posix.cc
    ${BASE_SOURCES_PATH}file_descriptor_posix.h
    ${BASE_SOURCES_PATH}files/dir_reader_posix.h
    ${BASE_SOURCES_PATH}files/file_util_posix.cc
    ${BASE_SOURCES_PATH}files/memory_mapped_file_posix.cc
    ${BASE_SOURCES_PATH}memory/protected_memory_posix.cc
    ${BASE_SOURCES_PATH}message_loop/watchable_io_message_pump_posix.cc
    ${BASE_SOURCES_PATH}message_loop/watchable_io_message_pump_posix.h
    ${BASE_SOURCES_PATH}native_library_posix.cc
    ${BASE_SOURCES_PATH}posix/safe_strerror.cc
    ${BASE_SOURCES_PATH}posix/safe_strerror.h
    ${BASE_SOURCES_PATH}process/kill_posix.cc
    ${BASE_SOURCES_PATH}process/process_handle_posix.cc
    ${BASE_SOURCES_PATH}process/process_posix.cc
    ${BASE_SOURCES_PATH}profiler/stack_sampler_posix.cc
    ${BASE_SOURCES_PATH}rand_util_posix.cc
    ${BASE_SOURCES_PATH}sampling_heap_profiler/module_cache_posix.cc
    ${BASE_SOURCES_PATH}strings/string_util_posix.h
    ${BASE_SOURCES_PATH}strings/sys_string_conversions_posix.cc
    ${BASE_SOURCES_PATH}sync_socket_posix.cc
    ${BASE_SOURCES_PATH}synchronization/condition_variable_posix.cc
    ${BASE_SOURCES_PATH}synchronization/lock_impl_posix.cc
    ${BASE_SOURCES_PATH}synchronization/waitable_event_posix.cc
    ${BASE_SOURCES_PATH}synchronization/waitable_event_watcher_posix.cc
    ${BASE_SOURCES_PATH}system/sys_info_posix.cc
    ${BASE_SOURCES_PATH}threading/platform_thread_internal_posix.cc
    ${BASE_SOURCES_PATH}threading/platform_thread_internal_posix.h
    ${BASE_SOURCES_PATH}threading/platform_thread_posix.cc
    ${BASE_SOURCES_PATH}threading/thread_local_storage_posix.cc
    ${BASE_SOURCES_PATH}timer/hi_res_timer_manager_posix.cc
    # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1185
    ${BASE_SOURCES_PATH}base_paths_posix.h
    #
    ${BASE_SOURCES_PATH}threading/platform_thread_linux.cc
    #
    ${BASE_SOURCES_PATH}files/file_util_linux.cc
    ${BASE_SOURCES_PATH}files/file_enumerator_posix.cc
    ${BASE_SOURCES_PATH}files/file_posix.cc
  )
endif(TARGET_EMSCRIPTEN OR TARGET_LINUX)

if(TARGET_LINUX) # TODO: see TARGET_LINUX above!!!
  list(APPEND BASE_SOURCES
    ${BASE_SOURCES_PATH}process/memory_linux.cc
    ${BASE_SOURCES_PATH}process/process_handle_linux.cc
    #
    ${BASE_SOURCES_PATH}process/process_iterator_linux.cc
    #${BASE_SOURCES_PATH}process/process_iterator_mac.cc
    #${BASE_SOURCES_PATH}process/process_iterator_win.cc
    ${BASE_SOURCES_PATH}process/process_linux.cc
    ${BASE_SOURCES_PATH}process/internal_linux.cc
    ${BASE_SOURCES_PATH}process/internal_linux.h
    ${BASE_SOURCES_PATH}linux_util.cc
    ${BASE_SOURCES_PATH}linux_util.h
    ${BASE_SOURCES_PATH}files/file_path_watcher_linux.cc
    ${BASE_SOURCES_PATH}files/dir_reader_linux.h
    #
    ${BASE_SOURCES_PATH}threading/platform_thread_linux.cc
    #
    ${BASE_SOURCES_PATH}files/file_util_linux.cc
    ${BASE_SOURCES_PATH}process/memory_linux.cc
    ${BASE_SOURCES_PATH}process/process_handle_linux.cc
    ${BASE_SOURCES_PATH}process/process_metrics_linux.cc
    #
    #${BASE_SOURCES_PATH}debug/debugger_posix.cc
    # requires mojo::StructTraits<mojo_base::mojom::ProcessIdDataView,
    #
    ##${BASE_SOURCES_PATH}debug/stack_trace_posix.cc
    ${BASE_SOURCES_PATH}posix/eintr_wrapper.h
    ${BASE_SOURCES_PATH}posix/file_descriptor_shuffle.cc
    ${BASE_SOURCES_PATH}posix/file_descriptor_shuffle.h
    ${BASE_SOURCES_PATH}posix/global_descriptors.cc
    ${BASE_SOURCES_PATH}posix/global_descriptors.h
    ${BASE_SOURCES_PATH}posix/unix_domain_socket.cc
    ${BASE_SOURCES_PATH}posix/unix_domain_socket.h
    ${BASE_SOURCES_PATH}process/launch_posix.cc
    ${BASE_SOURCES_PATH}process/process_metrics_posix.cc
    ${BASE_SOURCES_PATH}base_paths_posix.h
    # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1929
    ${BASE_SOURCES_PATH}power_monitor/power_monitor_device_source_stub.cc
    # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L2747
    ###${BASE_SOURCES_PATH}files/dir_reader_posix_unittest.cc
    ###${BASE_SOURCES_PATH}files/file_descriptor_watcher_posix_unittest.cc
    ###${BASE_SOURCES_PATH}message_loop/message_loop_io_posix_unittest.cc
    ###${BASE_SOURCES_PATH}posix/file_descriptor_shuffle_unittest.cc
    ###${BASE_SOURCES_PATH}posix/unix_domain_socket_unittest.cc
    ###${BASE_SOURCES_PATH}task/thread_pool/task_tracker_posix_unittest.cc
  )
  list(APPEND BASE_SOURCES
    # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1894
    ${BASE_SOURCES_PATH}message_loop/message_pump_libevent.cc
    #${BASE_SOURCES_PATH}message_loop/message_pump_libevent.h
    ${BASE_SOURCES_PATH}task/thread_pool/task_tracker_posix.cc
    #${BASE_SOURCES_PATH}task/thread_pool/task_tracker_posix.h
    ${BASE_SOURCES_PATH}files/file_descriptor_watcher_posix.cc
    #${BASE_SOURCES_PATH}files/file_descriptor_watcher_posix.h
  )
endif(TARGET_LINUX)

if(TARGET_WINDOWS)
  if(BASE_USE_PARTITION_ALLOCATOR)
    list(APPEND BASE_SOURCES
      # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1665
      ${BASE_SOURCES_PATH}allocator/partition_allocator/page_allocator_internals_win.h
    )
  endif(BASE_USE_PARTITION_ALLOCATOR)

  list(APPEND BASE_SOURCES
    ## TODO ##
    ${BASE_SOURCES_PATH}trace_event/trace_event_etw_export_win.cc
    ## TODO ##
    ${BASE_SOURCES_PATH}trace_event/trace_event_etw_export_win.h
    ${BASE_SOURCES_PATH}timer/hi_res_timer_manager_win.cc
    ${BASE_SOURCES_PATH}threading/thread_local_storage_win.cc
    ${BASE_SOURCES_PATH}threading/platform_thread_win.cc
    ${BASE_SOURCES_PATH}threading/platform_thread_win.h
    ${BASE_SOURCES_PATH}task/thread_pool/thread_group_native_win.cc
    ${BASE_SOURCES_PATH}task/thread_pool/thread_group_native_win.h
    ${BASE_SOURCES_PATH}scoped_clear_last_error_win.cc
    ${BASE_SOURCES_PATH}sampling_heap_profiler/module_cache_win.cc
    ${BASE_SOURCES_PATH}profiler/thread_delegate_win.cc
    ${BASE_SOURCES_PATH}profiler/thread_delegate_win.h
    ${BASE_SOURCES_PATH}profiler/stack_sampler_win.cc
    ${BASE_SOURCES_PATH}profiler/native_unwinder_win.cc
    ${BASE_SOURCES_PATH}profiler/native_unwinder_win.h
    ${BASE_SOURCES_PATH}process/process_metrics_win.cc
    ${BASE_SOURCES_PATH}process/process_win.cc
    ${BASE_SOURCES_PATH}process/process_info_win.cc
    ${BASE_SOURCES_PATH}process/process_handle_win.cc
    ${BASE_SOURCES_PATH}process/memory_win.cc
    ${BASE_SOURCES_PATH}process/launch_win.cc
    ${BASE_SOURCES_PATH}process/kill_win.cc
    ${BASE_SOURCES_PATH}native_library_win.cc
    ${BASE_SOURCES_PATH}message_loop/message_pump_win.cc
    ${BASE_SOURCES_PATH}message_loop/message_pump_win.h
    ${BASE_SOURCES_PATH}memory/protected_memory_win.cc
    ${BASE_SOURCES_PATH}memory/memory_pressure_monitor_win.cc
    ${BASE_SOURCES_PATH}memory/memory_pressure_monitor_win.h
    ${BASE_SOURCES_PATH}logging_win.cc
    ${BASE_SOURCES_PATH}logging_win.h
    ${BASE_SOURCES_PATH}files/memory_mapped_file_win.cc
    ${BASE_SOURCES_PATH}files/file_util_win.cc
    ${BASE_SOURCES_PATH}files/file_win.cc
    ${BASE_SOURCES_PATH}files/file_path_watcher_win.cc
    ${BASE_SOURCES_PATH}file_version_info_win.cc
    ${BASE_SOURCES_PATH}file_version_info_win.h
    ${BASE_SOURCES_PATH}enterprise_util_win.cc
    ${BASE_SOURCES_PATH}debug/stack_trace_win.cc
    ${BASE_SOURCES_PATH}debug/gdi_debug_util_win.cc
    ${BASE_SOURCES_PATH}debug/gdi_debug_util_win.h
    ${BASE_SOURCES_PATH}debug/invalid_access_win.cc
    ${BASE_SOURCES_PATH}debug/invalid_access_win.h
    ${BASE_SOURCES_PATH}debug/debugger_win.cc
    ${BASE_SOURCES_PATH}debug/close_handle_hook_win.cc
    ${BASE_SOURCES_PATH}debug/close_handle_hook_win.h
    ${BASE_SOURCES_PATH}strings/string_util_win.h
    ${BASE_SOURCES_PATH}strings/sys_string_conversions_win.cc
    ${BASE_SOURCES_PATH}sync_socket_win.cc
    ${BASE_SOURCES_PATH}synchronization/condition_variable_win.cc
    ${BASE_SOURCES_PATH}synchronization/lock_impl_win.cc
    ${BASE_SOURCES_PATH}synchronization/waitable_event_watcher_win.cc
    ${BASE_SOURCES_PATH}synchronization/waitable_event_win.cc
  )

  list(APPEND BASE_SOURCES
    # static_library("pe_image")
    ${BASE_SOURCES_PATH}win/current_module.h
    ${BASE_SOURCES_PATH}win/pe_image.cc
    ${BASE_SOURCES_PATH}win/pe_image.h
    #
    #${BASE_SOURCES_PATH}win/static_constants.cc
    #${BASE_SOURCES_PATH}win/static_constants.h
    #
    ${BASE_SOURCES_PATH}win/async_operation.h
    ${BASE_SOURCES_PATH}win/atl.h
    ${BASE_SOURCES_PATH}win/com_init_check_hook.cc
    ${BASE_SOURCES_PATH}win/com_init_check_hook.h
    ${BASE_SOURCES_PATH}win/com_init_util.cc
    ${BASE_SOURCES_PATH}win/com_init_util.h
    ${BASE_SOURCES_PATH}win/core_winrt_util.cc
    ${BASE_SOURCES_PATH}win/core_winrt_util.h
    ${BASE_SOURCES_PATH}win/current_module.h
    ${BASE_SOURCES_PATH}win/embedded_i18n/language_selector.cc
    ${BASE_SOURCES_PATH}win/embedded_i18n/language_selector.h
    ${BASE_SOURCES_PATH}win/enum_variant.cc
    ${BASE_SOURCES_PATH}win/enum_variant.h
    ${BASE_SOURCES_PATH}win/event_trace_consumer.h
    ${BASE_SOURCES_PATH}win/event_trace_controller.cc
    ${BASE_SOURCES_PATH}win/event_trace_controller.h
    ${BASE_SOURCES_PATH}win/event_trace_provider.cc
    ${BASE_SOURCES_PATH}win/event_trace_provider.h
    ${BASE_SOURCES_PATH}win/hstring_reference.cc
    ${BASE_SOURCES_PATH}win/hstring_reference.h
    ${BASE_SOURCES_PATH}win/i18n.cc
    ${BASE_SOURCES_PATH}win/i18n.h
    ${BASE_SOURCES_PATH}win/iat_patch_function.cc
    ${BASE_SOURCES_PATH}win/iat_patch_function.h
    ${BASE_SOURCES_PATH}win/iunknown_impl.cc
    ${BASE_SOURCES_PATH}win/iunknown_impl.h
    ${BASE_SOURCES_PATH}win/message_window.cc
    ${BASE_SOURCES_PATH}win/message_window.h
    ${BASE_SOURCES_PATH}win/object_watcher.cc
    ${BASE_SOURCES_PATH}win/object_watcher.h
    ${BASE_SOURCES_PATH}win/patch_util.cc
    ${BASE_SOURCES_PATH}win/patch_util.h
    ${BASE_SOURCES_PATH}win/post_async_results.h
    ${BASE_SOURCES_PATH}win/process_startup_helper.cc
    ${BASE_SOURCES_PATH}win/process_startup_helper.h
    ${BASE_SOURCES_PATH}win/propvarutil.h
    ${BASE_SOURCES_PATH}win/reference.h
    ${BASE_SOURCES_PATH}win/registry.cc
    ${BASE_SOURCES_PATH}win/registry.h
    ${BASE_SOURCES_PATH}win/resource_util.cc
    ${BASE_SOURCES_PATH}win/resource_util.h
    ${BASE_SOURCES_PATH}win/scoped_bstr.cc
    ${BASE_SOURCES_PATH}win/scoped_bstr.h
    ${BASE_SOURCES_PATH}win/scoped_co_mem.h
    ${BASE_SOURCES_PATH}win/scoped_com_initializer.cc
    ${BASE_SOURCES_PATH}win/scoped_com_initializer.h
    ${BASE_SOURCES_PATH}win/scoped_gdi_object.h
    ${BASE_SOURCES_PATH}win/scoped_handle.cc
    ${BASE_SOURCES_PATH}win/scoped_handle.h
    ${BASE_SOURCES_PATH}win/scoped_handle_verifier.cc
    ${BASE_SOURCES_PATH}win/scoped_handle_verifier.h
    ${BASE_SOURCES_PATH}win/scoped_hdc.h
    ${BASE_SOURCES_PATH}win/scoped_hglobal.h
    ${BASE_SOURCES_PATH}win/scoped_hstring.cc
    ${BASE_SOURCES_PATH}win/scoped_hstring.h
    ${BASE_SOURCES_PATH}win/scoped_process_information.cc
    ${BASE_SOURCES_PATH}win/scoped_process_information.h
    ${BASE_SOURCES_PATH}win/scoped_propvariant.h
    ${BASE_SOURCES_PATH}win/scoped_safearray.h
    ${BASE_SOURCES_PATH}win/scoped_select_object.h
    ${BASE_SOURCES_PATH}win/scoped_variant.cc
    ${BASE_SOURCES_PATH}win/scoped_variant.h
    ${BASE_SOURCES_PATH}win/scoped_windows_thread_environment.h
    ${BASE_SOURCES_PATH}win/scoped_winrt_initializer.cc
    ${BASE_SOURCES_PATH}win/scoped_winrt_initializer.h
    ${BASE_SOURCES_PATH}win/shlwapi.h
    ${BASE_SOURCES_PATH}win/shortcut.cc
    ${BASE_SOURCES_PATH}win/shortcut.h
    ${BASE_SOURCES_PATH}win/sphelper.h
    ${BASE_SOURCES_PATH}win/startup_information.cc
    ${BASE_SOURCES_PATH}win/startup_information.h
    ${BASE_SOURCES_PATH}win/typed_event_handler.h
    ${BASE_SOURCES_PATH}win/vector.cc
    ${BASE_SOURCES_PATH}win/vector.h
    ${BASE_SOURCES_PATH}win/win_util.cc
    ${BASE_SOURCES_PATH}win/win_util.h
    ${BASE_SOURCES_PATH}win/wincrypt_shim.h
    ${BASE_SOURCES_PATH}win/windows_defines.inc
    ${BASE_SOURCES_PATH}win/windows_types.h
    ${BASE_SOURCES_PATH}win/windows_undefines.inc
    ${BASE_SOURCES_PATH}win/windows_version.cc
    ${BASE_SOURCES_PATH}win/windows_version.h
    ${BASE_SOURCES_PATH}win/windowsx_shim.h
    ${BASE_SOURCES_PATH}win/winrt_storage_util.cc
    ${BASE_SOURCES_PATH}win/winrt_storage_util.h
    ${BASE_SOURCES_PATH}win/wmi.cc
    ${BASE_SOURCES_PATH}win/wmi.h
    ${BASE_SOURCES_PATH}win/wrapped_window_proc.cc
    ${BASE_SOURCES_PATH}win/wrapped_window_proc.h
    # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1894
    ${BASE_SOURCES_PATH}message_loop/message_pump_win.cc
    ${BASE_SOURCES_PATH}message_loop/message_pump_win.h
    ${BASE_SOURCES_PATH}debug/close_handle_hook_win.cc
    ${BASE_SOURCES_PATH}debug/close_handle_hook_win.h
    ${BASE_SOURCES_PATH}debug/debugger_win.cc
    ${BASE_SOURCES_PATH}debug/gdi_debug_util_win.cc
    ${BASE_SOURCES_PATH}debug/gdi_debug_util_win.h
    ${BASE_SOURCES_PATH}debug/invalid_access_win.cc
    ${BASE_SOURCES_PATH}debug/invalid_access_win.h
    ${BASE_SOURCES_PATH}debug/stack_trace_win.cc
    ${BASE_SOURCES_PATH}enterprise_util_win.cc
    ${BASE_SOURCES_PATH}file_version_info_win.cc
    ${BASE_SOURCES_PATH}file_version_info_win.h
    ${BASE_SOURCES_PATH}files/file_path_watcher_win.cc
    ${BASE_SOURCES_PATH}files/file_util_win.cc
    ${BASE_SOURCES_PATH}files/file_win.cc
    ${BASE_SOURCES_PATH}files/memory_mapped_file_win.cc
    ${BASE_SOURCES_PATH}logging_win.cc
    ${BASE_SOURCES_PATH}logging_win.h
    ${BASE_SOURCES_PATH}memory/protected_memory_win.cc
    ${BASE_SOURCES_PATH}native_library_win.cc
    ${BASE_SOURCES_PATH}process/kill_win.cc
    ${BASE_SOURCES_PATH}process/launch_win.cc
    ${BASE_SOURCES_PATH}process/memory_win.cc
    ${BASE_SOURCES_PATH}process/process_handle_win.cc
    ${BASE_SOURCES_PATH}process/process_info_win.cc
    ${BASE_SOURCES_PATH}process/process_iterator_win.cc
    ${BASE_SOURCES_PATH}process/process_metrics_win.cc
    ${BASE_SOURCES_PATH}process/process_win.cc
    ${BASE_SOURCES_PATH}profiler/native_unwinder_win.cc
    ${BASE_SOURCES_PATH}profiler/native_unwinder_win.h
    ${BASE_SOURCES_PATH}profiler/stack_sampler_win.cc
    #${BASE_SOURCES_PATH}profiler/suspendable_thread_delegate_win.cc
    #${BASE_SOURCES_PATH}profiler/suspendable_thread_delegate_win.h
    ${BASE_SOURCES_PATH}sampling_heap_profiler/module_cache_win.cc
    ${BASE_SOURCES_PATH}scoped_clear_last_error_win.cc
    ${BASE_SOURCES_PATH}strings/string_util_win.h
    ${BASE_SOURCES_PATH}strings/sys_string_conversions_win.cc
    ${BASE_SOURCES_PATH}sync_socket_win.cc
    ${BASE_SOURCES_PATH}synchronization/condition_variable_win.cc
    ${BASE_SOURCES_PATH}synchronization/lock_impl_win.cc
    ${BASE_SOURCES_PATH}synchronization/waitable_event_watcher_win.cc
    ${BASE_SOURCES_PATH}synchronization/waitable_event_win.cc
    ${BASE_SOURCES_PATH}task/thread_pool/thread_group_native_win.cc
    ${BASE_SOURCES_PATH}task/thread_pool/thread_group_native_win.h
    ${BASE_SOURCES_PATH}threading/platform_thread_win.cc
    ${BASE_SOURCES_PATH}threading/platform_thread_win.h
    ${BASE_SOURCES_PATH}threading/thread_local_storage_win.cc
    ${BASE_SOURCES_PATH}timer/hi_res_timer_manager_win.cc
    # TODO # ${BASE_SOURCES_PATH}trace_event/trace_event_etw_export_win.cc
    # TODO # ${BASE_SOURCES_PATH}trace_event/trace_event_etw_export_win.h
    ${BASE_SOURCES_PATH}base_paths_win.cc
    ${BASE_SOURCES_PATH}base_paths_win.h
    # ${BASE_SOURCES_PATH}allocator/allocator_shim_default_dispatch_to_winheap.cc # if (use_allocator_shim)
    # ${BASE_SOURCES_PATH}allocator/allocator_shim_override_ucrt_symbols_win.h # if (use_allocator_shim)
    # ${BASE_SOURCES_PATH}allocator/winheap_stubs_win.cc # if (use_allocator_shim)
    # ${BASE_SOURCES_PATH}allocator/winheap_stubs_win.h # if (use_allocator_shim)
    # ${BASE_SOURCES_PATH}allocator/partition_allocator/page_allocator_internals_win.h # if (use_allocator_shim)
    ${BASE_SOURCES_PATH}files/file_enumerator_win.cc
    ${BASE_SOURCES_PATH}memory/platform_shared_memory_region_win.cc
    ${BASE_SOURCES_PATH}memory/shared_memory_handle_win.cc
    ${BASE_SOURCES_PATH}memory/shared_memory_win.cc
    ${BASE_SOURCES_PATH}power_monitor/power_monitor_device_source_win.cc
    ${BASE_SOURCES_PATH}profiler/win32_stack_frame_unwinder.cc
    ${BASE_SOURCES_PATH}profiler/win32_stack_frame_unwinder.h
    ${BASE_SOURCES_PATH}rand_util_win.cc
    ${BASE_SOURCES_PATH}system/sys_info_win.cc
    ${BASE_SOURCES_PATH}time/time_win.cc
  )
endif(TARGET_WINDOWS)

list(APPEND BASE_SOURCES
  ${BASE_SOURCES_PATH}base_paths.cc
  #if (is_linux) {
  #  sources += [
  #    "base_paths_posix.cc",
  #    "debug/elf_reader_linux.cc",
  #    "debug/elf_reader_linux.h",
  #  ]
  #}
)

if(TARGET_LINUX)
  list(APPEND BASE_SOURCES
    #if (!is_nacl) {
    #  sources += [
    #    "base_paths.cc",
    #    "base_paths.h",
    #    "base_paths_android.cc",
    #    "base_paths_android.h",
    #    "base_paths_mac.h",
    #    "base_paths_mac.mm",
    #    "base_paths_posix.h",
    #    "base_paths_win.cc",
    #    "base_paths_win.h",
    #    "metrics/persistent_histogram_storage.cc",
    #    "metrics/persistent_histogram_storage.h",
    #  ]
    ##${BASE_SOURCES_PATH}process/process_metrics_posix.cc
    ## TODO ##
    ##${BASE_SOURCES_PATH}debug/stack_trace_posix.cc
    #requires third_party/xdg_mime
    ## TODO ##
    ${BASE_SOURCES_PATH}nix/mime_util_xdg.cc
    #${BASE_SOURCES_PATH}nix/mime_util_xdg.h
    ##
    ${BASE_SOURCES_PATH}nix/xdg_util.cc
    #${BASE_SOURCES_PATH}nix/xdg_util.h
    ${BASE_SOURCES_PATH}system/sys_info_linux.cc
    ${BASE_SOURCES_PATH}linux_util.cc # if (!is_android)
    #${BASE_SOURCES_PATH}linux_util.h # if (!is_android)
    #
    ${BASE_SOURCES_PATH}debug/elf_reader.cc # only for linux
    ${BASE_SOURCES_PATH}debug/elf_reader.h # only for linux
    #
    ${BASE_SOURCES_PATH}files/file_descriptor_watcher_posix.cc
    ${BASE_SOURCES_PATH}files/file_descriptor_watcher_posix.h
    # #${BASE_SOURCES_PATH}debug/proc_maps_linux.cc
    # #${BASE_SOURCES_PATH}debug/proc_maps_linux.h
    ${BASE_SOURCES_PATH}files/file_util_linux.cc
    ${BASE_SOURCES_PATH}process/memory_linux.cc
    ${BASE_SOURCES_PATH}process/process_handle_linux.cc
    ${BASE_SOURCES_PATH}process/process_metrics_linux.cc
    ${BASE_SOURCES_PATH}threading/platform_thread_linux.cc
    ${BASE_SOURCES_PATH}process/process_metrics_linux.cc
    #${BASE_SOURCES_PATH}debug/proc_maps_linux.cc
    #${BASE_SOURCES_PATH}debug/proc_maps_linux.h
    ##https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1942
    #${BASE_SOURCES_PATH}message_loop/message_pump_glib.cc
    #${BASE_SOURCES_PATH}message_loop/message_pump_glib.h
    ##https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1120
    # ${BASE_SOURCES_PATH}debug/debugger_posix.cc
    # ${BASE_SOURCES_PATH}debug/stack_trace_posix.cc
    # ${BASE_SOURCES_PATH}files/file_descriptor_watcher_posix.cc
    # ${BASE_SOURCES_PATH}files/file_descriptor_watcher_posix.h
    # ${BASE_SOURCES_PATH}files/file_enumerator_posix.cc
    # ${BASE_SOURCES_PATH}files/file_posix.cc
    # ${BASE_SOURCES_PATH}posix/eintr_wrapper.h
    # ${BASE_SOURCES_PATH}posix/file_descriptor_shuffle.cc
    # ${BASE_SOURCES_PATH}posix/file_descriptor_shuffle.h
    # ${BASE_SOURCES_PATH}posix/global_descriptors.cc
    # ${BASE_SOURCES_PATH}posix/global_descriptors.h
    # ${BASE_SOURCES_PATH}posix/unix_domain_socket.cc
    # ${BASE_SOURCES_PATH}posix/unix_domain_socket.h
    # ${BASE_SOURCES_PATH}process/launch_posix.cc
    # ${BASE_SOURCES_PATH}process/process_metrics_posix.cc
    ${BASE_SOURCES_PATH}task/thread_pool/task_tracker_posix.cc
    ${BASE_SOURCES_PATH}task/thread_pool/task_tracker_posix.h
    ${BASE_SOURCES_PATH}files/file_descriptor_watcher_posix.cc
    ${BASE_SOURCES_PATH}files/file_descriptor_watcher_posix.h
  )
  list(APPEND EXTRA_DEFINES
    #USE_SYMBOLIZE=1
  )
endif()

if(NOT DEFINED ENABLE_COBALT)
  message(FATAL_ERROR "NOT DEFINED: ENABLE_COBALT")
endif(NOT DEFINED ENABLE_COBALT)
if(ENABLE_COBALT)
  list(APPEND COBALT_port_base_SOURCES
    # TODO: port chromium base to starboard
    #${LOCAL_COBALT_DIR}base/base_paths_starboard.cc
    #${LOCAL_COBALT_DIR}base/debug/debugger_starboard.cc
    #${LOCAL_COBALT_DIR}base/debug/stack_trace_starboard.cc
    #${LOCAL_COBALT_DIR}base/files/file_enumerator_starboard.cc
    #${LOCAL_COBALT_DIR}base/files/file_starboard.cc
    #${LOCAL_COBALT_DIR}base/files/file_util_starboard.cc
    #${LOCAL_COBALT_DIR}base/message_loop/message_pump_io_starboard.cc
    #${LOCAL_COBALT_DIR}base/message_loop/message_pump_ui_starboard.cc
    #${LOCAL_COBALT_DIR}base/process/memory_starboard.cc
    #${LOCAL_COBALT_DIR}base/process/process_starboard.cc
    #${LOCAL_COBALT_DIR}base/profiler/native_stack_sampler_starboard.cc
    #${LOCAL_COBALT_DIR}base/rand_util_starboard.cc
    #${LOCAL_COBALT_DIR}base/sampling_heap_profiler/module_cache_starboard.cc
    #${LOCAL_COBALT_DIR}base/strings/sys_string_conversions_starboard.cc
    #${LOCAL_COBALT_DIR}base/synchronization/condition_variable_starboard.cc
    #${LOCAL_COBALT_DIR}base/synchronization/lock_impl_starboard.cc
    #${LOCAL_COBALT_DIR}base/synchronization/waitable_event_starboard.cc
    #${LOCAL_COBALT_DIR}base/sys_info_starboard.cc
    #${LOCAL_COBALT_DIR}base/threading/platform_thread_starboard.cc
    #${LOCAL_COBALT_DIR}base/threading/thread_local_storage_starboard.cc
    #${LOCAL_COBALT_DIR}base/time/time_now_starboard.cc
    ${LOCAL_COBALT_DIR}base/time/time_starboard.cc
  )
endif(ENABLE_COBALT)
