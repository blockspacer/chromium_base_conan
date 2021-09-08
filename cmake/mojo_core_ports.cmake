list(APPEND COMPONENT_MOJO_CORE_PORTS_SOURCES
  "event.cc"
  "event.h"
  "message_filter.h"
  "message_queue.cc"
  "message_queue.h"
  "name.cc"
  "name.h"
  "node.cc"
  "node.h"
  "node_delegate.h"
  "port.cc"
  "port.h"
  "port_locker.cc"
  "port_locker.h"
  "port_ref.cc"
  "port_ref.h"
  "user_data.h"
  "user_message.cc"
  "user_message.h"
)

list(TRANSFORM COMPONENT_MOJO_CORE_PORTS_SOURCES
  PREPEND "${MOJO_SOURCES_PATH}/core/ports/")

add_library(mojo_core_ports
  ${COMPONENT_MOJO_CORE_PORTS_SOURCES}
)

target_link_libraries(mojo_core_ports PUBLIC
  ${BASE_LIB_NAME}
)

target_compile_definitions(mojo_core_ports PRIVATE
  IS_MOJO_CORE_PORTS_IMPL=1
)
