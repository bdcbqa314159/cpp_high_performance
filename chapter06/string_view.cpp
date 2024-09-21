#include <string_view>
#include <version>
#if defined(__cpp_lib_ranges)

// #include "to_vector.hpp"
#include <cstring>
#include <gtest/gtest.h>
#include <ranges>
#include <vector>

/* -- this code does not work neither with gcc 14 neither with llvm 18
namespace {
auto split(std::string_view s, char delim) {
  const auto to_string = [](auto &&r) -> std::string {
    const auto cv = std::ranges::common_view{r};
    return {cv.begin(), cv.end()};
  };
  const auto v =
      std::ranges::split_view{s, delim} | std::views::transform(to_string);
  return to_vector(v);
}
} // namespace
*/

std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

std::vector<std::string> split_1(const std::string &s, char delimiter) {
  auto splitView = std::ranges::views::split(s, delimiter) |
                   std::ranges::views::transform([](const auto &subrange) {
                     return std::string_view(subrange.begin(), subrange.end());
                   });
  std::vector<std::string> splitText;
  for (const std::string_view &w : splitView)
    splitText.push_back(std::string(w));

  return splitText;
}

TEST(StringView, Split) {
  const char *c_str = "ABC,DEF,GHI";

  const auto v1 = split(c_str, ',');

  const auto s = std::string{"ABC,DEF,GHI"};
  const auto v2 = split(s, ',');

  ASSERT_EQ(v1, v2);
}

TEST(StringView, Split_1) {
  const char *c_str = "ABC,DEF,GHI";

  const auto v1 = split_1(c_str, ',');

  const auto s = std::string{"ABC,DEF,GHI"};
  const auto v2 = split_1(s, ',');

  ASSERT_EQ(v1, v2);
}

#endif
