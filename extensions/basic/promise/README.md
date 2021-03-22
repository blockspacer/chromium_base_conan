# About

Our promises implementation based on code from https://github.com/chromium/chromium/commit/112c5128dc6bc95cd7bfadbe5ebba15a226ece4b#diff-dadf55e86fb5f4ed44cff9f8318c821d

You can find code example with promises in unit tests from https://github.com/chromium/chromium/commit/112c5128dc6bc95cd7bfadbe5ebba15a226ece4b#diff-dadf55e86fb5f4ed44cff9f8318c821d and https://chromium-review.googlesource.com/c/chromium/src/+/1054068

Note that original `chromium-review` decided to delete promises https://chromium-review.googlesource.com/c/chromium/src/+/1916479

But promises are not completely banned in chromium - you can find chromium-related code with custom promises like https://github.com/ccuGabinete/baseNotificado/blob/880e65bcd0287c7853792ece3f1fee190ecbadbd/electron-master/shell/browser/api/atom_api_net_log.cc#L66 or https://github.com/ccuGabinete/baseNotificado/blob/880e65bcd0287c7853792ece3f1fee190ecbadbd/electron-master/shell/browser/api/atom_api_net_log.cc#L66 or https://github.com/blockspacer/skia-opengl-emscripten/blob/d14632fbeeeb5e0c5739c796a5f237946102c08e/src/cobalt/src/cobalt/script/promise.h

You can find code example with promises (before/after) on https://chromium-review.googlesource.com/c/chromium/src/+/1062245

Promises forum topics: https://groups.google.com/a/chromium.org/forum/#!topic/cxx/rd4LkcWl0ng and https://groups.google.com/a/chromium.org/forum/#!topic/chromium-dev/4WpWjIzZmtg

C++ Promises for Chromium - Google Docs https://docs.google.com/document/d/1l12PAJgEtlrqTXKiw6mk2cR2jP7FAfCCDr-DGIdiC9w/

Tracking bug for all promises related patches - https://bugs.chromium.org/p/chromium/issues/detail?id=906125

## Performance

Designed for NOT performance-critical code.

Uses dynamic allocations, so avoid it in hot-code-paths.

Also `Promise` has shared ownership (`shared_ptr` is anti-pattern).

Performance overhead expected to be NOT large (TODO: measure).

## Avoid antipattern: The Broken Chain

The problem:

```cpp
auto anAsyncCall() {
  Promise<void, std::unique_ptr<Err>> promise1 = doSomethingAsync();
  promise1.ThenOn(task_runner2, FROM_HERE, BindOnce([]() {
                   somethingComplicated();
                 }));
  // The problem here is that any error raised in the somethingComplicated()
  // method will not get caught.
  return promise1;
}
```

The fix:

```cpp
auto anAsyncCall() {
  Promise<void, std::unique_ptr<Err>> promise1 = doSomethingAsync();
  auto promise2 = promise1.ThenOn(task_runner2, FROM_HERE, BindOnce([]() {
                    somethingComplicated();
                  }));
  return promise2;
}
```

## Alternatives

https://github.com/grantila/q uses similar approach, so you can find it's docs useful, see http://libq.io

## Promises codestyle

Note that:

- For now we prefer `base::ManualPromiseResolver` and callback-style approach (`PostTask` does not return promise). That will allow us to integrate with some third-party API without need for `base::Promise` or switch to other promises implementation (for example, to support fibers or coroutines).
- Use `base::PostPromise` from `post_promise.h` carefully, prefer `base::ManualPromiseResolver`
- Use `unique_ptr` to prevent copy in `.ThenOn(...)` for passed data
- Use `scoped_refptr` to prevent copy in `.ThenOn(...)` for shared data
- Use `weak_ptr_factory_.GetWeakPtr()` to cancel callback
- Always specify `base::PromiseResult` where possible. Example: `base::PromiseResult< /*ResolveType*/ ... , /*RejectType*/ base::NoReject>`
- Always specify `base::Resolved` where possible. Example: `base::Resolved<Type>(val)`. Same for `base::Rejected`
- Prefer code without `reject` where possible. Use `base::NoReject`
- Don't forget that `p.ThenHere(...); p.ThenHere(...)` is different from `p.ThenHere(...).ThenHere(...)`

See examples section below.

## Avoid memory leaks

Cancel promises via `OnCanceled` that are not resolved.

```cpp
promise->OnCanceled();
```

Note that `OnCanceled` will be automatically called in `Promise` destructor.

Handle cancellation to make sure we don't leak memory due to
promises that will never be resolved. The semantics are described in the
follow on patch. We'll need to decide if we want to expose this on the
Promise<> template or not.

## Brief

```cpp
// Inspired by ES6 promises, Promise<> is a PostTask based callback system for
// asynchronous operations. An operation can resolve (succeed) with a value and
// optionally reject (fail) with a different result. Interested parties can be
// notified using ThenOn() and CatchOn() which schedule callbacks to run as
// appropriate on the specified task runner or task traits. If a promise is
// settled when a ThenOn() / CatchOn() / FinallyOn() statement is added, the
// callback will be posted immediately, otherwise it has to wait.
//
// Promise<> is copyable, moveable and thread safe. Under the hood
// AbstractPromise is refcounted so retaining multiple Promises<> will
// prevent that part of the promise graph from being released.
```

```cpp
//
// prints 101
//
task_runner->PostTask(FROM_HERE, base::Bind([](){ return 10; }))
    .ThenOn(task_runner2, FROM_HERE, base::Bind([](int i){ return i * i; }))
    .ThenOn(task_runner3, FROM_HERE, base::Bind([](int i){ return i + 1; }))
    .ThenHere(FROM_HERE, base::Bind([](int i){ LOG(INFO) << i; }));
```

```cpp
ThenHere(...) is a short version of promise.ThenOn(SequencedTaskRunnerHandle::Get(),...)
```

```cpp
Preventing use after move
The following code is unsafe and it is likely the second callback would segfault. However in debug builds ThenHere/ThenOn and CatchHere/CatchOn will detect if more than one has been registered for a move only type and if so DCHECK.

Promise<std::unique_ptr<int>> p = ThreadTaskRunnerHandle::Get()->PostTask(
    FROM_HERE, BindOnce([]() { return std::make_unique<int>(123); }));

p.ThenHere(FROM_HERE,
           BindOnce([](std::unique_ptr<int> i) { // Do something with i. }));


// This will DCHECK
// cause it passes |unique_ptr| twice
p.ThenHere(FROM_HERE,
           BindOnce([](std::unique_ptr<int> i) { // Do something with i. }));
```

```cpp
`.ThenHere` returns `Promise` - because of that code below:

// subscribed to same promise (for example, different plugins may want to be notified with COPY of ResolveType from same promise)
p.ThenHere(...)
p.ThenHere(...)

is not equal to code below:

// subscribed to chain of diferent promises (for example, do async http request, send collected data to process via remote endpoint, subscribe to `data finished processing` event via promise)
p
  .ThenHere(...)
  .ThenHere(...)
```

```cpp
Promise<ResolveType>              // can not reject
Promise<ResolveType, RejectType>  // can reject (must have a catch)

task_runner->PostTask(FROM_HERE, base::Bind([]() -> PromiseResult<int, std::string> {
      int result;

      ....

      if (success) return result;

      return "Oh no!";
    }))
    .ThenHere(FROM_HERE, base::Bind([](int i ){/* Do something with |i| */}))
    .CatchHere(FROM_HERE, base::Bind([](const std::string& err) {/* Do something with |err| */})));
```

```cpp
We should not get to last ThenHere, the promise was rejected below:

Promise<int, std::string> p;
p.ThenHere(
    FROM_HERE, base::BindOnce([](int result) { return result + 1; }))
 .ThenHere(
    FROM_HERE, base::BindOnce([](int result) { return result + 1; }))
 .ThenHere(
    FROM_HERE, base::BindOnce([](int result) -> PromiseResult<int, std::string> {
    // We can reject by returning the reject type here.
    return std::string("Oh no!");
 }))
  // Just like in ES6 a Then() can be passed resolve and reject callbacks.
 .ThenHere(
      FROM_HERE, base::BindOnce([](int result) {
        // We shouldn't get here, the promise was rejected!
      }),
      base::BindOnce([](const std::string& err) {
        EXPECT_EQ("Oh no!", err);
      }));
```

```cpp
What if ResolveType and RejectType are the same?

Use base::Resolve<> and base::Rejected<> to disambiguate

Promise<int> p = ...;
p.promise()
    .ThenHere(FROM_HERE, BindOnce([](int i) -> PromiseResult<Value, Value> {
                if ((i % 2) == 1)
                  return Resolved<Value>("Success it was odd.");
                return Rejected<Value>("Failure it was even.");
              }))
    .ThenHere(FROM_HERE,
              BindOnce([](Value result) { /* on success */ }),
              BindOnce([](Value result) { /* on failure */ }));
```

```cpp
use of base::Resolved<> and base::Rejected<> to disambiguate.  E.g.:

Promise<int> a;
...
Promise<void, void> b = a.ThenHere(
    FROM_HERE, base::BindOnce([](int result) -> PromiseResult<void, void> {
      if (result % 2 == 0)
        return base::Resolved<void>();
      else
        return base::Rejected<void>();
    });

E.g.
base::PromiseResult<int, std::string> Handler() {
  if (foo) return base::Resolved<int>(123);
  if (bar) return base::Rejected<string>("Whooops");
  if (baz) {
    return 123; // Resolve
  } else {
    return std::string("Oh no");  // Reject
  }
}

If a callback always returns a promise, this syntax can be used:

base::Promise<int, std::string> Handler() {
  return task_runner->PostTask(FROM_HERE, base::BindOnce([](){
    // Do something.
  });
}
```

base::NoReject type which disables CatchOn. For convenience the Promise<> template sets the default value of the RejectType as base::NoReject, allowing Promise<MyType> to represent a promise that can't be rejected.

```cpp
The Promise<> template is refcounted
For copyable types multiple Thens are allowed

class AfterStartupTaskUtils {
 public:
  static Promise<void> AfterStartup();
};

...

AfterStartupTaskUtils::AfterStartup().Then(FROM_HERE, base::Bind(PostStartupTask1));
AfterStartupTaskUtils::AfterStartup().Then(FROM_HERE, base::Bind(PostStartupTask2));
AfterStartupTaskUtils::AfterStartup().Then(FROM_HERE, base::Bind(PostStartupTask3));
```

```cpp
Multiple Thens

Sometimes we want to do multiple things in response to a single event. To make the graph more explicit we propose to support multiple thens. E.g. you can do this:

Promise<void> p;

p.ThenOn(io_sequence, FROM_HERE, base::Bind(&ThingToDoOnIoSequence)
    .ThenHere(FROM_HERE, base::Bind(&ThingToDoAfterThatOnUiThread);

p.ThenHere(FROM_HERE, base::Bind(&OtherThingToDoOnUiThread)
    .ThenHere(FROM_HERE, base::Bind(&ThingToDoAfterThat);


And this:

class ServiceProvider {
 public:
  virtual Promise<scoped_refptr<ServiceA>> GetServiceA() = 0;

  virtual Promise<scoped_refptr<ServiceB>> GetServiceB() = 0;

  virtual Promise<scoped_refptr<ServiceC>> GetServiceC() = 0;
};

class ServiceA {
 public:
  static scoped_refptr<ServiceA> Create();
};

class ServiceB {
 public:
  static scoped_refptr<ServiceB> Create(scoped_refptr<ServiceA> a);
};

class ServiceC {
 public:
  static scoped_refptr<ServiceC> Create(scoped_refptr<ServiceA> a,
                                        scoped_refptr<ServiceB> b);
};

class ServiceProviderImpl : public ServiceProvider {
 public:
  void Init() {
    service_a_ = task_runner_->PostTask(FROM_HERE, base::Bind(ServiceA::Create));
    service_b_ = service_a.ThenHere(FROM_HERE, base::Bind(ServiceB::Create));
    service_c_ = Promises::All(service_a, service_b)
       .ThenHere(FROM_HERE, base::Bind(ServiceC::Create));
  }

  Promise<scoped_refptr<ServiceA>> GetServiceA() override {
    return service_a_;
  }

  Promise<scoped_refptr<ServiceB>> GetServiceB() override {
    return service_b_;
  }

  Promise<scoped_refptr<ServiceAC>> GetServiceC() override {
    return service_c_;
  }

 private:
  Promise<scoped_refptr<ServiceA>> service_a_;
  Promise<scoped_refptr<ServiceB>> service_b_;
  Promise<scoped_refptr<ServiceC>> service_c_;
};


This has a few implications:
Promises need to be refcounted.
We need to be careful to prevent use after move errors
```

```cpp
A promise can return a promise

Useful if you need to delegate to something else to provide the answer
Any chained FromHere runs after the new promise has resolved

MyResult Utility();

task_runner->PostTask(FROM_HERE, base::Bind([]() {
       ...
       return ThreadTaskRunnerHandle::Get()->PostTask(
           FROM_HERE, base::Bind(&Utility));
    }).ThenHere(FROM_HERE, base::Bind([](MyResult r) { /* Do something */ })
```

CatchOn/CatchHere - will be called on reject:

```cpp
  // A task to execute |on_reject| is posted on |task_runner| as soon as this
  // promise (or an uncaught ancestor) is rejected. A Promise<> for the return
  // value of |on_reject| is returned.
  //
  // The following callback return types have special meanings:
  // 1. PromiseResult<Resolve, Reject> lets the callback resolve, reject or
  //    curry a Promise<Resolve, Reject>
  // 2. Promise<Resolve, Reject> where the result is a curried promise.
  //
  // If a promise has multiple Catches they will be run in order of creation.
  //
  // |task_runner| is const-ref to avoid bloat due the destructor (which posts a
  // task).
```

ThenOn/ThenHere - will be called on resolve:

```cpp
  // A task to execute |on_resolve| is posted on |task_runner| as soon as this
  // promise (or an unhandled ancestor) is resolved. A Promise<> for the return
  // value of |on_resolve| is returned.
  //
  // The following callback return types have special meanings:
  // 1. PromiseResult<Resolve, Reject> lets the callback resolve, reject or
  //    curry a Promise<Resolve, Reject>
  // 2. Promise<Resolve, Reject> where the result is a curried promise.
  //
  // If a promise has multiple Thens they will be run in order of creation.
  //
  // |task_runner| is const-ref to avoid bloat due the destructor (which posts a
  // task).
```

```cpp
  // A task to execute |on_reject| is posted on |task_runner| as soon as this
  // promise (or an uncaught ancestor) is rejected. Likewise a task to execute
  // |on_resolve| is posted on |task_runner| as soon as this promise (or an
  // unhandled ancestor) is resolved. A Promise<> for the return value of
  // |on_resolve| or |on_reject| is returned.
  //
  // The following callback return types have special meanings:
  // 1. PromiseResult<Resolve, Reject> lets the callback resolve, reject or
  //    curry a Promise<Resolve, Reject>
  // 2. Promise<Resolve, Reject> where the result is a curried promise.
  //
  // If a promise has multiple Catches/ Thens, they will be run in order of
  // creation.
  //
  // Note if either |on_resolve| or |on_reject| are canceled (due to weak
  // pointer invalidation), then the other must be canceled at the same time as
  // well. This restriction only applies to this form of ThenOn/ThenHere.
  //
  // |task_runner| is const-ref to avoid bloat due the destructor (which posts a
  // task).
  template <typename ThenCb, typename CatchCb>
  auto ThenOn(const scoped_refptr<TaskRunner>& task_runner,
              const Location& from_here,
              ThenCb on_resolve,
              CatchCb on_reject) noexcept;
```

FinallyOn/FinallyHere - will be called on resolve or reject:

finally callbacks run after all child resolve & reject callbacks have run

```cpp
  // A task to execute |finally_callback| on |task_runner| is posted after the
  // parent promise is resolved or rejected. |finally_callback| is not executed
  // if the parent promise is cancelled. Unlike the finally() in Javascript
  // promises, this doesn't return a Promise that is resolved or rejected with
  // the parent's value if |finally_callback| returns void. (We could support
  // this if needed it but it seems unlikely to be used).
  //
  // |task_runner| is const-ref to avoid bloat due the destructor (which posts a
  // task).

Just like ES6 we support promise.FinallyOn() & promise.FinallyHere()
Runs after after the promise is resolved or rejected and all Thens and Catches have executed
ManualPromiseResolver<void, void> promise_a(FROM_HERE);
Promise<void, void> promise_b = promise_a.promise()
      .ThenHere(FROM_HERE, base::Bind([](){ LOG(INFO) << 1;}))
      .ThenHere(FROM_HERE, base::Bind([](){ LOG(INFO) << 2;}))
      .CatchHere(FROM_HERE, base::Bind([](){ LOG(INFO) << 3;}));

Promise<void, void> promise_c = promise_a.promise()
      .ThenHere(FROM_HERE, base::Bind([](){ LOG(INFO) << 4;}))
      .ThenHere(FROM_HERE, base::Bind([](){ LOG(INFO) << 5;}))
      .CatchHere(FROM_HERE, base::Bind([](){ LOG(INFO) << 6;}));

Promise<void, void> promise_d = promise_a.promise()
      .ThenHere(FROM_HERE, base::Bind([](){ LOG(INFO) << 7;}))
      .ThenHere(FROM_HERE, base::Bind([](){ LOG(INFO) << 8;}))
      .CatchHere(FROM_HERE, base::Bind([](){ LOG(INFO) << 9;}));

promise_d.FinallyHere(FROM_HERE, base::Bind([](){ LOG(INFO) << "Finally";}))
promise_a.Reject();

Prints: 3, 6, 9, Finally
```

```cpp
E.g.

ManualPromise<void, std::string> p1(FROM_HERE);
Promise<void, std::string> p2 =
    p1.promise()
        .ThenHere(FROM_HERE, BindOnce([]() { LOG(INFO) << "Then #1"; }))
        .ThenHere(FROM_HERE,
                       BindOnce([]()-> PromiseResult<void, std::string> {
                                  LOG(INFO) << "Then #2 (reject)";
                                  return std::string("Whoops!");
                                }))
        .ThenHere(FROM_HERE, BindOnce([]() { LOG(INFO) << "Then #3"; }))
        .ThenHere(FROM_HERE,  BindOnce([]() { LOG(INFO) << "Then #4"; }))
        .CatchHere(FROM_HERE, BindOnce([](const std::string& err) {
                                              LOG(INFO) << "Caught " << err;
                                            }));

p2.FinallyHere(FROM_HERE, BindOnce([]() { LOG(INFO) << "Finally"; }));
p2.ThenHere(FROM_HERE, BindOnce([]() { LOG(INFO) << "Then #5"; }))
p2.ThenHere(FROM_HERE, BindOnce([]() { LOG(INFO) << "Then #6"; }))

p1.Resolve();


Will print:

Then #1
Then #2 (reject)
Caught Whoops!
Then #5
Then #6
Finally
```

`ManualPromiseResolver`:

```cpp
// Used for manually resolving and rejecting a Promise. This is for
// compatibility with old code and will eventually be removed.
```

`Promises::All`:

Note that `Promises::All` will reject if any of prerequisites rejected, but resolve if all of prerequisites resolved.

```cpp
  // Promises::All can have multiple prerequisites and
  // it will reject as soon as any prerequisite rejects. Multiple prerequisites
  // can reject, but we wish to record only the first one. Also we can only
  // invoke executors once.
```

Promise.all is typically used to do something when N asynchronous actions have completed.

```cpp
  // Accepts a container of Promise<Resolve, Reject> and returns a
  // Promise<std::vector<Resolve>, Reject>. This is resolved when all
  // prerequisite promises are resolved returning a vector of all the Resolve
  // values, or rejects with the Reject value of the first promise to do so.
  auto All(const Location& from_here, const Container& promises);

  // Accepts one or more promises and returns a
  // Promise<std::tuple<Resolve> ...>, Reject> which is resolved when all
  // promises resolve or rejects with the Reject value of the first promise to
  // do so.
  auto All(const Location& from_here, Promise<Resolve, Reject>... promises);

Returns a promise resolved when all of the specified promises have resolved
Rejects immediately if any of the specified promises have rejected
Supports either a varargs list of promises or a container, or a container of variants of promises!
Promise<float, std::string> p1 = ...;
Promise<int, std::string> p2 = ...;
Promise<bool, std::string> p3 = ...;

Promises::All(p1, p2, p3)
    .ThenHere(FROM_HERE,
              BindOnce([](std::tuple<float, int, bool> result) {
                // Do something with |result|.
              }),
              BindOnce([](const std::string& err) {
                // Do something with |err|.
              }));

What if those promises had different error types?
Variant to the rescue!
Promise<float, ErrorA> p1 = ...;
Promise<int, ErrorB> p2 = ...;
Promise<bool, ErrorC> p3 = ...;

Promises::All(p1, p2, p3)
    .ThenHere(FROM_HERE,
              BindOnce([](std::tuple<float, int, bool> result) {
                // Do something with |result|.
              }),
              BindOnce([](base::Variant<ErrorA, ErrorB, ErrorC> err) {
                // Do something with |err|.
              }));

What if you want to wait for a lot of things and the tuple is unwieldy?
You can specify a void call back!

Promise<void> p1, p2, p3, p4, p5, p6;

...

Promises::All(p1, p2, p3, p4, p5, p6)
    .ThenHere(FROM_HERE,
              BindOnce([]() {
                // Do something after p1, p2, p3, p4, p5 and p6 have resolved
              }));

A vararg list of promises:

Promise<float, ErrorType1> p1;
Promise<int, ErrorType2> p2;
Promise<bool, ErrorType3> p3;

Promise<std::tuple<float, int, bool>> p = Promises::All(p1, p2, p3);
p.ThenHere(sequence, FROM_HERE,
    base::BindOnce([](std::tuple<float, int, bool> result) {
       // Do something with result.
    }),
    base::BindOnce([](Variant<ErrorType1, ErrorType2, ErrorType3> err) {
       // Do something with err.
    }));

std::tuple is awkward to work with, so as syntactic sugar we will support unpacking the tuple like so:
Promise<float> p1;
Promise<int> p2;
Promise<bool> p3;

Promise<std::tuple<float, int, bool>> p = Promises::All(p1, p2, p3);
p.ThenHere(sequence, FROM_HERE,
    base::BindOnce([](float a, int b, bool c) {
      ...
    }));

A container of promises:

std::vector<Promise<int>> promises;

Promises::All(promises).ThenOn(sequence, FROM_HERE,
    base::BindOnce([](std::vector<int> result) {
              ...
            });

A container of variants of promises:

Promise<int> p1;
Promise<void> p2;
Promise<std::string> p3;

std::vector<Variant<Promise<int>, Promise<void>, Promise<std::string>>> promises;
promises.push_back(p1);
promises.push_back(p2);
promises.push_back(p3);

Promises::All(promises).ThenHere(FROM_HERE,
    base::BindOnce([](std::vector<Variant<int, Void, std::string>> result) {
      ....
    });
```

`Promises::Race`:

 Promise.race is typically used to wait for something to happen with a time out, or in UI code to do something when one of N buttons is pressed.

Use smart pointers like `unique_ptr` to check if promise resolved with some value:

```cpp
TEST_F(PromiseTest, RaceResolveMoveOnlyType) {
  ManualPromiseResolver<std::unique_ptr<float>> p1(FROM_HERE);
  ManualPromiseResolver<std::unique_ptr<int>> p2(FROM_HERE);
  ManualPromiseResolver<std::unique_ptr<bool>> p3(FROM_HERE);

  RunLoop run_loop;
  Promises::Race(FROM_HERE, p1.promise(), p2.promise(), p3.promise())
      .ThenHere(
          FROM_HERE,
          BindOnce(
              [](RunLoop* run_loop,
                 std::tuple<std::unique_ptr<float>, std::unique_ptr<int>,
                         std::unique_ptr<bool>> result) {
                EXPECT_FALSE(std::get<0>(result));
                EXPECT_TRUE(std::get<1>(result));
                EXPECT_FALSE(std::get<2>(result));

                EXPECT_EQ(1337, *std::get<std::unique_ptr<int>>(result));
                EXPECT_EQ(1337, *std::get<1>(result));

                run_loop->Quit();
              },
              &run_loop));

  p2.Resolve(std::make_unique<int>(1337));
  run_loop.Run();
}
```

```cpp
Returns a promise resolved when any of the specified promises have resolved
Rejects immediately if any of the specified promises have rejected
Supports either a varargs list of promises or a container, or a container of variants of promises!
Promise<std::unique_ptr<float>> p1 = ...;
Promise<std::unique_ptr<int>> p2 = ...;
Promise<std::unique_ptr<bool>> p3 = ...;

Promises::Race(p1, p2, p3)
    .ThenHere(FROM_HERE,
              BindOnce([](Variant<std::unique_ptr<float>, std::unique_ptr<int>,
                                  std::unique_ptr<bool>> result) {
                    // Do something with |result|.
                  }));
```

```cpp
Promise<int, void> p1;
Promise<void, net::Error> p2;
Promise<void, CustomError> p3;
Promise<int, std::string> p4;

Promises::Race(p1, p2, p3, p4)
  .ThenOn(sequence, FROM_HERE, base::BindOnce([](Variant<int, Void> result) {
         // Do something with result.
       }),
       base::BindOnce([](const Variant<base::Void, net::Error, CustomError,
                                       std::string>& err) {
         // Do something with err.
       }));
....
p2.Resolve(); // This would trigger the Then above.

Note the use of Variant here, std::variant is coming in C++17 and its used to return a value from a set of types.

A container of Promises:
std::vector<Promise<int>> promises;

Promises::Race(promises).ThenOn(sequence, FROM_HERE,
    base::BindOnce([]( int result) {
       ...
    }));

A container of Variants of Promises:
std::vector<Variant<Promise<int, ErrorType1>,
                    Promise<int, ErrorType2>,
                    Promise<void, ErrorType3>>> promises;

Promise<void, ErrorType1> p1;
Promise<int, ErrorType2> p2;
Promise<void, ErrorType3> p3;
promises.push_back(p1);
promises.push_back(p2);
promises.push_back(p3);
Promises::Race(promises)
  .ThenOn(sequence, FROM_HERE, base::BindOnce([](Variant<int, Void> result) {
         // Do something with result.
       }),
   base::BindOnce(
       [](const Variant<ErrorType1, ErrorType2, ErrorType3>& err) {
         // Do something with err.
       }));
```

```cpp
RejectPolicy::kCatchNotRequired or by Posting a Task with a kCatchNotRequired trait:

The JS experience suggests uncaught rejection is likely to be a common problem.  To combat this in debug builds some extra sanity checks are run when a rejectable promise is resolved or rejected to detect the presence required catch handlers in the promise graph. Since we know the base::Location for each promise, we can print a useful error when we DCHECK showing where the promise initially came from and where the leaf node where the possible rejection wasn't handled.

This checking can sometimes be onerous (e.g. in the case of Mojo) so it will be possible to disable it by either constructing a ManualPromise with RejectPolicy::kCatchNotRequired or by Posting a Task with a kCatchNotRequired trait.
```

```cpp
Cross sequence promises

A common pattern in chromium (often via PostTaskAndReply) is to post a task from one sequence which then posts a reply onto the original sequence.  E.g.

// On the UI sequence
io_sequence_runner->PostTaskAndReply(FROM_HERE,
                                     base::BindOnce(&ThingToRunOnIoThread),
                                     base::BindOnce(&ThingToRunOnUiThread));

The promise equivalent of that would be:

// On the UI sequence
io_sequence_runner->PostTask(FROM_HERE, base::BindOnce(&ThingToRunOnIoThread))
    .ThenHere(FROM_HERE, base::BindOnce(&ThingToRunOnUiThread));

If you need the continuation(s) to run on another sequence you can do:

// On the UI sequence
io_sequence_runner->PostTask(FROM_HERE, base::BindOnce(&ThingToRunOnIoThread))
    .ThenOn(sequence_runner1, FROM_HERE, base::BindOnce(&ThingToRunOnSequence1))
    .ThenOn(sequence_runner2, FROM_HERE, base::BindOnce(&ThingToRunOnSequence2));
```

```cpp
Resolve and Reject results are not always useful, particularly after a Promises::All.  We will optionally support void callbacks.  E.g.

Promise<int> p1;
Promise<void, bool> p2;
Promise<void, int> p3;
Promise<int, std::string> p4;

Promises::All(p1, p2, p3, p4)
  .ThenHere(FROM_HERE, base::BindOnce([]() {
         // Do something when done, ignoring individual results.
         DoSomethingOnResolution();
       });

For Mojo it's useful for std::tuple unpacking to apply generally. E.g.

Promise<std::tuple<float, int, bool>> p;
p.ThenHere(FROM_HERE,
    base::BindOnce([](float a, int b, bool c) {
      ...
    }));
```

```cpp
Lifetimes of promises and objects bound to them
Promises are refcounted and objects bound to them will be destructed along with them. When a promise is resolved or rejected, depending on whether the bound object is move only or not, it's either copied or moved down the chain of promises (NB for move only types multiple Thens are not allowed). This means that it doesn't matter if something retains a reference to the original promise, the bound object will either get passed to a resolve or reject handler (who now owns it) or it will get deleted when the very last promise in the chain gets deleted.

A simple example:

{
  Promise<std::unique_ptr<Foo>> p = my_task_runner
      ->PostTask(FROM_HERE, BindOnce([](){ return std::make_unique<Foo>(); }));

  RunLoop().RunUntilIdle();

  // If |my_task_runner| runs tasks on this sequence then |p| and |Foo| will be
  // destructed at here at the end of this scope.  If |my_task_runner| posts tasks
  // on a different thread then destruction could happen on either this thread or the
  // other thread depending on where the refcount to |p| goes to zero.
}

If there was a ThenOn() clause, we know for sure where Foo gets deleted:

Promise<std::unique_ptr<Foo>> p = ThreadTaskRunnerHandle::Get()
    ->PostTask(FROM_HERE, BindOnce([](){ return std::make_unique<Foo>(); }));

p.ThenOn(my_task_runner,
         BindOnce([](std::unique_ptr<Foo> result) {
           // |Foo| gets destructed here on |my_task_runner|.
         });


Things get more complicated for unhandled rejections, consider:
Promise<void, std::unique_ptr<Err>> p1 = task_runner1
    ->PostTask(FROM_HERE,
               BindOnce([]() -> PromiseResult<void, std::unique_ptr<Err>> {
                 return std::make_unique<Err>();
               }));

Promise<void, std::unique_ptr<Err>> p2 =
    p1.ThenOn(task_runner2, FROM_HERE, BindOnce([]() {
                 ...
               }));

Promise<void, std::unique_ptr<Err>> p3 =
    p2.ThenOn(task_runner3, FROM_HERE, BindOnce([]() {
                 ...
               }));

When |p1| rejects |p2| also rejects which causes |p3| to reject. At each stage ownership of Err is passed down the chain and Err will eventually get deleted on |task_runner3|.

Similar considerations apply to resolved promises and void callbacks, e.g:

Promise<std::unique_ptr<Foo>> p1 = task_runner1
    ->PostTask(FROM_HERE,
               BindOnce([]() {
                 return std::make_unique<Foo>();
               }));

p2 = p1.ThenOn(task_runner2, FROM_HERE, BindOnce([]() {
                 ...
               }));

p3 = p1.ThenOn(task_runner3, FROM_HERE, BindOnce([]() {
                 ...
               }));

Foo will be deleted after |p2| and |p3| have run.  Since |p2| and |p3| are posted to different sequences, we can't be sure which sequence Foo will be deleted on.  NB it's illegal for p2 & p3 to both take ownership of Foo and the library will DCHECK if you try to do this.
```

```cpp
// catch and rethrow using the new type:
Promise<int, bool> p;
p.ThenHere(FROM_HERE, base::BindOnce([](int result) { return result + 1; }))
  .ThenHere(FROM_HERE, base::BindOnce([](int result) { return result + 1; }))
  .ThenHere(FROM_HERE,
        base::BindOnce([](int result) -> base::PromiseResult<int, std::string> {
          if (result < 0) std::string("Oh no!"); // Reject
          return result; // Resolve
        },
        base::BindOnce([](bool err) -> base::PromiseResult<int, std::string> {
          // Convert the reject reason to the new type.
          return err ? std::string("Reason 1") : std::string("Reason 2");
        })
  .ThenHere(FROM_HERE,
        base::BindOnce([](int result) {
          // Handle result.
        }),
        base::BindOnce([](const std::string& error) {
          // Handle error.
        }));
```

## Example 1

```cpp
// creates promise and resolves via GetRepeatingResolveCallback
base::Promise<std::unique_ptr<GlobalMemoryDump>>
MemoryInstrumentation::RequestGlobalDumpPromise() {
  std::vector<std::string> allocator_dump_names;
  base::ManualPromiseResolver<
    /*ResolveType*/std::unique_ptr<GlobalMemoryDump>
    , /*RejectType*/ base::NoReject> p(
        FROM_HERE
        , RejectPolicy::kMustCatchRejection);
  const auto& coordinator = GetCoordinatorBindingForCurrentThread();
  // This should get a bunch simpler if mojo is promisified.
  coordinator->RequestGlobalMemoryDump(
      MemoryDumpType::SUMMARY_ONLY, MemoryDumpLevelOfDetail::BACKGROUND,
      allocator_dump_names,
      base::BindRepeating(
          &WrapGlobalMemoryDump,
          base::BindRepeating(
              [](base::RepeatingCallback<void(
                     std::unique_ptr<GlobalMemoryDump>)> cb,
                 bool success, std::unique_ptr<GlobalMemoryDump> dump) {
                std::move(cb).Run(std::move(dump));
              },
              p.GetRepeatingResolveCallback())));
  return p.promise();
}
```

## Example 2

code below will print:

```bash
running doJobPromise
running doJobAsync
running doJobSync
running doFirstJob
running doFirstJobSync
doFirstJobSync: previous resolved with:
-1
-2
-3
running doSecondJob
running doSecondJobSync
doSecondJobSync: previous resolved with:
-1
-2
-3
-9
running doThirdJob
doThirdJob: previous resolved with: -1
running doLastJob
doLastJob: previous resolved with: 1
```

Note comments about `base::Unretained` below:

```cpp
  // code below uses base::ManualPromiseResolver

  typedef std::vector<int> TestVecForPromise;

  class RequestPromiseAPI
    : public base::RefCountedThreadSafe<RequestPromiseAPI>
  {
   private:
    friend class base::RefCountedThreadSafe<RequestPromiseAPI>;
    ~RequestPromiseAPI()
    {
      DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
    }

   public:
    typedef base::RepeatingCallback<void(std::unique_ptr<TestVecForPromise>)>
      RepeatingCallbackType;

    RequestPromiseAPI(
      scoped_refptr<base::SingleThreadTaskRunner> task_runner)
      : task_runner_(task_runner)
        , ALLOW_THIS_IN_INITIALIZER_LIST(weak_ptr_factory_(this))
        , ALLOW_THIS_IN_INITIALIZER_LIST(
            weak_this_(weak_ptr_factory_.GetWeakPtr()))
    {
      DETACH_FROM_SEQUENCE(sequence_checker_);
      DCHECK(task_runner_);
    }

    std::unique_ptr<TestVecForPromise> doJobSync()
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();

      DCHECK(task_runner_);
      DCHECK(task_runner_->RunsTasksInCurrentSequence());

      result_.push_back(-1);
      result_.push_back(-2);
      result_.push_back(-3);

      // copy data to return result
      std::unique_ptr<TestVecForPromise> result
        = std::make_unique<TestVecForPromise>(result_);

      return std::move(result);
    }

    // old-style API with callback when done
    void doJobAsync(RepeatingCallbackType done_cb)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();

      DCHECK(task_runner_);
      base::PostTaskAndReplyWithResult(task_runner_.get()
        , FROM_HERE
        , base::BindRepeating(
            &RequestPromiseAPI::doJobSync
            //, weakPtr()
            , base::Unretained(this) // <-- Unretained may be wrong
        )
        , done_cb
      );
    }

    base::Promise<std::unique_ptr<TestVecForPromise>> doJobPromise()
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();

      base::ManualPromiseResolver<std::unique_ptr<TestVecForPromise>>
        promise_resolver(
          FROM_HERE
          , base::RejectPolicy::kMustCatchRejection);
      doJobAsync(promise_resolver.GetRepeatingResolveCallback());
      return promise_resolver.promise();
    }

    std::unique_ptr<TestVecForPromise> doFirstJobSync(
      std::unique_ptr<TestVecForPromise> vec)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();

      DCHECK(task_runner_);
      DCHECK(task_runner_->RunsTasksInCurrentSequence());
      DCHECK(vec);

      LOG(INFO)
        << FROM_HERE.function_name()
        << ": previous resolved with: ";
      // print result and find max
      for(auto& it : *vec) {
        LOG(INFO)
          << it;
      }
      vec->push_back(-9);
      return std::move(vec);
    }

    base::PromiseResult<
        /*ResolveType*/ std::unique_ptr<TestVecForPromise>
        , /*RejectType*/ base::NoReject
      > doFirstJob(std::unique_ptr<TestVecForPromise> vec)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();
      std::unique_ptr<TestVecForPromise> res
        = doFirstJobSync(std::move(vec));
      return base::Resolved<std::unique_ptr<TestVecForPromise>>(
        std::move(res));
    }

    int doSecondJobSync(std::unique_ptr<TestVecForPromise> vec)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();

      DCHECK(task_runner_);
      DCHECK(task_runner_->RunsTasksInCurrentSequence());
      DCHECK(vec);

      LOG(INFO)
        << FROM_HERE.function_name()
        << ": previous resolved with: ";
      // print result and find max
      int max = std::numeric_limits<int>::min();
      for(auto& it : *vec) {
        LOG(INFO)
          << it;
        if(it > max) {
          max = it;
        }
      }
      return max;
    }

    base::PromiseResult<
        /*ResolveType*/ int
        , /*RejectType*/ base::NoReject
      > doSecondJob(std::unique_ptr<TestVecForPromise> vec)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();
      int max = doSecondJobSync(std::move(vec));
      return base::Resolved<int>(max);
    }

    base::PromiseResult<
        /*ResolveType*/ int
        , /*RejectType*/ base::NoReject
      > doThirdJob(int val)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();

      LOG(INFO)
        << FROM_HERE.function_name()
        << ": previous resolved with: "
        << val;

      return base::Resolved<int>(std::abs(val));
    }

    void doLastJob(int val)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();

      DCHECK(task_runner_);
      DCHECK(task_runner_->RunsTasksInCurrentSequence());

      LOG(INFO)
        << FROM_HERE.function_name()
        << ": previous resolved with: "
        << val;
    }

    // When we need a WeakPtr, we copy construct this,
    // which is safe to do from any thread
    base::WeakPtr<RequestPromiseAPI> weakPtr()
    {
      return weak_this_;
    }

   private:
    SEQUENCE_CHECKER(sequence_checker_);

    TestVecForPromise result_;

    scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

    // base::WeakPtr can be used to ensure that any callback bound
    // to an object is canceled when that object is destroyed
    // (guarantees that |this| will not be used-after-free).
    base::WeakPtrFactory<
        RequestPromiseAPI
      > weak_ptr_factory_;

    // After constructing |weak_ptr_factory_|
    // we immediately construct a WeakPtr
    // in order to bind the WeakPtr object to its thread.
    // When we need a WeakPtr, we copy construct this,
    // which is safe to do from any
    // thread according to weak_ptr.h (versus calling
    // |weak_ptr_factory_.GetWeakPtr() which is not).
    base::WeakPtr<RequestPromiseAPI> weak_this_;

    DISALLOW_COPY_AND_ASSIGN(RequestPromiseAPI);
  };

  scoped_refptr<RequestPromiseAPI> test_api
    = new RequestPromiseAPI(main_loop_task_runner);

  base::Promise<std::unique_ptr<TestVecForPromise>>
      test_promise = test_api->doJobPromise();

  test_promise
  .ThenOn(main_loop_task_runner, FROM_HERE,
     base::BindOnce(
        &RequestPromiseAPI::doFirstJob
        //, test_api.weakPtr()
        , base::Unretained(test_api.get()) // <-- Unretained may be wrong
     ))
  .ThenOn(main_loop_task_runner, FROM_HERE,
     base::BindOnce(
        &RequestPromiseAPI::doSecondJob
        //, test_api.weakPtr()
        , base::Unretained(test_api.get()) // <-- Unretained may be wrong
     ))
  .ThenOn(main_loop_task_runner, FROM_HERE,
     base::BindOnce(
       &RequestPromiseAPI::doThirdJob
       //, test_api->weakPtr()
       , base::Unretained(test_api.get()) // <-- Unretained may be wrong
     ))
  .ThenOn(main_loop_task_runner, FROM_HERE,
     base::BindOnce(
       &RequestPromiseAPI::doLastJob
       , test_api->weakPtr()
     ));
```

Note that `base::Unretained(test_api.get())` is UNSAFE if `test_api` may be freed.

One way to solve that issue is passing shared or weak pointer to `base::BindOnce` like below:

```cpp
  /// \note wrapped code in scope to test refcount on scoped_refptr and lifetime with BindOnce
  {
    scoped_refptr<RequestPromiseAPI> test_api
      = new RequestPromiseAPI(main_loop_task_runner);

    base::Promise<std::unique_ptr<TestVecForPromise>>
        test_promise = test_api->doJobPromise();

    test_promise
    .ThenOn(main_loop_task_runner, FROM_HERE,
       base::BindOnce(
          &RequestPromiseAPI::doFirstJob
          //, test_api.weakPtr()
          //, base::Unretained(test_api.get())
          , test_api
       ))
    .ThenOn(main_loop_task_runner, FROM_HERE,
       base::BindOnce(
          &RequestPromiseAPI::doSecondJob
          //, test_api.weakPtr()
          //, base::Unretained(test_api.get())
          , test_api
       ))
    .ThenOn(main_loop_task_runner, FROM_HERE,
       base::BindOnce(
         &RequestPromiseAPI::doThirdJob
         //, test_api->weakPtr()
         //, base::Unretained(test_api.get())
         , test_api
       ))
    .ThenOn(main_loop_task_runner, FROM_HERE,
       base::BindOnce(
         &RequestPromiseAPI::doLastJob
         , test_api->weakPtr()
       ));
  }
```

Also you may want to change `base::Unretained(this)` to `base::RetainedRef(this)` near `PostTaskAndReplyWithResult`

```cpp
// before
      base::PostTaskAndReplyWithResult(task_runner_.get()
        , FROM_HERE
        , base::BindRepeating(
            &RequestPromiseAPI::doJobSync
            , base::Unretained(this) // <-- wrong
        )
        , done_cb
      );

// after
      base::PostTaskAndReplyWithResult(task_runner_.get()
        , FROM_HERE
        , base::BindRepeating(
            &RequestPromiseAPI::doJobSync
            , base::RetainedRef(this) // prolong lifetime of refcounted object (base::RefCountedThreadSafe)
        )
        , done_cb
      );
```

## Example 3

Note resolve/reject behavior:

```cpp
// prints:
//  step (2) recieved:Oh no!
//  step (3) recieved:5
base::ManualPromiseResolver<int, std::string>
  promise_resolver(
    FROM_HERE
    , base::RejectPolicy::kMustCatchRejection);
promise_resolver.promise().ThenHere(
    FROM_HERE, base::BindOnce([](int result)
      -> base::PromiseResult<int, base::NoReject>
      { return result + 1; }))
  .ThenHere(
    FROM_HERE, base::BindOnce([](int result)
      -> base::PromiseResult<int, base::NoReject>
      { return result + 1; }))
  .ThenHere(
    FROM_HERE, base::BindOnce([](int result)
      -> base::PromiseResult<int, std::string>
    {
      // We can reject by returning the reject type here.
      return base::Rejected<std::string>("Oh no!");
    })
  )
  // Just like in ES6 a Then() can be passed resolve and reject callbacks.
  .ThenHere(
      FROM_HERE, base::BindOnce([](int result)
        -> base::PromiseResult<int, std::string>
        {
        // We shouldn't get here, the promise was rejected!
        LOG(INFO)
          << "step (1) recieved:"
          << result;
        return base::Resolved<int>(8);
      }),
      base::BindOnce([](const std::string& err)
        -> base::PromiseResult<int, std::string>
        {
        DCHECK_EQ("Oh no!", err);
        LOG(INFO)
          << "step (2) recieved:"
          << err;
        return base::Resolved<int>(5);
      }))
  .ThenHere(
      FROM_HERE, base::BindOnce([](int result) {
        LOG(INFO)
          << "step (3) recieved:"
          << result;
      }),
      base::BindOnce([](const std::string& err) {
        DCHECK_EQ("Oh no!", err);
        LOG(INFO)
          << "step (4) recieved:"
          << err;
      }));
promise_resolver.Resolve(9);
```

## Example 4

You can wrap PostTask to return Promise, see `post_promise.h`.

code below will print:

```bash
promise from base::PostPromise...
running doFirstJob
running doFirstJobSync
doFirstJobSync: previous resolved with:
-1
-2
-3
running doSecondJob
running doSecondJobSync
doSecondJobSync: previous resolved with:
-1
-2
-3
-9
running doThirdJob
doThirdJob: previous resolved with: -1
running doLastJob
doLastJob: previous resolved with: 1
```

```cpp
  // code below uses base::PostPromise

  typedef std::vector<int> TestVecForPromise;

  class RequestPromiseAPI
    : public base::RefCountedThreadSafe<RequestPromiseAPI>
  {
   private:
    friend class base::RefCountedThreadSafe<RequestPromiseAPI>;
    ~RequestPromiseAPI()
    {
      DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
    }

   public:
    typedef base::RepeatingCallback<void(std::unique_ptr<TestVecForPromise>)>
      RepeatingCallbackType;

    RequestPromiseAPI(
      scoped_refptr<base::SingleThreadTaskRunner> task_runner)
      : task_runner_(task_runner)
        , ALLOW_THIS_IN_INITIALIZER_LIST(weak_ptr_factory_(this))
        , ALLOW_THIS_IN_INITIALIZER_LIST(
            weak_this_(weak_ptr_factory_.GetWeakPtr()))
    {
      DETACH_FROM_SEQUENCE(sequence_checker_);
      DCHECK(task_runner_);
    }

    std::unique_ptr<TestVecForPromise> doFirstJobSync(
      std::unique_ptr<TestVecForPromise> vec)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();

      DCHECK(task_runner_);
      DCHECK(task_runner_->RunsTasksInCurrentSequence());
      DCHECK(vec);

      LOG(INFO)
        << FROM_HERE.function_name()
        << ": previous resolved with: ";
      // print result and find max
      for(auto& it : *vec) {
        LOG(INFO)
          << it;
      }
      vec->push_back(-9);
      return std::move(vec);
    }

    base::PromiseResult<
        /*ResolveType*/ std::unique_ptr<TestVecForPromise>
        , /*RejectType*/ base::NoReject
      > doFirstJob(std::unique_ptr<TestVecForPromise> vec)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();
      std::unique_ptr<TestVecForPromise> res
        = doFirstJobSync(std::move(vec));
      return base::Resolved<std::unique_ptr<TestVecForPromise>>(
        std::move(res));
    }

    int doSecondJobSync(std::unique_ptr<TestVecForPromise> vec)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();

      DCHECK(task_runner_);
      DCHECK(task_runner_->RunsTasksInCurrentSequence());
      DCHECK(vec);

      LOG(INFO)
        << FROM_HERE.function_name()
        << ": previous resolved with: ";
      // print result and find max
      int max = std::numeric_limits<int>::min();
      for(auto& it : *vec) {
        LOG(INFO)
          << it;
        if(it > max) {
          max = it;
        }
      }
      return max;
    }

    base::PromiseResult<
        /*ResolveType*/ int
        , /*RejectType*/ base::NoReject
      > doSecondJob(std::unique_ptr<TestVecForPromise> vec)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();
      int max = doSecondJobSync(std::move(vec));
      return base::Resolved<int>(max);
    }

    base::PromiseResult<
        /*ResolveType*/ int
        , /*RejectType*/ base::NoReject
      > doThirdJob(int val)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();

      LOG(INFO)
        << FROM_HERE.function_name()
        << ": previous resolved with: "
        << val;

      return base::Resolved<int>(std::abs(val));
    }

    void doLastJob(int val)
    {
      LOG(INFO)
        << "running "
        << FROM_HERE.function_name();

      DCHECK(task_runner_);
      DCHECK(task_runner_->RunsTasksInCurrentSequence());

      LOG(INFO)
        << FROM_HERE.function_name()
        << ": previous resolved with: "
        << val;
    }

    // When we need a WeakPtr, we copy construct this,
    // which is safe to do from any thread
    base::WeakPtr<RequestPromiseAPI> weakPtr()
    {
      return weak_this_;
    }

   private:
    SEQUENCE_CHECKER(sequence_checker_);

    scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

    // base::WeakPtr can be used to ensure that any callback bound
    // to an object is canceled when that object is destroyed
    // (guarantees that |this| will not be used-after-free).
    base::WeakPtrFactory<
        RequestPromiseAPI
      > weak_ptr_factory_;

    // After constructing |weak_ptr_factory_|
    // we immediately construct a WeakPtr
    // in order to bind the WeakPtr object to its thread.
    // When we need a WeakPtr, we copy construct this,
    // which is safe to do from any
    // thread according to weak_ptr.h (versus calling
    // |weak_ptr_factory_.GetWeakPtr() which is not).
    base::WeakPtr<RequestPromiseAPI> weak_this_;

    DISALLOW_COPY_AND_ASSIGN(RequestPromiseAPI);
  };

  scoped_refptr<RequestPromiseAPI> test_api
    = new RequestPromiseAPI(main_loop_task_runner);

  /// \note allows PostTask to return Promise
  base::Promise<std::unique_ptr<TestVecForPromise>> test_promise
    = base::PostPromise(FROM_HERE, main_loop_task_runner.get()
        , base::BindOnce([]
          ()
        {
          LOG(INFO)
            << "promise from base::PostPromise...";

          TestVecForPromise result_;
          result_.push_back(-1);
          result_.push_back(-2);
          result_.push_back(-3);

          // move data to return result
          std::unique_ptr<TestVecForPromise> result
            = std::make_unique<TestVecForPromise>(std::move(result_));

          return base::Resolved<
              std::unique_ptr<TestVecForPromise>
            >(std::move(result));
        }));

  test_promise
  .ThenOn(main_loop_task_runner, FROM_HERE,
     base::BindOnce(
        &RequestPromiseAPI::doFirstJob
        //, test_api.weakPtr()
        , base::Unretained(test_api.get()) // <-- Unretained may be wrong
     ))
  .ThenOn(main_loop_task_runner, FROM_HERE,
     base::BindOnce(
        &RequestPromiseAPI::doSecondJob
        //, test_api.weakPtr()
        , base::Unretained(test_api.get()) // <-- Unretained may be wrong
     ))
  .ThenOn(main_loop_task_runner, FROM_HERE,
     base::BindOnce(
       &RequestPromiseAPI::doThirdJob
       //, test_api->weakPtr()
       , base::Unretained(test_api.get()) // <-- Unretained may be wrong
     ))
  .ThenOn(main_loop_task_runner, FROM_HERE,
     base::BindOnce(
       &RequestPromiseAPI::doLastJob
       , test_api->weakPtr()
     ));
```

## Example 5

About `base::promisifySynchronousTask`:

```cpp
// Wraps synchronous task into promise
// that will be executed when synchronous task will be done.
// That approach may not work with async tasks
// (async tasks may require ManualPromiseResolver).
```

About `base::internal::ClosureExecutePromise`:

```cpp
// wraps `task.Execute` into `base::OnceClosure`
// used to execute task wrapped in promise
base::OnceClosure ClosureExecutePromise(base::WrappedPromise task);
```

In example below we store queue of tasks `backupTasksQueue_`.

`backupTasksQueue_` will be flushed on timer.

we have API to create backup synchronously with `CreateBackupFileWithResult`

we want to schedule backup task in `backupTasksQueue_` asynchronously and get notified about backup multiple times, without copy of result of `CreateBackupFileWithResult` for each listener. So we wrap result of old-style API `CreateBackupFileWithResult` into `scoped_refptr` to prevent copying.

we can use `base::ObserverListThreadSafe` to get notified about `backup-on-timer-event` multiple times (multiple listeners).

In example below we also want to promisify individual backup request, so `base::ObserverListThreadSafe` may not fit well.

Using `Promise` we will be able to get result of individual backup request `bak_mgr->promise_backup` and process it from different modules. Imagine we have `tracing-module` and `old-backup-removal-module`. We want to run `old-backup-removal-module` only after `tracing-module` was notified about `backup-on-timer-event` and saved tracing report. `tracing-module` can return promise in `.ThenOn` instead of `base::Resolved`, so we will be able to run `old-backup-removal-module` only if tracing report was successfully saved. So we can use promise chain similar to:

```cpp.
  // prints:
  //   (1) notified about periodic backup with SomeBackupFilenameStr
  //   (2) notified about periodic backup with SomeBackupFilenameStr
  //   (after 1) notified about periodic backup with SomeBackupFilenameStr

  {
    std::string  BackupFilenameStr = "SomeBackupFilenameStr";

    base::Promise<scoped_refptr<BackupManager::BackupResult>>
      bak_promise = bak_mgr->promise_backup(FROM_HERE
        , BackupFilenameStr
        , BackupManager::BackupData{}
      );

    bak_promise
    .ThenOn(main_loop_task_runner, FROM_HERE,
       base::BindOnce(
         []
         (scoped_refptr<BackupManager::BackupResult> data)
         {
           DCHECK(data);

           LOG(INFO)
            << "(1) notified about periodic backup with "
            << data->full_path;

           /// you can return promise in `.ThenOn` instead of `base::Resolved`
           return base::Resolved<
              scoped_refptr<BackupManager::BackupResult>
            >(data);
         }
         //, bak_mgr
       ))
    .ThenOn(main_loop_task_runner, FROM_HERE,
       base::BindOnce(
         []
         (scoped_refptr<BackupManager::BackupResult> data)
         {
           DCHECK(data);
           LOG(INFO)
            << "(after 1) notified about periodic backup with "
            << data->full_path;
         }
         //, bak_mgr
       ));

    bak_promise
    .ThenOn(main_loop_task_runner, FROM_HERE,
       base::BindOnce(
         []
         (scoped_refptr<BackupManager::BackupResult> data)
         {
           DCHECK(data);
           LOG(INFO)
            << "(2) notified about periodic backup with "
            << data->full_path;
         }
         //, bak_mgr
       ));
  }
```

Now we know how to use promise chain without memory copy (use scoped_refptr) and what promise can return a promise.

But how to convert synchronous `CreateBackupFileWithResult` into asynchronous with `base::Promise`? How to resolve created `base::Promise`? Possible solution to that problem below:

```cpp
  base::OnceCallback<
      scoped_refptr<BackupManager::BackupResult>(void)
    > task
      = base::BindOnce(&CreateBackupFileWithResult
          , /*copied*/dir_path_.Append(filename)
          , base::Passed(std::move(serialize(data))));

  // wrap synchronous task into promise
  // promise will be resolved when synchronous task will be done
  scoped_refptr<base::internal::AbstractPromise> promise =
    base::promisifySynchronousTask(from_here, std::move(task));

  // used to execute task wrapped in promise
  base::OnceClosure promise_execute_closure
    = base::internal::ClosureExecutePromise(base::WrappedPromise(promise));
```

Now you can return result of `base::promisifySynchronousTask` and schedule execution of task `promise_execute_closure` using some timer.

Cause we don't want to use `mutex` we must always modify `backupTasksQueue_` on same sequence using `PostTask`:

```cpp
  // no need to use `PostPromise` here, just use `PostTask`
  {
    const bool is_posted
      = task_runner_->PostTask(from_here, base::BindOnce(
        &BackupManager::addOnBackupTask
        , weak_this_
        , std::move(promise_execute_closure)
      ));
    DCHECK(is_posted);
  }
```

Full code (ignore code related to `ObserverListThreadSafe` and `backupLatestDataQueue_` cause we are interested in promises and `backupTasksQueue_`):

```cpp
#pragma once

#include "common/ECS/ecs.hpp"

#include <basis/promise/promise.h>
#include <basis/promise/helpers.h>
#include <basis/promise/post_task_executor.h>

#include <base/timer/timer.h>
#include <base/time/time.h>
#include <base/bind.h>
#include <base/logging.h>
#include <base/macros.h>
#include <base/optional.h>
#include <base/files/file_path.h>
#include <base/trace_event/trace_event.h>
#include <base/synchronization/waitable_event.h>
#include <base/observer_list_threadsafe.h>

#include <vector>
#include <optional>

namespace backend {

enum class BackupWriteStatus {
  Ok
  , FailTooBig
  , FailWrite
  , TOTAL
};

class BackupObserver {
 public:
  BackupObserver();

  virtual
    ~BackupObserver();

  virtual void
    OnBackup(
      const base::FilePath& full_path
      , const BackupWriteStatus& status) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(BackupObserver);
};

class BackupManager
    : public base::RefCountedThreadSafe<BackupManager> {
public:
  typedef std::string BackupFilenameStr;

  class BackupResult
    : public base::RefCountedThreadSafe<BackupResult> {
   public:
    BackupResult(const base::FilePath& path
      , const BackupWriteStatus& status)
      : full_path(path), status(status)
      {}

    const base::FilePath full_path;
    const BackupWriteStatus status;

   private:
    friend class base::RefCountedThreadSafe<BackupResult>;

    /// \note from |base::RefCounted| docs:
    /// You should always make your destructor non-public,
    /// to avoid any code deleting
    /// the object accidently while there are references to it.
    ~BackupResult() = default;

    DISALLOW_COPY_AND_ASSIGN(BackupResult);
  };

  struct BackupData{
    std::vector<int> somedata;
  };

  struct Events {
    struct Startup {
      // event parameters
      base::TimeDelta backupPeriod;
    };
    struct Shutdown {
      // event parameters
    };
  };

public:
  BackupManager(
    const base::FilePath& dir_path
    , scoped_refptr<base::SequencedTaskRunner> task_runner);

  // Add a non owning pointer
  void
    AddObserver(
      BackupObserver* observer);

  // Does nothing if the |observer| is
  // not in the list of known observers.
  void
    RemoveObserver(
      BackupObserver* observer);

  // Notify |Observer|s
  void
    NotifyBackupObservers(
      const base::FilePath& full_path
      , const BackupWriteStatus& status);

  std::optional<BackupManager::BackupData>
    load_backup(
      const base::FilePath& full_path);

  void
    processQueuedBackupData();

  void
    asyncAddDataToBackupQueue(
      const BackupFilenameStr& filename
      , BackupManager::BackupData&& data);

  /// \note task will be added to queue
  /// and executed once on backup event,
  /// when removed from queue
  void
    addOnBackupTask(base::OnceClosure&& closure);

  void
    queue_backup_data(
      const BackupFilenameStr& filename
      , BackupManager::BackupData&& data);

  base::Promise<scoped_refptr<BackupManager::BackupResult>>
    promise_backup(
      base::Location from_here
      , const BackupFilenameStr& filename
      , BackupManager::BackupData&& data);

  void
    connect_to_dispatcher(
      entt::dispatcher& event_dispatcher);

  void
    startup(
      const Events::Startup& event);

  void
    shutdown(
      const Events::Shutdown& event);

  void
    wait_shutdown();

private:
  void
    restart_timer(
      const Events::Startup& event);

private:
  SEQUENCE_CHECKER(sequence_checker_);

  friend class BackupObserver;

  /// \note created and destroyed on |sequence_checker_|,
  /// but used on |task_runner_|
  base::RepeatingTimer backup_timer_;

  // queued data, will be written to disk with some period
  /// \note only latest data must be written
  std::map<
      BackupFilenameStr
      , BackupData
    > backupLatestDataQueue_;

  // queued tasks, will be executed with some period
  std::vector<
      base::OnceClosure
    > backupTasksQueue_;

  base::WaitableEvent wait_shutdown_;

  const base::FilePath dir_path_;

  /// \note ObserverListThreadSafe may be ued from multiple threads
  const scoped_refptr<
      base::ObserverListThreadSafe<BackupObserver>
    > observers_;

  scoped_refptr<
      base::SequencedTaskRunner
    > task_runner_;

  // base::WeakPtr can be used to ensure that any callback bound
  // to an object is canceled when that object is destroyed
  // (guarantees that |this| will not be used-after-free).
  base::WeakPtrFactory<
      BackupManager
    > weak_ptr_factory_;

  // After constructing |weak_ptr_factory_|
  // we immediately construct a WeakPtr
  // in order to bind the |BackupManager| WeakPtr object to its thread.
  // When we need a WeakPtr, we copy construct this,
  // which is safe to do from any
  // thread according to weak_ptr.h (versus calling
  // |weak_ptr_factory_.GetWeakPtr() which is not).
  base::WeakPtr<BackupManager> weak_this_;

 private:
  friend class base::RefCountedThreadSafe<BackupManager>;

  /// \note from |base::RefCounted| docs:
  /// You should always make your destructor non-public,
  /// to avoid any code deleting
  /// the object accidently while there are references to it.
  ~BackupManager();

  DISALLOW_COPY_AND_ASSIGN(BackupManager);
};

} // namespace backend


#include "BackupManager.hpp" // IWYU pragma: associated

#include "application/application_configuration.hpp"

#include <basis/promise/post_promise.h>
#include <basis/trace_event_util.hpp>

#include <base/logging.h>
#include <base/files/file.h>
#include <base/files/file_util.h>
#include <base/files/file_path.h>
#include <base/trace_event/trace_event.h>
#include <base/threading/scoped_blocking_call.h>
#include <base/threading/thread_restrictions.h>
#include <base/macros.h>
#include <base/memory/ref_counted.h>
#include <base/timer/timer.h>
#include <base/path_service.h>
#include <base/sequenced_task_runner.h>
#include <base/task/post_task.h>
#include <base/task/task_traits.h>
#include <base/trace_event/trace_event.h>
#include <base/compiler_specific.h>

namespace backend {

static constexpr size_t kBackupFileMaxSizeInBytes
  // ~100 MB
  = 100000000;

static constexpr size_t kBackupFilenameMaxLen
  = 9999;

BackupObserver::BackupObserver() = default;

BackupObserver::~BackupObserver() = default;

static BackupManager::BackupData
  parseBackupFromStr(const std::string& data)
{
  std::vector<int> TODO;

  return BackupManager::BackupData{
    .somedata = std::move(TODO)
  };
}

static BackupWriteStatus
  CreateBackupFile(
    const base::FilePath& path
    , const std::string& text)
{
  // When a ScopedBlockingCall is instantiated from a ThreadPool parallel or
  // sequenced task, the thread pool size is incremented to compensate for the
  // blocked thread (more or less aggressively depending on BlockingType).
  /// \note CPU usage should be minimal within that scope.
  base::ScopedBlockingCall scoped_blocking_call(FROM_HERE
    , base::BlockingType::MAY_BLOCK);

  DCHECK(!path.empty()
    && path.value().size() < kBackupFilenameMaxLen);
  DCHECK(!text.empty()
    && text.size() < kBackupFileMaxSizeInBytes);

  if (text.size() > kBackupFileMaxSizeInBytes)
  {
    LOG(ERROR)
      << "Could not create file (file too big): "
      << path.value();
    return BackupWriteStatus::FailTooBig;
  }

  const bool write_error
    = base::WriteFile(
        path, text.data(), text.size()) == /*error*/ -1;

  /// \note overwrites any data that was previously there
  if (write_error)
  {
    LOG(ERROR)
      << "Could not create file: "
      << path.value();
    return BackupWriteStatus::FailWrite;
  }

  return BackupWriteStatus::Ok;
}

static scoped_refptr<BackupManager::BackupResult>
  CreateBackupFileWithResult(
    const base::FilePath& path
    , const std::string& text)
{
  BackupWriteStatus status = CreateBackupFile(path, text);

  scoped_refptr<BackupManager::BackupResult> result
    = new BackupManager::BackupResult(
        path // copyed
        , std::move(status)
      );

  return result;
}

static std::string serialize(
  const BackupManager::BackupData& data)
{
  return "TODO";
}

void
  BackupManager::connect_to_dispatcher(
    entt::dispatcher &event_dispatcher)
{
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  event_dispatcher.sink<Events::Startup>()
      .connect<&BackupManager::startup>(this);
  event_dispatcher.sink<Events::Shutdown>()
      .connect<&BackupManager::shutdown>(this);
}

void
  BackupManager::asyncAddDataToBackupQueue(
    const BackupFilenameStr& filename
    , BackupManager::BackupData&& data)
{
  const bool is_posted =
    task_runner_->PostTask(FROM_HERE
      , base::Bind(&BackupManager::queue_backup_data
                   , weak_this_
                   , /*copied*/filename
                   , base::Passed(std::move(data)))
    );
  DCHECK(is_posted);
}

base::Promise<scoped_refptr<BackupManager::BackupResult>>
  BackupManager::promise_backup(
    base::Location from_here
    , const BackupFilenameStr& filename
    , BackupManager::BackupData&& data)
{
  TRACE_EVENT0("headless", "BackupManager_queue_backup_data");

  LOG(INFO) << "(BackupManager) promise backup...";

  DCHECK(!filename.empty()
    && filename.size() < kBackupFilenameMaxLen);

  base::OnceCallback<
      scoped_refptr<BackupManager::BackupResult>(void)
    > task
      = base::BindOnce(&CreateBackupFileWithResult
          , /*copied*/dir_path_.Append(filename)
          , base::Passed(std::move(serialize(data))));

  // wrap synchronous task into promise
  // promise will be resolved when synchronous task will be done
  scoped_refptr<base::internal::AbstractPromise> promise =
    base::promisifySynchronousTask(from_here, std::move(task));

  // used to execute task wrapped in promise
  base::OnceClosure promise_execute_closure
    = base::internal::ClosureExecutePromise(base::WrappedPromise(promise));

  DCHECK(!task_runner_->RunsTasksInCurrentSequence());

  {
    const bool is_posted
      = task_runner_->PostTask(from_here, base::BindOnce(
        &BackupManager::addOnBackupTask
        , weak_this_
        , std::move(promise_execute_closure)
      ));
    DCHECK(is_posted);
  }

  return base::Promise<scoped_refptr<BackupManager::BackupResult>>(
    base::internal::PassedPromise(std::move(promise))
  );
}

void
  BackupManager::addOnBackupTask(base::OnceClosure&& closure)
{
  TRACE_EVENT_LOC(FROM_HERE);

  LOG(INFO) << "(BackupManager) addOnBackupTask...";

  DCHECK(task_runner_->RunsTasksInCurrentSequence());

  backupTasksQueue_.push_back(std::move(closure));
}

void
  BackupManager::queue_backup_data(
    const BackupFilenameStr& filename
    , BackupManager::BackupData&& data)
{
  TRACE_EVENT0("headless", "BackupManager_queue_backup_data");

  LOG(INFO) << "(BackupManager) started backup...";

  DCHECK(task_runner_->RunsTasksInCurrentSequence());

  DCHECK(!filename.empty()
    && filename.size() < kBackupFilenameMaxLen);

  backupLatestDataQueue_[filename] = std::move(data);
}

BackupManager::BackupManager(
  const base::FilePath &dir_path
  , scoped_refptr<base::SequencedTaskRunner> task_runner)
  : dir_path_(dir_path)
  , task_runner_(task_runner)
  , ALLOW_THIS_IN_INITIALIZER_LIST(weak_ptr_factory_(this))
  , ALLOW_THIS_IN_INITIALIZER_LIST(
      weak_this_(weak_ptr_factory_.GetWeakPtr()))
  , observers_(new base::ObserverListThreadSafe<BackupObserver>())
{
  DETACH_FROM_SEQUENCE(sequence_checker_);
  //DCHECK(weak_this_factory_.HasWeakPtrs());
}

BackupManager::~BackupManager()
{
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
}

std::optional<BackupManager::BackupData>
  BackupManager::load_backup(const base::FilePath& full_path)
{
  TRACE_EVENT0("headless", "BackupManager_backup");

  LOG(INFO) << "(BackupManager) loading backup...";

  DCHECK(task_runner_->RunsTasksInCurrentSequence());

  std::string file_data;

  /// \note MAY_BLOCK
  {
    // When a ScopedBlockingCall is instantiated from a ThreadPool parallel or
    // sequenced task, the thread pool size is incremented to compensate for the
    // blocked thread (more or less aggressively depending on BlockingType).
    /// \note CPU usage should be minimal within that scope.
    base::ScopedBlockingCall scoped_blocking_call(FROM_HERE
      , base::BlockingType::MAY_BLOCK);

    DCHECK(!full_path.empty()
      && full_path.value().size() < kBackupFilenameMaxLen);

    bool read_success
      = base::ReadFileToStringWithMaxSize(full_path
          , &file_data
          , kBackupFileMaxSizeInBytes);
    if (!read_success) {
      LOG(ERROR)
        << "Failed to read file: "
        << full_path.value();
      return std::nullopt;
    }
  }

  return parseBackupFromStr(file_data);
}

void
  BackupManager::processQueuedBackupData()
{
  TRACE_EVENT0("headless", "BackupManager_backup");

  LOG(INFO) << "(BackupManager) started backup...";

  DCHECK(task_runner_->RunsTasksInCurrentSequence());

  if(backupLatestDataQueue_.empty() && backupTasksQueue_.empty()) {
    LOG(INFO) << "(BackupManager) nothing to backup...";
    return;
  }

  for(auto const &kv : backupLatestDataQueue_)
  {
    LOG(INFO) << "(BackupManager) processing queued data...";

    const base::FilePath full_path
      = dir_path_.Append(kv.first);

    /// \note MAY_BLOCK
    const BackupWriteStatus create_status
      = CreateBackupFile(full_path
          , serialize(kv.second));

    NotifyBackupObservers(full_path, create_status);
  }

  backupLatestDataQueue_.clear();

  for(base::OnceClosure& task : backupTasksQueue_)
  {
    LOG(INFO) << "(BackupManager) processing queued task...";
    DCHECK(task);
    std::move(task).Run();
  }

  backupTasksQueue_.clear();

  LOG(INFO) << "(BackupManager) finished backup...";
}

void
  BackupManager::NotifyBackupObservers(
    const base::FilePath &full_path
    , const BackupWriteStatus &status)
{
  DCHECK(task_runner_->RunsTasksInCurrentSequence());

  observers_->Notify(FROM_HERE
    , &BackupObserver::OnBackup
    , full_path
    , status);
}

void
  BackupManager::AddObserver(
    BackupObserver* observer)
{
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  DCHECK(observer);
  observers_->AddObserver(observer);
}

void
  BackupManager::RemoveObserver(
    BackupObserver* observer)
{
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  DCHECK(observer);
  observers_->RemoveObserver(observer);
}

void
  BackupManager::startup(
    const Events::Startup& event)
{
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  LOG(INFO) << "(BackupManager) startup";

  DCHECK(!backup_timer_.IsRunning());

  task_runner_->PostTask(FROM_HERE
    , base::Bind(&BackupManager::restart_timer
                 , weak_this_
                 , /*copied*/event)
  );
}

void
  BackupManager::restart_timer(
    const Events::Startup& event)
{
  DCHECK(task_runner_->RunsTasksInCurrentSequence());

  LOG(INFO) << "(BackupManager) restart_timer";

  // It's safe to destroy or restart Timer on another sequence after Stop().
  backup_timer_.Stop();
  backup_timer_.Reset(); // abandon scheduled task
  backup_timer_.Start(FROM_HERE
    , event.backupPeriod
    , this
    , &BackupManager::processQueuedBackupData
  );
  DCHECK_EQ(backup_timer_.GetCurrentDelay(), event.backupPeriod);
}

void
  BackupManager::shutdown(
    const Events::Shutdown& event)
{
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  LOG(INFO) << "(BackupManager) shutdown";
  backup_timer_.Stop();

  // If you want some state to be deleted only after all tasks
  // currently posted to a SequencedTaskRunner have run,
  // use WaitableEvent after posting the last task.
  wait_shutdown_.Signal();

  // All observers must be gone now:
  // unregister observers before, in their own Shutdown(), and all others
  // should have done it now when they got the shutdown notification.
  // Note: "might_have_observers" sounds like it might be inaccurate, but it can
  // only return false positives while an iteration over the ObserverList is
  // ongoing.
  //DCHECK(!observers_->might_have_observers());
#if DCHECK_IS_ON()
  observers_->AssertEmpty();
#endif // DCHECK_IS_ON()
}

void
  BackupManager::wait_shutdown()
{
  wait_shutdown_.Wait();
}

} // namespace backend

// in main()

  std::unique_ptr<BackupObserver> backupObserver
    = std::make_unique<AppBackupObserver>(
        backup_sequenced_task_runner
        );

  {
    std::string  BackupFilenameStr = "SomeBackupFilenameStr";

    base::Promise<scoped_refptr<BackupManager::BackupResult>>
      bak_promise = bak_mgr->promise_backup(FROM_HERE
        , BackupFilenameStr
        , BackupManager::BackupData{}
      );

    bak_promise
    .ThenOn(main_loop_task_runner, FROM_HERE,
       base::BindOnce(
         []
         (scoped_refptr<BackupManager::BackupResult> data)
         {
           DCHECK(data);

           LOG(INFO)
            << "(1) notified about periodic backup with "
            << data->full_path;

           return base::Resolved<
              scoped_refptr<BackupManager::BackupResult>
            >(data);
         }
         //, bak_mgr
       ))
    .ThenOn(main_loop_task_runner, FROM_HERE,
       base::BindOnce(
         []
         (scoped_refptr<BackupManager::BackupResult> data)
         {
           DCHECK(data);
           LOG(INFO)
            << "(after 1) notified about periodic backup with "
            << data->full_path;
         }
         //, bak_mgr
       ));

    bak_promise
    .ThenOn(main_loop_task_runner, FROM_HERE,
       base::BindOnce(
         []
         (scoped_refptr<BackupManager::BackupResult> data)
         {
           DCHECK(data);
           LOG(INFO)
            << "(2) notified about periodic backup with "
            << data->full_path;
         }
         //, bak_mgr
       ));
  }
```
