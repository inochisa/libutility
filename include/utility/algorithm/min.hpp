
#ifndef __UTILITY_ALGORITHM_MIN__
#define __UTILITY_ALGORITHM_MIN__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    template<typename _T>
    inline __UTILITY_CPP14_CONSTEXPR__
    const _T& min(const _T& __a, const _T& __b) noexcept
    {
      if(__a < __b )
      { return __a;}
      return __b;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_MIN__
