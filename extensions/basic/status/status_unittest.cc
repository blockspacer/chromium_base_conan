// Copyright 2018 Google LLC
// Copyright 2018-present Open Networking Foundation
// SPDX-License-Identifier: Apache-2.0

#include "basic/status/status.h"
#include "basic/files/scoped_temp_file.h"

#include <base/strings/strcat.h>
#include <base/strings/string_number_conversions.h>

#include <stdio.h>

#include <algorithm>

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

TEST(ErrorSpace, SpaceName) {
  ASSERT_EQ(std::string("generic"),
            ::basic::OkStatus().error_space()->SpaceName());
  ASSERT_EQ(std::string("myerrors"), my_error_space.SpaceName());
}

TEST(ErrorSpace, FindKnown) {
  ASSERT_EQ(&my_error_space, ::basic::ErrorSpace::Find("myerrors"));
  ASSERT_EQ(&my_error_space2, ::basic::ErrorSpace::Find("myerrors2"));
}

TEST(ErrorSpace, FindGeneric) {
  ASSERT_NE(kNullSpace, ::basic::ErrorSpace::Find("generic"));
}

TEST(ErrorSpace, FindUnknown) {
  ASSERT_EQ(kNullSpace, ::basic::ErrorSpace::Find("nonexistent_error_space"));
}

TEST(ErrorSpace, FindDestroyed) {
  { MyErrorSpace temp_space("temporary_name"); }
  ASSERT_EQ(kNullSpace, ::basic::ErrorSpace::Find("temporary_name"));
}

TEST(ErrorSpace, GenericCodeNames) {
  const ::basic::ErrorSpace* e = ::basic::CancelledStatus(FROM_HERE).error_space();
  EXPECT_EQ("cancelled", e->String(::basic::error::CANCELLED));
  EXPECT_EQ("unknown", e->String(::basic::error::UNKNOWN));
  EXPECT_EQ("aborted", e->String(::basic::error::ABORTED));
  EXPECT_EQ("1000", e->String(1000));  // Out of range
  EXPECT_EQ("OK", e->String(::basic::error::OK));
}

TEST(Status, Empty) {
  ::basic::Status status;
  CheckStatus(status, OkSpace(), 0, "");
}

TEST(Status, OK) { CheckStatus(::basic::OkStatus(), OkSpace(), 0, ""); }

TEST(Status, GenericCodes) {
  EXPECT_EQ(static_cast<int>(::basic::error::OK),
            static_cast<int>(::basic::Status::OK_CODE));
  EXPECT_EQ(static_cast<int>(::basic::error::CANCELLED),
            static_cast<int>(::basic::Status::CANCELLED_CODE));
  EXPECT_EQ(static_cast<int>(::basic::error::UNKNOWN),
            static_cast<int>(::basic::Status::UNKNOWN_CODE));
}

TEST(Status, ConstructorZero) {
  ::basic::Status status;
  CheckStatus(status, OkSpace(), 0, "");
}

TEST(Status, CheckOK) {
  ::basic::Status status;
  CHECK_OK(status);
  CHECK_OK(status) << "Failed";
  DCHECK_OK(status) << "Failed";
}

TEST(DeathStatus, CheckOK) {
  ::basic::Status status;
  status =
      ::basic::Status(FROM_HERE, ::basic::Status::canonical_space(),
                     ::basic::Status::CANCELLED_CODE, "Operation Cancelled");
  ASSERT_DEATH(CHECK_OK(status), "Operation Cancelled");
}

#if 0 /// \todo ignore error message if status is ok
TEST(Status, SetErrorZero) {
  ::basic::Status status(FROM_HERE, &my_error_space, 2, "message");
  status = ::basic::Status(FROM_HERE, &my_error_space, 0, "msg");
  CheckStatus(status, OkSpace(), 0, "");
}
#endif

TEST(Status, Cancelled) {
  ASSERT_THAT(::basic::CancelledStatus(FROM_HERE).ToString(),
              testing::HasSubstr("cancel"));
}

TEST(Status, Filled) {
  ::basic::Status status(FROM_HERE, &my_error_space, 2, "message");
  CheckStatus(status, &my_error_space, 2, "message");
}

TEST(Status, FilledNegative) {
  ::basic::Status status(FROM_HERE, &my_error_space, -2, "message");
  CheckStatus(status, &my_error_space, -2, "message");
}

TEST(Status, Set) {
  ::basic::Status status;
  status = ::basic::Status(FROM_HERE, &my_error_space, 2, "message");
  CheckStatus(status, &my_error_space, 2, "message");
}

TEST(Status, SetOverlappingMessage) {
  ::basic::Status status;
  status = ::basic::Status(FROM_HERE, &my_error_space, 2, "message");
  CheckStatus(status, &my_error_space, 2, "message");

  std::string old_message = status.error_message();
  status = ::basic::Status(FROM_HERE, &my_error_space, 2, old_message);
  CheckStatus(status, &my_error_space, 2, "message");

  std::string full_message = status.error_message();
  std::string part_message = full_message.substr(1, 3);
  EXPECT_EQ(part_message, "ess");
  status = ::basic::Status(FROM_HERE, &my_error_space, 2, part_message);
  CheckStatus(status, &my_error_space, 2, "ess");
}

TEST(Status, Clear) {
  ::basic::Status status(FROM_HERE, &my_error_space, 2, "message");
  status.Clear();
  CheckStatus(status, OkSpace(), 0, "");
}

TEST(Status, Copy) {
  ::basic::Status a(FROM_HERE, &my_error_space, 2, "message");
  ::basic::Status b(a);
  ASSERT_EQ(a.ToString(), b.ToString());
}

TEST(Status, Assign) {
  ::basic::Status a(FROM_HERE, &my_error_space, 2, "message");
  ::basic::Status b;
  b = a;
  ASSERT_EQ(a.ToString(), b.ToString());
}

TEST(Status, Update) {
  ::basic::Status s;
  s.UpdateIfOk(::basic::OkStatus());
  ASSERT_TRUE(s.ok());
  ::basic::Status a(FROM_HERE, &my_error_space, 2, "message");
  s.UpdateIfOk(a);
  ASSERT_EQ(s.ToString(), a.ToString());
  ::basic::Status b(FROM_HERE, &my_error_space, 17, "other message");
  s.UpdateIfOk(b);
  ASSERT_EQ(s.ToString(), a.ToString());
  s.UpdateIfOk(::basic::OkStatus());
  ASSERT_EQ(s.ToString(), a.ToString());
  ASSERT_FALSE(s.ok());
}

TEST(Status, Swap) {
  ::basic::Status a(FROM_HERE, &my_error_space, 2, "message");
  ::basic::Status b = a;
  ::basic::Status c;
  c.Swap(&a);
  ASSERT_EQ(c.ToString(), b.ToString());
  EXPECT_THAT(a.ToString(), testing::HasSubstr("OK"));
}

TEST(Status, UnknownCode) {
  ::basic::Status status(FROM_HERE, &my_error_space, 10, "message");
  ASSERT_TRUE(!status.ok());
  ASSERT_EQ(10, status.error_code());
  ASSERT_EQ(::basic::error::UNKNOWN, CanonicalCode(status));
  ASSERT_EQ(std::string("message"), status.error_message());
  ASSERT_EQ(status.error_space(), &my_error_space);
  ASSERT_THAT(status.ToString(),
              testing::MatchesRegex("myerrors.*10.*message.*"));
}

TEST(Status, MatchOK) {
  ASSERT_TRUE(::basic::OkStatus().Matches(::basic::OkStatus()));
}

TEST(Status, MatchSame) {
  const ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1, "message");
  const ::basic::Status b = ::basic::Status(FROM_HERE, &my_error_space, 1, "message");
  ASSERT_TRUE(a.Matches(b));
}

TEST(Status, MatchCopy) {
  const ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1, "message");
  const ::basic::Status b = a;
  ASSERT_TRUE(a.Matches(b));
}

TEST(Status, MatchDifferentCode) {
  const ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1, "message");
  const ::basic::Status b = ::basic::Status(FROM_HERE, &my_error_space, 2, "message");
  ASSERT_TRUE(!a.Matches(b));
}

TEST(Status, MatchDifferentSpace) {
  const ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1, "message");
  const ::basic::Status b = ::basic::Status(FROM_HERE, &my_error_space2, 1, "message");
  ASSERT_TRUE(!a.Matches(b));
}

TEST(Status, MatchDifferentMessage) {
  const ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1, "message");
  const ::basic::Status b = ::basic::Status(FROM_HERE, &my_error_space, 1, "another");
  ASSERT_TRUE(a.Matches(b));
}

TEST(Status, EqualsOK) { ASSERT_EQ(::basic::OkStatus(), ::basic::OkStatus()); }

TEST(Status, EqualsSame) {
  const ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1, "message");
  const ::basic::Status b = ::basic::Status(FROM_HERE, &my_error_space, 1, "message");
  ASSERT_EQ(a, b);
}

TEST(Status, EqualsCopy) {
  const ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1, "message");
  const ::basic::Status b = a;
  ASSERT_EQ(a, b);
}

TEST(Status, EqualsDifferentCode) {
  const ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1, "message");
  const ::basic::Status b = ::basic::Status(FROM_HERE, &my_error_space, 2, "message");
  ASSERT_NE(a, b);
}

TEST(Status, EqualsDifferentSpace) {
  const ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1, "message");
  const ::basic::Status b = ::basic::Status(FROM_HERE, &my_error_space2, 1, "message");
  ASSERT_NE(a, b);
}

TEST(Status, EqualsDifferentMessage) {
  const ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1, "message");
  const ::basic::Status b = ::basic::Status(FROM_HERE, &my_error_space, 1, "another");
  ASSERT_NE(a, b);
}

TEST(Status, EqualsCanonicalCodeSame) {
  ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1234, "message");
  ::basic::Status b = ::basic::Status(FROM_HERE, &my_error_space, 1234, "message");
  ASSERT_EQ(a, b);
  a.SetCanonicalCode(::basic::error::RESOURCE_EXHAUSTED);
  b.SetCanonicalCode(::basic::error::RESOURCE_EXHAUSTED);
  ASSERT_EQ(a, b);
}

TEST(Status, EqualsCanonicalCodeMismatch) {
  ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1234, "message");
  ::basic::Status b = ::basic::Status(FROM_HERE, &my_error_space, 1234, "message");
  ASSERT_EQ(a, b);
  a.SetCanonicalCode(::basic::error::RESOURCE_EXHAUSTED);
  b.SetCanonicalCode(::basic::error::UNAVAILABLE);
  ASSERT_NE(a, b);
}

TEST(Status, StripMessage) {
  ::basic::Status a = ::basic::Status(FROM_HERE, &my_error_space, 1, "");
  ::basic::Status b = ::basic::Status(FROM_HERE, &my_error_space, 1, "x");
  ASSERT_EQ(a, b.StripMessage());
}

static void SanityCheck(const ::basic::Status& s, const ::basic::ErrorSpace* space,
                        int code, const std::string& msg) {
  EXPECT_EQ(code, s.error_code());
  EXPECT_EQ(space, s.error_space());

  ::basic::Status copy(s);
  EXPECT_EQ(s, copy);

  ::basic::Status other(FROM_HERE, ::basic::error::DEADLINE_EXCEEDED, "_sanity_check_");
  EXPECT_NE(other, s);

  ::basic::Status updated;
  updated.UpdateIfOk(s);
  EXPECT_EQ(s, updated);

  // Matches / StripMessage
  ::basic::Status with_msg(FROM_HERE, space, code, "_sanity_check_");
  EXPECT_TRUE(s.Matches(with_msg));
  EXPECT_EQ(s, with_msg.StripMessage());
  if (!s.ok()) {
    EXPECT_FALSE(s == with_msg);
  }

  // SetError
  ::basic::Status err;
  err = ::basic::Status(FROM_HERE, space, code, msg);
  EXPECT_EQ(s, err);
}

TEST(Status, Globals) {
  const ::basic::ErrorSpace* space = ::basic::Status::canonical_space();
  SanityCheck(::basic::OkStatus(), space, ::basic::Status::OK_CODE, "");
  SanityCheck(::basic::CancelledStatus(FROM_HERE), space, ::basic::Status::CANCELLED_CODE,
              "");
  SanityCheck(::basic::UnknownStatus(FROM_HERE), space, ::basic::Status::UNKNOWN_CODE, "");
}

TEST(Canonical, WrongSpace) {
  ::basic::Status status(FROM_HERE, &my_error_space, 1, "message");
  const ::basic::ErrorSpace* space = ::basic::Status::canonical_space();
  EXPECT_EQ(::basic::error::UNKNOWN, space->CanonicalCode(status));
}

TEST(Canonical, CustomMapping) {
  ::basic::Status s(FROM_HERE, &my_error_space, 60, "message");
  EXPECT_EQ(::basic::error::PERMISSION_DENIED, CanonicalCode(s));
}

static void VerifyCanonical(const ::basic::Status& s,
                            ::basic::error::Code match_code,
                            ::basic::error::Code nomatch_code) {
  EXPECT_EQ(match_code, s.CanonicalCode());
  EXPECT_TRUE(s.Matches(match_code)) << match_code;
  EXPECT_FALSE(s.Matches(nomatch_code)) << nomatch_code;
}

TEST(Canonical, CanonicalCode) {
  ::basic::Status ok = ::basic::OkStatus();
  ::basic::Status cancel = ::basic::CancelledStatus(FROM_HERE);
  ::basic::Status perm(FROM_HERE, &my_error_space, 60, "message");
  ::basic::Status other(FROM_HERE, &my_error_space, 10, "message");
  VerifyCanonical(ok, ::basic::error::OK, ::basic::error::UNKNOWN);
  VerifyCanonical(cancel, ::basic::error::CANCELLED, ::basic::error::UNKNOWN);
  VerifyCanonical(perm, ::basic::error::PERMISSION_DENIED,
                  ::basic::error::UNKNOWN);
  VerifyCanonical(other, ::basic::error::UNKNOWN,
                  ::basic::error::PERMISSION_DENIED);

  // Check handling of a canonical code not known in this address space.
  perm.SetCanonicalCode(static_cast<int>(::basic::error::Code_MAX) + 1);
  VerifyCanonical(perm, ::basic::error::UNKNOWN,
                  ::basic::error::PERMISSION_DENIED);
}

TEST(Canonical, SetCanonicalCode) {
  ::basic::Status s(FROM_HERE, &my_error_space, 1234, "message");
  s.SetCanonicalCode(::basic::error::RESOURCE_EXHAUSTED);
  EXPECT_EQ(1234, s.error_code());
  EXPECT_EQ(::basic::error::RESOURCE_EXHAUSTED, CanonicalCode(s));
}

#if 0 /// \todo ignore CanonicalCode if status is ok
TEST(Canonical, SetCanonicalCodeIgnoredOnOkStatus) {
  ::basic::Status s(FROM_HERE, &my_error_space, 0, "message");
  s.SetCanonicalCode(::basic::error::RESOURCE_EXHAUSTED);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(::basic::error::OK, CanonicalCode(s));
}
#endif

TEST(Canonical, SetCanonicalCodeIgnoredOnCanonicalSpace) {
  ::basic::Status s(FROM_HERE, ::basic::error::DEADLINE_EXCEEDED, "message");
  s.SetCanonicalCode(::basic::error::RESOURCE_EXHAUSTED);
  EXPECT_EQ(::basic::error::DEADLINE_EXCEEDED, s.error_code());
  EXPECT_EQ(::basic::error::DEADLINE_EXCEEDED, CanonicalCode(s));
}

TEST(Canonical, SetCanonicalCodeOnSharedStatus) {
  const ::basic::Status x(FROM_HERE, &my_error_space, 1234, "message");

  // Set canonical code on a copy.
  ::basic::Status y = x;
  y.SetCanonicalCode(::basic::error::RESOURCE_EXHAUSTED);
  EXPECT_NE(x, y);
  EXPECT_EQ(x.error_space(), y.error_space());
  EXPECT_EQ(x.error_code(), y.error_code());
  EXPECT_EQ(x.error_message(), y.error_message());
  EXPECT_EQ(::basic::error::UNKNOWN, CanonicalCode(x));
  EXPECT_EQ(::basic::error::RESOURCE_EXHAUSTED, CanonicalCode(y));

  // Yet another copy, with a different code set.
  ::basic::Status z = y;
  z.SetCanonicalCode(::basic::error::DEADLINE_EXCEEDED);
  EXPECT_NE(y, z);
  EXPECT_EQ(x.error_space(), z.error_space());
  EXPECT_EQ(x.error_code(), z.error_code());
  EXPECT_EQ(x.error_message(), z.error_message());
  EXPECT_EQ(::basic::error::RESOURCE_EXHAUSTED, CanonicalCode(y));
  EXPECT_EQ(::basic::error::DEADLINE_EXCEEDED, CanonicalCode(z));
}

#ifdef BENCHMARK
static void BM_StatusCreateDestroy(int iters) {
  int count = 0;
  ::basic::Status dummy = ::basic::CancelledStatus(FROM_HERE);
  for (int i = 0; i < iters; i++) {
    ::basic::Status s;
    if (i == 17) {
      s = dummy;
    }
    if (!s.ok()) {
      count++;
    }
  }
  if (count == -1) {
    fprintf(stderr, "Dummy use");
  }
}
BENCHMARK(BM_StatusCreateDestroy);

static void BM_StatusCopy(int iters) {
  ::basic::Status dummy[2];
  dummy[1] = ::basic::CancelledStatus(FROM_HERE);
  int count = 0;
  for (int i = 0; i < iters; i++) {
    ::basic::Status s = dummy[i == 17];
    if (!s.ok()) {
      count++;
    }
  }
  if (count == -1) {
    fprintf(stderr, "Dummy use");
  }
}
BENCHMARK(BM_StatusCopy);
#endif  // BENCHMARK
