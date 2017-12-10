
#ifndef __UTILITY_ALGORITHM_FOR_EACH_N__
#define __UTILITY_ALGORITHM_FOR_EACH_N__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Applies function to n element
     *
     * Applies the given function object \a __unary to the result of
     * dereferencing every iterator in the range [\a __first, \a __first + \a __size), in order.<br/>
     * if the iterator type is mutable, \a __unary may
     * modify the elements of the range through the dereferenced iterator.
     * If \a __unary returns a result, the result is ignored.<br/>
     * Unlike the rest of the algorithms,
     * for_each is not allowed to make copies of the elements
     * in the sequence even if they are trivially copyable.
     *
     * \tparam _InputIterator the iterator type
     * \tparam _Size          the size type, usually is \a size_t or \a ptrdiff_t.
     * \tparam _UnaryFunction the function type
     * \param __first the begint of the range to apply the function to
     * \param __unary function object, to be applied to the result of
     *                dereferencing every iterator in the range [\a __first, \a __first + \a __size)<br/>
     *                The signature of the function should be logically equivalent to the following:
     *                \code{.cpp}
     *                void func(const Type&);
     *                void func(Types&);
     *                \endcode
     * \return \a __first + \a __size
     */
    template<typename _InputIterator, typename _Size, typename _UnaryFunction>
    inline _InputIterator for_each_n(
      _InputIterator __first, _Size __size,
      _UnaryFunction __unary
    )
    {
      for(_Size __i = 0; __i < __size; ++__first)
      { __unary(*__first);}
      return __first;
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_FOR_EACH_N__
