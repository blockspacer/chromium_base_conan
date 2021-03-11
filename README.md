# About

Modified `base` library from chromium https://github.com/chromium/chromium/tree/master/base

## How to do minor updates

Clone latest base:

```bash
cd ~
git clone https://chromium.googlesource.com/chromium/src/base
# see https://chromium.googlesource.com/chromium/src/base/+/944910a3c30b76db99a3978f59098e8a33953617
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

Parse json to generate cmake vars, see as example https://github.com/google/skia/blob/375e1f6a6486a1e423f61d221bc39d81a2aaf6a0/gn/gn_to_cmake.py

## EXTRA FEATURES

- ported to CMake
- supports Conan
- added CMake options to disable some features
- ported to WASM (emscripten) with threading support
- ported to WASM (emscripten) without threading support

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
  -e flextool:enable_tests=True \
  -e flextool:enable_llvm_tools=True

cmake -E time cmake .. \
  -DCMAKE_C_COMPILER=clang-10 \
  -DCMAKE_CXX_COMPILER=clang++-10 \
  -DCMAKE_VERBOSE_MAKEFILE=FALSE \
  -DENABLE_TESTS=FALSE \
  -DBASE_NEED_GEN_BUILD_DATE=FALSE \
  -DENABLE_DOCTEST=OFF \
  -DBUILD_SHARED_LIBS=FALSE \
  -DCONAN_AUTO_INSTALL=OFF \
  -DCMAKE_BUILD_TYPE=Debug

cmake -E time cmake --build . -- -j8
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
        -o chromium_tcmalloc:use_alloc_shim=False \
        -o openssl:shared=True

# clean build cache
conan remove "*" --build --force
```

## HOW TO INSTALL FROM CONAN

```
conan install --build=missing --profile clang ..
```

## USAGE EXAMPLES

TODO

## LICENSE

TODO

## PORT ISSUES

- Some flags from `declare_args` may be not supported.
- Some platforms may be not supported.

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
from commit 07bf855b4db90ee18e4cf3452bcbc0b4f80256e5
05/13/2019 12:28 PM
Worker: Clear ResourceTimingNotifier on WorkerFetchContext::Detach()
Bug: 959508, 960626
Change-Id: I2663e5acddec0d9f88a78842c093c594fb57acb8
Reviewed-on: https://chromium-review.googlesource.com/c/chromium/src/+/1609024
```

## Disclaimer

That open source project based on the Google Chromium project.

This is not official Google product.

Portions Copyright (c) Google Inc.

See LICENSE files.
