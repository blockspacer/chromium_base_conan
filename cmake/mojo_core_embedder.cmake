list(APPEND COMPONENT_MOJO_CORE_EMBEDDER_SOURCES
  "configuration.h"
  "embedder.h"
  "scoped_ipc_support.h"
  "embedder.cc"
  "scoped_ipc_support.cc"
  "features.h"
  "features.cc"
)

list(TRANSFORM COMPONENT_MOJO_CORE_EMBEDDER_SOURCES
  PREPEND "${MOJO_SOURCES_PATH}/core/embedder/")

add_library(mojo_core_embedder
  ${COMPONENT_MOJO_CORE_EMBEDDER_SOURCES}
)

target_link_libraries(mojo_core_embedder PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system_cpp
  mojo_core
)

target_compile_definitions(mojo_core_embedder PRIVATE
  IS_MOJO_CORE_EMBEDDER_FEATURES_IMPL=1
  IS_MOJO_CORE_EMBEDDER_IMPL=1
)
