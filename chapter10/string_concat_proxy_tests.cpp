#include <gtest/gtest.h>

#include <algorithm>
#include <cassert>
#include <string>

class String {
public:
  String() = default;
  String(std::string istr) : str_{std::move(istr)} {}
  std::string str_{};
};

struct ConcatProxy {
  const std::string &a, b;
  operator String() const && { return String{a + b}; }
};

auto is_concat_equal(const std::string &a, const std::string &b,
                     const std::string &c) {
  return a.size() + b.size() == c.size() &&
         std::equal(a.begin(), a.end(), c.begin()) &&
         std::equal(b.begin(), b.end(), c.begin() + a.size());
}

auto operator+(const String &a, const String &b) {
  return ConcatProxy{a.str_, b.str_};
}

// auto operator==(ConcatProxy &&concat, const String &str);
auto operator==(ConcatProxy &&concat, const String &str) -> bool {
  return is_concat_equal(concat.a, concat.b, str.str_);
}

TEST(ConcatProxy, StdConcatenateAndCompareStrings) {
  auto a = std::string{"Cole"};
  auto b = std::string{"Porter"};
  auto c = std::string{"ColePorter"};
  auto is_cole_porter = is_concat_equal(a, b, c);
  ASSERT_TRUE(is_cole_porter);
}

TEST(ConcatProxy, ConcatenateAndCompareStrings) {
  auto a = String{"Cole"};
  auto b = String{"Porter"};
  auto c = String{"ColePorter"};
  auto is_cole_porter = (a + b) == c;
  ASSERT_TRUE(is_cole_porter);
}

TEST(ConcatProxy, ConcatenateStrings) {
  String c = String{"Marc"} + String{"Chagall"};
  ASSERT_TRUE(c.str_ == "MarcChagall");
}

TEST(ConcatenateProxy, Test) {
  auto a = String{"Marc"};
  auto b = String{"Chagall"};
  auto c = String{"MarcChagall"};
  auto is_equal = (String{"Marc"} + String{"Chagall"}) == c;
  ASSERT_TRUE(is_equal);
  is_equal = (a + b) == String{"MarcChagall"};
  ASSERT_TRUE(is_equal);
}
