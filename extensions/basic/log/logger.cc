#include "basic/log/logger.h" // IWYU pragma: associated

#include <base/location.h>

#include <iostream>

namespace gloer {
namespace log {

bool VlogIsOnForLocation(
  const ::base::Location& from_here
  , int verbose_level)
{
  return (verbose_level <=
          logging::GetVlogLevelHelper(from_here.file_name(),
                                      ::strlen(from_here.file_name())));
}

} // namespace log
} // namespace gloer
