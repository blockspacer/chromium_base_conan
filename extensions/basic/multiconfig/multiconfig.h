#pragma once

#include "basic/annotations/guard_annotations.h"
#include <basic/rvalue_cast.h>
#include "basic/status/status_macros.h"
#include "basic/strong_types/strong_bool.h"
#include "basic/core/typed_enum.h"
#include "basic/core/type_name.h"
#include "basic/concept/dependent_false.h"
#include "basic/multiconfig/option_parser.h"

#include <base/gtest_prod_util.h>
#include <base/logging.h>
#include <base/values.h>
#include <base/callback_forward.h>
#include <base/bind.h>
#include <base/base_export.h>
#include <base/macros.h>
#include <base/no_destructor.h>
#include <base/optional.h>
#include <base/files/file_path.h>
#include <base/threading/thread_collision_warner.h>
#include <base/observer_list_threadsafe.h>

#include <string>
#include <ostream>

#define ENV_MULTICONF_LOADER \
    basic::MultiConfLoader{ \
      ::basic::EnvMultiConf::kId \
      , base::BindRepeating( \
          &::basic::EnvMultiConf::tryLoadString \
          , base::Unretained(&EnvMultiConf::GetInstance())) \
    }

#define CMD_MULTICONF_LOADER \
    basic::MultiConfLoader{ \
      ::basic::CmdMultiConf::kId \
      , base::BindRepeating( \
          &::basic::CmdMultiConf::tryLoadString \
          , base::Unretained(&CmdMultiConf::GetInstance())) \
    }

#define JSON_MULTICONF_LOADER \
    basic::MultiConfLoader{ \
      ::basic::JsonMultiConf::kId \
      , base::BindRepeating( \
          &::basic::JsonMultiConf::tryLoadString \
          , base::Unretained(&JsonMultiConf::GetInstance())) \
    }

// Does nothing, useful for tests
#define DUMMY_LOADER \
    basic::MultiConfLoader{ \
      ::basic::DummyLoader::kId \
      , base::BindRepeating(&::basic::DummyLoader::tryLoadString) \
    }

#define BUILTIN_MULTICONF_LOADERS \
  { \
    CMD_MULTICONF_LOADER \
    , ENV_MULTICONF_LOADER \
    , JSON_MULTICONF_LOADER \
  }

/// \note Each `MULTICONF_*` macro expected to create single variable,
/// so you will be able to write code: `static MULTICONF_String(...)`.
///
/// \note You can not create same option `my_key` using
/// `MULTICONF_String(my_key, "", MY_LOADERS);`
/// multiple times (even in different files or plugins).
/// Use multiple configuration groups to avoid collision like so:
/// `MULTICONF_String(my_key, "", MY_LOADERS, CONFIG_GROUP_A);`
/// `MULTICONF_String(my_key, "", MY_LOADERS, CONFIG_GROUP_B);`

// USAGE
//
// MULTICONF_type(float, my_conf_key, "1.12", BUILTIN_MULTICONF_LOADERS);
//
#define MULTICONF_type(TYPE, KEY_NAME, DEFAULT_STR, ...) \
  basic::MultiConfWrapper<TYPE> KEY_NAME \
    {basic::CheckOptionPolicy::kCheckAddedNew, STRINGIFY(KEY_NAME) \
      , DEFAULT_STR \
      , __VA_ARGS__}

// USAGE
//
// MULTICONF_String(my_conf_key, "abcd", BUILTIN_MULTICONF_LOADERS);
//
#define MULTICONF_String(KEY_NAME, DEFAULT_STR, ...) \
  MULTICONF_type(std::string, KEY_NAME, DEFAULT_STR, __VA_ARGS__)

// USAGE
//
// MULTICONF_Bool(my_conf_key, "true", BUILTIN_MULTICONF_LOADERS);
// MULTICONF_Bool(my_conf_key, "True", BUILTIN_MULTICONF_LOADERS);
// MULTICONF_Bool(my_conf_key, "TRUE", BUILTIN_MULTICONF_LOADERS);
// MULTICONF_Bool(my_conf_key, "1", BUILTIN_MULTICONF_LOADERS);
//
#define MULTICONF_Bool(...) \
  MULTICONF_type(bool, __VA_ARGS__)

// USAGE
//
// MULTICONF_Int(my_conf_key, "-12345", BUILTIN_MULTICONF_LOADERS);
//
#define MULTICONF_Int(...) \
  MULTICONF_type(int, __VA_ARGS__)

// USAGE
//
// MULTICONF_Uint(my_conf_key, "12345", BUILTIN_MULTICONF_LOADERS);
//
#define MULTICONF_Uint(...) \
  MULTICONF_type(unsigned, __VA_ARGS__)

// USAGE
//
// MULTICONF_Int64(my_conf_key, "-12345", BUILTIN_MULTICONF_LOADERS);
//
#define MULTICONF_Int64(...) \
  MULTICONF_type(int64_t, __VA_ARGS__)

// USAGE
//
// MULTICONF_Int32(my_conf_key, "-12345", BUILTIN_MULTICONF_LOADERS);
//
#define MULTICONF_Int32(...) \
  MULTICONF_type(int32_t, __VA_ARGS__)

// USAGE
//
// MULTICONF_Uint32(my_conf_key, "12345", BUILTIN_MULTICONF_LOADERS);
//
#define MULTICONF_Uint32(...) \
  MULTICONF_type(uint32_t, __VA_ARGS__)

// USAGE
//
// MULTICONF_Uint64(my_conf_key, "12345", BUILTIN_MULTICONF_LOADERS);
//
#define MULTICONF_Uint64(...) \
  MULTICONF_type(uint64_t, __VA_ARGS__)

// USAGE
//
// MULTICONF_SizeT(my_conf_key, "12345", BUILTIN_MULTICONF_LOADERS);
//
#define MULTICONF_SizeT(...) \
  MULTICONF_type(size_t, __VA_ARGS__)

// USAGE
//
// MULTICONF_Double(my_conf_key, "1.12", BUILTIN_MULTICONF_LOADERS);
//
#define MULTICONF_Double(...) \
  MULTICONF_type(double, __VA_ARGS__)

// USAGE
//
// MULTICONF_Float(my_conf_key, "1.12", BUILTIN_MULTICONF_LOADERS);
//
#define MULTICONF_Float(...) \
  MULTICONF_type(float, __VA_ARGS__)

// MOTIVATION
//
// `MULTICONF_type` can not be used concurrently from multiple threads.
// You can create per-thread `MULTICONF_Observer` to overcome that issue.
//
// USAGE
//
// MULTICONF_Float(my_conf_key, "1.12", BUILTIN_MULTICONF_LOADERS);
// // Observe existing variable on multiple threads
// MULTICONF_Observer(my_conf_key_observer_thread_1, my_namespace::my_conf_key);
// MULTICONF_Observer(my_conf_key_observer_thread_2, my_namespace::my_conf_key);
// MULTICONF_Observer(my_conf_key_observer_thread_3, my_namespace::my_conf_key);
//
/// \note `KEY_NAME` expected to be already existing variable
/// of type `MultiConfWrapper<...>` i.e. no need to call `addOption`.
//
#define MULTICONF_Observer(VAR_NAME, KEY_NAME) \
  auto VAR_NAME = KEY_NAME

namespace base {

class Environment;
class CommandLine;

} // namespace base

namespace basic {

namespace internal {

basic::StatusOr<base::Value> parseJSONData(
  const std::string& json_data);

} // namespace internal

std::string formatConfigNameAndGroup(
  const std::string&name, const std::string group);

struct DummyLoader {
  static basic::StatusOr<std::string> tryLoadString(
    const std::string& key
    , const std::string& configuration_group
    , const base::Value& option_settings) {
    RETURN_ERROR();
  }

  // id for debug purposes
  static constexpr char kId[] = "DummyLoader";
};

// Configuration loader that uses environment vars
class JsonMultiConf {
 public:
  // Thread safe GetInstance.
  static JsonMultiConf& GetInstance();

  // Loads configuraton value from environment vars in order:
  // * key
  // * uppercase(key)
  // * lowercase(key)
  basic::StatusOr<std::string> tryLoadString(
    const std::string& name
    , const std::string& configuration_group
    , const base::Value& option_settings);

  /// \note resets cache even in case of loading error
  MUST_USE_RETURN_VALUE
  basic::Status clearAndParseFromFilePath(
    const base::FilePath& file_path);

  /// \note resets cache even in case of loading error
  // Initializes the instance from a given JSON string,
  // returning true if the string was successfully parsed.
  MUST_USE_RETURN_VALUE
  basic::Status clearAndParseFromString(
    const std::string& json_data);

  // for test purposes
  std::string serializeCachedConfig() const;

 public:
  // id for debug purposes
  static constexpr char kId[] = "JsonMultiConf";

 private:
  JsonMultiConf();

 private:
  FRIEND_TEST_ALL_PREFIXES(MultiConfTest, SimpleTest);

  friend class base::NoDestructor<JsonMultiConf>;

  base::Optional<base::Value> cached_dictionary_;

  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);

  DISALLOW_COPY_AND_ASSIGN(JsonMultiConf);
};

// Configuration loader that uses environment vars
class EnvMultiConf {
 public:
  // Thread safe GetInstance.
  static EnvMultiConf& GetInstance();

  // Loads configuraton value from environment vars in order:
  // * key
  // * uppercase(key)
  // * lowercase(key)
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
  FRIEND_TEST_ALL_PREFIXES(MultiConfTest, SimpleTest);

  std::unique_ptr<base::Environment> env_;

  friend class base::NoDestructor<EnvMultiConf>;

  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);

  DISALLOW_COPY_AND_ASSIGN(EnvMultiConf);
};

// Configuration loader that uses command line switches
class CmdMultiConf {
 public:
  // Thread safe GetInstance.
  static CmdMultiConf& GetInstance();

  // Loads configuraton value from command line switches in order:
  // * key
  // * uppercase(key)
  // * lowercase(key)
  basic::StatusOr<std::string> tryLoadString(
    const std::string& name
    , const std::string& configuration_group
    , const base::Value& option_settings);

 public:
  // id for debug purposes
  static constexpr char kId[] = "CmdMultiConf";

 private:
  CmdMultiConf();

 private:
  FRIEND_TEST_ALL_PREFIXES(MultiConfTest, SimpleTest);

  const base::CommandLine* command_line_;

  friend class base::NoDestructor<CmdMultiConf>;

  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);

  DISALLOW_COPY_AND_ASSIGN(CmdMultiConf);
};

// Wraps functions from any configuration loader
struct MultiConfLoader {
  using LoaderFunc
    = base::RepeatingCallback<
        basic::StatusOr<std::string>(
          const std::string& name
          , const std::string& configuration_group
          , const base::Value& option_settings)
      >;

  friend bool operator==(const MultiConfLoader& a, const MultiConfLoader& b) {
    return a.name == b.name;
  }

  friend bool operator<(const MultiConfLoader& a, const MultiConfLoader& b) {
    return a.name < b.name;
  }

  friend std::ostream& operator<<(std::ostream& out, const MultiConfLoader& i) {
    return out << i.name;
  }

  std::string name;
  LoaderFunc func;
};

STRONGLY_TYPED_BOOL(UseGlobalLoaders);

// Configuration option that can be read from file, environment vars, etc.
struct MultiConfOption
{
 public:
  MultiConfOption();

  MultiConfOption(
    const std::string& name
    , const base::Optional<std::string>& default_value
    , const std::initializer_list<MultiConfLoader>& loaders
    , const std::string& configuration_group
    , UseGlobalLoaders useGlobal = UseGlobalLoaders::kTrue
    , base::Value&& option_settings = base::Value{});

  friend bool operator<(const MultiConfOption& a, const MultiConfOption& b) {
    return formatConfigNameAndGroup(a.name, a.configuration_group)
           < formatConfigNameAndGroup(b.name, b.configuration_group);
  }

  friend bool operator==(const MultiConfOption& a, const MultiConfOption& b) {
    return formatConfigNameAndGroup(a.name, a.configuration_group)
           == formatConfigNameAndGroup(b.name, b.configuration_group);
  }

  friend std::ostream& operator<<(std::ostream& out, const MultiConfOption& i) {
    return out << formatConfigNameAndGroup(i.name, i.configuration_group);
  }

  MultiConfOption(const MultiConfOption& other)
    : name{other.name}
    , default_str{other.default_str}
    , loaders{other.loaders}
    , configuration_group{other.configuration_group}
    , useGlobalLoaders{other.useGlobalLoaders}
    , optionSettings{other.optionSettings.Clone()}
  {}

  MultiConfOption(MultiConfOption&& other)
    : name{RVALUE_CAST(other.name)}
    , default_str{RVALUE_CAST(other.default_str)}
    , loaders{RVALUE_CAST(other.loaders)}
    , configuration_group{RVALUE_CAST(other.configuration_group)}
    , useGlobalLoaders{RVALUE_CAST(other.useGlobalLoaders)}
    , optionSettings{RVALUE_CAST(other.optionSettings)}
  {}

  MultiConfOption& operator=(
    const MultiConfOption& other)
  {
    name = other.name;
    default_str = other.default_str;
    loaders = other.loaders;
    configuration_group = other.configuration_group;
    useGlobalLoaders = other.useGlobalLoaders;
    optionSettings = other.optionSettings.Clone();
    return *this;
  }

  MultiConfOption& operator=(
    MultiConfOption&& other)
  {
    name = RVALUE_CAST(other.name);
    default_str = RVALUE_CAST(other.default_str);
    loaders = RVALUE_CAST(other.loaders);
    configuration_group = RVALUE_CAST(other.configuration_group);
    useGlobalLoaders = RVALUE_CAST(other.useGlobalLoaders);
    optionSettings = RVALUE_CAST(other.optionSettings);
    return *this;
  }

  std::string name;
  base::Optional<std::string> default_str = base::nullopt;
  std::vector<MultiConfLoader> loaders;
  std::string configuration_group;
  UseGlobalLoaders useGlobalLoaders;
  base::Value optionSettings;
};

class MultiConf {
 public:
  class Observer {
   public:
    Observer();

    virtual ~Observer();

    /// \note will trigger only if configuration value loaded without errors
    virtual void onOptionReloaded(
      const MultiConfOption& option
      , const std::string& prev_value
      , const std::string& new_value)  = 0;

    /// \note will NOT trigger if `known_config_options_.empty()`.
    virtual void onCacheReloaded()  = 0;

    virtual std::string id() {
      return "MultiConf::Observer";
    }

   private:
    DISALLOW_COPY_AND_ASSIGN(Observer);
  };

  ~MultiConf();

  // Thread safe GetInstance.
  static MultiConf& GetInstance();

  // Add a non owning pointer
  void addObserver(
    MultiConf::Observer* observer);

  // Does nothing if the |observer| is
  // not in the list of known observers.
  void removeObserver(
    MultiConf::Observer* observer);

  void AssertObserversEmpty() {
    DCHECK(observers_);

    /// \note thread-safe, so skip `debug_thread_collision_warner_`
    observers_->AssertEmpty();
  }

  // may be called from `clearAndReload()` or `reloadOption()`
  void notifyCacheReloaded();

  // called if `reloadOption()` succeeded
  void notifyOptionReloaded(
    const MultiConfOption& option
    , const std::string& prev_value
    , const std::string& new_value);

  // USAGE
  //
  // /// \note will cache configuration values,
  // /// so use `clearAndReload` if you need to update configuration values.
  // CHECK_OK(basic::MultiConf::GetInstance().init())
  //   << "Wrong configuration.";
  // /// \note required to refresh configuration cache.
  // /// Do not use `RunUntilIdle` if you already started another `RunLoop`.
  // base::RunLoop().RunUntilIdle();
  //
  MUST_USE_RETURN_VALUE
  basic::Status init() {
    DCHECK_EQ(current_config_cache_.size(), 0);
    RETURN_WITH_MESSAGE_IF_NOT_OK(clearAndReload())
      << "Failed to initialize configuration";
    RETURN_OK();
  }

  MUST_USE_RETURN_VALUE
  bool isCacheEmpty() const NO_EXCEPTION {
    return current_config_cache_.empty();
  }

  void clearCache() NO_EXCEPTION {
    current_config_cache_.clear();
  }

  MUST_USE_RETURN_VALUE
  size_t countOptions() const NO_EXCEPTION {
    return known_config_options_.size();
  }

  MUST_USE_RETURN_VALUE
  bool hasOptions() const NO_EXCEPTION {
    return !known_config_options_.empty();
  }

  void clearOptions() NO_EXCEPTION {
    known_config_options_.clear();
  }

  // Adds configuration option to `known_config_options_`
  basic::Status addOption(const MultiConfOption& option);

  void addGlobalLoaders(
    const std::initializer_list<MultiConfLoader>& loaders);

  void removeGlobalLoaders(
    const std::initializer_list<MultiConfLoader>& loaders);

  bool hasGlobalLoaders(
    const std::initializer_list<MultiConfLoader>& loaders);

  /// \note Will reload cache even if nothing changed.
  /// \note Will do nothing if `known_config_options_.empty()`.
  // Updates config based on current content of config files, env. vars, etc.
  // Populates `current_config_cache_`
  //
  // USAGE
  //
  // CHECK_OK(basic::MultiConf::GetInstance().clearAndReload())
  //   << "Wrong configuration.";
  // /// \note required to refresh configuration cache.
  // /// Do not use `RunUntilIdle` if you already started another `RunLoop`.
  // base::RunLoop().RunUntilIdle();
  //
  basic::Status clearAndReload(
    // if your application requires all configuration values
    // to be valid or have valid defaults,
    // than set `clear_cache_on_error` to true
    bool clear_cache_on_error = true);

  // Finds key with provided name in `current_config_cache_`
  basic::StatusOr<std::string> getAsStringFromCache(const std::string& name
    , const std::string& configuration_group
    , bool allow_default_value = false);

  bool hasOptionWithName(const std::string& name
    , const std::string& configuration_group);

  // Populates `current_config_cache_`
  // Calls `reloadOption`
  /// \note Does not return error if configuration option has default value.
  basic::Status reloadOptionWithName(
    const std::string& name
    , const std::string& configuration_group
    // if want to reload multiple options in batches and
    // notify about change only once,
    // than set `notify_cache_reload_on_success` to true
    , bool notify_cache_reload_on_success = true
    // if your application requires all configuration values
    // to be valid or have valid defaults,
    // than set `clear_cache_on_error` to true
    , bool clear_cache_on_error = true);

  // can be used to get default value of registered option
  basic::StatusOr<MultiConfOption> findOptionWithName(
    const std::string& name
    , const std::string& configuration_group);

 private:
  MultiConf();

  // Calls each loader in `MultiConfOption` until it returns value.
  /// \note Ignores default value
  basic::StatusOr<std::string> loadAsStringWithoutDefaults(
    const MultiConfOption& option);

  // Populates `current_config_cache_`
  /// \note Does not return error if configuration option has default value.
  basic::Status reloadOption(
    const MultiConfOption& option
    , bool notify_cache_reload_on_success
    , bool clear_cache_on_error);

 private:
  friend class base::NoDestructor<MultiConf>;

  friend class MultiConf::Observer;

  /// \note ObserverListThreadSafe may be used from multiple threads
  const scoped_refptr<
      ::base::ObserverListThreadSafe<MultiConf::Observer>
    > observers_;

  std::set<MultiConfOption> known_config_options_;

  std::map<std::string, std::string> current_config_cache_;

  std::vector<MultiConfLoader> global_loaders_;

  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);

  DISALLOW_COPY_AND_ASSIGN(MultiConf);
};

template<typename T>
class MultiConfObserver : public MultiConf::Observer {
 public:
  MultiConfObserver(const std::string& target_name
    , const std::string& default_value
    , const std::string& configuration_group)
    : target_name_(target_name)
    , target_configuration_group_(configuration_group)
    /// \note `ConsumeValueOrDie` can CRASH without error,
    /// so provide error text using `dcheckCanParseAndReturnOk`,
    /// but only in DEBUG builds.
    , error_status_(dcheckCanParseAndReturnOk(default_value))
    /// \note Will CRASH without error text
    /// if default configuration value is not valid!
    , cached_value_{basic::rvalue_cast(parseOptionAs<T>(default_value).ConsumeValueOrDie())}
  {}

  ~MultiConfObserver() override {}

  MultiConfObserver(const MultiConfObserver& other)
    : target_name_{other.target_name_}
    , target_configuration_group_{other.target_configuration_group_}
    , cached_value_{other.cached_value_}
    , error_status_{other.error_status_}
  {}

  MultiConfObserver(MultiConfObserver&& other)
    : target_name_{RVALUE_CAST(other.target_name_)}
    , target_configuration_group_{RVALUE_CAST(other.target_configuration_group_)}
    , cached_value_{RVALUE_CAST(other.cached_value_)}
    , error_status_{RVALUE_CAST(other.error_status_)}
  {}

  MultiConfObserver& operator=(
    const MultiConfObserver& other)
  {
    target_name_ = other.target_name_;
    target_configuration_group_ = other.target_configuration_group_;
    cached_value_ = other.cached_value_;
    error_status_ = other.error_status_;
    return *this;
  }

  MultiConfObserver& operator=(
    MultiConfObserver&& other)
  {
    target_name_ = RVALUE_CAST(other.target_name_);
    target_configuration_group_ = RVALUE_CAST(other.target_configuration_group_);
    cached_value_ = RVALUE_CAST(other.cached_value_);
    error_status_ = RVALUE_CAST(other.error_status_);
    return *this;
  }

  void onOptionReloaded(
    const MultiConfOption& option
    , const std::string& prev_value
    , const std::string& new_value) override
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    error_status_ = basic::OkStatus();

    if (option.name == target_name_
        && option.configuration_group == target_configuration_group_
        && prev_value != new_value)
    {
      basic::StatusOr<T> statusor = parseOptionAs<T>(new_value);
      if(statusor.ok()) {
        cached_value_ = basic::rvalue_cast(statusor.ConsumeValueOrDie());
      } else {
        error_status_ = statusor.status();
      }
    }
  }

  void onCacheReloaded() override {
    error_status_ = basic::OkStatus();

    basic::StatusOr<std::string> cache_statusor
      = basic::MultiConf::GetInstance().getAsStringFromCache(
          target_name_
          , target_configuration_group_
          , true // allow default value
        );
    if(cache_statusor.ok()) {
      basic::StatusOr<T> new_value_statusor
        = parseOptionAs<T>(cache_statusor.ConsumeValueOrDie());
      if(new_value_statusor.ok()) {
        T new_value = new_value_statusor.ConsumeValueOrDie();
        if (cached_value_ != new_value) {
          cached_value_ = basic::rvalue_cast(new_value);
        }
      } else {
        // failed to parse new value
        error_status_ = new_value_statusor.status();
      }
    } else {
      // failed to find value in cache or use default value
      error_status_ = cache_statusor.status();
    }
  }

  std::string id() override {
    return "MultiConfObserver";
  }

  basic::Status error_status() const NO_EXCEPTION {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return error_status_;
  }

  std::string target_name() const NO_EXCEPTION {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return target_name_;
  }

  std::string target_configuration_group() const NO_EXCEPTION {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    return target_configuration_group_;
  }

  /// \note `GetValue()` requires `error_status().ok()`
  T GetValue(
    const base::Location& location = base::Location::Current()) const NO_EXCEPTION
  {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    CHECK(error_status_.ok())
      << location.ToString();
    return cached_value_;
  }

 private:
  static basic::Status dcheckCanParseAndReturnOk(const std::string& default_value) NO_EXCEPTION
  {
#if DCHECK_IS_ON()
    basic::StatusOr<T> statusor = parseOptionAs<T>(default_value);
    CHECK(statusor.ok())
      << "Default configuration value expected to be valid."
      << " Can not parse to "
      << type_name<T>()
      << " value: "
      << default_value;
#endif // DCHECK_IS_ON
    RETURN_OK();
  }

 private:
  std::string target_name_;

  std::string target_configuration_group_;

  basic::Status error_status_;

  T cached_value_;

  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);
};

template<typename T>
class ScopedAddConfObserver {
 public:
  using AddObserverCb
    = base::RepeatingCallback<void(MultiConf::Observer*)>;

  using DelObserverCb
    = base::RepeatingCallback<void(MultiConf::Observer*)>;

  ScopedAddConfObserver(T* ptr
    , AddObserverCb addObserverCb
    , DelObserverCb delObserverCb)
    : ptr_(ptr)
    , addObserverCb_(addObserverCb)
    , delObserverCb_(delObserverCb)
  {
    DCHECK(addObserverCb_);
    addObserverCb_.Run(ptr_);
  }

  ~ScopedAddConfObserver()
  {
    DCHECK(delObserverCb_);
    delObserverCb_.Run(ptr_);
  }

private:
  T* ptr_;

  SCOPED_UNOWNED_PTR_CHECKER(ptr_);

  AddObserverCb addObserverCb_;
  DelObserverCb delObserverCb_;

  DISALLOW_COPY_AND_ASSIGN(ScopedAddConfObserver);
};

TYPED_ENUM(CheckOptionPolicy, int, (kCheckAddedNew)(kCheckExists)(kIgnoreCheck))

// Used by `MULTICONF_*` macros to both create configuration option
// and register observer using single var,
// so you will be able to write code: `static MULTICONF_String(...)`.
/// \note Automatically adds configuration option
/// \note Automatically adds and removes itself from observer list
template<typename T>
class MultiConfWrapper {
 public:
  using MCO
    = MultiConfObserver<T>;

  using SAO
    = ScopedAddConfObserver<MCO>;

  template <typename... Args>
  MultiConfWrapper(CheckOptionPolicy checkOptionPolicy
    , const std::string& target_name
    , const std::string& default_value
    , const std::initializer_list<MultiConfLoader>& loaders
    , const std::string& configuration_group
    , Args... args)
    : mco_{std::make_shared<MCO>(target_name, default_value, configuration_group)}
    , sao_{std::make_shared<SAO>(
        mco_.get()
        , base::BindRepeating(
            &basic::MultiConf::addObserver
            , base::Unretained(&basic::MultiConf::GetInstance()))
        , base::BindRepeating(
            &basic::MultiConf::removeObserver
            , base::Unretained(&basic::MultiConf::GetInstance()))
      )}
    , target_name_(target_name)
    , target_configuration_group_(configuration_group)
  {
    switch (checkOptionPolicy) {
      case CheckOptionPolicy::kCheckExists: {
        CHECK(basic::MultiConf::GetInstance().hasOptionWithName(target_name, configuration_group));
        break;
      }
      case CheckOptionPolicy::kCheckAddedNew: {
        CHECK_GT(loaders.size(), 0)
          << "No configuration loaders provided for option:"
          << target_name;
        auto result
          = basic::MultiConf::GetInstance().addOption(basic::MultiConfOption{
              target_name
              , default_value
              , loaders
              , target_configuration_group_
              , FORWARD(args)...
            });
        if(checkOptionPolicy == CheckOptionPolicy::kCheckAddedNew) {
          CHECK_OK(result);
        } else {
          ignore_result(result);
        }
        break;
      }
      case CheckOptionPolicy::kIgnoreCheck: {
        break;
      }
      default: {
        FATAL_INVALID_ENUM_VALUE(CheckOptionPolicy, checkOptionPolicy);
      }
    }
  }

  T GetValue(
    const base::Location& location = base::Location::Current()) const NO_EXCEPTION
  {
    return mco_->GetValue();
  }

  basic::Status error_status() const NO_EXCEPTION {
    return mco_->error_status();
  }

  MultiConfWrapper(const MultiConfWrapper& other)
    : mco_{other.mco_}
    , sao_{other.sao_}
    , target_name_{other.target_name_}
    , target_configuration_group_{other.target_configuration_group_}
  {
  }

  MultiConfWrapper(MultiConfWrapper&& other)
    : mco_{RVALUE_CAST(other.mco_)}
    , sao_{RVALUE_CAST(other.sao_)}
    , target_name_{RVALUE_CAST(other.target_name_)}
    , target_configuration_group_{RVALUE_CAST(other.target_configuration_group_)}
  {
  }

  MultiConfWrapper& operator=(
    const MultiConfWrapper& other)
  {
    mco_ = other.mco_;
    sao_ = other.sao_;
    target_name_ = other.target_name_;
    target_configuration_group_ = other.target_configuration_group_;
    return *this;
  }

  MultiConfWrapper& operator=(
    MultiConfWrapper&& other)
  {
    mco_ = RVALUE_CAST(other.mco_);
    sao_ = RVALUE_CAST(other.sao_);
    target_name_ = RVALUE_CAST(other.target_name_);
    target_configuration_group_ = RVALUE_CAST(other.target_configuration_group_);
    return *this;
  }

  // USAGE
  //
  // ::base::FilePath file_exe_{};
  //
  // if (!base::PathService::Get(base::FILE_EXE, &file_exe_)) {
  //   NOTREACHED();
  //   // stop app execution with EXIT_FAILURE
  //   return
  //     false;
  // }
  //
  // ::base::FilePath base_exe_name_ = file_exe_.BaseName().RemoveExtension();
  //
  // MULTICONF_String(log_file_conf
  //   , /* default value */ ""
  //   , BUILTIN_MULTICONF_LOADERS
  //   , /* name of configuration group */ base_exe_name_);
  //
  // {
  //   const std::string& log_file = log_file_conf.GetValue();
  //   if (log_file.empty()) {
  //     LOG(WARNING)
  //       << "You can set path to log file using configuration option: "
  //       << log_file_conf.optionFormatted();
  //   }
  //   ::basic::initLogging(
  //     log_file
  //   );
  // }
  std::string optionFormatted() {
    return formatConfigNameAndGroup(target_name(), target_configuration_group());
  }

  std::string target_name() const NO_EXCEPTION {
    return target_name_;
  }

  std::string target_configuration_group() const NO_EXCEPTION {
    return target_configuration_group_;
  }

 private:
  // Multiple wrappers can have shared MCO (MultiConfObserver<T>)
  // and shared SAO (ScopedAddConfObserver)
  std::shared_ptr<MCO> mco_;
  std::shared_ptr<SAO> sao_;
  std::string target_name_;
  std::string target_configuration_group_;

};

} // namespace basic
