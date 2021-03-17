cmake_minimum_required( VERSION 3.13.3 FATAL_ERROR )

set(ROOT_PROJECT_NAME ${PROJECT_NAME})
set(ROOT_PROJECT_LIB ${STATIC_LIB_NAME})
set(${ROOT_PROJECT_NAME}_CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

set( PROJECT_NAME "${ROOT_PROJECT_NAME}-tests" )
set( PROJECT_DESCRIPTION "unit tests" )
set( ${PROJECT_NAME}_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "${PROJECT_NAME}_PROJECT_DIR" )

# Get CMAKE_MODULE_PATH from parent project
#include( ${ROOT_PROJECT_DIR}/cmake/Utils.cmake )
#set_cmake_module_paths( ${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR};${${ROOT_PROJECT_NAME}_CMAKE_MODULE_PATH}" ) # from Utils.cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR};${${ROOT_PROJECT_NAME}_CMAKE_MODULE_PATH}")

# NOTE: you can run single test manually like so:
# HEAPCHECK=draconian BASE_GDBINIT_SOURCED=1 gdb -ex r -ex bt -ex q \
#   --args ~/chromium_base_conan/build/Debug/tests/chromium_base-tests/chromium_base-output_parameter_unittest \
#   --single-process-tests \
#   --gtest_filter=* \
#   --vmodule=*=9999 \
#   --test-data-dir="~/chromium_base_conan/tests/data/" \
#   --icu-data-file="~/chromium_base_conan/build/Debug/tests/chromium_base-tests/resources/icu/optimal/icudt68l.dat"
set( GTEST_TEST_ARGS
  "--gtest_shuffle"
  "--test-data-dir=${CMAKE_CURRENT_SOURCE_DIR}/data/"
  "--icu-data-file=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/resources/icu/optimal/icudt68l.dat")

# Run ALL tests with verbose output
# Usage: cmake -E time cmake --build . --target chromium_base_run_all_tests
add_custom_target(${ROOT_PROJECT_NAME}_run_all_tests
    DEPENDS ${ROOT_PROJECT_LIB}
)

list(APPEND TESTS_3DPARTY_LIBS
    CONAN_PKG::conan_gtest
    ${USED_3DPARTY_LIBS}
    ${ROOT_PROJECT_LIB}-test-includes
)

include( testRunner ) # start tests as CMake targets

#findPackageCrossPlatform( Sanitizers ) # see https://github.com/arsenm/sanitizers-cmake
# sanitizer_add_blacklist_file("blacklist.txt") # https://github.com/arsenm/sanitizers-cmake#build-targets-with-sanitizer-support

macro(add_to_tests_list source_list)
  list(APPEND UNIT_TEST_SOURCE_LIST ${source_list})
endmacro()

macro(set_test_compile_options target)
  target_compile_options(${target} PRIVATE
              $<$<CXX_COMPILER_ID:MSVC>:
              /W3 # Set warning level
              #/WX # Treats all compiler warnings as errors.
              >
              $<$<CXX_COMPILER_ID:GNU>:
              -Wformat=2
              -Wall
              -W
##              "$<$<CONFIG:RELEASE>:-Werror>" # Treats all compiler warnings as errors.
              -Wpedantic
              #-fsanitize-address-use-after-scope # https://clang.llvm.org/docs/AddressSanitizer.html
              #-fsanitize=pointer-compare # https://kristerw.blogspot.com/2018/06/useful-gcc-address-sanitizer-checks-not.html
              -fno-omit-frame-pointer # https://github.com/google/sanitizers/wiki/AddressSanitizer#using-addresssanitizer
              >
              $<$<CXX_COMPILER_ID:Clang>:
              -Wformat=2
              -Wall
              -W
##              "$<$<CONFIG:RELEASE>:-Werror>" # Treats all compiler warnings as errors.
              -Wpedantic
              -Wdeprecated-register
              #-fsanitize-address-use-after-scope # https://clang.llvm.org/docs/AddressSanitizer.html
              #-fsanitize=pointer-compare # https://kristerw.blogspot.com/2018/06/useful-gcc-address-sanitizer-checks-not.html
              -fno-omit-frame-pointer # https://github.com/google/sanitizers/wiki/AddressSanitizer#using-addresssanitizer
              >
          )

  # @see https://github.com/eranpeer/FakeIt
  target_compile_options( ${target} PRIVATE
    # If you don't use /ZI, you will have exceptions mocking destructors (which includes unique_ptr and other smart pointers).
    $<$<CXX_COMPILER_ID:MSVC>:/ZI>
    # On GCC, optimization flag O2 and O3 are not supported. You must compile the test project with -O1 or -O0.
    $<$<CXX_COMPILER_ID:GNU>:-O0>
    $<$<CXX_COMPILER_ID:Clang>:-O0> )

  set_target_properties( ${target} PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    CMAKE_CXX_STANDARD_REQUIRED ON
    CMAKE_CXX_FLAGS "-fno-rtti /std:c++latest"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} )
endmacro()

macro(tests_add_executable target source_list TEST_ARGS TEST_LIB)
  list(APPEND UNIT_TEST_TARGETS ${target})

  add_to_tests_list(${source_list})

  add_executable(${target} ${source_list})

  if (NOT CMAKE_BUILD_TYPE MATCHES "Debug" )
##    add_sanitizers( ${target} ) # https://github.com/arsenm/sanitizers-cmake#build-targets-with-sanitizer-support
  endif()

  target_link_libraries(${target} PRIVATE
    # 3dparty libs
    ${TESTS_3DPARTY_LIBS}
    # system libs
    ${USED_SYSTEM_LIBS}
    # main project lib
    ${ROOT_PROJECT_LIB}
    ${TEST_LIB}
  )

  target_include_directories(${target} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )

  set_test_compile_options( ${target} )

  target_compile_options(${target} PUBLIC
    -Wno-c++11-narrowing
    -Wno-c++98-compat
    -Wno-reserved-id-macro
    -Wno-macro-redefined
    -Wno-implicit-function-declaration
    -Wno-c++11-narrowing
    -Wno-builtin-macro-redefined
    #  format string is not a string literal
    -Wno-format-nonliteral
    -fno-exceptions # disabling exceptions
    # definition of implicit copy assignment operator
    # for 'Location' is deprecated because it has a user-declared copy constructor
    -Wno-deprecated-copy
    # trace_event.h: warning: unused function template 'AddMetadataEvent'
    -Wno-unused-template
    # warning: empty expression statement has no effect; remove unnecessary ';'
    # to silence this warning [-Wextra-semi-stmt]
    # TRACE_EVENT0
    -Wno-extra-semi-stmt
    -Wno-unused-parameter
    -Wno-unused-variable
    -Wno-old-style-cast
    # frame.h: warning: definition of implicit copy constructor for 'Frame'
    # is deprecated because it has a user-declared destructor
    -Wno-deprecated-copy-dtor
    # fixes base/logging.h:406:65: warning: token pasting of ',' and __VA_ARGS__ is a GNU extension [-Wgnu-zero-variadic-macro-arguments]
    -Wno-gnu-zero-variadic-macro-arguments
    -Wno-missing-field-initializers
    -Wno-implicit-int-float-conversion
    -Wno-gnu-statement-expression
  )

  add_test(
    NAME ${target}
    COMMAND ${target} ${TEST_ARGS})

  add_test_command_targets( ${target} )

  if(ENABLE_VALGRIND)
    # |base::TestSuite| tries to kill test process
    # but valgrind wraps process, so nothing to kill
    target_compile_definitions( ${target} PUBLIC
      BUILD_DATE=BASE_BUILD_DATE
      GTEST_NO_SUITE=1) # TODO: valgrind may not support chromium base, FIXME. And remove GTEST_NO_SUITE
  endif(ENABLE_VALGRIND)

  # USAGE:
  # cmake -E time cmake --build . --target TARGET_NAME_run_valgrind
  valgrind_enabler(
    IS_ENABLED
      ${ENABLE_VALGRIND}
    STANDALONE_TARGET
      ${target}
    EXTRA_OPTIONS # see https://valgrind.org/docs/manual/manual-core.html
      # When enabled, Valgrind will trace into sub-processes
      # initiated via the exec system call.
      # This is necessary for multi-process programs.
      --trace-children=yes
      # --leak-check=full:
      # each individual leak will be shown in detail
      --leak-check=full
      # --show-leak-kinds=all:
      # Show all of "definite, indirect, possible, reachable"
      # leak kinds in the "full" report.
      --show-leak-kinds=all
      # --track-origins=yes:
      # Favor useful output over speed.
      # This tracks the origins of uninitialized values,
      # which could be very useful for memory errors.
      # Consider turning off if Valgrind is unacceptably slow.
      --track-origins=yes
      # --verbose:
      # Can tell you about unusual behavior of your program.
      # Repeat for more verbosity.
      --verbose
      --show-reachable=yes
      # When enabled, Valgrind stops reporting errors
      # after 10,000,000 in total, or 1,000 different ones,
      # have been seen.
      --error-limit=yes
      # is option is particularly useful with C++ programs,
      # as it prints out the suppressions with mangled names,
      # as required.
      --gen-suppressions=all
      # Write to a file.
      # Useful when output exceeds terminal space.
      --log-file=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${target}_valgrind_raw.log
      # executable
      $<TARGET_FILE:${target}>
      # arguments of executable
      ${TEST_ARGS}
    REQUIRED
  )
  if(ENABLE_VALGRIND AND ENABLE_VALGRIND_TESTS)
    add_dependencies(${ROOT_PROJECT_NAME}_run_all_tests
      ${target}_run_valgrind
    )
  endif(ENABLE_VALGRIND AND ENABLE_VALGRIND_TESTS)

  if(AUTORUN_TESTS)
    add_test_autostarter( ${target} )
  endif()
endmacro()

set(test_main_gtest "${ROOT_PROJECT_NAME}-test_main_gtest")
add_library( ${test_main_gtest} OBJECT
  main_gtest.cpp
  #${${ROOT_PROJECT_NAME}_SRCS} # all source files  of root project without main.cpp
  #${THIRDPARTY_SOURCES}
  tests_common.hpp # include in IDE
  )

set_property(TARGET ${test_main_gtest} PROPERTY CXX_STANDARD 17)

# ensure that dependencies build before <target> does.
add_dependencies(${test_main_gtest} ${ROOT_PROJECT_LIB})

set_test_compile_options( ${test_main_gtest} )

target_link_libraries(${test_main_gtest} PUBLIC
  # 3dparty libs
  ${TESTS_3DPARTY_LIBS}
  # system libs
  ${USED_SYSTEM_LIBS}
  # main project lib
  ${ROOT_PROJECT_LIB}
)

target_compile_definitions( ${test_main_gtest} PUBLIC
  BUILD_DATE=BASE_BUILD_DATE
  USE_GTEST_TEST=1 )

if(ENABLE_VALGRIND)
  # |base::TestSuite| tries to kill test process
  # but valgrind wraps process, so nothing to kill
  target_compile_definitions( ${test_main_gtest} PUBLIC
    GTEST_NO_SUITE=1) # TODO: valgrind may not support chromium base, FIXME. And remove GTEST_NO_SUITE
endif(ENABLE_VALGRIND)

set(test_main_perftest "${ROOT_PROJECT_NAME}-test_main_perftest")
add_library( ${test_main_perftest} OBJECT
  main_gtest.cpp
  #${${ROOT_PROJECT_NAME}_SRCS} # all source files  of root project without main.cpp
  #${THIRDPARTY_SOURCES}
  tests_common.hpp # include in IDE
  )

set_property(TARGET ${test_main_perftest} PROPERTY CXX_STANDARD 17)

# ensure that dependencies build before <target> does.
add_dependencies(${test_main_perftest} ${ROOT_PROJECT_LIB})

set_test_compile_options( ${test_main_perftest} )

target_link_libraries(${test_main_perftest} PUBLIC
  # 3dparty libs
  ${TESTS_3DPARTY_LIBS}
  # system libs
  ${USED_SYSTEM_LIBS}
  # main project lib
  ${ROOT_PROJECT_LIB}
)

target_compile_definitions( ${test_main_perftest} PUBLIC
  BUILD_DATE=BASE_BUILD_DATE
  USE_GTEST_TEST=1
  GTEST_PERF_SUITE=1
  PERF_TEST=1)

if(ENABLE_VALGRIND)
  # |base::TestSuite| tries to kill test process
  # but valgrind wraps process, so nothing to kill
  target_compile_definitions( ${test_main_perftest} PUBLIC
    GTEST_NO_SUITE=1) # TODO: valgrind may not support chromium base, FIXME. And remove GTEST_NO_SUITE
endif(ENABLE_VALGRIND)

option(AUTORUN_TESTS "Autorun tests" OFF) # see add_test_autostarter

# TODO: add nc tests https://stackoverflow.com/questions/30155619/expected-build-failure-tests-in-cmake
# https://www.chromium.org/developers/testing/no-compile-tests
# https://chromium.googlesource.com/chromium/src/+/master/build/nocompile.gni

option(${ROOT_PROJECT_NAME}_BUILD_TESTS "Enable tests" ON)
if(${ROOT_PROJECT_NAME}_BUILD_TESTS)
  message( "${PROJECT_NAME} testing enabled" )

  set ( gmock_deps
    gmock.test.cpp
  )
  tests_add_executable(${ROOT_PROJECT_NAME}-gmock
    "${gmock_deps}" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  set ( i18n_deps
    i18n.test.cpp
  )
  tests_add_executable(${ROOT_PROJECT_NAME}-i18n
    "${i18n_deps}" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # "i18n" is one of test program names
  add_custom_command( TARGET ${ROOT_PROJECT_NAME}-i18n POST_BUILD
                      COMMAND ${CMAKE_COMMAND} -E copy_directory
                          ${CMAKE_CURRENT_SOURCE_DIR}/data
                          ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} )

  enable_testing()

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
    "build_time_unittest.cc"
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
    #"path_service_unittest.cc"
    #"pickle_unittest.cc"
    #"power_monitor/power_monitor_device_source_unittest.cc"
    #"power_monitor/power_monitor_unittest.cc"
    #"process/environment_internal_unittest.cc"
    #"process/memory_unittest.cc"
    #"process/process_metrics_unittest.cc"
    #"process/process_unittest.cc"
    #"process/process_util_unittest.cc"
    #"profiler/arm_cfi_table_unittest.cc"
    #"profiler/metadata_recorder_unittest.cc"
    #"profiler/module_cache_unittest.cc"
    #"profiler/sample_metadata_unittest.cc"
    #"profiler/stack_copier_suspend_unittest.cc"
    #"profiler/stack_copier_unittest.cc"
    #"profiler/stack_sampler_impl_unittest.cc"
    #"profiler/stack_sampling_profiler_unittest.cc"
    #"rand_util_unittest.cc"
    #"ranges/algorithm_unittest.cc"
    #"ranges/functional_unittest.cc"
    #"ranges/ranges_unittest.cc"
    #"run_loop_unittest.cc"
    #"safe_numerics_unittest.cc"
    #"sampling_heap_profiler/lock_free_address_hash_set_unittest.cc"
    #"scoped_clear_last_error_unittest.cc"
    #"scoped_generic_unittest.cc"
    #"scoped_multi_source_observation_unittest.cc"
    #"scoped_observation_unittest.cc"
    #"security_unittest.cc"
    #"sequence_checker_unittest.cc"
    #"sequence_token_unittest.cc"
    #"sequenced_task_runner_unittest.cc"
    #"stl_util_unittest.cc"
    #"strings/abseil_string_conversions_unittest.cc"
    #"strings/char_traits_unittest.cc"
    #"strings/escape_unittest.cc"
    #"strings/no_trigraphs_unittest.cc"
    #"strings/nullable_string16_unittest.cc"
    #"strings/pattern_unittest.cc"
    #"strings/safe_sprintf_unittest.cc"
    #"strings/strcat_unittest.cc"
    #"strings/string_number_conversions_unittest.cc"
    #"strings/string_piece_unittest.cc"
    #"strings/string_split_unittest.cc"
    #"strings/string_tokenizer_unittest.cc"
    #"strings/string_util_unittest.cc"
    #"strings/stringize_macros_unittest.cc"
    #"strings/stringprintf_unittest.cc"
    #"strings/sys_string_conversions_unittest.cc"
    #"strings/utf_offset_string_conversions_unittest.cc"
    #"strings/utf_string_conversions_unittest.cc"
    #"supports_user_data_unittest.cc"
    #"sync_socket_unittest.cc"
    #"synchronization/atomic_flag_unittest.cc"
    #"synchronization/condition_variable_unittest.cc"
    #"synchronization/lock_unittest.cc"
    #"synchronization/waitable_event_unittest.cc"
    #"synchronization/waitable_event_watcher_unittest.cc"
    #"sys_byteorder_unittest.cc"
    #"system/sys_info_unittest.cc"
    #"system/system_monitor_unittest.cc"
    #"task/cancelable_task_tracker_unittest.cc"
    #"task/common/checked_lock_unittest.cc"
    #"task/common/operations_controller_unittest.cc"
    #"task/common/task_annotator_unittest.cc"
    #"task/lazy_thread_pool_task_runner_unittest.cc"
    #"task/post_job_unittest.cc"
    #"task/post_task_unittest.cc"
    #"task/scoped_set_task_priority_for_current_thread_unittest.cc"
    #"task/sequence_manager/atomic_flag_set_unittest.cc"
    #"task/sequence_manager/lazily_deallocated_deque_unittest.cc"
    #"task/sequence_manager/sequence_manager_impl_unittest.cc"
    #"task/sequence_manager/task_queue_selector_unittest.cc"
    #"task/sequence_manager/task_queue_unittest.cc"
    #"task/sequence_manager/test/mock_time_message_pump_unittest.cc"
    #"task/sequence_manager/thread_controller_power_monitor_unittest.cc"
    #"task/sequence_manager/thread_controller_with_message_pump_impl_unittest.cc"
    #"task/sequence_manager/time_domain_unittest.cc"
    #"task/sequence_manager/work_deduplicator_unittest.cc"
    #"task/sequence_manager/work_queue_sets_unittest.cc"
    #"task/sequence_manager/work_queue_unittest.cc"
    #"task/single_thread_task_executor_unittest.cc"
    #"task/task_traits_extension_unittest.cc"
    #"task/task_traits_unittest.cc"
    #"task/thread_pool/delayed_task_manager_unittest.cc"
    #"task/thread_pool/environment_config_unittest.cc"
    #"task/thread_pool/job_task_source_unittest.cc"
    #"task/thread_pool/pooled_single_thread_task_runner_manager_unittest.cc"
    #"task/thread_pool/priority_queue_unittest.cc"
    #"task/thread_pool/sequence_unittest.cc"
    #"task/thread_pool/service_thread_unittest.cc"
    #"task/thread_pool/task_source_sort_key_unittest.cc"
    #"task/thread_pool/task_tracker_unittest.cc"
    #"task/thread_pool/thread_group_impl_unittest.cc"
    #"task/thread_pool/thread_group_unittest.cc"
    #"task/thread_pool/thread_pool_impl_unittest.cc"
    #"task/thread_pool/tracked_ref_unittest.cc"
    #"task/thread_pool/worker_thread_stack_unittest.cc"
    #"task/thread_pool/worker_thread_unittest.cc"
    #"task/thread_pool_unittest.cc"
    #"task_runner_unittest.cc"
    #"task_runner_util_unittest.cc"
    #"template_util_unittest.cc"
    #"test/gmock_callback_support_unittest.cc"
    #"test/gmock_move_support_unittest.cc"
    #"test/gtest_links_unittest.cc"
    #"test/gtest_xml_unittest_result_printer_unittest.cc"
    #"test/launcher/test_launcher_unittest.cc"
    #"test/launcher/test_results_tracker_unittest.cc"
    #"test/metrics/histogram_enum_reader_unittest.cc"
    #"test/metrics/histogram_tester_unittest.cc"
    #"test/metrics/user_action_tester_unittest.cc"
    #"test/mock_callback_unittest.cc"
    #"test/scoped_feature_list_unittest.cc"
    #"test/scoped_logging_settings.h"
    #"test/scoped_mock_clock_override_unittest.cc"
    #"test/scoped_mock_time_message_loop_task_runner_unittest.cc"
    #"test/scoped_run_loop_timeout_unittest.cc"
    #"test/task_environment_unittest.cc"
    #"test/test_mock_time_task_runner_unittest.cc"
    #"test/test_pending_task_unittest.cc"
    #"test/test_waitable_event_unittest.cc"
    #"thread_annotations_unittest.cc"
    #"threading/hang_watcher_unittest.cc"
    #"threading/platform_thread_unittest.cc"
    #"threading/post_task_and_reply_impl_unittest.cc"
    #"threading/scoped_blocking_call_unittest.cc"
    #"threading/scoped_thread_priority_unittest.cc"
    #"threading/sequence_bound_unittest.cc"
    #"threading/sequence_local_storage_map_unittest.cc"
    #"threading/sequence_local_storage_slot_unittest.cc"
    #"threading/sequenced_task_runner_handle_unittest.cc"
    #"threading/simple_thread_unittest.cc"
    #"threading/thread_checker_unittest.cc"
    #"threading/thread_collision_warner_unittest.cc"
    #"threading/thread_id_name_manager_unittest.cc"
    #"threading/thread_local_storage_unittest.cc"
    #"threading/thread_local_unittest.cc"
    #"threading/thread_restrictions_unittest.cc"
    #"threading/thread_task_runner_handle_unittest.cc"
    #"threading/thread_unittest.cc"
    #"threading/watchdog_unittest.cc"
    #"time/pr_time_unittest.cc"
    #"time/time_unittest.cc"
    #"timer/elapsed_timer_unittest.cc"
    #"timer/hi_res_timer_manager_unittest.cc"
    #"timer/lap_timer_unittest.cc"
    #"timer/mock_timer_unittest.cc"
    #"timer/timer_unittest.cc"
    #"token_unittest.cc"
    #"tools_sanity_unittest.cc"
    #"traits_bag_unittest.cc"
    #"tuple_unittest.cc"
    #"types/pass_key_unittest.cc"
    #"types/strong_alias_unittest.cc"
    #"unguessable_token_unittest.cc"
    #"value_iterators_unittest.cc"
    #"values_unittest.cc"
    #"version_unittest.cc"
    #"vlog_unittest.cc"
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

  list(APPEND extensions_unittests
    debug/leak_tracker_unittest.cc
  )

  list(APPEND extensions_unittests
    containers/bounded_inline_vector_unittest.cc
    containers/unique_any_unittest.cc
    containers/any_internal_unittest.cc
  )

  list(APPEND extensions_unittests
    hash/city_hash_unittest.cc
    hash/murmurhash_unittest.cc
    hash/xxhash_unittest.cc
  )

  list(APPEND extensions_unittests
    ranges/enumerated_unittest.cc
    ranges/pipelined_unittest.cc
  )

  list(APPEND extensions_unittests
    strings/string_number_conversions_unittest.cc
    strings/substitute_unittest.cc
    strings/string_util_unittest.cc
    strings/string_format_unittest.cc
  )

  list(APPEND extensions_unittests
    annnotations/guard_annotations_unittest.cc
  )

  list(APPEND extensions_unittests
    numerics/double_summation_unittest.cc
    numerics/floating_point_comparison_unittest.cc
  )

  list(APPEND extensions_unittests
    test/test_macros_unittest.cc
  )

  list(APPEND extensions_unittests
    algorithm/top_n_unittest.cc
  )

  list(APPEND extensions_unittests
    bit_field/bit_field_unittest.cc
  )

  list(TRANSFORM extensions_unittests PREPEND "../extensions/basic/")
  list(APPEND base_unittests ${extensions_unittests})

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
    tests_add_executable(${ROOT_PROJECT_NAME}-${FILENAME_WITHOUT_EXT}
      "${test_sources}" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  endforeach()
endif()

foreach(target IN LISTS ALL_TESTS_LIST_VERBOSE)
  add_dependencies(${ROOT_PROJECT_NAME}_run_all_tests
    ${target}
  )
endforeach()

option(ENABLE_CODE_COVERAGE "ENABLE CODE COVERAGE" OFF)
if (ENABLE_CODE_COVERAGE)
  set(LCOV_REMOVE_EXTRA "'*/src/include/webrtc/*'" "'${ROOT_PROJECT_DIR}/lib/*'" "'${ROOT_PROJECT_DIR}/submodules/*'" "'test/*'" "'ext/*'" "'abseil/*'" "'submodules/*'" "'*/tests/*'" "'scripts/*'" "'lib/*'" "'build/*'" "'bin/*'" "'*Catch/*'" "'*FakeIt/*'")
  set(CMAKE_BUILD_TYPE Coverage)
  # test coverage build configuration for C++: debug build, no optimization, profiling enabled
  #set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
  #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")

  target_compile_options(${ROOT_PROJECT_NAME}_run_all_tests PRIVATE
    -g -O0 -Wall -fprofile-arcs -ftest-coverage
  )
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
  # include the cmake code coverage module
  include( CodeCoverage )
  # cmake code coverage module target
  setup_target_for_coverage(
    # Name for custom target.
    unit_tests_coverage
    # Name of the test driver executable that runs the tests.
    # NOTE! This should always have a ZERO as exit code
    # otherwise the coverage generation will not complete.
    check_all
    coverage # Name of output directory.
    )
  message("added make code coverage for ${PROJECT_NAME}_coverage")
else()
  message(WARNING "code coverage off")
endif()

#find_package(Sanitizers)
#if(HAS_Address_SANITIZER AND HAS_Fuzzer_SANITIZER)
#	add_executable(fuzz fuzzing.cpp)
#	target_link_libraries(fuzz PUBLIC gltfpp Sanitizer::Fuzzer Sanitizer::Address)
#endif()
