
#ifndef __UTILITY_ALGORITHM_COPY_IF__
#define __UTILITY_ALGORITHM_COPY_IF__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Copy certain elements of range
     *
     * Copies the elements in the range, defined by [\a __first, \a __last),
     * to another range beginning at \a __ffirst,
     * and only copies the elements for which the predicate \a __unary returns \b true.
     * The order of the elements that are not removed is preserved.
     *
     * \tparam _InputIterator   the input iterator type
     * \tparam _OutputIterator  the output iterator type
     * \tparam _UnaryPredicate  the predicate type
     * \param __first,__last  the range of elements to copy
     * \param __ffirst        the beginning of the destination range.
     * \param __unary         unary predicate which returns ​\b true
     *                        for the required elements.<br/>
     *                        The signature of the predicate function
     *                        should be logically equivalent to the following:
     *                        \code{.cpp}
     *                          bool pred(const Type&);
     *                        \endcode
     * \return Output iterator to the element in the destination range,
     *         one past the last element copied.
     * \warning The behavior is undefined if the source and the destination ranges overlap.
     */
    template<typename _InputIterator,
      typename _OutputIterator, typename _UnaryPredicate>
    _OutputIterator copy_if(
      _InputIterator __first, _InputIterator __last,
      _OutputIterator __ffirst, _UnaryPredicate __unary
    )
    {
      for(;__first != __last; ++__first)
      {
        if(__unary(*__first))
        { *__ffirst++ = *__first;}
      }
      return __ffirst;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_COPY_IF__
