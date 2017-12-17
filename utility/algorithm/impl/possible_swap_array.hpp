
#ifndef __UTILITY_ALGORITHM_POSSIBLE_SWAP_ARRAY__
#define __UTILITY_ALGORITHM_POSSIBLE_SWAP_ARRAY__

#include<utility/config/utility_config.hpp>
#include<utility/trait/type/features/is_possible_swappable.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>

namespace utility
{
  namespace algorithm
  {
    template<typename _T, ::utility::size_t __size>
    inline
    typename ::utility::trait::type::miscellaneous::enable_if<
      ::utility::trait::type::features::is_possible_swappable_with<_T&, _T&>::value,
      void
    >::type
    possible_swap(_T(&__a)[__size], _T(&__b)[__size]) noexcept(
      ::utility::trait::type::features::is_nothrow_possible_swappable_with<_T&, _T&>::value
    )
    {
      for(::utility::size_t __i = 0; __i < __size; ++__i)
      { possible_swap(__a[__i], __b[__i]);}
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_POSSIBLE_SWAP_ARRAY__
