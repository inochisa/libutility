
#ifndef __UTILITY_ALGORITHM_SEARCH_N__
#define __UTILITY_ALGORITHM_SEARCH_N__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Search range for elements
     *
     * Searches the range [\a __first, \a __last) for
     * the first sequence of count identical elements using the given binary predicate.
     *
     * \tparam _ForwardIterator the iterator type
     * \tparam _Size            the length type usually is size_t or ptrdiff_t
     * \tparam _T               the value type
     * \tparam _BinaryPredicate the predicate type
     * \param __first,__last    the range of elements to examine
     * \param __size            the length of the sequence to search for
     * \param __val             the value of the elements to search for
     * \param __pred            binary predicate which returns ​\b true
     *                          if the elements should be treated as equal.<br/>
     *                          The signature of the predicate function
     *                          should be logically equivalent to the following:
     *                          \code{.cpp}
     *                            bool pred(const Type1&, const Type2&);
     *                          \endcode
     * \return Iterator to the beginning of the found sequence in the range [\a __first, \a __last).
     *         If no such sequence is found, \a __last is returned.
     */
    template<
      typename _ForwardIterator, typename _Size, typename _T,
      typename _BinaryPredicate
    >
    _ForwardIterator search_n(
      _ForwardIterator __first, _ForwardIterator __last,
      _Size __size, const _T& __val, _BinaryPredicate __pred
    )
    {
      for(; __first != __last; ++__first)
      {
        if(!__pred(*__first, __val))
        { continue;}
        _ForwardIterator __it = __first++;
        _Size __now = 1U;
        for(;; ++__first, ++__now)
        {
          if(__now == __size)
          { return __it;}
          if(__first == __last)
          { return __last;}
          if(!__pred(*__first, __val))
          { break;}
        }
      }
      return __last;
    }
    /**
     * \overload _ForwardIterator1 search(
     *   _ForwardIterator1 __first,  _ForwardIterator1 __last,
     *   _Size __size, const _T& __val
     * )
     *
     * this version use operator== as binary predicate
     */
    template<typename _ForwardIterator, typename _Size, typename _T>
    _ForwardIterator search_n(
      _ForwardIterator __first, _ForwardIterator __last,
      _Size __size, const _T& __val
    )
    {
      for(; __first != __last; ++__first)
      {
        if(!(*__first == __val))
        { continue;}
        _ForwardIterator __it = __first++;
        _Size __now = 1U;
        for(;; ++__first, ++__now)
        {
          if(__now == __size)
          { return __it;}
          if(__first == __last)
          { return __last;}
          if(!(*__first == __val))
          { break;}
        }
      }
      return __last;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_SEARCH_N__
