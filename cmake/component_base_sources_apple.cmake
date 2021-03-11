# see component("base") in BUILD.gn
list(APPEND COMPONENT_BASE_SOURCES_APPLE_UNPROCESSED
  "native_library_posix.cc"
  "profiler/module_cache_posix.cc"
  "strings/sys_string_conversions_posix.cc"
  "synchronization/waitable_event_posix.cc"
  "synchronization/waitable_event_watcher_posix.cc"
  "threading/platform_thread_internal_posix.cc"
)

list(APPEND COMPONENT_BASE_SOURCES ${COMPONENT_BASE_SOURCES_APPLE_UNPROCESSED})
