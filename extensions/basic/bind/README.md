# About

Place here code related to `callback` and `bind`.

## bindChecked*

If you want to

* Limit callback execution time.
* Check that callback will be executed at least once.
* Check that bound object pointer will not become invalid during callback execution.
* Bind custom checks to callback.

than see `bind_checked.h`

## BindToTaskRunner*

If you want to force callback execution on specific task runner, than see `bind_to_task_runner.h`

## `CallableHook`

`CallableHook` is `map<string, callback>`.
