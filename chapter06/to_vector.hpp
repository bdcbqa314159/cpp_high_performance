#pragma once

#include <algorithm>
#include <ranges>
#include <vector>

/*auto to_vector(auto &&r)
{
    std::vector<std::ranges::range_value_t<decltype(r)>> v;
    if constexpr (std::ranges::sized_range<decltype(r)>)
    {
        v.reserve(std::ranges::size(r));
    }
    std::ranges::copy(r, std::back_inserter(v));
    return v;
}*/

auto to_vector(auto &&r) {
  std::vector<std::ranges::range_value_t<decltype(r)>> v;
  if constexpr (std::ranges::sized_range<decltype(r)>) {
    v.reserve(std::ranges::size(r));
  }
  std::ranges::copy(r, std::back_inserter(v));
  return v;
}
