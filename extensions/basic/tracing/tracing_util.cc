#include "basic/tracing/tracing_util.h" // IWYU pragma: associated

#include <base/logging.h>
#include <base/path_service.h>
#include <base/memory/ref_counted_memory.h>
#include <base/files/file_util.h>
#include <base/trace_event/trace_event.h>
#include <base/trace_event/trace_buffer.h>
#include <base/trace_event/trace_log.h>
#include <base/trace_event/memory_dump_manager.h>
#include <base/trace_event/heap_profiler.h>
#include <base/trace_event/heap_profiler_allocation_context_tracker.h>
#include <base/trace_event/heap_profiler_event_filter.h>
#include <base/sampling_heap_profiler/sampling_heap_profiler.h>
#include <base/sampling_heap_profiler/poisson_allocation_sampler.h>
#include <base/trace_event/malloc_dump_provider.h>
#include <base/trace_event/memory_dump_provider.h>
#include <base/trace_event/memory_dump_scheduler.h>
#include <base/trace_event/process_memory_dump.h>

namespace {

static const char kTraceJsonStart[]
  = "{\"traceEvents\":[";

static const char kTraceJsonEnd[]
  = "]}";

void onTraceDataCollected(
  ::base::File& _output_file
  , ::base::Closure quit_closure
  , ::base::trace_event::TraceResultBuffer* in_trace_buffer
  , const scoped_refptr<::base::RefCountedString>&
  json_events_str
  , bool has_more_events)
{
  DCHECK(in_trace_buffer);
  in_trace_buffer->AddFragment(json_events_str->data());
  if (!has_more_events) {
    quit_closure.Run();
  } else {
    _output_file.WriteAtCurrentPos(",", 1);
  }
}

}  // namespace

namespace basic {

void initTracing(
  const bool auto_start_tracer
  , const std::string& event_categories)
{
  // Used by out-of-process heap-profiling. When malloc is profiled by an
  // external process, that process will be responsible for emitting metrics on
  // behalf of this one. Thus, MallocDumpProvider should not do anything.
  ::base::trace_event::MallocDumpProvider::GetInstance()
    ->DisableMetrics();

#if defined(OS_MACOSX)
  // On macOS, this call is necessary to shim malloc zones that were created
  // after startup. This cannot be done during shim initialization because the
  // task scheduler has not yet been initialized.
  ::base::allocator::PeriodicallyShimNewMallocZones();
#endif

  // see https://github.com/mbbill/libTraceEvent
  // see https://habr.com/ru/post/256907/
  // see http://dev.chromium.org/developers/how-tos/trace-event-profiling-tool
  // see https://www.chromium.org/developers/how-tos/trace-event-profiling-tool/tracing-event-instrumentation
  ::base::trace_event::TraceConfig trace_config{
    // |category_filter_string| is a comma-delimited list of category wildcards.
    // A category can have an optional '-' prefix to make it an excluded category.
    // All the same rules apply above, so for example, having both included and
    // excluded categories in the same list would not be supported.
    // Example: "test_MyTest*"
    // Example: "test_MyTest*,test_OtherStuff"
    // Example: "-excluded_category1,-excluded_category2"
    event_categories
    //, ::base::trace_event::RECORD_CONTINUOUSLY
    , ::base::trace_event::RECORD_UNTIL_FULL
    };

  /// \todo https://www.chromium.org/developers/how-tos/trace-event-profiling-tool/memory/howto-adding-memory-infra-tracing-to-a-component
  //base::tracing::ProcessMetricsMemoryDumpProvider::RegisterForProcess(
  //    ::base::kNullProcessId);

  /// \todo
  /// use ::base::trace_event::MemoryDumpManager::GetInstance()->RegisterDumpProvider
  // Create trace config with heap profiling filter.
  /*std::string filter_string = ::base::JoinString(
      {"*", TRACE_DISABLED_BY_DEFAULT("net"), TRACE_DISABLED_BY_DEFAULT("cc"),
       ::base::trace_event::MemoryDumpManager::kTraceCategory},
      ",");
  ::base::trace_event::TraceConfigCategoryFilter category_filter;
  category_filter.InitializeFromString(filter_string);
  ::base::trace_event::TraceConfig::EventFilterConfig heap_profiler_filter_config(
      ::base::HeapProfilerEventFilter::kName);
  heap_profiler_filter_config.SetCategoryFilter(category_filter);
  ::base::trace_event::TraceConfig::EventFilters enabled_event_filters_;
  enabled_event_filters_.push_back(heap_profiler_filter_config);
  trace_config.SetEventFilters(enabled_event_filters_);*/
  //base::trace_event::TraceLog::GetInstance()->SetEnabled(
  //  ::base::trace_event::TraceConfig(
  //    ::base::trace_event::MemoryDumpManager::kTraceCategory, ""),
  //  ::base::trace_event::TraceLog::RECORDING_MODE);

  ::base::trace_event::TraceLog::GetInstance()->SetEnabled(
    trace_config
    , ::base::trace_event::TraceLog::RECORDING_MODE);

  if(!auto_start_tracer) {
    ::base::trace_event::TraceLog::GetInstance()->SetDisabled();
    VLOG(1)
      << "Tracing disabled."
      << " You can control tracing by cmd flags";
  } else {
    VLOG(1)
      << "Tracing started with config: "
      << trace_config.ToString();
    VLOG(1)
      << "Tracing file may require a lot of space, so"
      << " consider enabling tracing on-demand";
  }

  ::base::trace_event::TraceLog::GetInstance()
    ->set_process_name("Main Process");

  {
    using ::base::trace_event::AllocationContextTracker;
    using CaptureMode
      = ::base::trace_event::AllocationContextTracker::CaptureMode;

    DCHECK(AllocationContextTracker
      ::GetInstanceForCurrentThread());
    AllocationContextTracker::SetCaptureMode(
      CaptureMode::DISABLED);
  }

  ::base::SamplingHeapProfiler::Init();

  auto* h_profiler = ::base::SamplingHeapProfiler::Get();
  DCHECK(h_profiler);
  const uint32_t profile_id = h_profiler->Start();

  ::base::trace_event::MemoryDumpManager* mdump_instance
    = ::base::trace_event::MemoryDumpManager::GetInstance();
  DCHECK(mdump_instance);
  mdump_instance->Initialize(
   ::base::BindRepeating(
     [
     ](
       ::base::trace_event::MemoryDumpType dump_type
       , ::base::trace_event::MemoryDumpLevelOfDetail level_of_detail
     ){
       NOTIMPLEMENTED();
     }
   )
   // Only coordinator process triggers periodic memory dumps.
   , false // is_coordinator.
  );

  mdump_instance->SetupForTracing(
    ::base::trace_event::TraceConfig::MemoryDumpConfig());

  /// \todo
  //void* volatile p = ::base::allocator::UncheckedAlloc(400);
  //free(p);
  //std::vector<::base::SamplingHeapProfiler::Sample> h_samples =
  //    h_profiler->GetSamples(
  //      //profile_id
  //      0 // To retrieve all set to 0.
  //      );
  //h_profiler->Stop();
  ////DCHECK(h_samples.size() > 0); /// \todo
  //std::map<size_t, size_t> h_buckets;
  //std::map<size_t, size_t> h_sums;
  //for (auto& sample : h_samples) {
  //  h_buckets[sample.size] += sample.total;
  //}
  //for (auto& it : h_buckets) {
  //  //if (it.first != 400 && it.first != 700 && it.first != 20480)
  //  //  continue;
  //  h_sums[it.first] += it.second;
  //  VLOG(1)
  //      << "h_sums: " << it.second;
  //}
  //static uint64_t dump_guid = 0;
  //base::trace_event::MemoryDumpType dump_type
  //  = ::base::trace_event::MemoryDumpType::EXPLICITLY_TRIGGERED;
  //base::trace_event::MemoryDumpLevelOfDetail level_of_detail
  //  = ::base::trace_event::MemoryDumpLevelOfDetail::DETAILED;
  //base::trace_event::MemoryDumpRequestArgs request_args{
  //  dump_guid, dump_type, level_of_detail};
  //mdump_instance->CreateProcessDump(request_args
  //  , ::base::BindRepeating(
  //    [](
  //      bool success
  //      , uint64_t dump_guid
  //      , std::unique_ptr<::base::trace_event::ProcessMemoryDump> pmd
  //    ){
  //      using ::base::trace_event::TracedValue;
  //
  //      VLOG(1)
  //        << "MemoryDumpRequest done"
  //        << (success ? " fine" : " with errors");
  //      DCHECK(success || !pmd);
  //      if(!success || !pmd) {
  //        DCHECK(false); /// \todo
  //        return;
  //      }
  //
  //      //const auto& allocator_dumps = pmd->allocator_dumps();
  //      //for (const auto& expected_dump_name : allocator_dumps.) {
  //      //  VLOG(1)
  //      //    << "expected_dump_name: "
  //      //    << expected_dump_name;
  //      //}
  //
  //      std::unique_ptr<TracedValue> traced_value
  //        = std::make_unique<TracedValue>();
  //
  //      pmd->SerializeAllocatorDumpsInto(traced_value.get());
  //      {
  //        bool enabled;
  //        TRACE_EVENT_CATEGORY_GROUP_ENABLED(
  //            ::base::trace_event::MemoryDumpManager::kTraceCategory, &enabled);
  //        //DCHECK(enabled);
  //      }
  //      traced_value->SetString(
  //          "level_of_detail",
  //          ::base::trace_event::MemoryDumpLevelOfDetailToString(
  //            /// \todo
  //            ::base::trace_event::MemoryDumpLevelOfDetail::DETAILED
  //            ));
  //
  //      ::base::trace_event::TraceArguments trace_args(
  //        "dumps"
  //        , std::move(traced_value));
  //
  //      // don't forget to enable tracing category
  //      // and call `TeardownForTracing`
  //      TRACE_EVENT_API_ADD_TRACE_EVENT(
  //          TRACE_EVENT_PHASE_MEMORY_DUMP,
  //          ::base::trace_event::TraceLog::GetCategoryGroupEnabled(
  //              ::base::trace_event::MemoryDumpManager::kTraceCategory)
  //          , ::base::trace_event::MemoryDumpTypeToString(
  //             /// \todo
  //             ::base::trace_event::MemoryDumpType::EXPLICITLY_TRIGGERED
  //          )
  //          , ::trace_event_internal::kGlobalScope
  //          , dump_guid
  //          //, 0//pid ///\todo
  //          , &trace_args
  //          , TRACE_EVENT_FLAG_HAS_ID);
  //      TRACE_EVENT_NESTABLE_ASYNC_BEGIN2(
  //          ::base::trace_event::MemoryDumpManager::kTraceCategory
  //          , "GlobalMemoryDump"
  //          , TRACE_ID_LOCAL(dump_guid)
  //          , "dump_type"
  //          , ::base::trace_event::MemoryDumpTypeToString(
  //              /// \todo
  //              ::base::trace_event::MemoryDumpType::EXPLICITLY_TRIGGERED
  //            )
  //          , "level_of_detail",
  //          ::base::trace_event::MemoryDumpLevelOfDetailToString(
  //              /// \todo
  //              ::base::trace_event::MemoryDumpLevelOfDetail::DETAILED
  //            )
  //          );
  //      TRACE_EVENT_NESTABLE_ASYNC_END2(
  //          ::base::trace_event::MemoryDumpManager::kTraceCategory
  //          , "GlobalMemoryDump"
  //          , TRACE_ID_LOCAL(dump_guid)
  //          , "dump_type"
  //          , ::base::trace_event::MemoryDumpTypeToString(
  //              /// \todo
  //              ::base::trace_event::MemoryDumpType::EXPLICITLY_TRIGGERED
  //            )
  //          , "level_of_detail",
  //          ::base::trace_event::MemoryDumpLevelOfDetailToString(
  //              /// \todo
  //              ::base::trace_event::MemoryDumpLevelOfDetail::DETAILED
  //            )
  //          );
  //      LOG(INFO)
  //        << "MemoryDumpRequest finished";
  //    }
  //));
}

void writeTraceReport(
  const ::base::FilePath &output_filepath)
{
  DCHECK(base::trace_event::TraceLog::GetInstance());

  /// \note call that function only if tracing enabled
  {
    const bool need_write_tracing_report
      = ::base::trace_event::TraceLog::GetInstance()->IsEnabled();
    DCHECK(need_write_tracing_report);
    if(!need_write_tracing_report) {
      LOG(ERROR)
        << "unable to write tracing report "
           "while tracing is disabled";
      return;
    }
  }

  // disable writing of new tracing data
  // before flush of trace report
  ::base::trace_event::TraceLog::GetInstance()->SetDisabled();

  ::base::trace_event::TraceResultBuffer trace_buffer;

  // Start JSON output.
  // This resets all internal state, so you can reuse
  // the TraceResultBuffer by calling Start.
  trace_buffer.Start();

  ::base::File output_file(
    output_filepath
    /// \note create file if not exists
    , ::base::File::FLAG_CREATE_ALWAYS
      | ::base::File::FLAG_WRITE);

  output_file.WriteAtCurrentPos(
    kTraceJsonStart, strlen(kTraceJsonStart));

  // output to file
  trace_buffer.SetOutputCallback(
    ::base::Bind(
      []
        (base::File& _output_file
        , const std::string& data)
      {
        _output_file.WriteAtCurrentPos(
          data.c_str()
          , static_cast<int>(data.length()));
      }
      , std::ref(output_file)
      )
    );

  ::base::trace_event::MemoryDumpManager::GetInstance()
    ->TeardownForTracing();

  ::base::RunLoop trace_run_loop{};

  ::base::trace_event::TraceLog::GetInstance()->Flush(
    ::base::BindRepeating(
      &onTraceDataCollected
      , std::ref(output_file)
      , trace_run_loop.QuitClosure(),
      ::base::Unretained(&trace_buffer)));

  trace_run_loop.Run();

  // When all fragments have been added,
  // call Finish to complete the JSON
  // formatted output.
  trace_buffer.Finish();

  CHECK(output_file.IsValid());

  output_file.WriteAtCurrentPos(
    kTraceJsonEnd, strlen(kTraceJsonEnd));

  output_file.Close();

  LOG(INFO)
    << "tracing report written into file: "
    << output_filepath
    << ". You can open resulting file in chrome://tracing";
}

}  // namespace basic
