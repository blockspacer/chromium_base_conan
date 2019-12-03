// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file adds defines about the platform we're currently building on.
//  Operating System:
//    OS_WIN / OS_MACOSX / OS_LINUX / OS_POSIX (MACOSX or LINUX) /
//    OS_NACL (NACL_SFI or NACL_NONSFI) / OS_NACL_SFI / OS_NACL_NONSFI
//    OS_CHROMEOS is set by the build system
//  Compiler:
//    COMPILER_MSVC / COMPILER_GCC
//  Processor:
//    ARCH_CPU_X86 / ARCH_CPU_X86_64 / ARCH_CPU_X86_FAMILY (X86 or X86_64)
//    ARCH_CPU_32_BITS / ARCH_CPU_64_BITS

#ifndef BUILD_BUILD_CONFIG_H_
#define BUILD_BUILD_CONFIG_H_

// TODO
#ifndef SK_CRASH
#define SK_CRASH() \
  printf("called SK_CRASH");
#endif

// TODO: remove custom debug messages than wasm port will be finalized
#if defined(PORT_OWN_DLOG)
#define P_LOG(...) \
  printf("This message is in %s on line %d\n",  __FILE__, __LINE__); \
  printf((__VA_ARGS__));
#else
#define P_LOG(...) \
  (void)(0);
#endif

// TODO: move wasm helpers to separate file
// (also than can use OS_EMSCRIPTEN)
#if defined(__EMSCRIPTEN__)

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

#endif

//#if defined(STARBOARD)
//#define OS_STARBOARD 1

// A set of macros to use for platform detection.
#if defined(__native_client__)
// __native_client__ must be first, so that other OS_ defines are not set.
#define OS_NACL 1
// OS_NACL comes in two sandboxing technology flavors, SFI or Non-SFI.
// PNaCl toolchain defines __native_client_nonsfi__ macro in Non-SFI build
// mode, while it does not in SFI build mode.
#if defined(__native_client_nonsfi__)
#define OS_NACL_NONSFI
#else
#define OS_NACL_SFI
#endif
#elif defined(EMSCRIPTEN) || defined(__EMSCRIPTEN__)
#define OS_EMSCRIPTEN 1
#elif defined(ANDROID)
#define OS_ANDROID 1
#elif defined(__APPLE__)
// only include TargetConditions after testing ANDROID as some android builds
// on mac don't have this header available and it's not needed unless the target
// is really mac/ios.
#include <TargetConditionals.h>
#define OS_MACOSX 1
#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#define OS_IOS 1
#endif  // defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#elif defined(__linux__)
#define OS_LINUX 1
// include a system header to pull in features.h for glibc/uclibc macros.
#include <unistd.h>
#if defined(__GLIBC__) && !defined(__UCLIBC__)
// we really are using glibc, not uClibc pretending to be glibc
#define LIBC_GLIBC 1
#endif
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define OS_WIN 1
// custom
#define OS_WINDOWS 1 // https://github.com/blockspacer/skia-opengl-emscripten/blob/7c423190544c8da1bf8ae79b800c9c0c83dd3c6e/src/chromium/base/third_party/symbolize/demangle.cc#L41
#elif defined(__Fuchsia__)
#define OS_FUCHSIA 1
#elif defined(__FreeBSD__)
#define OS_FREEBSD 1
#elif defined(__NetBSD__)
#define OS_NETBSD 1
#elif defined(__OpenBSD__)
#define OS_OPENBSD 1
#elif defined(__sun)
#define OS_SOLARIS 1
#elif defined(__QNXNTO__)
#define OS_QNX 1
// https://github.com/kwonoj/docker-pdfium-wasm/blob/master/patches/build_config.h.patch
//
// see https://github.com/google/xrtl/blob/master/xrtl/tools/target_platform/target_platform.h#L63
#if defined(__wasm32__)
#define ARCH_CPU_ARCH_WASM_32 1
#elif defined(__wasm64__)
#define ARCH_CPU_ARCH_WASM_64 1
#elif defined(__asmjs__)
#define ARCH_CPU_ARCH_ASMJS 1
#endif  // wasm/asmjs
//
#define OS_ASMJS 1
#elif defined(_AIX)
#define OS_AIX 1
#elif defined(__asmjs__)
#define OS_ASMJS
#else
#error Please add support for your platform in build/build_config.h
#endif
// NOTE: Adding a new port? Please follow
// https://chromium.googlesource.com/chromium/src/+/master/docs/new_port_policy.md

// For access to standard BSD features, use OS_BSD instead of a
// more specific macro.
#if defined(OS_FREEBSD) || defined(OS_NETBSD) || defined(OS_OPENBSD)
#define OS_BSD 1
#endif

// For access to standard POSIXish features, use OS_POSIX instead of a
// more specific macro.
#if defined(OS_AIX) || defined(OS_ANDROID) || defined(OS_ASMJS) ||    \
    defined(OS_FREEBSD) || defined(OS_LINUX) || defined(OS_MACOSX) || \
    defined(OS_NACL) || defined(OS_NETBSD) || defined(OS_OPENBSD) ||  \
    defined(OS_QNX) || defined(OS_SOLARIS) || defined(OS_EMSCRIPTEN)
#define OS_POSIX 1
#endif

// Use tcmalloc
#if (defined(OS_WIN) || defined(OS_LINUX) || defined(OS_ANDROID)) && \
    !defined(NO_TCMALLOC)
#define USE_TCMALLOC 1
#endif

// Compiler detection.
#if defined(__GNUC__)
#define COMPILER_GCC 1
#elif defined(_MSC_VER)
#define COMPILER_MSVC 1
#else
#error Please add support for your compiler in build/build_config.h
#endif

// Processor architecture detection.  For more info on what's defined, see:
//   http://msdn.microsoft.com/en-us/library/b0084kay.aspx
//   http://www.agner.org/optimize/calling_conventions.pdf
//   or with gcc, run: "echo | gcc -E -dM -"
#if defined(_M_X64) || defined(__x86_64__)
#define ARCH_CPU_X86_FAMILY 1
#define ARCH_CPU_X86_64 1
#define ARCH_CPU_64_BITS 1
#define ARCH_CPU_LITTLE_ENDIAN 1
#elif defined(EMSCRIPTEN) || defined(__EMSCRIPTEN__) || defined(OS_EMSCRIPTEN)
#define ARCH_CPU_JS 1
#define ARCH_CPU_32_BITS 1
#define ARCH_CPU_LITTLE_ENDIAN 1
#elif defined(_M_IX86) || defined(__i386__)
#define ARCH_CPU_X86_FAMILY 1
#define ARCH_CPU_X86 1
#define ARCH_CPU_32_BITS 1
#define ARCH_CPU_LITTLE_ENDIAN 1
#elif defined(__s390x__)
#define ARCH_CPU_S390_FAMILY 1
#define ARCH_CPU_S390X 1
#define ARCH_CPU_64_BITS 1
#define ARCH_CPU_BIG_ENDIAN 1
#elif defined(__s390__)
#define ARCH_CPU_S390_FAMILY 1
#define ARCH_CPU_S390 1
#define ARCH_CPU_31_BITS 1
#define ARCH_CPU_BIG_ENDIAN 1
#elif (defined(__PPC64__) || defined(__PPC__)) && defined(__BIG_ENDIAN__)
#define ARCH_CPU_PPC64_FAMILY 1
#define ARCH_CPU_PPC64 1
#define ARCH_CPU_64_BITS 1
#define ARCH_CPU_BIG_ENDIAN 1
#elif defined(__PPC64__)
#define ARCH_CPU_PPC64_FAMILY 1
#define ARCH_CPU_PPC64 1
#define ARCH_CPU_64_BITS 1
#define ARCH_CPU_LITTLE_ENDIAN 1
#elif defined(__ARMEL__)
#define ARCH_CPU_ARM_FAMILY 1
#define ARCH_CPU_ARMEL 1
#define ARCH_CPU_32_BITS 1
#define ARCH_CPU_LITTLE_ENDIAN 1
#elif defined(__aarch64__) || defined(_M_ARM64)
#define ARCH_CPU_ARM_FAMILY 1
#define ARCH_CPU_ARM64 1
#define ARCH_CPU_64_BITS 1
#define ARCH_CPU_LITTLE_ENDIAN 1
#elif defined(__pnacl__) || defined(__asmjs__)
#define ARCH_CPU_32_BITS 1
#define ARCH_CPU_LITTLE_ENDIAN 1
#elif defined(__MIPSEL__)
#if defined(__LP64__)
#define ARCH_CPU_MIPS_FAMILY 1
#define ARCH_CPU_MIPS64EL 1
#define ARCH_CPU_64_BITS 1
#define ARCH_CPU_LITTLE_ENDIAN 1
#else
#define ARCH_CPU_MIPS_FAMILY 1
#define ARCH_CPU_MIPSEL 1
#define ARCH_CPU_32_BITS 1
#define ARCH_CPU_LITTLE_ENDIAN 1
#endif
#elif defined(__MIPSEB__)
#if defined(__LP64__)
#define ARCH_CPU_MIPS_FAMILY 1
#define ARCH_CPU_MIPS64 1
#define ARCH_CPU_64_BITS 1
#define ARCH_CPU_BIG_ENDIAN 1
#else
#define ARCH_CPU_MIPS_FAMILY 1
#define ARCH_CPU_MIPS 1
#define ARCH_CPU_32_BITS 1
#define ARCH_CPU_BIG_ENDIAN 1
#endif
#else
#error Please add support for your architecture in build/build_config.h
#endif

// Type detection for wchar_t.
#if defined(OS_WIN)
#define WCHAR_T_IS_UTF16
#elif defined(OS_FUCHSIA)
#define WCHAR_T_IS_UTF32
#elif defined(OS_POSIX) && defined(COMPILER_GCC) && defined(__WCHAR_MAX__) && \
    (__WCHAR_MAX__ == 0x7fffffff || __WCHAR_MAX__ == 0xffffffff)
#define WCHAR_T_IS_UTF32
#elif defined(OS_POSIX) && defined(COMPILER_GCC) && defined(__WCHAR_MAX__) && \
    (__WCHAR_MAX__ == 0x7fff || __WCHAR_MAX__ == 0xffff)
// On Posix, we'll detect short wchar_t, but projects aren't guaranteed to
// compile in this mode (in particular, Chrome doesn't). This is intended for
// other projects using base who manage their own dependencies and make sure
// short wchar works for them.
#define WCHAR_T_IS_UTF16
#else
#error Please add support for your compiler in build/build_config.h
#endif

#if defined(OS_ANDROID)
// The compiler thinks std::string::const_iterator and "const char*" are
// equivalent types.
#define STD_STRING_ITERATOR_IS_CHAR_POINTER
// The compiler thinks base::string16::const_iterator and "char16*" are
// equivalent types.
#define BASE_STRING16_ITERATOR_IS_CHAR16_POINTER
#endif

#endif  // BUILD_BUILD_CONFIG_H_
