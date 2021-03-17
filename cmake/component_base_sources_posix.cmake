# see component("base") in BUILD.gn
list(APPEND COMPONENT_BASE_SOURCES_POSIX_UNPROCESSED
  "debug/debugger_posix.cc"
  "debug/stack_trace_posix.cc"
  "file_descriptor_posix.h"
  "files/dir_reader_posix.h"
  "files/file_descriptor_watcher_posix.cc"
  "files/file_descriptor_watcher_posix.h"
  "files/file_enumerator_posix.cc"
  "files/file_posix.cc"
  "files/file_util_posix.cc"
  "files/memory_mapped_file_posix.cc"
  "memory/madv_free_discardable_memory_allocator_posix.cc"
  "memory/madv_free_discardable_memory_allocator_posix.h"
  "memory/madv_free_discardable_memory_posix.cc"
  "memory/madv_free_discardable_memory_posix.h"
  "message_loop/watchable_io_message_pump_posix.cc"
  "message_loop/watchable_io_message_pump_posix.h"
  "native_library_posix.cc"
  "posix/eintr_wrapper.h"
  "posix/file_descriptor_shuffle.cc"
  "posix/file_descriptor_shuffle.h"
  "posix/global_descriptors.cc"
  "posix/global_descriptors.h"
  "posix/safe_strerror.cc"
  "posix/safe_strerror.h"
  "posix/unix_domain_socket.cc"
  "posix/unix_domain_socket.h"
  "process/kill_posix.cc"
  "process/launch_posix.cc"
  "process/process_handle_posix.cc"
  "process/process_metrics_posix.cc"
  "process/process_posix.cc"
  "profiler/module_cache_posix.cc"
  "rand_util_posix.cc"
  "strings/string_util_posix.h"
  "strings/sys_string_conversions_posix.cc"
  "sync_socket_posix.cc"
  "synchronization/condition_variable_posix.cc"
  "synchronization/lock_impl_posix.cc"
  "synchronization/waitable_event_posix.cc"
  "synchronization/waitable_event_watcher_posix.cc"
  "system/sys_info_posix.cc"
  "task/thread_pool/task_tracker_posix.cc"
  "task/thread_pool/task_tracker_posix.h"
  "threading/platform_thread_internal_posix.cc"
  "threading/platform_thread_internal_posix.h"
  "threading/platform_thread_posix.cc"
  "threading/thread_local_storage_posix.cc"
  "timer/hi_res_timer_manager_posix.cc"
)

if(NOT USE_NACL AND NOT TARGET_APPLE)
  list(APPEND COMPONENT_BASE_SOURCES_POSIX_UNPROCESSED
    "cpu_affinity_posix.cc"
    "cpu_affinity_posix.h"
    "profiler/stack_copier_signal.cc"
    "profiler/stack_copier_signal.h"
    "profiler/stack_sampler_posix.cc"
    "profiler/thread_delegate_posix.cc"
    "profiler/thread_delegate_posix.h"
  )
endif()

if(NOT TARGET_EMSCRIPTEN AND (TARGET_LINUX OR TARGET_CHROMEOS))
  list(APPEND COMPONENT_BASE_SOURCES_POSIX_UNPROCESSED
    "debug/proc_maps_linux.cc"
    "debug/proc_maps_linux.h"
    "files/dir_reader_linux.h"
    "files/file_path_watcher_linux.cc"
    "files/file_util_linux.cc"
    "process/internal_linux.cc"
    "process/internal_linux.h"
    "process/memory_linux.cc"
    "process/process_handle_linux.cc"
    "process/process_iterator_linux.cc"
    "process/process_linux.cc"
    "process/process_metrics_linux.cc"
    "threading/platform_thread_linux.cc"
  )
endif()

if(TARGET_POSIX AND NOT TARGET_ANDROID AND NOT TARGET_MACOS)
  list(APPEND COMPONENT_BASE_SOURCES_POSIX_UNPROCESSED
    "memory/platform_shared_memory_region_posix.cc"
  )
endif()

if(TARGET_POSIX AND NOT TARGET_APPLE)
  list(APPEND COMPONENT_BASE_SOURCES_POSIX_UNPROCESSED
    "time/time_conversion_posix.cc"
    "time/time_exploded_posix.cc"
    "time/time_now_posix.cc"
  )
  if(NOT TARGET_CHROMECAST)
    list(APPEND COMPONENT_BASE_SOURCES_POSIX_UNPROCESSED
      "time/time_exploded_icu.cc"
    )
  endif()
endif()

if(TARGET_POSIX AND NOT TARGET_APPLE AND NOT USE_NACL)
  list(APPEND COMPONENT_BASE_SOURCES_POSIX_UNPROCESSED
    "posix/can_lower_nice_to.cc"
    "posix/can_lower_nice_to.h"
  )
endif()

if((TARGET_POSIX AND NOT TARGET_APPLE AND NOT TARGET_ANDROID AND NOT TARGET_CHROMEOS_ASH) OR TARGET_FUCHSIA)
  list(APPEND COMPONENT_BASE_SOURCES_POSIX_UNPROCESSED
    "power_monitor/power_monitor_device_source_stub.cc"
  )
endif()

list(APPEND COMPONENT_BASE_SOURCES ${COMPONENT_BASE_SOURCES_POSIX_UNPROCESSED})
