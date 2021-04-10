# About

Modified `base` library from chromium, see https://github.com/chromium/chromium/tree/master/base

Modification history in `extensions/PATCH_HISTORY.md` and added files in `extensions/`.

NOTE: Some features or platforms may be not supported.
Run unit tests to check support of some feature.

## Project goals

* Easy integration with open-source projects that use `CMake` and `conan`
* Provide codebase similar to `chromium/base`, `libchrome`, `mini_chromium` etc.
* Make library cross-platform (add browser support etc.)
* Extend `base` library from chromium with extra general-purpose functionality

## What is `base` library?

Base, libchrome and mini_chromium are general utility libraries from chromium.

See:

* https://github.com/chromium/chromium/tree/master/base
* https://chromium.googlesource.com/chromiumos/docs/+/master/packages/libchrome.md
* https://chromium.googlesource.com/chromium/mini_chromium/

## What is `basic` library?

In `./extensions/basic/` you can find code that extends `base` library.

For example, `basic` adopts some code from `facebook/folly` library.

Some changes made in `facebook/folly`:

* Exceptions replaced with `StatusOr` or `CHECK`.
* `std::thread` replaced with `base::Thread` or `base::PlatformThread`.
* Removed already existing functionality (avoids code duplication).
* Ported to more platforms (Android, browser, etc.)

## How to use it?

Before usage set:

* `setlocale(LC_ALL, "en_US.UTF-8")`
* `base::i18n::InitializeICU()`
* `logging::InitLogging(settings);`
* `base::ThreadPoolInstance::CreateAndStartWithDefaultParams`
* `base::AtExitManager`
* `base::CommandLine::Init`
* `base::RunLoop`
* `base::ThreadPoolInstance::Get()->Shutdown()`
* etc.

Usage:

```cpp
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

#include <locale.h>

class AppDemo {
 public:
  AppDemo();
  ~AppDemo();

  void Initialize();
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

const int kTraceEventAppSortIndex = -1;

} // namespace switches

int main(int argc, const char* argv[]) {
  setlocale(LC_ALL, "en_US.UTF-8");

  base::EnableTerminationOnHeapCorruption();
  // Manages the destruction of singletons.
  base::AtExitManager exit_manager;

  CHECK(base::CommandLine::Init(argc, argv));
  const base::CommandLine& command_line = *base::CommandLine::ForCurrentProcess();

#ifndef NDEBUG
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
  settings.logging_dest = destination;

  settings.log_file_path = log_filename.value().c_str();
  settings.delete_old = logging::DELETE_OLD_LOG_FILE;
  logging::InitLogging(settings);

  logging::SetLogItems(true /* Process ID */, true /* Thread ID */,
                       true /* Timestamp */, false /* Tick count */);

  base::i18n::InitializeICU();

#ifndef NDEBUG
  CHECK(base::debug::EnableInProcessStackDumping());
#endif

  // Initialize tracing.
  base::trace_event::TraceLog::GetInstance()->set_process_name("Browser");
  base::trace_event::TraceLog::GetInstance()->SetProcessSortIndex(
      kTraceEventAppSortIndex);
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
}
```

See as example:

* https://source.chromium.org/chromium/chromium/src/+/b28193d300f6a0853f31d305b3fb917c3a1601b7:remoting/host/it2me/it2me_native_messaging_host_main.cc
* https://source.chromium.org/chromium/chromium/src/+/b28193d300f6a0853f31d305b3fb917c3a1601b7:gpu/vulkan/demo/
* https://source.chromium.org/chromium/chromium/src/+/b28193d300f6a0853f31d305b3fb917c3a1601b7:content/shell/app/shell_main_delegate.cc
* https://source.chromium.org/chromium/chromium/src/+/b28193d300f6a0853f31d305b3fb917c3a1601b7:chrome/browser/chrome_browser_main.cc

Run compiled app with arguments:

* `--icu-data-file=` must point to icu data file (example `.dat` files in https://chromium.googlesource.com/chromium/deps/icu/+/dc4ceac1fd9c77c3cacf6dec4ac83f684e069644/common/)
* set logging level using vmodule i.e. `--vmodule=*=9999`
* `--assets-dir=` can be used to change `DIR_ASSETS` (see `base/base_paths.h`)

## DOCS

See `./extensions/docs/`

Extra docs:

* The Chromium Projects https://www.chromium.org/developers
* Chromium docs https://chromium.googlesource.com/chromium/src/+/master/docs
* Chromium Chronicle https://developer.chrome.com/tags/chromium-chronicle/

`base` is similar to `abseil`, so you may want to read `abseil` docs:

* https://abseil.io/docs/cpp/guides/

`basic` is similar to `folly`, so you may want to read `folly` docs:

* https://github.com/facebook/folly/tree/master/folly/docs
* https://engineering.fb.com/2012/06/02/developer-tools/folly-the-facebook-open-source-library/
* https://engineering.fb.com/2015/06/19/developer-tools/futures-for-c-11-at-facebook/
* https://engineering.fb.com/2019/04/25/developer-tools/f14/
* https://groups.google.com/g/facebook-folly

## Before build (dependencies)

Create clang conan profile https://docs.conan.io/en/1.34/reference/profiles.html#examples

Re-build dependencies:

```bash
git clone https://github.com/blockspacer/conan_github_downloader.git ~/conan_github_downloader

cmake \
  -DSCRIPT_PATH="$PWD/get_conan_dependencies.cmake"\
  -DEXTRA_CONAN_OPTS="--profile;clang\
;-s;build_type=Debug\
;-s;cling_conan:build_type=Release\
;-s;llvm_tools:build_type=Release\
;--build;missing" \
  -P ~/conan_github_downloader/conan_github_downloader.cmake
```

## Dev-only build (local conan flow)

```bash
find . -type f -name "*_buildflags.h" -exec rm {} \;
find . -type f -name "*_buildflags.tmp" -exec rm {} \;

(rm -rf local_build || true)

mkdir local_build

cd local_build

export CONAN_REVISIONS_ENABLED=1
export CONAN_VERBOSE_TRACEBACK=1
export CONAN_PRINT_RUN_COMMANDS=1
export CONAN_LOGGING_LEVEL=10
export GIT_SSL_NO_VERIFY=true

cmake -E time \
  conan install .. \
  --install-folder . \
  -s build_type=Debug \
  -s cling_conan:build_type=Release \
  -s llvm_tools:build_type=Release \
  --profile clang \
  -e chromium_base:enable_tests=True \
  -o chromium_base:shared=True \
  -o perfetto:is_hermetic_clang=False

(rm CMakeCache.txt || true)

# You can use `cmake --build . -- -j14` on second run.
cmake -E time \
  conan build .. --build-folder=.

cmake -E time \
  conan package --build-folder=. ..

cmake -E time \
  conan export-pkg .. conan/stable --settings build_type=Debug --force --profile clang

cmake -E time \
  conan test ../test_package chromium_base/master@conan/stable --settings build_type=Debug --profile clang
```

## HOW TO BUILD FROM SOURCE

```bash
# NOTE: change `build_type=Debug` to `build_type=Release` in production
CONAN_REVISIONS_ENABLED=1 \
    CONAN_VERBOSE_TRACEBACK=1 \
    CONAN_PRINT_RUN_COMMANDS=1 \
    CONAN_LOGGING_LEVEL=10 \
    GIT_SSL_NO_VERIFY=true \
    conan create . \
        conan/stable \
        -s build_type=Debug \
        -s llvm_tools:build_type=Release \
        --profile clang \
        --build missing \
        --build cascade \
        -e chromium_base:enable_tests=True \
        -o chromium_base:use_alloc_shim=True \
        -o chromium_base:shared=True \
        -o chromium_tcmalloc:use_alloc_shim=True \
        -o perfetto:is_hermetic_clang=False \
        -o openssl:shared=True

# clean build cache
conan remove "*" --build --force
```

## HOW TO BUILD WITH SANITIZERS ENABLED

Use `enable_asan` or `enable_ubsan`, etc.

```bash
# NOTE: change `build_type=Debug` to `build_type=Release` in production
CONAN_REVISIONS_ENABLED=1 \
    CONAN_VERBOSE_TRACEBACK=1 \
    CONAN_PRINT_RUN_COMMANDS=1 \
    CONAN_LOGGING_LEVEL=10 \
    GIT_SSL_NO_VERIFY=true \
    conan create . \
        conan/stable \
        -s build_type=Debug \
        -s llvm_tools:build_type=Release \
        --profile clang \
        --build chromium_tcmalloc \
        -s llvm_tools:build_type=Release \
        -o llvm_tools:enable_tsan=True \
        -o llvm_tools:include_what_you_use=False \
        -e chromium_base:enable_tests=True \
        -o chromium_base:enable_tsan=True \
        -e chromium_base:enable_llvm_tools=True \
        -o chromium_base:use_alloc_shim=False \
        -o chromium_base:shared=True \
        -o abseil:enable_tsan=True \
        -e abseil:enable_llvm_tools=True \
        -o perfetto:is_hermetic_clang=False \
        -o openssl:shared=True

# clean build cache
conan remove "*" --build --force
```

## DEPS

See https://github.com/chromium/chromium/blob/master/base/DEPS

- icu
- ced
- modp_b64
- dynamic_annotations
- libevent (on UNIX)
- tcmalloc (on UNIX)
- LIBATOMIC (on UNIX)
- PTHREADS (on UNIX)
- xdg_mime (on UNIX)
- xdg_user_dirs (on UNIX)

Extra deps used by `./extensions/basic/`:

- header-only boost libraries
- fmt
- abseil

## Used chromium version

```bash
[base] Add C++23 Enum Helpers

This change adds the C++23 enum utilities std::to_underlying and
std::is_scoped_enum.

Bug: None
Change-Id: Idb275bfb4833080701dbce5f5d307091debe27b2
Reviewed-on: https://chromium-review.googlesource.com/c/chromium/src/+/2736976
Reviewed-by: Daniel Cheng <dcheng@chromium.org>
Commit-Queue: Jan Wilken D?rrie <jdoerrie@chromium.org>
Cr-Commit-Position: refs/heads/master@{#860144}
GitOrigin-RevId: f89fc2ac30e582dfe9e334baf19ef8e535eea30d
```

## How to do minor updates

Clone latest base:

```bash
cd ~
git clone https://chromium.googlesource.com/chromium/src/base
# see https://chromium.googlesource.com/chromium/src/base/+/944910a3c30b76db99a3978f59098e8a33953617
# see https://source.chromium.org/chromium/chromium/src/base/+/944910a3c30b76db99a3978f59098e8a33953617:
git checkout 944910a3c30b76db99a3978f59098e8a33953617
```

Copy sources and apply patches by hand.

## How to do major updates

```bash
#
git config --global url."https://github.com/".insteadOf git://github.com/
git config --global url."https://chromium.googlesource.com/".insteadOf git://chromium.googlesource.com/

git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
export PATH=$PWD/depot_tools:$PATH

mkdir ~/chromium && cd ~/chromium

cat >> git_with_retry.sh << EOF
#!/bin/bash

GIT_TRACE=1
REALGIT=/usr/bin/git

RETRIES=10
DELAY=1
COUNT=1
while [ \$COUNT -lt \$RETRIES ]; do
  \$REALGIT "\$@"
  if [ \$? -eq 0 ]; then
    RETRIES=0
    break
  fi
  let COUNT=\$COUNT+1
  sleep \$DELAY
done
EOF
chmod +x git_with_retry.sh
export PATH=$PWD:$PATH

# see https://chromium.googlesource.com/chromium/src/+/f89fc2ac30e582dfe9e334baf19ef8e535eea30d
wget https://chromium.googlesource.com/chromium/src/+archive/f89fc2ac30e582dfe9e334baf19ef8e535eea30d.tar.gz
mkdir src && cd src
tar xzvf ../f89fc2ac30e582dfe9e334baf19ef8e535eea30d.tar.gz
git init
git remote add origin https://chromium.googlesource.com/chromium/src.git
git_with_retry.sh fetch origin master
git checkout f89fc2ac30e582dfe9e334baf19ef8e535eea30d
git reset --hard f89fc2ac30e582dfe9e334baf19ef8e535eea30d

# Pull in all dependencies for HEAD
gclient.py sync --nohooks --no-history --shallow --revision=f89fc2ac30e582dfe9e334baf19ef8e535eea30d

# see https://chromium.googlesource.com/chromium/src/+/master/build/install-build-deps.sh
sudo apt install -y \
  bzip2 tar bison binutils gperf wdiff python-psutil \
  php php-cli python-psutil

# (only on linux)
./build/install-build-deps.sh

# Once you've run install-build-deps at least once, you can now run the Chromium-specific hooks,
# which will download additional binaries and other things you might need:
gclient runhooks

gn gen out/config --args='is_debug=false is_official_build=true' --ide=json
```

Follow `extensions/README.md`

## Conan workspace and QT Creator

```bash
# remove old build files, but keep conan workspace layout
find conan_workspace\
  \! -name 'conan_workspace' \
  \! -name 'conan_workspace.yml' \
  \! -name 'conan_layout' \
  \! -name 'CMakeLists.txt' \
  -exec rm -rf {} +

cd conan_workspace

conan workspace install \
  ./conan_workspace.yml \
  --profile=clang \
  -s build_type=Debug \
  -s cling_conan:build_type=Release \
  -s llvm_tools:build_type=Release \
  -o openssl:shared=True \
  -e chromium_base:enable_tests=True \
  -o chromium_base:shared=True

cmake -E time \
  conan build .. --build-folder=.
```

We need to run QT Creator from terminal that uses environment variables from `activate.sh`:

```bash
source activate.sh

# run new QtCreator window
qtcreator
```

Create kit in QT Creator with same compiler version as in conan profile.

Open `conan_workspace/CMakelists.txt` file in QT Creator, but enable only `Debug` output directory and set `Debug` output directory to `conan_workspace` (replace with full path to build folder that used `conan build` above).

## Coroutines support

Used conan profile:

```txt
[settings]
# We are building in Ubuntu Linux
os_build=Linux
os=Linux
arch_build=x86_64
arch=x86_64

compiler=clang
compiler.version=11
compiler.libcxx=libc++
compiler.cppstd=20

[env]
CC=/usr/bin/clang-11
CXX=/usr/bin/clang++-11
CXXFLAGS="-v"

[build_requires]
cmake_installer/3.15.5@conan/stable
```

Used clang version:

```bash
# LLVM
sudo apt-get install libllvm-11-ocaml-dev libllvm11 llvm-11 llvm-11-dev llvm-11-doc llvm-11-examples llvm-11-runtime
# Clang and co
sudo apt-get install clang-11 clang-tools-11 clang-11-doc libclang-common-11-dev libclang-11-dev libclang1-11 clang-format-11 clangd-11
# libfuzzer
sudo apt-get install libfuzzer-11-dev
# lldb
sudo apt-get install lldb-11
# lld (linker)
sudo apt-get install lld-11
# libc++
sudo apt-get install libc++-11-dev libc++abi-11-dev
# OpenMP
sudo apt-get install libomp-11-dev
# clang-tidy
sudo apt-get install clang-tidy-11
# libunwind
sudo apt-get install -y libunwind-dev
```

Re-install conan workspace with `--build=missing`.

NOTE: You can use `-e chromium_base:compile_with_llvm_tools=True` instead.

## Disclaimer

That open source project based on the Google Chromium project.

This is not official Google product.

Portions Copyright (c) Google Inc.

See LICENSE files.
