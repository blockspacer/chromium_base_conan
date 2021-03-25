#include "basic/multiconfig/multiconfig.h"
#include "basic/promise/post_promise.h"
#include "basic/promise/post_task_executor.h"
#include "basic/promise/do_nothing_promise.h"
#include "basic/promise/abstract_promise.h"
#include "basic/promise/helpers.h"
#include "basic/rvalue_cast.h"
#include "basic/strings/substitute.h"

#include "base/test/gtest_util.h"
#include "base/test/test_mock_time_task_runner.h"
#include "base/test/task_environment.h"
#include "base/location.h"
#include "base/bind.h"
#include "base/run_loop.h"
#include "base/threading/thread.h"
#include "base/task_runner.h"
#include "base/strings/string_util.h"
#include "base/test/scoped_environment_variable_override.h"
#include "base/environment.h"
#include "base/run_loop.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace basic {

constexpr char kMustReturnStr[] = "MustReturnStr";
constexpr char kMustReturnStrResult[] = "kMustReturnStrResult";
constexpr char kDefaultTestGroup[] = "test_group_1";
constexpr char kUnknownKey[] = "unknown_key";
constexpr char kDefaultKey[] = "default_key";
constexpr char kTestKeyA[] = "test_key_a";
constexpr char kTestKeyB[] = "test_key_b";
constexpr char kTestKeyC[] = "test_key_c";
constexpr char kTestKeyD[] = "test_key_d";
constexpr char kTestKeyF[] = "test_key_f";
constexpr char kResultForDefaultKey[] = "result_for_default_key";
constexpr char kResultForTestKeyA[] = "result_for_test_key_a";
constexpr char kResultForTestKeyB[] = "result_for_test_key_b";
constexpr char kResultForTestKeyC[] = "result_for_test_key_c";
constexpr char kResultForTestKeyD[] = "result_for_test_key_d";
constexpr char kResultForTestKeyF[] = "result_for_test_key_f";

static void assertClearedJsonConfEquals(
  const std::string& json_data)
{
  ASSERT_OK(JsonMultiConf::GetInstance().clearAndParseFromString(json_data));

  std::string serialized
    = JsonMultiConf::GetInstance().serializeCachedConfig();

  std::string clean_serialized;
  ASSERT_TRUE(base::ReplaceChars(serialized, " \n\r",
                             "", &clean_serialized));

  std::string clean_json_data;
  ASSERT_TRUE(base::ReplaceChars(json_data, " \n\r",
                             "", &clean_json_data));

  ASSERT_EQ(clean_serialized, clean_json_data);
}

struct TestMultiConf_1 {
  static basic::StatusOr<std::string> tryLoadString(
    const std::string& key
    , const std::string& configuration_group
    , const base::Value& option_settings);

  // id for debug purposes
  static constexpr char kId[] = "TestMultiConf_1";
};

// static
basic::StatusOr<std::string> TestMultiConf_1::tryLoadString(
  const std::string& key
  , const std::string& configuration_group
  , const base::Value& option_settings)
{
  UNREFERENCED_PARAMETER(option_settings);

  DCHECK(!key.empty());

  if(option_settings.is_dict()) {
    if(const base::Value* value = option_settings.FindKey(kMustReturnStr); value) {
      return value->GetString();
    }
  }

  if(base::ToLowerASCII(formatConfigNameAndGroup(key, configuration_group))
      == formatConfigNameAndGroup(kTestKeyA, configuration_group))
  {
    return std::string{kResultForTestKeyA};
  }

  if(base::ToLowerASCII(formatConfigNameAndGroup(key, configuration_group))
      == formatConfigNameAndGroup(kTestKeyB, configuration_group))
  {
    return std::string{kResultForTestKeyB};
  }

  RETURN_ERROR()
    << FROM_HERE.ToString()
    << " unable to find env. key: "
    << formatConfigNameAndGroup(key, configuration_group)
    << " in loader "
    << kId;
}

#define TEST_MULTICONF_LOADER_1 \
    basic::MultiConfLoader{ \
      ::basic::TestMultiConf_1::kId \
      , base::BindRepeating(&::basic::TestMultiConf_1::tryLoadString) \
    }

struct TestMultiConf_2 {
  static basic::StatusOr<std::string> tryLoadString(
    const std::string& key
    , const std::string& configuration_group
    , const base::Value& option_settings);

  // id for debug purposes
  static constexpr char kId[] = "TestMultiConf_2";
};

// static
basic::StatusOr<std::string> TestMultiConf_2::tryLoadString(
  const std::string& key
  , const std::string& configuration_group
  , const base::Value& option_settings)
{
  UNREFERENCED_PARAMETER(option_settings);

  DCHECK(!key.empty());

  if(base::ToLowerASCII(formatConfigNameAndGroup(key, configuration_group))
       == formatConfigNameAndGroup(kTestKeyC, configuration_group))
  {
    return std::string{kResultForTestKeyC};
  }

  RETURN_ERROR()
    << FROM_HERE.ToString()
    << " unable to find env. key: "
    << formatConfigNameAndGroup(key, configuration_group)
    << " in loader "
    << kId;
}

#define TEST_MULTICONF_LOADER_2 \
    basic::MultiConfLoader{ \
      ::basic::TestMultiConf_2::kId \
      , base::BindRepeating(&::basic::TestMultiConf_2::tryLoadString) \
    }

class MultiConfTestObserver : public MultiConf::Observer {
 public:
  MultiConfTestObserver() : num_cache_changed_(0), num_option_changed_(0) {}

  ~MultiConfTestObserver() override = default;

  void onOptionReloaded(
    const MultiConfOption& option
    , const std::string& prev_value
    , const std::string& new_value) override
  {
    UNREFERENCED_PARAMETER(option);
    DVLOG(999)
      << "Detected change in configuration option from "
      << prev_value
      << " to "
      << new_value;
    ++num_option_changed_;
  }

  void onCacheReloaded() override
  {
    DVLOG(999)
      << "Detected configuration cache reload";
    ++num_cache_changed_;
  }

  std::string id() override {
    return "MultiConfTestObserver";
  }

  int num_option_changed() const { return num_option_changed_; }

  int num_cache_changed() const { return num_cache_changed_; }

 private:
  int num_cache_changed_;
  int num_option_changed_;

  DISALLOW_COPY_AND_ASSIGN(MultiConfTestObserver);
};

class MultiConfTest : public testing::Test {
  void SetUp() override {
    observer_ = std::make_unique<MultiConfTestObserver>();
    basic::MultiConf::GetInstance().AssertObserversEmpty();
    basic::MultiConf::GetInstance().addObserver(observer_.get());
    base::RunLoop().RunUntilIdle();
    ASSERT_TRUE(basic::MultiConf::GetInstance().isCacheEmpty());
    ASSERT_FALSE(basic::MultiConf::GetInstance().hasOptions());
    ASSERT_OK(basic::MultiConf::GetInstance().init());
  }
  void TearDown() override {
    basic::MultiConf::GetInstance().clearCache();
    basic::MultiConf::GetInstance().clearOptions();
    basic::MultiConf::GetInstance().removeObserver(observer_.get());
    base::RunLoop().RunUntilIdle();
    basic::MultiConf::GetInstance().AssertObserversEmpty();
  }
 public:
  base::test::TaskEnvironment task_environment;
  /// \note observer uses `PostTask`,
  /// so it requires `base::RunLoop().RunUntilIdle();`
  std::unique_ptr<MultiConfTestObserver> observer_;
};

TEST_F(MultiConfTest, DefaultValueTest) {
  ASSERT_TRUE(basic::MultiConf::GetInstance().isCacheEmpty());
  ASSERT_FALSE(basic::MultiConf::GetInstance().hasOptions());
  base::RunLoop().RunUntilIdle();
  ASSERT_EQ(observer_->num_option_changed(), 0);
  // Skips `onCacheReloaded` because no configuration options provided.
  ASSERT_EQ(observer_->num_cache_changed(), 1);

  MultiConfWrapper<std::string> tmp(CheckOptionPolicy::kCheckAddedNew,
    kDefaultKey, kResultForDefaultKey, {TEST_MULTICONF_LOADER_1}
    , kDefaultTestGroup, basic::UseGlobalLoaders::kFalse);
  MultiConfWrapper<std::string> keyDefaultObserver
    = basic::rvalue_cast(tmp);
  ASSERT_NOT_OK(TestMultiConf_1::tryLoadString(
    kDefaultKey, kDefaultTestGroup, base::Value{}));

  // already added by MultiConfWrapper
  {
    // must call `removeObserver(&tmp)` and `addObserver(&keyDefaultObserver)`
    EXPECT_EQ(kResultForDefaultKey, keyDefaultObserver.GetValue());

    ASSERT_NOT_OK(basic::MultiConf::GetInstance().addOption(
      basic::MultiConfOption{
        kDefaultKey
        , kResultForDefaultKey
        , {TEST_MULTICONF_LOADER_1}
        , kDefaultTestGroup
        , basic::UseGlobalLoaders::kFalse
      }));
  }

  EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
    kDefaultKey, kDefaultTestGroup));

  MULTICONF_String(my_conf_key_1, "abcd", {TEST_MULTICONF_LOADER_1}
    , kDefaultTestGroup, basic::UseGlobalLoaders::kFalse);
  ASSERT_NOT_OK(TestMultiConf_1::tryLoadString(
    "my_conf_key_1", kDefaultTestGroup, base::Value{}));

  ASSERT_OK(basic::MultiConf::GetInstance().clearAndReload());
  base::RunLoop().RunUntilIdle();

  ASSERT_EQ(basic::MultiConf::GetInstance().countOptions(), 2);
  ASSERT_EQ(observer_->num_option_changed(), 2);
  ASSERT_EQ(observer_->num_cache_changed(), 2);

  {
    base::RunLoop().RunUntilIdle();
    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      "my_conf_key_1", kDefaultTestGroup));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(
        "my_conf_key_1", kDefaultTestGroup))
      , "abcd");
    EXPECT_EQ(my_conf_key_1.GetValue(), "abcd");
  }

  {
    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      kDefaultKey, kDefaultTestGroup));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(kDefaultKey, kDefaultTestGroup))
      , kResultForDefaultKey);
    base::RunLoop().RunUntilIdle();
    EXPECT_EQ(kResultForDefaultKey, keyDefaultObserver.GetValue());
  }

  {
    EXPECT_FALSE(basic::MultiConf::GetInstance().hasOptionWithName(
      kUnknownKey, kDefaultTestGroup));
    EXPECT_NOT_OK(basic::MultiConf::GetInstance().getAsStringFromCache(
      kUnknownKey, kDefaultTestGroup));
  }

  {
    base::Value json_settings = basic::internal::parseJSONData(basic::Substitute(R"raw(
{
  "opt1":"val1",
  "$1":"$2",
  "opt3":"val3"
}
)raw", kMustReturnStr, kMustReturnStrResult)).ConsumeValueOrDie();
    const base::Value* json_key = json_settings.FindKey(kMustReturnStr);
    EXPECT_EQ(json_key->GetString(), kMustReturnStrResult);
    MULTICONF_String(my_conf_key_json, "ggdf", {TEST_MULTICONF_LOADER_1}
      , kDefaultTestGroup, basic::UseGlobalLoaders::kFalse
      , basic::rvalue_cast(json_settings));
    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      "my_conf_key_json", kDefaultTestGroup));
    EXPECT_NOT_OK(basic::MultiConf::GetInstance().getAsStringFromCache(
      "my_conf_key_json", kDefaultTestGroup));
    ASSERT_OK(basic::MultiConf::GetInstance().clearAndReload());
    base::RunLoop().RunUntilIdle();
    EXPECT_EQ(kMustReturnStrResult, my_conf_key_json.GetValue());
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache("my_conf_key_json", kDefaultTestGroup))
      , kMustReturnStrResult);
  }
}

TEST_F(MultiConfTest, ReloadJsonOptionTest) {
  ASSERT_TRUE(basic::MultiConf::GetInstance().isCacheEmpty());
  ASSERT_FALSE(basic::MultiConf::GetInstance().hasOptions());
  base::RunLoop().RunUntilIdle();
  ASSERT_EQ(observer_->num_option_changed(), 0);
  // Skips `onCacheReloaded` because no configuration options provided.
  ASSERT_EQ(observer_->num_cache_changed(), 1);

  MULTICONF_String(my_conf_key_1, "abcd", {JSON_MULTICONF_LOADER}
    , kDefaultTestGroup, basic::UseGlobalLoaders::kFalse);

  {
    ASSERT_OK(basic::MultiConf::GetInstance().reloadOptionWithName(
      "my_conf_key_1"
      , kDefaultTestGroup // configuration_group
      , false // notify_cache_reload
      , false // clear_cache_on_error
    ));

    ASSERT_EQ(basic::MultiConf::GetInstance().countOptions(), 1);
    base::RunLoop().RunUntilIdle();
    ASSERT_EQ(observer_->num_option_changed(), 1);
    ASSERT_EQ(observer_->num_cache_changed(), 1);

    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      "my_conf_key_1", kDefaultTestGroup));
    ASSERT_NOT_OK(basic::JsonMultiConf::GetInstance().tryLoadString(
      "my_conf_key_1", kDefaultTestGroup, base::Value{}));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(
        "my_conf_key_1", kDefaultTestGroup)
    ), "abcd");
    EXPECT_EQ(my_conf_key_1.GetValue(), "abcd");
  }

  {
    std::string json_data = basic::Substitute(R"raw(
  {"$1":"$2"}
  )raw", formatConfigNameAndGroup("my_conf_key_1", kDefaultTestGroup), "gdgdf");
    ASSERT_OK(JsonMultiConf::GetInstance().clearAndParseFromString(json_data));
    assertClearedJsonConfEquals(json_data);

    ASSERT_OK(basic::MultiConf::GetInstance().reloadOptionWithName(
      "my_conf_key_1"
      , kDefaultTestGroup // configuration_group
      , true // notify_cache_reload
      , false // clear_cache_on_error
    ));

    ASSERT_EQ(basic::MultiConf::GetInstance().countOptions(), 1);
    base::RunLoop().RunUntilIdle();
    ASSERT_EQ(observer_->num_option_changed(), 2);
    ASSERT_EQ(observer_->num_cache_changed(), 2);

    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      "my_conf_key_1", kDefaultTestGroup));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::JsonMultiConf::GetInstance().tryLoadString(
        "my_conf_key_1", kDefaultTestGroup, base::Value{})
    ), "gdgdf");
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(
        "my_conf_key_1", kDefaultTestGroup)
    ), "gdgdf");
    EXPECT_EQ(my_conf_key_1.GetValue(), "gdgdf");
  }

  {
    std::string json_data = basic::Substitute(R"raw(
  {"$1":"$2"}
  )raw", formatConfigNameAndGroup("my_conf_key_1", kDefaultTestGroup), "fhhffg");
    ASSERT_OK(JsonMultiConf::GetInstance().clearAndParseFromString(json_data));
    assertClearedJsonConfEquals(json_data);

    ASSERT_OK(basic::MultiConf::GetInstance().reloadOptionWithName(
      "my_conf_key_1"
      , kDefaultTestGroup // configuration_group
      , false // notify_cache_reload
      , false // clear_cache_on_error
    ));

    ASSERT_EQ(basic::MultiConf::GetInstance().countOptions(), 1);
    base::RunLoop().RunUntilIdle();
    ASSERT_EQ(observer_->num_option_changed(), 3);
    ASSERT_EQ(observer_->num_cache_changed(), 2);

    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      "my_conf_key_1", kDefaultTestGroup));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::JsonMultiConf::GetInstance().tryLoadString(
        "my_conf_key_1", kDefaultTestGroup, base::Value{})
    ), "fhhffg");
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(
        "my_conf_key_1", kDefaultTestGroup)
    ), "fhhffg");
    EXPECT_EQ(my_conf_key_1.GetValue(), "fhhffg");
  }
}

TEST_F(MultiConfTest, SimpleTest) {
  ASSERT_TRUE(basic::MultiConf::GetInstance().isCacheEmpty());
  ASSERT_FALSE(basic::MultiConf::GetInstance().hasOptions());
  base::RunLoop().RunUntilIdle();
  ASSERT_EQ(observer_->num_option_changed(), 0);
  // Skips `onCacheReloaded` because no configuration options provided.
  ASSERT_EQ(observer_->num_cache_changed(), 1);

  basic::MultiConfWrapper<std::string> keyAObserver(CheckOptionPolicy::kCheckAddedNew,
    kTestKeyA, "EMPTY", {TEST_MULTICONF_LOADER_1}, kDefaultTestGroup
    , basic::UseGlobalLoaders::kFalse);
  base::RunLoop().RunUntilIdle();
  EXPECT_EQ("EMPTY", keyAObserver.GetValue());

  // already added by MultiConfWrapper
  {
    ASSERT_NOT_OK(basic::MultiConf::GetInstance().addOption(basic::MultiConfOption{
      kTestKeyA
      , base::nullopt
      , { TEST_MULTICONF_LOADER_1 }
      , kDefaultTestGroup
      , basic::UseGlobalLoaders::kFalse
    }));
    EXPECT_EQ(CONSUME_STATUSOR(
      TestMultiConf_1::tryLoadString(kTestKeyA, kDefaultTestGroup, base::Value{})), kResultForTestKeyA);
  }

  EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
    kTestKeyA, kDefaultTestGroup));
  base::RunLoop().RunUntilIdle();
  EXPECT_EQ("EMPTY", keyAObserver.GetValue());

  ASSERT_OK(basic::MultiConf::GetInstance().addOption(basic::MultiConfOption{
    kTestKeyB
    , base::nullopt
    , { TEST_MULTICONF_LOADER_1 }
    , kDefaultTestGroup
    , basic::UseGlobalLoaders::kFalse
  }));
  EXPECT_EQ(CONSUME_STATUSOR(
    TestMultiConf_1::tryLoadString(kTestKeyB, kDefaultTestGroup, base::Value{})), kResultForTestKeyB);
  EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
    kTestKeyB, kDefaultTestGroup));

  ASSERT_OK(basic::MultiConf::GetInstance().clearAndReload());
  base::RunLoop().RunUntilIdle();

  ASSERT_EQ(basic::MultiConf::GetInstance().countOptions(), 2);
  ASSERT_EQ(observer_->num_option_changed(), 2);
  ASSERT_EQ(observer_->num_cache_changed(), 2);

  {
    EXPECT_FALSE(basic::MultiConf::GetInstance().hasOptionWithName(
      kUnknownKey, kDefaultTestGroup));
    EXPECT_NOT_OK(basic::MultiConf::GetInstance().getAsStringFromCache(
      kUnknownKey, kDefaultTestGroup));
  }

  {
    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      kTestKeyA, kDefaultTestGroup));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(kTestKeyA, kDefaultTestGroup))
      , kResultForTestKeyA);
    base::RunLoop().RunUntilIdle();
    EXPECT_EQ(kResultForTestKeyA, keyAObserver.GetValue());
  }

  {
    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      kTestKeyB, kDefaultTestGroup));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(kTestKeyB, kDefaultTestGroup))
      , kResultForTestKeyB);
  }

  /// \note added new option, need to reload cache
  ASSERT_OK(basic::MultiConf::GetInstance().addOption(basic::MultiConfOption{
    kTestKeyC
    , base::nullopt
    , { TEST_MULTICONF_LOADER_2 }
    , kDefaultTestGroup
    , basic::UseGlobalLoaders::kFalse
  }));
  EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
    kTestKeyC, kDefaultTestGroup));
  EXPECT_EQ(CONSUME_STATUSOR(
    TestMultiConf_2::tryLoadString(kTestKeyC, kDefaultTestGroup, base::Value{})), kResultForTestKeyC);

  /// \note added new option, need to reload cache
  ASSERT_OK(basic::MultiConf::GetInstance().addOption(basic::MultiConfOption{
    kTestKeyD
    , base::nullopt
    , { JSON_MULTICONF_LOADER }
    , kDefaultTestGroup
    , basic::UseGlobalLoaders::kFalse
  }));
  EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
    kTestKeyD, kDefaultTestGroup));

  base::test::ScopedEnvironmentVariableOverride scoped_env1(
    formatConfigNameAndGroup(kTestKeyF, kDefaultTestGroup), kResultForTestKeyF);

  {
    ASSERT_TRUE(scoped_env1.IsOverridden());
    std::string key_value;
    ASSERT_TRUE(basic::EnvMultiConf::GetInstance().env_->GetVar(
      formatConfigNameAndGroup(kTestKeyF, kDefaultTestGroup), &key_value));
    ASSERT_EQ(key_value, kResultForTestKeyF);
  }

  /// \note added new option, need to reload cache
  ASSERT_OK(basic::MultiConf::GetInstance().addOption(basic::MultiConfOption{
    kTestKeyF
    , base::nullopt
    , { ENV_MULTICONF_LOADER }
    , kDefaultTestGroup
    , basic::UseGlobalLoaders::kFalse
  }));
  EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
    kTestKeyF, kDefaultTestGroup));

  MULTICONF_String(my_conf_key_1, "abcd", {ENV_MULTICONF_LOADER}
    , kDefaultTestGroup, basic::UseGlobalLoaders::kFalse);

  base::test::ScopedEnvironmentVariableOverride scoped_env2(
    formatConfigNameAndGroup("my_conf_key_1", kDefaultTestGroup), "12345");

  {
    ASSERT_TRUE(scoped_env2.IsOverridden());
    std::string key_value;
    ASSERT_TRUE(basic::EnvMultiConf::GetInstance().env_->GetVar(
      formatConfigNameAndGroup("my_conf_key_1", kDefaultTestGroup), &key_value));
    ASSERT_EQ(key_value, "12345");
  }

  std::string json_data = basic::Substitute(R"raw(
{"$1":"$2"}
)raw", formatConfigNameAndGroup(kTestKeyD, kDefaultTestGroup), kResultForTestKeyD);
  ASSERT_OK(JsonMultiConf::GetInstance().clearAndParseFromString(json_data));
  assertClearedJsonConfEquals(json_data);

  ASSERT_OK(basic::MultiConf::GetInstance().clearAndReload());
  base::RunLoop().RunUntilIdle();

  EXPECT_EQ(CONSUME_STATUSOR(
    basic::EnvMultiConf::GetInstance().tryLoadString(
      kTestKeyF, kDefaultTestGroup, base::Value{})
  ), kResultForTestKeyF);

  EXPECT_EQ(CONSUME_STATUSOR(
    basic::JsonMultiConf::GetInstance().tryLoadString(
      kTestKeyD, kDefaultTestGroup, base::Value{})
  ), kResultForTestKeyD);

  {
    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      "my_conf_key_1", kDefaultTestGroup));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::EnvMultiConf::GetInstance().tryLoadString(
        "my_conf_key_1", kDefaultTestGroup, base::Value{})
    ), "12345");
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(
        "my_conf_key_1", kDefaultTestGroup)
    ), "12345");
    EXPECT_EQ(my_conf_key_1.GetValue(), "12345");
  }

  {
    EXPECT_FALSE(basic::MultiConf::GetInstance().hasOptionWithName(
      kUnknownKey, kDefaultTestGroup));
    EXPECT_NOT_OK(basic::MultiConf::GetInstance().getAsStringFromCache(
      kUnknownKey, kDefaultTestGroup));
  }

  {
    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      kTestKeyA, kDefaultTestGroup));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(
        kTestKeyA, kDefaultTestGroup))
      , kResultForTestKeyA);
  }

  {
    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      kTestKeyB, kDefaultTestGroup));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(
        kTestKeyB, kDefaultTestGroup))
      , kResultForTestKeyB);
  }

  {
    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(kTestKeyC, kDefaultTestGroup));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(kTestKeyC, kDefaultTestGroup))
      , kResultForTestKeyC);
  }

  {
    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      kTestKeyD, kDefaultTestGroup));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(
        kTestKeyD, kDefaultTestGroup))
      , kResultForTestKeyD);
  }

  {
    EXPECT_TRUE(basic::MultiConf::GetInstance().hasOptionWithName(
      kTestKeyF, kDefaultTestGroup));
    EXPECT_EQ(CONSUME_STATUSOR(
      basic::MultiConf::GetInstance().getAsStringFromCache(
        kTestKeyF, kDefaultTestGroup))
      , kResultForTestKeyF);
  }
}

class MultiThreadChecker {
 public:
  using Resolver
    = ::base::ManualPromiseResolver<
        void, ::base::NoReject
      >;

  MultiThreadChecker(
    MultiConfWrapper<std::string>& observer
    , const std::string& thread_name
    , scoped_refptr<::base::SingleThreadTaskRunner> runner)
    : observer(observer)
    , thread{std::make_shared<base::Thread>(thread_name)}
    , promiseResolver(FROM_HERE)
    , main_loop_task_runner_(runner)
  {}

  MultiThreadChecker(const MultiThreadChecker& other)
    : observer{other.observer}
    , thread{other.thread}
    , promiseResolver{other.promiseResolver}
    , main_loop_task_runner_{other.main_loop_task_runner_}
  {}

  MultiThreadChecker(MultiThreadChecker&& other)
    : observer(RVALUE_CAST(other.observer))
    , thread{RVALUE_CAST(other.thread)}
    , promiseResolver{RVALUE_CAST(other.promiseResolver)}
    , main_loop_task_runner_{RVALUE_CAST(other.main_loop_task_runner_)}
  {}

  MultiThreadChecker& operator=(
    const MultiThreadChecker& other)
  {
    observer = other.observer;
    thread = other.thread;
    promiseResolver = other.promiseResolver;
    main_loop_task_runner_ = other.main_loop_task_runner_;
    return *this;
  }

  MultiThreadChecker& operator=(
    MultiThreadChecker&& other)
  {
    observer = RVALUE_CAST(other.observer);
    thread = RVALUE_CAST(other.thread);
    promiseResolver = RVALUE_CAST(other.promiseResolver);
    main_loop_task_runner_ = RVALUE_CAST(other.main_loop_task_runner_);
    return *this;
  }

  auto postClearAndReload() {
    /// \note `clearAndReload` is not thread-safe
    return base::PostTaskAndReplyWithPromise(main_loop_task_runner_.get()
      , FROM_HERE
      , ::base::BindOnce(
          &basic::MultiConf::clearAndReload
          , base::Unretained(&basic::MultiConf::GetInstance())
          , true // clear_cache_on_error
        )
      // check result of `clearAndReload`
      , ::base::BindOnce([](
          basic::Status result)
        {
          EXPECT_OK(result);
        })
    );
  }

  void onTaskDone(const std::string& expected_value) {
    /// \note requires `clearAndReload`
    EXPECT_EQ(observer.get().GetValue(), expected_value);
    // allow program termination
    // after all threads executed `GetResolveCallback`
    basic::rvalue_cast(promiseResolver.GetResolveCallback()).Run();
  }

  void DoTask(const std::string& expected_value) {
    postClearAndReload()
    .ThenHere(
      FROM_HERE
      , ::base::BindOnce(
          &MultiThreadChecker::onTaskDone
          , base::Unretained(this)
          , expected_value)
    );
  }

  std::reference_wrapper<MultiConfWrapper<std::string>> observer;

  std::shared_ptr<::base::Thread> thread;

  Resolver promiseResolver;

  // allows to schedule arbitrary tasks on main loop
  scoped_refptr<::base::SingleThreadTaskRunner> main_loop_task_runner_;
};

TEST_F(MultiConfTest, ReloadObserver) {
  MULTICONF_String(my_key_X, "dasasd", {JSON_MULTICONF_LOADER}
    , kDefaultTestGroup, basic::UseGlobalLoaders::kFalse);
  EXPECT_EQ(my_key_X.target_name(), "my_key_X");
  EXPECT_EQ(my_key_X.target_configuration_group(), kDefaultTestGroup);

  MULTICONF_Observer(observer_X, my_key_X);
  EXPECT_EQ(observer_X.target_name(), my_key_X.target_name());
  EXPECT_EQ(observer_X.target_configuration_group(), my_key_X.target_configuration_group());

  ASSERT_OK(basic::MultiConf::GetInstance().clearAndReload());
  base::RunLoop().RunUntilIdle();

  EXPECT_EQ("dasasd", my_key_X.GetValue());
  EXPECT_EQ("dasasd", observer_X.GetValue());

  std::string json_data = basic::Substitute(R"raw(
{"$1":"$2"}
)raw", formatConfigNameAndGroup("my_key_X", kDefaultTestGroup), "bbbddf");
  ASSERT_OK(JsonMultiConf::GetInstance().clearAndParseFromString(json_data));
  assertClearedJsonConfEquals(json_data);

  ASSERT_OK(basic::MultiConf::GetInstance().clearAndReload());
  base::RunLoop().RunUntilIdle();

  EXPECT_EQ("bbbddf", my_key_X.GetValue());
  EXPECT_EQ("bbbddf", observer_X.GetValue());
}

TEST_F(MultiConfTest, GlobalLoader) {
  basic::MultiConf::GetInstance().addGlobalLoaders({JSON_MULTICONF_LOADER});
  EXPECT_TRUE(basic::MultiConf::GetInstance().hasGlobalLoaders({JSON_MULTICONF_LOADER}));

  MULTICONF_String(my_key_global_load, "dasasd", {DUMMY_LOADER}
    , kDefaultTestGroup, basic::UseGlobalLoaders::kTrue);
  EXPECT_EQ(my_key_global_load.target_name(), "my_key_global_load");
  EXPECT_EQ(my_key_global_load.target_configuration_group(), kDefaultTestGroup);

  MULTICONF_String(my_key_without_global_load, "dffgg", {DUMMY_LOADER}
    , kDefaultTestGroup, basic::UseGlobalLoaders::kFalse);

  MULTICONF_Observer(observer_X, my_key_global_load);
  EXPECT_EQ(observer_X.target_name(), my_key_global_load.target_name());
  EXPECT_EQ(observer_X.target_configuration_group(), my_key_global_load.target_configuration_group());

  ASSERT_OK(basic::MultiConf::GetInstance().clearAndReload());
  base::RunLoop().RunUntilIdle();

  EXPECT_EQ("dffgg", my_key_without_global_load.GetValue());
  EXPECT_EQ("dasasd", my_key_global_load.GetValue());
  EXPECT_EQ("dasasd", observer_X.GetValue());

  std::string json_data = basic::Substitute(R"raw(
{
  "$1":"$2",
  "$3":"$4"
}
)raw"
  , formatConfigNameAndGroup("my_key_global_load", kDefaultTestGroup)
  , "bbbddf"
  , formatConfigNameAndGroup("my_key_without_global_load", kDefaultTestGroup)
  , "bbbddf");
  ASSERT_OK(JsonMultiConf::GetInstance().clearAndParseFromString(json_data));
  assertClearedJsonConfEquals(json_data);

  ASSERT_OK(basic::MultiConf::GetInstance().clearAndReload());
  base::RunLoop().RunUntilIdle();

  EXPECT_EQ(CONSUME_STATUSOR(
    basic::MultiConf::GetInstance().getAsStringFromCache("my_key_without_global_load", kDefaultTestGroup))
    , "dffgg");
  EXPECT_EQ("dffgg", my_key_without_global_load.GetValue());
  EXPECT_EQ(CONSUME_STATUSOR(
    basic::MultiConf::GetInstance().getAsStringFromCache("my_key_global_load", kDefaultTestGroup))
    , "bbbddf");
  EXPECT_EQ("bbbddf", my_key_global_load.GetValue());
  EXPECT_EQ("bbbddf", observer_X.GetValue());

  basic::MultiConf::GetInstance().removeGlobalLoaders({JSON_MULTICONF_LOADER});
  EXPECT_FALSE(basic::MultiConf::GetInstance().hasGlobalLoaders({JSON_MULTICONF_LOADER}));

  ASSERT_OK(basic::MultiConf::GetInstance().clearAndReload());
  base::RunLoop().RunUntilIdle();

  EXPECT_EQ(CONSUME_STATUSOR(
    basic::MultiConf::GetInstance().getAsStringFromCache("my_key_without_global_load", kDefaultTestGroup))
    , "dffgg");
  EXPECT_EQ("dffgg", my_key_without_global_load.GetValue());
  EXPECT_EQ(CONSUME_STATUSOR(
    basic::MultiConf::GetInstance().getAsStringFromCache("my_key_global_load", kDefaultTestGroup))
    , "dasasd");
  EXPECT_EQ("dasasd", my_key_global_load.GetValue());
  EXPECT_EQ("dasasd", observer_X.GetValue());
}

TEST_F(MultiConfTest, MultiThreadTest) {
  static constexpr const size_t num_treads = 8;

  MULTICONF_String(my_conf_key_Y, "abcd", {TEST_MULTICONF_LOADER_1}
    , kDefaultTestGroup, basic::UseGlobalLoaders::kFalse);

  MULTICONF_Observer(key_Y_observer_0, my_conf_key_Y);
  MULTICONF_Observer(key_Y_observer_1, my_conf_key_Y);
  MULTICONF_Observer(key_Y_observer_2, my_conf_key_Y);
  MULTICONF_Observer(key_Y_observer_3, my_conf_key_Y);
  MULTICONF_Observer(key_Y_observer_4, my_conf_key_Y);
  MULTICONF_Observer(key_Y_observer_5, my_conf_key_Y);
  MULTICONF_Observer(key_Y_observer_6, my_conf_key_Y);
  MULTICONF_Observer(key_Y_observer_7, my_conf_key_Y);

  base::RunLoop run_loop;

  std::vector<MultiThreadChecker> thread_checkers;

  {
    /// \note Each thread uses individual observer.
    /// If you change code to use single observer by multiple threads,
    /// than test must `DCHECK` on thread collision.
    std::array<std::reference_wrapper<decltype(my_conf_key_Y)>, num_treads> thread_observers {
      REFERENCED(key_Y_observer_0)
      , REFERENCED(key_Y_observer_1)
      , REFERENCED(key_Y_observer_2)
      , REFERENCED(key_Y_observer_7)
      , REFERENCED(key_Y_observer_4)
      , REFERENCED(key_Y_observer_5)
      , REFERENCED(key_Y_observer_6)
      , REFERENCED(key_Y_observer_7)
    };
    for(size_t i = 0; i < num_treads; i++)
    {
      thread_checkers.emplace_back(
        REFERENCED(thread_observers[i].get())
        , basic::Substitute("Test thread $1", i)
        , ::base::ThreadTaskRunnerHandle::Get());
    }
  }

  // Run `run_loop.QuitClosure()` after all threads finished `DoTask`
  std::vector<base::Promise<void>> thread_promises;
  for(MultiThreadChecker& thread_checker: thread_checkers) {
    thread_promises.push_back(thread_checker.promiseResolver.promise());
  }
  base::Promises::All(FROM_HERE, thread_promises)
  .ThenHere(FROM_HERE
    , run_loop.QuitClosure()
  );

  for(MultiThreadChecker& thread_checker: thread_checkers) {
    ASSERT_TRUE(thread_checker.thread->Start());
    // Without this call this test is racy.
    EXPECT_TRUE(thread_checker.thread->WaitUntilThreadStarted());
  }

  /// \note schedules per-thread tasks only after `run_loop.Run()`
  ::base::ThreadTaskRunnerHandle::Get()->PostTask(
    FROM_HERE
    , base::BindOnce([
    ](
      std::vector<MultiThreadChecker>& thread_checkers
    ){
      /// \note runs per-thread tasks
      for(MultiThreadChecker& thread_checker: thread_checkers) {
        thread_checker.thread->task_runner()->PostTask(
          FROM_HERE
          , ::base::BindOnce(
              &MultiThreadChecker::DoTask
              , base::Unretained(&thread_checker)
              , "abcd"
            )
        );
      }
    }
    , REFERENCED(thread_checkers))
  );

  run_loop.Run();

  for(MultiThreadChecker& thread_checker: thread_checkers) {
    thread_checker.thread->Stop();
  }
}

} // namespace basic
