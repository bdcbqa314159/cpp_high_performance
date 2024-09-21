#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>

#include <gtest/gtest.h>

TEST(Pair, MinMax) {
  std::pair<int, int> v = std::minmax({4, 3, 2, 4, 5, 1});
  std::cout << v.first << " " << v.second << "\n";
}

TEST(Pair, Map) {
  auto scores = std::map<std::string, int>{};
  scores.insert(std::pair{"Neo", 12});
  scores.emplace("Tri", 45);
  scores.emplace("Ari", 33);

  for (auto &&it : scores) {
    auto key = it.first;
    auto val = it.second;
    std::cout << key << " " << val << "\n";
  }
}

TEST(Pair, MapInitializerListAndStructuredBindings) {
  auto scores =
      std::map<std::string, int>{{"Neo", 12}, {"Tri", 45}, {"Ari", 33}};

  for (auto &&[key, val] : scores) {

    std::cout << key << " " << val << "\n";
  }
}
