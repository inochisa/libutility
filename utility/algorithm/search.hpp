
#ifndef __UTILITY_ALGORITHM_SEARCH__
#define __UTILITY_ALGORITHM_SEARCH__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Search range for subsequence
     *
     * Searches for the first occurrence of the subsequence of elements
     * [\a __ffirst, \a __flast) in the range
     * [\a __first, \a __last - (\a __flast - \a __ffirst))
     * using the given binary predicate \a __pred
     *
     * \tparam _ForwardIterator1,_ForwardIterator2 the iterator type
     * \tparam _BinaryPredicate the predicate type
     * \param __first,__last    the range of elements to examine
     * \param __ffirst,__flast 	the range of elements to search for
     * \param __pred            binary predicate which returns ​\b true
     *                          if the elements should be treated as equal.<br/>
     *                          The signature of the predicate function
     *                          should be logically equivalent to the following:
     *                          \code{.cpp}
     *                            bool pred(const Type1&, const Type2&);
     *                          \endcode
     * \return Iterator to the beginning of first subsequence [\a __ffirst, \a __flast)
     *         in the range [\a __first, \a __last - (\a __flast - \a __ffirst)).
     *         If no such subsequence is found, \a __last is returned.<br/>
     *         If [\a __ffirst, \a __flast) is empty, \a __first is returned.
     */
    template<
      typename _ForwardIterator1, typename _ForwardIterator2,
      typename _BinaryPredicate
    >
    _ForwardIterator1 search(
      _ForwardIterator1 __first,  _ForwardIterator1 __last,
      _ForwardIterator2 __ffirst, _ForwardIterator2 __flast,
      _BinaryPredicate __pred
    )
    {
      for(;; ++__first)
      {
        _ForwardIterator1 __it = __first;
        for(_ForwardIterator2 __tit = __ffirst;; ++__it, ++__tit)
        {
          if(__tit == __flast)
          { return __it;}
          if(__it == __last)
          { return __last;}
          if(!__pred(*__it, *__tit))
          { break;}
        }
      }
    }
    /**
     * \overload _ForwardIterator1 search(
     *   _ForwardIterator1 __first,  _ForwardIterator1 __last,
     *   _ForwardIterator2 __ffirst, _ForwardIterator2 __flast
     * )
     *
     * this version use operator== as binary predicate
     */
    template<typename _ForwardIterator1, typename _ForwardIterator2>
    _ForwardIterator1 search(
      _ForwardIterator1 __first,  _ForwardIterator1 __last,
      _ForwardIterator2 __ffirst, _ForwardIterator2 __flast
    )
    {
      for(;; ++__first)
      {
        _ForwardIterator1 __it = __first;
        for(_ForwardIterator2 __tit = __ffirst;; ++__it, ++__tit)
        {
          if(__tit == __flast)
          { return __it;}
          if(__it == __last)
          { return __last;}
          if(!(*__it == *__tit))
          { break;}
        }
      }
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_SEARCH__
