#

if(NOT BASE_USE_JSON)
  filter_regex(
    OUTPUT_VAR COMPONENT_BASE_SOURCES
    IS_INCLUDE_REGEX FALSE
    REGEX "json"
    INPUT_ITEMS ${COMPONENT_BASE_SOURCES}
  )
endif()

if(TARGET_WINDOWS)
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${COMPONENT_BASE_SOURCES}
    OUTPUT COMPONENT_BASE_SOURCES
    ITEMS
    "file_descriptor_store.cc"
    "file_descriptor_store.h")
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
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${COMPONENT_BASE_SOURCES}
    OUTPUT COMPONENT_BASE_SOURCES
    ITEMS
    "debug/stack_trace_posix.cc"
    "profiler/stack_sampler_posix.cc")
  if (NOT TARGET_ARM AND NOT TARGET_ARM64)
    # The reached code profiler is only supported on Android arm arch.
    remove_from_list(
      CHECK_EXISTS TRUE
      INPUT ${COMPONENT_BASE_SOURCES}
      OUTPUT COMPONENT_BASE_SOURCES
      ITEMS
      "android/reached_code_profiler.cc")
  endif()
endif()

if (NOT USE_GLIB)
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${COMPONENT_BASE_SOURCES}
    OUTPUT COMPONENT_BASE_SOURCES
    ITEMS
    "message_loop/message_pump_glib.cc"
    "message_loop/message_pump_glib.h")
endif()

# TODO

# NaCl.
#if (is_nacl) {
#  # Explicitly include the linux file.
#  sources += [
#    "debug/stack_trace_nacl.cc",
#    "files/file_path_watcher_stub.cc",
#    "process/process_metrics_nacl.cc",
#    "process/process_stubs.cc",
#    "sync_socket_nacl.cc",
#    "threading/platform_thread_linux.cc",
#  ]
#  sources -= [
#    "cpu.cc",
#    "debug/crash_logging.cc",
#    "debug/crash_logging.h",
#    "debug/stack_trace.cc",
#    "debug/stack_trace_posix.cc",
#    "files/file_enumerator.cc",
#    "files/file_enumerator_posix.cc",
#    "files/file_proxy.cc",
#    "files/important_file_writer.cc",
#    "files/important_file_writer.h",
#    "files/important_file_writer_cleaner.cc",
#    "files/important_file_writer_cleaner.h",
#    "files/scoped_temp_dir.cc",
#    "memory/discardable_memory.cc",
#    "memory/discardable_memory.h",
#    "memory/discardable_memory_allocator.cc",
#    "memory/discardable_memory_allocator.h",
#    "memory/discardable_shared_memory.cc",
#    "memory/discardable_shared_memory.h",
#    "memory/madv_free_discardable_memory_allocator_posix.cc",
#    "memory/madv_free_discardable_memory_allocator_posix.h",
#    "memory/madv_free_discardable_memory_posix.cc",
#    "memory/madv_free_discardable_memory_posix.h",
#    "native_library.cc",
#    "native_library_posix.cc",
#    "path_service.cc",
#    "process/kill.cc",
#    "process/kill.h",
#    "process/memory.cc",
#    "process/memory.h",
#    "process/process_iterator.cc",
#    "process/process_iterator.h",
#    "process/process_metrics.cc",
#    "process/process_metrics_posix.cc",
#    "process/process_posix.cc",
#    "profiler/module_cache_posix.cc",
#    "scoped_native_library.cc",
#    "sync_socket_posix.cc",
#    "system/sys_info.cc",
#    "system/sys_info_posix.cc",
#    "task/thread_pool/initialization_util.cc",
#    "task/thread_pool/initialization_util.h",
#  ]
#  if (is_nacl_nonsfi) {
#    sources -= [ "rand_util_nacl.cc" ]
#  } else {
#    sources -= [
#      "files/file_descriptor_watcher_posix.cc",
#      "files/file_descriptor_watcher_posix.h",
#      "files/file_util.cc",
#      "files/file_util.h",
#      "files/file_util_posix.cc",
#      "json/json_file_value_serializer.cc",
#      "json/json_file_value_serializer.h",
#      "posix/unix_domain_socket.cc",
#      "process/kill_posix.cc",
#      "process/launch.cc",
#      "process/launch.h",
#      "process/launch_posix.cc",
#      "rand_util_posix.cc",
#      "task/thread_pool/task_tracker_posix.cc",
#      "task/thread_pool/task_tracker_posix.h",
#    ]
#  }

if (TARGET_APPLE)
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${COMPONENT_BASE_SOURCES}
    OUTPUT COMPONENT_BASE_SOURCES
    ITEMS
    "native_library_posix.cc"
    "profiler/module_cache_posix.cc"
    "strings/sys_string_conversions_posix.cc"
    "synchronization/waitable_event_posix.cc"
    "synchronization/waitable_event_watcher_posix.cc"
    "threading/platform_thread_internal_posix.cc")
endif()

if (NOT USE_NACL)
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${COMPONENT_BASE_SOURCES}
    OUTPUT COMPONENT_BASE_SOURCES
    ITEMS
    "os_compat_nacl.cc"
    "os_compat_nacl.h"
    "rand_util_nacl.cc")
endif()

if (USE_PERFETTO_CLIENT_LIBRARY)
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${COMPONENT_BASE_SOURCES}
    OUTPUT COMPONENT_BASE_SOURCES
    ITEMS
    "trace_event/builtin_categories.cc")
endif()

if(NOT TARGET_LINUX AND NOT TARGET_CHROMEOS AND NOT TARGET_ANDROID)
  remove_from_list(
    CHECK_EXISTS TRUE
    INPUT ${COMPONENT_BASE_SOURCES}
    OUTPUT COMPONENT_BASE_SOURCES
    ITEMS
    "linux_util.cc"
    "linux_util.h")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_extensions_sources.cmake)
