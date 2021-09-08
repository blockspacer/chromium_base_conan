﻿#
set(BUILDFLAG_INTERNAL_MOJO_RANDOM_DELAYS_ENABLED "0")
if(MOJO_RANDOM_DELAYS_ENABLED)
  set(BUILDFLAG_INTERNAL_MOJO_RANDOM_DELAYS_ENABLED "1")
endif(MOJO_RANDOM_DELAYS_ENABLED)
#
set(BUILDFLAG_INTERNAL_MOJO_TRACE_ENABLED "0")
if(MOJO_TRACE_ENABLED)
  set(BUILDFLAG_INTERNAL_MOJO_TRACE_ENABLED "1")
endif()

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/mojo_buildflags.h.inc
  OUTPUT ${MOJO_SOURCES_PATH}/public/cpp/bindings/mojo_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/mojo_buildflags.tmp)