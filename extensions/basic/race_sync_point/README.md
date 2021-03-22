# About

unit tests and stress test use the SyncPoint utility to simulate specific execution sequence.

```cpp
// Use TEST_SYNC_POINT to specify sync points inside code base.
// Sync points can have happens-after depedency on other sync points,
// configured at runtime via RaceSyncPoint::ClearAndLoadDependencies. This could be
// utilized to re-produce race conditions between threads.
// TEST_SYNC_POINT is no op in release build.
```

## EXAMPLES

Changes execution order from `sync_points_A` to `sync_points_B`:

```cpp
static const char* sync_points_A[4] = {
     "WalManager::GetSortedWalsOfType:1",
     "WalManager::PurgeObsoleteFiles:1",
     "WalManager::PurgeObsoleteFiles:2",
     "WalManager::GetSortedWalsOfType:2"};

basis::RaceSyncPoint::GetInstance()->ClearAndLoadDependencies(
{ { sync_points_A[0], sync_points_A[1] },
  { sync_points_A[2], sync_points_A[3] },
});

basis::RaceSyncPoint::GetInstance()->EnableProcessing();

/// ...

basis::RaceSyncPoint::GetInstance()->ClearTrace();
basis::RaceSyncPoint::GetInstance()->DisableProcessing();

// Lets change execution order:

static const char* sync_points_B[4] = {
     "WalManager::GetSortedWalFiles:1",
     "WalManager::PurgeObsoleteFiles:1",
     "WalManager::PurgeObsoleteFiles:2",
     "WalManager::GetSortedWalFiles:2"};

basis::RaceSyncPoint::GetInstance()->ClearAndLoadDependencies(
{ { sync_points_B[0], sync_points_B[1] },
  { sync_points_B[2], sync_points_B[3] },
});

basis::RaceSyncPoint::GetInstance()->EnableProcessing();

/// ...

basis::RaceSyncPoint::GetInstance()->ClearTrace();
basis::RaceSyncPoint::GetInstance()->DisableProcessing();
```
