list(APPEND COMPONENT_MOJO_PUBLIC_CPP_SYSTEM_SOURCES
  "buffer.cc"
  "buffer.h"
  "core.h"
  "data_pipe.h"
  "data_pipe_drainer.cc"
  "data_pipe_drainer.h"
  "data_pipe_producer.cc"
  "data_pipe_producer.h"
  "data_pipe_utils.cc"
  "data_pipe_utils.h"
  "dynamic_library_support.cc"
  "dynamic_library_support.h"
  "file_data_source.cc"
  "file_data_source.h"
  "filtered_data_source.cc"
  "filtered_data_source.h"
  "functions.cc"
  "functions.h"
  "handle.h"
  "handle_signal_tracker.cc"
  "handle_signal_tracker.h"
  "handle_signals_state.h"
  "invitation.cc"
  "invitation.h"
  "isolated_connection.cc"
  "isolated_connection.h"
  "message.h"
  "message_pipe.cc"
  "message_pipe.h"
  "platform_handle.cc"
  "platform_handle.h"
  "scope_to_message_pipe.cc"
  "scope_to_message_pipe.h"
  "simple_watcher.cc"
  "simple_watcher.h"
  "string_data_source.cc"
  "string_data_source.h"
  "system_export.h"
  "trap.cc"
  "trap.h"
  "wait.cc"
  "wait.h"
  "wait_set.cc"
  "wait_set.h"
)

if(NOT USE_NACL)
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${COMPONENT_MOJO_PUBLIC_CPP_SYSTEM_SOURCES}
    OUTPUT COMPONENT_MOJO_PUBLIC_CPP_SYSTEM_SOURCES
    ITEMS
    "file_data_source.cc"
  )
endif()

list(TRANSFORM COMPONENT_MOJO_PUBLIC_CPP_SYSTEM_SOURCES
  PREPEND "${MOJO_SOURCES_PATH}/public/cpp/system/")

add_library(mojo_public_system_cpp
  ${COMPONENT_MOJO_PUBLIC_CPP_SYSTEM_SOURCES}
)

target_link_libraries(mojo_public_system_cpp PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system
  mojo_cpp_platform
)

target_compile_definitions(mojo_public_system_cpp PRIVATE
  MOJO_CPP_SYSTEM_IMPLEMENTATION=1
)
