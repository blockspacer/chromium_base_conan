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
set(USE_ALLOCATOR_SHIM_FLAG "(0)")
if(USE_ALLOC_SHIM)
  set(USE_ALLOCATOR_SHIM_FLAG "(1)")
endif(USE_ALLOC_SHIM)
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
set(ENABLE_LOCATION_SOURCE "(1)")
set(USE_PROFILING "(0)")
if(ALLOCATOR_TCMALLOC)
  set(USE_PROFILING "(1)")
endif(ALLOCATOR_TCMALLOC)
set(CAN_UNWIND_WITH_FRAME_POINTERS "(0)")
if(TARGET_LINUX AND cmake_build_type_tolower MATCHES "debug")
  set(CAN_UNWIND_WITH_FRAME_POINTERS "(1)")
endif()
# TODO: enable for android if using_sanitizer || enable_profiling || is_debug
set(CAN_UNWIND_WITH_CFI_TABLE "(0)")
set(ENABLE_MEMORY_TASK_PROFILER "(0)")
if(USE_ALLOC_SHIM AND cmake_build_type_tolower MATCHES "debug")
  set(ENABLE_MEMORY_TASK_PROFILER "(1)")
endif()
set(ENABLE_GDBINIT_WARNING "(0)")
if(TARGET_LINUX AND cmake_build_type_tolower MATCHES "debug")
  set(ENABLE_GDBINIT_WARNING "(1)")
endif()
set(IS_UNSAFE_DEVELOPER_BUILD "(0)")
if(TARGET_LINUX AND cmake_build_type_tolower MATCHES "debug")
  set(IS_UNSAFE_DEVELOPER_BUILD "(1)")
endif()
# `NOTREACHED()` will log without crash
set(ENABLE_LOG_ERROR_NOT_REACHED "(1)")
set(EXPENSIVE_DCHECKS_ARE_ON "(0)")
if(cmake_build_type_tolower MATCHES "debug")
  set(ENABLE_LOG_ERROR_NOT_REACHED "(0)")
  set(EXPENSIVE_DCHECKS_ARE_ON "(1)")
endif()
configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/chromeos_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}/build/chromeos_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/chromeos_buildflags.tmp)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/logging_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}/logging_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/logging_buildflags.tmp)

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/clang_profiling_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}/clang_profiling_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/clang_profiling_buildflags.tmp)

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
