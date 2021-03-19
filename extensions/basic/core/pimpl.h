#pragma once

/// \note This is `standalone` header that can depend only on `std`.
/// Don't `include` any non-standard files here.

// Define to 0 to remove extra |value_| member
// to Pimpl which is useful for being able to see the T*
// value at debug-time at the expense of increasing Pimpl's
// size by an extra pointer + potential
// alignment padding.
#if !defined(NDEBUG)
#if !defined(PIMPL_DEBUG_VALUE_MEMBER)
#define PIMPL_DEBUG_VALUE_MEMBER 1
#endif // PIMPL_DEBUG_VALUE_MEMBER
#endif // NDEBUG

#include <cstddef>
#include <type_traits>
#include <utility>

#if defined(PIMPL_DEBUG_VALUE_MEMBER) || !defined(NDEBUG)
#include <cassert>
#endif // PIMPL_DEBUG_VALUE_MEMBER

/// \note Run-time checks are expensive,
/// so we use them only for debug builds
#if !defined(NDEBUG)
  #define PIMPL_DEBUG_RUNTIME_VALIDATE(size, align) \
    debug_runtime_validate<size, align>();
#else // defined(NDEBUG)
  #define PIMPL_DEBUG_RUNTIME_VALIDATE(size, align) \
    (void)(0);
#endif // defined(NDEBUG)

/// \note Provide both run-time and compile-time checks
#define PIMPL_VALIDATE(size, align) \
  PIMPL_DEBUG_RUNTIME_VALIDATE(size, align); \
  static_validate<size, align>();

/// \note Implementation uses |aligned_storage_t| to
/// 1) reduce dynamic allocations
/// 2) improve performance by better cache locality
/// 3) remove allocations on the heap.
/// Allocations on the heap take precious clock cycles,
/// may grab a lock on the heap and thus limit parallelization
/// or can fail and throw exceptions.
/// \see https://cleeus.de/w/blog/2017/03/10/static_pimpl_idiom.html
/// \see section about Pimpl at https://habr.com/ru/company/hsespb/blog/481358/
/// \see https://www.youtube.com/watch?v=mkPTreWiglk
/// slides https://www.slideshare.net/corehard_by/c-antony-polukhin-corehard-autumn-2019

/// \note fast pimpl (aligned_storage) improves performance by better cache locality:
/// If you have this extra pointer to something allocated on the heap,
/// it's entirely possible that it will be allocated nowhere in memory near
/// the rest of the class. If you have an array of these then it gets worse.
/// This means that for cache access, any time you try to access
/// an instance of this class via pointer you'll (probably) get a cache miss,
/// load the class, then access the pointer resulting in another cache miss
/// and thus stalling the CPU twice (the first time you access the class).
/// Iterating over these things can incur this performance penalty on each access
/// to each object, particularly if these things are allocated
/// in arbitrary places on the heap.
/// \see about `Data Locality` https://gameprogrammingpatterns.com/data-locality.html

/// \note What to prefer - dynamic pimpl (heap allocation)
/// or fast pimpl (aligned_storage)?
/// Dynamic heap allocated pImpl pattern is great for those
/// who don't care about performance
/// but it's inappropriate for most header libraries.
/// You wouldn't want a library that hides the
/// implementation of std::vector for example.
/// With a visible implementation the compiler compile
/// e.g. operator[] down one x86 instruction.
/// With a pImpl pattern it will be an indirect function call
/// in all likelihood that will be hundreds of times slower.
/// It can make sense for libraries where every function
/// is really expensive anyway, but it's ruinous for STL and the like.

/// \note This is not a technique to use lightly.
/// Only use it when you really have performance requirements
/// that trump maintainability concerns.
/// If your implementation is big or changes often,
/// a classic PIMPL might be more appropriate
/// as adjusting the buffer sizes will become a tedious activity.

/// \note If you can't detect proper |Size| and |Alignment|,
/// than compile your app once and search for error message similar to
/// |basic::SizePolicy::Exact>::validate<1, 1>|
/// where |<1, 1>| - proper |Size| and |Alignment|

// Pimpl (Private IMPLemenation) is a class used to
// declare storage for an undefined type |T|,
// while providing a way to construct and then access
// |T|'s members through the type. It's similar to using
// |std::unique_ptr| except that it avoids heap allocation and access.
//
// |T| should be a forward-declared type for this class to be useful.
// If |Pimpl<T>| is a data member of |Foo|,
// then you'll need to define |Foo|'s constructor and destructor
// in the translation unit where |T| is defined.
// You can access members of T using Pimpl's pointer-like interface.

// Constructors, destructors and assignment operators of
// the front-end class holding the PImpl instance as a member must be
// defined in a place where T is a complete type - usually
// the .cpp file that includes T's definition.
// So, you cannot use the compiler-generated special member functions,
// and it is necessary to define even empty destructors in the .cpp file.

// PIMPL idiom may be used to to reduce the includes of a header.
// Instead of putting the implementation details of classes in the header,
// you move it into a source file (compilation unit).


// Typical usage:
//
// // Foo.h:
// #include <basic/core/pimpl.h>
//
// class Foo {
// public:
//   Foo();
//
//   ~Foo();
//
//   int foo();
//
// private:
//   class FooImpl;
//
//   ::basic::FastPimpl<
//       FooImpl
//       , /*Size*/1
//       , /*Alignment*/1
//     > m_impl;
// };
//
// // Foo.cpp:
// #include "Foo.h"
//
// class Foo::FooImpl
// {
//  public:
//   FooImpl() = default;
//
//   ~FooImpl() = default;
//
//   int foo();
// };
//
// int Foo::FooImpl::foo() {
//   return 1234;
// }
//
// Foo::Foo()
// {}
//
// Foo::~Foo()
// {}
//
// int Foo::foo() {
//   return m_impl->foo();
// }

namespace basic {

namespace pimpl {
  /// \note with SizePolicy::Exact your code becomes less portable,
  /// because different compilers may use different sizes and alignments
  /// for the same type.
  enum class SizePolicy {
    Exact,  // Size == sizeof(T)
    AtLeast // Size >= sizeof(T)
  };

  enum class AlignPolicy {
    Exact,  // Alignment == alignof(T)
    AtLeast // Alignment >= alignof(T)
  };
} // namespace pimpl

  /// \note Compiler cannot know the size and alignment requirements,
  /// so we must choose them manually.
  /// For the alignment, you can choose the platforms maximum alignment:
  /// |std::alignment_of<std::max_align_t>::value|.
  /// \note For the size, you can measure the size on one platform,
  /// then divide it by sizeof(void*) and express the size constant
  /// as a multiple of sizeof(void*).
  /// \note When size and/or alignment are wrong,
  /// you are doomed and your code will fail in mysterious ways.
  /// So it is essential to guarantee size
  /// and alignment by runtime asserts and static_asserts.
  template<
      typename T
      , size_t Size
      , size_t Alignment
      , pimpl::SizePolicy SizePolicyType = pimpl::SizePolicy::Exact
      , pimpl::AlignPolicy AlignPolicyType = pimpl::AlignPolicy::Exact
    >
  class FastPimpl {

    /* Required wrapper for if constexpr
     *
     * Is dependent on a template parameter.
     * Is used in static_assert in a false branch to produce a compile error
     * with message containing provided type.
     * See an example with dependent_false at https://en.cppreference.com/w/cpp/language/if
     *
     * if constexpr (std::is_same<T, someType1>) {
     * } else if constexpr (std::is_same<T, someType2>) {
     * } else {
     *     static_assert(dependent_false<T>::value, "unknown type");
     * }
     */
    template<class U>
    struct dependent_false : std::false_type {};

    // wrap static_assert into static_validate
    // for console message with desired sizeof in case of error
    /// \note Usage is completely safe,
    /// as the size and alignment are validated at compile time.
    /// \note static_assert used only for compile-time checks, so
    /// also don't forget to provide some runtime checks by assert-s
    /// \note we use template,
    /// so compiler will be able to print required |Size| and |Alignment|
    template<
      std::size_t ActualSize
      , std::size_t ActualAlignment
    >
    constexpr
    inline /* use `inline` to eleminate function call overhead */
    static
    void static_validate() noexcept
    {
      if constexpr (AlignPolicyType == pimpl::AlignPolicy::AtLeast)
      {
        static_assert(
          Alignment >= ActualAlignment
          , "Pimpl: Alignment must be at least alignof(T)");
      }
      else if constexpr (AlignPolicyType == pimpl::AlignPolicy::Exact)
      {
        static_assert(
          Alignment == ActualAlignment
          , "Pimpl: Alignment must be at exactly alignof(T)");
      }
      else
      {
        // dependent_false yields false only if
        // previous if branches yield false
        static_assert(dependent_false<T>::value);
      }

      if constexpr (SizePolicyType == pimpl::SizePolicy::AtLeast)
      {
        static_assert(
          Size >= ActualSize
          , "Pimpl: sizeof(T) must be at least 'Size'");
      }
      else if constexpr (SizePolicyType == pimpl::SizePolicy::Exact)
      {
        static_assert(
          Size == ActualSize
          , "Pimpl: sizeof(T) must be exactly 'Size'");
      }
      else
      {
        // dependent_false yields false only if
        // previous if branches yield false
        static_assert(dependent_false<T>::value);
      }
    }

    /// \note Using PImpl instances in the front-end class
    /// makes revisions of the latter potentially binary incompatible,
    /// if the size or alignment of the implementation object changes.
    /// You can mitigate this issue by providing a larger size
    /// than necessary, at the expense of wasted memory,
    /// so prefer SizePolicy::AtLeast where possible.
    /// \note |debug_runtime_validate| checks that
    /// revisions are binary compatible, but only in Debug builds
#if !defined(NDEBUG)
    template<
      std::size_t ActualSize
      , std::size_t ActualAlignment
    >
    constexpr
    inline /* use `inline` to eleminate function call overhead */
    static
    void debug_runtime_validate() noexcept
    {
      if constexpr (AlignPolicyType == pimpl::AlignPolicy::AtLeast)
      {
        assert(Alignment >= ActualAlignment
          && "Pimpl: Alignment must be at least alignof(T)"
          && " Alignment:" &&  Alignment
          && " alignment_of<T>:" &&  std::alignment_of<T>::value);
      }
      else if constexpr (AlignPolicyType == pimpl::AlignPolicy::Exact)
      {
        assert(Alignment == ActualAlignment
          && "Pimpl: Alignment must be at exactly alignof(T)"
          && " Alignment:" &&  Alignment
          && " alignment_of<T>:" &&  std::alignment_of<T>::value);
      }
      else
      {
        assert(false
          && "Wrong AlignPolicy");
      }

      if constexpr (SizePolicyType == pimpl::SizePolicy::AtLeast)
      {
        assert(Size >= ActualSize
          && "Pimpl: sizeof(T) must be at least 'Size'"
          && " Size:" && Size
          && " sizeof<T>:" && sizeof(T));
      }
      else if constexpr (SizePolicyType == pimpl::SizePolicy::Exact)
      {
        assert(Size == ActualSize
          && "Pimpl: sizeof(T) must be exactly 'Size'"
          && " Size:" &&  Size
          && " sizeof<T>:" && sizeof(T));
      }
      else
      {
        assert(false
          && "Wrong SizePolicy");
      }
    }
#endif // defined(NDEBUG)

    // may be used for debug purposes
    constexpr
    inline /* use `inline` to eleminate function call overhead */
    size_t GetSize() noexcept
    {
      return Size;
    }

    // may be used for debug purposes
    constexpr
    inline /* use `inline` to eleminate function call overhead */
    size_t GetAlign() noexcept
    {
      return Alignment;
    }
public:
    // Default constructor constructs T into storage,
    // so T must be defined
    // This class mimicks value semantics,
    // not pointer semantics. In particular,
    // the class invariant is that a PImpl object holds
    // a fully constructed T object at any time.
    // Its constructor forwards the arguments directly
    // to T's constructor.
    template<typename... Args>
    FastPimpl(Args&&... args)
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      Construct(std::forward(args)...);

#if PIMPL_DEBUG_VALUE_MEMBER
      SetValue();
#endif // PIMPL_DEBUG_VALUE_MEMBER
    }

    // Destructor invokes T's destructor, so T must be defined
    ~FastPimpl()
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      /// \note must call ~T() manually
      Destruct();
    }

    // Copy constructor
    FastPimpl(const FastPimpl& rhs)
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      CopyAssign(rhs);

#if PIMPL_DEBUG_VALUE_MEMBER
      SetValue();
#endif // PIMPL_DEBUG_VALUE_MEMBER
    }

    // Move constructor
    FastPimpl(FastPimpl&& rhs)
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      MoveAssign(std::move(rhs));

#if PIMPL_DEBUG_VALUE_MEMBER
      SetValue();
#endif // PIMPL_DEBUG_VALUE_MEMBER
    }

    // Copy assignment operator
    FastPimpl& operator=(const FastPimpl& rhs)
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      if (this != &rhs) {
        CopyAssign(rhs);
      }

      return *this;
    }

    // Move assignment operator
    FastPimpl& operator=(FastPimpl&& rhs)
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      if (this != &rhs)
      {
        MoveAssign(std::move(rhs));
      }

      return *this;
    }

    // casts |aligned_storage_t| to |T*|
    inline /* use `inline` to eleminate function call overhead */
    T* placement_cast() noexcept
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      return reinterpret_cast<T*>(&storage_);
    }

    // casts |aligned_storage_t| to |const T*|
    inline /* use `inline` to eleminate function call overhead */
    const T* placement_cast() const noexcept
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      return reinterpret_cast<const T*>(&storage_);
    }

    // Returns the implementation object for member access.
    constexpr T* operator->() noexcept
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      return placement_cast();
    }

    // Returns the implementation object for member access (const overload).
    constexpr const T* operator->() const noexcept
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      return placement_cast();
    }

    // Returns the implementation object.
    constexpr T& operator*() noexcept
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      return *placement_cast();
    }

    // Returns the implementation object (const overload).
    constexpr const T& operator*() const noexcept
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      return *placement_cast();
    }

private:
    // Construct implementation object, forwarding arguments
    template<typename... Args>
    inline /* use `inline` to eleminate function call overhead */
    void Construct(Args&&... args) noexcept
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      // uses placement new to save data into |aligned_storage_t|
      new (&storage_) T(std::forward(args)...);
    }

    inline /* use `inline` to eleminate function call overhead */
    void CopyAssign(const FastPimpl& rhs) noexcept
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      // uses placement new to save data into |aligned_storage_t|
      new (&storage_) T(*rhs.placement_cast());
    }

    inline /* use `inline` to eleminate function call overhead */
    void MoveAssign(FastPimpl&& rhs) noexcept
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      // uses placement new to save data into |aligned_storage_t|
      new (&storage_) T(std::move(*rhs.placement_cast()));
    }

    inline /* use `inline` to eleminate function call overhead */
    void Destruct() noexcept
    {
      PIMPL_VALIDATE(sizeof(T), alignof(T));

      // NOTE: If you get a compiler error about "use of undefined type" here,
      // it's likely because you need to define both constructor and destructor
      // for the owning type in the cpp file.
      // See usage notes at the top of this file.
      placement_cast()->~T();
    }

#if PIMPL_DEBUG_VALUE_MEMBER
    void SetValue() noexcept
    {
      value_ = placement_cast();
      assert(value_);
    }
#endif // PIMPL_DEBUG_VALUE_MEMBER

#if PIMPL_DEBUG_VALUE_MEMBER
    T* value_ = nullptr; // Not necessary but useful for debugging
#endif // PIMPL_DEBUG_VALUE_MEMBER

    /// \note |aligned_storage_t| ensures that memory is contiguous in the class,
    /// avoids cache miss.
    /// (comparing to dynamic heap allocation approach where impl may be in heap,
    /// but the class may be in stack or another region in heap)
    /// \see about `Data Locality` https://gameprogrammingpatterns.com/data-locality.html
    /// \note Keep in mind that since the implementation objects
    /// are constructed in-place, they increase the size of
    /// the front-end object. Its copy and move operations are
    /// thus more expensive than simple pointer copy.
    std::aligned_storage_t<Size, Alignment> storage_;
  };

} // namespace basic
