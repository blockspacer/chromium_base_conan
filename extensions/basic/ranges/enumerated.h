#pragma once

#include <iterator>

#include "base/ranges/ranges.h"
#include "base/ranges/functional.h"
#include "base/ranges/algorithm.h"

// Python-like enumerate function template for using range-for loops
// to iterate containers together with indices.
//
// USAGE
//
// const std::vector<std::string> strings
// {
//     "Hello", "World", "Yeah",
//     "Things", "Strings", "Vector"
// };
// for (const auto [index, str] : basis::ranges::enumerated(strings))
// {
//     std::cout << "index: " << index
//         << " string: " << str << '\n';
// }
//
// See for details:
// * http://reedbeta.com/blog/python-like-enumerate-in-cpp17/
// * https://faouellet.github.io/enumerate/
// * rsv::zip(rsv::indices, es), rsv::enumerate
//   https://github.com/ericniebler/range-v3/issues/785
// * https://infektor.net/posts/2017-03-31-range-based-enumerate.html

#if __has_include(<ranges>)
#include <ranges>
#endif // __has_include(<ranges>)

namespace basic {

namespace ranges {

#if __has_include(<ranges>)
namespace internal {

template <typename Rng>
class enumerated_t final
{
private:
  using Iter = std::ranges::iterator_t<Rng>;
  using Sent = std::ranges::sentinel_t<Rng>;
  using Ref = std::ranges::range_reference_t<Rng>;

public:
  struct sentinel final
  {
    Sent sent;
  };

  class iterator final
  {
  public:
    using difference_type = ptrdiff_t;
    using value_type = std::pair<size_t, Ref>;
    using pointer = value_type*;
    using reference = value_type;
    using iterator_category = std::input_iterator_tag;

  private:
    size_t index_ = 0;
    Iter it_;

  public:
    constexpr iterator() = default;
    explicit constexpr iterator(const Iter iter): it_(iter) {}

    constexpr reference operator*() { return { index_, *it_ }; }

    constexpr iterator& operator++()
    {
        ++index_;
        ++it_;
        return *this;
    }

    constexpr iterator operator++(int)
    {
        iterator res = *this;
        operator++();
        return res;
    }

    friend constexpr bool operator==(const iterator& lhs, const iterator& rhs) { return lhs.it_ == rhs.it_; }
    friend constexpr bool operator==(const iterator& it, const sentinel& sent) { return it.it_ == sent.sent; }
  };

  using const_iterator = iterator;

private:
  Rng range_; // Take ownership if rvalue, take reference if lvalue

public:
  explicit constexpr enumerated_t(Rng&& range): range_(static_cast<Rng&&>(range)) {}

  constexpr auto begin() { return iterator(std::begin(range_)); }
  constexpr auto end() { return sentinel{ std::end(range_) }; }
  constexpr auto cbegin() const { return iterator(std::cbegin(range_)); }
  constexpr auto cend() const { return sentinel{ std::cend(range_) }; }
  constexpr auto begin() const { return cbegin(); }
  constexpr auto end() const { return cend(); }
};

} // namespace internal

template <std::ranges::input_range Rng>
constexpr auto enumerate(Rng&& range) { return internal::enumerated_t<Rng>(std::forward<Rng>(range)); }

#else // __has_include(<ranges>)

/// \todo Due to C++14's lack of std::ranges concepts like sentinels.
/// Use only <ranges> when possible.
template <typename T,
          typename TIter = decltype(base::ranges::begin(std::declval<T>())),
          typename = decltype(base::ranges::end(std::declval<T>()))>
constexpr auto enumerated(T && iterable)
{
  struct iterator
  {
    size_t i;
    TIter iter;
    bool operator != (const iterator & other) const { return iter != other.iter; }
    void operator ++ () { ++i; ++iter; }
    auto operator * () const { return std::tie(i, *iter); }
  };
  struct iterable_wrapper
  {
    T iterable;
    auto begin() { return iterator{ 0, base::ranges::begin(iterable) }; }
    auto end() { return iterator{ 0, base::ranges::end(iterable) }; }
  };
  return iterable_wrapper{ std::forward<T>(iterable) };
}

#endif // __has_include(<ranges>)

} // namespace ranges

} // namespace basic
