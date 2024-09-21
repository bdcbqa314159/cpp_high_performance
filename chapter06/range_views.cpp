#include <version>
#if defined(__cpp_lib_ranges)

#include <gtest/gtest.h>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

TEST(RangeViews, Generatingviews) {
  for (auto i : std::views::iota(-2, 2)) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}

TEST(RangeViews, TransformingViews) {
  auto csv = std::string{"10,11,12"};
  auto digits = csv | std::views::split(',') | std::views::join;

  for (auto i : digits) {
    std::cout << i;
  }
  std::cout << "\n";
}

TEST(RangeViews, SamplingViews) {
  auto vec = std::vector{1, 2, 3, 4, 5, 4, 3, 2, 1};
  auto v = vec | std::views::drop_while([](auto i) { return i < 5; }) |
           std::views::take(3);

  for (const auto &i : v) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}

TEST(RangeViews, UtilityViews) {
  auto ifs = std::istringstream{"1.4142 1.618 2.71828 3.14159 6.283"};

  for (auto f : std::ranges::istream_view<float>(ifs)) {
    std::cout << f << "\n";
  }
  std::cout << "\n";
}

#endif
