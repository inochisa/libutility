
#ifndef __UTILITY_MEMORY_ALLOCATOR_HELPER__
#define __UTILITY_MEMORY_ALLOCATOR_HELPER__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace memory
  {
    struct allocator_arg_t
    {
      explicit allocator_arg_t() = default;
    };

    __UTILITY_CPP17_INLINE__
    constexpr memory::allocator_arg_t allocator_arg{};
  }
}

#endif // ! __UTILITY_MEMORY_ALLOCATOR_HELPER__
