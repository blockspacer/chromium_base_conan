#include "basic/log/progress_logger.h" // IWYU pragma: associated

#include <algorithm>
#include <ostream>
#include <limits>
#include <string>

namespace basic {

namespace { const unsigned char kWidth = 100; }

const char kProgressBannerStr[]
  = "----5---10---15---20---25---30---35---40---45---50---55---60"
    "---65---70---75---80---85---90---95--100";

ProgressLogger::ProgressLogger()
  : currentPoints_(0)
  , nextMilestonePoints_(std::numeric_limits<PointType>::max())
  , maxPoints_(nextMilestonePoints_)
  , milestonesReached_(0)
  , stream_(nullptr)
{
  DETACH_FROM_SEQUENCE(sequence_checker_);
}

ProgressLogger::ProgressLogger(
  PointType completePoints
  , std::ostream* outStream
  , const std::string& title)
  : currentPoints_(0)
  , nextMilestonePoints_(completePoints / kWidth)
  , maxPoints_(completePoints)
  , milestonesReached_(0)
  , stream_(outStream)
{
  DETACH_FROM_SEQUENCE(sequence_checker_);

  if (!stream_)
  {
    nextMilestonePoints_ = std::numeric_limits<PointType>::max();
    return;
  }

  if (!title.empty())
  {
    DCHECK(stream_);
    (*stream_) << title << '\n';
  }

  DCHECK(stream_);
  (*stream_) << kProgressBannerStr << '\n';
}

ProgressLogger::~ProgressLogger()
{
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  if (stream_)
  {
    setMaxPoints();
  }
}

void ProgressLogger::toNextMilestone()
{
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  if (!stream_)
  {
    currentPoints_ = 0;
    return;
  }

  if (!maxPoints_)
  {
    return;
  }

  PointType milestone
    = std::min(
        static_cast<PointType>(kWidth)
        , (currentPoints_ * kWidth) / maxPoints_
      );

  for (; milestonesReached_ < milestone; ++milestonesReached_)
  {
    DCHECK(stream_);
    (*stream_) << '*';
  }

  const bool isEndMilestone
    = milestone == kWidth;

  if (isEndMilestone)
  {
    DCHECK(stream_);
    (*stream_) << '\n';
    nextMilestonePoints_ = std::numeric_limits<PointType>::max();
    stream_ = nullptr;
  } else {
    nextMilestonePoints_
      = std::max(
          nextMilestonePoints_
          , ((milestone + 1) * maxPoints_ + kWidth - 1) / kWidth
        );
  }
}

} // namespace basic
