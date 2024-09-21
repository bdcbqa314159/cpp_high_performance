#include <gtest/gtest.h>

TEST(LambdaTypes, StatelessLambda) {
  auto x = [] {};
  auto y = x;
  decltype(y) z;
  static_assert(std::is_same_v<decltype(x), decltype(y)>);
  static_assert(std::is_same_v<decltype(x), decltype(z)>);
}
