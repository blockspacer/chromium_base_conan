cmake_minimum_required(VERSION 3.0)

project(WorkspaceProject)

include(${CMAKE_BINARY_DIR}/conanworkspace.cmake)

list(PREPEND CMAKE_MODULE_PATH "${PACKAGE_chromium_base_SRC}/cmake")

conan_workspace_subdirectories()
