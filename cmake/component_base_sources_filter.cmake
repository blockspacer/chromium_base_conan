if(NOT BASE_USE_JSON)
  filter_regex(
    OUTPUT_VAR COMPONENT_BASE_SOURCES
    IS_INCLUDE_REGEX FALSE
    REGEX "json"
    INPUT_ITEMS ${COMPONENT_BASE_SOURCES}
  )
endif()

if(TARGET_WINDOWS)
  filter_regex(
    OUTPUT_VAR COMPONENT_BASE_SOURCES
    IS_INCLUDE_REGEX FALSE
    REGEX "file_descriptor_store"
    INPUT_ITEMS ${COMPONENT_BASE_SOURCES}
  )
endif()

if(NOT TARGET_WINDOWS)
  filter_regex(
    OUTPUT_VAR COMPONENT_BASE_SOURCES
    IS_INCLUDE_REGEX FALSE
    REGEX "_msvc"
    INPUT_ITEMS ${COMPONENT_BASE_SOURCES}
  )
endif()

if(NOT TARGET_LINUX AND NOT TARGET_ANDROID)
  filter_regex(
    OUTPUT_VAR COMPONENT_BASE_SOURCES
    IS_INCLUDE_REGEX FALSE
    REGEX "linux_util"
    INPUT_ITEMS ${COMPONENT_BASE_SOURCES}
  )
endif()

if(TARGET_IOS)
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${COMPONENT_BASE_SOURCES}
    OUTPUT COMPONENT_BASE_SOURCES
    ITEMS
    "files/file_path_watcher.cc"
    "files/file_path_watcher.h"
    "memory/discardable_shared_memory.cc"
    "memory/discardable_shared_memory.h"
    "process/kill.cc"
    "process/kill.h"
    "process/kill_posix.cc"
    "process/launch.cc"
    "process/launch.h"
    "process/launch_posix.cc"
    "process/memory.cc"
    "process/memory.h"
    "process/process_iterator.cc"
    "process/process_iterator.h"
    "process/process_metrics_posix.cc"
    "process/process_posix.cc"
    "sync_socket.h"
    "sync_socket_posix.cc"
    "synchronization/waitable_event_watcher.h")
endif()

if(TERGET_IOS AND NOT USE_ALLOC_SHIM)
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${COMPONENT_BASE_SOURCES}
    OUTPUT COMPONENT_BASE_SOURCES
    ITEMS
    "sampling_heap_profiler/poisson_allocation_sampler.cc"
    "sampling_heap_profiler/poisson_allocation_sampler.h"
    "sampling_heap_profiler/sampling_heap_profiler.cc"
    "sampling_heap_profiler/sampling_heap_profiler.h")
endif(TERGET_IOS AND NOT USE_ALLOC_SHIM)

if(TARGET_MACOS)
  filter_regex(
    OUTPUT_VAR COMPONENT_BASE_SOURCES
    IS_INCLUDE_REGEX FALSE
    REGEX "launch_posix"
    INPUT_ITEMS ${COMPONENT_BASE_SOURCES}
  )
endif()

if(TARGET_ANDOID)
  filter_regex(
    OUTPUT_VAR COMPONENT_BASE_SOURCES
    IS_INCLUDE_REGEX FALSE
    REGEX "stack_trace_posix"
    INPUT_ITEMS ${COMPONENT_BASE_SOURCES}
  )
  filter_regex(
    OUTPUT_VAR COMPONENT_BASE_SOURCES
    IS_INCLUDE_REGEX FALSE
    REGEX "stack_sampler_posix"
    INPUT_ITEMS ${COMPONENT_BASE_SOURCES}
  )
  # TODO
  #if (current_cpu != "arm" && current_cpu != "arm64") {
  #  # The reached code profiler is only supported on Android arm arch.
  #  sources -= [ "android/reached_code_profiler.cc" ]
  #}
endif()

if (USE_PERFETTO_CLIENT_LIBRARY)
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${COMPONENT_BASE_SOURCES}
    OUTPUT COMPONENT_BASE_SOURCES
    ITEMS
    "trace_event/builtin_categories.cc")
endif()
