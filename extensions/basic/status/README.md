# About

Developer guide for error handling.

Inspired by https://abseil.io/docs/cpp/guides/status

## MUST SEE

Read comments in `status_macros.h`

## TIPS AND TRICKS: Combine `StatusOr` and `WithDetails` (see `with_details.h`).

That allows to provide custom reason text to successfull `StatusOr` (not only error message text).

In functions with priority-ordered return statements, this helps with identifying the statement that took effect.

But it is bad to log something in API function, so you need to return reason string using `WithDetails`.

## TIPS AND TRICKS: Make debugging easy

You can include extensive free form information in the error message string, but do not forget that you can access source code location that created `Status` (using `.location()` method).

## TIPS AND TRICKS: Use macros to simplify these common checks:

Suppose we want to read number from file or string, lets create helper functions:

```cpp
static ::basic::StatusOr<int> ParseInt(const std::string& str)
{
  using namespace ::app_error_space;

  std::size_t index = 0;
  int result = std::stoi(str, &index);
  if(index == str.length()){
    // successful conversion
    return {FROM_HERE, result};
  }

  // something in the string stopped the conversion, at index
  RETURN_ERROR(ERR_INVALID_PARAM).without_logging()
    << "Invalid input string:"
    << str;
}

static ::basic::Status GetContents(const std::string& path, std::string* data)
{
  using namespace ::app_error_space;

  if(path.empty())
    RETURN_ERROR(ERR_INVALID_PARAM)
        << "Invalid path.";

  *data = path; // for test purposes only

  RETURN_OK();
}
```

BEFORE:

```cpp
static ::basic::StatusOr<int> ReadNumber(const std::string& path) {
  std::string data;
  auto status = GetContents(path, &data);
  if (!status.ok()) return status;

  auto number_or = ParseInt(data)
  if (!number_or.ok()) {
    return number_or.status()
  }

  return number.ConsumeValueOrDie();
}
```

AFTER:

```cpp
static ::basic::StatusOr<int> ReadNumber(const std::string& path) {
  std::string data;
  RETURN_IF_ERROR(GetContents(path, &data));

  ASSIGN_OR_RETURN(int number, ParseInt(data));
  return {FROM_HERE, number};
}
```

USAGE:

```cpp
int main()
{
  DVLOG(99)
    << " ReadNumber 327: "
    << ReadNumber("327"); // OK
  DVLOG(99)
    << " ReadNumber abc: "
    << ReadNumber("abc"); // ERR
  DVLOG(99)
    << " ReadNumber xyz: ";
  ::basic::StatusOr<int> readNumberStatusOr = ReadNumber("xyz");
  // `!status.ok()` required by APPEND_ERROR
  DCHECK(!readNumberStatusOr.ok());
  ::basic::Status readNumberStatus = readNumberStatusOr.status();
  DVLOG(99)
    << " Performing APPEND_ERROR ";
  readNumberStatus = APPEND_ERROR(readNumberStatus).with_log_stack_trace()
      << " Custom error appended.";
  DVLOG(99)
    << " Performing APPEND_ERROR ";
  readNumberStatus = APPEND_ERROR(readNumberStatus).without_logging()
      << " Another error appended.";
  DVLOG(99)
    << " Performing APPEND_STATUS_IF_ERROR ";
  APPEND_STATUS_IF_ERROR(readNumberStatus, ParseInt("foo").status());
  DVLOG(99)
    << " Result xyz: "
    << readNumberStatus; // ERR
  LOG_IF_ERROR(readNumberStatus);
  exit(0);
}
```

## How to map custom error code to status code

See `app_error_space.h`

## MUST READ

- http://www.furidamu.org/blog/2017/01/28/error-handling-with-statusor/
- https://github.com/sabbakumov/rst/blob/83004dfb406ffc5d3a791e71815320488b0d7b3d/README.md#statusor
- https://github.com/samiurkh1n/condit

## constructors

For constructors, the style guide is pretty specific not to do heavy work that could fail in constructors, and prefer factory functions (plus making the constructor private) to make sure you do not get a half-formed object.

## Use `Status(Or)` for error handling

Explicitly declare your function to be capable of returning an error.

```cpp
Functions which can produce an error should return a Status.

To propagate an error status, use the RETURN_IF_ERROR macro.

RETURN_IF_ERROR(f());

StatusOr
StatusOr<T> is the union of a Status object and a T object.

It offers a way to use return values instead of output parameters for functions which may fail.

For example, consider the code:

Output out;
Status s = foo(&out);
if (!s.ok()) {
  return {FROM_HERE, s};
}
out.DoSomething();
With StatusOr<T>, we can write this as

StatusOr<Output> result = foo();
if (!result.ok()) {
  return result.status();
}
result->DoSomething();
Pros:

Return values are easier to reason about than output parameters.

The types returned through StatusOr<T> don't need to support empty states.

To return a type as an output parameter, we must either use a unique_ptr<T> or support an empty state for the type so that we can initialize the type before passing it as an output parameter.

StatusOr<T> reduces the number of objects we have in an "uninitialized" state.

Cons:

StatusOr<T> adds complexity. It raises questions about what happens when T is null and how StatusOr<T> behaves during moves and copies.

StatusOr<T> also generally comes with macros such as ASSIGN_OR_RETURN, which add additional complexity.
```

```cpp
// StatusOr<T> is the union of a Status object and a T
// object. StatusOr models the concept of an object that is either a
// usable value, or an error Status explaining why such a value is
// not present. To this end, StatusOr<T> does not allow its Status
// value to be Status::OK. Furthermore, the value of a StatusOr<T*>
// must not be null. This is enforced by a debug check in most cases,
// but even when it is not, clients must not set the value to null.
//
// The primary use-case for StatusOr<T> is as the return value of a
// function which may fail.
//
// Example client usage for a StatusOr<T>, where T is not a pointer:
//
//  StatusOr<float> result = DoBigCalculationThatCouldFail();
//  if (result.ok()) {
//    float answer = result.ValueOrDie();
//    printf("Big calculation yielded: %f", answer);
//  } else {
//    LOG(ERROR) << result.status();
//  }
//
// Example client usage for a StatusOr<T*>:
//
//  StatusOr<Foo*> result = FooFactory::MakeNewFoo(arg);
//  if (result.ok()) {
//    std::unique_ptr<Foo> foo(result.ValueOrDie());
//    foo->DoSomethingCool();
//  } else {
//    LOG(ERROR) << result.status();
//  }
//
// Example client usage for a StatusOr<std::unique_ptr<T>>:
//
//  StatusOr<std::unique_ptr<Foo>> result = FooFactory::MakeNewFoo(arg);
//  if (result.ok()) {
//    std::unique_ptr<Foo> foo = std::move(result.ValueOrDie());
//    foo->DoSomethingCool();
//  } else {
//    LOG(ERROR) << result.status();
//  }
//
// Example factory implementation returning StatusOr<T*>:
//
//  StatusOr<Foo*> FooFactory::MakeNewFoo(int arg) {
//    if (arg <= 0) {
//      return InvalidArgument("Arg must be positive");
//    } else {
//      return {FROM_HERE, new Foo(arg)};
//    }
//  }
//
// Note that the assignment operators require that destroying the currently
// stored value cannot invalidate the argument; in other words, the argument
// cannot be an alias for the current value, or anything owned by the current
// value.
```

Example:

```cpp
::basic::Status ReadProtoFromBinFile(const std::string& filename,
                                    ::google::protobuf::Message* message) {
  std::string buffer;
  RETURN_IF_ERROR(ReadFileToString(filename, &buffer));
  if (!message->ParseFromString(buffer)) {
    return MAKE_ERROR(ERR_INTERNAL) << "Failed to parse the binary content of "
                                    << filename << " to proto.";
  }

  return ::basic::OkStatus(FROM_HERE);
}

::basic::StatusOr<std::unique_ptr<Query>> Adapter::Subscribe(
    const std::vector<Path>& paths,
    std::unique_ptr<ChannelWriter<PhalDB>> writer, absl::Duration poll_time) {
  ASSIGN_OR_RETURN(auto db_query, database_->MakeQuery(paths));
  RETURN_IF_ERROR(db_query->Subscribe(std::move(writer), poll_time));
  return {FROM_HERE, db_query};
}

::basic::Status BFSwitch::VerifyChassisConfig(const ChassisConfig& config) {
  // First make sure PHAL is happy with the config then continue with the rest
  // of the managers and nodes.
  absl::ReaderMutexLock l(&chassis_lock);
  ::basic::Status status = ::basic::OkStatus(FROM_HERE);
  APPEND_STATUS_IF_ERROR(status, phal_interface_->VerifyChassisConfig(config));
  APPEND_STATUS_IF_ERROR(status,
                         bf_chassis_manager_->VerifyChassisConfig(config));

  // Get the current copy of the node_id_to_unit from chassis manager. If this
  // fails with ERR_NOT_INITIALIZED, do not verify anything at the node level.
  // Note that we do not expect any change in node_id_to_unit. Any change in
  // this map will be detected in bcm_chassis_manager_->VerifyChassisConfig.
  auto ret = bf_chassis_manager_->GetNodeIdToUnitMap();
  if (!ret.ok()) {
    if (ret.status().error_code() != ERR_NOT_INITIALIZED) {
      APPEND_STATUS_IF_ERROR(status, ret.status());
    }
  } else {
    const auto& node_id_to_unit = ret.ValueOrDie();
    for (const auto& entry : node_id_to_unit) {
      uint64 node_id = entry.first;
      int unit = entry.second;
      ASSIGN_OR_RETURN(auto* pi_node, GetPINodeFromUnit(unit));
      APPEND_STATUS_IF_ERROR(status,
                             pi_node->VerifyChassisConfig(config, node_id));
    }
  }

  if (status.ok()) {
    LOG(INFO) << "Chassis config verified successfully.";
  }

  return status;
}

::basic::Status BFChassisManager::UnregisterEventWriters() {
  absl::WriterMutexLock l(&chassis_lock);
  ::basic::Status status = ::basic::OkStatus(FROM_HERE);
  APPEND_STATUS_IF_ERROR(
      status, bf_pal_interface_->PortStatusChangeUnregisterEventWriter());
  if (!port_status_change_event_channel_->Close()) {
    APPEND_ERROR(status)
        << "Error when closing port status change event channel.";
  }
  if (xcvr_event_writer_id_ != kInvalidWriterId) {
    APPEND_STATUS_IF_ERROR(status,
                           phal_interface_->UnregisterTransceiverEventWriter(
                               xcvr_event_writer_id_));
    xcvr_event_writer_id_ = kInvalidWriterId;
    if (!xcvr_event_channel_->Close()) {
      APPEND_ERROR(status) << "Error when closing transceiver event channel.";
    }
  } else {
    return MAKE_ERROR(ERR_INTERNAL)
           << "Transceiver event handler not registered.";
  }

  port_status_change_event_thread_.join();
  // Once the thread is joined, it is safe to reset these pointers.
  port_status_change_event_reader_ = nullptr;
  port_status_change_event_channel_ = nullptr;

  xcvr_event_thread_.join();
  xcvr_event_reader_ = nullptr;
  xcvr_event_channel_ = nullptr;
  return status;
}

::basic::StatusOr<int> BFChassisManager::GetUnitFromNodeId(
    uint64 node_id) const {
  if (!initialized_) {
    return MAKE_ERROR(ERR_NOT_INITIALIZED) << "Not initialized!";
  }
  const int* unit = FindOrNull(node_id_to_unit_, node_id);
  CHECK_RETURN_IF_FALSE(unit != nullptr)
      << "Node " << node_id << " is not configured or not known.";

  return *unit;
}
```

Where `Code` is one of:

```cpp
enum Code {
  OK = 0,
  CANCELLED = 1,
  UNKNOWN = 2,
  INVALID_ARGUMENT = 3,
  DEADLINE_EXCEEDED = 4,
  NOT_FOUND = 5,
  ALREADY_EXISTS = 6,
  PERMISSION_DENIED = 7,
  UNAUTHENTICATED = 16,
  RESOURCE_EXHAUSTED = 8,
  FAILED_PRECONDITION = 9,
  ABORTED = 10,
  OUT_OF_RANGE = 11,
  UNIMPLEMENTED = 12,
  INTERNAL = 13,
  UNAVAILABLE = 14,
  DATA_LOSS = 15,
  DO_NOT_USE_RESERVED_FOR_FUTURE_EXPANSION_USE_DEFAULT_IN_SWITCH_INSTEAD_ = 20,
  // **DO NOT ADD ANYTHING TO THIS**
};
```

## Example

```cpp
static ::basic::Status testErrInternal()
{
  ::basic::Status status =
    MAKE_ERROR()
      << "testErrInternal_text";
  return status;
}

static ::basic::Status testErrInternal2()
{
  RETURN_ERROR(/*ERR_INVALID_PARAM*/)
      << "testErrInternal2_text";
}

static ::basic::Status testErrInternal3()
{
  int port = -1;

  RETURN_ERR_IF_FALSE(port >= 0)
      << "Port ID must be non-negative. Attempted to get port " << port;

  NOTREACHED();

  //RETURN_ERROR(/*ERR_INVALID_PARAM*/);
  ::basic::Status status =
    MAKE_ERROR()
      << "testErrInternal3_text";
  return status;
}

static ::basic::Status testOk()
{
  RETURN_OK();
}

static ::basic::Status testOk2()
{
  return ::basic::OkStatus(FROM_HERE);
}

static ::basic::StatusOr<std::string> or_testErrInternal()
{
  ::basic::StatusOr<std::string> status =
    MAKE_ERROR()
      << "or_testErrInternal_text";
  return status;
}

static ::basic::StatusOr<std::string> or_testErrInternal2()
{
  RETURN_ERROR(/*ERR_INVALID_PARAM*/)
      << "Unsupported or_testErrInternal2.";
}

static ::basic::StatusOr<std::string> or_testOk()
{
  return {FROM_HERE, "or_testOk!!"};
}

static ::basic::StatusOr<std::string> or_testErrInternal3()
{
  int port = -1;

  RETURN_ERR_IF_FALSE(port >= 0)
      << "Port ID must be non-negative. Attempted to get port " << port;

  NOTREACHED();

  //RETURN_ERROR(/*ERR_INVALID_PARAM*/);
  ::basic::Status status =
    MAKE_ERROR()
      << "or_testErrInternal3_text";
  return status;
}

static ::basic::StatusOr<std::string> or_testOk2()
{
  return {FROM_HERE, "or_testOk2!!"};
}

int main()
{
  {
    ::basic::Status resErrInternal
      = testErrInternal();
    ::basic::Status resErrInternal2
      = testErrInternal2();
    ::basic::Status resErrInternal3
      = testErrInternal3();
    ::basic::Status resOk
      = testOk();
    ::basic::Status resOk2
      = testOk2();
    DVLOG(99)
      << " resErrInternal "
      << resErrInternal;
    DVLOG(99)
      << " resErrInternal2 "
      << resErrInternal2;
    DVLOG(99)
      << " resErrInternal3 "
      << resErrInternal3;
    DVLOG(99)
      << " resOk "
      << resOk;
    DVLOG(99)
      << " resOk2 "
      << resOk2;
  }

  {
    ::basic::StatusOr<std::string> or_resErrInternal
      = or_testErrInternal();
    ::basic::StatusOr<std::string> or_resErrInternal2
      = or_testErrInternal2();
    ::basic::StatusOr<std::string> or_resErrInternal3
      = or_testErrInternal3();
    ::basic::StatusOr<std::string> or_resOk
      = or_testOk();
    ::basic::StatusOr<std::string> or_resOk2
      = or_testOk2();
    DVLOG(99)
      << " or_resErrInternal "
      << or_resErrInternal;
    DVLOG(99)
      << " or_resErrInternal2 "
      << or_resErrInternal2;
    DVLOG(99)
      << " or_resErrInternal3 "
      << or_resErrInternal3;
    DVLOG(99)
      << " or_resOk "
      << or_resOk;
    DVLOG(99)
      << " or_resOk2 "
      << or_resOk2;
  }

  exit(0);
}
```
