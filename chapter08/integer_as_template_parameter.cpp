#include <gtest/gtest.h>

template <int N, typename T> auto const_pow_n(const T &v) {
  auto product = T{1};
  for (int i = 0; i < N; ++i) {
    product *= v;
  }
  return product;
}

template <> auto const_pow_n<2, int>(const int &v) { return v * v; }

TEST(IntegerAsTemplateParameter, ConstPowN) {
  auto x2 = const_pow_n<2>(4.f);
  ASSERT_FLOAT_EQ(16.f, x2);

  auto x3 = const_pow_n<3>(4.f);
  ASSERT_FLOAT_EQ(64.f, x3);
}

TEST(IntegerAsTemplateParameter, TemplateSpecialization) {
  auto x2 = const_pow_n<2>(4);
  ASSERT_EQ(16, x2);
  auto x3 = const_pow_n<3>(4);
  ASSERT_EQ(64, x3);
}
