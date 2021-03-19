#include <base/logging.h>
#include <base/location.h>

#include <basic/core/sequence_bound_flag.h>

#include <atomic>

// MOTIVATION
//
// Sometimes we need to add extra checks using `bool` variable,
// but perform that checks only in debug builds.
// So we wrap `std::atomic<bool>` or `SequenceBoundFlag`
// into macros with `DCHECK_IS_ON()`.
//
// Flag that can be used on any thread
//
// USAGE
//
// DEBUG_ATOMIC_FLAG(object_valid);
// SET_DEBUG_ATOMIC_FLAG(object_valid);
// DCHECK_HAS_ATOMIC_FLAG(object_valid);
// UNSET_DEBUG_ATOMIC_FLAG(object_valid);
// DCHECK_NO_ATOMIC_FLAG(object_valid);
//
// Flag that can be used only on specific sequence
//
// USAGE
//
// DEBUG_FLAG(object_valid);
// SET_DEBUG_FLAG(object_valid);
// DCHECK_HAS_FLAG(object_valid);
// UNSET_DEBUG_FLAG(object_valid);
// DCHECK_NO_FLAG(object_valid);

// Flags some object state as `set` or `not set`.
#if DCHECK_IS_ON()
  #define DEBUG_ATOMIC_FLAG(OBJ) \
    std::atomic<bool> OBJ
#else
  #define DEBUG_ATOMIC_FLAG(OBJ)
#endif

#define DCHECK_HAS_ATOMIC_FLAG(OBJ) \
  DCHECK(OBJ.load()) \
    << FROM_HERE.ToString() \
    << " expected to be set: " STRINGIFY(OBJ);

#define DCHECK_NO_ATOMIC_FLAG(OBJ) \
  DCHECK(!OBJ.load()) \
    << FROM_HERE.ToString() \
    << " expected to be NOT set: " STRINGIFY(OBJ);

#if DCHECK_IS_ON()
  // Flags some object state as `valid`.
  #define SET_DEBUG_ATOMIC_FLAG(OBJ) \
    OBJ.store(true)
#else
  #define SET_DEBUG_ATOMIC_FLAG(OBJ)
#endif

#if DCHECK_IS_ON()
  // Flags some object state as `valid`.
  #define UNSET_DEBUG_ATOMIC_FLAG(OBJ) \
    OBJ.store(false)
#else
  #define UNSET_DEBUG_ATOMIC_FLAG(OBJ)
#endif

// Flags some object state as `set` or `not set`.
#if DCHECK_IS_ON()
  #define DEBUG_FLAG(OBJ) \
    SequenceBoundFlag OBJ
#else
  #define DEBUG_FLAG(OBJ)
#endif

#define DCHECK_HAS_FLAG(OBJ) \
  DCHECK(OBJ.IsSet()) \
    << FROM_HERE.ToString() \
    << " expected to be set: " STRINGIFY(OBJ);

#define DCHECK_NO_FLAG(OBJ) \
  DCHECK(!OBJ.IsSet()) \
    << FROM_HERE.ToString() \
    << " expected to be NOT set: " STRINGIFY(OBJ);

#if DCHECK_IS_ON()
  // Flags some object state as `valid`.
  #define SET_DEBUG_FLAG(OBJ) \
    OBJ.Set()
#else
  #define SET_DEBUG_FLAG(OBJ)
#endif

#if DCHECK_IS_ON()
  // Flags some object state as `valid`.
  #define UNSET_DEBUG_FLAG(OBJ) \
    OBJ.UnSet()
#else
  #define UNSET_DEBUG_FLAG(OBJ)
#endif
