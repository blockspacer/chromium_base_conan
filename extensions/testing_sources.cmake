#
# See:
# https://source.chromium.org/chromium/chromium/src/+/master:build_overrides/gtest.gni
# https://source.chromium.org/chromium/chromium/src/+/master:testing/gtest/BUILD.gn

# Exclude support for registering main function in multi-process tests.
set(gtest_include_multiprocess TRUE)

# Exclude support for platform-specific operations across unit tests.
set(gtest_include_platform_test TRUE)

# Exclude support for testing Objective C code on OS X and iOS.
set(gtest_include_objc_support TRUE)

# Exclude support for flushing coverage files on iOS.
set(gtest_include_ios_coverage TRUE)

list(APPEND GTEST_SOURCES_UNPROCESSED
  "include/gtest/gtest-death-test.h"
  "include/gtest/gtest-message.h"
  "include/gtest/gtest-param-test.h"
  "include/gtest/gtest-spi.h"
  "include/gtest/gtest.h"
  "include/gtest/gtest_prod.h"
)

if(gtest_include_multiprocess)
  list(APPEND GTEST_SOURCES_UNPROCESSED
    "../multiprocess_func_list.cc"
    "../multiprocess_func_list.cc"
  )
endif()

if(gtest_include_platform_test)
  list(APPEND GTEST_SOURCES_UNPROCESSED
    "../platform_test.h"
  )
endif()

if (TARGET_APPLE AND gtest_include_objc_support)
  list(APPEND GTEST_SOURCES_UNPROCESSED
    "../gtest_mac.h"
    "../gtest_mac.mm"
  )
  if (gtest_include_platform_test)
    list(APPEND GTEST_SOURCES_UNPROCESSED
      "../platform_test_mac.mm"
    )
  endif()
endif()

if (TARGET_IOS AND gtest_include_ios_coverage)
  list(APPEND GTEST_SOURCES_UNPROCESSED
    "../coverage_util_ios.h"
    "../coverage_util_ios.mm"
  )
endif()

list(TRANSFORM GTEST_SOURCES_UNPROCESSED PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/extensions/testing/gtest/")
list(APPEND BASE_SOURCES ${GTEST_SOURCES_UNPROCESSED})
