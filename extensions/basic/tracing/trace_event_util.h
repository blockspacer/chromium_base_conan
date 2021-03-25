#pragma once

#define TRACE_EVENT_LOC(from_here) \
  TRACE_EVENT0("headless", \
    (std::string(from_here.file_name()) + from_here.function_name()).c_str())
