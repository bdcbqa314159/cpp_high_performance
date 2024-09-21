#include <cstddef>
#include <vector>
#include <version>

// #if defined(__cpp_lib_memory_ressources)

#include <array>
#include <iostream>
#include <memory_resource>
#include <set>

#include <gtest/gtest.h>

TEST(PolymorphicMemoryAllocators, MonotonicBuffer) {
  auto buffer = std::array<std::byte, 512>{};
  auto ressource = std::pmr::monotonic_buffer_resource{
      buffer.data(), buffer.size(), std::pmr::new_delete_resource()};

  auto unique_numbers = std::pmr::set<int>{&ressource};

  unique_numbers.insert(7);
  unique_numbers.insert(3);
  unique_numbers.insert(2);
  unique_numbers.insert(7);
  unique_numbers.insert(2);

  for (const auto &number : unique_numbers)
    std::cout << number << "\n";
}

class PrintingRessource : public std::pmr::memory_resource {

public:
  PrintingRessource() : res_{std::pmr::get_default_resource()} {}

private:
  void *do_allocate(std::size_t bytes, std::size_t alignement) override {
    std::cout << "allocate: " << bytes << "\n";
    return res_->allocate(bytes, alignement);
  }

  void do_deallocate(void *p, std::size_t bytes,
                     std::size_t alignement) override {
    std::cout << "deallocate: " << bytes << "\n";
    return res_->deallocate(p, bytes, alignement);
  }

  bool
  do_is_equal(const std::pmr::memory_resource &other) const noexcept override {
    return (this == &other);
  }

  std::pmr::memory_resource *res_{};
};

TEST(PolymorphicMemoryAllocators, CustomMemoryResource) {
  auto res = PrintingRessource{};
  auto vec = std::pmr::vector<int>{&res};

  vec.emplace_back(1);
  vec.emplace_back(2);
}

// #endif
