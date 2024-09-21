#include <gtest/gtest.h>

#include <cassert>
#include <cmath>
#include <cstdint>
#include <type_traits>

template <typename T> constexpr auto make_false() { return false; }

template <typename Dst, typename Src> auto safe_cast(const Src &v) -> Dst {
  using namespace std;
  constexpr auto is_same_type = is_same_v<Src, Dst>;
  constexpr auto is_pointer_to_pointer = is_pointer_v<Src> && is_pointer_v<Dst>;
  constexpr auto is_float_to_float =
      is_floating_point_v<Src> && is_floating_point_v<Dst>;

  constexpr auto is_number_to_number =
      is_arithmetic_v<Src> && is_arithmetic_v<Dst>;
  constexpr auto is_intptr_to_ptr =
      (is_same_v<uintptr_t, Src> ||
       is_same_v<intptr_t, Src> && is_pointer_v<Dst>);

  constexpr auto is_ptr_to_intptr =
      is_pointer_v<Src> &&
      (is_same_v<uintptr_t, Dst> || is_same_v<intptr_t, Dst>);

  if constexpr (is_same_type)
    return v;

  else if constexpr (is_intptr_to_ptr || is_ptr_to_intptr)
    return reinterpret_cast<Dst>(v);

  else if constexpr (is_pointer_to_pointer) {
    assert(dynamic_cast<Dst>(v) != nullptr);
    return static_cast<Dst>(v);
  }

  else if constexpr (is_float_to_float) {
    auto casted = static_cast<Dst>(v);
    auto casted_back = static_cast<Src>(v);
    assert(!isnan(casted_back) && !isinf(casted_back));
    return casted;
  }

  else if constexpr (is_number_to_number) {
    auto casted = static_cast<Dst>(v);
    [[maybe_unused]] auto casted_back = static_cast<Src>(casted);
    return casted;
  }

  else {
    static_assert(make_false<Src>(), "CastError");
    return Dst{};
  }
}

TEST(SageCast, FloatToInt) {
  auto x = safe_cast<int>(42.f);
  (void)(x);
}
