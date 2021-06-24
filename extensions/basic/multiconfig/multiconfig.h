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
#include <base/at_exit.h>
#include <base/synchronization/atomic_flag.h>

#include <string>
#include <ostream>

// Loads configuration from env. vars
#define ENV_MULTICONF_LOADER \
    basic::MultiConfLoader{ \
      ::basic::EnvMultiConf::kId \
      , base::BindRepeating( \
          &::basic::EnvMultiConf::tryLoadString \
          , base::Unretained(&::basic::EnvMultiConf::GetInstance())) \
    }

// Loads configuration from command-line
#define CMD_MULTICONF_LOADER \
    basic::MultiConfLoader{ \
      ::basic::CmdMultiConf::kId \
      , base::BindRepeating( \
          &::basic::CmdMultiConf::tryLoadString \
          , base::Unretained(&::basic::CmdMultiConf::GetInstance())) \
    }

// Loads configuration from json file
#define JSON_MULTICONF_LOADER \
    basic::MultiConfLoader{ \
      ::basic::JsonMultiConf::kId \
      , base::BindRepeating( \
          &::basic::JsonMultiConf::tryLoadString \
          , base::Unretained(&::basic::JsonMultiConf::GetInstance())) \
    }

// Does nothing, useful for tests
#define DUMMY_LOADER \
    basic::MultiConfLoader{ \
      ::basic::DummyLoader::kId \
      , base::BindRepeating(&::basic::DummyLoader::tryLoadString) \
    }

// Common configuration providers
#define BUILTIN_MULTICONF_LOADERS \
  { \
    CMD_MULTICONF_LOADER \
    , ENV_MULTICONF_LOADER \
    , JSON_MULTICONF_LOADER \
  }

#define DEFAULT_MULTICONF_GROUP "DEFAULT_MULTICONF_GROUP"

/// \note Each `MULTICONF_*` macro expected to create single variable,
/// so you will be able to write code: `static MULTICONF_String(...)`.
///
/// \note You can not create same option `my_key` using
/// `MULTICONF_String(my_key, "", MY_LOADERS);`
/// multiple times (even in different files or plugins).
/// Use multiple configuration groups to avoid collision like so:
/// `MULTICONF_String(my_key, "", MY_LOADERS, CONFIG_GROUP_A);`
/// `MULTICONF_String(my_key, "", MY_LOADERS, CONFIG_GROUP_B);`
//
// USAGE
//
// MULTICONF_type(float, my_conf_key, "1.12", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
//
#define MULTICONF_type(TYPE, KEY_NAME, DEFAULT_STR, ...) \
  basic::MultiConfWrapper<TYPE> KEY_NAME \
    {basic::CheckOptionPolicy::kCheckAddedNew, STRINGIFY(KEY_NAME) \
      , DEFAULT_STR \
      , /* configuration group, etc. */ __VA_ARGS__}

// `MULTICONF_type` that uses default loaders and group
#define MULTICONF(type, KEY_NAME, DEFAULT_STR, ...) \
  MULTICONF_type(type, KEY_NAME, DEFAULT_STR, BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP, __VA_ARGS__)

// USAGE
//
// MULTICONF_String(my_conf_key, "abcd", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
//
#define MULTICONF_String(KEY_NAME, DEFAULT_STR, ...) \
  MULTICONF_type(std::string, KEY_NAME, DEFAULT_STR, __VA_ARGS__)

// USAGE
//
// MULTICONF_Bool(my_conf_key, "true", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
// MULTICONF_Bool(my_conf_key, "True", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
// MULTICONF_Bool(my_conf_key, "TRUE", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
// MULTICONF_Bool(my_conf_key, "1", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
//
#define MULTICONF_Bool(...) \
  MULTICONF_type(bool, __VA_ARGS__)

// USAGE
//
// MULTICONF_Int(my_conf_key, "-12345", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
//
#define MULTICONF_Int(...) \
  MULTICONF_type(int, __VA_ARGS__)

// USAGE
//
// MULTICONF_Uint(my_conf_key, "12345", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
//
#define MULTICONF_Uint(...) \
  MULTICONF_type(unsigned, __VA_ARGS__)

// USAGE
//
// MULTICONF_Int64(my_conf_key, "-12345", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
//
#define MULTICONF_Int64(...) \
  MULTICONF_type(int64_t, __VA_ARGS__)

// USAGE
//
// MULTICONF_Int32(my_conf_key, "-12345", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
//
#define MULTICONF_Int32(...) \
  MULTICONF_type(int32_t, __VA_ARGS__)

// USAGE
//
// MULTICONF_Uint32(my_conf_key, "12345", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
//
#define MULTICONF_Uint32(...) \
  MULTICONF_type(uint32_t, __VA_ARGS__)

// USAGE
//
// MULTICONF_Uint64(my_conf_key, "12345", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
//
#define MULTICONF_Uint64(...) \
  MULTICONF_type(uint64_t, __VA_ARGS__)

// USAGE
//
// MULTICONF_SizeT(my_conf_key, "12345", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
//
#define MULTICONF_SizeT(...) \
  MULTICONF_type(size_t, __VA_ARGS__)

// USAGE
//
// MULTICONF_Double(my_conf_key, "1.12", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
//
#define MULTICONF_Double(...) \
  MULTICONF_type(double, __VA_ARGS__)

// USAGE
//
// MULTICONF_Float(my_conf_key, "1.12", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
//
#define MULTICONF_Float(...) \
  MULTICONF_type(float, __VA_ARGS__)

// MOTIVATION
//
// Single `MULTICONF_type` can not be used concurrently from multiple threads.
// You can create per-thread `DUPLICATE_Observer` to overcome that issue.
// Under the hood it will copy shared pointers to `observer_and_cache_` and  `observer_lifetime_`.
// I.e. you can use multiple `MULTICONF_type` objects to access cached values
// of single configuration option from multiple threads.
//
// USAGE
//
// MULTICONF_Float(my_conf_key, "1.12", BUILTIN_MULTICONF_LOADERS, DEFAULT_MULTICONF_GROUP);
// // Observe existing variable on multiple threads
// DUPLICATE_Observer(my_conf_key_observer_thread_1, my_namespace::my_conf_key);
// DUPLICATE_Observer(my_conf_key_observer_thread_2, my_namespace::my_conf_key);
// DUPLICATE_Observer(my_conf_key_observer_thread_3, my_namespace::my_conf_key);
//
/// \note `KEY_NAME` expected to be already existing variable
/// of type `MultiConfWrapper<...>` i.e. no need to call `addOption`.
//
/// \note We copy `MultiConfWrapper` into new variable.
/// That must copy cached value and register newly created observer
#define DUPLICATE_Observer(VAR_NAME, KEY_NAME) \
  auto VAR_NAME = KEY_NAME.duplicate()

/// \note kCheckExists - we do not create new config option,
/// just use existing one
#define MULTICONF_Observer(TYPE, KEY_NAME, ...) \
  basic::MultiConfWrapper<TYPE> KEY_NAME \
    {basic::CheckOptionPolicy::kCheckExists, STRINGIFY(KEY_NAME) \
      , /* default value not used */ "" \
      , /* loaders not used */ std::initializer_list<basic::MultiConfLoader>{} \
      , /* configuration group, etc. */ __VA_ARGS__}

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
// Each conf. option can use both custom and global configuration providers.
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

    // For debug purposes
    virtual std::string id() const {
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

  // Can be used to detect changes in configuration.
  // May be called from `resetAndReload()` or `reloadOption()`
  void notifyCacheReloaded();

  // Can be used to detect changes in configuration.
  // Called if `reloadOption()` succeeded.
  void notifyOptionReloaded(
    const MultiConfOption& option
    , const std::string& prev_value
    , const std::string& new_value);

  // USAGE
  //
  // /// \note will cache configuration values,
  // /// so use `resetAndReload` if you need to update configuration values.
  // CHECK_OK(basic::MultiConf::GetInstance().init())
  //   << "Wrong configuration.";
  // /// \note required to refresh configuration cache.
  // /// Do not use `RunUntilIdle` if you already started another `RunLoop`.
  // base::RunLoop().RunUntilIdle();
  //
  MUST_USE_RETURN_VALUE
  basic::Status init() {
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);
    DCHECK_EQ(current_config_cache_.size(), 0);
    RETURN_WITH_MESSAGE_IF_NOT_OK(resetAndReload())
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
  // CHECK_OK(basic::MultiConf::GetInstance().resetAndReload())
  //   << "Wrong configuration.";
  // /// \note required to refresh configuration cache.
  // /// Do not use `RunUntilIdle` if you already started another `RunLoop`.
  // base::RunLoop().RunUntilIdle();
  //
  basic::Status resetAndReload(
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
  /// \note Does not return error if configuration option has default value
  /// i.e. parsing errors will load to defaults.
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
  /// \note Ignores default value.
  /// \note Does not read or write cache.
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
class MultiConfWrapper;

// Used to:
// 1. Reload cached value for some configuration option.
// 2. Store cached value.
// 3. Get cached value.
template<typename T>
class ConfOptionObserverAndCache : public MultiConf::Observer {
 public:
  ConfOptionObserverAndCache(const std::string& target_name
    , const std::string& default_value
    , const std::string& configuration_group)
    : target_name_(target_name)
    , target_configuration_group_(configuration_group)
    /// \note `ConsumeValueOrDie` can CRASH without error,
    /// so provide error text using `debugCheckValidStringOption`,
    /// but only in DEBUG builds.
    , error_status_(debugCheckValidStringOption(default_value))
    /// \note Will CRASH without error text
    /// if default configuration value is not valid!
    , cached_value_{basic::rvalue_cast(parseOptionAs<T>(default_value).ConsumeValueOrDie())}
  {}

  ~ConfOptionObserverAndCache() override {}

  ConfOptionObserverAndCache(const ConfOptionObserverAndCache& other)
    : target_name_{other.target_name_}
    , target_configuration_group_{other.target_configuration_group_}
    , cached_value_{other.cached_value_}
    , error_status_{other.error_status_}
  {}

  ConfOptionObserverAndCache(ConfOptionObserverAndCache&& other)
    : target_name_{RVALUE_CAST(other.target_name_)}
    , target_configuration_group_{RVALUE_CAST(other.target_configuration_group_)}
    , cached_value_{RVALUE_CAST(other.cached_value_)}
    , error_status_{RVALUE_CAST(other.error_status_)}
  {}

  /// \note Do not forget to register newly created observer somehow
  /// (or prolong observer registration in case of shared pointers).
  ConfOptionObserverAndCache& operator=(
    const ConfOptionObserverAndCache& other)
  {
    target_name_ = other.target_name_;
    target_configuration_group_ = other.target_configuration_group_;
    cached_value_ = other.cached_value_;
    error_status_ = other.error_status_;
    return *this;
  }

  ConfOptionObserverAndCache& operator=(
    ConfOptionObserverAndCache&& other)
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
    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

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

  // For debug purposes
  std::string id() const override {
    return "ConfOptionObserverAndCache";
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
  /// \note Will crash in debug build if option can not be parsed from string.
  static basic::Status debugCheckValidStringOption(const std::string& default_value) NO_EXCEPTION
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

 protected:
  friend class MultiConfWrapper<T>;

  std::string target_name_;

  std::string target_configuration_group_;

  // Use to check if `cached_value_` is valid.
  // For example, use `error_status_` to check if:
  // * failed to parse value
  // * failed to find value in cache or use default value
  // * etc.
  basic::Status error_status_;

  T cached_value_;

  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);
};

TYPED_ENUM(ConfObserverLifetime, int, (kScoped)(kAtExit))

// Decides (based on `ConfObserverLifetime`)
// when to register and unregister `Observer` pointer.
template<typename T>
class ConfObserverLifetimeHelper {
 public:
  using AddObserverCb
    = base::OnceCallback<void(MultiConf::Observer*)>;

  using DelObserverCb
    = base::OnceCallback<void(MultiConf::Observer*)>;

  ConfObserverLifetimeHelper(T* ptr
    , ConfObserverLifetime lifetime = ConfObserverLifetime::kScoped
    , AddObserverCb addObserverCb
      = base::BindOnce(
          &basic::MultiConf::addObserver
          , base::Unretained(&basic::MultiConf::GetInstance()))
    , DelObserverCb delObserverCb
        = base::BindOnce(
            &basic::MultiConf::removeObserver
            , base::Unretained(&basic::MultiConf::GetInstance())))
    : ptr_(ptr)
    , lifetime_(lifetime)
    , addObserverCb_(std::move(addObserverCb))
    , delObserverCb_(std::move(delObserverCb))
  {
    DCHECK(addObserverCb_);
    std::move(addObserverCb_).Run(ptr_);
    switch(lifetime_) {
      case ConfObserverLifetime::kScoped: {
        // skip
        break;
      }
      case ConfObserverLifetime::kAtExit: {
        base::AtExitManager::RegisterTask(createDeletionCallback());
        break;
      }
      default: {
        FATAL_INVALID_ENUM_VALUE(ConfObserverLifetime, lifetime_);
      }
    }
  }

  // Resets `ptr_` to avoid calling `createDeletionCallback()` multiple times.
  base::OnceCallback<void()> createDeletionCallback() {
    DCHECK(ptr_);
    DCHECK(delObserverCb_);
    auto cb = base::BindOnce([](DelObserverCb&& delCb, T* ptr){
      DCHECK(delCb);
      DCHECK(ptr);
      std::move(delCb).Run(ptr);
    }, std::move(delObserverCb_), base::Unretained(ptr_));
    ptr_ = nullptr;
    return cb;
  }

  ~ConfObserverLifetimeHelper()
  {
    switch(lifetime_) {
      case ConfObserverLifetime::kScoped: {
        createDeletionCallback().Run();
        break;
      }
      case ConfObserverLifetime::kAtExit: {
        // skip
        break;
      }
      default: {
        FATAL_INVALID_ENUM_VALUE(ConfObserverLifetime, lifetime_);
      }
    }

    // `createDeletionCallback()` must be called at this point,
    // so `ptr_` must be reset
    DCHECK(!ptr_);
  }

private:
  T* ptr_{nullptr};

  ConfObserverLifetime lifetime_;

  SCOPED_UNOWNED_PTR_CHECKER(ptr_);

  AddObserverCb addObserverCb_;
  DelObserverCb delObserverCb_;

  DISALLOW_COPY_AND_ASSIGN(ConfObserverLifetimeHelper);
};

// kCheckAddedNew - Creates new option. Option must NOT be created before.
// kCheckExists - Checks that some option exists.
// kIgnoreCheck - Does no checks at all.
TYPED_ENUM(CheckOptionPolicy, int, (kCheckAddedNew)(kCheckExists)(kIgnoreCheck))

// Used by `MULTICONF_*` macros to both create configuration option
// and register observer using single var,
// so you will be able to write code: `static MULTICONF_String(...)`.
/// \note Automatically adds configuration option
/// \note Automatically adds and removes itself from observer list
template<typename T>
class MultiConfWrapper {
 public:
  using ObserverAndCache
    = ConfOptionObserverAndCache<T>;

  using ObserverLifetime
    = ConfObserverLifetimeHelper<ObserverAndCache>;

  template <typename... Args>
  MultiConfWrapper(CheckOptionPolicy checkOptionPolicy
    , const std::string& target_name
    , const std::string& default_value
    , const std::initializer_list<MultiConfLoader>& loaders
    , const std::string& configuration_group
    , Args... args)
    : observer_and_cache_{std::make_shared<ObserverAndCache>(
        target_name, default_value, configuration_group)}
    , observer_lifetime_{std::make_shared<ObserverLifetime>(
        observer_and_cache_.get())}
    , target_name_(target_name)
    , default_value_(default_value)
    , target_configuration_group_(configuration_group)
  {
    switch (checkOptionPolicy) {
      case CheckOptionPolicy::kCheckExists: {
        DCHECK(default_value_.empty()); // default value not used
        DCHECK(!loaders.size()); // loaders not used
        CHECK(basic::MultiConf::GetInstance().hasOptionWithName(
          target_name, configuration_group));
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
        DCHECK(default_value_.empty()); // default value not used
        DCHECK(!loaders.size()); // loaders not used
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
    return observer_and_cache_->GetValue();
  }

  basic::Status error_status() const NO_EXCEPTION {
    return observer_and_cache_->error_status();
  }

  /// \note for thread-safety purposes we want to create
  /// separate `observer_lifetime_` and `observer_and_cache_`
  /// i.e. will not copy shared pointers
  MultiConfWrapper duplicate() {
    auto conf = MultiConfWrapper{
      /// \note kCheckExists - we do not create new config option,
      /// just use existing one
      CheckOptionPolicy::kCheckExists
      , target_name_
      , /* default value not used */ ""
      , /* loaders not used */ std::initializer_list<MultiConfLoader>{}
      , target_configuration_group_};

    /// \note separate object
    DCHECK(conf.observer_and_cache_ != observer_and_cache_);

    conf.observer_and_cache_->target_name_
      = observer_and_cache_->target_name_;

    conf.observer_and_cache_->target_configuration_group_
       = observer_and_cache_->target_configuration_group_;

    conf.observer_and_cache_->error_status_
       = observer_and_cache_->error_status_;

    conf.observer_and_cache_->cached_value_
       = observer_and_cache_->cached_value_;

    /// \note separate object
    DCHECK(conf.observer_lifetime_ != observer_lifetime_);

    conf.target_name_ = target_name_;
    conf.default_value_ = default_value_;
    conf.target_configuration_group_ = target_configuration_group_;

    return conf;
  }

  MultiConfWrapper(const MultiConfWrapper& other)
    : observer_and_cache_{other.observer_and_cache_}
    , observer_lifetime_{other.observer_lifetime_}
    , target_name_{other.target_name_}
    , default_value_{other.default_value_}
    , target_configuration_group_{other.target_configuration_group_}
  {
    *this = other;
  }

  MultiConfWrapper(MultiConfWrapper&& other)
    : observer_and_cache_{RVALUE_CAST(other.observer_and_cache_)}
    , observer_lifetime_{RVALUE_CAST(other.observer_lifetime_)}
    , target_name_{RVALUE_CAST(other.target_name_)}
    , default_value_{RVALUE_CAST(other.default_value_)}
    , target_configuration_group_{RVALUE_CAST(other.target_configuration_group_)}
  {
  }

  /// \note We copy shared pointer to `observer_and_cache_` and  `observer_lifetime_`,
  /// so cached in `observer_and_cache_` value will remain same
  /// and observer will be kept registered by `observer_lifetime_`.
  MultiConfWrapper& operator=(
    const MultiConfWrapper& other)
  {
    observer_and_cache_ = other.observer_and_cache_;
    observer_lifetime_ = other.observer_lifetime_;
    target_name_ = other.target_name_;
    default_value_ = other.default_value_;
    target_configuration_group_ = other.target_configuration_group_;
    return *this;
  }

  MultiConfWrapper& operator=(
    MultiConfWrapper&& other)
  {
    observer_and_cache_ = RVALUE_CAST(other.observer_and_cache_);
    observer_lifetime_ = RVALUE_CAST(other.observer_lifetime_);
    target_name_ = RVALUE_CAST(other.target_name_);
    default_value_ = RVALUE_CAST(other.default_value_);
    target_configuration_group_ = RVALUE_CAST(other.target_configuration_group_);
    return *this;
  }

  // optionFormatted() prints to string informatin about configuration option.
  //
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

  std::string default_value() const NO_EXCEPTION {
    return default_value;
  }

  std::string target_configuration_group() const NO_EXCEPTION {
    return target_configuration_group_;
  }

 private:
  // Multiple wrappers can have shared ConfOptionObserverAndCache<T>
  // and shared ConfObserverLifetimeHelper
  std::shared_ptr<ObserverAndCache> observer_and_cache_;
  std::shared_ptr<ObserverLifetime> observer_lifetime_;
  std::string target_name_;
  std::string default_value_;
  std::string target_configuration_group_;
};

} // namespace basic
