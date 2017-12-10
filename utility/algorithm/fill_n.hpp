
#ifndef __UTILITY_ALGORITHM_FILL_N__
#define __UTILITY_ALGORITHM_FILL_N__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Fill sequence with value
     *
     * Assigns the given value to the first count elements
     * in the range beginning at \a __ofirst if \a __size > 0. Does nothing otherwise.
     *
     * \tparam _OutputIterator the filled iterator type
     * \tparam _Size           the length type, usually is size_t or ptrdiff_t
     * \tparam _T              the value type
     * \param __ofirst  the beginning of the range of elements to modify
     * \param __size    number of elements to modify
     * \param __val     the value to be assigned
     * \return Iterator one past the last element assigned if count > 0,
     *         \a __ofirst otherwise.
     */
    template<typename _OutputIterator, typename _Size, typename _T>
    _OutputIterator fill_n(
      _OutputIterator __ofirst, _Size __size, const _T& __val
    )
    {
      for(_Size __i = 0; __i < __size; ++__i)
      { *__ofirst++ = __val;}
      return __ofirst;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_FILL_N__
