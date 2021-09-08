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
set(USE_PARTITION_ALLOC ${BASE_USE_PARTITION_ALLOCATOR})
set(USE_PARTITION_ALLOCATOR ${BASE_USE_PARTITION_ALLOCATOR})

option(ENABLE_TESTS "Enable tests" OFF)

option(ENABLE_WEB_PTHREADS "ENABLE_WEB_PTHREADS" OFF)

set(USE_TEST_SUPPORT TRUE CACHE BOOL "USE_TEST_SUPPORT")

set(ENABLE_UKM FALSE CACHE BOOL "ENABLE_UKM")

set(can_unwind_with_cfi_table FALSE CACHE BOOL "can_unwind_with_cfi_table")

set(USE_ALLOC_SHIM FALSE CACHE BOOL "USE_ALLOC_SHIM")
set(USE_ALLOCATOR_SHIM ${USE_ALLOC_SHIM})
set(use_allocator_shim ${USE_ALLOC_SHIM})

set(use_clang_profiling FALSE CACHE BOOL "use_clang_profiling")

set(USE_DEB_ALLOC FALSE CACHE BOOL "USE_DEB_ALLOC")

set(BASE_USE_JSON TRUE CACHE BOOL "BASE_USE_JSON")

set(USE_NONSFI FALSE CACHE BOOL "USE_NONSFI")
set(IS_NONSFI ${USE_NONSFI})
set(TARGET_NONSFI ${USE_NONSFI})

set(USE_NACL FALSE CACHE BOOL "USE_GLIB")
set(IS_NACL ${USE_NACL})
set(TARGET_NACL ${USE_NACL})

set(TARGET_NACL_NONSFI FALSE)
if (TARGET_NACL AND TARGET_NONSFI)
  set(TARGET_NACL_NONSFI TRUE)
endif()

set(USE_GLIB FALSE CACHE BOOL "USE_GLIB")

# Set to true to disable COM init check hooks.
set(com_init_check_hook_disabled FALSE CACHE BOOL "com_init_check_hook_disabled")

# Set to true to enable mutex priority inheritance. See the comments in
# LockImpl::PriorityInheritanceAvailable() in lock_impl_posix.cc for the
# platform requirements to safely enable priority inheritance.
set(enable_mutex_priority_inheritance FALSE CACHE BOOL "enable_mutex_priority_inheritance")

# Set to true to use BackupRefPtr as the implementation of CheckedPtr.
# Optionally can be controlled (partially disabled) at run-time.
# Optionally can place ref count at the end of each allocation.
set(use_backup_ref_ptr FALSE CACHE BOOL "use_backup_ref_ptr")
set(enable_runtime_backup_ref_ptr_control FALSE CACHE BOOL "enable_runtime_backup_ref_ptr_control")
set(is_ref_count_at_end_of_allocation FALSE CACHE BOOL "is_ref_count_at_end_of_allocation")
set(enable_backup_ref_ptr_slow_checks FALSE CACHE BOOL "enable_backup_ref_ptr_slow_checks")
set(make_gigacage_granularity_partition_page_size TRUE CACHE BOOL "make_gigacage_granularity_partition_page_size")

# Tracing support requires //third_party/perfetto, which is not available in
# libchrome (CrOS's version of //base). This flag can disable tracing support
# altogether, in which case all tracing instrumentation in //base becomes a
# no-op.
# TODO(crbug/1065905): Add dependency on perfetto to support typed events.
set(ENABLE_BASE_TRACING TRUE CACHE BOOL "ENABLE_BASE_TRACING")

set(ENABLE_BORINGSSL FALSE CACHE BOOL "ENABLE_BORINGSSL")

# Whether OPTIONAL_TRACE_EVENT macros are included in the build or not.
# Disabled by default on Android and ChromeOS due to binary size impact,
# enabled everywhere else.
set(OPTIONAL_TRACE_EVENTS_ENABLED TRUE CACHE BOOL "OPTIONAL_TRACE_EVENTS_ENABLED")
set(optional_trace_events_enabled ${OPTIONAL_TRACE_EVENTS_ENABLED})

set(strip_absolute_paths_from_debug_symbols FALSE CACHE BOOL "strip_absolute_paths_from_debug_symbols")

set(use_custom_libcxx FALSE CACHE BOOL "use_custom_libcxx")

# Switches the TRACE_EVENT instrumentation from base's TraceLog implementation
# to //third_party/perfetto's client library. Not implemented yet, currently a
# no-op to set up trybot infrastructure.
# TODO(crbug/1006769): Switch to perfetto's client library.
set(USE_PERFETTO_CLIENT_LIBRARY FALSE CACHE BOOL "USE_PERFETTO_CLIENT_LIBRARY")
set(use_perfetto_client_library ${USE_PERFETTO_CLIENT_LIBRARY})

# Enable more trace events. Disabled by default due to binary size impact,
# but highly recommended for local development.
set(EXTENDED_TRACING_ENABLED FALSE CACHE BOOL "EXTENDED_TRACING_ENABLED")

set(IPC_MESSAGE_LOG_ENABLED FALSE CACHE BOOL "IPC_MESSAGE_LOG_ENABLED")

set(BASE_SOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/base/)

set(EXTENSIONS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extensions/)

set(MOJO_SOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extensions/mojo/)

# TODO: generate code from ".mojom" files
set(MOJO_GENERATOR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extensions/mojo/public/tools/bindings/mojom_bindings_generator.py)

set(IPC_SOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extensions/ipc/)

set(BASIC_SOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extensions/basic)

set(TESTING_SOURCES_PATH ${EXTENSIONS_PATH}testing/)

# TODO: use shared BUILD_CONFIG
set(BUILD_CONFIG_PARENT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/codegen/build/)

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

option(USE_OPENSSL
  "Enable openssl in crypto lib" ON)
message(STATUS "USE_OPENSSL=${USE_OPENSSL}")

cmake_dependent_option(USE_NSS_CERTS
  "NSS CERTS"
  ON
  "NOT USE_OPENSSL;\
TARGET_LINUX;\
TARGET_CHROMEOS"
  # If the condition above is not true
  OFF)
message(STATUS "USE_NSS_CERTS=${USE_NSS_CERTS}")

cmake_dependent_option(ALLOCATOR_TCMALLOC
  "Disable custom allocators (use glibc on linux)"
  ON
  "NOT ENABLE_ASAN;\
NOT ENABLE_TSAN;\
NOT ENABLE_MSAN;\
NOT ENABLE_UBSAN;\
NOT ENABLE_VALGRIND"
  # If the condition above is not true
  OFF)

message(STATUS
  "ALLOCATOR_TCMALLOC=${ALLOCATOR_TCMALLOC}")

cmake_dependent_option(ALLOCATOR_NONE
  "Disable custom allocators (use glibc on linux)"
  OFF
  "NOT ENABLE_ASAN;\
NOT ENABLE_TSAN;\
NOT ENABLE_MSAN;\
NOT ENABLE_UBSAN;\
NOT ENABLE_VALGRIND"
  # If the condition above is not true
  ON)

message(STATUS
  "ALLOCATOR_NONE=${ALLOCATOR_NONE}")
