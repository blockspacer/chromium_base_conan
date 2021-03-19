#pragma once

#include <base/macros.h>
#include <base/logging.h>

#include <memory>
#include <string>
#include <cstdint>
#include <iosfwd>

// USAGE
//
// bool has_err = ...;
// LOG_TIMING_IF(has_err, logging::LOG_INFO, "Some calculations ")
// {
//   //  ... Some calculations ...
// }
//
#define LOG_TIMING_IF(condition, ...) \
  if (basic::ScopedLogRunTime internal_scopedLogRunTime(__VA_ARGS__); condition)

// USAGE
//
// LOG_TIMING(logging::LOG_INFO, "Some calculations ")
// {
//   //  ... Some calculations ...
// }
//
#define LOG_TIMING(...) \
  LOG_TIMING_IF(true, __VA_ARGS__)

namespace base {
class ElapsedTimer;
} // namespace base

namespace basic {

// USAGE
//
// {
//   ::basic::ScopedLogRunTime scopedLogRunTime{};
//   //  ... Some calculations ...
// }
//
// {
//   ::basic::ScopedLogRunTime scopedLogRunTime{logging::LOG_INFO, "Some calculations "};
//   //  ... Some calculations ...
// }
//
class ScopedLogRunTime {
public:
  ScopedLogRunTime(logging::LogSeverity = logging::LOG_INFO, const std::string& prefix = "");

  ~ScopedLogRunTime();

private:
  std::unique_ptr<::base::ElapsedTimer> timer_;

  std::string prefix_;

  logging::LogSeverity severity_;

  DISALLOW_COPY_AND_ASSIGN(ScopedLogRunTime);
};

}  // namespace basic
