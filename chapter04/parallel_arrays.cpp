#include "scoped_timer.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>

struct OriginalUser {
  std::string name_, username_, password_, security_question_, security_answer_;
  short level_{};
  bool is_playing_{};
};

auto num_users_at_level(short level, const std::vector<OriginalUser> &users) {
  ScopedTimer t{"num_users_at_level (using OriginalUser)"};
  auto num_users = 0;
  for (const auto &user : users) {
    if (user.level_ == level)
      ++num_users;
  }
  return num_users;
}

auto num_playing_users(const std::vector<OriginalUser> &users) {
  ScopedTimer t{"num_playing_users (using OriginalUser)"};
  return std::count_if(users.begin(), users.end(),
                       [](const auto &user) { return user.is_playing_; });
}

struct AuthInfo {
  std::string username_, password_, security_question_, security_answer_;
};

struct User {
  std::string name_;
  std::unique_ptr<AuthInfo> auth_info_;
  short level_{};
  bool is_playing_{};
};

auto num_users_at_level(short level, const std::vector<User> &users) {
  ScopedTimer t{"num_users_at_level (using User)"};
  auto num_users = 0;

  for (const auto &user : users) {
    if (user.level_ == level)
      ++num_users;
  }

  return num_users;
}

auto num_playing_users(const std::vector<User> &users) {
  ScopedTimer t{"num_playing_users (using User)"};

  return std::count_if(users.begin(), users.end(),
                       [](const auto &user) { return user.is_playing_; });
}

auto num_users_at_level(short level, const std::vector<short> &users) {
  ScopedTimer t{"num_users_at_level using vector<short>"};
  return std::count(users.begin(), users.end(), level);
}

auto num_playing_users(const std::vector<bool> &users) {
  ScopedTimer t{"num_playing_users using vector<bool>"};
  return std::count(users.begin(), users.end(), true);
}

auto gen_is_playing() { return static_cast<bool>(std::rand() % 2); }

auto gen_level() { return static_cast<short>(std::rand() % 100); }

auto create_users(size_t count) {
  auto vec = std::vector<User>(count);
  for (auto &user : vec) {
    user.name_ = "some level";
    user.level_ = gen_level();
    user.is_playing_ = gen_is_playing();
  }
  return vec;
}

auto create_levels(size_t count) {
  auto vec = std::vector<short>(count);
  for (auto &level : vec)
    level = std::rand() % 100;
  return vec;
}

auto create_playing_users(size_t count) {
  auto vec = std::vector<bool>(count);
  for (auto &&is_playing_ : vec)
    is_playing_ = static_cast<bool>(std::rand() % 2);
  return vec;
}

TEST(ParallelArrays, CompareProcessingTime) {
  std::cout << "sizeof(OriginalUser): " << sizeof(OriginalUser) << " bytes"
            << "\n";
  std::cout << "sizeof(User): " << sizeof(User) << " bytes" << "\n";

  auto num_objects = 1'000'000;

  std::cout << "Creating objects ..." << "\n";
  auto original_users = std::vector<OriginalUser>(num_objects);
  auto users = create_users(num_objects);
  auto user_levels = create_levels(num_objects);
  auto playing_users = create_playing_users(num_objects);

  std::cout << "done " << "\n";

  auto n = 0ul;
  auto level = short{5};

  std::cout << "\n"
            << "+++ count stats using OriginalUser +++" << "\n";

  n += num_users_at_level(level, original_users);
  n += num_users_at_level(level, original_users);
  n += num_users_at_level(level, original_users);

  n += num_playing_users(original_users);
  n += num_playing_users(original_users);
  n += num_playing_users(original_users);

  std::cout << "\n"
            << "+++ count stats using User +++" << "\n";

  n += num_users_at_level(level, users);
  n += num_users_at_level(level, users);
  n += num_users_at_level(level, users);

  n += num_playing_users(users);
  n += num_playing_users(users);
  n += num_playing_users(users);

  std::cout << "\n"
            << "+++ count stats using vector<short> and vector<bool>" << "\n";

  n += num_users_at_level(level, user_levels);
  n += num_users_at_level(level, user_levels);
  n += num_users_at_level(level, user_levels);

  n += num_playing_users(playing_users);
  n += num_playing_users(playing_users);
  n += num_playing_users(playing_users);

  std::cout << n << "\n";
}
