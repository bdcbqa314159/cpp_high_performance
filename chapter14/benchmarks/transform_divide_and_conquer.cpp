#include "transform.hpp"
#include <benchmark/benchmark.h>
#include <cassert>
#include <numeric>
#include <tuple>
#include <vector>

namespace {

auto setup_fixture(size_t n) {
  auto src = std::vector<float>(n);
  std::iota(src.begin(), src.end(), 1.0f); // "src" goes from 1.0 to n
  auto dst = std::vector<float>(src.size());
  auto transform_func = [](float v) {
    auto sum = v;
    auto n = v / 20'000;
    for (auto i = 0; i < n; ++i) {
      sum += (i * i * i * sum);
    }
    return sum;
  };
  return std::tuple{src, dst, transform_func};
}

void bm_parallel(benchmark::State &state) {
  auto [src, dst, f] = setup_fixture(10'000'000);
  auto chunk_sz = state.range(0);
  for (auto _ : state) {
    par_transform(src.begin(), src.end(), dst.begin(), f, chunk_sz);
  }
}

void bm_parallel_naive(benchmark::State &state) {
  auto [src, dst, f] = setup_fixture(10'000'000);
  for (auto _ : state) {
    par_transform_naive(src.begin(), src.end(), dst.begin(), f);
  }
}

void CustomArguments(benchmark::internal::Benchmark *b) {
  b->MeasureProcessCPUTime()->UseRealTime()->Unit(benchmark::kMillisecond);
}

} // namespace

BENCHMARK(bm_parallel)
    ->Apply(CustomArguments)
    ->RangeMultiplier(10)
    ->Range(10000, 10'000'000);
BENCHMARK(bm_parallel_naive)->Apply(CustomArguments);

BENCHMARK_MAIN();
