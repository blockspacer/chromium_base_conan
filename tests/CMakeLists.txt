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
# gdb -ex r -ex bt -ex q \
#   --args $HOME/chromium_base_conan/build/Debug/tests/chromium_base-tests/chromium_base-string_search_unittest \
#   --single-process-tests \
#   --gtest_filter=* \
#   --test-data-dir="$HOME/chromium_base_conan/tests/data/"
set( GTEST_TEST_ARGS
  "--gtest_shuffle"
  "--test-data-dir=${CMAKE_CURRENT_SOURCE_DIR}/data/")

# Run ALL tests with verbose output
# Usage: cmake --build build --target run_all_tests
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
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${ROOT_PROJECT_NAME}-tests )
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
    # TRACE_EVENT0("toplevel", "PluginManager::shutdown()");
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
      --log-file=${CMAKE_CURRENT_BINARY_DIR}/${ROOT_PROJECT_NAME}-tests/${target}_valgrind_raw.log
      # executable
      $<TARGET_FILE:${target}>
      # arguments of executable
      ${TEST_ARGS}
    VERBOSE
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
  "-DUSE_GTEST_TEST=1" )

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
  USE_GTEST_TEST=1
  GTEST_PERF_SUITE=1)

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

  tests_add_executable(${ROOT_PROJECT_NAME}-break_iterator_unittest
    "${BASE_SOURCES_PATH}i18n/break_iterator_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-timezone_unittest
    "${BASE_SOURCES_PATH}i18n/timezone_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-time_formatting_unittest
    "${BASE_SOURCES_PATH}i18n/time_formatting_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-char_iterator_unittest
    "${BASE_SOURCES_PATH}i18n/char_iterator_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-file_util_icu_unittest
    "${BASE_SOURCES_PATH}i18n/file_util_icu_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # FIXME: requires codepages in icu `.dat` files
  #tests_add_executable(${ROOT_PROJECT_NAME}-icu_string_conversions_unittest
  #  "${BASE_SOURCES_PATH}i18n/icu_string_conversions_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-streaming_utf8_validator_unittest
    "${BASE_SOURCES_PATH}i18n/streaming_utf8_validator_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-streaming_utf8_validator_perftest
  #  "${BASE_SOURCES_PATH}i18n/streaming_utf8_validator_perftest.cc" "${GTEST_TEST_ARGS}" "${test_main_perftest}")

  # FIXME: requires codepages in icu `.dat` files
  #tests_add_executable(${ROOT_PROJECT_NAME}-number_formatting_unittest
  #  "${BASE_SOURCES_PATH}i18n/number_formatting_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-message_formatter_unittest
    "${BASE_SOURCES_PATH}i18n/message_formatter_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-string_search_unittest
    "${BASE_SOURCES_PATH}i18n/string_search_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # FIXME: requires codepages in icu `.dat` files
  #tests_add_executable(${ROOT_PROJECT_NAME}-rtl_unittest
  #  "${BASE_SOURCES_PATH}i18n/rtl_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-case_conversion_unittest
    "${BASE_SOURCES_PATH}i18n/case_conversion_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-optional_unittest
    "${BASE_SOURCES_PATH}optional_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-parameter_pack_unittest
    "${BASE_SOURCES_PATH}parameter_pack_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-path_service_unittest
    "${BASE_SOURCES_PATH}path_service_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-component_export_unittest
    "${BASE_SOURCES_PATH}component_export_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # FIXME Update version to https://source.chromium.org/chromium/chromium/src/+/master:base/containers/checked_iterators.h
  #tests_add_executable(${ROOT_PROJECT_NAME}-checked_iterators_unittest
  #  "${BASE_SOURCES_PATH}containers/checked_iterators_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-flat_set_unittest
    "${BASE_SOURCES_PATH}containers/flat_set_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO: FIXME
  #tests_add_executable(${ROOT_PROJECT_NAME}-fixed_flat_set_unittest
  #  "${BASE_SOURCES_PATH}containers/fixed_flat_set_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-intrusive_heap_unittest
    "${BASE_SOURCES_PATH}containers/intrusive_heap_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-buffer_iterator_unittest
    "${BASE_SOURCES_PATH}containers/buffer_iterator_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-flat_map_unittest
    "${BASE_SOURCES_PATH}containers/flat_map_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO: FIXME
  #tests_add_executable(${ROOT_PROJECT_NAME}-fixed_flat_map_unittest
  #  "${BASE_SOURCES_PATH}containers/fixed_flat_map_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-mru_cache_unittest
    "${BASE_SOURCES_PATH}containers/mru_cache_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-id_map_unittest
    "${BASE_SOURCES_PATH}containers/id_map_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-bounded_inline_vector_unittest
    "${BASE_SOURCES_PATH}containers/bounded_inline_vector_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-buffer_iterator_unittest
  #  "${BASE_SOURCES_PATH}containers/buffer_iterator_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-contiguous_iterator_unittest
    "${BASE_SOURCES_PATH}containers/contiguous_iterator_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-any_internal_unittest
    "${BASE_SOURCES_PATH}containers/any_internal_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-small_map_unittest
    "${BASE_SOURCES_PATH}containers/small_map_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-unique_ptr_adapters_unittest
    "${BASE_SOURCES_PATH}containers/unique_ptr_adapters_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-span_unittest
  #  "${BASE_SOURCES_PATH}containers/span_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO FIXME
  #tests_add_executable(${ROOT_PROJECT_NAME}-span_unittest
  #  "${BASE_SOURCES_PATH}containers/span_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-circular_deque_unittest
    "${BASE_SOURCES_PATH}containers/circular_deque_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-checked_iterators_unittest
  #  "${BASE_SOURCES_PATH}containers/checked_iterators_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-flat_tree_unittest
    "${BASE_SOURCES_PATH}containers/flat_tree_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-unique_any_unittest
    "${BASE_SOURCES_PATH}containers/unique_any_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-linked_list_unittest
    "${BASE_SOURCES_PATH}containers/linked_list_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-adapters_unittest
    "${BASE_SOURCES_PATH}containers/adapters_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-contains_unittest
    "${BASE_SOURCES_PATH}containers/contains_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-stack_container_unittest
    "${BASE_SOURCES_PATH}containers/stack_container_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-vector_buffer_unittest
    "${BASE_SOURCES_PATH}containers/vector_buffer_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-unique_any_unittest
  #  "${BASE_SOURCES_PATH}containers/unique_any_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-environment_internal_unittest
    "${BASE_SOURCES_PATH}process/environment_internal_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-process_metrics_unittest
    "${BASE_SOURCES_PATH}process/process_metrics_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO: ProcessUtilTest.GetAppOutputWithExitCode
  # tests_add_executable(${ROOT_PROJECT_NAME}-process_util_unittest
  #   "${BASE_SOURCES_PATH}process/process_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-memory_unittest
    "${BASE_SOURCES_PATH}process/memory_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-process_unittest
    "${BASE_SOURCES_PATH}process/process_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-message_loop_io_posix_unittest
  #  "${BASE_SOURCES_PATH}message_loop/message_loop_io_posix_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-message_pump_glib_unittest
  #  "${BASE_SOURCES_PATH}message_loop/message_pump_glib_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO: ThreadSanitizer: data race
  # in ScheduleWorkTest.ThreadTimeToIOFromTwoThreads
  # tests_add_executable(${ROOT_PROJECT_NAME}-message_pump_perftest
  #   "${BASE_SOURCES_PATH}message_loop/message_pump_perftest.cc" "${GTEST_TEST_ARGS}" "${test_main_perftest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-message_pump_mac_unittest
  #  "${BASE_SOURCES_PATH}message_loop/message_pump_mac_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-message_loop_unittest
    "${BASE_SOURCES_PATH}message_loop/message_loop_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-message_pump_libevent_unittest
  #  "${BASE_SOURCES_PATH}message_loop/message_pump_libevent_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-message_pump_kqueue_unittest
  #  "${BASE_SOURCES_PATH}message_loop/message_pump_kqueue_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-work_id_provider_unittest
    "${BASE_SOURCES_PATH}message_loop/work_id_provider_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-message_pump_io_ios_unittest
  #  "${BASE_SOURCES_PATH}message_loop/message_pump_io_ios_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-message_pump_unittest
    "${BASE_SOURCES_PATH}message_loop/message_pump_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-values_util_unittest
    "${BASE_SOURCES_PATH}util/values/values_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-id_type_unittest
    "${BASE_SOURCES_PATH}util/type-safety/id_type_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-value_iterators_unittest
    "${BASE_SOURCES_PATH}value_iterators_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-one_shot_event_unittest
    "${BASE_SOURCES_PATH}one_shot_event_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-thread_annotations_unittest
    "${BASE_SOURCES_PATH}thread_annotations_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-os_compat_android_unittest
  #  "${BASE_SOURCES_PATH}os_compat_android_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-task_trace_unittest
    "${BASE_SOURCES_PATH}debug/task_trace_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-debugger_unittest
    "${BASE_SOURCES_PATH}debug/debugger_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-leak_tracker_unittest
    "${BASE_SOURCES_PATH}debug/leak_tracker_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-activity_analyzer_unittest
    "${BASE_SOURCES_PATH}debug/activity_analyzer_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  if(TARGET_LINUX)
    tests_add_executable(${ROOT_PROJECT_NAME}-proc_maps_linux_unittest
      "${BASE_SOURCES_PATH}debug/proc_maps_linux_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  endif(TARGET_LINUX)

  tests_add_executable(${ROOT_PROJECT_NAME}-alias_unittest
    "${BASE_SOURCES_PATH}debug/alias_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-stack_trace_unittest
    "${BASE_SOURCES_PATH}debug/stack_trace_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # FIXME
  # This library is used by ElfReaderTest to test reading elf files.
  #"MALLOC_WRAPPER_LIB=\"${shlib_prefix}malloc_wrapper${shlib_extension}\"",
  #tests_add_executable(${ROOT_PROJECT_NAME}-elf_reader_unittest
  #  "${BASE_SOURCES_PATH}debug/elf_reader_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-activity_tracker_unittest
    "${BASE_SOURCES_PATH}debug/activity_tracker_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO: ThreadSanitizer: unlock of an unlocked mutex
  # eztime.cc(159)] Not implemented reached in bool EzTimeValueExplode
  # tests_add_executable(${ROOT_PROJECT_NAME}-crash_logging_unittest
  #   "${BASE_SOURCES_PATH}debug/crash_logging_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-scoped_clear_last_error_unittest
    "${BASE_SOURCES_PATH}scoped_clear_last_error_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-atomic_flag_unittest
    "${BASE_SOURCES_PATH}synchronization/atomic_flag_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-waitable_event_perftest
  #  "${BASE_SOURCES_PATH}synchronization/waitable_event_perftest.cc" "${GTEST_TEST_ARGS}" "${test_main_perftest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-waitable_event_watcher_unittest
    "${BASE_SOURCES_PATH}synchronization/waitable_event_watcher_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-condition_variable_unittest
    "${BASE_SOURCES_PATH}synchronization/condition_variable_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-lock_unittest
    "${BASE_SOURCES_PATH}synchronization/lock_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-waitable_event_unittest
    "${BASE_SOURCES_PATH}synchronization/waitable_event_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-metadata_recorder_unittest
    "${BASE_SOURCES_PATH}profiler/metadata_recorder_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-stack_sampling_profiler_unittest
    "${BASE_SOURCES_PATH}profiler/stack_sampling_profiler_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-stack_sampler_impl_unittest
    "${BASE_SOURCES_PATH}profiler/stack_sampler_impl_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-win32_stack_frame_unwinder_unittest
  #  "${BASE_SOURCES_PATH}profiler/win32_stack_frame_unwinder_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sample_metadata_unittest
    "${BASE_SOURCES_PATH}profiler/sample_metadata_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-type_id_unittest
    "${BASE_SOURCES_PATH}type_id_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-run_loop_unittest
    "${BASE_SOURCES_PATH}run_loop_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-traits_bag_unittest
  #  "${BASE_SOURCES_PATH}traits_bag_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-no_destructor_unittest
    "${BASE_SOURCES_PATH}no_destructor_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-supports_user_data_unittest
    "${BASE_SOURCES_PATH}supports_user_data_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-guid_unittest
    "${BASE_SOURCES_PATH}guid_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-thread_task_runner_handle_unittest
    "${BASE_SOURCES_PATH}threading/thread_task_runner_handle_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-thread_restrictions_unittest
    "${BASE_SOURCES_PATH}threading/thread_restrictions_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-thread_local_storage_unittest
    "${BASE_SOURCES_PATH}threading/thread_local_storage_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO: ThreadSanitizer: data race
  # tests_add_executable(${ROOT_PROJECT_NAME}-watchdog_unittest
  #   "${BASE_SOURCES_PATH}threading/watchdog_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-platform_thread_win_unittest
  #  "${BASE_SOURCES_PATH}threading/platform_thread_win_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-thread_unittest
    "${BASE_SOURCES_PATH}threading/thread_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-scoped_blocking_call_unittest
    "${BASE_SOURCES_PATH}threading/scoped_blocking_call_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  #TODO FIXME
  #tests_add_executable(${ROOT_PROJECT_NAME}-thread_perftest
  #  "${BASE_SOURCES_PATH}threading/thread_perftest.cc" "${GTEST_TEST_ARGS}" "${test_main_perftest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-thread_id_name_manager_unittest
    "${BASE_SOURCES_PATH}threading/thread_id_name_manager_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sequence_bound_unittest
    "${BASE_SOURCES_PATH}threading/sequence_bound_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-thread_checker_unittest
    "${BASE_SOURCES_PATH}threading/thread_checker_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sequence_local_storage_slot_unittest
    "${BASE_SOURCES_PATH}threading/sequence_local_storage_slot_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sequence_local_storage_map_unittest
    "${BASE_SOURCES_PATH}threading/sequence_local_storage_map_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sequenced_task_runner_handle_unittest
    "${BASE_SOURCES_PATH}threading/sequenced_task_runner_handle_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-simple_thread_unittest
    "${BASE_SOURCES_PATH}threading/simple_thread_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO: ThreadSanitizer: data race
  # tests_add_executable(${ROOT_PROJECT_NAME}-thread_collision_warner_unittest
  #   "${BASE_SOURCES_PATH}threading/thread_collision_warner_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-post_task_and_reply_impl_unittest
    "${BASE_SOURCES_PATH}threading/post_task_and_reply_impl_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-platform_thread_unittest
    "${BASE_SOURCES_PATH}threading/platform_thread_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # FIXME
  #tests_add_executable(${ROOT_PROJECT_NAME}-hang_watcher_unittest
  #  "${BASE_SOURCES_PATH}threading/hang_watcher_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-thread_local_unittest
    "${BASE_SOURCES_PATH}threading/thread_local_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-scoped_generic_unittest
    "${BASE_SOURCES_PATH}scoped_generic_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-rand_util_unittest
    "${BASE_SOURCES_PATH}rand_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-base64_unittest
    "${BASE_SOURCES_PATH}base64_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sequence_checker_unittest
    "${BASE_SOURCES_PATH}sequence_checker_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-task_runner_util_unittest
    "${BASE_SOURCES_PATH}task_runner_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-callback_helpers_unittest
    "${BASE_SOURCES_PATH}callback_helpers_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-pickle_unittest
    "${BASE_SOURCES_PATH}pickle_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-traits_bag_unittest
    "${BASE_SOURCES_PATH}traits_bag_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-vlog_unittest
    "${BASE_SOURCES_PATH}vlog_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sys_byteorder_unittest
    "${BASE_SOURCES_PATH}sys_byteorder_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sequenced_task_runner_unittest
    "${BASE_SOURCES_PATH}sequenced_task_runner_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-test_reg_util_win_unittest
  #  "${BASE_SOURCES_PATH}test/test_reg_util_win_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-scoped_task_environment_unittest
    "${BASE_SOURCES_PATH}test/scoped_task_environment_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-scoped_mock_time_message_loop_task_runner_unittest
    "${BASE_SOURCES_PATH}test/scoped_mock_time_message_loop_task_runner_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-scoped_mock_clock_override_unittest
    "${BASE_SOURCES_PATH}test/scoped_mock_clock_override_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-multiprocess_test
  #  "${BASE_SOURCES_PATH}test/multiprocess_test.h" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-multiprocess_test
  #  "${BASE_SOURCES_PATH}test/multiprocess_test.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-serializer_nested_test
    "${BASE_SOURCES_PATH}test/data/serializer_nested_test.json" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-serializer_test
    "${BASE_SOURCES_PATH}test/data/serializer_test.json" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-trace_event_analyzer_unittest
    "${BASE_SOURCES_PATH}test/trace_event_analyzer_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-test_mock_time_task_runner_unittest
    "${BASE_SOURCES_PATH}test/test_mock_time_task_runner_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-histogram_tester_unittest
    "${BASE_SOURCES_PATH}test/metrics/histogram_tester_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO: enums.xml file does not exist.
  # tests_add_executable(${ROOT_PROJECT_NAME}-histogram_enum_reader_unittest
  #   "${BASE_SOURCES_PATH}test/metrics/histogram_enum_reader_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-user_action_tester_unittest
    "${BASE_SOURCES_PATH}test/metrics/user_action_tester_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-test_pending_task_unittest
    "${BASE_SOURCES_PATH}test/test_pending_task_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-mock_callback_unittest
    "${BASE_SOURCES_PATH}test/mock_callback_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-platform_test
  #  "${BASE_SOURCES_PATH}test/testing/platform_test.h" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-test_results_tracker_unittest
    "${BASE_SOURCES_PATH}test/launcher/test_results_tracker_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-unit_test_launcher_unittest
    "${BASE_SOURCES_PATH}test/launcher/unit_test_launcher_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-scoped_feature_list_unittest
    "${BASE_SOURCES_PATH}test/scoped_feature_list_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-lazy_instance_unittest
    "${BASE_SOURCES_PATH}lazy_instance_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-scoped_set_task_priority_for_current_thread_unittest
    "${BASE_SOURCES_PATH}task/scoped_set_task_priority_for_current_thread_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-operations_controller_unittest
    "${BASE_SOURCES_PATH}task/common/operations_controller_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-common-intrusive_heap_unittest
    "${BASE_SOURCES_PATH}task/common/intrusive_heap_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-checked_lock_unittest
    "${BASE_SOURCES_PATH}task/common/checked_lock_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-task_annotator_unittest
    "${BASE_SOURCES_PATH}task/common/task_annotator_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-thread_group_impl_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/thread_group_impl_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sequence_sort_key_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/sequence_sort_key_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-priority_queue_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/priority_queue_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-thread_group_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/thread_group_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sequence_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/sequence_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-thread_pool_impl_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/thread_pool_impl_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-task_tracker_posix_unittest
  #  "${BASE_SOURCES_PATH}task/thread_pool/task_tracker_posix_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-tracked_ref_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/tracked_ref_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-task_source_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/task_source_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # FIXME
  #tests_add_executable(${ROOT_PROJECT_NAME}-thread_pool_perftest
  #  "${BASE_SOURCES_PATH}task/thread_pool/thread_pool_perftest.cc" "${GTEST_TEST_ARGS}" "${test_main_perftest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-can_run_policy_test
  #  "${BASE_SOURCES_PATH}task/thread_pool/can_run_policy_test.h" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-pooled_single_thread_task_runner_manager_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/pooled_single_thread_task_runner_manager_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-service_thread_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/service_thread_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-task_tracker_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/task_tracker_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-worker_thread_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/worker_thread_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-delayed_task_manager_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/delayed_task_manager_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-worker_thread_stack_unittest
    "${BASE_SOURCES_PATH}task/thread_pool/worker_thread_stack_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-post_task_unittest
    "${BASE_SOURCES_PATH}task/post_task_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-lazy_task_runner_unittest
    "${BASE_SOURCES_PATH}task/lazy_task_runner_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-task_queue_unittest
    "${BASE_SOURCES_PATH}task/sequence_manager/task_queue_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-work_queue_unittest
    "${BASE_SOURCES_PATH}task/sequence_manager/work_queue_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-atomic_flag_set_unittest
    "${BASE_SOURCES_PATH}task/sequence_manager/atomic_flag_set_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-task_queue_selector_unittest
    "${BASE_SOURCES_PATH}task/sequence_manager/task_queue_selector_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sequence_manager_impl_unittest
    "${BASE_SOURCES_PATH}task/sequence_manager/sequence_manager_impl_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-thread_controller_with_message_pump_impl_unittest
    "${BASE_SOURCES_PATH}task/sequence_manager/thread_controller_with_message_pump_impl_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-sequence_manager_for_test
  #  "${BASE_SOURCES_PATH}task/sequence_manager/test/sequence_manager_for_test.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-sequence_manager_for_test
  #  "${BASE_SOURCES_PATH}task/sequence_manager/test/sequence_manager_for_test.h" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-mock_time_message_pump_unittest
    "${BASE_SOURCES_PATH}task/sequence_manager/test/mock_time_message_pump_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-work_deduplicator_unittest
    "${BASE_SOURCES_PATH}task/sequence_manager/work_deduplicator_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-time_domain_unittest
    "${BASE_SOURCES_PATH}task/sequence_manager/time_domain_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO: HANGS
  # tests_add_executable(${ROOT_PROJECT_NAME}-sequence_manager_perftest
  #   "${BASE_SOURCES_PATH}task/sequence_manager/sequence_manager_perftest.cc" "${GTEST_TEST_ARGS}" "${test_main_perftest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-lazily_deallocated_deque_unittest
    "${BASE_SOURCES_PATH}task/sequence_manager/lazily_deallocated_deque_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-work_queue_sets_unittest
    "${BASE_SOURCES_PATH}task/sequence_manager/work_queue_sets_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-cancelable_task_tracker_unittest
    "${BASE_SOURCES_PATH}task/cancelable_task_tracker_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-task_traits_extension_unittest
  #  "${BASE_SOURCES_PATH}task/task_traits_extension_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-task_traits_unittest
    "${BASE_SOURCES_PATH}task/task_traits_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-task_traits_extension_unittest
    "${BASE_SOURCES_PATH}task/task_traits_extension_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  # tests_add_executable(${ROOT_PROJECT_NAME}-task_traits_unittest
  #  "${BASE_SOURCES_PATH}task/task_traits_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-safe_numerics_unittest
    "${BASE_SOURCES_PATH}safe_numerics_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-mach_port_broker_unittest
  #  "${BASE_SOURCES_PATH}mac/mach_port_broker_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-bind_objc_block_unittest
  #  "${BASE_SOURCES_PATH}mac/bind_objc_block_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-call_with_eh_frame_unittest
  #  "${BASE_SOURCES_PATH}mac/call_with_eh_frame_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-foundation_util_unittest
  #  "${BASE_SOURCES_PATH}mac/foundation_util_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-mac_util_unittest
  #  "${BASE_SOURCES_PATH}mac/mac_util_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-scoped_sending_event_unittest
  #  "${BASE_SOURCES_PATH}mac/scoped_sending_event_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-dispatch_source_mach_unittest
  #  "${BASE_SOURCES_PATH}mac/dispatch_source_mach_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-scoped_mach_vm_unittest
  #  "${BASE_SOURCES_PATH}mac/scoped_mach_vm_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-objc_release_properties_unittest
  #  "${BASE_SOURCES_PATH}mac/objc_release_properties_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-scoped_nsobject_unittest
  #  "${BASE_SOURCES_PATH}mac/scoped_nsobject_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-scoped_objc_class_swizzler_unittest
  #  "${BASE_SOURCES_PATH}mac/scoped_objc_class_swizzler_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-mach_port_rendezvous_unittest
  #  "${BASE_SOURCES_PATH}mac/mach_port_rendezvous_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-ranges
    "${BASE_SOURCES_PATH}values_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-trace_event_unittest
    "${BASE_SOURCES_PATH}trace_event/trace_event_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-memory_allocator_dump_unittest
    "${BASE_SOURCES_PATH}trace_event/memory_allocator_dump_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-blame_context_unittest
    "${BASE_SOURCES_PATH}trace_event/blame_context_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-cpufreq_monitor_android_unittest
  #  "${BASE_SOURCES_PATH}trace_event/cpufreq_monitor_android_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-memory_infra_background_whitelist_unittest
    "${BASE_SOURCES_PATH}trace_event/memory_infra_background_whitelist_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-process_memory_dump_unittest
    "${BASE_SOURCES_PATH}trace_event/process_memory_dump_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-memory_dump_scheduler_unittest
    "${BASE_SOURCES_PATH}trace_event/memory_dump_scheduler_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-heap_profiler_allocation_context_tracker_unittest
    "${BASE_SOURCES_PATH}trace_event/heap_profiler_allocation_context_tracker_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-trace_category_unittest
    "${BASE_SOURCES_PATH}trace_event/trace_category_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-traced_value_unittest
    "${BASE_SOURCES_PATH}trace_event/traced_value_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-java_heap_dump_provider_android_unittest
  #  "${BASE_SOURCES_PATH}trace_event/java_heap_dump_provider_android_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-memory_usage_estimator_unittest
    "${BASE_SOURCES_PATH}trace_event/memory_usage_estimator_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-trace_arguments_unittest
    "${BASE_SOURCES_PATH}trace_event/trace_arguments_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-event_name_filter_unittest
    "${BASE_SOURCES_PATH}trace_event/event_name_filter_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-trace_event_android_unittest
  #  "${BASE_SOURCES_PATH}trace_event/trace_event_android_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-cfi_backtrace_android_unittest
  #  "${BASE_SOURCES_PATH}trace_event/cfi_backtrace_android_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-trace_config_unittest
    "${BASE_SOURCES_PATH}trace_event/trace_config_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-memory_dump_manager_unittest
    "${BASE_SOURCES_PATH}trace_event/memory_dump_manager_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-allocator_interception_mac_unittest
  #  "${BASE_SOURCES_PATH}allocator/allocator_interception_mac_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-tcmalloc_unittest
    "${BASE_SOURCES_PATH}allocator/tcmalloc_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-malloc_zone_functions_mac_unittest
  #  "${BASE_SOURCES_PATH}allocator/malloc_zone_functions_mac_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-winheap_stubs_win_unittest
  #  "${BASE_SOURCES_PATH}allocator/winheap_stubs_win_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  if(USE_ALLOC_SHIM)
    tests_add_executable(${ROOT_PROJECT_NAME}-allocator_shim_unittest
      "${BASE_SOURCES_PATH}allocator/allocator_shim_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  endif(USE_ALLOC_SHIM)

  if(BASE_USE_PARTITION_ALLOCATOR)
    tests_add_executable(${ROOT_PROJECT_NAME}-page_allocator_unittest
      "${BASE_SOURCES_PATH}allocator/partition_allocator/page_allocator_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

    # TODO
    #tests_add_executable(${ROOT_PROJECT_NAME}-partition_alloc_perftest
    #  "${BASE_SOURCES_PATH}allocator/partition_allocator/partition_alloc_perftest.cc" "${GTEST_TEST_ARGS}" "${test_main_perftest}")

    tests_add_executable(${ROOT_PROJECT_NAME}-spin_lock_unittest
      "${BASE_SOURCES_PATH}allocator/partition_allocator/spin_lock_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

    tests_add_executable(${ROOT_PROJECT_NAME}-partition_alloc_unittest
      "${BASE_SOURCES_PATH}allocator/partition_allocator/partition_alloc_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

    tests_add_executable(${ROOT_PROJECT_NAME}-address_space_randomization_uni
      "${BASE_SOURCES_PATH}allocator/partition_allocator/address_space_randomization_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  endif(BASE_USE_PARTITION_ALLOCATOR)

  tests_add_executable(${ROOT_PROJECT_NAME}-tuple_unittest
    "${BASE_SOURCES_PATH}tuple_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # base::allocator shims are not available for memory sampling.
  if(NOT USE_ALLOC_SHIM)
    tests_add_executable(${ROOT_PROJECT_NAME}-module_cache_unittest
      "${BASE_SOURCES_PATH}sampling_heap_profiler/module_cache_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

    tests_add_executable(${ROOT_PROJECT_NAME}-sampling_heap_profiler_unittest
      "${BASE_SOURCES_PATH}sampling_heap_profiler/sampling_heap_profiler_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

    tests_add_executable(${ROOT_PROJECT_NAME}-lock_free_address_hash_set_unittest
      "${BASE_SOURCES_PATH}sampling_heap_profiler/lock_free_address_hash_set_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  endif(NOT USE_ALLOC_SHIM)

  tests_add_executable(${ROOT_PROJECT_NAME}-template_util_unittest
    "${BASE_SOURCES_PATH}template_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  # tests_add_executable(${ROOT_PROJECT_NAME}-callback_list_unittest
  #  "${BASE_SOURCES_PATH}callback_list_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-deferred_sequenced_task_runner_unittest
    "${BASE_SOURCES_PATH}deferred_sequenced_task_runner_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  # tests_add_executable(${ROOT_PROJECT_NAME}-optional_unittest
  #  "${BASE_SOURCES_PATH}optional_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-histogram_functions_unittest
    "${BASE_SOURCES_PATH}metrics/histogram_functions_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sample_vector_unittest
    "${BASE_SOURCES_PATH}metrics/sample_vector_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-histogram_delta_serialization_unittest
    "${BASE_SOURCES_PATH}metrics/histogram_delta_serialization_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-histogram_base_unittest
    "${BASE_SOURCES_PATH}metrics/histogram_base_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sample_map_unittest
    "${BASE_SOURCES_PATH}metrics/sample_map_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-field_trial_unittest
    "${BASE_SOURCES_PATH}metrics/field_trial_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-histogram_unittest
    "${BASE_SOURCES_PATH}metrics/histogram_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-field_trial_params_unittest
    "${BASE_SOURCES_PATH}metrics/field_trial_params_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-persistent_histogram_allocator_unittest
    "${BASE_SOURCES_PATH}metrics/persistent_histogram_allocator_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  # tests_add_executable(${ROOT_PROJECT_NAME}-field_trial_params_unittest
  #  "${BASE_SOURCES_PATH}metrics/field_trial_params_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-histogram_macros_unittest
    "${BASE_SOURCES_PATH}metrics/histogram_macros_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-histogram_samples_unittest
    "${BASE_SOURCES_PATH}metrics/histogram_samples_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sparse_histogram_unittest
    "${BASE_SOURCES_PATH}metrics/sparse_histogram_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-metrics_hashes_unittest
    "${BASE_SOURCES_PATH}metrics/metrics_hashes_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-persistent_memory_allocator_unittest
    "${BASE_SOURCES_PATH}metrics/persistent_memory_allocator_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-persistent_histogram_storage_unittest
    "${BASE_SOURCES_PATH}metrics/persistent_histogram_storage_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-persistent_sample_map_unittest
    "${BASE_SOURCES_PATH}metrics/persistent_sample_map_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  # tests_add_executable(${ROOT_PROJECT_NAME}-histogram_unittest
  #  "${BASE_SOURCES_PATH}metrics/histogram_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-statistics_recorder_unittest
    "${BASE_SOURCES_PATH}metrics/statistics_recorder_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-histogram_snapshot_manager_unittest
    "${BASE_SOURCES_PATH}metrics/histogram_snapshot_manager_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-bucket_ranges_unittest
    "${BASE_SOURCES_PATH}metrics/bucket_ranges_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-single_sample_metrics_unittest
    "${BASE_SOURCES_PATH}metrics/single_sample_metrics_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-xdg_util_unittest
  #  "${BASE_SOURCES_PATH}nix/xdg_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-observer_list_unittest
    "${BASE_SOURCES_PATH}observer_list_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-hash_unittest
    "${BASE_SOURCES_PATH}hash/hash_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-md5_unittest
    "${BASE_SOURCES_PATH}hash/md5_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sha1_unittest
    "${BASE_SOURCES_PATH}hash/sha1_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-bits_unittest
    "${BASE_SOURCES_PATH}bits_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-atomicops_unittest
    "${BASE_SOURCES_PATH}atomicops_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-unguessable_token_unittest
    "${BASE_SOURCES_PATH}unguessable_token_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  # tests_add_executable(${ROOT_PROJECT_NAME}-observer_list_unittest
  #  "${BASE_SOURCES_PATH}observer_list_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-service_provider_impl_unittest
  #  "${BASE_SOURCES_PATH}fuchsia/service_provider_impl_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-file_utils_unittest
  #  "${BASE_SOURCES_PATH}fuchsia/file_utils_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-service_directory_unittest
  #  "${BASE_SOURCES_PATH}fuchsia/service_directory_unittest.cc
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-filtered_service_directory_unittest
  #  "${BASE_SOURCES_PATH}fuchsia/filtered_service_directory_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-test
  #  "${BASE_SOURCES_PATH}fuchsia/test.fidl" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-callback_unittest
    "${BASE_SOURCES_PATH}callback_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  # tests_add_executable(${ROOT_PROJECT_NAME}-bind_unittest
  #  "${BASE_SOURCES_PATH}bind_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-environment_unittest
    "${BASE_SOURCES_PATH}environment_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO: SUMMARY: ThreadSanitizer: unlock of an unlocked mutex (or by a wrong thread)
  # cobalt/starboard/shared/pthread/mutex_release.cc:26:20 in SbMutexRelease
  # eztime.cc(159) Not implemented reached in
  # bool EzTimeValueExplode
  # tests_add_executable(${ROOT_PROJECT_NAME}-logging_unittest
  #   "${BASE_SOURCES_PATH}logging_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-version_unittest
    "${BASE_SOURCES_PATH}version_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-observer_list_perftest
  #  "${BASE_SOURCES_PATH}observer_list_perftest.cc" "${GTEST_TEST_ARGS}" "${test_main_perftest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-observer_list_threadsafe_unittest
    "${BASE_SOURCES_PATH}observer_list_threadsafe_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-enumerated_unittest
    "${BASE_SOURCES_PATH}ranges/enumerated_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-pipelined_unittest
    "${BASE_SOURCES_PATH}ranges/pipelined_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-algorithm_unittest
    "${BASE_SOURCES_PATH}ranges/algorithm_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-functional_unittest
    "${BASE_SOURCES_PATH}ranges/functional_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-ranges_unittest
    "${BASE_SOURCES_PATH}ranges/ranges_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-string_tokenizer_unittest
    "${BASE_SOURCES_PATH}strings/string_tokenizer_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-char_traits_unittest
    "${BASE_SOURCES_PATH}strings/char_traits_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-safe_sprintf_unittest
    "${BASE_SOURCES_PATH}strings/safe_sprintf_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-utf_string_conversions_unittest
    "${BASE_SOURCES_PATH}strings/utf_string_conversions_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-strcat_unittest
    "${BASE_SOURCES_PATH}strings/strcat_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-stringprintf_unittest
    "${BASE_SOURCES_PATH}strings/stringprintf_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-string_number_conversions_unittest
    "${BASE_SOURCES_PATH}strings/string_number_conversions_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-nullable_string16_unittest
    "${BASE_SOURCES_PATH}strings/nullable_string16_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-string_util_perftest
  #  "${BASE_SOURCES_PATH}strings/string_util_perftest.cc" "${GTEST_TEST_ARGS}" "${test_main_perftest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-escape_unittest
    "${BASE_SOURCES_PATH}strings/escape_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-utf_offset_string_conversions_unittest
    "${BASE_SOURCES_PATH}strings/utf_offset_string_conversions_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  # tests_add_executable(${ROOT_PROJECT_NAME}-ranges
  #  "${BASE_SOURCES_PATH}strings/string16_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-string_piece_unittest
    "${BASE_SOURCES_PATH}strings/string_piece_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-pattern_unittest
    "${BASE_SOURCES_PATH}strings/pattern_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sys_string_conversions_unittest
    "${BASE_SOURCES_PATH}strings/sys_string_conversions_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-stringize_macros_unittest
    "${BASE_SOURCES_PATH}strings/stringize_macros_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-string_util_unittest
    "${BASE_SOURCES_PATH}strings/string_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-string16_unittest
    "${BASE_SOURCES_PATH}strings/string16_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-sys_string_conversions_mac_unittest
  #  "${BASE_SOURCES_PATH}strings/sys_string_conversions_mac_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-string_split_unittest
    "${BASE_SOURCES_PATH}strings/string_split_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-power_monitor_unittest
    "${BASE_SOURCES_PATH}power_monitor/power_monitor_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-barrier_closure_unittest
    "${BASE_SOURCES_PATH}barrier_closure_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-big_endian_unittest
    "${BASE_SOURCES_PATH}big_endian_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-hi_res_timer_manager_unittest
    "${BASE_SOURCES_PATH}timer/hi_res_timer_manager_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-mock_timer_unittest
    "${BASE_SOURCES_PATH}timer/mock_timer_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-lap_timer_unittest
    "${BASE_SOURCES_PATH}timer/lap_timer_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-timer_unittest
    "${BASE_SOURCES_PATH}timer/timer_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-bit_cast_unittest
    "${BASE_SOURCES_PATH}bit_cast_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-unix_domain_socket_unittest
  #  "${BASE_SOURCES_PATH}posix/unix_domain_socket_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-file_descriptor_shuffle_unittest
  #  "${BASE_SOURCES_PATH}posix/file_descriptor_shuffle_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-shared_memory_mac_unittest
  #  "${BASE_SOURCES_PATH}memory/shared_memory_mac_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-memory_pressure_monitor_mac_unittest
  #  "${BASE_SOURCES_PATH}memory/memory_pressure_monitor_mac_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-memory_pressure_listener_unittest
    "${BASE_SOURCES_PATH}memory/memory_pressure_listener_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-discardable_shared_memory_unittest
    "${BASE_SOURCES_PATH}memory/discardable_shared_memory_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-platform_shared_memory_region_unittest
    "${BASE_SOURCES_PATH}memory/platform_shared_memory_region_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-shared_memory_win_unittest
  #  "${BASE_SOURCES_PATH}memory/shared_memory_win_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-ref_counted_memory_unittest
    "${BASE_SOURCES_PATH}memory/ref_counted_memory_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-shared_memory_mapping_unittest
    "${BASE_SOURCES_PATH}memory/shared_memory_mapping_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-ptr_util_unittest
    "${BASE_SOURCES_PATH}memory/ptr_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-aligned_memory_unittest
    "${BASE_SOURCES_PATH}memory/aligned_memory_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-shared_memory_region_unittest
    "${BASE_SOURCES_PATH}memory/shared_memory_region_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-memory_pressure_monitor_chromeos_unittest
  #  "${BASE_SOURCES_PATH}memory/memory_pressure_monitor_chromeos_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-shared_memory_hooks_unittest
    "${BASE_SOURCES_PATH}memory/shared_memory_hooks_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-memory_pressure_monitor_unittest
    "${BASE_SOURCES_PATH}memory/memory_pressure_monitor_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-ref_counted_unittest
    "${BASE_SOURCES_PATH}memory/ref_counted_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  # tests_add_executable(${ROOT_PROJECT_NAME}-weak_ptr_unittest
  #  "${BASE_SOURCES_PATH}memory/weak_ptr_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-memory_pressure_monitor_notifying_chromeos_unittest
  #  "${BASE_SOURCES_PATH}memory/memory_pressure_monitor_notifying_chromeos_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-weak_ptr_unittest
    "${BASE_SOURCES_PATH}memory/weak_ptr_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  # tests_add_executable(${ROOT_PROJECT_NAME}-ref_counted_unittest
  #  "${BASE_SOURCES_PATH}memory/ref_counted_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-shared_memory_unittest
    "${BASE_SOURCES_PATH}memory/shared_memory_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-protected_memory_unittest
    "${BASE_SOURCES_PATH}memory/protected_memory_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-memory_pressure_monitor_win_unittest
  #  "${BASE_SOURCES_PATH}memory/memory_pressure_monitor_win_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-singleton_unittest
    "${BASE_SOURCES_PATH}memory/singleton_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-base64url_unittest
    "${BASE_SOURCES_PATH}base64url_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-cpu_unittest
    "${BASE_SOURCES_PATH}cpu_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-security_unittest
    "${BASE_SOURCES_PATH}security_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-file_descriptor_watcher_posix_unittest
  #  "${BASE_SOURCES_PATH}files/file_descriptor_watcher_posix_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-file_path_watcher_unittest
    "${BASE_SOURCES_PATH}files/file_path_watcher_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-file_locking_unittest
    "${BASE_SOURCES_PATH}files/file_locking_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-dir_reader_posix_unittest
  #  "${BASE_SOURCES_PATH}files/dir_reader_posix_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-file_util_unittest
    "${BASE_SOURCES_PATH}files/file_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-file_enumerator_unittest
    "${BASE_SOURCES_PATH}files/file_enumerator_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-memory_mapped_file_unittest
    "${BASE_SOURCES_PATH}files/memory_mapped_file_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-important_file_writer_unittest
    "${BASE_SOURCES_PATH}files/important_file_writer_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-file_unittest
    "${BASE_SOURCES_PATH}files/file_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-scoped_temp_dir_unittest
    "${BASE_SOURCES_PATH}files/scoped_temp_dir_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-file_path_unittest
    "${BASE_SOURCES_PATH}files/file_path_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-file_proxy_unittest
    "${BASE_SOURCES_PATH}files/file_proxy_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-at_exit_unittest
    "${BASE_SOURCES_PATH}at_exit_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-cancelable_callback_unittest
    "${BASE_SOURCES_PATH}cancelable_callback_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO: ToolsSanityTest.DataRace
  # tools_sanity_unittest.cc:331: Failure
  # Death test: DataRace()
  #     Result: died but not with expected error.
  #   Expected: contains regular expression "1 race:base/tools_sanity_unittest.cc"
  # tests_add_executable(${ROOT_PROJECT_NAME}-tools_sanity_unittest
  #   "${BASE_SOURCES_PATH}tools_sanity_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-file_version_info_win_unittest
  #  "${BASE_SOURCES_PATH}file_version_info_win_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-callback_list_unittest
    "${BASE_SOURCES_PATH}callback_list_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-bind_unittest
    "${BASE_SOURCES_PATH}bind_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  if (NOT CMAKE_BUILD_TYPE MATCHES "Debug" )
    # NOTE: release builds must include valid build time
    tests_add_executable(${ROOT_PROJECT_NAME}-build_time_unittest
      "${BASE_SOURCES_PATH}build_time_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  endif()

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-device_util_unittest
  #  "${BASE_SOURCES_PATH}ios/device_util_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-crb_protocol_observers_unittest
  #  "${BASE_SOURCES_PATH}ios/crb_protocol_observers_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-weak_nsobject_unittest
  #  "${BASE_SOURCES_PATH}ios/weak_nsobject_unittest.mm" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sync_socket_unittest
    "${BASE_SOURCES_PATH}sync_socket_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-event_trace_controller_unittest
  #  "${BASE_SOURCES_PATH}win/event_trace_controller_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-hstring_reference_unittest
  #  "${BASE_SOURCES_PATH}win/hstring_reference_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-wmi_unittest
  #  "${BASE_SOURCES_PATH}win/wmi_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-scoped_variant_unittest
  #  "${BASE_SOURCES_PATH}win/scoped_variant_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-async_operation_unittest
  #  "${BASE_SOURCES_PATH}win/async_operation_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-language_selector_unittest
  #  "${BASE_SOURCES_PATH}win/embedded_i18n/language_selector_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-message_window_unittest
  #  "${BASE_SOURCES_PATH}win/message_window_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-winrt_storage_util_unittest
  #  "${BASE_SOURCES_PATH}win/winrt_storage_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-scoped_safearray_unittest
  #  "${BASE_SOURCES_PATH}win/scoped_safearray_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-core_winrt_util_unittest
  #  "${BASE_SOURCES_PATH}win/core_winrt_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-shortcut_unittest
  #  "${BASE_SOURCES_PATH}win/shortcut_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-reference_unittest
  #  "${BASE_SOURCES_PATH}win/reference_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-event_trace_provider_unittest
  #  "${BASE_SOURCES_PATH}win/event_trace_provider_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-i18n_unittest
  #  "${BASE_SOURCES_PATH}win/i18n_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-registry_unittest
  #  "${BASE_SOURCES_PATH}win/registry_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-win_includes_unittest
  #  "${BASE_SOURCES_PATH}win/win_includes_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-pe_image_unittest
  #  "${BASE_SOURCES_PATH}win/pe_image_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-com_init_check_hook_unittest
  #  "${BASE_SOURCES_PATH}win/com_init_check_hook_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-vector_unittest
  #  "${BASE_SOURCES_PATH}win/vector_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-object_watcher_unittest
  #  "${BASE_SOURCES_PATH}win/object_watcher_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-typed_event_handler_unittest
  #  "${BASE_SOURCES_PATH}win/typed_event_handler_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-startup_information_unittest
  #  "${BASE_SOURCES_PATH}win/startup_information_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-wrapped_window_proc_unittest
  #  "${BASE_SOURCES_PATH}win/wrapped_window_proc_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-enum_variant_unittest
  #  "${BASE_SOURCES_PATH}win/enum_variant_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-iunknown_impl_unittest
  #  "${BASE_SOURCES_PATH}win/iunknown_impl_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-scoped_winrt_initializer_unittest
  #  "${BASE_SOURCES_PATH}win/scoped_winrt_initializer_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-scoped_handle_unittest
  #  "${BASE_SOURCES_PATH}win/scoped_handle_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-win_util_unittest
  #  "${BASE_SOURCES_PATH}win/win_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-pe_image_test
  #  "${BASE_SOURCES_PATH}win/pe_image_test.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-scoped_hstring_unittest
  #  "${BASE_SOURCES_PATH}win/scoped_hstring_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-scoped_process_information_unittest
  #  "${BASE_SOURCES_PATH}win/scoped_process_information_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-event_trace_consumer_unittest
  #  "${BASE_SOURCES_PATH}win/event_trace_consumer_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-com_init_util_unittest
  #  "${BASE_SOURCES_PATH}win/com_init_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-scoped_bstr_unittest
  #  "${BASE_SOURCES_PATH}win/scoped_bstr_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-windows_version_unittest
  #  "${BASE_SOURCES_PATH}win/windows_version_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sequence_token_unittest
    "${BASE_SOURCES_PATH}sequence_token_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  # tests_add_executable(${ROOT_PROJECT_NAME}-callback_unittest
  #  "${BASE_SOURCES_PATH}callback_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO:
  # [ RUN      ] NativeLibraryTest.LoadLibrary
  # native_library_unittest.cc(89) Check failed: library_.
  # NEED TO BUILD FILE base/test/test_shared_library.cc
  # tests_add_executable(${ROOT_PROJECT_NAME}-native_library_unittest
  #   "${BASE_SOURCES_PATH}native_library_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-stl_util_unittest
    "${BASE_SOURCES_PATH}stl_util_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-crc32_unittest
    "${BASE_SOURCES_PATH}crc32_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-sys_info_unittest
    "${BASE_SOURCES_PATH}system/sys_info_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-system_monitor_unittest
    "${BASE_SOURCES_PATH}system/system_monitor_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-feature_list_unittest
    "${BASE_SOURCES_PATH}feature_list_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-scoped_native_library_unittest
    "${BASE_SOURCES_PATH}scoped_native_library_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-child_process_unittest
  #  "${BASE_SOURCES_PATH}android/child_process_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-jni_array_unittest
  #  "${BASE_SOURCES_PATH}android/jni_array_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-android_image_reader_compat_unittest
  #  "${BASE_SOURCES_PATH}android/android_image_reader_compat_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-scoped_java_ref_unittest
  #  "${BASE_SOURCES_PATH}android/scoped_java_ref_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-reached_addresses_bitset_unittest
  #  "${BASE_SOURCES_PATH}android/reached_addresses_bitset_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-path_utils_unittest
  #  "${BASE_SOURCES_PATH}android/path_utils_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-library_prefetcher_unittest
  #  "${BASE_SOURCES_PATH}android/library_loader/library_prefetcher_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-library_loader_hooks_unittest
  #  "${BASE_SOURCES_PATH}android/library_loader/library_loader_hooks_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-orderfile_instrumentation_perftest
  #  "${BASE_SOURCES_PATH}android/orderfile/orderfile_instrumentation_perftest.cc" "${GTEST_TEST_ARGS}" "${test_main_perftest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-orderfile_call_graph_instrumentation_perftest
  #  "${BASE_SOURCES_PATH}android/orderfile/orderfile_call_graph_instrumentation_perftest.cc" "${GTEST_TEST_ARGS}" "${test_main_perftest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-jni_string_unittest
  #  "${BASE_SOURCES_PATH}android/jni_string_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-content_uri_utils_unittest
  #  "${BASE_SOURCES_PATH}android/content_uri_utils_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-unguessable_token_android_unittest
  #  "${BASE_SOURCES_PATH}android/unguessable_token_android_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-jni_android_unittest
  #  "${BASE_SOURCES_PATH}android/jni_android_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-application_status_listener_unittest
  #  "${BASE_SOURCES_PATH}android/application_status_listener_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")
  #
  #tests_add_executable(${ROOT_PROJECT_NAME}-sys_utils_unittest
  #  "${BASE_SOURCES_PATH}android/sys_utils_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  # tests_add_executable(${ROOT_PROJECT_NAME}-thread_annotations_unittest
  #  "${BASE_SOURCES_PATH}thread_annotations_unittest.nc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-json_writer_unittest
    "${BASE_SOURCES_PATH}json/json_writer_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-json_value_converter_unittest
    "${BASE_SOURCES_PATH}json/json_value_converter_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-json_value_serializer_unittest
    "${BASE_SOURCES_PATH}json/json_value_serializer_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-json_parser_unittest
    "${BASE_SOURCES_PATH}json/json_parser_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-json_perftest
  #  "${BASE_SOURCES_PATH}json/json_perftest.cc" "${GTEST_TEST_ARGS}" "${test_main_perftest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-json_reader_unittest
    "${BASE_SOURCES_PATH}json/json_reader_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-string_escape_unittest
    "${BASE_SOURCES_PATH}json/string_escape_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-time_unittest
    "${BASE_SOURCES_PATH}time/time_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-pr_time_unittest
    "${BASE_SOURCES_PATH}time/pr_time_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # TODO
  #tests_add_executable(${ROOT_PROJECT_NAME}-time_win_unittest
  #  "${BASE_SOURCES_PATH}time/time_win_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-not_fn_unittest
    "${BASE_SOURCES_PATH}functional/not_fn_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-invoke_unittest
    "${BASE_SOURCES_PATH}functional/invoke_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-identity_unittest
    "${BASE_SOURCES_PATH}functional/identity_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-command_line_unittest
    "${BASE_SOURCES_PATH}command_line_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  tests_add_executable(${ROOT_PROJECT_NAME}-token_unittest
    "${BASE_SOURCES_PATH}token_unittest.cc" "${GTEST_TEST_ARGS}" "${test_main_gtest}")

  # "i18n" is one of test program names
  add_custom_command( TARGET ${ROOT_PROJECT_NAME}-i18n POST_BUILD
                      COMMAND ${CMAKE_COMMAND} -E copy_directory
                          ${CMAKE_CURRENT_SOURCE_DIR}/data
                          ${CMAKE_CURRENT_BINARY_DIR}/${ROOT_PROJECT_NAME}-tests )

  enable_testing()
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
