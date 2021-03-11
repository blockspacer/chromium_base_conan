# see component("base") in BUILD.gn
list(APPEND COMPONENT_BASE_SOURCES_IOS_UNPROCESSED
  "critical_closure_internal_ios.mm"
  "ios/block_types.h"
  "ios/device_util.h"
  "ios/device_util.mm"
  "ios/ios_util.h"
  "ios/ios_util.mm"
  "ios/ns_error_util.h"
  "ios/ns_error_util.mm"
  "ios/scoped_critical_action.h"
  "ios/scoped_critical_action.mm"
  "message_loop/message_pump_io_ios.cc"
  "message_loop/message_pump_io_ios.h"
  "native_library_ios.mm"
  "process/launch_ios.cc"
  "process/process_metrics_ios.cc"
  "profiler/module_cache_mac.cc"
  "profiler/stack_sampler_ios.cc"
)

list(APPEND COMPONENT_BASE_SOURCES_IOS_UNPROCESSED
  "base_paths_mac.h"
  "base_paths_mac.mm"
  "file_version_info_mac.h"
  "file_version_info_mac.mm"
  "files/file_util_mac.mm"
  "mac/bundle_locations.h"
  "mac/bundle_locations.mm"
  "mac/call_with_eh_frame.cc"
  "mac/call_with_eh_frame.h"
  "mac/call_with_eh_frame_asm.S"
  "mac/foundation_util.h"
  "mac/foundation_util.mm"
  "mac/mac_logging.h"
  "mac/mac_logging.mm"
  "mac/mach_logging.cc"
  "mac/mach_logging.h"
  "mac/objc_release_properties.h"
  "mac/objc_release_properties.mm"
  "mac/scoped_block.h"
  "mac/scoped_mach_port.cc"
  "mac/scoped_mach_port.h"
  "mac/scoped_mach_vm.cc"
  "mac/scoped_mach_vm.h"
  "mac/scoped_nsautorelease_pool.h"
  "mac/scoped_nsautorelease_pool.mm"
  "mac/scoped_nsobject.h"
  "mac/scoped_objc_class_swizzler.h"
  "mac/scoped_objc_class_swizzler.mm"
  "mac/scoped_typeref.h"
  "message_loop/message_pump_mac.h"
  "message_loop/message_pump_mac.mm"
  "power_monitor/power_monitor_device_source_ios.mm"
  "process/memory_stubs.cc"
  "process/process_stubs.cc"
  "strings/sys_string_conversions_mac.mm"
  "synchronization/waitable_event_mac.cc"
  "system/sys_info_ios.mm"
  "task/thread_pool/thread_group_native_mac.h"
  "task/thread_pool/thread_group_native_mac.mm"
  "threading/platform_thread_mac.mm"
  "time/time_conversion_posix.cc"
  "time/time_mac.cc"
)

if(USE_ALLOC_SHIM)
  list(APPEND COMPONENT_BASE_SOURCES_IOS_UNPROCESSED
    "allocator/allocator_interception_mac.h"
    "allocator/allocator_interception_mac.mm"
    "allocator/malloc_zone_functions_mac.cc"
    "allocator/malloc_zone_functions_mac.h"
  )
endif(USE_ALLOC_SHIM)

# if (current_cpu == "x64" || current_cpu == "arm64")
if(TARGET_X86_64 OR TARGET_ARM64)
  list(APPEND COMPONENT_BASE_SOURCES_IOS_UNPROCESSED
    "time/time_exploded_posix.cc"
  )
else()
  list(APPEND COMPONENT_BASE_SOURCES_IOS_UNPROCESSED
    "time/time_exploded_ios.cc"
  )
endif()

list(APPEND COMPONENT_BASE_SOURCES_IOS_UNPROCESSED
  "crb_protocol_observers.h"
  "crb_protocol_observers.mm"
)

list(APPEND COMPONENT_BASE_SOURCES ${COMPONENT_BASE_SOURCES_IOS_UNPROCESSED})
