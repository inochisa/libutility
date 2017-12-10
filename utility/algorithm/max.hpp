
#ifndef __UTILITY_ALGORITHM_MAX__
#define __UTILITY_ALGORITHM_MAX__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    template<typename _T>
    inline __UTILITY_CPP14_CONSTEXPR__
    const _T& max(const _T& __a, const _T& __b) noexcept
    {
      if(__a > __b )
      { return __a;}
      return __b;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_MAX__
