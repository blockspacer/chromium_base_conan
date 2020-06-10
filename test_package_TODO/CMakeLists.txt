cmake_minimum_required(VERSION 2.8.11)

project(test_package CXX)

message(STATUS "Loading conan scripts for {0} dependencies...")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
include("${CMAKE_BINARY_DIR}/conan_paths.cmake" OPTIONAL)
message(STATUS "Doing conan basic setup")
conan_basic_setup()

#list(APPEND CMAKE_PROGRAM_PATH ${CONAN_BIN_DIRS})

# TODO: make better: link lib dirs
link_directories(${CONAN_LIB_DIRS})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_executable(testme
    main.cpp
)

find_package(chromium_base REQUIRED)
if(TARGET chromium_base::chromium_base-static)
  set(base_LIB chromium_base::chromium_base-static)
else()
  message(FATAL_ERROR "not supported: using system provided chromium_base library")
endif()

# modp_b64
find_package(chromium_modp_b64 REQUIRED)
if(TARGET chromium_modp_b64::chromium_modp_b64-static)
  set(modp_b64_LIB chromium_modp_b64::chromium_modp_b64-static)
else()
  message(FATAL_ERROR "not supported: using system provided modp_b64 library")
endif()

target_link_libraries(testme PRIVATE
  #${USED_3DPARTY_LIBS}
  #${USED_SYSTEM_LIBS}
  ${base_LIB}
  #${modp_b64_LIB}
  #${STATIC_LIB_NAME}
  #chromium_base-static
)
