
#ifndef __UTILITY_MEMORY_ALLOCATOR_HELPER__
#define __UTILITY_MEMORY_ALLOCATOR_HELPER__

#include<utility/config/utility_config.hpp>

#ifdef ___UTILITY__CHECK__USE__STD___

#include<memory>

namespace utility
{
  namespace container
  {
    using std::allocator_arg;
    using std::allocator_arg_t;
  }
}

#else // ___UTILITY__CHECK__USE__STD___

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

#endif // ! ___UTILITY__CHECK__USE__STD___

#endif // ! __UTILITY_MEMORY_ALLOCATOR_HELPER__
