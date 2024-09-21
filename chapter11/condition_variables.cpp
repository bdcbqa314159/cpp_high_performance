#include <gtest/gtest.h>

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

namespace {

auto cv = std::condition_variable{};
auto q = std::queue<int>{};
auto mtx = std::mutex{};

constexpr int sentinel = -1;

std::vector<int> result{};

void print_ints() {
  auto i = int{0};
  while (i != sentinel) {
    {
      auto lock = std::unique_lock<std::mutex>{mtx};
      while (q.empty())
        cv.wait(lock);

      i = q.front();
      q.pop();
    }
    if (i != sentinel) {
      std::cout << "Got: " << i << "\n";
      result.push_back(i);
    }
  }
}

auto generate_ints() {
  for (auto i : {1, 2, 3, sentinel}) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
      auto lock = std::scoped_lock{mtx};
      q.push(i);
    }
    cv.notify_one();
  }
}

} // namespace

TEST(ConditionVariables, ProduceConsumer) {
  std::thread produces(generate_ints);
  std::thread consumer(print_ints);

  produces.join();
  consumer.join();

  ASSERT_EQ(std::vector<int>({1, 2, 3}), result);
}
