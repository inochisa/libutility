
#ifndef __UTILITY_ALGORITHM_TRANSFORM__
#define __UTILITY_ALGORITHM_TRANSFORM__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Transform range
     *
     * Applies the given function to a range and stores the result
     * in another range, beginning at \a __ffirst.
     *
     * \tparam _InputIterator   the input iterator type
     * \tparam _OuputIterator   the ouput iterator type
     * \tparam _UnaryOperation  the operation type
     * \param __first,__last  the first range of elements to transform
     * \param __ffirst        the beginning of the destination range,
     *                        may be equal to \a __first
     * \param __unary_op      unary operation function object that will be applied.<br/>
     *                        The signature of the function
     *                        should be logically equivalent to the following:
     *                        \code{.cpp}
     *                          Ret fun(const Type&);
     *                        \endcode
     * \return Output iterator to the element past the last element transformed.
     */
    template<typename _InputIterator, typename _OuputIterator, typename _UnaryOperation>
    _OuputIterator transform(
      _InputIterator __first, _InputIterator __last,
      _OuputIterator __ffirst, _UnaryOperation __unary_op
    )
    {
      for(;__first != __last)
      { *__ffirst++ = __unary_op(*__first++);}
      return __first;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_TRANSFORM__
