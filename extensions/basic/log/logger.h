#pragma once

#include <memory>
#include <string>

#include <base/logging.h>
#include <base/trace_event/trace_event.h>

namespace base {
class Location;
}  // namespace base

#define VLOG_LOC_STREAM(from_here, verbose_level)                     \
  logging::LogMessage(from_here.file_name(), from_here.line_number(), \
                      -verbose_level)                                 \
      .stream()

#define VLOG_LOC_IF(from_here, verbose_level, condition) \
  LAZY_STREAM(VLOG_LOC_STREAM(from_here, verbose_level), \
              condition &&                               \
                  (VLOG_IS_ON(verbose_level) ||          \
                   ::gloer::log::VlogIsOnForLocation(from_here, verbose_level)))

// USAGE:
// command_line->AppendSwitchASCII(switches::kV, "1");
// DVLOG(1) << "number of arguments: " << argc;
//
#define DVLOG_LOC(from_here, verbose_level)              \
  VLOG_LOC_IF(from_here, verbose_level, DCHECK_IS_ON())

// USAGE:
// #define MY_FILE_VERBOSE_LOG 1
// command_line->AppendSwitchASCII(switches::kV, "1");
// DVLOG(1) << "number of arguments: " << argc;
//
#define DVLOG_LOC_IF(from_here, verbose_level, condition)  \
  VLOG_LOC_IF(from_here, verbose_level, DCHECK_IS_ON() && condition)

#define VLOG_LOC(from_here, verbose_level)              \
  VLOG_LOC_IF(from_here, verbose_level, 1)

namespace gloer {
namespace log {

bool VlogIsOnForLocation(const ::base::Location& from_here, int verbose_level);

} // namespace log
} // namespace gloer
