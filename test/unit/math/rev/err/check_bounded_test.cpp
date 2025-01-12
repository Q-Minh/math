#include <stan/math/rev.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <vector>

TEST(AgradRevErrorHandlingScalar, CheckBoundedVarCheckVectorized) {
  using stan::math::check_bounded;
  using stan::math::var;
  using std::vector;

  int N = 5;
  const char* function = "check_bounded";
  vector<var> a;

  for (int i = 0; i < N; ++i)
    a.push_back(var(i));

  size_t stack_size
      = stan::math::ChainableStack::instance()->var_stack_.size()
        + stan::math::ChainableStack::instance()->var_nochain_stack_.size();

  EXPECT_EQ(5U, stack_size);
  EXPECT_NO_THROW(check_bounded(function, "a", a, -1.0, 6.0));

  size_t stack_size_after_call
      = stan::math::ChainableStack::instance()->var_stack_.size()
        + stan::math::ChainableStack::instance()->var_nochain_stack_.size();
  EXPECT_EQ(5U, stack_size_after_call);
  stan::math::recover_memory();
}

TEST(AgradRevErrorHandlingScalar, CheckBounded_X) {
  using stan::math::check_bounded;
  using stan::math::var;

  const char* function = "check_bounded";
  const char* name = "x";
  var x = 0;
  var low = -1;
  var high = 1;

  EXPECT_NO_THROW(check_bounded(function, name, x, low, high))
      << "check_bounded should be TRUE with x: " << x << " and bounds: " << low
      << ", " << high;

  x = low;
  EXPECT_NO_THROW(check_bounded(function, name, x, low, high))
      << "check_bounded should be TRUE with x: " << x
      << " equal to the lower bound: " << low;

  x = high;
  EXPECT_NO_THROW(check_bounded(function, name, x, low, high))
      << "check_bounded should be TRUE with x: " << x
      << " equal to the lower bound: " << low;

  x = low - 1;
  EXPECT_THROW(check_bounded(function, name, x, low, high), std::domain_error)
      << "check_bounded should throw with x: " << x << " and bounds: " << high
      << ", " << low;

  x = high + 1;
  EXPECT_THROW(check_bounded(function, name, x, low, high), std::domain_error)
      << "check_bounded should throw with x: " << x << " and bounds: " << high
      << ", " << low;

  x = std::numeric_limits<var>::quiet_NaN();
  EXPECT_THROW(check_bounded(function, name, x, low, high), std::domain_error)
      << "check_bounded should throw with x: " << x << " and bounds: " << high
      << ", " << low;

  x = -std::numeric_limits<var>::infinity();
  EXPECT_THROW(check_bounded(function, name, x, low, high), std::domain_error)
      << "check_bounded should throw with x: " << x << " and bounds: " << high
      << ", " << low;

  x = std::numeric_limits<var>::infinity();
  EXPECT_THROW(check_bounded(function, name, x, low, high), std::domain_error)
      << "check_bounded should throw with x: " << x << " and bounds: " << high
      << ", " << low;
  stan::math::recover_memory();
}

TEST(AgradRevErrorHandlingScalar, CheckBounded_Low) {
  using stan::math::check_bounded;
  using stan::math::var;

  const char* function = "check_bounded";
  const char* name = "x";
  var x = 0;
  var low = -1;
  var high = 1;

  EXPECT_NO_THROW(check_bounded(function, name, x, low, high))
      << "check_bounded should be true x: " << x << " and bounds: " << low
      << ", " << high;

  low = -std::numeric_limits<var>::infinity();
  EXPECT_NO_THROW(check_bounded(function, name, x, low, high))
      << "check_bounded should be TRUE with x: " << x << " and bounds: " << low
      << ", " << high;

  low = std::numeric_limits<var>::quiet_NaN();
  EXPECT_THROW(check_bounded(function, name, x, low, high), std::domain_error)
      << "check_bounded should throw with x: " << x << " and bounds: " << low
      << ", " << high;

  low = std::numeric_limits<var>::infinity();
  EXPECT_THROW(check_bounded(function, name, x, low, high), std::domain_error)
      << "check_bounded should throw with x: " << x << " and bounds: " << low
      << ", " << high;
  stan::math::recover_memory();
}
TEST(AgradRevErrorHandlingScalar, CheckBounded_High) {
  using stan::math::check_bounded;
  using stan::math::var;

  const char* function = "check_bounded";
  const char* name = "x";
  var x = 0;
  var low = -1;
  var high = 1;

  EXPECT_NO_THROW(check_bounded(function, name, x, low, high))
      << "check_bounded should be true x: " << x << " and bounds: " << low
      << ", " << high;

  high = std::numeric_limits<var>::infinity();
  EXPECT_NO_THROW(check_bounded(function, name, x, low, high))
      << "check_bounded should be TRUE with x: " << x << " and bounds: " << low
      << ", " << high;

  high = std::numeric_limits<var>::quiet_NaN();
  EXPECT_THROW(check_bounded(function, name, x, low, high), std::domain_error)
      << "check_bounded should throw with x: " << x << " and bounds: " << low
      << ", " << high;

  high = -std::numeric_limits<var>::infinity();
  EXPECT_THROW(check_bounded(function, name, x, low, high), std::domain_error)
      << "check_bounded should throw with x: " << x << " and bounds: " << low
      << ", " << high;
  stan::math::recover_memory();
}

TEST(AgradRevErrorHandlingScalar, CheckBoundedVarCheckUnivariate) {
  using stan::math::check_bounded;
  using stan::math::var;

  const char* function = "check_bounded";
  var a(5.0);

  size_t stack_size
      = stan::math::ChainableStack::instance()->var_stack_.size()
        + stan::math::ChainableStack::instance()->var_nochain_stack_.size();

  EXPECT_EQ(1U, stack_size);
  EXPECT_NO_THROW(check_bounded(function, "a", a, 4.0, 6.0));

  size_t stack_size_after_call
      = stan::math::ChainableStack::instance()->var_stack_.size()
        + stan::math::ChainableStack::instance()->var_nochain_stack_.size();
  EXPECT_EQ(1U, stack_size_after_call);

  stan::math::recover_memory();
}
