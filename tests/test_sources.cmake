chromium_base_test_gtest(${ROOT_PROJECT_NAME}-gmock "gmock.test.cpp")

chromium_base_test_gtest(${ROOT_PROJECT_NAME}-i18n "i18n.test.cpp")

# "i18n" is one of test program names
add_custom_command( TARGET ${ROOT_PROJECT_NAME}-i18n POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_CURRENT_SOURCE_DIR}/data
                        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} )

if (NOT CMAKE_BUILD_TYPE MATCHES "Debug" )
  list(APPEND base_unittests
    "build_time_unittest.cc"
  )
endif()

# TODO undefined reference to `g_native_library_exported_value'
# "scoped_native_library_unittest.cc"
# "native_library_unittest.cc"
#
# TODO requires helper_library.is_valid()
# "immediate_crash_unittest.cc"
#
# TODO
# [  FAILED  ] HeapAndPersistent/HistogramTest.WriteAscii/0, where GetParam() = false
# [  FAILED  ] HeapAndPersistent/HistogramTest.WriteAscii/1, where GetParam() = true
# [  FAILED  ] HeapAndPersistent/HistogramTest.ToGraphDict/0, where GetParam() = false
# [  FAILED  ] HeapAndPersistent/HistogramTest.ToGraphDict/1, where GetParam() = true
# [  FAILED  ] HeapAndPersistent/HistogramTest.ToGraphDictNormalize/0, where GetParam() = false
# [  FAILED  ] HeapAndPersistent/HistogramTest.ToGraphDictNormalize/1, where GetParam() = true
# "metrics/histogram_unittest.cc"
#
# TODO
# [  FAILED  ] HeapAndPersistent/SparseHistogramTest.WriteAscii/0, where GetParam() = false
# [  FAILED  ] HeapAndPersistent/SparseHistogramTest.WriteAscii/1, where GetParam() = true
# [  FAILED  ] HeapAndPersistent/SparseHistogramTest.ToGraphDict/0, where GetParam() = false
# [  FAILED  ] HeapAndPersistent/SparseHistogramTest.ToGraphDict/1, where GetParam() = true
# "metrics/sparse_histogram_unittest.cc"
#
# TODO
# [  FAILED  ] ProcessUtilTest.GetAppOutput
# [  FAILED  ] 149: ./base/process/process_util_unittest.cc:912: Failure
# [  FAILED  ] 149: Value of: GetAppOutput(command, &output)
# [  FAILED  ] 149:   Actual: false
# [  FAILED  ] 149: Expected: true
# [  FAILED  ] 149: ./base/process/process_util_unittest.cc:913: Failure
# "process/process_util_unittest.cc"
#
# TODO
# [  FAILED  ] ./base/profiler/module_cache_unittest.cc:117: Failure
# [  FAILED  ] Expected equality of these values:
# [  FAILED  ]   "base_unittests"
# [  FAILED  ]   module->GetDebugBasename().value()
# [  FAILED  ]     Which is: "chromium_base-module_cache_unittest"
# "profiler/module_cache_unittest.cc"
#
# TODO
# [  FAILED  ] 228: ./base/task/thread_pool/pooled_single_thread_task_runner_manager_unittest.cc:349: Failure
# [  FAILED  ] 228: Value of: PlatformThread::GetName()
# [  FAILED  ] 228: Expected: matches regular expression "^ThreadPoolSingleThreadSharedForeground\\d+$"
# [  FAILED  ] 228:   Actual: 0x7fdba86829c0 pointing to "ThreadPoolSingleThreadSharedForeground0" (of type char const*)
# "task/thread_pool/pooled_single_thread_task_runner_manager_unittest.cc"
#
# TODO
# [  FAILED  ] ReadEnumFromEnumsXml("Boolean")
# "test/metrics/histogram_enum_reader_unittest.cc"
#
# TODO
# [  FAILED  ] 258: [ RUN      ] ScopedRunLoopTimeoutTest.OnTimeoutLog
# [  FAILED  ] 258: /home/denis/.conan/data/conan_gtest/stable/conan/stable/build/6c4f123ede24f5b530592b743ef64a8b8bcd19e9/source_subfolder/googletest/src/gtest.cc:907: Failure
# [  FAILED  ] 258: Expected: 1 fatal failure containing "Run() timed out. Timeout set at TestBody@../../base/test/scoped_run_loop_timeout_unittest.cc:70.
# [  FAILED  ] 258: I like kittens!"
# [  FAILED  ] 258:   Actual:
# [  FAILED  ] 258: /home/denis/code/chromium_base_conan/base/test/scoped_run_loop_timeout_unittest.cc:79: Fatal failure:
# [  FAILED  ] 258: Failed
# [  FAILED  ] 258: RunLoop::Run() timed out. Timeout set at TestBody@/home/denis/code/chromium_base_conan/base/test/scoped_run_loop_timeout_unittest.cc:70.
# [  FAILED  ] 258: I like kittens!
# "test/scoped_run_loop_timeout_unittest.cc"
#
# TODO
# [  FAILED  ] 259: [ RUN      ] TaskEnvironmentTest.SetsDefaultRunTimeout
# [  FAILED  ] 259: /home/denis/.conan/data/conan_gtest/stable/conan/stable/build/6c4f123ede24f5b530592b743ef64a8b8bcd19e9/source_subfolder/googletest/src/gtest.cc:907: Failure
# [  FAILED  ] 259: Expected: 1 fatal failure containing "RunLoop::Run() timed out. Timeout set at TaskEnvironment@../../base/test/task_environment.cc:"
# [  FAILED  ] 259:   Actual:
# [  FAILED  ] 259: ./base/test/task_environment_unittest.cc:888: Fatal failure:
# [  FAILED  ] 259: Failed
# [  FAILED  ] 259: RunLoop::Run() timed out. Timeout set at TaskEnvironment@./base/test/task_environment.cc:404.
# [  FAILED  ] 259: {"active_queues":[{"any_thread_.immediate_incoming_queuecapacity":0,"any_thread_.immediate_incoming_queuesize":0,"delayed_incoming_queue":[],"delayed_incoming_queue_size":0,"delayed_work_queue":[],"delayed_work_queue_capacity":0,"delayed_work_queue_size":0,"enabled":true,"immediate_incoming_queue":[],"immediate_work_queue":[],"immediate_work_queue_capacity":0,"immediate_work_queue_size":0,"name":"task_environment_default","priority":"normal","task_queue_id":"0x7f84ffc278c0","time_domain_name":"RealTimeDomain"}],"native_work_priority":"best_effort","queues_to_delete":[],"queues_to_gracefully_shutdown":[],"selector":{"immediate_starvation_count":0},"time_domains":[{"name":"RealTimeDomain","registered_delay_count":0}]}
# "test/task_environment_unittest.cc"
#
list(APPEND base_unittests
  "allocator/tcmalloc_unittest.cc"
  "at_exit_unittest.cc"
  "atomicops_unittest.cc"
  "auto_reset_unittest.cc"
  "barrier_closure_unittest.cc"
  "base64_unittest.cc"
  "base64url_unittest.cc"
  "big_endian_unittest.cc"
  "bind_post_task_unittest.cc"
  "bind_unittest.cc"
  "bit_cast_unittest.cc"
  "bits_unittest.cc"
  "callback_helpers_unittest.cc"
  "callback_list_unittest.cc"
  "callback_unittest.cc"
  "cancelable_callback_unittest.cc"
  "check_unittest.cc"
  "command_line_unittest.cc"
  "component_export_unittest.cc"
  "containers/adapters_unittest.cc"
  "containers/buffer_iterator_unittest.cc"
  "containers/checked_iterators_unittest.cc"
  "containers/checked_range_unittest.cc"
  "containers/circular_deque_unittest.cc"
  "containers/contains_unittest.cc"
  "containers/contiguous_iterator_unittest.cc"
  "containers/fixed_flat_map_unittest.cc"
  "containers/fixed_flat_set_unittest.cc"
  "containers/flat_map_unittest.cc"
  "containers/flat_set_unittest.cc"
  "containers/flat_tree_unittest.cc"
  "containers/id_map_unittest.cc"
  "containers/intrusive_heap_unittest.cc"
  "containers/linked_list_unittest.cc"
  "containers/mru_cache_unittest.cc"
  "containers/small_map_unittest.cc"
  "containers/span_unittest.cc"
  "containers/stack_container_unittest.cc"
  "containers/unique_ptr_adapters_unittest.cc"
  "containers/vector_buffer_unittest.cc"
  "cpu_unittest.cc"
  "debug/activity_analyzer_unittest.cc"
  "debug/activity_tracker_unittest.cc"
  "debug/alias_unittest.cc"
  "debug/crash_logging_unittest.cc"
  "debug/debugger_unittest.cc"
  "debug/stack_trace_unittest.cc"
  "debug/task_trace_unittest.cc"
  "deferred_sequenced_task_runner_unittest.cc"
  "environment_unittest.cc"
  "feature_list_unittest.cc"
  "files/file_enumerator_unittest.cc"
  "files/file_path_unittest.cc"
  "files/file_path_watcher_unittest.cc"
  "files/file_proxy_unittest.cc"
  "files/file_unittest.cc"
  "files/file_util_unittest.cc"
  "files/important_file_writer_cleaner_unittest.cc"
  "files/important_file_writer_unittest.cc"
  "files/memory_mapped_file_unittest.cc"
  "files/scoped_temp_dir_unittest.cc"
  "functional/identity_unittest.cc"
  "functional/invoke_unittest.cc"
  "functional/not_fn_unittest.cc"
  "gmock_unittest.cc"
  "guid_unittest.cc"
  "hash/hash_unittest.cc"
  "hash/legacy_hash_unittest.cc"
  "hash/md5_constexpr_unittest.cc"
  "hash/md5_unittest.cc"
  "hash/sha1_unittest.cc"
  "i18n/break_iterator_unittest.cc"
  "i18n/case_conversion_unittest.cc"
  "i18n/char_iterator_unittest.cc"
  "i18n/character_encoding_unittest.cc"
  "i18n/file_util_icu_unittest.cc"
  "i18n/icu_string_conversions_unittest.cc"
  "i18n/icu_util_unittest.cc"
  "i18n/message_formatter_unittest.cc"
  "i18n/number_formatting_unittest.cc"
  "i18n/rtl_unittest.cc"
  "i18n/streaming_utf8_validator_unittest.cc"
  "i18n/string_search_unittest.cc"
  "i18n/time_formatting_unittest.cc"
  "i18n/timezone_unittest.cc"
  "json/json_parser_unittest.cc"
  "json/json_reader_unittest.cc"
  "json/json_value_converter_unittest.cc"
  "json/json_value_serializer_unittest.cc"
  "json/json_writer_unittest.cc"
  "json/string_escape_unittest.cc"
  "lazy_instance_unittest.cc"
  "location_unittest.cc"
  "logging_unittest.cc"
  "memory/aligned_memory_unittest.cc"
  "memory/checked_ptr_unittest.cc"
  "memory/discardable_memory_backing_field_trial_unittest.cc"
  "memory/discardable_shared_memory_unittest.cc"
  "memory/memory_pressure_listener_unittest.cc"
  "memory/memory_pressure_monitor_unittest.cc"
  "memory/platform_shared_memory_region_unittest.cc"
  "memory/ptr_util_unittest.cc"
  "memory/ref_counted_memory_unittest.cc"
  "memory/ref_counted_unittest.cc"
  "memory/shared_memory_hooks_unittest.cc"
  "memory/shared_memory_mapping_unittest.cc"
  "memory/shared_memory_region_unittest.cc"
  "memory/singleton_unittest.cc"
  "memory/unsafe_shared_memory_pool_unittest.cc"
  "memory/weak_ptr_unittest.cc"
  "message_loop/message_pump_glib_unittest.cc"
  "message_loop/message_pump_unittest.cc"
  "message_loop/work_id_provider_unittest.cc"
  "metrics/bucket_ranges_unittest.cc"
  "metrics/crc32_unittest.cc"
  "metrics/field_trial_params_unittest.cc"
  "metrics/field_trial_unittest.cc"
  "metrics/histogram_base_unittest.cc"
  "metrics/histogram_delta_serialization_unittest.cc"
  "metrics/histogram_functions_unittest.cc"
  "metrics/histogram_macros_unittest.cc"
  "metrics/histogram_samples_unittest.cc"
  "metrics/histogram_snapshot_manager_unittest.cc"
  "metrics/metrics_hashes_unittest.cc"
  "metrics/persistent_histogram_allocator_unittest.cc"
  "metrics/persistent_histogram_storage_unittest.cc"
  "metrics/persistent_memory_allocator_unittest.cc"
  "metrics/persistent_sample_map_unittest.cc"
  "metrics/sample_map_unittest.cc"
  "metrics/sample_vector_unittest.cc"
  "metrics/single_sample_metrics_unittest.cc"
  "metrics/statistics_recorder_unittest.cc"
  "no_destructor_unittest.cc"
  "observer_list_threadsafe_unittest.cc"
  "observer_list_unittest.cc"
  "one_shot_event_unittest.cc"
  "optional_unittest.cc"
  "parameter_pack_unittest.cc"
  "path_service_unittest.cc"
  "pickle_unittest.cc"
  "power_monitor/power_monitor_device_source_unittest.cc"
  "power_monitor/power_monitor_unittest.cc"
  "process/environment_internal_unittest.cc"
  "process/memory_unittest.cc"
  "process/process_metrics_unittest.cc"
  "process/process_unittest.cc"
  "profiler/arm_cfi_table_unittest.cc"
  "profiler/metadata_recorder_unittest.cc"
  "profiler/sample_metadata_unittest.cc"
  "profiler/stack_copier_suspend_unittest.cc"
  "profiler/stack_copier_unittest.cc"
  "profiler/stack_sampler_impl_unittest.cc"
  "profiler/stack_sampling_profiler_unittest.cc"
  "rand_util_unittest.cc"
  "ranges/algorithm_unittest.cc"
  "ranges/functional_unittest.cc"
  "ranges/ranges_unittest.cc"
  "run_loop_unittest.cc"
  "safe_numerics_unittest.cc"
  "sampling_heap_profiler/lock_free_address_hash_set_unittest.cc"
  "scoped_clear_last_error_unittest.cc"
  "scoped_generic_unittest.cc"
  "scoped_multi_source_observation_unittest.cc"
  "scoped_observation_unittest.cc"
  "security_unittest.cc"
  "sequence_checker_unittest.cc"
  "sequence_token_unittest.cc"
  "sequenced_task_runner_unittest.cc"
  "stl_util_unittest.cc"
  "strings/abseil_string_conversions_unittest.cc"
  "strings/char_traits_unittest.cc"
  "strings/escape_unittest.cc"
  "strings/no_trigraphs_unittest.cc"
  "strings/nullable_string16_unittest.cc"
  "strings/pattern_unittest.cc"
  "strings/safe_sprintf_unittest.cc"
  "strings/strcat_unittest.cc"
  "strings/string_number_conversions_unittest.cc"
  "strings/string_piece_unittest.cc"
  "strings/string_split_unittest.cc"
  "strings/string_tokenizer_unittest.cc"
  "strings/string_util_unittest.cc"
  "strings/stringize_macros_unittest.cc"
  "strings/stringprintf_unittest.cc"
  "strings/sys_string_conversions_unittest.cc"
  "strings/utf_offset_string_conversions_unittest.cc"
  "strings/utf_string_conversions_unittest.cc"
  "supports_user_data_unittest.cc"
  "sync_socket_unittest.cc"
  "synchronization/atomic_flag_unittest.cc"
  "synchronization/condition_variable_unittest.cc"
  "synchronization/lock_unittest.cc"
  "synchronization/waitable_event_unittest.cc"
  "synchronization/waitable_event_watcher_unittest.cc"
  "sys_byteorder_unittest.cc"
  "system/sys_info_unittest.cc"
  "system/system_monitor_unittest.cc"
  "task/cancelable_task_tracker_unittest.cc"
  "task/common/checked_lock_unittest.cc"
  "task/common/operations_controller_unittest.cc"
  "task/common/task_annotator_unittest.cc"
  "task/lazy_thread_pool_task_runner_unittest.cc"
  "task/post_job_unittest.cc"
  "task/post_task_unittest.cc"
  "task/scoped_set_task_priority_for_current_thread_unittest.cc"
  "task/sequence_manager/atomic_flag_set_unittest.cc"
  "task/sequence_manager/lazily_deallocated_deque_unittest.cc"
  "task/sequence_manager/sequence_manager_impl_unittest.cc"
  "task/sequence_manager/task_queue_selector_unittest.cc"
  "task/sequence_manager/task_queue_unittest.cc"
  "task/sequence_manager/test/mock_time_message_pump_unittest.cc"
  "task/sequence_manager/thread_controller_power_monitor_unittest.cc"
  "task/sequence_manager/thread_controller_with_message_pump_impl_unittest.cc"
  "task/sequence_manager/time_domain_unittest.cc"
  "task/sequence_manager/work_deduplicator_unittest.cc"
  "task/sequence_manager/work_queue_sets_unittest.cc"
  "task/sequence_manager/work_queue_unittest.cc"
  "task/single_thread_task_executor_unittest.cc"
  "task/task_traits_extension_unittest.cc"
  "task/task_traits_unittest.cc"
  "task/thread_pool/delayed_task_manager_unittest.cc"
  "task/thread_pool/environment_config_unittest.cc"
  "task/thread_pool/job_task_source_unittest.cc"
  "task/thread_pool/priority_queue_unittest.cc"
  "task/thread_pool/sequence_unittest.cc"
  "task/thread_pool/service_thread_unittest.cc"
  "task/thread_pool/task_source_sort_key_unittest.cc"
  "task/thread_pool/task_tracker_unittest.cc"
  "task/thread_pool/thread_group_impl_unittest.cc"
  "task/thread_pool/thread_group_unittest.cc"
  "task/thread_pool/thread_pool_impl_unittest.cc"
  "task/thread_pool/tracked_ref_unittest.cc"
  "task/thread_pool/worker_thread_stack_unittest.cc"
  "task/thread_pool/worker_thread_unittest.cc"
  "task/thread_pool_unittest.cc"
  "task_runner_unittest.cc"
  "task_runner_util_unittest.cc"
  "template_util_unittest.cc"
  "test/gmock_callback_support_unittest.cc"
  "test/gmock_move_support_unittest.cc"
  "test/gtest_links_unittest.cc"
  "test/gtest_xml_unittest_result_printer_unittest.cc"
  "test/launcher/test_launcher_unittest.cc"
  "test/launcher/test_results_tracker_unittest.cc"
  "test/metrics/histogram_tester_unittest.cc"
  "test/metrics/user_action_tester_unittest.cc"
  "test/mock_callback_unittest.cc"
  "test/scoped_feature_list_unittest.cc"
  "test/scoped_logging_settings.h"
  "test/scoped_mock_clock_override_unittest.cc"
  "test/scoped_mock_time_message_loop_task_runner_unittest.cc"
  "test/test_mock_time_task_runner_unittest.cc"
  "test/test_pending_task_unittest.cc"
  "test/test_waitable_event_unittest.cc"
  "thread_annotations_unittest.cc"
  "threading/hang_watcher_unittest.cc"
  "threading/platform_thread_unittest.cc"
  "threading/post_task_and_reply_impl_unittest.cc"
  "threading/scoped_blocking_call_unittest.cc"
  "threading/scoped_thread_priority_unittest.cc"
  "threading/sequence_bound_unittest.cc"
  "threading/sequence_local_storage_map_unittest.cc"
  "threading/sequence_local_storage_slot_unittest.cc"
  "threading/sequenced_task_runner_handle_unittest.cc"
  "threading/simple_thread_unittest.cc"
  "threading/thread_checker_unittest.cc"
  "threading/thread_collision_warner_unittest.cc"
  "threading/thread_id_name_manager_unittest.cc"
  "threading/thread_local_storage_unittest.cc"
  "threading/thread_local_unittest.cc"
  "threading/thread_restrictions_unittest.cc"
  "threading/thread_task_runner_handle_unittest.cc"
  "threading/thread_unittest.cc"
  "threading/watchdog_unittest.cc"
  "time/pr_time_unittest.cc"
  "time/time_unittest.cc"
  "timer/elapsed_timer_unittest.cc"
  "timer/hi_res_timer_manager_unittest.cc"
  "timer/lap_timer_unittest.cc"
  "timer/mock_timer_unittest.cc"
  "timer/timer_unittest.cc"
  "token_unittest.cc"
  "tools_sanity_unittest.cc"
  "traits_bag_unittest.cc"
  "tuple_unittest.cc"
  "types/pass_key_unittest.cc"
  "types/strong_alias_unittest.cc"
  "unguessable_token_unittest.cc"
  "value_iterators_unittest.cc"
  "values_unittest.cc"
  "version_unittest.cc"
  "vlog_unittest.cc"
)
list(APPEND base_unittest_utils
  "allocator/partition_allocator/arm_bti_test_functions.h"
  "task/thread_pool/can_run_policy_test.h"
  "task/thread_pool/test_task_factory.cc"
  "task/thread_pool/test_task_factory.h"
  "task/thread_pool/test_utils.cc"
  "task/thread_pool/test_utils.h"
)

if(TARGET_WINDOWS)
  list(APPEND base_unittest_utils
    "win/dispatch_stub.cc"
    "win/dispatch_stub.h"
    "win/dllmain.cc"
  )
  list(APPEND base_unittests
    "debug/gdi_debug_util_win_unittest.cc"
    "file_version_info_win_unittest.cc"
    "process/launch_unittest_win.cc"
    "test/fake_iasync_operation_win_unittest.cc"
    "test/test_reg_util_win_unittest.cc"
    "threading/platform_thread_win_unittest.cc"
    "time/time_win_unittest.cc"
    "win/async_operation_unittest.cc"
    "win/com_init_balancer_unittest.cc"
    "win/com_init_check_hook_unittest.cc"
    "win/com_init_util_unittest.cc"
    "win/core_winrt_util_unittest.cc"
    "win/embedded_i18n/language_selector_unittest.cc"
    "win/enum_variant_unittest.cc"
    "win/event_trace_consumer_unittest.cc"
    "win/event_trace_controller_unittest.cc"
    "win/event_trace_provider_unittest.cc"
    "win/hstring_compare_unittest.cc"
    "win/hstring_reference_unittest.cc"
    "win/i18n_unittest.cc"
    "win/map_unittest.cc"
    "win/message_window_unittest.cc"
    "win/object_watcher_unittest.cc"
    "win/pe_image_reader_unittest.cc"
    "win/pe_image_unittest.cc"
    "win/post_async_results_unittest.cc"
    "win/reference_unittest.cc"
    "win/registry_unittest.cc"
    "win/scoped_bstr_unittest.cc"
    "win/scoped_handle_unittest.cc"
    "win/scoped_hstring_unittest.cc"
    "win/scoped_process_information_unittest.cc"
    "win/scoped_safearray_unittest.cc"
    "win/scoped_variant_unittest.cc"
    "win/scoped_winrt_initializer_unittest.cc"
    "win/shortcut_unittest.cc"
    "win/startup_information_unittest.cc"
    "win/variant_util_unittest.cc"
    "win/variant_vector_unittest.cc"
    "win/vector_unittest.cc"
    "win/win_includes_unittest.cc"
    "win/win_util_unittest.cc"
    "win/windows_version_unittest.cc"
    "win/winrt_storage_util_unittest.cc"
    "win/wmi_unittest.cc"
    "win/wrapped_window_proc_unittest.cc"
  )
  if (enable_cet_shadow_stack)
    list(APPEND base_unittests
      "win/cet_shadow_stack_unittest.cc"
    )
  endif()
endif()

if(TARGET_LINIX OR TARGET_CHROMEOS)
  list(APPEND base_unittests
    "debug/proc_maps_linux_unittest.cc"
  )
endif()

if(TARGET_MACOS)
  list(APPEND base_unittests
    "allocator/allocator_interception_mac_unittest.mm"
    "allocator/malloc_zone_functions_mac_unittest.cc"
    "enterprise_util_mac_unittest.mm"
    "mac/bind_objc_block_unittest.mm"
    "mac/call_with_eh_frame_unittest.mm"
    "mac/dispatch_source_mach_unittest.cc"
    "mac/foundation_util_unittest.mm"
    "mac/mac_util_unittest.mm"
    "mac/mach_o_unittest.cc"
    "mac/mach_port_rendezvous_unittest.cc"
    "mac/objc_release_properties_unittest.mm"
    "mac/scoped_mach_vm_unittest.cc"
    "mac/scoped_nsobject_unittest.mm"
    "mac/scoped_objc_class_swizzler_unittest.mm"
    "mac/scoped_sending_event_unittest.mm"
    "message_loop/message_pump_mac_unittest.mm"
    "power_monitor/thermal_state_observer_mac_unittest.mm"
    "process/launch_unittest_mac.cc"
    "process/memory_unittest_mac.h"
    "process/memory_unittest_mac.mm"
    "strings/sys_string_conversions_mac_unittest.mm"
  )
  list(APPEND base_unittests
    "message_loop/message_pump_kqueue_unittest.cc"
  )
endif()

if(TARGET_POSIX)
  list(APPEND base_unittests
    "files/dir_reader_posix_unittest.cc"
    "files/file_descriptor_watcher_posix_unittest.cc"
    "memory/madv_free_discardable_memory_allocator_posix_unittest.cc"
    "memory/madv_free_discardable_memory_posix_unittest.cc"
    "message_loop/fd_watch_controller_posix_unittest.cc"
    "posix/file_descriptor_shuffle_unittest.cc"
    "posix/unix_domain_socket_unittest.cc"
    "task/thread_pool/task_tracker_posix_unittest.cc"
  )
  if(NOT USE_NACL AND NOT TARGET_APPLE)
    list(APPEND base_unittests
      "files/dir_reader_posix_unittest.cc"
      "cpu_affinity_posix_unittest.cc"
      "profiler/stack_copier_signal_unittest.cc"
      "profiler/thread_delegate_posix_unittest.cc"
    )
  endif()
endif()

if(TARGET_ANDROID)
  if(can_unwind_with_cfi_table)
    list(APPEND base_unittests
      "trace_event/cfi_backtrace_android_unittest.cc"
    )
  endif()
  if(TARGET_ARM)
    list(APPEND base_unittests
      "profiler/chrome_unwinder_android_unittest.cc"
    )
  endif()
  if(NOT exclude_unwind_tables AND (TARGET_ARM OR TARGET_ARM64))
    list(APPEND base_unittests
      "profiler/native_unwinder_android_unittest.cc"
    )
  endif()
  list(APPEND base_unittests
    "android/android_image_reader_compat_unittest.cc"
    "android/application_status_listener_unittest.cc"
    "android/child_process_unittest.cc"
    "android/content_uri_utils_unittest.cc"
    "android/java_handler_thread_unittest.cc"
    "android/jni_android_unittest.cc"
    "android/jni_array_unittest.cc"
    "android/jni_string_unittest.cc"
    "android/library_loader/library_prefetcher_unittest.cc"
    "android/linker/modern_linker_unittest.cc"
    "android/path_utils_unittest.cc"
    "android/reached_addresses_bitset_unittest.cc"
    "android/scoped_java_ref_unittest.cc"
    "android/sys_utils_unittest.cc"
    "android/unguessable_token_android_unittest.cc"
    "os_compat_android_unittest.cc"
  )
  list(APPEND base_unittest_utils
    "android/linker/linker_jni.cc"
    "android/linker/linker_jni.h"
    "android/linker/modern_linker_jni.cc"
    "android/linker/modern_linker_jni.h"
  )
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${base_unittests}
    OUTPUT base_unittests
    ITEMS
    "process/process_unittest.cc"
    "process/process_util_unittest.cc"
    "test/gtest_links_unittest.cc"
    "test/gtest_xml_unittest_result_printer_unittest.cc"
    "test/launcher/test_launcher_unittest.cc"
    "test/launcher/test_results_tracker_unittest.cc"
  )
endif(TARGET_ANDROID)

if(TARGET_IOS)
  list(APPEND base_unittests
    "ios/device_util_unittest.mm"
    "ios/weak_nsobject_unittest.mm"
    "message_loop/message_pump_io_ios_unittest.cc"
  )
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${base_unittests}
    OUTPUT base_unittests
    ITEMS
    "files/file_path_watcher_unittest.cc"
    "memory/discardable_shared_memory_unittest.cc"
    "process/memory_unittest.cc"
    "process/process_unittest.cc"
    "process/process_util_unittest.cc"
    "sync_socket_unittest.cc"
    "synchronization/waitable_event_watcher_unittest.cc"
    "test/gtest_links_unittest.cc"
    "test/gtest_xml_unittest_result_printer_unittest.cc"
    "test/launcher/test_launcher_unittest.cc"
    "test/launcher/test_results_tracker_unittest.cc"
  )
  list(APPEND base_unittests
    # Pull in specific Mac files for iOS.
    "mac/bind_objc_block_unittest.mm"
    "mac/foundation_util_unittest.mm"
    "mac/objc_release_properties_unittest.mm"
    "mac/scoped_nsobject_unittest.mm"
    "strings/sys_string_conversions_mac_unittest.mm"
  )
  # The immediate crash tests require shared libraries, which we don't
  # support loading on iOS.
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${base_unittests}
    OUTPUT base_unittests
    ITEMS
    "immediate_crash_unittest.cc"
  )
  if(USE_ALLOC_SHIM)
    list(APPEND base_unittests
      "allocator/allocator_interception_mac_unittest.mm"
      "allocator/malloc_zone_functions_mac_unittest.cc"
    )
  endif(USE_ALLOC_SHIM)
endif(TARGET_IOS)

if(BASE_USE_PARTITION_ALLOCATOR)
  list(APPEND base_unittests
    "allocator/partition_allocator/address_pool_manager_unittest.cc"
    "allocator/partition_allocator/address_space_randomization_unittest.cc"
    "allocator/partition_allocator/memory_reclaimer_unittest.cc"
    "allocator/partition_allocator/object_bitmap_unittest.cc"
    "allocator/partition_allocator/page_allocator_unittest.cc"
    "allocator/partition_allocator/partition_alloc_unittest.cc"
    "allocator/partition_allocator/partition_lock_unittest.cc"
    "allocator/partition_allocator/pcscan_unittest.cc"
    "allocator/partition_allocator/thread_cache_unittest.cc"
  )
endif(BASE_USE_PARTITION_ALLOCATOR)

if(TARGET_LINUX OR TARGET_FUCHSIA OR TARGET_CHROMEOS)
  # TODO: error: use of undeclared identifier 'MALLOC_WRAPPER_LIB'
  #list(APPEND base_unittest_utils
  #  "debug/test_elf_image_builder.cc"
  #  "debug/test_elf_image_builder.h"
  #)
  #list(APPEND base_unittests
  #  "debug/elf_reader_unittest.cc"
  #)
  if(TARGET_LINUX OR is_chromeos_lacros)
    list(APPEND base_unittests
      "linux_util_unittest.cc"
      "nix/xdg_util_unittest.cc"
    )
  endif()
endif()

if(NOT use_glib)
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${base_unittests}
    OUTPUT base_unittests
    ITEMS
    "message_loop/message_pump_glib_unittest.cc"
  )
endif(NOT use_glib)

if(USE_LIBEVENT)
  list(APPEND base_unittests
    "message_loop/message_pump_libevent_unittest.cc"
  )
endif()

if(TARGET_FUCHSIA)
  list(APPEND base_unittest_utils
    "fuchsia/service_directory_test_base.cc"
    "fuchsia/service_directory_test_base.h"
  )
  list(APPEND base_unittests
    "files/dir_reader_posix_unittest.cc"
    "files/file_descriptor_watcher_posix_unittest.cc"
    "fuchsia/file_utils_unittest.cc"
    "fuchsia/filtered_service_directory_unittest.cc"
    "fuchsia/intl_profile_watcher_unittest.cc"
    "fuchsia/scoped_service_binding_unittest.cc"
    "fuchsia/scoped_service_publisher_unittest.cc"
    "fuchsia/service_provider_impl_unittest.cc"
    "fuchsia/test_component_context_for_process_unittest.cc"
    "fuchsia/time_zone_data_unittest.cc"
    "message_loop/fd_watch_controller_posix_unittest.cc"
    "posix/file_descriptor_shuffle_unittest.cc"
    "task/thread_pool/task_tracker_posix_unittest.cc"
  )
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${base_unittests}
    OUTPUT base_unittests
    ITEMS
     "files/file_path_watcher_unittest.cc"
  )
endif()

if(NOT TARGET_FUCHSIA AND NOT TARGET_IOS)
  list(APPEND base_unittests
    "files/file_locking_unittest.cc"
  )
endif()

if(TARGET_ANDROID)
  list(APPEND base_unittest_utils
    "debug/test_elf_image_builder.cc"
    "debug/test_elf_image_builder.h"
  )
  list(APPEND base_unittests
    "debug/elf_reader_unittest.cc"
    "debug/proc_maps_linux_unittest.cc"
  )
endif()

if(TARGET_WINDOWS)
  if(TARGET_X86_64 OR TARGET_ARM64)
    list(APPEND base_unittests
      "profiler/win32_stack_frame_unwinder_unittest.cc"
    )
  endif()
  list(APPEND base_unittests
    "files/os_validation_win_unittest.cc"
  )
endif(TARGET_WINDOWS)

if(USE_ALLOC_SHIM)
  list(APPEND base_unittests
    "allocator/allocator_shim_unittest.cc"
    "sampling_heap_profiler/sampling_heap_profiler_unittest.cc"
  )
  if(TARGET_WINDOWS)
    list(APPEND base_unittests
      "allocator/winheap_stubs_win_unittest.cc"
    )
  endif(TARGET_WINDOWS)
endif(USE_ALLOC_SHIM)

if(ENABLE_BASE_TRACING)
  list(APPEND base_unittest_utils
    "trace_event/trace_event_filter_test_utils.cc"
    "trace_event/trace_event_filter_test_utils.h"
  )
  # TODO undefined reference to `perfetto::internal::DebugAnnotationToString
  # because chromium includes `component("perfetto_test_support")` directly from subproject `third_party/perfetto/BUILD.gn`.
  # "trace_event/traced_value_support_unittest.cc"
  #
  # TODO: CRASHES "trace_event/typed_macros_unittest.cc"
  #
  list(APPEND base_unittests
    "test/trace_event_analyzer_unittest.cc"
    "trace_event/blame_context_unittest.cc"
    "trace_event/event_name_filter_unittest.cc"
    "trace_event/heap_profiler_allocation_context_tracker_unittest.cc"
    "trace_event/memory_allocator_dump_unittest.cc"
    "trace_event/memory_dump_manager_unittest.cc"
    "trace_event/memory_dump_scheduler_unittest.cc"
    "trace_event/memory_infra_background_allowlist_unittest.cc"
    "trace_event/memory_usage_estimator_unittest.cc"
    "trace_event/process_memory_dump_unittest.cc"
    "trace_event/trace_arguments_unittest.cc"
    "trace_event/trace_category_unittest.cc"
    "trace_event/trace_config_unittest.cc"
    "trace_event/trace_conversion_helper_unittest.cc"
    "trace_event/trace_event_unittest.cc"
    "trace_event/traced_value_unittest.cc"
  )
  if(TARGET_ANDROID)
    list(APPEND base_unittests
      "trace_event/cpufreq_monitor_android_unittest.cc"
      "trace_event/java_heap_dump_provider_android_unittest.cc"
      "trace_event/trace_event_android_unittest.cc"
    )
  endif(TARGET_ANDROID)
endif(ENABLE_BASE_TRACING)

list(APPEND base_unittests
  util/values/values_util_unittest.cc
  util/type_safety/id_type_unittest.cc
  util/type_safety/token_type_unittest.cc
  util/timer/wall_clock_timer_unittest.cc
  util/memory_pressure/memory_pressure_voter_unittest.cc
  util/memory_pressure/multi_source_memory_pressure_monitor_unittest.cc
)

if(TARGET_WINDOWS)
  list(APPEND base_unittests
    util/memory_pressure/system_memory_pressure_evaluator_win_unittest.cc
  )
endif(TARGET_WINDOWS)

if(TARGET_MACOS)
  list(APPEND base_unittests
    util/memory_pressure/system_memory_pressure_evaluator_mac_unittest.cc
  )
endif(TARGET_MACOS)

if(TARGET_FUCHSIA)
  list(APPEND base_unittests
    util/memory_pressure/system_memory_pressure_evaluator_fuchsia_unittest.cc
  )
endif(TARGET_FUCHSIA)

if(TARGET_LINUX OR TARGET_CHROMEOS_LACROS)
  list(APPEND base_unittests
    util/memory_pressure/system_memory_pressure_evaluator_linux_unittest.cc
  )
endif(TARGET_LINUX OR TARGET_CHROMEOS_LACROS)

list(APPEND base_unittest_utils
  util/memory_pressure/fake_memory_pressure_monitor.cc
  util/memory_pressure/fake_memory_pressure_monitor.h
)

list(REMOVE_DUPLICATES base_unittests)
list(TRANSFORM base_unittests PREPEND ${BASE_SOURCES_PATH})

list(REMOVE_DUPLICATES base_unittest_utils)
list(FILTER base_unittest_utils EXCLUDE REGEX ".*_unittest.cc$")
list(TRANSFORM base_unittest_utils PREPEND ${BASE_SOURCES_PATH})

foreach(FILEPATH ${base_unittests})
  set(test_sources
    "${FILEPATH}"
    ${base_unittest_utils}
  )
  list(REMOVE_DUPLICATES base_unittest_utils)
  get_filename_component(FILENAME_WITHOUT_EXT ${FILEPATH} NAME_WE)
  chromium_base_test_gtest(${ROOT_PROJECT_NAME}-base-${FILENAME_WITHOUT_EXT}
    "${test_sources}")
endforeach()

list(APPEND extensions_unittests
  crc32_unittest.cc
  output_parameter_unittest.cc
  stl_util_unittest.cc
  type_id_unittest.cc
)

list(APPEND extensions_unittests
  debug/leak_tracker_unittest.cc
)

list(APPEND extensions_unittests
  containers/bounded_inline_vector_unittest.cc
  containers/unique_any_unittest.cc
  containers/any_internal_unittest.cc
  containers/prioritized_job_dispatcher_unittest.cc
  containers/prioritized_list_unittest.cc
  containers/prioritized_repeating_task_list_unittest.cc
  containers/sparse_byte_set_unittest.cc
  containers/indexed_mem_pool_unittest.cc
  containers/flat_combining_priority_queue_unittest.cc
  containers/mpmc_queue_unittest.cc
)

list(APPEND extensions_unittests
  synchronization/futex_unittest.cc
  synchronization/parking_lot_unittest.cc
  synchronization/flat_combining_unittest.cc
  synchronization/saturating_semaphore_unittest.cc
  synchronization/memory_idler_unittest.cc
  synchronization/atomic_util_unittest.cc
  synchronization/spin_lock_unittest.cc
  synchronization/baton_unittest.cc
)

list(APPEND extensions_unittests
  state_machine/state_machine_unittest.cc
)

list(APPEND extensions_unittests
  decimal/decimal_unittest.cc
  decimal/fixed_point_unittest.cc
)

list(APPEND extensions_unittests
  hash/city_hash_unittest.cc
  hash/farmhash_unittest.cc
  hash/murmurhash_unittest.cc
  hash/xxhash_unittest.cc
  hash/twang_hash_unittest.cc
  hash/jenkins_hash_unittest.cc
  hash/spooky_hash_v2_unittest.cc
  hash/hash_combine_unittest.cc
)

list(APPEND extensions_unittests
  ranges/enumerated_unittest.cc
  ranges/pipelined_unittest.cc
)

list(APPEND extensions_unittests
  interval/interval_map_unittest.cc
  interval/interval_set_unittest.cc
  interval/interval_unittest.cc
)

list(APPEND extensions_unittests
  jsonb/jsonb_unittest.cc
)

list(APPEND extensions_unittests
  lru/lru_cache_unittest.cc
  lru/lru_unittest.cc
)

list(APPEND extensions_unittests
  fail_point/fail_point_unittest.cc
)

list(APPEND extensions_unittests
  plug_point/plug_point_unittest.cc
)

list(APPEND extensions_unittests
  race_sync_point/race_sync_point_unittest.cc
)

list(APPEND extensions_unittests
  token_bucket/token_bucket_unittest.cc
)

list(APPEND extensions_unittests
  statistics/usage_limiter_unittest.cc
  statistics/weighted_moving_average_unittest.cc
  statistics/expandable_statistics_window_unittest.cc
  statistics/percentile_filter_unittest.cc
  statistics/moving_median_filter_unittest.cc
  statistics/moving_statistics_window_unittest.cc
  statistics/weighted_moving_linear_regression_unittest.cc
  statistics/quality_threshold_unittest.cc
  statistics/rate_tracker_unittest.cc
  statistics/moving_average_unittest.cc
  statistics/hdr_histogram_unittest.cc
)

list(APPEND extensions_unittests
  prometheus_metrics/metrics_unittest.cc
)

list(APPEND extensions_unittests
  promise/promise_unittest.cc
  promise/promise_value_unittest.cc
  promise/helpers_unittest.cc
  promise/abstract_promise_unittest.cc
  promise/post_task_executor_unittest.cc
  promise/dependent_list_unittest.cc
)

list(APPEND extensions_unittests
  dependency_hierarchy/dependency_hierarchy_unittest.cc
  dependency_hierarchy/dependency_util_unittest.cc
)

list(APPEND extensions_unittests
  disjoint_sets/disjoint_sets_unittest.cc
)

list(APPEND extensions_unittests
  memory/wrap_unique_ptr_not_array_unittest.cc
  memory/unowned_ptr_unittest.cc
  memory/unowned_ref_unittest.cc
  memory/padded_unittest.cc
  memory/not_null_unittest.cc
  memory/arena_unittest.cc
)

list(APPEND extensions_unittests
  multiconfig/multiconfig_unittest.cc
)

list(APPEND extensions_unittests
  json/json_serializers_unittest.cc
)

list(APPEND extensions_unittests
  types_bucket/types_bucket_unittest.cc
  types_bucket/thread_local_types_bucket_unittest.cc
)

list(APPEND extensions_unittests
  static_sequence/static_sequence_unittest.cc
)

list(APPEND extensions_unittests
  time/backoff_timer_unittest.cc
  time/system_time_change_notifier_unittest.cc
  time/time_macros_unittest.cc
)

list(APPEND extensions_unittests
  strong_types/strong_checked_math_unittest.cc
  strong_types/strong_alias_unittest.cc
  strong_types/strong_bool_unittest.cc
  strong_types/strong_checked_math_unittest.cc
  strong_types/strong_int_unittest.cc
  strong_types/strong_double_unittest.cc
  strong_types/strong_string_unittest.cc
  strong_types/money/money_unittest.cc
)

list(APPEND extensions_unittests
  log/spacer_unittest.cc
  log/table_printer_unittest.cc
)

list(APPEND extensions_unittests
  status/status_macros_unittest.cc
  status/status_unittest.cc
  status/statusor_unittest.cc
  status/with_details_unittest.cc
)

list(APPEND extensions_unittests
  core/weak_handle_unittest.cc
  core/observable_unittest.cc
  core/typed_enum_unittest.cc
  core/move_wrapper_unittest.cc
  core/memory_unittest.cc
)

list(APPEND extensions_unittests
  varint/memcmpable_varint_unittest.cc
  varint/fast_varint_unittest.cc
)

list(APPEND extensions_unittests
  strings/string_number_conversions_unittest.cc
  strings/substitute_unittest.cc
  strings/string_util_unittest.cc
  strings/string_format_unittest.cc
  strings/fixed_string_unittest.cc
)

list(APPEND extensions_unittests
  annotations/guard_annotations_unittest.cc
)

list(APPEND extensions_unittests
  numerics/double_summation_unittest.cc
  numerics/floating_point_comparison_unittest.cc
  numerics/pack_numbers_unittest.cc
  numerics/uint128_unittest.cc
  numerics/uint256_unittest.cc
)

list(APPEND extensions_unittests
  test/test_macros_unittest.cc
  test/deterministic_schedule_unittest.cc
  test/semaphore_unittest.cc
  test/barrier_unittest.cc
)

list(APPEND extensions_unittests
  algorithm/top_n_unittest.cc
)

list(APPEND extensions_unittests
  bit_field/bit_field_unittest.cc
)

list(APPEND extensions_unittests
  bind/bind_to_task_runner_unittest.cc
)

list(APPEND extensions_unittests
  backoff_entry/backoff_entry_serializer_unittest.cc
  backoff_entry/backoff_entry_unittest.cc
)

list(APPEND extensions_unittests
  concurrency/concurrent_int64_unittest.cc
  concurrency/lock_free_producer_consumer_queue_unittest.cc
)

list(APPEND extensions_unittests
  bloom_filter/bloom_unittest.cc
  bloom_filter/counting_bloom_unittest.cc
  bloom_filter/double_hashing_bloom_unittest.cc
)

list(TRANSFORM extensions_unittests PREPEND "../extensions/basic/")

list(REMOVE_DUPLICATES extensions_unittests)
list(TRANSFORM extensions_unittests PREPEND ${BASE_SOURCES_PATH})

foreach(FILEPATH ${extensions_unittests})
  set(test_sources
    "${FILEPATH}"
    ${base_unittest_utils}
  )
  get_filename_component(FILENAME_WITHOUT_EXT ${FILEPATH} NAME_WE)
  chromium_base_test_gtest(${ROOT_PROJECT_NAME}-basic-${FILENAME_WITHOUT_EXT}
    "${test_sources}")
endforeach()
