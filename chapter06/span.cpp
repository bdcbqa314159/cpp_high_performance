#include <version>
#if defined(__cpp_lib_ranges)

#include <algorithm>
#include <gtest/gtest.h>
#include <ranges>
#include <span>
#include <vector>

namespace {
auto reset(std::span<int> values, int n) {
  for (auto &i : std::ranges::take_view{values, n}) {
    i = int{};
  }
}
} // namespace

TEST(Span, ResetArray) {
  int a[]{33, 44, 55, 66, 77};
  reset(a, 3);

  int result[]{0, 0, 0, 66, 77};

  ASSERT_EQ(sizeof(result), sizeof(a));
  const int n = sizeof(a) / sizeof(*a);

  ASSERT_TRUE(std::equal(a, a + n, result));
}

TEST(Span, ResetVector) {
  auto v = std::vector{33, 44, 55, 66, 77};
  reset(v, 2);

  auto result = std::vector{0, 0, 55, 66, 77};

  ASSERT_EQ(v, result);
}

#endif
