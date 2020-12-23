#pragma once

// Turns nested function calls to linear pipelines.
//
// `pipelined(x) | y(z)` is syntactic sugar for `y(x, z)`.
//
// USAGE
//
//  return get_value()
//      | base::pipelined(add, 5)
//      | base::pipelined(square)
//      | base::pipelined(add, 6);
//
// Inspired by pipeline style from <ranges>.
//
// See for details:
// * https://quuxplusone.github.io/blog/2020/04/10/pipeline-operator-examples/
//
#include <tuple>

namespace base {

namespace internal {

template <typename Inv, typename... Ts>
class pipelined_t
{
private:
  Inv invocable_;
  std::tuple<Ts...> args_;

public:
  explicit constexpr pipelined_t(Inv&& invocable, Ts&&... args):
    invocable_(static_cast<Inv>(invocable)),
    args_(static_cast<Ts>(args)...) {}

  template <typename... Us>
  constexpr decltype(auto) operator()(Us&&... args)
  {
    static_assert(std::is_invocable_v<Inv&&, Us&&..., Ts&&...>,
                  "pipelined requires invocable");

    return std::apply([&]<typename... Bs>(Bs&&... bound_args)
    {
      return std::invoke(static_cast<Inv&&>(invocable_),
        std::forward<Us>(args)..., std::forward<Bs>(bound_args)...);
    }, args_);
  }

  template <typename U>
  friend constexpr decltype(auto) operator|(U&& arg, pipelined_t&& part)
  {
    static_assert(std::is_invocable_v<Inv&&, U&&, Ts&&...>,
                  "pipelined requires invocable");

    return std::move(part)(std::forward<U>(arg));
  }
};

} // namespace internal

template <typename Inv, typename... Ts>
constexpr auto pipelined(Inv&& invocable, Ts&&... args)
{
  return internal::pipelined_t<Inv, Ts...>(
    std::forward<Inv>(invocable), std::forward<Ts>(args)...);
}

} // namespace base
