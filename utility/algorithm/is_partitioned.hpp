
#ifndef __UTILITY_ALGORITHM_IS_PARTITIONED__
#define __UTILITY_ALGORITHM_IS_PARTITIONED__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Test whether range is partitioned
     *
     * Returns true if all elements in the range [\a __first, \a __last)
     * that satisfy the predicate \a __unary appear before all elements that don't.
     * Also returns true if [\a __first, \a __last) is empty.
     *
     * \param __first,__last  the range of elements to check
     * \param __unary         unary predicate which returns \b ​true for the elements
     *                        expected to be found in the beginning of the range.
     *                        The signature of the predicate function
     *                        should be logically equivalent to the following:
     *                        \code{.cpp}
     *                          bool pred(const Type&);
     *                        \endcode
     * \return \b true if the range [\a __first, \a __last) is empty or
     *         is partitioned by \a __unary. \b false otherwise.
     */
    template<typename _InputIterator, typename _UnaryPredicate>
    bool is_partitioned(
      _InputIterator __first, _InputIterator __last,
      _UnaryPredicate __unary
    )
    {
      for(;__first != __last; ++__first)
      {
        if(!__unary(*__first))
        { break;}
      }
      for(;__first != __last; ++__first)
      {
        if(__unary(*__first))
        { return false;}
      }
      return true;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_IS_PARTITIONED__
