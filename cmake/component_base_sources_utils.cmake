# source_set("values_util")
list(APPEND COMPONENT_UTIL_SOURCES_UNPROCESSED
  "values/values_util.cc"
  "values/values_util.h"
)

# source_set("type_safety")
list(APPEND COMPONENT_UTIL_SOURCES_UNPROCESSED
  "type_safety/id_type.h"
  "type_safety/token_type.h"
)

# source_set("timer")
list(APPEND COMPONENT_UTIL_SOURCES_UNPROCESSED
  "timer/wall_clock_timer.h"
  "timer/wall_clock_timer.cc"
)

# source_set("memory_pressure")
list(APPEND COMPONENT_UTIL_SOURCES_UNPROCESSED
  "memory_pressure/memory_pressure_voter.cc"
  "memory_pressure/memory_pressure_voter.h"
  "memory_pressure/multi_source_memory_pressure_monitor.cc"
  "memory_pressure/multi_source_memory_pressure_monitor.h"
  "memory_pressure/system_memory_pressure_evaluator.cc"
  "memory_pressure/system_memory_pressure_evaluator.h"
)

if(TARGET_WINDOWS)
  list(APPEND COMPONENT_UTIL_SOURCES_UNPROCESSED
    "memory_pressure/system_memory_pressure_evaluator_win.cc"
    "memory_pressure/system_memory_pressure_evaluator_win.h"
  )
endif(TARGET_WINDOWS)

if(TARGET_MACOS)
  list(APPEND COMPONENT_UTIL_SOURCES_UNPROCESSED
    "memory_pressure/system_memory_pressure_evaluator_mac.cc"
    "memory_pressure/system_memory_pressure_evaluator_mac.h"
  )
endif(TARGET_MACOS)

if(TARGET_FUCHSIA)
  list(APPEND COMPONENT_UTIL_SOURCES_UNPROCESSED
    "memory_pressure/system_memory_pressure_evaluator_fuchsia.cc"
    "memory_pressure/system_memory_pressure_evaluator_fuchsia.h"
  )
endif(TARGET_FUCHSIA)

if(TARGET_LINUX OR TARGET_CHROMEOS_LACROS)
  list(APPEND COMPONENT_UTIL_SOURCES_UNPROCESSED
    "memory_pressure/system_memory_pressure_evaluator_linux.cc"
    "memory_pressure/system_memory_pressure_evaluator_linux.h"
  )
endif(TARGET_LINUX OR TARGET_CHROMEOS_LACROS)

list(TRANSFORM COMPONENT_UTIL_SOURCES_UNPROCESSED PREPEND "util/")
list(APPEND COMPONENT_BASE_SOURCES ${COMPONENT_UTIL_SOURCES_UNPROCESSED})
