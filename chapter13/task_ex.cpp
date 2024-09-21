#include "entry_point.hpp"
#ifdef SUPPORTS_COROUTINES

#include "sync_wait.hpp"
#include "task.hpp"
#include <gtest/gtest.h>

#include <iostream>

namespace {

Task<int> height() { co_return 20; }
Task<int> width() { co_return 30; }
Task<int> area() {
  auto h = co_await height();
  auto w = co_await width();
  co_return h *w;
}
} // namespace

TEST(TaskEx, Area) {
  auto a = area();
  //  auto x = sync_wait<Task<int> &>(a);
  auto x = sync_wait(a);
  std::cout << x << "\n";
}

#endif
