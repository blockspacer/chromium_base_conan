# see component("base") in BUILD.gn
list(APPEND COMPONENT_BASE_SOURCES_ANDROID_UNPROCESSED
  "debug/stack_trace_android.cc"
  "files/file_util_android.cc"
  "files/scoped_file_android.cc"
  "message_loop/message_pump_android.cc"
  "message_loop/message_pump_android.h"
  "os_compat_android.cc"
  "os_compat_android.h"
  "process/process_android.cc"
  "profiler/stack_sampler_android.cc"
  "threading/platform_thread_android.cc"
)

list(TRANSFORM COMPONENT_BASE_SOURCES_ANDROID_UNPROCESSED PREPEND ${BASE_SOURCES_PATH})
list(APPEND COMPONENT_BASE_SOURCES ${COMPONENT_BASE_SOURCES_ANDROID_UNPROCESSED})
