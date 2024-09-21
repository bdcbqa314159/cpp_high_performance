#include <cstddef>
#include <version>
#if defined(__cpp_lib_execution) && defined(__cpp_lib_parallel_algorithm)

#include <gtest/gtest.h>

#include <algorithm>
#include <execution>
#include <numeric>
#include <string>
#include <vector>

TEST(ParallePolicy, DataRaceWithForEach) {
  auto std::vector<std::string>{"Ada", "APL"};
  auto tot_size = size_t{0};
  std::for_each(std::execution::par, v.begin(), v.end(),
                [&](const auto &s) { toto_size += s.size(); });
}

TEST(ParallelPolicy, Reduce) {
  auto v = std::vector<std::string>{"Ada", "APL"};
#ifdef _MSC_VER
  // Workaround as std::reduce and std::execution::par does not compile at the
  // time of writing this
  constexpr auto policy = std::execution::seq;
#else
  constexpr auto policy = std::execution::par;
#endif

  auto tot_size =
      std::reduce(policy, v.begin(), v.end(), size_t{0},
                  [](auto i, const auto &s) { return i + s.size(); });
  (void)(tot_size);
}

#endif
