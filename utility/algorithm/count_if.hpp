
#ifndef __UTILITY_ALGORITHM_COUNT_IF__
#define __UTILITY_ALGORITHM_COUNT_IF__

#include<utility/config/utility_config.hpp>
#include<utility/iterator/iterator_traits.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Return number of elements in range satisfying condition
     *
     * Returns the number of elements in the range [\a __first, \a __last)
     * that for which predicate \a __unary returns \b true.
     *
     * \tparam _InputIterator the iterator type
     * \tparam _T             the value type
     * \param __first,__last  the range of elements to examine
     * \param __unary         unary predicate which returns ​\b true for the required elements.<br/>
     *                        The signature of the predicate function should be logically
     *                        equivalent to the following:
     *                        \code{.cpp}
     *                          bool pred(const Type&);
     *                        \endcode
     * \return number of elements satisfying the condition.
     */
    template<typename _InputIterator, typename _UnaryPredicate>
    inline
    typename
    iterator::iterator_traits<_InputIterator>::difference_type
    count_if(
      _InputIterator __first, _InputIterator __last,
      _UnaryPredicate __unary
    )
    {
      typedef typename
        iterator::iterator_traits<_InputIterator>::difference_type
        __difference_type;
      __difference_type __res = 0;
      for(; __first != __last;)
      {
        if(__unary(*__first++))
        { ++__res;}
      }
      return __res;
    }

  }
}

#endif // ! __UTILITY_ALGORITHM_COUNT_IF__
