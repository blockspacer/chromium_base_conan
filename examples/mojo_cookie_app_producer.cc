#include "fortune_cookie_impl.h"

#include <base/logging.h>
#include <base/i18n/icu_util.h>
#include <base/command_line.h>
#include <base/threading/platform_thread.h>
#include <base/base_switches.h>
#include <base/feature_list.h>
#include <base/at_exit.h>
#include <base/rand_util.h>
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

using namespace examples;

namespace switches {

const char kLogFile[] = "log-file";

const char kTraceToConsole[] = "trace-to-console";

const int kTraceEventAppSortIndex = -1;

} // namespace switches

namespace {

constexpr char kMojoRemoteToken[] = "mojo-remote-token";
constexpr char kMojoReceiverToken[] = "mojo-receiver-token";

}  // namespace

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

/// \todo find better way for bidirectional communication
// A message pipe is a bidirectional messaging channel
// which can carry arbitrary unstructured binary messages
// with zero or more MojoHandle attachments
// to be transferred from one end of a pipe to the other.
struct BidirectionalPipes {
  mojo::ScopedMessagePipeHandle pipe_remote;
  mojo::ScopedMessagePipeHandle pipe_receiver;
};

class AppDemo {
 public:
  AppDemo();
  ~AppDemo();

  void Initialize();
  void Destroy();
  void Run();

 private:
  void OnCloseRequest();
  void QuitWhenIdle();
  void RenderFrame();
  BidirectionalPipes LaunchAndConnect();

private:
  base::RunLoop* run_loop_ = nullptr;
  bool is_running_ = false;
  base::Time next_render_time_ = base::Time::Now();
  std::unique_ptr<
    examples::FortuneCookieRemote> cookie_remote_;
  std::unique_ptr<
    examples::FortuneCookieReceiver> cookie_receiver_;
  base::Process child_process_;
};

AppDemo::AppDemo() = default;

AppDemo::~AppDemo() {
  Destroy();
}

void AppDemo::OnCloseRequest() {
  LOG(INFO)
    << "OnCloseRequest";

  if (cookie_receiver_) {
    cookie_receiver_->SetWish("Producer already closed!");
  }

  if (cookie_remote_) {
    cookie_remote_->SendCrack();
    cookie_remote_->SendCloseStream();
  }

  base::ThreadTaskRunnerHandle::Get()->PostDelayedTask(
      FROM_HERE,
      base::BindOnce(&AppDemo::QuitWhenIdle, base::Unretained(this)),
      base::TimeDelta::FromSeconds(5));
}

void AppDemo::QuitWhenIdle() {
  Destroy();

  LOG(INFO)
    << "QuitWhenIdle";

  is_running_ = false;
  if (run_loop_)
    run_loop_->QuitWhenIdle();
}

void AppDemo::RenderFrame() {
  if (!is_running_)
    return;

  LOG(INFO)
    << "RenderFrame";

  if (base::Time::Now() >= next_render_time_) {
    static const base::TimeDelta tickrate{
      base::TimeDelta::FromMilliseconds(500)};
    next_render_time_ = base::Time::Now() + tickrate;
    base::ThreadTaskRunnerHandle::Get()->PostDelayedTask(
        FROM_HERE,
        base::BindOnce(&AppDemo::RenderFrame, base::Unretained(this)),
        tickrate);
  }

  /// \note stops main loop
  // base::ThreadTaskRunnerHandle::Get()->PostTask(
  //     FROM_HERE,
  //     base::BindOnce(&AppDemo::OnCloseRequest, base::Unretained(this)));
}

void AppDemo::Initialize() {
  BidirectionalPipes pipes = LaunchAndConnect();

  // Wraps a message pipe endpoint that receives incoming messages.
  cookie_receiver_ = std::make_unique<
    examples::FortuneCookieReceiver>(
    mojo::PendingReceiver<
      mojom::FortuneCookie>(std::move(pipes.pipe_remote)));
  cookie_receiver_->SetId("Producer");
  cookie_receiver_->SetWish("Producer world!");
  cookie_receiver_->SetCallbackOnError(
    base::BindRepeating(&AppDemo::OnCloseRequest, base::Unretained(this)));

  // if a client on version above X
  // interface with [MinVersion=X]
  // sends an request to an implementation of version kMinVersion,
  // the client will be disconnected.
  static uint64_t kMinVersion = 0;

  // Wraps a message pipe endpoint for making remote calls.
  cookie_remote_ = std::make_unique<
    examples::FortuneCookieRemote>(
      PendingRemote<mojom::FortuneCookie>(
        std::move(pipes.pipe_receiver), kMinVersion));
  cookie_remote_->SetId("Producer");
  cookie_remote_->SetCallbackOnError(
    base::BindRepeating(&AppDemo::OnCloseRequest, base::Unretained(this)));

  base::Promise<bool> task1
    = cookie_remote_->SendSetName("Producer");
  task1.ThenHere(FROM_HERE,
    base::BindOnce([](bool data){
      LOG(INFO)
        << "SendSetName finished with response: "
        << std::to_string(data);
    })
  );
  cookie_remote_->SendCrack();
  cookie_remote_->SendFillRects();

  // quit by request or automatically after some time
  {
    base::ThreadTaskRunnerHandle::Get()->PostDelayedTask(
        FROM_HERE,
        base::BindOnce(&AppDemo::OnCloseRequest, base::Unretained(this)),
        base::TimeDelta::FromSeconds(7));
  }
}

BidirectionalPipes AppDemo::LaunchAndConnect() {
  // Under the hood, this is essentially always an OS pipe (domain socket pair,
  // Windows named pipe, Fuchsia channel, etc).
  mojo::PlatformChannel channel;

  LOG(INFO)
    << "(LaunchAndConnect) local: "
    << channel.local_endpoint().platform_handle().GetFD().get()
    << " remote: "
    << channel.remote_endpoint().platform_handle().GetFD().get();

  // Invitations provide the means to bootstrap one or more
  // primordial cross-process message pipes between two processes.
  mojo::OutgoingInvitation invitation;

  std::string token_remote = base::NumberToString(base::RandUint64());
  std::string token_receiver = base::NumberToString(base::RandUint64());
  CHECK_NE(token_remote, token_receiver);

  // Attach a message pipe to be extracted by the receiver.
  // The other end of the
  // pipe is returned for us to use locally.
  mojo::ScopedMessagePipeHandle pipe_remote =
      invitation.AttachMessagePipe(token_remote);

  mojo::ScopedMessagePipeHandle pipe_receiver =
      invitation.AttachMessagePipe(token_receiver);

  static const char kTestTargetName[]
    = "mojo_cookie_app_consumer";

  base::LaunchOptions options;
  base::CommandLine command_line
    = *base::CommandLine::ForCurrentProcess();

  base::FilePath target_path;
  CHECK(base::PathService::Get(base::DIR_EXE, &target_path));
#if defined(OS_WIN)
    target_path =
      target_path.AppendASCII(kTestTargetName)
        .AddExtensionASCII("exe");
#else
    target_path
      = target_path.Append(FILE_PATH_LITERAL(kTestTargetName));
#endif

  command_line.SetProgram(
    base::MakeAbsoluteFilePath(target_path));

  command_line.AppendSwitchASCII(kMojoRemoteToken, token_remote);
  command_line.AppendSwitchASCII(kMojoReceiverToken, token_receiver);
  channel.PrepareToPassRemoteEndpoint(&options, &command_line);
  child_process_
    = base::LaunchProcess(command_line, options);
  channel.RemoteProcessLaunchAttempted();

  if (child_process_.IsValid()) {
    mojo::OutgoingInvitation::Send(
      std::move(invitation),
      child_process_.Handle(),
      channel.TakeLocalEndpoint(),
      base::BindRepeating(
        [](const std::string& error)
        {
          LOG(ERROR)
            << "OutgoingInvitation: "
            << error;
        })
    );
  } else {
    LOG(ERROR)
      << "Invalid child process";
  }

  return BidirectionalPipes{
    std::move(pipe_remote),
    std::move(pipe_receiver)};
}

void AppDemo::Destroy() {
  if (cookie_remote_) {
    cookie_remote_.reset();
  }
  if (cookie_receiver_) {
    cookie_receiver_.reset();
  }

  if (child_process_.IsValid()) {
    int exit_code;
    child_process_.WaitForExitWithTimeout(
      base::TimeDelta::FromSeconds(5), &exit_code);
    LOG(INFO)
      << "child_process exit_code:"
      << exit_code;
  }
}

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

// Initializes and owns mojo.
// In order to use any of the more interesting
// high-level support libraries like the System APIs or Bindings APIs,
// a process must first initialize Mojo Core.
// This is a one-time initialization which remains active
// for the remainder of the process's lifetime.
// There are two ways to initialize Mojo Core:
// via the Embedder API, or through a dynamically linked library.
class InitMojo {
 public:
  InitMojo() : thread_("Mojo thread") {
    mojo::core::Configuration mojo_config;
    /// \note Instead of calling `mojo::core::Init()`
    /// as embedders do, an application using
    /// dynamic Mojo Core instead calls `MojoInitialize()`
    /// from the C System API. This
    /// call will attempt to locate (see above)
    /// and load the Mojo Core library to
    /// support subsequent Mojo API usage within the process.
    mojo::core::Init(mojo_config);
    thread_.StartWithOptions(
      base::Thread::Options(base::MessagePumpType::IO, 0));
    thread_.WaitUntilThreadStarted();
    // As long as this object is alive,
    // all API surface relevant to IPC
    // connections is usable and message pipes
    // which span a process boundary will
    // continue to function.
    ipc_support_ = std::make_unique<mojo::core::ScopedIPCSupport>(
      thread_.task_runner(),
      mojo::core::ScopedIPCSupport::ShutdownPolicy::CLEAN);
  }

  ~InitMojo() {
    thread_.Stop();
  }

 private:
  base::Thread thread_;
  std::unique_ptr<mojo::core::ScopedIPCSupport> ipc_support_;

  DISALLOW_COPY_AND_ASSIGN(InitMojo);
};


// Initializes and owns the components from base necessary to run the app.
class InitBase {
 public:
  InitBase(int argc, const char** argv)
    // Build UI thread task executor. This is used by platform
    // implementations for event polling & running background tasks.
    : main_task_executor_(base::MessagePumpType::UI)
  {
    setlocale(LC_ALL, "en_US.UTF-8");

    base::EnableTerminationOnHeapCorruption();

    CHECK(base::CommandLine::Init(argc, argv));
    const base::CommandLine& command_line
      = *base::CommandLine::ForCurrentProcess();

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

    logging::SetLogPrefix("producer");

    // Initialize tracing.
    base::trace_event::TraceLog::GetInstance()
      ->set_process_name("producer");
    base::trace_event::TraceLog::GetInstance()
      ->SetProcessSortIndex(
        switches::kTraceEventAppSortIndex);
    if (command_line.HasSwitch(switches::kTraceToConsole)) {
      base::trace_event::TraceConfig trace_config
        = tracing::GetConfigForTraceToConsole();
      base::trace_event::TraceLog::GetInstance()->SetEnabled(
        trace_config, base::trace_event::TraceLog::RECORDING_MODE);
    }

    base::FeatureList::InitializeInstance(
      command_line.GetSwitchValueASCII(switches::kEnableFeatures),
      command_line.GetSwitchValueASCII(switches::kDisableFeatures));

    // Initialize ThreadPool.
    constexpr int kMaxForegroundThreads = 6;
    base::ThreadPoolInstance::InitParams thread_pool_init_params(
        kMaxForegroundThreads);

    base::ThreadPoolInstance::Create("AppThreadPool");
    base::ThreadPoolInstance::Get()->Start(thread_pool_init_params);

    LOG(INFO)
      << "Command Line: "
      << command_line.GetCommandLineString();
  }

  ~InitBase() {
    base::ThreadPoolInstance::Get()->Shutdown();
  }

 private:
  // The exit manager is in charge
  // of calling the dtors of singleton objects.
  base::AtExitManager exit_manager_;
  base::SingleThreadTaskExecutor main_task_executor_;

  DISALLOW_COPY_AND_ASSIGN(InitBase);
};

int main(int argc, const char* argv[]) {
  InitBase base(argc, &argv[0]);

  LOG(INFO)
    << "Starting mojo... ";

  InitMojo mojo;

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

  return 0;
}
