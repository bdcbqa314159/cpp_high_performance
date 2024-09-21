#include <gtest/gtest.h>

#include <iostream>

namespace {
struct Bear {
  auto roar() const { std::cout << "roar\n"; }
};

struct Duck {
  auto quack() const { std::cout << "quack\n"; }
};

template <typename Animal> auto speak(const Animal &a) {
  if (std::is_same_v<Animal, Bear>)
    a.roar();
  else if (std::is_same_v<Animal, Duck>)
    a.quack();
  else
    std::cout << "unknown\n";
}

template <typename Animal> void constexpr_if_speak(const Animal &a) {
  if constexpr (std::is_same_v<Animal, Bear>)
    a.roar();
  else if constexpr (std::is_same_v<Animal, Duck>)
    a.quack();
  else
    std::cout << "unknown\n";
}

} // namespace

TEST(constexprIfAnimals, Speak) {
  Bear bear;
  Duck duck;

  constexpr_if_speak(bear);
  constexpr_if_speak(duck);
}
