#include <version>
#if defined(__cpp_lib_barrier)

#include <algorithm>
#include <array>
#include <barrier>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

auto random_int(int min, int max) {
  thread_local static auto engine =
      std::default_random_engine{std::random_device{}()};
  auto dist = std::uniform_int_distribution<>{min, max};
  return dist(engine);
}

TEST(Barriers, ForkJoin) {
  constexpr auto n = 5;

  auto done = false;
  auto dice = std::array<int, n>{};
  auto threads = std::vector<std::thread>{};
  auto n_turns = 0;

  auto check_result = [&] {
    ++n_turns;
    auto is_six = [](auto i) { return i == 6; };
    done = std::all_of(dice.begin(), dice.end(), is_six);
  };

  auto bar = std::barrier{n, check_result};
  for (int i = 0; i < n; ++i) {
    threads.emplace_back([&, i] {
      while (!done) {
        dice[i] = random_int(1, 6);
        bar.arrive_and_wait();
      }
    });
  }
  for (auto &&t : threads)
    t.join();

  std::cout << n_turns << "\n";
}

#endif
