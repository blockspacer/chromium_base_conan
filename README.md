# About

Modified `base` library from chromium https://github.com/chromium/chromium/tree/master/base

## EXTRA FEATURES

- ported to CMake
- supports Conan
- added CMake options to disable some features
- supports starboard from cobalt.foo
- ported to WASM (emscripten) with threading support
- ported to WASM (emscripten) without threading support

## DOCS

The Chromium Projects https://www.chromium.org/developers

Chromium docs https://chromium.googlesource.com/chromium/src/+/master/docs

## HOW TO BUILD FROM SOURCE

TODO
```
conan create . conan/stable
```

## HOW TO INSTALL FROM CONAN

TODO
```
# conan install --build=missing --profile clang -o enable_tests=False ..
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
- (optional) starboard from cobalt.foo

## Used chromium version

```bash
from commit 07bf855b4db90ee18e4cf3452bcbc0b4f80256e5
05/13/2019 12:28 PM
Worker: Clear ResourceTimingNotifier on WorkerFetchContext::Detach()
Bug: 959508, 960626
Change-Id: I2663e5acddec0d9f88a78842c093c594fb57acb8
Reviewed-on: https://chromium-review.googlesource.com/c/chromium/src/+/1609024
```
