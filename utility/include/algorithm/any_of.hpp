
#ifndef __UTILITY_ALGORITHM_ANY_OF__
#define __UTILITY_ALGORITHM_ANY_OF__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Checks whether all elementes satisfied some condition.
     *
     * Checks if unary predicate \a __unary returns \b true
     * for at least one element in the range [\a __first, \a __last).
     *
     * \tparam _InputIterator     the iterator type
     * \tparam _UnaryPredicate    function object type
     * \param __first,__last the range of elements to examine
     * \param __unary unary predicate.<br/>
     *                The signature of the predicate function
     *                should be logically equivalent to the following:
     *                \code{.cpp}
     *                bool pred(const Type& a);
     *                \endcode
     * \return \b true if unary predicate returns \b true for at least one element
     *         in the range, \b false otherwise. Returns \b true if the range is empty.
     */
    template<typename _InputIterator, typename _UnaryPredicate>
    inline bool any_of(
      _InputIterator __first, _InputIterator __last,
      _UnaryPredicate __unary
    )
    {
      for(; __first != __last; ++__first)
      {
        if(__unary(*__first))
        { return true;}
      }
      return false;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_ANY_OF__
