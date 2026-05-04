#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <new>
#include <sys/types.h>
#include <type_traits>

using namespace std;

template<size_t SIZE, typename... Types>
void allocate(void* memory, Types... args) {
  static_assert((std::is_copy_constructible<std::remove_cv_t<Types>> && ...), "All types are copyconstructible");
  constexpr size_t total_size = (sizeof(Types) + ...);
  static_assert(total_size <= SIZE, "Total size is more than acceptable size");

  std::byte* ptr = static_cast<std::byte*>(memory);

  auto place = [&ptr](auto&& arg) {
    using ArgType = std::remove_cv_t<decltype(arg)>;
    new (ptr) ArgType(std::forward<decltype(arg)>(arg));
    ptr += sizeof(ArgType);
  };

  (place(args), ...);
}
