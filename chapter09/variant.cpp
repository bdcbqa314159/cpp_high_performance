#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <variant>

using VariantType = std::variant<int, std::string, bool>;

struct FunctorImpl {
  auto operator()(const int &v) { std::cout << v << "\n"; }
  auto operator()(const std::string &v) { std::cout << v << "\n"; }
  auto operator()(const bool &v) { std::cout << v << "\n"; }
};

auto visit_impl(FunctorImpl ifunctor, const VariantType &ivariant) {
  if (std::holds_alternative<int>(ivariant))
    return ifunctor(std::get<int>(ivariant));
  else if (std::holds_alternative<std::string>(ivariant))
    return ifunctor(std::get<std::string>(ivariant));
  else if (std::holds_alternative<bool>(ivariant))
    return ifunctor(std::get<bool>(ivariant));
}

TEST(Variant, Assignement) {
  auto v = VariantType{};
  ASSERT_TRUE(std::holds_alternative<int>(v));
  v = 7;
  ASSERT_TRUE(std::holds_alternative<int>(v));
  v = std::string{"Anne"};
  ASSERT_FALSE(std::holds_alternative<int>(v));
  v = false;
  ASSERT_TRUE(std::holds_alternative<bool>(v));
}

TEST(Variant, SizeOf) {
  std::cout << "VariantType: " << sizeof(VariantType) << "\n";
  std::cout << "std::string: " << sizeof(std::string) << "\n";
  std::cout << "std::size_t: " << sizeof(size_t) << "\n";
}

namespace {
struct Widget {

  explicit Widget(int) { throw std::exception{}; }
};
} // namespace

TEST(Variant, ExceptionSafety) {
  auto var = std::variant<double, Widget>{1.};

  try {
    var.emplace<1>(42);
  } catch (...) {
    std::cout << "exception caught\n";
    if (var.valueless_by_exception())
      std::cout << "valueless\n";
    else
      std::cout << std::get<0>(var) << "\n";
  }
}

TEST(Variant, StdVisit) {
  auto var = std::variant<int, bool, float>{};
  std::visit([](auto &&val) { std::cout << val; }, var);
  std::cout << "\n";
}

template <class... Lambdas> struct Overloaded : Lambdas... {
  using Lambdas::operator()...;
};

template <class... Lambdas> Overloaded(Lambdas...) -> Overloaded<Lambdas...>;

TEST(Variant, Overloaded) {
  auto overloaded_lambdas =
      Overloaded{[](int v) { std::cout << "Int: " << v; },
                 [](bool v) { std::cout << "Bool: " << v; },
                 [](float v) { std::cout << "Float: " << v; }};
  overloaded_lambdas(30031);
  overloaded_lambdas(2.71828f);
}

TEST(Variant, VisitOverloaded) {
  std::variant<int, bool, float> v = 42;
  std::visit(Overloaded{[](int v) { std::cout << "Int: " << v; },
                        [](bool v) { std::cout << "Bool: " << v; },
                        [](float v) { std::cout << "Float: " << v; }},
             v);
}
