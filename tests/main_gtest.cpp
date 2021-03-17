#include <base/logging.h>
#include <base/i18n/icu_util.h>
#include <base/command_line.h>
#include <base/threading/platform_thread.h>
#include <base/base_switches.h>
#include <base/feature_list.h>
#include <base/at_exit.h>
#include <base/message_loop/message_pump_for_io.h>
#include <base/run_loop.h>
#include <base/files/file_path.h>
#include <base/base_paths.h>
#include "base/notreached.h"
#include "base/stl_util.h"

#include <base/trace_event/trace_event.h>
#include <base/bind.h>
#include <base/test/launcher/unit_test_launcher.h>
#include <base/test/test_suite.h>
#include <base/path_service.h>
#include <build/build_config.h>
#include <locale.h>

#include "testing/gtest/include/gtest/gtest.h"

#if defined(GTEST_PERF_SUITE)
#include "base/test/perf_test_suite.h"
# endif // GTEST_PERF_SUITE

#if defined(GTEST_NO_SUITE)
static inline void initI18n()
{
  base::FilePath exe_path;
  DCHECK(base::PathService::Get(base::DIR_EXE, &exe_path));
  base::FilePath data_path = exe_path.AppendASCII("./resources/icu/optimal/icudt68l.dat");
  bool icu_initialized = base::i18n::InitializeICUWithPath(data_path);
  DCHECK(icu_initialized);
}

static inline void initCommandLine(int argc, char* argv[])
{
  base::PlatformThread::SetName("Main");

  // see https://stackoverflow.com/a/18981514/10904212
  std::locale::global(std::locale::classic());

  // see https://peter.sh/experiments/chromium-command-line-switches/
  base::CommandLine::Init(argc, argv);

  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();

  // initialize |g_vlog_info| in debug mode
#if !defined(NDEBUG)
  // Gives the default maximal active V-logging level; 0 is the default.
  // Normally positive values are used for V-logging levels.
  if(!command_line->HasSwitch(switches::kV)) {
    command_line->AppendSwitchASCII(switches::kV,
      "1");
  }
  // Gives the per-module maximal V-logging levels to override the value
  // given by --v.  E.g. "my_module=2,foo*=3" would change the logging
  // level for all code in source files "my_module.*" and "foo*.*"
  // ("-inl" suffixes are also disregarded for this matching).
  //
  // Any pattern containing a forward or backward slash will be tested
  // against the whole pathname and not just the module.  E.g.,
  // "*/foo/bar/*=2" would change the logging level for all code in
  // source files under a "foo/bar" directory.
  if(!command_line->HasSwitch(switches::kVModule)) {
    command_line->AppendSwitchASCII(switches::kVModule,
      "*main*=0"
      ",*webrtc*=2"
      ",*libjingle*=2");
  }

  // Indicates that crash reporting should be enabled. On platforms where helper
  // processes cannot access to files needed to make this decision, this flag is
  // generated internally.
  if(!command_line->HasSwitch(switches::kEnableCrashReporter)) {
    command_line->AppendSwitchASCII(switches::kEnableCrashReporter,
      "1");
  }

  // Generates full memory crash dump.
  if(!command_line->HasSwitch(switches::kFullMemoryCrashReport)) {
    command_line->AppendSwitchASCII(switches::kFullMemoryCrashReport,
      "1");
  }

#if defined(OS_LINUX)
    // Controls whether or not retired instruction counts are surfaced for threads
    // in trace events on Linux.
    //
    // This flag requires the BPF sandbox to be disabled.  if(!command_line->HasSwitch(switches::kVModule)) {
    if(!command_line->HasSwitch(switches::kEnableThreadInstructionCount)) {
      command_line->AppendSwitchASCII(switches::kEnableThreadInstructionCount,
        "1");
    }
#endif

  DCHECK(command_line->HasSwitch(switches::kV) ||
      command_line->HasSwitch(switches::kVModule));
#endif // NDEBUG

  // Initialize tracing.
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kTraceToConsole)) {
    base::trace_event::TraceConfig trace_config =
        tracing::GetConfigForTraceToConsole();
    base::trace_event::TraceLog::GetInstance()->SetEnabled(
        trace_config, base::trace_event::TraceLog::RECORDING_MODE);
  }

  /// \todo
  // init allocator https://github.com/aranajhonny/chromium/blob/caf5bcb822f79b8997720e589334266551a50a13/content/app/content_main_runner.cc#L512
  // base::EnableTerminationOnHeapCorruption();
  // base::EnableTerminationOnOutOfMemory();
  // mojo::embedder::Init();
  // mojo::ServiceManager::GetInstance();
//#if !defined(OFFICIAL_BUILD)
//  base::debug::EnableInProcessStackDumping();
//#if defined(OS_WIN)
//  base::RouteStdioToConsole(false);
//#endif
//#endif

  base::FeatureList::InitializeInstance(std::string(), std::string());

  /// \todo
  //base::FeatureList::InitializeInstance(
  //    command_line->GetSwitchValueASCII(switches::kEnableFeatures),
  //    command_line->GetSwitchValueASCII(switches::kDisableFeatures));

  // DCHECK(!base::TaskScheduler::GetInstance());
  // // A one-per-process task scheduler is needed for usage of APIs in
  // // base/post_task.h
  // base::TaskScheduler::CreateAndStartWithDefaultParams("MainThreadPool");
  // DCHECK(base::TaskScheduler::GetInstance());
}
#endif // defined(GTEST_NO_SUITE)

int main(int argc, char* argv[]) {
  CHECK(setlocale(LC_ALL, "en_US.UTF-8") != nullptr)
      << "Failed to set locale: " << "en_US.UTF-8";

#if defined(GTEST_NO_SUITE)
  initCommandLine(argc, argv);

  // This object instance is required (for example,
  // LazyInstance, MessageLoop).
  base::AtExitManager at_exit;

  /// \note creates base::MessageLoop::current()
  base::MessageLoopForIO main_thread_message_loop;

  initI18n();

  /*basis::initLogging(
    "" // logFile
  );*/

  // If the LogWorker is initialized then at scope exit the g3::shutDownLogging() will be called.
  // This is important since it protects from LOG calls from static or other entities that will go
  // out of scope at a later time.
  //
  // It can also be called manually:
  at_exit.RegisterTask(base::BindOnce(
    []
    ()
    {
      LOG(INFO) << "shutdown...";
    }
  ));
#endif // defined(GTEST_NO_SUITE)

#if defined(USE_GTEST_TEST)
#if defined(GTEST_NO_SUITE)
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  const int gtest_res = RUN_ALL_TESTS();
  return gtest_res;
#elif defined(GTEST_PERF_SUITE)
  LOG(INFO) << "Running perf test...";
  return base::PerfTestSuite(argc, argv).Run();
#else
  base::TestSuite test_suite(argc, argv);
  return base::LaunchUnitTests(
      argc, argv,
      base::BindOnce(&base::TestSuite::Run, base::Unretained(&test_suite)));
#endif // GTEST_NO_SUITE
#endif // USE_GTEST_TEST

  // start working on other parts of your project here.
  return 0;
}
