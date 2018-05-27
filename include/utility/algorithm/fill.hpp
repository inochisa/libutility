
#ifndef __UTILITY_ALGORITHM_FILL__
#define __UTILITY_ALGORITHM_FILL__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace algorithm
  {
    /**
     * \brief Fill range with value
     *
     * Assigns the given value to the elements in the range [ \a __first, \a __last).
     *
     * \tparam _ForwardIterator the range iterator
     * \tparam _T               the value type
     * \param __first,__last    the range of elements to modify
     * \param __val             the value to be assigned
     */
    template<typename _ForwardIterator, typename _T>
    void fill(
      _ForwardIterator __first, _ForwardIterator __last,
      const _T& __val
    )
    {
      for(;__first != __last;)
      { *__first++ = __val;}
    }
  }
}

#endif // ! __UTILITY_ALGORITHM_FILL__
