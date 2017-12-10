
#ifndef __UTILITY_ALGORITHM_ADJACENT_FIND__
#define __UTILITY_ALGORITHM_ADJACENT_FIND__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Find equal adjacent elements in range
     *
     * Searches the range [\a __first, \a __last) for
     * two consecutive identical elements satisfied the binary predicate.
     *
     * \tparam _ForwardIterator the iterator type
     * \tparam _BinaryPredicate the predicate type
     * \param __first,__last 	the range of elements to examine
     * \param __pred          binary predicate which returns ​\b true if
     *                        the elements should be treated as equal.<br/>
     *                        The signature of the predicate function
     *                        should be logically equivalent to the following:
     *                        \code{.cpp}
     *                          bool pred(const Type1&, const Type2&);
     *                        \endcode
     * \return an iterator to the first of the first pair of identical elements
     *         satisfied the binary predicate.<br/>
     *         If no such elements are found, \a __last is returned
     */
    template<typename _ForwardIterator, typename _BinaryPredicate>
    _ForwardIterator adjacent_find(
      _ForwardIterator __first, _ForwardIterator __last,
      _BinaryPredicate __pred
    )
    {
      if(__first == __last)
      { return __first;}
      _ForwardIterator __next = __first;
      ++__next;
      for(;__next != __last;  ++__first, ++__next)
      {
        if(__pred(*__first, *__next))
        { return __first;}
      }
      return __last;
    }
    /**
     * \overload _ForwardIterator adjacent_find(
     *   _ForwardIterator __first, _ForwardIterator __last
     * )
     *
     * this version use operator== as binary predicate
     *
     */
    template<typename _ForwardIterator>
    _ForwardIterator adjacent_find(
      _ForwardIterator __first, _ForwardIterator __last
    )
    {
      if(__first == __last)
      { return __first;}
      _ForwardIterator __next = __first;
      ++__next;
      for(;__next != __last;  ++__first, ++__next)
      {
        if(*__first == *__next)
        { return __first;}
      }
      return __last;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_ADJACENT_FIND__
