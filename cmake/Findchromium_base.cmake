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
find_package(cobalt_starboard_headers_only QUIET)
find_package(cobalt_starboard QUIET)
find_package(Threads QUIET)

list(REMOVE_AT CMAKE_MODULE_PATH -1)

# uses Config.cmake or a -config.cmake file
# see https://gitlab.kitware.com/cmake/community/wikis/doc/tutorials/How-to-create-a-ProjectConfig.cmake-file
# BELOW MUST BE EQUAL TO find_package(... CONFIG QUIET)
# NOTE: find_package(CONFIG) not supported with EMSCRIPTEN, so use include()
include(${CMAKE_CURRENT_LIST_DIR}/cmake/chromium_base-config.cmake)
