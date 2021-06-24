#include "basic/algorithm/base32.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace base {

static constexpr const uint32_t kOutputSize = 256;

TEST(Base32Test, EmptyWithNullptr)
{
  char output[kOutputSize] = "";
  Base32Encode(nullptr, 0, output, kOutputSize);
  EXPECT_STREQ("", output);
}

TEST(Base32Test, EmptyWitoutNullptr)
{
  char output[kOutputSize] = "";
  Base32Encode("", 0, output, kOutputSize);
  EXPECT_STREQ("", output);
}

TEST(Base32Test, First)
{
  {
    std::string output;
    Base32Encode("f", &output);
    EXPECT_EQ("MY======", output);
  }

  char output[kOutputSize] = "";
  Base32Encode("f", 1, output, kOutputSize);
  EXPECT_STREQ("MY======", output);
}

TEST(Base32Test, Second)
{
  {
    std::string output;
    Base32Encode("fo", &output);
    EXPECT_EQ("MZXQ====", output);
  }

  char output[kOutputSize] = "";
  Base32Encode("fo", 2, output, kOutputSize);
  EXPECT_STREQ("MZXQ====", output);
}

TEST(Base32Test, Third)
{
  {
    std::string output;
    Base32Encode("foo", &output);
    EXPECT_EQ("MZXW6===", output);
  }

  char output[kOutputSize] = "";
  Base32Encode("foo", 3, output, kOutputSize);
  EXPECT_STREQ("MZXW6===", output);
}

TEST(Base32Test, Fourth)
{
  {
    std::string output;
    Base32Encode("foob", &output);
    EXPECT_EQ("MZXW6YQ=", output);
  }

  char output[kOutputSize] = "";
  Base32Encode("foob", 4, output, kOutputSize);
  EXPECT_STREQ("MZXW6YQ=", output);
}

TEST(Base32Test, Fith)
{
  {
    std::string output;
    Base32Encode("fooba", &output);
    EXPECT_EQ("MZXW6YTB", output);
  }

  char output[kOutputSize] = "";
  Base32Encode("fooba", 5, output, kOutputSize);
  EXPECT_STREQ("MZXW6YTB", output);
}

TEST(Base32Test, Sixth)
{
  {
    std::string output;
    Base32Encode("foobar", &output);
    EXPECT_EQ("MZXW6YTBOI======", output);
  }

  char output[kOutputSize] = "";
  Base32Encode("foobar", 6, output, kOutputSize);
  EXPECT_STREQ("MZXW6YTBOI======", output);
}

}  // namespace base
