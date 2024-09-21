#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <iostream>

auto func(std::byte *stack_bottom_addr) -> void {
  std::byte data[1024];
  std::cout << stack_bottom_addr - data << "\n";
  func(stack_bottom_addr);
}

TEST(StackSize, StackOverFlow) {
  ASSERT_DEATH_IF_SUPPORTED(
      {
        std::byte b;
        func(&b);
      },
      "");
}
