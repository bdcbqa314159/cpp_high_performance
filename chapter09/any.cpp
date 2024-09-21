#include <any>
#include <gtest/gtest.h>
#include <iostream>

TEST(Any, VectorOfAny) {
  auto container = std::vector<std::any>{42, "hi", true};
  for (const auto &a : container) {
    if (a.type() == typeid(int)) {
      const auto &value = std::any_cast<int>(a);
      std::cout << value << "\n";
    } else if (a.type() == typeid(const char *)) {
      const auto &value = std::any_cast<const char *>(a);
      std::cout << value << "\n";
    } else if (a.type() == typeid(bool)) {
      const auto &value = std::any_cast<bool>(a);
      std::cout << value << "\n";
    } else {
      std::cout << "unknown case\n";
    }
  }
}
