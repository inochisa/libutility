
#ifndef __UTILITY_ALGORITHM_REVERSE_COPY__
#define __UTILITY_ALGORITHM_REVERSE_COPY__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Copy range reversed
     *
     * Copies the elements from the range [\a __first, \a __last)
     * to another range beginning at \a __ofirst in such a way
     * that the elements in the new range are in reverse order.
     *
     * \param __first,__last the range of elements to copy
     * \param __ofirst       the beginning of the destination range
     * \return Output iterator to the element past the last element copied.
     * \note Behaves as if by executing the assignment
     *       *(\a __ofirst + (\a __last - \a __first) - 1 - i) =
     *       *(\a __first + i) once for
     *       each non-negative i < (\a __last - \a __first)
     * \warning If the source and destination ranges
     *          (that is, [\a __first, \a __last) and
     *          [\a __ofirst, \a __ofirst + (\a __last - \a __first))
     *          respectively) overlap, the behavior is undefined.
     */
    template<typename _BidirectionalIterator, typename _OutputIterator>
    _OutputIterator reverse_copy(
      _BidirectionalIterator __first, _BidirectionalIterator __last,
      _OutputIterator __ofirst
    )
    {
      for(;__first != __last;)
      { *(++__ofirst) = *(--__last);}
      return __ofirst;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_REVERSE_COPY__
