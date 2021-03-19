#pragma once

#include <type_traits>

// USAGE
//
// template <typename Func>
// CONCEPT( requires std::is_nothrow_move_constructible_v<Func> )
// auto
// moveFunc(Func func) noexcept {
//   static_assert(std::is_nothrow_move_constructible_v<Func>);
//   return std::move(func);
// }
#if defined(__cpp_concepts) && __cpp_concepts >= 201907

#define CONCEPT(x...) x
#define NO_CONCEPT(x...)

#else // __cpp_concepts

#define CONCEPT(x...)
#define NO_CONCEPT(x...) x

#endif // __cpp_concepts

// USAGE
//
// START_TEMPLATE(typename ElementT)
// CONCEPT_REQUIRES(std::is_default_constructible_v<ElementT>)
// class RegistryList {};
//
// START_TEMPLATE(int I)
// CONCEPT_REQUIRES(sizeof(T) == 1)
// std::integral_constant<int, 5> requiresTest() {
//     return {};
// }
//
// START_TEMPLATE(int I)
// CONCEPT_REQUIRES(-10 < I && I < 0)
// std::integral_constant<int, 14> requiresTest() {
//     return {};
// }
//
// START_TEMPLATE(int I)
// CONCEPT_REQUIRES(I >= 0)
// std::integral_constant<int, 4> requiresTest();
//
// START_TEMPLATE(int I)
// CONCEPT_REQUIRES_OUT_OF_LINE_DEF(I >= 0)
// std::integral_constant<int, 4> requiresTest() {
//     return {};
// }
#if defined(__cpp_concepts)

//
// These macros provide an emulation of C++20-style requires-clauses and requires-expression. These
// are part of the "Concepts" feature, however this does not provide a way to emulate the definition
// of actual concepts. You will need to continue either using the std type_traits, or define your
// own constexpr bools.
//
// The emulation does allow overloading based on requirements, however because it doesn't have a way
// to define actual concepts, there is no subsumption/refinement rules. In other words, you are
// responsible for ensuring that only one overload (with the same arguments) will match a given
// call, the compiler won't select the best one. eg, with real concepts support, you can overload
// these functions and it will do the right thing:
//      template <typename T>                                void doThing(T);
//      template <typename T> requires(IsFoo<T>)             void doThing(T);
//      template <typename T> requires(IsFoo<T> && IsBar<T>) void doThing(T);
//
// With the emulation, you need to explicitly make them all mutually exclusive:
//      template <typename T> requires(!IsFoo<T>)              void doThing(T);
//      template <typename T> requires( IsFoo<T> && !IsBar<T>) void doThing(T);
//      template <typename T> requires( IsFoo<T> &&  IsBar<T>) void doThing(T);
//

/**
 * Use "START_TEMPLATE(typename T)" instead of "template <typename T>" when you are using the REQUIRES
 * macros.
 */
#define START_TEMPLATE(...) template <__VA_ARGS__>

/**
 * Disables this template if the argument evaluates to false at compile time.
 *
 * Use the OUT_OF_LINE_DEF version when you are defining the template out of line following an
 * earlier forward declaration.
 *
 * Must be placed between the START_TEMPLATE() macro and the declaration (ie it doesn't support the
 * "trailing requires clause" style). Can not be used to enable/disable explicit specializations,
 * they will need to match exactly one version of the primary template.
 *
 * Be careful will top-level commas, because everything before the comma will be ignored.
 *
 * Example (you could also just define the body with the initial declaration):
 *
 *      START_TEMPLATE(typename Callback)
 *      CONCEPT_REQUIRES(std::is_invocable_v<Callback, Status>)
 *      void registerCallback(Callback&& cb);
 *
 *      START_TEMPLATE(typename Callback)
 *      CONCEPT_REQUIRES_OUT_OF_LINE_DEF(std::is_invocable_v<Callback, Status>)
 *      void registerCallback(Callback&& cb) { stuff }
 */
#define CONCEPT_REQUIRES(...) requires(__VA_ARGS__)
#define CONCEPT_REQUIRES_OUT_OF_LINE_DEF(...) requires(__VA_ARGS__)

/**
 * Use this on a non-template to impose requirements on it. With *very* few exceptions, this should
 * only be used on non-template methods inside of a class template.
 *
 * Due to limitations of the emulation, you cannot forward declare methods this is used with.
 *
 * Example:
 *      template <typename T>
 *      struct Holder {
 *          CONCEPT_REQUIRES_FOR_NON_TEMPLATE(sizeof(T) == 4)
 *          void doThing() {}
 *
 *          CONCEPT_REQUIRES_FOR_NON_TEMPLATE(sizeof(T) == 8)
 *          void doThing() {}
 *      };
 */
#define CONCEPT_REQUIRES_FOR_NON_TEMPLATE(...) \
    template <int... ignoreThisArg>    \
    requires(__VA_ARGS__)

/**
 * Defines a boolean trait that is true if a set of expressions compiles.
 *
 * Args (some are lists that must be wrapped in parens):
 *      name          - name of the template
 *      (tpl_params)  - template parameters for the trait definition (ie with typename)
 *      (tpl_args)    - template arguments for a usage of the trait (ie without typename)
 *      (decls)       - declarations of variables used in the trait's expression
 *      exprs         - the expressions that are tested to see if they compile
 *
 * Examples (the // separator tends to improve readability with clang-format):
 *      BASIC_MAKE_BOOL_TRAIT(isAddable,
 *                            (typename LHS, typename RHS),
 *                            (LHS, RHS),
 *                            (LHS& mutableLhs, const LHS& lhs, const RHS& rhs),
 *                            //
 *                            mutableLhs += rhs);
 *                            lhs + rhs,
 *
 *      BASIC_MAKE_BOOL_TRAIT(isCallable,
 *                            (typename Func, typename... Args),
 *                            (Func, Args...),
 *                            (Func& func, Args&&... args),
 *                            //
 *                            func(args...));
 *
 * WARNING: This only works for compiler failures in the "immediate context" of the expression.
 *          For example, if a function is templated to take all arguments, but the body will fail to
 *          compile with some, isCallable will either return true or cause a hard compile error.
 *          These should only be used with well-constrained functions.
 *
 * We need to use a real concept to work around https://gcc.gnu.org/bugzilla/show_bug.cgi?id=90287.
 * Still using a constexpr bool in the public API for consistency with the no-concepts
 * implementation so it doesn't behave like a concept during normalization and overload resolution.
 */
#define BASIC_MAKE_BOOL_TRAIT(name, tpl_params, tpl_args, decls, /*exprs*/...) \
    template <BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND tpl_params>                  \
    BASIC_MAKE_BOOL_TRAIT_CONCEPTS_KEYWORD make_trait_impl_##name##_concept =  \
        requires(BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND decls) {                  \
        {__VA_ARGS__};                                                         \
    };                                                                         \
    template <BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND tpl_params>                  \
    constexpr inline bool name =                                               \
        make_trait_impl_##name##_concept<BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND tpl_args>

// Everything under here is an implementation detail, so you should only need to read it if you are
// looking to change or add something. The whole public API is described above.

#if __cpp_concepts <= 201507  // gcc-8 still uses concepts TS syntax.
#define BASIC_MAKE_BOOL_TRAIT_CONCEPTS_KEYWORD concept bool
#else
#define BASIC_MAKE_BOOL_TRAIT_CONCEPTS_KEYWORD concept
#endif

#else // __cpp_concepts

// This is the polyfill for when not using concepts-enabled compilers.

#define START_TEMPLATE(...) template <__VA_ARGS__,  // intentionally left open; closed below.

// Note: the best error messages are generated when __VA_ARGS__ is the direct first argument of
// enable_if_t, or directly inside of the parens of a decltype without an extra set of parens.
// If you want to alter these, be sure to check error messages on clang and gcc!
#define CONCEPT_REQUIRES(...) std::enable_if_t<(__VA_ARGS__), int> = 0 >

// Same as above, but without the default argument since some compilers (correctly) disallow
// repeating the default argument on the definition.
#define CONCEPT_REQUIRES_OUT_OF_LINE_DEF(...) std::enable_if_t<(__VA_ARGS__), int>>

// Need the second arg in the template to depend on both a template argument (so it is dependent),
// and the current line number (so it can be overloaded). The __VA_ARGS__ expression will generally
// be a constant expression at parse time (or class instantiation time), so in order to allow more
// than one overload that is false, we need to defer the evaluation of the outer enable_if_t to
// function instantiation time.
#define CONCEPT_REQUIRES_FOR_NON_TEMPLATE(...)        \
    template <int ignoreThisArg = 0,          \
              std::enable_if_t<(__VA_ARGS__), \
                               std::enable_if_t<(ignoreThisArg * __LINE__) == 0, int>> = 0>

// Works by declaring a function template taking `decls` arguments and using expression-SFINAE using
// `exprs` on the return type. A bool is defined as true if it is possible to instantiate the
// template with the supplied arguments by taking its address.
#define BASIC_MAKE_BOOL_TRAIT(name, tpl_params, tpl_args, decls, /*exprs*/...)            \
    template <BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND tpl_params>                             \
    auto make_trait_impl_##name##_fn(BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND decls)           \
        ->decltype(__VA_ARGS__);                                                          \
                                                                                          \
    template <typename ALWAYS_VOID, BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND tpl_params>       \
    constexpr inline bool make_trait_impl_##name##_bool = false;                          \
                                                                                          \
    template <BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND tpl_params>                             \
    constexpr inline bool make_trait_impl_##name##_bool<                                  \
        std::void_t<decltype(                                                             \
            &make_trait_impl_##name##_fn<BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND tpl_args>)>, \
        BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND tpl_args> = true;                             \
                                                                                          \
    template <BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND tpl_params>                             \
    constexpr inline bool name =                                                          \
        make_trait_impl_##name##_bool<void, BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND tpl_args>

#endif

// Strips off wrapping parens used to group some arguments. Use *without* any parens.
#define BASIC_MAKE_BOOL_TRAIT_HELPER_EXPAND(...) __VA_ARGS__
