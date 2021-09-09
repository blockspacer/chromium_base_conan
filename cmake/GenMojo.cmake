include_guard( DIRECTORY )

# https://cmake.org/cmake/help/latest/module/FindPythonInterp.html
find_package(PythonInterp 2.7 REQUIRED)

find_package(Git REQUIRED)

# Generates bytecode
#
# USAGE
#
# precompile_mojom_bindings(
#   TARGET precompile_mojom_fortune_cookie
#   OUTPUT_DIR ".generated/mojo"
#   WORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
#
function(precompile_mojom_bindings)
  # see https://cliutils.gitlab.io/modern-cmake/chapters/basics/functions.html
  #set(options ) # empty
  set(oneValueArgs GENERATOR_PATH TARGET OUTPUT_DIR WORK_DIR)
  set(multiValueArgs ) # empty
  #
  cmake_parse_arguments(
    ARGUMENTS # prefix of output variables
    "${options}" # list of names of the boolean arguments (only defined ones will be true)
    "${oneValueArgs}" # list of names of mono-valued arguments
    "${multiValueArgs}" # list of names of multi-valued arguments (output variables are lists)
    ${ARGN} # arguments of the function to parse, here we take the all original ones
  )
  #
  set(GENERATOR_PATH ${MOJO_GENERATOR_PATH})
  if (NOT "${ARGUMENTS_GENERATOR_PATH}" STREQUAL "")
    set(GENERATOR_PATH ${ARGUMENTS_GENERATOR_PATH})
  endif()
  if ("${GENERATOR_PATH}" STREQUAL "")
    message(FATAL_ERROR
      "(precompile_mojom_bindings) \
      set global cmake variable with \
      valid MOJO_GENERATOR_PATH or pass valid GENERATOR_PATH")
  endif()
  if (NOT EXISTS "${GENERATOR_PATH}")
    message(FATAL_ERROR
      "(precompile_mojom_bindings) \
      unable to find path: \
      GENERATOR_PATH=${GENERATOR_PATH}")
  endif()
  #
  set(TARGET ${ARGUMENTS_TARGET})
  #
  set(OUTPUT_DIR ${ARGUMENTS_OUTPUT_DIR})
  #
  set(WORK_DIR ${ARGUMENTS_WORK_DIR})
  #
  set(UNPARSED_ARGUMENTS ${ARGUMENTS_UNPARSED_ARGUMENTS})
  #
  set(MOJO_PYTHON_VERSION ""
    CACHE STRING "Optional user-selected Python version")
  if(MOJO_PYTHON_VERSION)
    find_package(Python ${MOJO_PYTHON_VERSION}
      EXACT REQUIRED COMPONENTS Interpreter Development)
  else()
    find_package(Python
      REQUIRED COMPONENTS Interpreter Development)
  endif()

  set(mojo_precompile_command ${Python_EXECUTABLE}
    ${GENERATOR_PATH}
    --use_bundled_pylibs
    --output_dir=${OUTPUT_DIR}
    precompile
  )
  message(STATUS "mojo_precompile_command=${mojo_precompile_command}")

  add_custom_target(${TARGET}
    COMMAND ${CMAKE_COMMAND} -E echo
      ----------------------------------
    COMMAND ${CMAKE_COMMAND} -E make_directory
      ${OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E time
      ${mojo_precompile_command}
    WORKING_DIRECTORY ${WORK_DIR}
    COMMENT "Precompiling into ${OUTPUT_DIR}"
  )
endfunction()

# Generates mojom-module files (binary)
#
# USAGE
#
# parse_mojom(
#   TARGET parse_mojom_fortune_cookie
#   INPUT ${CMAKE_CURRENT_SOURCE_DIR}/fortune_cookie.mojom
#   OUTPUT_DIR ".generated/mojo"
#   INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}
#   WORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
#
function(parse_mojom)
  # see https://cliutils.gitlab.io/modern-cmake/chapters/basics/functions.html
  #set(options ) # empty
  set(oneValueArgs PARSER_PATH TARGET INPUT INPUT_DIR OUTPUT_DIR WORK_DIR)
  set(multiValueArgs ) # empty
  #
  cmake_parse_arguments(
    ARGUMENTS # prefix of output variables
    "${options}" # list of names of the boolean arguments (only defined ones will be true)
    "${oneValueArgs}" # list of names of mono-valued arguments
    "${multiValueArgs}" # list of names of multi-valued arguments (output variables are lists)
    ${ARGN} # arguments of the function to parse, here we take the all original ones
  )
  #
  set(PARSER_PATH ${MOJO_PARSER_PATH})
  if (NOT "${ARGUMENTS_PARSER_PATH}" STREQUAL "")
    set(PARSER_PATH ${ARGUMENTS_PARSER_PATH})
  endif()
  if ("${PARSER_PATH}" STREQUAL "")
    message(FATAL_ERROR
      "(parse_mojom) \
      set global cmake variable with \
      valid MOJO_PARSER_PATH or pass valid PARSER_PATH")
  endif()
  if (NOT EXISTS "${PARSER_PATH}")
    message(FATAL_ERROR
      "(parse_mojom) \
      unable to find path: \
      PARSER_PATH=${PARSER_PATH}")
  endif()
  #
  set(TARGET ${ARGUMENTS_TARGET})
  #
  set(INPUT ${ARGUMENTS_INPUT})
  #
  set(OUTPUT_DIR ${ARGUMENTS_OUTPUT_DIR})
  #
  set(INPUT_DIR ${ARGUMENTS_INPUT_DIR})
  if (NOT EXISTS "${INPUT_DIR}")
    message(FATAL_ERROR
      "(parse_mojom) \
      unable to find path: \
      INPUT_DIR=${INPUT_DIR}")
  endif()
  #
  set(WORK_DIR ${ARGUMENTS_WORK_DIR})
  #
  set(UNPARSED_ARGUMENTS ${ARGUMENTS_UNPARSED_ARGUMENTS})
  #
  set(MOJO_PYTHON_VERSION ""
    CACHE STRING "Optional user-selected Python version")
  if(MOJO_PYTHON_VERSION)
    find_package(Python ${MOJO_PYTHON_VERSION}
      EXACT REQUIRED COMPONENTS Interpreter Development)
  else()
    find_package(Python
      REQUIRED COMPONENTS Interpreter Development)
  endif()

  set(mojo_parse_command ${Python_EXECUTABLE}
    ${PARSER_PATH}
    --output-root=${OUTPUT_DIR}
    --input-root=${INPUT_DIR}
    --mojoms=${INPUT}
  )
  message(STATUS "mojo_parse_command=${mojo_parse_command}")

  add_custom_target(${TARGET}
    COMMAND ${CMAKE_COMMAND} -E echo
      ----------------------------------
    COMMAND ${CMAKE_COMMAND} -E make_directory
      ${OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E time
      ${mojo_parse_command}
    WORKING_DIRECTORY ${WORK_DIR}
    COMMENT "Parsing file ${INPUT} into ${OUTPUT}"
  )
endfunction()

# Generates source code files based on mojom files
#
# USAGE
#
# generate_mojom_cpp_bindings(
#   TARGET generate_mojom_fortune_cookie_cc
#   INPUT ${CMAKE_CURRENT_SOURCE_DIR}/fortune_cookie.mojom
#   OUTPUT_DIR ".generated/mojo"
#   BYTECODE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/.generated/mojo"
#   OUTPUT_FILES "fortune_cookie.mojom-module.cc"
#   INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
#   WORK_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
#   TEMPLATE_FILES module.cc.tmpl)
#
function(generate_mojom_cpp_bindings)
  # see https://cliutils.gitlab.io/modern-cmake/chapters/basics/functions.html
  #set(options ) # empty
  set(oneValueArgs GENERATOR_PATH TARGET INPUT INPUT_DIR OUTPUT_DIR
    BYTECODE_PATH WORK_DIR)
  set(multiValueArgs TEMPLATE_FILES OUTPUT_FILES)
  #
  cmake_parse_arguments(
    ARGUMENTS # prefix of output variables
    "${options}" # list of names of the boolean arguments (only defined ones will be true)
    "${oneValueArgs}" # list of names of mono-valued arguments
    "${multiValueArgs}" # list of names of multi-valued arguments (output variables are lists)
    ${ARGN} # arguments of the function to parse, here we take the all original ones
  )
  #
  set(GENERATOR_PATH ${MOJO_GENERATOR_PATH})
  if (NOT "${ARGUMENTS_GENERATOR_PATH}" STREQUAL "")
    set(GENERATOR_PATH ${ARGUMENTS_GENERATOR_PATH})
  endif()
  if ("${GENERATOR_PATH}" STREQUAL "")
    message(FATAL_ERROR
      "(generate_mojom_cpp_bindings) \
      set global cmake variable with \
      valid MOJO_GENERATOR_PATH or pass valid GENERATOR_PATH")
  endif()
  if (NOT EXISTS "${GENERATOR_PATH}")
    message(FATAL_ERROR
      "(generate_mojom_cpp_bindings) \
      unable to find path: \
      GENERATOR_PATH=${GENERATOR_PATH}")
  endif()
  #
  set(TARGET ${ARGUMENTS_TARGET})
  #
  set(INPUT ${ARGUMENTS_INPUT})
  #
  set(OUTPUT_DIR ${ARGUMENTS_OUTPUT_DIR})
  #
  set(INPUT_DIR ${ARGUMENTS_INPUT_DIR})
  if (NOT EXISTS "${INPUT_DIR}")
    message(FATAL_ERROR
      "(generate_mojom_cpp_bindings) \
      unable to find path: \
      INPUT_DIR=${INPUT_DIR}")
  endif()
  #
  set(BYTECODE_PATH ${ARGUMENTS_BYTECODE_PATH})
  #
  set(OUTPUT_FILES ${ARGUMENTS_OUTPUT_FILES})
  #
  set(WORK_DIR ${ARGUMENTS_WORK_DIR})
  #
  set(TEMPLATE_FILES ${ARGUMENTS_TEMPLATE_FILES})
  #
  set(UNPARSED_ARGUMENTS ${ARGUMENTS_UNPARSED_ARGUMENTS})
  #
  set(MOJO_PYTHON_VERSION ""
    CACHE STRING "Optional user-selected Python version")
  if(MOJO_PYTHON_VERSION)
    find_package(Python ${MOJO_PYTHON_VERSION}
      EXACT REQUIRED COMPONENTS Interpreter Development)
  else()
    find_package(Python
      REQUIRED COMPONENTS Interpreter Development)
  endif()

  set(bindings_generators_path
    ${MOJO_SOURCES_PATH}/public/tools/bindings/generators
  )
  message(STATUS "bindings_generators_path=${bindings_generators_path}")
  if (NOT EXISTS "${bindings_generators_path}")
    message(FATAL_ERROR
      "(generate_mojom_cpp_bindings) \
      unable to find path: \
      bindings_generators_path=${bindings_generators_path}")
  endif()

  add_custom_target(${TARGET}
    COMMAND ${CMAKE_COMMAND} -E echo
      ----------------------------------
    COMMAND ${CMAKE_COMMAND} -E make_directory
      ${OUTPUT_DIR}
    WORKING_DIRECTORY ${WORK_DIR}
    COMMENT "Generating files ${OUTPUT_FILES} \
      from ${TEMPLATE_FILEPATH}"
  )

  set(mojo_gen_command ${Python_EXECUTABLE}
    ${GENERATOR_PATH}
    --use_bundled_pylibs
    generate
    ${INPUT}
    --depth=${INPUT_DIR}
    --import_directories=${WORK_DIR}/${OUTPUT_DIR},${WORK_DIR},${MOJO_SOURCES_PATH},${EXTENSIONS_PATH},${bindings_generators_path},${bindings_generators_path}/..,${bindings_generators_path}/../..,${bindings_generators_path}/../../..,${bindings_generators_path}/../../../..,${bindings_generators_path}/../../../../..
    --output_dir=${OUTPUT_DIR}
    --gen_dir=${bindings_generators_path}/cpp_templates
    --bytecode_path=${BYTECODE_PATH}
    --generators c++
  )
  message(STATUS "mojo_gen_command=${mojo_gen_command}")

  add_custom_target(${TARGET}-templates
    COMMAND ${CMAKE_COMMAND} -E echo
      ----------------------------------
    COMMAND ${CMAKE_COMMAND} -E make_directory
      ${OUTPUT_DIR}
    COMMAND ${CMAKE_COMMAND} -E time
      ${mojo_gen_command}
      --generate_non_variant_code
    COMMAND ${CMAKE_COMMAND} -E time
      ${mojo_gen_command}
      --generate_non_variant_code
      --generate_message_ids
    COMMAND ${CMAKE_COMMAND} -E time
      ${mojo_gen_command}
    WORKING_DIRECTORY ${WORK_DIR}
    COMMENT "${TARGET}-templates: \
      Generating files ${OUTPUT_FILES}"
  )

  add_dependencies(${TARGET}
    ${TARGET}-templates)

  set(extra_cpp_template_paths "")
  foreach(TEMPLATE_FILE ${TEMPLATE_FILES})
    set(TEMPLATE_FILEPATH
      ${bindings_generators_path}/cpp_templates/${TEMPLATE_FILE})
    message(STATUS "TEMPLATE_FILEPATH=${TEMPLATE_FILEPATH}")
    if (NOT EXISTS "${TEMPLATE_FILEPATH}")
      message(FATAL_ERROR
        "(generate_mojom_cpp_bindings) \
        unable to find path: \
        TEMPLATE_FILEPATH=${TEMPLATE_FILEPATH}")
    endif()

    # if (NOT "${extra_cpp_template_paths}" STREQUAL "")
    #   set(extra_cpp_template_paths
    #     "${extra_cpp_template_paths},")
    # endif()
    # set(extra_cpp_template_paths
    #   "${extra_cpp_template_paths}${TEMPLATE_FILEPATH}")

    set(mojo_gen_command ${Python_EXECUTABLE}
      ${GENERATOR_PATH}
      --use_bundled_pylibs
      generate
      ${INPUT}
      --depth=${INPUT_DIR}
      --import_directories=${WORK_DIR}/${OUTPUT_DIR},${WORK_DIR},${MOJO_SOURCES_PATH},${EXTENSIONS_PATH},${bindings_generators_path},${bindings_generators_path}/..,${bindings_generators_path}/../..,${bindings_generators_path}/../../..,${bindings_generators_path}/../../../..,${bindings_generators_path}/../../../../..
      --output_dir=${OUTPUT_DIR}
      --gen_dir=${bindings_generators_path}/cpp_templates
      --bytecode_path=${BYTECODE_PATH}
      --extra_cpp_template_paths=${TEMPLATE_FILEPATH}
      --generators c++
      --generate_extra_cpp_only
    )
    message(STATUS "mojo_gen_command=${mojo_gen_command}")

    get_filename_component(TEMPLATE_FILENAME
      ${TEMPLATE_FILEPATH} NAME)

    add_custom_target(${TARGET}-${TEMPLATE_FILENAME}
      COMMAND ${CMAKE_COMMAND} -E echo
        ----------------------------------
      COMMAND ${CMAKE_COMMAND} -E make_directory
        ${OUTPUT_DIR}
      COMMAND ${CMAKE_COMMAND} -E time
        ${mojo_gen_command}
        --generate_non_variant_code
      COMMAND ${CMAKE_COMMAND} -E time
        ${mojo_gen_command}
        --generate_non_variant_code
        --generate_message_ids
      COMMAND ${CMAKE_COMMAND} -E time
        ${mojo_gen_command}
      WORKING_DIRECTORY ${WORK_DIR}
      COMMENT "${TARGET}-${TEMPLATE_FILENAME}: \
        Generating files ${OUTPUT_FILES} \
        from ${TEMPLATE_FILEPATH}"
    )
    add_dependencies(${TARGET}
      ${TARGET}-${TEMPLATE_FILENAME})
  endforeach()

  foreach(OUTPUT_FILE ${OUTPUT_FILES})
    set(OUTPUT_FULLPATH "${WORK_DIR}/${OUTPUT_DIR}/${OUTPUT_FILE}")
    set_source_files_properties(${OUTPUT_FULLPATH}
      PROPERTIES GENERATED TRUE)
  endforeach()
endfunction()

function(generate_all_mojom_cpp_bindings)
  # see https://cliutils.gitlab.io/modern-cmake/chapters/basics/functions.html
  #set(options ) # empty
  set(oneValueArgs GENERATOR_PATH TARGET INPUT INPUT_DIR OUTPUT_DIR
    BYTECODE_PATH WORK_DIR)
  set(multiValueArgs OUTPUT_FILES)
  #
  cmake_parse_arguments(
    ARGUMENTS # prefix of output variables
    "${options}" # list of names of the boolean arguments (only defined ones will be true)
    "${oneValueArgs}" # list of names of mono-valued arguments
    "${multiValueArgs}" # list of names of multi-valued arguments (output variables are lists)
    ${ARGN} # arguments of the function to parse, here we take the all original ones
  )
  #
  set(GENERATOR_PATH ${MOJO_GENERATOR_PATH})
  if (NOT "${ARGUMENTS_GENERATOR_PATH}" STREQUAL "")
    set(GENERATOR_PATH ${ARGUMENTS_GENERATOR_PATH})
  endif()
  if ("${GENERATOR_PATH}" STREQUAL "")
    message(FATAL_ERROR
      "(generate_all_mojom_cpp_bindings) \
      set global cmake variable with \
      valid MOJO_GENERATOR_PATH or pass valid GENERATOR_PATH")
  endif()
  if (NOT EXISTS "${GENERATOR_PATH}")
    message(FATAL_ERROR
      "(generate_all_mojom_cpp_bindings) \
      unable to find path: \
      GENERATOR_PATH=${GENERATOR_PATH}")
  endif()
  #
  set(TARGET ${ARGUMENTS_TARGET})
  #
  set(INPUT ${ARGUMENTS_INPUT})
  #
  set(OUTPUT_DIR ${ARGUMENTS_OUTPUT_DIR})
  #
  set(INPUT_DIR ${ARGUMENTS_INPUT_DIR})
  if (NOT EXISTS "${INPUT_DIR}")
    message(FATAL_ERROR
      "(generate_all_mojom_cpp_bindings) \
      unable to find path: \
      INPUT_DIR=${INPUT_DIR}")
  endif()
  #
  set(BYTECODE_PATH ${ARGUMENTS_BYTECODE_PATH})
  #
  set(OUTPUT_FILES ${ARGUMENTS_OUTPUT_FILES})
  #
  set(WORK_DIR ${ARGUMENTS_WORK_DIR})
  #
  set(UNPARSED_ARGUMENTS ${ARGUMENTS_UNPARSED_ARGUMENTS})
  #
  precompile_mojom_bindings(
    TARGET precompile_mojom_${TARGET}
    OUTPUT_DIR ${OUTPUT_DIR}
    WORK_DIR ${WORK_DIR})

  parse_mojom(
    TARGET parse_mojom_${TARGET}
    INPUT ${INPUT}
    OUTPUT_DIR ${OUTPUT_DIR}
    INPUT_DIR ${WORK_DIR}
    WORK_DIR ${WORK_DIR})

  add_dependencies(parse_mojom_${TARGET}
    precompile_mojom_${TARGET})

  generate_mojom_cpp_bindings(
    TARGET generate_mojom_${TARGET}
    INPUT ${INPUT}
    BYTECODE_PATH ${BYTECODE_PATH}
    OUTPUT_DIR ${OUTPUT_DIR}
    OUTPUT_FILES ${OUTPUT_FILES}
    INPUT_DIR ${WORK_DIR}
    WORK_DIR ${WORK_DIR}
    TEMPLATE_FILES
      module.cc.tmpl
      module.h.tmpl
      module-shared.cc.tmpl
      module-shared.h.tmpl
  )

  add_dependencies(generate_mojom_${TARGET}-templates
    parse_mojom_${TARGET})
  add_dependencies(generate_mojom_${TARGET}-module.cc.tmpl
    parse_mojom_${TARGET})
  add_dependencies(generate_mojom_${TARGET}-module.h.tmpl
    parse_mojom_${TARGET})
  add_dependencies(generate_mojom_${TARGET}-module-shared.cc.tmpl
    parse_mojom_${TARGET})
  add_dependencies(generate_mojom_${TARGET}-module-shared.h.tmpl
    parse_mojom_${TARGET})
  add_dependencies(generate_mojom_${TARGET}
    parse_mojom_${TARGET})

  #generate_mojom_cpp_bindings(
  #  TARGET generate_mojom_${TARGET}-shared
  #  INPUT ${INPUT}
  #  BYTECODE_PATH ${BYTECODE_PATH}
  #  OUTPUT_DIR ${OUTPUT_DIR}
  #  INPUT_DIR ${WORK_DIR}
  #  OUTPUT_FILES ${OUTPUT_FILES}
  #  WORK_DIR ${WORK_DIR}
  #  TEMPLATE_FILES
  #)
  #
  #add_dependencies(generate_mojom_${TARGET}-shared
  #  parse_mojom_${TARGET})

  add_custom_target(${TARGET}
    DEPENDS
      generate_mojom_${TARGET}
      #generate_mojom_${TARGET}-shared
  )
endfunction()

# see github.com/chromium/chromium/blob/f89fc2ac30e582dfe9e334baf19ef8e535eea30d/mojo/public/tools/bindings/mojom_bindings_generator.py
# `generate_mojom_bindings` able to detect configuration changes
# (changes in used cmake defines) or missing files
# i.e. it will not re-generate files if configuration not changed.
#
# MOTIVATION: `configure_file` will NOT re-generate file if used cmake defines
# changed. It able to detect changes only in input file before preprocessing.
#
# Function
#   generate_mojom_bindings(GENERATOR_PATH <...>
#     INPUT <...> OUTPUT <...> TMP_FILE <...>)
#
# function(generate_mojom)
#   # see https://cliutils.gitlab.io/modern-cmake/chapters/basics/functions.html
#   #set(options ) # empty
#   set(oneValueArgs INPUT OUTPUT TMP_FILE GENERATOR_PATH)
#   set(multiValueArgs ) # empty
#   #
#   cmake_parse_arguments(
#     ARGUMENTS # prefix of output variables
#     "${options}" # list of names of the boolean arguments (only defined ones will be true)
#     "${oneValueArgs}" # list of names of mono-valued arguments
#     "${multiValueArgs}" # list of names of multi-valued arguments (output variables are lists)
#     ${ARGN} # arguments of the function to parse, here we take the all original ones
#   )
#   #
#   set(GENERATOR_PATH ${MOJO_GENERATOR_PATH})
#   if (NOT "${ARGUMENTS_GENERATOR_PATH}" STREQUAL "")
#     set(GENERATOR_PATH ${ARGUMENTS_GENERATOR_PATH})
#   endif()
#   if ("${GENERATOR_PATH}" STREQUAL "")
#     message(FATAL_ERROR "(generate_mojom_bindings) set global cmake variable with valid MOJO_GENERATOR_PATH or pass valid GENERATOR_PATH")
#   endif()
#   if (NOT EXISTS "${GENERATOR_PATH}")
#     message(FATAL_ERROR "(generate_mojom_bindings) unable to find path: GENERATOR_PATH=${GENERATOR_PATH}")
#   endif()
#   #
#   set(INPUT ${ARGUMENTS_INPUT})
#   #
#   set(OUTPUT ${ARGUMENTS_OUTPUT})
#   #
#   set(TMP_FILE ${ARGUMENTS_TMP_FILE})
#   #
#   set(UNPARSED_ARGUMENTS ${ARGUMENTS_UNPARSED_ARGUMENTS})
#   #
#   set(MOJO_PYTHON_VERSION "" CACHE STRING "Optional user-selected Python version")
#   if(MOJO_PYTHON_VERSION)
#     find_package(Python ${MOJO_PYTHON_VERSION} EXACT REQUIRED COMPONENTS Interpreter Development)
#   else()
#     find_package(Python REQUIRED COMPONENTS Interpreter Development)
#   endif()
#
#   set(output_dir ${MOJO_SOURCES_PATH})
#
#   #
#   # TODO
#   # set(INTERNAL_NEED_TO_UPDATE_FILE FALSE)
#   set(INTERNAL_NEED_TO_UPDATE_FILE TRUE)
#
#   if(NOT EXISTS "${OUTPUT}")
#     message(STATUS "Unable to find required file: ${OUTPUT}")
#     message(STATUS "File will be re-generated: ${OUTPUT}")
#     set(INTERNAL_NEED_TO_UPDATE_FILE TRUE)
#   else()
#     # remove old tmp file
#     execute_process(
#       COMMAND
#         ${CMAKE_COMMAND} -E remove
#           ${TMP_FILE}
#       OUTPUT_QUIET
#     )
#
#     set(mojo_gen_command ${Python_EXECUTABLE}
#       ${GENERATOR_PATH}
#       --use_bundled_pylibs
#       generate
#       ${TMP_FILE}
#       -d ${MOJO_SOURCES_PATH}
#       -I ${MOJO_SOURCES_PATH}
#       --output_dir=${output_dir}
#       --bytecode_path ${MOJO_SOURCES_PATH}public/tools/bindings
#     )
#     message(STATUS "mojo_gen_command=${mojo_gen_command}")
#
#     execute_process(COMMAND ${mojo_gen_command}
#       WORKING_DIRECTORY ${MOJO_SOURCES_PATH})
#
#     # compare tmp file with the real file
#     execute_process(
#       COMMAND
#         ${CMAKE_COMMAND} -E compare_files
#           ${TMP_FILE}
#           ${OUTPUT}
#       RESULT_VARIABLE
#         INTERNAL_NEED_TO_UPDATE_FILE
#       OUTPUT_QUIET
#     )
#   endif()
#
#   # update the real file if necessary
#   if(INTERNAL_NEED_TO_UPDATE_FILE)
#     # remove old file
#     execute_process(
#       COMMAND
#         ${CMAKE_COMMAND} -E remove
#           ${OUTPUT}
#       OUTPUT_QUIET
#     )
#
#     set(mojo_gen_command ${Python_EXECUTABLE}
#       ${GENERATOR_PATH}
#       --use_bundled_pylibs
#       generate
#       ${INPUT}
#       -d ${MOJO_SOURCES_PATH}
#       -I ${MOJO_SOURCES_PATH}
#       --output_dir=${output_dir}
#       --bytecode_path ${MOJO_SOURCES_PATH}public/tools/bindings
#     )
#     message(STATUS "mojo_gen_command=${mojo_gen_command}")
#
#     execute_process(COMMAND ${mojo_gen_command}
#       WORKING_DIRECTORY ${MOJO_SOURCES_PATH})
#     message(STATUS "File was re-generated: ${OUTPUT}")
#   else()
#     message(STATUS "Skipped file generation: ${OUTPUT}")
#     if(NOT EXISTS "${OUTPUT}")
#       message(FATAL_ERROR "Unable to find required file: ${OUTPUT}")
#     endif()
#   endif(INTERNAL_NEED_TO_UPDATE_FILE)
#
#   # file generation may fail due to OS or drive issues (not enough disk space, etc.)
#   if(NOT EXISTS "${OUTPUT}")
#     message(WARNING "Something went wrong. Unable to find generated file: ${OUTPUT}")
#   endif()
#
#   set_source_files_properties(${OUTPUT}
#     PROPERTIES GENERATED TRUE)
# endfunction()
