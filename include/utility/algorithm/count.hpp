
#ifndef __UTILITY_ALGORITHM_COUNT__
#define __UTILITY_ALGORITHM_COUNT__

#include<utility/config/utility_config.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Counts appearances of value in range
     *
     * Returns the number of elements in the range [\a __first, \a __last)
     * that are equal to value.
     *
     * \tparam _InputIterator the iterator type
     * \tparam _T             the value type
     * \param __first,__last  the range of elements to examine
     * \param __val           the value to search for
     * \return number of elements satisfying the condition.
     */
    template<typename _InputIterator, typename _T>
    inline
    typename
    iterator::iterator_traits<_InputIterator>::difference_type
    count(
      _InputIterator __first, _InputIterator __last,
      const _T& __val
    )
    {
      typedef typename
        iterator::iterator_traits<_InputIterator>::difference_type
        __difference_type;
      __difference_type __res = 0;
      for(; __first != __last;)
      {
        if(*__first++ == __val)
        { ++__res;}
      }
      return __res;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_COUNT__
