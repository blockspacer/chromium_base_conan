// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_IMMEDIATE_CRASH_H_
#define BASE_IMMEDIATE_CRASH_H_

#include "build/build_config.h"

#if defined(OS_EMSCRIPTEN)
#include <emscripten/emscripten.h>
#endif

// Crashes in the fastest possible way with no attempt at logging.
// There are several constraints; see http://crbug.com/664209 for more context.
//
// - TRAP_SEQUENCE_() must be fatal. It should not be possible to ignore the
//   resulting exception or simply hit 'continue' to skip over it in a debugger.
// - Different instances of TRAP_SEQUENCE_() must not be folded together, to
//   ensure crash reports are debuggable. Unlike __builtin_trap(), asm volatile
//   blocks will not be folded together.
//   Note: TRAP_SEQUENCE_() previously required an instruction with a unique
//   nonce since unlike clang, GCC folds together identical asm volatile
//   blocks.
// - TRAP_SEQUENCE_() must produce a signal that is distinct from an invalid
//   memory access.
// - TRAP_SEQUENCE_() must be treated as a set of noreturn instructions.
//   __builtin_unreachable() is used to provide that hint here. clang also uses
//   this as a heuristic to pack the instructions in the function epilogue to
//   improve code density.
//
// Additional properties that are nice to have:
// - TRAP_SEQUENCE_() should be as compact as possible.
// - The first instruction of TRAP_SEQUENCE_() should not change, to avoid
//   shifting crash reporting clusters. As a consequence of this, explicit
//   assembly is preferred over intrinsics.
//   Note: this last bullet point may no longer be true, and may be removed in
//   the future.

// Note: TRAP_SEQUENCE Is currently split into two macro helpers due to the fact
// that clang emits an actual instruction for __builtin_unreachable() on certain
// platforms (see https://crbug.com/958675). In addition, the int3/bkpt/brk will
// be removed in followups, so splitting it up like this now makes it easy to
// land the followups.

// Crashes in the fastest possible way with no attempt at logging.
// There are different constraints to satisfy here, see http://crbug.com/664209
// for more context:
// - The trap instructions, and hence the PC value at crash time, have to be
//   distinct and not get folded into the same opcode by the compiler.
//   On Linux/Android this is tricky because GCC still folds identical
//   asm volatile blocks. The workaround is generating distinct opcodes for
//   each CHECK using the __COUNTER__ macro.
// - The debug info for the trap instruction has to be attributed to the source
//   line that has the CHECK(), to make crash reports actionable. This rules
//   out the ability of using a inline function, at least as long as clang
//   doesn't support attribute(artificial).
// - Failed CHECKs should produce a signal that is distinguishable from an
//   invalid memory access, to improve the actionability of crash reports.
// - The compiler should treat the CHECK as no-return instructions, so that the
//   trap code can be efficiently packed in the prologue of the function and
//   doesn't interfere with the main execution flow.
// - When debugging, developers shouldn't be able to accidentally step over a
//   CHECK. This is achieved by putting opcodes that will cause a non
//   continuable exception after the actual trap instruction.
// - Don't cause too much binary bloat.
#if defined(__EMSCRIPTEN__)
  // see emscripten/bits/signal.h
  #define TRAP_SEQUENCE() raise(SIGTRAP)
#elif defined(COMPILER_GCC)

#if defined(OS_NACL)

// Crash report accuracy is not guaranteed on NaCl.
#define TRAP_SEQUENCE1_() __builtin_trap()
#define TRAP_SEQUENCE2_() asm volatile("")

#elif defined(ARCH_CPU_X86_FAMILY)

// TODO(https://crbug.com/958675): In theory, it should be possible to use just
// int3. However, there are a number of crashes with SIGILL as the exception
// code, so it seems likely that there's a signal handler that allows execution
// to continue after SIGTRAP.
#define TRAP_SEQUENCE1_() asm volatile("int3")

#if defined(OS_APPLE)
// Intentionally empty: __builtin_unreachable() is always part of the sequence
// (see IMMEDIATE_CRASH below) and already emits a ud2 on Mac.
#define TRAP_SEQUENCE2_() asm volatile("")
#else
#define TRAP_SEQUENCE2_() asm volatile("ud2")
#endif  // defined(OS_APPLE)

#elif defined(ARCH_CPU_ARMEL)

// bkpt will generate a SIGBUS when running on armv7 and a SIGTRAP when running
// as a 32 bit userspace app on arm64. There doesn't seem to be any way to
// cause a SIGTRAP from userspace without using a syscall (which would be a
// problem for sandboxing).
// TODO(https://crbug.com/958675): Remove bkpt from this sequence.
#define TRAP_SEQUENCE1_() asm volatile("bkpt #0")
#define TRAP_SEQUENCE2_() asm volatile("udf #0")

#elif defined(ARCH_CPU_ARM64)

// This will always generate a SIGTRAP on arm64.
// TODO(https://crbug.com/958675): Remove brk from this sequence.
#define TRAP_SEQUENCE1_() asm volatile("brk #0")
#define TRAP_SEQUENCE2_() asm volatile("hlt #0")

#else

// Crash report accuracy will not be guaranteed on other architectures, but at
// least this will crash as expected.
#define TRAP_SEQUENCE1_() __builtin_trap()
#define TRAP_SEQUENCE2_() asm volatile("")

#endif  // ARCH_CPU_*

#elif defined(COMPILER_MSVC)

#if !defined(__clang__)

// MSVC x64 doesn't support inline asm, so use the MSVC intrinsic.
#define TRAP_SEQUENCE1_() __debugbreak()
#define TRAP_SEQUENCE2_()

#elif defined(ARCH_CPU_ARM64)

// Windows ARM64 uses "BRK #F000" as its breakpoint instruction, and
// __debugbreak() generates that in both VC++ and clang.
#define TRAP_SEQUENCE1_() __debugbreak()
// Intentionally empty: __builtin_unreachable() is always part of the sequence
// (see IMMEDIATE_CRASH below) and already emits a ud2 on Win64,
// https://crbug.com/958373
#define TRAP_SEQUENCE2_() __asm volatile("")

#else

#define TRAP_SEQUENCE1_() asm volatile("int3")
#define TRAP_SEQUENCE2_() asm volatile("ud2")

#endif  // __clang__

#else

#error No supported trap sequence!

#endif  // COMPILER_GCC

#define TRAP_SEQUENCE_() \
  do {                   \
    TRAP_SEQUENCE1_();   \
    TRAP_SEQUENCE2_();   \
  } while (false)

// CHECK() and the trap sequence can be invoked from a constexpr function.
// This could make compilation fail on GCC, as it forbids directly using inline
// asm inside a constexpr function. However, it allows calling a lambda
// expression including the same asm.
// The side effect is that the top of the stacktrace will not point to the
// calling function, but to this anonymous lambda. This is still useful as the
// full name of the lambda will typically include the name of the function that
// calls CHECK() and the debugger will still break at the right line of code.
#if !defined(COMPILER_GCC)

#define WRAPPED_TRAP_SEQUENCE_() TRAP_SEQUENCE_()

#else

#define WRAPPED_TRAP_SEQUENCE_() \
  do {                           \
    [] { TRAP_SEQUENCE_(); }();  \
  } while (false)

#endif  // !defined(COMPILER_GCC)

#if defined(__clang__) || defined(COMPILER_GCC)

// __builtin_unreachable() hints to the compiler that this is noreturn and can
// be packed in the function epilogue.
#define IMMEDIATE_CRASH()     \
  ({                          \
    WRAPPED_TRAP_SEQUENCE_(); \
    __builtin_unreachable();  \
  })

#else

// This is supporting non-chromium user of logging.h to build with MSVC, like
// pdfium. On MSVC there is no __builtin_unreachable().
#define IMMEDIATE_CRASH() WRAPPED_TRAP_SEQUENCE_()

#endif  // defined(__clang__) || defined(COMPILER_GCC)

#endif  // BASE_IMMEDIATE_CRASH_H_
