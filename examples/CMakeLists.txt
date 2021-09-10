precompile_mojom_bindings(
  TARGET precompile_mojom
  OUTPUT_DIR ".generated/mojo"
  WORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

generate_all_mojom_cpp_bindings(
  TARGET rect_mojom
  INPUT ${CMAKE_CURRENT_SOURCE_DIR}/examples/mojom/rect/rect.mojom
  BYTECODE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.generated/mojo"
  OUTPUT_DIR ".generated/mojo"
  INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  BYPRODUCTS
    "examples/mojom/rect/rect.mojom-module"
  OUTPUT_FILES
    "examples/mojom/rect/rect.mojom.h"
    "examples/mojom/rect/rect.mojom.cc"
    "examples/mojom/rect/rect.mojom-shared.h"
    "examples/mojom/rect/rect.mojom-shared.cc"
    "examples/mojom/rect/rect.mojom-module.h"
    "examples/mojom/rect/rect.mojom-module.cc"
    "examples/mojom/rect/rect.mojom-module-shared.h"
    "examples/mojom/rect/rect.mojom-module-shared.cc"
  WORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
)

generate_all_mojom_cpp_bindings(
  TARGET fortune_cookie_mojom
  INPUT ${CMAKE_CURRENT_SOURCE_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom
  BYTECODE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.generated/mojo"
  OUTPUT_DIR ".generated/mojo"
  INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  BYPRODUCTS
    "examples/mojom/fortune_cookie/fortune_cookie.mojom-module"
  OUTPUT_FILES
    "examples/mojom/fortune_cookie/fortune_cookie.mojom.h"
    "examples/mojom/fortune_cookie/fortune_cookie.mojom.cc"
    "examples/mojom/fortune_cookie/fortune_cookie.mojom-shared.h"
    "examples/mojom/fortune_cookie/fortune_cookie.mojom-shared.cc"
    "examples/mojom/fortune_cookie/fortune_cookie.mojom-module.h"
    "examples/mojom/fortune_cookie/fortune_cookie.mojom-module.cc"
    "examples/mojom/fortune_cookie/fortune_cookie.mojom-module-shared.h"
    "examples/mojom/fortune_cookie/fortune_cookie.mojom-module-shared.cc"
  WORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_dependencies(fortune_cookie_mojom
  parse_mojom_rect_mojom)

add_dependencies(fortune_cookie_mojom
  rect_mojom)

set(MOJO_GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.generated/mojo)
message(STATUS "MOJO_GEN_DIR=${MOJO_GEN_DIR}")

# ------- mojo_dummy_example -------

add_executable(mojo_dummy_example
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/mojo_dummy_example.cc
  ${MOJO_GEN_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom.cc
  ${MOJO_GEN_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom.h
  ${MOJO_GEN_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom-shared.cc
  ${MOJO_GEN_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom-shared.h
  ${MOJO_GEN_DIR}/examples/mojom/rect/rect.mojom.cc
  ${MOJO_GEN_DIR}/examples/mojom/rect/rect.mojom.h
  ${MOJO_GEN_DIR}/examples/mojom/rect/rect.mojom-shared.cc
  ${MOJO_GEN_DIR}/examples/mojom/rect/rect.mojom-shared.h
)

add_dependencies(mojo_dummy_example
  fortune_cookie_mojom)

add_dependencies(mojo_dummy_example
  rect_mojom)

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
  ${MOJO_GEN_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom.cc
  ${MOJO_GEN_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom.h
  ${MOJO_GEN_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom-shared.cc
  ${MOJO_GEN_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom-shared.h
  ${MOJO_GEN_DIR}/examples/mojom/rect/rect.mojom.cc
  ${MOJO_GEN_DIR}/examples/mojom/rect/rect.mojom.h
  ${MOJO_GEN_DIR}/examples/mojom/rect/rect.mojom-shared.cc
  ${MOJO_GEN_DIR}/examples/mojom/rect/rect.mojom-shared.h
)

add_dependencies(mojo_cookie_app_consumer
  fortune_cookie_mojom)

add_dependencies(mojo_cookie_app_consumer
  rect_mojom)

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
  ${MOJO_GEN_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom.cc
  ${MOJO_GEN_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom.h
  ${MOJO_GEN_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom-shared.cc
  ${MOJO_GEN_DIR}/examples/mojom/fortune_cookie/fortune_cookie.mojom-shared.h
  ${MOJO_GEN_DIR}/examples/mojom/rect/rect.mojom.cc
  ${MOJO_GEN_DIR}/examples/mojom/rect/rect.mojom.h
  ${MOJO_GEN_DIR}/examples/mojom/rect/rect.mojom-shared.cc
  ${MOJO_GEN_DIR}/examples/mojom/rect/rect.mojom-shared.h
)

add_dependencies(mojo_cookie_app_producer
  fortune_cookie_mojom)

add_dependencies(mojo_cookie_app_producer
  rect_mojom)

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
