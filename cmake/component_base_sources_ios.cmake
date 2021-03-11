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

list(TRANSFORM COMPONENT_BASE_SOURCES_IOS_UNPROCESSED PREPEND ${BASE_SOURCES_PATH})
list(APPEND COMPONENT_BASE_SOURCES ${COMPONENT_BASE_SOURCES_IOS_UNPROCESSED})
