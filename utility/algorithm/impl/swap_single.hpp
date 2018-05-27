
#ifndef __UTILITY_ALGORITHM_SWAP_SINGLE__
#define __UTILITY_ALGORITHM_SWAP_SINGLE__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/move.hpp>
#include<utility/trait/type/features/is_move_assignable.hpp>
#include<utility/trait/type/features/is_move_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_move_assignable.hpp>
#include<utility/trait/type/features/is_nothrow_move_constructible.hpp>
#include<utility/trait/type/miscellaneous/enable_if.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Exchange values of two objects
     *
     * Swaps the values \a __a and \a __b.
     *
     * \param __a,__b the values to be swapped
     * \note This overload does not participate in overload resolution
     *       unless \c is_move_constructible_v<_T>
     *       && \c is_move_assignable_v<_T> is \b true
     * \exception this function is \b noexcept when
     *            \c is_nothrow_move_constructible<_T> &&
     *            \c is_nothrow_move_assignable<_T> is \b true
     * \related algorithm::possible_swap
     */
    template<typename _T>
    inline
    typename trait::type::miscellaneous::enable_if
    <
      trait::type::features::is_move_assignable<_T>::value &&
      trait::type::features::is_move_constructible<_T>::value,
      void
    >::type
    swap(_T& __a, _T& __b)
      noexcept(
        trait::type::features::is_nothrow_move_constructible<_T>::value &&
        trait::type::features::is_nothrow_move_assignable<_T>::value
      )
    {
      _T __tmp(algorithm::move(__a));
      __a = algorithm::move(__b);
      __b = algorithm::move(__tmp);
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_SWAP_SINGLE__
