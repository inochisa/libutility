
#ifndef __UTILITY_ALGORITHM_FIND_FIRST_OF__
#define __UTILITY_ALGORITHM_FIND_FIRST_OF__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Find element from set in range
     *
     * Searches the range [\a __first, \a __last) for any of the elements in the range [\a __ffirst, \a __flast) satisfy the binary predicate.
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
     * \return Iterator to the first element in the range [\a __first, \a __last)
     *         that is equal to an element from the range [\a __ffirst, \a __flast).<br/>
     *         If no such element is found, last is returned.
     */
    template<
      typename _InputIterator, typename _ForwardIterator,
      typename _BinaryPredicate
    >
    _InputIterator find_first_of(
      _InputIterator __first, _InputIterator __last,
      _ForwardIterator __ffirst, _ForwardIterator __flast,
      _BinaryPredicate __pred
    )
    {
      for(; __first != __last; ++__first)
      {
        for(_ForwardIterator __it = __ffirst; __it != __flast; ++__it)
        {
          if(__pred(*__first, *__it))
          { return __first;}
        }
      }
      return __last;
    }
    /**
     *
     * \overload _InputIterator find_first_of(
     * _InputIterator __first, _InputIterator __last,
     * _ForwardIterator __ffirst, _ForwardIterator __flast
     * )
     *
     * this version use operator== as binary predicate
     *
     */
    template<typename _InputIterator, typename _ForwardIterator>
    _InputIterator find_first_of(
      _InputIterator __first, _InputIterator __last,
      _ForwardIterator __ffirst, _ForwardIterator __flast
    )
    {
      for(; __first != __last; ++__first)
      {
        for(_ForwardIterator __it = __ffirst; __it != __flast; ++__it)
        {
          if(*__first == *__it)
          { return __first;}
        }
      }
      return __last;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_FIND_FIRST_OF__
