#include "entry_point.hpp"
#include <coroutine>

#ifdef SUPPORTS_COROUTINES

#include "resumable.hpp"
#include <gtest/gtest.h>

#include <thread>

namespace {

Resumable coroutine() {
  std::cout << "c1 ";
  co_await std::suspend_always{};
  std::cout << "c2 ";
}

auto coro_factory() {
  auto res = coroutine();
  return res;
}
} // namespace
TEST(PassingCoroutinesAround, ResumeFromDifferentThread) {
  auto r = coro_factory();
  r.resume(); // Resume from main

  auto t = std::thread{[r = std::move(r)]() mutable {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    r.resume(); // Resume from thread
  }};
  t.join();
}

#endif
