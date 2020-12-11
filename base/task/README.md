This directory has the following layout:
- base/task/: public APIs for posting tasks and managing task queues.
- base/task/thread_pool/: implementation of the ThreadPool.
- base/task/sequence_manager/: implementation of the SequenceManager.

Apart from embedders explicitly managing a ThreadPool and/or SequenceManager
instance(s) for their process/threads, the vast majority of users should only
need APIs in base/task/.

See for details:

* https://www.chromium.org/developers/threaded-task-tracking
* https://chromium.googlesource.com/chromium/src.git/+/62.0.3178.1/docs/subtle_threading_bugs.md
* https://chromium.googlesource.com/chromium/src.git/+/master/docs/callback.md
* https://chromium.googlesource.com/chromium/src/+/master/docs/threading_and_tasks.md

Documentation:

* [Threading and tasks](/docs/threading_and_tasks.md)
* [Callbacks](/docs/callback.md)
