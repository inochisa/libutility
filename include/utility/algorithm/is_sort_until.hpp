
#ifndef __UTILITY_ALGORITHM_IS_SORT_UNTIL__
#define __UTILITY_ALGORITHM_IS_SORT_UNTIL__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Find the largest sorted subrange
     *
     * Examines the range [\a __first, \a __last) and finds the largest range
     * beginning at \a __first in which the elements are sorted in ascending order.
     *
     * \param __first,__last  the range of elements to examine
     * \param __compare       comparison function object which returns ​true
     *                        if the first argument is less than the second.
     *                        The signature of the comparison function
     *                        should be logically equivalent to the following:
     *                        \code{.cpp}
     *                          bool cmp(const Type1&, const Type2&);
     *                        \endcode
     * \return The upper bound of the largest range beginning at \a __first
     *         in which the elements are sorted in ascending order. That is,
     *         the last iterator \a __it for which range [\a __first, \a __it) is sorted.
     */
    template<typename _ForwardIterator, typename _Compare>
    _ForwardIterator is_sort_until(
      _ForwardIterator __first, _ForwardIterator __last,
      _Compare __compare
    )
    {
      if(__first != __last)
      {
        _ForwardIterator __next = __first;
        for(;++__next != __last;)
        {
          if(__compare(*__next, *__first))
          { return __next;}
          __first = __next;
        }
      }
      return __last;
    }
    /**
     * \overload _ForwardIterator is_sort_until(
     *   _ForwardIterator __first, _ForwardIterator __last
     * )
     *
     * this version use operator< as comparison function object
     *
     */
    template<typename _ForwardIterator>
    _ForwardIterator is_sort_until(
      _ForwardIterator __first, _ForwardIterator __last
    )
    {
      if(__first != __last)
      {
        _ForwardIterator __next = __first;
        for(;++__next != __last;)
        {
          if(*__next < *__first)
          { return __next;}
          __first = __next;
        }
      }
      return __last;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_IS_SORT_UNTIL__
