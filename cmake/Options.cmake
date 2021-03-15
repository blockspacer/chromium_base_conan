include_guard( DIRECTORY )

# Helper module for selecting option based on multiple values. Module help:
# https://cmake.org/cmake/help/latest/module/CMakeDependentOption.html
include(CMakeDependentOption)

# used by https://docs.conan.io/en/latest/developing_packages/workspaces.html
get_filename_component(LOCAL_BUILD_ABSOLUTE_ROOT_PATH
  "${PACKAGE_chromium_base_SRC}"
  ABSOLUTE)
if(EXISTS "${LOCAL_BUILD_ABSOLUTE_ROOT_PATH}")
  # path to Find*.cmake file
  list(PREPEND CMAKE_MODULE_PATH "${LOCAL_BUILD_ABSOLUTE_ROOT_PATH}/cmake")
endif()

set(BASE_USE_PARTITION_ALLOCATOR TRUE CACHE BOOL "BASE_USE_PARTITION_ALLOCATOR")

option(ENABLE_TESTS "Enable tests" OFF)

option(ENABLE_WEB_PTHREADS "ENABLE_WEB_PTHREADS" OFF)

set(USE_TEST_SUPPORT TRUE CACHE BOOL "USE_TEST_SUPPORT")

set(ENABLE_UKM FALSE CACHE BOOL "ENABLE_UKM")

set(USE_ALLOC_SHIM FALSE CACHE BOOL "USE_ALLOC_SHIM")

set(USE_DEB_ALLOC FALSE CACHE BOOL "USE_DEB_ALLOC")

set(BASE_USE_JSON TRUE CACHE BOOL "BASE_USE_JSON")

set(USE_NACL FALSE CACHE BOOL "USE_GLIB")

set(USE_GLIB FALSE CACHE BOOL "USE_GLIB")

set(ENABLE_BASE_TRACING TRUE CACHE BOOL "ENABLE_BASE_TRACING")

set(USE_PERFETTO_CLIENT_LIBRARY FALSE CACHE BOOL "USE_PERFETTO_CLIENT_LIBRARY")

# Enable more trace events. Disabled by default due to binary size impact,
# but highly recommended for local development.
set(EXTENDED_TRACING_ENABLED FALSE CACHE BOOL "EXTENDED_TRACING_ENABLED")

set(BASE_SOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/base/)

set(EXTENSIONS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extensions/)

set(TESTING_SOURCES_PATH ${EXTENTIONS_PATH}testing/)

set(BUILD_CONFIG_PARENT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/codegen/build/) # TODO: use shared BUILD_CONFIG

set(BUILDFLAGS_GENERATORS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/codegen/)

option(ENABLE_VALGRIND
  "Enable valgrind" OFF)

# TODO: __do_global_dtors_aux, base::debug::CollectStackTrace
option(ENABLE_VALGRIND_TESTS
  "Enable valgrind for unit tests" OFF)

option(COMPILE_WITH_LLVM_TOOLS
  "Enable clang from llvm_tools (conan package)" OFF)

# see https://github.com/Ericsson/codechecker/blob/master/tools/report-converter/README.md#undefined-behaviour-sanitizer
# NOTE: Compile with -g and -fno-omit-frame-pointer
# to get proper debug information in your binary.
# NOTE: Run your program with environment variable UBSAN_OPTIONS=print_stacktrace=1.
# see https://github.com/google/sanitizers/wiki/SanitizerCommonFlags
option(ENABLE_UBSAN
  "Enable Undefined Behaviour Sanitizer" OFF)

# see https://github.com/google/sanitizers/wiki/AddressSanitizerLeakSanitizer
# see https://github.com/Ericsson/codechecker/blob/master/tools/report-converter/README.md#address-sanitizer
# NOTE: Compile with -g and -fno-omit-frame-pointer
# to get proper debug information in your binary.
# NOTE: use ASAN_OPTIONS=detect_leaks=1 LSAN_OPTIONS=suppressions=suppr.txt
# NOTE: You need the ASAN_OPTIONS=symbolize=1
# to turn on resolving addresses in object code
# to source code line numbers and filenames.
# This option is implicit for Clang but it won't do any harm.
# see https://github.com/google/sanitizers/wiki/SanitizerCommonFlags
option(ENABLE_ASAN
  "Enable Address Sanitizer" OFF)

# see https://github.com/Ericsson/codechecker/blob/master/tools/report-converter/README.md#memory-sanitizer
# NOTE: Compile with -g and -fno-omit-frame-pointer
# to get proper debug information in your binary.
option(ENABLE_MSAN
  "Enable Memory Sanitizer" OFF)

# see https://github.com/Ericsson/codechecker/blob/master/tools/report-converter/README.md#thread-sanitizer
# NOTE: Compile with -g
# to get proper debug information in your binary.
option(ENABLE_TSAN
  "Enable Thread Sanitizer" OFF)

cmake_dependent_option(ALLOCATOR_TCMALLOC
  "Disable custom allocators (use glibc on linux)"
  ON
  "NOT ENABLE_ASAN \
  AND NOT ENABLE_TSAN \
  AND NOT ENABLE_MSAN \
  AND NOT ENABLE_UBSAN \
  AND NOT ENABLE_VALGRIND"
  OFF)

message(STATUS
  "ALLOCATOR_TCMALLOC=${ALLOCATOR_TCMALLOC}")

cmake_dependent_option(ALLOCATOR_NONE
  "Disable custom allocators (use glibc on linux)"
  ON
  "ENABLE_ASAN \
  OR ENABLE_TSAN \
  OR ENABLE_MSAN \
  OR ENABLE_UBSAN \
  OR ENABLE_VALGRIND"
  OFF)

message(STATUS
  "ALLOCATOR_NONE=${ALLOCATOR_NONE}")
