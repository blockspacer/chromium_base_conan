# see https://github.com/chromium/chromium/blob/9db0b5162b8648833c3a6b1af044cebd9d7d3855/base/BUILD.gn

cmake_minimum_required(VERSION 3.5)

# project() must be before checks, see https://stackoverflow.com/a/26437667/10904212
set(PROJECT_NAME "chromium_base")
set(PROJECT_VERSION 1.0.0.1)
project(${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  LANGUAGES CXX C)

set(BASE_LIB_NAME ${PROJECT_NAME})

# --------------------------- conan configuration ------------------------------

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/fetch_cmake_utils.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/fetch_conan_auto_install.cmake)

option(CONAN_AUTO_INSTALL "Let CMake call conan install automatically"
  OFF
)
if (CONAN_AUTO_INSTALL)
  set(CONAN_PROFILE
      "clang"
      CACHE STRING "Conan profile to use during installation")
  if (NOT CMAKE_BUILD_TYPE MATCHES "Debug" )
    set(conan_build_type "Release")
  else()
    set(conan_build_type "Debug")
  endif()
  # You can use `EXTRA_CONAN_AUTO_INSTALL_OPTIONS` like so:
  # cmake .. -DCONAN_AUTO_INSTALL=ON -DEXTRA_CONAN_AUTO_INSTALL_OPTIONS="--build missing" -DCMAKE_BUILD_TYPE=Debug
  conan_auto_install(
    CONAN_OPTIONS "--profile=${CONAN_PROFILE} -s build_type=${conan_build_type} -s llvm_tools:build_type=Release --build=missing -o openssl:shared=True ${EXTRA_CONAN_AUTO_INSTALL_OPTIONS}"
    #FORCE
  )
endif()

if(COMPILE_WITH_LLVM_TOOLS)
  message(STATUS
    "Using COMPILE_WITH_LLVM_TOOLS")
  # do not check compile in conanbuildinfo
  # cause we will switch to other compiler after conan install
  set(CONAN_DISABLE_CHECK_COMPILER ON)
else(COMPILE_WITH_LLVM_TOOLS)
  message(STATUS
    "Disabled COMPILE_WITH_LLVM_TOOLS")
endif(COMPILE_WITH_LLVM_TOOLS)

if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR}/)
  include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
  include(${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake OPTIONAL)
  conan_basic_setup(
    # prevent conan_basic_setup from resetting cmake variables
    TARGETS
    KEEP_RPATHS
    # see https://github.com/conan-io/conan/issues/6012
    NO_OUTPUT_DIRS
  )
else()
  message (FATAL_ERROR "must use conan")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/)

# ------------------------------- Options --------------------------------------

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Options.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CommonOptions.cmake)

find_package(cmake_platform_detection REQUIRED)
run_cmake_platform_detection()
# NOTE: perform platform checks before everything else
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PlatformChecks.cmake)

find_package(cmake_build_options REQUIRED)
setup_default_build_type(RELEASE)
setup_cmake_build_options(RELEASE DEBUG)

find_package(chromium_build_util REQUIRED)
if(TARGET chromium_build_util::chromium_build_util-static)
  set(build_util_LIB chromium_build_util::chromium_build_util-static)
else()
  message(FATAL_ERROR "not supported: using system provided chromium_build_util library")
endif()

check_cmake_build_type_selected() # from Utils.cmake

enable_colored_diagnostics() # from Utils.cmake

print_cmake_system_info() # from Utils.cmake

check_supported_os() # from Utils.cmake

find_package(cmake_helper_utils REQUIRED)

force_latin_paths() # from cmake_helper_utils (conan package)

validate_out_dirs() # from cmake_helper_utils (conan package)

# In-source builds not allowed
validate_out_source_build(WARNING) # from cmake_helper_utils (conan package)

message(STATUS "Conan setup done!")
message(STATUS "CONAN_INCLUDE_DIRS_PROTOBUF: ${CONAN_INCLUDE_DIRS_PROTOBUF}")
message(STATUS "CONAN_LIBS: ${CONAN_LIBS}")
message(STATUS "_gRPC_PROTOBUF_LIBRARIES: ${_gRPC_PROTOBUF_LIBRARIES}")
#message(STATUS "CONAN_LIBS_GRPC_CONAN: ${CONAN_LIBS_GRPC_CONAN}")
message(STATUS "CONAN_LIBS_PROTOBUF: ${CONAN_LIBS_PROTOBUF}")
message(STATUS "CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")
message(STATUS "CMAKE_PROGRAM_PATH: ${CMAKE_PROGRAM_PATH}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")
find_program(_gRPC_PROTOBUF_PROTOC_EXECUTABLE protoc NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH)
message(STATUS "_gRPC_PROTOBUF_PROTOC_EXECUTABLE: ${_gRPC_PROTOBUF_PROTOC_EXECUTABLE}")
find_program(PROTOBUF_PROTOC_EXECUTABLE protoc NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH)
message(STATUS "PROTOBUF_PROTOC_EXECUTABLE: ${PROTOBUF_PROTOC_EXECUTABLE}")
find_program(Protobuf_PROTOC_EXECUTABLE protoc NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH)
message(STATUS "Protobuf_PROTOC_EXECUTABLE: ${Protobuf_PROTOC_EXECUTABLE}")

if(ENABLE_MSAN OR ENABLE_TSAN OR ENABLE_ASAN OR ENABLE_UBSAN)
  find_package(cmake_sanitizers REQUIRED)
endif()

if(ENABLE_MSAN)
  add_msan_flags()
endif(ENABLE_MSAN)

if(ENABLE_TSAN)
  add_tsan_flags()
endif(ENABLE_TSAN)

if(ENABLE_ASAN)
  add_asan_flags()
endif(ENABLE_ASAN)

if(ENABLE_UBSAN)
  add_ubsan_flags()
endif(ENABLE_UBSAN)

if(COMPILE_WITH_LLVM_TOOLS)
  message(STATUS
    "Using COMPILE_WITH_LLVM_TOOLS")
  # force change CMAKE_*_COMPILER and CMAKE_LINKER to clang from conan
  compile_with_llvm_tools() # from cmake_helper_utils (conan package)
else(COMPILE_WITH_LLVM_TOOLS)
  message(STATUS
    "Disabled COMPILE_WITH_LLVM_TOOLS")
endif(COMPILE_WITH_LLVM_TOOLS)

if(ENABLE_ASAN
   OR ENABLE_TSAN
   OR ENABLE_MSAN
   OR ENABLE_UBSAN
   OR ENABLE_VALGRIND
   )
  list(APPEND BASE_DEFINES MEMORY_TOOL_REPLACES_ALLOCATOR=1)

  if(NOT ALLOCATOR_NONE OR ALLOCATOR_TCMALLOC)
    message(FATAL_ERROR
      "use ALLOCATOR_NONE with memory tools")
  endif(NOT ALLOCATOR_NONE OR ALLOCATOR_TCMALLOC)
endif()

if(TARGET_LINUX)
  if(ALLOCATOR_TCMALLOC AND ALLOCATOR_NONE)
    message(FATAL_ERROR
      "LINUX-ONLY: you must specify only one allocator")
  endif(ALLOCATOR_TCMALLOC AND ALLOCATOR_NONE)
endif(TARGET_LINUX)

#
# ICU
#
list(APPEND BASE_DEFINES HAS_ICU=1)
# chromium_icu
if(TARGET_LINUX OR TARGET_EMSCRIPTEN)
  find_package(chromium_icu REQUIRED)
  if(NOT TARGET chromium_icu::chromium_icu-static)
    message(FATAL_ERROR "not supported: using system provided libevent library")
  endif()
elseif(TARGET_WINDOWS)
  # skip
else()
  message(FATAL_ERROR "chromium_icu not found")
endif()
#
list(APPEND BASE_DEFINES USE_CUSTOM_ICU=1)
set(CUSTOM_ICU_LIB chromium_icu::chromium_icu-static) # see icu.cmake
#
if(NOT DEFINED CUSTOM_ICU_LIB)
  message(FATAL_ERROR "CUSTOM_ICU_LIB must be defined")
endif(NOT DEFINED CUSTOM_ICU_LIB)

if(TARGET_LINUX)
  # ENABLE_DYNAMIC_ANNOTATIONS option defines DYNAMIC_ANNOTATIONS_ENABLED=1
  # NOTE: we always need to link with dynamic_annotations
  set(ENABLE_DYNAMIC_ANNOTATIONS TRUE) # required by tcmalloc
elseif(TARGET_EMSCRIPTEN OR TARGET_WINDOWS)
  set(ENABLE_DYNAMIC_ANNOTATIONS FALSE)
else()
  message(FATAL_ERROR "unknown platform")
endif()
if(NOT DEFINED ENABLE_DYNAMIC_ANNOTATIONS)
  message(FATAL_ERROR "ENABLE_DYNAMIC_ANNOTATIONS must be defined")
endif(NOT DEFINED ENABLE_DYNAMIC_ANNOTATIONS)

find_package(chromium_dynamic_annotations REQUIRED)
if(TARGET chromium_dynamic_annotations::chromium_dynamic_annotations-static)
  set(dynamic_annotations_LIB chromium_dynamic_annotations::chromium_dynamic_annotations-static)
else()
  message(FATAL_ERROR "not supported: using system provided dynamic_annotations library")
endif()

if(TARGET_LINUX)
  if(ALLOCATOR_TCMALLOC)
    find_package(chromium_tcmalloc REQUIRED)
    if(TARGET chromium_tcmalloc::chromium_tcmalloc-static)
      set(tcmalloc_LIB chromium_tcmalloc::chromium_tcmalloc-static)
    else()
      message(FATAL_ERROR "not supported: using system provided chromium_tcmalloc library")
    endif()
  endif(ALLOCATOR_TCMALLOC)
elseif(TARGET_WINDOWS OR TARGET_EMSCRIPTEN)
  # skip
else()
  message(FATAL_ERROR "platform not supported")
endif()

# xdg_user_dirs
if(TARGET_LINUX)
  find_package(chromium_xdg_user_dirs REQUIRED)
  if(TARGET chromium_xdg_user_dirs::chromium_xdg_user_dirs-static)
    set(xdg_user_dirs_LIB chromium_xdg_user_dirs::chromium_xdg_user_dirs-static)
  else()
    message(FATAL_ERROR "not supported: using system provided xdg_user_dirs library")
  endif()
elseif(TARGET_WINDOWS OR TARGET_EMSCRIPTEN)
  # skip
else()
  message(FATAL_ERROR "platform no supported")
endif()

# xdg_mime
if(TARGET_LINUX)
  find_package(chromium_xdg_mime REQUIRED)
  if(TARGET chromium_xdg_mime::chromium_xdg_mime-static)
    set(xdg_mime_LIB chromium_xdg_mime::chromium_xdg_mime-static)
  else()
    message(FATAL_ERROR "not supported: using system provided xdg_mime library")
  endif()
elseif(TARGET_WINDOWS OR TARGET_EMSCRIPTEN)
  # skip
else()
  message(FATAL_ERROR "platform no supported")
endif()

# libevent
if(TARGET_LINUX)
  find_package(chromium_libevent REQUIRED)
  if(TARGET chromium_libevent::chromium_libevent-static)
    set(libevent_LIB chromium_libevent::chromium_libevent-static)
    set(USE_LIBEVENT TRUE)
  else()
    message(FATAL_ERROR "not supported: using system provided libevent library")
  endif()
elseif(TARGET_WINDOWS OR TARGET_EMSCRIPTEN)
  # skip
else()
  message(FATAL_ERROR "platform no supported")
endif()

# modp_b64
find_package(chromium_modp_b64 REQUIRED)
if(TARGET chromium_modp_b64::chromium_modp_b64-static)
  set(modp_b64_LIB chromium_modp_b64::chromium_modp_b64-static)
else()
  message(FATAL_ERROR "not supported: using system provided modp_b64 library")
endif()

# compact_enc_det
set(ENABLE_COMPACT_ENC_DET TRUE)
if(NOT ENABLE_COMPACT_ENC_DET)
  list(APPEND BASE_DEFINES DISABLE_COMPACT_ENC_DET=1)
endif(NOT ENABLE_COMPACT_ENC_DET)
if(ENABLE_COMPACT_ENC_DET)
  find_package(chromium_compact_enc_det REQUIRED)
  if(TARGET chromium_compact_enc_det::chromium_compact_enc_det-static)
    set(ced_LIB chromium_compact_enc_det::chromium_compact_enc_det-static)
  else()
    message(FATAL_ERROR "not supported: using system provided compact_enc_det library")
  endif()
endif(ENABLE_COMPACT_ENC_DET)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/GenBuildFlags.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/GenMojo.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectFiles.cmake)

if(TARGET_EMSCRIPTEN)
  # skip
elseif(TARGET_LINUX OR TARGET_WINDOWS)
  find_package( Threads REQUIRED )
  message(STATUS "CMAKE_THREAD_LIBS_INIT = ${CMAKE_THREAD_LIBS_INIT}")
  set(PTHREADS_LIBS ${CMAKE_THREAD_LIBS_INIT}) # note: not set for emscripten
else()
  message(FATAL_ERROR "platform not supported")
endif()

add_library(${BASE_LIB_NAME}-test-includes INTERFACE)

macro(add_absolute_include_dir TARGET VISIBILITY NEW_ELEM)
  target_include_directories(${TARGET} ${VISIBILITY}
    ${NEW_ELEM}
  )
  target_include_directories( ${TARGET}-test-includes SYSTEM INTERFACE
    ${NEW_ELEM} )
endmacro(add_absolute_include_dir)

# $<INSTALL_INTERFACE:...> is exported using install(EXPORT)
# $<BUILD_INTERFACE:...> is exported using export(), or when the target is used by another target in the same buildsystem
macro(add_relative_include_dir TARGET VISIBILITY_BUILD VISIBILITY_INSTALL NEW_ELEM)
  target_include_directories(${TARGET}
    ${VISIBILITY_BUILD} "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${NEW_ELEM}>"
    ${VISIBILITY_INSTALL} "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}/${NEW_ELEM}>"
  )
  target_include_directories( ${TARGET}-test-includes SYSTEM INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/${NEW_ELEM} )
endmacro(add_relative_include_dir)

if(TARGET_LINUX)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/detect_atomic32_support.cmake)
endif(TARGET_LINUX)

if(ENABLE_BASE_TRACING)

  # generate_pbzero(
  #   OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}
  #   TMP_FILE_DIR ${CMAKE_CURRENT_BINARY_DIR}
  #   INPUT_FILES ${CMAKE_CURRENT_SOURCE_DIR}/proto/chrome_track_event.proto
  #   INCLUDE_PROTO_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/proto
  #   APPEND_GENERATED_FILES_TO_LIST MY_PROJECT_GENERATED_FILES
  #   VERBOSE TRUE
  # )
  function(generate_pbzero)
    # see https://cliutils.gitlab.io/modern-cmake/chapters/basics/functions.html
    #set(options ) # empty
    set(oneValueArgs VERBOSE TMP_FILE_DIR OUT_DIR APPEND_GENERATED_FILES_TO_LIST)
    set(multiValueArgs INPUT_FILES INCLUDE_PROTO_PATHS)
    #
    cmake_parse_arguments(
      ARGUMENTS # prefix of output variables
      "${options}" # list of names of the boolean arguments (only defined ones will be true)
      "${oneValueArgs}" # list of names of mono-valued arguments
      "${multiValueArgs}" # list of names of multi-valued arguments (output variables are lists)
      ${ARGN} # arguments of the function to parse, here we take the all original ones
    )
    #
    set(OUT_DIR ${ARGUMENTS_OUT_DIR})
    set(INPUT_FILES ${ARGUMENTS_INPUT_FILES})
    set(INCLUDE_PROTO_PATHS ${ARGUMENTS_INCLUDE_PROTO_PATHS})
    set(APPEND_GENERATED_FILES_TO_LIST ${ARGUMENTS_APPEND_GENERATED_FILES_TO_LIST})
    set(TMP_FILE_DIR ${ARGUMENTS_TMP_FILE_DIR})
    if(NOT EXISTS "${TMP_FILE_DIR}")
      message(FATAL_ERROR "Unable to find required directory: ${TMP_FILE_DIR}")
    endif()
    #
    if(${ARGUMENTS_VERBOSE})
      set_if_not_empty(PERFETTO_protozero_plugin_BIN "$ENV{PERFETTO_protozero_plugin_BIN}")
      message(STATUS "PERFETTO_protozero_plugin_BIN=${PERFETTO_protozero_plugin_BIN}")
      set_if_not_empty(PERFETTO_PROTOC_BIN "$ENV{PERFETTO_PROTOC_BIN}")
      message(STATUS "PERFETTO_PROTOC_BIN=${PERFETTO_PROTOC_BIN}")
      set_if_not_empty(PERFETTO_SDK_DIR "$ENV{PERFETTO_SDK_DIR}")
      message(STATUS "PERFETTO_SDK_DIR=${PERFETTO_SDK_DIR}")
      set_if_not_empty(PERFETTO_GEN_DIR "$ENV{PERFETTO_GEN_DIR}")
      message(STATUS "PERFETTO_GEN_DIR=${PERFETTO_GEN_DIR}")
      set_if_not_empty(PERFETTO_PROTOS_DIR "$ENV{PERFETTO_PROTOS_DIR}")
      message(STATUS "PERFETTO_PROTOS_DIR=${PERFETTO_PROTOS_DIR}")
      set_if_not_empty(PERFETTO_BUILDTOOLS_DIR "$ENV{PERFETTO_BUILDTOOLS_DIR}")
      message(STATUS "PERFETTO_BUILDTOOLS_DIR=${PERFETTO_BUILDTOOLS_DIR}")
    endif()
    #
    foreach(FILEPATH ${INPUT_FILES})
      get_filename_component(FILENAME_WITHOUT_EXT ${FILEPATH} NAME_WE)
      #
      set(protoc_generated_tmp_files
        ${TMP_FILE_DIR}/${FILENAME_WITHOUT_EXT}.pbzero.h
        ${TMP_FILE_DIR}/${FILENAME_WITHOUT_EXT}.pbzero.cc
      )
      foreach(TMP_FILE_PATH ${protoc_generated_tmp_files})
        # remove old tmp file
        execute_process(
          COMMAND
            ${CMAKE_COMMAND} -E remove
              ${TMP_FILE_PATH}
          OUTPUT_QUIET
        )
      endforeach()
      #
      set(FULL_PROTOC_CMD
        ${PERFETTO_PROTOC_BIN}
        "-I${PERFETTO_PROTOS_DIR}"
        $<$<BOOL:${INCLUDE_PROTO_PATHS}>:-I$<JOIN:${INCLUDE_PROTO_PATHS}, -I>>
        "--proto_path=${PERFETTO_PROTOS_DIR}"
        "--plugin_out=wrapper_namespace=pbzero:${TMP_FILE_DIR}"
        "--plugin=protoc-gen-plugin=${PERFETTO_protozero_plugin_BIN}"
        "${FILEPATH}"
      )
      #
      add_custom_command(
        OUTPUT ${protoc_generated_tmp_files}
        COMMAND
          "${CMAKE_COMMAND}"
          -E
          echo
          "executing command: ${FULL_PROTOC_CMD}"
        COMMAND
          "${FULL_PROTOC_CMD}"
        # code generator COMMAND will only be launched
        # if some of DEPENDS files were changed.
        DEPENDS
          ${FILEPATH}
        # NOTE: uses COMMAND_EXPAND_LISTS
        # to support generator expressions
        # see https://cmake.org/cmake/help/v3.13/command/add_custom_target.html
        COMMAND_EXPAND_LISTS
        COMMENT "running ${PERFETTO_PROTOC_BIN}"
        VERBATIM # to support \t for example
      )
      #
      foreach(TMP_FILE_PATH ${protoc_generated_tmp_files})
        get_filename_component(TMP_FILENAME ${TMP_FILE_PATH} NAME)
        set(FULL_CP_TMP_CMD
          ${CMAKE_COMMAND} -E copy_if_different
            ${TMP_FILE_PATH}
            ${OUT_DIR}/${TMP_FILENAME}
        )
        add_custom_command(
          OUTPUT ${OUT_DIR}/${TMP_FILENAME}
          COMMAND
            "${CMAKE_COMMAND}"
            -E
            echo
            "executing command: ${FULL_CP_TMP_CMD}"
          COMMAND
            "${FULL_CP_TMP_CMD}"
          # code generator COMMAND will only be launched
          # if some of DEPENDS files were changed.
          DEPENDS
            ${protoc_generated_tmp_files}
          # NOTE: uses COMMAND_EXPAND_LISTS
          # to support generator expressions
          # see https://cmake.org/cmake/help/v3.13/command/add_custom_target.html
          COMMAND_EXPAND_LISTS
          COMMENT "copying protozero file ${TMP_FILE_PATH} into ${OUT_DIR}/${TMP_FILENAME}"
          VERBATIM # to support \t for example
        )
      endforeach()
      #
      set(protoc_generated_files
        ${OUT_DIR}/${FILENAME_WITHOUT_EXT}.pbzero.h
        ${OUT_DIR}/${FILENAME_WITHOUT_EXT}.pbzero.cc
      )
      foreach(GENERATED_FILE_PATH ${protoc_generated_files})
        if(NOT EXISTS "${GENERATED_FILE_PATH}")
          message(STATUS "Generating protozero file: ${GENERATED_FILE_PATH}")
        endif()
      endforeach()
      # Set GENERATED properties of your generated source file.
      # So cmake won't complain about missing source file.
      set_source_files_properties(
        ${protoc_generated_files}
        PROPERTIES GENERATED 1)
      #
      set(all_protoc_generated_files)
      list(APPEND all_protoc_generated_files ${protoc_generated_files})
    endforeach()
    #
    if("${all_protoc_generated_files}" STREQUAL "")
      message(FATAL_ERROR "No files generated by protozero")
    endif()
    set(${APPEND_GENERATED_FILES_TO_LIST} ${all_protoc_generated_files} PARENT_SCOPE)
  endfunction(generate_pbzero)

  generate_pbzero(
    OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/base/tracing/protos
    TMP_FILE_DIR ${CMAKE_CURRENT_BINARY_DIR}
    INPUT_FILES ${CMAKE_CURRENT_SOURCE_DIR}/base/tracing/protos/chrome_track_event.proto
    INCLUDE_PROTO_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/base/tracing/protos
    APPEND_GENERATED_FILES_TO_LIST ${BASE_LIB_NAME}_GENERATED_FILES
    VERBOSE TRUE
  )

  set_if_not_empty(PERFETTO_SDK_DIR "$ENV{PERFETTO_SDK_DIR}")
  list(APPEND BASE_SOURCES
    ${PERFETTO_SDK_DIR}/perfetto.cc
    ${${BASE_LIB_NAME}_GENERATED_FILES}
  )
endif(ENABLE_BASE_TRACING)

# Creates shared or static library depending on BUILD_SHARED_LIBS variable,
# conan passes the shared option as the BUILD_SHARED_LIBS variable.
add_library(${BASE_LIB_NAME}
  ${BASE_SOURCES}
)

if(NOT DEFINED ENABLE_COMPACT_ENC_DET)
  message(FATAL_ERROR "NOT DEFINED ENABLE_COMPACT_ENC_DET")
endif(NOT DEFINED ENABLE_COMPACT_ENC_DET)

if(ENABLE_COMPACT_ENC_DET)
  if(NOT DEFINED ced_LIB)
    message(FATAL_ERROR "NOT DEFINED ced_LIB")
  endif(NOT DEFINED ced_LIB)
endif(ENABLE_COMPACT_ENC_DET)

if(TARGET_EMSCRIPTEN)
  list(APPEND EXTRA_CHROMIUM_BASE_LIBS
    ${ced_LIB}
  )
elseif(TARGET_LINUX)
  if(NOT DEFINED libevent_LIB)
    message(FATAL_ERROR "NOT DEFINED libevent_LIB")
  endif(NOT DEFINED libevent_LIB)

  if(ALLOCATOR_TCMALLOC AND NOT DEFINED tcmalloc_LIB)
    message(FATAL_ERROR "NOT DEFINED tcmalloc_LIB")
  endif(ALLOCATOR_TCMALLOC AND NOT DEFINED tcmalloc_LIB)

  if(NOT DEFINED modp_b64_LIB)
    message(FATAL_ERROR "NOT DEFINED modp_b64_LIB")
  endif(NOT DEFINED modp_b64_LIB)

  list(APPEND EXTRA_CHROMIUM_BASE_LIBS
    ${tcmalloc_LIB} # if ALLOCATOR_TCMALLOC
    ${ced_LIB}
    # libevent only for posix/linux/e.t.c.
    ${libevent_LIB}
    ${modp_b64_LIB}
  )
  add_dependencies(${BASE_LIB_NAME}
    ${tcmalloc_LIB} # if ALLOCATOR_TCMALLOC
    ${ced_LIB}
    ${modp_b64_LIB}
  )
elseif(TARGET_WINDOWS)
  list(APPEND EXTRA_CHROMIUM_BASE_LIBS
    ${ced_LIB}
    # libevent only for posix/linux/e.t.c.
    #${libevent_LIB}
    ${modp_b64_LIB}
  )
  add_dependencies(${BASE_LIB_NAME}
    ${ced_LIB}
    ${CUSTOM_ICU_LIB}
    ${modp_b64_LIB}
  )
else()
  message(FATAL_ERROR "platform not supported")
endif()

if(TARGET_LINUX)
  list(APPEND EXTRA_CHROMIUM_BASE_LIBS
    ${xdg_mime_LIB}
    ${xdg_user_dirs_LIB}
  )
endif(TARGET_LINUX)

#add_dependencies(base
#  ${EXTRA_CHROMIUM_BASE_LIBS}
#)

#message(FATAL_ERROR EXTRA_CHROMIUM_BASE_LIBS=${EXTRA_CHROMIUM_BASE_LIBS})

if(TARGET_WINDOWS)
  # see https://github.com/chromium/chromium/blob/9db0b5162b8648833c3a6b1af044cebd9d7d3855/base/BUILD.gn#L1799
  list(APPEND EXTRA_CHROMIUM_BASE_LIBS
    cfgmgr32.lib
    powrprof.lib
    propsys.lib
    setupapi.lib
    userenv.lib
    wbemuuid.lib
    winmm.lib
    # https://stackoverflow.com/questions/7028304/error-lnk2019-when-using-getfileversioninfosize
    version.lib
    # https://github.com/blockspacer/skia-opengl-emscripten/blob/7c423190544c8da1bf8ae79b800c9c0c83dd3c6e/src/chromium/build/config/BUILD.gn#L203
    advapi32.lib
    comdlg32.lib
    dbghelp.lib
    dnsapi.lib
    gdi32.lib
    msimg32.lib
    odbc32.lib
    odbccp32.lib
    oleaut32.lib
    shell32.lib
    shlwapi.lib
    user32.lib
    usp10.lib
    uuid.lib
    wininet.lib
    winmm.lib
    winspool.lib
    ws2_32.lib
  )
endif(TARGET_WINDOWS)

if(NOT DEFINED dynamic_annotations_LIB)
  message(FATAL_ERROR "NOT DEFINED: dynamic_annotations_LIB")
endif(NOT DEFINED dynamic_annotations_LIB)

find_package(fmt QUIET)
if(FMT_HEADER_ONLY)
  set(FMTLIB CONAN_PKG::fmt-header-only)
else()
  set(FMTLIB CONAN_PKG::fmt)
endif()
#get_target_property(moggle_interface_includes ${FMTLIB} INTERFACE_INCLUDE_DIRECTORIES)
#message(FATAL_ERROR "Moggle interface includes: ${moggle_interface_includes}")
#
if(NOT TARGET CONAN_PKG::fmt)
  message(FATAL_ERROR "not supported ${FMTLIB}: using system provided CONAN_PKG::fmt library")
endif()

target_link_libraries(${BASE_LIB_NAME} PRIVATE
  ${modp_b64_LIB}
  CONAN_PKG::double-conversion
  CONAN_PKG::openssl
  #
  ${dynamic_annotations_LIB}
  ${EXTRA_CHROMIUM_BASE_LIBS}
  ${LIBATOMIC} # from system, no dep. for __atomic_is_lock_free
  ${PTHREADS_LIBS} # note: not set for emscripten
  ${CMAKE_DL_LIBS} # https://cmake.org/cmake/help/v3.13/variable/CMAKE_DL_LIBS.html
)

find_package(Threads)

list(APPEND USED_3DPARTY_LIBS
  ${CUSTOM_ICU_LIB}
  CONAN_PKG::abseil
  CONAN_PKG::boost
  ${FMTLIB}
  ${CMAKE_THREAD_LIBS_INIT}
  #CONAN_PKG::protobuf # TODO: collides with perfetto_trace_protos in function google::protobuf::Base64Escape
)

if(ENABLE_BASE_TRACING)
  list(APPEND USED_3DPARTY_LIBS
    CONAN_PKG::perfetto
  )
endif(ENABLE_BASE_TRACING)

if(TARGET_LINUX)
  list(APPEND USED_3DPARTY_LIBS
    CONAN_PKG::linux-syscall-support
  )
endif()

if(NOT DEFINED build_util_LIB)
  message(FATAL_ERROR "NOT DEFINED: build_util_LIB")
endif(NOT DEFINED build_util_LIB)

target_compile_definitions(${BASE_LIB_NAME} PUBLIC
  # https://stackoverflow.com/a/30877725
  BOOST_SYSTEM_NO_DEPRECATED
  BOOST_ERROR_CODE_HEADER_ONLY
  # TODO: make program_options work without rtti (boost::bad_any_cast)
  #BOOST_NO_RTTI
  #BOOST_NO_TYPEID
  # TODO
  #BOOST_NO_EXCEPTIONS
  BOOST_ASIO_STANDALONE=1
)

if(ENABLE_BORINGSSL)
  target_compile_definitions(${BASE_LIB_NAME} PUBLIC
    ENABLE_BORINGSSL=1
  )
endif()

if(ENABLE_BASE_TRACING AND USE_PERFETTO_CLIENT_LIBRARY)
  target_compile_definitions(${BASE_LIB_NAME} PUBLIC
    BASE_USE_PERFETTO_CLIENT_LIBRARY=1
  )
endif()

if(USE_TEST_SUPPORT)
  message(STATUS "enabled USE_TEST_SUPPORT")

  # chromium_libxml
  find_package(chromium_libxml MODULE REQUIRED)
  if(TARGET chromium_libxml::chromium_libxml-static)
    set(libxml_LIB chromium_libxml::chromium_libxml-static)
  else()
    message(FATAL_ERROR "not supported: using system provided chromium_libxml library")
  endif()

  list(APPEND USED_3DPARTY_LIBS
    ${libxml_LIB}
    CONAN_PKG::conan_gtest
  )

  target_compile_definitions(${BASE_LIB_NAME} PRIVATE
    IS_BASE_TEST_IMPL=1
    BUILD_DATE=BASE_BUILD_DATE
  )

  target_compile_definitions(${BASE_LIB_NAME} PUBLIC
    UNIT_TEST=1
  )

  target_link_libraries(${BASE_LIB_NAME} PUBLIC
    ${dynamic_annotations_LIB}
  )
endif(USE_TEST_SUPPORT)

list(APPEND USED_3DPARTY_LIBS
  ${build_util_LIB}
)

target_link_libraries(${BASE_LIB_NAME} PUBLIC
  ${USED_3DPARTY_LIBS}
)

#set_property(TARGET ${BASE_LIB_NAME} PROPERTY CXX_STANDARD 17)

# POSITION_INDEPENDENT_CODE for -fPIC
# -fPIC may be used to link static library into dynamic one
# Position-independent code requires special support,
# and therefore works only on certain machines.
# see https://akkadia.org/drepper/dsohowto.pdf
set_property(TARGET ${BASE_LIB_NAME}
  PROPERTY POSITION_INDEPENDENT_CODE ON)

if(TARGET_LINUX)
  set(ENABLE_DYNAMIC_ANNOTATIONS TRUE) # required by tcmalloc
elseif(TARGET_EMSCRIPTEN OR TARGET_WINDOWS)
  # skip
  set(ENABLE_DYNAMIC_ANNOTATIONS FALSE)
else()
  message(FATAL_ERROR "unknown platform")
endif()

# Annotations useful when implementing condition variables such as CondVar,
# using conditional critical sections (Await/LockWhen) and when constructing
# user-defined synchronization mechanisms.
if(ENABLE_DYNAMIC_ANNOTATIONS)
  list(APPEND BASE_DEFINES DYNAMIC_ANNOTATIONS_ENABLED=1)
endif(ENABLE_DYNAMIC_ANNOTATIONS)

string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if(cmake_build_type_tolower MATCHES "release")
  list(APPEND BASE_DEFINES
    # The official build does not print the stacktrace
    # or reason a CHECK failed.
    OFFICIAL_BUILD=1
  )
endif() # NOT CMAKE_BUILD_TYPE MATCHES

list(APPEND BASE_DEFINES
  BASE_PORT=1
)

if(NOT ALLOCATOR_TCMALLOC)
  list(APPEND BASE_DEFINES
    NO_TCMALLOC=1
  )
endif(NOT ALLOCATOR_TCMALLOC)

if(ENABLE_BASE_TRACING)
  set_if_not_empty(PERFETTO_SDK_DIR "$ENV{PERFETTO_SDK_DIR}")
  set_if_not_empty(PERFETTO_BUILDTOOLS_DIR "$ENV{PERFETTO_BUILDTOOLS_DIR}")
  set_if_not_empty(PERFETTO_GEN_DIR "$ENV{PERFETTO_GEN_DIR}")

  # path to `protobuf/src/google/protobuf/port_def.inc`
  add_absolute_include_dir(${BASE_LIB_NAME} PUBLIC "${PERFETTO_BUILDTOOLS_DIR}/protobuf/src")

  # path to perfetto_build_flags.h
  add_absolute_include_dir(${BASE_LIB_NAME} PUBLIC "${PERFETTO_GEN_DIR}/build_config")

  # path to protos/perfetto/trace/track_event/track_event.pbzero.h
  add_absolute_include_dir(${BASE_LIB_NAME} PUBLIC "${PERFETTO_GEN_DIR}")

  # path to perfetto.h
  add_absolute_include_dir(${BASE_LIB_NAME} PUBLIC "${PERFETTO_SDK_DIR}")
endif(ENABLE_BASE_TRACING)

add_relative_include_dir(${BASE_LIB_NAME} PUBLIC PUBLIC "")
add_relative_include_dir(${BASE_LIB_NAME} PUBLIC PUBLIC "extensions")

# path to base/threading/thread.h

if(TARGET_APPLE OR TARGET_CHROMEOS_ASH OR TARGET_CHROMECAST OR TARGET_FUCHSIA)
  list(APPEND BASE_EXTRA_DEFINITIONS
    SYSTEM_NATIVE_UTF8=1
  )
endif()

if(TARGET_LINUX OR TARGET_CHROMEOS)
  list(APPEND BASE_EXTRA_DEFINITIONS
    USE_SYMBOLIZE=1
  )
endif()

if(TARGET_LINUX)
  list(APPEND BASE_EXTRA_DEFINITIONS
    HAVE_MMAP=1
  )
elseif(TARGET_WINDOWS)
  if (com_init_check_hook_disabled)
    list(APPEND BASE_EXTRA_DEFINITIONS
      COM_INIT_CHECK_HOOK_DISABLED=1
    )
  endif()
endif()

target_compile_definitions(${BASE_LIB_NAME} PUBLIC
  ${BASE_DEFINES}
  ${EXTRA_DEFINES}
  ${LIB_SYMBOLIZE_PUBLIC_DEFINES}
  _USE_MATH_DEFINES=1 # https://stackoverflow.com/a/58379321
  ${BASE_EXTRA_DEFINITIONS}
)

target_compile_definitions(${BASE_LIB_NAME} PRIVATE
  ${BASE_PRIVATE_DEFINES}
  BASE_IMPLEMENTATION=1
  BASE_I18N_IMPLEMENTATION=1
)

if(TARGET_EMSCRIPTEN)
  # use PROPERTY compiler.cppstd
else()
  target_compile_features(${BASE_LIB_NAME}
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates)
endif()

if(CXX_COROUTINES_HAVE_COROUTINES)
  message(WARNING "Found coroutines support")
  target_link_libraries(${BASE_LIB_NAME} PRIVATE std::coroutines)
  target_compile_options(${BASE_LIB_NAME} PRIVATE ${_CXX_COROUTINES_AWAIT})
else()
  message(WARNING "No coroutines support found")
endif()

if(NOT MSVC OR IS_CLANG_CL)
  target_compile_options(${BASE_LIB_NAME} PRIVATE
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
    -Wno-old-style-cast
    # frame.h: warning: definition of implicit copy constructor for 'Frame'
    # is deprecated because it has a user-declared destructor
    -Wno-deprecated-copy-dtor
  )
  target_compile_options(${BASE_LIB_NAME} PUBLIC
    # fixes base/logging.h:406:65: warning: token pasting of ',' and __VA_ARGS__ is a GNU extension [-Wgnu-zero-variadic-macro-arguments]
    -Wno-gnu-zero-variadic-macro-arguments
  )
elseif(MSVC)
  target_compile_options(${BASE_LIB_NAME} PRIVATE
    /EHs-c- # disabling exceptions
  )
endif()

set(DEBUG_LIBRARY_SUFFIX "-d")
set_target_properties(${BASE_LIB_NAME}
  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" # TODO: /lib
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" # TODO: /lib
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" # TODO: /bin
    OUTPUT_NAME "${BASE_LIB_NAME}$<$<CONFIG:Debug>:${DEBUG_LIBRARY_SUFFIX}>"
)

## ---------------------------- valgrind -------------------------------- ##

if(ENABLE_VALGRIND)
  check_valgrind_config()
endif()

## ---------------------------- sanitizers -------------------------------- ##

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/setup_sanitizers.cmake)

## ------------------------------- mojo ----------------------------------- ##

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/mojo_public_c_system.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/mojo_public_cpp_platform.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/mojo_public_cpp_system.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/mojo_public_interfaces_bindings.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/mojo_public_cpp_bindings.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/mojo_public_cpp_base.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/mojo_core_ports.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/mojo_core.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/mojo_core_embedder.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ipc.cmake)

## ------------------------------- examples ----------------------------------- ##

include(${CMAKE_CURRENT_SOURCE_DIR}/examples/CMakeLists.txt)

## ------------------------------ exports ---------------------------------- ##

# install and export steps
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Exports.cmake)

if(ENABLE_TESTS)
  enable_testing()
  message( "${PROJECT_NAME} testing enabled" )
  add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/tests )
endif()
