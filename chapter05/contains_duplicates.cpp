#include <algorithm>
#include <cassert>
#include <gtest/gtest.h>
#include <type_traits>
#include <vector>

template <typename Iterator>
auto constains_duplicate_n2(Iterator begin, Iterator end) {
  for (auto it = begin; it != end; ++it)
    if (std::find(std::next(it), end, *it) != end)
      return true;
  return false;
}

template <typename Iterator>
auto contains_duplicate_allocating(Iterator first, Iterator last) {
  using ValueType = std::decay_t<decltype(*first)>;
  auto copy = std::vector<ValueType>(first, last);
  std::sort(copy.begin(), copy.end());

  return std::adjacent_find(copy.begin(), copy.end()) != copy.end();
}

TEST(ContainsDuplicates, Examples) {
  auto vals = std::vector{1, 4, 2, 5, 3, 6, 4, 7, 5, 8, 6, 9, 0};
  auto a = constains_duplicate_n2(vals.begin(), vals.end());
  ASSERT_TRUE(a);
  auto b = contains_duplicate_allocating(vals.begin(), vals.end());
  ASSERT_TRUE(b);
}
