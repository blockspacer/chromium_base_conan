#pragma once

#include <string>
#include <base/files/file_path.h>
#include <base/run_loop.h>

namespace basic {

/// \todo move to TraceManager
/// https://github.com/blockspacer/cobalt-clone-28052019/blob/89664d116629734759176d820e9923257717e09c/src/cobalt/browser/trace_manager.h
/// \todo use ScopedTraceToFile
/// https://github.com/blockspacer/cobalt-clone-cab7770533804d582eaa66c713a1582f361182d3/blob/0b72f93b07285f3af3c8452ae2ceaf5860ca7c72/src/cobalt/trace_event/scoped_trace_to_file.cc
void initTracing(
  const bool auto_start_tracer
  , const std::string& event_categories);

void writeTraceReport(
  const ::base::FilePath& output_filepath);

}  // namespace basic
