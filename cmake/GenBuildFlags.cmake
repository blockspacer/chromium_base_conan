include_guard( DIRECTORY )

# https://cmake.org/cmake/help/latest/module/FindPythonInterp.html
find_package(PythonInterp 2.7 REQUIRED)

find_package(Git REQUIRED)

# NOTE: To speed up builds pass to cmake -DBASE_NEED_GEN_BUILD_DATE=FALSE
# Otherwise code will be FULLY recompiled on each build.
set(BASE_NEED_GEN_BUILD_DATE FALSE CACHE BOOL "BASE_NEED_GEN_BUILD_DATE")

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/base/generated_build_date.h")
  set(BASE_NEED_GEN_BUILD_DATE TRUE)
  message(STATUS "Unable to find required file: generated_build_date.h")
  message(STATUS "File will be re-generated: generated_build_date.h")
endif()

if(BASE_NEED_GEN_BUILD_DATE)
  if(NOT GIT_EXECUTABLE)
    MESSAGE(FATAL_ERROR "Python not found! Aborting...")
  endif(NOT GIT_EXECUTABLE)
  # NOTE: git timestamp can be populated only when WORKING_DIRECTORY
  # points to valid git repo
  set(TIMESTAMP_FROM_GIT FALSE)
  if(TIMESTAMP_FROM_GIT)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} log -n1 --format="%at"
      # NOTE: must point to folder containing .git
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../.."
      OUTPUT_VARIABLE _build_timestamp
      #ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_VARIABLE _ERROR_VARIABLE
      RESULT_VARIABLE retcode
    )
    if(NOT "${retcode}" STREQUAL "0")
      message( FATAL_ERROR "Bad exit status ${_ERROR_VARIABLE}")
    endif()
  else()
    # %s - Seconds since midnight (UTC) 1-Jan-1970 (UNIX time).
    # see https://gitlab.kitware.com/cmake/cmake/blob/master/Help/command/string.rst
    string(TIMESTAMP _build_timestamp "%s")
  endif(TIMESTAMP_FROM_GIT)
endif(BASE_NEED_GEN_BUILD_DATE)

#
if(BASE_NEED_GEN_BUILD_DATE)
  string(REPLACE "\"" "" _build_timestamp ${_build_timestamp})
  #message(FATAL_ERROR ${_build_timestamp})

	if(NOT PYTHON_EXECUTABLE)
    MESSAGE(FATAL_ERROR "Python not found! Aborting...")
  endif(NOT PYTHON_EXECUTABLE)

  # PRE-GENERATION GENERATED_BUILD_DATE.H (NEEDED BY "build_time.cc")
  # generates "base/generated_build_date.h"
  execute_process(
    COMMAND "${PYTHON_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/codegen/write_build_date_header.py" "generated_build_date.h" "${_build_timestamp}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/base"
    TIMEOUT 7200 # sec
    RESULT_VARIABLE retcode
    OUTPUT_VARIABLE _OUTPUT_VARIABLE
    ERROR_VARIABLE _ERROR_VARIABLE)
    if(NOT "${retcode}" STREQUAL "0")
      message( FATAL_ERROR "Bad exit status ${retcode} ${_ERROR_VARIABLE} ${_OUTPUT_VARIABLE}")
    endif()
endif(BASE_NEED_GEN_BUILD_DATE)

# Compile with Control Flow Integrity to protect virtual calls and casts.
# See http://clang.llvm.org/docs/ControlFlowIntegrity.html
configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/cfi_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}cfi_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/cfi_buildflags.tmp)

if(NOT DEFINED USE_ALLOC_SHIM)
  message(FATAL_ERROR "define USE_ALLOC_SHIM")
endif()
#
set(BUILDFLAG_INTERNAL_ENABLE_MUTEX_PRIORITY_INHERITANCE "0")
if(enable_mutex_priority_inheritance)
  set(BUILDFLAG_INTERNAL_ENABLE_MUTEX_PRIORITY_INHERITANCE "1")
endif(enable_mutex_priority_inheritance)
#
set(BUILDFLAG_INTERNAL_USE_BACKUP_REF_PTR "0")
if(use_backup_ref_ptr)
  set(BUILDFLAG_INTERNAL_USE_BACKUP_REF_PTR "1")
endif(use_backup_ref_ptr)
#
set(BUILDFLAG_INTERNAL_USE_PARTITION_ALLOC "0")
if(USE_PARTITION_ALLOC)
  set(BUILDFLAG_INTERNAL_USE_PARTITION_ALLOC "1")
endif(USE_PARTITION_ALLOC)
#
set(BUILDFLAG_INTERNAL_REF_COUNT_AT_END_OF_ALLOCATION "0")
if(is_ref_count_at_end_of_allocation)
  set(BUILDFLAG_INTERNAL_REF_COUNT_AT_END_OF_ALLOCATION "1")
endif(is_ref_count_at_end_of_allocation)
#
set(BUILDFLAG_INTERNAL_ENABLE_RUNTIME_BACKUP_REF_PTR_CONTROL "0")
if(enable_runtime_backup_ref_ptr_control)
  set(BUILDFLAG_INTERNAL_ENABLE_RUNTIME_BACKUP_REF_PTR_CONTROL "1")
endif(enable_runtime_backup_ref_ptr_control)
#
set(BUILDFLAG_INTERNAL_ENABLE_BACKUP_REF_PTR_SLOW_CHECKS "0")
if(enable_backup_ref_ptr_slow_checks)
  set(BUILDFLAG_INTERNAL_ENABLE_BACKUP_REF_PTR_SLOW_CHECKS "1")
endif(enable_backup_ref_ptr_slow_checks)
#
set(BUILDFLAG_INTERNAL_MAKE_GIGACAGE_GRANULARITY_PARTITION_PAGE_SIZE "0")
if(make_gigacage_granularity_partition_page_size)
  set(BUILDFLAG_INTERNAL_MAKE_GIGACAGE_GRANULARITY_PARTITION_PAGE_SIZE "1")
endif(make_gigacage_granularity_partition_page_size)
#
set(BUILDFLAG_INTERNAL_USE_ALLOCATOR_SHIM "0")
if(USE_ALLOC_SHIM)
  set(BUILDFLAG_INTERNAL_USE_ALLOCATOR_SHIM "1")
endif(USE_ALLOC_SHIM)
set(BUILDFLAG_INTERNAL_USE_TCMALLOC "0")
if(ALLOCATOR_TCMALLOC)
  set(BUILDFLAG_INTERNAL_USE_TCMALLOC "1")
endif(ALLOCATOR_TCMALLOC)
set(BUILDFLAG_INTERNAL_USE_PARTITION_ALLOC_AS_MALLOC "0")
set(BUILDFLAG_INTERNAL_USE_NEW_TCMALLOC "0")
if(TARGET_LINUX OR TARGET_EMSCRIPTEN)
  set(BUILDFLAG_INTERNAL_USE_NEW_TCMALLOC "1")
endif()
#
configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/allocator_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}allocator/buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/allocator_buildflags.tmp)

if(TARGET_WINDOWS)
  configure_file_if_changed(
    INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/base_win_buildflags.h.inc
    OUTPUT ${BASE_SOURCES_PATH}win/base_win_buildflags.h
    TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/base_win_buildflags.tmp)
endif(TARGET_WINDOWS)

string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)

# NOTE: Prefer to use Profiling with Release builds.
# In order to enable cpu profiling, run with the environment variable CPUPROFILE
# and use "profiling-flush" flag
set(ENABLE_LOCATION_SOURCE "1")
set(USE_PROFILING "0")
if(ALLOCATOR_TCMALLOC)
  set(USE_PROFILING "0") # TODO support profiling
endif(ALLOCATOR_TCMALLOC)
set(BUILDFLAG_INTERNAL_CAN_UNWIND_WITH_FRAME_POINTERS "0")
if(NOT TARGET_EMSCRIPTEN AND IS_DEBUG)
  set(BUILDFLAG_INTERNAL_CAN_UNWIND_WITH_FRAME_POINTERS "1")
endif()
set(EXCLUDE_UNWIND_TABLES "0")
# TODO: enable for android if using_sanitizer || enable_profiling || is_debug
set(BUILDFLAG_INTERNAL_CAN_UNWIND_WITH_CFI_TABLE "0")
if(NOT TARGET_EMSCRIPTEN AND can_unwind_with_cfi_table)
  set(BUILDFLAG_INTERNAL_CAN_UNWIND_WITH_CFI_TABLE "1")
endif()
set(ENABLE_MEMORY_TASK_PROFILER "0")
if(USE_ALLOC_SHIM AND IS_DEBUG)
  set(ENABLE_MEMORY_TASK_PROFILER "1")
endif()
set(ENABLE_GDBINIT_WARNING "0")
set(ENABLE_LLDBINIT_WARNING "0")
if(NOT TARGET_EMSCRIPTEN AND IS_DEBUG AND (strip_absolute_paths_from_debug_symbols OR use_custom_libcxx))
  set(ENABLE_GDBINIT_WARNING "1")
endif()
if(NOT TARGET_EMSCRIPTEN AND IS_DEBUG AND strip_absolute_paths_from_debug_symbols AND is_mac)
  set(ENABLE_LLDBINIT_WARNING "1")
endif()
set(IS_UNSAFE_DEVELOPER_BUILD "0")
#if(TARGET_LINUX AND IS_DEBUG)
#  set(IS_UNSAFE_DEVELOPER_BUILD "1")
#endif()
# `NOTREACHED()` will log without crash
set(ENABLE_LOG_ERROR_NOT_REACHED "1")
set(FROM_HERE_USES_LOCATION_BUILTINS "1")
set(EXPENSIVE_DCHECKS_ARE_ON "0")
if(IS_DEBUG)
  set(ENABLE_LOG_ERROR_NOT_REACHED "0")
  set(EXPENSIVE_DCHECKS_ARE_ON "1")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tracing_buildflags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/profiler_buildflags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/mojo_buildflags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ipc_buildflags.cmake)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/clang_profiling_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}/clang_profiling_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/clang_profiling_buildflags.tmp)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/branding_buildflags.h.inc
  OUTPUT ${EXTENSIONS_PATH}/build/branding_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/branding_buildflags.tmp)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/chromecast_buildflags.h.inc
  OUTPUT ${EXTENSIONS_PATH}/build/chromecast_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/chromecast_buildflags.tmp)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/chromeos_buildflags.h.inc
  OUTPUT ${EXTENSIONS_PATH}/build/chromeos_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/chromeos_buildflags.tmp)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/logging_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}/logging_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/logging_buildflags.tmp)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/debugging_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}debug/debugging_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/debugging_buildflags.tmp)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/synchronization_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}synchronization/synchronization_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/synchronization_buildflags.tmp)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/protected_memory_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}memory/protected_memory_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/protected_memory_buildflags.tmp)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/partition_alloc_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}partition_alloc_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/partition_alloc_buildflags.tmp)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/clang_coverage_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}clang_coverage_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/clang_coverage_buildflags.tmp)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/sanitizer_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}sanitizer_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/sanitizer_buildflags.tmp)

include(CheckCXXSourceCompiles)
include(CheckCXXSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFileCXX)
include(CheckSymbolExists)
include(CheckTypeSize)
include(CheckCXXCompilerFlag)

if (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
  CHECK_INCLUDE_FILE_CXX(malloc_np.h BASIC_USE_JEMALLOC)
else()
  CHECK_INCLUDE_FILE_CXX(jemalloc/jemalloc.h BASIC_USE_JEMALLOC)
endif()

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
  # clang only rejects unknown warning flags if -Werror=unknown-warning-option
  # is also specified.
  check_cxx_compiler_flag(
    -Werror=unknown-warning-option
    COMPILER_HAS_UNKNOWN_WARNING_OPTION)
  if (COMPILER_HAS_UNKNOWN_WARNING_OPTION)
    set(CMAKE_REQUIRED_FLAGS
      "${CMAKE_REQUIRED_FLAGS} -Werror=unknown-warning-option")
  endif()

  check_cxx_compiler_flag(-Wshadow-local COMPILER_HAS_W_SHADOW_LOCAL)
  check_cxx_compiler_flag(
    -Wshadow-compatible-local
    COMPILER_HAS_W_SHADOW_COMPATIBLE_LOCAL)
  if (COMPILER_HAS_W_SHADOW_LOCAL AND COMPILER_HAS_W_SHADOW_COMPATIBLE_LOCAL)
    set(BASIC_HAVE_SHADOW_LOCAL_WARNINGS ON)
    list(APPEND BASIC_CXX_FLAGS -Wshadow-compatible-local)
  endif()

  check_cxx_compiler_flag(-Wnoexcept-type COMPILER_HAS_W_NOEXCEPT_TYPE)
  if (COMPILER_HAS_W_NOEXCEPT_TYPE)
    list(APPEND BASIC_CXX_FLAGS -Wno-noexcept-type)
  endif()

  check_cxx_compiler_flag(
      -Wnullability-completeness
      COMPILER_HAS_W_NULLABILITY_COMPLETENESS)
  if (COMPILER_HAS_W_NULLABILITY_COMPLETENESS)
    list(APPEND BASIC_CXX_FLAGS -Wno-nullability-completeness)
  endif()

  check_cxx_compiler_flag(
      -Winconsistent-missing-override
      COMPILER_HAS_W_INCONSISTENT_MISSING_OVERRIDE)
  if (COMPILER_HAS_W_INCONSISTENT_MISSING_OVERRIDE)
    list(APPEND BASIC_CXX_FLAGS -Wno-inconsistent-missing-override)
  endif()

  check_cxx_compiler_flag(-faligned-new COMPILER_HAS_F_ALIGNED_NEW)
  if (COMPILER_HAS_F_ALIGNED_NEW)
    list(APPEND BASIC_CXX_FLAGS -faligned-new)
  endif()

  check_cxx_compiler_flag(-fopenmp COMPILER_HAS_F_OPENMP)
  if (COMPILER_HAS_F_OPENMP)
      list(APPEND BASIC_CXX_FLAGS -fopenmp)
  endif()
endif()

set(BASIC_ORIGINAL_CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS}")
string(REGEX REPLACE
  "-std=(c|gnu)\\+\\+.."
  ""
  CMAKE_REQUIRED_FLAGS
  "${CMAKE_REQUIRED_FLAGS}")

check_symbol_exists(pthread_atfork pthread.h BASIC_HAVE_PTHREAD_ATFORK)

check_symbol_exists(accept4 sys/socket.h BASIC_HAVE_ACCEPT4)
check_symbol_exists(getrandom sys/random.h BASIC_HAVE_GETRANDOM)
check_symbol_exists(preadv sys/uio.h BASIC_HAVE_PREADV)
check_symbol_exists(pwritev sys/uio.h BASIC_HAVE_PWRITEV)
check_symbol_exists(clock_gettime time.h BASIC_HAVE_CLOCK_GETTIME)
check_symbol_exists(pipe2 unistd.h BASIC_HAVE_PIPE2)
check_symbol_exists(sendmmsg sys/socket.h BASIC_HAVE_SENDMMSG)
check_symbol_exists(recvmmsg sys/socket.h BASIC_HAVE_RECVMMSG)

check_function_exists(malloc_usable_size BASIC_HAVE_MALLOC_USABLE_SIZE)

set(CMAKE_REQUIRED_FLAGS "${BASIC_ORIGINAL_CMAKE_REQUIRED_FLAGS}")

check_cxx_source_compiles("
  #pragma GCC diagnostic error \"-Wattributes\"
  extern \"C\" void (*test_ifunc(void))() { return 0; }
  void func() __attribute__((ifunc(\"test_ifunc\")));
  int main() { return 0; }"
  BASIC_HAVE_IFUNC
)
check_cxx_source_compiles("
  #include <type_traits>
  const bool val = std::is_trivially_copyable<bool>::value;
  int main() { return 0; }"
  BASIC_HAVE_STD__IS_TRIVIALLY_COPYABLE
)
check_cxx_source_runs("
  int main(int, char**) {
    char buf[64] = {0};
    unsigned long *ptr = (unsigned long *)(buf + 1);
    *ptr = 0xdeadbeef;
    return (*ptr & 0xff) == 0xef ? 0 : 1;
  }"
  BASIC_HAVE_UNALIGNED_ACCESS
)
check_cxx_source_compiles("
  int main(int argc, char** argv) {
    unsigned size = argc;
    char data[size];
    return 0;
  }"
  BASIC_HAVE_VLA
)
check_cxx_source_runs("
  extern \"C\" int BASIC_example_undefined_weak_symbol() __attribute__((weak));
  int main(int argc, char** argv) {
    auto f = BASIC_example_undefined_weak_symbol; // null pointer
    return f ? f() : 0; // must compile, link, and run with null pointer
  }"
  BASIC_HAVE_WEAK_SYMBOLS
)
check_cxx_source_runs("
  #include <dlfcn.h>
  int main() {
    void *h = dlopen(\"linux-vdso.so.1\", RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
    if (h == nullptr) {
      return -1;
    }
    dlclose(h);
    return 0;
  }"
  BASIC_HAVE_LINUX_VDSO
)

check_type_size(__int128 INT128_SIZE LANGUAGE CXX)
if (NOT INT128_SIZE STREQUAL "")
  set(BASIC_HAVE_INT128_T ON)
  check_cxx_source_compiles("
    #include <functional>
    #include <type_traits>
    #include <utility>
    static_assert(
      ::std::is_same<::std::make_signed<unsigned __int128>::type,
                     __int128>::value,
      \"signed form of 'unsigned __uint128' must be '__int128'.\");
    static_assert(
        sizeof(::std::hash<__int128>{}(0)) > 0, \
        \"std::hash<__int128> is disabled.\");
    int main() { return 0; }"
    HAVE_INT128_TRAITS
  )
  if (HAVE_INT128_TRAITS)
    set(BASIC_SUPPLY_MISSING_INT128_TRAITS OFF)
  else()
    set(BASIC_SUPPLY_MISSING_INT128_TRAITS ON)
  endif()
endif()

check_cxx_source_runs("
  #include <cstddef>
  #include <cwchar>
  int main(int argc, char** argv) {
    return wcstol(L\"01\", nullptr, 10) == 1 ? 0 : 1;
  }"
  BASIC_HAVE_WCHAR_SUPPORT
)

check_cxx_source_compiles("
  #include <ext/random>
  int main(int argc, char** argv) {
    __gnu_cxx::sfmt19937 rng;
    return 0;
  }"
  BASIC_HAVE_EXTRANDOM_SFMT19937
)

check_cxx_source_compiles("
  #include <type_traits>
  #if !_LIBCPP_VERSION
  #error No libc++
  #endif
  int main() { return 0; }"
  BASIC_USE_LIBCPP
)

check_cxx_source_compiles("
  #include <type_traits>
  #if !__GLIBCXX__
  #error No libstdc++
  #endif
  int main() { return 0; }"
  BASIC_USE_LIBSTDCPP
)

# Probe for coroutine TS support
find_package(Coroutines COMPONENTS Experimental Final)
message(STATUS "_CXX_COROUTINES_AWAIT=${_CXX_COROUTINES_AWAIT}")
message(STATUS "_CXX_COROUTINES_STDLIB=${_CXX_COROUTINES_STDLIB}")
message(STATUS "_CXX_COROUTINES_HAVE_HEADER=${_CXX_COROUTINES_HAVE_HEADER}")
message(STATUS "_CXX_COROUTINES_HAVE_EXPERIMENTAL_HEADER=${_CXX_COROUTINES_HAVE_EXPERIMENTAL_HEADER}")
message(STATUS "CXX_COROUTINES_HEADER=${CXX_COROUTINES_HEADER}")
message(STATUS "CXX_COROUTINES_NAMESPACE=${CXX_COROUTINES_NAMESPACE}")
message(STATUS "can_link for COROUTINES=${can_link}")
message(STATUS "_have_coro for COROUTINES=${_have_coro}")

check_cxx_source_runs("
  #include <stdarg.h>
  #include <stdio.h>
  int call_vsnprintf(const char* fmt, ...) {
    char buf[256];
    va_list ap;
    va_start(ap, fmt);
    int result = vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    return result;
  }
  int main(int argc, char** argv) {
    return call_vsnprintf(\"%\", 1) < 0 ? 0 : 1;
  }"
  HAVE_VSNPRINTF_ERRORS
)

if (BASIC_HAVE_LIBGFLAGS)
  # Older releases of gflags used the namespace "gflags"; newer releases
  # use "google" but also make symbols available in the deprecated "gflags"
  # namespace too.  The BASIC code internally uses "gflags" unless we tell it
  # otherwise.
  list(APPEND CMAKE_REQUIRED_LIBRARIES ${BASIC_LIBGFLAGS_LIBRARY})
  list(APPEND CMAKE_REQUIRED_INCLUDES ${BASIC_LIBGFLAGS_INCLUDE})
  check_cxx_source_compiles("
    #include <gflags/gflags.h>
    int main() {
      gflags::GetArgv();
      return 0;
    }
    "
    GFLAGS_NAMESPACE_IS_GFLAGS
  )
  list(REMOVE_ITEM CMAKE_REQUIRED_LIBRARIES ${BASIC_LIBGFLAGS_LIBRARY})
  list(REMOVE_ITEM CMAKE_REQUIRED_INCLUDES ${BASIC_LIBGFLAGS_INCLUDE})
  if (GFLAGS_NAMESPACE_IS_GFLAGS)
    set(BASIC_UNUSUAL_GFLAGS_NAMESPACE OFF)
    set(BASIC_GFLAGS_NAMESPACE gflags)
  else()
    set(BASIC_UNUSUAL_GFLAGS_NAMESPACE ON)
    set(BASIC_GFLAGS_NAMESPACE google)
  endif()
endif()

configure_file_if_changed(
  INPUT ${CMAKE_CURRENT_SOURCE_DIR}/cmake/basic-config.h.cmake
  OUTPUT ${BASIC_SOURCES_PATH}/basic-config.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/basic-config.tmp)
