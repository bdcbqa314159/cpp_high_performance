#include <gtest/gtest.h>
#include <iostream>
#include <mutex>

struct Account {
  int balance_{0};
  std::mutex m_{};
};

void transfer_money(Account &from, Account &to, int amount) {
  auto lock1 = std::unique_lock<std::mutex>{from.m_, std::defer_lock};
  auto lock2 = std::unique_lock<std::mutex>{to.m_, std::defer_lock};

  std::lock(lock1, lock2);
  from.balance_ -= amount;
  to.balance_ += amount;
}

TEST(AvoidDeadLock, MoneyTransfer) {
  auto account1 = Account{100};
  auto account2 = Account{30};

  transfer_money(account1, account2, 20);
  std::cout << "Account 1: " << account1.balance_ << "\n";
  std::cout << "Account 2: " << account2.balance_ << "\n";

  ASSERT_EQ(80, account1.balance_);
  ASSERT_EQ(50, account2.balance_);
}
