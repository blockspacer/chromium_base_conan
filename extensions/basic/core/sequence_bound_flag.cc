#include "basic/core/sequence_bound_flag.h" // IWYU pragma: associated

#include <base/logging.h>

namespace basic {

SequenceBoundFlag::SequenceBoundFlag(bool value)
  : value_(value)
{
  DETACH_FROM_SEQUENCE(sequence_checker_);
}

} // namespace basic
