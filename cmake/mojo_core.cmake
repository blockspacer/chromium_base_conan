list(APPEND COMPONENT_MOJO_CORE_SOURCES
  "channel.h"
  "configuration.h"
  "connection_params.h"
  "core.h"
  "data_pipe_consumer_dispatcher.h"
  "data_pipe_control_message.h"
  "data_pipe_producer_dispatcher.h"
  "dispatcher.h"
  "embedder/configuration.h"
  "embedder/process_error_callback.h"
  "entrypoints.h"
  "handle_signals_state.h"
  "handle_table.h"
  "invitation_dispatcher.h"
  "message_pipe_dispatcher.h"
  "node_channel.h"
  "node_controller.h"
  "options_validation.h"
  "platform_handle_dispatcher.h"
  "platform_handle_utils.h"
  "platform_shared_memory_mapping.h"
  "request_context.h"
  "shared_buffer_dispatcher.h"
  "user_message_impl.h"
  "atomic_flag.h"
  "broker.h"
  "channel.cc"
  "configuration.cc"
  "connection_params.cc"
  "core.cc"
  "data_pipe_consumer_dispatcher.cc"
  "data_pipe_control_message.cc"
  "data_pipe_producer_dispatcher.cc"
  "dispatcher.cc"
  "entrypoints.cc"
  "handle_table.cc"
  "invitation_dispatcher.cc"
  "message_pipe_dispatcher.cc"
  "node_channel.cc"
  "node_controller.cc"
  "platform_handle_dispatcher.cc"
  "platform_handle_in_transit.cc"
  "platform_handle_in_transit.h"
  "platform_handle_utils.cc"
  "platform_shared_memory_mapping.cc"
  "request_context.cc"
  "shared_buffer_dispatcher.cc"
  "user_message_impl.cc"
  "watch.cc"
  "watch.h"
  "watcher_dispatcher.cc"
  "watcher_dispatcher.h"
  "watcher_set.cc"
  "watcher_set.h"
)

if (TARGET_FUCHSIA)
  list(APPEND COMPONENT_MOJO_CORE_SOURCES
    "channel_fuchsia.cc"
  )
  # public_deps += [ "//third_party/fuchsia-sdk/sdk/pkg/fdio" ]
endif()

if (TARGET_POSIX AND NOT TARGET_MAC)
  if (NOT TARGET_NACL OR TARGET_NONSFI)
    list(APPEND COMPONENT_MOJO_CORE_SOURCES
      "broker_posix.cc"
      "channel_posix.cc"
      "channel_posix.h"
    )
  endif()

  if ((TARGET_LINUX OR TARGET_CHROMEOS OR TARGET_ANDROID) AND NOT TARGET_NACL)
    list(APPEND COMPONENT_MOJO_CORE_SOURCES
      "channel_linux.cc"
      "channel_linux.h"
    )
  endif()
endif()

if (TARGET_MAC)
  list(APPEND COMPONENT_MOJO_CORE_SOURCES
    "channel_mac.cc"
  )
endif()

if (NOT TARGET_NACL OR TARGET_NONSFI)
  list(APPEND COMPONENT_MOJO_CORE_SOURCES
    "broker_host.cc"
    "broker_host.h"
  )
endif()

if (TARGET_WIN)
  list(APPEND COMPONENT_MOJO_CORE_SOURCES
    "broker_win.cc"
    "channel_win.cc"
  )
endif()

list(APPEND COMPONENT_MOJO_CORE_SOURCES
  "mojo_core.cc"
)

#     # Use target_os == "chromeos" instead of is_chromeos because we need to
#     # build NaCl targets (i.e. IRT) for ChromeOS the same as the rest of ChromeOS.
#     if (is_android || target_os == "chromeos" ||
#         (target_os == "linux" && chromeos_is_browser_only)) {
#       defines += [ "MOJO_CORE_LEGACY_PROTOCOL" ]
#     }
if (TARGET_ANDROID OR TARGET_CHROMEOS) # OR?
  target_compile_definitions(mojo_core PRIVATE
    MOJO_CORE_LEGACY_PROTOCOL=1
  )
endif()

list(TRANSFORM COMPONENT_MOJO_CORE_SOURCES
  PREPEND "${MOJO_SOURCES_PATH}/core/")

add_library(mojo_core
  ${COMPONENT_MOJO_CORE_SOURCES}
)

target_link_libraries(mojo_core PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system_cpp
  mojo_cpp_platform
  mojo_core_ports
)

#     if (invoker.for_shared_library) {
#       defines += [ "MOJO_CORE_SHARED_LIBRARY" ]
#     } else {
#       defines += [ "MOJO_SYSTEM_IMPL_IMPLEMENTATION" ]
#     }
if (BUILD_SHARED_LIBS)
  target_compile_definitions(mojo_core PRIVATE
    MOJO_CORE_SHARED_LIBRARY=1
  )
else()
  target_compile_definitions(mojo_core PRIVATE
    MOJO_SYSTEM_IMPL_IMPLEMENTATION=1
  )
endif()
