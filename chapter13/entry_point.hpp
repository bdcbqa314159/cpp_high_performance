#pragma once
#include <version>

#ifdef __has_include
#if __has_include(<coroutine>)
#include <coroutine>

#define SUPPORTS_COROUTINES 1
#elif __has_include(<experimental/coroutine>)

#include <experimental/coroutine>
namespace std {
using std::experimental::coroutine_handle;
using std::experimental::suspend_always;
using std::experimental::suspend_never;
} // namespace std

#define SUPPORTS_COROUTINES 1

#endif

#endif

// non sense warning - had to add this to wipe the unused include lsp warning
struct foo;
struct bar : std::coroutine_handle<foo> {
  using promise_type = ::foo;
};
