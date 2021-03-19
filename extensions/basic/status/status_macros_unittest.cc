// Copyright 2018 Google LLC
// Copyright 2018-present Open Networking Foundation
// SPDX-License-Identifier: Apache-2.0

#include "basic/status/status_callback.h"
#include "basic/status/app_error_space.h"
#include "basic/test/test_macros.h"

#include <base/strings/strcat.h>
#include <base/strings/string_number_conversions.h>
#include <base/bind.h>
#include <base/callback.h>
#include <base/location.h>
#include <base/i18n/string_search.h>

#include <cstdio>
#include <string>
#include <algorithm>
#include <functional>

#include "testing/gtest/include/gtest/gtest.h"
#include "testing/gmock/include/gmock/gmock.h"

class MyErrorSpace : public ::basic::ErrorSpace {
 public:
  explicit MyErrorSpace(const char* name) : ::basic::ErrorSpace(name) {}
  std::string String(int code) const {
    return ::base::StrCat({"error(", base::NumberToString(code), ")"});
  }

  ::basic::error::Code CanonicalCode(const ::basic::Status& status) const {
    switch (status.error_code()) {
      case 60:
        return ::basic::error::PERMISSION_DENIED;
      default:
        return ::basic::error::UNKNOWN;
    }
  }
};
static MyErrorSpace my_error_space("myerrors");
static MyErrorSpace my_error_space2("myerrors2");

// Typed null pointer for tests below
static const ::basic::ErrorSpace* kNullSpace =
    reinterpret_cast<::basic::ErrorSpace*>(NULL);

static const ::basic::ErrorSpace* OkSpace() {
  return ::basic::OkStatus().error_space();
}

static int CanonicalCode(const ::basic::Status& s) {
  return s.ToCanonical().error_code();
}

// Check that s has the specified fields.
// An empty payload means the s must not contain a payload.
static void CheckStatus(const ::basic::Status& s, const ::basic::ErrorSpace* space,
                        int code, const std::string& message) {
  EXPECT_EQ(code, s.error_code()) << s;
  EXPECT_EQ(space, s.error_space()) << s;
  EXPECT_EQ(message, s.error_message()) << s;

  if (code == 0) {
    EXPECT_TRUE(s.ok()) << s;
    EXPECT_EQ(0, CanonicalCode(s));
    EXPECT_THAT(s.ToString(), testing::HasSubstr("OK")) << s;
  } else {
    EXPECT_TRUE(!s.ok()) << s;
    EXPECT_EQ(::basic::error::UNKNOWN, CanonicalCode(s));
    EXPECT_THAT(s.ToString(), testing::HasSubstr(space->SpaceName()));
    EXPECT_THAT(s.ToString(), testing::HasSubstr(space->String(code)));
    EXPECT_THAT(s.ToString(), testing::HasSubstr(message));
  }
}

basic::Status ReturnCheckStatus(
  const ::basic::Status& s, const ::basic::ErrorSpace* space,
  int code, const std::string& message)
{
  CheckStatus(s, space, code, message);
  RETURN_OK();
}

basic::StatusOr<std::unique_ptr<int>> ReturnUniquePtr(
  const base::Location& loc, int x)
{
  // Uses implicit constructor from T&&
  return {std::unique_ptr<int>(new int(x))};
}

TEST(StatusMacros, RepeatingStatus) {
  {
    basic::RepeatingStatusClosure testCb
      = base::BindRepeating(&ReturnCheckStatus, ::basic::OkStatus(), OkSpace(), 0, "");
    EXPECT_OK(testCb.Run());
  }

  {
    basic::RepeatingStatus<
      const ::basic::Status&, const ::basic::ErrorSpace*, int, const std::string&
    > testCb
      = base::BindRepeating(&ReturnCheckStatus);
    EXPECT_OK(testCb.Run(::basic::OkStatus(), OkSpace(), 0, ""));
  }

  {
    basic::RepeatingStatusOrClosure<std::unique_ptr<int>> testCb
      = base::BindRepeating(&ReturnUniquePtr, FROM_HERE, 0);
    basic::StatusOr<std::unique_ptr<int>> thing(testCb.Run());
    ASSERT_TRUE(thing.ok());
    std::unique_ptr<int> ptr = thing.ConsumeValueOrDie();
    EXPECT_EQ(0, *ptr);
  }

  {
    basic::RepeatingStatusOr<std::unique_ptr<int>, const base::Location&, int> testCb
      = base::BindRepeating(&ReturnUniquePtr);
    basic::StatusOr<std::unique_ptr<int>> thing(testCb.Run(FROM_HERE, 0));
    ASSERT_TRUE(thing.ok());
    std::unique_ptr<int> ptr = thing.ConsumeValueOrDie();
    EXPECT_EQ(0, *ptr);
  }
}

TEST(StatusMacros, OnceStatus) {
  {
    basic::OnceStatusClosure testCb
      = base::BindOnce(&ReturnCheckStatus, ::basic::OkStatus(), OkSpace(), 0, "");
    EXPECT_OK(std::move(testCb).Run());
  }

  {
    basic::OnceStatus<
      const ::basic::Status&, const ::basic::ErrorSpace*, int, const std::string&
    > testCb
      = base::BindOnce(&ReturnCheckStatus);
    EXPECT_OK(std::move(testCb).Run(::basic::OkStatus(), OkSpace(), 0, ""));
  }

  {
    basic::OnceStatusOrClosure<std::unique_ptr<int>> testCb
      = base::BindOnce(&ReturnUniquePtr, FROM_HERE, 0);
    basic::StatusOr<std::unique_ptr<int>> thing(std::move(testCb).Run());
    ASSERT_TRUE(thing.ok());
    std::unique_ptr<int> ptr = thing.ConsumeValueOrDie();
    EXPECT_EQ(0, *ptr);
  }

  {
    basic::OnceStatusOr<std::unique_ptr<int>, const base::Location&, int> testCb
      = base::BindOnce(&ReturnUniquePtr);
    basic::StatusOr<std::unique_ptr<int>> thing(std::move(testCb).Run(FROM_HERE, 0));
    ASSERT_TRUE(thing.ok());
    std::unique_ptr<int> ptr = thing.ConsumeValueOrDie();
    EXPECT_EQ(0, *ptr);
  }
}

TEST(StatusMacros, MakeError) {
  {
    basic::Status status = MAKE_ERROR() << "Message";
    EXPECT_NOT_OK(status);
  }
  {
    using namespace app_error_space;
    basic::Status status = MAKE_ERROR(ERR_UNKNOWN) << "Message";
    EXPECT_ERROR_CODE(ERR_UNKNOWN, status);
  }
}

TEST(StatusMacros, AppendError) {
  {
    basic::Status status = MAKE_ERROR() << "Message";
    status = APPEND_ERROR(status) << "Message2";
    EXPECT_NOT_OK(status);
  }
  {
    using namespace app_error_space;
    basic::Status status = MAKE_ERROR(ERR_UNKNOWN) << "Message";
    status = APPEND_ERROR(status) << "Message2";
    EXPECT_ERROR_CODE(ERR_UNKNOWN, status);
  }
}

TEST(StatusMacros, ErrorIf) {
  {
    std::function<basic::Status(bool)> task = [](bool has_err)
      -> basic::Status
    {
      RETURN_ERROR_IF(has_err)
        << "Message";
      RETURN_OK();
    };
    EXPECT_NOT_OK(task(true));
    ASSERT_STR_CONTAINS(task(true).error_message(), "Message");
    EXPECT_OK(task(false));
  }
  {
    using namespace app_error_space;
    std::function<basic::Status(bool)> task = [](bool has_err)
      -> basic::Status
    {
      RETURN_ERROR_IF(has_err, ERR_UNKNOWN)
        << "Message";
      RETURN_OK();
    };
    EXPECT_ERROR_CODE(ERR_UNKNOWN, task(true));
    ASSERT_STR_CONTAINS(task(true).error_message(), "Message");
    EXPECT_OK(task(false));
  }
}

TEST(StatusMacros, AppendIfNotOk) {
  using namespace app_error_space;
  std::function<basic::Status(bool)> task = [](bool has_err)
    -> basic::Status
  {
    RETURN_ERROR_IF(has_err, ERR_UNKNOWN)
      << "Message";
    RETURN_OK();
  };

  {
    basic::Status result;
    EXPECT_OK(result);
    APPEND_STATUS_IF_NOT_OK(result, task(true));
    EXPECT_ERROR_CODE(ERR_UNKNOWN, result);
    ASSERT_STR_CONTAINS(result.error_message(), "Message");
  }

  {
    basic::Status result;
    EXPECT_OK(result);
    APPEND_STATUS_IF_NOT_OK(result, task(false));
    EXPECT_OK(result);
  }
}

TEST(StatusMacros, ReturnWithMessageIfNotOk) {
  using namespace app_error_space;
  std::function<basic::Status(app_error_space::ErrorCode)> task
    = [](app_error_space::ErrorCode code) -> basic::Status
  {
    basic::Status status;
    if(code != ERR_SUCCESS) {
      status = MAKE_ERROR(code);
    }
    RETURN_WITH_MESSAGE_IF_NOT_OK(status)
      << "Message";
    RETURN_OK();
  };

  {
    basic::Status result = task(ERR_UNKNOWN);
    EXPECT_ERROR_CODE(ERR_UNKNOWN, result);
    ASSERT_STR_CONTAINS(result.error_message(), "Message");
  }

  {
    EXPECT_OK(task(ERR_SUCCESS));
  }
}


TEST(StatusMacros, ReturnOtherStatusIfNotOk) {
  using namespace app_error_space;
  std::function<basic::Status(app_error_space::ErrorCode)> task
    = [](app_error_space::ErrorCode code) -> basic::Status
  {
    basic::Status status;
    if(code != ERR_SUCCESS) {
      status = MAKE_ERROR(code)
      << "Message2";
    }
    DCHECK_NE(code, ERR_INTERNAL);
    RETURN_OTHER_STATUS_IF_NOT_OK(status, ERR_INTERNAL)
      << "Message1"
      /// \note added message from other status
      << STATUS_MESSAGE(status);
    RETURN_OK();
  };

  {
    basic::Status result = task(ERR_UNKNOWN);
    /// \note code changed from ERR_UNKNOWN
    EXPECT_ERROR_CODE(ERR_INTERNAL, result);
    ASSERT_STR_CONTAINS(result.error_message(), "Message1");
    ASSERT_STR_CONTAINS(result.error_message(), "Message2");
  }

  {
    EXPECT_OK(task(ERR_SUCCESS));
  }
}

TEST(StatusMacros, ReturnIfErrorCode) {
  using namespace app_error_space;
  std::function<basic::Status(app_error_space::ErrorCode)> task
    = [](app_error_space::ErrorCode code) -> basic::Status
  {
    basic::Status status;
    if(code != ERR_SUCCESS) {
      status = MAKE_ERROR(code);
    }
    RETURN_IF_ERROR_CODE_EQUALS(status, ERR_UNKNOWN)
      << "Message";
    RETURN_OK();
  };

  {
    basic::Status result = task(ERR_UNKNOWN);
    EXPECT_ERROR_CODE(ERR_UNKNOWN, result);
    ASSERT_STR_CONTAINS(result.error_message(), "Message");
  }

  {
    EXPECT_OK(task(ERR_SUCCESS));
  }
}

TEST(StatusMacros, AssignOrReturn) {
  using namespace app_error_space;

  const int kTaskExpectedRet = 11223344;

  std::function<basic::StatusOr<int>(int val)> taskA
    = [&](int val) -> basic::StatusOr<int>
  {
    RETURN_ERROR_IF(val < 0, ERR_OUT_OF_RANGE)
      << "Message1";
    return {val};
  };

  std::function<basic::Status(basic::StatusOr<int>)> taskB
    = [&](basic::StatusOr<int> statusor) -> basic::Status
  {
    // Think that `CONSUME_OR_RETURN(int value, statusor)` is same as:
    // int value;
    // if(statusor) {
    //   value = statusor.ConsumeValueOrDie();
    // } else {
    //   return statusor.status();
    // } /* It is safe now to use `int value`... */
    CONSUME_OR_RETURN(int value, statusor);
    RETURN_ERROR_IF(value != kTaskExpectedRet, ERR_FAILED_PRECONDITION)
      << "Message2";
    RETURN_OK();
  };

  std::function<basic::Status(int&)> taskC
    = [&](int& val) -> basic::Status
  {
    basic::StatusOr<int> statusor;
    if (val > 0) statusor = basic::StatusOr<int>{val};
    CONSUME_OR_RETURN_WITH_MESSAGE(val
      , statusor, std::string{"failed_to_parse_JSON_string"});
    RETURN_OK();
  };

  {
    int val = -1;
    ASSERT_NOT_OK(taskC(REFERENCED(val)));
    ASSERT_EQ(val, -1);
  }

  {
    int val = 1;
    ASSERT_OK(taskC(REFERENCED(val)));
    ASSERT_EQ(val, 1);
  }

  {
    basic::Status result = taskB(taskA(-123));
    EXPECT_ERROR_CODE(ERR_OUT_OF_RANGE, result);
    ASSERT_STR_CONTAINS(result.error_message(), "Message1");
  }

  {
    basic::Status result = taskB(taskA(123));
    EXPECT_ERROR_CODE(ERR_FAILED_PRECONDITION, result);
    ASSERT_STR_CONTAINS(result.error_message(), "Message2");
  }

  {
    basic::Status result = taskB(taskA(kTaskExpectedRet));
    EXPECT_OK(result);
  }
}
