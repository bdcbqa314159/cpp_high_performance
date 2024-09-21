#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>

bool is_aligned(void *ptr, std::size_t alignement) {
  assert(ptr != nullptr);

  auto s = std::numeric_limits<std::size_t>::max();

  auto *aligned_ptr = ptr;
  std::align(alignement, 1, aligned_ptr, s);
  return ptr == aligned_ptr;
}

TEST(Alignement, PointerAddress) {
  auto *p = new char{};
  auto max_alignement = alignof(std::max_align_t);
  ASSERT_TRUE(is_aligned(p, max_alignement));
}

TEST(Alignement, SingleByteAllocation) {
  auto *p1 = new char{};
  auto *p2 = new char{};
  auto a1 = reinterpret_cast<std::uintptr_t>(p1);
  auto a2 = reinterpret_cast<std::uintptr_t>(p2);

  std::cout << "Num bytes between p1 and p2: " << a2 - a1 << "\n";
}

struct alignas(64) CacheLine {
  std::byte data[64];
};

TEST(Alignement, CacheLine) {
  auto x = CacheLine{};
  auto y = CacheLine{};

  ASSERT_TRUE(is_aligned(&x, 64));
  ASSERT_TRUE(is_aligned(&y, 64));

  auto *p = new CacheLine{};
  ASSERT_TRUE(is_aligned(p, 64));
}

TEST(Alignement, Aligned) {
  constexpr auto ps = std::size_t{4096};
  struct alignas(ps) Page {
    std::byte data_[ps];
  };

  auto *page = new Page{};
  ASSERT_TRUE(is_aligned(page, ps));
  delete page;
}
