# see component("base") in BUILD.gn
list(APPEND LIB_BASE_STATIC_UNPROCESSED
  "base_switches.cc"
  "base_switches.h"
)

if(TARGET_WINDOWS)
  list(APPEND LIB_BASE_STATIC_UNPROCESSED
    "win/static_constants.cc"
    "win/static_constants.h"
  )
endif()

list(APPEND COMPONENT_BASE_SOURCES ${LIB_BASE_STATIC_UNPROCESSED})
