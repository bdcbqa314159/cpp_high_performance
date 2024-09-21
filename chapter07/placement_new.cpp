#include <cstdlib>
#include <gtest/gtest.h>
#include <memory>

struct User {
  User(const std::string &name) : name_(name) {}
  std::string name_;
};

TEST(PlacementNew, MallocAllocate) {
  auto *memory = std::malloc(sizeof(User));
  auto *user = new (memory) User("john");

  ASSERT_EQ("john", user->name_);
  user->~User();
  std::free(memory);
}

TEST(PlacementNew, UninitalizedFill) {
  auto *memory = std::malloc(sizeof(User));
  auto *user_ptr = reinterpret_cast<User *>(memory);
  std::uninitialized_fill_n(user_ptr, 1, User{"john"});
  ASSERT_EQ("john", user_ptr->name_);
  std::destroy_at(user_ptr);
  std::free(memory);
}

#if not defined(_LIBCPP_VERSION)

TEST(PlacementNew, ConstructAt) {
  auto *memory = std::malloc(sizeof(User));
  auto *user_ptr = reinterpret_cast<User *>(memory);
  std::construct_at(user_ptr, User{"john"});
  ASSERT_EQ("john", user_ptr->name_);
  std::destroy_at(user_ptr);
  std::free(memory);
}

#endif
