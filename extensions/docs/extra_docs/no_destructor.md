## `base::NoDestructor`

USAGE

```cpp
class ReachedCodeProfiler {
 public:
  static ReachedCodeProfiler* GetInstance();

 private:
  // private constructor due to `NoDestructor`
  ReachedCodeProfiler()
      : current_pid_(getpid()), iteration_number_(0), is_enabled_(false) {}

  // private destructor due to `NoDestructor`
  ~ReachedCodeProfiler() = delete;

  static void OnTimerNotify(sigval_t ignored) {
    ReachedCodeProfiler::GetInstance()->SendSignalToAllThreads();
  }

  // ...

  friend class NoDestructor<ReachedCodeProfiler>;

  DISALLOW_COPY_AND_ASSIGN(ReachedCodeProfiler);
};

// static
ReachedCodeProfiler* ReachedCodeProfiler::GetInstance() {
  static base::NoDestructor<ReachedCodeProfiler> instance;
  return instance.get();
}
```

