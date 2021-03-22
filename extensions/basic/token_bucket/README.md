# About

The basic principle is this:
a bucket with some maximum token capacity has tokens added to it at a constant rate,
and every operation withdraws some number of tokens from the bucket.
Between the maximum capacity, the rate at which tokens are added, and the cost of an operation,
token buckets have quite a bit of flexibility.

Token buckets are, in a sense, a generalization of a more common technique,
where a certain amount of time must pass between operations.

Where this simple time-based technique falls short, however,
is addressing short bursts of operations.
If your goal is to, say, set a limit of ten operations a second,
then requiring a tenth of a second to pass between each operation would certainly accomplish that.
However, this would prevent someone from, for example,
performing ten operations in a burst, waiting one second,
performing a burst of ten more operations, etc.
The average rate would still be ten operations per second,
but the throttling mechanism is restricting users to one operation per tenth of a second,
which turns out to be a subtly different limit from the one we had in mind.

A token bucket can be used to implement a ten operation per second limit more logically.
If each operation costs one token,
then we can add a token to the bucket every tenth of a second and limit the bucket to ten tokens.
A user can “spend” these tokens at whatever rate they want,
but will on average be limited to ten operations in a second.
It’s worth noting that, using this configuration,
a second can pass in which more than ten operations have succeeded.
However, the total average rate will never exceed our ten per second limit.

See for details:

* https://medium.com/quinbay/rate-limiter-implementation-token-bucket-algorithm-636bb32741b2
* https://medium.com/bliblidotcom-techblog/understanding-rate-limiting-algorithms-2244c302025a
* https://medium.com/smyte/rate-limiter-df3408325846
* https://cloud.google.com/solutions/rate-limiting-strategies-techniques

## Efficiently implementing token buckets

Token bucket centers around withdrawals,
i.e. checking whether there are enough tokens available and removing them if possible.
It turns out that right before each withdrawal we can also take care of adding tokens to the bucket.
If we also store the time the balance was last updated,
then we can calculate the number of tokens that would have been added
and add them before attempting a withdrawal.

Token bucket only needs to remember the time of and balance after the last withdrawal.

A withdrawal can then be performed in a constant number of operations.

## Token Bucket for rate limiting

Token Bucket is the simplest rate limiter algorithm.

We simply keep track of the number of requests made within a set time interval.

# Example: Using Token Bucket to rate limit function calls

We have a function which is going to be called by multiple threads.

The problem is to find a way to limit the number of times this function
is executed per second given that we don't have a control over:

a) The number of threads calling this function.

b) The number of times per second this function will be called by any thread.

Suppose you want to limit the execution rate of the function given below:

```cpp
void printHelloWorld();
```

You need to do 2 things:

You need to create a tokenBucket object constructed with the required rate you want your function to be executed per second. e.g. tokenBucket aBucket(500);

When calling your function, then instead of: printHelloWorld();

you have to do:

```cpp
if(token_bucket.AreTokensAvailable()) {
  printHelloWorld();
}
```
