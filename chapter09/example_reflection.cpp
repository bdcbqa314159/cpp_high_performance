#include "example_reflection.hpp"
#include <sstream>
#include <string>

#include <gtest/gtest.h>

namespace {

auto &operator<<(std::ostream &ostr, const Player &p) {
  tuple_for_each(p.reflect(), [&ostr](const auto &m) { ostr << m << " "; });
  return ostr;
}
} // namespace

TEST(Reflection, StreamOperator) {
  auto v = Player{"Kai", 4, 2568};
  std::cout << v;

  auto os = std::ostringstream{};
  os << v;
  ASSERT_EQ("Kai 4 2568 ", os.str());
}
