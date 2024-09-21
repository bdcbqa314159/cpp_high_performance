#include "entry_point.hpp"
#ifdef SUPPORTS_COROUTINES

#include "lin_value.hpp"
#include <gtest/gtest.h>

#include <sstream>
#include <vector>

namespace {

template <typename T> auto lin_space(T start, T stop, size_t n) {
  auto v = std::vector<T>{};
  for (auto i = 0u; i < n; ++i)
    v.push_back(lin_value(start, stop, i, n));

  return v;
}

} // namespace

TEST(LinSpaceCoroutine, Example) {
  for (auto v : lin_space(2., 3., 5))
    std::cout << v << ", ";

  std::ostringstream os;
  for (auto v : lin_space(2., 3., 5))
    os << v << ", ";
  ASSERT_EQ("2, 2.25, 2.5, 2.75, 3, ", os.str());
}

#endif
