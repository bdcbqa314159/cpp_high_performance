#include "entry_point.hpp"
#ifdef SUPPORTS_COROUTINES

#include "generator.hpp"
#include <gtest/gtest.h>

#include <limits>

Generator<int> iota(int start) {
  for (int i = start; i < std::numeric_limits<int>::max(); ++i) {
    co_yield i;
  }
}

Generator<int> take_until(Generator<int> &gen, int value) {
  for (auto v : gen) {
    if (v == value)
      co_return;
    co_yield v;
  }
}

TEST(GeneratorIntialExample, IotaAndTakeUntil) {
  auto i = iota(2);
  auto t = take_until(i, 5);
  for (auto v : t)
    std::cout << v << ", ";

  std::cout << "\n";
}

#endif
