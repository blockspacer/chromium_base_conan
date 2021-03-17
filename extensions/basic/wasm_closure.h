#pragma once

#include <basic/wasm_util.h>
#include <base/callback.h>

#if defined(OS_EMSCRIPTEN) && defined(DISABLE_PTHREADS)
/// \note Used to schedule task using emscripten_async_call
///       without blocking browser main loop.
/// \see https://developer.mozilla.org/en-US/docs/Web/JavaScript/EventLoop#Zero_delays
struct BASE_EXPORT STClosure {
    STClosure(OnceClosure onceClosure) : onceClosure_(std::move(onceClosure)) {}
    OnceClosure onceClosure_;
};
#endif
