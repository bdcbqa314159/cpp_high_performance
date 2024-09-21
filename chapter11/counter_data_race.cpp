#include <cassert>
#include <gtest/gtest.h>
#include <iostream>
#include <thread>

namespace {

int counter = 0;

auto increment_counter(int n) {
  for (int i = 0; i < n; ++i)
    ++counter;
}
} // namespace

TEST(CounterDataRace, IncrementCounter) {
  const auto n_times = 1000000;
  std::thread t1(increment_counter, n_times);
  std::thread t2(increment_counter, n_times);

  t1.join();
  t2.join();

  std::cout << counter << "\n";
}
