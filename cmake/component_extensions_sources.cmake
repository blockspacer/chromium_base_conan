﻿list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "type_id.cc"
  "type_id.h"
  "value_conversions.cc"
  "value_conversions.h"
  "wasm_util.h"
  "wasm_closure.h"
  "stl_util.h"
  "spin_lock.cc"
  "spin_lock.h"
  "rvalue_cast.h"
  "recursion_checker.h"
  "output_parameter.h"
  "macros.h"
  "logging.h"
  "enum_to_int.h"
  "crc32.h"
  "crc32.cc"
  "compiler_specific.h"
  "basictypes.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "containers/bounded_inline_vector_impl.h"
  "containers/bounded_inline_vector.h"
  "containers/unique_any.h"
  "containers/unique_any.cc"
  "containers/any_internal.h"
  "containers/any_internal.cc"
  "containers/prioritized_job_dispatcher.h"
  "containers/prioritized_job_dispatcher.cc"
  "containers/prioritized_list.h"
  "containers/prioritized_repeating_task_list.h"
  "containers/prioritized_repeating_task_list.cc"
  "containers/seq_num_buffer.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "decimal/decimal.h"
  "decimal/decimal_numeric_limits.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "dependency_hierarchy/dependency_error_space.h"
  "dependency_hierarchy/dependency_error_space.cc"
  "dependency_hierarchy/dependency_hierarchy.h"
  "dependency_hierarchy/dependency_hierarchy.cc"
  "dependency_hierarchy/dependency_util.h"
  "dependency_hierarchy/dependency_util.cc"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "disjoint_sets/disjoint_sets.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
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
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  memory/wrap_unique_ptr_not_array.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "concurrency/lock_free_producer_consumer_queue.h"
  "concurrency/lock_free_producer_consumer_queue.cc"
  "concurrency/concurrent_int64.h"
  "concurrency/concurrent_int64.cc"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  term_color/term_color.cc
  term_color/term_color.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  fail_point/fail_point.cc
  fail_point/fail_point.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  interval/interval_map.h
  interval/interval_set.h
  interval/interval.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  jsonb/jsonb.h
  jsonb/jsonb.cc
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  lru/estimate_memory_usage_for_lru_cache.h
  lru/lru_cache.h
  lru/lru.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  plug_point/plug_point.cc
  plug_point/plug_point.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  race_sync_point/race_sync_point.cc
  race_sync_point/race_sync_point.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  token_bucket/token_bucket.cc
  token_bucket/token_bucket.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  statistics/rate_tracker.h
  statistics/expandable_statistics_window.h
  statistics/usage_limiter.h
  statistics/rate_tracker.cc
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

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  prometheus_metrics/metrics.cc
  prometheus_metrics/metrics.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "hash/city_hash.h"
  "hash/city_hash.cc"
  "hash/murmurhash.h"
  "hash/murmurhash.cc"
  "hash/xxhash.h"
  "hash/xxhash.cc"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "debug/leak_tracker.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "ranges/enumerated.h"
  "ranges/pipelined.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "strong_types/strong_string.h"
  "strong_types/strong_alias.h"
  "strong_types/strong_bool.h"
  "strong_types/strong_checked_math.h"
  "strong_types/strong_int.h"
  "strong_types/strong_double.h"
  "strong_types/strong_string.h"
  "strong_types/metric_units/strong_metric_units.h"
  "strong_types/money/money_util.cc"
  "strong_types/money/money_util.h"
  "strong_types/money/money.h"
  "strong_types/size_units/strong_size_units.h"
  "strong_types/time_units/strong_time_units.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "synchronization/spin_wait.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "strings/substitute.h"
  "strings/substitute.cc"
  "strings/string_number_conversions.h"
  "strings/string_number_conversions.cc"
  "strings/string_format.h"
  "strings/string_util.h"
  "strings/string_util.cc"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "status/app_error_space.h"
  "status/app_error_space.cc"
  "status/posix_error_space.h"
  "status/posix_error_space.cc"
  "status/status_callback.h"
  "status/status_macros.h"
  "status/status_macros.cc"
  "status/status.h"
  "status/status.cc"
  "status/statusor.h"
  "status/statusor.cc"
  "status/with_details.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "varint/fast_varint.h"
  "varint/fast_varint.cc"
  "varint/memcmpable_varint.h"
  "varint/memcmpable_varint.cc"
  "varint/varint.h"
  "varint/varint.cc"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "annotations/guard_annotations.h"
  "annotations/guard_annotations.cc"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "files/scoped_temp_file.h"
  "files/scoped_temp_file.cc"
  "files/file_path_util.h"
  "files/file_path_util.cc"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  bind/callable_hook.cc
  bind/delay_time_checker.cc
  bind/verify_nothing.h
  bind/ptr_checker.h
  bind/callable_hook.h
  bind/delay_time_checker.h
  bind/call_count_checker.h
  bind/ref_checker.h
  bind/dummy_checker.h
  bind/bind_checked.h
  bind/bind_to_task_runner.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  concept/concepts.h
  concept/is_constructible.h
  concept/dependent_false.h
  concept/is_reference_wrapper.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
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
  core/move_only.h
  core/observable.h
  core/ptr_element_compare.h
  core/scoped_cleanup.h
  core/weak_handle.h
  core/bitmask.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
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

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  backoff_entry/backoff_entry_serializer.cc
  backoff_entry/backoff_entry_serializer.h
  backoff_entry/backoff_entry.cc
  backoff_entry/backoff_entry.h
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  bloom_filter/bloom.cc
  bloom_filter/bloom.h
  bloom_filter/counting_bloom.h
  bloom_filter/double_hashing_bloom.cc
  bloom_filter/double_hashing_bloom.h
  bloom_filter/filter_policy.cc
  bloom_filter/filter_policy.h
)

# TODO
# "numerics/uint256.h"
# "numerics/uint256.cc"
list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "numerics/floating_point_comparison.h"
  "numerics/double_summation.h"
  "numerics/double_summation.cc"
  "numerics/integral_macros.h"
  "numerics/math_utils.h"
  "numerics/pack_numbers.h"
  "numerics/uint128.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "algorithm/top_n.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "bit_field/bit_field.h"
)

list(TRANSFORM EXTENSIONS_SOURCES_UNPROCESSED PREPEND "../extensions/basic/")
list(APPEND COMPONENT_BASE_SOURCES ${EXTENSIONS_SOURCES_UNPROCESSED})
