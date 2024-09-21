#include <stdexcept>
#if _MSC_VER
#pragma warning(disable : 4244)
#endif

#include <gtest/gtest.h>

#include <future>
#include <thread>

namespace {

int divide(int a, int b) {
  if (b == 0)
    throw std::runtime_error{"Divide by zero exception"};

  return a / b;
}

} // namespace

TEST(Tasks, Divide) {
  std::packaged_task<decltype(divide)> task(divide);
  auto f = task.get_future();
  std::thread t(std::move(task), 45, 5);
  auto result = int{};
  ASSERT_NO_THROW({ result = f.get(); });
  ASSERT_EQ(45 / 5, result);
  t.join();
}
