#include "example_reflection.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

namespace {

template <typename T>
concept Reflectable = requires(T &t) { t.reflect(); };

template <Reflectable R> auto &operator<<(std::ostream &os, const R &v) {
  tuple_for_each(v.reflect(), [&os](const auto &m) { os << m << " "; });
  return os;
}
} // namespace

TEST(Reflection, Concepts) {
  auto kai = Player{"Kai", 48, 2568};
  auto ari = Player{"Ari", 2, 1068};
  std::cout << kai;
  std::cout << "\n";
  std::cout << ari;
  std::cout << "\n";

  auto os = std::ostringstream{};
  os << kai;

  ASSERT_EQ("Kai 48 2568 ", os.str());
}
