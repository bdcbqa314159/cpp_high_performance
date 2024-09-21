#include <unistd.h>
#include <version>
#if defined(__cpp_lib_semaphore)

#include <gtest/gtest.h>

#include <array>
#include <iostream>
#include <optional>
#include <semaphore>
#include <string>
#include <thread>

namespace {

template <class T, int N> class BoundedBuffer {
  std::array<T, N> buf_;
  std::size_t read_pos_{}, write_pos_{};
  std::mutex m_{};
  std::counting_semaphore<N> n_empty_slots_{N}, n_full_slots_{0};

  void do_push(auto &&item) {
    n_empty_slots_.acquire();
    try {
      auto lock = std::unique_lock{m_};
      buf_[write_pos_] = std::forward<decltype(item)>(item);
      write_pos_ = (write_pos_ + 1) % N;
    } catch (...) {
      n_empty_slots_.release();
      throw;
    }
    n_full_slots_.release();
  }

public:
  void push(const T &item) { do_push(item); }
  void push(T &&item) { do_push(std::move(item)); }

  auto pop() {
    n_full_slots_.acquire();
    auto item = std::optional<T>{};
    try {
      auto lock = std::unique_lock{m_};
      item = std::move(buf_[read_pos_]);
      read_pos_ = (read_pos_ + 1) % N;
    } catch (...) {
      n_full_slots_.release();
      throw;
    }
    n_empty_slots_.release();
    return std::move(*item);
  }
};

} // namespace

TEST(Semaphores, BoundedBuffer) {
  auto buffer = BoundedBuffer<std::string, 5>{};
  auto sentinel = std::string{};

  auto producer = std::thread{[&]() {
    buffer.push("A");
    buffer.push("B");
    buffer.push("C");
    buffer.push(sentinel);
  }};

  auto consumer = std::thread{[&]() {
    for (;;) {
      auto s = buffer.pop();
      if (s != sentinel)
        std::cout << "Got: " << s << "\n";

      else
        break;
    }
  }};

  producer.join();
  consumer.join();
}

#endif
