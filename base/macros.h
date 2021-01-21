// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file contains macros and macro-like constructs (e.g., templates) that
// are commonly used throughout Chromium source. (It may also contain things
// that are closely related to things that are commonly used that belong in this
// file.)

// Related files that contain macros:
// cobalt/base/basictypes.h
// base/logging.h
// base/compiler_specific.h

#pragma once

/// \note Do NOT include other files here, even if some macros
/// depend on that files
/// (i.e. user must include all required files manually).
/// \note `<cstddef>` is exception to rule above
#include <cstddef>  // For size_t.

#define DELETE_FUNCTION(decl) \
  decl = delete

// Put this in the declarations for a class to be uncopyable.
#define DISALLOW_COPY(TypeName) \
  DELETE_FUNCTION(TypeName(const TypeName&))

// Put this in the declarations for a class to be unassignable.
#define DISALLOW_ASSIGN(TypeName) \
  DELETE_FUNCTION(TypeName& operator=(const TypeName&))

// Put this in the declarations for a class to be uncopyable and unassignable.
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  DISALLOW_COPY(TypeName);                 \
  DISALLOW_ASSIGN(TypeName)

// A macro to disallow all the implicit constructors, namely the
// default constructor, copy constructor and operator= functions.
// This is especially useful for classes containing only static methods.
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  DELETE_FUNCTION(TypeName());                   \
  DISALLOW_COPY_AND_ASSIGN(TypeName)

// Macro used to simplify the task of deleting the new and new[]
// operators i.e, disallow heap allocations.
/// \note accepts |ClassName| argument
/// for documentation purposes and to avoid copy-n-paste errors
#define DISALLOW_NEW_OPERATOR(ClassName)                         \
  DELETE_FUNCTION(static void* operator new(size_t));            \
  DELETE_FUNCTION(static void* operator new[](size_t))

#define DEFAULT_CONSTRUCTOR(ClassName) \
  ClassName() = default;

#define DEFAULT_COPY(ClassName)                                 \
  ClassName(const ClassName &rhs) = default;                    \
  ClassName &operator=(const ClassName &rhs) = default;         \
  /* Fails during compile-time if default-copy can not work. */ \
  static void COPYABLE_DEMAND_COPY_CAN_COMPILE() {              \
    (void) static_cast<ClassName& (ClassName::*)(               \
        const ClassName&)>(&ClassName::operator=);              \
  }

#define DEFAULT_MOVE(ClassName)                             \
  ClassName(ClassName &&rhs) = default;            \
  ClassName &operator=(ClassName &&rhs) = default;

#define DEFAULT_COPY_AND_MOVE(ClassName)                \
  DEFAULT_COPY(ClassName)                               \
  DEFAULT_MOVE(ClassName)

/// \note Use `UNREFERENCED_PARAMETER(x)` for ignoring function parameter.
/// \note Use `ignore_result(x)` for ignoring result of function call.
/// \note Use `ALLOW_UNUSED_LOCAL(x)` for ignoring local variable.
//
// Used to explicitly mark the return value of a function as unused. If you are
// really sure you don't want to do anything with the return value of a function
// that has been marked WARN_UNUSED_RESULT, wrap it with this. Example:
//
//   std::unique_ptr<MyType> my_var = ...;
//   if (TakeOwnership(my_var.get()) == SUCCESS)
//     ignore_result(my_var.release());
//
template<typename T>
inline void ignore_result(const T&) {
}

// C++11 supports compile-time assertion directly
//
// USAGE
//
// CT_ASSERT(sizeof(T) > 0, T_is_empty);
//
#define CT_ASSERT(expr, msg) static_assert(expr, #msg)

// BASE_HAVE_BUILTIN()
//
// Checks whether the compiler supports a Clang Feature Checking Macro, and if
// so, checks whether it supports the provided builtin function "x" where x
// is one of the functions noted in
// https://clang.llvm.org/docs/LanguageExtensions.html
//
// Note: Use this macro to avoid an extra level of #ifdef __has_builtin check.
// http://releases.llvm.org/3.3/tools/clang/docs/LanguageExtensions.html
#ifdef __has_builtin
#define BASE_HAVE_BUILTIN(x) __has_builtin(x)
#else
#define BASE_HAVE_BUILTIN(x) 0
#endif

#if defined(__is_identifier)
#define BASE_HAS_KEYWORD(x) !(__is_identifier(x))
#else
#define BASE_HAS_KEYWORD(x) 0
#endif

// BASE_HAVE_TLS is defined to 1 when __thread should be supported.
// We assume __thread is supported on Linux when compiled with Clang or compiled
// against libstdc++ with _GLIBCXX_HAVE_TLS defined.
#ifdef BASE_HAVE_TLS
#error BASE_HAVE_TLS cannot be directly set
#elif defined(__linux__) && (defined(__clang__) || defined(_GLIBCXX_HAVE_TLS))
#define BASE_HAVE_TLS 1
#endif

// BASE_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE
//
// Checks whether `std::is_trivially_destructible<T>` is supported.
//
// Notes: All supported compilers using libc++ support this feature, as does
// gcc >= 4.8.1 using libstdc++, and Visual Studio.
#ifdef BASE_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE
#error BASE_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE cannot be directly set
#elif defined(_LIBCPP_VERSION) ||                                        \
    (!defined(__clang__) && defined(__GNUC__) && defined(__GLIBCXX__) && \
     (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8))) ||        \
    defined(_MSC_VER)
#define BASE_HAVE_STD_IS_TRIVIALLY_DESTRUCTIBLE 1
#endif

// BASE_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE
//
// Checks whether `std::is_trivially_default_constructible<T>` and
// `std::is_trivially_copy_constructible<T>` are supported.

// BASE_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE
//
// Checks whether `std::is_trivially_copy_assignable<T>` is supported.

// Notes: Clang with libc++ supports these features, as does gcc >= 5.1 with
// either libc++ or libstdc++, and Visual Studio (but not NVCC).
#if defined(BASE_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE)
#error BASE_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE cannot be directly set
#elif defined(BASE_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE)
#error BASE_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE cannot directly set
#elif (defined(__clang__) && defined(_LIBCPP_VERSION)) ||        \
    (!defined(__clang__) && defined(__GNUC__) &&                 \
     (__GNUC__ > 7 || (__GNUC__ == 7 && __GNUC_MINOR__ >= 4)) && \
     (defined(_LIBCPP_VERSION) || defined(__GLIBCXX__))) ||      \
    (defined(_MSC_VER) && !defined(__NVCC__))
#define BASE_HAVE_STD_IS_TRIVIALLY_CONSTRUCTIBLE 1
#define BASE_HAVE_STD_IS_TRIVIALLY_ASSIGNABLE 1
#endif

// BASE_HAVE_SOURCE_LOCATION_CURRENT
//
// Indicates whether `base::SourceLocation::current()` will return useful
// information in some contexts.
#ifndef BASE_HAVE_SOURCE_LOCATION_CURRENT
#if BASE_HAS_KEYWORD(__builtin_LINE) && \
    BASE_HAS_KEYWORD(__builtin_FILE)
#define BASE_HAVE_SOURCE_LOCATION_CURRENT 1
#endif
#endif

// BASE_HAVE_THREAD_LOCAL
//
// Checks whether C++11's `thread_local` storage duration specifier is
// supported.
#ifdef BASE_HAVE_THREAD_LOCAL
#error BASE_HAVE_THREAD_LOCAL cannot be directly set
#elif defined(__APPLE__)
// Notes:
// * Xcode's clang did not support `thread_local` until version 8, and
//   even then not for all iOS < 9.0.
// * Xcode 9.3 started disallowing `thread_local` for 32-bit iOS simulator
//   targeting iOS 9.x.
// * Xcode 10 moves the deployment target check for iOS < 9.0 to link time
//   making __has_feature unreliable there.
//
// Otherwise, `__has_feature` is only supported by Clang so it has be inside
// `defined(__APPLE__)` check.
#if __has_feature(cxx_thread_local) && \
    !(TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_9_0)
#define BASE_HAVE_THREAD_LOCAL 1
#endif
#else  // !defined(__APPLE__)
#define BASE_HAVE_THREAD_LOCAL 1
#endif

// There are platforms for which TLS should not be used even though the compiler
// makes it seem like it's supported (Android NDK < r12b for example).
// This is primarily because of linker problems and toolchain misconfiguration:
// Abseil does not intend to support this indefinitely. Currently, the newest
// toolchain that we intend to support that requires this behavior is the
// r11 NDK - allowing for a 5 year support window on that means this option
// is likely to be removed around June of 2021.
// TLS isn't supported until NDK r12b per
// https://developer.android.com/ndk/downloads/revision_history.html
// Since NDK r16, `__NDK_MAJOR__` and `__NDK_MINOR__` are defined in
// <android/ndk-version.h>. For NDK < r16, users should define these macros,
// e.g. `-D__NDK_MAJOR__=11 -D__NKD_MINOR__=0` for NDK r11.
#if defined(__ANDROID__) && defined(__clang__)
#if __has_include(<android/ndk-version.h>)
#include <android/ndk-version.h>
#endif  // __has_include(<android/ndk-version.h>)
#if defined(__ANDROID__) && defined(__clang__) && defined(__NDK_MAJOR__) && \
    defined(__NDK_MINOR__) &&                                               \
    ((__NDK_MAJOR__ < 12) || ((__NDK_MAJOR__ == 12) && (__NDK_MINOR__ < 1)))
#undef BASE_HAVE_TLS
#undef BASE_HAVE_THREAD_LOCAL
#endif
#endif  // defined(__ANDROID__) && defined(__clang__)

// BASE_HAVE_INTRINSIC_INT128
//
// Checks whether the __int128 compiler extension for a 128-bit integral type is
// supported.
//
// Note: __SIZEOF_INT128__ is defined by Clang and GCC when __int128 is
// supported, but we avoid using it in certain cases:
// * On Clang:
//   * Building using Clang for Windows, where the Clang runtime library has
//     128-bit support only on LP64 architectures, but Windows is LLP64.
// * On Nvidia's nvcc:
//   * nvcc also defines __GNUC__ and __SIZEOF_INT128__, but not all versions
//     actually support __int128.
#ifdef BASE_HAVE_INTRINSIC_INT128
#error BASE_HAVE_INTRINSIC_INT128 cannot be directly set
#elif defined(__SIZEOF_INT128__)
#if (defined(__clang__) && !defined(_WIN32)) || \
    (defined(__CUDACC__) && __CUDACC_VER_MAJOR__ >= 9) ||                \
    (defined(__GNUC__) && !defined(__clang__) && !defined(__CUDACC__))
#define BASE_HAVE_INTRINSIC_INT128 1
#elif defined(__CUDACC__)
// __CUDACC_VER__ is a full version number before CUDA 9, and is defined to a
// string explaining that it has been removed starting with CUDA 9. We use
// nested #ifs because there is no short-circuiting in the preprocessor.
// NOTE: `__CUDACC__` could be undefined while `__CUDACC_VER__` is defined.
#if __CUDACC_VER__ >= 70000
#define BASE_HAVE_INTRINSIC_INT128 1
#endif  // __CUDACC_VER__ >= 70000
#endif  // defined(__CUDACC__)
#endif  // BASE_HAVE_INTRINSIC_INT128

// BASE_HAVE_EXCEPTIONS
//
// Checks whether the compiler both supports and enables exceptions. Many
// compilers support a "no exceptions" mode that disables exceptions.
//
// Generally, when BASE_HAVE_EXCEPTIONS is not defined:
//
// * Code using `throw` and `try` may not compile.
// * The `noexcept` specifier will still compile and behave as normal.
// * The `noexcept` operator may still return `false`.
//
// For further details, consult the compiler's documentation.
#ifdef BASE_HAVE_EXCEPTIONS
#error BASE_HAVE_EXCEPTIONS cannot be directly set.

#elif defined(__clang__)

#if __clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 6)
// Clang >= 3.6
#if __has_feature(cxx_exceptions)
#define BASE_HAVE_EXCEPTIONS 1
#endif  // __has_feature(cxx_exceptions)
#else
// Clang < 3.6
// http://releases.llvm.org/3.6.0/tools/clang/docs/ReleaseNotes.html#the-exceptions-macro
#if defined(__EXCEPTIONS) && __has_feature(cxx_exceptions)
#define BASE_HAVE_EXCEPTIONS 1
#endif  // defined(__EXCEPTIONS) && __has_feature(cxx_exceptions)
#endif  // __clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 6)

// Handle remaining special cases and default to exceptions being supported.
#elif !(defined(__GNUC__) && (__GNUC__ < 5) && !defined(__EXCEPTIONS)) &&    \
    !(defined(__GNUC__) && (__GNUC__ >= 5) && !defined(__cpp_exceptions)) && \
    !(defined(_MSC_VER) && !defined(_CPPUNWIND))
#define BASE_HAVE_EXCEPTIONS 1
#endif

// Platform Feature Checks
//
// Currently supported operating systems and associated preprocessor
// symbols:
//
//   Linux and Linux-derived           __linux__
//   Android                           __ANDROID__ (implies __linux__)
//   Linux (non-Android)               __linux__ && !__ANDROID__
//   Darwin (macOS and iOS)            __APPLE__
//   Akaros (http://akaros.org)        __ros__
//   Windows                           _WIN32
//   NaCL                              __native_client__
//   AsmJS                             __asmjs__
//   WebAssembly                       __wasm__
//   Fuchsia                           __Fuchsia__
//
// Note that since Android defines both __ANDROID__ and __linux__, one
// may probe for either Linux or Android by simply testing for __linux__.

// BASE_HAVE_MMAP
//
// Checks whether the platform has an mmap(2) implementation as defined in
// POSIX.1-2001.
#ifdef BASE_HAVE_MMAP
#error BASE_HAVE_MMAP cannot be directly set
#elif defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) ||   \
    defined(__ros__) || defined(__native_client__) || defined(__asmjs__) || \
    defined(__wasm__) || defined(__Fuchsia__) || defined(__sun) || \
    defined(__ASYLO__)
#define BASE_HAVE_MMAP 1
#endif

// BASE_HAVE_PTHREAD_GETSCHEDPARAM
//
// Checks whether the platform implements the pthread_(get|set)schedparam(3)
// functions as defined in POSIX.1-2001.
#ifdef BASE_HAVE_PTHREAD_GETSCHEDPARAM
#error BASE_HAVE_PTHREAD_GETSCHEDPARAM cannot be directly set
#elif defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) || \
    defined(__ros__)
#define BASE_HAVE_PTHREAD_GETSCHEDPARAM 1
#endif

// BASE_HAVE_SCHED_YIELD
//
// Checks whether the platform implements sched_yield(2) as defined in
// POSIX.1-2001.
#ifdef BASE_HAVE_SCHED_YIELD
#error BASE_HAVE_SCHED_YIELD cannot be directly set
#elif defined(__linux__) || defined(__ros__) || defined(__native_client__)
#define BASE_HAVE_SCHED_YIELD 1
#endif

// BASE_HAVE_SEMAPHORE_H
//
// Checks whether the platform supports the <semaphore.h> header and sem_init(3)
// family of functions as standardized in POSIX.1-2001.
//
// Note: While Apple provides <semaphore.h> for both iOS and macOS, it is
// explicitly deprecated and will cause build failures if enabled for those
// platforms.  We side-step the issue by not defining it here for Apple
// platforms.
#ifdef BASE_HAVE_SEMAPHORE_H
#error BASE_HAVE_SEMAPHORE_H cannot be directly set
#elif defined(__linux__) || defined(__ros__)
#define BASE_HAVE_SEMAPHORE_H 1
#endif

// BASE_HAVE_ALARM
//
// Checks whether the platform supports the <signal.h> header and alarm(2)
// function as standardized in POSIX.1-2001.
#ifdef BASE_HAVE_ALARM
#error BASE_HAVE_ALARM cannot be directly set
#elif defined(__GOOGLE_GRTE_VERSION__)
// feature tests for Google's GRTE
#define BASE_HAVE_ALARM 1
#elif defined(__GLIBC__)
// feature test for glibc
#define BASE_HAVE_ALARM 1
#elif defined(_MSC_VER)
// feature tests for Microsoft's library
#elif defined(__MINGW32__)
// mingw32 doesn't provide alarm(2):
// https://osdn.net/projects/mingw/scm/git/mingw-org-wsl/blobs/5.2-trunk/mingwrt/include/unistd.h
// mingw-w64 provides a no-op implementation:
// https://sourceforge.net/p/mingw-w64/mingw-w64/ci/master/tree/mingw-w64-crt/misc/alarm.c
#elif defined(__EMSCRIPTEN__)
// emscripten doesn't support signals
#elif defined(__Fuchsia__)
// Signals don't exist on fuchsia.
#elif defined(__native_client__)
#else
// other standard libraries
#define BASE_HAVE_ALARM 1
#endif

// BASE_IS_LITTLE_ENDIAN
// BASE_IS_BIG_ENDIAN
//
// Checks the endianness of the platform.
//
// Notes: uses the built in endian macros provided by GCC (since 4.6) and
// Clang (since 3.2); see
// https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html.
// Otherwise, if _WIN32, assume little endian. Otherwise, bail with an error.
#if defined(BASE_IS_BIG_ENDIAN)
#error "BASE_IS_BIG_ENDIAN cannot be directly set."
#endif
#if defined(BASE_IS_LITTLE_ENDIAN)
#error "BASE_IS_LITTLE_ENDIAN cannot be directly set."
#endif

#if (defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && \
     __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define BASE_IS_LITTLE_ENDIAN 1
#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && \
    __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define BASE_IS_BIG_ENDIAN 1
#elif defined(_WIN32)
#define BASE_IS_LITTLE_ENDIAN 1
#else
#error "endian detection needs to be set up for your compiler"
#endif

// macOS 10.13 and iOS 10.11 don't let you use <any>, <optional>, or <variant>
// even though the headers exist and are publicly noted to work.  See
// https://github.com/abseil/abseil-cpp/issues/207 and
// https://developer.apple.com/documentation/xcode_release_notes/xcode_10_release_notes
// libc++ spells out the availability requirements in the file
// llvm-project/libcxx/include/__config via the #define
// _LIBCPP_AVAILABILITY_BAD_OPTIONAL_ACCESS.
#if defined(__APPLE__) && defined(_LIBCPP_VERSION) && \
  ((defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && \
   __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 101400) || \
  (defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) && \
   __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ < 120000) || \
  (defined(__ENVIRONMENT_WATCH_OS_VERSION_MIN_REQUIRED__) && \
   __ENVIRONMENT_WATCH_OS_VERSION_MIN_REQUIRED__ < 120000) || \
  (defined(__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__) && \
   __ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__ < 50000))
#define BASE_INTERNAL_APPLE_CXX17_TYPES_UNAVAILABLE 1
#else
#define BASE_INTERNAL_APPLE_CXX17_TYPES_UNAVAILABLE 0
#endif

// BASE_HAVE_STD_ANY
//
// Checks whether C++17 std::any is available by checking whether <any> exists.
#ifdef BASE_HAVE_STD_ANY
#error "BASE_HAVE_STD_ANY cannot be directly set."
#endif

#ifdef __has_include
#if __has_include(<any>) && __cplusplus >= 201703L && \
    !BASE_INTERNAL_APPLE_CXX17_TYPES_UNAVAILABLE
#define BASE_HAVE_STD_ANY 1
#endif
#endif

// BASE_HAVE_STD_OPTIONAL
//
// Checks whether C++17 std::optional is available.
#ifdef BASE_HAVE_STD_OPTIONAL
#error "BASE_HAVE_STD_OPTIONAL cannot be directly set."
#endif

#ifdef __has_include
#if __has_include(<optional>) && __cplusplus >= 201703L && \
    !BASE_INTERNAL_APPLE_CXX17_TYPES_UNAVAILABLE
#define BASE_HAVE_STD_OPTIONAL 1
#endif
#endif

// BASE_HAVE_STD_VARIANT
//
// Checks whether C++17 std::variant is available.
#ifdef BASE_HAVE_STD_VARIANT
#error "BASE_HAVE_STD_VARIANT cannot be directly set."
#endif

#ifdef __has_include
#if __has_include(<variant>) && __cplusplus >= 201703L && \
    !BASE_INTERNAL_APPLE_CXX17_TYPES_UNAVAILABLE
#define BASE_HAVE_STD_VARIANT 1
#endif
#endif

// BASE_HAVE_STD_STRING_VIEW
//
// Checks whether C++17 std::string_view is available.
#ifdef BASE_HAVE_STD_STRING_VIEW
#error "BASE_HAVE_STD_STRING_VIEW cannot be directly set."
#endif

#ifdef __has_include
#if __has_include(<string_view>) && __cplusplus >= 201703L
#define BASE_HAVE_STD_STRING_VIEW 1
#endif
#endif

// For MSVC, `__has_include` is supported in VS 2017 15.3, which is later than
// the support for <optional>, <any>, <string_view>, <variant>. So we use
// _MSC_VER to check whether we have VS 2017 RTM (when <optional>, <any>,
// <string_view>, <variant> is implemented) or higher. Also, `__cplusplus` is
// not correctly set by MSVC, so we use `_MSVC_LANG` to check the language
// version.
// TODO(zhangxy): fix tests before enabling aliasing for `std::any`.
#if defined(_MSC_VER) && _MSC_VER >= 1910 && \
    ((defined(_MSVC_LANG) && _MSVC_LANG > 201402) || __cplusplus > 201402)
// #define BASE_HAVE_STD_ANY 1
#define BASE_HAVE_STD_OPTIONAL 1
#define BASE_HAVE_STD_VARIANT 1
#define BASE_HAVE_STD_STRING_VIEW 1
#endif

// HAVE_FEATURE
//
// A function-like feature checking macro that is a wrapper around
// `__has_feature`, which is defined by GCC 5+ and Clang and evaluates to a
// nonzero constant integer if the feature is supported or 0 if not.
//
// It evaluates to zero if `__has_feature` is not defined by the compiler.
//
// GCC: https://gcc.gnu.org/gcc-5/changes.html
// Clang: https://clang.llvm.org/docs/LanguageExtensions.html
#ifdef __has_feature
#define HAVE_FEATURE(x) __has_feature(x)
#else
#define HAVE_FEATURE(x) 0
#endif // __has_feature

// HAVE_ATTRIBUTE
//
// A function-like feature checking macro that is a wrapper around
// `__has_attribute`, which is defined by GCC 5+ and Clang and evaluates to a
// nonzero constant integer if the attribute is supported or 0 if not.
//
// It evaluates to zero if `__has_attribute` is not defined by the compiler.
//
// GCC: https://gcc.gnu.org/gcc-5/changes.html
// Clang: https://clang.llvm.org/docs/LanguageExtensions.html
#ifdef __has_attribute
#define HAVE_ATTRIBUTE(x) __has_attribute(x)
#else
#define HAVE_ATTRIBUTE(x) 0
#endif // __has_attribute

// HAVE_CPP_ATTRIBUTE
//
// A function-like feature checking macro that accepts C++11 style attributes.
// It's a wrapper around `__has_cpp_attribute`, defined by ISO C++ SD-6
// (https://en.cppreference.com/w/cpp/experimental/feature_test). If we don't
// find `__has_cpp_attribute`, will evaluate to 0.
#ifndef HAVE_CPP_ATTRIBUTE
#if defined(__cplusplus) && defined(__has_cpp_attribute)
// NOTE: requiring __cplusplus above should not be necessary, but
// works around https://bugs.llvm.org/show_bug.cgi?id=23435.
#define HAVE_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#define HAVE_CPP_ATTRIBUTE(x) 0
#endif // defined(__cplusplus) && defined(__has_cpp_attribute)
#endif // HAVE_CPP_ATTRIBUTE

#if defined(UNDEFINED_BEHAVIOR_SANITIZER) \
  || HAVE_FEATURE(undefined_sanitizer) \
  || HAVE_FEATURE(undefined_behavior_sanitizer) \
  || defined(__SANITIZE_UNDEFINED_BEHAVIOR__)

// This macro prevents the undefined behavior sanitizer from reporting
// failures. This is only meant to silence unaligned loads on platforms that
// are known to support them.
#define UBSAN_IGNORE_UNDEF \
  __attribute__((no_sanitize("undefined")))

/**
  C and C++ perform implicit casts when,
  for example, you pass an integer-typed variable
  to a function that expects a different type.
  When the target type is wider,
  there is no problem,
  but when the target type is narrower
  or when it is the same size and the other signedness,
  integer values may silently change when the type changes.
  For example, this program:
    #include <iostream>
    int main() {
      int x = -3;
      unsigned y = x;
      std::cout << y << "\n";
    }
  prints 4294967293.
**/
#define UBSAN_IGNORE_IMPLICIT \
  __attribute__((no_sanitize("implicit-conversion")))

/// \note Unsigned integer overflow,
/// where the result of an unsigned integer computation
/// cannot be represented in its type.
/// Unlike signed integer overflow,
/// this is not undefined behavior,
/// but it is often unintentional.
// This macro prevents the undefined behavior sanitizer from reporting
// failures related to unsigned integer overflows. This is only meant to
// silence cases where this well defined behavior is expected.
#define UBSAN_IGNORE_UNSIGNED_OVERFLOW \
  __attribute__((no_sanitize("unsigned-integer-overflow")))

#else

#define UBSAN_IGNORE_IMPLICIT

#define UBSAN_IGNORE_UNDEF

#define UBSAN_IGNORE_UNSIGNED_OVERFLOW

#endif // UNDEFINED_BEHAVIOR_SANITIZER

#if defined(THREAD_SANITIZER) \
  || HAVE_FEATURE(thread_sanitizer) \
  || defined(__SANITIZE_THREAD__)

#define NO_SANITIZE_THREAD \
  __attribute__((no_sanitize_thread))

#else

#define NO_SANITIZE_THREAD

#endif // THREAD_SANITIZER

#if defined(MEMORY_SANITIZER) \
  || HAVE_FEATURE(memory_sanitizer) \
  || defined(__SANITIZE_MEMORY__)

#define NO_SANITIZE_MEMORY \
  __attribute__((no_sanitize_memory))

#else

#define NO_SANITIZE_MEMORY

#endif // MEMORY_SANITIZER

#if defined(ADDRESS_SANITIZER) \
  || HAVE_FEATURE(address_sanitizer) \
  || defined(__SANITIZE_ADDRESS__)

#define NO_SANITIZE_ADDRESS \
  __attribute__((no_sanitize_address))

// Describe the current state of a contiguous container such as e.g.
// std::vector or std::string. For more details see
// sanitizer/common_interface_defs.h, which is provided by the compiler.
#include <sanitizer/common_interface_defs.h>

#define ANNOTATE_CONTIGUOUS_CONTAINER(beg, end, old_mid, new_mid) \
  __sanitizer_annotate_contiguous_container(beg, end, old_mid, new_mid)

#define ADDRESS_SANITIZER_REDZONE(name) \
  struct {                                   \
    char x[8] __attribute__((aligned(8)));   \
  } name

#else

#define NO_SANITIZE_ADDRESS

#define ANNOTATE_CONTIGUOUS_CONTAINER(beg, end, old_mid, new_mid)  // empty

#define ADDRESS_SANITIZER_REDZONE(name) static_assert(true, "")

#endif // ADDRESS_SANITIZER

// CONST_INIT
//
// A variable declaration annotated with the `CONST_INIT` attribute will
// not compile (on supported platforms) unless the variable has a constant
// initializer. This is useful for variables with static and thread storage
// duration, because it guarantees that they will not suffer from the so-called
// "static init order fiasco".  Prefer to put this attribute on the most visible
// declaration of the variable, if there's more than one, because code that
// accesses the variable can then use the attribute for optimization.
//
// Example:
//
//   class MyClass {
//    public:
//     CONST_INIT static MyType my_var;
//   };
//
//   MyType MyClass::my_var = MakeMyType(...);
//
// Note that this attribute is redundant if the variable is declared constexpr.
#if HAVE_CPP_ATTRIBUTE(clang::require_constant_initialization)
// NOLINTNEXTLINE(whitespace/braces)
#define CONST_INIT [[clang::require_constant_initialization]]
#else
#define CONST_INIT
#endif  // HAVE_CPP_ATTRIBUTE(clang::require_constant_initialization)

// ATTRIBUTE_UNUSED
//
// Prevents the compiler from complaining about variables that appear unused.
//
// Example:
//
// ATTRIBUTE_UNUSED void f(ATTRIBUTE_UNUSED bool thing1,
//                         ATTRIBUTE_UNUSED bool thing2)
// {
//    ATTRIBUTE_UNUSED bool b = thing1 && thing2;
//    assert(b); // in release mode, assert is compiled out, and b is unused
//               // no warning because it is declared ATTRIBUTE_UNUSED
// } // parameters thing1 and thing2 are not used, no warning
#if HAVE_ATTRIBUTE(unused) || (defined(__GNUC__) && !defined(__clang__))
#undef ATTRIBUTE_UNUSED
#define ATTRIBUTE_UNUSED __attribute__((__unused__))
#elif __cplusplus >= 201703L
#define ATTRIBUTE_UNUSED [[maybe_unused]]
#else
#define ATTRIBUTE_UNUSED
#endif

#ifndef MAYBE_UNUSED
#define MAYBE_UNUSED ATTRIBUTE_UNUSED
#endif // MAYBE_UNUSED

// ATTRIBUTE_INITIAL_EXEC
//
// Tells the compiler to use "initial-exec" mode for a thread-local variable.
// See http://people.redhat.com/drepper/tls.pdf for the gory details.
#if HAVE_ATTRIBUTE(tls_model) || (defined(__GNUC__) && !defined(__clang__))
#define ATTRIBUTE_INITIAL_EXEC __attribute__((tls_model("initial-exec")))
#else
#define ATTRIBUTE_INITIAL_EXEC
#endif

// ATTRIBUTE_PACKED
//
// Prevents the compiler from padding a structure to natural alignment
#if HAVE_ATTRIBUTE(packed) || (defined(__GNUC__) && !defined(__clang__))
#define ATTRIBUTE_PACKED __attribute__((__packed__))
#else
#define ATTRIBUTE_PACKED
#endif

// ATTRIBUTE_FUNC_ALIGN
//
// Tells the compiler to align the function start at least to certain
// alignment boundary
#if HAVE_ATTRIBUTE(aligned) || (defined(__GNUC__) && !defined(__clang__))
#define ATTRIBUTE_FUNC_ALIGN(bytes) __attribute__((aligned(bytes)))
#else
#define ATTRIBUTE_FUNC_ALIGN(bytes)
#endif

// ATTRIBUTE_NORETURN
//
// Tells the compiler that a given function never returns.
#if HAVE_ATTRIBUTE(noreturn) || (defined(__GNUC__) && !defined(__clang__))
#define ATTRIBUTE_NORETURN __attribute__((noreturn))
#elif defined(_MSC_VER)
#define ATTRIBUTE_NORETURN __declspec(noreturn)
#elif defined(__clang__) && __cplusplus >= 201103L
#define ATTRIBUTE_NORETURN [[ noreturn ]]
#else
#define ATTRIBUTE_NORETURN
#endif

// documents that moved-from object will be in the same state
// as if constructed using moved-from object the constructor.
/// \example boost.org/doc/libs/1_54_0/doc/html/boost_asio/reference/basic_stream_socket/basic_stream_socket/overload5.html
/// i.e. it does not actually destroy |stream| by |move|
/// \note unlike `COPY_OR_MOVE` it documents
/// that value will not be moved for sure.
#define COPY_ON_MOVE(x) x

/// \note prefer basis::AccessVerifier or `RUN_ON` to `LIVES_ON`
// documents that value must be created/modified/used
// only from one sequence i.e. must be thread-safe
/// \todo integrate with thread-safety annotations
#define LIVES_ON(sequenceChecker)

/// \note prefer `DCHECK_RUN_ON`
/// to `BIND_UNRETAINED_RUN_ON_SEQUENCE_CHECK` where possible.
// Can be used to check that value is accessed
// only on sequence i.e. thread-safe
//
// USAGE
//
//  /// \note It is not real lock, only annotated as lock.
//  /// It just calls callback on scope entry AND exit.
//  basis::FakeLockWithCheck<FakeLockRunType>
//    fakeLockToSequence_ {
//      BIND_UNRETAINED_RUN_ON_SEQUENCE_CHECK(&sequence_checker_)
//    };
#define BIND_UNRETAINED_RUN_ON_SEQUENCE_CHECK(checker) \
  base::BindRepeating( \
    &base::SequenceChecker::CalledOnValidSequence \
    , base::Unretained(checker) \
  )

// Can be used to check that object exists
// (does extra lifetime checks when ASAN enabled)
//
// USAGE
//
//  /// \note It is not real lock, only annotated as lock.
//  /// It just calls callback on scope entry AND exit.
//  basis::FakeLockWithCheck<FakeLockRunType>
//    fakeLockToUnownedPointer_ {
//      BIND_UNOWNED_PTR_VALIDATOR(ExampleServer, this)
//    };
//
//  // The io_context is required for all I/O
//  boost::asio::io_context ioc_
//    // It safe to read value from any thread
//    // because its storage expected to be not modified,
//    // we just need to check storage validity.
//    GUARDED_BY(fakeLockToUnownedPointer_);
#define BIND_UNOWNED_PTR_VALIDATOR(StoredType, RawPtr) \
  base::BindRepeating( \
    [] \
    (util::UnownedPtr<StoredType> ptr) \
    -> bool \
    { \
      ptr.checkForLifetimeIssues(); \
      return ptr.Get(); \
    } \
    , /* COPIED */ COPIED() util::UnownedPtr<StoredType>(RawPtr) \
  )

// Can be used to check that value is accessed
// only on asio strand i.e. thread-safe
//
// USAGE
//
// BIND_UNRETAINED_RUN_ON_STRAND_CHECK(&strand_)
#define BIND_UNRETAINED_RUN_ON_STRAND_CHECK(checker) \
  base::BindRepeating( \
    &::boost::asio::strand< \
        ::boost::asio::io_context::executor_type \
      >::running_in_this_thread \
    , base::Unretained(checker) \
  )

// USAGE
//
// BIND_UNRETAINED_MEMBER(&ClassName::MemberFn)
#define BIND_UNRETAINED_MEMBER(member) \
  base::BindRepeating( \
    member \
    , base::Unretained(this) \
  )

// Use `MUST_USE_RETURN_VALUE` with functions
// because `MUST_USE_RESULT` must be used with enum or class.
//
// similar to __attribute__((warn_unused_result))
/// \usage (note order restriction)
/// [[nodisard]] extern bool foo();
/// [[nodisard]] inline bool foo();
/// [[nodisard]] static bool foo();
/// [[nodisard]] static inline bool foo();
/// [[nodisard]] virtual bool foo();
#ifndef MUST_USE_RETURN_VALUE
#define MUST_USE_RETURN_VALUE \
  [[nodiscard]] /* do not ignore return value */
#endif // MUST_USE_RETURN_VALUE

/// \deprecated. Use `MUST_USE_RETURN_VALUE`
/// \see WARN_UNUSED_RESULT from `base/compiler_specific.h`
#ifndef WARN_UNUSED_RESULT
#define WARN_UNUSED_RESULT MUST_USE_RETURN_VALUE
#endif // WARN_UNUSED_RESULT

// Use `MUST_USE_RESULT` with enum or class
// because `MUST_USE_RETURN_VALUE` must be used with functions.
//
// USAGE
//
// enum class MUST_USE_RESULT ErrorCode {
//     OK,
//     Fatal,
//     System,
//     FileIssue
// };
#ifndef MUST_USE_RESULT
#define MUST_USE_RESULT MUST_USE_RETURN_VALUE
#endif // MUST_USE_RESULT

/// \deprecated
/// \note Prefer |MUST_USE_RETURN_VALUE|
/// \note Similar to [[nodiscard]] attribute,
/// being implemented by Clang and GCC as __attribute__((warn_unused_result))
///
// Annotate a function indicating the caller must examine the return value.
// Use like:
//   ATTRIBUTE_DISCARDED_RESULT int foo();
//
/// \note Use `UNREFERENCED_PARAMETER(x)` for ignoring function parameter.
/// \note Use `ignore_result(x)` for ignoring result of function call.
/// \note Use `ALLOW_UNUSED_LOCAL(x)` for ignoring local variable.
//
#undef ATTRIBUTE_DISCARDED_RESULT
#if defined(COMPILER_GCC) || defined(__clang__)
#define ATTRIBUTE_DISCARDED_RESULT __attribute__((warn_unused_result))
#else
#define ATTRIBUTE_DISCARDED_RESULT
#endif

/// \usage
/// NEW_NO_THROW(FROM_HERE,
///   ptr // lhs of assignment
///   , SomeType(somearg1, somearg2) // rhs of assignment
///   , LOG(ERROR) // log allocation failure
/// );
#define NEW_NO_THROW(from_here, lhs, rhs, FAILED_LOG_STREAM) \
  DCHECK(!lhs); \
  lhs = new(std::nothrow/*, from_here.file_name(), from_here.line_number()*/) rhs; \
  if(!lhs) \
  { \
    FAILED_LOG_STREAM \
      << "failed to allocate " \
      << from_here.ToString(); \
  }

/// \usage
/// DELETE_NOT_ARRAY_AND_NULLIFY(FROM_HERE, ptr);
#define DELETE_NOT_ARRAY_AND_NULLIFY(from_here, x) \
  DCHECK(x) \
      << "failed to deallocate " \
      << from_here.ToString(); \
  delete x; \
  x = nullptr; \
  DCHECK(!x) \
      << "failed to deallocate " \
      << from_here.ToString();

/// \note prefer basis::AccessVerifier to `GLOBAL_THREAD_SAFE_LIFETIME`
// Documents that value may not be thread-safe in general,
// but because it can be modified only during
// `initialization` and `teardown` steps
// it can be used by multiple threads during `running` step.
/// \note It means that object must exist during `running` step,
/// but it does NOT mean that internals of the object are thread-safe.
#define GLOBAL_THREAD_SAFE_LIFETIME(x)

/// \note prefer basis::AccessVerifier to `NOT_THREAD_SAFE_LIFETIME`
// Documents that value can NOT be used from
// any thread without extra thread-safety checks.
// i.e. take care of possible thread-safety bugs.
// Usually it means that value MUST be guarded by some mutex lock
// OR modified only during `initialization` step.
/// \note prefer sequence checkers or
/// <base/thread_collision_warner.h> to it if possible
#define NOT_THREAD_SAFE_LIFETIME(x)

/// \note prefer `RUN_ON_ANY_THREAD` where possible
// Documents that function does not perform thread-safety checks.
// Usually that means that funtion unable to have
// checks like `running_in_this_thread` or `DCHECK_CALLED_ON_VALID_SEQUENCE`
#define NOT_THREAD_SAFE_FUNCTION(x)

/// \note requires `#include <basis/scoped_checks.hpp>`
/// due to usage of `GUARD_NOT_THREAD_BOUND_MEMBER`
// Creates `weak_ptr_factory_` and `weak_this_`.
// base::WeakPtr can be used to ensure that any callback bound
// to an object is canceled when that object is destroyed
// (guarantees that |this| will not be used-after-free).
//
// After constructing |weak_ptr_factory_|
// we immediately construct a WeakPtr
// in order to bind the WeakPtr object to its thread.
// When we need a WeakPtr, we copy construct this,
// which is safe to do from any
// thread according to weak_ptr.h (versus calling
// |weak_ptr_factory_.GetWeakPtr() which is not).
#define SET_WEAK_POINTERS(Name) \
  CREATE_NOT_THREAD_BOUND_GUARD(weak_ptr_factory_); \
  base::WeakPtrFactory<Name> weak_ptr_factory_ \
    GUARDED_BY(NOT_THREAD_BOUND_GUARD(weak_ptr_factory_)); \
  CREATE_NOT_THREAD_BOUND_GUARD(weak_this_); \
  const base::WeakPtr<Name> weak_this_ \
    GUARDED_BY(NOT_THREAD_BOUND_GUARD(weak_this_))

// Creates `weakSelf()` function.
/// \note requires `#include <basis/scoped_checks.hpp>`
/// due to usage of `DCHECK_NOT_THREAD_BOUND_GUARD`
// It is thread-safe to copy |base::WeakPtr|.
// Weak pointers may be passed safely between sequences, but must always be
// dereferenced and invalidated on the same SequencedTaskRunner otherwise
// checking the pointer would be racey.
#define SET_WEAK_SELF(Name) \
  MUST_USE_RETURN_VALUE \
  base::WeakPtr<Name> weakSelf() const NO_EXCEPTION \
  { \
    DCHECK_NOT_THREAD_BOUND_GUARD(weak_this_); \
    return weak_this_; \
  }

// Documents that value can be used from any thread.
// Usually it means that value is guarded by some mutex lock.
/// \example
/// std::atomic<bool> assume_is_accepting_{false};
/// // atomic types can be documented with |ALWAYS_THREAD_SAFE|
/// ALWAYS_THREAD_SAFE()
///   assume_is_accepting_ = true;
#define ALWAYS_THREAD_SAFE(x) x

// Documents that value can be used from any thread.
// Usually it means that value is thread-safe
// during `init` or `teardown` step.
/// \note value may be not generally thread-safe,
/// but assumed to be thread-safe at least here
#define ASSUME_THREAD_SAFE_BECAUSE(x)

// Documents that value will become invalid.
// Usually it means that value is moved or freed.
#define MAKES_INVALID(x)

// Documents that value can become invalid.
// Usually it means that value can be moved or freed.
#define CAN_BECOME_INVALID(x)

/// \note prefer |MoveOnly| to |COPIED|
// Documents that value will be copied.
/// \note use it to annotate arguments that are bound to function
#define COPIED(x) x

/// \note use `base::rvalue_cast` instead of `std::move`
/// where possible.
/// Document usage of `std::move` like below:
/// COPY_OR_MOVE(x)
//
// Documents that value may be NOT moved
// while using `std::move` or cast to rvalue.
// see https://stackoverflow.com/a/38917200
//
// EXAMPLE
//
// Calling `std::move` on a const object
// may call the copy constructor
// when passed to another object
#define CAN_COPY_ON_MOVE(x)

// Use it instead of `CAN_COPY_ON_MOVE("moving const") std::move(x)`
#define COPY_OR_MOVE(x) std::move(x)

/// \note prefer `REFERENCED` to `RAW_REFERENCED`
// Documents that value will be used as alias
// i.e. another name for an already existing variable.
// For example, you may want to notice
// that value passed to function will NOT be copied.
#define RAW_REFERENCED(x) x

// Documents that value will be used as alias
// i.e. another name for an already existing variable.
// For example, you may want to notice
// that value passed to function will NOT be copied.
/// \note Prefer to use it to annotate arguments that are bound to function.
#define REFERENCED(x) std::ref(x)

#define CONST_REFERENCED(x) std::cref(x)

/// \note if possible, use `Shared` in data type name
/// instead of `SHARED_LIFETIME` comments everywhere
// Documents that value has shared storage
// like shaped_ptr, scoped_refptr, etc.
// i.e. that object lifetime will be prolonged.
/// \note use it to annotate arguments that are bound to function
#define SHARED_LIFETIME(x) x

/// \note Prefer to use |DEBUG_BIND_CHECKS|, |bindChecked*|
// Documents that value has external storage
// i.e. that object lifetime not conrolled.
// If you found lifetime-related bug,
// than you can `grep-search` for |UNOWNED_LIFETIME| in code.
/// \note see also |UnownedPtr|
/// \note use it to annotate arguments that are bound to function
/// \example
///   beast::async_detect_ssl(
///     stream_, // The stream to read from
///     buffer_, // The dynamic buffer to use
///     boost::asio::bind_executor(perConnectionStrand_,
///       std::bind(
///         &DetectChannel::onDetected
///         , /// \note Lifetime must be managed externally.
///           /// API user can free |DetectChannel| only if
///           /// that callback finished (or failed to schedule).
///           UNOWNED_LIFETIME(
///             COPIED(this))
///         , std::placeholders::_1
///         , std::placeholders::_2
///       )
///     )
///   );
#define UNOWNED_LIFETIME(x) x

/**
 * @usage
  if (ec == ::boost::asio::error::connection_aborted)
  {
    LOG_ERROR_CODE(LOG(WARNING),
      "Listener failed with"
      " connection_aborted error: ", what, ec);
  }
 **/
#define LOG_ERROR_CODE(LOG_STREAM, description, what, ec) \
  LOG_STREAM  \
    << description  \
    << what  \
    << ": "  \
    << ec.message()

/**
 * @brief Print current position in file and passed data
 * into stream of provided logger.
 * @usage
  LOG_CALL(DVLOG(99)) << "Hello";
 **/
#define LOG_CALL(LOG_STREAM) \
  LOG_STREAM \
    << "called from location: " \
    << FROM_HERE.ToString() \
    << " \n "

#if defined(COMPILER_MSVC)

// For _Printf_format_string_.
#include <sal.h>

// Macros for suppressing and disabling warnings on MSVC.
//
// Warning numbers are enumerated at:
// http://msdn.microsoft.com/en-us/library/8x5x43k7(VS.80).aspx
//
// The warning pragma:
// http://msdn.microsoft.com/en-us/library/2c8f766e(VS.80).aspx
//
// Using __pragma instead of #pragma inside macros:
// http://msdn.microsoft.com/en-us/library/d9x1s805.aspx

// MSVC_SUPPRESS_WARNING disables warning |n| for the remainder of the line and
// for the next line of the source file.
#if !defined(MSVC_SUPPRESS_WARNING)
#define MSVC_SUPPRESS_WARNING(n) __pragma(warning(suppress:n))
#endif // !defined(MSVC_SUPPRESS_WARNING)

// Macros for suppressing and disabling warnings on MSVC.
//
// Warning numbers are enumerated at:
// http://msdn.microsoft.com/en-us/library/8x5x43k7(VS.80).aspx
//
// The warning pragma:
// http://msdn.microsoft.com/en-us/library/2c8f766e(VS.80).aspx
//
// Using __pragma instead of #pragma inside macros:
// http://msdn.microsoft.com/en-us/library/d9x1s805.aspx

#if !defined(MSVC_PUSH_DISABLE_WARNING)
// MSVC_PUSH_DISABLE_WARNING pushes |n| onto a stack of warnings to be disabled.
// The warning remains disabled until popped by MSVC_POP_WARNING.
#define MSVC_PUSH_DISABLE_WARNING(n) __pragma(warning(push)) \
                                     __pragma(warning(disable:n))
#endif // !defined(MSVC_PUSH_DISABLE_WARNING)

// Pop effects of innermost MSVC_PUSH_* macro.
#if !defined(MSVC_POP_WARNING)
#define MSVC_POP_WARNING() __pragma(warning(pop))
#endif // !defined(MSVC_POP_WARNING)

// Allows |this| to be passed as an argument in constructor initializer lists.
// This uses push/pop instead of the seemingly simpler suppress feature to avoid
// having the warning be disabled for more than just |code|.
//
// Example usage:
// Foo::Foo() : x(NULL), ALLOW_THIS_IN_INITIALIZER_LIST(y(this)), z(3) {}
//
// Compiler warning C4355: 'this': used in base member initializer list:
// http://msdn.microsoft.com/en-us/library/3c594ae3(VS.80).aspx
#if !defined(ALLOW_THIS_IN_INITIALIZER_LIST)
#define ALLOW_THIS_IN_INITIALIZER_LIST(code) \
  MSVC_PUSH_DISABLE_WARNING(4355)            \
  code MSVC_POP_WARNING()
#endif // !defined(ALLOW_THIS_IN_INITIALIZER_LIST)

#else  // Not MSVC

#if !defined(ALLOW_THIS_IN_INITIALIZER_LIST)
#define ALLOW_THIS_IN_INITIALIZER_LIST(code) code
#endif // !defined(ALLOW_THIS_IN_INITIALIZER_LIST)

#endif  // COMPILER_MSVC

// Use Clang's thread safety analysis annotations when available. In other
// environments, the macros receive empty definitions.
// Usage documentation: https://clang.llvm.org/docs/ThreadSafetyAnalysis.html

#if !defined(THREAD_ANNOTATION_ATTRIBUTE__)

#if defined(__clang__)

#define THREAD_ANNOTATION_ATTRIBUTE__(x) __attribute__((x))
#else
#define THREAD_ANNOTATION_ATTRIBUTE__(x)  // no-op
#endif // defined(__clang__)

#endif  // !defined(THREAD_ANNOTATION_ATTRIBUTE__)

#ifndef GUARDED_BY
#define GUARDED_BY(x) THREAD_ANNOTATION_ATTRIBUTE__(guarded_by(x))
#endif

#ifndef PT_GUARDED_BY
#define PT_GUARDED_BY(x) THREAD_ANNOTATION_ATTRIBUTE__(pt_guarded_by(x))
#endif

#ifndef ACQUIRED_AFTER
#define ACQUIRED_AFTER(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(acquired_after(__VA_ARGS__))
#endif

#ifndef ACQUIRED_BEFORE
#define ACQUIRED_BEFORE(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(acquired_before(__VA_ARGS__))
#endif

#ifndef EXCLUSIVE_LOCKS_REQUIRED
#define EXCLUSIVE_LOCKS_REQUIRED(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(exclusive_locks_required(__VA_ARGS__))
#endif

#ifndef SHARED_LOCKS_REQUIRED
#define SHARED_LOCKS_REQUIRED(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(shared_locks_required(__VA_ARGS__))
#endif

#ifndef LOCKS_EXCLUDED
#define LOCKS_EXCLUDED(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(locks_excluded(__VA_ARGS__))
#endif

#ifndef LOCK_RETURNED
#define LOCK_RETURNED(x) THREAD_ANNOTATION_ATTRIBUTE__(lock_returned(x))
#endif

#ifndef LOCKABLE
#define LOCKABLE THREAD_ANNOTATION_ATTRIBUTE__(lockable)
#endif

#ifndef SCOPED_LOCKABLE
#define SCOPED_LOCKABLE THREAD_ANNOTATION_ATTRIBUTE__(scoped_lockable)
#endif

#ifndef EXCLUSIVE_LOCK_FUNCTION
#define EXCLUSIVE_LOCK_FUNCTION(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(exclusive_lock_function(__VA_ARGS__))
#endif

#ifndef SHARED_LOCK_FUNCTION
#define SHARED_LOCK_FUNCTION(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(shared_lock_function(__VA_ARGS__))
#endif

#ifndef EXCLUSIVE_TRYLOCK_FUNCTION
#define EXCLUSIVE_TRYLOCK_FUNCTION(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(exclusive_trylock_function(__VA_ARGS__))
#endif

#ifndef SHARED_TRYLOCK_FUNCTION
#define SHARED_TRYLOCK_FUNCTION(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(shared_trylock_function(__VA_ARGS__))
#endif

#ifndef UNLOCK_FUNCTION
#define UNLOCK_FUNCTION(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(unlock_function(__VA_ARGS__))
#endif

#ifndef NO_THREAD_SAFETY_ANALYSIS
#define NO_THREAD_SAFETY_ANALYSIS \
  THREAD_ANNOTATION_ATTRIBUTE__(no_thread_safety_analysis)
#endif

#ifndef ASSERT_EXCLUSIVE_LOCK
#define ASSERT_EXCLUSIVE_LOCK(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(assert_exclusive_lock(__VA_ARGS__))
#endif

#ifndef ASSERT_SHARED_LOCK
#define ASSERT_SHARED_LOCK(...) \
  THREAD_ANNOTATION_ATTRIBUTE__(assert_shared_lock(__VA_ARGS__))
#endif

// BAD_CALL_IF()
//
// Used on a function overload to trap bad calls: any call that matches the
// overload will cause a compile-time error. This macro uses a clang-specific
// "enable_if" attribute, as described at
// http://clang.llvm.org/docs/AttributeReference.html#enable-if
//
// Overloads which use this macro should be bracketed by
// `#ifdef BAD_CALL_IF`.
//
// Example:
//
//   int isdigit(int c);
//   #ifdef BAD_CALL_IF
//   int isdigit(int c)
//     BAD_CALL_IF(c <= -1 || c > 255,
//                       "'c' must have the value of an unsigned char or EOF");
//   #endif // BAD_CALL_IF

#if defined(__clang__)
# if HAVE_ATTRIBUTE(enable_if)
#  define BAD_CALL_IF(expr, msg) \
    __attribute__((enable_if(expr, "Bad call trap"), unavailable(msg)))
# endif
#endif

#if HAVE_ATTRIBUTE(uninitialized)
// Attribute "uninitialized" disables -ftrivial-auto-var-init=pattern for
// the specified variable.
//
// -ftrivial-auto-var-init is security risk mitigation feature, so attribute
// should not be used "just in case", but only to fix real performance
// bottlenecks when other approaches do not work. In general the compiler is
// quite effective at eliminating unneeded initializations introduced by the
// flag, e.g. when they are followed by actual initialization by a program.
// However if compiler optimization fails and code refactoring is hard, the
// attribute can be used as a workaround.
#define ATTRIBUTE_UNINITIALIZED __attribute__((uninitialized))
#else
#define ATTRIBUTE_UNINITIALIZED
#endif  // HAVE_ATTRIBUTE(uninitialized)

#ifndef NO_EXCEPTION
#define NO_EXCEPTION noexcept
#endif // NO_EXCEPTION

// ATTRIBUTE_COLD
//
// Good candidates for the cold attribute are internal error handling functions
// which are called only in case of errors.
//
// The cold attribute is used to inform the compiler
// that a function is unlikely executed.
// The function is optimized for size
// rather than speed and on many targets
// it is placed into special subsection of the text section
// so all cold functions appears close together
// improving code locality of non-cold parts of program.
// The paths leading to call of cold functions within code
// are marked as unlikely by the branch prediction mechanism.
// It is thus useful to mark functions used to handle unlikely conditions,
// such as perror, as cold to improve optimization of hot functions
// that do call marked functions in rare occasions.
// When profile feedback is available, via -fprofile-use,
// hot functions are automatically detected and this attribute is ignored.
// GCC >= 4.3.
// https://gcc.gnu.org/onlinedocs/gcc-4.7.2/gcc/Function-Attributes.html
// https://clang.llvm.org/docs/AttributeReference.html
#ifndef ATTRIBUTE_COLD
#define ATTRIBUTE_COLD() __attribute__((cold))
#endif // ATTRIBUTE_COLD

// ATTRIBUTE_HOT
//
// The compiler can order the code in branches, such as if statements,
// to favour branches that call these hot functions
// and disfavour functions cold functions, under the assumption
// that it is more likely that that the branch that will be taken
// will call a hot function and less likely to call a cold one.
//
// In addition, the compiler can choose to group together functions
// marked as hot in a special section in the generated binary
//
// Tells GCC that a function is hot or cold. GCC can use this information to
// improve static analysis, i.e. a conditional branch to a cold function
// is likely to be not-taken.
// This annotation is used for function declarations.
//
// Example:
//
//   int foo() ATTRIBUTE_HOT;
#ifndef ATTRIBUTE_HOT
#define ATTRIBUTE_HOT() __attribute__((hot))
#endif // ATTRIBUTE_HOT

// A common technique for improving performance of hot code in C/C++
// is to inline the hottest functions called.
// While it often helps make things faster, there are some downsides to inlining
// (larger program size, worse cache locality, longer build time).
//
// Flattening instead of global inlining lets you opt in to the pros
// of aggressive inlining on a per-function basis,
// while protecting the rest of your program from the cons!
//
// Note:
//
// Functions with __attribute__((noinline)) will not be inlined.
// The same goes for functions where the compiler can’t see the body.
//
// Example:
//
// ATTRIBUTE_FLATTEN void hot_code()
// {
//     // the program spends >80% of its runtime in this function
//     while (condition) {
//         call_something();   // inlined!
//         do_thing(y);        // inlined!
//         other_thing();      // also inlined!
//     }
// }
#ifndef ATTRIBUTE_FLATTEN
#define ATTRIBUTE_FLATTEN() __attribute__((flatten))
#endif // ATTRIBUTE_FLATTEN

// ATTRIBUTE_REINITIALIZES
//
// Indicates that a member function reinitializes the entire object to a known
// state, independent of the previous state of the object.
//
// The clang-tidy check bugprone-use-after-move allows member functions marked
// with this attribute to be called on objects that have been moved from;
// without the attribute, this would result in a use-after-move warning.
#if HAVE_CPP_ATTRIBUTE(clang::reinitializes)
#define ATTRIBUTE_REINITIALIZES [[clang::reinitializes]]
#else
#define ATTRIBUTE_REINITIALIZES
#endif

// ATTRIBUTE_NO_SANITIZE_CFI
//
// Tells the ControlFlowIntegrity sanitizer to not instrument a given function.
// See https://clang.llvm.org/docs/ControlFlowIntegrity.html for details.
#if defined(__GNUC__) && defined(CONTROL_FLOW_INTEGRITY)
#define ATTRIBUTE_NO_SANITIZE_CFI __attribute__((no_sanitize("cfi")))
#else
#define ATTRIBUTE_NO_SANITIZE_CFI
#endif

// ATTRIBUTE_NO_SANITIZE_SAFESTACK
//
// Tells the SafeStack to not instrument a given function.
// See https://clang.llvm.org/docs/SafeStack.html for details.
#if defined(__GNUC__) && defined(SAFESTACK_SANITIZER)
#define ATTRIBUTE_NO_SANITIZE_SAFESTACK \
  __attribute__((no_sanitize("safe-stack")))
#else
#define ATTRIBUTE_NO_SANITIZE_SAFESTACK
#endif

// ATTRIBUTE_RETURNS_NONNULL
//
// Tells the compiler that a particular function never returns a null pointer.
#if HAVE_ATTRIBUTE(returns_nonnull) || \
    (defined(__GNUC__) && \
     (__GNUC__ > 5 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9)) && \
     !defined(__clang__))
#define ATTRIBUTE_RETURNS_NONNULL __attribute__((returns_nonnull))
#else
#define ATTRIBUTE_RETURNS_NONNULL
#endif

// ATTRIBUTE_NO_TAIL_CALL
//
// Prevents the compiler from optimizing away stack frames for functions which
// end in a call to another function.
#if HAVE_ATTRIBUTE(disable_tail_calls)
#define HAVE_ATTRIBUTE_NO_TAIL_CALL 1
#define ATTRIBUTE_NO_TAIL_CALL __attribute__((disable_tail_calls))
#elif defined(__GNUC__) && !defined(__clang__)
#define HAVE_ATTRIBUTE_NO_TAIL_CALL 1
#define ATTRIBUTE_NO_TAIL_CALL \
  __attribute__((optimize("no-optimize-sibling-calls")))
#else
#define ATTRIBUTE_NO_TAIL_CALL
#define HAVE_ATTRIBUTE_NO_TAIL_CALL 0
#endif

// ATTRIBUTE_WEAK
//
// Tags a function as weak for the purposes of compilation and linking.
// Weak attributes currently do not work properly in LLVM's Windows backend,
// so disable them there. See https://bugs.llvm.org/show_bug.cgi?id=37598
// for further information.
// The MinGW compiler doesn't complain about the weak attribute until the link
// step, presumably because Windows doesn't use ELF binaries.
#if (HAVE_ATTRIBUTE(weak) ||                   \
     (defined(__GNUC__) && !defined(__clang__))) && \
    !(defined(__llvm__) && defined(_WIN32)) && !defined(__MINGW32__)
#undef ATTRIBUTE_WEAK
#define ATTRIBUTE_WEAK __attribute__((weak))
#define HAVE_ATTRIBUTE_WEAK 1
#else
#define ATTRIBUTE_WEAK
#define HAVE_ATTRIBUTE_WEAK 0
#endif

// ATTRIBUTE_NONNULL
//
// Tells the compiler either (a) that a particular function parameter
// should be a non-null pointer, or (b) that all pointer arguments should
// be non-null.
//
// Note: As the GCC manual states, "[s]ince non-static C++ methods
// have an implicit 'this' argument, the arguments of such methods
// should be counted from two, not one."
//
// Args are indexed starting at 1.
//
// For non-static class member functions, the implicit `this` argument
// is arg 1, and the first explicit argument is arg 2. For static class member
// functions, there is no implicit `this`, and the first explicit argument is
// arg 1.
//
// Example:
//
//   /* arg_a cannot be null, but arg_b can */
//   void Function(void* arg_a, void* arg_b) ATTRIBUTE_NONNULL(1);
//
//   class C {
//     /* arg_a cannot be null, but arg_b can */
//     void Method(void* arg_a, void* arg_b) ATTRIBUTE_NONNULL(2);
//
//     /* arg_a cannot be null, but arg_b can */
//     static void StaticMethod(void* arg_a, void* arg_b)
//     ATTRIBUTE_NONNULL(1);
//   };
//
// If no arguments are provided, then all pointer arguments should be non-null.
//
//  /* No pointer arguments may be null. */
//  void Function(void* arg_a, void* arg_b, int arg_c) ATTRIBUTE_NONNULL();
//
// NOTE: The GCC nonnull attribute actually accepts a list of arguments, but
// ATTRIBUTE_NONNULL does not.
#if HAVE_ATTRIBUTE(nonnull) || (defined(__GNUC__) && !defined(__clang__))
#define ATTRIBUTE_NONNULL(arg_index) __attribute__((nonnull(arg_index)))
#else
#define ATTRIBUTE_NONNULL(...)
#endif

// PRINTF_ATTRIBUTE
// SCANF_ATTRIBUTE
//
// Tells the compiler to perform `printf` format string checking if the
// compiler supports it; see the 'format' attribute in
// <https://gcc.gnu.org/onlinedocs/gcc-4.7.0/gcc/Function-Attributes.html>.
//
// Note: As the GCC manual states, "[s]ince non-static C++ methods
// have an implicit 'this' argument, the arguments of such methods
// should be counted from two, not one."
#if HAVE_ATTRIBUTE(format) || (defined(__GNUC__) && !defined(__clang__))
#define PRINTF_ATTRIBUTE(string_index, first_to_check) \
  __attribute__((__format__(__printf__, string_index, first_to_check)))
#define SCANF_ATTRIBUTE(string_index, first_to_check) \
  __attribute__((__format__(__scanf__, string_index, first_to_check)))
#else
#define PRINTF_ATTRIBUTE(string_index, first_to_check)
#define SCANF_ATTRIBUTE(string_index, first_to_check)
#endif

/// \see `ALWAYS_INLINE` from `base/compiler_specific.h`
//
// ATTRIBUTE_ALWAYS_INLINE
// ATTRIBUTE_NOINLINE
//
// Forces functions to either inline or not inline. Introduced in gcc 3.1.
#if HAVE_ATTRIBUTE(always_inline) || \
    (defined(__GNUC__) && !defined(__clang__))
#define ATTRIBUTE_ALWAYS_INLINE __attribute__((always_inline))
#define HAVE_ATTRIBUTE_ALWAYS_INLINE 1
#else
#define ATTRIBUTE_ALWAYS_INLINE
#endif

/// \see `NOINLINE` from `base/compiler_specific.h`
//
#if HAVE_ATTRIBUTE(noinline) || (defined(__GNUC__) && !defined(__clang__))
#define ATTRIBUTE_NOINLINE __attribute__((noinline))
#define HAVE_ATTRIBUTE_NOINLINE 1
#else
#define ATTRIBUTE_NOINLINE
#endif

// ATTRIBUTE_DEPRECATED()
//
// Marks a deprecated class, struct, enum, function, method and variable
// declarations. The macro argument is used as a custom diagnostic message (e.g.
// suggestion of a better alternative).
//
// Examples:
//
//   class ATTRIBUTE_DEPRECATED("Use Bar instead") Foo {...};
//
//   ATTRIBUTE_DEPRECATED("Use Baz() instead") void Bar() {...}
//
//   template <typename T>
//   ATTRIBUTE_DEPRECATED("Use DoThat() instead")
//   void DoThis();
//
// Every usage of a deprecated entity will trigger a warning when compiled with
// clang's `-Wdeprecated-declarations` option. This option is turned off by
// default, but the warnings will be reported by clang-tidy.
//
// NOTE 1: The annotation goes on the declaration in the .h file, not the
// definition in the .cc file!
//
// NOTE 2: In order to keep unit testing the deprecated function without
// getting warnings, do something like this:
//
//   std::pony DEPRECATED_PonyPlz(const std::pony_spec& ps);
//   ATTRIBUTE_DEPRECATED("Do not use PonyPlz()") inline std::pony PonyPlz(const std::pony_spec& ps) {
//     return DEPRECATED_PonyPlz(ps);
//   }
//
// In other words, rename the existing function, and provide an inline wrapper
// using the original name that calls it. That way, callers who are willing to
// call it using the DEPRECATED_-prefixed name don't get the warning.
//
#if HAVE_ATTRIBUTE(unused) || defined(__clang__) && __cplusplus >= 201103L
#define ATTRIBUTE_DEPRECATED(message) __attribute__((deprecated(message)))
#elif __cplusplus >= 201703L
#define ATTRIBUTE_DEPRECATED(message) [[deprecated]]
#else
#define ATTRIBUTE_DEPRECATED(message)
#endif

// USAGE
//
// using MyType = deprecated_type<int>::type;
template <typename T>
struct ATTRIBUTE_DEPRECATED("deprecated_type") deprecated_type {
  using type = T;
};

/// \see `FALLTHROUGH` from `base/compiler_specific.h`
//
// FALL_THROUGH_BREAK
//
// Annotates implicit fall-through between switch labels, allowing a case to
// indicate intentional fallthrough and turn off warnings about any lack of a
// `break` statement. The FALL_THROUGH_BREAK macro should be followed by
// a semicolon and can be used in most places where `break` can, provided that
// no statements exist between it and the next switch label.
//
// Example:
//
//  switch (x) {
//    case 40:
//    case 41:
//      if (truth_is_out_there) {
//        ++x;
//        FALL_THROUGH_BREAK;  // Use instead of/along with annotations
//                                    // in comments
//      } else {
//        return x;
//      }
//    case 42:
//      ...
//
// Notes: when compiled with clang in C++11 mode, the FALL_THROUGH_BREAK
// macro is expanded to the [[clang::fallthrough]] attribute, which is analysed
// when  performing switch labels fall-through diagnostic
// (`-Wimplicit-fallthrough`). See clang documentation on language extensions
// for details:
// https://clang.llvm.org/docs/AttributeReference.html#fallthrough-clang-fallthrough
//
// When used with unsupported compilers, the FALL_THROUGH_BREAK macro
// has no effect on diagnostics. In any case this macro has no effect on runtime
// behavior and performance of code.
#if /* C++17 and above */ \
    __cplusplus >= 201703L \
    /* C++14 clang-5 */ \
    || (__cplusplus >= 201402L && __clang_major__ >= 5)
#define FALL_THROUGH_BREAK [[fallthrough]]
#elif defined(__clang__) && defined(__has_warning)
#if __has_feature(cxx_attributes) && __has_warning("-Wimplicit-fallthrough")
#define FALL_THROUGH_BREAK [[clang::fallthrough]]
#endif
#elif (defined(__GNUC__) && __GNUC__ >= 7) \
    /* C++11 gcc 7 */ \
    || (__cplusplus >= 201103L && __GNUC__ >= 7)
#define FALL_THROUGH_BREAK [[gnu::fallthrough]]
#endif

#ifndef FALL_THROUGH_BREAK
#define FALL_THROUGH_BREAK \
  do {                        \
  } while (0)
#endif

// Friendly name for a pure virtual routine.
#ifndef PURE_VIRTUAL_FUNCTION
#define PURE_VIRTUAL_FUNCTION = 0
#endif // PURE_ZEROED

#undef arraysize
// The arraysize(arr) macro returns the # of elements in an array arr.
// The expression is a compile-time constant, and therefore can be
// used in defining new arrays, for example.  If you use arraysize on
// a pointer by mistake, you will get a compile-time error.
//
// One caveat is that arraysize() doesn't accept any array of an
// anonymous type or a type defined inside a function.  In these rare
// cases, you have to use the unsafe ARRAY_SIZE_UNSAFE() macro below.  This is
// due to a limitation in C++'s template system.  The limitation might
// eventually be removed, but it hasn't happened yet.

// This template function declaration is used in defining arraysize.
// Note that the function doesn't need an implementation, as we only
// use its type.
namespace internal {
template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];
} // namespace internal

// That gcc wants both of these prototypes seems mysterious. VC, for
// its part, can't decide which to use (another mystery). Matching of
// template overloads: the final frontier.
#ifndef _MSC_VER
namespace internal {
template <typename T, size_t N>
char (&ArraySizeHelper(const T (&array)[N]))[N];
} // namespace internal
#endif // _MSC_VER

#define arraysize(array) (sizeof(::internal::ArraySizeHelper(array)))

// gejun: Following macro was used in other modules.
#undef ARRAY_SIZE
#define ARRAY_SIZE(array) arraysize(array)

// return the size of a C array.
#ifndef arraysize_unsafe
#define arraysize_unsafe(a)     \
  ((sizeof(a) / sizeof(*(a))) / \
   static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))
#endif // arraysize_unsafe

// ARRAY_SIZE_UNSAFE performs essentially the same calculation as arraysize,
// but can be used on anonymous types or types defined inside
// functions.  It's less safe than arraysize as it accepts some
// (although not all) pointers.  Therefore, you should use arraysize
// whenever possible.
//
// The expression ARRAY_SIZE_UNSAFE(a) is a compile-time constant of type
// size_t.
//
// ARRAY_SIZE_UNSAFE catches a few type errors.  If you see a compiler error
//
//   "warning: division by zero in ..."
//
// when using ARRAY_SIZE_UNSAFE, you are (wrongfully) giving it a pointer.
// You should only use ARRAY_SIZE_UNSAFE on statically allocated arrays.
//
// The following comments are on the implementation details, and can
// be ignored by the users.
//
// ARRAY_SIZE_UNSAFE(arr) works by inspecting sizeof(arr) (the # of bytes in
// the array) and sizeof(*(arr)) (the # of bytes in one array
// element).  If the former is divisible by the latter, perhaps arr is
// indeed an array, in which case the division result is the # of
// elements in the array.  Otherwise, arr cannot possibly be an array,
// and we generate a compiler error to prevent the code from
// compiling.
//
// Since the size of bool is implementation-defined, we need to cast
// !(sizeof(a) & sizeof(*(a))) to size_t in order to ensure the final
// result has type size_t.
//
// This macro is not perfect as it wrongfully accepts certain
// pointers, namely where the pointer size is divisible by the pointee
// size.  Since all our code has to go through a 32-bit compiler,
// where a pointer is 4 bytes, this means all pointers to a type whose
// size is 3 or greater than 4 will be (righteously) rejected.
#undef ARRAY_SIZE_UNSAFE
#define ARRAY_SIZE_UNSAFE(a) arraysize_unsafe(a)

// the length of a static string literal,
// e.g. STATIC_STRLEN("foo") == 3.
#ifndef STATIC_STRLEN
#define STATIC_STRLEN(X) (sizeof(X) - 1)
#endif // STATIC_STRLEN

// MOTIVATION
//
// Macro expansion proceeds recursively in "layers."
// Stringization prevents the preprocessor from performing macro expansion,
// therefore it is often necessary to delay stringization.
//
// EXAMPLE
//
// // prints "person.address().zip_code()":
// LOG(INFO) << STRINGIFY(person.address().zip_code());
//
// EXAMPLE
//
// #define NOTE(str) \
//   message(__FILE__ "(" BOOST_PP_STRINGIZE(__LINE__) ") : " str) \
//   /**/
#ifndef STRINGIFY
#define STRINGIFY(X) #X
#endif // STRINGIFY

/// \note without comma (see STRINGIFY_VA_ARGS)
#ifndef STRINGIFY_VA_ARG
#define STRINGIFY_VA_ARG(...) #__VA_ARGS__
#endif // STRINGIFY_VA_ARGS

/// \note without comma  (see STRINGIFY_VA_ARG)
#ifndef STRINGIFY_VA_ARGS
#define STRINGIFY_VA_ARGS(...) , ##__VA_ARGS__
#endif // STRINGIFY_VA_ARGS


// Use PP_CONCAT instead of ## when necessary.
//
// MOTIVATION
//
// Macro expansion proceeds recursively in "layers."
// Token pasting prevents the preprocessor from performing macro expansion,
// therefore it is often necessary to delay token concatenation.
#ifndef PP_CONCAT
#define PP_CONCAT(X, ...) X##__VA_ARGS__
#endif // STRINGIFY_VA_ARGS

#ifndef STR_CONCAT
# define STR_CONCAT(a, b) STR_CONCAT_HELPER(a, b)
# define STR_CONCAT_HELPER(a, b) a##b
#endif

/// \note Use `UNREFERENCED_PARAMETER(x)` for ignoring function parameter.
/// \note Use `ignore_result(x)` for ignoring result of function call.
/// \note Use `ALLOW_UNUSED_LOCAL(x)` for ignoring local variable.
//
// Example:
// void onReceiveError(IoErrorCode error_code) {
//   config_->stats().downstream_rx_errors_.inc();
//   UNREFERENCED_PARAMETER(error_code);
// }
// struct TaskTraitsExtension {
//   template <class... ArgTypes,
//             class CheckCanMakeExtension =
//                 decltype(MakeTaskTraitsExtension(std::declval<ArgTypes>()...))>
//   constexpr TaskTraitsExtension(ArgTypes... args) {
//     ((void)(UNREFERENCED_PARAMETER(args)), ...);
//   }
// };
// windows.h defines UNREFERENCED_PARAMETER:
// #define UNREFERENCED_PARAMETER(P) {(P) = (P);}
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(X) ((void)(X))
#endif

#ifndef GEN_CAT
#define GEN_CAT(a, b) GEN_CAT_I(a, b)
#endif

#ifndef GEN_CAT_I
#define GEN_CAT_I(a, b) GEN_CAT_II(~, a ## b)
#endif

#ifndef GEN_CAT_II
#define GEN_CAT_II(p, res) res
#endif

#ifndef GEN_UNIQUE_NAME
#define GEN_UNIQUE_NAME(base) GEN_CAT(base, __COUNTER__)
#endif

// Lazily-initialized boolean value.
// Similar to BOOST_TRIBOOL.
enum TriBool { kNotSet = -1, kFalse = 0, kTrue = 1 };
