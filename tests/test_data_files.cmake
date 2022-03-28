add_executable(test_child_process
  ${BASE_SOURCES_PATH}/test/test_child_process.cc
)

target_link_libraries(test_child_process PUBLIC
  ${BASE_LIB_NAME}
)

# ----

add_custom_target(copy_testdata
   COMMAND ${CMAKE_COMMAND} -E copy_directory
       ${CMAKE_CURRENT_SOURCE_DIR}/data
       ${CMAKE_CURRENT_BINARY_DIR}/${TESTS_BINARY_DIR_NAME})

add_dependencies(copy_testdata
  ${BASE_LIB_NAME}
)

set(test_child_process_path
  "${CMAKE_CURRENT_BINARY_DIR}/${TESTS_BINARY_DIR_NAME}/test_child_process")

set_target_properties(test_child_process PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${TESTS_BINARY_DIR_NAME}/)

# ----

add_library(immediate_crash_test_helper SHARED
  ${BASE_SOURCES_PATH}/test/immediate_crash_test_helper.cc
)

target_link_libraries(immediate_crash_test_helper PUBLIC
  ${BASE_LIB_NAME}
)

set(immediate_crash_test_helper_path
  "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}immediate_crash_test_helper${CMAKE_SHARED_LIBRARY_SUFFIX}")

set(immediate_crash_test_helper_copy
  ${CMAKE_CURRENT_BINARY_DIR}/${TESTS_BINARY_DIR_NAME}/${CMAKE_SHARED_LIBRARY_PREFIX}immediate_crash_test_helper${CMAKE_SHARED_LIBRARY_SUFFIX}
)

message(STATUS "in immediate_crash_test_helper_path=${immediate_crash_test_helper_path}")
message(STATUS "out immediate_crash_test_helper_path=${immediate_crash_test_helper_copy}")

add_custom_target(immediate_crash_test_helper_copy
  COMMAND ${CMAKE_COMMAND} -E copy
    ${immediate_crash_test_helper_path}
    ${immediate_crash_test_helper_copy})

add_dependencies(immediate_crash_test_helper_copy
  immediate_crash_test_helper
)

# ----

add_library(test_shared_library SHARED
  ${BASE_SOURCES_PATH}/test/test_shared_library.cc
)

target_link_libraries(test_shared_library PUBLIC
  ${BASE_LIB_NAME}
)

set(test_shared_library_path
  "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}test_shared_library${CMAKE_SHARED_LIBRARY_SUFFIX}")

set(test_shared_library_copy
  ${CMAKE_CURRENT_BINARY_DIR}/${TESTS_BINARY_DIR_NAME}/${CMAKE_SHARED_LIBRARY_PREFIX}test_shared_library${CMAKE_SHARED_LIBRARY_SUFFIX}
)

message(STATUS "in test_shared_library_path=
  ${test_shared_library_path}")
message(STATUS "test_shared_library_copy=
  ${test_shared_library_copy}")

add_custom_target(test_shared_library_copy
  COMMAND ${CMAKE_COMMAND} -E copy
    ${test_shared_library_path}
    ${test_shared_library_copy})

add_dependencies(test_shared_library_copy
  test_shared_library
)


# ----

# add_library(dummy_library SHARED
#   ${BASE_SOURCES_PATH}/test/dummy_library.cc
# )
#
# target_link_libraries(dummy_library PUBLIC
#   ${BASE_LIB_NAME}
# )
#
# set(dummy_library_path
#   "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}dummy_library${CMAKE_SHARED_LIBRARY_SUFFIX}")
#
# set(dummy_library_copy
#   ${CMAKE_CURRENT_BINARY_DIR}/${TESTS_BINARY_DIR_NAME}/${CMAKE_SHARED_LIBRARY_PREFIX}dummy_library${CMAKE_SHARED_LIBRARY_SUFFIX}
# )
#
# message(STATUS "in dummy_library_path=
#   ${dummy_library_path}")
# message(STATUS "dummy_library_copy=
#   ${dummy_library_copy}")
#
# add_custom_target(dummy_library_copy
#   COMMAND ${CMAKE_COMMAND} -E copy
#     ${dummy_library_path}
#     ${dummy_library_copy})
#
# add_dependencies(dummy_library_copy
#   dummy_library
# )

add_custom_target(${BASE_LIB_NAME}_test_data_files
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  COMMENT "Install unit test data")

add_dependencies(${BASE_LIB_NAME}_test_data_files
  ${BASE_LIB_NAME}
)

add_dependencies(${BASE_LIB_NAME}_test_data_files
  copy_testdata
)

add_dependencies(${BASE_LIB_NAME}_test_data_files
  immediate_crash_test_helper
)

add_dependencies(${BASE_LIB_NAME}_test_data_files
  immediate_crash_test_helper_copy
)

add_dependencies(${BASE_LIB_NAME}_test_data_files
  test_shared_library
)

add_dependencies(${BASE_LIB_NAME}_test_data_files
  test_shared_library_copy
)

# add_dependencies(${BASE_LIB_NAME}_test_data_files
#   dummy_library
# )
#
# add_dependencies(${BASE_LIB_NAME}_test_data_files
#   dummy_library_copy
# )
