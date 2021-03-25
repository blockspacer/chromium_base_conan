// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/decimal/fixed_point.h"
#include "basic/decimal/fixed_point_numeric_limits.h"
#include "basic/status/status_macros.h"
#include "basic/promise/post_promise.h"
#include "basic/rvalue_cast.h"
#include "basic/promise/abstract_promise.h"
#include "basic/promise/helpers.h"

#include "base/test/gtest_util.h"
#include "base/test/test_mock_time_task_runner.h"
#include "base/test/task_environment.h"
#include "base/bind.h"
#include "base/check.h"
#include "base/run_loop.h"
#include "base/threading/thread.h"
#include "base/task_runner.h"

#include "testing/gtest/include/gtest/gtest.h"

#include <cstdint>
#include <limits>
#include <algorithm>
#include <numeric>

namespace basic {

namespace test {

class FixedPointTest : public testing::Test {
 public:
  void SetUp() override {}

 protected:
  base::test::TaskEnvironment task_environment;
};

template <typename T>
class FixedPointTestBothReps : public testing::Test {
 public:
  void SetUp() override {}

 protected:
  base::test::TaskEnvironment task_environment;
};

using RepresentationTypes = ::testing::Types<int32_t, int64_t>;

TYPED_TEST_CASE(FixedPointTestBothReps, RepresentationTypes);

TYPED_TEST(FixedPointTestBothReps, SimpleDecimalXXConstruction)
{
  using decimalXX = FixedPointNumber<TypeParam, Radix::BASE_10>;

  decimalXX num0{1.234567, scale_type{0}};
  decimalXX num1{1.234567, scale_type{-1}};
  decimalXX num2{1.234567, scale_type{-2}};
  decimalXX num3{1.234567, scale_type{-3}};
  decimalXX num4{1.234567, scale_type{-4}};
  decimalXX num5{1.234567, scale_type{-5}};
  decimalXX num6{1.234567, scale_type{-6}};

  EXPECT_EQ(1, static_cast<double>(num0));
  EXPECT_EQ(1.2, static_cast<double>(num1));
  EXPECT_EQ(1.23, static_cast<double>(num2));
  EXPECT_EQ(1.234, static_cast<double>(num3));
  EXPECT_EQ(1.2345, static_cast<double>(num4));
  EXPECT_EQ(1.23456, static_cast<double>(num5));
  EXPECT_EQ(1.234567, static_cast<double>(num6));
}

TYPED_TEST(FixedPointTestBothReps, SimpleNegativeDecimalXXConstruction)
{
  using decimalXX = FixedPointNumber<TypeParam, Radix::BASE_10>;

  decimalXX num0{-1.234567, scale_type{0}};
  decimalXX num1{-1.234567, scale_type{-1}};
  decimalXX num2{-1.234567, scale_type{-2}};
  decimalXX num3{-1.234567, scale_type{-3}};
  decimalXX num4{-1.234567, scale_type{-4}};
  decimalXX num5{-1.234567, scale_type{-5}};
  decimalXX num6{-1.234567, scale_type{-6}};

  EXPECT_EQ(-1, static_cast<double>(num0));
  EXPECT_EQ(-1.2, static_cast<double>(num1));
  EXPECT_EQ(-1.23, static_cast<double>(num2));
  EXPECT_EQ(-1.234, static_cast<double>(num3));
  EXPECT_EQ(-1.2345, static_cast<double>(num4));
  EXPECT_EQ(-1.23456, static_cast<double>(num5));
  EXPECT_EQ(-1.234567, static_cast<double>(num6));
}

TYPED_TEST(FixedPointTestBothReps, PaddedDecimalXXConstruction)
{
  using decimalXX = FixedPointNumber<TypeParam, Radix::BASE_10>;

  decimalXX a{1.1, scale_type{-1}};
  decimalXX b{1.01, scale_type{-2}};
  decimalXX c{1.001, scale_type{-3}};
  decimalXX d{1.0001, scale_type{-4}};
  decimalXX e{1.00001, scale_type{-5}};
  decimalXX f{1.000001, scale_type{-6}};

  decimalXX x{1.000123, scale_type{-8}};
  decimalXX y{0.000123, scale_type{-8}};

  EXPECT_EQ(1.1, static_cast<double>(a));
  EXPECT_EQ(1.01, static_cast<double>(b));
  EXPECT_EQ(1, static_cast<double>(c));  // intentional (inherited problem from floating point)
  EXPECT_EQ(1.0001, static_cast<double>(d));
  EXPECT_EQ(1.00001, static_cast<double>(e));
  EXPECT_EQ(1, static_cast<double>(f));  // intentional (inherited problem from floating point)

  EXPECT_TRUE(1.000123 - static_cast<double>(x) < std::numeric_limits<double>::epsilon());
  EXPECT_EQ(0.000123, static_cast<double>(y));

  decimalXX num9{1.45, scale_type{-4}};
  EXPECT_EQ(1.45, static_cast<double>(num9));

  decimalXX num10{1.45, scale_type{-2}};
  EXPECT_EQ(1.45, static_cast<double>(num10));
}

TYPED_TEST(FixedPointTestBothReps, SimpleBinaryFPConstruction)
{
  using binary_fp = FixedPointNumber<TypeParam, Radix::BASE_2>;

  binary_fp num0{10, scale_type{0}};
  binary_fp num1{10, scale_type{1}};
  binary_fp num2{10, scale_type{2}};
  binary_fp num3{10, scale_type{3}};
  binary_fp num4{10, scale_type{4}};

  binary_fp num5{1.24, scale_type{0}};
  binary_fp num6{1.24, scale_type{-1}};
  binary_fp num7{1.32, scale_type{-2}};
  binary_fp num8{1.41, scale_type{-3}};
  binary_fp num9{1.45, scale_type{-4}};

  EXPECT_EQ(10, static_cast<double>(num0));
  EXPECT_EQ(10, static_cast<double>(num1));
  EXPECT_EQ(8, static_cast<double>(num2));
  EXPECT_EQ(8, static_cast<double>(num3));
  EXPECT_EQ(0, static_cast<double>(num4));

  EXPECT_EQ(1, static_cast<double>(num5));
  EXPECT_EQ(1, static_cast<double>(num6));
  EXPECT_EQ(1.25, static_cast<double>(num7));
  EXPECT_EQ(1.375, static_cast<double>(num8));
  EXPECT_EQ(1.4375, static_cast<double>(num9));
}

TYPED_TEST(FixedPointTestBothReps, MoreSimpleBinaryFPConstruction)
{
  using binary_fp = FixedPointNumber<TypeParam, Radix::BASE_2>;

  binary_fp num0{1.25, scale_type{-2}};
  binary_fp num1{2.1, scale_type{-4}};

  EXPECT_EQ(1.25, static_cast<double>(num0));
  EXPECT_EQ(2.0625, static_cast<double>(num1));
}

TYPED_TEST(FixedPointTestBothReps, SimpleDecimalXXMath)
{
  using decimalXX = FixedPointNumber<TypeParam, Radix::BASE_10>;

  decimalXX ONE{1, scale_type{-2}};
  decimalXX TWO{2, scale_type{-2}};
  decimalXX THREE{3, scale_type{-2}};
  decimalXX SIX{6, scale_type{-2}};

  EXPECT_TRUE(ONE + ONE == TWO);

  EXPECT_EQ(ONE + ONE, TWO);
  EXPECT_EQ(ONE * TWO, TWO);
  EXPECT_EQ(THREE * TWO, SIX);
  EXPECT_EQ(THREE - TWO, ONE);
#if TODO
  EXPECT_EQ(TWO / ONE, TWO);
  EXPECT_EQ(SIX / TWO, THREE);
#endif

  decimalXX a{1.23, scale_type{-2}};
  decimalXX b{0, scale_type{0}};

  EXPECT_EQ(a + b, a);
  EXPECT_EQ(a - b, a);
}

TYPED_TEST(FixedPointTestBothReps, ComparisonOperators)
{
  using decimalXX = FixedPointNumber<TypeParam, Radix::BASE_10>;

  decimalXX ONE{1, scale_type{-1}};
  decimalXX TWO{2, scale_type{-2}};
  decimalXX THREE{3, scale_type{-3}};
  decimalXX SIX{6, scale_type{-4}};

  EXPECT_TRUE(ONE + ONE >= TWO);

  EXPECT_TRUE(ONE + ONE <= TWO);
  EXPECT_TRUE(ONE * TWO < THREE);
  EXPECT_TRUE(THREE * TWO > THREE);
  EXPECT_TRUE(THREE - TWO >= ONE);
#if TODO
  EXPECT_TRUE(TWO / ONE < THREE);
  EXPECT_TRUE(SIX / TWO >= ONE);
#endif
}

TYPED_TEST(FixedPointTestBothReps, DecimalXXTrickyDivision)
{
  using decimalXX = FixedPointNumber<TypeParam, Radix::BASE_10>;

  decimalXX ONE_1{1, scale_type{1}};
  decimalXX ONE_0{1, scale_type{0}};
  decimalXX SIX_0{6, scale_type{0}};
  decimalXX SIX_1{6, scale_type{1}};
  decimalXX TEN_0{10, scale_type{0}};
  decimalXX TEN_1{10, scale_type{1}};
  decimalXX SIXTY_1{60, scale_type{1}};
  decimalXX SIXTY_0{60, scale_type{0}};

  EXPECT_EQ(static_cast<int32_t>(ONE_1), 0);
  EXPECT_EQ(static_cast<std::string>(ONE_1), "00");
  EXPECT_EQ(static_cast<int32_t>(SIX_1), 0);
  EXPECT_EQ(static_cast<std::string>(SIX_1), "00");
  EXPECT_EQ(static_cast<int32_t>(TEN_0), 10);
  EXPECT_EQ(static_cast<std::string>(TEN_0), "10");
  EXPECT_EQ(static_cast<int32_t>(SIXTY_1), 60);
  EXPECT_EQ(static_cast<std::string>(SIXTY_1), "60");

  EXPECT_EQ(static_cast<std::string>(TEN_1), "10");
  EXPECT_EQ(static_cast<std::string>(SIX_0), "6");

#if TODO
  EXPECT_EQ(SIXTY_0 / TEN_0, SIX_0);
  EXPECT_EQ(SIXTY_1 / TEN_0, ONE_1);
  EXPECT_EQ(SIXTY_1 / TEN_1, SIX_0);

  decimalXX A{34.56, scale_type{-2}};
  decimalXX B{1.234, scale_type{-3}};
  decimalXX C{1, scale_type{-2}};

  EXPECT_EQ(static_cast<int32_t>(A / B), 20);
  EXPECT_EQ(static_cast<int32_t>((A * C) / B), 28);
#endif

  decimalXX n{28, scale_type{1}};
  EXPECT_EQ(static_cast<int32_t>(n), 20);
}

TYPED_TEST(FixedPointTestBothReps, DecimalXXRounding)
{
  using decimalXX = FixedPointNumber<TypeParam, Radix::BASE_10>;

  decimalXX ZERO_0{0, scale_type{0}};
  decimalXX ZERO_1{4, scale_type{1}};
  decimalXX THREE_0{3, scale_type{0}};
  decimalXX FOUR_0{4, scale_type{0}};
  decimalXX FIVE_0{5, scale_type{0}};
  decimalXX TEN_0{10, scale_type{0}};
  decimalXX TEN_1{10, scale_type{1}};

  decimalXX FOURTEEN_0{14, scale_type{0}};
  decimalXX FIFTEEN_0{15, scale_type{0}};

  EXPECT_EQ(ZERO_0, ZERO_1);
  EXPECT_EQ(TEN_0, TEN_1);

  EXPECT_EQ(ZERO_1 + TEN_1, TEN_1);
  EXPECT_EQ(FOUR_0 + TEN_1, FOURTEEN_0);
  EXPECT_TRUE(ZERO_0 == ZERO_1);
  EXPECT_TRUE(FIVE_0 != TEN_1);
  EXPECT_TRUE(FIVE_0 + FIVE_0 + FIVE_0 == FIFTEEN_0);
  EXPECT_TRUE(FIVE_0 + FIVE_0 + FIVE_0 != TEN_1);
  EXPECT_TRUE(FIVE_0 * THREE_0 == FIFTEEN_0);
  EXPECT_TRUE(FIVE_0 * THREE_0 != TEN_1);
}

TYPED_TEST(FixedPointTestBothReps, ArithmeticWithDifferentScales)
{
  using decimalXX = FixedPointNumber<TypeParam, Radix::BASE_10>;

  decimalXX a{1, scale_type{0}};
  decimalXX b{1.2, scale_type{-1}};
  decimalXX c{1.23, scale_type{-2}};
  decimalXX d{1.111, scale_type{-3}};

  decimalXX x{2.2, scale_type{-1}};
  decimalXX y{3.43, scale_type{-2}};
  decimalXX z{4.541, scale_type{-3}};

  decimalXX xx{0.2, scale_type{-1}};
  decimalXX yy{0.03, scale_type{-2}};
  decimalXX zz{0.119, scale_type{-3}};

  EXPECT_EQ(a + b, x);
  EXPECT_EQ(a + b + c, y);
  EXPECT_EQ(a + b + c + d, z);
  EXPECT_EQ(b - a, xx);
  EXPECT_EQ(c - b, yy);
  EXPECT_EQ(c - d, zz);
}

TYPED_TEST(FixedPointTestBothReps, RescaledTest)
{
  using decimalXX = FixedPointNumber<TypeParam, Radix::BASE_10>;

  decimalXX num0{1, scale_type{0}};
  decimalXX num1{1.2, scale_type{-1}};
  decimalXX num2{1.23, scale_type{-2}};
  decimalXX num3{1.234, scale_type{-3}};
  decimalXX num4{1.2345, scale_type{-4}};
  decimalXX num5{1.23456, scale_type{-5}};
  decimalXX num6{1.234567, scale_type{-6}};

  EXPECT_EQ(num0, num6.rescaled(scale_type{0}));
  EXPECT_EQ(num1, num6.rescaled(scale_type{-1}));
  EXPECT_EQ(num2, num6.rescaled(scale_type{-2}));
  EXPECT_EQ(num3, num6.rescaled(scale_type{-3}));
  EXPECT_EQ(num4, num6.rescaled(scale_type{-4}));
  EXPECT_EQ(num5, num6.rescaled(scale_type{-5}));
}

TYPED_TEST(FixedPointTestBothReps, RescaledRounding)
{
  using decimalXX = FixedPointNumber<TypeParam, Radix::BASE_10>;

  decimalXX num0{1500, scale_type{0}};
  decimalXX num1{1499, scale_type{0}};
  decimalXX num2{-1499, scale_type{0}};
  decimalXX num3{-1500, scale_type{0}};

  EXPECT_EQ(1000, static_cast<TypeParam>(num0.rescaled(scale_type{3})));
  EXPECT_EQ(1000, static_cast<TypeParam>(num1.rescaled(scale_type{3})));
  EXPECT_EQ(-1000, static_cast<TypeParam>(num2.rescaled(scale_type{3})));
  EXPECT_EQ(-1000, static_cast<TypeParam>(num3.rescaled(scale_type{3})));
}

TYPED_TEST(FixedPointTestBothReps, BoolConversion)
{
  using decimalXX = FixedPointNumber<TypeParam, Radix::BASE_10>;

  decimalXX truthy_value{1.234567, scale_type{0}};
  decimalXX falsy_value{0, scale_type{0}};

  // Test explicit conversions
  EXPECT_EQ(static_cast<bool>(truthy_value), true);
  EXPECT_EQ(static_cast<bool>(falsy_value), false);

  // These operators also *explicitly* convert to bool
  EXPECT_EQ(truthy_value && true, true);
  EXPECT_EQ(true && truthy_value, true);
  EXPECT_EQ(falsy_value || false, false);
  EXPECT_EQ(false || falsy_value, false);
  EXPECT_EQ(!truthy_value, false);
  EXPECT_EQ(!falsy_value, true);
}

TEST_F(FixedPointTest, OverflowDecimal32)
{
  // This flag is needed to avoid warnings with ASSERT_DCHECK_DEATH
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  using decimal32 = FixedPointNumber<int32_t, Radix::BASE_10>;

  decimal32 num0{2, scale_type{-9}};
  decimal32 num1{-2, scale_type{-9}};

  {
    auto const scale = std::min(num0.scale(), num0.scale());
    EXPECT_TRUE(addition_overflow<int32_t>(num0.rescaled(scale).value(), num0.rescaled(scale).value()))
      << "FixedPointNumber overflow of underlying representation type "
      << print_rep<int32_t>();
  }

  ASSERT_DCHECK_DEATH(num0 + num0);
  ASSERT_DCHECK_DEATH(num1 - num0);

  decimal32 min{std::numeric_limits<int32_t>::min(), scale_type{0}};
  decimal32 max{std::numeric_limits<int32_t>::max(), scale_type{0}};
  decimal32 NEG_ONE{-1, scale_type{0}};
  decimal32 ONE{1, scale_type{0}};
  decimal32 TWO{2, scale_type{0}};

#if TODO
  ASSERT_DCHECK_DEATH(min / NEG_ONE);
#endif
  ASSERT_DCHECK_DEATH(max * TWO);
  ASSERT_DCHECK_DEATH(min * TWO);
  ASSERT_DCHECK_DEATH(max + ONE);
  ASSERT_DCHECK_DEATH(max - NEG_ONE);
  ASSERT_DCHECK_DEATH(min - ONE);
  ASSERT_DCHECK_DEATH(max - NEG_ONE);
}

TEST_F(FixedPointTest, OverflowDecimal64)
{
  // This flag is needed to avoid warnings with ASSERT_DEATH
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  using decimal64 = FixedPointNumber<int64_t, Radix::BASE_10>;

  decimal64 num0{5, scale_type{-18}};
  decimal64 num1{-5, scale_type{-18}};

#if TODO
  {
    auto const scale = std::min(num0.scale(), num0.scale());
    EXPECT_TRUE(addition_overflow<int64_t>(num0.rescaled(scale).value(), num0.rescaled(scale).value()))
      << "FixedPointNumber overflow of underlying representation type "
      << print_rep<int64_t>();
  }

  ASSERT_DCHECK_DEATH(num0 + num0);
  ASSERT_DCHECK_DEATH(num1 - num0);
#endif

  decimal64 min{std::numeric_limits<int64_t>::min(), scale_type{0}};
  decimal64 max{std::numeric_limits<int64_t>::max(), scale_type{0}};
  decimal64 NEG_ONE{-1, scale_type{0}};
  decimal64 ONE{1, scale_type{0}};
  decimal64 TWO{2, scale_type{0}};

#if TODO
  ASSERT_DCHECK_DEATH(min / NEG_ONE);
#endif
  ASSERT_DCHECK_DEATH(max * TWO);
  ASSERT_DCHECK_DEATH(min * TWO);
  ASSERT_DCHECK_DEATH(max + ONE);
  ASSERT_DCHECK_DEATH(max - NEG_ONE);
  ASSERT_DCHECK_DEATH(min - ONE);
  ASSERT_DCHECK_DEATH(max - NEG_ONE);
}

template <typename ValueType, typename Binop>
void integer_vector_test(ValueType const initial_value,
                         int32_t const size,
                         int32_t const scale,
                         Binop binop)
{
  using decimal32 = FixedPointNumber<int32_t, Radix::BASE_10>;

  std::vector<decimal32> vec1(size);
  std::vector<ValueType> vec2(size);

  std::iota(std::begin(vec1), std::end(vec1), decimal32{initial_value, scale_type{scale}});
  std::iota(std::begin(vec2), std::end(vec2), initial_value);

  auto const res1 =
    std::accumulate(std::cbegin(vec1), std::cend(vec1), decimal32{0, scale_type{scale}});

  auto const res2 = std::accumulate(std::cbegin(vec2), std::cend(vec2), static_cast<ValueType>(0));

  EXPECT_EQ(static_cast<int32_t>(res1), res2);

  std::vector<ValueType> vec3(vec1.size());

  std::transform(std::cbegin(vec1), std::cend(vec1), std::begin(vec3), [](auto const& e) {
    return static_cast<int32_t>(e);
  });

  EXPECT_EQ(vec2, vec3);
}

TEST_F(FixedPointTest, Decimal32IntVector)
{
  integer_vector_test(0, 10, -2, std::plus<>());
  integer_vector_test(0, 1000, -2, std::plus<>());

  integer_vector_test(1, 10, 0, std::multiplies<>());
  integer_vector_test(2, 20, 0, std::multiplies<>());
}

template <typename ValueType, typename Binop>
void float_vector_test(ValueType const initial_value,
                       int32_t const size,
                       int32_t const scale,
                       Binop binop)
{
  using decimal32 = FixedPointNumber<int32_t, Radix::BASE_10>;

  std::vector<decimal32> vec1(size);
  std::vector<ValueType> vec2(size);

  std::iota(std::begin(vec1), std::end(vec1), decimal32{initial_value, scale_type{scale}});
  std::iota(std::begin(vec2), std::end(vec2), initial_value);

  auto equal = std::equal(
    std::cbegin(vec1), std::cend(vec1), std::cbegin(vec2), [](auto const& a, auto const& b) {
      return static_cast<double>(a) - b <= std::numeric_limits<ValueType>::epsilon();
    });

  EXPECT_TRUE(equal);
}

TEST_F(FixedPointTest, Decimal32FloatVector)
{
  // float_vector_test(initial_value, size, scale, binop)

  float_vector_test(0.1, 1000, -2, std::plus<>());
  float_vector_test(0.15, 1000, -2, std::plus<>());

  float_vector_test(0.1, 10, -2, std::multiplies<>());
  float_vector_test(0.15, 20, -2, std::multiplies<>());
}

TEST_F(FixedPointTest, String)
{
  EXPECT_EQ(static_cast<double>(decimal32{100, scale_type{-5}}), 100);
  EXPECT_EQ(static_cast<double>(decimal32{100, scale_type{-4}}), 100);
  EXPECT_EQ(static_cast<double>(decimal32{100, scale_type{-3}}), 100);
  EXPECT_EQ(static_cast<double>(decimal32{100, scale_type{-2}}), 100);
  EXPECT_EQ(static_cast<double>(decimal32{100, scale_type{-1}}), 100);
  EXPECT_EQ(static_cast<double>(decimal32{100, scale_type{0}}), 100);
  EXPECT_EQ(static_cast<double>(decimal32{100, scale_type{1}}), 100);
  EXPECT_EQ(static_cast<double>(decimal32{100, scale_type{2}}), 100);
  EXPECT_EQ(static_cast<double>(decimal32{100, scale_type{3}}), 0);
  EXPECT_EQ(static_cast<double>(decimal32{100, scale_type{4}}), 0);

#if TODO
  decimal32 one_0{1.0000, scale_type{0}};
  EXPECT_EQ(static_cast<std::string>(one_0 / decimal32(2.5, scale_type{-1})), "00");
  EXPECT_EQ(static_cast<double>(one_0 / decimal32(2.5, scale_type{-1})), 0);
  decimal32 one_4{1.0000, scale_type{-4}};
  EXPECT_EQ(static_cast<std::string>(one_4 / decimal32(2.5, scale_type{-1})), "0.400");
  EXPECT_EQ(static_cast<double>(one_4 / decimal32(2.5, scale_type{-1})), 0.4);

  EXPECT_EQ(decimal32(1, scale_type{0}).value(), 1);
  EXPECT_EQ(static_cast<std::string>(decimal32(1, scale_type{0})), "1");
  EXPECT_EQ(static_cast<size_t>(decimal32(1, scale_type{0})), 1);

  EXPECT_EQ(decimal32(1, scale_type{-2}).value(), 100);
  EXPECT_EQ(static_cast<std::string>(decimal32(1, scale_type{-2})), "1.00");
  EXPECT_EQ(static_cast<size_t>(decimal32(1, scale_type{-2})), 1);

  EXPECT_EQ(decimal32(1, scale_type{2}).value(), 0);
  EXPECT_EQ(static_cast<std::string>(decimal32(1, scale_type{2})), "000");
  EXPECT_EQ(static_cast<size_t>(decimal32(1, scale_type{2})), 0);

  EXPECT_EQ(static_cast<std::string>(decimal32(6)), "6");
  EXPECT_EQ(static_cast<std::string>(decimal32(22.22, scale_type{-2})), "22.22");

  decimal32 num1 = decimal32(22.22, scale_type{-2}) / decimal32(2.2, scale_type{-1});
  EXPECT_EQ(static_cast<std::string>(num1), "10.1");

  decimal32 num0 = decimal32(22.22, scale_type{-2}) / decimal32(2.2, scale_type{-2});
  EXPECT_EQ(static_cast<std::string>(num0), "10.1");

  // 22 / 2 == 11
  decimal32 num2 = decimal32(22.22, scale_type{0}) / decimal32(2.2, scale_type{0});
  EXPECT_EQ(static_cast<std::string>(num2), "11"); /// \note not 10, got 11!

  // 22 / 2.2 == 10
  decimal32 num3 = decimal32(22.22, scale_type{0}) / decimal32(2.2, scale_type{-1});
  EXPECT_EQ(static_cast<std::string>(num3), "10"); /// \note not 10.1, got 10!

  // 6.0 / 2.5 == 2.4
  EXPECT_EQ(static_cast<std::string>(decimal64(6.0, scale_type{-1})), "6.0");
  EXPECT_EQ(static_cast<std::string>(decimal64(2.5, scale_type{-1})), "2.5");
  decimal64 num4 = decimal64(6.0, scale_type{-1}) / decimal64(2.5, scale_type{-1});
  EXPECT_EQ(static_cast<double>(num4), 2); /// \note not 2.4, got 2!
  EXPECT_EQ(static_cast<std::string>(num4), "2.4"); /// \note not 2.4, got 2!

  // 6.00 / 2.50 == 2.4
  EXPECT_EQ(static_cast<std::string>(decimal64(6.0, scale_type{-2})), "6.00");
  EXPECT_EQ(static_cast<std::string>(decimal64(2.5, scale_type{-2})), "2.50");
  decimal64 num5 = decimal64(6.0, scale_type{-2});
  num5 /= decimal64(2.5, scale_type{-2});
  EXPECT_EQ(static_cast<double>(num5), 2.4); /// \note not 2.4, got 2!
  EXPECT_EQ(static_cast<std::string>(num5), "2.4"); /// \note not 2.4, got 2!

  // 6.00000 / 2.50 == 2.4
  decimal64 num6 = decimal64(6.0, scale_type{-5});
  EXPECT_EQ(static_cast<std::string>(num6), "6.00000");
  EXPECT_EQ(static_cast<std::string>(decimal64(2.5, scale_type{-2})), "2.50");
  num6 /= decimal64(2.5, scale_type{-2});
  EXPECT_EQ(static_cast<double>(num6), 2.40);
  EXPECT_EQ(static_cast<std::string>(num6), "2.400");
#endif
}

#if TODO
TEST_F(FixedPointTest, CompoundAssignmentDivision)
{
  EXPECT_EQ((decimal32(6) /= decimal32(2)), decimal32(3));
  EXPECT_EQ((decimal64(6) /= decimal64(2)), decimal64(3));
  EXPECT_EQ((decimal64(6) /= decimal64(2.5, scale_type{-1})), decimal64(2.4, scale_type{-1}));

  EXPECT_EQ((decimal32(6.2, scale_type{-1}) /= decimal32(decimal64(2).value())), decimal32(3.1, scale_type{-1}));
  EXPECT_EQ((decimal64(6.2, scale_type{-1}) /= decimal64(decimal32(2).value())), decimal64(3.1, scale_type{-1}));

  EXPECT_EQ(decimal32(22.22, scale_type{-2}) /= decimal32(2.2, scale_type{-1}), decimal32(10.1, scale_type{-1}));
  EXPECT_EQ(decimal64(22.22, scale_type{-2}) /= decimal64(2.2, scale_type{-1}), decimal64(10.1, scale_type{-1}));
}

TEST_F(FixedPointTest, MiscMath)
{
  EXPECT_EQ((decimal32(6) /= decimal32(2)), decimal32(3));
  EXPECT_EQ((decimal64(6) /= decimal64(2)), decimal64(3));
  EXPECT_EQ((decimal64(6) /= decimal64(2.5, scale_type{-1})), decimal64(2.4, scale_type{-1}));

  EXPECT_EQ((decimal32(6.2, scale_type{-1}) /= decimal32(decimal64(2).value())), decimal32(3.1, scale_type{-1}));
  EXPECT_EQ((decimal64(6.2, scale_type{-1}) /= decimal64(decimal32(2).value())), decimal64(3.1, scale_type{-1}));

  EXPECT_EQ(decimal32(22.22, scale_type{-2}) /= decimal32(2.2, scale_type{-1}), decimal32(10.1, scale_type{-1}));
  EXPECT_EQ(decimal64(22.22, scale_type{-2}) /= decimal64(2.2, scale_type{-1}), decimal64(10.1, scale_type{-1}));

  decimal32 num(12);
  EXPECT_EQ(static_cast<std::string>(num), "6");
  EXPECT_EQ(static_cast<int32_t>(num), 6);
  EXPECT_EQ(basic::ceil<int32_t>(num), 6);
  EXPECT_EQ(basic::floor<int32_t>(num), 6);
  EXPECT_EQ(basic::abs<int32_t>(num), 6);

  num /= decimal32(2.5, scale_type{-1});
  EXPECT_EQ(static_cast<std::string>(num), "4.8");
  EXPECT_EQ(static_cast<double>(num), 4.8);
  EXPECT_EQ(basic::ceil<int32_t>(num), 4);
  EXPECT_EQ(basic::floor<int32_t>(num), 4);
  EXPECT_EQ(basic::abs<int32_t>(num), 4);

  num *= decimal32(1.234, scale_type{-3});
  EXPECT_EQ(static_cast<std::string>(num), "5.9232");
  EXPECT_EQ(static_cast<double>(num), 5.9232);
  EXPECT_EQ(basic::ceil<int32_t>(num), 5);
  EXPECT_EQ(basic::floor<int32_t>(num), 5);
  EXPECT_EQ(basic::abs<int32_t>(num), 5);

  num /= decimal32(2, scale_type{0});
  EXPECT_EQ(static_cast<std::string>(num), "2.9616");
  EXPECT_EQ(static_cast<double>(num), 2.9616);
  EXPECT_EQ(basic::ceil<int32_t>(num), 2);
  EXPECT_EQ(basic::floor<int32_t>(num), 2);
  EXPECT_EQ(basic::abs<int32_t>(num), 2);

  num *= decimal32(-2, scale_type{0});
  EXPECT_EQ(static_cast<std::string>(num), "-5.9232");
  EXPECT_EQ(static_cast<double>(num), -5);
  EXPECT_EQ(basic::ceil<int32_t>(num), -5);
  EXPECT_EQ(basic::floor<int32_t>(num), -5);
  EXPECT_EQ(basic::abs<int32_t>(num), -5);
}

TEST_F(FixedPointTest, FixedPointValue)
{
  EXPECT_EQ(decimal64(2).value(), 2);
  EXPECT_EQ(decimal64(122.123456, scale_type{0}).value(), 122);
  EXPECT_EQ(decimal64(122.123456, scale_type{-6}).value(), 122);
  EXPECT_EQ(decimal64(122.123456, scale_type{-3}).value(), 122);
  EXPECT_EQ(decimal64(0.2, scale_type{0}).value(), 0);
  EXPECT_EQ(decimal64(0.2, scale_type{-1}).value(), 0);
}

TEST_F(FixedPointTest, FixedPointScale)
{
  EXPECT_EQ(decimal64(2, scale_type{0}).scale(), 0);
  EXPECT_EQ(decimal64(122.123456, scale_type{-6}).scale(), 0);
  EXPECT_EQ(decimal64(122.123456, scale_type{-3}).scale(), 0);
  EXPECT_EQ(decimal64(0.2, scale_type{0}).scale(), 0);
  EXPECT_EQ(decimal64(0.2, scale_type{-1}).scale(), 2);
}

TEST_F(FixedPointTest, FixedPointUnaryCast)
{
  double result1 = fixed_point_unary_cast<decimal32, double>{scale_type{-2}}.operator()(1243);
  EXPECT_EQ(result1, 12.43);
  int32_t result2 = fixed_point_unary_cast<decimal32, int32_t>{scale_type{0}}.operator()(1243);
  EXPECT_EQ(result2, 1243);
}
#endif

}  // namespace test

}  // namespace basic
