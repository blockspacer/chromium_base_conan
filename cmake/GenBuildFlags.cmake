include_guard( DIRECTORY )

# https://cmake.org/cmake/help/latest/module/FindPythonInterp.html
find_package(PythonInterp 2.7 REQUIRED)

find_package(Git REQUIRED)

# NOTE: To speed up builds pass to cmake
#   -DBASE_NEED_GEN_BUILD_DATE=FALSE \
#   -DBASE_NEED_GEN_BUILDFLAGS=FALSE
# Otherwise code will be FULLY recompiled on each build.
set(BASE_NEED_GEN_BUILD_DATE FALSE CACHE BOOL "BASE_NEED_GEN_BUILD_DATE")
set(BASE_NEED_GEN_BUILDFLAGS FALSE CACHE BOOL "BASE_NEED_GEN_BUILDFLAGS")

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/base/generated_build_date.h")
  set(BASE_NEED_GEN_BUILD_DATE TRUE)
  message(STATUS "Unable to find required file: generated_build_date.h")
  message(STATUS "File will be re-generated: generated_build_date.h")
endif()

if(NOT EXISTS "${BASE_SOURCES_PATH}cfi_buildflags.h")
  message(STATUS "Unable to find required file: cfi_buildflags.h")
  message(STATUS "File will be re-generated: cfi_buildflags.h")
  set(BASE_NEED_GEN_BUILDFLAGS TRUE)
endif()

if(NOT EXISTS "${BASE_SOURCES_PATH}allocator/buildflags.h")
  message(STATUS "Unable to find required file: allocator/buildflags.h")
  message(STATUS "File will be re-generated: allocator/buildflags.h")
  set(BASE_NEED_GEN_BUILDFLAGS TRUE)
endif()

if(TARGET_WINDOWS)
  if(NOT EXISTS "${BASE_SOURCES_PATH}win/base_win_buildflags.h")
    message(STATUS "Unable to find required file: win/base_win_buildflags.h")
    message(STATUS "File will be re-generated: win/base_win_buildflags.h")
    set(BASE_NEED_GEN_BUILDFLAGS TRUE)
  endif()
endif(TARGET_WINDOWS)

if(NOT EXISTS "${BASE_SOURCES_PATH}debug/debugging_buildflags.h")
  message(STATUS "Unable to find required file: debug/debugging_buildflags.h")
  message(STATUS "File will be re-generated: debug/debugging_buildflags.h")
  set(BASE_NEED_GEN_BUILDFLAGS TRUE)
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

if(BASE_NEED_GEN_BUILDFLAGS)
  configure_file(${BUILDFLAGS_GENERATORS_PATH}/buildflags/cfi_buildflags.h.inc
    ${BASE_SOURCES_PATH}cfi_buildflags.h COPYONLY)

  if(NOT DEFINED USE_ALLOC_SHIM)
    message(FATAL_ERROR "define USE_ALLOC_SHIM")
  endif()

  set(USE_ALLOCATOR_SHIM_FLAG "(0)")
  if(USE_ALLOC_SHIM)
    set(USE_ALLOCATOR_SHIM_FLAG "(1)")
  endif(USE_ALLOC_SHIM)

  # https://github.com/chromium/chromium/blob/master/base/allocator/BUILD.gn#L291
  # https://github.com/ruslanch/quic-cmake/blob/master/base/CMakeLists.txt#L35
  configure_file(${BUILDFLAGS_GENERATORS_PATH}/buildflags/allocator_buildflags.h.inc
    ${BASE_SOURCES_PATH}allocator/buildflags.h COPYONLY)

  if(TARGET_WINDOWS)
    configure_file(${BUILDFLAGS_GENERATORS_PATH}/buildflags/base_win_buildflags.h.inc
      ${BASE_SOURCES_PATH}win/base_win_buildflags.h COPYONLY)
  endif(TARGET_WINDOWS)

  # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L1980
  configure_file(${BUILDFLAGS_GENERATORS_PATH}/buildflags/debugging_buildflags.h.inc
    ${BASE_SOURCES_PATH}/debug/debugging_buildflags.h COPYONLY)

  # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L2017
  # https://github.com/geanix/courgette/blob/master/gen/base/synchronization/synchronization_buildflags.h
  configure_file(${BUILDFLAGS_GENERATORS_PATH}/buildflags/synchronization_buildflags.h.inc
    ${BASE_SOURCES_PATH}synchronization/synchronization_buildflags.h COPYONLY)

  configure_file(${BUILDFLAGS_GENERATORS_PATH}/buildflags/protected_memory_buildflags.h.inc
    ${BASE_SOURCES_PATH}memory/protected_memory_buildflags.h COPYONLY)

  configure_file(${BUILDFLAGS_GENERATORS_PATH}/buildflags/partition_alloc_buildflags.h.inc
    ${BASE_SOURCES_PATH}partition_alloc_buildflags.h COPYONLY)

  # https://github.com/chromium/chromium/blob/master/base/BUILD.gn#L2044
  configure_file(${BUILDFLAGS_GENERATORS_PATH}/buildflags/clang_coverage_buildflags.h.inc
    ${BASE_SOURCES_PATH}clang_coverage_buildflags.h COPYONLY)

  # https://github.com/citizenfx/fivem/blob/master/vendor/chromium/base/sanitizer_buildflags.h
  configure_file(${BUILDFLAGS_GENERATORS_PATH}/buildflags/sanitizer_buildflags.h.inc
    ${BASE_SOURCES_PATH}sanitizer_buildflags.h COPYONLY)
endif(BASE_NEED_GEN_BUILDFLAGS)
