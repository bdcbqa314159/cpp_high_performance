#include <algorithm>
#include <gtest/gtest.h>
#include <numeric>

TEST(ReduceForeach, TransformReduce) {
  const auto v = std::vector<std::string>{"Ada", "Bash", "C++"};
  auto num_chars = std::transform_reduce(
      v.begin(), v.end(), size_t{0}, [](size_t a, size_t b) { return a + b; },
      [](const std::string &s) { return s.size(); });
  ASSERT_EQ(num_chars, 10);
}

TEST(ReduceForeach, ForEachFunctor) {
  struct Func {
    void operator()(const std::string &s) { res += s; };
    std::string res{};
  };

  auto v = std::vector<std::string>{"A", "B", "C"};
  auto s = std::for_each(v.begin(), v.end(), Func{}).res;

  ASSERT_EQ(s, "ABC");
}
