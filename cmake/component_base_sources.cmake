﻿# see component("base") in BUILD.gn
list(APPEND COMPONENT_BASE_SOURCES_UNPROCESSED
  "allocator/allocator_check.cc"
  "allocator/allocator_check.h"
  "allocator/allocator_extension.cc"
  "allocator/allocator_extension.h"
  "at_exit.cc"
  "at_exit.h"
  "atomic_ref_count.h"
  "atomic_sequence_num.h"
  "atomicops.h"
  "atomicops_internals_atomicword_compat.h"
  "atomicops_internals_portable.h"
  "atomicops_internals_x86_msvc.h"
  "auto_reset.h"
  "barrier_closure.cc"
  "barrier_closure.h"
  "base64.cc"
  "base64.h"
  "base64url.cc"
  "base64url.h"
  "base_export.h"
  "base_switches.h"
  "big_endian.cc"
  "big_endian.h"
  "bind.h"
  "bind_internal.h"
  "bind_post_task.h"
  "bind_post_task_internal.h"
  "bit_cast.h"
  "bits.h"
  "build_time.cc"
  "build_time.h"
  "callback.h"
  "callback_forward.h"
  "callback_helpers.cc"
  "callback_helpers.h"
  "callback_internal.cc"
  "callback_internal.h"
  "callback_list.cc"
  "callback_list.h"
  "cancelable_callback.h"
  "check.cc"
  "check.h"
  "check_op.cc"
  "check_op.h"
  "command_line.cc"
  "command_line.h"
  "compiler_specific.h"
  "component_export.h"
  "containers/adapters.h"
  "containers/buffer_iterator.h"
  "containers/checked_iterators.h"
  "containers/checked_range.h"
  "containers/circular_deque.h"
  "containers/contains.h"
  "containers/contiguous_iterator.h"
  "containers/fixed_flat_map.h"
  "containers/fixed_flat_set.h"
  "containers/flat_map.h"
  "containers/flat_set.h"
  "containers/flat_tree.cc"
  "containers/flat_tree.h"
  "containers/id_map.h"
  "containers/intrusive_heap.cc"
  "containers/intrusive_heap.h"
  "containers/linked_list.cc"
  "containers/linked_list.h"
  "containers/mru_cache.h"
  "containers/small_map.h"
  "containers/span.h"
  "containers/stack.h"
  "containers/stack_container.h"
  "containers/unique_ptr_adapters.h"
  "containers/util.h"
  "containers/vector_buffer.h"
  "cpu.cc"
  "cpu.h"
  "critical_closure.h"
  "dcheck_is_on.h"
  "debug/activity_analyzer.cc"
  "debug/activity_analyzer.h"
  "debug/activity_tracker.cc"
  "debug/activity_tracker.h"
  "debug/alias.cc"
  "debug/alias.h"
  "debug/asan_invalid_access.cc"
  "debug/asan_invalid_access.h"
  "debug/crash_logging.cc"
  "debug/crash_logging.h"
  "debug/debugger.cc"
  "debug/debugger.h"
  "debug/dump_without_crashing.cc"
  "debug/dump_without_crashing.h"
  "debug/leak_annotations.h"
  "debug/profiler.cc"
  "debug/profiler.h"
  "debug/stack_trace.cc"
  "debug/stack_trace.h"
  "debug/task_trace.cc"
  "debug/task_trace.h"
  "deferred_sequenced_task_runner.cc"
  "deferred_sequenced_task_runner.h"
  "enterprise_util.h"
  "environment.cc"
  "environment.h"
  "export_template.h"
  "feature_list.cc"
  "feature_list.h"
  "file_descriptor_store.cc"
  "file_descriptor_store.h"
  "file_version_info.h"
  "files/dir_reader_fallback.h"
  "files/file.cc"
  "files/file.h"
  "files/file_enumerator.cc"
  "files/file_enumerator.h"
  "files/file_path.cc"
  "files/file_path.h"
  "files/file_path_constants.cc"
  "files/file_path_watcher.cc"
  "files/file_path_watcher.h"
  "files/file_proxy.cc"
  "files/file_proxy.h"
  "files/file_tracing.cc"
  "files/file_tracing.h"
  "files/file_util.cc"
  "files/file_util.h"
  "files/important_file_writer.cc"
  "files/important_file_writer.h"
  "files/important_file_writer_cleaner.cc"
  "files/important_file_writer_cleaner.h"
  "files/memory_mapped_file.cc"
  "files/memory_mapped_file.h"
  "files/platform_file.h"
  "files/scoped_file.cc"
  "files/scoped_file.h"
  "files/scoped_temp_dir.cc"
  "files/scoped_temp_dir.h"
  "format_macros.h"
  "functional/identity.h"
  "functional/invoke.h"
  "functional/not_fn.h"
  "gtest_prod_util.h"
  "guid.cc"
  "guid.h"
  "hash/hash.cc"
  "hash/hash.h"
  "hash/legacy_hash.cc"
  "hash/legacy_hash.h"
  "immediate_crash.h"
  "json/json_common.h"
  "json/json_file_value_serializer.cc"
  "json/json_file_value_serializer.h"
  "json/json_parser.cc"
  "json/json_parser.h"
  "json/json_reader.cc"
  "json/json_reader.h"
  "json/json_string_value_serializer.cc"
  "json/json_string_value_serializer.h"
  "json/json_value_converter.cc"
  "json/json_value_converter.h"
  "json/json_writer.cc"
  "json/json_writer.h"
  "json/string_escape.cc"
  "json/string_escape.h"
  "lazy_instance.h"
  "lazy_instance_helpers.cc"
  "lazy_instance_helpers.h"
  "linux_util.cc"
  "linux_util.h"
  "location.cc"
  "location.h"
  "logging.cc"
  "logging.h"
  "macros.h"
  "memory/aligned_memory.cc"
  "memory/aligned_memory.h"
  "memory/checked_ptr.cc"
  "memory/checked_ptr.h"
  "memory/discardable_memory.cc"
  "memory/discardable_memory.h"
  "memory/discardable_memory_allocator.cc"
  "memory/discardable_memory_allocator.h"
  "memory/discardable_memory_internal.h"
  "memory/discardable_shared_memory.cc"
  "memory/discardable_shared_memory.h"
  "memory/free_deleter.h"
  "memory/memory_pressure_listener.cc"
  "memory/memory_pressure_listener.h"
  "memory/memory_pressure_monitor.cc"
  "memory/memory_pressure_monitor.h"
  "memory/platform_shared_memory_region.cc"
  "memory/platform_shared_memory_region.h"
  "memory/ptr_util.h"
  "memory/raw_scoped_refptr_mismatch_checker.h"
  "memory/read_only_shared_memory_region.cc"
  "memory/read_only_shared_memory_region.h"
  "memory/ref_counted.cc"
  "memory/ref_counted.h"
  "memory/ref_counted_delete_on_sequence.h"
  "memory/ref_counted_memory.cc"
  "memory/ref_counted_memory.h"
  "memory/scoped_policy.h"
  "memory/scoped_refptr.h"
  "memory/shared_memory_hooks.h"
  "memory/shared_memory_mapping.cc"
  "memory/shared_memory_mapping.h"
  "memory/shared_memory_security_policy.cc"
  "memory/shared_memory_security_policy.h"
  "memory/shared_memory_tracker.cc"
  "memory/shared_memory_tracker.h"
  "memory/singleton.h"
  "memory/tagging.cc"
  "memory/tagging.h"
  "memory/unsafe_shared_memory_pool.cc"
  "memory/unsafe_shared_memory_pool.h"
  "memory/unsafe_shared_memory_region.cc"
  "memory/unsafe_shared_memory_region.h"
  "memory/weak_ptr.cc"
  "memory/weak_ptr.h"
  "memory/writable_shared_memory_region.cc"
  "memory/writable_shared_memory_region.h"
  "message_loop/message_pump.cc"
  "message_loop/message_pump.h"
  "message_loop/message_pump_default.cc"
  "message_loop/message_pump_default.h"
  "message_loop/message_pump_for_io.h"
  "message_loop/message_pump_for_ui.h"
  "message_loop/message_pump_glib.cc"
  "message_loop/message_pump_glib.h"
  "message_loop/message_pump_type.h"
  "message_loop/timer_slack.h"
  "message_loop/work_id_provider.cc"
  "message_loop/work_id_provider.h"
  "metrics/bucket_ranges.cc"
  "metrics/bucket_ranges.h"
  "metrics/crc32.cc"
  "metrics/crc32.h"
  "metrics/dummy_histogram.cc"
  "metrics/dummy_histogram.h"
  "metrics/field_trial.cc"
  "metrics/field_trial.h"
  "metrics/field_trial_param_associator.cc"
  "metrics/field_trial_param_associator.h"
  "metrics/field_trial_params.cc"
  "metrics/field_trial_params.h"
  "metrics/histogram.cc"
  "metrics/histogram.h"
  "metrics/histogram_base.cc"
  "metrics/histogram_base.h"
  "metrics/histogram_delta_serialization.cc"
  "metrics/histogram_delta_serialization.h"
  "metrics/histogram_flattener.h"
  "metrics/histogram_functions.cc"
  "metrics/histogram_functions.h"
  "metrics/histogram_macros.h"
  "metrics/histogram_macros_internal.h"
  "metrics/histogram_macros_local.h"
  "metrics/histogram_samples.cc"
  "metrics/histogram_samples.h"
  "metrics/histogram_snapshot_manager.cc"
  "metrics/histogram_snapshot_manager.h"
  "metrics/metrics_hashes.cc"
  "metrics/metrics_hashes.h"
  "metrics/persistent_histogram_allocator.cc"
  "metrics/persistent_histogram_allocator.h"
  "metrics/persistent_memory_allocator.cc"
  "metrics/persistent_memory_allocator.h"
  "metrics/persistent_sample_map.cc"
  "metrics/persistent_sample_map.h"
  "metrics/record_histogram_checker.h"
  "metrics/sample_map.cc"
  "metrics/sample_map.h"
  "metrics/sample_vector.cc"
  "metrics/sample_vector.h"
  "metrics/single_sample_metrics.cc"
  "metrics/single_sample_metrics.h"
  "metrics/sparse_histogram.cc"
  "metrics/sparse_histogram.h"
  "metrics/statistics_recorder.cc"
  "metrics/statistics_recorder.h"
  "metrics/user_metrics.cc"
  "metrics/user_metrics.h"
  "metrics/user_metrics_action.h"
  "native_library.cc"
  "native_library.h"
  "no_destructor.h"
  "notreached.cc"
  "notreached.h"
  "observer_list.h"
  "observer_list_internal.cc"
  "observer_list_internal.h"
  "observer_list_threadsafe.cc"
  "observer_list_threadsafe.h"
  "observer_list_types.cc"
  "observer_list_types.h"
  "one_shot_event.cc"
  "one_shot_event.h"
  "optional.h"
  "os_compat_nacl.cc"
  "os_compat_nacl.h"
  "parameter_pack.h"
  "path_service.cc"
  "path_service.h"
  "pending_task.cc"
  "pending_task.h"
  "pickle.cc"
  "pickle.h"
  "post_task_and_reply_with_result_internal.h"
  "power_monitor/power_monitor.cc"
  "power_monitor/power_monitor.h"
  "power_monitor/power_monitor_device_source.cc"
  "power_monitor/power_monitor_device_source.h"
  "power_monitor/power_monitor_source.cc"
  "power_monitor/power_monitor_source.h"
  "power_monitor/power_observer.h"
  "process/environment_internal.cc"
  "process/environment_internal.h"
  "process/kill.cc"
  "process/kill.h"
  "process/launch.cc"
  "process/launch.h"
  "process/memory.cc"
  "process/memory.h"
  "process/process.h"
  "process/process_handle.cc"
  "process/process_handle.h"
  "process/process_info.h"
  "process/process_iterator.cc"
  "process/process_iterator.h"
  "process/process_metrics.cc"
  "process/process_metrics.h"
  "profiler/arm_cfi_table.cc"
  "profiler/arm_cfi_table.h"
  "profiler/frame.cc"
  "profiler/frame.h"
  "profiler/metadata_recorder.cc"
  "profiler/metadata_recorder.h"
  "profiler/module_cache.cc"
  "profiler/module_cache.h"
  "profiler/native_unwinder.h"
  "profiler/profile_builder.h"
  "profiler/register_context.h"
  "profiler/sample_metadata.cc"
  "profiler/sample_metadata.h"
  "profiler/sampling_profiler_thread_token.cc"
  "profiler/sampling_profiler_thread_token.h"
  "profiler/stack_buffer.cc"
  "profiler/stack_buffer.h"
  "profiler/stack_copier.cc"
  "profiler/stack_copier.h"
  "profiler/stack_copier_suspend.cc"
  "profiler/stack_copier_suspend.h"
  "profiler/stack_sampler.cc"
  "profiler/stack_sampler.h"
  "profiler/stack_sampler_impl.cc"
  "profiler/stack_sampler_impl.h"
  "profiler/stack_sampling_profiler.cc"
  "profiler/stack_sampling_profiler.h"
  "profiler/suspendable_thread_delegate.h"
  "profiler/thread_delegate.h"
  "profiler/unwinder.cc"
  "profiler/unwinder.h"
  "rand_util.cc"
  "rand_util.h"
  "rand_util_nacl.cc"
  "ranges/algorithm.h"
  "ranges/functional.h"
  "ranges/ranges.h"
  "run_loop.cc"
  "run_loop.h"
  "sampling_heap_profiler/lock_free_address_hash_set.cc"
  "sampling_heap_profiler/lock_free_address_hash_set.h"
  "sampling_heap_profiler/poisson_allocation_sampler.cc"
  "sampling_heap_profiler/poisson_allocation_sampler.h"
  "sampling_heap_profiler/sampling_heap_profiler.cc"
  "sampling_heap_profiler/sampling_heap_profiler.h"
  "scoped_clear_last_error.h"
  "scoped_generic.h"
  "scoped_multi_source_observation.h"
  "scoped_native_library.cc"
  "scoped_native_library.h"
  "scoped_observation.h"
  "scoped_observer.h"
  "sequence_checker.h"
  "sequence_checker_impl.cc"
  "sequence_checker_impl.h"
  "sequence_token.cc"
  "sequence_token.h"
  "sequenced_task_runner.cc"
  "sequenced_task_runner.h"
  "sequenced_task_runner_helpers.h"
  "single_thread_task_runner.h"
  "stl_util.h"
  "strings/abseil_string_conversions.cc"
  "strings/abseil_string_conversions.h"
  "strings/char_traits.h"
  "strings/escape.cc"
  "strings/escape.h"
  "strings/latin1_string_conversions.cc"
  "strings/latin1_string_conversions.h"
  "strings/nullable_string16.cc"
  "strings/nullable_string16.h"
  "strings/pattern.cc"
  "strings/pattern.h"
  "strings/safe_sprintf.cc"
  "strings/safe_sprintf.h"
  "strings/strcat.cc"
  "strings/strcat.h"
  "strings/strcat_internal.h"
  "strings/string16.h"
  "strings/string_number_conversions.cc"
  "strings/string_number_conversions.h"
  "strings/string_number_conversions_internal.h"
  "strings/string_piece.cc"
  "strings/string_piece.h"
  "strings/string_piece_forward.h"
  "strings/string_split.cc"
  "strings/string_split.h"
  "strings/string_split_internal.h"
  "strings/string_tokenizer.h"
  "strings/string_util.cc"
  "strings/string_util.h"
  "strings/string_util_constants.cc"
  "strings/string_util_internal.h"
  "strings/stringize_macros.h"
  "strings/stringprintf.cc"
  "strings/stringprintf.h"
  "strings/sys_string_conversions.h"
  "strings/utf_offset_string_conversions.cc"
  "strings/utf_offset_string_conversions.h"
  "strings/utf_string_conversion_utils.cc"
  "strings/utf_string_conversion_utils.h"
  "strings/utf_string_conversions.cc"
  "strings/utf_string_conversions.h"
  "supports_user_data.cc"
  "supports_user_data.h"
  "sync_socket.cc"
  "sync_socket.h"
  "synchronization/atomic_flag.cc"
  "synchronization/atomic_flag.h"
  "synchronization/condition_variable.h"
  "synchronization/lock.cc"
  "synchronization/lock.h"
  "synchronization/lock_impl.h"
  "synchronization/waitable_event.h"
  "synchronization/waitable_event_watcher.h"
  "sys_byteorder.h"
  "syslog_logging.cc"
  "syslog_logging.h"
  "system/sys_info.cc"
  "system/sys_info.h"
  "system/sys_info_internal.h"
  "system/system_monitor.cc"
  "system/system_monitor.h"
  "task/cancelable_task_tracker.cc"
  "task/cancelable_task_tracker.h"
  "task/common/checked_lock.h"
  "task/common/checked_lock_impl.cc"
  "task/common/checked_lock_impl.h"
  "task/common/intrusive_heap.h"
  "task/common/operations_controller.cc"
  "task/common/operations_controller.h"
  "task/common/scoped_defer_task_posting.cc"
  "task/common/scoped_defer_task_posting.h"
  "task/common/task_annotator.cc"
  "task/common/task_annotator.h"
  "task/current_thread.cc"
  "task/current_thread.h"
  "task/lazy_thread_pool_task_runner.cc"
  "task/lazy_thread_pool_task_runner.h"
  "task/post_job.cc"
  "task/post_job.h"
  "task/post_task.cc"
  "task/post_task.h"
  "task/scoped_set_task_priority_for_current_thread.cc"
  "task/scoped_set_task_priority_for_current_thread.h"
  "task/sequence_manager/associated_thread_id.cc"
  "task/sequence_manager/associated_thread_id.h"
  "task/sequence_manager/atomic_flag_set.cc"
  "task/sequence_manager/atomic_flag_set.h"
  "task/sequence_manager/enqueue_order.h"
  "task/sequence_manager/enqueue_order_generator.cc"
  "task/sequence_manager/enqueue_order_generator.h"
  "task/sequence_manager/lazily_deallocated_deque.h"
  "task/sequence_manager/lazy_now.cc"
  "task/sequence_manager/lazy_now.h"
  "task/sequence_manager/real_time_domain.cc"
  "task/sequence_manager/real_time_domain.h"
  "task/sequence_manager/sequence_manager.cc"
  "task/sequence_manager/sequence_manager.h"
  "task/sequence_manager/sequence_manager_impl.cc"
  "task/sequence_manager/sequence_manager_impl.h"
  "task/sequence_manager/sequenced_task_source.h"
  "task/sequence_manager/task_queue.cc"
  "task/sequence_manager/task_queue.h"
  "task/sequence_manager/task_queue_impl.cc"
  "task/sequence_manager/task_queue_impl.h"
  "task/sequence_manager/task_queue_selector.cc"
  "task/sequence_manager/task_queue_selector.h"
  "task/sequence_manager/task_queue_selector_logic.h"
  "task/sequence_manager/task_time_observer.h"
  "task/sequence_manager/tasks.cc"
  "task/sequence_manager/tasks.h"
  "task/sequence_manager/thread_controller.cc"
  "task/sequence_manager/thread_controller.h"
  "task/sequence_manager/thread_controller_impl.cc"
  "task/sequence_manager/thread_controller_impl.h"
  "task/sequence_manager/thread_controller_power_monitor.cc"
  "task/sequence_manager/thread_controller_power_monitor.h"
  "task/sequence_manager/thread_controller_with_message_pump_impl.cc"
  "task/sequence_manager/thread_controller_with_message_pump_impl.h"
  "task/sequence_manager/time_domain.cc"
  "task/sequence_manager/time_domain.h"
  "task/sequence_manager/work_deduplicator.cc"
  "task/sequence_manager/work_deduplicator.h"
  "task/sequence_manager/work_queue.cc"
  "task/sequence_manager/work_queue.h"
  "task/sequence_manager/work_queue_sets.cc"
  "task/sequence_manager/work_queue_sets.h"
  "task/simple_task_executor.cc"
  "task/simple_task_executor.h"
  "task/single_thread_task_executor.cc"
  "task/single_thread_task_executor.h"
  "task/single_thread_task_runner_thread_mode.h"
  "task/task_executor.cc"
  "task/task_executor.h"
  "task/task_features.cc"
  "task/task_features.h"
  "task/task_observer.h"
  "task/task_traits.cc"
  "task/task_traits.h"
  "task/task_traits_extension.h"
  "task/thread_pool.cc"
  "task/thread_pool.h"
  "task/thread_pool/delayed_task_manager.cc"
  "task/thread_pool/delayed_task_manager.h"
  "task/thread_pool/environment_config.cc"
  "task/thread_pool/environment_config.h"
  "task/thread_pool/initialization_util.cc"
  "task/thread_pool/initialization_util.h"
  "task/thread_pool/job_task_source.cc"
  "task/thread_pool/job_task_source.h"
  "task/thread_pool/pooled_parallel_task_runner.cc"
  "task/thread_pool/pooled_parallel_task_runner.h"
  "task/thread_pool/pooled_sequenced_task_runner.cc"
  "task/thread_pool/pooled_sequenced_task_runner.h"
  "task/thread_pool/pooled_single_thread_task_runner_manager.cc"
  "task/thread_pool/pooled_single_thread_task_runner_manager.h"
  "task/thread_pool/pooled_task_runner_delegate.cc"
  "task/thread_pool/pooled_task_runner_delegate.h"
  "task/thread_pool/priority_queue.cc"
  "task/thread_pool/priority_queue.h"
  "task/thread_pool/sequence.cc"
  "task/thread_pool/sequence.h"
  "task/thread_pool/service_thread.cc"
  "task/thread_pool/service_thread.h"
  "task/thread_pool/task.cc"
  "task/thread_pool/task.h"
  "task/thread_pool/task_source.cc"
  "task/thread_pool/task_source.h"
  "task/thread_pool/task_source_sort_key.cc"
  "task/thread_pool/task_source_sort_key.h"
  "task/thread_pool/task_tracker.cc"
  "task/thread_pool/task_tracker.h"
  "task/thread_pool/thread_group.cc"
  "task/thread_pool/thread_group.h"
  "task/thread_pool/thread_group_impl.cc"
  "task/thread_pool/thread_group_impl.h"
  "task/thread_pool/thread_group_native.cc"
  "task/thread_pool/thread_group_native.h"
  "task/thread_pool/thread_pool_impl.cc"
  "task/thread_pool/thread_pool_impl.h"
  "task/thread_pool/thread_pool_instance.cc"
  "task/thread_pool/thread_pool_instance.h"
  "task/thread_pool/tracked_ref.h"
  "task/thread_pool/worker_thread.cc"
  "task/thread_pool/worker_thread.h"
  "task/thread_pool/worker_thread_observer.h"
  "task/thread_pool/worker_thread_stack.cc"
  "task/thread_pool/worker_thread_stack.h"
  "task_runner.cc"
  "task_runner.h"
  "task_runner_util.h"
  "template_util.h"
  "test/malloc_wrapper.h"
  "test/scoped_logging_settings.h"
  "test/spin_wait.h"
  "third_party/cityhash/city.cc"
  "third_party/cityhash/city.h"
  "third_party/cityhash_v103/src/city_v103.cc"
  "third_party/cityhash_v103/src/city_v103.h"
  "third_party/icu/icu_utf.h"
  "third_party/nspr/prtime.cc"
  "third_party/nspr/prtime.h"
  "third_party/superfasthash/superfasthash.c"
  "thread_annotations.h"
  "threading/hang_watcher.cc"
  "threading/hang_watcher.h"
  "threading/platform_thread.cc"
  "threading/platform_thread.h"
  "threading/post_task_and_reply_impl.cc"
  "threading/post_task_and_reply_impl.h"
  "threading/scoped_blocking_call.cc"
  "threading/scoped_blocking_call.h"
  "threading/scoped_blocking_call_internal.cc"
  "threading/scoped_blocking_call_internal.h"
  "threading/scoped_thread_priority.cc"
  "threading/scoped_thread_priority.h"
  "threading/sequence_bound.h"
  "threading/sequence_local_storage_map.cc"
  "threading/sequence_local_storage_map.h"
  "threading/sequence_local_storage_slot.cc"
  "threading/sequence_local_storage_slot.h"
  "threading/sequenced_task_runner_handle.cc"
  "threading/sequenced_task_runner_handle.h"
  "threading/simple_thread.cc"
  "threading/simple_thread.h"
  "threading/thread.cc"
  "threading/thread.h"
  "threading/thread_checker.h"
  "threading/thread_checker_impl.cc"
  "threading/thread_checker_impl.h"
  "threading/thread_collision_warner.cc"
  "threading/thread_collision_warner.h"
  "threading/thread_id_name_manager.cc"
  "threading/thread_id_name_manager.h"
  "threading/thread_local.h"
  "threading/thread_local_internal.h"
  "threading/thread_local_storage.cc"
  "threading/thread_local_storage.h"
  "threading/thread_restrictions.cc"
  "threading/thread_restrictions.h"
  "threading/thread_task_runner_handle.cc"
  "threading/thread_task_runner_handle.h"
  "threading/threading_features.h"
  "threading/watchdog.cc"
  "threading/watchdog.h"
  "time/clock.cc"
  "time/clock.h"
  "time/default_clock.cc"
  "time/default_clock.h"
  "time/default_tick_clock.cc"
  "time/default_tick_clock.h"
  "time/tick_clock.cc"
  "time/tick_clock.h"
  "time/time.cc"
  "time/time.h"
  "time/time_override.cc"
  "time/time_override.h"
  "time/time_to_iso8601.cc"
  "time/time_to_iso8601.h"
  "timer/elapsed_timer.cc"
  "timer/elapsed_timer.h"
  "timer/hi_res_timer_manager.h"
  "timer/lap_timer.cc"
  "timer/lap_timer.h"
  "timer/timer.cc"
  "timer/timer.h"
  "token.cc"
  "token.h"
  "trace_event/base_tracing.h"
  "trace_event/base_tracing_forward.h"
  "trace_event/common/trace_event_common.h"
  "trace_event/heap_profiler_allocation_context.cc"
  "trace_event/heap_profiler_allocation_context.h"
  "trace_event/heap_profiler_allocation_context_tracker.cc"
  "trace_event/heap_profiler_allocation_context_tracker.h"
  "trace_event/memory_allocator_dump_guid.cc"
  "trace_event/memory_allocator_dump_guid.h"
  "trace_event/trace_id_helper.cc"
  "trace_event/trace_id_helper.h"
  "traits_bag.h"
  "tuple.h"
  "types/pass_key.h"
  "types/strong_alias.h"
  "unguessable_token.cc"
  "unguessable_token.h"
  "updateable_sequenced_task_runner.h"
  "value_iterators.cc"
  "value_iterators.h"
  "values.cc"
  "values.h"
  "version.cc"
  "version.h"
  "vlog.cc"
  "vlog.h"
)

# if (!is_nacl)
list(APPEND COMPONENT_BASE_SOURCES_UNPROCESSED
  "base_paths.cc"
  "base_paths.h"
  "metrics/persistent_histogram_storage.cc"
  "metrics/persistent_histogram_storage.h"
)
#
# if (!is_nacl)
if (TARGET_WINDOWS)
  list(APPEND COMPONENT_BASE_SOURCES_UNPROCESSED
    "base_paths_win.cc"
    "base_paths_win.h"
  )
endif()
#
# if (!is_nacl)
if (TARGET_MACOS)
  list(APPEND COMPONENT_BASE_SOURCES_UNPROCESSED
    "base_paths_mac.h"
    "base_paths_mac.mm"
  )
endif()
#
if (TARGET_ANDROID)
  list(APPEND COMPONENT_BASE_SOURCES_UNPROCESSED
    "base_paths_android.cc"
    "base_paths_android.h"
  )
endif()
#
if(TARGET_EMSCRIPTEN OR TARGET_LINUX)
  list(APPEND COMPONENT_BASE_SOURCES_UNPROCESSED
    "base_paths_posix.h"
  )
endif()
#
# if (!is_nacl)
# if (is_linux || is_chromeos)
if(TARGET_EMSCRIPTEN OR TARGET_LINUX)
  list(APPEND COMPONENT_BASE_SOURCES_UNPROCESSED
    "base_paths_posix.cc"
    "debug/elf_reader.cc"
    "debug/elf_reader.h"
  )
endif()

list(TRANSFORM COMPONENT_BASE_SOURCES_UNPROCESSED PREPEND ${BASE_SOURCES_PATH})
list(APPEND COMPONENT_BASE_SOURCES ${COMPONENT_BASE_SOURCES_UNPROCESSED})

if(NOT BASE_USE_JSON)
  filter_regex(
    OUTPUT_VAR COMPONENT_BASE_SOURCES
    IS_INCLUDE_REGEX FALSE
    REGEX "json"
    INPUT_ITEMS ${COMPONENT_BASE_SOURCES}
  )
endif()

if(NOT TARGET_WINDOWS)
  filter_regex(
    OUTPUT_VAR COMPONENT_BASE_SOURCES
    IS_INCLUDE_REGEX FALSE
    REGEX "_msvc"
    INPUT_ITEMS ${COMPONENT_BASE_SOURCES}
  )
endif()
