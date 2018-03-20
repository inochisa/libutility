
#ifndef __UTILITY_ALGORITHM_FIND_IF__
#define __UTILITY_ALGORITHM_FIND_IF__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * Finds value in range
     *
     * Returns the first element in the range [\a __first, \a __last)
     * that for which predicate \a __unary returns \b true
     *
     * \tparam _InputIterator   the iterator type
     * \tparam _UnaryPredicate  the predicate type
     * \param __first,__last the range of elements to examine
     * \param __unary        unary predicate which returns \b ​true for
     *                       the required element.<br/>
     *                       The signature of the predicate function
     *                       should be logically equivalent to the following:
     *                       \code{.cpp}
     *                         bool pred(const Type&);
     *                       \endcode
     * \return Iterator to the first element satisfying the condition
     *         or \a __last if no such element is found.
     */
    template<typename _InputIterator, typename _UnaryPredicate>
    inline _InputIterator find_if(
      _InputIterator __first, _InputIterator __last,
      _UnaryPredicate __unary
    )
    {
      for(; __first != __last; ++__first)
      {
        if(__unary(*__first))
        { return __first;}
      }
      return __last;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_FIND_IF__
