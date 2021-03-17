#
# See https://source.chromium.org/chromium/chromium/src/+/master:base/test/BUILD.gn

# see static_library("test_config") in /test/BUILD.gn
list(APPEND LIB_TEST_CONFIG_UNPROCESSED
  "test_switches.cc"
  "test_switches.h"
  "test_timeouts.cc"
  "test_timeouts.h"
)

list(TRANSFORM LIB_TEST_CONFIG_UNPROCESSED PREPEND "test/")
list(APPEND COMPONENT_BASE_SOURCES ${LIB_TEST_CONFIG_UNPROCESSED})
