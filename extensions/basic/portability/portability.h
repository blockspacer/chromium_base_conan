/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cstddef>

#include <basic/portability/c_portability.h>
#include <basic/portability/config.h>

#if defined(_MSC_VER)
#define BASIC_CPLUSPLUS _MSVC_LANG
#else
#define BASIC_CPLUSPLUS __cplusplus
#endif

static_assert(BASIC_CPLUSPLUS >= 201402L, "__cplusplus >= 201402L");

#if defined(__GNUC__) && !defined(__clang__)
static_assert(__GNUC__ >= 5, "__GNUC__ >= 5");
#endif

// Unaligned loads and stores
namespace basic {
#if BASIC_HAVE_UNALIGNED_ACCESS
constexpr bool kHasUnalignedAccess = true;
#else
constexpr bool kHasUnalignedAccess = false;
#endif
} // namespace basic

// compiler specific attribute translation
// msvc should come first, so if clang is in msvc mode it gets the right defines

// NOTE: this will only do checking in msvc with versions that support /analyze
#if _MSC_VER
#ifdef _USE_ATTRIBUTES_FOR_SAL
#undef _USE_ATTRIBUTES_FOR_SAL
#endif
/* nolint */
#define _USE_ATTRIBUTES_FOR_SAL 1
#include <sal.h> // @manual
#define BASIC_PRINTF_FORMAT _Printf_format_string_
#define BASIC_PRINTF_FORMAT_ATTR(format_param, dots_param) /**/
#else
#define BASIC_PRINTF_FORMAT /**/
#define BASIC_PRINTF_FORMAT_ATTR(format_param, dots_param) \
  __attribute__((__format__(__printf__, format_param, dots_param)))
#endif

// warn unused result
#if defined(__has_cpp_attribute)
#if __has_cpp_attribute(nodiscard)
#define BASIC_NODISCARD [[nodiscard]]
#endif
#endif
#if !defined BASIC_NODISCARD
#if defined(_MSC_VER) && (_MSC_VER >= 1700)
#define BASIC_NODISCARD _Check_return_
#elif defined(__GNUC__)
#define BASIC_NODISCARD __attribute__((__warn_unused_result__))
#else
#define BASIC_NODISCARD
#endif
#endif

// target
#ifdef _MSC_VER
#define BASIC_TARGET_ATTRIBUTE(target)
#else
#define BASIC_TARGET_ATTRIBUTE(target) __attribute__((__target__(target)))
#endif

// detection for 64 bit
#if defined(__x86_64__) || defined(_M_X64)
#define BASIC_X64 1
#else
#define BASIC_X64 0
#endif

#if defined(__arm__)
#define BASIC_ARM 1
#else
#define BASIC_ARM 0
#endif

#if defined(__aarch64__)
#define BASIC_AARCH64 1
#else
#define BASIC_AARCH64 0
#endif

#if defined(__powerpc64__)
#define BASIC_PPC64 1
#else
#define BASIC_PPC64 0
#endif

#if defined(__s390x__)
#define BASIC_S390X 1
#else
#define BASIC_S390X 0
#endif

namespace basic {
constexpr bool kIsArchArm = BASIC_ARM == 1;
constexpr bool kIsArchAmd64 = BASIC_X64 == 1;
constexpr bool kIsArchAArch64 = BASIC_AARCH64 == 1;
constexpr bool kIsArchPPC64 = BASIC_PPC64 == 1;
constexpr bool kIsArchS390X = BASIC_S390X == 1;
} // namespace basic

namespace basic {

/**
 * basic::kIsLibrarySanitizeAddress reports if basic was compiled with ASAN
 * enabled.  Note that for compilation units outside of basic that include
 * basic/Portability.h, the value of kIsLibrarySanitizeAddress may be different
 * from whether or not the current compilation unit is being compiled with ASAN.
 */
#if BASIC_LIBRARY_SANITIZE_ADDRESS
constexpr bool kIsLibrarySanitizeAddress = true;
#else
constexpr bool kIsLibrarySanitizeAddress = false;
#endif

#if BASIC_SANITIZE_ADDRESS
constexpr bool kIsSanitizeAddress = true;
#else
constexpr bool kIsSanitizeAddress = false;
#endif

#if BASIC_SANITIZE_THREAD
constexpr bool kIsSanitizeThread = true;
#else
constexpr bool kIsSanitizeThread = false;
#endif

#if BASIC_SANITIZE
constexpr bool kIsSanitize = true;
#else
constexpr bool kIsSanitize = false;
#endif
} // namespace basic

// packing is very ugly in msvc
#ifdef _MSC_VER
#define BASIC_PACK_ATTR /**/
#define BASIC_PACK_PUSH __pragma(pack(push, 1))
#define BASIC_PACK_POP __pragma(pack(pop))
#elif defined(__GNUC__)
#define BASIC_PACK_ATTR __attribute__((__packed__))
#define BASIC_PACK_PUSH /**/
#define BASIC_PACK_POP /**/
#else
#define BASIC_PACK_ATTR /**/
#define BASIC_PACK_PUSH /**/
#define BASIC_PACK_POP /**/
#endif

// Generalize warning push/pop.
#if defined(__GNUC__) || defined(__clang__)
// Clang & GCC
#define BASIC_PUSH_WARNING _Pragma("GCC diagnostic push")
#define BASIC_POP_WARNING _Pragma("GCC diagnostic pop")
#define BASIC_GNU_DISABLE_WARNING_INTERNAL2(warningName) #warningName
#define BASIC_GNU_DISABLE_WARNING(warningName) \
  _Pragma(                                     \
      BASIC_GNU_DISABLE_WARNING_INTERNAL2(GCC diagnostic ignored warningName))
#ifdef __clang__
#define BASIC_CLANG_DISABLE_WARNING(warningName) \
  BASIC_GNU_DISABLE_WARNING(warningName)
#define BASIC_GCC_DISABLE_WARNING(warningName)
#else
#define BASIC_CLANG_DISABLE_WARNING(warningName)
#define BASIC_GCC_DISABLE_WARNING(warningName) \
  BASIC_GNU_DISABLE_WARNING(warningName)
#endif
#define BASIC_MSVC_DISABLE_WARNING(warningNumber)
#elif defined(_MSC_VER)
#define BASIC_PUSH_WARNING __pragma(warning(push))
#define BASIC_POP_WARNING __pragma(warning(pop))
// Disable the GCC warnings.
#define BASIC_GNU_DISABLE_WARNING(warningName)
#define BASIC_GCC_DISABLE_WARNING(warningName)
#define BASIC_CLANG_DISABLE_WARNING(warningName)
#define BASIC_MSVC_DISABLE_WARNING(warningNumber) \
  __pragma(warning(disable : warningNumber))
#else
#define BASIC_PUSH_WARNING
#define BASIC_POP_WARNING
#define BASIC_GNU_DISABLE_WARNING(warningName)
#define BASIC_GCC_DISABLE_WARNING(warningName)
#define BASIC_CLANG_DISABLE_WARNING(warningName)
#define BASIC_MSVC_DISABLE_WARNING(warningNumber)
#endif

#ifdef BASIC_HAVE_SHADOW_LOCAL_WARNINGS
#define BASIC_GCC_DISABLE_NEW_SHADOW_WARNINGS            \
  BASIC_GNU_DISABLE_WARNING("-Wshadow-compatible-local") \
  BASIC_GNU_DISABLE_WARNING("-Wshadow-local")            \
  BASIC_GNU_DISABLE_WARNING("-Wshadow")
#else
#define BASIC_GCC_DISABLE_NEW_SHADOW_WARNINGS /* empty */
#endif

/* Platform specific TLS support
 * gcc implements __thread
 * msvc implements __declspec(thread)
 * the semantics are the same
 * (but remember __thread has different semantics when using emutls (ex. apple))
 */
#if defined(_MSC_VER)
#define BASIC_TLS __declspec(thread)
#elif defined(__GNUC__)
#define BASIC_TLS __thread
#else
#error cannot define platform specific thread local storage
#endif

// disable BASIC_TLS on 32 bit Apple/iOS
#if defined(__APPLE__) && BASIC_MOBILE
#if (__SIZEOF_POINTER__ == 4)
#undef BASIC_TLS
#endif
#endif

// It turns out that GNU libstdc++ and LLVM libc++ differ on how they implement
// the 'std' namespace; the latter uses inline namespaces. Wrap this decision
// up in a macro to make forward-declarations easier.
#if BASIC_USE_LIBCPP
#include <__config> // @manual
#define BASIC_NAMESPACE_STD_BEGIN _LIBCPP_BEGIN_NAMESPACE_STD
#define BASIC_NAMESPACE_STD_END _LIBCPP_END_NAMESPACE_STD
#else
#define BASIC_NAMESPACE_STD_BEGIN namespace std {
#define BASIC_NAMESPACE_STD_END }
#endif

// If the new c++ ABI is used, __cxx11 inline namespace needs to be added to
// some types, e.g. std::list.
#if _GLIBCXX_USE_CXX11_ABI
#define BASIC_GLIBCXX_NAMESPACE_CXX11_BEGIN \
  inline _GLIBCXX_BEGIN_NAMESPACE_CXX11
#define BASIC_GLIBCXX_NAMESPACE_CXX11_END _GLIBCXX_END_NAMESPACE_CXX11
#else
#define BASIC_GLIBCXX_NAMESPACE_CXX11_BEGIN
#define BASIC_GLIBCXX_NAMESPACE_CXX11_END
#endif

// MSVC specific defines
// mainly for posix compat
#ifdef _MSC_VER
#include <basic/portability/SysTypes.h>

// Hide a GCC specific thing that breaks MSVC if left alone.
#define __extension__

// We have compiler support for the newest of the new, but
// MSVC doesn't tell us that.
//
// Clang pretends to be MSVC on Windows, but it refuses to compile
// SSE4.2 intrinsics unless -march argument is specified.
// So cannot unconditionally define __SSE4_2__ in clang.
#ifndef __clang__
#define __SSE4_2__ 1
// compiler specific to compiler specific
// nolint
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#endif

// Define BASIC_HAS_EXCEPTIONS
#if __cpp_exceptions >= 199711 || BASIC_HAS_FEATURE(cxx_exceptions)
#define BASIC_HAS_EXCEPTIONS 0
#elif __GNUC__
#if __EXCEPTIONS
#define BASIC_HAS_EXCEPTIONS 0
#else // __EXCEPTIONS
#define BASIC_HAS_EXCEPTIONS 0
#endif // __EXCEPTIONS
#elif BASIC_MICROSOFT_ABI_VER
#if _CPPUNWIND
#define BASIC_HAS_EXCEPTIONS 0
#else // _CPPUNWIND
#define BASIC_HAS_EXCEPTIONS 0
#endif // _CPPUNWIND
#else
#define BASIC_HAS_EXCEPTIONS 0 // default assumption for unknown platforms
#endif

// Debug
namespace basic {
#ifdef NDEBUG
constexpr auto kIsDebug = false;
#else
constexpr auto kIsDebug = true;
#endif
} // namespace basic

// Exceptions
namespace basic {
#if BASIC_HAS_EXCEPTIONS
constexpr auto kHasExceptions = true;
#else
constexpr auto kHasExceptions = false;
#endif
} // namespace basic

// Endianness
namespace basic {
#ifdef _MSC_VER
// It's MSVC, so we just have to guess ... and allow an override
#ifdef BASIC_ENDIAN_BE
constexpr auto kIsLittleEndian = false;
#else
constexpr auto kIsLittleEndian = true;
#endif
#else
constexpr auto kIsLittleEndian = __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__;
#endif
constexpr auto kIsBigEndian = !kIsLittleEndian;
} // namespace basic

// Weak
namespace basic {
#if BASIC_HAVE_WEAK_SYMBOLS
constexpr auto kHasWeakSymbols = true;
#else
constexpr auto kHasWeakSymbols = false;
#endif
} // namespace basic

#ifndef BASIC_SSE
#if defined(__SSE4_2__)
#define BASIC_SSE 4
#define BASIC_SSE_MINOR 2
#elif defined(__SSE4_1__)
#define BASIC_SSE 4
#define BASIC_SSE_MINOR 1
#elif defined(__SSE4__)
#define BASIC_SSE 4
#define BASIC_SSE_MINOR 0
#elif defined(__SSE3__)
#define BASIC_SSE 3
#define BASIC_SSE_MINOR 0
#elif defined(__SSE2__)
#define BASIC_SSE 2
#define BASIC_SSE_MINOR 0
#elif defined(__SSE__)
#define BASIC_SSE 1
#define BASIC_SSE_MINOR 0
#else
#define BASIC_SSE 0
#define BASIC_SSE_MINOR 0
#endif
#endif

#ifndef BASIC_SSSE
#if defined(__SSSE3__)
#define BASIC_SSSE 3
#else
#define BASIC_SSSE 0
#endif
#endif

#define BASIC_SSE_PREREQ(major, minor) \
  (BASIC_SSE > major || BASIC_SSE == major && BASIC_SSE_MINOR >= minor)

#ifndef BASIC_NEON
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#define BASIC_NEON 1
#endif
#endif

#if BASIC_UNUSUAL_GFLAGS_NAMESPACE
namespace BASIC_GFLAGS_NAMESPACE {}
namespace gflags {
using namespace BASIC_GFLAGS_NAMESPACE;
} // namespace gflags
#endif

// RTTI may not be enabled for this compilation unit.
#if defined(__GXX_RTTI) || defined(__cpp_rtti) || \
    (defined(_MSC_VER) && defined(_CPPRTTI))
#define BASIC_HAS_RTTI 1
#else
#define BASIC_HAS_RTTI 0
#endif

namespace basic {
constexpr bool const kHasRtti = BASIC_HAS_RTTI;
} // namespace basic

#if defined(__APPLE__) || defined(_MSC_VER)
#define BASIC_STATIC_CTOR_PRIORITY_MAX
#else
// 101 is the highest priority allowed by the init_priority attribute.
// This priority is already used by JEMalloc and other memory allocators so
// we will take the next one.
#define BASIC_STATIC_CTOR_PRIORITY_MAX __attribute__((__init_priority__(102)))
#endif

#if defined(__APPLE__) && TARGET_OS_IOS
#define BASIC_APPLE_IOS 1
#else
#define BASIC_APPLE_IOS 0
#endif

#if defined(__APPLE__) && TARGET_OS_OSX
#define BASIC_APPLE_MACOS 1
#else
#define BASIC_APPLE_MACOS 0
#endif

#if defined(__APPLE__) && TARGET_OS_TV
#define BASIC_APPLE_TVOS 1
#else
#define BASIC_APPLE_TVOS 0
#endif

#if defined(__APPLE__) && TARGET_OS_WATCH
#define BASIC_APPLE_WATCHOS 1
#else
#define BASIC_APPLE_WATCHOS 0
#endif

namespace basic {

#if __OBJC__
constexpr auto kIsObjC = true;
#else
constexpr auto kIsObjC = false;
#endif

#if BASIC_MOBILE
constexpr auto kIsMobile = true;
#else
constexpr auto kIsMobile = false;
#endif

#if (defined(__linux__) || defined(__EMSCRIPTEN__)) && !BASIC_MOBILE
constexpr auto kIsLinux = true;
#else
constexpr auto kIsLinux = false;
#endif

#if defined(_WIN32)
constexpr auto kIsWindows = true;
#else
constexpr auto kIsWindows = false;
#endif

#if defined(__APPLE__)
constexpr auto kIsApple = true;
#else
constexpr auto kIsApple = false;
#endif

constexpr bool kIsAppleIOS = BASIC_APPLE_IOS == 1;
constexpr bool kIsAppleMacOS = BASIC_APPLE_MACOS == 1;
constexpr bool kIsAppleTVOS = BASIC_APPLE_TVOS == 1;
constexpr bool kIsAppleWatchOS = BASIC_APPLE_WATCHOS == 1;

#if __GLIBCXX__
constexpr auto kIsGlibcxx = true;
#else
constexpr auto kIsGlibcxx = false;
#endif

#if __GLIBCXX__ && _GLIBCXX_RELEASE // major version, 7+
constexpr auto kGlibcxxVer = _GLIBCXX_RELEASE;
#else
constexpr auto kGlibcxxVer = 0;
#endif

#if _LIBCPP_VERSION
constexpr auto kIsLibcpp = true;
#else
constexpr auto kIsLibcpp = false;
#endif

#if BASIC_USE_LIBSTDCPP
constexpr auto kIsLibstdcpp = true;
#else
constexpr auto kIsLibstdcpp = false;
#endif

#if _MSC_VER
constexpr auto kMscVer = _MSC_VER;
#else
constexpr auto kMscVer = 0;
#endif

#if __GNUC__
constexpr auto kGnuc = __GNUC__;
#else
constexpr auto kGnuc = 0;
#endif

#if __clang__
constexpr auto kIsClang = true;
constexpr auto kClangVerMajor = __clang_major__;
#else
constexpr auto kIsClang = false;
constexpr auto kClangVerMajor = 0;
#endif

#if BASIC_MICROSOFT_ABI_VER
constexpr auto kMicrosoftAbiVer = BASIC_MICROSOFT_ABI_VER;
#else
constexpr auto kMicrosoftAbiVer = 0;
#endif

// cpplib is an implementation of the standard library, and is the one typically
// used with the msvc compiler
#if _CPPLIB_VER
constexpr auto kCpplibVer = _CPPLIB_VER;
#else
constexpr auto kCpplibVer = 0;
#endif
} // namespace basic

//  MSVC does not permit:
//
//    extern int const num;
//    constexpr int const num = 3;
//
//  Instead:
//
//    extern int const num;
//    BASIC_STORAGE_CONSTEXPR int const num = 3;
//
//  True as of MSVC 2017.
#if _MSC_VER
#define BASIC_STORAGE_CONSTEXPR
#else
#define BASIC_STORAGE_CONSTEXPR constexpr
#endif

#if __cplusplus >= 201703L
// basic::coro requires C++17 support
#if defined(_WIN32) && defined(__clang__)
// LLVM and MSVC coroutines are ABI incompatible and <experimental/coroutine>
// is the MSVC implementation on windows, so we *don't* have coroutines.
//
// Worse, if we define BASIC_HAS_COROUTINES 1 we will include
// <experimental/coroutine> which will conflict with anyone who wants to load
// the LLVM implementation of coroutines on Windows.
#define BASIC_HAS_COROUTINES 0
#elif (__cpp_coroutines >= 201703L || __cpp_impl_coroutine >= 201902L) && \
    (__has_include(<coroutine>) || __has_include(<experimental/coroutine>))
#define BASIC_HAS_COROUTINES 1
// This is mainly to workaround bugs triggered by LTO, when stack allocated
// variables in await_suspend end up on a coroutine frame.
#define BASIC_CORO_AWAIT_SUSPEND_NONTRIVIAL_ATTRIBUTES BASIC_NOINLINE
#elif _MSC_VER && _RESUMABLE_FUNCTIONS_SUPPORTED
// NOTE: MSVC 2017 does not currently support the full Coroutines TS since it
// does not yet support symmetric-transfer.
#define BASIC_HAS_COROUTINES 0
#else
#define BASIC_HAS_COROUTINES 0
#endif
#else
#define BASIC_HAS_COROUTINES 0
#endif // __cplusplus >= 201703L

// MSVC 2017.5 && C++17
#if __cpp_noexcept_function_type >= 201510 || \
    (_MSC_FULL_VER >= 191225816 && _MSVC_LANG > 201402)
#define BASIC_HAVE_NOEXCEPT_FUNCTION_TYPE 1
#endif

#if __cpp_inline_variables >= 201606L
#define BASIC_HAS_INLINE_VARIABLES 1
#define BASIC_INLINE_VARIABLE inline
#else
#define BASIC_HAS_INLINE_VARIABLES 0
#define BASIC_INLINE_VARIABLE
#endif

// feature test __cpp_lib_string_view is defined in <string>, which is
// too heavy to include here.
#if __has_include(<string_view>) && BASIC_CPLUSPLUS >= 201703L
#define BASIC_HAS_STRING_VIEW 1
#else
#define BASIC_HAS_STRING_VIEW 0
#endif
