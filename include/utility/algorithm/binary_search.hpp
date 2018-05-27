
#ifndef __UTILITY_ALGORITHM_BINARY_SEARCH__
#define __UTILITY_ALGORITHM_BINARY_SEARCH__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/lower_bound.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Test if value exists in sorted sequence
     *
     * Checks if an element equivalent to value appears within the range [\a __first, \a __last).
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
     * \return \b true if an element equal to value is found, \b false otherwise.
     * \attention The range [\a __first, \a __last) must be at least partially ordered.
     * \note The number of comparisons performed is logarithmic in the distance between
     *       \a __firs and \a __last (At most log(last - first) + O(1) comparisons).
     *       However, for non-RandomAccessIterators,
     *       the number of iterator increments is linear.
     */
    template<typename _ForwardIterator, typename _T, typename _Compare>
    bool binary_search(
      _ForwardIterator __first, _ForwardIterator __last,
      const _T& __val, _Compare __compare
    )
    {
      __first =
        algorithm::lower_bound(__first, __last, __val, __compare);
      return !(__first == __last) && !(__compare(__val, *__first));
    }
    /**
     * \overload _ForwardIterator binary_search(
     *   _ForwardIterator __first, _ForwardIterator __last,
     *   const _T& __val
     * )
     *
     * this version use operator< as comparison function object
     *
     */

    template<typename _ForwardIterator, typename _T>
    bool binary_search(
      _ForwardIterator __first, _ForwardIterator __last,
      const _T& __val
    )
    {
      __first =
        algorithm::lower_bound(__first, __last, __val);
      return !(__first == __last) && !(__val < *__first);
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_BINARY_SEARCH__

