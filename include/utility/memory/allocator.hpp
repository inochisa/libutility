
#ifndef __UTILITY_MEMORY_ADV_ALLOCATOR__
#define __UTILITY_MEMORY_ADV_ALLOCATOR__

#include<utility/memory/basic_allocator.hpp>

namespace utility
{
  namespace memory
  {
    template<typename _T>
    using allocator = basic_allocator<_T>;
  }
}

#endif // ! __UTILITY_MEMORY_ADV_ALLOCATOR__
