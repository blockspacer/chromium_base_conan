get_filename_component(CURRENT_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
list(APPEND CMAKE_MODULE_PATH ${CURRENT_CMAKE_DIR})

#include(CMakeFindDependencyMacro) # use find_package instead

# NOTE: some packages may be optional (platform-specific, etc.)
find_package(chromium_build_util REQUIRED)
find_package(chromium_icu QUIET)
find_package(chromium_dynamic_annotations QUIET)
find_package(chromium_tcmalloc QUIET)
find_package(chromium_xdg_user_dirs QUIET)
find_package(chromium_xdg_mime QUIET)
find_package(chromium_libevent QUIET)
find_package(chromium_modp_b64 QUIET)
find_package(chromium_compact_enc_det QUIET)
find_package(Threads QUIET)
find_package(abseil QUIET)
find_package(perfetto QUIET)
find_package(double-conversion QUIET)
find_package(protobuf QUIET)
find_package(fmt QUIET)
find_package(boost QUIET)

# see use_test_support option in base
find_package(chromium_libxml QUIET)

list(REMOVE_AT CMAKE_MODULE_PATH -1)

set(chromium_base_LIB chromium_base::chromium_base)
# conan package has '/include' dir
set(chromium_base_HEADER_DIR
  ${CONAN_CHROMIUM_BASE_ROOT}/include
)
# used by https://docs.conan.io/en/latest/developing_packages/workspaces.html
if(TARGET chromium_base)
  # name of created target
  set(chromium_base_LIB chromium_base)
  # no '/include' dir on local build
  set(chromium_base_HEADER_DIR
    ${CONAN_CHROMIUM_BASE_ROOT}
  )
endif()

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/cmake/chromium_base-config.cmake")
  # uses Config.cmake or a -config.cmake file
  # see https://gitlab.kitware.com/cmake/community/wikis/doc/tutorials/How-to-create-a-ProjectConfig.cmake-file
  # BELOW MUST BE EQUAL TO find_package(... CONFIG REQUIRED)
  # NOTE: find_package(CONFIG) not supported with EMSCRIPTEN, so use include()
  include(${CMAKE_CURRENT_LIST_DIR}/cmake/chromium_base-config.cmake)
endif()

set(base_LIB ${chromium_base_LIB})
message(STATUS "base_LIB=${base_LIB}")
message(STATUS "chromium_base_HEADER_DIR=${chromium_base_HEADER_DIR}")
