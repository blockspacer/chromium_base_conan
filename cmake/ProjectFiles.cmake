include_guard( DIRECTORY )

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources.cmake)
#
if(TARGET_POSIX)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources_posix.cmake)
endif()
#
if(TARGET_LINUX)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources_linux.cmake)
endif()
#
if(TARGET_WINDOWS)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources_win.cmake)
endif()
#
if(TARGET_MACOS)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources_mac.cmake)
endif()
#
if(TARGET_IOS)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources_ios.cmake)
endif()
#
if(TARGET_ANDROID)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources_android.cmake)
endif()
#
if(TARGET_MACOS OR TARGET_IOS)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources_apple.cmake)
endif()
#
# TODO move to separate lib
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib_base_static.cmake)
#
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_i18n.cmake)
#
message(STATUS "COMPONENT_BASE_SOURCES=${COMPONENT_BASE_SOURCES}")

if(USE_ALLOC_SHIM)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources_allocator_shim.cmake)
endif()

if(NOT USE_NACL AND BASE_USE_PARTITION_ALLOCATOR)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources_partition_allocator.cmake)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib_test_config.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib_test_support.cmake)

# NOTE: *filter.cmake must be LAST included file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources_filter.cmake)

list(TRANSFORM COMPONENT_BASE_SOURCES PREPEND ${BASE_SOURCES_PATH})
list(APPEND BASE_SOURCES ${COMPONENT_BASE_SOURCES})
