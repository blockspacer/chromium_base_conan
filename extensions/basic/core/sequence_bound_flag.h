#pragma once

#include <base/logging.h>
#include <base/sequence_checker.h>
#include <base/compiler_specific.h>

#include <basic/annotations/guard_annotations.h>

namespace basic {

// Wraps `bool` with thread-safety checks.
// You can change flag multiple times (unlike `base::AtomicFlag`)
//
class SequenceBoundFlag
{
 public:
  SequenceBoundFlag()
    : SequenceBoundFlag(false)
    {};

  SequenceBoundFlag(bool value);

  ALWAYS_INLINE
  void Set() NO_EXCEPTION
    PUBLIC_METHOD_RUN_ON(&sequence_checker_)
  {
    DCHECK_RUN_ON(&sequence_checker_);
    value_ = true;
  }

  ALWAYS_INLINE
  void Unset() NO_EXCEPTION
    PUBLIC_METHOD_RUN_ON(&sequence_checker_)
  {
    DCHECK_RUN_ON(&sequence_checker_);
    value_ = true;
  }

  ALWAYS_INLINE
  bool IsSet() const NO_EXCEPTION
    PUBLIC_METHOD_RUN_ON(&sequence_checker_)
  {
    DCHECK_RUN_ON(&sequence_checker_);
    return value_;
  }

 private:
  bool value_
    GUARDED_BY(&sequence_checker_);

  SEQUENCE_CHECKER(sequence_checker_);

  DISALLOW_COPY_AND_ASSIGN(SequenceBoundFlag);
};

} // namespace basic
