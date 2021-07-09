list(APPEND COMPONENT_MOJO_PUBLIC_CPP_PLATFORM_SOURCES
  "platform_channel.h"
  "platform_channel_endpoint.h"
  "platform_channel_server_endpoint.h"
  "platform_handle.h"
  "platform_channel.cc"
  "platform_channel_endpoint.cc"
  "platform_channel_server_endpoint.cc"
  "platform_handle.cc"
)

if (TARGET_POSIX AND NOT TARGET_MACOS AND (NOT TARGET_NACL OR TARGET_NONSFI))
  list(APPEND COMPONENT_MOJO_PUBLIC_CPP_PLATFORM_SOURCES
    "socket_utils_posix.h"
    "socket_utils_posix.cc"
  )
endif()

if (TARGET_POSIX AND NOT TARGET_NACL AND NOT TARGET_MACOS)
  list(APPEND COMPONENT_MOJO_PUBLIC_CPP_PLATFORM_SOURCES
    "named_platform_channel_posix.cc"
  )
endif()

if (TARGET_MACOS)
  list(APPEND COMPONENT_MOJO_PUBLIC_CPP_PLATFORM_SOURCES
    "named_platform_channel_mac.cc"
  )
endif()

if (TARGET_WNDOWS)
  list(APPEND COMPONENT_MOJO_PUBLIC_CPP_PLATFORM_SOURCES
    "named_platform_channel_win.cc"
  )
endif()

if (TARGET_FUCHSIA)
  # TODO
  #public_deps += [
  #  "//third_party/fuchsia-sdk/sdk/pkg/fdio"
  #  "//third_party/fuchsia-sdk/sdk/pkg/zx"
  #]
else()
  list(APPEND COMPONENT_MOJO_PUBLIC_CPP_PLATFORM_SOURCES
    "named_platform_channel.cc"
    "named_platform_channel.h"
  )
endif()

list(TRANSFORM COMPONENT_MOJO_PUBLIC_CPP_PLATFORM_SOURCES
  PREPEND "${MOJO_SOURCES_PATH}/public/cpp/platform/")

add_library(mojo_cpp_platform
  ${COMPONENT_MOJO_PUBLIC_CPP_PLATFORM_SOURCES}
)

target_link_libraries(mojo_cpp_platform PUBLIC
  ${BASE_LIB_NAME}
)

target_compile_definitions(mojo_cpp_platform PRIVATE
  IS_MOJO_CPP_PLATFORM_IMPL=1
)
