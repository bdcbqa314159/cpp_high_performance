#if _MSC_VER
#pragma warning(disable : 4244)
#endif

#include <cmath>
#include <gtest/gtest.h>
#include <type_traits>

template <typename T> auto generic_mod(const T &v, const T &n) -> T {
  assert(n != 0);
  if (std::is_floating_point_v<T>)
    return std::fmod(v, n);
  else
    return v % n;
}

template <typename T>
auto constexpr_if_generic_mod(const T &v, const T &n) -> T {
  assert(n != 0);
  if constexpr (std::is_floating_point_v<T>)
    return std::fmod(v, n);
  else
    return v % n;
}

TEST(ConstexprIfMod, ModOfInts) {
  auto const value = 7;
  auto const modulus = 5;
  auto const result = generic_mod(value, modulus);

  auto const constexpr_if_result = constexpr_if_generic_mod(value, modulus);
  ASSERT_EQ(constexpr_if_result, result);
}

TEST(ConstexprIfMod, ModOfFloats) {
  auto const value = 1.5f;
  auto const modulus = 1.0f;

  auto const constexpr_if_result = constexpr_if_generic_mod(value, modulus);
  ASSERT_FLOAT_EQ(0.5f, constexpr_if_result);
}
