if(ENABLE_ASAN OR ENABLE_MSAN OR ENABLE_TSAN OR ENABLE_UBSAN)
  set(print_unsymbolized_stack_traces TRUE)
endif()

if (print_unsymbolized_stack_traces)
  set(LIB_SYMBOLIZE_PUBLIC_DEFINES "PRINT_UNSYMBOLIZED_STACK_TRACES=1")
endif()

list(APPEND LIB_SYMBOLIZE_UNPROCESSED
  "config.h"
  "demangle.cc"
  "demangle.h"
  "glog/logging.h"
  "glog/raw_logging.h"
  "symbolize.cc"
  "symbolize.h"
  "utilities.h"
)

list(TRANSFORM LIB_SYMBOLIZE_UNPROCESSED PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/base/third_party/symbolize/")
list(APPEND BASE_SOURCES ${LIB_SYMBOLIZE_UNPROCESSED})
