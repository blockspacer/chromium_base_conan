add_custom_target(${BASE_LIB_NAME}_test_data_files ALL
   COMMAND ${CMAKE_COMMAND} -E copy_directory
       ${CMAKE_CURRENT_SOURCE_DIR}/data
       ${CMAKE_CURRENT_BINARY_DIR}/${TESTS_BINARY_DIR_NAME}
   DEPENDS ${BASE_LIB_NAME}
   WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
   COMMENT "Install unit test data")
