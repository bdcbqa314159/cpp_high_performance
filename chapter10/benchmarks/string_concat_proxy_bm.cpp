#include <benchmark/benchmark.h>
#include <random>
#include <string>
#include <vector>

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

namespace {

template <typename T> auto create_strings(int n, size_t length) {
  auto re = std::default_random_engine{std::random_device{}()};
  auto random_string = [&] {
    auto d = std::uniform_int_distribution<>{'A', 'Z'};
    auto random_char = [&] { return static_cast<char>(d(re)); };
    auto s = std::string(length, '\0');
    std::generate(std::begin(s), std::end(s), random_char);
    return s;
  };
  auto v = std::vector<T>(n);
  std::generate(std::begin(v), std::end(v), random_string);
  return v;
}

template <typename T> void bm_string_compare(benchmark::State &state) {
  const auto n = 10'000;
  const auto length = state.range(0);
  const auto a = create_strings<T>(n, length);
  const auto b = create_strings<T>(n, length);
  const auto c = create_strings<T>(n, length * 2);

  for (auto _ : state) {
    for (auto i = 0; i < n; ++i) {
      auto is_equal = a[i] + b[i] == c[i];
      benchmark::DoNotOptimize(is_equal);
    }
  }
}

} // namespace

BENCHMARK_TEMPLATE(bm_string_compare, std::string)
    ->Arg(50)
    ->Arg(10)
    ->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(bm_string_compare, String)
    ->Arg(50)
    ->Arg(10)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
