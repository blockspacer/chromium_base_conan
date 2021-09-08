list(APPEND COMPONENT_BASIC_SOURCES
  type_id.cc
  type_id.h
  value_conversions.cc
  value_conversions.h
  wasm_util.h
  wasm_closure.h
  stl_util.h
  rvalue_cast.h
  recursion_checker.h
  output_parameter.h
  macros.h
  logging.h
  enum_to_int.h
  cmd_util.h
  cmd_util.cc
  compiler_specific.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  test/test_macros.h
  test/test_random.h
  test/type_id_test_support_a.h
  test/type_id_test_support_a.cc
  test/type_id_test_support_b.h
  test/type_id_test_support_b.cc
  test/deterministic_schedule.h
  test/deterministic_schedule.cc
  test/semaphore.h
  test/barrier.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  state_machine/state_machine.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  containers/bounded_inline_vector_impl.h
  containers/bounded_inline_vector.h
  containers/unique_any.h
  containers/unique_any.cc
  containers/invertible_map.h
  containers/invertible_map.cc
  containers/any_internal.h
  containers/any_internal.cc
  containers/any_dictionary.h
  containers/prioritized_job_dispatcher.h
  containers/prioritized_job_dispatcher.cc
  containers/prioritized_list.h
  containers/prioritized_repeating_task_list.h
  containers/prioritized_repeating_task_list.cc
  containers/seq_num_buffer.h
  containers/sparse_byte_set.h
  containers/indexed_mem_pool.h
  # TODO
  # containers/mem_pool.h
  # containers/mem_pool.cc
  containers/flat_combining_priority_queue.h
  containers/mpmc_queue.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  portability/sysmman.h
  portability/sysmman.cc
  portability/unistd.h
  portability/unistd.cc
  portability/malloc_impl.cc
  portability/basictypes.h
  portability/c_portability.h
  portability/config.h
  portability/constexpr.h
  portability/SysTime.h
  portability/SysTime.cc
  portability/SysResource.h
  portability/SysResource.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  decimal/decimal.h
  decimal/decimal.cc
  decimal/fixed_point.h
  decimal/fixed_point_numeric_limits.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  dependency_hierarchy/dependency_error_space.h
  dependency_hierarchy/dependency_error_space.cc
  dependency_hierarchy/dependency_hierarchy.h
  dependency_hierarchy/dependency_hierarchy.cc
  dependency_hierarchy/dependency_util.h
  dependency_hierarchy/dependency_util.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  disjoint_sets/disjoint_sets.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  promise/dependent_list.h
  promise/promise_value.h
  promise/abstract_promise.cc
  promise/abstract_promise.h
  promise/finally_executor.cc
  promise/no_op_promise_executor.h
  promise/dependent_list.cc
  promise/finally_executor.h
  promise/no_op_promise_executor.cc
  promise/do_nothing_promise.cc
  promise/all_tuple_executor.h
  promise/all_container_executor.h
  promise/do_nothing_promise.h
  promise/helpers.cc
  promise/helpers.h
  promise/promise_value.cc
  promise/race_tuple_executor.h
  promise/promise_collection.h
  promise/race_container_executor.h
  promise/promise_executor.h
  promise/promise_executor.cc
  promise/then_and_catch_executor.h
  promise/then_and_catch_executor.cc
  promise/promise_result.h
  promise/post_task_executor.h
  promise/post_promise.cc
  promise/promise.h
  promise/post_promise.h
  promise/coroutine.h
  promise/coroutine.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  memory/wrap_unique_ptr_not_array.h
  memory/unowned_ptr.h
  memory/unowned_ref.h
  memory/mallctl_helper.cc
  memory/padded.h
  memory/not_null.h
  memory/not_null-inl.h
  memory/arena.h
  memory/arena-inl.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  json/json_serializers.h
  json/json_serializers.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  multiconfig/multiconfig.h
  multiconfig/multiconfig.cc
  multiconfig/option_parser.h
  multiconfig/option_parser.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  time/backoff_timer.h
  time/backoff_timer.cc
  time/delta_timer.h
  time/delta_timer.cc
  time/system_time_change_notifier.h
  time/system_time_change_notifier.cc
  time/time_macros.h
  time/hardware_timestamp.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  concurrency/lock_free_producer_consumer_queue.h
  concurrency/lock_free_producer_consumer_queue.cc
  concurrency/concurrent_int64.h
  concurrency/concurrent_int64.cc
  concurrency/cache_locality.h
  concurrency/cache_locality.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  term_color/term_color.cc
  term_color/term_color.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  fail_point/fail_point.cc
  fail_point/fail_point.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  interval/interval_map.h
  interval/interval_set.h
  interval/interval.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  jsonb/jsonb.h
  jsonb/jsonb.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  lru/estimate_memory_usage_for_lru_cache.h
  lru/lru_cache.h
  lru/lru.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  plug_point/plug_point.cc
  plug_point/plug_point.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  race_sync_point/race_sync_point.cc
  race_sync_point/race_sync_point.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  token_bucket/token_bucket.cc
  token_bucket/token_bucket.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  statistics/rate_tracker.h
  statistics/rate_tracker.cc
  statistics/rate_tracker.h
  statistics/rate_tracker_window.cc
  statistics/expandable_statistics_window.h
  statistics/usage_limiter.h
  statistics/quality_threshold.h
  statistics/usage_limiter.cc
  statistics/weighted_moving_average.h
  statistics/moving_average.h
  statistics/moving_average.cc
  statistics/percentile_filter.h
  statistics/quality_threshold.cc
  statistics/moving_median_filter.h
  statistics/moving_statistics_window.h
  statistics/weighted_moving_linear_regression.h
  statistics/weighted_moving_linear_regression.cc
  statistics/weighted_moving_average.cc
  statistics/weighted_mean.h
  statistics/weighted_mean.cc
  statistics/hdr_histogram.h
  statistics/hdr_histogram.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  prometheus_metrics/metrics.cc
  prometheus_metrics/metrics.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  secure_clear/secure_string.h
  secure_clear/secure_string.cc
  secure_clear/secure_blob.h
  secure_clear/secure_blob.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  hash/crc32.h
  hash/crc32.cc
  hash/city_hash.h
  hash/city_hash.cc
  hash/farmhash.h
  hash/farmhash.cc
  hash/murmurhash.h
  hash/murmurhash.cc
  hash/xxhash.h
  hash/xxhash.cc
  hash/twang_hash.h
  hash/jenkins_hash.h
  hash/spooky_hash_v2.h
  hash/spooky_hash_v2.cc
  hash/hash_combine.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  debug/leak_tracker.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  ranges/enumerated.h
  ranges/pipelined.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  strong_types/strong_string.h
  strong_types/strong_alias.h
  strong_types/strong_bool.h
  strong_types/strong_checked_math.h
  strong_types/strong_int.h
  strong_types/strong_double.h
  strong_types/strong_string.h
  strong_types/metric_units/strong_metric_units.h
  strong_types/money/money_util.cc
  strong_types/money/money_util.h
  strong_types/money/money.h
  strong_types/size_units/strong_size_units.h
  strong_types/time_units/strong_time_units.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  synchronization/atomic_struct.h
  synchronization/atomic_utils.h
  synchronization/futex.h
  synchronization/futex.cc
  synchronization/futex_inl.h
  synchronization/parking_lot.h
  synchronization/parking_lot.cc
  synchronization/flat_combining.h
  synchronization/saturating_semaphore.h
  synchronization/memory_idler.h
  synchronization/memory_idler.cc
  synchronization/atomic_util.h
  synchronization/atomic_util_inl.h
  synchronization/wait_options.h
  synchronization/wait_options.cc
  synchronization/spin_wait.h
  synchronization/spin.h
  synchronization/spin_lock.h
  synchronization/spin_lock.cc
  synchronization/baton.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  random/random.h
  random/random.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  strings/substitute.h
  strings/substitute.cc
  strings/string_number_conversions.h
  strings/string_number_conversions.cc
  strings/string_format.h
  strings/string_util.h
  strings/string_util.cc
  strings/fixed_string.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  status/app_error_space.h
  status/app_error_space.cc
  status/posix_error_space.h
  status/posix_error_space.cc
  status/status_callback.h
  status/status_macros.h
  status/status_macros.cc
  status/status.h
  status/status.cc
  status/statusor.h
  status/statusor.cc
  status/with_details.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  tracing/local_trace.h
  tracing/stats_table.h
  tracing/stats_table.cc
  tracing/trace_event_util.h
  tracing/tracing_util.h
  tracing/tracing_util.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  static_sequence/static_sequence.h
  static_sequence/static_sequence.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  varint/fast_varint.h
  varint/fast_varint.cc
  varint/memcmpable_varint.h
  varint/memcmpable_varint.cc
  varint/varint.h
  varint/varint.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  annotations/guard_annotations.h
  annotations/guard_annotations.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  files/scoped_temp_file.h
  files/scoped_temp_file.cc
  files/file_path_util.h
  files/file_path_util.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  types_bucket/types_bucket.cc
  types_bucket/types_bucket.h
  types_bucket/thread_local_types_bucket.cc
  types_bucket/thread_local_types_bucket.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  bind/callable_hook.cc
  bind/verify_nothing.h
  bind/callable_hook.h
  bind/bind_ptr_checker.h
  bind/bind_delay_time_checker.cc
  bind/bind_exec_time_checker.h
  bind/bind_exec_time_checker.cc
  bind/bind_delay_time_checker.h
  bind/bind_call_count_checker.h
  bind/bind_ref_checker.h
  bind/bind_dummy_checker.h
  bind/bind_checked.h
  bind/bind_to_task_runner.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  concept/concepts.h
  concept/is_constructible.h
  concept/dependent_false.h
  concept/is_reference_wrapper.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  core/container_beginning_address.h
  core/polymorphic_upcast.h
  core/pimpl.h
  core/debug_flag_macros.h
  core/numeric_static_cast.h
  core/immutable.h
  core/sequence_bound_flag.cc
  core/type_name.h
  core/sequence_bound_flag.h
  core/scoped_value_saver.h
  core/pointer_cast.h
  core/exact_pointer_cast.h
  core/typed_enum.h
  core/implicit_cast.h
  core/enum_limits.h
  core/retrier.h
  core/weak_handle.cc
  core/polymorphic_downcast.h
  core/enum_set.h
  core/move_only_on_sequence.h
  core/observable.h
  core/ptr_element_compare.h
  core/scoped_cleanup.h
  core/weak_handle.h
  core/bitmask.h
  core/move_wrapper.h
  core/memory.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  log/progress_logger.cc
  log/scoped_log_run_time.cc
  log/scoped_log_run_time.h
  log/spacer.h
  log/logger.cc
  log/log_util.cc
  log/logger.h
  log/spacer.cc
  log/table_printer.h
  log/table_printer.cc
  log/log_util.h
  log/progress_logger.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  backoff_entry/backoff_entry_serializer.cc
  backoff_entry/backoff_entry_serializer.h
  backoff_entry/backoff_entry.cc
  backoff_entry/backoff_entry.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  bloom_filter/bloom.cc
  bloom_filter/bloom.h
  bloom_filter/counting_bloom.h
  bloom_filter/double_hashing_bloom.cc
  bloom_filter/double_hashing_bloom.h
  bloom_filter/filter_policy.cc
  bloom_filter/filter_policy.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  numerics/floating_point_comparison.h
  numerics/double_summation.h
  numerics/double_summation.cc
  numerics/integral_macros.h
  numerics/math_utils.h
  numerics/pack_numbers.h
  numerics/uint128.h
  numerics/uint256.h
  numerics/uint256.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  algorithm/top_n.h
  algorithm/base32.h
  algorithm/base32.cc
)

list(APPEND COMPONENT_BASIC_SOURCES
  message_loop/message_loop_utils.cc
  message_loop/message_loop_utils.h
)

list(APPEND COMPONENT_BASIC_SOURCES
  bit_field/bit_field.h
)
