generate_all_mojom_cpp_bindings(
  TARGET fortune_cookie
  INPUT ${CMAKE_CURRENT_SOURCE_DIR}/examples/fortune_cookie.mojom
  BYTECODE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.generated/mojo"
  OUTPUT_DIR ".generated/mojo"
  INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  OUTPUT_FILES
    "examples/fortune_cookie.mojom.h"
    "examples/fortune_cookie.mojom.cc"
    "examples/fortune_cookie.mojom-shared.h"
    "examples/fortune_cookie.mojom-shared.cc"
    "examples/fortune_cookie.mojom-module.h"
    "examples/fortune_cookie.mojom-module.cc"
    "examples/fortune_cookie.mojom-module-shared.h"
    "examples/fortune_cookie.mojom-module-shared.cc"
  WORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  TEMPLATE_FILES module.h.tmpl module.cc.tmpl)

set(MOJO_GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.generated/mojo)
message(STATUS "MOJO_GEN_DIR=${MOJO_GEN_DIR}")

# ------- mojo_dummy_example -------

add_executable(mojo_dummy_example
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/mojo_dummy_example.cc
  ${MOJO_GEN_DIR}/examples/fortune_cookie.mojom.cc
  ${MOJO_GEN_DIR}/examples/fortune_cookie.mojom.h
  ${MOJO_GEN_DIR}/examples/fortune_cookie.mojom-shared.cc
  ${MOJO_GEN_DIR}/examples/fortune_cookie.mojom-shared.h
)

add_dependencies(mojo_dummy_example
  fortune_cookie)

target_include_directories(mojo_dummy_example PUBLIC
  ${MOJO_GEN_DIR}
  ${MOJO_GEN_DIR}/mojom
)

target_link_libraries(mojo_dummy_example PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system
  mojo_cpp_platform
  mojo_public_system_cpp
  mojo_core_embedder
  ipc
)

# ------- mojo_cookie_app_consumer -------

add_executable(mojo_cookie_app_consumer
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/mojo_cookie_app_consumer.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/fortune_cookie_impl.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/fortune_cookie_impl.h
  ${MOJO_GEN_DIR}/examples/fortune_cookie.mojom.cc
  ${MOJO_GEN_DIR}/examples/fortune_cookie.mojom.h
  ${MOJO_GEN_DIR}/examples/fortune_cookie.mojom-shared.cc
  ${MOJO_GEN_DIR}/examples/fortune_cookie.mojom-shared.h
)

add_dependencies(mojo_cookie_app_consumer
  fortune_cookie)

target_include_directories(mojo_cookie_app_consumer PUBLIC
  ${MOJO_GEN_DIR}
  ${MOJO_GEN_DIR}/mojom
)

target_link_libraries(mojo_cookie_app_consumer PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system
  mojo_cpp_platform
  mojo_public_system_cpp
  mojo_core_embedder
  ipc
)

# ------- mojo_cookie_app_producer -------

add_executable(mojo_cookie_app_producer
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/mojo_cookie_app_producer.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/fortune_cookie_impl.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/fortune_cookie_impl.h
  ${MOJO_GEN_DIR}/examples/fortune_cookie.mojom.cc
  ${MOJO_GEN_DIR}/examples/fortune_cookie.mojom.h
  ${MOJO_GEN_DIR}/examples/fortune_cookie.mojom-shared.cc
  ${MOJO_GEN_DIR}/examples/fortune_cookie.mojom-shared.h
)

add_dependencies(mojo_cookie_app_producer
  fortune_cookie)

target_include_directories(mojo_cookie_app_producer PUBLIC
  ${MOJO_GEN_DIR}
  ${MOJO_GEN_DIR}/mojom
)

target_link_libraries(mojo_cookie_app_producer PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system
  mojo_cpp_platform
  mojo_public_system_cpp
  mojo_core_embedder
  ipc
)
