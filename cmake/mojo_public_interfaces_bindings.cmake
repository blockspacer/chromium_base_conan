list(APPEND GEN_MOJO_PUBLIC_INTERFACES_BINDINGS
  interface_control_messages.mojom.cc
  interface_control_messages.mojom-shared.cc
  #
  native_struct.mojom.cc
  native_struct.mojom-shared.cc
  #
  pipe_control_messages.mojom.cc
  pipe_control_messages.mojom-shared.cc
)

list(TRANSFORM GEN_MOJO_PUBLIC_INTERFACES_BINDINGS
  PREPEND "${MOJO_SOURCES_PATH}/../gen/mojo/public/interfaces/bindings/")

add_library(mojo_public_interfaces_bindings
  ${GEN_MOJO_PUBLIC_INTERFACES_BINDINGS}
)

target_include_directories(mojo_public_interfaces_bindings PUBLIC
  "${MOJO_SOURCES_PATH}/../gen/"
)

target_link_libraries(mojo_public_interfaces_bindings PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system
  mojo_cpp_platform
  mojo_public_system_cpp
)

#list(APPEND MOJO_PUBLIC_INTERFACES_BINDINGS_SOURCES
#  "interface_control_messages.mojom"
#  "native_struct.mojom"
#  "pipe_control_messages.mojom"
#)
#
#list(TRANSFORM MOJO_PUBLIC_INTERFACES_BINDINGS_SOURCES
#  PREPEND "${MOJO_SOURCES_PATH}public/cpp/bindings/")
#
#foreach(component IN LISTS MOJO_PUBLIC_INTERFACES_BINDINGS_SOURCES)
#  generate_mojom_bindings(
#    INPUT ${component} OUTPUT ${component}.mojom.cc TMP_FILE ${component}.mojom.cc.tmp)
#endforeach()
