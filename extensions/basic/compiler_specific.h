#pragma once

#include "build/build_config.h"
#include "basic/wasm_util.h"

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
#define MSVC_SUPPRESS_WARNING(n) __pragma(warning(suppress:n))

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

// MSVC_PUSH_DISABLE_WARNING pushes |n| onto a stack of warnings to be disabled.
// The warning remains disabled until popped by MSVC_POP_WARNING.
#define MSVC_PUSH_DISABLE_WARNING(n) __pragma(warning(push)) \
                                     __pragma(warning(disable:n))

// Pop effects of innermost MSVC_PUSH_* macro.
#define MSVC_POP_WARNING() __pragma(warning(pop))

// Allows |this| to be passed as an argument in constructor initializer lists.
// This uses push/pop instead of the seemingly simpler suppress feature to avoid
// having the warning be disabled for more than just |code|.
//
// Example usage:
// Foo::Foo() : x(NULL), ALLOW_THIS_IN_INITIALIZER_LIST(y(this)), z(3) {}
//
// Compiler warning C4355: 'this': used in base member initializer list:
// http://msdn.microsoft.com/en-us/library/3c594ae3(VS.80).aspx
#define ALLOW_THIS_IN_INITIALIZER_LIST(code) \
  MSVC_PUSH_DISABLE_WARNING(4355)            \
  code MSVC_POP_WARNING()

#else  // Not MSVC

#define MSVC_SUPPRESS_WARNING(n)
#define MSVC_PUSH_DISABLE_WARNING(n)
#define MSVC_POP_WARNING()
#define MSVC_DISABLE_OPTIMIZE()
#define MSVC_ENABLE_OPTIMIZE()

#define ALLOW_THIS_IN_INITIALIZER_LIST(code) code

#endif  // COMPILER_MSVC

// These macros can be helpful when investigating compiler bugs or when
// investigating issues in local optimized builds, by temporarily disabling
// optimizations for a single function or file. These macros should never be
// used to permanently work around compiler bugs or other mysteries, and should
// not be used in landed changes.
#if !defined(OFFICIAL_BUILD)
#if defined(__clang__)
#define DISABLE_OPTIMIZE() __pragma(clang optimize off)
#define ENABLE_OPTIMIZE() __pragma(clang optimize on)
#elif defined(COMPILER_MSVC)
#define DISABLE_OPTIMIZE() __pragma(optimize("", off))
#define ENABLE_OPTIMIZE() __pragma(optimize("", on))
#else
// These macros are not currently available for other compiler options.
#endif
// These macros are not available in official builds.
#endif  // !defined(OFFICIAL_BUILD)

// BASE_BLOCK_TAIL_CALL_OPTIMIZATION
//
// Instructs the compiler to avoid optimizing tail-call recursion. Use of this
// macro is useful when you wish to preserve the existing function order within
// a stack trace for logging, debugging, or profiling purposes.
//
// Example:
//
//   int f() {
//     int result = g();
//     BASE_BLOCK_TAIL_CALL_OPTIMIZATION();
//     return result;
//   }
#if defined(__pnacl__)
#define BASE_BLOCK_TAIL_CALL_OPTIMIZATION() if (volatile int x = 0) { (void)x; }
#elif defined(__clang__)
// Clang will not tail call given inline volatile assembly.
#define BASE_BLOCK_TAIL_CALL_OPTIMIZATION() __asm__ __volatile__("")
#elif defined(__GNUC__)
// GCC will not tail call given inline volatile assembly.
#define BASE_BLOCK_TAIL_CALL_OPTIMIZATION() __asm__ __volatile__("")
#elif defined(_MSC_VER)
#include <intrin.h>
// The __nop() intrinsic blocks the optimisation.
#define BASE_BLOCK_TAIL_CALL_OPTIMIZATION() __nop()
#else
#define BASE_BLOCK_TAIL_CALL_OPTIMIZATION() if (volatile int x = 0) { (void)x; }
#endif

// BASE_CACHELINE_SIZE
//
// Explicitly defines the size of the L1 cache for purposes of alignment.
// Setting the cacheline size allows you to specify that certain objects be
// aligned on a cacheline boundary with `BASE_CACHELINE_ALIGNED` declarations.
// (See below.)
//
// NOTE: this macro should be replaced with the following C++17 features, when
// those are generally available:
//
//   * `std::hardware_constructive_interference_size`
//   * `std::hardware_destructive_interference_size`
//
// See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0154r1.html
// for more information.
#if defined(__GNUC__)
// Cache line alignment
#if defined(__i386__) || defined(__x86_64__)
#define BASE_CACHELINE_SIZE 64
#elif defined(__powerpc64__)
#define BASE_CACHELINE_SIZE 128
#elif defined(__aarch64__)
// We would need to read special register ctr_el0 to find out L1 dcache size.
// This value is a good estimate based on a real aarch64 machine.
#define BASE_CACHELINE_SIZE 64
#elif defined(__arm__)
// Cache line sizes for ARM: These values are not strictly correct since
// cache line sizes depend on implementations, not architectures.  There
// are even implementations with cache line sizes configurable at boot
// time.
#if defined(__ARM_ARCH_5T__)
#define BASE_CACHELINE_SIZE 32
#elif defined(__ARM_ARCH_7A__)
#define BASE_CACHELINE_SIZE 64
#endif
#endif // __GNUC__

#ifndef BASE_CACHELINE_SIZE
// A reasonable default guess.  Note that overestimates tend to waste more
// space, while underestimates tend to waste more time.
#define BASE_CACHELINE_SIZE 64
#endif

// BASE_CACHELINE_ALIGNED
//
// Indicates that the declared object be cache aligned using
// `BASE_CACHELINE_SIZE` (see above). Cacheline aligning objects allows you to
// load a set of related objects in the L1 cache for performance improvements.
// Cacheline aligning objects properly allows constructive memory sharing and
// prevents destructive (or "false") memory sharing.
//
// NOTE: this macro should be replaced with usage of `alignas()` using
// `std::hardware_constructive_interference_size` and/or
// `std::hardware_destructive_interference_size` when available within C++17.
//
// See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0154r1.html
// for more information.
//
// On some compilers, `BASE_CACHELINE_ALIGNED` expands to an `__attribute__`
// or `__declspec` attribute. For compilers where this is not known to work,
// the macro expands to nothing.
//
// No further guarantees are made here. The result of applying the macro
// to variables and types is always implementation-defined.
//
// WARNING: It is easy to use this attribute incorrectly, even to the point
// of causing bugs that are difficult to diagnose, crash, etc. It does not
// of itself guarantee that objects are aligned to a cache line.
//
// NOTE: Some compilers are picky about the locations of annotations such as
// this attribute, so prefer to put it at the beginning of your declaration.
// For example,
//
//   BASE_CACHELINE_ALIGNED static Foo* foo = ...
//
//   class BASE_CACHELINE_ALIGNED Bar { ...
//
// Recommendations:
//
// 1) Consult compiler documentation; this comment is not kept in sync as
//    toolchains evolve.
// 2) Verify your use has the intended effect. This often requires inspecting
//    the generated machine code.
// 3) Prefer applying this attribute to individual variables. Avoid
//    applying it to types. This tends to localize the effect.
#define BASE_CACHELINE_ALIGNED __attribute__((aligned(BASE_CACHELINE_SIZE)))
#elif defined(_MSC_VER)
#define BASE_CACHELINE_SIZE 64
#define BASE_CACHELINE_ALIGNED __declspec(align(BASE_CACHELINE_SIZE))
#else
#define BASE_CACHELINE_SIZE 64
#define BASE_CACHELINE_ALIGNED
#endif

// See also: CHECK(x), DCHECK(x)
//
// ASSUME_TRUE_OR_ASSERT(cond)
// Informs the compiler than a condition is always true and that it can assume
// it to be true for optimization purposes. The call has undefined behavior if
// the condition is false.
// In !NDEBUG mode, the condition is checked with an assert().
// NOTE: The expression must not have side effects, as it will only be evaluated
// in some compilation modes and not others.
//
// Example:
//
//   int x = ...;
//   ASSUME_TRUE_OR_ASSERT(x >= 0);
//   // The compiler can optimize the division to a simple right shift using the
//   // assumption specified above.
//   int y = x / 16;
//
#if !defined(NDEBUG)
#define ASSUME_TRUE_OR_ASSERT(cond) assert(cond)
#elif BASE_HAVE_BUILTIN(__builtin_assume)
#define ASSUME_TRUE_OR_ASSERT(cond) __builtin_assume(cond)
#elif defined(__GNUC__) || BASE_HAVE_BUILTIN(__builtin_unreachable)
#define ASSUME_TRUE_OR_ASSERT(cond)        \
  do {                                    \
    if (!(cond)) __builtin_unreachable(); \
  } while (0)
#elif defined(_MSC_VER)
#define ASSUME_TRUE_OR_ASSERT(cond) __assume(cond)
#else
#define ASSUME_TRUE_OR_ASSERT(cond)      \
  do {                                  \
    static_cast<void>(false && (cond)); \
  } while (0)
#endif
