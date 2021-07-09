list(APPEND COMPONENT_MOJO_PUBLIC_C_SYSTEM_SOURCES
  "thunks.cc"
  "buffer.h"
  "core.h"
  "data_pipe.h"
  "functions.h"
  "invitation.h"
  "macros.h"
  "message_pipe.h"
  "platform_handle.h"
  "system_export.h"
  "thunks.h"
  "trap.h"
  "types.h"
)

list(TRANSFORM COMPONENT_MOJO_PUBLIC_C_SYSTEM_SOURCES
  PREPEND "${MOJO_SOURCES_PATH}/public/c/system/")

add_library(mojo_public_system
  ${COMPONENT_MOJO_PUBLIC_C_SYSTEM_SOURCES}
)

target_link_libraries(mojo_public_system PUBLIC
  ${BASE_LIB_NAME}
)

target_compile_definitions(mojo_public_system PRIVATE
  MOJO_SYSTEM_IMPLEMENTATION=1
)
