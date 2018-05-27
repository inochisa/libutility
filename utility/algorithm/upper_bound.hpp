
#ifndef __UTILITY_ALGORITHM_UPPER_BOUND__
#define __UTILITY_ALGORITHM_UPPER_BOUND__

#include<utility/config/utility_config.hpp>
#include<utility/iterator/iterator_traits.hpp>
#include<utility/iterator/distance.hpp>
#include<utility/iterator/advance.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Return iterator to upper bound
     *
     * Returns an iterator pointing to the first element in the range
     * [\a __first, \a __last) that is greater than value.
     *
     * \param __first,__last  iterators defining the partially-ordered range to examine
     * \param __val           value to compare the elements to
     * \param __compare       comparison function object which returns ​true
     *                        if the first argument is less than the second.
     *                        The signature of the comparison function
     *                        should be logically equivalent to the following:
     *                        \code{.cpp}
     *                          bool cmp(const Type1&, const Type2&);
     *                        \endcode
     * \return Iterator pointing to the first element that is not less than value,
     *         or \a __last if no such element is found.
     * \attention The range [\a __first, \a __last) must be at least partially ordered.
     * \note The number of comparisons performed is logarithmic in the distance between
     *       \a __firs and \a __last (At most log(last - first) + O(1) comparisons).
     *       However, for non-RandomAccessIterators,
     *       the number of iterator increments is linear.
     */
    template<typename _ForwardIterator, typename _T, typename _Compare>
    _ForwardIterator upper_bound(
      _ForwardIterator __first, _ForwardIterator __last,
      const _T& __val, _Compare __compare
    )
    {
      _ForwardIterator __it;
      typedef typename
        iterator::iterator_traits<_ForwardIterator>::difference_type
        __difference_type;
      __difference_type __len = iterator::distance(__first, __last);
      __difference_type __now;
      for(;__len > 0;)
      {
        __it = __first;
        __now = __len / 2;
        iterator::advance(__it, __now);
        if(!__compare(__val, *__it))
        {
          __first = ++__it;
          __len -= __now + 1;
        }
        else
        { __len = __now;}
      }
      return __first;
    }
    /**
     * \overload _ForwardIterator upper_bound(
     *   _ForwardIterator __first, _ForwardIterator __last,
     *   const _T& __val
     * )
     *
     * this version use operator< as comparison function object
     *
     */
    template<typename _ForwardIterator, typename _T>
    _ForwardIterator upper_bound(
      _ForwardIterator __first, _ForwardIterator __last,
      const _T& __val
    )
    {
      _ForwardIterator __it;
      typedef typename
        iterator::iterator_traits<_ForwardIterator>::difference_type
        __difference_type;
      __difference_type __len = iterator::distance(__first, __last);
      __difference_type __now;
      for(;__len > 0;)
      {
        __it = __first;
        __now = __len / 2;
        iterator::advance(__it, __now);
        if(!(__val < *__it))
        {
          __first = ++__it;
          __len -= __now + 1;
        }
        else
        { __len = __now;}
      }
      return __first;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_UPPER_BOUND__
