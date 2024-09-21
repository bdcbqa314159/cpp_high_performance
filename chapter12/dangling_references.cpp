#include "entry_point.hpp"
#include <coroutine>
#ifdef SUPPORTS_COROUTINES

#include "resumable.hpp"
#include <gtest/gtest.h>
#include <version>

#include <iostream>
#include <string>

namespace {

auto coroutine_ref(const std::string &str) -> Resumable {
  std::cout << str;
  co_return;
}

auto coro_factory_ref() {
  auto str = std::string{"ABC"};
  auto res = coroutine_ref(str);
  return res;
}

auto coroutine(std::string str) -> Resumable {
  std::cout << str;
  co_return;
}

auto coro_factory() {
  auto str = std::string{"ABC"};
  auto res = coroutine(str);
  return res;
}

auto lambda_factory() {
  auto str = std::string{"ABC"};
  auto lambda = [&str]() { std::cout << str; };
  return lambda;
}
} // namespace

TEST(DanglingReferences, CoroutineWithStringReference) {
  auto coro = coro_factory_ref();
}

TEST(DanglingReferences, CoroutineWithStringValue) {
  auto coro = coro_factory();
  coro.resume();
}

namespace {

struct Widget {
  auto coroutine() -> Resumable {
    std::cout << i++ << " ";
    co_await std::suspend_always{};
    std::cout << i++ << " ";
  }
  int i{};
};

auto widget_coro_factory() {
  auto w = Widget{};
  auto coro = w.coroutine();
  return coro;
}
} // namespace

TEST(DanglingReferences, WidgetMemberFunction) {
  auto w = Widget{99};
  auto coro = w.coroutine();
  coro.resume();
  coro.resume();
}

TEST(DanglingReferences, WidgetMemberFunctionUndefinedBehavior) {
  auto r = widget_coro_factory();
}

TEST(DanglingReferences, CoroutineLambdaOK) {
  auto lambda = [](int i) -> Resumable {
    std::cout << i;
    co_return;
  };
  auto coro = lambda(42);
  coro.resume();
}

TEST(DanglingReferences, CoroutineLambdaUndefinedBehavior) {
  auto coro = [i = 0]() mutable -> Resumable {
    std::cout << i++;
    co_await std::suspend_always{};
    std::cout << i++;
  }();
}

#endif
