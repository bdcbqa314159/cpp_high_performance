#include <gtest/gtest.h>

#ifndef _MSC_VER
auto pow_n(const auto &v, int n) {
  auto product = decltype(v){1};
  for (int i = 0; i < n; ++i) {
    product *= v;
  }
  return product;
}

TEST(AbbreviatedFunctionTemplates, PowN) {
  auto x = pow_n(3, 3);
  ASSERT_EQ(27, x);
  ASSERT_EQ(typeid(int), typeid(x));
}
#endif

TEST(AbbreviatedFunctionTemplates, ExplicitTemplateParameters) {
  auto pow_n_func = []<class T>(const T &v, int n) {
    auto product = T{1};
    for (int i = 0; i < n; ++i) {
      product *= v;
    }
    return product;
  };

  auto x = pow_n_func(3, 3);
  ASSERT_EQ(27, x);
  ASSERT_EQ(typeid(int), typeid(x));
}
