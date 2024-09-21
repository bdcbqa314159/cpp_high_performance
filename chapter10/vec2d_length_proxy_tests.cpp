#include <version>
#if defined(__cpp_lib_ranges)

#include "vec2d_length_proxy.hpp"
#include <gtest/gtest.h>
// #include <ranges>
#include <vector>

template <typename T> auto min_length(const T &r) -> float {
  assert(!r.empty());
  auto cmp = [](auto &&a, auto &&b) { return a.length() < b.length(); };

  auto it = std::ranges::min_element(r, cmp);
  return it->length();
}

TEST(lengthProxy, MinLength) {
  auto v = std::vector<Vec2D>{{7.f, 5.f}, {3.f, 4.f}, {9.f, 9.f}};

  auto x = min_length(v);
  ASSERT_FLOAT_EQ(x, 5.f);
}

#endif
