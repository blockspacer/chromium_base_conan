#include "fortune_cookie_impl.h"

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
#include "base/bind.h"
#include "base/callback_helpers.h"
#include "base/check_op.h"
#include "base/macros.h"
#include "base/memory/ptr_util.h"
#include "base/memory/weak_ptr.h"
#include "base/notreached.h"
#include "base/run_loop.h"
#include "base/synchronization/waitable_event.h"
#include "base/test/bind.h"
#include "base/threading/thread.h"

#include "mojo/core/embedder/embedder.h"
#include "mojo/core/embedder/scoped_ipc_support.h"
#include "mojo/public/c/system/buffer.h"
#include "mojo/public/c/system/data_pipe.h"
#include "mojo/public/c/system/message_pipe.h"
#include "mojo/public/cpp/platform/platform_channel.h"
#include "mojo/public/cpp/system/buffer.h"
#include "mojo/public/cpp/system/data_pipe.h"
#include "mojo/public/cpp/system/invitation.h"
#include "mojo/public/cpp/system/message_pipe.h"
#include "mojo/public/cpp/system/simple_watcher.h"
#include "mojo/public/cpp/system/wait.h"

#include "mojo/public/cpp/bindings/associated_receiver.h"
#include "mojo/public/cpp/bindings/associated_remote.h"
#include "mojo/public/cpp/bindings/pending_associated_receiver.h"
#include "mojo/public/cpp/bindings/pending_associated_remote.h"
#include "mojo/public/cpp/bindings/associated_interface_ptr_info.h"
#include "mojo/public/cpp/bindings/scoped_interface_endpoint_handle.h"

#include "mojo/public/cpp/bindings/interface_ptr.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "mojo/public/cpp/bindings/self_owned_receiver.h"
#include "mojo/public/cpp/bindings/tests/bindings_test_base.h"
#include "mojo/public/cpp/bindings/tests/receiver_unittest.test-mojom.h"
#include "mojo/public/cpp/system/functions.h"
#include "mojo/public/interfaces/bindings/tests/ping_service.mojom.h"
#include "mojo/public/interfaces/bindings/tests/sample_interfaces.mojom.h"
#include "mojo/public/interfaces/bindings/tests/sample_service.mojom.h"

#include <cstdint>
#include <clocale>
#include <utility>
#include <memory>
#include <string>
#include <iostream>

//template <class T>
//using AssociatedRemote = mojo::AssociatedRemote<T>;
//template <class T>
//using PendingAssociatedRemote = mojo::AssociatedInterfacePtrInfo<T>;
//template <class T>
//using AssociatedReceiver = mojo::AssociatedReceiver<T>;
//template <class T>
//using PendingAssociatedReceiver = mojo::AssociatedInterfaceRequest<T>;
//
//template <class T>
//using Remote = mojo::InterfacePtr<T>;
//template <class T>
//using PendingRemote = mojo::InterfacePtrInfo<T>;
//template <class T>
//using Receiver = mojo::Receiver<T>;
//template <class T>
//using PendingReceiver = mojo::InterfaceRequest<T>;

using namespace examples;

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

using namespace mojo;
using namespace sample;
using namespace base;

class ServiceImpl : public sample::Service {
 public:
  ServiceImpl() = default;
  explicit ServiceImpl(bool* was_deleted)
      : destruction_callback_(base::BindLambdaForTesting(
            [was_deleted] { *was_deleted = true; })) {}
  explicit ServiceImpl(base::OnceClosure destruction_callback)
      : destruction_callback_(std::move(destruction_callback)) {}

  ~ServiceImpl() override {
    if (destruction_callback_)
      std::move(destruction_callback_).Run();
  }

 private:
  // sample::Service implementation
  void Frobinate(sample::FooPtr foo,
                 BazOptions options,
                 PendingRemote<sample::Port> port,
                 FrobinateCallback callback) override {
    std::move(callback).Run(1);
  }
  void GetPort(PendingReceiver<sample::Port> port) override {}

  base::OnceClosure destruction_callback_;

  DISALLOW_COPY_AND_ASSIGN(ServiceImpl);
};

class PingServiceImpl : public mojo::test::PingService {
 public:
  PingServiceImpl() = default;
  ~PingServiceImpl() override = default;

  // mojo::test::PingService:
  void Ping(PingCallback callback) override {
    if (ping_handler_)
      ping_handler_.Run();
    std::move(callback).Run();
  }

  void set_ping_handler(base::RepeatingClosure handler) {
    ping_handler_ = std::move(handler);
  }

 private:
  base::RepeatingClosure ping_handler_;

  DISALLOW_COPY_AND_ASSIGN(PingServiceImpl);
};

class CallbackFilter : public MessageFilter {
 public:
  explicit CallbackFilter(const base::RepeatingClosure& will_dispatch_callback,
                          const base::RepeatingClosure& did_dispatch_callback)
      : will_dispatch_callback_(will_dispatch_callback),
        did_dispatch_callback_(did_dispatch_callback) {}
  ~CallbackFilter() override {}

  static std::unique_ptr<CallbackFilter> Wrap(
      const base::RepeatingClosure& will_dispatch_callback,
      const base::RepeatingClosure& did_dispatch_callback) {
    return std::make_unique<CallbackFilter>(will_dispatch_callback,
                                            did_dispatch_callback);
  }

  // MessageFilter:
  bool WillDispatch(Message* message) override {
    will_dispatch_callback_.Run();
    return true;
  }

  void DidDispatchOrReject(Message* message, bool accepted) override {
    did_dispatch_callback_.Run();
  }

 private:
  const base::RepeatingClosure will_dispatch_callback_;
  const base::RepeatingClosure did_dispatch_callback_;
};

// interface PingService {
//   [Sync]
//   Ping() => ();
// };
class PingImpl : public mojo::test::PingService {
 public:
  explicit PingImpl(PendingReceiver<mojo::test::PingService> receiver)
      : receiver_(this, std::move(receiver)) {}
  ~PingImpl() override = default;

  bool pinged() const { return pinged_; }

  // mojo::test::PingService:
  void Ping(PingCallback callback) override {
    pinged_ = true;
    std::move(callback).Run();
  }

 private:
  bool pinged_ = false;
  Receiver<mojo::test::PingService> receiver_;

  DISALLOW_COPY_AND_ASSIGN(PingImpl);
};

// interface EchoService {
//   Echo(string test_data) => (string echo_data);
// };
class EchoImpl : public mojo::test::EchoService {
 public:
  explicit EchoImpl(PendingReceiver<mojo::test::EchoService> receiver)
      : receiver_(this, std::move(receiver)) {}
  ~EchoImpl() override = default;

  // mojo::test::EchoService:
  void Echo(const std::string& message, EchoCallback callback) override {
    std::move(callback).Run(message);
  }

 private:
  Receiver<mojo::test::EchoService> receiver_;

  DISALLOW_COPY_AND_ASSIGN(EchoImpl);
};

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

int main(int argc, const char* argv[]) {
  setlocale(LC_ALL, "en_US.UTF-8");

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

  LOG(INFO)
    << "Starting mojo... ";

  mojo::core::Configuration mojo_config;
  mojo::core::Init(mojo_config);

  base::Thread ipc_thread("AppIpcThread");
  ipc_thread.StartWithOptions(
      base::Thread::Options(base::MessagePumpType::IO, 0));
  ipc_thread.WaitUntilThreadStarted();

  // As long as this object is alive,
  // all API surface relevant to IPC
  // connections is usable and message pipes
  // which span a process boundary will
  // continue to function.
  mojo::core::ScopedIPCSupport ipc_support(
    ipc_thread.task_runner(),
    mojo::core::ScopedIPCSupport::ShutdownPolicy::CLEAN);

  AppDemo app_demo;

  LOG(INFO)
    << "app_demo.Initialize... ";
  app_demo.Initialize();

  LOG(INFO)
    << "app_demo.Run... ";
  app_demo.Run();

  LOG(INFO)
    << "app_demo.Destroy... ";
  app_demo.Destroy();

  base::ThreadPoolInstance::Get()->Shutdown();

  ipc_thread.Stop();

  return 0;
}
