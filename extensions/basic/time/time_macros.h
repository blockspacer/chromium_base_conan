#pragma once

#define INTERNAL_DO_EVERY_N_US(periodInMicroseconds, now_microsec) \
  static ::base::subtle::Atomic64 STR_CONCAT(doeverys_, __LINE__) = 0; \
  const int64_t STR_CONCAT(doeverys_ts_, __LINE__) = now_microsec; \
  const int64_t STR_CONCAT(doeverys_seen_, __LINE__) = STR_CONCAT(doeverys_, __LINE__); \
  if(STR_CONCAT(doeverys_ts_, __LINE__) >= \
             (STR_CONCAT(doeverys_seen_, __LINE__) + periodInMicroseconds) &&  \
             ::base::subtle::NoBarrier_CompareAndSwap(                \
                 &STR_CONCAT(doeverys_, __LINE__),                 \
                 STR_CONCAT(doeverys_seen_, __LINE__),             \
                 STR_CONCAT(doeverys_ts_, __LINE__))               \
             == STR_CONCAT(doeverys_seen_, __LINE__))

// USAGE
//
// DO_EVERY_N_US(100L) {
//   // code here ...
// }
//
#define DO_EVERY_N_US(periodInMicroseconds) \
  INTERNAL_DO_EVERY_N_US(periodInMicroseconds, (base::Time::Now() - base::Time::UnixEpoch()).InMicroseconds())

// 1'000'000 microseconds equals 1 second
//
// USAGE
//
// DO_EVERY_SECOND() {
//   // code here ...
// }
//
#define DO_EVERY_SECOND() \
  DO_EVERY_N_US(1'000'000L)
