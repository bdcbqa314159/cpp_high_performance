#include <cassert>
#include <gtest/gtest.h>
#include <iostream>
#include <mutex>
#include <thread>

namespace {

int counter = 0;
std::mutex counter_mutex{};

void increment_counter(int n) {
  for (int i = 0; i < n; ++i) {
    auto lock = std::scoped_lock{counter_mutex};
    ++counter;
  }
}
} // namespace

TEST(CounterMutex, IncrementCounter) {
  const int n = 1000000;
  std::thread t1(increment_counter, n);
  std::thread t2(increment_counter, n);

  t1.join();
  t2.join();

  std::cout << counter << "\n";
  ASSERT_EQ(n * 2, counter);
}
