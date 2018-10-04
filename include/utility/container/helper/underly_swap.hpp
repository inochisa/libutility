
#ifndef __UTILITY_CONTAINER_HELPER_UNDERLY_SWAP__
#define __UTILITY_CONTAINER_HELPER_UNDERLY_SWAP__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace container
  {
    namespace helper
    {
      template<typename _T>
      UTILITY_ALWAYS_INLINE
      inline void underly_swap(void* _x, void* _y) noexcept
      {
        unsigned char __tmp;
        unsigned char* __x = reinterpret_cast<unsigned char*>(_x);
        unsigned char* __y = reinterpret_cast<unsigned char*>(_y);
        unsigned long __len = sizeof(_T);
        for(unsigned long __i = 0; __i < __len; ++__i)
        {
          __tmp = *__x;
          *__x++ = *__y;
          *__y++ = __tmp;
        }
      }
    }
  }
}

#endif // ! __UTILITY_CONTAINER_HELPER_UNDERLY_SWAP__
