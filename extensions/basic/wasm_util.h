#pragma once

#include <build/build_config.h>

#if defined(__EMSCRIPTEN__) && !defined(OS_EMSCRIPTEN)
#error "__EMSCRIPTEN__ requires OS_EMSCRIPTEN to be defined"
#endif

#if defined(__EMSCRIPTEN__)

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#ifdef __EMSCRIPTEN_PTHREADS__
#include <emscripten/threading.h>
#endif // __EMSCRIPTEN_PTHREADS__

#if (defined(ASYNCIFY) || defined(EMTERPRETIFY)) && !defined(HAS_ASYNC)
#define HAS_ASYNC 1
#endif

#if !defined(__EMSCRIPTEN_PTHREADS__) && !defined(DISABLE_PTHREADS)
#define DISABLE_PTHREADS 1
#endif

/// \note rquires "emscripten/emscripten.h"
/// \note The stack trace is not available at least on IE10 and Safari 6.
/// \note build with -s DEMANGLE_SUPPORT=1 and -O1
/// \note stackTrace() tries to demangle C++ function names
/// \see https://emscripten.org/docs/porting/Debugging.html#manual-print-debugging
/// \see emscripten_get_callstack, stackTrace, emscripten_run_script_string, EM_ASM
/// \see https://github.com/lolengine/lol/blob/master/src/base/assert.cpp#L32
/// \see http://webassemblycode.com/using-browsers-debug-webassembly/
#define HTML5_STACKTRACE() \
  printf("This message is in %s:%d:%s\n",  __FILE__, __LINE__, __func__); \
  printf("Callstack:\n%s", emscripten_run_script_string("stackTrace();"));

#define HTML5_STACKTRACE_IF(x) \
  if ((x)) { \
    HTML5_STACKTRACE(); \
  }

#define HTML5_STACKTRACE_WRAP() \
  []() { \
    HTML5_STACKTRACE(); \
    return ""; \
  }()

#define EM_IS_MAIN_THREAD() \
  (emscripten_has_threading_support() ? emscripten_is_main_runtime_thread() : true)

/// \note printing to console or emscripten terminal area may
/// decrease performance drastically
/// \note Webassembly worker thread may hang if printf is used in threads
/// \see https://github.com/emscripten-core/emscripten/issues/8325
#define EM_LOG(arg) \
  EM_ASM(console.log('EM_LOG: ' + UTF8ToString($0)), arg);

#define EM_ERR(arg) \
  EM_ASM(console.error('EM_LOG: ' + UTF8ToString($0)), arg);

#define EM_LOG_NUM(arg) \
  EM_ASM(console.log('EM_LOG: ' + $0), arg);

#define EM_ERR_NUM(arg) \
  EM_ASM(console.error('EM_LOG: ' + $0), arg);

/// \note use emscripten_async* to prevent blocking of browser event loop
/// \note emscripten_async* may be delayed too much, use it only with async logic
#define emscripten_async_call_closure(closureArg) \
{ \
  base::STClosure* stClosure = new base::STClosure(std::move( \
        (closureArg) \
      )); \
  void* dataIn = reinterpret_cast<void*>(stClosure); \
  DCHECK(dataIn); \
  emscripten_async_call([](void* data) { \
      DCHECK(data); \
      base::STClosure* stClosureData = reinterpret_cast<base::STClosure*>(data); \
      std::move(stClosureData->onceClosure_).Run(); \
      delete stClosureData; \
  }, dataIn, 10); \
}

// wraps std::function into async call (emscripten only)
// see https://github.com/chadaustin/Web-Benchmarks/blob/master/embind_calls/bench.cpp#L90
#define DECLARE_HTML5_YIELD_HELPER() \
static void emscripten_yield_call(std::function<void()> f, const int ms = 500) { \
    P_LOG("emscripten_yield_call waitable\n"); \
    auto p = new std::function<void()>(f); \
    emscripten_async_call([](void* p) { \
        P_LOG("emscripten_async_call waitable\n"); \
        auto q = reinterpret_cast<std::function<void()>*>(p); \
        (*q)(); \
        delete q; \
    }, p, ms); \
}

#define HTML5_YIELD_HELPER_1(x) \
  emscripten_yield_call((x));

#define HTML5_YIELD_HELPER_2(x, y) \
  emscripten_yield_call((x), (y));

// see https://github.com/h-s-c/libKD/blob/master/source/kd_threads.c#L861
// see https://emscripten.org/docs/api_reference/emscripten.h.html?highlight=emscripten_sleep#c.emscripten_sleep
// emscripten_sleep - Sleep for ms milliseconds. blocks all other operations while it runs
// emscripten_sleep_with_yield - If you do want things to happen while sleeping
#ifdef HAS_ASYNC
#define HTML5_ASYNC_SLEEP(x) \
  printf("This message is in %s:%d:%s\n",  __FILE__, __LINE__, __func__); \
  printf("called emscripten_sleep_with_yield(%lld)\n", (x)); \
  emscripten_sleep_with_yield((x)); \
  printf("finished emscripten_sleep_with_yield(%lld)\n", (x));
#else
#define HTML5_ASYNC_SLEEP(x) \
  printf("This message is in %s on line %d\n",  __FILE__, __LINE__); \
  printf("called emscripten_sleep_with_yield(%lld)\n", (x)); \
  printf("emscripten_sleep_with_yield requires emterpreter or https://emscripten.org/docs/porting/asyncify.html"); \
  HTML5_STACKTRACE(); \
  printf("finished emscripten_sleep_with_yield(%lld)\n", (x));
#endif

#else

#define HTML5_STACKTRACE()

#define HTML5_STACKTRACE_IF(x)

#define HTML5_STACKTRACE_WRAP()

#define EM_IS_MAIN_THREAD()

#define EM_LOG(arg)

#define EM_ERR(arg)

#define EM_LOG_NUM(arg)

#define EM_ERR_NUM(arg)

#define emscripten_async_call_closure(closureArg)

#define DECLARE_HTML5_YIELD_HELPER()

#define HTML5_ASYNC_SLEEP()

#endif
