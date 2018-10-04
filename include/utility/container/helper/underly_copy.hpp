
#ifndef __UTILITY_CONTAINER_HELPER_UNDERLY_COPY__
#define __UTILITY_CONTAINER_HELPER_UNDERLY_COPY__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace container
  {
    namespace helper
    {
      template<typename _T>
      UTILITY_ALWAYS_INLINE
      inline void underly_copy(void* _dest, const void* _src) noexcept
      {
        unsigned char* __dest = reinterpret_cast<unsigned char*>(_dest);
        const unsigned char* __src = reinterpret_cast<const unsigned char*>(_src);
        unsigned long __len = sizeof(_T);
        for(unsigned long __i = 0; __i < __len; ++__i)
        { *__dest++ = *__src++;}
      }
    }
  }
}

#endif // ! __UTILITY_CONTAINER_HELPER_UNDERLY_COPY__
