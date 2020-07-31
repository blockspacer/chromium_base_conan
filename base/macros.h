// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file contains macros and macro-like constructs (e.g., templates) that
// are commonly used throughout Chromium source. (It may also contain things
// that are closely related to things that are commonly used that belong in this
// file.)

#ifndef BASE_MACROS_H_
#define BASE_MACROS_H_

// Put this in the declarations for a class to be uncopyable.
#define DISALLOW_COPY(TypeName) \
  TypeName(const TypeName&) = delete

// Put this in the declarations for a class to be unassignable.
#define DISALLOW_ASSIGN(TypeName) TypeName& operator=(const TypeName&) = delete

// Put this in the declarations for a class to be uncopyable and unassignable.
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  DISALLOW_COPY(TypeName);                 \
  DISALLOW_ASSIGN(TypeName)

// A macro to disallow all the implicit constructors, namely the
// default constructor, copy constructor and operator= functions.
// This is especially useful for classes containing only static methods.
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName() = delete;                           \
  DISALLOW_COPY_AND_ASSIGN(TypeName)

// Macro used to simplify the task of deleting the new and new[]
// operators i.e, disallow heap allocations.
/// \note accepts |ClassName| argument
/// for documentation purposes and to avoid copy-n-paste errors
#define DISALLOW_NEW_OPERATOR(ClassName)                         \
  static void* operator new(size_t) = delete;   \
  static void* operator new[](size_t) = delete

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
#if defined(__cplusplus) && defined(__has_cpp_attribute)
// NOTE: requiring __cplusplus above should not be necessary, but
// works around https://bugs.llvm.org/show_bug.cgi?id=23435.
#define HAVE_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#define HAVE_CPP_ATTRIBUTE(x) 0
#endif // defined(__cplusplus) && defined(__has_cpp_attribute)

#if defined(UNDEFINED_BEHAVIOR_SANITIZER)

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
  there’s no problem,
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

#if defined(THREAD_SANITIZER)

#define NO_SANITIZE_THREAD \
  __attribute__((no_sanitize_thread))

#else

#define NO_SANITIZE_THREAD

#endif // THREAD_SANITIZER

#if defined(MEMORY_SANITIZER)

#define NO_SANITIZE_MEMORY \
  __attribute__((no_sanitize_memory))

#else

#define NO_SANITIZE_MEMORY

#endif // MEMORY_SANITIZER

#if defined(ADDRESS_SANITIZER)

#define NO_SANITIZE_ADDRESS \
  __attribute__((no_sanitize_address))

#else

#define NO_SANITIZE_ADDRESS

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
#if HAVE_ATTRIBUTE(unused) || (defined(__GNUC__) && !defined(__clang__))
#undef ATTRIBUTE_UNUSED
#define ATTRIBUTE_UNUSED __attribute__((__unused__))
#else
#define ATTRIBUTE_UNUSED
#endif

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
#else
#define ATTRIBUTE_NORETURN
#endif

// documents that moved-from object will be in the same state
// as if constructed using moved-from object the constructor.
/// \example boost.org/doc/libs/1_54_0/doc/html/boost_asio/reference/basic_stream_socket/basic_stream_socket/overload5.html
/// i.e. it does not actually destroy |stream| by |move|
#define COPY_ON_MOVE(x) x

// documents that value must be created/modified/used
// only from one base::Sequence
/// \todo integrate with thread-safety annotations
#define LIVES_ON(sequenceChecker)

// similar to __attribute__((warn_unused_result))
/// \usage (note order restriction)
/// [[nodisard]] extern bool foo();
/// [[nodisard]] inline bool foo();
/// [[nodisard]] static bool foo();
/// [[nodisard]] static inline bool foo();
/// [[nodisard]] virtual bool foo();
#define MUST_USE_RETURN_VALUE \
  [[nodiscard]] /* do not ignore return value */

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

// Documents that value may not be thread-safe in general,
// but because it can be modified only during
// `initialization` and `teardown` steps
// it can be used by multiple threads during `running` step.
/// \note It means that object must exist during `running` step,
/// but it does NOT mean that internals of the object are thread-safe.
#define GLOBAL_THREAD_SAFE_LIFETIME(x) x

// Documents that value can NOT be used from
// any thread without extra thread-safety checks.
// i.e. take care of possible thread-safety bugs.
// Usually it means that value MUST be guarded by some mutex lock
// OR modified only during `initialization` step.
/// \note prefer sequence checkers or
/// <base/thread_collision_warner.h> to it if possible
#define NOT_THREAD_SAFE_LIFETIME(x) x

// Documents that function does not perform thread-safety checks.
#define NOT_THREAD_SAFE_FUNCTION(x) x

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

/// \note prefer |MoveOnly| to |COPIED|
// Documents that value will be copied.
/// \note use it to annotate arguments that are bound to function
#define COPIED(x) x

/// \note prefer `REFERENCED` to `RAW_REFERENCED`
// Documents that value will be used as alias
// i.e. another name for an already existing variable.
#define RAW_REFERENCED(x) x

// Documents that value will be used as alias
// i.e. another name for an already existing variable.
/// \note use it to annotate arguments that are bound to function
#define REFERENCED(x) std::ref(x)

#define CONST_REFERENCED(x) std::cref(x)

// Documents that value has shared storage
// like shaped_ptr, scoped_refptr, etc.
// i.e. that object lifetime will be prolonged.
/// \note use it to annotate arguments that are bound to function
#define SHARED_LIFETIME(x) x

// Documents that function returns promise,
// so next ThenOn/ThenHere will `wait` (asynchronously) for NESTED promise
#define NESTED_PROMISE(x) x

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
 * @usage
  LOG_CALL(VLOG(9));
 **/
#define LOG_CALL(LOG_STREAM) \
  LOG_STREAM \
    << "called " \
    << FROM_HERE.ToString()

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
# if __has_attribute(enable_if)
#  define BAD_CALL_IF(expr, msg) \
    __attribute__((enable_if(expr, "Bad call trap"), unavailable(msg)))
# endif
#endif

#endif  // BASE_MACROS_H_
