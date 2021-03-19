# About

When devices retry calls without waiting, they can produce a heavy load

Truncated exponential backoff is a standard error-handling strategy for network applications.

In this approach, a client periodically retries a failed request with increasing delays between requests.

An exponential backoff algorithm retries requests exponentially, increasing the waiting time between retries up to a maximum backoff time. For example:

1. Make a request to server.

2. If the request fails, wait 1 + random_number_milliseconds seconds and retry the request.

3. If the request fails, wait 2 + random_number_milliseconds seconds and retry the request.

4. If the request fails, wait 4 + random_number_milliseconds seconds and retry the request.

5. And so on, up to a maximum_backoff time.

6. Continue waiting and retrying up to some maximum number of retries, but do not increase the wait period between retries.

The client can continue retrying after it has reached the maximum_backoff time.

Retries after this point do not need to continue increasing backoff time.

The truncated (Truncated exponential backoff) simply means that after a certain number of increases, the exponentiation stops.

Use `BackoffEntry.maximum_backoff_ms` to truncate exponential backoff.

See for details:

* https://www.tutorialspoint.com/back-off-algorithm-for-csma-cd
* https://www.baeldung.com/resilience4j-backoff-jitter
* https://en.wikipedia.org/wiki/Exponential_backoff

## Jitter (randomness to the backoff to spread)

Adding jitter provides a way to break the synchronization across the clients thereby avoiding collisions.

If all the failed calls back off at the same time, they increase overload even more.

The solution is jitter.

Jitter adds randomness to the backoff to spread the retries in time.

## Example: login backoff

To add backoff during login:

```cpp
::basis::BackoffEntry login_backoff_;
```

To configure backoff:

```cpp

basis::BackoffEntry::Policy kDefaultBackoffPolicy = {
  // Number of initial errors (in sequence) to ignore before applying
  // exponential back-off rules.
  5,

  // Initial delay for exponential back-off in ms.
  2000,

  // Factor by which the waiting time will be multiplied.
  2,

  // Fuzzing percentage. ex: 10% will spread requests randomly
  // between 90%-100% of the calculated time.
  0,

  // Maximum amount of time we are willing to delay our request in ms.
  -1,

  // Time to keep an entry from being discarded even when it
  // has no significant state, -1 to never discard.
  -1,

  // If false, than don't use initial delay unless the last request was an error.
  false,
};

// ...
login_backoff_(&kDefaultBackoffPolicy),
// ...
// It's okay to fill the backoff policy after being used in construction.
kDefaultBackoffPolicy.num_errors_to_ignore = 4;
kDefaultBackoffPolicy.initial_delay_ms = 1000;
kDefaultBackoffPolicy.multiply_factor = 2.0;
kDefaultBackoffPolicy.jitter_factor = 0.2;
kDefaultBackoffPolicy.maximum_backoff_ms = 15 * 60 * 1000;
kDefaultBackoffPolicy.entry_lifetime_ms = -1;
kDefaultBackoffPolicy.always_use_initial_delay = false;
// ...
```

To check backoff during login:

```cpp
// Called after authentication has started.
void OnSessionAuthenticating(ClientSession* client) {
  // We treat each incoming connection as a failure to authenticate,
  // and clear the backoff when a connection successfully
  // authenticates. This allows the backoff to protect from parallel
  // connection attempts as well as sequential ones.
  if (login_backoff_.ShouldRejectRequest()) {
    LOG(WARNING) << "Disconnecting client " << client->client_jid() << " due to"
                    " an overload of failed login attempts.";
    // Disconnect client
    // ...
    return;
  }
  login_backoff_.InformOfRequest(false);
}

// Called after authentication has finished successfully.
void OnSessionAuthenticated(ClientSession* client) {
  // ...

  login_backoff_.Reset();

  // Notify observers that there is at least one authenticated client.
  // ...
}
```

## Example: retry backoff for url fetcher with delay `GetTimeUntilRelease`

```cpp
// Schedules a retry attempt, informs the backoff of a previous request's
// failure when |update_backoff| is true.
void RetryWithBackoff(bool update_backoff) {
  if (update_backoff) {
    // Inform that a request failed (`false`).
    backoff_entry_.InformOfRequest(false);
    url_fetcher_.reset();
  }

  if (backoff_entry_.ShouldRejectRequest()) {
    DVLOG(1) << "Delay for: "
             << backoff_entry_.GetTimeUntilRelease().InMilliseconds()
             << " milliseconds.";
    // schedule `RetryWithBackoff` with `update_backoff = false`
    // and delay `GetTimeUntilRelease`
    base::MessageLoop::current()->PostDelayedTask(
        FROM_HERE,
        base::Bind(&RetryWithBackoff,
                   weak_ptr_factory_.GetWeakPtr(),
                   false),
        backoff_entry_.GetTimeUntilRelease());
    return;
  }

  url_fetcher_.start();
}
```

## Example

Scenario:

We’re going to request the homepage of https://example.com.

This page requires a valid claims token – so the request I going to throw a HTTP 403 – Forbidden response.

This response, while expected in this case is a nice way to simulate errors which we can retry.

Client code requirements:

We need to try the operation 3 times.

The code should back off exponentially, i.e., the wait time between retries should increase exponentially.

Eg. The first retry happens after 2 seconds, the second after 4 seconds, the third after 8 seconds and so on.

TODO: example code

## TIPS AND TRICKS

* `InformOfRequest(true)` counts as a success, so the backoff entry won't apply exponential
backoff, but will apply the standard delay.

* If you want to reset `BackoffEntry`, than you may also need to change its `backoff_policy`

## BackoffTimer: An object similar to a base::Timer with exponential backoff.

See `BackoffTimer`
