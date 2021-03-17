
set(BUILDFLAG_INTERNAL_ENABLE_ARM_CFI_TABLE "0")

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/profiler_buildflags.h.inc
  OUTPUT ${BASE_SOURCES_PATH}profiler/profiler_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/profiler_buildflags.tmp)
