#pragma once

#include <version>

#if defined(__cpp_impl_coroutine) && defined(__cpp_lib_coroutine)
#include <coroutine>

#define SUPPORTS_COROUTINES
#endif

#if !defined(SUPPORT_COROUTINES) && defined(__has_include)

#if __has_include(<coroutine>)

#include <coroutine>
#define SUPPORTS_COROUTINES

#elif __has_include(<experimetal/coroutine>)

#include <experimental/coroutine>
namespace std {
using std::experimental::coroutine_handle;
using std::experimental::suspend_always;
using std::experimental::suspend_never;
} // namespace std

#define SUPPORTS_COROUTINES
#endif
#endif

// non sense warning - had to add this to wipe the unused include lsp warning
struct foo;
struct bar : std::coroutine_handle<foo> {
  using promise_type = ::foo;
};
