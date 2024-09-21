#include <array>
#include <gtest/gtest.h>

constexpr auto kL1CacheCapacity = 32768u;
constexpr auto kSize = kL1CacheCapacity / sizeof(int);
using MatrixType = std::array<std::array<int, kSize>, kSize>;

auto cache_trashing_fast(MatrixType &matrix) {
  auto counter = 0;
  for (auto i = 0u; i < kSize; ++i) {
    for (auto j = 0u; j < kSize; ++j) {
      matrix[i][j] = counter++;
    }
  }
}

auto cache_trashing_slow(MatrixType &matrix) {
  auto counter = 0;
  for (auto i = 0u; i < kSize; ++i) {
    for (auto j = 0u; j < kSize; ++j) {
      matrix[j][i] = counter++;
    }
  }
}

MatrixType m{};

TEST(CacheThrashing, Fast) { cache_trashing_fast(m); }
TEST(CacheThrashing, Slow) { cache_trashing_slow(m); }
