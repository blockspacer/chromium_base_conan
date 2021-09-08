add_executable(mojo_receiver_example
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/mojo_receiver_example.cc
)

target_link_libraries(mojo_receiver_example PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system
  mojo_cpp_platform
  mojo_public_system_cpp
  mojo_core_embedder
  ipc
)
