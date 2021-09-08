list(APPEND IPC_SOURCES
  "ipc_message_utils.cc"
  "ipc_message_utils.h"
  "ipc_mojo_param_traits.cc"
  "ipc_mojo_param_traits.h"
  "param_traits_log_macros.h"
  "param_traits_macros.h"
  "param_traits_read_macros.h"
  "param_traits_write_macros.h"
  "struct_constructor_macros.h"
)

if (NOT TARGET_IOS)
  list(APPEND IPC_SOURCES
    # Most sources go here since ios only needs the param_traits
    # code.
    "ipc_channel.h"
    "ipc_channel_common.cc"
    "ipc_channel_factory.cc"
    "ipc_channel_factory.h"
    "ipc_channel_handle.h"
    "ipc_channel_mojo.cc"
    "ipc_channel_mojo.h"
    "ipc_channel_proxy.cc"
    "ipc_channel_proxy.h"
    "ipc_channel_reader.cc"
    "ipc_channel_reader.h"
    "ipc_listener.h"
    "ipc_logging.cc"
    "ipc_logging.h"
    "ipc_message_macros.h"
    "ipc_message_pipe_reader.cc"
    "ipc_message_pipe_reader.h"
    "ipc_message_start.h"
    "ipc_message_templates.h"
    "ipc_message_templates_impl.h"
    "ipc_mojo_bootstrap.cc"
    "ipc_mojo_bootstrap.h"
    "ipc_sender.h"
    "ipc_sync_channel.cc"
    "ipc_sync_channel.h"
    "ipc_sync_message_filter.cc"
    "ipc_sync_message_filter.h"
    "message_filter.cc"
    "message_filter.h"
    "message_filter_router.cc"
    "message_filter_router.h"
    "message_router.cc"
    "message_router.h"
    "trace_ipc_message.cc"
    "trace_ipc_message.h"
  )
endif()

if (TARGET_NACL AND NOT TARGET_NACL_NONSFI)
  list(APPEND IPC_SOURCES
    "ipc_channel_nacl.cc"
    "ipc_channel_nacl.h"
  )
else()
  list(APPEND IPC_SOURCES
    "ipc_channel.cc"
  )
endif()

if (NOT TARGET_NACL_NONSFI)
  list(APPEND IPC_SOURCES
    "ipc_message_protobuf_utils.h"
  )
endif()

# source_set("native_handle_type_converters")
list(APPEND IPC_SOURCES
  "native_handle_type_converters.cc"
  "native_handle_type_converters.h"
)

# source_set("param_traits")
list(APPEND IPC_SOURCES
  "ipc_param_traits.h"
)

# component("message_support")
list(APPEND IPC_SOURCES
  "ipc_message.cc"
  "ipc_message.h"
  "ipc_message_attachment.cc"
  "ipc_message_attachment.h"
  "ipc_message_attachment_set.cc"
  "ipc_message_attachment_set.h"
  "ipc_message_support_export.h"
  "ipc_mojo_handle_attachment.cc"
  "ipc_mojo_handle_attachment.h"
  "ipc_mojo_message_helper.cc"
  "ipc_mojo_message_helper.h"
  "ipc_platform_file.cc"
  "ipc_platform_file.h"
  "ipc_sync_message.cc"
  "ipc_sync_message.h"
)

if (TARGET_WINDOWS)
  list(APPEND IPC_SOURCES
    "handle_attachment_win.cc"
    "handle_attachment_win.h"
    "handle_win.cc"
    "handle_win.h"
  )
endif()

if (TARGET_POSIX OR TARGET_FUCHSIA)
  list(APPEND IPC_SOURCES
    "ipc_platform_file_attachment_posix.cc"
    "ipc_platform_file_attachment_posix.h"
  )
endif()

if (TARGET_MACOS)
  list(APPEND IPC_SOURCES
    "mach_port_attachment_mac.cc"
    "mach_port_attachment_mac.h"
    "mach_port_mac.cc"
    "mach_port_mac.h"
  )
endif()

if (TARGET_FUCHSIA)
  list(APPEND IPC_SOURCES
    "handle_attachment_fuchsia.cc"
    "handle_attachment_fuchsia.h"
  )
endif()

# mojom_component("mojom")
list(APPEND IPC_SOURCES
  "message_mojom_traits.cc"
  "message_view.cc"
  "message_view.h"
)

list(APPEND IPC_MOJOM_SOURCES
  "ipc.mojom-shared.cc"
  "ipc.mojom.cc"
)

list(TRANSFORM IPC_SOURCES
  PREPEND "${IPC_SOURCES_PATH}/")

# TODO
# mojom("test_interfaces") {
#   testonly = true
#   sources = [ "ipc_test.mojom" ]
#   support_lazy_serialization = true
# }

# mojom_constants
list(APPEND IPC_MOJOM_SOURCES
  "constants.mojom-shared.cc"
  "constants.mojom.cc"
)

list(TRANSFORM IPC_MOJOM_SOURCES
  PREPEND "${IPC_SOURCES_PATH}/../gen/ipc/")

add_library(ipc
  ${IPC_SOURCES}
  ${IPC_MOJOM_SOURCES}
)

target_sources(ipc PUBLIC
  ${IPC_SOURCES_PATH}/ipc_buildflags.h
)

target_include_directories(ipc PUBLIC
  "${IPC_SOURCES_PATH}/../gen/"
)

target_link_libraries(ipc PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system
  mojo_cpp_platform
  mojo_public_system_cpp
  mojo_public_interfaces_bindings
  mojo_public_cpp_bindings
)

# TODO
# if (enable_ipc_fuzzer) {
#   public_configs = [ "//tools/ipc_fuzzer:ipc_fuzzer_config" ]
# }

target_compile_definitions(ipc PRIVATE
  IS_IPC_IMPL=1
  IPC_MESSAGE_SUPPORT_IMPL=1
)
