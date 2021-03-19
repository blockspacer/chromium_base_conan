list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
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
