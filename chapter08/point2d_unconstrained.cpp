#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

namespace {

template <typename T> class Point2D {
public:
  Point2D(T x, T y) : x_{x}, y_{y} {}
  auto x() { return x_; }
  auto y() { return y_; }

private:
  T x_{}, y_{};
};

template <typename T> auto dist(T p1, T p2) {
  auto a = p1.x() - p2.x();
  auto b = p1.y() - p2.y();

  return std::sqrt(a * a + b * b);
}
} // namespace

TEST(Point2DUnconstrained, Dist) {
  auto p1 = Point2D{2, 2};
  auto p2 = Point2D{6, 5};

  auto d = dist(p1, p2);

  ASSERT_DOUBLE_EQ(d, 5.);
}

TEST(Point2DUnconstrained, DistWithCharPtr) {
  auto from = Point2D{"2.", "2."};
  auto to = Point2D{"6.", "5."};
  auto d = dist(from, to);
  std::cout << d << "\n";
}
