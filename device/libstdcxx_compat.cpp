#include <new>
#include <cstdlib>

#if defined(__GNUC__) && !defined(__clang__) && (__GNUC__ < 10)
namespace std {
[[noreturn]] void __throw_bad_array_new_length() {
#if defined(__cpp_exceptions)
  throw bad_array_new_length();
#else
  std::abort();
#endif
}
}  // namespace std
#endif
