#pragma once

#include <cmath>
#include <compare>

class LengthProxy {
public:
  LengthProxy(float x, float y) : squared_{x * x + y * y} {}
  bool operator==(const LengthProxy &other) const = default;
  auto operator<=>(const LengthProxy &other) const = default;
  friend auto operator<=>(const LengthProxy &proxy,
                          float len) -> std::partial_ordering {
    return proxy.squared_ <=> len * len;
  }

  operator float() const { return std::sqrt(squared_); }

private:
  float squared_{};
};

class Vec2D {
public:
  Vec2D() = default;
  Vec2D(const Vec2D &) = default;
  Vec2D(Vec2D &&) = default;
  Vec2D &operator=(const Vec2D &) = default;
  Vec2D &operator=(Vec2D &&) = default;
  Vec2D(float x, float y) : x_{x}, y_{y} {}
  auto length() const { return LengthProxy(x_, y_); }

  // auto length_slow() const {
  //   auto squared = x_ * x_ + y_ * y_;
  //   return std::sqrt(squared);
  // }
  // auto length_squared() const {
  //   auto squared = x_ * x_ + y_ * y_;
  //   return squared;
  // }

  float x_{};
  float y_{};
};
