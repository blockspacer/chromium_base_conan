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

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources_utils.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib_test_config.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib_test_support.cmake)

if(TARGET_ANDROID OR TARGET_CHROMEOS_ASH)
  list(APPEND COMPONENT_BASE_SOURCES
    "time/time_android.cc"
  )
endif()

if(ENABLE_TESTS)
  list(APPEND COMPONENT_BASE_SOURCES
    "task/test_task_traits_extension.cc"
    "task/test_task_traits_extension.h"
  )
endif()

# NOTE: *filter.cmake must be LAST included file from `${CMAKE_CURRENT_SOURCE_DIR}/cmake/*`
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_base_sources_filter.cmake)

list(TRANSFORM COMPONENT_BASE_SOURCES PREPEND ${BASE_SOURCES_PATH})
list(APPEND BASE_SOURCES ${COMPONENT_BASE_SOURCES})

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_extensions_basic_sources.cmake)
list(TRANSFORM COMPONENT_BASIC_SOURCES PREPEND "../extensions/basic/")
list(TRANSFORM COMPONENT_BASIC_SOURCES PREPEND ${BASE_SOURCES_PATH})
list(APPEND BASE_SOURCES ${COMPONENT_BASIC_SOURCES})

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_extensions_crypto_sources.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_extensions_crypto_sources_filter.cmake)
list(TRANSFORM COMPONENT_CRYPTO_SOURCES PREPEND "../extensions/crypto/")
list(TRANSFORM COMPONENT_CRYPTO_SOURCES PREPEND ${BASE_SOURCES_PATH})
list(APPEND BASE_SOURCES ${COMPONENT_CRYPTO_SOURCES})

# NOTE: `${CMAKE_CURRENT_SOURCE_DIR}/extensions/*` must be LAST included file and filtered manually
include(${CMAKE_CURRENT_SOURCE_DIR}/extensions/testing_sources.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/extensions/base/third_party/lib_symbolize.cmake)
