## About

`multiconfig` - configuration system that can support
multiple configuration providers.

Configuration providers can read value from some data source
(json file, environment variables, etc.)

Imagine that you already have `json configuration loader`
and `ini configuration loader`.

Some configuration options use `json configuration loader`: `my_json_guid`.

And some configuration options use `ini configuration loader`: `my_ini_id`.

You can use `multiconfig` to add configuration option `my_name`
that can load from either `json configuration loader` or `ini configuration loader`.

```cpp
// "my_name" can load from ini or json files
MULTICONF_string(my_name, "my_default_value", {INI_MULTICONF_LOADER, JSON_MULTICONF_LOADER});

// "my_json_guid" can load only from json files
MULTICONF_string(my_json_guid, "my_default_value", {JSON_MULTICONF_LOADER});

// "my_ini_id" can load only from ini files
MULTICONF_string(my_ini_id, "my_default_value", {INI_MULTICONF_LOADER});
```

Note that `MULTICONF_String` is same as `MULTICONF_type(std::string, ...)`

```cpp
#define MULTICONF_String(...) \
  MULTICONF_type(std::string, __VA_ARGS__)
```

## Usage

Syntax used to add new configuration option:

```cpp
MULTICONF_{{typename}}({[NAME}}, {{DEFAULT_VALUE}}, {{INITIALIZER_LIST_OF_LOADERS}});
```

Example that adds multiple configuration options:

```cpp
// creates var. `my_string_key` and configuration option using text "my_string_key"
MULTICONF_String(my_string_key, "-12345", BUILTIN_MULTICONF_LOADERS);

// creates var. `my_bool_key` and configuration option using text "my_bool_key"
MULTICONF_Bool(my_bool_key, "True", BUILTIN_MULTICONF_LOADERS);

MULTICONF_Int(my_int_key, "-12345", BUILTIN_MULTICONF_LOADERS);
```

Note that `MULTICONF_Bool(my_bool_key, ...`
will declare variable `basic::MultiConfValueObserver<bool> my_bool_key = ...`.

So make sure that you place `MULTICONF_`
inside anonymous namespace or struct/class/etc.

It is also valid to use `static` like so:
`static MULTICONF_Bool(my_bool_key, "True", BUILTIN_MULTICONF_LOADERS);`

To use registered configuration options:

```cpp
// required before first usage
CHECK_OK(basic::MultiConf::GetInstance().init());

// you can reload confuguration on demand
CHECK_OK(basic::MultiConf::GetInstance().clearAndReload());

// may crash if `string` not convertable to `bool`, see `error_status().ok()`
std::string str = my_string_key.GetValue();

// may crash if `string` not convertable to `bool`, see `error_status().ok()`
bool flag = my_bool_key.GetValue();
```

Note that without `clearAndReload` configuration values will be cached
i.e. changes in configuration files are NOT auto detected
(but you can add that functionality manually, see `addObserver`).

Note that `GetValue` may fail if provided configuration is broken
(for example, if `my_int_key` can not be converted to `int`  from `string`),
so you can check for errors using `error_status().ok()`.


## Configuration groups

Imagine that you have multiple "plugins" and you need to avoid collision.

You can not create same option `my_key` using
`MULTICONF_String(my_key, "", MY_LOADERS);`
multiple times (even in different files or plugins).

Use multiple configuration groups to avoid collision like so:
#define CONFIG_GROUP_A "my_plugin_a"
#define CONFIG_GROUP_B "my_plugin_b"
`MULTICONF_String(my_key, "", MY_LOADERS, CONFIG_GROUP_A);`
`MULTICONF_String(my_key, "", MY_LOADERS, CONFIG_GROUP_B);`

It will create `my_plugin_a_my_key` and `my_plugin_b_my_key`
configuration values (combines group name and option name).

For now we used configuration groups only to avoid collision.

They can also be used to reload on demand limited set of options
without need to refresh whole configuration.

That may help if you have configuration stored in multiple files,
each configuration group can be associated with individual file.

See:

```cpp
basic::StatusOr<std::string> tryLoadString(
  const std::string& name
  , const std::string& configuration_group
  , const base::Value& option_settings)
```

The basic idea is that your configuration loader can load file based
on provided `configuration_group`.

```cpp
// load file with name based on `configuration_group`!
std::string json_loaded = loadFileByPath(configuration_group);
// no need to combine `name` and `configuration_group` here!
std::string result = getValueByJsonKey(name);
```

Make sure that `configuration_group` is used somehow to avoid collision.
If `configuration_group` does not affect anything, than at least use it
to create combined key name:

```cpp
// load configuration option with title `key`, but not with title `name`!
std::string key = formatConfigNameAndGroup(name, configuration_group);
// used combined `name` and `configuration_group` here!
std::string result = getEnvironmentVariableByName(key);
```

## Multiple threads

`MULTICONF_String`, `MULTICONF_type` can be called from multiple threads,
but can NOT be called concurrently.

You can create per-thread `MULTICONF_Observer` to overcome that issue.

```cpp
MULTICONF_Float(my_conf_key, "1.12", BUILTIN_MULTICONF_LOADERS);
// Observe existing variable on multiple thread
MULTICONF_Observer(conf_key_observer_on_thread_1, my_namespace::my_conf_key);
MULTICONF_Observer(conf_key_observer_on_thread_2, my_namespace::my_conf_key);
MULTICONF_Observer(conf_key_observer_on_thread_3, my_namespace::my_conf_key);
```

Note that `MULTICONF_Observer` observes already existing configuration option.

## Global configuration loaders

You can create configuration option with
`basic::useGlobalLoaders::kTrue` or `basic::useGlobalLoaders::kFalse`

```cpp
MULTICONF_String(my_conf_key_1, "abcd", BUILTIN_MULTICONF_LOADERS, basic::useGlobalLoaders::kTrue);

MULTICONF_String(my_conf_key_2, "abcd", BUILTIN_MULTICONF_LOADERS, basic::useGlobalLoaders::kFalse);
```

Not provided `basic::useGlobalLoaders` value equals to `kTrue`.

If you used `basic::useGlobalLoaders::kTrue`,
than your configuration option will be affeted by functions:

* basic::MultiConf::GetInstance().addGlobalLoaders(...)
* basic::MultiConf::GetInstance().removeGlobalLoaders(...)
* basic::MultiConf::GetInstance().hasGlobalLoaders(...)

I.e. configuration option will use no only loaders prvodided during its construction,
but also global ones.

## Dynamic per-option settings using `base::Value`

You can associate `base::Value` with configuration option:

```cpp
MULTICONF_String(my_conf_key_Y, "abcd", {MY_LOADER_1}
  , kDefaultTestGroup, basic::useGlobalLoaders::kTrue, jsonConfigOption());
```

Here `jsonConfigOption` is:

```cpp
static base::Value simpleJsonConfigOption()
{
  base::Value root(base::Value::Type::DICTIONARY);

  // `root.ExtractPath("one.two.three")` is `Value(123)`
  root.SetPath("one.two.three", base::Value(123));

  // `moved_value.FindKey("Int")->GetInt()` is `Value(123)`
  storage.emplace("Int", std::make_unique<Value>(123));

  return root;
}
```

Because `base::Value` can be parsed from json,
you can associate arbitrary json string with configuration option:

```cpp
constexpr char kMustReturnStr[] = "MustReturnStr";
constexpr char kMustReturnStrResult[] = "kMustReturnStrResult";
constexpr char kDefaultTestGroup[] = "test_group_1";

MULTICONF_String(my_conf_key_json, "default_val", {MY_LOADER_1}
  , kDefaultTestGroup, basic::useGlobalLoaders::kTrue
  , basic::internal::parseJSONData(basic::Substitute(R"raw(
{
  "opt1":"val1",
  "$1":"$2",
  "opt3":"val3"
}
)raw", kMustReturnStr, kMustReturnStrResult)).ConsumeValueOrDie());

EXPECT_EQ(kMustReturnStrResult, my_conf_key_json.GetValue());
```

Here `parseJSONData` is:

```cpp
basic::StatusOr<base::Value> parseJSONData(
  const std::string& json_data)
{
  static const size_t kMaxDebugLogItemSize = 9999;

  // This could be really slow.
  base::ScopedBlockingCall scoped_blocking_call(
    FROM_HERE, base::BlockingType::MAY_BLOCK);

  base::JSONReader::ValueWithError value_with_error =
    base::JSONReader::ReadAndReturnValueWithError(
      json_data
      , base::JSON_PARSE_RFC);

  if (!value_with_error.value) {
    RETURN_ERROR()
      << "Failed to parse JSON: "
      << "JSON error "
      << base::StringPrintf(
           "%s (%d:%d)"
           , value_with_error.error_message.c_str()
           , value_with_error.error_line
           ,  value_with_error.error_column)
      << " JSON data starts with: "
      << json_data.substr(0, kMaxDebugLogItemSize)
      << " ...";
  }

  base::Value& root
    = value_with_error.value.value();

  if (!root.is_dict()) {
    RETURN_ERROR()
      << "Failed to parse JSON:"
      << " Root item must be a dictionary."
      << " But it is: "
      << base::Value::GetTypeName(root.type())
      << " and it has type index: "
      << static_cast<size_t>(root.type())
      << " JSON data starts with: "
      << json_data.substr(0, kMaxDebugLogItemSize)
      << " ...";
  }

  return std::move(value_with_error.value.value());
}
```

## How to add custom configuration provider

Imagine that you want to load some configuration option from
either json file environment variable.

Lets create configuration provider that can read environment variables.

Each configuration provider must have public `id` and function that returns `basic::StatusOr<std::string>` based on provided `string`:

```cpp
basic::StatusOr<std::string> tryLoadString(
  const std::string& name
  , const std::string& configuration_group
  , const base::Value& option_settings);
static constexpr char kId[] = "EnvMultiConf";
```

Example:

```cpp
// Configuration loader that uses environment vars
class EnvMultiConf {
 public:
  // Thread safe GetInstance.
  static EnvMultiConf& GetInstance();

  // Loads configuraton value from environment vars
  basic::StatusOr<std::string> tryLoadString(
    const std::string& name
    , const std::string& configuration_group
    , const base::Value& option_settings);

 public:
  // id for debug purposes
  static constexpr char kId[] = "EnvMultiConf";

 private:
  EnvMultiConf();

 private:
  std::unique_ptr<base::Environment> env_;

  friend class base::NoDestructor<EnvMultiConf>;

  DISALLOW_COPY_AND_ASSIGN(EnvMultiConf);
};


EnvMultiConf::EnvMultiConf()
  : env_{base::Environment::Create()}
{}

EnvMultiConf& EnvMultiConf::GetInstance() {
  // C++11 static local variable initialization is
  // thread-safe.
  static base::NoDestructor<EnvMultiConf> instance;
  return *instance;
}

basic::StatusOr<std::string> EnvMultiConf::tryLoadString(
  const std::string& name
  , const std::string& configuration_group
  , const base::Value& option_settings)
{
  UNREFERENCED_PARAMETER(option_settings);

  std::string key = FORMAT_NAME_AND_GROUP(name, configuration_group);

  DCHECK(!key.empty());

  std::string result;

  if(env_->GetVar(key, &result))
  {
    return result;
  }

  RETURN_ERROR()
    << " ("
    << kId
    << ") unable to find key in environment variables: "
    << key;
}
```

Now you can pass created configuration provided when you create
new configuration options using `MULTICONF_`

Example:

```cpp
#define ENV_MULTICONF_LOADER \
    basic::MultiConfLoader{ \
      ::basic::EnvMultiConf::kId \
      , base::BindRepeating( \
          &::basic::EnvMultiConf::tryLoadString \
          , base::Unretained(&EnvMultiConf::GetInstance())) \
    }

// note that each configuration option can have custom set of configuration loaders
MULTICONF_String(my_conf_key, "abcd", {ENV_MULTICONF_LOADER, JSON_MULTICONF_LOADER});
```

## Implementation details

Configuration provider can return only string value (see `tryLoadString`)
i.e. even if you read `int` from json file, it will be stored as `string` internally.

`GetValue()` returs cached value.

Cached value may be any data type that was parsed from `string`.

`GetValue()` does not parse `string` on each use.

We use observer pattern to detect configuration changes and invalidate
only required values in cache, see `addObserver`.

Each `MULTICONF_*` macro expected to create single wariable,
so you will be able to write code: `static MULTICONF_String(...)`.
