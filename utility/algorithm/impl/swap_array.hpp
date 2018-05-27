
#ifndef __UTILITY_ALGORITHM_SWAP_ARRAY__
#define __UTILITY_ALGORITHM_SWAP_ARRAY__

#include<utility/config/utility_config.hpp>
#include<utility/trait/type/features/is_swappable.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Exchange values of two array
     *
     * Swaps the arrays \a __a and \a __b
     *
     * \param __a,__b the arrays to be swapped
     * \note This overload does not participate in
     *       overload resolution unless \c
     *       is_swappable<_T> is \b true
     * \exception This function is noexcept
     *            when \c is_nothrow_swappable_with<_T> is \b true
     * \related algorithm::possible_swap
     */
    template<typename _T, size_t __size>
    inline
    typename trait::type::miscellaneous::enable_if
    <
      trait::type::features::is_swappable_with<_T&, _T&>::value,
      void
    >::type
    swap(_T(&__a)[__size], _T(&__b)[__size])
     noexcept(
       trait::type::features::is_nothrow_swappable_with<_T&, _T&>::value)
    {
      for(size_t __i = 0; __i < __size; ++__i)
      { swap(__a[__i], __b[__i]);}
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_SWAP_ARRAY__
