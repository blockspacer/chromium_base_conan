# Usage

Recording activity over a period of time is known as tracing.

NOTE: Make sure recorded period of time is short to keep trace report small. Big trace report can not not be loaded into `chrome://tracing`.

Tracing can help identify performance bottlenecks, slow operations, and events with irregular lengths (leading to e.g. framerate variation).

Our tracing system is invasive (or inline) profiling that requires you to modify your existing source code (to use macros that handle timing).

Alternative to our tracing system is non-invasive (or external) profiling.

External profilers will generate sample data by polling the target application at regular intervals (usually capped at 1ms), so the granularity of your sampling is limited by that constraint.

If you make a call to 30 separate functions during that millisecond sampling interval using external profiler, that information will not be displayed in the resulting data (rather you may see a single function taking 1ms of time).

Our tracing system allows to navigate the profiling timeline to see what is really going on while external profilers give information for whatever functions are being called, on whatever threads, regardless of what you are looking for.

Writing a custom viewer is a non-trivial task. We use `chrome://tracing` to view inline profiling data.

`chrome://tracing` allows you to load external log files (in JSON format).

Trace viewer can be embedded as a component in your own code because the Javascript front-end code for rendering the timeline is open sourced, see `https://github.com/catapult-project/catapult/tree/master/tracing`

Its easy to extend trace viewer `https://github.com/catapult-project/catapult/blob/master/tracing/docs/extending-and-customizing-trace-viewer.md`

The tracing data format is a non-optimized JSON file containing a sequence of event blocks.

Each block includes the following name/value pairs:

'cat' – the category for this event. Useful when doing larger grouping (eg "UnitUpdates")
'name' – the name of this event (eg 'PathingUpdate')
'pid' – the processor ID that spawned this event
'tid' – the thread ID that spawned this event
'ts' – the processor time stamp at the time this event was created
'ph' – the phase or type of this event
'args' – any programmatic metadata that's attached to this event

```json
[
  {
       "cat": "MY_SUBSYSTEM",  //catagory
       "pid": 4260,  //process ID
       "tid": 4776, //thread ID
       "ts": 2168627922668, //time-stamp of this event
       "ph": "B", // Begin sample
       "name": "doSomethingCostly", //name of this event
       "args": { //arguments associated with this event.
         }
  },
]
```

See Trace Event Format if you want to generate traces yourself `https://github.com/catapult-project/catapult/blob/master/tracing/docs/getting-started.md#making-traces`

If you want to know more about tracing, see:

* https://www.gamasutra.com/view/news/176420/Indepth_Using_Chrometracing_to_view_your_inline_profiling_data.php
* https://slack.engineering/chrome-tracing-for-fun-and-profit/
* https://www.chromium.org/developers/how-tos/trace-event-profiling-tool/recording-tracing-runs
* https://www.chromium.org/developers/how-tos/trace-event-profiling-tool
* https://skia.org/dev/tools/tracing
* https://developer.android.com/topic/performance/tracing
* https://www.chromium.org/developers/how-tos/trace-event-profiling-tool/tracing-event-instrumentation
* https://www.chromium.org/developers/how-tos/trace-event-profiling-tool/trace-event-reading
* https://github.com/mbbill/libTraceEvent
* https://habr.com/ru/post/256907/

Use ``::base::trace_event` for performance instrumentation and logging like Chrome Trace Events, memory-infra memory dumps, netlog, etc.

Use `::base::trace_event::TraceLog::GetInstance()->Flush` to save trace report into file.

You can open resulting file in `chrome://tracing` or `about://tracing`

First, include some files from `base/trace_event`:

```cpp
#include <base/trace_event/trace_event.h>
#include <base/trace_event/common/trace_event_common.h>
#include <base/trace_event/trace_event.h>
#include <base/trace_event/trace_buffer.h>
#include <base/trace_event/trace_log.h>
#include <base/trace_event/memory_dump_manager.h>
#include <base/trace_event/heap_profiler.h>
#include <base/trace_event/heap_profiler_allocation_context_tracker.h>
#include <base/trace_event/heap_profiler_event_filter.h>#include <base/trace_event/malloc_dump_provider.h>
#include <base/trace_event/memory_dump_provider.h>
#include <base/trace_event/memory_dump_scheduler.h>
#include <base/trace_event/memory_infra_background_whitelist.h>
#include <base/trace_event/process_memory_dump.h>
```

Trace macros are very low overhead.

When tracing is not turned on, trace macros cost at most a few dozen clocks.

When running, trace macros cost a few thousand clocks at most.

Arguments to the trace macro are evaluated only when tracing is on - if tracing is off, the value of the arguments dont get computed.

The trace system will automatically add information about current process id, thread id, and a timestamp in microseconds.

## Function Tracing

The basic trace macros are TRACE_EVENTx, in 0, 1, and 2 argument flavors:

```cpp
#include <base/trace_event/trace_event.h>
// This traces the start and end of the function automatically:
void doSomethingCostly() {
  TRACE_EVENT0("MY_SUBSYSTEM", "doSomethingCostly");
  ...
}
```

The "MY_SUBSYSTEM" argument is a logical category for the trace event.

This category can be used to hide certain kinds events, or even skip them from being collected.

A common practice is to use the module name in which the code lies as logical category name, so for example, code in content/renderer gets the "renderer" category.

TRACE_EVENT1 and 2 allows you to capture 1 and 2 pieces of data long with the event.

```cpp
  const std::string& name = ...;
  TRACE_EVENT1("leveldb", "ChromiumEnv::RewriteDB", "name", name);
```

So, for example, this records the paint dimensions number along with the paint:

```cpp
    void RenderWidget::paint(const Rect& r) {
        TRACE_EVENT2("renderer", "RenderWidget::paint", "width", r.width(), "height", r.height());
```

## Counters

To track a value as it evolves over time, use TRACE_COUNTERx or TRACE_COUNTER_IDx.

Sometimes a counter is specific to a class instance. For that, use the _ID variant.

For example:

```cpp
#include "base/trace_event/trace_event.h"
shmAlloc(...) {
   ...
   TRACE_COUNTER2("shm", "BytesAllocated", "allocated", g_shmBytesAllocated, "remaining", g_shmBytesFree);
}
shmFree(...) {
   ...
   TRACE_COUNTER2("shm", "BytesAllocated", "allocated", g_shmBytesAllocated, "remaining", g_shmBytesFree);
}
```

Sometimes, you want to track two counters at once. You can do this with two
counter macros:

```cpp
  TRACE_COUNTER1("MY_SUBSYSTEM", "myCounter0", g_myCounterValue[0]);
  TRACE_COUNTER1("MY_SUBSYSTEM", "myCounter1", g_myCounterValue[1]);
```

Or you can do it with a combined macro:

```cpp
  TRACE_COUNTER2("MY_SUBSYSTEM", "myCounter",
      "bytesPinned", g_myCounterValue[0],
      "bytesAllocated", g_myCounterValue[1]);
```

This indicates to the tracing UI that these counters should be displayed
in a single graph, as a summed area chart.

More examples:

```cpp
TRACE_COUNTER2("dom", "numDOMNodes", calcNumNodes());
TRACE_COUNTER_WITH_TIMESTAMP1("all", "TRACE_COUNTER_WITH_TIMESTAMP1 call",
                              TimeTicks::FromInternalValue(42), 31415);
TRACE_COUNTER_WITH_TIMESTAMP2("all", "TRACE_COUNTER_WITH_TIMESTAMP2 call",
                              TimeTicks::FromInternalValue(42),
                              "a", 30000, "b", 1415);

TRACE_COUNTER_ID1("all", "TRACE_COUNTER_ID1 call", 0x319009, 31415);
TRACE_COUNTER_ID2("all", "TRACE_COUNTER_ID2 call", 0x319009,
                  "a", 30000, "b", 1415);


TRACE_COUNTER_WITH_FLAG1(
    TRACE_DISABLED_BY_DEFAULT("sequence_manager"), GetName(),
    TRACE_EVENT_FLAG_DISALLOW_POSTTASK,
    any_thread_.immediate_incoming_queue.size() +
        main_thread_only().immediate_work_queue->Size() +
        main_thread_only().delayed_work_queue->Size() +
        main_thread_only().delayed_incoming_queue.size());
```

## Asynchronous Events

Sometimes, you will have an asynchronous event that you want to track.

For this, use TRACE_EVENT_ASYNC_BEGINx and TRACE_EVENT_ASYNC_ENDx. For example:

```cpp
#include "base/trace_event/trace_event.h"
AsyncFileOperation::AsyncFileOperation(...) {
    TRACE_EVENT_ASYNC_BEGIN("io", "AsyncFileOperation", this);
}
void AsyncFileOperation::OnReady() {
    TRACE_EVENT_ASYNC_END("io", "AsyncFileOperation", this);
    ...
}
```

The third parameter is a unique ID to match ASYNC_BEGIN/ASYNC_END pairs. Pointers can be used for the ID parameter.

Async operations can start and finish on different threads, or even different proceses.

Association is done by the concatenation of the name string and the third "id" argument.

The nearest match in time establishes the relationship.

## Synchronous Events - measure execution time between two code points

Note: Our tools can not always determine the correct BEGIN/END pairs unless
these are used in the same scope. Use ASYNC_BEGIN/ASYNC_END macros if you
need them to be in separate scopes.

```cpp
TRACE_EVENT_BEGIN0("headless", "App:MESSAGE_LOOP");
TRACE_EVENT_END0("headless", "App:MESSAGE_LOOP");
```

## Instant Events

```cpp
TRACE_EVENT_INSTANT0("MY_SUBSYSTEM", "SomeImportantEvent")
```

## Track memory usage in the heap profiler

Record a trace as usual: open chrome://tracing.

Make sure to enable the memory-infra category on the right.

See https://chromium.googlesource.com/chromium/src/+/master/docs/memory-infra/README.md

See `base/trace_event/heap_profiler.h` and `base/sampling_heap_profiler/sampling_heap_profiler.h`

See `base::SamplingHeapProfiler::Get()->GetSamples`

```cpp
TRACE_HEAP_PROFILER_API_SCOPED_TASK_EXECUTION heap_profiler_scope(
  controller->created_from_location().file_name());

TRACE_HEAP_PROFILER_API_SCOPED_WITH_PROGRAM_COUNTER e1(pc1);

HEAP_PROFILER_SCOPED_IGNORE;
```

## Builtin categories

See `base/trace_event/builtin_categories.h`

## TRACE_DISABLED_BY_DEFAULT

```cpp
// This will mark the trace event as disabled by default. The user will need
// to explicitly enable the event.
#define TRACE_DISABLED_BY_DEFAULT(name) "disabled-by-default-" name
```

Usage:

```cpp
  TRACE_EVENT0(TRACE_DISABLED_BY_DEFAULT("cpu_profiler"),
               "StackSamplingProfiler::SamplingThread::ScheduleShutdownIfIdle");

  TRACE_EVENT_INSTANT1(TRACE_DISABLED_BY_DEFAULT("memory-infra"),
                       "MemoryPressureListener::NotifyMemoryPressure",
                       TRACE_EVENT_SCOPE_THREAD, "level",
                       memory_pressure_level);
```

Usage:

```cpp
constexpr const char kTraceCategory[] = TRACE_DISABLED_BY_DEFAULT("power");
const char kEventTitle[] = "CPU Frequency";
bool CPUFreqMonitorDelegate::IsTraceCategoryEnabled() const {
  bool enabled;
  TRACE_EVENT_CATEGORY_GROUP_ENABLED(kTraceCategory, &enabled);
  return enabled;
}
void CPUFreqMonitorDelegate::RecordFrequency(unsigned int cpu_id,
                                             unsigned int freq) {
  TRACE_COUNTER_ID1(kTraceCategory, kEventTitle, cpu_id, freq);
}
```

## Memory scoping note

Tracing copies the pointers, not the string content, of the strings passed
in for category, name, and arg_names.  Thus, the following code will cause
problems:

```cpp
    char* str = strdup("importantName");
    TRACE_EVENT_INSTANT0("SUBSYSTEM", str);  // BAD!
    free(str);                   // Trace system now has dangling pointer
```

To avoid this issue with the |name| and |arg_name| parameters, use the
TRACE_EVENT_COPY_XXX overloads of the macros at additional runtime
overhead.

```cpp
const int kThreadId = 42;
const int kAsyncId = 5;
    TRACE_EVENT_COPY_BEGIN_WITH_ID_TID_AND_TIMESTAMP0("all",
        "TRACE_EVENT_COPY_BEGIN_WITH_ID_TID_AND_TIMESTAMP0 call",
        kAsyncId, kThreadId, TimeTicks::FromInternalValue(12345));
    TRACE_EVENT_COPY_END_WITH_ID_TID_AND_TIMESTAMP0("all",
        "TRACE_EVENT_COPY_END_WITH_ID_TID_AND_TIMESTAMP0 call",
        kAsyncId, kThreadId, TimeTicks::FromInternalValue(23456));
```

Notes: The category must always be in a long-lived char* (i.e. static const).
       The |arg_values|, when used, are always deep copied with the _COPY
       macros.

## Thread Safety

All tracing macros are thread safe and can be used from any process.


## Memory dumps in trace reports

See https://www.chromium.org/developers/how-tos/trace-event-profiling-tool/memory/howto-adding-memory-infra-tracing-to-a-component

```cpp
base::tracing::ProcessMetricsMemoryDumpProvider::RegisterForProcess(::base::kNullProcessId);
```

```cpp
base::trace_event::MemoryDumpManager::GetInstance()->RegisterDumpProvider(...);
```

Example:

```cpp
#include "base/trace_event/memory_dump_manager.h"
#include "base/trace_event/memory_dump_provider.h"
#include "base/trace_event/process_memory_dump.h"
#include "base/trace_event/trace_event.h"

using base::FilePath;
using base::trace_event::MemoryAllocatorDump;
using base::trace_event::MemoryDumpArgs;
using base::trace_event::ProcessMemoryDump;

MemoryAllocatorDump* CreateDumpMalloced(ProcessMemoryDump* pmd,
                                        const std::string& name,
                                        size_t size) {
  auto* dump = pmd->CreateAllocatorDump(name);
  dump->AddScalar(MemoryAllocatorDump::kNameSize,
                  MemoryAllocatorDump::kUnitsBytes, size);
  static const char* system_allocator_name =
      base::trace_event::MemoryDumpManager::GetInstance()
          ->system_allocator_pool_name();
  if (system_allocator_name)
    pmd->AddSuballocation(dump->guid(), system_allocator_name);
  return dump;
}

void RecordCacheUsageInTracing(ProcessMemoryDump* pmd,
                               DBTracker::SharedReadCacheUse cache) {
  std::string name = GetDumpNameForCache(cache);
  leveldb::Cache* cache_ptr = nullptr;
  switch (cache) {
    case DBTracker::SharedReadCacheUse_Browser:
      cache_ptr = leveldb_chrome::GetSharedBrowserBlockCache();
      break;
    case DBTracker::SharedReadCacheUse_Web:
      cache_ptr = leveldb_chrome::GetSharedWebBlockCache();
      break;
    case DBTracker::SharedReadCacheUse_Unified:
      cache_ptr = leveldb_chrome::GetSharedBrowserBlockCache();
      break;
    case DBTracker::SharedReadCacheUse_InMemory:
      cache_ptr = leveldb_chrome::GetSharedInMemoryBlockCache();
      break;
    case DBTracker::SharedReadCacheUse_NumCacheUses:
      NOTREACHED();
  }
  if (!cache_ptr)
    return;
  CreateDumpMalloced(pmd, name, cache_ptr->TotalCharge());
}

// Reports live databases and in-memory env's to memory-infra. For each live
// database the following information is reported:
// 1. Instance pointer (to disambiguate databases).
// 2. Memory taken by the database, with the shared cache being attributed
// equally to each database sharing 3. The name of the database (when not in
// BACKGROUND mode to avoid exposing
//    PIIs in slow reports).
//
// Example report (as seen after clicking "leveldatabase" in "Overview" pane
// in Chrome tracing UI):
//
// Component                  effective_size  size        name
// ---------------------------------------------------------------------------
// leveldatabase              390 KiB         490 KiB
//   db_0x7FE70F2040A0        100 KiB         100 KiB     Users/.../Sync
//     block_cache (browser)  40 KiB          40 KiB
//   db_0x7FE70F530D80        150 KiB         150 KiB     Users/.../Data Proxy
//     block_cache (web)      30 KiB          30 KiB
//   db_0x7FE70F530D80        140 KiB         140 KiB     Users/.../Extensions
//     block_cache (web)      30 KiB          30 KiB
//   block_cache              0 KiB           100 KiB
//     browser                0 KiB           40 KiB
//     web                    0 KiB           60 KiB
//   memenv_0x7FE80F2040A0    4 KiB           4 KiB
//   memenv_0x7FE80F3040A0    4 KiB           4 KiB
//
class DBTracker::MemoryDumpProvider
    : public base::trace_event::MemoryDumpProvider {
 public:
  void DumpAllDatabases(ProcessMemoryDump* pmd);
  bool OnMemoryDump(const MemoryDumpArgs& args,
                    ProcessMemoryDump* pmd) override {
    DumpAllDatabases(pmd);
    return true;
  }
  void DatabaseOpened(const TrackedDBImpl* database) {
    database_use_count_[database->block_cache_type()]++;
  }
  void DatabaseDestroyed(const TrackedDBImpl* database) {
    database_use_count_[database->block_cache_type()]--;
    DCHECK_GE(database_use_count_[database->block_cache_type()], 0);
  }
 private:
  void DumpVisitor(ProcessMemoryDump* pmd, TrackedDB* db);
  int database_use_count_[SharedReadCacheUse_NumCacheUses] = {};
};
void DBTracker::MemoryDumpProvider::DumpAllDatabases(ProcessMemoryDump* pmd) {
  if (pmd->GetAllocatorDump("leveldatabase"))
    return;
  pmd->CreateAllocatorDump("leveldatabase");
  const auto* browser_cache = leveldb_chrome::GetSharedBrowserBlockCache();
  const auto* web_cache = leveldb_chrome::GetSharedWebBlockCache();
  if (browser_cache == web_cache) {
    RecordCacheUsageInTracing(pmd, SharedReadCacheUse_Unified);
  } else {
    RecordCacheUsageInTracing(pmd, SharedReadCacheUse_Browser);
    RecordCacheUsageInTracing(pmd, SharedReadCacheUse_Web);
  }
  RecordCacheUsageInTracing(pmd, SharedReadCacheUse_InMemory);
  DBTracker::GetInstance()->VisitDatabases(
      base::BindRepeating(&DBTracker::MemoryDumpProvider::DumpVisitor,
                          base::Unretained(this), base::Unretained(pmd)));
  leveldb_chrome::DumpAllTrackedEnvs(pmd);
}
void DBTracker::MemoryDumpProvider::DumpVisitor(ProcessMemoryDump* pmd,
                                                TrackedDB* db) {
  std::string db_dump_name = GetDumpNameForDB(db);
  auto* db_cache_dump = pmd->CreateAllocatorDump(db_dump_name + "/block_cache");
  const std::string cache_dump_name =
      GetDumpNameForCache(db->block_cache_type());
  pmd->AddSuballocation(db_cache_dump->guid(), cache_dump_name);
  size_t cache_usage =
      pmd->GetAllocatorDump(cache_dump_name)->GetSizeInternal();
  // The |database_use_count_| can be accessed by the visitor because the
  // visitor is called holding the lock at DBTracker.
  size_t cache_usage_pss =
      cache_usage / database_use_count_[db->block_cache_type()];
  db_cache_dump->AddScalar(MemoryAllocatorDump::kNameSize,
                           MemoryAllocatorDump::kUnitsBytes, cache_usage_pss);
  auto* db_dump = pmd->CreateAllocatorDump(db_dump_name);
  uint64_t total_usage = 0;
  std::string usage_string;
  bool success =
      db->GetProperty("leveldb.approximate-memory-usage", &usage_string) &&
      base::StringToUint64(usage_string, &total_usage);
  DCHECK(success);
  db_dump->AddScalar(MemoryAllocatorDump::kNameSize,
                     MemoryAllocatorDump::kUnitsBytes,
                     total_usage - cache_usage + cache_usage_pss);
  if (pmd->dump_args().level_of_detail !=
      base::trace_event::MemoryDumpLevelOfDetail::BACKGROUND) {
    db_dump->AddString("name", "", db->name());
  }
}
DBTracker::DBTracker() : mdp_(new MemoryDumpProvider()) {
  base::trace_event::MemoryDumpManager::GetInstance()->RegisterDumpProvider(
      mdp_.get(), "LevelDB", nullptr);
}
DBTracker::~DBTracker() {
  NOTREACHED();  // DBTracker is a singleton
}
// static
DBTracker* DBTracker::GetInstance() {
  static DBTracker* instance = new DBTracker();
  return instance;
}
// static
MemoryAllocatorDump* DBTracker::GetOrCreateAllocatorDump(
    ProcessMemoryDump* pmd,
    leveldb::DB* tracked_db) {
  DCHECK(GetInstance()->IsTrackedDB(tracked_db))
      << std::hex << tracked_db << " is not tracked";
  // Create dumps for all databases to make sure the shared cache is equally
  // attributed to each database sharing it.
  GetInstance()->mdp_->DumpAllDatabases(pmd);
  return pmd->GetAllocatorDump(GetDumpNameForDB(tracked_db));
}
// static
MemoryAllocatorDump* DBTracker::GetOrCreateAllocatorDump(
    ProcessMemoryDump* pmd,
    leveldb::Env* tracked_memenv) {
  GetInstance()->mdp_->DumpAllDatabases(pmd);
  return leveldb_chrome::GetEnvAllocatorDump(pmd, tracked_memenv);
}
```
