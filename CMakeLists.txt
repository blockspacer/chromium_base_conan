# see https://github.com/chromium/chromium/blob/9db0b5162b8648833c3a6b1af044cebd9d7d3855/base/BUILD.gn

cmake_minimum_required(VERSION 3.5)

# project() must be before checks, see https://stackoverflow.com/a/26437667/10904212
set(PROJECT_NAME "chromium_base")
set(PROJECT_VERSION 1.0.0.1)
project(${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  LANGUAGES CXX C)

set(STATIC_LIB_NAME ${PROJECT_NAME}-static)

set(COBALT_DIR cobalt)
set(LOCAL_COBALT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${COBALT_DIR}/)

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

option(ENABLE_COBALT "ENABLE_COBALT" ON)
if(ENABLE_COBALT)
  find_package(cobalt_starboard_headers_only REQUIRED)
  if(TARGET cobalt_starboard_headers_only::cobalt_starboard_headers_only-static)
    set(cobalt_starboard_headers_only_LIB cobalt_starboard_headers_only::cobalt_starboard_headers_only-static)
  else()
    message(FATAL_ERROR "not supported: using system provided cobalt_starboard_headers_only library")
  endif()
  #
  find_package(cobalt_starboard REQUIRED)
  if(TARGET cobalt_starboard::cobalt_starboard-static)
    set(cobalt_starboard_LIB cobalt_starboard::cobalt_starboard-static)
  else()
    message(FATAL_ERROR "not supported: using system provided cobalt_starboard library")
  endif()
endif(ENABLE_COBALT)

# TODO
#if(NOT DEFINED BASE_STANDALONE)
#  message("FATAL_ERROR: TODO: USE BASE_STANDALONE")
#  set(BASE_STANDALONE TRUE) # TODO
#endif(NOT DEFINED BASE_STANDALONE)

#if(BASE_STANDALONE)
#  set(CHROMIUM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../chromium/)
#  set(COMMON_THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/)
#  set(ICU_PARENT_FULL_DIR ${COMMON_THIRDPARTY_DIR}/icu_wrapper/)
#  set(ICU_FULL_DIR ${ICU_PARENT_FULL_DIR}third_party/icu/)
#  set(BASE_PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
#  set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/base/)
#endif(BASE_STANDALONE)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/GenBuildFlags.cmake)

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

# $<INSTALL_INTERFACE:...> is exported using install(EXPORT)
# $<BUILD_INTERFACE:...> is exported using export(), or when the target is used by another target in the same buildsystem
macro(add_relative_include_dir TARGET VISIBILITY_BUILD VISIBILITY_INSTALL NEW_ELEM)
  target_include_directories(${TARGET}
    ${VISIBILITY_BUILD} "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${NEW_ELEM}>"
    ${VISIBILITY_INSTALL} "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}/${NEW_ELEM}>"
  )
endmacro(add_relative_include_dir)

if(TARGET_LINUX)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/detect_atomic32_support.cmake)
endif(TARGET_LINUX)

add_library(${STATIC_LIB_NAME} STATIC
  ${BASE_SOURCES}
  ${COBALT_port_base_SOURCES}
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
  add_dependencies(${STATIC_LIB_NAME}
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
  add_dependencies(${STATIC_LIB_NAME}
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

#if(TARGET_WINDOWS)
#  list(APPEND EXTRA_STARBOARD_DEFINES
#    STARBOARD_ATOMIC_INCLUDE="starboard/win/x64x11/atomic_public.h"
#    STARBOARD_THREAD_TYPES_INCLUDE="starboard/win/x64x11/thread_types_public.h"
#    STARBOARD_CONFIGURATION_INCLUDE="starboard/win/x64x11/configuration_public.h"
#  )
#elseif(TARGET_LINUX OR TARGET_EMSCRIPTEN)
#  list(APPEND EXTRA_STARBOARD_DEFINES
#    STARBOARD_ATOMIC_INCLUDE="starboard/linux/x64x11/atomic_public.h"
#    STARBOARD_THREAD_TYPES_INCLUDE="starboard/linux/x64x11/thread_types_public.h"
#    STARBOARD_CONFIGURATION_INCLUDE="starboard/linux/x64x11/configuration_public.h"
#  )
#else()
#  message(FATAL_ERROR "platform not supported")
#endif()
#
#target_compile_definitions(${STATIC_LIB_NAME} PUBLIC
#  ${EXTRA_STARBOARD_DEFINES}
#)

if(NOT DEFINED ENABLE_COBALT)
  message(FATAL_ERROR "NOT DEFINED: ENABLE_COBALT")
endif(NOT DEFINED ENABLE_COBALT)
if(ENABLE_COBALT)
  if(NOT DEFINED cobalt_starboard_LIB)
    message(FATAL_ERROR "NOT DEFINED: cobalt_starboard_LIB")
  endif(NOT DEFINED cobalt_starboard_LIB)

  target_link_libraries(${STATIC_LIB_NAME} PUBLIC
    ${cobalt_starboard_LIB}
    ${cobalt_starboard_headers_only_LIB}
  )
endif(ENABLE_COBALT)

#'dependencies': [
#  '<(DEPTH)/nb/nb.gyp:nb',
#  '<(DEPTH)/starboard/client_porting/eztime/eztime.gyp:eztime',
#  '<(DEPTH)/starboard/starboard.gyp:starboard',
#  '<(DEPTH)/testing/gtest.gyp:gtest_prod',
#  '<(DEPTH)/third_party/modp_b64/modp_b64.gyp:modp_b64',
#  'base_static',
#  'third_party/dynamic_annotations/dynamic_annotations.gyp:dynamic_annotations',
#],
target_link_libraries(${STATIC_LIB_NAME} PRIVATE
  # ${cobalt_nanobase_LIB} # TODO: recursion
  # ${STARBOARD_PLATFORM_LIB} # TODO: recursion
  # #starboard_core
  # ${STARBOARD_EZTIME_LIB} # TODO: recursion
  # ${STARBOARD_COMMON_LIB} # TODO: recursion
  ${modp_b64_LIB}
  #
  ${dynamic_annotations_LIB}
  ${EXTRA_CHROMIUM_BASE_LIBS}
  ${LIBATOMIC} # from system, no dep. for __atomic_is_lock_free
  # see https://stackoverflow.com/questions/1236670/how-to-make-opengl-apps-in-64-bit-windows
  #${FOUND_OPENGL_LIBRARIES}
  # ${GLEW_LIBRARY}
  ${PTHREADS_LIBS} # note: not set for emscripten
)

target_link_libraries(${STATIC_LIB_NAME} PUBLIC
  ${CUSTOM_ICU_LIB}
)

if(NOT DEFINED build_util_LIB)
  message(FATAL_ERROR "NOT DEFINED: build_util_LIB")
endif(NOT DEFINED build_util_LIB)

if(USE_TEST_SUPPORT)
  # chromium_libxml
  find_package(chromium_libxml MODULE REQUIRED)
  if(TARGET chromium_libxml::chromium_libxml-static)
    set(libxml_LIB chromium_libxml::chromium_libxml-static)
  else()
    message(FATAL_ERROR "not supported: using system provided chromium_libxml library")
  endif()

  target_link_libraries(${STATIC_LIB_NAME} PUBLIC
    ${libxml_LIB}
    CONAN_PKG::conan_gtest
  )

  target_compile_definitions(${STATIC_LIB_NAME} PRIVATE
    IS_BASE_TEST_IMPL=1
    #PERF_TEST=1
  )
endif(USE_TEST_SUPPORT)

target_link_libraries(${STATIC_LIB_NAME} PUBLIC
  ${build_util_LIB}
)

set_property(TARGET ${STATIC_LIB_NAME} PROPERTY CXX_STANDARD 17)

# POSITION_INDEPENDENT_CODE for -fPIC
# -fPIC may be used to link static library into dynamic one
# Position-independent code requires special support,
# and therefore works only on certain machines.
# see https://akkadia.org/drepper/dsohowto.pdf
set_property(TARGET ${STATIC_LIB_NAME}
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

list(APPEND BASE_DEFINES
  OFFICIAL_BUILD=1
  BASE_PORT=1
)

if(NOT ALLOCATOR_TCMALLOC)
  list(APPEND BASE_DEFINES
    NO_TCMALLOC=1
  )
endif(NOT ALLOCATOR_TCMALLOC)

add_relative_include_dir(${STATIC_LIB_NAME} PUBLIC PUBLIC "")

if(ENABLE_COBALT)
  add_relative_include_dir(${STATIC_LIB_NAME} PUBLIC PUBLIC "${COBALT_DIR}")
endif(ENABLE_COBALT)

# path to base/threading/thread.h

# TODO: COBALT_COMMON_INCLUDES
# add_relative_include_dir(${STATIC_LIB_NAME} PRIVATE PRIVATE "")

if(TARGET_LINUX)
  list(APPEND BASE_EXTRA_DEFINITIONS
    HAVE_MMAP=1
  )
elseif(TARGET_WINDOWS)
  list(APPEND BASE_EXTRA_DEFINITIONS
    COM_INIT_CHECK_HOOK_DISABLED=1
  )
endif()

if(ENABLE_COBALT)
  list(APPEND BASE_EXTRA_DEFINITIONS
    STARBOARD_IMPLEMENTATION=1
    COBALT_IMPLEMENTATION=1
  )
endif(ENABLE_COBALT)

target_compile_definitions(${STATIC_LIB_NAME} PRIVATE
  # TODO
  ${COBALT_COMMON_DEFINES}
)

target_compile_definitions(${STATIC_LIB_NAME} PUBLIC
  # was #include "testing/gtest/include/gtest/gtest.h"
  GTEST_HEADER_INCLUDE="gtest/gtest.h"
  # was #include "testing/gmock/include/gmock/gmock.h"
  GMOCK_HEADER_INCLUDE="gmock/gmock.h"
)

target_compile_definitions(${STATIC_LIB_NAME} PUBLIC
  ${BASE_DEFINES}
  #${WTF_EMCC_DEFINITIONS}
  #${WTF_COMMON_DEFINITIONS}
  ${EXTRA_DEFINES}
  # _HAS_ITERATOR_DEBUGGING=0 # https://github.com/blockspacer/skia-opengl-emscripten/blob/7c423190544c8da1bf8ae79b800c9c0c83dd3c6e/src/chromium/build/config/BUILD.gn#L164
  _USE_MATH_DEFINES=1 # https://stackoverflow.com/a/58379321
  BASE_IMPLEMENTATION=1
  BASE_I18N_IMPLEMENTATION=1
  ${BASE_EXTRA_DEFINITIONS}
  # TODO
  #${COBALT_COMMON_DEFINES}
)

if(TARGET_EMSCRIPTEN)
  # use PROPERTY CXX_STANDARD 17
else()
  target_compile_features(${STATIC_LIB_NAME}
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates)
endif()

if(NOT MSVC OR IS_CLANG_CL)
  target_compile_options(${STATIC_LIB_NAME} PRIVATE
    -Wno-c++11-narrowing
    -Wno-c++98-compat
    -Wno-reserved-id-macro
    -Wno-macro-redefined
    -Wno-implicit-function-declaration
    -Wno-c++11-narrowing
    -Wno-builtin-macro-redefined
    -fno-exceptions # disabling exceptions
  )
elseif(MSVC)
  target_compile_options(${STATIC_LIB_NAME} PRIVATE
    /EHs-c- # disabling exceptions
  )
endif()

set(DEBUG_LIBRARY_SUFFIX "-d")
set_target_properties(${STATIC_LIB_NAME}
  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" # TODO: /lib
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" # TODO: /lib
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" # TODO: /bin
    OUTPUT_NAME "${STATIC_LIB_NAME}$<$<CONFIG:Debug>:${DEBUG_LIBRARY_SUFFIX}>"
)

## ---------------------------- valgrind -------------------------------- ##

if(ENABLE_VALGRIND)
  check_valgrind_config()
endif()

## ---------------------------- sanitizers -------------------------------- ##

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/setup_sanitizers.cmake)

# install and export steps
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Exports.cmake)
