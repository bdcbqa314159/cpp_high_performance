#include <version>
#if defined(__cpp_lib_latch)

#include <array>
#include <gtest/gtest.h>
#include <iostream>
#include <latch>
#include <thread>
#include <vector>

void prefault_stack() {
  constexpr auto stack_size = 500u * 1024u;
  volatile unsigned char mem[stack_size];
  std::fill(std::begin(mem), std::end(mem), 0);
}

void do_work() { std::cout << "Thread is working\n"; }

TEST(Latches, PrefaultStack) {
  constexpr auto n_threads = 2;
  auto initialized = std::latch{n_threads};
  auto threads = std::vector<std::thread>{};
  for (auto i = 0; i < n_threads; ++i) {
    threads.emplace_back([&] {
      prefault_stack();
      initialized.arrive_and_wait();
      do_work();
    });
  }

  initialized.wait();
  std::cout << "Threads have been initialized, starting to work\n";
  for (auto &&t : threads)
    t.join();
}

#endif
