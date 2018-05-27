
#ifndef __UTILITY_MEMORY_NEW__
#define __UTILITY_MEMORY_NEW__

#include<utility/config/utility_config.hpp>
#include<utility/info/exception/bad_alloc.hpp>

namespace utility
{
  namespace memory
  {
    struct nothrow_t { };
    constexpr nothrow_t nothrow;
  }
}

void* operator new(size_t __size, void* __ptr)
{ return __ptr;}
void* operator new[](size_t __size, void* __ptr)
{ return __ptr;}

#endif // ! __UTILITY_MEMORY_NEW__
