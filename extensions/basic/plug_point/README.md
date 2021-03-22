## Key concepts: Plug points (code points to plug into)

* Plug points are similar to `sigslot`
* Plug points have priority
* Useful for fault-injection testing.
* Useful for plugin system (plugin may want to modify original logic, not only process events).
* Plug points use `std::unique_ptr<MyPlugPoint::Subscription>` similar to `base::CallbackList`

Plug points are similar to synchronous event dispatching or sigslot i.e. single plug point can have multiple receivers.

NOTE: It is also possible to use single plug point `StrongPlugPoint` (can store only one callback) and plug point without return value (`PlugPointNotifierStorage`, can store only callback<void(...)>)

`StrongPlugPoint` can store only one callback.

If you want to support multiple callbacks, than use `StrongPlugPointNotifier` or `StrongPlugPointRunner.

Registered callback can be removed by `StrongPlugPoint` or `StrongPlugPointRunner`.

Registered callback can NOT be removed by `StrongPlugPointNotifier`.

## What to use: `StrongPlugPoint`, `StrongPlugPointNotifier` or `StrongPlugPointRunner`

See `USE CASE` comments in `plug_point.hpp`

`StrongPlugPoint`:

```cpp
// USE CASE
//
// Multiple plugins can provide callback to process some file,
// but only one callback must be run to process file only once.
```

`StrongPlugPointNotifier`:

```cpp
// USE CASE
//
// Multiple plugins can provide callback to process some file,
// and all registered callbacks must be run to process file.
// All callbacks return `void` because they do not affect original logic
// (i.e. they watch data, but do not change it).
```

`StrongPlugPointRunner`:

```cpp
// USE CASE
//
// Multiple plugins can provide callback to process some file,
// and all registered callbacks must be run to process file.
// All callbacks return NOT `void` result because they DO affect original logic
// (i.e. they watch data AND change it).
```

## What to use: `plug points` or `fail points`

`fail points` can not return custom data or recieve input data (`fail point` is like simple bool).

So use `plug points` when you need to return custom data or recieve input data.

## What to use: `plug points` or `entt::dispatcher`?

`plug points` can NOT delay event processing i.e. plug points are synchronous. While `entt::dispatcher` is designed so as to be used in a loop (`entt::dispatcher` allows users both to trigger immediate events or to queue events to be published all together once per tick)

Receiver in `entt::dispatcher` does NOT return any value (e.g., returns void) i.e. event system well suited to add extra logic, while plug points can modify original logic.

`plug points` can control event propagation (unlike `sigslot`).

`event propagation` in `plug points` will continue until some callback returns value instead of `nullopt`.

If single plug point has multiple receivers - any receiver can stop event processing (or return `base::nullopt` to continue event propagation).

## Motivation: Event propagation

Main app sends event `backup started`

Plugin `Simple backup` receives event `backup started` with priority `MEDIUM`

Plugin `Premium backup` receives event `backup started` with priority `HIGH`

`Premium backup` want to stop event event propagation, so it returns true (not `base::nullopt`).

## Usage

```cpp
// my_plug_points.hpp
using PlugPointRunner_FP1
  = ::basic::StrongPlugPointRunner<
        class PlugPointFP1Tag
        , base::Optional<bool>(int, double)
      >;

std::vector<
  std::unique_ptr<
    PlugPointRunner_FP1::Subscription
  >
> runner_subscriptions;

// on `plugin A` thread, before app started
{
  // `plugin A` includes "my_plug_points.hpp"

  PlugPointRunner_FP1* fp1
    = PlugPointRunner_FP1::GetInstance(FROM_HERE, ::basic::PlugPointName{"fp1"});

  fp1->enable();

  runner_subscriptions.push_back(fp1->addCallback(basic::PlugPointPriority::High
    , base::BindRepeating(
      [
      ](
        int a
        , double b
      ) -> base::Optional<bool>
      {
        return base::nullopt;
      }
    )));

  runner_subscriptions.push_back(fp1->addCallback(basic::PlugPointPriority::Lowest
    , base::BindRepeating(
      [
      ](
        int a
        , double b
      ) -> base::Optional<bool>
      {
        return base::nullopt;
      }
    )));
}

// on `plugin B` thread, while app is running
{
  // `plugin B` includes "my_plug_points.hpp"

  PlugPointRunner_FP1* fp1
    = PlugPointRunner_FP1::GetInstance(FROM_HERE, ::basic::PlugPointName{"fp1"});
  const base::Optional<bool> pluggedReturn = fp1->RunUntilReturnValueOrNullopt(int{1}, double{3.0});
  if(UNLIKELY(pluggedReturn))
  {
    return pluggedReturn.value();
  }
}
```

## TIPS AND TRICKS: use macros

```cpp
STRONG_PLUG_POINT(PlugPoint_RecievedData, base::Optional<bool>(const std::string&));
// NOTE: Avoid `ASSIGN_PLUG_POINT`, prefer to cache pointer using `PLUG_POINT_INSTANCE`
ASSIGN_PLUG_POINT(plugPointPtr, flexnet::ws::PlugPoint_RecievedData);
RETURN_IF_PLUG_POINT_WITH_VALUE(plugPointPtr, REFERENCED(message));
```

## FAQ

* How to create event that's expected to happen once?

Use `base::OneShotEvent`
