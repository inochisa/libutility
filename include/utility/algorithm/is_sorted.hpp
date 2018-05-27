
#ifndef __UTILITY_ALGORITHM_IS_SORTED__
#define __UTILITY_ALGORITHM_IS_SORTED__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Check whether a range is sorted into ascending order
     *
     * Checks if the elements in range [\a __first, \a __last)
     * are sorted in non-descending order.
     *
     * \param __first,__last  the range of elements to examine
     * \param __compare       comparison function object which returns ​true
     *                        if the first argument is less than the second.
     *                        The signature of the comparison function
     *                        should be logically equivalent to the following:
     *                        \code{.cpp}
     *                          bool cmp(const Type1&, const Type2&);
     *                        \endcode
     * \return true if the elements in the range are sorted in ascending order
     */
    template<typename _ForwardIterator, typename _Compare>
    bool is_sorted(
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
          { return false;}
          __first = __next;
        }
      }
      return true;
    }
    /**
     * \overload bool is_sorted(
     *   _ForwardIterator __first, _ForwardIterator __last
     * )
     *
     * this version use operator< as comparison function object
     *
     */
    template<typename _ForwardIterator>
    bool is_sorted(
      _ForwardIterator __first, _ForwardIterator __last
    )
    {
      if(__first != __last)
      {
        _ForwardIterator __next = __first;
        for(;++__next != __last;)
        {
          if(*__next < *__first)
          { return false;}
          __first = __next;
        }
      }
      return true;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_IS_SORTED__
