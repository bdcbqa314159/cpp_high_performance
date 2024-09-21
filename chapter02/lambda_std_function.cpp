#include <cassert>
#include <functional>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

TEST(StdFunction, FunctionalCall) {
  auto func = std::function<void(int)>{};
  func = [](int v) { std::cout << v; };
  func(12);

  auto forty_two = 42;
  func = [forty_two](int v) { std::cout << (v + forty_two); };
  func(12);
}

class Button {
public:
  Button(std::function<void(void)> click) : handler_{click} {}
  auto on_click() const { handler_(); }

private:
  std::function<void(void)> handler_{};
};

auto create_buttons() {
  auto beep = Button([counter = 0]() mutable {
    std::cout << "Beep: " << counter << "!";
    ++counter;
  });

  auto bop = Button([] { std::cout << "Bop. "; });
  auto silent = Button([] {});

  return std::vector<Button>{beep, bop, silent};
}

TEST(StdFunction, Buttons) {
  const auto &buttons = create_buttons();
  for (const auto &b : buttons) {
    b.on_click();
  }

  buttons.front().on_click();
}
