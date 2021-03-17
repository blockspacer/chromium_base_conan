# About

Modified `base` library from chromium https://github.com/chromium/chromium/tree/master/base

Modification history in `extensions/PATCH_HISTORY.md` and added files in `extensions/`.

NOTE: Some features or platforms may be not tested. Run unit tests to check support of some feature.

## Project goals

* Easy integration with open-source projectes that use `CMake` and `conan`
* Provide codebase similar to `chromium/base`, `libchrome`, `mini_chromium` etc.
* Make library cross-platform (add browser support etc.)
* Extend `base` library from chromium with extra general-purpose functionality

## What is it?

Base, libchrome and mini_chromium are general utility libraries from chromium.

See:

* https://github.com/chromium/chromium/tree/master/base
* https://chromium.googlesource.com/chromiumos/docs/+/master/packages/libchrome.md
* https://chromium.googlesource.com/chromium/mini_chromium/

## How to use it?

Before usage set `base::i18n::InitializeICU()`, `setlocale(LC_ALL, "en_US.UTF-8")`, `logging::InitLogging(settings);`, `base::ThreadPoolInstance::CreateAndStartWithDefaultParams`, `base::AtExitManager`, `base::CommandLine::Init`, `base::RunLoop`, `base::ThreadPoolInstance::Get()->Shutdown()`, etc.

See as example https://source.chromium.org/chromium/chromium/src/+/b28193d300f6a0853f31d305b3fb917c3a1601b7:remoting/host/it2me/it2me_native_messaging_host_main.cc

Run compiled app with arguments:

* `--icu-data-file=` must point to icu data file (example `.dat` files in https://chromium.googlesource.com/chromium/deps/icu/+/dc4ceac1fd9c77c3cacf6dec4ac83f684e069644/common/)
* set logging level using vmodule i.e. `--vmodule=*=9999`
* `--assets-dir=` can be used to change `DIR_ASSETS` (see `base/base_paths.h`)

## DOCS

The Chromium Projects https://www.chromium.org/developers

Chromium docs https://chromium.googlesource.com/chromium/src/+/master/docs

## Dev build

```bash
find . -type f -name "*_buildflags.h" -exec rm {} \;
find . -type f -name "*_buildflags.tmp" -exec rm {} \;

(rm -rf local_build || true)

mkdir local_build

cd local_build

CONAN_REVISIONS_ENABLED=1 \
CONAN_VERBOSE_TRACEBACK=1 \
CONAN_PRINT_RUN_COMMANDS=1 \
CONAN_LOGGING_LEVEL=10 \
GIT_SSL_NO_VERIFY=true \
  cmake -E time \
  conan install .. \
  --install-folder . \
  -s build_type=Debug \
  -s cling_conan:build_type=Release \
  -s llvm_tools:build_type=Release \
  --profile clang \
  -e chromium_base:enable_tests=True \
  -e abseil:enable_llvm_tools=True \
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
        -o abseil:enable_tsan=True \
        -e abseil:enable_llvm_tools=True \
        -o perfetto:is_hermetic_clang=False \
        -o openssl:shared=True

# clean build cache
conan remove "*" --build --force
```

## HOW TO INSTALL FROM CONAN

```
conan install --build=missing --profile clang ..
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
# and https://source.chromium.org/chromium/chromium/src/base/+/944910a3c30b76db99a3978f59098e8a33953617:
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

## Disclaimer

That open source project based on the Google Chromium project.

This is not official Google product.

Portions Copyright (c) Google Inc.

See LICENSE files.
