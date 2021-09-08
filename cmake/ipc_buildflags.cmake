#
set(BUILDFLAG_INTERNAL_IPC_MESSAGE_LOG_ENABLED "0")
if(IPC_MESSAGE_LOG_ENABLED)
  set(BUILDFLAG_INTERNAL_IPC_MESSAGE_LOG_ENABLED "1")
endif()

configure_file_if_changed(
  INPUT ${BUILDFLAGS_GENERATORS_PATH}/buildflags/ipc_buildflags.h.inc
  OUTPUT ${IPC_SOURCES_PATH}/ipc_buildflags.h
  TMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/ipc_buildflags.tmp)
