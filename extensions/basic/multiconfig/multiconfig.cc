#include "basic/multiconfig/multiconfig.h" // IWYU pragma: associated
#include <basic/macros.h>
#include <basic/stl_util.h>
#include <basic/logging.h>

#include <base/environment.h>
#include <base/location.h>
#include <base/strings/string_util.h>
#include <base/strings/stringprintf.h>
#include <base/stl_util.h>
#include <base/bind.h>
#include <base/values.h>
#include <base/files/file_util.h>
#include <base/json/json_string_value_serializer.h>
#include <base/json/json_reader.h>
#include <base/threading/scoped_blocking_call.h>
#include <base/command_line.h>

#include <algorithm>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>

namespace basic {

namespace internal {

static const size_t kMaxDebugLogItemSize = 9999;

basic::StatusOr<base::Value> parseJSONData(
  const std::string& json_data)
{
  // This could be really slow.
  base::ScopedBlockingCall scoped_blocking_call(
    FROM_HERE, base::BlockingType::MAY_BLOCK);

  base::JSONReader::ValueWithError value_with_error =
    base::JSONReader::ReadAndReturnValueWithError(
      json_data
      , base::JSON_PARSE_RFC);

  if (!value_with_error.value) {
    RETURN_ERROR().with_dvlog(99)
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
    RETURN_ERROR().with_dvlog(99)
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

} // namespace internal

std::string formatConfigNameAndGroup(
  const std::string&name, const std::string group)
{
  return (name + "_" + group);
  //return group.empty()
  //  ? name
  //  : (name + "_" + group);
}

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
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  UNREFERENCED_PARAMETER(option_settings);

  std::string key = formatConfigNameAndGroup(name, configuration_group);

  DCHECK(!key.empty());

  std::string result;

  if(env_->GetVar(key, &result))
  {
    return result;
  }

  if(env_->GetVar(base::ToUpperASCII(key), &result))
  {
    return result;
  }

  if(env_->GetVar(base::ToLowerASCII(key), &result))
  {
    return result;
  }

  RETURN_ERROR().with_dvlog(99)
    << "unable to find key in environment variables: "
    << key
    << " in loader "
    << kId;
}

CmdMultiConf::CmdMultiConf()
  : command_line_{base::CommandLine::ForCurrentProcess()}
{}

CmdMultiConf& CmdMultiConf::GetInstance() {
  // C++11 static local variable initialization is
  // thread-safe.
  static base::NoDestructor<CmdMultiConf> instance;
  return *instance;
}

basic::StatusOr<std::string> CmdMultiConf::tryLoadString(
  const std::string& name
  , const std::string& configuration_group
  , const base::Value& option_settings)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  UNREFERENCED_PARAMETER(option_settings);

  const std::string key
    = formatConfigNameAndGroup(name, configuration_group);

  DCHECK(!key.empty());

  /// \note command line switches will `DCHECK` if switch is not lowercase.
  const std::string key_lower = base::ToLowerASCII(key);

  if(command_line_->HasSwitch(key_lower))
  {
    return command_line_->GetSwitchValueASCII(key_lower);
  }

  RETURN_ERROR().with_dvlog(99)
    << "unable to find key in command-line switches: "
    << key_lower
    << " in loader "
    << kId;
}

JsonMultiConf::JsonMultiConf()
{}

JsonMultiConf& JsonMultiConf::GetInstance() {
  // C++11 static local variable initialization is
  // thread-safe.
  static base::NoDestructor<JsonMultiConf> instance;
  return *instance;
}

basic::Status JsonMultiConf::clearAndParseFromFilePath(
  const base::FilePath& file_path)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  std::string json_data;

  // Failure to read the file is ignored
  // as |json_data| will be the empty string
  // and the remainder of this object should still be
  // initialized as best as possible.
  if (!base::PathExists(file_path))
  {
    RETURN_ERROR().with_dvlog(99)
      << "File does not exist: "
      << file_path.value()
      << " in loader "
      << kId;

    /// \note init from empty |json_data| string
  } else if (
      base::PathExists(file_path)
      && !base::ReadFileToString(file_path, &json_data))
  {
    RETURN_ERROR().with_dvlog(99)
      << "Failed to read JSON from file: "
      << file_path.value()
      << " in loader "
      << kId;

    /// \note clearAndParseFromString will be called
    /// with empty |json_data| string
  }

  /// \note resets cache even in case of loading error
  cached_dictionary_.reset();

  RETURN_WITH_MESSAGE_IF_NOT_OK(clearAndParseFromString(json_data))
    << "Failed to parse JSON from file:"
    << file_path;

  RETURN_OK();
}

std::string JsonMultiConf::serializeCachedConfig() const
{
  if(!cached_dictionary_.has_value()) return "";
  // Serialize back the |cached_dictionary_|.
  std::string serialized_json;
  JSONStringValueSerializer str_serializer(&serialized_json);
  str_serializer.set_pretty_print(true);
  const bool serializeOk
    = str_serializer.Serialize(cached_dictionary_.value());
  DCHECK(serializeOk);
  return serialized_json;
}

basic::Status JsonMultiConf::clearAndParseFromString(
  const std::string& json_data)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  if (json_data.empty()) {
    RETURN_ERROR().with_dvlog(99)
      << "empty JSON"
      << " in loader "
      << kId;
  }

  /// \note resets cache even in case of loading error
  cached_dictionary_.reset();

  // will hold the nullptr in case of an error.
  CONSUME_OR_RETURN_WITH_MESSAGE(cached_dictionary_
    , internal::parseJSONData(json_data), std::string{"failed_to_parse_JSON_string"});

  RETURN_OK();
}

basic::StatusOr<std::string> JsonMultiConf::tryLoadString(
  const std::string& name
  , const std::string& configuration_group
  , const base::Value& option_settings)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  UNREFERENCED_PARAMETER(option_settings);

  std::string key = formatConfigNameAndGroup(name, configuration_group);

  DCHECK(!key.empty());

  if(!cached_dictionary_.has_value())
  {
    RETURN_ERROR().with_dvlog(99)
      << "json configuration not loaded"
      << key
      << " in loader "
      << kId;
  }

  DCHECK(cached_dictionary_.value().is_dict());
  if(!cached_dictionary_.value().is_dict())
  {
    RETURN_ERROR().with_dvlog(99)
      << "invalid json configuration for key: "
      << key
      << " in loader "
      << kId;
  }

  const std::string* foundValue
    = cached_dictionary_.value().FindStringKey(key);
  if(foundValue == nullptr)
  {
    RETURN_ERROR().with_dvlog(99)
      << "unable to find key in json configuration: "
      << key
      << " in loader "
      << kId;
  }

  return *foundValue;
}

MultiConfOption::MultiConfOption()
  : name()
  , default_str()
  , loaders()
  , configuration_group()
  , useGlobalLoaders(basic::UseGlobalLoaders::kFalse)
  , optionSettings()
{}

MultiConfOption::MultiConfOption(
  const std::string& key
  , const base::Optional<std::string>& default_value
  , const std::initializer_list<MultiConfLoader>& loaders
  , const std::string& configuration_group
  , ::basic::UseGlobalLoaders useGlobal
  , base::Value&& option_settings)
  : name(key)
  , default_str(default_value)
  , loaders(loaders)
  , configuration_group(configuration_group)
  , useGlobalLoaders(useGlobal)
  , optionSettings(basic::rvalue_cast(option_settings))
{}

MultiConf::Observer::Observer() = default;

MultiConf::Observer::~Observer() = default;

MultiConf::MultiConf()
  : observers_(new ::base::ObserverListThreadSafe<MultiConf::Observer>())
{}

MultiConf::~MultiConf() {
  AssertObserversEmpty();
}

void MultiConf::notifyOptionReloaded(
  const MultiConfOption& option
  , const std::string& prev_value
  , const std::string& new_value)
{
  DCHECK(observers_);

  /// \note thread-safe, so skip `debug_thread_collision_warner_`
  observers_->Notify(FROM_HERE
    , &MultiConf::Observer::onOptionReloaded
    , option
    , prev_value
    , new_value);
}

void MultiConf::notifyCacheReloaded()
{
  DCHECK(observers_);

  /// \note thread-safe, so skip `debug_thread_collision_warner_`
  observers_->Notify(FROM_HERE, &MultiConf::Observer::onCacheReloaded);
}

void MultiConf::addObserver(
  MultiConf::Observer* observer)
{
  DCHECK(observer);
  DCHECK(observers_);

  /// \note thread-safe, so skip `debug_thread_collision_warner_`
  observers_->AddObserver(observer);
}

void MultiConf::removeObserver(
  MultiConf::Observer* observer)
{
  DCHECK(observer);
  DCHECK(observers_);

  /// \note thread-safe, so skip `debug_thread_collision_warner_`
  observers_->RemoveObserver(observer);
}

MultiConf& MultiConf::GetInstance() {
  // C++11 static local variable initialization is
  // thread-safe.
  static base::NoDestructor<MultiConf> instance;
  return *instance;
}

void MultiConf::addGlobalLoaders(
  const std::initializer_list<MultiConfLoader>& loaders)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  CHECK_GT(loaders.size(), 0)
    << "No configuration loaders provided";

  std::vector<MultiConfLoader> tmp(loaders);

  // Move elements from src to dest.
  // src is left in undefined but safe-to-destruct state.
  global_loaders_.insert(
    global_loaders_.end(),
    std::make_move_iterator(tmp.begin()),
    std::make_move_iterator(tmp.end())
  );
}

void MultiConf::removeGlobalLoaders(
  const std::initializer_list<MultiConfLoader>& loaders)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  CHECK_GT(loaders.size(), 0)
    << "No configuration loaders provided";

  for(const MultiConfLoader& loader : loaders) {
    base::Erase(global_loaders_, loader);
  }
}


bool MultiConf::hasGlobalLoaders(
  const std::initializer_list<MultiConfLoader>& loaders)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  CHECK_GT(loaders.size(), 0)
    << "No configuration loaders provided";

  for(const MultiConfLoader& loader : loaders) {
    if(!basic::ContainsValue(global_loaders_, loader)) {
      return false;
    }
  }

  return true;
}

basic::Status MultiConf::addOption(const MultiConfOption& option)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  CHECK_GT(option.loaders.size(), 0)
    << "No configuration loaders provided for option:"
    << formatConfigNameAndGroup(option.name, option.configuration_group);

  auto [iter, is_newly_inserted] = known_config_options_.insert(option);
  RETURN_ERROR_IF(!is_newly_inserted)
    << "Failed to add configuration option twice: "
    << formatConfigNameAndGroup(option.name, option.configuration_group);
  DCHECK(iter != known_config_options_.end());
  RETURN_OK();
}

bool MultiConf::hasOptionWithName(const std::string& name
  , const std::string& configuration_group)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  // creates dummy option to find real option
  return known_config_options_.find(
    MultiConfOption{name, base::nullopt, {}, configuration_group}) != known_config_options_.end();
}

basic::Status MultiConf::reloadOptionWithName(
  const std::string& name
  , const std::string& configuration_group
  , bool notify_cache_reload_on_success
  , bool clear_cache_on_error)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  // creates dummy option to find real option
  auto it = known_config_options_.find(MultiConfOption{name, base::nullopt, {}, configuration_group});
  RETURN_ERROR_IF(it == known_config_options_.end())
    << "Failed to find configuration option: "
    << formatConfigNameAndGroup(name, configuration_group);

  RETURN_IF_NOT_OK(reloadOption(*it, notify_cache_reload_on_success, clear_cache_on_error));

  RETURN_OK();
}

basic::StatusOr<MultiConfOption> MultiConf::findOptionWithName(
  const std::string& name
  , const std::string& configuration_group)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  // creates dummy option to find real option
  auto it = known_config_options_.find(MultiConfOption{name, base::nullopt, {}, configuration_group});
  RETURN_ERROR_IF(it == known_config_options_.end())
    << "Failed to find configuration option: "
    << formatConfigNameAndGroup(name, configuration_group);

  return *it;
}

basic::Status MultiConf::clearAndReload(bool clear_cache_on_error)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  current_config_cache_.clear();

  if(known_config_options_.empty()) {
    LOG_EVERY_N_MS(WARNING, 100)
      << "No configuration options provided.";
  }

  /// \note loading order is not guaranteed to be same as user may want
  for(const MultiConfOption& option: known_config_options_) {
    /// \note Does not return error if configuration option has default value.
    RETURN_IF_NOT_OK(reloadOption(option
      // no need to call `notifyCacheReloaded` on success
      // because we will call it below anyway
      , false
      , clear_cache_on_error));
  }

  notifyCacheReloaded();

  RETURN_OK();
}

basic::Status MultiConf::reloadOption(
  const MultiConfOption& option
  , bool notify_cache_reload_on_success
  , bool clear_cache_on_error)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  std::string prev_value
    = basic::FindWithDefault(
        current_config_cache_
        , formatConfigNameAndGroup(option.name, option.configuration_group)
        , option.default_str.has_value() ? option.default_str.value() : "");

  DCHECK_GT(option.loaders.size(), 0)
    << "No configuration loaders provided for option:"
    << formatConfigNameAndGroup(option.name, option.configuration_group);

  basic::StatusOr<std::string> statusor = loadAsStringWithoutDefaults(option);
  if(statusor.ok()) {
    current_config_cache_[formatConfigNameAndGroup(option.name, option.configuration_group)]
      = statusor.ConsumeValueOrDie();
  } else {
    if(!option.default_str.has_value()) {
      if(notify_cache_reload_on_success) {
        notifyCacheReloaded();
      }
      if(clear_cache_on_error) {
        /// \note Resets whole cache in case of any error.
        /// We assume that each hard-coded configuration option is important
        /// and required to proceed.
        current_config_cache_.clear();
        // cache corrupted, need to notify about change anyway
        notifyCacheReloaded();
      }
      RETURN_ERROR().with_dvlog(99)
        << "Failed to load configuration value: "
        << formatConfigNameAndGroup(option.name, option.configuration_group);
    }
    // Configuration option uses default value
    current_config_cache_[formatConfigNameAndGroup(option.name, option.configuration_group)]
      = option.default_str.value();
  }

  notifyOptionReloaded(option
    , prev_value
    , current_config_cache_[formatConfigNameAndGroup(option.name, option.configuration_group)]);

  if(notify_cache_reload_on_success) {
    notifyCacheReloaded();
  }

  RETURN_OK();
}

basic::StatusOr<std::string> MultiConf::getAsStringFromCache(
  const std::string& name
  , const std::string& configuration_group
  , bool allow_default_value)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  std::string* result
    = basic::FindOrNull(current_config_cache_
      , formatConfigNameAndGroup(name, configuration_group));

  if (!result && !allow_default_value) {
    RETURN_ERROR().with_dvlog(99)
      << "Unable to find cached configuration value "
      << formatConfigNameAndGroup(name, configuration_group)
      << ". Maybe you forgot to reload configuration"
      << " or configuration is broken?";
  }

  if(!result && allow_default_value) {
    basic::StatusOr<MultiConfOption> statusor
      = findOptionWithName(name, configuration_group);
    RETURN_IF_NOT_OK(statusor.status());
    MultiConfOption option = basic::rvalue_cast(statusor.ConsumeValueOrDie());
    RETURN_ERROR_IF(!option.default_str.has_value());
    *result = option.default_str.value();
  }

  return *result;
}

basic::StatusOr<std::string> MultiConf::loadAsStringWithoutDefaults(
  const MultiConfOption& option)
{
  DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

  DCHECK_GT(option.loaders.size(), 0)
    << "No configuration loaders provided for option:"
    << formatConfigNameAndGroup(option.name, option.configuration_group);

  /// \note loading order is not guaranteed to be same as user may want
  for(const MultiConfLoader& loader : option.loaders) {
    basic::StatusOr<std::string> result
      = loader.func.Run(option.name, option.configuration_group, option.optionSettings);
    if (result.ok()) {
      // Valid configuration value loaded by loader
      return result;
    }
  }

  if(option.useGlobalLoaders) {
    for(const MultiConfLoader& loader : global_loaders_) {
      basic::StatusOr<std::string> result
        = loader.func.Run(option.name, option.configuration_group, option.optionSettings);
      if (result.ok()) {
        // Valid configuration value loaded by loader
        return result;
      }
    }
  }

  RETURN_ERROR().with_dvlog(99)
    << "Failed to find configuration value: "
    << formatConfigNameAndGroup(option.name, option.configuration_group)
    << " Count of used loaders: "
    << option.loaders.size();
}

} // namespace basic
