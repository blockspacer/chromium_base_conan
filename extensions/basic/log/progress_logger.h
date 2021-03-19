#pragma once

#include <base/base_export.h>
#include <base/logging.h>
#include <base/macros.h>
#include <base/sequence_checker.h>
#include <base/callback.h>
#include <base/optional.h>
#include <base/location.h>
#include <basic/rvalue_cast.h>

#include <iostream>
#include <string>
#include <cstdint>

namespace basic {

extern const char kProgressBannerStr[];

/*
 * USAGE
  #include <base/threading/platform_thread.h>
  #include <base/threading/thread.h>
  #include <base/time/time.h>

  if (LOG_IS_ON(INFO))
  {
    ::basic::ProgressLogger progress(
      5
      , &std::cout
      , "Loading progress");

    progress.setPoints(2);
    // Output:
    //  Loading progress
    //  ----5---10---15---20---25---30---35---40---45---50---55---60---65---70---75---80---85---90---95--100
    //  ****************************************

    ::base::PlatformThread::Sleep(
      ::base::TimeDelta::FromMilliseconds(900));

    ++progress;
    // Output:
    //  Loading progress
    //  ----5---10---15---20---25---30---35---40---45---50---55---60---65---70---75---80---85---90---95--100
    //  ************************************************************

    ::base::PlatformThread::Sleep(
      ::base::TimeDelta::FromMilliseconds(900));

    // Output:
    //  Loading progress
    //  ----5---10---15---20---25---30---35---40---45---50---55---60---65---70---75---80---85---90---95--100
    //  ****************************************************************************************************
  }
*/
class ProgressLogger {
 public:
  using PointType = uint64_t;

  // nullptr means no output.
  ProgressLogger();

  // nullptr means no output.
  // The null value is useful for passing along the ostream pointer from another caller.
  explicit ProgressLogger(
    PointType completePoints
    , std::ostream* outStream = &std::cerr
    , const std::string& title = "");

  ~ProgressLogger();

  ProgressLogger& operator++()
  {
    if (++currentPoints_ >= nextMilestonePoints_)
    {
      toNextMilestone();
    }

    return *this;
  }

  ProgressLogger& operator+=(PointType amount)
  {
    if ((currentPoints_ += amount) >= nextMilestonePoints_)
    {
      toNextMilestone();
    }

    return *this;
  }

  void setPoints(PointType to)
  {
    currentPoints_ = to;

    if (currentPoints_ >= nextMilestonePoints_)
    {
      toNextMilestone();
    }
  }

  void setMaxPoints()
  {
    setPoints(maxPoints_);
  }

 private:
  void toNextMilestone();

 private:
  PointType currentPoints_;

  PointType nextMilestonePoints_;

  PointType maxPoints_;

  unsigned char milestonesReached_;

  std::ostream* stream_;

  SEQUENCE_CHECKER(sequence_checker_);

  DISALLOW_COPY_AND_ASSIGN(ProgressLogger);
};

} // namespace basic
