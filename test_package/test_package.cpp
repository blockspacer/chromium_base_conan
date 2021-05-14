#include <base/logging.h>
#include <base/i18n/icu_util.h>
#include <base/command_line.h>
#include <base/threading/platform_thread.h>
#include <base/base_switches.h>
#include <base/feature_list.h>
#include <base/at_exit.h>
#include <base/bind.h>
#include <build/build_config.h>
#include "base/at_exit.h"
#include "base/command_line.h"
#include "base/debug/stack_trace.h"
#include "base/message_loop/message_pump_type.h"
#include "base/task/single_thread_task_executor.h"
#include "base/task/thread_pool/thread_pool_instance.h"
#include "base/trace_event/trace_event.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/i18n/icu_util.h"
#include "base/logging.h"
#include "base/path_service.h"
#include "base/bind.h"
#include "base/run_loop.h"
#include "base/check.h"
#include "base/base_switches.h"
#include "base/threading/thread_task_runner_handle.h"
#include "base/process/memory.h"
#include "base/process/launch.h"

#include <locale.h>

#include <memory>
#include <string>
#include <iostream>

class AppDemo {
 public:
  AppDemo();
  ~AppDemo();

  void Initialize(){}
  void Destroy();
  void Run();

 private:
  void OnCloseRequest();
  void RenderFrame();

private:
  base::RunLoop* run_loop_ = nullptr;
  bool is_running_ = false;
};

AppDemo::AppDemo() = default;

AppDemo::~AppDemo() = default;

void AppDemo::OnCloseRequest() {
  is_running_ = false;
  if (run_loop_)
    run_loop_->QuitWhenIdle();
}

void AppDemo::RenderFrame() {
  if (!is_running_)
    return;

  base::ThreadTaskRunnerHandle::Get()->PostTask(
      FROM_HERE,
      base::BindOnce(&AppDemo::RenderFrame, base::Unretained(this)));

  /// \note stops main loop
  base::ThreadTaskRunnerHandle::Get()->PostTask(
      FROM_HERE,
      base::BindOnce(&AppDemo::OnCloseRequest, base::Unretained(this)));
}

void AppDemo::Destroy() {}

void AppDemo::Run() {
  DCHECK(!is_running_);
  DCHECK(!run_loop_);
  base::RunLoop run_loop;
  is_running_ = true;
  run_loop_ = &run_loop;
  RenderFrame();
  run_loop.Run();
  run_loop_ = nullptr;
}

namespace switches {

const char kLogFile[] = "log-file";

const char kTraceToConsole[] = "trace-to-console";

const int kTraceEventAppSortIndex = -1;

} // namespace switches

namespace tracing {

namespace {
// These categories will cause deadlock when ECHO_TO_CONSOLE. crbug.com/325575.
const char kEchoToConsoleCategoryFilter[] = "-ipc,-toplevel";
}  // namespace

base::trace_event::TraceConfig GetConfigForTraceToConsole() {
  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  DCHECK(command_line.HasSwitch(switches::kTraceToConsole));
  std::string filter = command_line.GetSwitchValueASCII(
      switches::kTraceToConsole);
  if (filter.empty()) {
    filter = kEchoToConsoleCategoryFilter;
  } else {
    filter.append(",");
    filter.append(kEchoToConsoleCategoryFilter);
  }
  return base::trace_event::TraceConfig(
      filter, base::trace_event::ECHO_TO_CONSOLE);
}

}  // namespace tracing

int main(int argc, const char* argv[]) {
  setlocale(LC_ALL, "en_US.UTF-8");

  std::cout << "HI from " << FROM_HERE.function_name();

  base::EnableTerminationOnHeapCorruption();
  // Manages the destruction of singletons.
  base::AtExitManager exit_manager;

  CHECK(base::CommandLine::Init(argc, argv));
  const base::CommandLine& command_line = *base::CommandLine::ForCurrentProcess();

#if defined(OS_WIN) && !defined(NDEBUG)
  base::RouteStdioToConsole(false);
#endif

  base::FilePath log_filename =
      command_line.GetSwitchValuePath(switches::kLogFile);
  if (log_filename.empty()) {
    base::PathService::Get(base::DIR_EXE, &log_filename);
    log_filename = log_filename.AppendASCII("app_logfile.log");
  }

// Only use OutputDebugString in debug mode.
#ifdef NDEBUG
  logging::LoggingDestination destination = logging::LOG_TO_FILE;
#else
  logging::LoggingDestination destination =
      logging::LOG_TO_ALL;
#endif

  logging::LoggingSettings settings;
  settings.logging_dest = destination;

  settings.log_file_path = log_filename.value().c_str();
  settings.delete_old = logging::DELETE_OLD_LOG_FILE;
  logging::InitLogging(settings);

  logging::SetLogItems(true /* Process ID */, true /* Thread ID */,
                       true /* Timestamp */, false /* Tick count */);

  /// \todo provide ICU data file
  /// base::i18n::InitializeICU();

#ifndef NDEBUG
  CHECK(base::debug::EnableInProcessStackDumping());
#endif

  // Initialize tracing.
  base::trace_event::TraceLog::GetInstance()->set_process_name("Browser");
  base::trace_event::TraceLog::GetInstance()->SetProcessSortIndex(
      switches::kTraceEventAppSortIndex);
  if (command_line.HasSwitch(switches::kTraceToConsole)) {
    base::trace_event::TraceConfig trace_config =
        tracing::GetConfigForTraceToConsole();
    base::trace_event::TraceLog::GetInstance()->SetEnabled(
        trace_config, base::trace_event::TraceLog::RECORDING_MODE);
  }

  // Build UI thread task executor. This is used by platform
  // implementations for event polling & running background tasks.
  base::SingleThreadTaskExecutor main_task_executor(base::MessagePumpType::UI);

  // Initialize ThreadPool.
  constexpr int kMaxForegroundThreads = 6;
  base::ThreadPoolInstance::InitParams thread_pool_init_params(
      kMaxForegroundThreads);

  base::ThreadPoolInstance::Create("AppThreadPool");
  base::ThreadPoolInstance::Get()->Start(thread_pool_init_params);

  AppDemo app_demo;
  app_demo.Initialize();
  app_demo.Run();
  app_demo.Destroy();

  base::ThreadPoolInstance::Get()->Shutdown();

  return 0;
}
