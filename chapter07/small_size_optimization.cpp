#include <cstddef>
#include <gtest/gtest.h>
#include <iostream>

extern size_t allocated;

auto print_string_mem(const char *chars) {
  size_t allocated = 0;
  auto s = std::string(chars);
  std::cout << "stack space = " << sizeof(s) << ", heap space = " << allocated
            << ", capacity = " << s.capacity() << "\n";
}

class SmallSizeOptimization : public ::testing::Test {
protected:
  void SetUp() override { size_t allocated = 0; }
};

TEST_F(SmallSizeOptimization, StringMemory) {
  print_string_mem("");
  print_string_mem("1234567890123456789012");
  print_string_mem("12345678901234567890123");
}
