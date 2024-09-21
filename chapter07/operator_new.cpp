#include <gtest/gtest.h>
#include <iostream>

auto allocated = size_t{};
auto print_allocation = bool{false};

void *operator new(size_t isize) {
  void *p = std::malloc(isize);

  if (print_allocation)
    std::cout << "allocated " << isize << " byte(s)" << "\n";

  allocated += isize;

  return p;
}

void operator delete(void *p) noexcept {
  if (print_allocation)
    std::cout << "deleted memory" << "\n";

  std::free(p);
}

void operator delete(void *p, std::size_t) noexcept { operator delete(p); }

auto operator new[](size_t isize) -> void * {
  void *p = std::malloc(isize);
  if (print_allocation)
    std::cout << "allocated " << isize << " byte(s) with new[]" << "\n";

  return p;
}

void operator delete[](void *p) noexcept {
  if (print_allocation)
    std::cout << "deleted memory with delete[]" << "\n";

  std::free(p);
}

void operator delete[](void *p, std::size_t) noexcept { operator delete[](p); }

class Document {
private:
  double rank_{};
  int id_{};
  bool is_cached_{};

public:
  auto operator new(size_t size) -> void * { return ::operator new(size); }

  auto operator delete(void *p) -> void { ::operator delete(p); }
};

class OperatorNew : public ::testing::Test {
protected:
  void SetUp() override { print_allocation = true; }

  void TearDown() override { print_allocation = false; }
};

TEST(OperatorNew, AllocateAndDeleteMemory) {

  {
    auto *p = new char{'a'};
    delete p;
  }

  {
    auto *p = new char[10];
    delete[] p;
  }

  {
    auto *p = new Document{};
    delete p;
  }

  {
    auto *p = ::new Document{};
    ::delete p;
  }
}
