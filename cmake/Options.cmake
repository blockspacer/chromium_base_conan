include_guard( DIRECTORY )

set(BASE_USE_PARTITION_ALLOCATOR TRUE CACHE BOOL "BASE_USE_PARTITION_ALLOCATOR")

set(ENABLE_UKM FALSE CACHE BOOL "ENABLE_UKM")

set(USE_ALLOC_SHIM FALSE CACHE BOOL "USE_ALLOC_SHIM")

set(USE_DEB_ALLOC FALSE CACHE BOOL "USE_DEB_ALLOC")

set(BASE_USE_JSON TRUE CACHE BOOL "BASE_USE_JSON")

set(BASE_SOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/base/)

set(BUILD_CONFIG_PARENT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/codegen/build/) # TODO: use shared BUILD_CONFIG

set(BUILDFLAGS_GENERATORS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/codegen/)

option(ENABLE_VALGRIND
  "Enable valgrind" OFF)

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
