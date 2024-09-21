#if _MSC_VER
#pragma warning(disable : 4834)
#endif

#include <cassert>
#include <optional>
#include <vector>

#include <gtest/gtest.h>

namespace {
struct Point {};

struct Line {};

auto lines_are_parallel(Line, Line) -> bool { return false; }
auto compute_intersection(Line, Line) -> Point { return Point{}; }
auto set_magic_point(Point) {}

auto get_intersection(const Line &a, const Line &b) -> std::optional<Point> {
  if (lines_are_parallel(a, b))
    return std::optional{compute_intersection(a, b)};
  else
    return {};
}

} // namespace

TEST(Optional, Intersection) {
  auto intersection = get_intersection(Line{}, Line{});
  if (intersection.has_value())
    set_magic_point(*intersection);

  ASSERT_FALSE(intersection.has_value());
  EXPECT_THROW(intersection.value(), std::bad_optional_access);
}

namespace {
struct Hat {};
} // namespace

class Head {
public:
  Head() { assert(!hat_); }
  auto set_hat(const Hat &h) { hat_ = h; }
  auto has_hat() const { return hat_.has_value(); }
  auto &get_hat() const {
    assert(hat_.has_value());
    return *hat_;
  }

  auto remove_hat() { hat_ = {}; }

private:
  std::optional<Hat> hat_;
};

TEST(Optional, Head) {
  auto a = Head{};
  auto b = a;
  ASSERT_FALSE(a.has_hat());
  ASSERT_FALSE(b.has_hat());

  a.set_hat(Hat{});
  ASSERT_TRUE(a.has_hat());
  ASSERT_FALSE(b.has_hat());
}

TEST(Optional, Sort) {
  auto c = std::vector<std::optional<int>>{{3}, {}, {1}, {}, {2}};
  std::sort(c.begin(), c.end());
  const auto sorted = std::vector<std::optional<int>>{{}, {}, {1}, {2}, {3}};
  ASSERT_EQ(sorted, c);
}
