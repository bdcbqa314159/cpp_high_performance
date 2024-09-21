#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <future>
#include <vector>

template <class SrcIt, class DstIt, class Func>
auto transform(SrcIt first, SrcIt last, DstIt dst, Func func) {
  while (first != last)
    *dst++ = func(*first++);
}

template <typename SrcIt, typename DstIt, typename Func>
auto par_transform_naive(SrcIt first, DstIt last, DstIt dst, Func f) {
  auto n = static_cast<size_t>(std::distance(first, last));
  auto n_cores = size_t{std::thread::hardware_concurrency()};
  auto n_tasks = std::max(n_cores, size_t{1});
  auto chunk_sz = (n + n_tasks - 1) / n_tasks;
  auto futures = std::vector<std::future<void>>{};

  for (auto i = 0ul; i < n_tasks; ++i) {
    auto start = chunk_sz * i;
    if (start < n) {
      auto stop = std::min(chunk_sz * (i + 1), n);
      auto fut = std::async(std::launch::async, [first, dst, start, stop, f]() {
        std::transform(first + start, first + stop, dst + start, f);
      });

      futures.emplace_back(std::move(fut));
    }

    for (auto &&fut : futures)
      fut.wait();
  }
}

template <typename SrcIt, typename DstIt, typename Func>
auto par_transform(SrcIt first, SrcIt last, DstIt dst, Func func,
                   size_t chunk_sz) {
  const auto n = static_cast<size_t>(std::distance(first, last));

  if (n <= chunk_sz) {
    std::transform(first, last, dst, func);
    return;
  }

  const auto src_middle = std::next(first, n / 2);

  auto future = std::async(std::launch::async, [=, &func] {
    par_transform(first, src_middle, dst, func, chunk_sz);
  });

  // par_transform(first, src_middle, dst, func, chunk_sz);

  const auto dst_middle = std::next(dst, n / 2);
  par_transform(src_middle, last, dst_middle, func, chunk_sz);
  future.wait();
};
