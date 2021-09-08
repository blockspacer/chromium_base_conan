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

  std::cout
    << "Starting app... "
    << FROM_HERE.function_name();

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

  std::cout
    << "app_demo.Initialize... ";
  app_demo.Initialize();

  std::cout
    << "app_demo.Run... ";
  app_demo.Run();

  std::cout
    << "app_demo.Destroy... ";
  app_demo.Destroy();

  base::ThreadPoolInstance::Get()->Shutdown();

  ipc_thread.Stop();

  return 0;
}

#if 0
namespace mojo {
namespace test {
namespace receiver_unittest {

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

using ReceiverTest = BindingsTestBase;

TEST_P(ReceiverTest, Reset) {
  bool called = false;
  Remote<sample::Service> remote;

  ServiceImpl impl;
  Receiver<sample::Service> receiver(&impl,
                                     remote.BindNewPipeAndPassReceiver());

  base::RunLoop run_loop;
  remote.set_disconnect_handler(base::BindLambdaForTesting([&] {
    run_loop.Quit();
    called = true;
  }));

  receiver.reset();
  EXPECT_FALSE(called);
  run_loop.Run();
  EXPECT_TRUE(called);
}

// Tests that destroying a mojo::Binding closes the bound message pipe handle.
TEST_P(ReceiverTest, DestroyClosesMessagePipe) {
  bool encountered_error = false;
  ServiceImpl impl;
  Remote<sample::Service> remote;
  auto pending_receiver = remote.BindNewPipeAndPassReceiver();
  base::RunLoop run_loop;
  remote.set_disconnect_handler(base::BindLambdaForTesting([&] {
    run_loop.Quit();
    encountered_error = true;
  }));

  bool called = false;
  base::RunLoop run_loop2;
  {
    Receiver<sample::Service> binding(&impl, std::move(pending_receiver));
    remote->Frobinate(nullptr, sample::Service::BazOptions::REGULAR,
                      NullRemote(), base::BindLambdaForTesting([&](int32_t) {
                        run_loop2.Quit();
                        called = true;
                      }));
    run_loop2.Run();
    EXPECT_TRUE(called);
    EXPECT_FALSE(encountered_error);
  }
  // Now that the Binding is out of scope we should detect an error on the other
  // end of the pipe.
  run_loop.Run();
  EXPECT_TRUE(encountered_error);

  // And calls should fail.
  called = false;
  remote->Frobinate(
      nullptr, sample::Service::BazOptions::REGULAR, NullRemote(),
      base::BindLambdaForTesting([&](int32_t) { called = true; }));
  base::RunLoop().RunUntilIdle();
  EXPECT_FALSE(called);
}

// Tests that the binding's connection error handler gets called when the other
// end is closed.
TEST_P(ReceiverTest, Disconnect) {
  bool called = false;
  {
    ServiceImpl impl;
    Remote<sample::Service> remote;
    Receiver<sample::Service> receiver(&impl,
                                       remote.BindNewPipeAndPassReceiver());
    base::RunLoop run_loop;
    receiver.set_disconnect_handler(base::BindLambdaForTesting([&] {
      called = true;
      run_loop.Quit();
    }));
    remote.reset();
    EXPECT_FALSE(called);
    run_loop.Run();
    EXPECT_TRUE(called);
    // We want to make sure that it isn't called again during destruction.
    called = false;
  }
  EXPECT_FALSE(called);
}

// Tests that calling Close doesn't result in the connection error handler being
// called.
TEST_P(ReceiverTest, ResetDoesntCallDisconnectHandler) {
  ServiceImpl impl;
  Remote<sample::Service> remote;
  Receiver<sample::Service> receiver(&impl,
                                     remote.BindNewPipeAndPassReceiver());
  bool called = false;
  receiver.set_disconnect_handler(
      base::BindLambdaForTesting([&] { called = true; }));
  receiver.reset();
  base::RunLoop().RunUntilIdle();
  EXPECT_FALSE(called);

  // We can also close the other end, and the error handler still won't be
  // called.
  remote.reset();
  base::RunLoop().RunUntilIdle();
  EXPECT_FALSE(called);
}

class ServiceImplWithReceiver : public ServiceImpl {
 public:
  ServiceImplWithReceiver(bool* was_deleted,
                          base::OnceClosure closure,
                          PendingReceiver<sample::Service> receiver)
      : ServiceImpl(was_deleted),
        receiver_(this, std::move(receiver)),
        closure_(std::move(closure)) {
    receiver_.set_disconnect_handler(base::BindOnce(
        &ServiceImplWithReceiver::OnDisconnect, base::Unretained(this)));
  }

 private:
  ~ServiceImplWithReceiver() override { std::move(closure_).Run(); }

  void OnDisconnect() { delete this; }

  Receiver<sample::Service> receiver_;
  base::OnceClosure closure_;

  DISALLOW_COPY_AND_ASSIGN(ServiceImplWithReceiver);
};

// Tests that the receiver may be deleted in its disconnect handler.
TEST_P(ReceiverTest, SelfDeleteOnDisconnect) {
  bool was_deleted = false;
  Remote<sample::Service> remote;
  base::RunLoop run_loop;
  // This will delete itself on disconnect.
  new ServiceImplWithReceiver(&was_deleted, run_loop.QuitClosure(),
                              remote.BindNewPipeAndPassReceiver());
  remote.reset();
  EXPECT_FALSE(was_deleted);
  run_loop.Run();
  EXPECT_TRUE(was_deleted);
}

// Tests that explicitly calling Unbind followed by rebinding works.
TEST_P(ReceiverTest, Unbind) {
  ServiceImpl impl;
  Remote<sample::Service> remote;
  Receiver<sample::Service> receiver(&impl,
                                     remote.BindNewPipeAndPassReceiver());

  bool called = false;
  base::RunLoop run_loop;
  remote->Frobinate(nullptr, sample::Service::BazOptions::REGULAR, NullRemote(),
                    base::BindLambdaForTesting([&](int32_t) {
                      called = true;
                      run_loop.Quit();
                    }));
  run_loop.Run();
  EXPECT_TRUE(called);

  called = false;
  auto pending_receiver = receiver.Unbind();
  EXPECT_FALSE(receiver.is_bound());
  EXPECT_TRUE(pending_receiver);

  // All calls should be withheld when the receiver is not bound...
  remote->Frobinate(nullptr, sample::Service::BazOptions::REGULAR, NullRemote(),
                    base::BindLambdaForTesting([&](int32_t) {
                      called = true;
                      run_loop.Quit();
                    }));
  base::RunLoop().RunUntilIdle();
  EXPECT_FALSE(called);

  called = false;
  receiver.Bind(std::move(pending_receiver));
  EXPECT_TRUE(receiver.is_bound());
  EXPECT_FALSE(pending_receiver);

  // ...and calls should resume again when the receiver is
  // rebound.
  base::RunLoop run_loop2;
  remote->Frobinate(nullptr, sample::Service::BazOptions::REGULAR, NullRemote(),
                    base::BindLambdaForTesting([&](int32_t) {
                      called = true;
                      run_loop2.Quit();
                    }));
  run_loop2.Run();
  EXPECT_TRUE(called);
}

class IntegerAccessorImpl : public sample::IntegerAccessor {
 public:
  IntegerAccessorImpl() = default;
  ~IntegerAccessorImpl() override = default;

 private:
  // sample::IntegerAccessor implementation.
  void GetInteger(GetIntegerCallback callback) override {
    std::move(callback).Run(1, sample::Enum::VALUE);
  }
  void SetInteger(int64_t data, sample::Enum type) override {}

  DISALLOW_COPY_AND_ASSIGN(IntegerAccessorImpl);
};

TEST_P(ReceiverTest, PauseResume) {
  bool called = false;
  base::RunLoop run_loop;
  Remote<sample::Service> remote;
  ServiceImpl impl;
  Receiver<sample::Service> receiver(&impl,
                                     remote.BindNewPipeAndPassReceiver());
  receiver.Pause();
  remote->Frobinate(nullptr, sample::Service::BazOptions::REGULAR, NullRemote(),
                    base::BindLambdaForTesting([&](int32_t) {
                      called = true;
                      run_loop.Quit();
                    }));

  EXPECT_FALSE(called);
  base::RunLoop().RunUntilIdle();
  // Frobinate() should not be called as the receiver is paused.
  EXPECT_FALSE(called);

  // Resume the receiver, which should trigger processing.
  receiver.Resume();
  run_loop.Run();
  EXPECT_TRUE(called);
}

// Verifies the disconnect handler is not run while a receiver is paused.
TEST_P(ReceiverTest, ErrorHandleNotRunWhilePaused) {
  bool called = false;
  base::RunLoop run_loop;
  Remote<sample::Service> remote;
  ServiceImpl impl;
  Receiver<sample::Service> receiver(&impl,
                                     remote.BindNewPipeAndPassReceiver());
  receiver.set_disconnect_handler(base::BindLambdaForTesting([&] {
    called = true;
    run_loop.Quit();
  }));
  receiver.Pause();

  remote.reset();
  base::RunLoop().RunUntilIdle();
  // The disconnect handler should not be called as the receiver is paused.
  EXPECT_FALSE(called);

  // Resume the receiver, which should trigger the disconnect handler.
  receiver.Resume();
  run_loop.Run();
  EXPECT_TRUE(called);
}

class PingServiceImpl : public test::PingService {
 public:
  PingServiceImpl() = default;
  ~PingServiceImpl() override = default;

  // test::PingService:
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

// Verifies that message filters are notified in the order they were added and
// are always notified before a message is dispatched.
TEST_P(ReceiverTest, MessageFilter) {
  Remote<test::PingService> remote;
  PingServiceImpl impl;
  Receiver<test::PingService> receiver(&impl,
                                       remote.BindNewPipeAndPassReceiver());

  int status = 0;
  receiver.SetFilter(CallbackFilter::Wrap(base::BindLambdaForTesting([&] {
                                            EXPECT_EQ(0, status);
                                            status = 1;
                                          }),
                                          base::BindLambdaForTesting([&] {
                                            EXPECT_EQ(2, status);
                                            status = 3;
                                          })));

  impl.set_ping_handler(base::BindLambdaForTesting([&] {
    EXPECT_EQ(1, status);
    status = 2;
  }));

  for (int i = 0; i < 10; ++i) {
    status = 0;
    base::RunLoop loop;
    remote->Ping(loop.QuitClosure());
    loop.Run();
    EXPECT_EQ(3, status);
  }
}

void Fail() {
  FAIL() << "Unexpected connection error";
}

TEST_P(ReceiverTest, FlushForTesting) {
  bool called = false;
  Remote<sample::Service> remote;
  ServiceImpl impl;
  Receiver<sample::Service> receiver(&impl,
                                     remote.BindNewPipeAndPassReceiver());
  receiver.set_disconnect_handler(base::BindOnce(&Fail));

  remote->Frobinate(
      nullptr, sample::Service::BazOptions::REGULAR, NullRemote(),
      base::BindLambdaForTesting([&](int32_t) { called = true; }));
  EXPECT_FALSE(called);
  // Because the flush is sent from the receiver, it only guarantees that the
  // request has been received, not the response. The second flush waits for
  // the response to be received.
  receiver.FlushForTesting();
  receiver.FlushForTesting();
  EXPECT_TRUE(called);
}

TEST_P(ReceiverTest, FlushForTestingWithClosedPeer) {
  bool called = false;
  Remote<sample::Service> remote;
  ServiceImpl impl;
  Receiver<sample::Service> receiver(&impl,
                                     remote.BindNewPipeAndPassReceiver());
  receiver.set_disconnect_handler(
      base::BindLambdaForTesting([&] { called = true; }));
  remote.reset();

  EXPECT_FALSE(called);
  receiver.FlushForTesting();
  EXPECT_TRUE(called);
  receiver.FlushForTesting();
}

TEST_P(ReceiverTest, DisconnectWithReason) {
  Remote<sample::Service> remote;
  ServiceImpl impl;
  Receiver<sample::Service> receiver(&impl,
                                     remote.BindNewPipeAndPassReceiver());

  base::RunLoop run_loop;
  receiver.set_disconnect_with_reason_handler(base::BindLambdaForTesting(
      [&](uint32_t custom_reason, const std::string& description) {
        EXPECT_EQ(1234u, custom_reason);
        EXPECT_EQ("hello", description);
        run_loop.Quit();
      }));

  remote.ResetWithReason(1234u, "hello");
  run_loop.Run();
}

template <typename T>
struct WeakPtrImplRefTraits {
  using PointerType = base::WeakPtr<T>;

  static bool IsNull(const base::WeakPtr<T>& ptr) { return !ptr; }
  static T* GetRawPointer(base::WeakPtr<T>* ptr) { return ptr->get(); }
};

template <typename T>
using WeakReceiver = Receiver<T, WeakPtrImplRefTraits<T>>;

TEST_P(ReceiverTest, CustomImplPointerType) {
  PingServiceImpl impl;
  base::WeakPtrFactory<test::PingService> weak_factory(&impl);

  Remote<test::PingService> remote;
  WeakReceiver<test::PingService> receiver(weak_factory.GetWeakPtr(),
                                           remote.BindNewPipeAndPassReceiver());

  {
    // Ensure the receiver is functioning.
    base::RunLoop run_loop;
    remote->Ping(run_loop.QuitClosure());
    run_loop.Run();
  }

  {
    // Attempt to dispatch another message after the WeakPtr is invalidated.
    impl.set_ping_handler(base::BindRepeating([] { NOTREACHED(); }));
    remote->Ping(base::BindOnce([] { NOTREACHED(); }));

    // The receiver will close its end of the pipe which will trigger a
    // disconnect on |remote|.
    base::RunLoop run_loop;
    remote.set_disconnect_handler(run_loop.QuitClosure());
    weak_factory.InvalidateWeakPtrs();
    run_loop.Run();
  }
}

TEST_P(ReceiverTest, ReportBadMessage) {
  bool called = false;
  Remote<test::PingService> remote;
  auto pending_receiver = remote.BindNewPipeAndPassReceiver();
  base::RunLoop run_loop;
  remote.set_disconnect_handler(base::BindLambdaForTesting([&] {
    called = true;
    run_loop.Quit();
  }));
  PingServiceImpl impl;
  Receiver<test::PingService> receiver(&impl, std::move(pending_receiver));
  impl.set_ping_handler(base::BindLambdaForTesting(
      [&] { receiver.ReportBadMessage("received bad message"); }));

  std::string received_error;
  SetDefaultProcessErrorHandler(base::BindLambdaForTesting(
      [&](const std::string& error) { received_error = error; }));

  remote->Ping(base::DoNothing());
  EXPECT_FALSE(called);
  run_loop.Run();
  EXPECT_TRUE(called);
  EXPECT_EQ("received bad message", received_error);

  SetDefaultProcessErrorHandler(base::NullCallback());
}

TEST_P(ReceiverTest, GetBadMessageCallback) {
  Remote<test::PingService> remote;
  base::RunLoop run_loop;
  PingServiceImpl impl;
  ReportBadMessageCallback bad_message_callback;

  std::string received_error;
  SetDefaultProcessErrorHandler(base::BindLambdaForTesting(
      [&](const std::string& error) { received_error = error; }));

  {
    Receiver<test::PingService> receiver(&impl,
                                         remote.BindNewPipeAndPassReceiver());
    impl.set_ping_handler(base::BindLambdaForTesting(
        [&] { bad_message_callback = receiver.GetBadMessageCallback(); }));
    remote->Ping(run_loop.QuitClosure());
    run_loop.Run();
    EXPECT_TRUE(received_error.empty());
    EXPECT_TRUE(bad_message_callback);
  }

  std::move(bad_message_callback).Run("delayed bad message");
  EXPECT_EQ("delayed bad message", received_error);

  SetDefaultProcessErrorHandler(base::NullCallback());
}

TEST_P(ReceiverTest, InvalidPendingReceivers) {
  PendingReceiver<sample::Service> uninitialized_pending;
  EXPECT_FALSE(uninitialized_pending);

  // A "null" receiver is just a generic helper for an uninitialized
  // PendingReceiver. Verify that it's equivalent to above.
  PendingReceiver<sample::Service> null_pending{NullReceiver()};
  EXPECT_FALSE(null_pending);
}

TEST_P(ReceiverTest, GenericPendingReceiver) {
  Remote<sample::Service> remote;
  GenericPendingReceiver receiver;
  EXPECT_FALSE(receiver.is_valid());
  EXPECT_FALSE(receiver.interface_name().has_value());

  receiver = GenericPendingReceiver(remote.BindNewPipeAndPassReceiver());
  ASSERT_TRUE(receiver.is_valid());
  EXPECT_EQ(sample::Service::Name_, receiver.interface_name());

  auto ping_receiver = receiver.As<test::PingService>();
  EXPECT_FALSE(ping_receiver.is_valid());
  EXPECT_TRUE(receiver.is_valid());

  auto sample_receiver = receiver.As<sample::Service>();
  EXPECT_TRUE(sample_receiver.is_valid());
  EXPECT_FALSE(receiver.is_valid());
}

class RebindTestImpl : public mojom::RebindTestInterface {
 public:
  explicit RebindTestImpl(base::WaitableEvent* event) : event_(event) {
    DCHECK(event_);
  }
  ~RebindTestImpl() override = default;

  // mojom::RebindTestInterface
  void BlockingUntilExternalSignalCall() override { event_->Wait(); }
  void NormalCall() override {}
  void SyncCall(SyncCallCallback callback) override {
    std::move(callback).Run();
  }

 private:
  base::WaitableEvent* event_;
};

TEST_P(ReceiverTest, RebindWithScheduledSyncMessage) {
  base::WaitableEvent event{base::WaitableEvent::ResetPolicy::MANUAL,
                            base::WaitableEvent::InitialState::NOT_SIGNALED};
  RebindTestImpl impl{&event};
  base::Thread receiver_thread{"receiver"};
  Remote<mojom::RebindTestInterface> remote;
  // Accessible only on receiver thread
  Receiver<mojom::RebindTestInterface> receiver1{&impl};
  Receiver<mojom::RebindTestInterface> receiver2{&impl};

  receiver_thread.Start();

  // Setup of remote and receiver
  auto pending_receiver = remote.BindNewPipeAndPassReceiver();
  receiver_thread.task_runner()->PostTask(
      FROM_HERE, base::BindLambdaForTesting(
                     [&]() { receiver1.Bind(std::move(pending_receiver)); }));
  receiver_thread.FlushForTesting();

  // Perform test
  remote->BlockingUntilExternalSignalCall();
  remote->NormalCall();

  receiver_thread.task_runner()->PostTask(
      FROM_HERE, base::BindLambdaForTesting(
                     [&]() { receiver2.Bind(receiver1.Unbind()); }));
  event.Signal();

  remote->SyncCall();

  // Cleanup
  remote.reset();
  receiver_thread.task_runner()->PostTask(FROM_HERE,
                                          base::BindLambdaForTesting([&]() {
                                            receiver1.reset();
                                            receiver2.reset();
                                          }));
  receiver_thread.FlushForTesting();
}

class TestGenericBinderImpl : public mojom::TestGenericBinder {
 public:
  explicit TestGenericBinderImpl(
      PendingReceiver<mojom::TestGenericBinder> receiver)
      : receiver_(this, std::move(receiver)) {
    receiver_.set_disconnect_handler(base::BindOnce(
        &TestGenericBinderImpl::OnDisconnect, base::Unretained(this)));
  }
  ~TestGenericBinderImpl() override = default;

  bool connected() const { return connected_; }

  void WaitForNextReceiver(GenericPendingReceiver* storage) {
    wait_loop_.emplace();
    next_receiver_storage_ = storage;
    wait_loop_->Run();
  }

  // mojom::TestGenericBinder:
  void BindOptionalReceiver(GenericPendingReceiver receiver) override {
    if (next_receiver_storage_) {
      *next_receiver_storage_ = std::move(receiver);
      next_receiver_storage_ = nullptr;
    }
    if (wait_loop_)
      wait_loop_->Quit();
  }

  void BindReceiver(GenericPendingReceiver receiver) override {
    if (next_receiver_storage_) {
      *next_receiver_storage_ = std::move(receiver);
      next_receiver_storage_ = nullptr;
    }
    if (wait_loop_)
      wait_loop_->Quit();
  }

 private:
  void OnDisconnect() {
    if (wait_loop_)
      wait_loop_->Quit();
    connected_ = false;
  }

  Receiver<mojom::TestGenericBinder> receiver_;
  bool connected_ = true;
  base::Optional<base::RunLoop> wait_loop_;
  GenericPendingReceiver* next_receiver_storage_ = nullptr;

  DISALLOW_COPY_AND_ASSIGN(TestGenericBinderImpl);
};

using ReceiverSerializationTest = ReceiverTest;

TEST_P(ReceiverSerializationTest, NullGenericPendingReceiver) {
  Remote<mojom::TestGenericBinder> remote;
  TestGenericBinderImpl binder(remote.BindNewPipeAndPassReceiver());

  // Bind a null, nullable receiver.
  remote->BindOptionalReceiver(GenericPendingReceiver());
  GenericPendingReceiver receiver;
  binder.WaitForNextReceiver(&receiver);
  EXPECT_FALSE(receiver.is_valid());

  // Bind some valid non-null, non-nullable receivers.
  remote->BindReceiver(
      mojo::Remote<mojom::TestInterface1>().BindNewPipeAndPassReceiver());
  binder.WaitForNextReceiver(&receiver);
  EXPECT_TRUE(receiver.is_valid());
  EXPECT_TRUE(receiver.As<mojom::TestInterface1>());

  remote->BindReceiver(
      mojo::Remote<mojom::TestInterface2>().BindNewPipeAndPassReceiver());
  binder.WaitForNextReceiver(&receiver);
  EXPECT_TRUE(receiver.is_valid());
  EXPECT_TRUE(receiver.As<mojom::TestInterface2>());

  mojo::internal::SerializationWarningObserverForTesting observer;

  // Now attempt to send a null receiver for a non-nullable argument.
  EXPECT_TRUE(binder.connected());
  remote->BindReceiver(GenericPendingReceiver());

  // We should see a validation warning at serialization time. Normally this
  // results in a DCHECK, but it's suppressed by the testing observer we have on
  // the stack. Note that this only works for DCHECK-enabled builds. For
  // non-DCHECK-enabled builds, serialization will succeed above with no errors,
  // but the receiver below will still reject the message and disconnect.
#if DCHECK_IS_ON()
  EXPECT_EQ(mojo::internal::VALIDATION_ERROR_UNEXPECTED_NULL_POINTER,
            observer.last_warning());
#endif

  // |receiver| should not be modified again by the implementation in |binder|,
  // because the it must never receive the invalid request. Instead the Wait
  // should be terminated by disconnection.
  receiver = mojo::Remote<mojom::TestInterface1>().BindNewPipeAndPassReceiver();
  binder.WaitForNextReceiver(&receiver);
  EXPECT_TRUE(receiver.is_valid());
  EXPECT_TRUE(receiver.As<mojom::TestInterface1>());
  EXPECT_FALSE(binder.connected());
}

using SelfOwnedReceiverTest = BindingsTestBase;

TEST_P(SelfOwnedReceiverTest, CloseDestroysImplAndPipe) {
  base::RunLoop run_loop;
  bool disconnected = false;
  bool was_deleted = false;
  Remote<sample::Service> remote;
  auto receiver = remote.BindNewPipeAndPassReceiver();
  remote.set_disconnect_handler(base::BindLambdaForTesting([&] {
    disconnected = true;
    run_loop.Quit();
  }));
  bool called = false;
  base::RunLoop run_loop2;

  auto binding = MakeSelfOwnedReceiver<sample::Service>(
      std::make_unique<ServiceImpl>(&was_deleted), std::move(receiver));
  remote->Frobinate(nullptr, sample::Service::BazOptions::REGULAR, NullRemote(),
                    base::BindLambdaForTesting([&](int32_t) {
                      called = true;
                      run_loop2.Quit();
                    }));
  run_loop2.Run();
  EXPECT_TRUE(called);
  EXPECT_FALSE(disconnected);
  binding->Close();

  // Now that the SelfOwnedReceiver is closed we should detect an error on the
  // other end of the pipe.
  run_loop.Run();
  EXPECT_TRUE(disconnected);

  // Destroying the SelfOwnedReceiver also destroys the impl.
  ASSERT_TRUE(was_deleted);
}

TEST_P(SelfOwnedReceiverTest, DisconnectDestroysImplAndPipe) {
  Remote<sample::Service> remote;
  bool was_deleted = false;
  base::RunLoop run_loop;

  MakeSelfOwnedReceiver<sample::Service>(
      std::make_unique<ServiceImpl>(base::BindLambdaForTesting([&] {
        was_deleted = true;
        run_loop.Quit();
      })),
      remote.BindNewPipeAndPassReceiver());

  base::RunLoop().RunUntilIdle();
  EXPECT_FALSE(was_deleted);

  remote.reset();
  EXPECT_FALSE(was_deleted);
  run_loop.Run();
  EXPECT_TRUE(was_deleted);
}

INSTANTIATE_MOJO_BINDINGS_TEST_SUITE_P(ReceiverTest);
INSTANTIATE_MOJO_BINDINGS_TEST_SUITE_P(SelfOwnedReceiverTest);

// These tests only make sense for serialized messages.
INSTANTIATE_TEST_SUITE_P(
    All,
    ReceiverSerializationTest,
    testing::Values(mojo::BindingsTestSerializationMode::kSerializeBeforeSend));

}  // namespace receiver_unittest
}  // namespace test
}  // namespace mojo
#endif
