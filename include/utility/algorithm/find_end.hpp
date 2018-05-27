
#ifndef __UTILITY_ALGORITHM_FIND_END__
#define __UTILITY_ALGORITHM_FIND_END__

#include<utility/config/utility_config.hpp>
#include<utility/algorithm/search.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Find last subsequence in range
     *
     * Searches for the last subsequence of elements [\a __ffirst, \a __flast)
     * in the range [\a __first, \a __last) satisfied the \a __pred.
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
     * \return Iterator to the beginning of last subsequence
     *         [\a __ffirst, \a __flast) in range [first, last).<br/>
     *         If [\a __ffirst, \a __flast) is empty or
     *         if no such subsequence is found, \a __last is returned.
     */
    template<
      typename _ForwardIterator1, typename _ForwardIterator2,
      typename _BinaryPredicate
    >
    _ForwardIterator1 find_end(
      _ForwardIterator1 __first, _ForwardIterator1 __last,
      _ForwardIterator2 __ffirst, _ForwardIterator2 __flast,
      _BinaryPredicate __pred
    )
    {
      if(__ffirst == __flast)
      { return __last;}
      _ForwardIterator1 __it;
      for(;;)
      {
        _ForwardIterator1 __tit =
          algorithm::search(
            __first, __last, __ffirst, __flast, __pred
          );
        if(__tit == __last)
        { return __it;}
        __first = __it = __tit;
        ++__first;
      }
    }
    /**
     *
     * \overload _ForwardIterator1 find_end(
     * _ForwardIterator1 __first, _ForwardIterator1 __last,
     * _ForwardIterator2 __ffirst, _ForwardIterator2 __flast
     * )
     *
     * this version use operator== as binary predicate
     *
     */
    template<typename _ForwardIterator1, typename _ForwardIterator2>
    _ForwardIterator1 find_end(
      _ForwardIterator1 __first, _ForwardIterator1 __last,
      _ForwardIterator2 __ffirst, _ForwardIterator2 __flast
    )
    {
      if(__ffirst == __flast)
      { return __last;}
      _ForwardIterator1 __it;
      for(;;)
      {
        _ForwardIterator1 __tit =
          algorithm::search(
            __first, __last, __ffirst, __flast
          );
        if(__tit == __last)
        { return __it;}
        __first = __it = __tit;
        ++__first;
      }
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_FIND_END__
