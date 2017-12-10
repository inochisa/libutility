
#ifndef __UTILITY_ALGORITHM_FOR_EACH__
#define __UTILITY_ALGORITHM_FOR_EACH__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Applies function to range
     *
     * Applies the given function object \a __unary to the result of
     * dereferencing every iterator in the range [\a __first, \a __last), in order.<br/>
     * if the iterator type is mutable, \a __unary may
     * modify the elements of the range through the dereferenced iterator.
     * If \a __unary returns a result, the result is ignored.<br/>
     * Unlike the rest of the algorithms,
     * for_each is not allowed to make copies of the elements
     * in the sequence even if they are trivially copyable.
     *
     * \tparam _InputIterator the iterator type
     * \tparam _UnaryFunction the function type
     * \param __first,__last the range to apply the function to
     * \param __unary function object, to be applied to the result of
     *                dereferencing every iterator in the range [\a __first, \a __last)<br/>
     *                The signature of the function should be logically equivalent to the following:
     *                \code{.cpp}
     *                void func(const Type&);
     *                void func(Types&);
     *                \endcode
     * \note Unlike standard library, this function return nothing.
     */
    template<typename _InputIterator, typename _UnaryFunction>
    inline void for_each(
      _InputIterator __first, _InputIterator __last,
      _UnaryFunction __unary
    )
    {
      for(; __first != __last;)
      { __unary(*__first++);}
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_FOR_EACH__
