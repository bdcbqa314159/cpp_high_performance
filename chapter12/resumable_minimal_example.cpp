#include "entry_point.hpp"
#include <coroutine>
#ifdef SUPPORTS_COROUTINES

#include "resumable.hpp"
#include <gtest/gtest.h>

auto coroutine() -> Resumable {
  std::cout << "3 ";
  co_await std::suspend_always{};
  std::cout << "5 ";
}

TEST(ResumableMinimalExample, ResumCoroutine) {
  std::cout << "1 ";
  auto resumable = coroutine();
  std::cout << "2 ";
  resumable.resume();
  std::cout << "4 ";
  resumable.resume();
  std::cout << "6 ";
}

#endif
