
#ifndef __UTILITY_ALGORITHM_MOVE__
#define __UTILITY_ALGORITHM_MOVE__

#include<utility/config/utility_config.hpp>
#include<utility/trait/type/transform/remove_reference.hpp>

namespace utility
{
  namespace algorithm
  {
    template<typename _T>
    inline __UTILITY_CPP14_CONSTEXPR__
    typename utility::trait::type::transform::remove_reference<_T>::type&&
    move(_T&& __val) noexcept
    {
      typedef typename
        utility::trait::type::transform::remove_reference<_T>::type _U;
      return static_cast<_U&&>(__val);
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_MOVE__
