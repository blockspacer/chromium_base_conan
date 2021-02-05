# About

Some usage examples.

## FAQ

* How to prevent not fully written files due to crash?

See `important_file_writer.h`

* How to store file path literals?

```cpp
const base::FilePath::CharType my_path[] = FILE_PATH_LITERAL("my_file.txt");
```

* How to check file errors?

```cpp
base::File::Error error = base::File::GetLastFileError();

base::File::ErrorToString(error)
```

* How to check max. open file limit?

```cpp
size_t max_open_files = base::GetMaxFds();
if (max_open_files < 10'000)
{
  // Disable file cache etc.
}
```

* How to work with UTF PathService

```cpp
const std::string& fname = ...;
FilePath::FromUTF8Unsafe(fname)
```

## Example (path literals)

```cpp
#include <base/logging.h>
#include <base/path_service.h>
#include <base/files/file_util.h>
#include <base/i18n/icu_util.h>

const ::base::FilePath::CharType kIcuDataFileName[]
  = FILE_PATH_LITERAL("./resources/icu/icudtl.dat");

void initICUi18n(
  const ::base::FilePath::CharType icuFileName[])
{
  ::base::FilePath dir_exe;
  if (!base::PathService::Get(base::DIR_EXE, &dir_exe)) {
    NOTREACHED();
  }
  if(!base::PathExists(dir_exe.Append(icuFileName))) {
    LOG(WARNING)
      << "unable to find icu i18n file: "
      << dir_exe.Append(icuFileName);
  } else {
    DVLOG(9)
      << "loading icu i18n file: "
      << dir_exe.Append(icuFileName);
  }
  bool icu_initialized
    = ::base::i18n::InitializeICUWithPath(
        dir_exe.Append(icuFileName));
  if(!icu_initialized) {
    LOG(WARNING)
      << "unable to initialize icu i18n file: "
      << dir_exe.Append(icuFileName);
  }
}
```

## Example (file seek)

```cpp
class ChromiumSequentialFile {
 public:
  ChromiumSequentialFile(const std::string& fname, base::File f)
      : filename_(fname), file_(std::move(f)) {}
  ~ChromiumSequentialFile() override = default;
  // Note: This method is relatively hot during leveldb database
  // compaction. Please avoid making them slower.
  Status Read(size_t n, Slice* result, char* scratch) override {
    int bytes_read = file_.ReadAtCurrentPosNoBestEffort(scratch, n);
    if (bytes_read == -1) {
      base::File::Error error = base::File::GetLastFileError();
      return MakeIOError(filename_, base::File::ErrorToString(error),
                         kSequentialFileRead, error);
    }
    *result = Slice(scratch, bytes_read);
    return Status::OK();
  }
  Status Skip(uint64_t n) override {
    if (file_.Seek(base::File::FROM_CURRENT, n) == -1) {
      base::File::Error error = base::File::GetLastFileError();
      return MakeIOError(filename_, base::File::ErrorToString(error),
                         kSequentialFileSkip, error);
    } else {
      return Status::OK();
    }
  }
 private:
  std::string filename_;
  base::File file_;
  DISALLOW_COPY_AND_ASSIGN(ChromiumSequentialFile);
};
```
