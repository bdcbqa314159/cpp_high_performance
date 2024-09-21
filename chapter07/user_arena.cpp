#include "arena.hpp"
#include <gtest/gtest.h>
#include <memory>

auto &&user_arena = Arena<1024>{};

class User {
public:
  auto operator new(size_t size) -> void * { return user_arena.allocate(size); }

  auto operator delete(void *p) -> void {
    user_arena.deallocate(static_cast<std::byte *>(p), sizeof(User));
  }

  auto operator new[](size_t size) -> void * {
    return user_arena.allocate(size);
  }

  auto operator delete[](void *p, size_t size) -> void {
    user_arena.deallocate(static_cast<std::byte *>(p), size);
  }

private:
  int id_{};
};

TEST(UserArena, UsingTheArena) {
  auto user1 = new User{};
  delete user1;

  auto users = new User[10];

  delete[] users;

  auto users2 = std::make_unique<User>();
}
