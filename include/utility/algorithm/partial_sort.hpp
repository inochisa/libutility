
#ifndef __UTILITY_ALGORITHM_PARTIAL_SORT__
#define __UTILITY_ALGORITHM_PARTIAL_SORT__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/swap.hpp>
#include<utility/algorithm/heap.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Partially sort elements in range
     *
     * Rearranges elements such that the range [\a __first, \a __middle)
     * contains the sorted \a __middle - \a __first smallest elements
     * in the range [\a __first, \a __last).
     *
     * \param __first,__last  the range of elements to sort
     * \param __mid           iterator to the pivor elements
     * \param __compare       comparison function object.<br/>
     *                        The signature of the comparison function
     *                        should be logically equivalent to the following:
     *                        \code{.cpp}
     *                          bool cmp(const Type1&, const Type2&);
     *                        \endcode
     * \attention The order of equal elements is not guaranteed to be preserved.
     *            The order of the remaining elements in the range
     *            [\a __middle, \a __last) is unspecified.
     */
    template<typename _RandomAccessIterator, typename _Compare>
    void partial_sort(
      _RandomAccessIterator __first, _RandomAccessIterator __middle,
      _RandomAccessIterator __last, _Compare __compare
    )
    {
      typedef typename
        iterator::iterator_traits<_RandomAccessIterator>::difference_type
        __difference_type;
      make_heap(__first, __middle, __compare);
      for(_RandomAccessIterator __i = __middle; __i < __last; ++__i)
      {
        if(__compare(*__i, *__first))
        {
          algorithm::swap(*__i, *__first);
          detail::__pop_heap_aux(
            __first, __difference_type(__middle-__first-1), __compare
          );
        }
      }
      sort_heap(__first, __middle, __compare);
    }
    /**
     * \overload inline void partial_sort(
     *   _RandomAccessIterator __first, _RandomAccessIterator __middle,
     *   _RandomAccessIterator __last
     * )
     *
     * this version use operator< as comparison function object
     *
     */
    template<typename _RandomAccessIterator>
    inline void partial_sort(
      _RandomAccessIterator __first, _RandomAccessIterator __middle,
      _RandomAccessIterator __last
    )
    {
      typedef typename
        iterator::iterator_traits<_RandomAccessIterator>::value_type
        __value_type;
        partial_sort(__first, __last, algorithm::less<__value_type>());
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_PARTIAL_SORT__
