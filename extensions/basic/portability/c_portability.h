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

/* These definitions are in a separate file so that they
 * may be included from C- as well as C++-based projects. */

#include <basic/portability/config.h>

/**
 * Portable version check.
 */
#ifndef __GNUC_PREREQ
#if defined __GNUC__ && defined __GNUC_MINOR__
/* nolint */
#define __GNUC_PREREQ(maj, min) \
  ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
/* nolint */
#define __GNUC_PREREQ(maj, min) 0
#endif
#endif

// portable version check for clang
#ifndef __CLANG_PREREQ
#if defined __clang__ && defined __clang_major__ && defined __clang_minor__
/* nolint */
#define __CLANG_PREREQ(maj, min) \
  ((__clang_major__ << 16) + __clang_minor__ >= ((maj) << 16) + (min))
#else
/* nolint */
#define __CLANG_PREREQ(maj, min) 0
#endif
#endif

#if defined(__has_builtin)
#define BASIC_HAS_BUILTIN(...) __has_builtin(__VA_ARGS__)
#else
#define BASIC_HAS_BUILTIN(...) 0
#endif

#if defined(__has_feature)
#define BASIC_HAS_FEATURE(...) __has_feature(__VA_ARGS__)
#else
#define BASIC_HAS_FEATURE(...) 0
#endif

/* BASIC_SANITIZE_ADDRESS is defined to 1 if the current compilation unit
 * is being compiled with ASAN enabled.
 *
 * Beware when using this macro in a header file: this macro may change values
 * across compilation units if some libraries are built with ASAN enabled
 * and some built with ASAN disabled.  For instance, this may occur, if basic
 * itself was compiled without ASAN but a downstream project that uses basic is
 * compiling with ASAN enabled.
 *
 * Use BASIC_LIBRARY_SANITIZE_ADDRESS (defined in basic-config.h) to check if
 * basic itself was compiled with ASAN enabled.
 */
#ifndef BASIC_SANITIZE_ADDRESS
#if BASIC_HAS_FEATURE(address_sanitizer) || __SANITIZE_ADDRESS__
#define BASIC_SANITIZE_ADDRESS 1
#endif
#endif

/* Define attribute wrapper for function attribute used to disable
 * address sanitizer instrumentation. Unfortunately, this attribute
 * has issues when inlining is used, so disable that as well. */
#ifdef BASIC_SANITIZE_ADDRESS
#if defined(__clang__)
#if __has_attribute(__no_sanitize__)
#define BASIC_DISABLE_ADDRESS_SANITIZER \
  __attribute__((__no_sanitize__("address"), __noinline__))
#elif __has_attribute(__no_address_safety_analysis__)
#define BASIC_DISABLE_ADDRESS_SANITIZER \
  __attribute__((__no_address_safety_analysis__, __noinline__))
#elif __has_attribute(__no_sanitize_address__)
#define BASIC_DISABLE_ADDRESS_SANITIZER \
  __attribute__((__no_sanitize_address__, __noinline__))
#endif
#elif defined(__GNUC__)
#define BASIC_DISABLE_ADDRESS_SANITIZER \
  __attribute__((__no_address_safety_analysis__, __noinline__))
#endif
#endif
#ifndef BASIC_DISABLE_ADDRESS_SANITIZER
#define BASIC_DISABLE_ADDRESS_SANITIZER
#endif

/* Define a convenience macro to test when thread sanitizer is being used
 * across the different compilers (e.g. clang, gcc) */
#ifndef BASIC_SANITIZE_THREAD
#if BASIC_HAS_FEATURE(thread_sanitizer) || __SANITIZE_THREAD__
#define BASIC_SANITIZE_THREAD 1
#endif
#endif

#if BASIC_SANITIZE_THREAD
#define BASIC_DISABLE_THREAD_SANITIZER \
  __attribute__((no_sanitize_thread, noinline))
#else
#define BASIC_DISABLE_THREAD_SANITIZER
#endif

/**
 * Define a convenience macro to test when memory sanitizer is being used
 * across the different compilers (e.g. clang, gcc)
 */
#ifndef BASIC_SANITIZE_MEMORY
#if BASIC_HAS_FEATURE(memory_sanitizer) || __SANITIZE_MEMORY__
#define BASIC_SANITIZE_MEMORY 1
#endif
#endif

#if BASIC_SANITIZE_MEMORY
#define BASIC_DISABLE_MEMORY_SANITIZER \
  __attribute__((no_sanitize_memory, noinline))
#else
#define BASIC_DISABLE_MEMORY_SANITIZER
#endif

/**
 * Define a convenience macro to test when ASAN, UBSAN, TSAN or MSAN sanitizer
 * are being used
 */
#ifndef BASIC_SANITIZE
#if defined(BASIC_SANITIZE_ADDRESS) || defined(BASIC_SANITIZE_THREAD) || \
    defined(BASIC_SANITIZE_MEMORY)
#define BASIC_SANITIZE 1
#endif
#endif

#if BASIC_SANITIZE
#define BASIC_DISABLE_UNDEFINED_BEHAVIOR_SANITIZER(...) \
  __attribute__((no_sanitize(__VA_ARGS__)))
#else
#define BASIC_DISABLE_UNDEFINED_BEHAVIOR_SANITIZER(...)
#endif // BASIC_SANITIZE

#define BASIC_DISABLE_SANITIZERS                                 \
  BASIC_DISABLE_ADDRESS_SANITIZER BASIC_DISABLE_THREAD_SANITIZER \
      BASIC_DISABLE_UNDEFINED_BEHAVIOR_SANITIZER("undefined")

/**
 * Macro for marking functions as having public visibility.
 */
#if defined(__GNUC__)
#define BASIC_EXPORT __attribute__((__visibility__("default")))
#else
#define BASIC_EXPORT
#endif

// noinline
#ifdef _MSC_VER
#define BASIC_NOINLINE __declspec(noinline)
#elif defined(__GNUC__)
#define BASIC_NOINLINE __attribute__((__noinline__))
#else
#define BASIC_NOINLINE
#endif

// always inline
#ifdef _MSC_VER
#define BASIC_ALWAYS_INLINE __forceinline
#elif defined(__GNUC__)
#define BASIC_ALWAYS_INLINE inline __attribute__((__always_inline__))
#else
#define BASIC_ALWAYS_INLINE inline
#endif

// attribute hidden
#if defined(_MSC_VER)
#define BASIC_ATTR_VISIBILITY_HIDDEN
#elif defined(__GNUC__)
#define BASIC_ATTR_VISIBILITY_HIDDEN __attribute__((__visibility__("hidden")))
#else
#define BASIC_ATTR_VISIBILITY_HIDDEN
#endif

// An attribute for marking symbols as weak, if supported
#if BASIC_HAVE_WEAK_SYMBOLS
#define BASIC_ATTR_WEAK __attribute__((__weak__))
#else
#define BASIC_ATTR_WEAK
#endif

// Microsoft ABI version (can be overridden manually if necessary)
#ifndef BASIC_MICROSOFT_ABI_VER
#ifdef _MSC_VER
#define BASIC_MICROSOFT_ABI_VER _MSC_VER
#endif
#endif

//  BASIC_ERASE
//
//  A conceptual attribute/syntax combo for erasing a function from the build
//  artifacts and forcing all call-sites to inline the callee, at least as far
//  as each compiler supports.
//
//  Semantically includes the inline specifier.
#define BASIC_ERASE BASIC_ALWAYS_INLINE BASIC_ATTR_VISIBILITY_HIDDEN

//  BASIC_ERASE_HACK_GCC
//
//  Equivalent to BASIC_ERASE, but without hiding under gcc. Useful when applied
//  to a function which may sometimes be hidden separately, for example by being
//  declared in an anonymous namespace, since in such cases with -Wattributes
//  enabled, gcc would emit: 'visibility' attribute ignored.
//
//  Semantically includes the inline specifier.
#if defined(__GNUC__) && !defined(__clang__)
#define BASIC_ERASE_HACK_GCC BASIC_ALWAYS_INLINE
#else
#define BASIC_ERASE_HACK_GCC BASIC_ERASE
#endif

//  BASIC_ERASE_TRYCATCH
//
//  Equivalent to BASIC_ERASE, but for code which might contain explicit
//  exception handling. Has the effect of BASIC_ERASE, except under MSVC which
//  warns about __forceinline when functions contain exception handling.
//
//  Semantically includes the inline specifier.
#ifdef _MSC_VER
#define BASIC_ERASE_TRYCATCH inline
#else
#define BASIC_ERASE_TRYCATCH BASIC_ERASE
#endif
