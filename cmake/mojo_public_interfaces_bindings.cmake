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
function(generate_mojom_bindings)
  # see https://cliutils.gitlab.io/modern-cmake/chapters/basics/functions.html
  #set(options ) # empty
  set(oneValueArgs INPUT OUTPUT TMP_FILE GENERATOR_PATH)
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
    message(FATAL_ERROR "(generate_mojom_bindings) set global cmake variable with valid MOJO_GENERATOR_PATH or pass valid GENERATOR_PATH")
  endif()
  if (NOT EXISTS "${GENERATOR_PATH}")
    message(FATAL_ERROR "(generate_mojom_bindings) unable to find path: GENERATOR_PATH=${GENERATOR_PATH}")
  endif()
  #
  set(INPUT ${ARGUMENTS_INPUT})
  #
  set(OUTPUT ${ARGUMENTS_OUTPUT})
  #
  set(TMP_FILE ${ARGUMENTS_TMP_FILE})
  #
  set(UNPARSED_ARGUMENTS ${ARGUMENTS_UNPARSED_ARGUMENTS})
  #
  set(MOJO_PYTHON_VERSION "" CACHE STRING "Optional user-selected Python version")
  if(MOJO_PYTHON_VERSION)
    find_package(Python ${MOJO_PYTHON_VERSION} EXACT REQUIRED COMPONENTS Interpreter Development)
  else()
    find_package(Python REQUIRED COMPONENTS Interpreter Development)
  endif()

  set(output_dir ${MOJO_SOURCES_PATH})

  #
  # TODO
  # set(INTERNAL_NEED_TO_UPDATE_FILE FALSE)
  set(INTERNAL_NEED_TO_UPDATE_FILE TRUE)

  if(NOT EXISTS "${OUTPUT}")
    message(STATUS "Unable to find required file: ${OUTPUT}")
    message(STATUS "File will be re-generated: ${OUTPUT}")
    set(INTERNAL_NEED_TO_UPDATE_FILE TRUE)
  else()
    # remove old tmp file
    execute_process(
      COMMAND
        ${CMAKE_COMMAND} -E remove
          ${TMP_FILE}
      OUTPUT_QUIET
    )

    set(mojo_gen_command ${Python_EXECUTABLE}
      ${GENERATOR_PATH}
      --use_bundled_pylibs
      generate
      ${TMP_FILE}
      -d ${MOJO_SOURCES_PATH}
      -I ${MOJO_SOURCES_PATH}
      -o ${output_dir}
      --bytecode_path ${MOJO_SOURCES_PATH}public/tools/bindings
    )
    message(STATUS "mojo_gen_command=${mojo_gen_command}")

    execute_process(COMMAND ${mojo_gen_command}
      WORKING_DIRECTORY ${MOJO_SOURCES_PATH})

    # compare tmp file with the real file
    execute_process(
      COMMAND
        ${CMAKE_COMMAND} -E compare_files
          ${TMP_FILE}
          ${OUTPUT}
      RESULT_VARIABLE
        INTERNAL_NEED_TO_UPDATE_FILE
      OUTPUT_QUIET
    )
  endif()

  # update the real file if necessary
  if(INTERNAL_NEED_TO_UPDATE_FILE)
    # remove old file
    execute_process(
      COMMAND
        ${CMAKE_COMMAND} -E remove
          ${OUTPUT}
      OUTPUT_QUIET
    )

    set(mojo_gen_command ${Python_EXECUTABLE}
      ${GENERATOR_PATH}
      --use_bundled_pylibs
      generate
      ${INPUT}
      -d ${MOJO_SOURCES_PATH}
      -I ${MOJO_SOURCES_PATH}
      -o ${output_dir}
      --bytecode_path ${MOJO_SOURCES_PATH}public/tools/bindings
    )
    message(STATUS "mojo_gen_command=${mojo_gen_command}")

    execute_process(COMMAND ${mojo_gen_command}
      WORKING_DIRECTORY ${MOJO_SOURCES_PATH})
    message(STATUS "File was re-generated: ${OUTPUT}")
  else()
    message(STATUS "Skipped file generation: ${OUTPUT}")
    if(NOT EXISTS "${OUTPUT}")
      message(FATAL_ERROR "Unable to find required file: ${OUTPUT}")
    endif()
  endif(INTERNAL_NEED_TO_UPDATE_FILE)

  # file generation may fail due to OS or drive issues (not enough disk space, etc.)
  if(NOT EXISTS "${OUTPUT}")
    message(WARNING "Something went wrong. Unable to find generated file: ${OUTPUT}")
  endif()

  set_source_files_properties(${OUTPUT}
    PROPERTIES GENERATED TRUE)
endfunction()

list(APPEND MOJO_PUBLIC_INTERFACES_BINDINGS_SOURCES
  "interface_control_messages.mojom"
  "native_struct.mojom"
  "pipe_control_messages.mojom"
)

list(TRANSFORM MOJO_PUBLIC_INTERFACES_BINDINGS_SOURCES
  PREPEND "${MOJO_SOURCES_PATH}public/cpp/bindings/")

foreach(component IN LISTS MOJO_PUBLIC_INTERFACES_BINDINGS_SOURCES)
  generate_mojom_bindings(
    INPUT ${component} OUTPUT ${component}.mojom.cc TMP_FILE ${component}.mojom.cc.tmp)
endforeach()
