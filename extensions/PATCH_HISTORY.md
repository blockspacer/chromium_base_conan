# About

Log of changes made in original `chromium/src/base`.

## Extra utils

About helper utils in `extensions/base`

## BoringSSL -> OpenSSL

BoringSSL replaced by OpenSSL.

Had to add `defined(ENABLE_BORINGSSL)` in `base/hash/md5_boringssl.h`

##  disabled `traced_value_support_unittest` due to missing `perfetto_test_support`

chromium includes `component("perfetto_test_support")` directly from subproject `third_party/perfetto/BUILD.gn`.

Had to disable `traced_value_support_unittest`

## `CHROMIUM_GDBINIT_SOURCED`

Replaced `CHROMIUM_GDBINIT_SOURCED` in `base/debug/debugger_posix.cc`

## `base/base_paths.cc`

Added ability to change built-in paths using command-line flags.

Patched `base/base_paths.cc` (`DIR_TEST_DATA`, `DIR_ASSETS`, etc.) using new `base::CommandLine`.

## `icu_util`

Added ability to load data file by custom path in `icu_util` and `base/test/icu_test_util.cc`

## `LOCKABLE`

Added `LOCKABLE` to:

```cpp
class LOCKABLE SequenceChecker
class BASE_EXPORT LOCKABLE SequencedTaskRunner
class BASE_EXPORT LOCKABLE Thread
class BASE_EXPORT LOCKABLE ThreadCollisionWarner
class BASE_EXPORT LOCKABLE Check
class BASE_EXPORT LOCKABLE ScopedRecursiveCheck
```

## `extensions/build/build_config.h`

Added `EMSCRIPTEN` support and:

```cpp
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define OS_WIN 1
#define OS_WINDOWS 1
```

Search defines in source files:

* __EMSCRIPTEN__
* EMSCRIPTEN
* OS_EMSCRIPTEN
* DISABLE_PTHREADS
* __EMSCRIPTEN_PTHREADS__
* HAS_ASYNC
* HTML5_
* EM_

## Ability to build with UCONFIG_NO_COLLATION, UCONFIG_NO_FORMATTING, UCONFIG_NO_BREAK_ITERATION

Search defines in source files:

* UCONFIG_NO_COLLATION
* UCONFIG_NO_FORMATTING
* UCONFIG_NO_BREAK_ITERATION

## `base/build_time_unittest.cc`

Changed `build_time_unittest.cc` and created private define `BUILD_DATE=BASE_BUILD_DATE` to avoid collision on `BUILD_DATE` with other projects.

## Tests

Had to add in `main` function used by tests (`run_all_unittests.cc`, `run_all_perftests.cc`, etc.)

```cpp
#include "base/test/scoped_locale.h"

base::ScopedLocale locale("en_US.UTF-8");
```

TODO: Had to disable some failing tests.

## Logging

Added to `logging.h`:

```cpp
using ::logging::noEndl;
using ::logging::noFormat;
using ::logging::doNothing;
using ::logging::info;
class LogStringStream;
```

## Added `friend struct CheckedBindState` into `callback.h`

```cpp
template <typename CheckerType, typename Functor, typename... BoundArgs>
struct CheckedBindState;

// ...

template <typename CheckerType, typename Functor, typename... BoundArgs>
friend struct CheckedBindState;
```

## numerics

Added `StrongCheckedNumeric`, `StrongClampedNumeric`, `StrongStrictNumeric`

## containers

Added to `base/containers/span.h`:

```cpp
TEST(SpanTest, WithoutPrefix)

TEST(SpanTest, WithoutSuffix)
```

Added `void clear()` and `void Prepend` into `base/containers/linked_list.h`

## Added C++20 support

Search defines in source files:

* `#if __cplusplus <= 201703L`

Affected C++20 changes:

* In C++20 the way that the relational operators work was changed, notably with the introduction of the spaceship <=> operator. In particular, If you only provide operator==, then a != b is rewritten to !(a == b).
* C++20 adds a new character type that is used to represent UTF-8 code units. u8 string literals in C++20 have type const char8_t[N] instead of const char[N], which was the case previously.
