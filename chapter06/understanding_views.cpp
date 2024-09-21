#include <version>
#if defined(__cpp_lib_ranges)

#include <algorithm>
#include <gtest/gtest.h>
#include <ranges>
#include <vector>

TEST(UnderstandingViews, LazyEvaluation) {
  auto numbers = std::vector{1, 2, 3, 4};
  auto square = [](auto v) { return v * v; };
  auto squared_view = std::views::transform(numbers, square);
  for (auto s : squared_view) {
    std::cout << s << " ";
  }

  std::cout << "\n";
}

TEST(UnderstandingViews, FilterViews) {
  auto v = std::vector{4, 5, 6, 7, 6, 5, 4};
  auto odd_view = std::views::filter(v, [](auto i) { return (i % 2) == 1; });

  for (auto odd_number : odd_view) {
    std::cout << odd_number << " ";
  }
  std::cout << "\n";
}

// #if defined(__clang__) && not defined(__apple_build_version__)
TEST(UnderstandingViews, FlattenAndJoin) {
  auto list_of_lists =
      std::vector<std::vector<int>>{{1, 2}, {3, 4, 5}, {5}, {4, 3, 2, 1}};
  auto flattened_view = std::views::join(list_of_lists);
  for (auto v : flattened_view) {
    std::cout << v << " ";
  }

  std::cout << "\n";

  auto max_value = *std::ranges::max_element(flattened_view);

  ASSERT_EQ(max_value, 5);
}
// #endif

#endif
