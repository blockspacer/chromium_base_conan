# precompile_mojom_bindings(
#   TARGET precompile_mojom_fortune_cookie
#   OUTPUT_DIR ".generated/mojo"
#   WORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
#
# parse_mojom(
#   TARGET parse_mojom_fortune_cookie
#   INPUT ${CMAKE_CURRENT_SOURCE_DIR}/extensions/mojom/fortune_cookie.mojom
#   OUTPUT_DIR ".generated/mojo"
#   WORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
#
# add_dependencies(parse_mojom_fortune_cookie
#   precompile_mojom_fortune_cookie)
#
# generate_mojom_cpp_bindings(
#   TARGET generate_mojom_fortune_cookie_cc
#   INPUT ${CMAKE_CURRENT_SOURCE_DIR}/extensions/mojom/fortune_cookie.mojom
#   BYTECODE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.generated/mojo"
#   OUTPUT_DIR ".generated/mojo"
#   OUTPUT_FILES "mojom/fortune_cookie.mojom-module.cc"
#   WORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
#   TEMPLATE_FILES module.cc.tmpl)
#
# add_dependencies(generate_mojom_fortune_cookie_cc
#   parse_mojom_fortune_cookie)
#
# generate_mojom_cpp_bindings(
#   TARGET generate_mojom_fortune_cookie_h
#   INPUT ${CMAKE_CURRENT_SOURCE_DIR}/extensions/mojom/fortune_cookie.mojom
#   BYTECODE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.generated/mojo"
#   OUTPUT_DIR ".generated/mojo"
#   OUTPUT_FILES "mojom/fortune_cookie.mojom-module.h"
#   WORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
#   TEMPLATE_FILES module.h.tmpl)
#
# add_dependencies(generate_mojom_fortune_cookie_h
#   parse_mojom_fortune_cookie)
#
# add_custom_target(fortune_cookie
#   DEPENDS
#     generate_mojom_fortune_cookie_cc
#     generate_mojom_fortune_cookie_h)

generate_all_mojom_cpp_bindings(
  TARGET fortune_cookie
  INPUT ${CMAKE_CURRENT_SOURCE_DIR}/extensions/mojom/fortune_cookie.mojom
  BYTECODE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.generated/mojo"
  OUTPUT_DIR ".generated/mojo"
  OUTPUT_FILES
    "mojom/fortune_cookie.mojom.h"
    "mojom/fortune_cookie.mojom.cc"
    "mojom/fortune_cookie.mojom-shared.h"
    "mojom/fortune_cookie.mojom-shared.cc"
    "mojom/fortune_cookie.mojom-module.h"
    "mojom/fortune_cookie.mojom-module.cc"
    "mojom/fortune_cookie.mojom-module-shared.h"
    "mojom/fortune_cookie.mojom-module-shared.cc"
  WORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  TEMPLATE_FILES module.h.tmpl module.cc.tmpl)

set(MOJO_GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.generated/mojo)
message(STATUS "MOJO_GEN_DIR=${MOJO_GEN_DIR}")

# ------- mojo_receiver_example -------

add_executable(mojo_receiver_example
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/mojo_receiver_example.cc
  ${MOJO_GEN_DIR}/mojom/fortune_cookie.mojom.cc
  ${MOJO_GEN_DIR}/mojom/fortune_cookie.mojom.h
  ${MOJO_GEN_DIR}/mojom/fortune_cookie.mojom-shared.cc
  ${MOJO_GEN_DIR}/mojom/fortune_cookie.mojom-shared.h
)

add_dependencies(mojo_receiver_example
  fortune_cookie)

target_include_directories(mojo_receiver_example PUBLIC
  ${MOJO_GEN_DIR}
  ${MOJO_GEN_DIR}/mojom
)

target_link_libraries(mojo_receiver_example PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system
  mojo_cpp_platform
  mojo_public_system_cpp
  mojo_core_embedder
  ipc
)

# ------- mojo_cookie_app_a -------

add_executable(mojo_cookie_app_a
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/mojo_cookie_app_a.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/fortune_cookie_impl.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/fortune_cookie_impl.h
  ${MOJO_GEN_DIR}/mojom/fortune_cookie.mojom.cc
  ${MOJO_GEN_DIR}/mojom/fortune_cookie.mojom.h
  ${MOJO_GEN_DIR}/mojom/fortune_cookie.mojom-shared.cc
  ${MOJO_GEN_DIR}/mojom/fortune_cookie.mojom-shared.h
)

add_dependencies(mojo_cookie_app_a
  fortune_cookie)

target_include_directories(mojo_cookie_app_a PUBLIC
  ${MOJO_GEN_DIR}
  ${MOJO_GEN_DIR}/mojom
)

target_link_libraries(mojo_cookie_app_a PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system
  mojo_cpp_platform
  mojo_public_system_cpp
  mojo_core_embedder
  ipc
)

# ------- mojo_cookie_app_b -------

add_executable(mojo_cookie_app_b
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/mojo_cookie_app_b.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/fortune_cookie_impl.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/examples/fortune_cookie_impl.h
  ${MOJO_GEN_DIR}/mojom/fortune_cookie.mojom.cc
  ${MOJO_GEN_DIR}/mojom/fortune_cookie.mojom.h
  ${MOJO_GEN_DIR}/mojom/fortune_cookie.mojom-shared.cc
  ${MOJO_GEN_DIR}/mojom/fortune_cookie.mojom-shared.h
)

add_dependencies(mojo_cookie_app_b
  fortune_cookie)

target_include_directories(mojo_cookie_app_b PUBLIC
  ${MOJO_GEN_DIR}
  ${MOJO_GEN_DIR}/mojom
)

target_link_libraries(mojo_cookie_app_b PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system
  mojo_cpp_platform
  mojo_public_system_cpp
  mojo_core_embedder
  ipc
)
